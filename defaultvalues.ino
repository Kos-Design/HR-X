void initextmems() {
  for (int i = 0; i < nombreofSamplerliners; i++) {
    for (int j = 0; j < pbars; j++) {

      for (int k = 0; k < 3; k++) {
        sampler_off_pat[j][k] = 0;
        sampler_partition[i][j][k] = 0;
        temp_sampler_partition[i][j][k] = 0;
      }
    }
  }
  for (int i = 0; i < liners_count; i++) {
    for (int j = 0; j < pbars; j++) {
      length0pbars[i][j] = 0;
      templength0pbars[i][j] = 0;
      length1notes1[i][j] = 0;
      for (int k = 0; k < 3; k++) {
        synth_off_pat[i][j][k] = 0;
        synth_partition[i][j][k] = 0;
        temp_synth_partition[i][j][k] = 0;
      }
    }
  }
  for (int i = 0; i < 128; i++) {
    leccinterpolated[i] = 0;
    for (int j = 0; j < pbars; j++) {
      cc_partition[i][j] = 127;

    }
  }
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 32; j++) {
      pots_controllers[i][j][0] = 0;
      pots_controllers[i][j][1] = 0;
    }
    recorded_ccs[i] = 0 ;
  }

    for (int i = 0; i < fxs_count; i++) {
      for (int j = 0; j < bqstagesnum; j++) {
          bqslope[i][j] = 0.0;
          bqgain[i][j] = 0.0;
          bqfreq[i][j] = 0.0;
          bqtype[i][j] = 0.0;
          bqVpot[i][j][0] = 0;
          bqVpot[i][j][1] = 0;
          bqVpot[i][j][2] = 0;
      }
    }
    for (int i = 0; i < GRANULAR_MEMORY_SIZE; i++) {
      granularMemory[i] = 0;
      granularMemory2[i] = 0;
      granularMemory3[i] = 0;
    }
    for (int i = 0; i < FLANGE_DELAY_LENGTH; i++) {
      flangedelay[i] = 0;
      flangedelay2[i] = 0;
      flangedelay3[i] = 0;
    }
    for (int i = 0; i < CHORUS_DELAY_LENGTH; i++) {
      chorusdelayline[i] = 0;
      chorusdelayline2[i] = 0;
      chorusdelayline3[i] = 0;
    }
  // ignorethatcc[88] = true;
}

void unplug_notefreq_from_ampL(){
  Notespy_cable.disconnect();
}
void replug_notefreq_from_ampL(){
  Notespy_cable.connect();
}

void loadsynthdefaults() {

  AudioNoInterrupts();

  adsrlevels[0] = MadsrAttackDelay;
  adsrlevels[1] = mappedattack;
  adsrlevels[3] = mappeddecay;
  adsrlevels[4] = float(mappedsustain / 100);
  adsrlevels[5] = mappedrelease;

  for (int i = 0; i < liners_count; i++) {
    enveloppesL[i]->delay(adsrlevels[0]);
    enveloppesL[i]->attack(adsrlevels[1]);
    // enveloppesL[i]->hold(adsrlevels[2]);
    enveloppesL[i]->decay(adsrlevels[3]);
    enveloppesL[i]->sustain(adsrlevels[4]);
    enveloppesL[i]->release(adsrlevels[5]);
    enveloppesL[i]->releaseNoteOn(20);
  }

  //ch 0 is the sum of signals sent to fx should stay at 1
  FXBusL.gain(0,1.0);
  FXBusR.gain(0,1.0);
  //1 = dry flash
  FXBusL.gain(1,1.0);
  FXBusR.gain(1,1.0);
  //2 = dry synth
  FXBusL.gain(2,1.0);
  FXBusR.gain(2,1.0);
  //3 = dry others ( IN, metro, SDWav)
  FXBusL.gain(3,1.0);
  FXBusR.gain(3,1.0);

  mixerWL1to4.gain(0, .25);
  mixerWL1to4.gain(1, .25);
  mixerWL1to4.gain(2, .25);
  mixerWL1to4.gain(3, .25);
  mixerWL5to8.gain(0, .25);
  mixerWL5to8.gain(1, .25);
  mixerWL5to8.gain(2, 0.0);
  mixerWL5to8.gain(3, 0.0);

  le303filtercontrols();
  AudioInterrupts();
}

void setupdefaultvalues() {
  initialize303group();
  ampL.gain(1);
  ampR.gain(1);
  // ADSR & synths
  loadsynthdefaults();
  premixMaster.gain(0, 0.5);
  premixMaster.gain(1, 0.5);

  for (int i = 0; i < liners_count; i++) {
    for (int j = 0; j < synths_count; j++) {
      Wavesmix[i]->gain(j, mixlevelsL[j]/127.0);
    }
  }
  unplug_notefreq_from_ampL();
  for (int i = 0; i < fxs_count; i++) {
    fx[i]->stopdelayline();
    delayCords[i]->disconnect();
  }
  AudioNoInterrupts();
  for (int i = 0; i < fxs_count; i++) {
    delaypostmix[i]->gain(0, 1);
    delaypostmix[i]->gain(1, 1);
    delayfeedbackmix[i]->gain(0, 1);
    delayfeedbackmix[i]->gain(1, 0);
    delayprefeed[i]->gain(0, 1);
    delayprefeed[i]->gain(1, 1);
    //for loop of 4 for convenience, not related to synths_count
    for (int j = 0; j < 4; j++) {
      lesdelays[i]->disable(2 * j);
      lesdelays[i]->disable(2 * j + 1);
      delaypremix[i * 2]->gain(j, 0);
      delaypremix[i * 2 + 1]->gain(j, 0);
    }
    AudioInterrupts();
  }
  //mixed others wet
  MasterL1.gain(0, 0);
  MasterR1.gain(0, 0);
  //nothing
  MasterL1.gain(1, 0);
  MasterR1.gain(1, 0);
  //synth wet
  MasterL1.gain(2, 0);
  MasterR1.gain(2, 0);
  //flash wet
  MasterL1.gain(3, 0);
  MasterR1.gain(3, 0);
  // Wavplayer
  MasterL.gain(0, 1.0);
  MasterR.gain(0, 1.0);
  //metrodrum
  MasterL.gain(1, 0);
  MasterR.gain(1, 0);
  //Input
  MasterL.gain(2, 0);
  MasterR.gain(2, 0);
  //PlayRaw
  MasterL.gain(3, 1.0);
  MasterR.gain(3, 1.0);

  WetMixMasterL.gain(0, 1);
  WetMixMasterR.gain(0, 1);

  //needed to level fxBus & wetins
  for (int i = 0; i < 3; i++) {
    set_dry_mix(i);
  }

  for (int i = 0; i < all_buttonns; i++) {
    if (!((i <= 11) || (i >= 46))) {
      pot_assignements[i] = i + 128 + 30;
    } else {
      pot_assignements[i] = ordered_pots[potsboards[i]];
    }
  }

  // Volume
  midiknobassigned[11] = 1;
  midiknobassigned[12] = 2;
  //midiknobassigned[13] = 3;

  midiknobassigned[14] = 93;
  midiknobassigned[15] = 94;
  midiknobassigned[16] = 95;

  //phase
  midiknobassigned[17] = 76;
  midiknobassigned[18] = 77;
  midiknobassigned[19] = 81;

  // FX Wet
  midiknobassigned[20] = 5;
  midiknobassigned[21] = 6;
  //audio In level
  midiknobassigned[22] = 97;

  // ccfxlineselector crossfader
  midiknobassigned[10] = 69;

  // 303 pulse
  midiknobassigned[23] = 20;
  midiknobassigned[24] = 21;

  pot_assignements[all_buttonns-4] = 100 ;
  pot_assignements[all_buttonns-13] = 101 ;
  pot_assignements[all_buttonns-18] = 111 ;
  pot_assignements[all_buttonns-19] = 110 ;
  pot_assignements[all_buttonns-10] = 108 ;
  pot_assignements[all_buttonns-9] = 107 ;
  midiknobassigned[111] = 109 ;
  //98 debugcpu
  pot_assignements[all_buttonns-5] = 106 ;
  //midiknobassigned[106] = 98;
  //granular fx toggle
  midiknobassigned[100] = 78;

  //note: WetMixMasterLs[0] is the dry channel
  for (int i = 0; i < synths_count; i++) {
    ccsynthselector = i;
    call_setwavetypefromlist();
  }
  // USB Line in
  InMixL.gain(0, 0);
  InMixR.gain(0, 0);
  // LineIn
  InMixL.gain(1,1.0);
  InMixR.gain(1, 1.0);
  //mp3 player
  InMixL.gain(2, 1.0);
  InMixR.gain(2, 1.0);
  InMixL.gain(3, 1.0);
  InMixR.gain(3, 1.0);
  LineInPreAmpL.gain(1.0);
  LineInPreAmpR.gain(1.0);
}
