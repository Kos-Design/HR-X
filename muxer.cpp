#include <CD74HC4067.h>
int val;
CD74HC4067 my_mux(3, 4, 5, 9);  // create a new CD74HC4067 object with its four control pins
const int g_common_pin = 41; // select a pin to share with the 16 channels of the CD74HC4067
#include "muxer.h"
  int iterer = 0;  
Muxer::Muxer(){
}
void Muxer::start(){
    pinMode(g_common_pin, INPUT); 
    my_mux.channel(6);
}

void Muxer::read_val(int iterat)                     
{
  val = analogRead(g_common_pin);
  /*
  Serial.print("analog ");
  Serial.print(iterat);
  Serial.print(" is: ");
  Serial.println(val);*/
  delay(1);
}
void Muxer::loopy()
{ 
    
  /*
        my_mux.channel(0);
  delay(300);
        read_val(0);
         my_mux.channel(1);
  delay(300);
        read_val(1);
         my_mux.channel(2);
  delay(300);
        read_val(2);
     */   
  if (( millis() % 300 ) == 0) {
     iterer++;
     if (iterer >= 6 ) {
      iterer = 0 ;  
     }
     
    //for (int i = 0; i < 8; i++) {
          my_mux.channel(8-iterer);
          //delay(10);
          read_val(8-iterer);
      //}  
  }  
    
}
