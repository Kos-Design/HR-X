#include "MenuClasses.h"
#include "Triggers.h"
#include "Patterns.h"
void cc_edgecases(byte,byte);
void moncontrollercc(byte , byte , byte );
int tick_for_that(int);
TriggerMessenger* TriggerMessenger::self = nullptr;

TriggerMessenger::TriggerMessenger() { self = this ;}

void TriggerMessenger::MaNoteOn(uint8_t ch_,uint8_t nt_,uint8_t ve_) {
  MidiEventer msg = {ch_,nt_,ve_};
  self->MaNoteOn(msg);
}

void TriggerMessenger::MaControlChange(byte channel, byte control, byte value) {
  bool isignored = self->noCCrecordlist(control);

  if (self->debugmidion) {
    self->debugmidi((char *)("ControlChange"), (MidiEventer){channel, control, value});
  }

  if (lv.navlevel)
    cc_edgecases(control, value);

  moncontrollercc(channel, control, value);
  if ((lv.patrecord || lv.recordCC) && !lv.stoptick && !isignored) {
    self->recordCCmidinotes(channel, control, value);
  }
}
void TriggerMessenger::recordCCmidinotes(byte channel, byte lanote, byte leccval) {
  int pos = tick_for_that(lv.tickposition);
  for (int i = 0 ; i < 32 ; i++){
    if (bb.recorded_ccs[i] == 0 || bb.recorded_ccs[i] == lanote ) {
        bb.recorded_ccs[i] = lanote ;
        bb.pots_controllers[i][pos][0] = lanote;
        bb.pots_controllers[i][pos][0] = leccval;
        break;
    }
  }
  pp.cc_partition[lanote][pos] = leccval;
}
bool TriggerMessenger::noCCrecordlist(byte lanotee) {
  for (byte i = 0; i < NO_CCREC_SIZE; i++) {
    if (gg.midiknobassigned[lanotee] == noCCrecord[i]) {
      return 1;
    }
  }
  return 0;
}

void TriggerMessenger::debugmidi(char *typemsg = (char *)"midi ", MidiEventer msg = {0,0,0}) {

  display.clearDisplay();
  canvastitle.fillScreen(SSD1306_BLACK);
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(1);
  canvastitle.print(typemsg);
  canvastitle.print(", c:");
  canvastitle.print(msg.channel);
  canvastitle.print(", n:");
  canvastitle.print(msg.note);
  canvastitle.print(", v:");
  canvastitle.print(msg.velocity);

  dm.dodisplay();
}

void TriggerMessenger::MaNoteOn(MidiEventer msg) {
  byte larpegeline;
  int lachordon;
  //uint8_t statusByte = static_cast<uint8_t>(0x90 | channel);
  if (msg.note == gg.tapnote && taptap_on) {
    taptap();
    return;
  }
  if (self->debugmidion) {
    debugmidi((char *)"NoteOn", msg);
  }
  if (lv.navlevel)
    notes_edgecases(msg.note,msg.velocity);
  //printnoteon(channel,msg.note,msg.velocity);
  if ((msg.channel == gg.synthmidichannel) or (gg.synthmidichannel == 0)) {
    if (!gg.arpegiatorOn) {
      if (!gg.chordson) {
        initiateasynthliner(msg.note, msg.velocity);
      } else {
        // if chords
        setchordnotes(msg.note, gg.lasetchord);
        for (int i = 0; i < 3; i++) {
          lachordon = chordnotes[i] + ((int(msg.note / 12)) * 12);
          initiateasynthliner(lachordon, msg.velocity);
        }
      }
    } else {
      larpegeline = incrementarpegiatingNote(msg.note);
      if (larpegeline < SYNTH_LINERS_COUNT) {
        //should not stop tick during arpegio
        lv.stoptick = 0;
        synth_arpegiator_ticker(msg.note, msg.velocity, larpegeline);
      }
    }
  }

  if ((msg.channel == gg.samplermidichannel) or (gg.samplermidichannel == 0)) {
    //printnoteon(channel, msg.note, msg.velocity);
    if (!gg.chordson) {
      initiateasamplerliner(msg.note, msg.velocity);
    } else {
      // if chords
      setchordnotes(msg.note, gg.lasetchord);
      for (int i = 0; i < 3; i++) {
        lachordon = chordnotes[i] + ((int(msg.note / 12)) * 12);
        initiateasamplerliner(lachordon, msg.velocity);
      }
    }
  }

  if (gg.SendMidiOut) {
    // TODO: send midi during sound trigger to use arpegiators (+ note offs if
    // arpegiator doesn't already send Off notes ?)
  // MidiUSB.sendMIDI({0x09, statusByte, msg.note, msg.velocity});
  // MidiUSB.flush();
    //usbMIDI.send((uint8_t)0x09, (uint8_t)msg.note, (uint8_t)msg.velocity, (uint8_t)msg.channel,(uint8_t)0);
    usbMIDI.sendNoteOn(msg.note, msg.velocity, msg.channel);
    usbMIDI.send_now();
  }
}

void TriggerMessenger::MaNoteOff(uint8_t ch_,uint8_t nt_,uint8_t ve_) {
  MidiEventer msg = {ch_,nt_,ve_};
  self->MaNoteOff(msg);
}

void TriggerMessenger::MaNoteOff(MidiEventer msg) {
  //uint8_t statusByte = static_cast<uint8_t>(0x80 | channel);
  int lachordnote;
  if (gg.SendMidiOut) {
    //MidiUSB.sendMIDI({0x08, statusByte, data1, data2});
    //MidiUSB.flush();
    //usbMIDI.send((uint8_t)0x09, (uint8_t)data1, (uint8_t)data2, (uint8_t)channel,(uint8_t)0);
    usbMIDI.sendNoteOff(msg.note, msg.velocity, msg.channel);

    usbMIDI.send_now();
  }
  if (!gg.arpegiatorOn) {
    if (!gg.chordson) {
      shutlineroff(msg.channel,msg.note);
    } else {
      setchordnotesOff(msg.note, gg.lasetchord);
      for (int i = 0; i < 3; i++) {
        lachordnote = chordnotesoff[i] + ((int(msg.note / 12)) * 12);
        shutlineroff(msg.channel,lachordnote);
      }
    }
  } else {
    // decrement_pt.arpegiatingNote();
    if (testarpege(msg.note)) {
      if (!retestarpege()) {
        lv.stoptickernextcycle = 1;
      }
    }
  }
}

void TriggerMessenger::inittapstime() {
          for (int i = 0; i < 5; i++) {
            tapstime[i] = 0;
          }
        }

void TriggerMessenger::starttaptap() {
          tapstarted = 1;
          starttaptime = millis();
        }

void TriggerMessenger::resettaptap() {

          tapstarted = 0;
          numberoftaps = 0;
          inittapstime();
        }

void TriggerMessenger::taptap() {
  if (!tapstarted) {
    starttaptap();
  } else {
    tapstime[numberoftaps] = millis();
    numberoftaps++;
  }
  if (millis() - starttaptime > 2000 || numberoftaps >= 4) {
    dotapaverage();
    resettaptap();
  }
}
