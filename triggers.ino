


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
  PadResult padder = Padded.padloop();
  lv.paddered = Padded.arranged_buttons[padder.pad_result[0]][padder.pad_result[1]];
  byte chan_received = gg.but_channel[11 + lv.paddered];
  int cc_note_num = gg.pot_assignements[11 + lv.paddered] - 128;
  //if multiplexed condition || 36 is the cancel button when in multiplexed mode, should not trigger another note or control.
  if ((padder.pad_result[2] == 1) && (lv.paddered != 36)) {
    if (cc_note_num < 0) {
      _tt.MaControlChange(chan_received,(byte)gg.pot_assignements[11 + lv.paddered], 64);
    }
    else {
      _tt.MaNoteOn((MidiEventer){chan_received, (byte)cc_note_num, gg.but_velocity[11 + lv.paddered]});
    }
  }
  else if ((padder.pad_result[2] == 0) && (lv.paddered != 36) && (cc_note_num > 0)) {
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




void update_active_lines() {
  for (int i = 0; i < _rg.synth_lines_active; i++) {
    _ft.pseudo303(i);
    _rg.active_synths[i]->update_line();
  }
}



