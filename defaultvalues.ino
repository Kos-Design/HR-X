void initextmems() {
  for (int i = 0; i < nombreofSamplerliners; i++) {
    for (int j = 0; j < pbars; j++) {
      // length2notes1[i][j] = 0 ;
      // length2pbars[i][j] = 0 ;
      // templength2pbars[i][j] = 0 ;

      for (int k = 0; k < 3; k++) {
        event2notesOff[j][k] = 0;
        event2notes1[i][j][k] = 0;
        tempevent2notes1[i][j][k] = 0;
      }
    }
  }
  for (int i = 0; i < nombreofliners; i++) {
    for (int j = 0; j < pbars; j++) {
      length0pbars[i][j] = 0;
      templength0pbars[i][j] = 0;
      length1notes1[i][j] = 0;
      for (int k = 0; k < 3; k++) {
        event1notesOff[i][j][k] = 0;
        event1notes1[i][j][k] = 0;
        tempevent1notes1[i][j][k] = 0;
        parsedevent1notesOff[i][j][k] = 0;
      }
    }
  }
  for (int i = 0; i < 128; i++) {
    leccinterpolated[i] = 0;
    for (int j = 0; j < pbars; j++) {
      event1controllers[i][j] = 128;
      // activeevent1controllers[i][j] = 0 ;
      // nextevent1controllers[i][j] = 0 ;
    }
  }

  // ignorethatcc[88] = true;
}

void loadsynthdefaults() {

  AudioNoInterrupts();
  
  adsrlevels[0] = MadsrAttackDelay;
  adsrlevels[1] = mappedattack;
  adsrlevels[3] = mappeddecay;
  adsrlevels[4] = float(mappedsustain / 100);
  adsrlevels[5] = mappedrelease;
  
  for (int i = 0; i < 8; i++) {
    enveloppesL[i]->delay(adsrlevels[0]);
    enveloppesL[i]->attack(adsrlevels[1]);
    // enveloppesL[i]->hold(adsrlevels[2]);
    enveloppesL[i]->decay(adsrlevels[3]);
    enveloppesL[i]->sustain(adsrlevels[4]);
    enveloppesL[i]->release(adsrlevels[5]);
    enveloppesL[i]->releaseNoteOn(20);
    // for ( int j = 0 ; j < 4 ; j++ ) {
    // Wavesmix[i]->gain(j,1);
    //}
  }

  for (int i = 0; i < 32; i++) {
    waveforms1[i]->begin(0.5, notefrequency, getwavetyped(Waveformstyped[0]));
    FMwaveforms1[i]->begin(1, 440, WAVEFORM_SINE);
  }

  MasterL.gain(1, .7);
  MasterR.gain(1, .7);

  mixerWL1to4.gain(0, .25);
  mixerWL1to4.gain(1, .25);
  mixerWL1to4.gain(2, .25);
  mixerWL1to4.gain(3, .25);
  mixerWL5to8.gain(0, .25);
  mixerWL5to8.gain(1, .25);
  mixerWL5to8.gain(2, .25);
  mixerWL5to8.gain(3, .25);

  le303filtercontrols();
  //  sine1LFO.begin(1,44,WAVEFORM_SINE);
  AudioInterrupts();
}

void setupdefaultvalues() {
  initializefxmoduleisconnected();

  audioShield.enable();

  audioShield.volume(1);
  // audioShield.inputSelect(AUDIO_INPUT_LINEIN);

  // testdelme

  //    sineVLFO.amplitude(1);
  // sineVLFO.frequency(2);
  // test
  initialize303group();
  // yep

  // metronome
  MasterL1.gain(2, 0);
  MasterR1.gain(2, 0);

  ampL.gain(1);
  ampR.gain(1);

  MasterL1.gain(0, 1);
  MasterR1.gain(0, 1);
  // ADSR & synths
  loadsynthdefaults();

  // FXTEST
  FXBusL.gain(0, 1);
  FXBusR.gain(0, 1);

  premixMaster.gain(0, 0.5);
  premixMaster.gain(1, 0.5);

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 4; j++) {
      Wavesmix[i]->gain(j, mixlevelsL[j]);
    }
  }

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

  for (int i = 0; i < 4; i++) {
    setwavetypefromlist(i, Waveformstyped[i]);
  }
  for (int i = 0; i < fxiterations; i++) {
    // lfo sines used by FXes, only amplitude freq & phase
    lfosinez[i]->amplitude(0.1);
    lfosinez[i]->frequency(5);
    delaypostmix[i]->gain(0, 1);
    delaypostmix[i]->gain(1, 1);
    delayfeedbackmix[i]->gain(0, 1);
    delayfeedbackmix[i]->gain(1, 0);
    delayprefeed[i]->gain(0, 1);
    delayprefeed[i]->gain(1, 1);
    for (int j = 0; j < 4; j++) {
      lesdelays[i]->disable(2 * j);
      lesdelays[i]->disable(2 * j + 1);
      delaypremix[i * 2]->gain(j, 0);
      delaypremix[i * 2 + 1]->gain(j, 0);
    }
    flange[i]->voices(flangeoffset, flangedepth, flangefreq);
    chorus[i]->voices(chorusvoices);
    granular[i]->setSpeed(1.0);
  }

  ////
  // PlayFlash
  MasterL1.gain(3, 1);
  MasterR1.gain(3, 1);

  // PlayRaw
  MasterL1.gain(1, 1);
  MasterR1.gain(1, 1);

  // Wetness/Dryness Mix
  MasterL.gain(3, 0);
  MasterR.gain(3, 0);

  WetMixMasterL.gain(0, 1);
  WetMixMasterR.gain(0, 1);
  // Wavplayer
  MasterL.gain(0, 1);
  MasterR.gain(0, 1);

  AudioNoInterrupts();
  for (int i = 0; i < all_buttonns; i++) {

    if (!((i <= 11) || (i >= 46))) {
      pot_assignements[i] = i + 128 + 30;
      // pot_assignements[i] = i ;
      // midiknobassigned[pot_assignements[i]] = pot_assignements[i];
    } else {
      pot_assignements[i] = muxed_pots[potsboards[i]];
    }
  }
  /*for (int i = 0; i < 15 ; i++) {
    muxed_pots[i] = i ;
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
  // stop
  midiknobassigned[110] = 37;
  // play
  midiknobassigned[108] = 36;
  // looper
  midiknobassigned[109] = 109;
  // Volume
  midiknobassigned[11] = 2;
  midiknobassigned[12] = 1;
  midiknobassigned[13] = 3;

  /*
  // audio In
  midiknobassigned[14] = 97;
  midiknobassigned[15] = 1;
  midiknobassigned[16] = 3;
  */

  // 303 filter
  midiknobassigned[17] = 20;
  midiknobassigned[18] = 21;
  midiknobassigned[19] = 22;

  // FX Wet
  midiknobassigned[20] = 6;
  midiknobassigned[21] = 7;
  midiknobassigned[22] = 97;

  // pan on crossfader
  midiknobassigned[10] = 48;

  // LFO freq & level
  midiknobassigned[23] = 55;
  midiknobassigned[24] = 53;
  pot_assignements[all_buttonns-4] = 100 ;
  pot_assignements[all_buttonns-13] = 101 ;
  pot_assignements[all_buttonns-18] = 111 ;
  midiknobassigned[100] = 107;
  midiknobassigned[101] = 108;
  midiknobassigned[111] = 109;
  

  // USB Line in
  InMixL.gain(0, 0);
  InMixR.gain(0, 0);
  
  // LineIn
  InMixL.gain(1,1.0);
  InMixR.gain(1, 1.0);

  LineInPreAmpL.gain(1.0);
  LineInPreAmpR.gain(1.0);

  MasterL.gain(2, 1.0);
  MasterR.gain(2, 1.0);
  // superseeded by wetness mix
  //  MasterL.gain(2, 1);
  //  MasterR.gain(2, 1);
  //  DelayBusL.gain(1, 0.5);
  // DelayBusR.gain(1, 0.5);
  // //DelayBusL

  // delay2.delay(7,600);

  // delay

  AudioInterrupts();
}
