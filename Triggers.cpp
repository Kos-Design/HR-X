#include "MenuClasses.h"
#include "Triggers.h"
#include "Patterns.h"
#include "Voices.h"
#include "SongsMenu.h"
#include "pads.h"
#include "KnobAssigner.h"
#include "WaveFormer.h"
#include "muxer.h"
#include "SynthMenu.h"

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

void Arpegiator::playarpegenote(byte larpegeline) {
  if (_pt.arpegemptyticks[larpegeline] > 0) {
    decrementcrementns(larpegeline);
    return;
  }
  incrementcs(larpegeline);
  byte relativenote;
  byte realnotetoplay;
  relativenote = _tt.all_arpegios[gg.arpegiatortype][_pt.tickgamme[larpegeline]][_pt.ticktriplet[larpegeline]];
  // realnotetoplay = (byte)(octave*12 + relativenote) ;
  realnotetoplay = (byte)(_pt.arpegiatingNote[larpegeline] + relativenote);
  if (gg.arpegmode == 4) {
    arpegioticker(larpegeline);
  }
  _pt.calledarpegenote[larpegeline][0] = realnotetoplay;
  initiatearpegesynthliner(larpegeline, realnotetoplay, _pt.calledarpegenote[larpegeline][1]);
  // initiateasynthliner(realnotetoplay, _pt.calledarpegenote[larpegeline][1] );
  if (gg.arpegmode != 4) {
    arpegioticker(larpegeline);
  }
}

void Arpegiator::decrementgamme(byte larpegeline) {

  if (_pt.tickgamme[larpegeline] > (int)(gg.arpegstartoffset / 6)) {
    _pt.tickgamme[larpegeline]--;
  } else {
    _pt.tickgamme[larpegeline] = gg.arpegnumofnotes - 1;
  }
}

void Arpegiator::allarpegeoffs() {
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    _pt.calledarpegenote[i][0] = 0;
    _pt.calledarpegenote[i][1] = 0;
    for (int j = 0; j < SYNTH_LINERS_COUNT; j++) {
      _pt.playingarpegiator[i][j] = 0;
      _pt.arpegnoteoffin[i][j] = 0;
    }
    _pt.arpegiatingNote[i] = 0;
  }
  _tt.stopallnotes();

}

byte Arpegiator::incrementarpegiatingNote(byte lanote) {
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    if (_pt.arpegiatingNote[i] == 0) {
      _pt.arpegiatingNote[i] = lanote;
      return i;
    }
  }
  return SYNTH_LINERS_COUNT;
}

bool Arpegiator::decrementarpegiatingNote() {
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    if (_pt.arpegiatingNote[i] != 0) {
      _pt.arpegiatingNote[i] = 0;
      return 1;
    }
  }
  return 0;
}

void Arpegiator::randomdirtest(byte larpegeline) {
  byte lerandom = (byte)random(0, 101);
  if (lerandom > 50) {
    _pt.tripletdirection[larpegeline] = !_pt.tripletdirection[larpegeline];
    // ticklagamme(larpegeline);
  }
  if (gg.arpegmode == 4) {
    randomgammedirtest(larpegeline);
  }
}

void Arpegiator::randomgammedirtest(byte larpegeline) {
  byte lerandom = (byte)random(0, 101);
  if (lerandom > 50) {

    decrementgamme(larpegeline);
  } else {
    ticklagamme(larpegeline);
  }
}

void Arpegiator::tickarpegedown(byte larpegeline) {
  if (_pt.ticktriplet[larpegeline] > 0) {
    _pt.ticktriplet[larpegeline]--;
  } else {
    _pt.ticktriplet[larpegeline] = 2;
    if (gg.arpegmode == 1 || gg.arpegmode == 5 || gg.arpegmode == 4) {
      decrementgamme(larpegeline);
    }
    if (gg.arpegmode == 3) {
      ticklagamme(larpegeline);
      _pt.tripletdirection[larpegeline] = 1;
      _pt.ticktriplet[larpegeline] = 0;
    }
    if (gg.arpegmode == 2) {
      _pt.tripletdirection[larpegeline] = 1;
      _pt.ticktriplet[larpegeline] = 0;
    }
    if (gg.arpegmode == 5) {
      _pt.tripletdirection[larpegeline] = 1;
      _pt.ticktriplet[larpegeline] = 0;
    }
    if (gg.arpegmode == 6) {
      _pt.tripletdirection[larpegeline] = 1;
      _pt.ticktriplet[larpegeline] = 0;
    }
    if (gg.arpegmode == 4) {
      randomdirtest(larpegeline);
      // randomgammedirtest(larpegeline);
    }
    if (gg.arpegmode == 7) {
      randomdirtest(larpegeline);
      randomgammedirtest(larpegeline);
    }
  }
}

void Arpegiator::tickarpege(byte larpegeline) {
  _pt.ticktriplet[larpegeline]++;
  if (_pt.ticktriplet[larpegeline] > 2) {
    _pt.ticktriplet[larpegeline] = 0;
    if (gg.arpegmode == 0 || gg.arpegmode == 2 || gg.arpegmode == 3 || gg.arpegmode == 4) {
      ticklagamme(larpegeline);
    }
    if (gg.arpegmode == 3) {
      _pt.tripletdirection[larpegeline] = 0;

      _pt.ticktriplet[larpegeline] = 2;
    }
    if (gg.arpegmode == 2) {
      _pt.tripletdirection[larpegeline] = 0;

      _pt.ticktriplet[larpegeline] = 2;
    }
    if (gg.arpegmode == 5) {
      _pt.tripletdirection[larpegeline] = 0;

      _pt.ticktriplet[larpegeline] = 2;
    }
    if (gg.arpegmode == 6) {
      _pt.tripletdirection[larpegeline] = 0;

      _pt.ticktriplet[larpegeline] = 2;
      decrementgamme(larpegeline);
    }
    if (gg.arpegmode == 4) {
      randomdirtest(larpegeline);
      //
    }
    if (gg.arpegmode == 7) {
      randomdirtest(larpegeline);
      randomgammedirtest(larpegeline);
    }
  }
}

void Arpegiator::synth_arpegiator_ticker(byte data1, byte data2, byte larpegeline) {
  // for (int i = 0 ; i < SYNTH_LINERS_COUNT ; i++ ) {
  // if (_pt.arpegiatingNote[larpegeline] == data1 ) {
  // for (int i = 0 ; i < SYNTH_LINERS_COUNT ; i++ ) {
  _pt.calledarpegenote[larpegeline][1] = data2;
  _pt.calledarpegenote[larpegeline][0] = 0;
  // }
  if (gg.arpegstartoffset > 0) {
    _pt.tickgamme[larpegeline] = (byte)((int)(gg.arpegstartoffset / 3.0));
    _pt.ticktriplet[larpegeline] = (byte)((int)(gg.arpegstartoffset % 3));
  } else {
    _pt.tickgamme[larpegeline] = 0;
    _pt.ticktriplet[larpegeline] = 0;
  }
  _pt.arpegemptyticks[larpegeline] = gg.arpeggridS;
  _pt.arpegnotestick[larpegeline] = 0;

  // if (gg.arpegstartoffset) {
  //  for (int i = 0 ; i < gg.arpegstartoffset ; i++ ) {
  //  tickarpege(larpegeline) ;
  //  }
  // }
  if (gg.arpegmode == 1 || gg.arpegmode == 5 || gg.arpegmode == 6) {
    _pt.tickgamme[larpegeline] = 6;
  }

  if (gg.arpegmode == 0 || gg.arpegmode == 3 || gg.arpegmode == 5) {
    _pt.ticktriplet[larpegeline] = 0;
  }
  if (gg.arpegmode == 1 || gg.arpegmode == 2 || gg.arpegmode == 6) {
    _pt.tripletdirection[larpegeline] = 0;
    _pt.ticktriplet[larpegeline] = 2;
  }

  // printarparams();
}
// modes 0 up , 1 down, 2 up-down , 3 down-up, 4 random
void Arpegiator::arpegioticker(byte larpegeline) {
  switch ((int)_pt.tripletdirection[larpegeline]) {
  case 0:
    // up
    tickarpegedown(larpegeline);
    break;
  case 1:
    // down
    tickarpege(larpegeline);
    break;

  default:
    break;
  }
}

void Arpegiator::ticklatriplet(byte larpegeline) {
  _pt.ticktriplet[larpegeline]++;
  if (_pt.ticktriplet[larpegeline] > 2) {
    _pt.ticktriplet[larpegeline] = 0;
    ticklagamme(larpegeline);
  }
}

void Arpegiator::ticklagamme(byte larpegeline) {
  if (gg.arpegmode == 4) {
    randomdirtest(larpegeline);
  }
  _pt.tickgamme[larpegeline]++;
  if (_pt.tickgamme[larpegeline] > gg.arpegnumofnotes - 1) {
    _pt.tickgamme[larpegeline] = int(gg.arpegstartoffset / 6);
  }
}

void Arpegiator::incrementcs(byte larpegeline) {
  if (_pt.arpegnotestick[larpegeline] < gg.arpeggridC) {
    _pt.arpegnotestick[larpegeline]++;
  } else {
    _pt.arpegemptyticks[larpegeline] = gg.arpeggridS;
    _pt.arpegnotestick[larpegeline] = 0;
  }
}

void Arpegiator::decrementcrementns(byte larpegeline) {
  if (_pt.arpegemptyticks[larpegeline] > 0) {
    _pt.arpegemptyticks[larpegeline]--;
  }
}

bool Arpegiator::testarpege(byte lanote) {
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    if (_pt.arpegiatingNote[i] == lanote) {
      _pt.arpegiatingNote[i] = 0;
      return 1;
    }
  }
  return 0;
}

bool Arpegiator::retestarpege() {
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    if (_pt.arpegiatingNote[i] != 0) {
      return 1;
    }
  }
  return 0;
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
int  MidiRecorder::tick_for_that(int ticko){
  ticko -= 1 ;
  if (ticko < 0 ){
    ticko = 31 ;
  }
  return ticko ;
}
void MidiRecorder::recordmidinotes(int liner, byte channel, byte lenote, byte velocity) {
  int pos = this->tick_for_that(lv.tickposition);
  synth_start_tpos[liner] = pos;
  pp.track_cells[Synth][lv.tickposition] = 1;
  pp.synth_partition[liner][pos] = {channel, lenote, velocity};
}

bool MidiRecorder::isalreadysameSamplerinpat(byte lenote,int ticko) {
  for (int i = 0; i < FLASH_LINERS_COUNT; i++) {
    if (lenote == pp.sampler_partition[i][ticko].note) {
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

int TriggerMessenger::clean_cursor(int pos){
  if (pos >= PBARS ) {
    pos = 0 ;
    return pos;
  } else if (pos < 0 ) {
    pos = PBARS - 1 ;
    return pos;
  }
  return pos;
}

void TriggerMessenger::advance_tick(){
  lv.tickposition = self->clean_cursor(lv.tickposition+1);
  //TODO : remove lv.tickerlasttick logic
  lv.tickerlasttick = millis();
  self->tick();
}

void TriggerMessenger::tick() {

  if (gg.arpegiatorOn) {
      _pt.arpegiate_synth();
  }
  if (lv.patternOn) {
    _se.use_pattern();
  }

  if (lv.songplaying) {
    _se.update_song_player();
  }

}


void TriggerMessenger::Mytickmidi() {
  //Serial.println("ext click");
  advance_tick();
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
void TriggerMessenger::stopallnotes() {
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    if (synth_lines[i]->note) {
      MaNoteOff(gg.synthmidichannel, synth_lines[i]->note, 0);
    }
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
void TriggerMessenger::setchordnotes(byte absolutenote, byte lachord) {
  byte relativenote = ((absolutenote + 12) % 12);
  for (int i = 0; i < 3; i++) {
    chordnotes[i] = leschords[lachord][relativenote][i];
  }
}

void TriggerMessenger::setchordnotesOff(byte absolutenote, byte lachord) {
  byte relativenote = ((absolutenote + 12) % 12);
  for (int i = 0; i < 3; i++) {
    chordnotesoff[i] = leschords[lachord][relativenote][i];
  }
}
void TriggerMessenger::update_active_lines() {
  for (int i = 0; i < _rg.synth_lines_active; i++) {
    _ft.pseudo303(i);
    _rg.active_synths[i]->update_line();
  }
}
void TriggerMessenger::check_pots() {
  int c_change = muxer.read_val(lv.muxer_ch_active);
  if (c_change >= 0 && lv.muxer_ch_active !=9) {
    _tt.MaControlChange(gg.muxed_channels[lv.muxer_ch_active], (byte)gg.ordered_pots[lv.muxer_ch_active], (byte)((c_change / 1024.0) * 127));
  }
  lv.muxer_ch_active = (lv.muxer_ch_active+1)%15; // mux_ch 16 is broken (pot in 9 as well)
}

void TriggerMessenger::check_pads() {
  PadResult padder = Padded.padloop();
  lv.paddered = Padded.arranged_buttons[padder.pad_result[0]][padder.pad_result[1]];
  byte chan_received = gg.but_channel[11 + lv.paddered];
  int cc_note_num = gg.pot_assignements[11 + lv.paddered] - 128;
  //if multiplexed condition || 36 is the cancel button when in multiplexed mode, should not trigger another note or control.
  if ((padder.pad_result[2] == 1) && (lv.paddered != 36)) {
    if (cc_note_num < 0) {
      MaControlChange(chan_received,(byte)gg.pot_assignements[11 + lv.paddered], 64);
    }
    else {
      MaNoteOn((MidiEventer){chan_received, (byte)cc_note_num, gg.but_velocity[11 + lv.paddered]});
    }
  }
  else if ((padder.pad_result[2] == 0) && (lv.paddered != 36) && (cc_note_num > 0)) {
    MaNoteOff(chan_received, cc_note_num, 0);
  }
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
      larpegeline = ap.incrementarpegiatingNote(msg.note);
      if (larpegeline < SYNTH_LINERS_COUNT) {
        //should not stop tick during arpegio
        lv.stoptick = 0;
        ap.synth_arpegiator_ticker(msg.note, msg.velocity, larpegeline);
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

void TriggerMessenger::synth_used_this_note(byte data1) {
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    if (data1 == synth_lines[i]->note) {
      synth_lines[i]->liner_off();
      if (lv.patrecord) 
        md.record_synth_notesOff(i, gg.synthmidichannel, data1, 0);
    }
  }
}

void TriggerMessenger::MaProgramchange(byte channel, byte data1) {
  if (self->debugmidion) {
    self->debugmidi((char *)"ProgramChange", (MidiEventer){channel, data1, 0});
  }
  /*
  int leprogchanged = (int)(data1);
  if (leprogchanged < _ps.catalog->files_counter) {
    _ps.catalog->displayable_offset = leprogchanged ;
    _ps.catalog->refresh_files_names();
    _ps.read_preset();
  }*/
}
void TriggerMessenger::flash_used_this_note(byte data1) {
  for (int i = 0; i < FLASH_LINERS_COUNT; i++) {
    if (data1 == flash_lines[i]->note) {
      flash_lines[i]->liner_off();
    }
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
    if (ap.testarpege(msg.note)) {
      if (!ap.retestarpege()) {
        lv.stoptickernextcycle = 1;
      }
    }
  }
}
void TriggerMessenger::shutlineroff(byte chan,byte data1) {

    if ((chan == gg.synthmidichannel) or ( gg.synthmidichannel == 0)) 
      synth_used_this_note(data1);
      
    if ((chan == gg.samplermidichannel) or ( gg.samplermidichannel == 0)) 
      flash_used_this_note(data1);
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

  if (!lv.songplaying && !self->noCCrecordlist(control) && !self->debugmidion) {
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
  if (Padded.potsboards[lv.sublevels[2]] >= 0) {
    gg.muxed_channels[Padded.potsboards[lv.sublevels[2]]] = gg.but_channel[lv.sublevels[2]];
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

void TriggerMessenger::dotapaverage() {
  int tottaptime = 0;
  for (int i = 0; i < numberoftaps; i++) {
    tottaptime += (tapstime[i] - starttaptime);
  }
  tapaverage = tottaptime / numberoftaps;
  gg.millitickinterval = round(tapaverage / 10.0);
  _pt.setbpms();
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
