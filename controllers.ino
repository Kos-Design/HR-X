

int fakeselector(float smallv, int maxrange) {
  return round(map(smallv, 0, 1, 0, maxrange));
}

void controlswitcher(int caser, int valu) {

  // all pots seems to be wired backwards, inverting result
  smallfloat = 1.0 - valu / 1023.0;

  switch (caser) {

  case 0:
    // nothing = controller-free
    break;

  case 1:
    // main synth level
    mixlevelsM[1] = smallfloat * 128;

    setmastersmixlevel(1);
    break;
  case 2:
    // audioShield.volume(smallfloat);
    mixlevelsM[0] = smallfloat * 128;

    setmastersmixlevel(0);
    break;
  case 3:
    // SDSamplePlayer
    MasterL.gain(0, smallfloat);
    MasterR.gain(0, smallfloat);

    break;
  case 4:
    // synth wetness
    wetins[0] = smallfloat * 128;
    setwet2smixlevel(0);

    break;
  case 5:
    // sampler wetness
    wetins[1] = smallfloat * 128;
    setwet2smixlevel(1);
    break;
  case 6:
    // WetMixMaster1
    WetMixMasters[1] = smallfloat;
    wetmixmastercontrols();
    break;
  case 7:
    // WetMixMaster2
    WetMixMasters[2] = smallfloat;
    wetmixmastercontrols();
    break;

  case 8:
    Serial.println(8);
    // WetMixMaster3
    WetMixMasters[3] = smallfloat;
    wetmixmastercontrols();
    break;

  case 9:
    Serial.println(9);
    mixlevelsM[2] = smallfloat * 128;

    setmastersmixlevel(2);

    break;
  case 10:
    Serial.println(10);
    // 303
    slope1 = smallfloat * 128;
    break;
  case 11:
    Serial.println(11);
    // 303
    slope2 = smallfloat * 128;
    break;
  case 12:
    Serial.println(12);
    // Recorder record
    recorderrecord = 1;

    if (recorderstop) {
      recorderstop = 0;
    }
    if (recorderplay) {
      recorderplay = 0;
    }
    startRecording();
    break;
  case 13:
    Serial.println(13);
    // play recorder
    recorderplay = 1;
    recorderstop = 0;
    if (recorderrecord) {
      recorderrecord = 0;
      stopRecordingL();
    }
    playrecordsd();
    break;
  case 14:
    Serial.println(14);
    // stop recorder
    recorderstop = 1;
    if (recorderplay) {
      recorderplay = 0;
    }
    if (recorderrecord) {
      recorderrecord = 0;
      stopRecordingL();
      stopRecordingR();
    }
    break;
  case 15:
    Serial.println(15);
    // bpms
    millitickinterval = map(smallfloat, 0, 1, 250, 63);
    //metro0.interval(millitickinterval);

    setbpms();
    break;
  case 16:
    Serial.println(16);
    le303pulsewidthmultiplier = round(smallfloat * 32.0);
    break;
  case 17:
    Serial.println(17);
    le303pulsewidthmultiplier2 = round(smallfloat * 32.0);

    break;
  case 18:
    le303filterzwet = round(smallfloat * 100.0);
    le303filterzWet();
    break;
  case 19:
    Serial.println(19);

    break;
  case 20:
    Serial.println(20);
    // le303filterzfreq and range

    le303ffilterzVknobs[0] = smallfloat * 128.0;
    le303filterzfreq = round((le303ffilterzVknobs[0] / 128.0) * 14000);
    le303filterzrange = le303filterzfreq;
    break;
  case 21:
    // le303filterzreso
    le303ffilterzVknobs[1] = smallfloat * 128.0;
    le303filterzreso = ((le303ffilterzVknobs[1]) / 128.0) * 5;
    break;
  case 22:
    // le303filterzoctv
    le303ffilterzVknobs[2] = smallfloat * 128.0;
    le303filterzoctv = ((le303ffilterzVknobs[2]) / 128.0) * 7;

    break;
  case 23:
    glidemode = smallfloat * 128.0;
    break;
  case 24:
    Serial.println(24);
    preampleswaves = smallfloat * 128.0;
    break;
  case 25:
    Serial.println(25);
    le303envlfofadintime = smallfloat * 128.0;

    break;
  case 26:
    Serial.println(26);
    le303envlfofadouttime = smallfloat * 128.0;
    break;
  case 27:
    Serial.println(27);

    // INTinsertmytxtfile(int(arpegiatorOn)+1,"arpegiatorOn");
    arpegiatortype = round(smallfloat * 8.0);
    if (arpegiatortype < 8) {
      arpegiatorOn = 1;
    } else {
      arpegiatorOn = 0;
    }
    break;
  case 28:
    arpegmode = round(smallfloat * 7.0);
    break;
  case 29:
    arpegstartoffset = round(smallfloat * 18.0);
    break;

  case 30:
    arpegnumofnotes = round(smallfloat * 6.0) + 1;
    break;
  case 31:
    arpeggridC = round(smallfloat * 8.0);
    break;
  case 32:
    arpeggridS = round(smallfloat * 8.0);
    break;
  case 33:
    arpeglengh = round(smallfloat * 8.0);
    break;
  case 34:
    digitalplay = !digitalplay;
    break;
  case 35:
    // CuePlay
    tickposition = 0;
    startticker();
    break;
  case 36:
    startticker();
    break;
  case 37:
    stopallnotes();
    stopticker();
    if (recorderrecord) {
      recorderrecord = 0;
      stopRecordingL();
    }
    break;
  case 38:
    MasterL1.gain(2, smallfloat);

    MasterR1.gain(2, smallfloat);
    // metronomemix

    break;
  case 39:
    getlinerwithoutevents();
    patrecord = 1;
    startticker();

    break;
  case 40:
    pausedasong();
    break;
  case 41:
    stopdasong();
    break;
  case 42:
    playdasong();
    break;

  case 43:

    lasetchord = round(smallfloat * 6.0);
    if (lasetchord < 6) {
      chordson = 1;
    } else {
      chordson = 0;
    }
    break;

  case 44:
    // Serial.println("got to 44");
    // record just CCs
    recordCC = 1;
    startticker();
    break;

  case 45:

    ccsynthselector = round(smallfloat * 3.0);
    break;

  case 46:
    // freqs

    if (wavesfreqs[ccsynthselector] == 1) {
      demimalmode = !demimalmode;
    } else {
      if (wavesfreqs[ccsynthselector] <= 1) {
        demimalmode = 1;
      }
    }
    if (demimalmode) {
      wavesfreqs[ccsynthselector] = (smallfloat * 10.0) / 10.0;
    }

    if (!demimalmode) {
      wavesfreqs[ccsynthselector] = round(smallfloat * 10.0);
    }
    break;

  case 47:
    Serial.println("got to 47");
    mixlevelsL[ccsynthselector] = smallfloat;
    break;
  case 48:
    // panLs[i-1]
    panLs[ccsynthselector] = map(smallfloat * 10.0, 0, 2, 0, 1);
    setwavemixlevel(ccsynthselector);
    break;
  case 49:
    FMmodulated[ccsynthselector] = round(smallfloat * 2.0);
    setwavetypefromlist(ccsynthselector, Waveformstyped[ccsynthselector]);
    break;

  case 50:
    // Serial.println("50");
    Waveformstyped[ccsynthselector] = round(smallfloat * 11.0);
    setwavetypefromlist(ccsynthselector, Waveformstyped[ccsynthselector]);
    break;
  case 51:
    wave1offset[ccsynthselector] = round(smallfloat * 128.0);
    for (int i = 0; i < nombreofliners; i++) {
      waveforms1[i + (ccsynthselector * nombreofliners)]->offset(
          (float)(((64.0 - wave1offset[ccsynthselector]) / 64.0)));
      FMwaveforms1[i + (ccsynthselector * nombreofliners)]->offset(
          (float)(((64.0 - wave1offset[ccsynthselector]) / 64.0)));
    }

    break;
  case 52:
    phaselevelsL[ccsynthselector] = round(smallfloat * 360.0);
    setphaselevel(ccsynthselector);
    break;
  case 53:
    LFOlevel[ccsynthselector] = round(smallfloat * 512.0);
    break;
  case 54:
    LFOformstype[ccsynthselector] = round(smallfloat * 8.0);

    break;
  case 55:
    LFOfreqs[ccsynthselector] = smallfloat * 100.0;
    break;
  case 56:

    LFOphase[ccsynthselector] = round(smallfloat * 360.0);
    break;
  case 57:
    LFOoffset[ccsynthselector] = round(smallfloat * 128.0);
    break;
  case 58:
    LFOsync[ccsynthselector] = !LFOsync[ccsynthselector];
    break;
    
  case 59:
    // delayAtck
    adsrlevels[0] = round(smallfloat * 32.0);
    break;
  case 60:
    Serial.println("60");
    // attack
    adsrlevels[1] = round(smallfloat * 128.0);
    break;
  case 61:
    // hold
    adsrlevels[2] = round(smallfloat * 128.0);
    break;

  case 62:
    // decay
    adsrlevels[3] = round(smallfloat * 512.0);
    break;

  case 63:
    // sustain
    adsrlevels[4] = round(smallfloat * 100.0);
    break;
    
  case 64:
    // free

    break;
  case 65:
    // release
    adsrlevels[5] = round(smallfloat * 512.0);
    break;
    
  case 66:

    mixle303ffilterzVknobs[0] = round(smallfloat * 128.0);
    le303filterzgainz[0] = smallfloat;
    le303filtercontrols();
    // le303filterzgainz[0]
    //  mixle303ffilterzVknobs[0]
    break;
  case 67:
    mixle303ffilterzVknobs[1] = round(smallfloat * 128.0);
    le303filterzgainz[1] = smallfloat;
    le303filtercontrols();
    break;
  case 68:
    mixle303ffilterzVknobs[2] = round(smallfloat * 128.0);
    le303filterzgainz[2] = smallfloat;
    le303filtercontrols();
    break;
  case 69:
    // gets the fx connected on 1, 2, or 3rd position on the fx lines
    //ccfxlineselector = moduleonfxline[round(smallfloat * 2.0)][1];
   // Serial.println(ccfxlineselector);
    break;
  case 70:
    Serial.println("70");
    chorusVknobs[ccfxlineselector] = round(smallfloat * 128.0);
    break;
  case 71:
    bqstage[ccfxlineselector] = round(smallfloat * 3.0);
    break;
  case 72:

    LFOonfilterz[ccfxlineselector] = round(smallfloat * 3.0);
    filtercontrols(ccfxlineselector);
    break;
  case 73:
    bqVpot[ccfxlineselector][bqstage[ccfxlineselector]][0] =
        round(smallfloat * 128.0);
    bqfreq[ccfxlineselector][bqstage[ccfxlineselector]] =
        (smallfloat * bqrange) + 101;
    if (bqfreq[ccfxlineselector][bqstage[ccfxlineselector]] >= 101) {
      biquadcontrols(ccfxlineselector);
    }
    break;
  case 74:
    bqVpot[ccfxlineselector][bqstage[ccfxlineselector]][1] =
        round(smallfloat * 128.0);
    bqslope[ccfxlineselector][bqstage[ccfxlineselector]] = smallfloat;
    if (bqfreq[ccfxlineselector][bqstage[ccfxlineselector]] >= 101) {
      biquadcontrols(ccfxlineselector);
    }
    break;
  case 75:

    bqVpot[ccfxlineselector][bqstage[ccfxlineselector]][2] =
        round(smallfloat * 128.0);
    bqgain[ccfxlineselector][bqstage[ccfxlineselector]] = smallfloat;
    if (bqfreq[ccfxlineselector][bqstage[ccfxlineselector]] >= 101) {
      biquadcontrols(ccfxlineselector);
    }
    break;
  case 76:
    granularVknobs[ccfxlineselector][0] = round(smallfloat * 128.0);
    granularcontrols(ccfxlineselector);
    break;
  case 77:
    granularVknobs[ccfxlineselector][1] = round(smallfloat * 128.0);
    granularcontrols(ccfxlineselector);
    break;

  case 78:
    granularVknobs[ccfxlineselector][2] = (round(smallfloat * 128.0)) * 128;
    granularcontrols(ccfxlineselector);
    break;

  case 79:
    granularVknobs[ccfxlineselector][3] = (round(smallfloat)) * 128;
    granularcontrols(ccfxlineselector);
    break;

  case 80:
    Serial.println("80");
    reverbVknobs[ccfxlineselector][0] = round(smallfloat * 128.0);
    freeverbscontrl(ccfxlineselector);
    break;
  case 81:
    reverbVknobs[ccfxlineselector][1] = round(smallfloat * 128.0);
    freeverbscontrl(ccfxlineselector);
    break;
  case 82:
    bitcrusherVknobs[ccfxlineselector][0] = round(smallfloat * 16.0);
    bitcrusherctrl(ccfxlineselector);
    break;
  case 83:
    bitcrusherVknobs[ccfxlineselector][1] = round(smallfloat * 128.0);
    bitcrusherctrl(ccfxlineselector);
    break;
  case 84:
    mixffilterzVknobs[ccfxlineselector][0] = round(smallfloat * 128.0);
    filtercontrols(ccfxlineselector);
    break;
  case 85:
    mixffilterzVknobs[ccfxlineselector][1] = round(smallfloat * 128.0);
    filtercontrols(ccfxlineselector);
    break;
  case 86:
    mixffilterzVknobs[ccfxlineselector][2] = round(smallfloat * 128.0);

    filtercontrols(ccfxlineselector);
    break;
  case 87:
    ffilterzVknobs[ccfxlineselector][0] = round(smallfloat * 128.0);
    filtercontrols(ccfxlineselector);
    break;
  case 88:
    ffilterzVknobs[ccfxlineselector][1] = round(smallfloat * 128.0);
    filtercontrols(ccfxlineselector);
    break;
  case 89:
    ffilterzVknobs[ccfxlineselector][2] = round(smallfloat * 128.0);
    filtercontrols(ccfxlineselector);
    break;

  case 90:
    Serial.println("90");

    flangerVknobs[ccfxlineselector][0] = round(smallfloat * 128.0);
    flangercontrols(ccfxlineselector);
    break;
  case 91:
    flangerVknobs[ccfxlineselector][1] = round(smallfloat * 128.0);
    flangercontrols(ccfxlineselector);
    break;
  case 92:
    flangerVknobs[ccfxlineselector][2] = round(smallfloat * 128.0);
    flangercontrols(ccfxlineselector);
    break;
  case 93:
    delayVknobs[ccfxlineselector][0] = round(smallfloat * 128.0);
    restartdelayline(ccfxlineselector);

    break;

  case 94:
    delayVknobs[ccfxlineselector][1] = round(smallfloat * 128.0);
    restartdelayline(ccfxlineselector);
    break;

  case 95:
    delayVknobs[ccfxlineselector][2] = round(smallfloat * 128.0);
    restartdelayline(ccfxlineselector);
    break;

  case 96:
    // type
    bqtype[ccfxlineselector][bqstage[ccfxlineselector]] =
        round(smallfloat * 5.0);
    if (bqfreq[ccfxlineselector][bqstage[ccfxlineselector]] >= 101) {
      biquadcontrols(ccfxlineselector);
    }
    break;

  case 97:
    // Audio In level

    //AudioNoInterrupts();
    //InMixL.gain(1, smallfloat);
    //InMixR.gain(1, smallfloat);
    Serial.println(" MasterL.gain(2) set to ");
    Serial.print(smallfloat);
    MasterL.gain(2, smallfloat);
    MasterR.gain(2, smallfloat);

    //AudioInterrupts();
    break;

  case 98:
    debug_cpu = !debug_cpu;
    break;

  case 99:

    break;

  case 100:
    Serial.println("100");
    writelemidi(lqcurrentpqt);
    break;

  case 101:
    // loqdcurrent
    clearlapattern();

    parsepattern(lqcurrentpqt);
    break;

  case 102:

    break;

  case 103:

    break;

  case 104:
    // freq1

    break;

  case 105:

    break;

  case 106:
    //  phase1
  print_gains();
    break;
  case 107:
    // type2
      clearlapattern();

      parsepattern(0);
    //.gain(2,smallfloat);
    break;

  case 108:
  parsefile(0);

    break;
  case 109:
  
      start_sample_in_place();
  
    break;
  case 110:
    smixervknobs[0] = byte(smallfloat * 128.0);

    break;
  case 111:

    smixervknobs[1] = byte(smallfloat * 128.0);

    break;
  case 112:

    smixervknobs[2] = byte(smallfloat * 128.0);

    break;
  case 113:
    smixervknobs[3] = byte(smallfloat * 128.0);

    break;

  case 114:
    smixervknobs[4] = byte(smallfloat * 128.0);

    break;

  case 115:
    smixervknobs[5] = byte(smallfloat * 128.0);

    break;

  case 116:
    smixervknobs[6] = byte(smallfloat * 128.0);

    break;

  case 117:
    smixervknobs[7] = byte(smallfloat * 128.0);

    break;
  case 118:
    smixervknobs[8] = byte(smallfloat * 128.0);

    break;

  case 119:
    smixervknobs[9] = byte(smallfloat * 128.0);

    break;

  case 120:
    smixervknobs[10] = byte(smallfloat * 128.0);

    break;

  case 121:
    smixervknobs[11] = byte(smallfloat * 128.0);

    break;
  case 122:
    smixervknobs[12] = byte(smallfloat * 128.0);

    break;

  case 123:
    smixervknobs[13] = byte(smallfloat * 128.0);

    break;

  case 124:
    smixervknobs[14] = byte(smallfloat * 128.0);

    break;

  case 125:
    smixervknobs[15] = byte(smallfloat * 128.0);

    break;

  case 126:
    // freq3

    // wavesfreqs[2]=round(map(smallfloat,0,1,0,10));
    break;

  case 127:

    break;

  case 128:
    //  phase3

    break;

  case 129:
    // type4

    break;

  case 130:
    Serial.println("130");
    //  mixwave4

    break;

  case 131:

    break;

  case 132:

    break;
  case 133:

    break;

  case 134:

    break;

  case 135:

    break;

  case 136:

    break;

  case 137:
    // freq4

    break;

  case 138:
    // pan4

    break;

  case 139:

    break;
  case 140:
    // Serial.println("octave 140");

    break;

  case 141:
    // Serial.println("resonance 141");

    break;
  case 142:
    // Serial.println("filter freq pot 142");
    // filterz[0]->frequency(valu);
    break;

  case 143:

    break;
  case 144:

    break;

  case 145:

    break;

  case 146:

    break;

  default:
    break;
  }
}
