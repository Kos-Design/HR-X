#include <Arduino.h>
#include "pads.h"
#include "Adafruit_Keypad.h"
bool back_pressed = false ;
const byte kROWS = 6; // rows
const byte kCOLS = 6; // columns
//define the symbols on the buttons of the keypads
char kkeys[kROWS][kCOLS] = {
  {'1','2','3','A','E','F'},
  {'4','5','6','B','G','H'},
  {'7','8','9','C','I','J'},
  {'*','0','#','D','K','L'},
  {'M','N','O','P','Q','R'},
  {'S','T','U','V','W','X'}
};
byte colPins[kCOLS] = {26,27,28,29,33,34}; //connect to the row pinouts of the keypad
byte rowPins[kROWS] = {35,36,37,38,39,40}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Adafruit_Keypad customKeypad = Adafruit_Keypad( makeKeymap(kkeys), rowPins, colPins, kROWS, kCOLS);

Pads::Pads(){
}
void Pads::begin(){
customKeypad.begin();
}
bool Pads::get_back(){
  if (back_pressed == true ) {
    back_pressed = false ;
    return true;
  };
  return false;
}
void Pads::padloop(){
  // put your main code here, to run repeatedly:
  customKeypad.tick();

  while(customKeypad.available()){
    keypadEvent e = customKeypad.read();
    Serial.print((char)e.bit.KEY);

    if(e.bit.EVENT == KEY_JUST_PRESSED) {
      Serial.println(" pressed");
      if((char)e.bit.KEY=='H'){
        Serial.println("back pressed");
        back_pressed = true ;
        }
;
    }
    else if(e.bit.EVENT == KEY_JUST_RELEASED) Serial.println(" released");
  }

  delay(1);
}
