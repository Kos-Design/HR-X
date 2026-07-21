#include <USBHost_t36.h>

USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
USBHub hub3(myusb);
MIDIDevice midi1(myusb);
MIDIDevice midi2(myusb);
MIDIDevice midi3(myusb);

void loopusbHub() {

  //works without .Task() but task seems to do other things too
  myusb.Task();
  //for multi devices in hub or devices with multiple IDs
  //TODO: check notes, may double trigger
  midi1.read();
  //if (!midi1){
    midi2.read();
    //if (!midi2){
       midi3.read();
    //}

  //}
  // need to handle MidiUSB.read() for msgs from pc or front usb
  midiEventPacket_t rx;
  do {
    rx = MidiUSB.read();
    if (rx.header != 0) {
      uint8_t status_midi  = rx.byte1;
      uint8_t type_midi    = status_midi & 0xF0;
      uint8_t channel_midi = (status_midi & 0x0F) + 1;
      switch(type_midi){
        case 0x90:
          MaNoteOn(channel_midi,rx.byte2,rx.byte3);
          //rec_test(0,rx.byte1,rx.byte2,rx.byte3);
          //song.send_to_wire(0,rx.byte1,rx.byte2,rx.byte3);
        break;

        case 0x80:
          //rec_test(1,rx.byte1,rx.byte2,rx.byte3);
          //song.send_to_wire(1,rx.byte1,rx.byte2,rx.byte3);
          MaNoteOff(channel_midi,rx.byte2,rx.byte3);
        break;

        case 0xB0:
          MaControlChange(channel_midi,rx.byte2,rx.byte3);
        break;

        default:
        break;
      }
    }
  } while (rx.header != 0);

}

void Mytickmidi() {
  //Serial.println("ext click");
  advance_tick();
}

void setuphubusb() {

  myusb.begin();

  midi1.setHandleNoteOn(MaNoteOn);
  midi1.setHandleNoteOff(MaNoteOff);
  midi1.setHandleControlChange(MaControlChange);

  midi2.setHandleNoteOn(MaNoteOn);
  midi2.setHandleNoteOff(MaNoteOff);
  midi2.setHandleControlChange(MaControlChange);

  midi3.setHandleNoteOn(MaNoteOn);
  midi3.setHandleNoteOff(MaNoteOff);
  midi3.setHandleControlChange(MaControlChange);
/*
TODO:
  void myAfterTouchPoly(byte channel, byte note, byte velocity)
  void myProgramChange(byte channel, byte program)
  void myAfterTouch(byte channel, byte pressure)
  void myPitchChange(byte channel, int pitch)
  void mySystemExclusiveChunk(const byte *data, uint16_t length, bool last)
  void mySystemExclusive(byte *data, unsigned int length)
  void myTimeCodeQuarterFrame(byte data)
  void mySongPosition(uint16_t beats)
  void mySongSelect(byte songNumber)
  void myTuneRequest()
  void myClock()
  void myStart()
  void myContinue()
  void myStop()
  void myActiveSensing()
  void mySystemReset()
  void myRealTimeSystem(byte realtimebyte)
  */
}


void debugmidi(char *typemsg = (char *)"midi ", byte channel = 0,
               byte mnote = 0, byte mvelocity = 0) {

  display.clearDisplay();
  canvastitle.fillScreen(SSD1306_BLACK);
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(1);
  canvastitle.print(typemsg);
  canvastitle.print(", c:");
  canvastitle.print(channel);
  canvastitle.print(", n:");
  canvastitle.print(mnote);
  canvastitle.print(", v:");
  canvastitle.print(mvelocity);

  dm.dodisplay();
}