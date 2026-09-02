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
      static constexpr uint16_t CtlCount = 128;
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
    static constexpr uint16_t local_navranges[6] = {100,1024,100,512,100,1024};
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

    StereoDualFilter(
        AudioStream& input,
        AudioStream& outL,
        AudioStream& outR,
        AudioStream& outL2,
        AudioStream& outR2,

        AudioFilterStateVariable& filterL,
        AudioFilterStateVariable& filterR,

        AudioConnection& p1,
        AudioConnection& p2,
        AudioConnection& p3,
        AudioConnection& p4,
        AudioConnection& p5,
        AudioConnection& p6);

    bool stereo_toggled = false ;

    void disconnect_standard();
    void reconnect_standard();
    void connect();
    void disconnect();
    void setCutoff(float left,float right);
    void setResonance(float left,float right);
  private:

    AudioStream& mInput;

    AudioStream& mOutL;
    AudioStream& mOutR;
    AudioStream& mOutL2;
    AudioStream& mOutR2;

    AudioFilterStateVariable& mFilterL;
    AudioFilterStateVariable& mFilterR;

    AudioConnection& patchInL;
    AudioConnection& patchInR;
    AudioConnection& patchOutL;
    AudioConnection& patchOutR;
    AudioConnection& patchOutL2;
    AudioConnection& patchOutR2;
};

extern StereoDualFilter stereoWidth;