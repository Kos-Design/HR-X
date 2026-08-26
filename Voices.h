#pragma once
#include "Constants.h"

void waveformize(uint8_t l_index,uint8_t osc_idx,float currentFreq,float targetFreq,uint8_t velocity);
void FMformize(uint8_t l_index,uint8_t osc_idx,float currentFreq,float targetFreq,uint8_t velocity);
void drumize(uint8_t l_index,uint8_t osc_idx,float currentFreq,float targetFreq,uint8_t velocity);
void stringize(uint8_t l_index,uint8_t osc_idx,float currentFreq,float targetFreq,uint8_t velocity);
void waveform_refresh(uint8_t l_index,uint8_t osc_idx,float currentFreq,uint8_t velocity);
void FMform_refresh(uint8_t l_index,uint8_t osc_idx,float currentFreq,uint8_t velocity);
void drum_refresh(uint8_t l_index,uint8_t osc_idx,float currentFreq,uint8_t velocity);

class SynthLiner {
  public:
    int totalUpdates = 0;
    int currentUpdate = 0;
    float startFreq = 0.0;    
    float targetFreq = 0.0;
    float currentFreq = 0.0;
    float steps = 0.0 ;
    uint8_t note = 0 ;
    uint8_t previous_note = 0 ;
    uint8_t velocity = 0 ;
    uint8_t l_index = 0 ;
    uint8_t length_in_arp = 0 ;
    uint8_t sloper_step = 0;
    uint8_t next_arp_note;
    bool arp_starter = 0;

    bool activated = 0 ;
    bool f303 = 0 ;

    SynthLiner(uint8_t line_index = 0 );

    void liner_on(uint8_t data1, uint8_t data2);
    void update_line_old();
    void update_line();
    void setPortamentoTime();
    void setfreqWavelines();
    void activateWavelines();
    void refreshWavelines();
    void liner_off();
    static constexpr void (*audio_obj_refresher[3])(uint8_t,uint8_t,float,uint8_t) = {&waveform_refresh, &FMform_refresh, &drum_refresh};

};

extern SynthLiner *synth_lines[SYNTH_LINERS_COUNT];

class FlashLiner {
  public:
    FlashLiner(uint8_t line_index = 0 );

    uint8_t l_index = 0 ;
    bool activated = 0 ;
    uint8_t note = 0 ;
    uint8_t velocity = 0 ;
    void liner_on(uint8_t data1, uint8_t data2);
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
