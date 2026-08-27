#include "Functions.h"
#include "WaveEditorMenu.h"
#include <USBHost_t36.h>
#include "SettingsMenu.h"
#include "SynthMenu.h"
#include "LfoMenu.h"
#include "Triggers.h"
#include "Patterns.h"
#include "WaveFormer.h"
#include "SamplerMenu.h"
#include "SongsMenu.h"
#include "Voices.h"
#include "muxer.h"
#include "pads.h"
#include "FxMenu.h"
#include "PresetsMenu.h"
#include "KnobAssigner.h"
#include "Frequencies.h"

extern USBHost myusb;
extern USBHub hub1;
extern USBHub hub2;
extern USBHub hub3;
extern MIDIDevice midi1;
extern MIDIDevice midi2;
extern MIDIDevice midi3;

void initextmems() {

  float tmparray[128] = {
    8.2129616380,
    8.7013297508,
    9.2187377429,
    9.7669124151,
    10.3476832497,
    10.9629885152,
    11.6148817357,
    12.3055385443,
    13.0372639439,
    13.8125000000,
    14.6338339908,
    15.5040070423,
    16.4259232760,
    17.4026595017,
    18.4374754857,
    19.5338248303,
    20.6953664994,
    21.9259770303,
    23.2297634714,
    24.6110770886,
    26.0745278878,
    27.6250000000,
    29.2676679817,
    31.0080140845,
    32.8518465520,
    34.8053190033,
    36.8749509714,
    39.0676496606,
    41.3907329987,
    43.8519540606,
    46.4595269428,
    49.2221541773,
    52.1490557757,
    55.2500000000,
    58.5353359634,
    62.0160281691,
    65.7036931039,
    69.6106380067,
    73.7499019429,
    78.1352993211,
    82.7814659974,
    87.7039081212,
    92.9190538855,
    98.4443083545,
    104.2981115513,
    110.5000000000,
    117.0706719267,
    124.0320563382,
    131.4073862078,
    139.2212760134,
    147.4998038858,
    156.2705986422,
    165.5629319949,
    175.4078162425,
    185.8381077711,
    196.8886167090,
    208.5962231027,
    221.0000000000,
    234.1413438534,
    248.0641126764,
    262.8147724156,
    278.4425520268,
    294.9996077716,
    312.5411972845,
    331.1258639897,
    350.8156324850,
    371.6762155421,
    393.7772334180,
    417.1924462053,
    442.0000000000,
    468.2826877068,
    496.1282253527,
    525.6295448312,
    556.8851040535,
    589.9992155432,
    625.0823945689,
    662.2517279795,
    701.6312649699,
    743.3524310843,
    787.5544668361,
    834.3848924106,
    884.0000000000,
    936.5653754136,
    992.2564507055,
    1051.2590896624,
    1113.7702081071,
    1179.9984310863,
    1250.1647891378,
    1324.5034559590,
    1403.2625299399,
    1486.7048621686,
    1575.1089336721,
    1668.7697848212,
    1768.0000000000,
    1873.1307508272,
    1984.5129014110,
    2102.5181793248,
    2227.5404162141,
    2359.9968621726,
    2500.3295782756,
    2649.0069119180,
    2806.5250598798,
    2973.4097243371,
    3150.2178673442,
    3337.5395696425,
    3536.0000000000,
    3746.2615016545,
    3969.0258028219,
    4205.0363586496,
    4455.0808324283,
    4719.9937243452,
    5000.6591565513,
    5298.0138238359,
    5613.0501197596,
    5946.8194486743,
    6300.4357346885,
    6675.0791392849,
    7072.0000000000,
    7492.5230033089,
    7938.0516056439,
    8410.0727172992,
    8910.1616648565,
    9439.9874486905,
    10001.3183131025,
    10596.0276476719,
    11226.1002395191,
    11893.6388973485,
    12600.8714693770

  };

  memset(bb.granularMemory, 0, sizeof(bb.granularMemory));
  memset(bb.chorusdelayline, 0, sizeof(bb.chorusdelayline));
  memset(bb.flangedelay, 0, sizeof(bb.flangedelay));
  memset(bb.rolling_queue_buff, 0, sizeof(bb.rolling_queue_buff));
  memset(bb.Flashsamplename, 0, sizeof(bb.Flashsamplename));
  memset(bb.consolemsg, 0, sizeof(bb.consolemsg));
  memset(bb.pleasewaitarray, 0, sizeof(bb.pleasewaitarray));
  memset(bb.pots_controllers, 0, sizeof(bb.pots_controllers));
  memset(bb.recorded_ccs, 0, sizeof(bb.recorded_ccs));

  memcpy(bb.notestofreq, tmparray, sizeof(bb.notestofreq));
  _sp.doclearassign();
  memset(gg.midiknobassigned, 0, sizeof(gg.midiknobassigned));
  memset(gg.arbitrary_waveforms, 0, sizeof(gg.arbitrary_waveforms));
  memset(gg.pot_assignements, 0, sizeof(gg.pot_assignements));
  memset(gg.vPots, 0, sizeof(gg.vPots));

  for (int j = 0; j < PBARS; j++) {
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
      
      pp.cc_partition[i][j] = 127;
    }
  }
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 32; j++) {
      bb.pots_controllers[i][j][0] = 0;
      bb.pots_controllers[i][j][1] = 0;
    }
    bb.recorded_ccs[i] = 0 ;
  }
  gg.fx[0] = FxBus();
  gg.fx[0].f_index = 0;
  gg.fx[1] = FxBus();
  gg.fx[1].f_index = 1;
  gg.fx[2] = FxBus();
  gg.fx[2].f_index = 2;
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
  _mx.le303filterzWet();

  _mx.le303filtercontrols();
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

  _st.unplug_notefreq_from_ampL();
  for (int i = 0; i < FXS_COUNT; i++) {
    gg.fx[i].stopdelayline();
    delayCords[i]->disconnect();
    delayCordsR[i]->disconnect();

  }
  AudioNoInterrupts();
  for (int i = 0; i < FXS_COUNT; i++) {
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
  for (int i = 0; i < ALL_BUTTONS; i++) {
    if (!((i <= 11) || (i >= 46))) {
      gg.pot_assignements[i] = i + 128 + 30;
    } else {
      gg.pot_assignements[i] = gg.ordered_pots[Padded.potsboards[i]];
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

  // lv.fidx crossfader
  //gg.midiknobassigned[10] = 69;

  // 303 pulse
  gg.midiknobassigned[23] = 13;
  gg.midiknobassigned[24] = 15;
 
  

  //gg.pot_assignements[ALL_BUTTONS-10] = 108 ;
  //gg.pot_assignements[ALL_BUTTONS-9] = 107 ;
  
  //gg.midiknobassigned[111] = 109 ;
  //98 debugcpu
  //pots_assignements are to map onboard buttons to midi notes or ccs
  //gg.pot_assignements[ALL_BUTTONS-5] = 106 ;
  gg.pot_assignements[ALL_BUTTONS-20] = 110 ;
  gg.pot_assignements[ALL_BUTTONS-21] = 109 ;
  gg.pot_assignements[ALL_BUTTONS-19] = 111 ;

  gg.pot_assignements[ALL_BUTTONS-12] = 108 ;
  gg.pot_assignements[ALL_BUTTONS-11] = 107 ;
  gg.pot_assignements[ALL_BUTTONS-10] = 106 ;

  gg.midiknobassigned[gg.alt_nav[2]] = 125 ;
  gg.midiknobassigned[gg.alt_nav[3]] = 126 ;
  gg.midiknobassigned[gg.alt_nav[0]] = 123 ;
  gg.midiknobassigned[gg.alt_nav[1]] = 124 ;



  gg.pot_assignements[ALL_BUTTONS-4] = 100 ;
  gg.pot_assignements[ALL_BUTTONS-13] = 101 ;
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
    lv.oscillator = i;
    _sn.setwavetypefromlist();
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

void fairly_often() {
  //tac_tics[0] = false;
  //set them all on a separate cycle if possible
  control_me();
  dm.UpdateSpectrum();
}

void at_a_paced_rate() {
  _tt.update_active_lines();
}

void once_in_a_while(){
  if (_mp.mp3_continue){
    refresh_mp3_player();
  }
}

void refresh_mp3_player(){
  if (!playFlac1.isPlaying() && !playMp31.isPlaying()) {  
    _mp.mp3_player_next();
    _mp.mp3_player_play();
  }
}

void loopusbHub() {

  //works without .Task() but task seems to do other things too
  myusb.Task();
  //for multi devices in hub or devices with multiple IDs
  //TODO: check notes, may double trigger
  midi1.read();
  //if (!midi1){
    midi2.read();
    //if (!midi2){
       midi3.read();
    //}
  usbMIDI.read();
  //usbmidi ??
  //}
  // needed to handle usbMIDI.read() for msgs from pc or front usb
  /*
  midiEventPacket_t rx;
  do {
    rx = usbMIDI.read();
    if (rx.header != 0) {
      uint8_t status_midi  = rx.byte1;
      uint8_t type_midi    = status_midi & 0xF0;
      uint8_t channel_midi = (status_midi & 0x0F) + 1;
      //if (status_midi == 0xF8) _sg.midi_clock_accumulator();
      if (status_midi == 0xF2){
        uint8_t songpos_midi = rx.byte2 | (rx.byte3 << 7);
        //4 seems to be pos 0 on ardour
        if (songpos_midi == 4 ) _sg.x_ = 0 ;
        //Serial.println(songpos_midi);
      } 
      switch(type_midi){
        case 0x90:
          MaNoteOn(channel_midi,rx.byte2,rx.byte3);
          //rec_test(0,rx.byte1,rx.byte2,rx.byte3);
          //song.send_to_wire(0,rx.byte1,rx.byte2,rx.byte3);
        break;

        case 0x80:
          //rec_test(1,rx.byte1,rx.byte2,rx.byte3);
          //song.send_to_wire(1,rx.byte1,rx.byte2,rx.byte3);
          _tt.MaNoteOff(channel_midi,rx.byte2,rx.byte3);
        break;

        case 0xB0:
          _tt.MaControlChange(channel_midi,rx.byte2,rx.byte3);
        break;

        default:
        break;
      }
    }
  } while (rx.header != 0);
  */
}

void control_me(){
  if (_st.noteprint)
    _st.printlanote();    
  if (MULTIPLEXED_PADS){
    _tt.check_pads();
    _tt.check_pots();
  }
  dm.evalinputs();
  dm.evalrota(); 
}

void loop() {
  //loops in millis cn occur multiple times per milli, set a tic_tacker to throttle or attach to clock
  loopusbHub();
  if (millis() % 2 == 0) {
    Tocker.dispatch_ticks();
  }
  //TODO: make one shot system instead or remove this
  if (_rd.pre_record) {
    if (millis() - lv.tocker > 500) {
      _rd.rec_looping = true ;
      _rd.pre_record = false ;
    }
  }
  if ( _rd.rec_looping && (millis() % 2 == 0)) {
    _rd.continue_looper();
  }
}

void loop_over_303(){
  for (int i = 0; i < _rg.synth_lines_active; i++) {
      _ft.pseudo303(i);
    }
}

void setuphubusb() {

  myusb.begin();

  midi1.setHandleNoteOn(_tt.MaNoteOn);
  midi1.setHandleNoteOff(_tt.MaNoteOff);
  midi1.setHandleControlChange(_tt.MaControlChange);

  midi2.setHandleNoteOn(_tt.MaNoteOn);
  midi2.setHandleNoteOff(_tt.MaNoteOff);
  midi2.setHandleControlChange(_tt.MaControlChange);

  midi3.setHandleNoteOn(_tt.MaNoteOn);
  midi3.setHandleNoteOff(_tt.MaNoteOff);
  midi3.setHandleControlChange(_tt.MaControlChange);

  usbMIDI.setHandleNoteOn(_tt.MaNoteOn);
  usbMIDI.setHandleNoteOff(_tt.MaNoteOff);
  usbMIDI.setHandleControlChange(_tt.MaControlChange);
  usbMIDI.setHandleClock(_sg.midi_clock_accumulator);
  /*
  TODO:
  void myAfterTouchPoly(byte channel, byte note, byte velocity)
  void myProgramChange(byte channel, byte program)
  void myAfterTouch(byte channel, byte pressure)
  void myPitchChange(byte channel, int pitch)
  void mySystemExclusiveChunk(const byte *data, uint16_t length, bool last)
  void mySystemExclusive(byte *data, unsigned int length)
  void myTimeCodeQuarterFrame(byte data)
  void mySongPosition(uint16_t beats)
  void mySongSelect(byte songNumber)
  void myTuneRequest()
  void myClock()
  void myStart()
  void myContinue()
  void myStop()
  void myActiveSensing()
  void mySystemReset()
  void myRealTimeSystem(byte realtimebyte)
  */
}

void unplugsynth() {

  // unplugfx();
  for (int i = 0; i < SYNTH_LINERS_COUNT*OSCS_COUNT; i++) {

    FMwavecords1[i]->disconnect();
    modulatecords1[i]->disconnect();
    stringcords1[i]->disconnect();
    MDdrumcords1[i]->disconnect();
    drumcords1[i]->disconnect();
    MDstringcords1[i]->disconnect();
    MDwavecords1[i]->disconnect();
    wavelinescords[i]->disconnect();
  }
}

void unplugfx() {

  for (int i = 0; i < PMIX_DM_SIZE; i++) {
    premixesMto[i]->disconnect();
    premixesMtoR[i]->disconnect();
  }
  for (int i = 0; i < FXCORDS_SIZE; i++) {
    fxcording[i]->disconnect();
  }
}

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
  _rg.init_synth_liners();
  _rg.init_flash_liners();
  // metrodrum1.pitchMod(0.9);
  AudioInterrupts();

  initextmems();
  // setupmemtest();
  Serial.begin(9600);

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
  Padded.begin();
  consoler.println((char *)"Setting up I/O");
  
  pinMode(MULTIPLEXER_PIN, INPUT_PULLUP);
  

  consoler.println((char *)"I/O Set !");
  consoler.println((char *)"Loading Defaults");
  Tocker.stopticker();
  setupdefaultvalues();
  _sp.Doautoassign();
  consoler.println((char *)"All Done !");
  consoler.println((char *)"starting muxer");
  consoler.refresh();

  muxer.start();
  //queue1.begin();
  AudioMemory(1200);
  AudioShield.volume(0.0);
  AudioShield.enable();
  _st.set_in_source();
  AudioShield.volume(1.0);
  _rd.playrecordsd_pathed("SOUNDSET/REC/LOOP22#L.RAW");
  Tocker.attach_24(_tt.advance_tick);
  Tocker.attach_24_bis(_tt.arp_tick);
  Tocker.attach_long(once_in_a_while);
  Tocker.attach_2(at_a_paced_rate);
  Tocker.attach_3(fairly_often);
  Tocker.attach_oscilloscope(dm.oscilloscope_loop);
  Tocker.attach_303(loop_over_303);
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
  _ft.avg_slope();
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
  _mx.le303filterzWet();
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
  _tt.stopallnotes();
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
    gg.chordson = 3;
  } else {
    gg.chordson = 1;
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
  _mx.le303filtercontrols();
  // gg.le303filterzgainz[0]
  //  gg.mixle303ffilterzVknobs[0]
}

void Filter303_Knob2_ctl(byte cc_value){
  gg.mixle303ffilterzVknobs[1] = cc_value;
  gg.le303filterzgainz[1] = cc_value ;
  _mx.le303filtercontrols();
}

void Filter303_Knob3_ctl(byte cc_value){
  gg.mixle303ffilterzVknobs[2] = cc_value;
  gg.le303filterzgainz[2] = cc_value ;
  _mx.le303filtercontrols();
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
  _ps.setbpms();
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
  gg.oscilloscope_tscale = map(cc_val,0,127, 4, 16);
}

void adjust_osc_framerate_ctl(byte cc_val) {
  gg.osc_framerate = map(cc_val,0,127, 8, 42);
}

void adjust_osc_refresher_period_ctl(byte cc_val) {
  gg.osc_refresher_period = 1 + (cc_val / 2) ; 
}

void adjust_rota_decrease_ctl(byte cc_val){
  int this_rota = dm.myEnc.read();
  dm.myEnc.write(this_rota-4);
  dm.evalrota(); 
}

void rota_increase_ctl(byte cc_val){
  int this_rota = dm.myEnc.read();
  dm.myEnc.write(this_rota+4);
  dm.evalrota() ;
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
    dm.myEnc.write(lv.retroaction * 4);
    lv.retroaction = 0;
  }
  dm.show();
  return;
}

void validate_pushed_ctl(byte cc_val){
  lv.navlevel++;
  lv.rota_true_pos = lv.sublevels[lv.navlevel];
  dm.myEnc.write(lv.sublevels[lv.navlevel] * 4);
  dm.show();
}

void adjust_waveEditor_pitch_ctl(byte cc_val) {
  _rd.pitcher = (cc_val/127.0) * 2.0; 
}

void spectro_Toggle_ctl(byte unused_cc){
  lv.showing_oscilloscope = !lv.showing_oscilloscope;
  dm.stop_spectro();
  if (lv.showing_oscilloscope) dm.start_spectro();
}

void eq_display_Toggle_ctl(byte cc_value){
  lv.showing_eq = !lv.showing_eq ;
}

void set_cutoff_period_ctl(byte cc_value){
  gg.period_303 = map(cc_value,0,127,24,96);
}


const CcCalls ctl[128] = {
    {"Disabled",nullptr},{"Volume",&Volume_ctl},{"SynthLevel",&SynthVolume_ctl},{"SDLevel",&SDPlayerVolume_ctl},{"FlashLevel",&FlashVolume_ctl},
    {"FX1 Wet",&Wet1Volume_ctl},{"FX2 Wet",&Wet2Volume_ctl},{"FX3 Wet",&Wet3Volume_ctl},{"Dry Sampler",&DrySampler_ctl},{"Dry Synth",&DrySynth_ctl},
    //10 ok
    {"Dry Audio In",&DryAudioIn_ctl},{"CutOff slp.",&Slope1_ctl},{"Reso slp.",&Slope2_ctl},{"Reso Tweak",&ResoTweak_ctl},{"Impulse length",&set_cutoff_period_ctl},
    {"CutOff Tweak",&CutOffTweak_ctl},{"Stereo On",toggle_stereo},{"Stereo Off",turn_off_stereo},{"Filter303 Lvl.",&Filter303_ctl},{"Portamento time",&set_Portamento_time_ctl},
    //20 ok
    {"Filter303 PreAmp",&FilterPreAmp_ctl},{"Synth Index",&SynthIndex_ctl},{"Syth X Lvl.",&SynthXLevel_ctl},{"Synth X Freq",&SynthXFreq_ctl},{"Chords type",&SetChords_ctl},
    {"Pans Levels",&PansLevels_ctl},{"Metronome Level",&MetroDrumLevel_ctl},{"Play Song",&PlaySong_Trigger_ctl},{"Stop Song",&StopSong_Trigger_ctl},{"Pause Song",&PauseSong_Trigger_ctl},
    //30 ok
    {"Record Midi",&RecordPattern_Trigger_ctl},{"Record CC Events",&RecordCCPatern_Trigger_ctl},{"Stop Ticking",&StopTicking_Trigger_ctl},{"Start Ticking",&StartTicking_Trigger_ctl},{"Restart Ticker",&TickFromStart_Trigger_ctl},
    {"Arpegio Type",&ArpegioType_ctl},{"Arpegio Mode",&ArpegioMode_ctl},{"Arp. Notes Count",&ArpegioNotesCount_ctl},{"Arpegio Offset",&ArpegioStartOffset_ctl},{"Arpegio Grid C.",&ArpegioGridC_ctl},
    //40 ok
    {"Arpegio Grid S",&ArpegioGridS_ctl},{"Arpegio Length",&ArpegioLength_ctl},{"SX Modulation type",&SynthXModulationType_ctl},{"Synth X Type",&SynthXtype_ctl},{"Synth X Offset",&SynthXOffset_ctl},
    {"Synth X Phase",&SynthXPhase_ctl},{"Analog Toggle",&AnalogTouch_Toggle_ctl},{"LFO X Level",&LFOXLevel_ctl},{"LFO X Type",&LFOXType_ctl},{"LFO X Freq",&LFOXFreq_ctl},
    //50 ok
    {"LFO X Phase",&LFOXPhase_ctl},{"LFO X Offset",&LFOXOffset_ctl},{"LFO X Sync",&LFOXLSync_Toggle_ctl},{"ADSR Atk. Delay",&AdsrAtckDelay_ctl},{"ADSR Attack",&AdsrAttack_ctl},
    {"ADSR Hold",&AdsrHold_ctl},{"ADSR Decay",&AdsrDecay_ctl},{"ADSR Sustain",&AdsrSustain_ctl},{"ADSR Release",&AdsrRelease_ctl},{"Filter303 Knob1",&Filter303_Knob1_ctl},
    //60 ok
    {"Filter303 Knob2",&Filter303_Knob2_ctl},{"Filter303 Knob3",&Filter303_Knob3_ctl},{"FX Bus select",&FXBusSelector_ctl},{"Chorus Voices",&ChorusVoices_ctl},{"BiQuad Stage",&BiQuadStage_ctl},
    {"BiQuad Freq.",&BiQuadFreq_ctl},{"BiQuad Slope",&BiQuadSlope_ctl},{"BiQuad Gain",&BiQuadGain_ctl},{"BQuad Type",&BiQuadType_ctl},{"Lfo on Ffilter",&LFOonFilter_ctl},
    //70 ok
    {"Ffilter CutOff",&FFilter_Cutoff_Knob1_ctl},{"Ffilter Resonance",&FFilter_Reso_Knob2_ctl},{"Ffilter Octave",&FFilter_Oct_Knob3_ctl},{"Ffilter LowPass",&FFilter_LowPass_Knob4_ctl},{"Ffilter BandPass",&FFilter_BandPass_Knob5_ctl},
    {"Ffilter HighPass",&FFilter_HighPass_Knob6_ctl},{"Granular Grains",&GranularGrains_Knob1_ctl},{"Granular Speed",&GranularSpeed_Knob2_ctl},{"Granular Freeze",&GranularFreeze_Toggle_ctl},{"Granular Shift",&GranularShifting_Toggle_ctl},
    //90 ok
    {"Reverb Size",&ReverbSize_ctl},{"BitCrusher Samples",&BitCrusherSamples_ctl},{"BitCrusher Bits",&BitCrusherBits_ctl},{"Flanger Offset",&FlangerOffset_Knob1_ctl},{"Flanger Depth",&FlangerDepth_Knob2_ctl},
    {"Flanger Delay",&FlangerDelay_Knob3_ctl},{"Delay Time sel.",&DelayTimeSelection_Knob1_ctl},{"Delay Multiplier",&DelayTimeMultiplier_Knob2_ctl},{"Delay Feedback",&DelayFeedback_Knob3_ctl},{"Audio In Volume",&AudioInVolume_ctl},
    //100ok
    {"FREE",nullptr},{"Set BPMs",&SetBPMs_ctl},{"Save New Pattern",&SaveToNewPattern_Trigger_ctl},{"Load First Pattern",&LoadFirstPattern_Trigger_ctl},{"Record Audio",&RecordAudio_Trigger_ctl},
    {"Play Record",&PlayLoadedAudio_Trigger_ctl},{"Stop Recording",&StopRecording_Trigger_ctl},{"Load First Preset",&LoadFirstPreset_Toggle_ctl},{"Arb[] MaxF",&ArbitraryMaxF_ctl},{"Merge Patterns",&MergeSynthPatterns_Trigger_ctl},
    //120 ok
    {"Flash Line1 Level",&FlashLineVolume_Knob1_ctl},{"Flash Line2 Level",&FlashLineVolume_Knob2_ctl},{"Flash Line3 Level",&FlashLineVolume_Knob3_ctl},{"Flash Line4 Level",&FlashLineVolume_Knob4_ctl},{"Flash Line5 Level",&FlashLineVolume_Knob5_ctl},
    {"Flash Line6 Level",&FlashLineVolume_Knob6_ctl},{"Flash Line7 Level",&FlashLineVolume_Knob7_ctl},{"Flash Line8 Level",&FlashLineVolume_Knob8_ctl},{"Flash Line9 Level",&FlashLineVolume_Knob9_ctl},{"Flash Line10 Level",&FlashLineVolume_Knob10_ctl},
    //130 ok
    {"Flash Line11 Level",&FlashLineVolume_Knob11_ctl},{"Flash Line12 Level",&FlashLineVolume_Knob12_ctl},{"Flash Line13 Level",&FlashLineVolume_Knob13_ctl},{"Flash Line14 Level",&FlashLineVolume_Knob14_ctl},{"Flash Line15 Level",&FlashLineVolume_Knob15_ctl},
    {"Flash Line16 Level",&FlashLineVolume_Knob16_ctl},{"Show oscilloscope",&spectro_Toggle_ctl},{"Show EQ Bars",&eq_display_Toggle_ctl},{"USB In Volume",&USB_In_Volume_ctl},{"Fps oscilloscope",&adjust_osc_framerate_ctl},
    //140 ok
    {"Time oscilloscope",&adjust_osc_timee_ctl},{"refresh OscScope",&adjust_osc_refresher_period_ctl},{"Wav Editor Pitch",&adjust_waveEditor_pitch_ctl},{"Rota Nav +",&rota_increase_ctl}, {"Rota Nav -",&adjust_rota_decrease_ctl},      
    {"Validate Nav",&validate_pushed_ctl},{"Cancel Nav",&cancel_pushed_ctl},{"Pitch Attack",&set_Portamento_height_ctl} 
};
