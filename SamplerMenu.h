#pragma once
#include "MenuClasses.h"
#include "FilesLister.h"

class SamplerMenuRouter : public SectionHolder {
    public:
        SamplerMenuRouter();
        FilesLister *catalog;
        String newmkdirpath = "SOUNDSET/MABANK01" ;
        const byte FlashChipSelect = 6;
        char samplefoldersregistered[99][SP_NAME_MAX]{};
        char sampledirpath[99] = {"SOUNDSET/"};
        char samplebase[99][999][9]{};
        int sizeofsamplefolder[99]{};
        int sampledirsregistered = 0;
        bool samplesselected[99][999]{};
        int numberofsamplesselected[99]{};
        bool samplesfoldersselected[99]{};
        int numofsamplesfoldersselected = 0;
        char Flashsamplebase[999][9]{};
        bool Flashsamplesselected[999]{};
        int numberofFlashsamplesselected = 0;
        int numberofFlashfiles = 0;
        static void voidsampledirpath();
        String make_full_dir_name(byte number,String base_path_dir);
        static void sampler_nav_two();
        static void sampler_nav_one();
        static void sampler_nav_zero();
        static void show();
        String get_new_dir_name(String base_path_dir);
        static void smixerVpanelAction();
        static void clearsizeofsamplefolder();
        static void initializesamplebase();
        String lower_extension_case(String f_name);
        bool test_flash_sample_name(String f_s_name);
        static void listSoundset();
        static void smixerVpanel();
        static void dolistsamplermenu();
        String samplefullpath(int lefolder, int lefile);
        static void addtofolderix(char *lepathtoadd, int ix);
        static void setupsamplefoldersregistered();
        static void setlefilenamed(int lefolder, int lefile, char *lefname);
        static void playsamplepreview();
        static void preview_flash_assignee();
        static void copybacklaflashfile(int leflashfile);
        static void copyflashtoSD();
        static void domkdir();
        static void Assingexplorer();
        static void samplerexplorer();
        static void Flashsamplerexplorer();
        static void showsamplerfolderList();
        static void showsamplerfilesList();
        static void showFlashSamplesList();
        static void drawtickboxflashBIG(int lestartx, int lestarty, int lasizex, int lasizey,
                                int lacolor, int lefile);
        static void drawtickboxflashtitle(int lestartx, int lestarty, int lasizex, int lasizey,
                                  int lacolor, int lefile);
        static void drawtickboxfolderBIG(int lestartx, int lestarty, int lasizex, int lasizey,
                                  int lacolor, int lefolder);
        static void drawtickboxfoldertitle(int lestartx, int lestarty, int lasizex,
                                    int lasizey, int lacolor,
                                    int lefolder);
        static void drawtickboxincanvasBIG(int lestartx, int lestarty, int lasizex,
                                    int lasizey, int lacolor,
                                    int lefolder, int lefile);
        static void drawtickboxincanvastitle(int lestartx, int lestarty, int lasizex,
                                      int lasizey, int lacolor,
                                      int lefolder, int lefile);
        static void addtoFlashsamplelist(char *lesample);
        static void initializeFlashsamplename();
        static void initializesamplesfoldersselectedlist();
        static void initializeFlashsamplesselected();
        static void initializesamplesselectedlist();
        static void drawFlashSamplesList();
        static void drawsamplerfilesList();
        static void drawSamplerFoldersList();
        static void dolistLoadSampleMenu();
        static void dolistDelSampleMenu();
        static void dolistAssignSampleMenu();
        static void Doautoassign();
        static void doclearassign();
        static void doConfirmmkdir();
        static void doConfirmClearassign();
        static void doConfirmClearList();
        static void doConfirmautoassign();
        static void doConfirmDelsamples();
        static void doConfirmClearSelectedFlashList();
        static void doConfirmRemoveAll();
        static void doConfirmLoadsamples();
        static void RemoveAllfromFlash();
        float eraseBytesPerSecond(const unsigned char *id);
        static void DelSelectedFlashSamples();
        static void addfolderstoselectionset();
        static void loadSelectedSamples();
        static void loadSampledSound();
        static void listFlashfiles();
        //unused
        static void getavailablespace();
        static void Sampleassigner();
        static void listsamplesassigner();
        static void samplesetter();
        static void listsamplesassigner2();
        static void listSoundsetsubdir(int ledir);
        static void makesoundsetfullpathfromchars(int eldir);
        static void dosoundlist();
  //TODO: refactor nav routing after using fileslister
        static constexpr void (*_route_nav[7])() = {&sampler_nav_zero, &sampler_nav_one, &sampler_nav_two, 
                                                    &sampler_nav_two, &sampler_nav_two,&sampler_nav_two, &sampler_nav_two};
                                    
        
    private:
        
        static constexpr void (*_nav_sampler[SP_LABELS_COUNT])() = {&dolistLoadSampleMenu, &dolistDelSampleMenu, &dolistAssignSampleMenu, &smixerVpanel};
        static SamplerMenuRouter* self;
};

extern SamplerMenuRouter _sp;
