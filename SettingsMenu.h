#pragma once
#include "MenuClasses.h"

class VirtualKnobs : public SectionHolder {
  public:
    VirtualKnobs();
    void doposkselector();
    static void Vbuttonspanel();
    void actionvbuttons();
    void displayonscreenbuttons();
  private:
    static VirtualKnobs* self;
};

extern VirtualKnobs _vk;        

class SettingsMenuRouter : public SectionHolder {
    public:
        SettingsMenuRouter();
                    
        static constexpr uint8_t settings_labels_count = 17;
        bool noteprint = 0;
        char usnotes[12][5] = {"C",  "C#", "D",  "Eb", "E",  "F",
                       "F#", "G",  "G#", "A",  "Bb", "B"};

        char eunotes[12][5] = {"Do",  "Do#", "Re",   "Mib", "Mi",  "Fa",
                              "Fa#", "Sol", "Sol#", "La",  "Sib", "Si"};
        uint8_t AudioInSource = 2;

        float freqtonotes[128] = {
          8.21, 8.70, 9.22, 9.77, 10.35, 10.96, 11.61, 12.31,
          13.04, 13.81, 14.63, 15.50, 16.43, 17.40, 18.44, 19.53,
          20.70, 21.93, 23.23, 24.61, 26.07, 27.63, 29.27, 31.01,
          32.85, 34.81, 36.87, 39.07, 41.39, 43.85, 46.46, 49.22,
          52.15, 55.25, 58.54, 62.02, 65.70, 69.61, 73.75, 78.14,
          82.78, 87.70, 92.92, 98.44, 104.30, 110.50, 117.07, 124.03,
          131.41, 139.22, 147.50, 156.27, 165.56, 175.41, 185.84, 196.89,
          208.60, 221.00, 234.14, 248.06, 262.81, 278.44, 295.00, 312.54,
          331.13, 350.82, 371.68, 393.78, 417.19, 442.00, 468.28, 496.13,
          525.63, 556.89, 590.00, 625.08, 662.25, 701.63, 743.35, 787.55,
          834.38, 884.00, 936.57, 992.26, 1051.26, 1113.77, 1180.00, 1250.16,
          1324.50, 1403.26, 1486.70, 1575.11, 1668.77, 1768.00, 1873.13, 1984.51,
          2102.52, 2227.54, 2360.00, 2500.33, 2649.01, 2806.53, 2973.41, 3150.22,
          3337.54, 3536.00, 3746.26, 3969.03, 4205.04, 4455.08, 4719.99, 5000.66,
          5298.01, 5613.05, 5946.82, 6300.44, 6675.08, 7072.00, 7492.52, 7938.05,
          8410.07, 8910.16, 9439.99, 10001.32, 10596.03, 11226.10, 11893.64, 12600.87
        };

        char onboards[ALL_BUTTONS][8] = {
          "Pot 1",  "Pot 2",  "Pot 3",  "Pot 4",  "Pot 5",  "Pot 6",  "Pot 7",
          "Pot 8",  "Pot 9",  "Fdr 01", "Fdr 02", "Fdr 03", "Pad 01", "Pad 02",
          "Pad 03", "Pad 04", "Pad 05", "Pad 06", "Pad 07", "Pad 08", "Pad 09",
          "Pad 10", "Pad 11", "Pad 12", "Pad 13", "Pad 14", "Pad 15", "Pad 16",
          "But 01", "But 02", "But 03", "But 04", "But 05", "But 06", "But 07",
          "But 08", "But 09", "But 10", "But 11", "But 12", "But 13", "But 14",
          "But 15", "But 16", "But 17", "But 18", "Cfd",    "Jk X",   "Jk Y"};

        char ch_lbl_buffer[4]{};
      /*
        //TODO: implement in notespy
        void notefreqloop() {
          if (notefreq1.available()) {
            float notep = notefreq1.read();
            float probz = notefreq1.probability();
            //  dm.pseudoconsole("Note: %3.2f | Probability: %.2f\n", notep, probz);
          }
        }
        */

      static void show();
      static void apply_alt_ctl();
      static void set_alternative_rota();
      static void set_in_source();
      static void settings_nav_zero();
      static void OnBoardVpanelAction();
      static void OnBoardVpanelSelector();
      static void OnBoardVpanel();
      static void arpegiatorVpanelAction();
      static void arpegiatorVpanelSelector();
      static void arpegiatorVpanel();
      static void makesettingslist();
      static void settings_nav_one();
      byte getnotefromfreq(float lafreq);
      byte getclosestnote(byte lei, float lafreq);
      static void printlanote();
      //TODO: unused
      static void metronomer();
      void unplug_notefreq_from_ampL();
      void replug_notefreq_from_ampL();
      static void toggle_echo_midi();
      static void toggle_freeze_midi();
      static void set_synth_midi_ch();
      static void set_sampler_midi_ch();
      static void toggle_digital_analog();
      static void set_tap_note();
      static void set_bpms_interval();
      static void set_chord_mode();
      static void toggle_ext_clock();
      static void toggle_note_spy();
      static void set_audio_source();
      static void toggle_midi_out();
      static void (*_settings_menu[settings_labels_count])();
      //static constexpr void (*_nav_fx[SP_LABELS_COUNT])() = {&fx_nav_one, &fx_nav_one, &fx_nav_one, &fx_nav_one, &fx_nav_one};

  private:
    static SettingsMenuRouter* self;
};

extern SettingsMenuRouter _st;