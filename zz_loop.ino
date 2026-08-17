



void check_pots() {
  int c_change = Muxer.read_val(lv.muxer_ch_active);
  if (c_change >= 0 && lv.muxer_ch_active !=9) {
    _tt.MaControlChange(gg.muxed_channels[lv.muxer_ch_active], (byte)gg.ordered_pots[lv.muxer_ch_active], (byte)((c_change / 1024.0) * 127));
  }
  lv.muxer_ch_active = (lv.muxer_ch_active+1)%15; // mux_ch 16 is broken (pot in 9 as well)
}

void printit() {

  Serial.print(" lv.navrange: ");
  Serial.print(lv.navrange);
  Serial.print(" lv.navlevel: ");
  Serial.print(lv.navlevel);
  Serial.print(" sublevel[");
  Serial.print(lv.navlevel);
  Serial.print("]:");
  Serial.println(lv.sublevels[lv.navlevel]);
  Serial.println(" ");
  Serial.print(" s0 = ");
  Serial.print(lv.sublevels[0]);
  Serial.print(" s1 = ");
  Serial.print(lv.sublevels[1]);
  Serial.print(" s2 = ");
  Serial.print(lv.sublevels[2]);
  Serial.print(" s3 = ");
  Serial.print(lv.sublevels[3]);
  Serial.print(" s4 = ");
  Serial.print(lv.sublevels[4]);
  Serial.print(" s5 = ");
  Serial.println(lv.sublevels[5]);

}

void fairly_often() {
  //set them all on a separate cycle if possible
  control_me();
  dm.UpdateSpectrum();
  Tocker.dispatch_ticks();
}

void at_a_paced_rate() {
  update_active_lines();

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
    check_pads();
    check_pots();
  }
  evalinputs();
  evalrota(); 
}

void loop() {

  loopusbHub();
  if (millis() % 3 == 0) {
   fairly_often();
  } else if (millis() % gg.osc_refresher_period == 0) {
    dm.oscilloscope_loop();
  }

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


