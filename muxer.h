#include <Arduino.h>
#ifndef MUXER_H
#define MUXER_H

class Muxer {
public:
  Muxer();
  void start();
  int get_raw(int iterer);
  int read_val(int iterer);
  
private:
};

#endif
