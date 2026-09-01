#pragma once
#include "elapsedMillis.h"
#include "MenuClasses.h"
#include "FilesLister.h"

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

class MasterClock {
    public:

        MasterClock();

        bool stop = 1 ;
        bool tic_toc[7]{};
        int timee = 0;
        static void click();
        void dispatch_ticks();
        void attach_2(void (*cb)());
        void attach_3(void (*cb)());
        void attach_long(void (*cb)());
        void attach_24(void (*cb)());
        void attach_24_bis(void (*cb)());
        void attach_96(void (*cb)());
        void attach_oscilloscope(void (*cb)());
        void attach_303(void (*cb)());
        void stopticker();
        void startticker();

    private:

        volatile uint32_t tick96 = 0;
        void (*_callback_24)() = nullptr;
        void (*_callback_24_bis)() = nullptr;
        void (*_callback_96)() = nullptr;
        void (*_callback_2)() = nullptr;
        void (*_callback_3)() = nullptr;
        void (*_callback_long)() = nullptr;
        void (*_callback_oscilloscope)() = nullptr;
        void (*_callback_303)() = nullptr;
        static MasterClock* self;
};

extern MasterClock Tocker;

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

        int getnextposofevent1Off_synth(int linei, byte lanote, int fromi);
        int getnextposofevent1Off_sampler(int linei, byte lanote, int fromi);
        static void computelenghtmesureoffline_synth();
        static void computelenghtmesureoffline_sampler();
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
        static constexpr byte sizeofoptionspattern = 6;
        static const char* optionspatternlabels[];
        static bool target_sampler;
        static bool target_synth;
        static bool target_ccs;
        bool interpolOn = 1;

        static void clearlapattern();
        static void clearCCline();
        static void clearsynthpatternline();
        static void merge_partitions();
        static void merge_synth_partition_liners();
        static void merge_sampler_partition_liners();
        static void clearsamplerpatternline();
        static void toggle_interpol_cc();
        static void dotransposesynth();
        static void dotransposeCC();
        static void doShifterCC();
        static void show();
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
        static bool *_targets[3];
        static constexpr void (*_pat_params[6])() = {&showtransposedisplays,&showShifterdisplays,&clearlapattern,
                                        &showlestargetdisplays,&toggle_interpol_cc,&merge_partitions};
        static constexpr void (*cleaners[3])() = {&clearsynthpatternline,&clearlapattern,&clearCCline};
        static constexpr void (*mergers[2])() = {&merge_synth_partition_liners,&merge_sampler_partition_liners};
        static constexpr void (*shifters[3])() = {&doShiftersynth,&doShiftersampler,&doShifterCC};
        static constexpr void (*transposers[3])() = {&dotransposesynth,&dotransposesampler,&dotransposeCC};
    private:
        static POptionsRouter* self;
};

extern POptionsRouter _po;

class PatternsMenuRouter : public SectionHolder {
  public:
        PatternsMenuRouter();
        FilesLister *catalog;
        static constexpr byte sizeofpatternlistlabels = 8;

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
        static void doPatternsmenu();
        static void deletepattern();
        static void copypattern();
        static void writelemidi();
        static void set_arp_type();

        static constexpr void (*_route_nav[7])() = {&pattern_nav_zero, &route_navlevel,
                        &route_navlevel, &route_navlevel, &route_navlevel,
                         &route_navlevel, &route_navlevel};

        static constexpr void (*_nav_pattern[8])() = {&_pe.show,&save_pattern,
                                            &load_pattern, &duplicate_pattern,&remove_pattern,
                                            &_po.show,&_po.clearlapattern,&_ce.show};
  private:
      static PatternsMenuRouter* self;
};

extern PatternsMenuRouter _pt;
