#include <CD74HC4067.h>
int val;
CD74HC4067
    my_mux(3, 4, 5,
           9); // create a new CD74HC4067 object with its four control pins
const int g_common_pin =
    41; // select a pin to share with the 16 channels of the CD74HC4067
#include "muxer.h"

int pots_previous[16];

Muxer::Muxer() {}
void Muxer::start() {
  pinMode(g_common_pin, INPUT);
  my_mux.channel(6);
}

int Muxer::read_val(int iterer) {
  my_mux.channel(iterer);
  delay(5);
  val = analogRead(g_common_pin);
  // return val ;
  if ((val > pots_previous[iterer] + 6) || (val < pots_previous[iterer] - 6)) {
    pots_previous[iterer] = val;
    return val;
  }
  return -1;
  /*
  Serial.print("analog ");
  Serial.print(iterat);
  Serial.print(" is: ");
  Serial.println(val);*/
}
