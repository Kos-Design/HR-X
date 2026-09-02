#pragma once
#include <stdint.h>
#include "Cablages.h"

struct BigBuffers {
    float notestofreq[128];
    short granularMemory[FXS_COUNT][GRANULAR_MEMORY_SIZE];
    short chorusdelayline[FXS_COUNT][CHORUS_DELAY_LENGTH];
    short flangedelay[FXS_COUNT][FLANGE_DELAY_LENGTH];
    int16_t rolling_queue_buff[128];
    char Flashsamplename[999][13];
    char consolemsg[10][32];
    char pleasewaitarray[10][32];
    uint8_t pots_controllers[32][32][2];
    uint8_t recorded_ccs[32];
};

extern BigBuffers bb;

class FxBus {
  public:

    FxBus();

    int delaymultiplier = 55;
    int flangeoffset = FLANGE_DELAY_LENGTH / 4;
    int flangedepth = FLANGE_DELAY_LENGTH / 4;

    float bqslope[STAGES_BQ] = {1.0,1.0,1.0,1.0};
    float bqgain[STAGES_BQ] = {0.0,0.0,0.0,0.0};
    float bqfreq[STAGES_BQ] = {0.0,0.0,0.0,0.0};
    float filterzgainz[3] = {0.0,0.0,0.0};
    float filterzfreq = 1000.0;
    float filterzreso = 0.7;
    float filterzoctv = 1.0;
    double flangefreq = 0.5;

    uint16_t premixesMto_index = 1000 ;
    uint16_t fxcording_index = 1000 ;
    // [lestage] freq slope gain
    uint8_t bqVpot[STAGES_BQ][3] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
    uint8_t bqtype[STAGES_BQ] = {0,0,0,0};
    // cutoff, resonance, octave
    uint8_t ffilterzVknobs[3] = {0,0,0};
    uint8_t flangerVknobs[3] = {0,0,0};
    uint8_t delayVknobs[3] = {0,0,0};
    //LowPass, BandPass, HighPass levels
    uint8_t mixffilterzVknobs[3] = {0,0,0};
    uint8_t reverbVknobs[2] = {0,0};
    uint8_t bitcrusherVknobs[2] = {0,0};
    uint8_t granularVknobs[2] = {0,0};
    uint8_t bqstage = 0;
    uint8_t chorusvoices = 2;
    uint8_t LFOonfilterz = 3;
    uint8_t chorusVknobs = 0;
    uint8_t plugged_fx = ALL_FX_TYPES-1;
    uint8_t f_index = 0 ;
    bool granular_shifting = 0;
    bool granular_freezing = 0;
    bool active = 0 ;

    void route_fx(byte selected_fx_type);
    void plug_fx_line(byte selected_fx_type);
    void stopdelayline();
    void unplug_fx_line();

};

struct Preset {
    FxBus fx[FXS_COUNT];

    int32_t millitickinterval = 115;
    //Atk Delay, Attack, Hold, Decay, Sustain, Release
    int32_t adsrlevels[6] = {0, 5, 0, 100, 0, 50};

    int32_t midiknobassigned[128];
    int32_t Sampleassigned[128];
    int16_t arbitrary_waveforms[OSCS_COUNT][256] ;
    uint16_t pot_assignements[ALL_BUTTONS];

    //individual frequency multipliers for the oscillators
    float wavesfreqs[OSCS_COUNT] = {1.0f, 1.0f, 0.5f};

    //doesn't seem to affect arbitrary waveforms... :(
    float arbitrary_maxF[OSCS_COUNT] = { 172.0, 172.0, 172.0} ;

    //individual frequency multipliers for the LFOs
    float LFOHz[OSCS_COUNT] = {1.0f,1.0f,1.0f};

    uint16_t ordered_pots[15] = {
        10, 12, 11, 16, 15, 14, 19, 18, 17, 13,
        24, 22, 23, 21, 20
    };

    uint16_t le303filterzfreq = 14000;
    GlideMode glideMode = Off;
    uint8_t le303filterzgainz[3] = {127,0,0};
    //0 is Off, 1-> Waveform, 2-> FM Waveform, 3->Drum, 4->String
    uint8_t audio_obj_type[OSCS_COUNT] = {1,1,1};
    uint8_t le303filterzreso = 70;
    uint8_t panLs = 64;
    uint8_t phaselevelsL[OSCS_COUNT] = {0,0,0};
    uint8_t cut_off_slope = 100;
    //unused until 303 refactor
    uint8_t resonance_slope = 1;
    // cutoff, resonance, octave
    uint8_t le303ffilterzVknobs[3] = {48,32,0};
    // LP BP HP
    uint8_t mixle303ffilterzVknobs[3] = {127,0,0};
    uint8_t le303filterzwet = 127;
    uint8_t preampleswaves = 64;
    //0: exponential | 64: linear | 127: log-like
    uint8_t glide_slope = 64;
    uint8_t portamento_height = 70;
    uint8_t portamento_time = 60;
    bool arpegiatorOn = true;
    uint8_t arpegiatortype = 7;
    uint8_t arpeglengh = 0;
    uint8_t arpegmode = 4;
    uint8_t arpegnumofnotes = 7;
    uint8_t arpegstartoffset = 0;
    uint8_t arpeggridC = 0;
    uint8_t arpeggridS = 0;
    uint8_t out_midichannel = 3 ;
    bool digitalplay = false;
    uint8_t chordson = 1;
    bool SendMidiOut = true;

    // 6 is Off
    uint8_t lasetchord = 6;
    //midi cc notes controlling navigation
    uint8_t alt_nav[4] = {106,107,110,111};
    //wetness for: synth, sampler, audio In
    uint8_t wetins[3] = {64,64,64};
    uint8_t synthmidichannel = 16;
    uint8_t samplermidichannel = 8;
    uint8_t tapnote = 3;

    uint8_t vPots[17];
    uint8_t smixervknobs[16] = {
        127,127,127,127,
        127,127,127,127,
        127,127,127,127,
        127,127,127,127
    };

    uint8_t WetMixMasters[4] = {0,0,0,0};
    uint8_t mixlevelsM[4] = {127,127,38,127};
    uint8_t FMmodulated[OSCS_COUNT] = {0,0,0};
    uint8_t mixlevelsL[OSCS_COUNT] = {126,64,64};
    uint8_t Waveformstyped[OSCS_COUNT] = {1,0,1};
    //64 is center 0 for -1  +1 range
    uint8_t wave1offset[OSCS_COUNT] = {64,64,64};
    uint8_t LFOlevel[OSCS_COUNT] = {0,0,0};
    uint8_t LFOformstype[OSCS_COUNT] = {0,0,0};
    uint8_t LFOphase[OSCS_COUNT] = {0,0,0};
    uint8_t LFOoffset[OSCS_COUNT] = {64,64,64};
    bool LFOsync[OSCS_COUNT] = {false,false,false};
    bool externalticker = 0;

    //midi channels used for the built-in buttons handled by the multiplexer
    uint8_t but_channel[ALL_BUTTONS] = {
        1,1,1,1,1,1,1,1,1,1,1,1,
        16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
        8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
        1,1,1
    };
    //midi default velocity used for the built-in buttons handled by the multiplexer
    uint8_t but_velocity[ALL_BUTTONS] = {
        127,127,127,127,127,127,127,127,127,127,127,127,
        127,127,127,127,127,127,127,127,127,127,127,127,
        127,127,127,127,
        64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
        127,127,127
    };
    //midi channels of the pots used for the built-in pots handled by the multiplexer
    uint8_t muxed_channels[15] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    // virtual pots available for keyboardless control

    uint8_t oscilloscope_tscale = 5;
    uint8_t osc_framerate = 33 ;
    uint8_t osc_refresher_period = 2 ;
    uint16_t period_303 = 96;


};

extern Preset gg ;

extern const unsigned char menuBG[];
extern const unsigned char wavesbg2[];
extern const unsigned char moonwave[];
extern const unsigned char samplehold[];
extern const unsigned char trianglewave[];
extern const unsigned char squarewave[];
extern const unsigned char variabletriangle[];
extern const unsigned char arbitrarywave[];
extern const unsigned char reversesawtoothwave[];
extern const unsigned char pulsewave[];
extern const unsigned char sawtoothwave[];
extern const unsigned char sinewave[];
extern const uint8_t lesformes[9];
extern const char* lelabelw[12];
extern const unsigned char *_img[12];
