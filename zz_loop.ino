
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
  if ( rec_looping ) {
    _rd.continue_looper();
  }

  
  
}
