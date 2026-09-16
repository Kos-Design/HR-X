#pragma once
#include <stdint.h>
#include "MenuClasses.h"

class KnobAssigner : public SectionHolder {
  public:
      KnobAssigner();
      static void show();
      static void learn_midi(byte captured);
      static int find_assigned_knob(int k);
      static void show_assignements();
      static void kb_home();
      static void assigner();
      static void set_midi_cc_to_ctl(byte cc_nt, int cc_cl);
      static void set_it();
      //sizeof(ctl) / sizeof(ctl[0]);

  private:

    static constexpr void (*_actionable[3])() = { &kb_home, &assigner, &set_it };
    static KnobAssigner* self;
};

extern KnobAssigner _ka;

class AdsrMenuRouter : public SectionHolder {
  public:
    AdsrMenuRouter();
    static constexpr const char* AdsrLabels[6] = {
            "Attack Delay ",
            "Attack ",
            "Hold ",
            "Decay ",
            "Sustain ",
            "Release "
    };
    static void show();
    static void ApplyADSR();
    static void slice_adsr();
    static void draw_frame();
    static void resync_tmp();
    static void SetADSR();
    static void GlobalADSR();
    static void print_adsr_echo(String titre, int niveau);
    int32_t tmp_adsrlevels[6] = {0, 5, 0, 100, 0, 50};

  private:

    static AdsrMenuRouter* self;
};

extern AdsrMenuRouter _ad;

class StereoDualFilter {
  public:

    StereoDualFilter();

    bool stereo_toggled = false ;
    const char* stereo_mode_lbls[4] = {"Off","Phase","Freq","Delay"};

    void disconnect_standard();
    void reconnect_standard();
    void connect_phase();
    void connect_freq();
    void connect_delay();
    void disconnect();
    void setCutoff(float left,float right);
    void setResonance(float left,float right);
   
};

extern StereoDualFilter stereoWidth;