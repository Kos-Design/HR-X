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
//buttons from the matrix associated with the 4x4 pad
char pads4x[4][4] = {
  {'1','2','3','A',},
  {'4','5','6','B',},
  {'7','8','9','C',},
  {'*','0','#','D',}
};

byte colPins[kCOLS] = {26,27,28,29,33,34}; //connect to the row pinouts of the keypad
byte rowPins[kROWS] = {38,37,35,36,39,40}; //connect to the column pinouts of the keypad
bool pads_mode[4][4] ;

//initialize an instance of class NewKeypad
Adafruit_Keypad customKeypad = Adafruit_Keypad( makeKeymap(kkeys), rowPins, colPins, kROWS, kCOLS);

Pads::Pads(){
}

void Pads::begin(){
customKeypad.begin();
}
void Pads::pads_to_note(){
customKeypad.begin();
}
bool Pads::get_back(){
  if (back_pressed == true ) {
    back_pressed = false ;
    return true;
  };
  return false;
}

int Pads::check_cancel_pad(char bitter,bool state){
  if(bitter=='L'){
      if(state) {
        //Serial.println("back pressed");
        back_pressed = true ;
        return 0 ;
        } 
        //else { Serial.println("back released");}
  }
  return 0;
}
 
PadResult Pads::padloop(){
  // put your main code here, to run repeatedly:
  customKeypad.tick();
  bool state;
  while(customKeypad.available()){
    keypadEvent e = customKeypad.read();
    //Serial.print((char)e.bit.KEY);
    if (e.bit.EVENT == KEY_JUST_PRESSED ) {
   
      state = true;
    } else if(e.bit.EVENT == KEY_JUST_RELEASED) state = false;
    
    check_cancel_pad((char)e.bit.KEY,state) ;
    PadResult result = {e.bit.ROW,e.bit.COL,byte(state)};
             
    return result ;
    delay(1);
}
return (PadResult){(byte)99,(byte)99,(byte)99};
}
