
#include "FilesLister.h"
#include "MenuClasses.h"
void reinitsublevels(byte);
extern DisplayManager dm ;

FilesLister::FilesLister(const char *main_folder, const char *base_filename, const char *file_extension, void (*menu_labels_method)(), byte navranger) : 
                 basenamer(base_filename),
                  extension(file_extension),
                   home(menu_labels_method),
                    home_navrange(navranger),
                     base_char_count(strlen(basenamer)) {
                      strncpy(folder_dir, main_folder, sizeof(folder_dir) - 1);
                      folder_dir[sizeof(folder_dir) - 1] = '\0';
                      snprintf(tmp_folder, 32, "%s%s",folder_dir,"TMP/");
            }
String FilesLister::get_file_name(byte number) {
            char formatted_number[4] ;
            sprintf(formatted_number,"%02d",number);
            return this->basenamer + (String)formatted_number ;
        }

String FilesLister::get_current_file_path(byte f_index=0){
  //Serial.println(((this->folder_dir + this->files_displayable[f_index]).c_str()));
  Serial.println(this->folder_dir);

  String based_file = this->folder_dir + this->files_displayable[f_index] + this->extension ;
  Serial.println(this->folder_dir);
  
  if (SD.exists(based_file.c_str())){
    Serial.println("based file");
    return this->folder_dir + this->files_displayable[f_index] + this->extension;
  } else if (SD.exists((this->folder_dir + this->files_displayable[f_index]).c_str())){
    Serial.println("wild file");
    return this->folder_dir + this->files_displayable[f_index] ;
  }
  Serial.println("");
  Serial.print("none even though file should be ");
  Serial.print(this->folder_dir);
  Serial.print(" in ");

  Serial.print(this->files_displayable[f_index]);
  Serial.println("");
  return "";
}

String FilesLister::make_full_file_name(byte number) {
            char formatted_number[4] ;
            sprintf(formatted_number,"%02d",number);
            return(String)((String)this->folder_dir+(String)this->basenamer + (String)formatted_number + this->extension);
        }

String FilesLister::get_full_tmp_file_path(byte number) {
    char formatted_number[4] ;
    sprintf(formatted_number,"%02d",number);
    return (String)((String)this->tmp_folder+(String)formatted_number);
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

String FilesLister::get_new_tmp_name() {
  byte tmp_file_number = this->tmp_counter ;
  String new_path = get_full_tmp_file_path(tmp_file_number);
  while (SD.exists(new_path.c_str())) {
      tmp_file_number++;
      new_path = get_full_tmp_file_path(tmp_file_number);
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

void FilesLister::deleteFileGeneric(const char* _target_file) {
  if (locked_fileing)
    return;
  locked_fileing = 1 ;
  if (SD.exists(_target_file)) {
    Serial.println(" ");
    Serial.print("deleting ");
    Serial.print(_target_file);

    SD.remove(_target_file);
  }
  locked_fileing = 0 ;
}

void FilesLister::copyFile() {
  if (locked_fileing)
    return;
  locked_fileing = 1 ;
  File origin_file;
  File target_file;
  String current_pathed = this->get_current_file_path(0) ;
  if (SD.exists(current_pathed.c_str())) {
    target_file = SD.open(this->get_new_file_name().c_str(), FILE_WRITE);
    origin_file = SD.open(current_pathed.c_str(), FILE_READ);
    size_t n_size;
    uint8_t buf[64];
    while ((n_size = origin_file.read(buf, sizeof(buf))) > 0) {
      target_file.write(buf, n_size);
    }
  }

  origin_file.close();
  target_file.close();
  this->list_files();
  
  locked_fileing = 0 ;
}

void FilesLister::copyFileGeneric(const char* _origin_file,const char* _target_file) {
  if (SD.exists(_origin_file)) {
    if (SD.exists(_target_file)) 
      deleteFileGeneric(_target_file);
    if (locked_fileing){
      Serial.println("already locked");
      return;
    }
    locked_fileing = 1 ;
    File origin_file = SD.open(_origin_file, FILE_READ);
    File target_file = SD.open(_target_file, FILE_WRITE);
    size_t n_size;
    uint8_t buf[64];
    while ((n_size = origin_file.read(buf, sizeof(buf))) > 0) {
      target_file.write(buf, n_size);
    }
        Serial.println(" ");
    Serial.print("copied ");
    Serial.print(_origin_file);
    Serial.print(" to ");
    Serial.print(_target_file);
  origin_file.close();
  target_file.close();
  locked_fileing = 0 ;
  } else {
    Serial.println("origin file error");
  }
  
}

void  FilesLister::make_temp_folders(){
  make_sub_folder(this->folder_dir, "TMP");
  strncpy(this->tmp_folder, ((String)this->folder_dir+"TMP/").c_str(), 31);
  this->tmp_folder[31] = '\0'; 
  //Serial.println(get_new_tmp_name());
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
  navrange = max(this->files_counter + this->free_counter - 1, 0);
  if (sublevels[lbl_navlevel] == save_lbl_idx) {
    navrange = this->files_counter + this->free_counter ;
    if (sublevels[lbl_navlevel+1] == this->files_counter + this->free_counter){
      this->new_file_mode = true;
    }
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
    } else if (this->displayable_offset+i-this->files_counter < this->free_counter ) {
      //{
        //this->files_displayable[i] = this->get_file_name(this->files_indexed[((this->displayable_offset+i)%this->files_counter) ]);
        this->files_displayable[i] =  this->free_files[(this->displayable_offset+i)-this->files_counter];
    } 
  }
}

void  FilesLister::refresh_folders_names() {
  for (int i = 0 ; i < max_displayables ; i++) {
    this->folders_displayable[i] = " ";
    if (this->displayable_offset+i < this->folders_counter ) {
        this->folders_displayable[i] = this->folders_indexed[this->displayable_offset+i];
    } else if (this->folders_counter >= max_displayables ){
        this->folders_displayable[i] = this->folders_indexed[((this->displayable_offset+i)%this->folders_counter)];
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
  canvasBIG.setCursor(left_margin,0);

  this->displayable_offset = sublevels[this->r_nav] ;
  //% this->files_counter  ;
  int all_files_count = this->free_counter + this->files_counter ;
  refresh_files_names();
  canvastitle.setCursor(left_margin, 0);
  //activate new_file_mode from instancer file actions selector
  if (this->displayable_offset == all_files_count && this->new_file_mode) {
    canvastitle.print("New()");
  } else {
    canvastitle.print(this->files_displayable[0]);
  }
  
  if (this->displayable_offset == all_files_count) {
    //if cursor is on new(), the size-1 elements are displayed below.
    for (int i = 0; i < max_displayables-1; i++) {
      canvasBIG.setCursor(left_margin, (v_spacer * (all_files_count - this->displayable_offset)) + top_margin + ((i)*v_spacer));
      canvasBIG.println(this->files_displayable[i]);
    }
  } else {
    //rest of indexes after title (refresh_names handles list population)
    for (int i = 0; i < max_displayables - 1 ; i++) {
      canvasBIG.setCursor(left_margin, top_margin + i*v_spacer);
      canvasBIG.println(this->files_displayable[1 + i]);
    }
  }
  //dirty patch to hide overflowing extensions
  canvasBIG.fillRect(0, 0, 30, 64, SSD1306_BLACK);
  canvastitle.fillRect(0, 0, 30, 64, SSD1306_BLACK);
}

void  FilesLister::display_folders_list() {
  dm.clean_title_1_1();
  
  this->displayable_offset = sublevels[this->r_nav]  ;

  //% this->files_counter  ;
  refresh_folders_names();
  this->folder_selected = this->folders_displayable[0];

       // strncpy(this->folder_selected, this->folders_displayable[0], 15);
        //this->folder_selected[15] = '\0';                 
  canvastitle.setCursor(left_margin, 0);
  canvastitle.print(this->folders_displayable[0]);
  for (int i = 0; i < max_displayables - 1 ; i++) {
    canvasBIG.setCursor(left_margin, top_margin + i*v_spacer);
    canvasBIG.println(this->folders_displayable[1 + i]);
  }
  
}

void  FilesLister::list_files() {
  //no lock fileing on read as it is used during locked ops, should be fine
  this->files_counter = 0;
  this->folders_counter = 0;
  this->free_counter = 0 ;
  if (SD.exists((const char*)this->folder_dir)) {
    File opened_dir = SD.open((const char*)this->folder_dir);
    while (this->files_counter < 99 && this->folders_counter < 99 && this->free_counter < 99) {
      File entry = opened_dir.openNextFile();
      
      if (!entry) {
        Serial.println("Empty now ");
          break;
      }
      //Serial.println(entry.name());
      if (!entry.isDirectory()) {
        char named[16];
        strncpy(named, entry.name(), 15);
        named[15] = '\0';                 
        //maybe get ext in a separate list for mixed files type <- but that shouldn't be happening
        //perhaps for .wav and .raw but best to sort them on pc before transfer to SD
        if (strlen(named)>strlen(this->extension)){
          named[strlen((char*)named) - strlen(this->extension)] = '\0';
        }
        //int is at X chars after prefix
        bool good_base = (bool)(strncmp((char*)named, this->basenamer, this->base_char_count) == 0) ;
            /*
            Serial.print(good_base);
            Serial.print(" -> ");
            Serial.print((strlen((char*)named)) );*/

        if (strlen((char*)named) != this->base_char_count+2 || !good_base ){
            
            
            //this->free_files[this->free_counter]=named;
            strncpy(this->free_files[this->free_counter], entry.name(), 15);
            this->free_files[this->free_counter][15] = '\0';
            //Serial.print(this->free_files[this->free_counter]);

            this->free_counter++;
            entry.close();
            continue;
        }
        //keep only last 2 digits assuming a basename of 8 chars
        this->files_indexed[this->files_counter] = atoi((char*)named+this->base_char_count);
        this->files_counter++;
      } else {
        //lets hope folders names aare below 15 chars
        strncpy(this->folders_indexed[this->folders_counter], entry.name(), 15);
        this->folders_indexed[this->folders_counter][15] = '\0';
        this->folders_counter++;
      }
      entry.close();
    }
    opened_dir.close();
    if (!this->folders_mode) {
      refresh_files_names();
    } else {
      refresh_folders_names();
    }
  }
}

