
#include "FilesLister.h"
#include "MenuClasses.h"
void reinitsublevels(byte);
extern DisplayManager dm ;

FilesLister::FilesLister(const char *main_folder, const char *base_filename, const char *file_extension, void (*menu_labels_method)(), byte navranger) : 
                folder_dir(main_folder),
                 basenamer(base_filename),
                  extension(file_extension),
                   home(menu_labels_method),
                    home_navrange(navranger),
                     base_char_count(strlen(basenamer)) {
            }
String FilesLister::get_file_name(byte number) {
            char formatted_number[4] ;
            sprintf(formatted_number,"%02d",number);
            return this->basenamer + (String)formatted_number ;
        }

String FilesLister::get_current_file_path(byte f_index=0){
            return this->folder_dir + this->files_displayable[f_index] + this->extension;
        }

String FilesLister::make_full_file_name(byte number) {
            char formatted_number[4] ;
            sprintf(formatted_number,"%02d",number);
            return(String)((String)this->folder_dir+(String)this->basenamer + (String)formatted_number + this->extension);
        }

String FilesLister::get_new_file_name() {
            byte file_number = this->files_counter ;
            String new_path = make_full_file_name(file_number);
            while (SD.exists(new_path.c_str())) {
                file_number++;
                new_path = make_full_file_name(file_number);
            }
            return new_path ;
        }
void FilesLister::deleteFile() {
          if (locked_fileing)
            return;
          locked_fileing = 1 ;
          if (SD.exists((char *)(this->get_current_file_path(0)).c_str())) {
            SD.remove((char *)(this->get_current_file_path(0)).c_str());
          }
          this->list_files();
          locked_fileing = 0 ;
        }
void  FilesLister::nav_zero(){
            dm.clear_buffs();
            navrange = this->home_navrange;
            reinitsublevels(this->r_nav);
            this->display_files_list();
            this->home();
            dm.dodisplay();
        }

void  FilesLister::nav_one(byte save_lbl_idx=0,byte lbl_navlevel=1){
            this->new_file_mode = false;
            navrange = max(this->files_counter - 1, 0);
            if (sublevels[lbl_navlevel] == save_lbl_idx) {
                navrange = this->files_counter;
                this->new_file_mode = true;
            }
            this->display_files_list();
            this->home();
            dm.dodisplay();
        }

void  FilesLister::refresh_files_names() {
            for (int i = 0 ; i < max_displayables ; i++) {
                //empty spots are left at the end of the list if it is small, otherwise the names are looped
                //maybe looped list is better actually...
                this->files_displayable[i] = " ";
                if (this->displayable_offset+i < this->files_counter ) {
                    this->files_displayable[i] = this->get_file_name(this->files_indexed[this->displayable_offset+i]);
                } else if (this->files_counter >= max_displayables ){
                    this->files_displayable[i] = this->get_file_name(this->files_indexed[((this->displayable_offset+i)%this->files_counter) ]);
                }

            }
        }

void FilesLister::make_sub_folder(const char *base_folder, const char *subfoldee){
  if (!(SD.exists(base_folder))) {
    SD.mkdir(base_folder);
  }
  if (!(SD.exists(((String)base_folder+"/"+(String)subfoldee).c_str()))) {
    SD.mkdir(((String)base_folder+"/"+(String)subfoldee).c_str());
  }
}

void  FilesLister::display_files_list() {
          dm.clean_title_1_1();

          this->displayable_offset = sublevels[this->r_nav] ;
          //% this->files_counter  ;
          refresh_files_names();
          canvastitle.setCursor(left_margin, 0);
          //activate new_file_mode from instancer file actions selector
          if (this->displayable_offset == this->files_counter && this->new_file_mode) {
            canvastitle.print("New()");
          } else {
            canvastitle.print(this->files_displayable[0]);
          }
          
          if (this->displayable_offset == this->files_counter) {
            //if cursor is on new(), the size-1 elements are displayed below.
            for (int i = 0; i < max_displayables-1; i++) {
              canvasBIG.setCursor(left_margin, (v_spacer * (this->files_counter - this->displayable_offset)) + top_margin + ((i)*v_spacer));
              canvasBIG.println(this->files_displayable[i]);
            }
          } else {
            //rest of indexes after title (refresh_names handles list population)
            for (int i = 0; i < max_displayables - 1 ; i++) {
              canvasBIG.setCursor(left_margin, top_margin + i*v_spacer);
              canvasBIG.println(this->files_displayable[1 + i]);
            }
          }
        }

void  FilesLister::list_files() {
  //no lock fileing on read as it is used during locked ops, should be fine
  this->files_counter = 0;
  if (SD.exists(this->folder_dir)) {
    File opened_dir = SD.open(this->folder_dir);
    while (this->files_counter < 99) {
      File entry = opened_dir.openNextFile();
      if (!entry) {
          break;
      }
      if (!entry.isDirectory()) {
        char* named = (char*)entry.name();                    
        //maybe get ext in a separate list for mixed files type <- but that shouldn't be happening
        //perhaps for .wav and .raw but best to sort them on pc before transfer to SD
        named[strlen(named) - strlen(this->extension)] = '\0';
        //int is at X chars after prefix
        bool good_base = (bool)(strncmp((char*)entry.name(), this->basenamer, this->base_char_count) == 0) ;
        if (strlen((char*)entry.name()) != this->base_char_count+2 || !good_base ){
            Serial.println(" ");
            Serial.print(strlen((char*)entry.name()));
            Serial.print("<-- badly named !!! or is it ? we got a base name length of ");
            Serial.println(this->base_char_count+2);
            continue;
        }
        //keep only last 2 digits assuming a basename of 8 chars
        this->files_indexed[this->files_counter] = atoi(named+this->base_char_count);
        this->files_counter++;
      }
      entry.close();
    }
    opened_dir.close();
  }
  refresh_files_names();
}

