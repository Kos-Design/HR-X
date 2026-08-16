#include "MenuClasses.h"
#include "Triggers.h"
#include "Patterns.h"
#include "Voices.h"
#include "pads.h"
#include "KnobAssigner.h"
#include "WaveFormer.h"


extern Pads Pads;
Arpegiator::Arpegiator() { }

void Arpegiator::initiatearpegesynthliner(byte larpegeline, byte data1, byte data2) {
  byte free_line = _tt.get_free_synth(data1);
  if (free_line < SYNTH_LINERS_COUNT) {
    for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
      if (data1 == _pt.calledarpegenote[i][0]) {
        _pt.arpegnoteoffin[i][free_line] = gg.arpeglengh + 1;
        _pt.playingarpegiator[i][free_line] = data1;
      }
    }
    _pt.arpegnoteoffin[larpegeline][free_line] = gg.arpeglengh + 1;
    _pt.playingarpegiator[larpegeline][free_line] = data1;
    if (lv.patrecord) {
      md.recordmidinotes(free_line, gg.synthmidichannel, data1, data2);
    }
    synth_lines[free_line]->liner_on(data1, data2);
  }
}

MidiRecorder::MidiRecorder() { }

void MidiRecorder::record_synth_notesOff(int liner, byte channel, byte lenote, byte velocity) {
  int pos = this->tick_for_that(lv.tickposition);
  if (synth_start_tpos[liner] != pos) {
    pp.synth_off_pat[liner][pos] = {channel, lenote, 0};

  } else {
    if (pos == PBARS - 1) {
      pp.synth_off_pat[liner][0] = {channel, lenote, 0};
    } else {
      pp.synth_off_pat[liner][pos + 1] = {channel, lenote, 0};
    }
  }
}
int  MidiRecorder::tick_for_that(int tick){
  tick -= 1 ;
  if (tick < 0 ){
    tick = 31 ;
  }
  return tick ;
}
void MidiRecorder::recordmidinotes(int liner, byte channel, byte lenote, byte velocity) {
  int pos = this->tick_for_that(lv.tickposition);
  synth_start_tpos[liner] = pos;
  pp.track_cells[Synth][lv.tickposition] = 1;
  pp.synth_partition[liner][pos] = {channel, lenote, velocity};
}

bool MidiRecorder::isalreadysameSamplerinpat(byte lenote,int tick) {
  for (int i = 0; i < FLASH_LINERS_COUNT; i++) {
    if (lenote == pp.sampler_partition[i][tick].note) {
      return 1;
    }
  }
  return 0;
}

void MidiRecorder::recordmidinotes2(int liner, byte channel, byte lenote, byte velocity) {
  int pos = this->tick_for_that(lv.tickposition);
  if (!isalreadysameSamplerinpat(lenote,pos)) {
    pp.track_cells[Flash][pos] = 1;
    pp.sampler_partition[liner][pos] = {channel,lenote,velocity};
  }
}

void MidiRecorder::recordCCmidinotes(byte channel, byte lanote, byte leccval) {
  int pos = this->tick_for_that(lv.tickposition);
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
    self->cc_edgecases(control, value);

  self->moncontrollercc(channel, control, value);
  if ((lv.patrecord || lv.recordCC) && !lv.stoptick && !isignored) {
    md.recordCCmidinotes(channel, control, value);
  }
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
  //dm.printnoteon(channel,msg.note,msg.velocity);
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
    //dm.printnoteon(channel, msg.note, msg.velocity);
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

void TriggerMessenger::moncontrollercc(byte channel, byte control, byte value) {
  if (value < 128) {
    if (gg.midiknobassigned[control] != 0 && !lv.freezemidicc) {
      if (gg.SendMidiOut) {
        //uint8_t statusByte = static_cast<uint8_t>(0xB0 | channel);
        //MidiUSB.sendMIDI({0x0B, statusByte, control, value});
        //MidiUSB.flush();
        usbMIDI.sendControlChange(control,value,channel);
        usbMIDI.send_now();
        
      }
      ctl[gg.midiknobassigned[control]].tweaker(value);
      // AudioInterrupts();
    }
  }
}

void TriggerMessenger::cc_edgecases(byte control, byte value){

  //inside Knobs Setter panel
  if (lv.knobsetting){
    _ka.learn_midi(control);
  }
  //set this control == 19 optional in settings 
  
  //inside pattern mode
  if (_pe.paterning && control == 19) {
    if (_pe.track_type == 0) {
      pp.synth_partition[lv.sublevels[2]][lv.sublevels[5]].velocity = value; 
    } else if (_pe.track_type == 1) {
      pp.sampler_partition[lv.sublevels[2]][lv.sublevels[5]].velocity = value; 
    }
  }

  if (lv.setting_on_board) {
    if (lv.navlevel == 2) {
      
      if (control == 19)  {
        gg.but_channel[lv.sublevels[2]] = (gg.but_channel[lv.sublevels[2]] + 1) % 17;
      }
      if (control == 28) {
        gg.but_channel[lv.sublevels[2]] = (gg.but_channel[lv.sublevels[2]] + 16) % 17;
      }
    }
    if (lv.navlevel == 3) {
      //should be another or check above
      if (control == 19) {
        gg.but_velocity[lv.sublevels[2]] = value;
      }
    }
  }

  //inside waveform tracer
  if (lv.waveforming) {
    _wf.set_tracer(control,value);
  }

  if (!lv.songplaying && !_tt.noCCrecordlist(control) && !_tt.debugmidion) {
    dm.show();
  }
}

void TriggerMessenger::notes_edgecases(byte note, byte velo){
  // control is (byte)gg.pot_assignements[11 + lv.paddered]
  //inside sample assigner
  if (lv.setting_on_board && (lv.navlevel == 2)) helper_onbard();
  
  if (lv.assigning_sample_to_note) dm.returntonav(3,127,note);
    //sets the navigation wheel to the captured note position for easier selection when assigning Flashsamples
}

void TriggerMessenger::helper_onbard(){
  if (Pads.potsboards[lv.sublevels[2]] >= 0) {
    gg.muxed_channels[Pads.potsboards[lv.sublevels[2]]] = gg.but_channel[lv.sublevels[2]];
  }
  if ((lv.paddered != 26) && (lv.paddered != 17)) {
    dm.returntonav(lv.navlevel,lv.navrange,lv.paddered + 11);
  }
}

void TriggerMessenger::inittapstime() {
          for (int i = 0; i < 5; i++) {
            tapstime[i] = 0;
          }
        }

byte TriggerMessenger::get_free_synth(byte note) {
  for (byte i = 0; i < SYNTH_LINERS_COUNT; i++) {
    if (!enveloppesL[i]->isActive()) {
      return i;
    }
  }
  return SYNTH_LINERS_COUNT;
}

byte TriggerMessenger::get_free_sampler(byte note) {
  for (byte i = 0; i < FLASH_LINERS_COUNT; i++) {
    if (!(FlashSampler[i]->isPlaying() )) {
      return i;
    } 
  }
  return 0;
}

void TriggerMessenger::initiateasynthliner(byte data1, byte data2) {
  byte free_line = self->get_free_synth(data1);
  if (free_line < SYNTH_LINERS_COUNT) {
    if (lv.patrecord) {
      md.recordmidinotes(free_line, gg.synthmidichannel, data1, data2);
    }
    //dm.printnoteon(0,data1,data2);
    synth_lines[free_line]->liner_on(data1, data2);
  }
}

void TriggerMessenger::initiateasamplerliner(byte data1, byte data2) {
  byte free_line = self->get_free_sampler(data1);
  if (free_line < FLASH_LINERS_COUNT) {
    if (lv.patrecord) {
      md.recordmidinotes(free_line, gg.samplermidichannel, data1, data2);
    }

    flash_lines[free_line]->liner_on(data1, data2);
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
