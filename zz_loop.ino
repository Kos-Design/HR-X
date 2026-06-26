void loop() {
  //wav_record_loop();
 // if (!stoptick) {
 // if (millis() % 2 == 0) {
  if (millis() % 2 == 0) {
    pseudo303();
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
    continue_looper();
  }

  if (!blocked) {
    if (millis() % display_lag == 0) {
      if (noteprint) {
        printlanote();
      }
      evalinputs();
      evalrota();
    }
    if ((millis() % (control_lag + 1) == 0) && MULTIPLEXED_PADS){
      check_pads();
    }
    if ((millis() % control_lag == 0) && MULTIPLEXED_PADS) {
      check_pots() ;
    }
  }
  loopusbHub();
}
