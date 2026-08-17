#pragma once

#include "MenuClasses.h"
#include "KnobAssigner.h"

class GlideMenuRouter : public SectionHolder {
  public:
    GlideMenuRouter();
        static constexpr const char* GlideModeLabels[5] = {
            "Off",
            "Portamento",
            "ReversePortamento",
            "PitchAttack",
            "ReversePitchAttack"
        };

        uint8_t *glide_params[4] = {reinterpret_cast<uint8_t*>(&gg.glideMode),&gg.portamento_time,&gg.portamento_height,&gg.glide_slope};

        static void show();
  private:
    
    static GlideMenuRouter* self;
};

extern GlideMenuRouter _gd;

class Filter303MenuRouter : public SectionHolder {
  public:
    Filter303MenuRouter();
    float slopelinear[18] = {0.85,0.858334,0.866668,0.875,0.883336,0.89167,0.900004,0.908338,0.916672,0.925006,0.93334,0.941674,0.95,0.958342,0.966676,0.97501,0.983344,0.991678};

    float fxsloper[18] = {0.85,0.88,0.91,0.92,0.93,0.95,0.95,0.96,0.97,0.97,0.98,0.98,0.99,0.99,1.00,1.00,1.00,1.00};
    int lardiff = 0;
    float sloped[18]{};
    int letbfreq = 450;

    static void initialize303group();
    static void allpasslevels();
    static void pseudo303(byte i);
    static void filter_knob_freq();
    static void filter_knob_res();
    static void filter_knob_low();
    static void filter_knob_band();
    static void filter_knob_high();
    static void filter_knob_wet();
    static void filter_knob_preamp();
    static void filter_knob_glide();
    static void le303filterVpanelAction();
    static void le303filterVpanel();
    static void le303filterVpanelSelector();
    static void restore_from_temp();
    static void set_filter_buff_temp();
    static void show();
  private:
    static constexpr void (*filters_pointers[8])() = {&filter_knob_freq, &filter_knob_res, &filter_knob_low, &filter_knob_band, &filter_knob_high,
                                            &filter_knob_wet, &filter_knob_preamp, &filter_knob_glide};
                    byte *filter_tmp_pointers[8] = { &gg.le303ffilterzVknobs[0], &gg.le303ffilterzVknobs[1], &gg.mixle303ffilterzVknobs[0], &gg.mixle303ffilterzVknobs[1], &gg.mixle303ffilterzVknobs[2],
                                              &gg.le303filterzwet, &gg.preampleswaves, &gg.portamento_time };

                    byte filter_tmp_values[8] = {gg.le303ffilterzVknobs[0],gg.le303ffilterzVknobs[1],gg.mixle303ffilterzVknobs[0],gg.mixle303ffilterzVknobs[1],gg.mixle303ffilterzVknobs[2],
                                          gg.le303filterzwet,gg.preampleswaves,gg.portamento_time };
    static Filter303MenuRouter* self;
};

extern Filter303MenuRouter _ft;


class Mp3PlayerRouter : public SectionHolder {
    public:
        Mp3PlayerRouter();
        FilesLister *catalog;
        String mp3_name = "MP3/Addict.mp3";
        String mp3_dir = "MP3/";
        uint16_t mp3_count = 0;
        uint16_t file_index = 0 ;
        uint16_t next_mp3 = 0 ;
        uint16_t previous_mp3 = 0 ;
        byte mp3_ext = 0 ;
        bool mp3_looped = 0 ;
        bool mp3_paused = 0 ;
        bool mp3_shuffle = 0 ;
        bool mp3_continue = 0 ;

        static void mp3_player_play();
        static void mp3_player_stop();
        static void mp3_player_continous();
        static void mp3_player_pause();
        static void mp3_player_next();
        static void mp3_player_previous();
        static void mp3_player_shuffle();
        static void mp3_loop_setter();
        static void mp3_player_actions();
        static void get_file_type();
        static void playFile(const char *mp3_file);
        static void get_next_mp3();
        static void count_mp3s();
        static void transport_selector();
        static void play_flac_file(const char *flac_file);
        static void display_mp3_title();
        static void mp3_player_panel();
  private:
      static Mp3PlayerRouter* self;
};

extern Mp3PlayerRouter _mp;


class SynthMenuRouter : public SectionHolder {
    public:
        SynthMenuRouter();
        int unit = (int)gg.wavesfreqs[lv.oscillator] % 10;
        int tenth     = ((int)(gg.wavesfreqs[lv.oscillator] * 10)) % 10;
        int hundredth = ((int)(gg.wavesfreqs[lv.oscillator] * 100)) % 10;
        //TODO give default value based on wformtype
        const byte synth_params_count = 8;

        static void show();
        static void route_navlevel_1();
        static void route_navlevel_2();
        static void displayoffsetwav();
        static void freqbars_panel_selector();
        static void freqbars_panel_action();
        static void displayfreqbars();
        static void freqbars_panel();
        static void displayphasebars();
        static void displayModulatedbool();
        static void setfmtophase();
        void setfmtofreq();
        static void wavelineModulatedbool();
        static void displaywaveformicon();
        static void displayLFOpanel();
        static void go_previous();
        static void go_next();
        static void wavelinesBG();
        static void wavelining();
        static void draw_synth_params();
        static void dolistsyntmenu();
        static void synths_switcher();
        static void wavesline_selector();
        static void synth_nav_zero();
        static void plug_no_waves();
        static void plug_waves();
        static void plug_moded_waves();
        static void plug_ampl_moded_waves();
        static void plug_strings_waves();
        static void plug_ampl_moded_strings();
        static void plug_drum_waves();
        static void plug_ampl_moded_drums();
        static void no_modulation();
        static void freq_modulation();
        static void phase_modulation();
        static void amplitude_modulation();
        static void setwavetypefromlist();
        static void setphaselevel();
        static constexpr void (*_nav_synth[SN_MENU_LABELS_COUNT])() = {&wavesline_selector,&_mx.show, &_ad.show, &_mp.mp3_player_panel, &_ft.show,&_gd.show};
        static constexpr void (*_waveliners[6])() = {&synths_switcher,&wavelining, &wavelining, &wavelining,&wavelining, &wavelining};
        static constexpr void (*modulation_pointers[4])() = {&no_modulation,&freq_modulation,&phase_modulation,&amplitude_modulation};

        static constexpr void (*_synth_params[8])() = {&displaywaveformicon,&wavelineModulatedbool,&displayLFOpanel,
                                                      &freqbars_panel,&displayoffsetwav,&displayphasebars,&go_previous,&go_next};

        static constexpr void (*_route_nav[7])() = {
            &route_navlevel_1,
            &route_navlevel_2,
            &route_navlevel_2,
            &route_navlevel_2,
            &route_navlevel_2,
            &route_navlevel_2,
            &route_navlevel_2
        };



  private:
    static SynthMenuRouter* self;
};

extern SynthMenuRouter _sn;

