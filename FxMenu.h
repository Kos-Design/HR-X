#pragma once

#include "MenuClasses.h"



class FxMenuRouter : public SectionHolder {
  public:
      FxMenuRouter();
      static const byte mainmenufxlistsize = 10;
      char mainmenufxlist[mainmenufxlistsize][12] = {
        "Multiply", "Reverb", "Granular", "BitCrusher", "Flanger",
        "Chorus",   "Biquad", "Filter",   "Delay",      "None"
      };
      const int bqrange = 20000;
      double coeffs[STAGES_BQ][5]{};
      uint16_t filterzrange = 14000;
      uint8_t filter_lfo_option = 3 ;
      //static void show();
      static void peakingEQ(float freq, float gainDB, float Q, float Fs, double *c);
      static void prepare_coeffs(byte fx_idx);
      static void dolistMainFxPanel();
      static void dolistmainfxlines();
      static void biquadcontrols(byte fx_idx);
      static void delayfeedback(byte fx_idx, float lesmallfloat);
      static void delaytimingselect(int fx_idx, int leselecta);
      static void restartdelayline(int fx_idx);
      static void changebiquadfreqvalue(byte fx_idx, int valub);
      static void displayfxVcontrols(byte fxinstance);
      static void flangercontrols(byte fx_idx);
      static void flangerVpanelAction(byte fx_idx);
      static void set_wet_mix_at_sub4(byte i);
      static void flangerVpanelSelector(byte fx_idx);
      static void flangerVpanel(byte fx_idx);
      static void choruscontrols(byte fx_idx);
      static void chorusVpanelAction(byte fx_idx);
      static void chorusVpanelSelector(byte fx_idx);
      static void chorusVpanel(byte fx_idx);
      static void granular_pitch_shift(byte fx_idx);
      static void granular_freeze(byte fx_idx);
      static void granularcontrols(byte fx_idx);
      static void granularVpanelAction(byte fx_idx);
      static void granularVpanelSelector(byte fx_idx);
      static void granularVpanel(byte fx_idx);
      static void bitcrusherctrl(byte fx_idx);
      static void bitcrusherVpanelAction(byte fx_idx);
      static void bitcrusherVpanelSelector(byte fx_idx);
      static void bitcrusherVpanel(byte fx_idx);
      static void freeverbscontrl(byte fx_idx);
      static void reverbVpanelAction(byte fx_idx);
      static void reverbVpanelSelector(byte fx_idx);
      static void reverbVpanel(byte fx_idx);
      static void delayVpanelAction(byte fx_idx);
      static void delayVpanelSelector(byte fx_idx);
      static void delayVpanel(byte fx_idx);
      static void filterVpanelAction(byte fx_idx);
      static void lfoonfilterreplug(byte fx_idx);
      static void unpluglfoonfilterz(byte fx_idx);
      static void filtercontrols(byte fx_idx);
      static void filterVpanel(byte fx_idx);
      static void filterVpanelSelector(byte fx_idx);
      static void biquadVpanelAction(byte fx_idx);
      static void biquadVpanel(byte fx_idx);
      static void biquadVpanelSelector(byte fx_idx);
      static void allfxcontrolled();
      static void fx_nav_zero();
      static void fx_nav_one();
      static void fx_nav_two();
      static void MainFxPanel();
      //static constexpr void (*_nav_fx[5])() = {&fx_nav_one, &fx_nav_one, &fx_nav_one, &fx_nav_one, &fx_nav_one};

  private:
    static FxMenuRouter* self;
};

extern FxMenuRouter _fx;

