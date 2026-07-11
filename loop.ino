
int pad_result;

void allpasslevels() {
  mix303L1.gain(0, 1);
  mix303L1.gain(1, 0);
  mix303L1.gain(2, 0);
}

void pseudo303() {
  float glidefactorCmode[synth_liners_count];
  for (int i = 0; i < synth_liners_count; i++) {
    if (glidemode > 0 && dogliding[i]) {
      glidefactorCmode[i] =  (millis() - leglideposition[i]) /  (glidemode * millitickinterval * 1.0);
      //notefrequency = (glidefactorCmode[i]) * leglidershiftCmode[i] + notestofreq[lapreviousnotewCmode[i]][1];
      notefrequency = glidefactorCmode[i] * freq_difference + notestofreq[note_before][1];
      tweakfreqlive(i, notefrequency);
      if ((int)(millis() - leglideposition[i]) > glidemode * millitickinterval ) {
        stopglidenoteChords(i);
      }
    }
    if (tb303[i] == 1) {
      ladiff1 = ( (millis()-pulsers[i][0]) / (1.0*pulsers[i][1]));
      ladiff2 = ladiff1 ;
      letbfreq = le303filterzrange + 50 - (le303filterzrange * (fxslopedown2(slope1, ladiff1)));
      if (millis()-pulsers[i][0]>pulsers[i][1]){
        tb303[i] = 0;
        letbfreq = 50 ;
        ladiff2 = 0 ;
      }
      les303filterz[i]->frequency(letbfreq);

      if (ladiff2 <= 1) {
        les303filterz[i]->resonance(0.1 + (le303filterzreso) * (fxslopedown2(slope2, ladiff2)));
      }
    }
  }
}

void check_pads() {
    PadResult pad_result = Pads.padloop();
  int paddered = arranged_buttons[pad_result.pad_result[0]][pad_result.pad_result[1]];
  cc_note_num = pot_assignements[11 + paddered] - 128;
  // TODO: if multiplexed condition || 36 is the cancel button when in multiplexed mode, should not trigger another note or control.
  if ((pad_result.pad_result[2] == 1) && (paddered != 36)) {
    //inside pattern mode
    if (sublevels[0] == 4 && navlevel >=5 && sublevels[1] == 0) {
      if (paddered == 17) {

        synth_partition[sublevels[2]][sublevels[5]][2] = (int)((Muxer.get_raw(6)/1024.0)*127);
        dm.lemenuroot();
      }
    }
    //inside sample assigner
    if ((sublevels[0] == 7) && (sublevels[1] == 2) && (sublevels[2] == 1) && (navlevel == 3)) {
      if (cc_note_num > 0) {
        //sets the navigation wheel to the captured note position for easier selection when assigning Flashsamples
        returntonav(3,127,cc_note_num);
      }
    }
    //inside Onboards Panel
    if ((sublevels[0] == 5) && (sublevels[1] == 11) && (navlevel == 2)) {

      if ((paddered == 17) && (but_channel[sublevels[2]] < 15)) {
        but_channel[sublevels[2]] += 1;
      }
      if ((paddered == 26) && (but_channel[sublevels[2]] > 0)) {
        but_channel[sublevels[2]] -= 1;
      }
      if (potsboards[sublevels[2]] >= 0) {
        muxed_channels[potsboards[sublevels[2]]] = but_channel[sublevels[2]];
      }
      if ((paddered != 26) && (paddered != 17)) {
        // set selection to last pad pushed
        //use returntonav
        sublevels[2] = paddered + 11;
        vraipos = sublevels[2];
        myEnc.write(4 * sublevels[2]);
      }
      call_st_onboardPanel();
    }
    //inside Set Knobs level 2: learn midi
    else if (sublevels[0] == 5 && sublevels[1] == 15 && navlevel == _ka.relative_navlevel +1 && cc_note_num <= 0){
      _ka.learn_midi((byte)pot_assignements[11 + paddered]);
    }
    //inside waveform tracer
    else if ((sublevels[0] == 8) && (sublevels[1] == 4) && (navlevel == 2)) {
      if (cc_note_num == trace_wave_cc) {
        trace_waveform = !trace_waveform;
      }
    } else {
      if (cc_note_num <= 0) {MaControlChange(but_channel[11 + paddered],(byte)pot_assignements[11 + paddered], 64);
      }
      //normal note pad
      else {
        MaNoteOn(but_channel[11 + paddered], cc_note_num, but_velocity[11 + paddered]);
      }
    }
  } else if ((pad_result.pad_result[2] == 0) && (paddered != 36) &&
             (cc_note_num > 0)) {
    MaNoteOff(but_channel[11 + paddered], cc_note_num, 0);
  }
}
void check_pots() {
  //checking one pot per loop as it is fast
     c_change = Muxer.read_val(itr);
    if (c_change > 0) {
        //ordered_pots[9] broken, ignoring
      if (itr < 15 && itr !=9) {
        if ((sublevels[0] == 5) && (sublevels[1] == 11) && (itr == 6)) {
          but_velocity[sublevels[2]] = (byte)((c_change / 1024.0) * 127);
          call_st_onboardPanel();
        }
         else {
          MaControlChange(muxed_channels[itr], (byte)ordered_pots[itr], (byte)((c_change / 1024.0) * 127));
        }
      }
    }
    itr++;
    if (itr >= 16) {
      itr = 0;
    }
}

void printit() {

  Serial.print(" navrange: ");
  Serial.print(navrange);
  Serial.print(" navlevel: ");
  Serial.print(navlevel);
  Serial.print(" sublevel[");
  Serial.print(navlevel);
  Serial.print("]:");
  Serial.println(sublevels[navlevel]);
  Serial.println(" ");
  Serial.print(" s0 = ");
  Serial.print(sublevels[0]);
  Serial.print(" s1 = ");
  Serial.print(sublevels[1]);
  Serial.print(" s2 = ");
  Serial.print(sublevels[2]);
  Serial.print(" s3 = ");
  Serial.print(sublevels[3]);
  Serial.print(" s4 = ");
  Serial.print(sublevels[4]);
  Serial.print(" s5 = ");
  Serial.println(sublevels[5]);

}

void fairly_often() {
  control_me();
  pseudo303();
}

void once_in_a_while(){
  if (mp3_continue){
    refresh_mp3_player();
  }
}

void refresh_mp3_player(){
  if (!playFlac1.isPlaying() && !playMp31.isPlaying()) {  
    _sn.mp3_player_next();
    _sn.mp3_player_play();
  }
}
