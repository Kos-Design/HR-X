#pragma once
#include "MenuClasses.h"
#include "FilesLister.h"

struct SelectableSample {
    uint16_t folder_n;
    uint16_t file_n;
};

class SamplerMenuRouter : public SectionHolder {
    public:
        SamplerMenuRouter();
        
        static void voidsampledirpath();
        bool is_selected_in_folder(uint16_t);
        bool make_full_dir_name(const char *base_path_dir, char *buffer, size_t buffer_size,byte number=0);
        static void sampler_nav_two();
        static void sampler_nav_one();
        static void sampler_nav_zero();
        static void show();
        bool get_new_dir_name(const char *base_path_dir, char *buffer, size_t buffer_size);
        static void smixerVpanelAction();
        static void clearsizeofsamplefolder();
        static void initializesamplebase();
        bool lower_RAW_extension_case(const char *f_name, char *buffer, size_t buffer_size);
        static void listSoundset();
        static void smixerVpanel();
        static void dolistsamplermenu();
        bool samplefullpath(int lefolder, int lefile, char *buffer, size_t buffer_size);
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

        static void add_folder_selection(uint16_t folder_);
        bool is_folder_selected(uint16_t folder_);
        static void remove_folder_from_selection(uint16_t folder_);

        //unused
        static void getavailablespace();
        bool is_selected_in_folder(uint16_t ,uint16_t);
        static void remove_file_from_selection(uint16_t ,uint16_t );
        static void add_file_selection(uint16_t ,uint16_t );
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

        FilesLister *catalog;
        char newmkdirpath[32] = "SOUNDSET/MABANK01" ;
        const byte FlashChipSelect = 6;
        char samplefoldersregistered[99][SP_NAME_MAX]{};
        char sampledirpath[99] = {"SOUNDSET/"};
        char samplebase[99][999][9]{};
        int sampledirsregistered = 0;
        char Flashsamplebase[999][9]{};
        bool Flashsamplesselected[999]{};
        int numberofFlashsamplesselected = 0;
        int numberofFlashfiles = 0;
        uint8_t samples_selected_count = 0;
        uint16_t sizeofsamplefolder[99]{};
        uint8_t folders_selected_count = 0;

        uint8_t folders_selected[256]{};
        SelectableSample samples_selected[256]{};
        
    private:

        static constexpr void (*_nav_sampler[SP_LABELS_COUNT])() = {&dolistLoadSampleMenu, &dolistDelSampleMenu, &dolistAssignSampleMenu, &smixerVpanel};
        static SamplerMenuRouter* self;
};

extern SamplerMenuRouter _sp;
