#include <stdint.h>
#pragma once

#include <Arduino.h>
#include "Constants.h"

class FilesLister{
    public:
        static const uint8_t max_displayables = 6; //displayables lines
    
        FilesLister(const char *main_folder, const char *base_filename, const char *file_extension, void (*menu_labels_method)(), uint8_t navranger);

        char folder_dir[32];
        const char *basenamer;
        const char *extension;
        void (*home)();
        uint8_t home_navrange;
        size_t base_char_count;
        int left_margin = 80;
        int tmp_index = 0;
        char tmp_folder[36];
        byte tmp_count = 0;
        int top_margin = 16;
        int v_spacer = 10 ;
        bool folders_mode = false;
        bool folders_already_listed = false;
        //only lists files with 00.ext suffix as it extracts the basename to only deal with their respective numbers.
        // can't work on normal files not following this naming format yet.
        uint8_t files_counter = 0 ;
        uint8_t folders_counter = 0 ;
        uint8_t free_counter = 0 ;
        uint8_t displayable_offset = 0 ;
        String files_displayable[max_displayables];
        String folders_displayable[max_displayables];

        //stores files suffixes numbers only
        uint8_t files_indexed[99];
        char folders_indexed[99][16];
        char free_files[99][16];
        String folder_selected;
        bool new_file_mode = 0;
        //the files list should be responding to shifting in lv.navlevel r_nav and display in r_nav-1(lv.navlevel of the menu instancer)
        uint8_t r_nav = 2;
        String get_file_name(uint8_t number);
        String get_current_file_path(uint8_t f_index);
        String make_full_file_name(uint8_t number);
        String get_new_file_name();
        void deleteFile();
        void deleteFileGeneric(const char*);
        void copyFile();
        void copyFileGeneric(const char*,const char*);
        void move_file(const char*,const char* );
        void nav_zero();
        void make_temp_folders();
        String get_full_tmp_file_path(uint8_t);
        String get_new_tmp_name(bool increment = true);
        void nav_one(uint8_t save_lbl_idx,uint8_t lbl_navlevel);
        void refresh_files_names();
        void refresh_folders_names();
        void make_sub_folder(const char *base_folder, const char *subfoldee);
        void display_files_list();
        void display_folders_list();
        void list_files();

};

