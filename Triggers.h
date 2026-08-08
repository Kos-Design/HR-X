#pragma once

#include "MenuClasses.h"

bool retestarpege();

extern bool stoptickernextcycle;

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
