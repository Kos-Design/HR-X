#pragma once
#include "Presets.h"

#include <Arduino.h>
#include <Audio.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

struct CcCalls {
    const char *name;
    void (*tweaker)(byte);
};



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

struct Preset;

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
        GlobalMixer();
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

class ClockSink : public AudioStream {
    public:
        ClockSink() : AudioStream(1, inputQueueArray) {}

        void update(void) override {}

    private:
    audio_block_t *inputQueueArray[1];
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
    static constexpr uint8_t CHAR_W = 6;     // Adafruit default font
    static constexpr uint8_t CHAR_H = 10;    // 8px glyph + spacing

    static constexpr uint8_t COLS = SCREEN_WIDTH / CHAR_W;   // 21
    static constexpr uint8_t ROWS = SCREEN_HEIGHT / CHAR_H;  // 6

    char _c_buff[ROWS][COLS];

    uint8_t cursorX;
    uint8_t cursorY;
};
