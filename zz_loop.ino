
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
  } else if (millis() % osc_refresher_period == 0) {
    oscilloscope_loop();
  }

  if (_rd.pre_record) {
    if (millis() - tocker > 500) {
      _rd.rec_looping = true ;
      _rd.pre_record = false ;
    }
  }
  if ( _rd.rec_looping && (millis() % 2 == 0)) {
    _rd.continue_looper();
  }
}
