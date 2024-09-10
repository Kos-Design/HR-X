#include <USBHost_t36.h>

USBHost myusb;
USBHub hub1(myusb);
//USBHub hub2(myusb);
MIDIDevice midi1(myusb);

void loopusbHub() {

  //myusb.Task();
  midi1.read();
}
void setuphubusb() {

  myusb.begin();

  midi1.setHandleNoteOn(MaNoteOn);
  midi1.setHandleNoteOff(MaNoteOff);
  // midi1.setHandleAfterTouchPoly(myAfterTouchPoly);
  midi1.setHandleControlChange(MaControlChange);
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