#include <Arduino.h>
#ifndef PADS_H
#define PADS_H

struct PadResult {
  byte pad_result[3];
};

class Pads {
public:
  Pads();
  PadResult padloop();
  void begin();
  bool get_back();
  int check_cancel_pad(char bitter, bool state);
  void pads_to_note();

private:
};

#endif
