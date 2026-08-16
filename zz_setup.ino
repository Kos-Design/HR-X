
void setupSD() {
  const int chipSelect = 10;
  if (!(SD.begin(chipSelect))) {
    consoler.println((char *)"initialization SD failed!");
    return;
  }
  //Serial.println(CtlCount);
  _rd.clear_temp_files();
  _sp.initializesamplesselectedlist();
  consoler.println((char *)"Scanning Samples");
  _sp.dosoundlist();
  consoler.println((char *)"Scanning Presets");
  _ps.catalog->list_files();
  consoler.println((char *)"Scanning Patterns");
  _pt.catalog->list_files();
  consoler.println((char *)"Scanning Waveforms");
  _wf.catalog->list_files();
  consoler.println((char *)"Scanning Songs");
  _sg.catalog->list_files();
    consoler.println((char *)"Scanning Records");
  _rd.catalog->list_files();
  consoler.println((char *)"Scanning MP3s");
  _mp.count_mp3s();
}

void call_sn_show(){
  _sn.show();
}
void call_ad_show(){
  _ad.show();
}
void call_fl_show(){
  _ft.show();
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

void call_setwavetypefromlist(){
  _sn.setwavetypefromlist();
}
void call_setwavemixlevel(){
  _mx.setwavemixlevel();
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

void call_st_onboardPanel(){
  _st.OnBoardVpanel();
}
void call_set_bpms(){
  _st.setbpms();
}
void call_refresh_flash_track(){
  _pe.refresh_flash_track();
}

void setup() {

  // consoler.println((char*)"initializing...");
  // settime();
  SPI.setSCK(14);  // Audio shield has SCK on pin 14
  SPI.setMOSI(7);  // Audio shield has MOSI on pin 7
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
  // metrodrum1.pitchMod(0.9);
  AudioInterrupts();

  initextmems();
  // setupmemtest();
  Serial.begin(9600);
  gg.fx[0].f_index = 0;
  gg.fx[1].f_index = 1;
  gg.fx[2].f_index = 2;
  dm.initializeconsolemsg();
  dm.setupscreen();
  consoler.wipe();
  consoler.println((char *)"initializing...");
  consoler.refresh();
  _sg.initializepatternonsong();
  //delay(100);
  //Initialise the AutoVolumeLeveller
  //audioShield.autoVolumeControl(1, 1, 0, -6, 40, 20); // **BUG** with a max
  //gain of 0, turning the AVC off leaves a hung AVC problem where the attack
  //seems to hang in a loop. with it set 1 or 2, this does not occur.
  //audioShield.autoVolumeDisable();
  //audioShield.audioPostProcessorEnable();
  consoler.println((char *)"Setting USB Host...");
  delay(100);

  setuphubusb();
  consoler.println((char *)"USB Host Ready !");
  delay(50);

  consoler.println((char *)"Scanning SD Card");
  delay(100);
  setupSD();
  consoler.println((char *)"SD Card OK !");
  Pads.begin();
  consoler.println((char *)"Setting up I/O");
  
  pinMode(MULTIPLEXER_PIN, INPUT_PULLUP);
  
  for (int i = 0; i < 128; i++) {
    gg.midiknobassigned[i] = 0;
  }
  consoler.println((char *)"I/O Set !");
  consoler.println((char *)"Loading Defaults");
  Tocker.stopticker();
  setupdefaultvalues();
  _sp.Doautoassign();
  consoler.println((char *)"All Done !");
  consoler.println((char *)"starting muxer");
  consoler.refresh();

  Muxer.start();
  //queue1.begin();
  AudioMemory(1200);
  AudioShield.volume(0.0);
  AudioShield.enable();
  _st.set_in_source();
  AudioShield.volume(1.0);
  _rd.playrecordsd_pathed("SOUNDSET/REC/LOOP22#L.RAW");
  Tocker.attach_24(advance_tick);
  Tocker.attach_long(once_in_a_while);
  //clocker.attach_3(fairly_often);
  Tocker.attach_16(at_a_paced_rate);
  //fft256.averageTogether(2);
  fft256.windowFunction(AudioWindowHanning256);
  clocker.setBPM(120);
  clocker.setPPQN(96);
  clocker.attach_96(Tocker.click);

  consoler.println((char *)"Enjoy !");
  consoler.refresh();

}

void Volume_ctl(byte cc_value){
  // audioShield.volume(1.0);
  gg.mixlevelsM[0] = cc_value;
  _mx.setmastersmixlevel(0);
}

void SynthVolume_ctl(byte cc_value){
  // main synth level
  gg.mixlevelsM[1] = cc_value;
  _mx.setmastersmixlevel(1);
}

void SDPlayerVolume_ctl(byte cc_value){
  // SDSamplePlayer
  MasterL.gain(0, (1.0 - (cc_value / 127.0)));
  MasterR.gain(0, (1.0 - (cc_value / 127.0)));
}

void FlashVolume_ctl(byte cc_value){
  // flash
  gg.mixlevelsM[2] = cc_value;
  _mx.setmastersmixlevel(2);
}

void Wet1Volume_ctl(byte cc_value){
  // WetMixMaster1
  gg.WetMixMasters[1] = cc_value;
  _mx.wetmixmastercontrols();
}

void Wet2Volume_ctl(byte cc_value){
  // WetMixMaster2
  gg.WetMixMasters[2] = cc_value;
  _mx.wetmixmastercontrols();
}

void Wet3Volume_ctl(byte cc_value){
  // WetMixMaster3
  gg.WetMixMasters[3] = cc_value;
  _mx.wetmixmastercontrols();
}

void DrySampler_ctl(byte cc_value){
  /// sampler wetness
  gg.wetins[1] = cc_value;
  _mx.set_dry_mix(1);
}

void DrySynth_ctl(byte cc_value){
  /// synth wetness
  gg.wetins[0] = cc_value;
  _mx.set_dry_mix(0);
}

void DryAudioIn_ctl(byte cc_value){
  /// audio In wetness
  gg.wetins[2] = cc_value;
  _mx.set_dry_mix(2);
}

void Slope1_ctl(byte cc_value){
  // 303 cutoff pulse length
  gg.cut_off_slope = cc_value;
  for (int i=0; i<18; i++){
    _ft.sloped[i] = _ft.fxsloper[i]*(gg.cut_off_slope/127.0) + _ft.slopelinear[i]*(1-(gg.cut_off_slope/127.0)) ;
  }
}

void Slope2_ctl(byte cc_value){
// 303 resonance pulse length
  gg.resonance_slope = cc_value;
}

void ArbitraryMaxF_ctl(byte cc_value){
  //TODO restart arb and synth
 gg.arbitrary_maxF[lv.oscillator] = (cc_value / 127.0) * 172.0 ;
}

void Filter303_ctl(byte cc_value){
  gg.le303filterzwet = cc_value;
  _ft.le303filterzWet();
}

void CutOffTweak_ctl(byte cc_value){
// Cutoff freq and range
  float _smallfloat = (cc_value / 127.0);
  gg.le303ffilterzVknobs[0] = cc_value;
  // used to be x 14000
  gg.le303filterzfreq = lround(_smallfloat * 14000);
}

void ResoTweak_ctl(byte cc_value){
  // Resonance
  gg.le303ffilterzVknobs[1] = cc_value;
  gg.le303filterzreso = cc_value;
}

void set_Portamento_time_ctl(byte cc_value){
  gg.portamento_time = cc_value ;   
}

void set_Portamento_height_ctl(byte cc_value){
  gg.portamento_height = cc_value ;   
}

void FilterPreAmp_ctl(byte cc_value){
  //filter Input gain
  gg.preampleswaves = cc_value;
}

void ArpegioType_ctl(byte cc_value){
  gg.arpegiatortype = round((cc_value / 127.0) * 8.0);
  if (gg.arpegiatortype < 8) {
    gg.arpegiatorOn = 1;
  } else {
    gg.arpegiatorOn = 0;
  }
}

void ArpegioMode_ctl(byte cc_value){
  gg.arpegmode = round((cc_value / 127.0) * 7.0);
}

void ArpegioNotesCount_ctl(byte cc_value){
  gg.arpegnumofnotes = round((cc_value / 127.0) * 6.0) + 1;
}

void ArpegioStartOffset_ctl(byte cc_value){
  gg.arpegstartoffset = round((cc_value / 127.0) * 18.0);  
}

void ArpegioGridC_ctl(byte cc_value){
  gg.arpeggridC = round((cc_value / 127.0) * 8.0);
}

void ArpegioGridS_ctl(byte cc_value){
  gg.arpeggridS = round((cc_value / 127.0) * 8.0);
}

void ArpegioLength_ctl(byte cc_value){
  gg.arpeglengh = round((cc_value / 127.0) * 8.0);
}

void TickFromStart_Trigger_ctl(byte cc_value){
  // CuePlay
  lv.tickposition = 0;
  Tocker.startticker();
}

void StartTicking_Trigger_ctl(byte cc_value){
  Tocker.startticker();
}

void StopTicking_Trigger_ctl(byte cc_value){
  stopallnotes();
  Tocker.stopticker();
  if (_rd.recorderrecord) {
    _rd.recorderrecord = 0;
    _rd.stopRecording();
  }
}

void RecordCCPatern_Trigger_ctl(byte cc_value){
  // record just CCs
  lv.recordCC = 1;
  Tocker.startticker();
}

void RecordPattern_Trigger_ctl(byte cc_value){
  //pattern record only on synth liners for now
  //use recordmidinotes2
  lv.patrecord = 1;
  Tocker.startticker();
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
  gg.lasetchord = round((cc_value / 127.0) * 6.0);
  if (gg.lasetchord < 6) {
    gg.chordson = 1;
  } else {
    gg.chordson = 0;
  }
}

void SynthIndex_ctl(byte cc_value){
  lv.oscillator = round((cc_value / 127.0) * 3.0);
}

void SynthXFreq_ctl(byte cc_value){
  // freqs
  gg.wavesfreqs[lv.oscillator] = (cc_value / 127.0) * 2.0;
}

void SynthXLevel_ctl(byte cc_value){
  gg.mixlevelsL[lv.oscillator] = cc_value;
}

void PansLevels_ctl(byte cc_value){
  gg.panLs = cc_value;
}

void MetroDrumLevel_ctl(byte cc_value){
  MasterL.gain(1, (cc_value / 127.0));
  MasterR.gain(1, (cc_value / 127.0));
}

void SynthXModulationType_ctl(byte cc_value){
  gg.FMmodulated[lv.oscillator] = round((cc_value / 127.0) * 3.0);
  _sn.setwavetypefromlist();
}

void SynthXtype_ctl(byte cc_value){
  gg.Waveformstyped[lv.oscillator] = round((cc_value / 127.0) * 11.0);
  _sn.setwavetypefromlist();
}

void SynthXOffset_ctl(byte cc_value){
  gg.wave1offset[lv.oscillator] = cc_value;
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    waveforms1[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->offset(
        (float)(((64.0 - gg.wave1offset[lv.oscillator]) / 64.0)));
    FMwaveforms1[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->offset(
        (float)(((64.0 - gg.wave1offset[lv.oscillator]) / 64.0)));
  }
}

void SynthXPhase_ctl(byte cc_value){
  gg.phaselevelsL[lv.oscillator] = cc_value ;
  _sn.setphaselevel();
}

void AnalogTouch_Toggle_ctl(byte cc_value){
  gg.digitalplay = !gg.digitalplay;
}

void LFOXLevel_ctl(byte cc_value){
  gg.LFOlevel[lv.oscillator] = cc_value;
}
      
void LFOXType_ctl(byte cc_value){
  gg.LFOformstype[lv.oscillator] = round((cc_value / 127.0) * 8.0);
}

void LFOXFreq_ctl(byte cc_value){
  gg.LFOHz[lv.oscillator] = (cc_value/127.0)*2.0;
}

void LFOXPhase_ctl(byte cc_value){
  gg.LFOphase[lv.oscillator] = cc_value;
}

void LFOXOffset_ctl(byte cc_value){
  gg.LFOoffset[lv.oscillator] = cc_value;
}

void LFOXLSync_Toggle_ctl(byte cc_value){
  gg.LFOsync[lv.oscillator] = !gg.LFOsync[lv.oscillator];
}

void AdsrAtckDelay_ctl(byte cc_value){
  gg.adsrlevels[AttackDelay] = round((cc_value / 127.0) * 32.0);
}

void AdsrAttack_ctl(byte cc_value){
  gg.adsrlevels[Attack] = cc_value;
}

void AdsrHold_ctl(byte cc_value){
  gg.adsrlevels[Hold] = cc_value;
}

void AdsrDecay_ctl(byte cc_value){
  gg.adsrlevels[Decay] = round((cc_value / 127.0) * 512.0);
}

void AdsrSustain_ctl(byte cc_value){
  gg.adsrlevels[Sustain] = round((cc_value / 127.0) * 100.0);
}

void AdsrRelease_ctl(byte cc_value){
  gg.adsrlevels[Release] = round((cc_value / 127.0) * 512.0);
}

void Filter303_Knob1_ctl(byte cc_value){
  gg.mixle303ffilterzVknobs[0] = cc_value;
  gg.le303filterzgainz[0] = cc_value;
  _ft.le303filtercontrols();
  // gg.le303filterzgainz[0]
  //  gg.mixle303ffilterzVknobs[0]
}

void Filter303_Knob2_ctl(byte cc_value){
  gg.mixle303ffilterzVknobs[1] = cc_value;
  gg.le303filterzgainz[1] = cc_value ;
  _ft.le303filtercontrols();
}

void Filter303_Knob3_ctl(byte cc_value){
  gg.mixle303ffilterzVknobs[2] = cc_value;
  gg.le303filterzgainz[2] = cc_value ;
  _ft.le303filtercontrols();
}
     
void FXBusSelector_ctl(byte cc_value){
  lv.fidx = map((int)((cc_value / 127.0)*100.0),0,100,0,2);
}

void ChorusVoices_ctl(byte cc_value){
  gg.fx[lv.fidx].chorusVknobs = cc_value;
}

void LFOonFilter_ctl(byte cc_value){
  gg.fx[lv.fidx].LFOonfilterz = round((cc_value / 127.0) * 3.0);
  _fx.filtercontrols(lv.fidx);
}

void BiQuadStage_ctl(byte cc_value){
  gg.fx[lv.fidx].bqstage = round((cc_value / 127.0) * 3.0);
}

void BiQuadFreq_ctl(byte cc_value){
  gg.fx[lv.fidx].bqVpot[gg.fx[lv.fidx].bqstage][0] = cc_value;
  gg.fx[lv.fidx].bqfreq[gg.fx[lv.fidx].bqstage] = ((cc_value / 127.0) * _fx.bqrange) + 101;
  if (gg.fx[lv.fidx].bqfreq[gg.fx[lv.fidx].bqstage] >= 101) {
    _fx.biquadcontrols(lv.fidx);
  }
}

void BiQuadSlope_ctl(byte cc_value){
  gg.fx[lv.fidx].bqVpot[gg.fx[lv.fidx].bqstage][1] = cc_value;
  gg.fx[lv.fidx].bqslope[gg.fx[lv.fidx].bqstage] = 0.001+(cc_value / 127.0)*5.0;
  if (gg.fx[lv.fidx].bqfreq[gg.fx[lv.fidx].bqstage] >= 101) {
    _fx.biquadcontrols(lv.fidx);
  }
}

void BiQuadGain_ctl(byte cc_value){
  gg.fx[lv.fidx].bqVpot[gg.fx[lv.fidx].bqstage][2] = cc_value;
  gg.fx[lv.fidx].bqgain[gg.fx[lv.fidx].bqstage] = 100.0 - (cc_value / 127.0)*200.0;
  if (gg.fx[lv.fidx].bqfreq[gg.fx[lv.fidx].bqstage] >= 101) {
    _fx.biquadcontrols(lv.fidx);
  }
}

void BiQuadType_ctl(byte cc_value){
   // type
  gg.fx[lv.fidx].bqtype[gg.fx[lv.fidx].bqstage] = round((cc_value / 127.0) * 6.0);
  if (gg.fx[lv.fidx].bqfreq[gg.fx[lv.fidx].bqstage] >= 101) {
    _fx.biquadcontrols(lv.fidx);
  }
}

void GranularGrains_Knob1_ctl(byte cc_value){
  //granular grains
  gg.fx[lv.fidx].granularVknobs[0] = cc_value;
}

void GranularSpeed_Knob2_ctl(byte cc_value){
  //granular speed ratio
  gg.fx[lv.fidx].granularVknobs[1] = cc_value;
  _fx.granularcontrols(lv.fidx);
}

void GranularShifting_Toggle_ctl(byte cc_value){
  gg.fx[lv.fidx].granular_shifting = !gg.fx[lv.fidx].granular_shifting;
  _fx.granular_pitch_shift(lv.fidx);
}

void GranularFreeze_Toggle_ctl(byte cc_value){
  gg.fx[lv.fidx].granular_freezing = !gg.fx[lv.fidx].granular_freezing;
  _fx.granular_freeze(lv.fidx);
}

void ReverbSize_ctl(byte cc_value){
  gg.fx[lv.fidx].reverbVknobs[0] = cc_value;
  _fx.freeverbscontrl(lv.fidx);
}

void BitCrusherSamples_ctl(byte cc_value){
  gg.fx[lv.fidx].bitcrusherVknobs[0] = round((cc_value / 127.0) * 16.0);
  _fx.bitcrusherctrl(lv.fidx);
}

void BitCrusherBits_ctl(byte cc_value){
  gg.fx[lv.fidx].bitcrusherVknobs[1] = cc_value;
  _fx.bitcrusherctrl(lv.fidx);
}

void FFilter_Cutoff_Knob1_ctl(byte cc_value){
  gg.fx[lv.fidx].mixffilterzVknobs[0] = cc_value;
  _fx.filtercontrols(lv.fidx);
}

void FFilter_Reso_Knob2_ctl(byte cc_value){
  gg.fx[lv.fidx].mixffilterzVknobs[1] = cc_value;
      _fx.filtercontrols(lv.fidx);
}

void FFilter_Oct_Knob3_ctl(byte cc_value){
   gg.fx[lv.fidx].mixffilterzVknobs[2] = cc_value;
      _fx.filtercontrols(lv.fidx);
}

void FFilter_LowPass_Knob4_ctl(byte cc_value){
  gg.fx[lv.fidx].ffilterzVknobs[0] = cc_value;
  _fx.filtercontrols(lv.fidx);
}

void FFilter_BandPass_Knob5_ctl(byte cc_value){
 gg.fx[lv.fidx].ffilterzVknobs[1] = cc_value;
  _fx.filtercontrols(lv.fidx);
}

void FFilter_HighPass_Knob6_ctl(byte cc_value){
  gg.fx[lv.fidx].ffilterzVknobs[2] = cc_value;
  _fx.filtercontrols(lv.fidx);
}

void FlangerOffset_Knob1_ctl(byte cc_value){
  gg.fx[lv.fidx].flangerVknobs[0] = cc_value;
  _fx.flangercontrols(lv.fidx);
}

void FlangerDepth_Knob2_ctl(byte cc_value){
  gg.fx[lv.fidx].flangerVknobs[1] = cc_value;
  _fx.flangercontrols(lv.fidx);
}

void FlangerDelay_Knob3_ctl(byte cc_value){
  gg.fx[lv.fidx].flangerVknobs[2] = cc_value;
  _fx.flangercontrols(lv.fidx);
}

void DelayTimeSelection_Knob1_ctl(byte cc_value){
  gg.fx[lv.fidx].delayVknobs[0] = cc_value;
  _fx.restartdelayline(lv.fidx);
}

void DelayTimeMultiplier_Knob2_ctl(byte cc_value){
  gg.fx[lv.fidx].delayVknobs[1] = cc_value;
  _fx.restartdelayline(lv.fidx);
}

void DelayFeedback_Knob3_ctl(byte cc_value){
  gg.fx[lv.fidx].delayVknobs[2] = cc_value;
  _fx.restartdelayline(lv.fidx);
}

void AudioInVolume_ctl(byte cc_value){
  // Audio In level
  MasterL.gain(2, (cc_value / 127.0));
  MasterR.gain(2, (cc_value / 127.0));
}

void SetBPMs_ctl(byte cc_value){
  // bpms
  gg.millitickinterval = map(cc_value, 0, 127, 250, 63);
  _st.setbpms();
}

void SaveToNewPattern_Trigger_ctl(byte cc_value){
  //to save in a new pattern
  // TODO reenable
  _pt.catalog->displayable_offset = _pt.catalog->files_counter ;
  //_pt.writelemidi();
}

void LoadFirstPattern_Trigger_ctl(byte cc_value){
  _po.clearlapattern();
  //loads 1st pattern, increment patterns_names_offset for a different one
  _pt.catalog->displayable_offset = 0 ;
  _pt.parsepattern();
}

void RecordAudio_Trigger_ctl(byte cc_value){
  // Recorder record
  _rd.recorderrecord = 1;
  if (_rd.recorderstop) {
    _rd.recorderstop = 0;
  }
  if (_rd.recorderplay) {
    _rd.recorderplay = 0;
  }
  _rd.startRecording();
}

void PlayLoadedAudio_Trigger_ctl(byte cc_value){
  // play recorder
  _rd.recorderplay = 1;
  _rd.recorderstop = 0;
  if (_rd.recorderrecord) {
    _rd.recorderrecord = 0;
    _rd.stopRecording();
  }
  _rd.playrecordsd();
}

void StopRecording_Trigger_ctl(byte cc_value){
  // stop recorder
  _rd.recorderstop = 1;
  if (_rd.recorderplay) {
    _rd.recorderplay = 0;
  }
  if (_rd.recorderrecord) {
    _rd.recorderrecord = 0;
    _rd.stopRecording();
  }
}

void LoadFirstPreset_Toggle_ctl(byte cc_value){
  _ps.catalog->displayable_offset = 0 ;
  _ps.catalog->refresh_files_names();
  _ps.read_preset();
}

void MergeSynthPatterns_Trigger_ctl(byte cc_value){
  //experimental
  _po.merge_synth_partition_liners();
}

void FlashLineVolume_Knob1_ctl(byte cc_value){
  gg.smixervknobs[0] = cc_value;
}

void FlashLineVolume_Knob2_ctl(byte cc_value){
  gg.smixervknobs[1] = cc_value;
}

void FlashLineVolume_Knob3_ctl(byte cc_value){
  gg.smixervknobs[2] = cc_value;
}

void FlashLineVolume_Knob4_ctl(byte cc_value){
  gg.smixervknobs[3] = cc_value;
}

void FlashLineVolume_Knob5_ctl(byte cc_value){
  gg.smixervknobs[4] = cc_value;
}

void FlashLineVolume_Knob6_ctl(byte cc_value){
  gg.smixervknobs[5] = cc_value;
}

void FlashLineVolume_Knob7_ctl(byte cc_value){
  gg.smixervknobs[6] = cc_value;
}

void FlashLineVolume_Knob8_ctl(byte cc_value){
  gg.smixervknobs[7] = cc_value;
}

void FlashLineVolume_Knob9_ctl(byte cc_value){
  gg.smixervknobs[8] = cc_value;
}

void FlashLineVolume_Knob10_ctl(byte cc_value){
  gg.smixervknobs[9] = cc_value;
}

void FlashLineVolume_Knob11_ctl(byte cc_value){
  gg.smixervknobs[10] = cc_value;
}

void FlashLineVolume_Knob12_ctl(byte cc_value){
  gg.smixervknobs[11] = cc_value;
}

void FlashLineVolume_Knob13_ctl(byte cc_value){
  gg.smixervknobs[12] = cc_value;
}

void FlashLineVolume_Knob14_ctl(byte cc_value){
  gg.smixervknobs[13] = cc_value;
}

void FlashLineVolume_Knob15_ctl(byte cc_value){
  gg.smixervknobs[14] = cc_value;
}

void FlashLineVolume_Knob16_ctl(byte cc_value){
  gg.smixervknobs[15] = cc_value;
}

void USB_In_Volume_ctl(byte cc_value){
  InMixL.gain(0,cc_value/127.0) ;
  InMixR.gain(0,cc_value/127.0) ;
}

void toggle_stereo(byte cc_value){
  if (!stereoWidth.stereo_toggled) {
    stereoWidth.stereo_toggled = true ;
    stereoWidth.connect();
    stereoWidth.setCutoff(1950,1800.5);
    stereoWidth.setResonance(0.8,0.8);
  }
}

void turn_off_stereo(byte cc_value){
  stereoWidth.stereo_toggled = false ;
  stereoWidth.disconnect();
}

void adjust_osc_timee_ctl(byte cc_val) {
  oscillisc_timee = map(cc_val,0,127, 4, 16);
}

void adjust_osc_framerate_ctl(byte cc_val) {
  osc_framerate = map(cc_val,0,127, 8, 42);
}

void adjust_osc_refresher_period_ctl(byte cc_val) {
  osc_refresher_period = 1 + (cc_val / 2) ; 
}

void adjust_rota_decrease_ctl(byte cc_val){
  int this_rota = myEnc.read();
  myEnc.write(this_rota-4);
  evalrota(); 
}

void rota_increase_ctl(byte cc_val){
  int this_rota = myEnc.read();
  myEnc.write(this_rota+4);
  evalrota() ;
}

void cancel_pushed_ctl(byte cc_val){
  if (lv.navlevel > 0) {
    lv.navlevel--;
  }
  if (!lv.navlevel) {
    dm.displaymenu();
    dm.reinitsublevels(1);
    return;
  }
  lv.sublevels[lv.navlevel] = 0;
  if (lv.retroaction) {
    lv.sublevels[lv.navlevel] = lv.retroaction ;
    lv.rota_true_pos = lv.retroaction;
    myEnc.write(lv.retroaction * 4);
    lv.retroaction = 0;
  }
  dm.show();
  return;
}

void validate_pushed_ctl(byte cc_val){
  lv.navlevel++;
  lv.rota_true_pos = lv.sublevels[lv.navlevel];
  myEnc.write(lv.sublevels[lv.navlevel] * 4);
  dm.show();
}

void adjust_waveEditor_pitch_ctl(byte cc_val) {
  _rd.pitcher = (cc_val/127.0) * 2.0; 
}

void spectro_Toggle_ctl(byte unused_cc){
  showing_oscilloscope = !showing_oscilloscope;
  stop_spectro();
  if (showing_oscilloscope) start_spectro();
}

void eq_display_Toggle_ctl(byte cc_value){
  lv.showing_eq = !lv.showing_eq ;
}
void call_stopallnotes(){
  stopallnotes();
}