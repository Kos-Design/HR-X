#pragma once

#include "MenuClasses.h"

class KnobAssigner : public SectionHolder {
  public:
      KnobAssigner();
      static void show();
      static void learn_midi(byte captured);
      static int find_assigned_knob(int k);
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