
void setupSD() {

  if (!(SD.begin(chipSelect))) {
    errorsd("initialization SD failed!");
    return;
  }
  
  initializesamplesselectedlist();
  pseudoconsole((char *)"Scanning Samples");
  dosoundlist();
  pseudoconsole((char *)"Scanning Presets");
  list_presets_files();
  pseudoconsole((char *)"Scanning Patterns");
  _pt.list_patterns_files();
  pseudoconsole((char *)"Scanning Waveforms");
  list_wforms_files();
  pseudoconsole((char *)"Scanning Songs");
  list_songs_files();
}

void attach_menus(){
  void (*menus[])() = {
    call_sn_show,call_lf_show,_ka.show,song_nav_zero,call_pt_show,
   call_st_show,call_fx_show,call_sp_show,call_wf_show,call_ps_show};
  for (int i=0;i<10;i++){
    dm.attach_nav_zero(i,menus[i]);
  }
}
//this feels so dumb
void call_restart_lfo(int lelfo) {
  _lf.restartLFO(lelfo%synths_count);
};
void call_setwavetypefromlist(){
  _sn.setwavetypefromlist();
}
void call_setwavemixlevel(){
  _sn.setwavemixlevel();
}
void call_sn_show(){
  _sn.show();
}
void call_synth_event_cells(){
  _pe.synth_event_cells();
}
void call_sampler_event_cells(){
  _pe.sampler_event_cells();
}
void call_song_home(){
  _sg.song_home();
}
void call_wf_show(){
  _wf.show();
}
void call_ps_show(){
  _ps.show();
}
void call_sp_show(){
  _sp.show();
}
void call_fx_show(){
  _fx.MainFxPanel();
}
void call_st_show(){
  _st.show();
}
void call_pt_show(){
  _pt.show();
}
void call_lf_show(){
  //TODO: chack why I had to call it that way since I populate some pointers unlike static _ka.show
  _lf.show();
}

String get_pattern_name_from_pt(int p_index) {
  return _pt.get_pattern_name(p_index);
}
void call_st_onboardPanel(){
  _st.OnBoardVpanel();
}
void call_set_bpms(){
  _st.setbpms();
}
void call_parsepattern(){
  _pt.parsepattern();
}
void call_refresh_track(){
  _pe.refresh_track();
}
void call_refreshevented2(){
  _pe.refreshevented2();
}
/*
void MyClass::lfo_zero() {}
void MyClass::LFOlining() {}
*/



void attach_menus_songs(){
  // wavesline_selector,showmixerwaves, displayadsrgraph, empty,le303filterVpanel,
  //void (*nav_songs_menu[])() = {"Edit", "Save", "Load", "Copy", "Delete", "Clear", "Params","showSongShifterdisplays"};
  void (*nav_songs_menu_tmp[])() = {call_songeditor,song_nav_one, song_nav_one, song_nav_one, song_nav_one,clear_song_popup,song_params_panel,showSongShifterdisplays};
  for (int i=0;i<truesizeofSongmenulabels;i++){
    _sg.attach_nav_songs_menu(i,nav_songs_menu_tmp[i]);
  }
}

void call_songeditor(){
  _se.Songmodepanel();
}
void call_fx_mainpanel(){
  _fx.MainFxPanel();
}
/*
void attach_menus_settings(){
  // wavesline_selector,showmixerwaves, displayadsrgraph, empty,le303filterVpanel,
  //void (*nav_songs_menu[])() = {"Edit", "Save", "Load", "Copy", "Delete", "Clear", "Params","showSongShifterdisplays"};
  void (*settings_menus[])() = {Songmodepanel,song_nav_one, song_nav_one, song_nav_one, song_nav_one,clear_song_popup,song_params_panel,showSongShifterdisplays};
  for (int i=0;i<numbofsettinglabels;i++){
    _st.attach_settings_menus(i,settings_menus[i]);
  }
}

void attach_menus_fx(){
  // wavesline_selector,showmixerwaves, displayadsrgraph, empty,le303filterVpanel,
  //void (*nav_songs_menu[])() = {"Edit", "Save", "Load", "Copy", "Delete", "Clear", "Params","showSongShifterdisplays"};
  void (*nav_songs_menu_tmp[])() = {Songmodepanel,song_nav_one, song_nav_one, song_nav_one, song_nav_one,clear_song_popup,song_params_panel,showSongShifterdisplays};
  for (int i=0;i<truesizeofSongmenulabels;i++){
    _fx.attach_nav_songs_menu(i,nav_songs_menu_tmp[i]);
  }
}
*/
void attach_menus_sampler(){
  // wavesline_selector,showmixerwaves, displayadsrgraph, empty,le303filterVpanel,
  //void (*nav_songs_menu[])() = {"Edit", "Save", "Load", "Copy", "Delete", "Clear", "Params","showSongShifterdisplays"};
  void (*nav_sampler_menu_tmp[sizeofsamplerlabels])() = {song_nav_one,song_nav_one, song_nav_one, song_nav_one, song_nav_one};
  for (int i=0;i<sizeofsamplerlabels;i++){
    _sp.attach_nav_sampler_menu(i,nav_sampler_menu_tmp[i]);
  }
}

void attach_menus_waveforms(){
  // wavesline_selector,showmixerwaves, displayadsrgraph, empty,le303filterVpanel,
  //void (*nav_songs_menu[])() = {"Edit", "Save", "Load", "Copy", "Delete", "Clear", "Params","showSongShifterdisplays"};
  void (*nav_waveforms_menu_tmp[truesizeofwaveformsmenulabels])() = {waveforms_nav_one, waveforms_nav_one, waveforms_nav_one, waveforms_nav_one,WaveformEditer ,nullptr,nullptr,WaveformParams};
  for (int i=0;i<truesizeofwaveformsmenulabels;i++){
    _wf.attach_nav_waveforms_menu(i,nav_waveforms_menu_tmp[i]);
  }
}
void attach_menus_presets(){
  // wavesline_selector,showmixerwaves, displayadsrgraph, empty,le303filterVpanel,
  //void (*nav_songs_menu[])() = {"Edit", "Save", "Load", "Copy", "Delete", "Clear", "Params","showSongShifterdisplays"};
  //"Save", "Load", "Copy", "Delete", "Edit", "-->", "<--","Params"};
  void (*nav_songs_menu_tmp[truesizeofpresetmenulabels])() = {song_nav_one, song_nav_one, song_nav_one,clear_song_popup,song_params_panel};
  for (int i=0;i<truesizeofpresetmenulabels;i++){
    _ps.attach_presets_menu(i,nav_songs_menu_tmp[i]);
  }
}

void setup() {

  // pseudoconsole((char*)"initializing...");
  // settime();

  AudioNoInterrupts();
  unplugsynth();
  unplugfx();
  for (int i=0;i<synths_count;i++) {
  unpluglfoonfilterz(i);
  }
  delay(500);
  // metrodrum1.frequency(100);
  // metrodrum1.length(50);
  init_synth_liners();
  init_fxes();
  // metrodrum1.pitchMod(0.9);
  AudioInterrupts();

  initextmems();
  // setupmemtest();
  Serial.begin(9600);

  initializeconsolemsg();
  dm.setupscreen();
  pseudoconsole((char *)"initializing...");
  initializepatternonsong();
  //delay(100);
  //Initialise the AutoVolumeLeveller
  //audioShield.autoVolumeControl(1, 1, 0, -6, 40, 20); // **BUG** with a max
  //gain of 0, turning the AVC off leaves a hung AVC problem where the attack
  //seems to hang in a loop. with it set 1 or 2, this does not occur.
  //audioShield.autoVolumeDisable();
  //audioShield.audioPostProcessorEnable();
  pseudoconsole((char *)"Setting USB Host...");
  delay(100);

  setuphubusb();
  pseudoconsole((char *)"USB Host Ready !");
  delay(50);

  pseudoconsole((char *)"Scanning SD Card");
  delay(100);
  setupSD();
  pseudoconsole((char *)"SD Card OK !");
  Pads.begin();
  pseudoconsole((char *)"Setting up I/O");
  for (unsigned int i = 0; i < manyinputpins; i++) {
    pinMode(inputpins[i], INPUT_PULLUP);
  }
  for (int i = 0; i < 128; i++) {
    midiknobassigned[i] = 0;
  }
  pseudoconsole((char *)"I/O Set !");
  pseudoconsole((char *)"Loading Defaults");
  clocker.stopticker();
  setupdefaultvalues();
  Doautoassign();
  pseudoconsole((char *)"All Done !");
  pseudoconsole((char *)"starting muxer");
  Muxer.start();
  //queue1.begin();
  AudioMemory(1200);
  audioShield.inputSelect(AUDIO_INPUT_LINEIN);
  audioShield.enable();
  audioShield.volume(1.0);
  set_in_source();
  clocker.attach_24(advance_tick);
  clocker.setBPM(120);
  clocker.setPPQN(96);
  initdone = 1;
  pseudoconsole((char *)"Enjoy !");
  attach_menus();
  //attach_menus_synths();
  //attach_lfo_menus();
  //knobs not
  attach_menus_songs();
  //done in class init
  //attach_menus_patterns();
  //settings not
  attach_menus_sampler();
  attach_menus_waveforms();
  attach_menus_presets();
  
}


void controlswitcher(int caser, int valu) {

  // pots values backwards, inverting results
  smallfloat = 1.0 - valu / 1023.0;

  switch (caser) {
    case 0:
    // nothing = controller-free
      break;
    case 1:
      // audioShield.volume(smallfloat);
      mixlevelsM[0] = smallfloat * 127;
      setmastersmixlevel(0);
      break;
    case 2:
      // main synth level
      mixlevelsM[1] = smallfloat * 127;
      setmastersmixlevel(1);
      break;
    case 3:
      // SDSamplePlayer
      MasterL.gain(0, smallfloat);
      MasterR.gain(0, smallfloat);
      break;
    case 4:
    //flash sampler
      mixlevelsM[2] = smallfloat * 127;
      setmastersmixlevel(2);
      break;
    case 5:
      // WetMixMaster1
      WetMixMasters[1] = smallfloat;
      wetmixmastercontrols();
      break;
    case 6:
      // WetMixMaster2
      WetMixMasters[2] = smallfloat;
      wetmixmastercontrols();
      break;
    case 7:
      // WetMixMaster3
      WetMixMasters[3] = smallfloat;
      wetmixmastercontrols();
      break;
    case 8:
      // sampler wetness
      wetins[1] = smallfloat * 127;
      set_dry_mix(1);
      break;
    case 9:
        // synth wetness
      wetins[0] = smallfloat * 127;
      set_dry_mix(0);
      break;
    case 10:
     //wetness Audio In, metronome & sd player
      wetins[2] = smallfloat * 127;
      set_dry_mix(2);
      break;
    case 11:
      // 303 cutoff pulse length
      slope1 = smallfloat * 127;
      break;
    case 12:
      // 303 resonance pulse length
      slope2 = smallfloat * 127;
      break;
    case 13:
      //FREE
      break;
    case 14:
      //free
      break;
    case 15:
     //free
      break;
    case 16:
      cutoff_pulse = round(smallfloat * 32.0);
      break;
    case 17:
      reson_pulse = round(smallfloat * 32.0);
      break;
    case 18:
      le303filterzwet = round(smallfloat * 100.0);
      le303filterzWet();
      break;
    case 19:
     //"free"
      break;
    case 20:
      // Cutoff freq and range
      le303ffilterzVknobs[0] = smallfloat * 127.0;
      le303filterzfreq = round((le303ffilterzVknobs[0] / 127.0) * 14000);
      le303filterzrange = le303filterzfreq;
      cutoff_pulse = 16+smallfloat * 16.0;
      setlepulse1();
      break;
    case 21:
      // Resonance
      le303ffilterzVknobs[1] = smallfloat * 127.0;
      le303filterzreso = ((le303ffilterzVknobs[1]) / 127.0) * 5;
      break;
    case 22:
      // Filter Octave range
      le303ffilterzVknobs[2] = smallfloat * 127.0;
      le303filterzoctv = ((le303ffilterzVknobs[2]) / 127.0) * 7;

      break;
    case 23:
      glidemode = smallfloat * 127.0;
      break;
    case 24:
    //filter Input gain
      preampleswaves = smallfloat * 127.0;
      break;
    case 25:
      //free
      break;
    case 26:
      //FREE
      break;
    case 27:
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
      clocker.startticker();
      break;
    case 36:
      clocker.startticker();
      break;
    case 37:
      _st.stopallnotes();
      clocker.stopticker();
      if (recorderrecord) {
        recorderrecord = 0;
        stopRecordingL();
      }
      break;
    case 38:
      MasterL.gain(1, smallfloat);
      MasterR.gain(1, smallfloat);
      // metronomemix

      break;
    case 39:
      getlinerwithoutevents();
      patrecord = 1;
      clocker.startticker();

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
      // record just CCs
      recordCC = 1;
      clocker.startticker();
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
      mixlevelsL[ccsynthselector] = smallfloat;
      break;
    case 48:
      // panLs[i-1]
      panLs[ccsynthselector] = map(smallfloat * 10.0, 0, 2, 0, 1);
      _sn.setwavemixlevel();
      break;
    case 49:
      FMmodulated[ccsynthselector] = round(smallfloat * 3.0);
      //Waveformstyped[ccsynthselector] = ;
      _sn.setwavetypefromlist();
      break;

    case 50:
      Waveformstyped[ccsynthselector] = round(smallfloat * 11.0);
      _sn.setwavetypefromlist();
      break;
    case 51:
      wave1offset[ccsynthselector] = round(smallfloat * 127.0);
      for (int i = 0; i < liners_count; i++) {
        waveforms1[i + (ccsynthselector * liners_count)]->offset(
            (float)(((64.0 - wave1offset[ccsynthselector]) / 64.0)));
        FMwaveforms1[i + (ccsynthselector * liners_count)]->offset(
            (float)(((64.0 - wave1offset[ccsynthselector]) / 64.0)));
      }

      break;
    case 52:
      phaselevelsL[ccsynthselector] = round(smallfloat * 360.0);
      _sn.setphaselevel();
      break;
    case 53:
      LFOlevel[ccsynthselector] = round(smallfloat * 127.0);
      break;
    case 54:
      LFOformstype[ccsynthselector] = round(smallfloat * 8.0);

      break;
    case 55:
      LFOfreqs[ccsynthselector] = round(smallfloat * 127.0);
      break;
    case 56:

      LFOphase[ccsynthselector] = round(smallfloat * 360.0);
      break;
    case 57:
      LFOoffset[ccsynthselector] = round(smallfloat * 127.0);
      break;
    case 58:
      LFOsync[ccsynthselector] = !LFOsync[ccsynthselector];
      break;

    case 59:
      // delayAtck
      adsrlevels[0] = round(smallfloat * 32.0);
      break;
    case 60:
      // attack
      adsrlevels[1] = round(smallfloat * 127.0);
      break;
    case 61:
      // hold
      adsrlevels[2] = round(smallfloat * 127.0);
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
      //free
      break;
    case 65:
      // release
      adsrlevels[5] = round(smallfloat * 512.0);
      break;

    case 66:
      mixle303ffilterzVknobs[0] = round(smallfloat * 127.0);
      le303filterzgainz[0] = smallfloat;
      le303filtercontrols();
      // le303filterzgainz[0]
      //  mixle303ffilterzVknobs[0]
      break;
    case 67:
      mixle303ffilterzVknobs[1] = round(smallfloat * 127.0);
      le303filterzgainz[1] = smallfloat;
      le303filtercontrols();
      break;
    case 68:
      mixle303ffilterzVknobs[2] = round(smallfloat * 127.0);
      le303filterzgainz[2] = smallfloat;
      le303filtercontrols();
      break;
    case 69:
      ccfxlineselector = map((int)(smallfloat*100.0),0,100,0,2);
      break;
    case 70:
      chorusVknobs[ccfxlineselector] = round(smallfloat * 127.0);
      break;
    case 71:
      bqstage[ccfxlineselector] = round(smallfloat * 3.0);
      break;
    case 72:
      LFOonfilterz[ccfxlineselector] = round(smallfloat * 3.0);
      filtercontrols(ccfxlineselector);
      break;
    case 73:
      bqVpot[ccfxlineselector][bqstage[ccfxlineselector]][0] = round(smallfloat * 127.0);
      bqfreq[ccfxlineselector][bqstage[ccfxlineselector]] = (smallfloat * bqrange) + 101;
      if (bqfreq[ccfxlineselector][bqstage[ccfxlineselector]] >= 101) {
        biquadcontrols(ccfxlineselector);
      }
      break;
    case 74:
      bqVpot[ccfxlineselector][bqstage[ccfxlineselector]][1] = round(smallfloat * 127.0);
      bqslope[ccfxlineselector][bqstage[ccfxlineselector]] = smallfloat;
      if (bqfreq[ccfxlineselector][bqstage[ccfxlineselector]] >= 101) {
        biquadcontrols(ccfxlineselector);
      }
      break;
    case 75:
      bqVpot[ccfxlineselector][bqstage[ccfxlineselector]][2] = round(smallfloat * 127.0);
      bqgain[ccfxlineselector][bqstage[ccfxlineselector]] = smallfloat;
      if (bqfreq[ccfxlineselector][bqstage[ccfxlineselector]] >= 101) {
        biquadcontrols(ccfxlineselector);
      }
      break;
    case 76:
      //granular grains
      granularVknobs[ccfxlineselector][0] = round(smallfloat * 127.0);
      break;

    case 77:
      //granular speed ratio
      granularVknobs[ccfxlineselector][1] = round(smallfloat * 127.0);
      granularcontrols(ccfxlineselector);
      break;

    case 78:

      granular_shifting[ccfxlineselector] = !granular_shifting[ccfxlineselector];
      granular_pitch_shift(ccfxlineselector);
      break;

    case 79:
      granular_freezing[ccfxlineselector] = !granular_freezing[ccfxlineselector];
      granular_freeze(ccfxlineselector);
      break;

    case 80:
      reverbVknobs[ccfxlineselector][0] = round(smallfloat * 127.0);
      freeverbscontrl(ccfxlineselector);
      break;
    case 81:
    //disabled with this reverb
      //reverbVknobs[ccfxlineselector][1] = round(smallfloat * 127.0);
      //freeverbscontrl(ccfxlineselector);
      break;
    case 82:
      bitcrusherVknobs[ccfxlineselector][0] = round(smallfloat * 16.0);
      bitcrusherctrl(ccfxlineselector);
      break;
    case 83:
      bitcrusherVknobs[ccfxlineselector][1] = round(smallfloat * 127.0);
      bitcrusherctrl(ccfxlineselector);
      break;
    case 84:
      mixffilterzVknobs[ccfxlineselector][0] = round(smallfloat * 127.0);
      filtercontrols(ccfxlineselector);
      break;
    case 85:
      mixffilterzVknobs[ccfxlineselector][1] = round(smallfloat * 127.0);
      filtercontrols(ccfxlineselector);
      break;
    case 86:
      mixffilterzVknobs[ccfxlineselector][2] = round(smallfloat * 127.0);

      filtercontrols(ccfxlineselector);
      break;
    case 87:
      ffilterzVknobs[ccfxlineselector][0] = round(smallfloat * 127.0);
      filtercontrols(ccfxlineselector);
      break;
    case 88:
      ffilterzVknobs[ccfxlineselector][1] = round(smallfloat * 127.0);
      filtercontrols(ccfxlineselector);
      break;
    case 89:
      ffilterzVknobs[ccfxlineselector][2] = round(smallfloat * 127.0);
      filtercontrols(ccfxlineselector);
      break;

    case 90:
      flangerVknobs[ccfxlineselector][0] = round(smallfloat * 127.0);
      flangercontrols(ccfxlineselector);
      break;
    case 91:
      flangerVknobs[ccfxlineselector][1] = round(smallfloat * 127.0);
      flangercontrols(ccfxlineselector);
      break;
    case 92:
      flangerVknobs[ccfxlineselector][2] = round(smallfloat * 127.0);
      flangercontrols(ccfxlineselector);
      break;
    case 93:
      delayVknobs[ccfxlineselector][0] = round(smallfloat * 127.0);
      restartdelayline(ccfxlineselector);
      break;

    case 94:
      delayVknobs[ccfxlineselector][1] = round(smallfloat * 127.0);
      restartdelayline(ccfxlineselector);
      break;

    case 95:
      delayVknobs[ccfxlineselector][2] = round(smallfloat * 127.0);
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
      MasterL.gain(2, smallfloat);
      MasterR.gain(2, smallfloat);
      break;

    case 98:
      debug_cpu = !debug_cpu;
      break;

    case 99:
       // bpms
      millitickinterval = map(smallfloat, 0, 1, 250, 63);
      _st.setbpms();
      break;

    case 100:
      //to save in a new pattern
      patterns_names_offset = patterns_count ;
      _pt.writelemidi();
      break;

    case 101:
      _po.clearlapattern();
      //loads 1st pattern, increment patterns_names_offset for a different one
      patterns_names_offset = 0 ;
      call_parsepattern();

      break;

    case 102:
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
    case 103:
      // play recorder
      recorderplay = 1;
      recorderstop = 0;
      if (recorderrecord) {
        recorderrecord = 0;
        stopRecordingL();
      }
      playrecordsd();
      break;
    case 104:
     
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

    case 105:

      break;

    case 106:
      //  phase1

      break;
    case 107:
      // type2
      _po.clearlapattern();
      patterns_names_offset = 0 ;
      call_parsepattern();
      break;
    case 108:
      presets_names_offset = 0 ;
      refresh_presets_names();
      parsefile();
      break;
    case 109:
      //auto record 10sec
      start_sample_in_place();
      break;
    case 110:
    //velocity levels for samplerlines
      smixervknobs[0] = byte(smallfloat * 127.0);
      break;
    case 111:
      smixervknobs[1] = byte(smallfloat * 127.0);
      break;
    case 112:
      smixervknobs[2] = byte(smallfloat * 127.0);
      break;
    case 113:
      smixervknobs[3] = byte(smallfloat * 127.0);
      break;
    case 114:
      smixervknobs[4] = byte(smallfloat * 127.0);
      break;
    case 115:
      smixervknobs[5] = byte(smallfloat * 127.0);
      break;
    case 116:
      smixervknobs[6] = byte(smallfloat * 127.0);
      break;
    case 117:
      smixervknobs[7] = byte(smallfloat * 127.0);
      break;
    case 118:
      smixervknobs[8] = byte(smallfloat * 127.0);
      break;
    case 119:
      smixervknobs[9] = byte(smallfloat * 127.0);
      break;
    case 120:
      smixervknobs[10] = byte(smallfloat * 127.0);
      break;
    case 121:
      smixervknobs[11] = byte(smallfloat * 127.0);
      break;
    case 122:
      smixervknobs[12] = byte(smallfloat * 127.0);
      break;
    case 123:
      smixervknobs[13] = byte(smallfloat * 127.0);
      break;
    case 124:
      smixervknobs[14] = byte(smallfloat * 127.0);
      break;
    case 125:
      smixervknobs[15] = byte(smallfloat * 127.0);
      break;

    case 126:
      _po.merge_synth_partition_liners();
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
      break;

    case 141:
      break;
    case 142:
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