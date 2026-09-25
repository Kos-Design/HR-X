#pragma once
#include <stdint.h>
#include "Constants.h"
#include "MenuClasses.h"
#include "Presets.h"

class MidiRecorder {
  public:
    MidiRecorder();
    uint8_t synth_start_tpos[SYNTH_LINERS_COUNT]{};
    uint8_t sampler_start_tpos[FLASH_LINERS_COUNT]{};
    uint8_t active_cc_count = 0 ;
    uint8_t active_ccs[128] ;
    void recordmidinotes(int liner, byte channel, byte lenote, byte velocity);
    void recordCCmidinotes(MidiEventer msg);
    bool isalreadysameSamplerinpat(byte lenote,int ticko);
    int tick_for_that(int ticko);
    void add_active_CC_index(uint8_t value);
    bool add_to_cc_list(uint8_t value);
    void remove_active_CC_index(uint8_t value);
    void rebuild_actives_ccs();
    void recordmidinotes2(int liner, byte channel, byte lenote, byte velocity);
    void record_sampler_notesOff(int liner, byte channel, byte lenote, byte velocity);
    void record_synth_notesOff(int liner, byte channel, byte lenote, byte velocity);
};

extern MidiRecorder md;

class TriggerMessenger {
    public:
        TriggerMessenger();
        uint32_t tapstime[5] = {0,0,0,0,0};
        uint32_t starttaptime;
        float tapaverage;

        byte chordnotes[3]{};
        byte chordnotesoff[3]{};
        byte numberoftaps = 0;
        bool taptap_on = true;
        bool debugmidion = 0;
        bool tapstarted = 0;
        byte noCCrecord[NO_CCREC_SIZE] = {3,35,36,37, 38,39,40,41,42,44,1};


        static void MaNoteOn(uint8_t ch_,uint8_t nt_,uint8_t ve_);

        void MaNoteOn(MidiEventer msg, bool from_partition = false);

        static void MaNoteOff(uint8_t ch_,uint8_t nt_,uint8_t ve_);

        void MaNoteOff(MidiEventer msg,bool from_partition = false);

        static void MaControlChange(byte channel, byte control, byte value);
        void MaControlChange(MidiEventer msg);
        static void MaProgramchange(byte channel, byte data1);
        static void advance_tick();
        void tick();
        int clean_cursor(int pos);
        void moncontrollercc(byte channel, byte control, byte value);
        void moncontrollercc(MidiEventer msg);
        void check_pads();
        void check_pots();
        void update_active_lines();
        void shutlineroff(byte chan,byte data1, bool from_partition = false);
        void cc_edgecases(MidiEventer msg);
        void notes_edgecases(MidiEventer msg);
        void setchordnotes(byte absolutenote, byte lachord);
        void setchordnotesOff(byte absolutenote, byte lachord);
        void helper_onbard();
        bool noCCrecordlist(byte lanotee);
        void taptap();
        void dotapaverage();
        void shut_used_synth_notes(byte data1);
        void shut_used_flash_notes(byte data1);
        static void stopallnotes();
        byte get_free_synth(byte note);
        byte get_free_sampler(byte note);
        void initiateasynthliner(MidiEventer msg, bool from_partition = false);
        void initiateasamplerliner(byte data1, byte data2, bool from_partition = false);
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
