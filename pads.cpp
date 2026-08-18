#include "pads.h"
#include "Adafruit_Keypad.h"

Adafruit_Keypad Pads::customKeypad = Adafruit_Keypad(makeKeymap(kkeys), (uint8_t*)rowPins, (uint8_t*)colPins, kROWS, kCOLS);

Pads::Pads() {}

void Pads::begin() { customKeypad.begin(); }
void Pads::pads_to_note() { customKeypad.begin(); }
bool Pads::get_back() {
  if (back_pressed) {
    back_pressed = false;
    return true;
  }
  return false;
}

int Pads::check_cancel_pad(char bitter, bool state) {
  if (bitter == 'L') {
    if (state) {
      back_pressed = true;
      return 0;
    }
  }
  return 0;
}

PadResult Pads::padloop() {
  customKeypad.tick();
  bool state = 0;
  while (customKeypad.available()) {
    keypadEvent e = customKeypad.read();
    // Serial.print((char)e.bit.KEY);
    if (e.bit.EVENT == KEY_JUST_PRESSED) {
      state = true;
    } else if (e.bit.EVENT == KEY_JUST_RELEASED)
      state = false;

    check_cancel_pad((char)e.bit.KEY, state);
    PadResult result = {e.bit.ROW, e.bit.COL, uint8_t(state)};

    return result;
    //delay(1);
  }
  return (PadResult){(uint8_t)99, (uint8_t)99, (uint8_t)99};
}
