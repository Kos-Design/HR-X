#include "muxer.h"
#include <CD74HC4067.h>


Muxer::Muxer() {}

// create a new CD74HC4067 multiplexer with its four control pins
CD74HC4067 Muxer::my_mux(3, 4, 5, 9); 

void Muxer::start() {
  pinMode(g_common_pin, INPUT);
  my_mux.channel(6);
}
int Muxer::get_raw(int iterer) {
  my_mux.channel(iterer);
  //delay(1);
  return analogRead(g_common_pin);
}
int Muxer::read_val(int iterer) {
  my_mux.channel(iterer);
  //delay(1);
  val = analogRead(g_common_pin);
  // return val ;
  if ((val > pots_previous[iterer] + 6) || (val < pots_previous[iterer] - 6)) {
    pots_previous[iterer] = val;
    return val;
  }
  return -1;
}
