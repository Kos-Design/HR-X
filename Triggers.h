#pragma once
#include <stdint.h>
#include "Constants.h"
#include "MenuClasses.h"
#include "Presets.h"

class MidiRecorder {
  public:
    MidiRecorder();
    byte synth_start_tpos[SYNTH_LINERS_COUNT]{};
    void recordmidinotes(int liner, byte channel, byte lenote, byte velocity);
    void recordCCmidinotes(byte channel, byte lanote, byte leccval);
    bool isalreadysameSamplerinpat(byte lenote,int ticko);
    int tick_for_that(int ticko);
    void recordmidinotes2(int liner, byte channel, byte lenote, byte velocity);
    void record_synth_notesOff(int liner, byte channel, byte lenote, byte velocity);
};

extern MidiRecorder md;

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
        byte noCCrecord[NO_CCREC_SIZE] = {3,35,36,37, 38,39,40,41,42,44,1};


        static void MaNoteOn(uint8_t ch_,uint8_t nt_,uint8_t ve_);

        void MaNoteOn(MidiEventer msg);

        static void MaNoteOff(uint8_t ch_,uint8_t nt_,uint8_t ve_);

        void MaNoteOff(MidiEventer msg);

        static void MaControlChange(byte channel, byte control, byte value);
        static void MaProgramchange(byte channel, byte data1);
        static void advance_tick();
        void tick();
        int clean_cursor(int pos);
        void moncontrollercc(byte channel, byte control, byte value);
        void check_pads();
        void check_pots();
        void update_active_lines();
        void shutlineroff(byte chan,byte data1);
        void cc_edgecases(byte control, byte value);
        void notes_edgecases(MidiEventer msg);
        void setchordnotes(byte absolutenote, byte lachord);
        void setchordnotesOff(byte absolutenote, byte lachord);
        void helper_onbard();
        bool noCCrecordlist(byte lanotee);
        void taptap();
        void dotapaverage();
        void shut_used_synth_notes(byte data1);
        void shut_used_flash_notes(byte data1);
        void stopallnotes();
        byte get_free_synth(byte note);
        byte get_free_sampler(byte note);
        void initiateasynthliner(MidiEventer msg);
        void initiateasamplerliner(byte data1, byte data2);
        void inittapstime();
        void starttaptap();
        static void show_midi(char *typemsg = (char *)"midi ", MidiEventer msg = {0,0,0}) ;
        static void arp_tick();
        static void Mytickmidi();
        void resettaptap();

    private:
      static TriggerMessenger* self;
};
extern TriggerMessenger _tt;


class Arpegiator {
    public:
        Arpegiator();
        byte tickgamme[SYNTH_LINERS_COUNT];
        byte ticktriplet[SYNTH_LINERS_COUNT];
        byte arpegnotestick[SYNTH_LINERS_COUNT];
        byte arpegemptyticks[SYNTH_LINERS_COUNT];
        bool tripletdirection[SYNTH_LINERS_COUNT];
        bool note_in_arp(uint8_t note);
        uint8_t last_3_notes[3]{};
        uint8_t last_indexer = 0;

        void initiatearpegesynthliner(byte larpegeline, MidiEventer msg);
        void arpegiate_synth();
        bool same_3_notes();
        void decrementgamme(byte larpegeline);
        void randomdirtest(byte larpegeline);
        void randomgammedirtest(byte larpegeline);
        void tickarpegedown(byte larpegeline);
        void tickarpege(byte larpegeline);
        void synth_arpegiator_ticker(byte larpegeline);
        void arpegioticker(byte larpegeline);
        void ticklatriplet(byte larpegeline);
        void ticklagamme(byte larpegeline);
        void incrementcs(byte larpegeline);
        void decrementcrementns(byte larpegeline);

    private:
        static Arpegiator* self;
};

extern Arpegiator ap;
