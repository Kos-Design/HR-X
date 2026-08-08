#pragma once

#include <Arduino.h>
#include <Audio.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

struct CcCalls {
    const char *name;
    void (*tweaker)(byte);
};

const unsigned short all_buttonns = 49;
constexpr uint8_t OSCS_COUNT = 3;
const int fxs_count = 3;
const int bqstagesnum = 4;
const int sizeopremixtoM = 9 * fxs_count;
const int sizeopremixWtoM = 9 * fxs_count;
const int sizeofxcords = 9 * fxs_count * 2 * 3;
constexpr uint8_t SCREEN_ADDRESS = 0x3C;
constexpr uint8_t SN_MENU_LABELS_COUNT = 6 ;
constexpr int SYNTH_LINERS_COUNT = 6 ;
const int available_track_types = 2;
const int FLASH_LINERS_COUNT = 16;
const int sampler_labels_count = 4;
const int pbars = 32;

extern const CcCalls ctl[] ;
class Adafruit_SSD1306;
class GFXcanvas1;
extern Adafruit_SSD1306 display;
extern int navlevel;
extern int navrange;
extern const unsigned char menuBG[];
extern int sublevels[9];
extern int previousnavlevel;

extern bool patternOn;
extern bool stoptick;
extern bool recordCC;
extern bool patrecord;

void call_sn_show();
void call_lf_show();
void call_rd_show();
void call_sg_show();
void call_pt_show();
void call_st_show();
void call_fx_show();
void call_sp_show();
void call_wf_show();
void call_ps_show();
void returntonav(byte,byte,byte);

extern int retroaction;
extern bool temp_buff_armed ;
extern GFXcanvas1 canvasBIG;
extern GFXcanvas1 canvastitle;
extern byte oscillator;
extern AudioAmplifier ampL;
extern AudioAmplifier ampR;
extern AudioMixer4 mixerWAll;
extern AudioMixer4 flashMastermix;
extern AudioMixer4 WetMixMasterL;
extern AudioMixer4 WetMixMasterR;
extern AudioMixer4 MasterL1;
extern AudioMixer4 MasterR1;
extern AudioMixer4 FXBusL;
extern AudioMixer4 FXBusR;
extern AudioMixer4 *Wavesmix[6];

struct MidiEventer{
    byte channel;
    byte note;
    byte velocity;
};

enum GlideMode : uint8_t {
    Off,
    Portamento,
    ReversePortamento,
    PitchAttack,
    ReversePitchAttack
};

enum ADSR : uint8_t  {
    AttackDelay,
    Attack,
    Hold,
    Decay,
    Sustain,
    Release
};

struct Preset {
    int32_t millitickinterval = 115;
    //Atk Delay, Attack, Hold, Decay, Sustain, Release
    int32_t adsrlevels[6] = {0, 5, 0, 50, 100, 750};
    int32_t pot_assignements[all_buttonns]{};
    int32_t ordered_pots[15] = {
        10, 12, 11, 16, 15, 14, 19, 18, 17, 13,
        24, 22, 23, 21, 20
    };
    int32_t midiknobassigned[128]{};
    int32_t Sampleassigned[128]{};

    //individual frequency multipliers for the oscillators
    float wavesfreqs[OSCS_COUNT] = {1.0f, 1.0f, 0.5f};
    //doesn't seem to affect arbitrary waveforms... :(
    float arbitrary_maxF[OSCS_COUNT] = { 172.0, 172.0, 172.0} ;

    //individual frequency multipliers for the LFOs
    float LFOHz[OSCS_COUNT] = {1.0f,1.0f,1.0f};
    int16_t arbitrary_waveforms[OSCS_COUNT][256]{} ;
    GlideMode glideMode = PitchAttack;

    uint16_t le303filterzfreq = 14000;
    // 1-byte aligned
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
    uint8_t le303ffilterzVknobs[3]{};
    // LP BP HP
    uint8_t mixle303ffilterzVknobs[3] = {127,0,0};
    uint8_t le303filterzwet = 127;
    uint8_t preampleswaves = 64;
    //0: exponential | 64: linear | 127: log-like
    uint8_t glide_slope = 64;
    uint8_t portamento_height = 70;
    uint8_t portamento_time = 60;
    bool arpegiatorOn = false;
    uint8_t arpegiatortype = 8;
    uint8_t arpeglengh = 0;
    uint8_t arpegmode = 4;
    uint8_t arpegnumofnotes = 7;
    uint8_t arpegstartoffset = 0;
    uint8_t arpeggridC = 0;
    uint8_t arpeggridS = 0;
    bool digitalplay = false;
    bool chordson = false;
    bool SendMidiOut;

    // 6 is Off
    uint8_t lasetchord = 6;//midi cc notes controlling navigation
    uint8_t alt_nav[4] = {106,107,110,111};
    //wetness for: synth, sampler, audio In
    uint8_t wetins[3] = {64,64,64};
    uint8_t synthmidichannel = 16;
    uint8_t samplermidichannel = 8;
    uint8_t tapnote = 3;
    uint8_t smixervknobs[16] = {
        127,127,127,127,
        127,127,127,127,
        127,127,127,127,
        127,127,127,127
    };
    uint8_t plugged_fx_type[3];
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
    uint8_t but_channel[all_buttonns] = {
        1,1,1,1,1,1,1,1,1,1,1,1,
        16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
        8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
        1,1,1
    };
    //midi default velocity used for the built-in buttons handled by the multiplexer
    uint8_t but_velocity[all_buttonns] = {
        127,127,127,127,127,127,127,127,127,127,127,127,
        127,127,127,127,127,127,127,127,127,127,127,127,
        127,127,127,127,
        64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
        127,127,127
    };
    //midi channels of the pots used for the built-in pots handled by the multiplexer
    uint8_t muxed_channels[15] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    // virtual pots available for keyboardless control
    uint8_t vPots[17];

};
extern Preset gg ;

class SectionHolder{
    public:
        struct MenuPager{ byte value1; byte value3; byte value2; };
        byte relative_navlevel;
        //max absolute as it should be tested against the relative one
        byte max_navlevel = 5;
        MenuPager sublevels_address = {0,0,0};
        byte home_navrange ;
        void set_home(void (*_cb)());

    private:
        void (*_home)() = nullptr;
};

class DisplayManager{
    public:
        bool ILI_128x64 = true;
        void display_home(void);
        void setupscreen(void);
        void displayleBGimg(const unsigned char *img);
        void printlabel(char *toprint);
        void displaymenu(void);
        void clear_buffs(void);
        void clear_buffs_1_1(void);
        void clear_buffs_2_1(void);
        void clear_buffs_2_2(void);
        void clear_3(void);
        void clean_title_2(void);
        void clean_title_2_1(void);
        void clean_title_1_1(void);
        void clean_title_1_2(void);
        void clean_title_2_2(void);
        void clean_title_1(void);
        void main_panel(const char* const*,int,int);
        void show(void);
        void dodisplay(void);
        static void (*root_route[10])();

    private:
        void _displayleBGimg(const unsigned char *img);
        void _setupscreen_ILI(void);
};

class GlobalMixer : public SectionHolder {
    public:
        GlobalMixer(AudioControlSGTL5000& shield);
        static void show(void);
        static void showmixerwaves(void);
        static void setmastersmixlevel(int lebus);
        static void restore_wmixer_from_temp();
        static void set_wmixer_buff_temp();
        static void wetmixmastercontrols(void);
        static void set_dry_mix(int lebus);
        static void actionwet1mixer(int linstru);
        static void action_dry_mix(int linstru);
        static void actionwmixer(byte vknob);
        static void actionwmixerM(int lebus);
        static void setwavemixlevel();

    private:
        byte *wmixer_tmp_pointers[12];
        byte wmixer_tmp_values[12];
        static GlobalMixer* self;
        AudioControlSGTL5000& MixShield;
};

class SequencerClocker : public AudioStream {
    public:
        SequencerClocker();
        void setBPM(float bpm);
        void setPPQN(uint8_t ppqn);
        void attach_96(void (*cb)());
        virtual void update() override;
    
    private:

        void calculatePPQN();
        float  _bpm = 120.0f;
        uint8_t _divisionsPerQuarter = 4;
        uint8_t _PPQN = 96 ;
        double _samplesPerTick = 0;
        double _sampleAccumulator = 0;
        void (*_callback_96)() = nullptr;
};

class DisplayConsoler : public Print {
public:
    DisplayConsoler();

    void clearing();
    void refresh();
    void wipe();
    size_t write(uint8_t c) override;

private:
    void newLine();
    void scroll();
    void drawChar(char c);

    static constexpr uint8_t SCREEN_WIDTH  = 128;
    static constexpr uint8_t SCREEN_HEIGHT = 64;

    static constexpr uint8_t CHAR_W = 6;     // Adafruit default font
    static constexpr uint8_t CHAR_H = 10;    // 8px glyph + spacing

    static constexpr uint8_t COLS = SCREEN_WIDTH / CHAR_W;   // 21
    static constexpr uint8_t ROWS = SCREEN_HEIGHT / CHAR_H;  // 6

    char _c_buff[ROWS][COLS];

    uint8_t cursorX;
    uint8_t cursorY;
};
