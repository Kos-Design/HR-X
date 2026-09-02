#pragma once
#include "MenuClasses.h"
#include "FilesLister.h"

struct Song {
    int numberofpatonsong=0;
    int patternonsong[99]{};
};

extern Song ng;

class SongEditorRouter : public SectionHolder {
    public:
        SongEditorRouter();
        byte songpage = 0;
        byte songselectorX = 0;
        byte songselectorY = 0;
        byte songplayhead = 0;

        //changing_ccs[32][32][2] cc,val
        void light_cc_change();
        void use_pattern();

        void playdasong();
        void stopdasong();
        void pausedasong();
        void showplayheadprogress();
        void loadsongpattern();

        void actionSongTransport();

        void showsongnavarrows();
        void setpatterninsong();
        void songmodetopbar();
        void showsongcell();

        void selectormoveX();
        void songTransportSelector();

        void showpatonSongGrid();
        void selectpatterninsong();

        void update_song_player();

        void play_synth_line(int linei);
        void play_sampler_line(int linei) ;

        void selectsongnavarrows();

        void songgridposselector();

        static void Songmodepanel();

  private:
      static SongEditorRouter* self;
};

extern SongEditorRouter _se;

class SongMenuRouter : public SectionHolder {
    public:
        SongMenuRouter();
        static constexpr uint8_t sg_labels_count = 8;

        FilesLister *catalog;
        int x_ = 0 ;
        int t_ = 0 ;
        static void show();
        static void route_navlevel();
        static void lv1_wrapper(void (*func)());

        static void save_song();
        static void writedasong();
        static void parseSong();
        static void load_song();
        static void song_nav_zero();
        static void initializeSong();
        static void clear_song_popup();
        static void duplicate_song();
        static void copySong();
        static void remove_song();
        static void deleteSong();
        static void shiftSongright(int leshifter);
        static void shiftSongleft(int leshifter);
        static void doSongShifter();
        static void showSongShifterdisplays();
        static void shift_song();
        static void midi_clock_accumulator();
        static void fine_cursor();
        static void show_some_params();

        static void song_params_panel();
        static void draw_song_menu();
        static constexpr void (*_route_nav[5])() = {&song_nav_zero, &route_navlevel,
                                                &route_navlevel, &route_navlevel, &route_navlevel};

    private:

      static constexpr void (*_nav_song[sg_labels_count])() = {&_se.Songmodepanel,&save_song, &load_song, &duplicate_song,
                                                      &remove_song, &clear_song_popup, &song_params_panel, &shift_song};
      static SongMenuRouter* self;
};

extern SongMenuRouter _sg;
