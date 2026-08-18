#pragma once
#include "Constants.h"
#include <Arduino.h>

void waveformize(byte l_index,byte osc_idx,float currentFreq,float targetFreq,byte velocity);
void FMformize(byte l_index,byte osc_idx,float currentFreq,float targetFreq,byte velocity);
void drumize(byte l_index,byte osc_idx,float currentFreq,float targetFreq,byte velocity);
void stringize(byte l_index,byte osc_idx,float currentFreq,float targetFreq,byte velocity);
void waveform_refresh(byte l_index,byte osc_idx,float currentFreq,byte velocity);
void FMform_refresh(byte l_index,byte osc_idx,float currentFreq,byte velocity);
void drum_refresh(byte l_index,byte osc_idx,float currentFreq,byte velocity);

class SynthLiner {
  public:
    byte l_index = 0 ;
    bool activated = 0 ;
    byte note = 0 ;
    byte previous_note = 0 ;
    byte velocity = 0 ;
    byte sloper_step = 0;
    float targetFreq = 0.0;
    float currentFreq = 0.0;
    float steps = 0.0 ;
    bool f303 = 0 ;
    int totalUpdates = 0;
    int currentUpdate = 0;
    float startFreq = 0.0;

    SynthLiner(byte line_index = 0 );

    void liner_on(byte data1, byte data2);
    void update_line_old();
    void update_line();
    void setPortamentoTime();
    void setfreqWavelines();
    void activateWavelines();
    void refreshWavelines();
    void liner_off();
    static constexpr void (*audio_obj_refresher[3])(byte,byte,float,byte) = {&waveform_refresh, &FMform_refresh, &drum_refresh};

};

extern SynthLiner *synth_lines[SYNTH_LINERS_COUNT];

class FlashLiner {
  public:
    FlashLiner(byte line_index = 0 );

    byte l_index = 0 ;
    bool activated = 0 ;
    byte note = 0 ;
    byte velocity = 0 ;

    String playable_file = "";

    void liner_on(byte data1, byte data2);
    void liner_off();
};

extern FlashLiner *flash_lines[FLASH_LINERS_COUNT];

class ActiveLinesRegister {
    public:
      ActiveLinesRegister();
      int synth_lines_active = 0 ;

      void add_active_synth(SynthLiner *snth);
      void remove_inactive_synth(SynthLiner *snth);
      void init_synth_liners();
      void init_flash_liners();
      SynthLiner *active_synths[SYNTH_LINERS_COUNT];
};

extern ActiveLinesRegister _rg;
