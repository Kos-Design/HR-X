void initextmems() {
  for (int i = 0; i < nombreofSamplerliners; i++) {
    for (int j = 0; j < pbars; j++) {
      // length2notes1[i][j] = 0 ;
      // length2pbars[i][j] = 0 ;
      // templength2pbars[i][j] = 0 ;

      for (int k = 0; k < 3; k++) {
        sampler_off_pat[j][k] = 0;
        sampler_partition[i][j][k] = 0;
        temp_sampler_partition[i][j][k] = 0;
      }
    }
  }
  for (int i = 0; i < nombreofliners; i++) {
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
      cc_partition[i][j] = 128;
      
    }
  }
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 32; j++) {
      pots_controllers[i][j][0] = 0;
      pots_controllers[i][j][1] = 0;
    }
    recorded_ccs[i] = 0 ;
  }
  // ignorethatcc[88] = true;
}

void unplug_delays_from_feedback(int delay_line){

    delayCords[delay_line]->disconnect();
    
}
void replug_delays_from_feedback(int delay_line){
    
    delayCords[delay_line]->connect();

  
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
  
  for (int i = 0; i < nombreofliners; i++) {
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
  initializefxmoduleisconnected();
  initialize303group();

  ampL.gain(1);
  ampR.gain(1);


  // ADSR & synths
  loadsynthdefaults();

  premixMaster.gain(0, 0.5);
  premixMaster.gain(1, 0.5);

  for (int i = 0; i < nombreofliners; i++) {
    for (int j = 0; j < numberofsynthsw; j++) {
      Wavesmix[i]->gain(j, mixlevelsL[j]);
    }
  }
  unplug_notefreq_from_ampL();
  for (int i = 0; i < fxiterations; i++) {
    stopdelayline(i);
    unplug_delays_from_feedback(i);
  }
  //we begin these on fx asignement only
  /*
  chorus1.begin(chorusdelayline, CHORUS_DELAY_LENGTH, chorusvoices);
  chorus2.begin(chorusdelayline2, CHORUS_DELAY_LENGTH, chorusvoices);
  chorus3.begin(chorusdelayline3, CHORUS_DELAY_LENGTH, chorusvoices);

  // FX
  flange1.begin(flangedelay, FLANGE_DELAY_LENGTH, flangeoffset, flangedepth,
                flangefreq);
  flange2.begin(flangedelay2, FLANGE_DELAY_LENGTH, flangeoffset, flangedepth,
                flangefreq);
  flange3.begin(flangedelay3, FLANGE_DELAY_LENGTH, flangeoffset, flangedepth,
                flangefreq);

  granular1.begin(granularMemory, GRANULAR_MEMORY_SIZE);
  granular2.begin(granularMemory2, GRANULAR_MEMORY_SIZE);
  granular3.begin(granularMemory3, GRANULAR_MEMORY_SIZE);
*/

  for (int i = 0; i < numberofsynthsw; i++) {
    setwavetypefromlist(i, Waveformstyped[i]);
  }
  AudioNoInterrupts();
  for (int i = 0; i < fxiterations; i++) {
    // lfo sines used by FXes, only amplitude freq & phase
    //lfosinez[i]->amplitude(0.1);
    //lfosinez[i]->frequency(5);
    delaypostmix[i]->gain(0, 1);
    delaypostmix[i]->gain(1, 1);
    delayfeedbackmix[i]->gain(0, 1);
    delayfeedbackmix[i]->gain(1, 0);
    delayprefeed[i]->gain(0, 1);
    delayprefeed[i]->gain(1, 1);
    //for loop of 4 for convenience, not related to numberofsynthsw
    for (int j = 0; j < 4; j++) {
      lesdelays[i]->disable(2 * j);
      lesdelays[i]->disable(2 * j + 1);
      delaypremix[i * 2]->gain(j, 0);
      delaypremix[i * 2 + 1]->gain(j, 0);
    }
    AudioInterrupts();
    /*
    flange[i]->voices(flangeoffset, flangedepth, flangefreq);
    chorus[i]->voices(chorusvoices);
    granular[i]->setSpeed(1.0);
    */
  }

  ////
  // PlayFlash

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
      // pot_assignements[i] = i ;
      // midiknobassigned[pot_assignements[i]] = pot_assignements[i];
    } else {
      pot_assignements[i] = ordered_pots[potsboards[i]];
    }
  }
  /*for (int i = 0; i < 15 ; i++) {
    ordered_pots[i] = i ;
  }*/
  // pot_assignements[35] = 64 ;

  // test
  // pot_assignements[44] = allfxes + 64 ;

  /*
   //Defaults for external midi keyboard
  midiknobassigned[91]=2;

  //play
  midiknobassigned[85]= 36 ;
  //stop
  midiknobassigned[81]= 37 ;
  //rec
  midiknobassigned[84]= 39 ;

  //Wet1
  midiknobassigned[75]= 6 ;
  //wet2
  midiknobassigned[76]= 7;
  //wet3
  midiknobassigned[77]= 8 ;
  //cueplay on Vbuttons
  midiknobassigned[32]= 35 ;
  //wet303
  midiknobassigned[73]= 18;
  //ccrecord
  midiknobassigned[87]= 44;
  //synthselect
  midiknobassigned[15]= 45;
  //fxmoduleselect
  midiknobassigned[72]= 69;
  //showallnotes
  midiknobassigned[67]= 100;
  //BPM
  midiknobassigned[20]= 15;
  */

  // Volume
  midiknobassigned[11] = 2;
  midiknobassigned[12] = 1;
  //midiknobassigned[13] = 3;

  
  midiknobassigned[14] = 93;
  midiknobassigned[15] = 94;
  midiknobassigned[16] = 95;
  

  // lfos
  //phase
  midiknobassigned[17] = 56;
  midiknobassigned[18] = 53;
  midiknobassigned[19] = 55;
  

  // FX Wet
  midiknobassigned[20] = 6;
  midiknobassigned[21] = 7;
  //audio In level
  midiknobassigned[22] = 97;

  // ccfxlineselector crossfader
  midiknobassigned[10] = 69;

  // LFO freq & level
  midiknobassigned[23] = 20;
  midiknobassigned[24] = 21;
  pot_assignements[all_buttonns-4] = 100 ;

  //101 is parsepreset(0)
  pot_assignements[all_buttonns-13] = 101 ;
  pot_assignements[all_buttonns-18] = 111 ;
  midiknobassigned[111] = 109 ;
  //98 debugcpu
  pot_assignements[all_buttonns-5] = 106 ;
  //midiknobassigned[106] = 98;
  midiknobassigned[100] = 107;
  //midiknobassigned[101] = 108;
  //midiknobassigned[111] = 109;
  
  // stop
  midiknobassigned[110] = 37;
  // play
  midiknobassigned[108] = 36;
  // looper
  //midiknobassigned[109] = 109;
  //note: WetMixMasterLs[0] is the dry channel
  // TODO : remove myaudiomixer4 class override
  // USB Line in
  InMixL.gain(0, 0);
  InMixR.gain(0, 0);
  
  // LineIn
  InMixL.gain(1,1.0);
  InMixR.gain(1, 1.0);

  LineInPreAmpL.gain(1.0);
  LineInPreAmpR.gain(1.0);

  //  DelayBusL.gain(1, 0.5);
  // DelayBusR.gain(1, 0.5);
  // //DelayBusL

  // delay2.delay(7,600);

  // delay

  
}
