
void control_me(){
  if (!blocked) {
      if (noteprint)
        _st.printlanote();    
      if (MULTIPLEXED_PADS){
        check_pads();
        check_pots();
      }
      evalinputs();
      evalrota();
    }
}

void loop() {
  //wav_record_loop();
 // if (!stoptick) {
  if (millis() % 3 == 0) {
   fairly_often();
   loopusbHub();
  } else if (millis() % osc_refresher_period == 0) {
    oscilloscope_loop();
    //UpdateSpectrum();
  }
  /*
  if (debug_cpu){
    print_memory_usage();
  }
  */
  if (pre_record) {
    if (millis() - tocker > 500) {
      rec_looping = true ;
      pre_record = false ;
    }
  }
  if ( rec_looping && (millis() % 2 == 0)) {
    _rd.continue_looper();
  }
}

void start_eq_display_Trigger_ctl(byte cc_value){
  if (showing_eq) return ;
  showing_eq = true ;
  
  //fft256.begin();
}

void stop_eq_display_Trigger_ctl(byte cc_value){
  if (!showing_eq) return ;
  showing_eq = false ;
  //fft256.end();
  //fft256.clear();
}

