void initextmems() {
  
  for (int j = 0; j < pbars; j++) {
    pp.sampler_off_pat[j] = {0,0,0};
    _pe.temp_sampler_partition[j] = {0,0,0};
    for (int i = 0; i < FLASH_LINERS_COUNT; i++) {
      pp.flash_notes_length[i][j] = 0;
      pp.sampler_partition[i][j] = {0,0,0};
    }
    pp.track_cells[0][j] = 0;
    pp.track_cells[1][j] = 0;
    _pe.temp_synth_partition[j] = {0,0,0};
    for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
      pp.synth_notes_length[i][j] = 0;
      pp.synth_partition[i][j] = {0,0,0};
      pp.synth_off_pat[i][j] = {0,0,0};
    }

    for (int i = 0; i < 128; i++) {
      if (!j) leccinterpolated[i] = 0;
      pp.cc_partition[i][j] = 127;
    }
  }
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 32; j++) {
      pots_controllers[i][j][0] = 0;
      pots_controllers[i][j][1] = 0;
    }
    recorded_ccs[i] = 0 ;
  }
}

void unplug_notefreq_from_ampL(){
  Notespy_cable.disconnect();
}
void replug_notefreq_from_ampL(){
  Notespy_cable.connect();
}

void loadsynthdefaults() {

  AudioNoInterrupts();
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    enveloppesL[i]->delay(gg.adsrlevels[AttackDelay]);
    enveloppesL[i]->attack(gg.adsrlevels[Attack]);
    // enveloppesL[i]->hold(gg.adsrlevels[2]);
    enveloppesL[i]->decay(gg.adsrlevels[Decay]);
    enveloppesL[i]->sustain(gg.adsrlevels[Sustain]);
    enveloppesL[i]->release(gg.adsrlevels[Release]);
    //enveloppesL[i]->releaseNoteOn(20);
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
  _ft.le303filterzWet();

  _ft.le303filtercontrols();
  AudioInterrupts();
}

void setupdefaultvalues() {
  _ft.initialize303group();
  ampL.gain(1.0);
  ampR.gain(1.0);
  // ADSR & synths
  loadsynthdefaults();


  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    for (int j = 0; j < OSCS_COUNT; j++) {
      Wavesmix[i]->gain(j, gg.mixlevelsL[j]/127.0);
    }
  }

  for (int i = 0; i < FLASH_LINERS_COUNT; i++) {
    //for (int j = 0; j < 4; j++) {
      Flashmixer[int(i / 4)]->gain(i - 4 * int(i / 4),1.0);
    //}
  }

  unplug_notefreq_from_ampL();
  for (int i = 0; i < fxs_count; i++) {
    fx[i]->stopdelayline();
    delayCords[i]->disconnect();
    delayCordsR[i]->disconnect();

  }
  AudioNoInterrupts();
  for (int i = 0; i < fxs_count; i++) {
    delaypostmix[i]->gain(0, 1);
    delaypostmix[i]->gain(1, 1);
    delaypostmixR[i]->gain(0, 1);
    delaypostmixR[i]->gain(1, 1);
    delayfeedbackmix[i]->gain(0, 1);
    delayfeedbackmix[i]->gain(1, 0);
    delayfeedbackmixR[i]->gain(0, 1);
    delayfeedbackmixR[i]->gain(1, 0);
    //loop of 4 channels, not OSCS_COUNT
    for (int j = 0; j < 4; j++) {
      lesdelays[i]->disable(2 * j);
      lesdelays[i]->disable(2 * j + 1);
      lesdelaysR[i]->disable(2 * j);
      lesdelaysR[i]->disable(2 * j + 1);

      delaypremix[i * 2]->gain(j, 0);
      delaypremix[i * 2 + 1]->gain(j, 0);
      delaypremixR[i * 2]->gain(j, 0);
      delaypremixR[i * 2 + 1]->gain(j, 0);

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
  MasterL.gain(2, 1.0);
  MasterR.gain(2, 1.0);
  //PlayRaw
  MasterL.gain(3, 1.0);
  MasterR.gain(3, 1.0);

  WetMixMasterL.gain(0, 1);
  WetMixMasterR.gain(0, 1);


  //needed to level fxBus & gg.wetins
  for (int i = 0; i < 3; i++) {
    _mx.set_dry_mix(i);
  }
  // if MULTIPLEXED_PADS
  for (int i = 0; i < all_buttonns; i++) {
    if (!((i <= 11) || (i >= 46))) {
      gg.pot_assignements[i] = i + 128 + 30;
    } else {
      gg.pot_assignements[i] = gg.ordered_pots[Pads.potsboards[i]];
    }
  }

  // Volume
  gg.midiknobassigned[11] = 1;
  gg.midiknobassigned[12] = 2;
  //gg.midiknobassigned[13] = 3;
  // FX Wet
  gg.midiknobassigned[20] = 5;
  //in levels
  gg.midiknobassigned[21] = 89;
  gg.midiknobassigned[22] = 118;
  //audio In level
  //gg.midiknobassigned[22] = 97;

  // fidx crossfader
  //gg.midiknobassigned[10] = 69;

  // 303 pulse
  //gg.midiknobassigned[23] = 20;
  //gg.midiknobassigned[24] = 21;
/*/
  

  gg.pot_assignements[all_buttonns-10] = 108 ;
  gg.pot_assignements[all_buttonns-9] = 107 ;
  */
  //gg.midiknobassigned[111] = 109 ;
  //98 debugcpu
  //pots_assignements are to map onboard buttons to midi notes or ccs
  //gg.pot_assignements[all_buttonns-5] = 106 ;
  gg.pot_assignements[all_buttonns-20] = 110 ;
  gg.pot_assignements[all_buttonns-21] = 109 ;
  gg.pot_assignements[all_buttonns-19] = 111 ;

  gg.pot_assignements[all_buttonns-12] = 108 ;
  gg.pot_assignements[all_buttonns-11] = 107 ;
  gg.pot_assignements[all_buttonns-10] = 106 ;

  gg.midiknobassigned[gg.alt_nav[2]] = 125 ;
  gg.midiknobassigned[gg.alt_nav[3]] = 126 ;
  gg.midiknobassigned[gg.alt_nav[0]] = 123 ;
  gg.midiknobassigned[gg.alt_nav[1]] = 124 ;



  gg.pot_assignements[all_buttonns-4] = 100 ;
  gg.pot_assignements[all_buttonns-13] = 101 ;
  //osc toggles
  //midiknobs link a midi cc note to an index from ctl[] 
  gg.midiknobassigned[100] = 116 ;
  gg.midiknobassigned[101] = 117 ;
  //gg.midiknobassigned[106] = 98;
  //granular fx toggle
  //gg.midiknobassigned[100] = 78;
    //phase
  //gg.midiknobassigned[17] = 76;
  //gg.midiknobassigned[18] = 77;
  //gg.midiknobassigned[19] = 81;

 // gg.midiknobassigned[14] = 93;
 // gg.midiknobassigned[15] = 94;
 // gg.midiknobassigned[16] = 95;


  //note: WetMixMasterLs[0] is the dry channel
  for (int i = 0; i < OSCS_COUNT; i++) {
    oscillator = i;
    call_setwavetypefromlist();
  }
  // USB Line in
  InMixL.gain(0, 1.0);
  InMixR.gain(0, 1.0);
  // LineIn
  InMixL.gain(1,1.0);
  InMixR.gain(1, 1.0);
  //mp3 player
  InMixL.gain(2, 1.0);
  InMixR.gain(2, 1.0);
  InMixL.gain(3, 0.0);
  InMixR.gain(3, 0.0);
  
  sd_mixerL.gain(0, 1.0);
  sd_mixerR.gain(0, 1.0);

  sd_mixerL.gain(1, 1.0);
  sd_mixerR.gain(1, 1.0);

  sd_mixerL.gain(2, 1.0);
  sd_mixerR.gain(2, 1.0);

  sd_mixerL.gain(3, 0.0);
  sd_mixerR.gain(3, 0.0);

  LineInPreAmpL.gain(1.0);
  LineInPreAmpR.gain(1.0);
}
