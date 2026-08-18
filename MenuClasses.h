#include "FilesLister.h"
#pragma once
#include "Presets.h"

#include <Arduino.h>
#include <Audio.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
class FilesLister;
struct CcCalls {
    const char *name;
    void (*tweaker)(byte);
};

extern const CcCalls ctl[] ;
class Adafruit_SSD1306;
class GFXcanvas1;
extern Adafruit_SSD1306 display;

extern GFXcanvas1 canvasBIG;
extern GFXcanvas1 canvastitle;

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
        float eqRawBars[NUM_BARS]{};
        uint8_t eqBars[NUM_BARS]{};
        float fftGain[NUM_BARS] = {
            15.0f,17.7f,45.82f,58.825f,
            65.2f,92.575f,98.6f,106.92f,
            
            117.12f,127.255f,136.5f,
            144.71f,151.9f,157.95f,
            
            163.15f,167.25f,180.0f,181.47f,
            181.94f,181.44f,180.0f, 193.8f,

            200.5f, 206.9f, 213.0f, 218.8f,
            224.3f, 229.5f, 234.4f, 239.0f,

            243.2f, 247.1f, 250.6f, 253.8f,
            256.6f, 259.0f, 260.9f, 262.5f,

            263.6f, 264.3f, 264.6f, 264.5f,
            263.9f, 262.9f, 261.5f, 259.7f,

            240.0f, 249.6f, 259.3f, 269.3f,
            279.5f, 289.8f, 300.3f, 311.1f,
            
            322.0f, 333.1f, 344.4f, 355.9f,
            367.5f, 379.4f, 391.4f, 403.6f
        };

        int rota_enc_new_pos = 0;
        int rota_enc_count = 0;
        int rota_old_Pos = -999;
        int rota_old_vrai_Pos = 0;

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
        void printit();
        void clean_title_2_1(void);
        void doConfirmpanel(char *letitlemsg);
        void display_oscilloscope();
        void stop_spectro();
        void start_spectro();
        void oscilloscope_loop();
        void UpdateSpectrum();
        void DrawSpectrum64();
        void dodisplayplayhead();
        void initializelapleasewaitarray();
        void shiftlapleasewaitarray();
        void setlapleasewaitarray(int consoleline, char *lemsg);
        void pleasewait(float lewait, float letotwait);
        void pseudoconsole(const char *lemsg,bool new_lines=true);
        void initializeconsolemsg() ;
        void shiftconsolemsgarray();
        void setleconsolemsg(int consoleline, char *lemsg);
        void printnoteon(byte channel, byte data1, byte data2);
        void print_memory_usage();
        void reinitsublevels(byte fromlei);
        void clean_title_1_1(void);
        void clean_title_1_2(void);
        void clean_title_2_2(void);
        void clean_title_1(void);
        void drawtransport();


        // rotaencoder library increments 4 steps for 1 and keeps absolute count
        void evalrota();
        void evalinputs();
        void printassignedmidi(int lemidiassknob);
        void main_panel(const char* const*,int,int);
        void show(void);
        void dodisplay(void);
        void returntonav(byte lelevel, byte lanavrange = lv.navrange,byte t_vraipos = lv.rota_true_pos);

        static void (*root_route[10])();

    private:
        void _displayleBGimg(const unsigned char *img);
        void _setupscreen_ILI(void);
};

extern DisplayManager dm;

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
        static void le303filterzWet();
        static void Wavespreamp303controls();
        static void setle303filterpass(int linei);
        static void le303filtercontrols();

    private:
        byte *wmixer_tmp_pointers[12];
        byte wmixer_tmp_values[12];
        static GlobalMixer* self;
        
};
extern GlobalMixer _mx;

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

extern SequencerClocker clocker;

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

extern DisplayConsoler consoler;

