#pragma once
#include <stdint.h>
#include "MenuClasses.h"
#include "FilesLister.h"

class RecorderMenuRouter : public SectionHolder {
    public:
        RecorderMenuRouter();
        FilesLister *catalog;
        FsFile looper;
        const byte rec_labels_count = 6;
        float pitcher = 1.0;
        bool recorderstop = false ;
        bool recorderrecord = false ;
        bool recorderplay = false ;
        bool rec_looping = false ;
        bool pre_record = false ;
        bool just_pressed_rec = false ;
        String newloopedpath = "SOUNDSET/REC/LOOP00#L.RAW";
        String newRecpathL = "SOUNDSET/REC/RECZ00#L.RAW";
        String newRecpathR = "SOUNDSET/REC/RECZ00#R.RAW";
        bool autoassign = 0;
        bool modestereo = 0;
        bool temp_ops = 0;
        float previous_offset = 0.0f ;
        float start_zone = 0.0f ;
        float end_zone = 1.0f ;
        bool wave_buffed = 0 ;
        bool wave_selected = 0 ;
        uint8_t undoables[99]{};

        static void show();
        static void Load_raw_file();
        static void startRecording();
        static void auto_stop_rec();
        static void continue_looper();
        static void stopRecording();
        static void recordVpanelAction();
        static void recordVpanelSelector();
        static void recordVpanel();
        static void playrecordsd();
        static void playrecordsd_pathed(const char* lepath);
        static void stopplayrecordsd();
        static void check_rec_folder_path();
        static void deleteRec();
        static void recorder_menu();
        static void rec_params();
        static void rec_nav_zero();
        static void drawFoldersList();
        static void lv1_wrapper(void (*func)());
        static void records_actions();
        static void remove_record();
        static void load_record();
        static void drawWaveform(float startPos = 0.0f,float endPos   = 1.0f, uint16_t width = 128, uint16_t height = 48);
        static void select_cursor();
        static void draw_editor_zones();
        static void redraw_selection_box();
        static void zoomRange(float subStart,float subEnd);
        static void reverseSection(float startPos, float endPos);
        static void pitchSection(float startPos, float endPos, float speed);
        static void trimSection(float start_pos = 0.0f, float end_pos = 1.0f);
        static void normalizeSection(float startPos, float endPos);
        static void playSection();
        static void scheddule_wave_rebuild(bool noreturn = 0,bool noreinit = 0);
        static void fadeInSection(float startPos, float endPos);
        static void fadeOutSection(float startPos, float endPos);
        static void start_inputting_pitch();
        static void deleteSection(float startPos, float endPos);
        static void edit_record();
        static void redo();
        String get_current_temp_file();
        static void Undo();
        static void clear_temp_files();
        static void make_temp_folders();

        static constexpr void (*_route_nav[9])() = {&rec_nav_zero, &records_actions, &records_actions,
                                    &records_actions, &records_actions,&records_actions, &records_actions,
                                    &records_actions, &records_actions};

        static constexpr void  (*_nav_recs[6])() = {&recordVpanel, &load_record, &remove_record, &rec_params, &edit_record, &drawFoldersList};


  private:
    static RecorderMenuRouter* self;
};

extern RecorderMenuRouter _rd;


