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
  midi1.read();
  if (!midi1){
    midi2.read();
    if (!midi2){
       midi3.read();
    }
  }

  //TODO: make devices selector
  //
  //if (midi1) {
  //  Serial.printf("midi1 VID=%04X PID=%04X\n",
  //                midi1.idVendor(),
  //                midi1.idProduct());
  //  }
  //
  //  if (midi2) {
  //     Serial.printf("midi2 VID=%04X PID=%04X\n",
  //                   midi2.idVendor(),
  //                   midi2.idProduct());
  //}

  // need to handle MidiUSB.read() for msgs from pc or front usb
  midiEventPacket_t rx;
  do {
    rx = MidiUSB.read();
    if (rx.header != 0) {
      //Serial.println(rx.header);
      switch(rx.header){
        case 8:
          MaNoteOn(rx.byte1,rx.byte2,rx.byte3);
          //rec_test(0,rx.byte1,rx.byte2,rx.byte3);
          //song.send_to_wire(0,rx.byte1,rx.byte2,rx.byte3);
        break;

        case 9:
          //rec_test(1,rx.byte1,rx.byte2,rx.byte3);
          //song.send_to_wire(1,rx.byte1,rx.byte2,rx.byte3);
          MaNoteOff(rx.byte1,rx.byte2,rx.byte3);
        break;

        case 11:
          MaControlChange(rx.byte1,rx.byte2,rx.byte3);
        break;

        default:
        break;
      }
      /*
      Serial.print("Received: ");
      byte m_status = (rx.header, HEX) ;
      byte m_messageType = m_status & 0xF0;  // Extract the message type (upper nibble)
      Serial.print(" ");
      byte m_channel = (rx.byte1, HEX) & 0x0F;
      Serial.print(rx.header);
      Serial.print(" ");
      Serial.print(m_channel);
      Serial.print(" ");
      Serial.print("-");
      Serial.print(rx.byte2);
      Serial.print("-");
      Serial.println(rx.byte3);
      */
    }
  } while (rx.header != 0);

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

  // midi1.setHandleAfterTouchPoly(myAfterTouchPoly);
  //  midi1.setHandleProgramChange(myProgramChange);
  //  midi1.setHandleAfterTouchChannel(myAfterTouchChannel);
  //  midi1.setHandlePitchChange(myPitchChange);
  // Only one of these System Exclusive handlers will actually be
  // used.  See the comments below for the difference between them.
  //  midi1.setHandleSystemExclusive(mySystemExclusiveChunk);
  //  midi1.setHandleSystemExclusive(mySystemExclusive);
  //  midi1.setHandleTimeCodeQuarterFrame(myTimeCodeQuarterFrame);
  // midi1.setHandleSongPosition(mySongPosition);
  // midi1.setHandleSongSelect(mySongSelect);
  //  midi1.setHandleTuneRequest(myTuneRequest);
  //midi1.setHandleClock(Mytickmidi);
  //  midi1.setHandleStart(myStart);
  //  midi1.setHandleContinue(myContinue);
  //  midi1.setHandleStop(myStop);
  //  midi1.setHandleActiveSensing(myActiveSensing);
  //  midi1.setHandleSystemReset(mySystemReset);
  // This generic System Real Time handler is only used if the
  // more specific ones are not set.
  //  midi1.setHandleRealTimeSystem(myRealTimeSystem);
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

  dodisplay();
}