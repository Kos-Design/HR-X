#pragma once

#include <Arduino.h>
#include <Audio.h>
constexpr uint8_t SCREEN_ADDRESS = 0x3C;
constexpr uint8_t OSCS_COUNT = 3;
constexpr uint8_t SN_MENU_LABELS_COUNT = 5 ;
constexpr int SYNTH_LINERS_COUNT = 6 ;


class Adafruit_SSD1306;
class GFXcanvas1;
extern Adafruit_SSD1306 display;
extern int navlevel;
extern int navrange;
extern const unsigned char menuBG[];
extern int sublevels[9];
extern int previousnavlevel;
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
extern byte mixlevelsM[4];
extern byte WetMixMasters[4];
extern byte mixlevelsL[OSCS_COUNT];
extern byte wetins[3];
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
extern AudioMixer4 *Wavesmix[SYNTH_LINERS_COUNT];

//extern byte mixlevelsM[3];

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
        void clean_title_2_2(void);
        void clean_title_1(void);
        void show(void);
        void dodisplay(void);
        static void (*root_route[10])();

    private:

        void _displayleBGimg(const unsigned char *img);
        void _setupscreen_ILI(void);
        
            
};


class GlobalMixer : public SectionHolder {
  public:
    GlobalMixer(void);
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

