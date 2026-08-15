#pragma once

#include "MenuClasses.h"

bool retestarpege();

extern DisplayManager dm ;
void synth_arpegiator_ticker(uint8_t, uint8_t, uint8_t);
void notes_edgecases(uint8_t,uint8_t);
void initiateasynthliner(uint8_t,uint8_t);
void initiateasamplerliner(uint8_t,uint8_t);
void setchordnotes(uint8_t,uint8_t);
void setchordnotesOff(uint8_t,uint8_t);
void shutlineroff(uint8_t,uint8_t);
byte incrementarpegiatingNote(uint8_t);
bool testarpege(uint8_t);
void dotapaverage();

class TriggerMessenger {
    public:
      TriggerMessenger();
      int tapstime[5] = {0,0,0,0,0};
      int starttaptime;
      float tapaverage;

      byte chordnotes[3]{};
      byte chordnotesoff[3]{};
      byte numberoftaps = 0;
      bool taptap_on = true;
      bool debugmidion = 0;
      bool tapstarted = 0;

      // C Ionian     { C maj;  D min;  E min;  F maj;  G maj;  A min;  B dim  }
      // const chord ionian[7]     = {{0, maj},    {2, minor}, {4, minor}, {5, maj},
      // {7, maj},   {9, minor}, {11, dim}};
      //                            {0,4,7} ,   {2,5,9},    {4,7,11}    {5,9,12},
      //                            {7,11,14},   {9,12,16}, {11,14,17}
      const byte *event_ionian[7] = {
          leschords[0][0], leschords[1][2], leschords[1][4], leschords[0][5],
          leschords[0][7], leschords[1][9], leschords[2][11]};
      // C Dorian     { C min;  D min;  D♯ maj; F maj;  G min;  A dim;  A♯ maj  }
      // const chord dorian[7]     = {{0, minor},  {2, minor}, {3, maj},   {5, maj},
      // {7, minor}, {9, dim},   {10, maj}};
      const byte *event_dorian[7] = {
          leschords[1][0], leschords[1][2], leschords[0][3], leschords[0][5],
          leschords[1][7], leschords[2][9], leschords[0][10]};
      // C Phrygian    { C min;  C♯ maj; D♯ maj; F min;  G dim;  G♯ maj; A♯ min  }
      // const chord phrygian[7]   = {{0, minor},  {1, maj},   {3, maj},   {5, minor},
      // {7, dim},   {8, maj},   {10, minor}};
      const byte *event_phrygian[7] = {
          leschords[1][0], leschords[0][1], leschords[0][3], leschords[1][5],
          leschords[2][7], leschords[0][8], leschords[1][10]};
      // C Lydian      { C maj;  D maj;  E min;  F♯ dim; G maj;  A min;  B min   }
      // const chord lydian[7]     = {{0, maj},    {2, maj},   {4, minor}, {6, dim},
      // {7, maj},   {9, minor}, {11, minor}};
      const byte *event_lydian[7] = {
          leschords[0][0], leschords[0][2], leschords[1][4], leschords[2][6],
          leschords[0][7], leschords[1][9], leschords[1][11]};
      // C Mixolydian  { C maj;  D min;  E dim;  F maj;  G min;  A min;  A♯ maj  }
      const byte *event_mixolydian[7] = {
          leschords[0][0], leschords[1][2], leschords[2][4], leschords[0][5],
          leschords[1][7], leschords[1][9], leschords[0][10]};
      // const chord mixolydian[7] = {{0, maj},    {2, minor}, {4, dim},   {5, maj},
      // {7, minor}, {9, minor}, {10, maj}}; C Aeolian     { C min;  D dim;  D♯ maj; F
      // min;  G min;  G♯ maj; A♯ maj  } const chord aeolian[7]    = {{0, minor},  {2,
      // dim},   {3, maj},   {5, minor}, {7, minor}, {8, maj},   {10, maj}};
      const byte *event_aeolian[7] = {
          leschords[1][0], leschords[2][2], leschords[0][3], leschords[1][5],
          leschords[1][7], leschords[0][8], leschords[0][10]};
      // C harmonic    { C min;  D dim;  D♯ aug; F min;  G maj;  G♯ maj; B dim   }
      // const chord harmonic[7]   = {{0, minor},  {2, dim},   {3, aug},   {5, minor},
      // {7, maj},   {8, maj},   {11, dim}};
      const byte *event_harmonic[7] = {
          leschords[1][0], leschords[2][2], leschords[3][3], leschords[1][5],
          leschords[0][7], leschords[0][8], leschords[2][11]};
      // C Locrian     { C dim;  C♯ maj; D♯ min; F min;  F♯ maj; G♯ maj; A♯ min  }
      // const chord locrian[7]    = {{0, dim},    {1, maj},   {3, minor}, {5, minor},
      // {6, maj},   {8, maj},   {10, minor}};
      const byte *event_locrian[7] = {
          leschords[2][0], leschords[0][1], leschords[1][3], leschords[1][5],
          leschords[0][6], leschords[0][8], leschords[1][10]};
      // const chord *all_chords[8] = {ionian, dorian, phrygian, lydian, mixolydian,
      // aeolian, harmonic, locrian};
      const byte **all_arpegios[arpeges_types] = {
          event_ionian,     event_dorian,  event_phrygian, event_lydian,
          event_mixolydian, event_aeolian, event_harmonic, event_locrian};

      static void MaNoteOn(uint8_t ch_,uint8_t nt_,uint8_t ve_);

      void MaNoteOn(MidiEventer msg);

      static void MaNoteOff(uint8_t ch_,uint8_t nt_,uint8_t ve_);

      void MaNoteOff(MidiEventer msg);
      void taptap();
      void inittapstime();
      void starttaptap();
      void resettaptap();
      void debugmidi(char *, MidiEventer);
    private:
      static TriggerMessenger* self;
};
