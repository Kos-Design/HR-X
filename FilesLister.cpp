
#include "FilesLister.h"
#include "MenuClasses.h"

FilesLister::FilesLister(const char *main_folder, const char *base_filename, const char *file_extension, void (*menu_labels_method)(), byte navranger) :
                 basenamer(base_filename),
                  extension(file_extension),
                   home(menu_labels_method),
                    //home_navrange(navranger),
                     base_char_count(strlen(basenamer)) {
                      strncpy(folder_dir, main_folder, sizeof(folder_dir) - 1);
                      folder_dir[sizeof(folder_dir) - 1] = '\0';
                      snprintf(tmp_folder, 36, "%s%s",folder_dir,"TMP/");
            }

bool FilesLister::get_file_name(char *buffer, size_t buffer_size,byte number){
    int written = snprintf(
        buffer,
        buffer_size,
        "%s%02u",
        this->basenamer,
        number
    );

    return written >= 0 && (size_t)written < buffer_size;
}
bool FilesLister::get_current_file_path(char *buffer, size_t buffer_size, int f_index){
    snprintf(buffer, buffer_size, "%s%s%s",
             this->folder_dir,
             this->files_displayable[f_index],
             this->extension);

    if (SD.sdfs.exists(buffer)) {
        Serial.println("based file");
        return true;
    }

    snprintf(buffer, buffer_size, "%s%s",
             this->folder_dir,
             this->files_displayable[f_index]);

    if (SD.sdfs.exists(buffer)) {
        Serial.println("wild file");
        return true;
    }

    buffer[0] = '\0';
    return false;
}

bool FilesLister::make_full_file_name(byte number, char *buffer, size_t buffer_size){
    int written = snprintf(
        buffer,
        buffer_size,
        "%s%s%02u%s",
        this->folder_dir,
        this->basenamer,
        number,
        this->extension
    );

    return written >= 0 && (size_t)written < buffer_size;
}

bool FilesLister::get_new_file_name(char *buffer, size_t buffer_size){
  byte file_number = this->files_counter;
  while (file_number < 255) {
    if (!make_full_file_name(file_number, buffer, buffer_size))
        return false;
    if (!SD.sdfs.exists(buffer))
        return true;
    file_number++;
  }
  return false;
}

bool FilesLister::get_full_tmp_file_path(char *buffer, size_t buffer_size,byte number){
    int n = snprintf(buffer, buffer_size,
                     "%s%02u",
                     this->tmp_folder,
                     number);

    return n >= 0 && (size_t)n < buffer_size;
}

bool FilesLister::get_new_tmp_name(char *buffer, size_t buffer_size,bool increment){
  byte tmp_file_number = this->tmp_index;
  while (true) {
    if (!get_full_tmp_file_path(buffer, buffer_size,tmp_file_number)) return false;
    if (!SD.sdfs.exists(buffer)) break;
    tmp_file_number++;
  }
  this->tmp_index = tmp_file_number;
  if (increment) this->tmp_count++;
  return true;
}

void FilesLister::deleteFile() {
  if (mc.locked_fileing)
    return;
  mc.locked_fileing = 1 ;
  char current_file_path[64];
  if (!this->get_current_file_path(current_file_path, sizeof(current_file_path), 0)) return;
  Serial.println();
  Serial.print("deleting ");
  Serial.print(current_file_path);

  if (SD.sdfs.exists(current_file_path)) {
    SD.sdfs.remove(current_file_path);
  }
  this->list_files();
  mc.locked_fileing = 0 ;
}

void FilesLister::deleteFileGeneric(const char* _target_file) {
  if (mc.locked_fileing) return;
  mc.locked_fileing = 1 ;
  if (SD.sdfs.exists(_target_file)) {
    SD.sdfs.remove(_target_file);
  }
  mc.locked_fileing = 0 ;
}

void FilesLister::copyFile() {
  if (mc.locked_fileing)
    return;
  mc.locked_fileing = 1 ;
  FsFile origin_file;
  FsFile target_file;
  char current_file_path[64];
  if (!this->get_current_file_path(current_file_path, sizeof(current_file_path), 0)) return;
  char new_file_name[64];
  if (!this->get_new_file_name(new_file_name, sizeof(new_file_name))) return;
  if (SD.sdfs.exists(current_file_path)) {
    target_file = SD.sdfs.open(new_file_name, O_WRITE | O_CREAT | O_TRUNC);
    origin_file = SD.sdfs.open(current_file_path, O_READ);
    size_t n_size;
    uint8_t buf[512];
    while ((n_size = origin_file.read(buf, sizeof(buf))) > 0) {
      target_file.write(buf, n_size);
    }
  }

  origin_file.close();
  target_file.close();
  this->list_files();
  mc.locked_fileing = 0 ;
}

void FilesLister::move_file(const char* _source, const char* _dest){
  FsFile file;
     Serial.println(" ");
        Serial.print("movying ");
        Serial.print(_source);
        Serial.print(" to ");
        Serial.print(_dest);
  if (SD.sdfs.exists(_dest)) SD.sdfs.remove(_dest);
  file.open(_source, O_READ);
  if (file.rename(_dest)) Serial.println(" movyed !");

}

void FilesLister::copyFileGeneric(const char* _origin_file,const char* _target_file) {
        Serial.println(" ");
        Serial.print("copy_ing ");
        Serial.print(_origin_file);
        Serial.print(" to ");
        Serial.print(_target_file);

  if (SD.sdfs.exists(_origin_file)) {
    if (SD.sdfs.exists(_target_file))
      deleteFileGeneric(_target_file);
    if (mc.locked_fileing){
      Serial.println("already locked");
      return;
    }
    mc.locked_fileing = 1 ;
   FsFile origin_file = SD.sdfs.open(_origin_file, O_READ);
   FsFile target_file = SD.sdfs.open(_target_file, O_WRITE | O_CREAT | O_TRUNC);
    size_t n_size;
    //uint8_t buf[64];
    uint8_t buf[512];
    while ((n_size = origin_file.read(buf, sizeof(buf))) > 0) {
      target_file.write(buf, n_size);
    }
  origin_file.close();
  target_file.close();
  mc.locked_fileing = 0 ;


  } else {
    Serial.println("origin file error");
  }
  Serial.println(" ");
  Serial.print("copy_ok ");

}

void FilesLister::make_temp_folders(){
  make_sub_folder(this->folder_dir, "TMP");
  snprintf(this->tmp_folder, sizeof(this->tmp_folder), "%sTMP/", this->folder_dir);
}

void FilesLister::nav_zero(){
  dm.clear_buffs();
  //mc.navrange = this->home_navrange;
  this->display_files_list();
  this->home();
  dm.dodisplay();
}

void FilesLister::nav_one(byte save_lbl_idx=0,byte lbl_navlevel=1){
  this->new_file_mode = false;
  if (mc.sublevels[lbl_navlevel] == save_lbl_idx) {
    mc.navrange = this->files_counter + this->free_counter ;
    if (mc.sublevels[lbl_navlevel+1] == this->files_counter + this->free_counter){
      this->new_file_mode = true;
    }
  } else {
    mc.navrange = max(this->files_counter + this->free_counter - 1, 0);

  }

  this->display_files_list();
  this->home();
  dm.dodisplay();
}

void FilesLister::refresh_files_names() {
  for (int i = 0 ; i < max_displayables ; i++) {
    //TODO:
    //empty spots are left at the end of the list if it is small, otherwise the names are looped
    //maybe looped list is better actually...
    this->files_displayable[i][0] = ' ';
    this->files_displayable[i][1] = '\0';
    if (this->displayable_offset+i < this->files_counter ) {
      char filename[64];
      if (!get_file_name(filename, sizeof(filename),this->files_indexed[this->displayable_offset+i])) return;
      strncpy(this->files_displayable[i], filename, sizeof(this->files_displayable[i]) - 1);
      this->files_displayable[i][sizeof(this->files_displayable[i]) - 1] = '\0';
    } else if (this->displayable_offset+i-this->files_counter < this->free_counter ) {
        strncpy(this->files_displayable[i], this->free_files[(this->displayable_offset+i)-this->files_counter], sizeof(this->files_displayable[i]) - 1);
        this->files_displayable[i][sizeof(this->files_displayable[i]) - 1] = '\0';
    }
  }
}

void FilesLister::refresh_folders_names() {
  for (int i = 0 ; i < max_displayables ; i++) {
    this->folders_displayable[i][0] = ' ';
    this->folders_displayable[i][1] = '\0';
    if (this->displayable_offset+i < this->folders_counter ) {
        strncpy(folders_displayable[i], this->folders_indexed[this->displayable_offset+i], sizeof(folders_displayable[i]) - 1);
        folders_displayable[i][sizeof(folders_displayable[i]) - 1] = '\0';

    } else if (this->folders_counter >= max_displayables ){
        strncpy(folders_displayable[i], this->folders_indexed[((this->displayable_offset+i)%this->folders_counter)], sizeof(folders_displayable[i]) - 1);
        folders_displayable[i][sizeof(folders_displayable[i]) - 1] = '\0';
    }
  }
}

void FilesLister::make_sub_folder(const char *base_folder, const char *subfoldee){
  if (!SD.sdfs.exists(base_folder)) {
    SD.mkdir(base_folder);
  }
  char path[64];
  snprintf(path, sizeof(path), "%s/%s", base_folder, subfoldee);
  if (!SD.sdfs.exists(path)) {
    SD.mkdir(path);
  }
}

void FilesLister::display_files_list() {
  dm.clean_title_1_1();
  dm.canvasBIG.setCursor(this->left_margin,0);
  int all_files_count = this->free_counter + this->files_counter ;
  if (mc.navlevel == this->r_nav) {
    this->displayable_offset = mc.sublevels[this->r_nav]  ;
  }
  refresh_files_names();
  dm.canvastitle.setCursor(this->left_margin, 0);
  //activate new_file_mode from instancer file actions selector
  if (this->displayable_offset == all_files_count && this->new_file_mode) {
    dm.canvastitle.print("New()");
  } else {
    dm.canvastitle.print(this->files_displayable[0]);
  }

  if (this->displayable_offset == all_files_count) {
    //if cursor is on new(), the size-1 elements are displayed below.
    for (int i = 0; i < max_displayables-1; i++) {
      dm.canvasBIG.setCursor(this->left_margin, (this->v_spacer * (all_files_count - this->displayable_offset)) + this->top_margin + ((i)*this->v_spacer));
      dm.canvasBIG.println(this->files_displayable[i]);
    }
  } else {
    //rest of indexes after title (refresh_names handles list population)
    for (int i = 0; i < max_displayables - 1 ; i++) {
      dm.canvasBIG.setCursor(this->left_margin, this->top_margin + i*this->v_spacer);
      dm.canvasBIG.println(this->files_displayable[1 + i]);
    }
  }
  //dirty patch to hide overflowing extensions
  dm.canvasBIG.fillRect(0, 0, 30, 64, SSD1306_BLACK);
  dm.canvastitle.fillRect(0, 0, 30, 64, SSD1306_BLACK);
}

void FilesLister::display_folders_list() {
  dm.clean_title_1_1();
  if (mc.navlevel == this->r_nav) {
    this->displayable_offset = mc.sublevels[this->r_nav]  ;
    Serial.println("");
    Serial.print("setted at lvl ");
    Serial.print(mc.navlevel);
  }
  //% this->files_counter  ;
  refresh_folders_names();
  strncpy(this->folder_selected, this->folders_displayable[0], sizeof(this->folder_selected) - 1);
  this->folder_selected[sizeof(this->folder_selected) - 1] = '\0';
  dm.canvastitle.setCursor(this->left_margin, 0);
  dm.canvastitle.print(this->folders_displayable[0]);
  for (int i = 0; i < max_displayables - 1 ; i++) {
    dm.canvasBIG.setCursor(this->left_margin, this->top_margin + i*this->v_spacer);
    dm.canvasBIG.println(this->folders_displayable[1 + i]);
  }

}

void FilesLister::list_files() {
  //no lock fileing on read as it is used during locked ops, should be fine
  this->files_counter = 0;
  this->folders_counter = 0;
  this->free_counter = 0 ;
  if (SD.sdfs.exists((const char*)this->folder_dir)) {
   FsFile opened_dir = SD.sdfs.open((const char*)this->folder_dir);
    while (this->files_counter < 99 && this->folders_counter < 99 && this->free_counter < 99) {
     FsFile entry = opened_dir.openNextFile();
      if (!entry) {
          break;
      }
      char entry_name[16];
      if (!entry.isDirectory()) {
        char named[16];

        entry.getName(entry_name, 16);
        strncpy(named, entry_name, 15);
        named[15] = '\0';
        if (strlen(named)>strlen(this->extension)){
          named[strlen((char*)named) - strlen(this->extension)] = '\0';
        }
        bool good_base = (bool)(strncmp((char*)named, this->basenamer, this->base_char_count) == 0) ;
        if (strlen((char*)named) != this->base_char_count+2 || !good_base ){
            //strncpy(this->free_files[this->free_counter], entry_name, 15);
            entry.getName(this->free_files[this->free_counter], 16);

            this->free_files[this->free_counter][15] = '\0';
            this->free_counter++;
            entry.close();
            continue;
        }
        //keep only last 2 digits assuming a basename of 8 chars
        this->files_indexed[this->files_counter] = atoi((char*)named+this->base_char_count);
        this->files_counter++;
      } else {
        //TODO securize name length
        //lets hope folders names aare below 15 chars
        //strncpy(this->folders_indexed[this->folders_counter], entry_name, 15);
        entry.getName(this->folders_indexed[this->folders_counter], 16);

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

