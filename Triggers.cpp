#include <sys/_stdint.h>
#include "Constants.h"
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
#include "Functions.h"
#include "Presets.h"
#include "Cablages.h"
#include "PresetsMenu.h"

byte leschords[6][12][3] = {{{0, 4, 7},
                                           {1, 5, 8},
                                           {2, 6, 9},
                                           {3, 7, 10},
                                           {4, 8, 11},
                                           {5, 9, 12},
                                           {6, 10, 13},
                                           {7, 11, 14},
                                           {8, 12, 15},
                                           {9, 13, 16},
                                           {10, 14, 17},
                                           {11, 15, 18}},
                                          {{0, 3, 7},
                                           {1, 4, 8},
                                           {2, 5, 9},
                                           {3, 6, 10},
                                           {4, 7, 11},
                                           {5, 8, 12},
                                           {6, 9, 13},
                                           {7, 10, 14},
                                           {8, 11, 15},
                                           {9, 12, 16},
                                           {10, 13, 17},
                                           {11, 14, 18}},
                                          {{0, 3, 6},
                                           {1, 4, 7},
                                           {2, 5, 8},
                                           {3, 6, 9},
                                           {4, 7, 10},
                                           {5, 8, 11},
                                           {6, 9, 12},
                                           {7, 10, 13},
                                           {8, 11, 14},
                                           {9, 12, 15},
                                           {10, 13, 16},
                                           {11, 14, 17}},
                                          {{0, 4, 8},
                                           {1, 5, 9},
                                           {2, 6, 10},
                                           {3, 7, 11},
                                           {4, 8, 12},
                                           {5, 9, 13},
                                           {6, 10, 14},
                                           {7, 11, 15},
                                           {8, 12, 16},
                                           {9, 13, 17},
                                           {10, 14, 18},
                                           {11, 15, 19}},
                                          {{0, 2, 7},
                                           {1, 3, 8},
                                           {2, 4, 9},
                                           {3, 5, 10},
                                           {4, 6, 11},
                                           {5, 7, 12},
                                           {6, 8, 13},
                                           {7, 9, 14},
                                           {8, 10, 15},
                                           {9, 11, 16},
                                           {10, 12, 17},
                                           {11, 13, 18}},
                                          {{0, 5, 7},
                                           {1, 6, 8},
                                           {2, 7, 9},
                                           {3, 8, 10},
                                           {4, 9, 11},
                                           {5, 10, 12},
                                           {6, 11, 13},
                                           {7, 12, 14},
                                           {8, 13, 15},
                                           {9, 14, 16},
                                           {10, 15, 17},
                                           {11, 16, 18}}
        };
        
        // C Ionian     { C maj;  D min;  E min;  F maj;  G maj;  A min;  B dim  }
        // const chord ionian[7]     = {{0, maj},    {2, minor}, {4, minor}, {5, maj},
        // {7, maj},   {9, minor}, {11, dim}};
        //                            {0,4,7} ,   {2,5,9},    {4,7,11}    {5,9,12},
        //                            {7,11,14},   {9,12,16}, {11,14,17}
        byte *event_ionian[7] = {
            leschords[0][0], leschords[1][2], leschords[1][4], leschords[0][5],
            leschords[0][7], leschords[1][9], leschords[2][11]};
        // C Dorian     { C min;  D min;  D♯ maj; F maj;  G min;  A dim;  A♯ maj  }
        // const chord dorian[7]     = {{0, minor},  {2, minor}, {3, maj},   {5, maj},
        // {7, minor}, {9, dim},   {10, maj}};
        byte *event_dorian[7] = {
            leschords[1][0], leschords[1][2], leschords[0][3], leschords[0][5],
            leschords[1][7], leschords[2][9], leschords[0][10]};
        // C Phrygian    { C min;  C♯ maj; D♯ maj; F min;  G dim;  G♯ maj; A♯ min  }
        // const chord phrygian[7]   = {{0, minor},  {1, maj},   {3, maj},   {5, minor},
        // {7, dim},   {8, maj},   {10, minor}};
        byte *event_phrygian[7] = {
            leschords[1][0], leschords[0][1], leschords[0][3], leschords[1][5],
            leschords[2][7], leschords[0][8], leschords[1][10]};
        // C Lydian      { C maj;  D maj;  E min;  F♯ dim; G maj;  A min;  B min   }
        // const chord lydian[7]     = {{0, maj},    {2, maj},   {4, minor}, {6, dim},
        // {7, maj},   {9, minor}, {11, minor}};
byte *event_lydian[7] = {
            leschords[0][0], leschords[0][2], leschords[1][4], leschords[2][6],
            leschords[0][7], leschords[1][9], leschords[1][11]};
        // C Mixolydian  { C maj;  D min;  E dim;  F maj;  G min;  A min;  A♯ maj  }
byte *event_mixolydian[7] = {
            leschords[0][0], leschords[1][2], leschords[2][4], leschords[0][5],
            leschords[1][7], leschords[1][9], leschords[0][10]};
        // const chord mixolydian[7] = {{0, maj},    {2, minor}, {4, dim},   {5, maj},
        // {7, minor}, {9, minor}, {10, maj}}; C Aeolian     { C min;  D dim;  D♯ maj; F
        // min;  G min;  G♯ maj; A♯ maj  } const chord aeolian[7]    = {{0, minor},  {2,
        // dim},   {3, maj},   {5, minor}, {7, minor}, {8, maj},   {10, maj}};
byte *event_aeolian[7] = {
            leschords[1][0], leschords[2][2], leschords[0][3], leschords[1][5],
            leschords[1][7], leschords[0][8], leschords[0][10]};
        // C harmonic    { C min;  D dim;  D♯ aug; F min;  G maj;  G♯ maj; B dim   }
        // const chord harmonic[7]   = {{0, minor},  {2, dim},   {3, aug},   {5, minor},
        // {7, maj},   {8, maj},   {11, dim}};
byte *event_harmonic[7] = {
            leschords[1][0], leschords[2][2], leschords[3][3], leschords[1][5],
            leschords[0][7], leschords[0][8], leschords[2][11]};
        // C Locrian     { C dim;  C♯ maj; D♯ min; F min;  F♯ maj; G♯ maj; A♯ min  }
        // const chord locrian[7]    = {{0, dim},    {1, maj},   {3, minor}, {5, minor},
        // {6, maj},   {8, maj},   {10, minor}};
byte *event_locrian[7] = {
            leschords[2][0], leschords[0][1], leschords[1][3], leschords[1][5],
            leschords[0][6], leschords[0][8], leschords[1][10]};
        // const chord *all_chords[8] = {ionian, dorian, phrygian, lydian, mixolydian,
        // aeolian, harmonic, locrian};
byte **all_arpegios[ARP_TYPES] = {
            event_ionian,     event_dorian,  event_phrygian, event_lydian,
            event_mixolydian, event_aeolian, event_harmonic, event_locrian};

Arpegiator* Arpegiator::self = nullptr;

Arpegiator::Arpegiator() { self = this;
                     
                          };
//larpegeline is created when pressing a note
//each of these lines can hen useany available synth liners
// length is set in voice after the note on 
//
bool Arpegiator::note_in_arp(uint8_t note){
  for (auto* synth : _rg.active_synths) if (synth && synth->note == note) return true ; 
  return false;
}

void Arpegiator::initiatearpegesynthliner(byte start_voice, MidiEventer msg) {
  if (note_in_arp(msg.note)) return;
  byte free_line = _tt.get_free_synth(msg.note);
  if (free_line < SYNTH_LINERS_COUNT) {
    if (lv.patrecord) {
      md.recordmidinotes(free_line, msg.channel, msg.note, msg.velocity);
    }
    //get and increment note from starter line
    //synth_lines[free_line]->
    synth_lines[free_line]->length_in_arp = gg.arpeglengh + 2;
    synth_lines[free_line]->liner_on(msg.note, msg.velocity);
    //+2 as it is decremented right after note ons
    //try +3 if none
    //add to arp line arp_line
  }
}


void Arpegiator::arpegiate_synth() {
  //
  /*SynthLiner* _rg.active_synths[6];
  memcpy(_rg.active_synths, _rg.active_synths, sizeof(_rg.active_synths));
  int currently_actives = _rg.synth_lines_active ;
  */
  //incrementcs(larpegeline);
  //if (gg.arpegmode == 4) {
  //  arpegioticker(larpegeline);
  //}

  for (int i = 0; i < _rg.synth_lines_active; i++) {
    if (_rg.active_synths[i]->arp_starter) {
      //check why same note is looped after a starter not off ?...
      //check increment & decrement
        if (arpegemptyticks[_rg.active_synths[i]->l_index] > 0) {
          decrementcrementns(_rg.active_synths[i]->l_index);
          return;
        }
      incrementcs(_rg.active_synths[i]->l_index);
      arpegioticker(_rg.active_synths[i]->l_index);

      uint8_t relativenote = all_arpegios[gg.arpegiatortype][tickgamme[i]][ticktriplet[i]];
      //if same note as before reinitialize like manoteon and return
      //original note from starting voice
      _rg.active_synths[i]->next_arp_note = _rg.active_synths[i]->note + relativenote;
      initiatearpegesynthliner(_rg.active_synths[i]->l_index,(MidiEventer){gg.synthmidichannel,_rg.active_synths[i]->next_arp_note,127});
      continue;
    } else {
      if (_rg.active_synths[i]->length_in_arp >= 2) _rg.active_synths[i]->length_in_arp--;
      else if (_rg.active_synths[i]->length_in_arp) _rg.active_synths[i]->liner_off();
      else if (_rg.active_synths[i]->activated && !_rg.active_synths[i]->length_in_arp) _rg.active_synths[i]->liner_off();
      }
  }
}


void Arpegiator::decrementgamme(byte larpegeline) {

  if (tickgamme[larpegeline] > (int)(gg.arpegstartoffset / 6)) {
    tickgamme[larpegeline]--;
  } else {
    tickgamme[larpegeline] = gg.arpegnumofnotes - 1;
  }
}

void Arpegiator::randomdirtest(byte larpegeline) {
  byte lerandom = (byte)random(0, 101);
  if (lerandom > 50) {
    tripletdirection[larpegeline] = !tripletdirection[larpegeline];
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
  if (ticktriplet[larpegeline] > 0) {
    ticktriplet[larpegeline]--;
  } else {
    ticktriplet[larpegeline] = 2;
    if (gg.arpegmode == 1 || gg.arpegmode == 5 || gg.arpegmode == 4) {
      decrementgamme(larpegeline);
    }
    if (gg.arpegmode == 3) {
      ticklagamme(larpegeline);
      tripletdirection[larpegeline] = 1;
      ticktriplet[larpegeline] = 0;
    }
    if (gg.arpegmode == 2) {
      tripletdirection[larpegeline] = 1;
      ticktriplet[larpegeline] = 0;
    }
    if (gg.arpegmode == 5) {
      tripletdirection[larpegeline] = 1;
      ticktriplet[larpegeline] = 0;
    }
    if (gg.arpegmode == 6) {
      tripletdirection[larpegeline] = 1;
      ticktriplet[larpegeline] = 0;
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
  ticktriplet[larpegeline]++;
  if (ticktriplet[larpegeline] > 2) {
    ticktriplet[larpegeline] = 0;
    if (gg.arpegmode == 0 || gg.arpegmode == 2 || gg.arpegmode == 3 || gg.arpegmode == 4) {
      ticklagamme(larpegeline);
    }
    if (gg.arpegmode == 3) {
      tripletdirection[larpegeline] = 0;

      ticktriplet[larpegeline] = 2;
    }
    if (gg.arpegmode == 2) {
      tripletdirection[larpegeline] = 0;

      ticktriplet[larpegeline] = 2;
    }
    if (gg.arpegmode == 5) {
      tripletdirection[larpegeline] = 0;

      ticktriplet[larpegeline] = 2;
    }
    if (gg.arpegmode == 6) {
      tripletdirection[larpegeline] = 0;

      ticktriplet[larpegeline] = 2;
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

void Arpegiator::synth_arpegiator_ticker(byte starting_voice) {


  if (gg.arpegstartoffset > 0) {
    tickgamme[starting_voice] = (byte)((int)(gg.arpegstartoffset / 3.0));
    ticktriplet[starting_voice] = (byte)((int)(gg.arpegstartoffset % 3));
  } else {
    tickgamme[starting_voice] = 0;
    ticktriplet[starting_voice] = 0;
  }
  arpegemptyticks[starting_voice] = gg.arpeggridS;
  arpegnotestick[starting_voice] = 0;

  if (gg.arpegmode == 1 || gg.arpegmode == 5 || gg.arpegmode == 6) {
    tickgamme[starting_voice] = 6;
  }

  if (gg.arpegmode == 0 || gg.arpegmode == 3 || gg.arpegmode == 5) {
    ticktriplet[starting_voice] = 0;
  }
  if (gg.arpegmode == 1 || gg.arpegmode == 2 || gg.arpegmode == 6) {
    tripletdirection[starting_voice] = 0;
    ticktriplet[starting_voice] = 2;
  }

  // printarparams();
  Serial.println();
  Serial.print(" triplet = ");
  Serial.print(ticktriplet[starting_voice]);
  Serial.print(" tickgamme = ");
  Serial.print(tickgamme[starting_voice]);
   
}

// modes 0 up , 1 down, 2 up-down , 3 down-up, 4 random
void Arpegiator::arpegioticker(byte larpegeline) {
  switch ((int)tripletdirection[larpegeline]) {
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
  ticktriplet[larpegeline]++;
  if (ticktriplet[larpegeline] > 2) {
    ticktriplet[larpegeline] = 0;
    ticklagamme(larpegeline);
  }
}

void Arpegiator::ticklagamme(byte larpegeline) {
  if (gg.arpegmode == 4) {
    randomdirtest(larpegeline);
  }
  tickgamme[larpegeline]++;
  if (tickgamme[larpegeline] > gg.arpegnumofnotes - 1) {
    tickgamme[larpegeline] = int(gg.arpegstartoffset / 6);
  }
}

void Arpegiator::incrementcs(byte larpegeline) {
  if (arpegnotestick[larpegeline] < gg.arpeggridC) {
    arpegnotestick[larpegeline]++;
  } else {
    arpegemptyticks[larpegeline] = gg.arpeggridS;
    arpegnotestick[larpegeline] = 0;
  }
}

void Arpegiator::decrementcrementns(byte larpegeline) {
  if (arpegemptyticks[larpegeline] > 0) {
    arpegemptyticks[larpegeline]--;
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

TriggerMessenger::TriggerMessenger() { self = this ; }

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

void TriggerMessenger::arp_tick() {
  if (gg.arpegiatorOn) ap.arpegiate_synth();
}

void TriggerMessenger::tick() {

  if (lv.patternOn) _se.use_pattern();
  
  if (lv.songplaying) _se.update_song_player();

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

  dm.clearDisplay();
  dm.canvastitle.fillScreen(SSD1306_BLACK);
  dm.canvasBIG.fillScreen(SSD1306_BLACK);
  dm.canvastitle.setCursor(0, 0);
  dm.canvastitle.setTextSize(1);
  dm.canvastitle.print(typemsg);
  dm.canvastitle.print(", c:");
  dm.canvastitle.print(msg.channel);
  dm.canvastitle.print(", n:");
  dm.canvastitle.print(msg.note);
  dm.canvastitle.print(", v:");
  dm.canvastitle.print(msg.velocity);

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
    _rg.active_synths[i]->update_line();
    //_ft.pseudo303(i);

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

//quid of a voiceplayer class handling voices dispatch and cleanup
// maybe via _rg actives_lines
//

void TriggerMessenger::MaNoteOn(MidiEventer msg) {
  //uint8_t statusByte = static_cast<uint8_t>(0x90 | channel);
        int lachordon;

  if (lv.navlevel) notes_edgecases(msg);
  //dm.printnoteon(channel,msg.note,msg.velocity);
  if ((msg.channel == gg.synthmidichannel) or (gg.synthmidichannel == 0)) {
    if (!gg.chordson) {
      initiateasynthliner(msg);
    } else {
      // if chords
      //!!! TODO chords should be in init liner or init arp liner
      setchordnotes(msg.note, gg.lasetchord);
      for (int i = 0; i < 3; i++) {
        lachordon = chordnotes[i] + ((int(msg.note / 12)) * 12);
        initiateasynthliner((MidiEventer){gg.synthmidichannel,(byte)lachordon, msg.velocity});
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
    usbMIDI.sendNoteOn(msg.note, msg.velocity, gg.out_midichannel);
    usbMIDI.send_now();
  }
}

bool TriggerMessenger::synth_used_this_note(byte notee) {
  //kind of bad: goes through all instead of only actives
  //for (auto* synth : _rg.active_synths) if (synth && synth->note == notee) return true ; 
  for (int i=0;i<_rg.synth_lines_active;i++){
    if (_rg.active_synths[i]->note == notee) return true ; 
  }
  return false;
}

bool TriggerMessenger::flash_used_this_note(byte data1) {
return false;
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

void TriggerMessenger::shut_used_flash_notes(byte data1) {
  for (int i = 0; i < FLASH_LINERS_COUNT; i++) {
    if (data1 == flash_lines[i]->note) {
      flash_lines[i]->liner_off();
    }
  }
}

void TriggerMessenger::shut_used_synth_notes(byte data1) {
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    if (data1 == synth_lines[i]->note) {
      synth_lines[i]->liner_off();
      if (lv.patrecord) 
        md.record_synth_notesOff(i, gg.synthmidichannel, data1, 0);
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
    usbMIDI.sendNoteOff(msg.note, msg.velocity, gg.out_midichannel);
    usbMIDI.send_now();
  }
  //if (!gg.arpegiatorOn) {
    if (!gg.chordson) {
      shutlineroff(msg.channel,msg.note);
    } else {
      setchordnotesOff(msg.note, gg.lasetchord);
      for (int i = 0; i < 3; i++) {
        lachordnote = chordnotesoff[i] + ((int(msg.note / 12)) * 12);
        shutlineroff(msg.channel,lachordnote);
      }
    }
  //} 
}

void TriggerMessenger::shutlineroff(byte chan,byte data1) {

    if ((chan == gg.synthmidichannel) or ( gg.synthmidichannel == 0)) 
      shut_used_synth_notes(data1);
      
    if ((chan == gg.samplermidichannel) or ( gg.samplermidichannel == 0)) 
      shut_used_flash_notes(data1);
}


void TriggerMessenger::moncontrollercc(byte channel, byte control, byte value) {
  if (value < 128) {
    if (gg.SendMidiOut) {
        //uint8_t statusByte = static_cast<uint8_t>(0xB0 | channel);
        //MidiUSB.sendMIDI({0x0B, statusByte, control, value});
        //MidiUSB.flush();
        //FIXED CC OUTPUT TO CH 3
        usbMIDI.sendControlChange(control,value,gg.out_midichannel);
        usbMIDI.send_now();
        
      }
    if (gg.midiknobassigned[control] != 0 && !lv.freezemidicc) {
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

void TriggerMessenger::notes_edgecases(MidiEventer msg){
    if (msg.note == gg.tapnote && taptap_on) {
    taptap();
    return;
  }
  if (self->debugmidion) debugmidi((char *)"NoteOn", msg);
  // control is (byte)gg.pot_assignements[11 + lv.paddered]
  //inside sample assigner
  if (lv.setting_on_board && (lv.navlevel == 2)) helper_onbard();
  
  if (lv.assigning_sample_to_note) dm.returntonav(3,127,msg.note);
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

void TriggerMessenger::initiateasynthliner(MidiEventer msg) {
  byte free_line = self->get_free_synth(msg.note);
  if (free_line < SYNTH_LINERS_COUNT) {
    if (lv.patrecord) {
      md.recordmidinotes(free_line, gg.synthmidichannel, msg.note, msg.velocity);
    }
    if (gg.arpegiatorOn)  {
      synth_lines[free_line]->arp_starter = 1; 
      ap.synth_arpegiator_ticker(synth_lines[free_line]->l_index);
    }
    synth_lines[free_line]->liner_on(msg.note, msg.velocity);
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
  _ps.setbpms();
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
