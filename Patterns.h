#pragma once

#include <Arduino.h>
#include "MenuClasses.h"
#include "FilesLister.h"


void computelenghtmesureoffline_synth();
void computelenghtmesureoffline_sampler();
void call_refresh_flash_track();
void shutlineroff(byte,byte);
void playarpegenote(byte);
void closeallenvelopes();
void call_stopallnotes();

/*class MidiPlayer{
  public:
    MidiPlayer();

    bool begin(FsFile &file);

    void stop();

    void reset();

    // Returns true if one or more events were emitted
    bool update(uint32_t currentTick);

    bool isPlaying() const { return playing; }

    //----------------------------------
    // MIDI information
    //----------------------------------

    uint16_t bpm = 120;

    uint16_t ppqn = 96;

    uint8_t numerator = 4;

    uint8_t denominator = 4;

    uint32_t stepTicks = 24;

  protected:

    //----------------------------------
    // User callbacks
    //----------------------------------

    virtual void noteOn(uint8_t ch,
                        uint8_t note,
                        uint8_t vel) {}

    virtual void noteOff(uint8_t ch,
                         uint8_t note,
                         uint8_t vel) {}

    virtual void controlChange(uint8_t ch,
                               uint8_t cc,
                               uint8_t value) {}

  private:

    //----------------------------------
    // File
    //----------------------------------

    FsFile *f = nullptr;

    uint32_t trackEnd = 0;

    bool playing = false;

    bool eof = false;

    //----------------------------------
    // Timing
    //----------------------------------

    uint32_t currentEventTick = 0;

    uint32_t nextEventTick = 0;

    //----------------------------------
    // Pending event
    //----------------------------------

    uint8_t eventType = 0;

    uint8_t eventChannel = 0;

    uint8_t eventData1 = 0;

    uint8_t eventData2 = 0;

    //----------------------------------
    // MIDI parser
    //----------------------------------

    uint8_t runningStatus = 0;

    bool readHeader();

    bool readTrack();

    bool readNextEvent();

    bool parseMeta();

    bool parseSysEx();

    //----------------------------------
    // Helpers
    //----------------------------------

    uint8_t read8();

    uint16_t read16();

    uint32_t read32();

    uint32_t readVar();

    void skip(uint32_t bytes);
};*/

enum TrackTypes : uint8_t  {
    Synth,
    Flash
};

struct Pattern {
  int flash_notes_length[16][PBARS];
  int synth_notes_length[6][PBARS];
  uint8_t cc_partition[128][PBARS];
  MidiEventer sampler_partition[16][PBARS];
  MidiEventer synth_partition[6][PBARS];
  MidiEventer synth_off_pat[6][PBARS];
  MidiEventer sampler_off_pat[PBARS];
  bool track_cells[2][PBARS] ;
};

extern Pattern pp;

class CCEditor : public SectionHolder {
  public:
        CCEditor();
        static void show();
        static void route_navlevel_1();
        static void showleditcc();
        static void headerccedit();
        static void showvertlinecursor(int lavertpos);
        static void editlaccactionpath();

  private:
      static CCEditor* self;
};

extern CCEditor _ce;

class PatEditRouter : public SectionHolder {
    public:
        PatEditRouter();
        int *_length_part;
        MidiEventer temp_sampler_partition[PBARS];
        MidiEventer temp_synth_partition[PBARS];
        MidiEventer *_on_part;
        MidiEventer *_off_part;
        MidiEventer *_temp_part;
        byte liners_count = 1 ;
        byte liners_page = 0;
        byte track_type = 0;
        byte local_line = 0;
        bool visible_tracks[6][PBARS]{};
        bool addinglength = 0;

        bool paterning = false ;

        static void homer();
        static void set_editor_to_synth(byte liner);
        static void set_editor_to_sampler(byte liner);
        static void show();
        static void doshownoteline();
        static void drawPatternRow();
        static void reshift_tracks_display();
        static void show_lines_events();
        static void clearevented0(int lapatline);
        static void refresh_synth_track();
        static void refresh_flash_track();
        static void dolistpatternlineblocks();
        int grid_start_note();
        static void terminatenotesinbetween();
        static void sync_temp();
        static void drawCursorCol();
        static void track_selector();
        static void show_track_header();
        static void note_selector();
        static void start_cell_setter();
        static void draw_velobars();
        static void stretch_cell_length();
        static void stretch_cell_velocity();
        static void sanitize_synth_partition();
        static void sanitize_sampler_partition();
        static void set_cell_at_pos(byte ch_, byte nt_, byte ve_);
        static void set_cell_velocity();
        static void refresh_patterns();

        static constexpr void (*cell_events[7])() = {&homer,&track_selector, &note_selector,
                                                    &start_cell_setter, &stretch_cell_length,
                                                    &stretch_cell_velocity, &set_cell_velocity};
    private:
      static constexpr void (*_refresher[2])() = {&refresh_synth_track, &refresh_flash_track};
      static constexpr void (*set_editor_type[2])(byte) = { &set_editor_to_synth, &set_editor_to_sampler};
      static constexpr void (*_sanitizer[2])() = {&sanitize_synth_partition,&sanitize_sampler_partition};
      static PatEditRouter* self;
};

extern PatEditRouter _pe;

class POptionsRouter : public SectionHolder {
    public:
        POptionsRouter();
        static void clearlapattern();
        static void clearCCline();
        static void clearsynthpatternline();
        static void merge_synth_partition_liners();
        static void clearsamplerpatternline();
        static void optionspattern();
        static void dotranspose();
        static void doShifter();
        static void dotransposesynth();
        static void dotransposeCC();
        static void doShifterCC();
        static void shiftnotesCCup(int leshifter);
        static void shiftnotesCCdown(int leshifter);
        static void shiftnotesCCright(int leshifter);
        static void shiftnotesCCleft(int leshifter);
        static void shiftnotes1up(int leshifter);
        static void shiftnotes1down(int leshifter);
        static void shiftnotes1right(int leshifter);
        static void shiftnotes1left(int leshifter);
        static void dotransposesampler();
        static void doShiftersampler();
        static void shiftnotes2up(int leshifter);
        static void shiftnotes2down(int leshifter);
        static void shiftnotes2right(int leshifter);
        static void shiftnotes2left(int leshifter);
        static void showtransposedisplays();
        static void doShiftersynth();
        static void showShifterdisplays();
        static void showlestargetdisplays();
        static void optionspatterndisplays();

    private:
        static POptionsRouter* self;
};

extern POptionsRouter _po;

class PatternsMenuRouter : public SectionHolder {
  public:
        PatternsMenuRouter();
        FilesLister *catalog;
        byte arpegnoteoffin[SYNTH_LINERS_COUNT][SYNTH_LINERS_COUNT];
        byte playingarpegiator[SYNTH_LINERS_COUNT][SYNTH_LINERS_COUNT];
        byte calledarpegenote[SYNTH_LINERS_COUNT][2];
        byte arpegiatingNote[SYNTH_LINERS_COUNT];
        byte tickgamme[SYNTH_LINERS_COUNT];
        byte ticktriplet[SYNTH_LINERS_COUNT];
        byte arpegnotestick[SYNTH_LINERS_COUNT];
        byte arpegemptyticks[SYNTH_LINERS_COUNT];
        bool tripletdirection[SYNTH_LINERS_COUNT];

        static void route_navlevel();
        static void show();
        static void pattern_nav_zero();
        static void remove_pattern();
        static void duplicate_pattern();
        static void load_pattern();
        static void save_pattern();
        static void lv1_wrapper(void (*func)());
        static void addnoteoff2next(byte lanotee, byte lapos);
        static void set_ccs();
        static void parsepattern();
        static void parsepattern_old();
        static void doPatternsmenu();
        static void deletepattern();
        static void copypattern();
        static void midifileliner(File &pat_filer,int liner, int ticker);
        static void midifilelinerSampler(File &pat_filer,int liner, int ticker);
        static void midifilelinerOff(File &pat_filer, int liner, int ticker);
        static void midifileCC(File &pat_filer,int lecc, int ticker);
        static void write_midi_info(File &pat_filer);
        static void writelemidi();
        static void arpegiate_synth();
        static void set_arp_type();
        static void call_draw_sequencer();
        static void call_options();
        static void call_edit_ccs();
        static void call_clearpattern();


        static constexpr void (*_route_nav[7])() = {&pattern_nav_zero, &route_navlevel,
                        &route_navlevel, &route_navlevel, &route_navlevel,
                         &route_navlevel, &route_navlevel};

        static constexpr void (*_nav_pattern[8])() = {&call_draw_sequencer,&save_pattern,
                                            &load_pattern, &duplicate_pattern,&remove_pattern,
                                            &call_options,&call_clearpattern,&call_edit_ccs};
  private:
      static PatternsMenuRouter* self;
};
