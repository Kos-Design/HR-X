
int paddered;


//checking one pot per loop as it is fast as long as we call it often
byte muxer_ch_active = 1;

void check_pots() {
  int c_change = Muxer.read_val(muxer_ch_active);
  if (c_change >= 0 && muxer_ch_active !=9) {
    MaControlChange(gg.muxed_channels[muxer_ch_active], (byte)gg.ordered_pots[muxer_ch_active], (byte)((c_change / 1024.0) * 127));
  }
  muxer_ch_active = (muxer_ch_active+1)%15; // mux_ch 16 is broken (pot in 9 as well)
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
  //set them all on a separate cycle if possible
  control_me();
  UpdateSpectrum();
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
