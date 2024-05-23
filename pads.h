#include <Arduino.h>
#ifndef PADS_H
#define PADS_H

class Pads {
  public:
    Pads();
    int padloop();
    void begin();
    bool get_back();
    int check_square_pad(char bitter,bool state);
    int check_cancel_pad(char bitter,bool state);
    void pads_to_note();

  private:

};

#endif 
