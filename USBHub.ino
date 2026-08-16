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
  usbMIDI.read();
  //usbmidi ??
  //}
  // needed to handle usbMIDI.read() for msgs from pc or front usb
  /*
  midiEventPacket_t rx;
  do {
    rx = usbMIDI.read();
    if (rx.header != 0) {
      uint8_t status_midi  = rx.byte1;
      uint8_t type_midi    = status_midi & 0xF0;
      uint8_t channel_midi = (status_midi & 0x0F) + 1;
      //if (status_midi == 0xF8) _sg.midi_clock_accumulator();
      if (status_midi == 0xF2){
        uint8_t songpos_midi = rx.byte2 | (rx.byte3 << 7);
        //4 seems to be pos 0 on ardour
        if (songpos_midi == 4 ) _sg.x_ = 0 ;
        //Serial.println(songpos_midi);
      } 
      switch(type_midi){
        case 0x90:
          MaNoteOn(channel_midi,rx.byte2,rx.byte3);
          //rec_test(0,rx.byte1,rx.byte2,rx.byte3);
          //song.send_to_wire(0,rx.byte1,rx.byte2,rx.byte3);
        break;

        case 0x80:
          //rec_test(1,rx.byte1,rx.byte2,rx.byte3);
          //song.send_to_wire(1,rx.byte1,rx.byte2,rx.byte3);
          _tt.MaNoteOff(channel_midi,rx.byte2,rx.byte3);
        break;

        case 0xB0:
          _tt.MaControlChange(channel_midi,rx.byte2,rx.byte3);
        break;

        default:
        break;
      }
    }
  } while (rx.header != 0);
  */
}

void Mytickmidi() {
  //Serial.println("ext click");
  advance_tick();
}

