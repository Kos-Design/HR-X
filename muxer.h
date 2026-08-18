#pragma once

class CD74HC4067;

class Muxer {
public:
  Muxer();
  // select a pin to share with the 16 channels of the CD74HC4067
  static const int g_common_pin = 41;
  int val = 0;
  int pots_previous[16]{};
  static CD74HC4067  my_mux;
  void start();
  int get_raw(int iterer);
  int read_val(int iterer);

};

extern Muxer muxer;
