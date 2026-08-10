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
  static constexpr uint8_t arranged_buttons[6][6] = {{1,  5,  9,  13, 32,  23},
                               {2,  6,  10, 14, 33,  24},
                               {3,  7,  11, 15, 34,  25},
                               {4,  8,  12, 16, 35,  36},
                               {26, 27, 28, 29, 30,  31},
                               {17, 18, 19, 20, 21,  22}
                               };
  //array should be the same size as ALL_BUTTONS
  static constexpr int potsboards[] = {
    2,  1,  9,  5,  4,  3,  8,  7,  6,  14, 13, 11, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0,  12, 10};
};

#endif
