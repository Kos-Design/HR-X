#pragma once

#include <Arduino.h>

class FilesLister{
    static const byte max_displayables = 6; //displayables lines
    public:
        FilesLister(const char *main_folder, const char *base_filename, const char *file_extension, void (*menu_labels_method)(), byte navranger);

        const char *folder_dir;
        const char *basenamer;
        const char *extension;
        void (*home)();
        byte home_navrange;
        size_t base_char_count;
        int left_margin = 80;
        int top_margin = 16;
        int v_spacer = 10 ;
        //only lists files with 00.ext suffix as it extracts the basename to only deal with their respective numbers.
        // can't work on normal files not following this naming format yet.
        byte files_counter = 0 ;
        byte displayable_offset = 0 ;
        String files_displayable[max_displayables];
        //stores files suffixes numbers only
        byte files_indexed[99];
        bool new_file_mode = 0;
        //the files list should be responding to shifting in navlevel r_nav and display in r_nav-1(navlevel of the menu instancer)
        byte r_nav = 2;
        String get_file_name(byte number);
        String get_current_file_path(byte f_index);
        String make_full_file_name(byte number);
        String get_new_file_name();
        void nav_zero();
        void nav_one(byte save_lbl_idx,byte lbl_navlevel);
        void refresh_files_names();
        void display_files_list();
        void list_files();
};

