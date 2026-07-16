
void setupSD() {

  if (!(SD.begin(chipSelect))) {
    _sp.errorsd("initialization SD failed!");
    return;
  }

  //for (int i=0; i<10 ; i++) {
      //FlashSampler[i]->enableInterpolation(true);
    //FlashSampler[i]->setFilesystem(thyfs);
  //}
  _sp.initializesamplesselectedlist();
  pseudoconsole((char *)"Scanning Samples");
  _sp.dosoundlist();
  pseudoconsole((char *)"Scanning Presets");
  _ps.list_presets_files();
  pseudoconsole((char *)"Scanning Patterns");
  _pt.list_patterns_files();
  pseudoconsole((char *)"Scanning Waveforms");
  _wf.list_wforms_files();
  pseudoconsole((char *)"Scanning Songs");
  _sg.list_songs_files();
}

void call_sn_show(){
  _sn.show();
}
void call_ad_show(){
  _ad.show();
}
void call_fl_show(){
  _fl.show();
}
void call_mx_show(){
  _mx.show();
}
void call_restart_lfo(int lelfo) {
  _lf.restartLFO(lelfo%OSCS_COUNT);
};
void call_allfxcontrolled(){
  _fx.allfxcontrolled();
}
void call_rd_show(){
  _rd.show();
}
void call_set_y_cursor_value(int val){
  _wf.set_y_cursor_value(val);
}
void call_set_x_cursor_value(int val){
  _wf.set_x_cursor_value(val);
}
void call_setwavetypefromlist(){
  _sn.setwavetypefromlist();
}
void call_setwavemixlevel(){
  _mx.setwavemixlevel();
}
void call_dosoundlist(){
  _sp.dosoundlist();
}
void call_loadSampledSound(){
  _sp.loadSampledSound();
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
void call_sg_show(){
  _sg.show();
}
void call_pt_show(){
  _pt.show();
}
void call_lf_show(){
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

void call_refresh_flash_track(){
  _pe.refresh_flash_track();
}

void call_songeditor(){
  _se.Songmodepanel();
}

void setup() {

  // pseudoconsole((char*)"initializing...");
  // settime();

  AudioNoInterrupts();
  unplugsynth();
  unplugfx();
  for (int i=0;i<OSCS_COUNT;i++) {
  _fx.unpluglfoonfilterz(i);
  }
  delay(500);
  // metrodrum1.frequency(100);
  // metrodrum1.length(50);
  init_synth_liners();
  init_flash_liners();

  init_fxes();
  // metrodrum1.pitchMod(0.9);
  AudioInterrupts();

  initextmems();
  // setupmemtest();
  Serial.begin(9600);

  initializeconsolemsg();
  dm.setupscreen();
  pseudoconsole((char *)"initializing...");
  _sg.initializepatternonsong();
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
  _sp.Doautoassign();
  pseudoconsole((char *)"All Done !");
  pseudoconsole((char *)"starting muxer");
  Muxer.start();
  //queue1.begin();
  AudioMemory(1200);
  audioShield.inputSelect(AUDIO_INPUT_LINEIN);
  audioShield.enable();
  audioShield.volume(1.0);
  _st.set_in_source();
  clocker.attach_24(advance_tick);
  clocker.attach_96(once_in_a_while);
  //clocker.attach_3(fairly_often);
  clocker.attach_16(at_a_paced_rate);
  clocker.setBPM(120);
  clocker.setPPQN(96);
  initdone = 1;
  pseudoconsole((char *)"Enjoy !");
}

void Volume_ctl(byte cc_value){
  // audioShield.volume(smallfloat);
  mixlevelsM[0] = cc_value;
  _mx.setmastersmixlevel(0);
}

void SynthVolume_ctl(byte cc_value){
  // main synth level
  mixlevelsM[1] = cc_value;
  _mx.setmastersmixlevel(1);
}

void SDPlayerVolume_ctl(byte cc_value){
  // SDSamplePlayer
  MasterL.gain(0, (1.0 - (cc_value / 127.0)));
  MasterR.gain(0, (1.0 - (cc_value / 127.0)));
}

void FlashVolume_ctl(byte cc_value){
  // flash
  mixlevelsM[2] = cc_value;
  _mx.setmastersmixlevel(2);
}

void Wet1Volume_ctl(byte cc_value){
  // WetMixMaster1
  WetMixMasters[1] = cc_value;
  _mx.wetmixmastercontrols();
}

void Wet2Volume_ctl(byte cc_value){
  // WetMixMaster2
  WetMixMasters[2] = cc_value;
  _mx.wetmixmastercontrols();
}

void Wet3Volume_ctl(byte cc_value){
  // WetMixMaster3
  WetMixMasters[3] = cc_value;
  _mx.wetmixmastercontrols();
}

void DrySampler_ctl(byte cc_value){
  /// sampler wetness
  wetins[1] = cc_value;
  _mx.set_dry_mix(1);
}

void DrySynth_ctl(byte cc_value){
  /// synth wetness
  wetins[0] = cc_value;
  _mx.set_dry_mix(0);
}

void DryAudioIn_ctl(byte cc_value){
  /// audio In wetness
  wetins[2] = cc_value;
  _mx.set_dry_mix(2);
}

void Slope1_ctl(byte cc_value){
  // 303 cutoff pulse length
  slope1 = cc_value;
  for (int i=0; i<18; i++){
    _fl.sloped[i] = _fl.fxsloper[i]*(slope1/127.0) + _fl.slopelinear[i]*(1-(slope1/127.0)) ;
  }
}

void Slope2_ctl(byte cc_value){
// 303 resonance pulse length
  slope2 = cc_value;
}

void ArbitraryMaxF_ctl(byte cc_value){
  //TODO restart arb and synth
 arbitrary_maxF[oscillator] = (cc_value / 127.0) * 172.0 ;
}

void Filter303_ctl(byte cc_value){
  le303filterzwet = round((cc_value / 127.0) * 100.0);
  _fl.le303filterzWet();
}

void CutOffTweak_ctl(byte cc_value){
// Cutoff freq and range
  float _smallfloat = (cc_value / 127.0);
  le303ffilterzVknobs[0] = cc_value;
  le303filterzfreq = round(_smallfloat * 14000);
}

void ResoTweak_ctl(byte cc_value){
  // Resonance
  le303ffilterzVknobs[1] = cc_value;
  le303filterzreso = ((le303ffilterzVknobs[1]) / 127.0) * 5;
}

void Filter303Octave_ctl(byte cc_value){
  // Filter Octave range
  le303ffilterzVknobs[2] = cc_value;
  le303filterzoctv = ((le303ffilterzVknobs[2]) / 127.0) * 7;
}

void Filter303Glide_ctl(byte cc_value){
  glidemode = cc_value;  
}

void FilterPreAmp_ctl(byte cc_value){
  //filter Input gain
  preampleswaves = cc_value;
}

void ArpegioType_ctl(byte cc_value){
  arpegiatortype = round((cc_value / 127.0) * 8.0);
  if (arpegiatortype < 8) {
    arpegiatorOn = 1;
  } else {
    arpegiatorOn = 0;
  }
}

void ArpegioMode_ctl(byte cc_value){
  arpegmode = round((cc_value / 127.0) * 7.0);
}

void ArpegioNotesCount_ctl(byte cc_value){
  arpegnumofnotes = round((cc_value / 127.0) * 6.0) + 1;
}

void ArpegioStartOffset_ctl(byte cc_value){
  arpegstartoffset = round((cc_value / 127.0) * 18.0);  
}

void ArpegioGridC_ctl(byte cc_value){
  arpeggridC = round((cc_value / 127.0) * 8.0);
}

void ArpegioGridS_ctl(byte cc_value){
  arpeggridS = round((cc_value / 127.0) * 8.0);
}

void ArpegioLength_ctl(byte cc_value){
  arpeglengh = round((cc_value / 127.0) * 8.0);
}

void TickFromStart_Trigger_ctl(byte cc_value){
  // CuePlay
  tickposition = 0;
  clocker.startticker();
}

void StartTicking_Trigger_ctl(byte cc_value){
  clocker.startticker();
}

void StopTicking_Trigger_ctl(byte cc_value){
  _st.stopallnotes();
  clocker.stopticker();
  if (recorderrecord) {
    recorderrecord = 0;
    _rd.stopRecording();
  }
}

void RecordCCPatern_Trigger_ctl(byte cc_value){
  // record just CCs
  recordCC = 1;
  clocker.startticker();
}

void RecordPattern_Trigger_ctl(byte cc_value){
  //pattern record only on synth liners for now
  //use recordmidinotes2
  getlinerwithoutevents();
  patrecord = 1;
  clocker.startticker();
}

void StopSong_Trigger_ctl(byte cc_value){
  _se.stopdasong(); 
}

void PauseSong_Trigger_ctl(byte cc_value){
  _se.pausedasong();   
}

void PlaySong_Trigger_ctl(byte cc_value){
  _se.playdasong();
}

void SetChords_ctl(byte cc_value){
  lasetchord = round((cc_value / 127.0) * 6.0);
  if (lasetchord < 6) {
    chordson = 1;
  } else {
    chordson = 0;
  }
}

void SynthIndex_ctl(byte cc_value){
  oscillator = round((cc_value / 127.0) * 3.0);
}

void SynthXFreq_ctl(byte cc_value){
  // freqs
  //rather do up to 2X current  ?
  if (wavesfreqs[oscillator] == 1) {
    demimalmode = !demimalmode;
  } else {
    if (wavesfreqs[oscillator] <= 1) {
      demimalmode = 1;
    }
  }
  if (demimalmode) {
    wavesfreqs[oscillator] = ((cc_value / 127.0) * 10.0) / 10.0;
  }

  if (!demimalmode) {
    wavesfreqs[oscillator] = round((cc_value / 127.0) * 10.0);
  }
}

void SynthXLevel_ctl(byte cc_value){
  mixlevelsL[oscillator] = cc_value;
}

void PansLevels_ctl(byte cc_value){
  // panLs[i-1]
  panLs[oscillator] = (cc_value / 127.0);
  _mx.setwavemixlevel();
}

void MetroDrumLevel_ctl(byte cc_value){
  MasterL.gain(1, (cc_value / 127.0));
  MasterR.gain(1, (cc_value / 127.0));
}

void SynthXModulationType_ctl(byte cc_value){
  FMmodulated[oscillator] = round((cc_value / 127.0) * 3.0);
  _sn.setwavetypefromlist();
}

void SynthXtype_ctl(byte cc_value){
  Waveformstyped[oscillator] = round((cc_value / 127.0) * 11.0);
  _sn.setwavetypefromlist();
}

void SynthXOffset_ctl(byte cc_value){
  wave1offset[oscillator] = cc_value;
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    waveforms1[i + (oscillator * SYNTH_LINERS_COUNT)]->offset(
        (float)(((64.0 - wave1offset[oscillator]) / 64.0)));
    FMwaveforms1[i + (oscillator * SYNTH_LINERS_COUNT)]->offset(
        (float)(((64.0 - wave1offset[oscillator]) / 64.0)));
  }
}

void SynthXPhase_ctl(byte cc_value){
   phaselevelsL[oscillator] = round((cc_value / 127.0) * 360.0);
      _sn.setphaselevel();
}

void AnalogTouch_Toggle_ctl(byte cc_value){
  digitalplay = !digitalplay;
}

void LFOXLevel_ctl(byte cc_value){
  LFOlevel[oscillator] = cc_value;
}
      
void LFOXType_ctl(byte cc_value){
  LFOformstype[oscillator] = round((cc_value / 127.0) * 8.0);
}

void LFOXFreq_ctl(byte cc_value){
  LFOfreqs[oscillator] = cc_value;
}

void LFOXPhase_ctl(byte cc_value){
  LFOphase[oscillator] = round((cc_value / 127.0) * 360.0);
}

void LFOXOffset_ctl(byte cc_value){
  LFOoffset[oscillator] = cc_value;
}

void LFOXLSync_Toggle_ctl(byte cc_value){
  LFOsync[oscillator] = !LFOsync[oscillator];
}

void AdsrAtckDelay_ctl(byte cc_value){
  adsrlevels[0] = round((cc_value / 127.0) * 32.0);
}

void AdsrAttack_ctl(byte cc_value){
  adsrlevels[1] = cc_value;
}

void AdsrHold_ctl(byte cc_value){
  adsrlevels[2] = cc_value;
}

void AdsrDecay_ctl(byte cc_value){
  adsrlevels[3] = round((cc_value / 127.0) * 512.0);
}

void AdsrSustain_ctl(byte cc_value){
  adsrlevels[4] = round((cc_value / 127.0) * 100.0);
}

void AdsrRelease_ctl(byte cc_value){
  adsrlevels[5] = round((cc_value / 127.0) * 512.0);
}

void Filter303_Knob1_ctl(byte cc_value){
  mixle303ffilterzVknobs[0] = cc_value;
  le303filterzgainz[0] = (cc_value / 127.0);
  _fl.le303filtercontrols();
  // le303filterzgainz[0]
  //  mixle303ffilterzVknobs[0]
}

void Filter303_Knob2_ctl(byte cc_value){
  mixle303ffilterzVknobs[1] = cc_value;
  le303filterzgainz[1] = (cc_value / 127.0);
  _fl.le303filtercontrols();
}

void Filter303_Knob3_ctl(byte cc_value){
  mixle303ffilterzVknobs[2] = cc_value;
  le303filterzgainz[2] = (cc_value / 127.0);
  _fl.le303filtercontrols();
}
     
void FXBusSelector_ctl(byte cc_value){
  ccfxlineselector = map((int)((cc_value / 127.0)*100.0),0,100,0,2);
}

void ChorusVoices_ctl(byte cc_value){
  chorusVknobs[ccfxlineselector] = cc_value;
}

void LFOonFilter_ctl(byte cc_value){
  LFOonfilterz[ccfxlineselector] = round((cc_value / 127.0) * 3.0);
  _fx.filtercontrols(ccfxlineselector);
}

void BiQuadStage_ctl(byte cc_value){
  bqstage[ccfxlineselector] = round((cc_value / 127.0) * 3.0);
}

void BiQuadFreq_ctl(byte cc_value){
  bqVpot[ccfxlineselector][bqstage[ccfxlineselector]][0] = cc_value;
  bqfreq[ccfxlineselector][bqstage[ccfxlineselector]] = ((cc_value / 127.0) * bqrange) + 101;
  if (bqfreq[ccfxlineselector][bqstage[ccfxlineselector]] >= 101) {
    _fx.biquadcontrols(ccfxlineselector);
  }
}

void BiQuadSlope_ctl(byte cc_value){
  bqVpot[ccfxlineselector][bqstage[ccfxlineselector]][1] = cc_value;
  bqslope[ccfxlineselector][bqstage[ccfxlineselector]] = (cc_value / 127.0);
  if (bqfreq[ccfxlineselector][bqstage[ccfxlineselector]] >= 101) {
    _fx.biquadcontrols(ccfxlineselector);
  }
}

void BiQuadGain_ctl(byte cc_value){
  bqVpot[ccfxlineselector][bqstage[ccfxlineselector]][2] = cc_value;
  bqgain[ccfxlineselector][bqstage[ccfxlineselector]] = (cc_value / 127.0);
  if (bqfreq[ccfxlineselector][bqstage[ccfxlineselector]] >= 101) {
    _fx.biquadcontrols(ccfxlineselector);
  }
}

void BiQuadType_ctl(byte cc_value){
   // type
  bqtype[ccfxlineselector][bqstage[ccfxlineselector]] =
      round((cc_value / 127.0) * 5.0);
  if (bqfreq[ccfxlineselector][bqstage[ccfxlineselector]] >= 101) {
    _fx.biquadcontrols(ccfxlineselector);
  }
}

void GranularGrains_Knob1_ctl(byte cc_value){
  //granular grains
  granularVknobs[ccfxlineselector][0] = cc_value;
}

void GranularSpeed_Knob2_ctl(byte cc_value){
  //granular speed ratio
  granularVknobs[ccfxlineselector][1] = cc_value;
  _fx.granularcontrols(ccfxlineselector);
}

void GranularShifting_Toggle_ctl(byte cc_value){
  granular_shifting[ccfxlineselector] = !granular_shifting[ccfxlineselector];
  _fx.granular_pitch_shift(ccfxlineselector);
}

void GranularFreeze_Toggle_ctl(byte cc_value){
  granular_freezing[ccfxlineselector] = !granular_freezing[ccfxlineselector];
  _fx.granular_freeze(ccfxlineselector);
}

void ReverbSize_ctl(byte cc_value){
  reverbVknobs[ccfxlineselector][0] = cc_value;
  _fx.freeverbscontrl(ccfxlineselector);
}

void BitCrusherSamples_ctl(byte cc_value){
  bitcrusherVknobs[ccfxlineselector][0] = round((cc_value / 127.0) * 16.0);
  _fx.bitcrusherctrl(ccfxlineselector);
}

void BitCrusherBits_ctl(byte cc_value){
  bitcrusherVknobs[ccfxlineselector][1] = cc_value;
  _fx.bitcrusherctrl(ccfxlineselector);
}

void FFilter_Cutoff_Knob1_ctl(byte cc_value){
  mixffilterzVknobs[ccfxlineselector][0] = cc_value;
  _fx.filtercontrols(ccfxlineselector);
}

void FFilter_Reso_Knob2_ctl(byte cc_value){
  mixffilterzVknobs[ccfxlineselector][1] = cc_value;
      _fx.filtercontrols(ccfxlineselector);
}

void FFilter_Oct_Knob3_ctl(byte cc_value){
   mixffilterzVknobs[ccfxlineselector][2] = cc_value;
      _fx.filtercontrols(ccfxlineselector);
}

void FFilter_LowPass_Knob4_ctl(byte cc_value){
  ffilterzVknobs[ccfxlineselector][0] = cc_value;
  _fx.filtercontrols(ccfxlineselector);
}

void FFilter_BandPass_Knob5_ctl(byte cc_value){
 ffilterzVknobs[ccfxlineselector][1] = cc_value;
  _fx.filtercontrols(ccfxlineselector);
}

void FFilter_HighPass_Knob6_ctl(byte cc_value){
  ffilterzVknobs[ccfxlineselector][2] = cc_value;
  _fx.filtercontrols(ccfxlineselector);
}

void FlangerOffset_Knob1_ctl(byte cc_value){
  flangerVknobs[ccfxlineselector][0] = cc_value;
  _fx.flangercontrols(ccfxlineselector);
}

void FlangerDepth_Knob2_ctl(byte cc_value){
  flangerVknobs[ccfxlineselector][1] = cc_value;
  _fx.flangercontrols(ccfxlineselector);
}

void FlangerDelay_Knob3_ctl(byte cc_value){
  flangerVknobs[ccfxlineselector][2] = cc_value;
  _fx.flangercontrols(ccfxlineselector);
}

void DelayTimeSelection_Knob1_ctl(byte cc_value){
  delayVknobs[ccfxlineselector][0] = cc_value;
  _fx.restartdelayline(ccfxlineselector);
}

void DelayTimeMultiplier_Knob2_ctl(byte cc_value){
  delayVknobs[ccfxlineselector][1] = cc_value;
  _fx.restartdelayline(ccfxlineselector);
}

void DelayFeedback_Knob3_ctl(byte cc_value){
  delayVknobs[ccfxlineselector][2] = cc_value;
  _fx.restartdelayline(ccfxlineselector);
}

void AudioInVolume_ctl(byte cc_value){
  // Audio In level
  MasterL.gain(2, (cc_value / 127.0));
  MasterR.gain(2, (cc_value / 127.0));
}

void DebugCPU_Toggle_ctl(byte cc_value){
  debug_cpu = !debug_cpu;
}

void SetBPMs_ctl(byte cc_value){
  // bpms
  millitickinterval = map(cc_value, 0, 127, 250, 63);
  _st.setbpms();
}

void SaveToNewPattern_Trigger_ctl(byte cc_value){
  //to save in a new pattern
  // TODO reenable
  patterns_names_offset = patterns_count ;
  //_pt.writelemidi();
}

void LoadFirstPattern_Trigger_ctl(byte cc_value){
  _po.clearlapattern();
  //loads 1st pattern, increment patterns_names_offset for a different one
  patterns_names_offset = 0 ;
  call_parsepattern();
}

void RecordAudio_Trigger_ctl(byte cc_value){
  // Recorder record
  recorderrecord = 1;
  if (recorderstop) {
    recorderstop = 0;
  }
  if (recorderplay) {
    recorderplay = 0;
  }
  _rd.startRecording();
}

void PlayLoadedAudio_Trigger_ctl(byte cc_value){
  // play recorder
  recorderplay = 1;
  recorderstop = 0;
  if (recorderrecord) {
    recorderrecord = 0;
    _rd.stopRecording();
  }
  _rd.playrecordsd();
}

void StopRecording_Trigger_ctl(byte cc_value){
  // stop recorder
  recorderstop = 1;
  if (recorderplay) {
    recorderplay = 0;
  }
  if (recorderrecord) {
    recorderrecord = 0;
    _rd.stopRecording();
  }
}

void LoadFirstPreset_Toggle_ctl(byte cc_value){
  presets_names_offset = 0 ;
  _ps.refresh_presets_names();
  _ps.parsefile();
}

void MergeSynthPatterns_Trigger_ctl(byte cc_value){
  //experimental
  _po.merge_synth_partition_liners();
}

void FlashLineVolume_Knob1_ctl(byte cc_value){
  smixervknobs[0] = cc_value;
}

void FlashLineVolume_Knob2_ctl(byte cc_value){
  smixervknobs[1] = cc_value;
}

void FlashLineVolume_Knob3_ctl(byte cc_value){
  smixervknobs[2] = cc_value;
}

void FlashLineVolume_Knob4_ctl(byte cc_value){
  smixervknobs[3] = cc_value;
}

void FlashLineVolume_Knob5_ctl(byte cc_value){
  smixervknobs[4] = cc_value;
}

void FlashLineVolume_Knob6_ctl(byte cc_value){
  smixervknobs[5] = cc_value;
}

void FlashLineVolume_Knob7_ctl(byte cc_value){
  smixervknobs[6] = cc_value;
}

void FlashLineVolume_Knob8_ctl(byte cc_value){
  smixervknobs[7] = cc_value;
}

void FlashLineVolume_Knob9_ctl(byte cc_value){
  smixervknobs[8] = cc_value;
}

void FlashLineVolume_Knob10_ctl(byte cc_value){
  smixervknobs[9] = cc_value;
}

void FlashLineVolume_Knob11_ctl(byte cc_value){
  smixervknobs[10] = cc_value;
}

void FlashLineVolume_Knob12_ctl(byte cc_value){
  smixervknobs[11] = cc_value;
}

void FlashLineVolume_Knob13_ctl(byte cc_value){
  smixervknobs[12] = cc_value;
}

void FlashLineVolume_Knob14_ctl(byte cc_value){
  smixervknobs[13] = cc_value;
}

void FlashLineVolume_Knob15_ctl(byte cc_value){
  smixervknobs[14] = cc_value;
}

void FlashLineVolume_Knob16_ctl(byte cc_value){
  smixervknobs[15] = cc_value;
}
