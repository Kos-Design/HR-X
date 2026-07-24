#pragma once

#include <Arduino.h>

extern bool locked_fileing;

class FilesLister{
    static const byte max_displayables = 6; //displayables lines
    public:
        FilesLister(const char *main_folder, const char *base_filename, const char *file_extension, void (*menu_labels_method)(), byte navranger);

        char folder_dir[32];
        const char *basenamer;
        const char *extension;
        void (*home)();
        byte home_navrange;
        size_t base_char_count;
        int left_margin = 80;
        int tmp_counter = 0;
        char tmp_folder[32];

        int top_margin = 16;
        int v_spacer = 10 ;
        bool folders_mode = false;
        bool folders_already_listed = false;
        //only lists files with 00.ext suffix as it extracts the basename to only deal with their respective numbers.
        // can't work on normal files not following this naming format yet.
        byte files_counter = 0 ;
        byte folders_counter = 0 ;
        byte free_counter = 0 ;
        byte displayable_offset = 0 ;
        String files_displayable[max_displayables];
        String folders_displayable[max_displayables];

        //stores files suffixes numbers only
        byte files_indexed[99];
        char folders_indexed[99][16];
        char free_files[99][16];
        String folder_selected;
        bool new_file_mode = 0;
        //the files list should be responding to shifting in navlevel r_nav and display in r_nav-1(navlevel of the menu instancer)
        byte r_nav = 2;
        String get_file_name(byte number);
        String get_current_file_path(byte f_index);
        String make_full_file_name(byte number);
        String get_new_file_name();
        void deleteFile();
        void deleteFileGeneric(const char*);
        void copyFile();
        void copyFileGeneric(const char* _origin_file,const char* _target_file) ;
        void nav_zero();
        void make_temp_folders();
        String get_full_tmp_file_path(byte);
        String get_new_tmp_name();
        void nav_one(byte save_lbl_idx,byte lbl_navlevel);
        void refresh_files_names();
        void refresh_folders_names();
        void make_sub_folder(const char *base_folder, const char *subfoldee);
        void display_files_list();
        void display_folders_list();
        void list_files();

};

