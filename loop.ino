
int pad_result;

void allpasslevels() {
  mix303L1.gain(0, 1);
  mix303L1.gain(1, 0);
  mix303L1.gain(2, 0);
}

void pseudo303() {

  for (int i = 0; i < nombreofliners; i++) {

    if (glidemode > 0 && dogliding[i]) {

      glidefactorCmode[i] = leglideposition[i] / (millitickinterval * 1.0);

      notefrequency = (glidefactorCmode[i]) * leglidershiftCmode[i] +
                      notestofreq[lapreviousnotewCmode[i]][1];

      tweakfreqlive(i, notefrequency);

      if (leglideposition[i] <
          (millitickinterval * 2.0 * (glidemode / 128.0) / 2.0)) {
        leglideposition[i]++;
        // Serial.print(leglideposition[i]);
      } else {
        stopglidenoteChords(i);
      }

      // }
    }

   // if (!stoptick) {
   //   checkall128cc();
   // }

    if (tb303[i] == 1) {

      int letimerz303 = millis() - le303start[i];
      if (letimerz303 > le303pulsewidth) {

        tb303[i] = 0;
        // TODO: Check why should we ?
       // le303start[0] = 0;
        letimerz303 = le303pulsewidth;
      }

      ladiff1 = (letimerz303 * 1.0 / le303pulsewidth);
      ladiff2 = (letimerz303 * 1.0 / le303pulsewidth2);

      letbfreq = le303filterzrange + 100 -
                 (le303filterzrange * (fxslopedown2(slope1, ladiff1)));
      // AudioNoInterrupts();
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

  // Serial.print(" received ");
  // Serial.print(c_change);
  // 36 is the cancel button, should not trigger another note or control.
  if ((pad_result.pad_result[2] == 1) && (paddered != 36)) {
    //inside pattern mode
    if (sublevels[0] == 4 && navlevel >=5 && sublevels[1] == 0) {
      if (paddered == 17) {
        Serial.println(Muxer.get_raw(6));
        synth_partition[sublevels[2]][sublevels[5]][2] = (int)((Muxer.get_raw(6)/1024.0)*128);
        lemenuroot();
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
        sublevels[2] = paddered + 11;
        vraipos = sublevels[2];
        myEnc.write(4 * sublevels[2]);
      }
      OnBoardVpanel();
    } 
    //inside waveform tracer
    else if ((sublevels[0] == 8) && (sublevels[1] == 4) && (navlevel == 2)) {
      if (paddered == 17) {
        trace_waveform = !trace_waveform;
      }
    } else {
      if (cc_note_num <= 0) {
        MaControlChange(but_channel[11 + paddered],
                        (byte)pot_assignements[11 + paddered], 64);
      } 
      //normal note pad
      else {
        /*Serial.println(" ");
        Serial.print("paddered ");
        Serial.print(paddered);
        Serial.println(" ");
        Serial.print("pot_assignements ([11+paddered])=");
        Serial.print(cc_note_num);
        */
        MaNoteOn(but_channel[11 + paddered], cc_note_num,
                 but_velocity[11 + paddered]);
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
          but_velocity[sublevels[2]] = (byte)((c_change / 1024.0) * 128);
          OnBoardVpanel();
        }
        
         else {
          MaControlChange(muxed_channels[itr], (byte)ordered_pots[itr], (byte)((c_change / 1024.0) * 128));
        }
        /*
        //10 & 12 = joystick
        //11,13,14 = equalizer faders
        //15 = crossfader
        // if ((itr !=11) && (itr !=13) && (itr !=14) && (itr !=15) ){
         Serial.println(" ");
         Serial.print("mux ");
         Serial.print(itr);
         Serial.print(" received ");
         Serial.print(c_change);
         Serial.print(" = ");
         Serial.print((byte)((c_change/1024.0)*128));
         Serial.print(" assigned to ");
         Serial.print((byte)pot_assignements[itr]);
         Serial.print(" = ");
         Serial.print(ControlList[(byte)pot_assignements[itr]]);
        */
      }
    }
    itr++;
    if (itr >= 16) {
      itr = 0;
    }
}
void loop() {
  //wav_record_loop();
 // if (!stoptick) {
 // if (millis() % 2 == 0) {
  if (millis() % 2 == 0) {
    pseudo303();
  }
  if (debug_cpu){
    print_memory_usage();
  }
  if (pre_record) {
    if (millis() - tocker > 500) {
      rec_looping = true ;
      pre_record = false ;
    }
  }
  if ( rec_looping ) { 
    continue_looper();
  } 
  if ( !rec_looping && !pre_record) {
    if (millis() % display_lag == 0) {
    
      if (noteprint) {
        printlanote();
      }
      
      evalinputs();
      evalrota();
    }

    if (millis() % (control_lag + 1) == 0) {
      check_pads();
    }

    if ( !stoptick ) {
      if (blinkTimer.TRIGGERED) {
        advance_tick();
        }
    } 
    //else {
      
      if ((millis() % control_lag) == 0) {
        check_pots() ;
      //}
    }
  }
  loopusbHub();
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
