

byte synth_start_tpos[SYNTH_LINERS_COUNT];

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

void check_pads() {
  PadResult padder = Pads.padloop();
  paddered = Pads.arranged_buttons[padder.pad_result[0]][padder.pad_result[1]];
  byte chan_received = gg.but_channel[11 + paddered];
  int cc_note_num = gg.pot_assignements[11 + paddered] - 128;
  //if multiplexed condition || 36 is the cancel button when in multiplexed mode, should not trigger another note or control.
  if ((padder.pad_result[2] == 1) && (paddered != 36)) {
    if (cc_note_num < 0) {
      _tt.MaControlChange(chan_received,(byte)gg.pot_assignements[11 + paddered], 64);
    }
    else {
      _tt.MaNoteOn((MidiEventer){chan_received, (byte)cc_note_num, gg.but_velocity[11 + paddered]});
    }
  }
  else if ((padder.pad_result[2] == 0) && (paddered != 36) && (cc_note_num > 0)) {
    _tt.MaNoteOff(chan_received, cc_note_num, 0);
  }
}

void init_synth_liners(){
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    synth_lines[i] = new SynthLiner(i);
  }
}

void init_flash_liners(){
  for (int i = 0; i < FLASH_LINERS_COUNT; i++) {
    flash_lines[i] = new FlashLiner(i);
  }
}

byte get_free_synth(byte note) {
  for (byte i = 0; i < SYNTH_LINERS_COUNT; i++) {
    if (!enveloppesL[i]->isActive()) {
      return i;
    }
  }
  return SYNTH_LINERS_COUNT;
}

bool linerhasevents(byte liner) {
  for (int i = 0; i < PBARS; i++) {
    if (pp.synth_partition[liner][i].note != 0) {
      return 1;
    }
  }
  return 0;
}

void setchordnotes(byte absolutenote, byte lachord) {
  byte relativenote = ((absolutenote + 12) % 12);
  for (int i = 0; i < 3; i++) {
    _tt.chordnotes[i] = leschords[lachord][relativenote][i];
  }
}

void setchordnotesOff(byte absolutenote, byte lachord) {
  byte relativenote = ((absolutenote + 12) % 12);
  for (int i = 0; i < 3; i++) {
    _tt.chordnotesoff[i] = leschords[lachord][relativenote][i];
  }
}

void stopallnotes() {
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    // stoplengthmesure(i);
    if (synth_lines[i]->note != 0) {
      _tt.MaNoteOff(gg.synthmidichannel, synth_lines[i]->note, 0);
    }
  }
}

void dotapaverage() {
  int tottaptime = 0;
  for (int i = 0; i < _tt.numberoftaps; i++) {
    tottaptime += (_tt.tapstime[i] - _tt.starttaptime);
  }
  _tt.tapaverage = tottaptime / _tt.numberoftaps;
  gg.millitickinterval = round(_tt.tapaverage / 10.0);
  _st.setbpms();
}

void allarpegeoffs() {
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    _pt.calledarpegenote[i][0] = 0;
    _pt.calledarpegenote[i][1] = 0;
    for (int j = 0; j < SYNTH_LINERS_COUNT; j++) {
      _pt.playingarpegiator[i][j] = 0;
      _pt.arpegnoteoffin[i][j] = 0;
    }
    _pt.arpegiatingNote[i] = 0;
  }
  stopallnotes();
}

byte incrementarpegiatingNote(byte lanote) {
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    if (_pt.arpegiatingNote[i] == 0) {
      _pt.arpegiatingNote[i] = lanote;
      return i;
    }
  }
  return SYNTH_LINERS_COUNT;
}

bool decrementarpegiatingNote() {
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    if (_pt.arpegiatingNote[i] != 0) {
      _pt.arpegiatingNote[i] = 0;
      return 1;
    }
  }
  return 0;
}

void initiatearpegesynthliner(byte larpegeline, byte data1, byte data2) {
  byte free_line = get_free_synth(data1);
  if (free_line < SYNTH_LINERS_COUNT) {
    for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
      if (data1 == _pt.calledarpegenote[i][0]) {
        _pt.arpegnoteoffin[i][free_line] = gg.arpeglengh + 1;
        _pt.playingarpegiator[i][free_line] = data1;
      }
    }
    _pt.arpegnoteoffin[larpegeline][free_line] = gg.arpeglengh + 1;
    _pt.playingarpegiator[larpegeline][free_line] = data1;
    if (lv.patrecord) {
      recordmidinotes(free_line, gg.synthmidichannel, data1, data2);
    }
    synth_lines[free_line]->liner_on(data1, data2);
  }
}

byte get_free_sampler(byte note) {
  for (byte i = 0; i < FLASH_LINERS_COUNT; i++) {
    if (!(FlashSampler[i]->isPlaying() )) {
      return i;
    } 
  }
  return 0;
}

void update_active_lines() {
  for (int i = 0; i < _rg.synth_lines_active; i++) {
    _ft.pseudo303(i);
    _rg.active_synths[i]->update_line();
  }
}

void initiateasynthliner(byte data1, byte data2) {
  byte free_line = get_free_synth(data1);
  if (free_line < SYNTH_LINERS_COUNT) {
    if (lv.patrecord) {
      recordmidinotes(free_line, gg.synthmidichannel, data1, data2);
    }
    //printnoteon(0,data1,data2);
    synth_lines[free_line]->liner_on(data1, data2);
  }
}

void initiateasamplerliner(byte data1, byte data2) {
  byte free_line = get_free_sampler(data1);
  if (free_line < FLASH_LINERS_COUNT) {
    if (lv.patrecord) {
      recordmidinotes(free_line, gg.samplermidichannel, data1, data2);
    }

    flash_lines[free_line]->liner_on(data1, data2);
  }
}

void MaProgramchange(byte channel, byte data1) {
  if (_tt.debugmidion) {
    _tt.debugmidi((char *)"ProgramChange", (MidiEventer){channel, data1, 0});
  }
  int leprogchanged = (int)(data1);
  if (leprogchanged < _ps.catalog->files_counter) {
    _ps.catalog->displayable_offset = leprogchanged ;
    _ps.catalog->refresh_files_names();
    _ps.read_preset();
  }
}

void synth_used_this_note(byte data1) {
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    if (data1 == synth_lines[i]->note) {
      synth_lines[i]->liner_off();
      if (lv.patrecord) 
        record_synth_notesOff(i, gg.synthmidichannel, data1, 0);
    }
  }
}

void flash_used_this_note(byte data1) {
  for (int i = 0; i < FLASH_LINERS_COUNT; i++) {
    if (data1 == flash_lines[i]->note) {
      flash_lines[i]->liner_off();
    }
  }
}

void shutlineroff(byte chan,byte data1) {

    if ((chan == gg.synthmidichannel) or ( gg.synthmidichannel == 0)) 
      synth_used_this_note(data1);
      
    if ((chan == gg.samplermidichannel) or ( gg.samplermidichannel == 0)) 
      flash_used_this_note(data1);
}

void decrementgamme(byte larpegeline) {

  if (_pt.tickgamme[larpegeline] > (int)(gg.arpegstartoffset / 6)) {
    _pt.tickgamme[larpegeline]--;
  } else {
    _pt.tickgamme[larpegeline] = gg.arpegnumofnotes - 1;
  }
}

void randomdirtest(byte larpegeline) {
  byte lerandom = (byte)random(0, 101);
  if (lerandom > 50) {
    _pt.tripletdirection[larpegeline] = !_pt.tripletdirection[larpegeline];
    // ticklagamme(larpegeline);
  }
  if (gg.arpegmode == 4) {
    randomgammedirtest(larpegeline);
  }
}

void randomgammedirtest(byte larpegeline) {
  byte lerandom = (byte)random(0, 101);
  if (lerandom > 50) {

    decrementgamme(larpegeline);
  } else {
    ticklagamme(larpegeline);
  }
}

void tickarpegedown(byte larpegeline) {
  if (_pt.ticktriplet[larpegeline] > 0) {
    _pt.ticktriplet[larpegeline]--;
  } else {
    _pt.ticktriplet[larpegeline] = 2;
    if (gg.arpegmode == 1 || gg.arpegmode == 5 || gg.arpegmode == 4) {
      decrementgamme(larpegeline);
    }
    if (gg.arpegmode == 3) {
      ticklagamme(larpegeline);
      _pt.tripletdirection[larpegeline] = 1;
      _pt.ticktriplet[larpegeline] = 0;
    }
    if (gg.arpegmode == 2) {
      _pt.tripletdirection[larpegeline] = 1;
      _pt.ticktriplet[larpegeline] = 0;
    }
    if (gg.arpegmode == 5) {
      _pt.tripletdirection[larpegeline] = 1;
      _pt.ticktriplet[larpegeline] = 0;
    }
    if (gg.arpegmode == 6) {
      _pt.tripletdirection[larpegeline] = 1;
      _pt.ticktriplet[larpegeline] = 0;
    }
    if (gg.arpegmode == 4) {
      randomdirtest(larpegeline);
      // randomgammedirtest(larpegeline);
    }
    if (gg.arpegmode == 7) {
      randomdirtest(larpegeline);
      randomgammedirtest(larpegeline);
    }
  }
}

void tickarpege(byte larpegeline) {
  _pt.ticktriplet[larpegeline]++;
  if (_pt.ticktriplet[larpegeline] > 2) {
    _pt.ticktriplet[larpegeline] = 0;
    if (gg.arpegmode == 0 || gg.arpegmode == 2 || gg.arpegmode == 3 || gg.arpegmode == 4) {
      ticklagamme(larpegeline);
    }
    if (gg.arpegmode == 3) {
      _pt.tripletdirection[larpegeline] = 0;

      _pt.ticktriplet[larpegeline] = 2;
    }
    if (gg.arpegmode == 2) {
      _pt.tripletdirection[larpegeline] = 0;

      _pt.ticktriplet[larpegeline] = 2;
    }
    if (gg.arpegmode == 5) {
      _pt.tripletdirection[larpegeline] = 0;

      _pt.ticktriplet[larpegeline] = 2;
    }
    if (gg.arpegmode == 6) {
      _pt.tripletdirection[larpegeline] = 0;

      _pt.ticktriplet[larpegeline] = 2;
      decrementgamme(larpegeline);
    }
    if (gg.arpegmode == 4) {
      randomdirtest(larpegeline);
      //
    }
    if (gg.arpegmode == 7) {
      randomdirtest(larpegeline);
      randomgammedirtest(larpegeline);
    }
  }
}

void synth_arpegiator_ticker(byte data1, byte data2, byte larpegeline) {
  // for (int i = 0 ; i < SYNTH_LINERS_COUNT ; i++ ) {
  // if (_pt.arpegiatingNote[larpegeline] == data1 ) {
  // for (int i = 0 ; i < SYNTH_LINERS_COUNT ; i++ ) {
  _pt.calledarpegenote[larpegeline][1] = data2;
  _pt.calledarpegenote[larpegeline][0] = 0;
  // }
  if (gg.arpegstartoffset > 0) {
    _pt.tickgamme[larpegeline] = (byte)((int)(gg.arpegstartoffset / 3.0));
    _pt.ticktriplet[larpegeline] = (byte)((int)(gg.arpegstartoffset % 3));
  } else {
    _pt.tickgamme[larpegeline] = 0;
    _pt.ticktriplet[larpegeline] = 0;
  }
  _pt.arpegemptyticks[larpegeline] = gg.arpeggridS;
  _pt.arpegnotestick[larpegeline] = 0;

  // if (gg.arpegstartoffset) {
  //  for (int i = 0 ; i < gg.arpegstartoffset ; i++ ) {
  //  tickarpege(larpegeline) ;
  //  }
  // }
  if (gg.arpegmode == 1 || gg.arpegmode == 5 || gg.arpegmode == 6) {
    _pt.tickgamme[larpegeline] = 6;
  }

  if (gg.arpegmode == 0 || gg.arpegmode == 3 || gg.arpegmode == 5) {
    _pt.ticktriplet[larpegeline] = 0;
  }
  if (gg.arpegmode == 1 || gg.arpegmode == 2 || gg.arpegmode == 6) {
    _pt.tripletdirection[larpegeline] = 0;
    _pt.ticktriplet[larpegeline] = 2;
  }

  // printarparams();
}
// modes 0 up , 1 down, 2 up-down , 3 down-up, 4 random
void arpegioticker(byte larpegeline) {
  switch ((int)_pt.tripletdirection[larpegeline]) {
  case 0:
    // up
    tickarpegedown(larpegeline);
    break;
  case 1:
    // down
    tickarpege(larpegeline);
    break;

  default:
    break;
  }
}

void ticklatriplet(byte larpegeline) {
  _pt.ticktriplet[larpegeline]++;
  if (_pt.ticktriplet[larpegeline] > 2) {
    _pt.ticktriplet[larpegeline] = 0;
    ticklagamme(larpegeline);
  }
}

void ticklagamme(byte larpegeline) {
  if (gg.arpegmode == 4) {
    randomdirtest(larpegeline);
  }
  _pt.tickgamme[larpegeline]++;
  if (_pt.tickgamme[larpegeline] > gg.arpegnumofnotes - 1) {
    _pt.tickgamme[larpegeline] = int(gg.arpegstartoffset / 6);
  }
}

void incrementcs(byte larpegeline) {
  if (_pt.arpegnotestick[larpegeline] < gg.arpeggridC) {
    _pt.arpegnotestick[larpegeline]++;
  } else {
    _pt.arpegemptyticks[larpegeline] = gg.arpeggridS;
    _pt.arpegnotestick[larpegeline] = 0;
  }
}

void decrementcrementns(byte larpegeline) {
  if (_pt.arpegemptyticks[larpegeline] > 0) {
    _pt.arpegemptyticks[larpegeline]--;
  }
}

void playarpegenote(byte larpegeline) {
  if (_pt.arpegemptyticks[larpegeline] > 0) {
    decrementcrementns(larpegeline);
    return;
  }
  incrementcs(larpegeline);
  byte relativenote;
  byte realnotetoplay;
  relativenote = _tt.all_arpegios[gg.arpegiatortype][_pt.tickgamme[larpegeline]][_pt.ticktriplet[larpegeline]];
  // realnotetoplay = (byte)(octave*12 + relativenote) ;
  realnotetoplay = (byte)(_pt.arpegiatingNote[larpegeline] + relativenote);
  if (gg.arpegmode == 4) {
    arpegioticker(larpegeline);
  }
  _pt.calledarpegenote[larpegeline][0] = realnotetoplay;
  initiatearpegesynthliner(larpegeline, realnotetoplay, _pt.calledarpegenote[larpegeline][1]);
  // initiateasynthliner(realnotetoplay, _pt.calledarpegenote[larpegeline][1] );
  if (gg.arpegmode != 4) {
    arpegioticker(larpegeline);
  }
}



bool testarpege(byte lanote) {
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    if (_pt.arpegiatingNote[i] == lanote) {
      _pt.arpegiatingNote[i] = 0;
      return 1;
    }
  }
  return 0;
}

bool retestarpege() {
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    if (_pt.arpegiatingNote[i] != 0) {
      return 1;
    }
  }
  return 0;
}

bool isalreadysamenoteinpat(byte lenote) {
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    if (lenote == pp.synth_partition[i][lv.tickposition].note) {
      return 1;
    }
  }
  return 0;
}

int tick_for_that(int tick){
  tick -= 1 ;
  if (tick < 0 ){
    tick = 31 ;
  }
  return tick ;
}

void recordmidinotes(int liner, byte channel, byte lenote, byte velocity) {
  int pos = tick_for_that(lv.tickposition);
  synth_start_tpos[liner] = pos;
  pp.track_cells[Synth][lv.tickposition] = 1;
  pp.synth_partition[liner][pos] = {channel, lenote, velocity};
}

bool isalreadysameoffinpat(byte lanotee, byte modeselect) {
  if (modeselect == 0) {
    for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
      if (lanotee == pp.synth_off_pat[i][lv.tickposition + 1].note) {
        return 1;
      }
    }
  }
  if (modeselect == 1) {
    for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
      if (lanotee == pp.synth_off_pat[i][0].note) {
        return 1;
      }
    }
  }
  if (modeselect == 2) {
    for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
      if (lanotee == pp.synth_off_pat[i][lv.tickposition].note) {
        return 1;
      }
    }
  }
  return 0;
}

void record_synth_notesOff(int liner, byte channel, byte lenote, byte velocity) {
  int pos = tick_for_that(lv.tickposition);
  if (synth_start_tpos[liner] != pos) {
    pp.synth_off_pat[liner][pos] = {channel, lenote, 0};

  } else {
    if (pos == PBARS - 1) {
      pp.synth_off_pat[liner][0] = {channel, lenote, 0};
    } else {
      pp.synth_off_pat[liner][pos + 1] = {channel, lenote, 0};
    }
  }
}

bool isalreadysameSamplerinpat(byte lenote,int tick) {
  for (int i = 0; i < FLASH_LINERS_COUNT; i++) {
    if (lenote == pp.sampler_partition[i][tick].note) {
      return 1;
    }
  }
  return 0;
}

void recordmidinotes2(int liner, byte channel, byte lenote, byte velocity) {
  int pos = tick_for_that(lv.tickposition);
  if (!isalreadysameSamplerinpat(lenote,pos)) {
    pp.track_cells[Flash][pos] = 1;
    pp.sampler_partition[liner][pos] = {channel,lenote,velocity};
  }
}

void deactivatelesccsfrompos(int lapos, byte lanote) {
  for (int i = lapos + 1; i < PBARS; i++) {
    pp.cc_partition[int(lanote)][i] = 127;
  }
}



bool testforaNoteOninbetween(int linei, int lapos0, int lapos2, byte lanotef) {
  for (int i = lapos0; i < lapos2; i++) {
    if (pp.synth_partition[linei][i].note == lanotef) {
      return 1;
    }
  }
  return 0;
}

int anothernOffisonafter(int linei, byte lanotee, int lapos) {
  for (int i = lapos; i < PBARS - 1; i++) {
    if (pp.synth_off_pat[linei][i + 1].note == lanotee) {
      // 0 is liner
      return i + 1;
    }
  }
  return PBARS;
}

int getnextposofevent1Off_synth(int linei, byte lanote, int fromi) {
  for (int i = fromi + 1; i < PBARS; i++) {
    if (pp.synth_off_pat[linei][i].note == lanote) {
      return i;
    }
  }
  return (fromi + 1);
}

int getnextposofevent1Off_sampler(int linei, byte lanote, int fromi) {
  for (int i = fromi + 1; i < PBARS; i++) {
    if (pp.sampler_off_pat[i].note == lanote) {
      return i;
    }
  }
  return (fromi + 1);
}

void tweakfreqlive(int liner, float tune) {
  //AudioNoInterrupts();
  for (int j = 0; j < OSCS_COUNT; j++) {
    waveforms1[liner + (j * SYNTH_LINERS_COUNT)]->frequency(tune * gg.wavesfreqs[j]);
    FMwaveforms1[liner + (j * SYNTH_LINERS_COUNT)]->frequency(tune * gg.wavesfreqs[j]);
    drums1[liner + (j * SYNTH_LINERS_COUNT)]->frequency(tune * gg.wavesfreqs[j]);
  }
  //AudioInterrupts();
}



void computelenghtmesureoffline_synth() {
  for (int linei = 0; linei < SYNTH_LINERS_COUNT; linei++) {
    for (int i = 0; i < PBARS; i++) {
      if (pp.synth_partition[linei][i].note != 0) {
        int laposof = getnextposofevent1Off_synth(linei, pp.synth_partition[linei][i].note, i);
        if (laposof < PBARS - 1) {
          pp.synth_notes_length[linei][i] = (laposof - i) * 4;
        } else {
          pp.synth_notes_length[linei][i] = (PBARS - i) * 4;
        }
      }
    }
  }
}

void computelenghtmesureoffline_sampler() {
  for (int linei = 0; linei < FLASH_LINERS_COUNT; linei++) {
    for (int i = 0; i < PBARS; i++) {
      if (pp.sampler_partition[linei][i].note != 0) {
        int laposof = getnextposofevent1Off_sampler(linei, pp.sampler_partition[linei][i].note, i);
        if (laposof < PBARS - 1) {
          pp.flash_notes_length[linei][i] = (laposof - i) * 4;
        } else {
          pp.flash_notes_length[linei][i] = (PBARS - i) * 4;
        }
      }
    }
  }
}

void closeallenvelopes() {
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    synth_lines[i]->liner_off();
    /*
    enveloppesL[i]->noteOff();
    enveloppesL[i]->hold(0);
    synth_lines[i]->note = 0;
    synth_lines[i]->activated = 0;
    */
  }
}

void moncontrollercc(byte channel, byte control, byte value) {
  if (value < 128) {
    if (gg.midiknobassigned[control] != 0 && !_st.freezemidicc) {
      if (gg.SendMidiOut) {
        //uint8_t statusByte = static_cast<uint8_t>(0xB0 | channel);
        //MidiUSB.sendMIDI({0x0B, statusByte, control, value});
        //MidiUSB.flush();
        usbMIDI.sendControlChange(control,value,channel);
        usbMIDI.send_now();
        
      }
      ctl[gg.midiknobassigned[control]].tweaker(value);
      // AudioInterrupts();
    }
  }
}

void cc_edgecases(byte control, byte value){

  //inside Knobs Setter panel
  if (_ka.knobsetting){
    _ka.learn_midi(control);
  }
  //set this control == 19 optional in settings 
  
  //inside pattern mode
  if (_pe.paterning && control == 19) {
    if (_pe.track_type == 0) {
      pp.synth_partition[lv.sublevels[2]][lv.sublevels[5]].velocity = value; 
    } else if (_pe.track_type == 1) {
      pp.sampler_partition[lv.sublevels[2]][lv.sublevels[5]].velocity = value; 
    }
  }

  if (_st.setting_on_board) {
    if (lv.navlevel == 2) {
      
      if (control == 19)  {
        gg.but_channel[lv.sublevels[2]] = (gg.but_channel[lv.sublevels[2]] + 1) % 17;
      }
      if (control == 28) {
        gg.but_channel[lv.sublevels[2]] = (gg.but_channel[lv.sublevels[2]] + 16) % 17;
      }
    }
    if (lv.navlevel == 3) {
      //should be another or check above
      if (control == 19) {
        gg.but_velocity[lv.sublevels[2]] = value;
      }
    }
  }

  //inside waveform tracer
  if (lv.waveforming) {
    call_wf_tracer(control,value);
  }

  if (!lv.songplaying && !_tt.noCCrecordlist(control) && !_tt.debugmidion) {
    dm.show();
  }
}

void notes_edgecases(byte note, byte velo){
  // control is (byte)gg.pot_assignements[11 + paddered]
  //inside sample assigner
  if (_st.setting_on_board && (lv.navlevel == 2)) helper_onbard();
  
  if (_sp.assigning_sample_to_note) dm.returntonav(3,127,note);
    //sets the navigation wheel to the captured note position for easier selection when assigning Flashsamples
}

void helper_onbard(){
  if (Pads.potsboards[lv.sublevels[2]] >= 0) {
    gg.muxed_channels[Pads.potsboards[lv.sublevels[2]]] = gg.but_channel[lv.sublevels[2]];
  }
  if ((paddered != 26) && (paddered != 17)) {
    dm.returntonav(lv.navlevel,lv.navrange,paddered + 11);
  }
}
