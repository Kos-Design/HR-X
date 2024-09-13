
/*
class PatFiler {
  public:
    static const byte pat_menu_size = 4 ;
    
    byte spacing = 2;
    byte slider_width = 25;
    uint16_t pat_files[999];
    uint16_t pattern_files_count = 0 ;
    static const byte pf_slots_size = 8 ;
    String pf_slots[pf_slots_size] ;
    byte pat_file_range = 0;
    byte previous_pat_file_range = 0;
    
    int16_t selected_file = 0 ;
    bool dialog_on = false;
    int confirmable = 0 ;

    PatFiler(uint16_t start_x = 200, uint16_t start_y=0,uint16_t max_frame_x = 120, uint16_t max_frame_y=180 ) {

    }

    void refresh_pattern_files_panel(){
     
      list_patterns_on_sd();
      refresh_pattern_files();
      tft.fillRoundRect(vslider_widget.x_start, vslider_widget.y_start, vslider_widget.x_size, vslider_widget.y_size, 11, RGB565(110, 110, 110));
    }

    void draw_pat_file_explorer(){

      String labels[pat_menu_size] = {"Load","Save","Copy","Delete"};

      refresh_pattern_files_panel();
    }
        
    void action_dialog_pat(byte indexee){
      switch (indexee) {
        case 0 :
        //select yes
        arrow_shifter = -60 ;
        break;

        case 1 :
        //select no
        arrow_shifter = 0 ;
        break;

        default:
        break;
      }
      if (confirmable == 1) {
        drawFF7Dialog("Confirm Delete ?", get_selected_path());
      } else if (confirmable == 2) {
        drawFF7Dialog("Confirm Overwrite ?", get_selected_path());
      }
    }

    void confirm_delete_pat(byte indexee){
      switch (indexee) {
        case 0 :
          if (confirmable == 1) {
            del_file();
          } else if (confirmable == 2) {
            String filer = get_selected_path();
            if (filer != "None") {
              SD.remove(filer.c_str());
              save_file(filer);
            }
          }
        break;

        case 1 :
        //cancel
        break;

        default:
        break;
      }
      close_pat_dialog_box();
    }

    void close_pat_dialog_box(){
      dialog_on = false ;
      confirmable = 0 ;
      arrow_shifter = 0 ;
    }

    void select_file(byte i){
      if (selected_file == i+1 + pat_file_range || i + 1 > pattern_files_count){
        selected_file = 0 ;
      } else {
      selected_file = i+1 + pat_file_range ;
      }
      refresh_pattern_files_panel();
    }

    void move_slider(int shifter){
      //snap to end caps or int values
      if (vslider_widget.y_end + shifter < vslider_dw.y_start - 5 && vslider_widget.y_start + shifter > vslider_up.y_end+2 ) {
        //fill_zone(vslider_widget,ILI9341_BLACK);
        vslider_widget.setDims(vslider_widget.x_start, vslider_widget.y_start+shifter, vslider_widget.x_size, vslider_widget.y_size);
        //fill_zone(vslider_widget);
        shift_pat_file_range();
      }
      refresh_pattern_files_panel();
    }
    
    void refresh_pattern_files() {
      for (int i = 0 ; i < pf_slots_size ; i++) {
        //TODO check condition
        if (pat_file_range+i < pattern_files_count ) {
          pf_slots[i] = get_base_pat_name(pat_files[pat_file_range+i]);
        } else { 
          pf_slots[i] = " "; 
        }
      }
      draw_pattern_files();
    }
    
    void draw_pattern_files(){
      //get formula for x size ~55
      tft.setTextColor(RGB565(150, 150, 150));
      //tft.fillRect(p_frame.x_start + p_frame.x_size/2.5 + 2,p_frame.y_start+1, 55 ,p_frame.y_size -2 , ILI9341_BLACK);
      for (int i = 0 ; i < pf_slots_size ; i++) {
        uint16_t x_start = p_frame.x_start+p_frame.x_size/2.5 + 6 ;
        uint16_t y_start = p_frame.y_start+13+(i*(p_frame.y_size/pf_slots_size));
        if (i + pat_file_range == selected_file - 1){
          tft.drawLine(x_start,y_start+3,x_start+50,y_start+3,RGB565(150, 150, 150));
        }
        tft.setCursor(x_start, y_start) ;
        tft.print(pf_slots[i]);
      }
    }

   
    void drawFF7Dialog(String line_one, String line_two="None"){
      int x = 65;
      int y = 65;
      dialog_on = true;
      
    }

    void shift_pat_file_range(){
      if (pf_slots_size < pattern_files_count){
        pat_file_range = map(vslider_widget.y_start,vslider_up.y_end+3,vslider_dw.y_start-vslider_widget.y_size,0,pattern_files_count-pf_slots_size+2);
        if (previous_pat_file_range != pat_file_range) {
          previous_pat_file_range = pat_file_range ;
          //refresh_pattern_files();
        }
      }
    }

    void action_slider(byte i){
      switch(i){
        case 0:
          move_slider(- vslider_bar.y_size / (pattern_files_count-pf_slots_size+9));
          
        break;

        case 1:
        //mid
        break;

        case 2:
          move_slider(vslider_bar.y_size / (pattern_files_count-pf_slots_size+9));
        break;

        case 3:
        //drag bar
        break;
        
        default:
        break;
      }
    }

    void action_button(byte i){
      switch(i){
        case 0:
        load_file();
        break;

        case 1:
        prepare_saver();
        break;

        case 2:
        copy_file();
        break;

        case 3:
        confirmable = 1 ;
        drawFF7Dialog("Confirm Delete ?", get_selected_path());
        break;
        
        default:
        break;
      }
    }
      
    void list_patterns_on_sd(){
      pattern_files_count = 0;
      File dir = SD.open("/PATTERNS");
      File entry ;
      entry = dir.openNextFile();
      while (entry) {
        if (entry.isDirectory() == false) {
          char* named = (char*)entry.name();
          named[strlen(named) - 4] = '\0';
          pat_files[pattern_files_count] = atoi(named+3);
          pattern_files_count++;
        }
      entry = dir.openNextFile();
      }
      entry.close();
      dir.close() ;
    }

    String get_base_pat_name(byte number) {
      char formatted_number[4] ;
      sprintf(formatted_number,"%03d",number);
      String new_path = "PAT" + (String)formatted_number ;
      return new_path ;
    } 

    String get_selected_path() {
      String new_path = "None" ;
      if (selected_file - 1 >= pat_file_range && selected_file - 1 < pat_file_range+8) {
         new_path = get_full_pat_name(pat_files[selected_file-1]);
      }
      return new_path ;
    } 

    String get_full_pat_name(byte number) {
      //change ext since writing & reading binary files
      char formatted_number[4] ;
      sprintf(formatted_number,"%03d",number);
      String new_path_dir = "/PATTERNS/PAT" ;
      String new_path = new_path_dir + (String)formatted_number + ".PAT" ;
      return new_path ;
    } 

    String get_new_pat_name() {
      byte file_number = 0 ;
      String new_path = "/PATTERNS/PAT000.PAT";
      while (SD.exists(new_path.c_str())) {
        new_path = get_full_pat_name(file_number);
        file_number++;
      }
      return new_path ;
    }

    void load_file(){
      if (selected_file != 0) {
        String filer = get_selected_path();
        if (filer != "None") {
          File pat_on_sd = SD.open(filer.c_str(), FILE_READ);
          if (pat_on_sd) {
            pat_on_sd.read((byte*)song.pat_catalog, sizeof(song.pat_catalog));
            pat_on_sd.read((byte*)cc.cc_patterns, sizeof(cc.cc_patterns));
            pat_on_sd.read((byte*)cc.cc_states, sizeof(cc.cc_states));

            pat_on_sd.close();
          }
          selected_file = 0 ;
          grid.refresh_cells();
          printme_str("Loaded",filer);
          cc.refresh_active_ccs_list();
        }
      }
    }

    void prepare_popup_overwrite(){
      confirmable = 2 ;
      drawFF7Dialog("Confirm overwrite ?",get_selected_path());
    }

    void prepare_saver(){
      String filer = "None";
      if (selected_file != 0) {
        prepare_popup_overwrite();
      } else {
        filer = get_new_pat_name();
      }
      save_file(filer);
    }

    void save_file(String filer){
      if (filer != "None") {  
        File pat_on_sd = SD.open(filer.c_str(), FILE_WRITE);
        pat_on_sd.write((byte*)song.pat_catalog, sizeof(song.pat_catalog));
        pat_on_sd.write((byte*)cc.cc_patterns, sizeof(cc.cc_patterns));
        pat_on_sd.write((byte*)cc.cc_states, sizeof(cc.cc_states));
        pat_on_sd.close();
        //list_patterns_on_sd();
        selected_file = 0 ;
        refresh_pattern_files_panel();
        printme_str("Saved",filer);
      }  
    }

    void del_file(){
      if (selected_file != 0) {
        String filer = get_selected_path();
        if (filer != "None") {
          SD.remove(filer.c_str());
          //list_patterns_on_sd();
          selected_file = 0 ;
          refresh_pattern_files_panel();
          printme_str("Deleted",filer);
        }
      }
    }

    void copy_file(){
      if (selected_file != 0) {
        //save current as temp in new file
        String origin = get_new_pat_name();
        File og = SD.open(origin.c_str(), FILE_WRITE);
        og.write((byte*)song.pat_catalog, sizeof(song.pat_catalog));
        og.write((byte*)cc.cc_patterns, sizeof(cc.cc_patterns));
        og.write((byte*)cc.cc_states, sizeof(cc.cc_states));
        og.close();
        String filer = get_selected_path();
        //load target
        File target_pat = SD.open(filer.c_str(), FILE_READ);
        target_pat.read((byte*)song.pat_catalog, sizeof(song.pat_catalog));
        target_pat.read((byte*)cc.cc_patterns, sizeof(cc.cc_patterns));
        target_pat.read((byte*)cc.cc_states, sizeof(cc.cc_states));
        target_pat.close();
        //saves target
        String target = get_new_pat_name() ;
        File target_copy = SD.open(target.c_str(), FILE_WRITE);
        target_copy.write((byte*)song.pat_catalog, sizeof(song.pat_catalog));
        target_copy.write((byte*)cc.cc_patterns, sizeof(cc.cc_patterns));
        target_copy.write((byte*)cc.cc_states, sizeof(cc.cc_states));
        target_copy.close();
        //reload original
        File reloaded_og = SD.open(origin.c_str(), FILE_READ);
        reloaded_og.read((byte*)song.pat_catalog, sizeof(song.pat_catalog));
        reloaded_og.read((byte*)cc.cc_patterns, sizeof(cc.cc_patterns));
        reloaded_og.read((byte*)cc.cc_states, sizeof(cc.cc_states));
        reloaded_og.close();
        //delete tmp og
        SD.remove(origin.c_str());
        selected_file = 0;
        refresh_pattern_files_panel();
      }
    }
       
};
*/

String make_full_rec_file_name(byte number,String base_path_dir,String suffix="#L.RAW") {
  char formatted_number[4] ;
  sprintf(formatted_number,"%02d",number);
  return(String)(base_path_dir + (String)formatted_number + suffix);
} 

String get_new_rec_file_name(String base_path_dir,String suffix="#L.RAW") {
  byte file_number = 0 ;
  String new_path = base_path_dir + "01" + suffix;
  while (SD.exists(new_path.c_str())) {
    new_path = make_full_rec_file_name(file_number,base_path_dir);
    file_number++;
  }
  return new_path ;
}

String make_full_file_name(byte number,String base_path_dir) {
  char formatted_number[4] ;
  sprintf(formatted_number,"%02d",number);
  return(String)(base_path_dir + (String)formatted_number + ".TXT");
} 

String get_new_file_name(String base_path_dir) {
  byte file_number = 0 ;
  String new_path = base_path_dir + "01" + ".TXT";
  while (SD.exists(new_path.c_str())) {
    new_path = make_full_file_name(file_number,base_path_dir);
    file_number++;
  }
  return new_path ;
}

String make_full_dir_name(byte number,String base_path_dir) {
  char formatted_number[4] ;
  sprintf(formatted_number,"%02d",number);
  return(String)(base_path_dir + (String)formatted_number);
} 

String get_new_dir_name(String base_path_dir) {
  byte file_number = 0 ;
  String new_path = base_path_dir + "01";
  while (SD.exists(new_path.c_str())) {
    new_path = make_full_dir_name(file_number,base_path_dir);
    file_number++;
  }
  return new_path ;
}

void initializeSynthPresetfullpath() {
  presets_count = 0;

  for (int i = 0; i < 999; i++) {
    for (int j = 0; j < 28; j++) {
      SynthPresetfullpath[i][j] = (char)'\0';
      if (j < 14) {
        SynthPresetfullpath[i][j] = (char)("PRESETS/SYNTH/"[j]);
      }
      if (j < 13) {
        SynthPresetname[i][j] = (char)'\0';
      }
      if (j < 9) {
        SynthPresetbase[i][j] = (char)'\0';
      }
    }
  }
}

void dopresetlist() {
  initializeSynthPresetfullpath();
  listSynthPresetfiles();
}

void setleSynthPresetname(int lefile, char *lefname) {

  int fnamesize = strlen((char *)lefname);
  for (int i = 0; i < fnamesize; i++) {

    SynthPresetname[lefile][i] = lefname[i];

    SynthPresetfullpath[lefile][14 + i] = SynthPresetname[lefile][i];
    if (i < fnamesize - 4) {
      SynthPresetbase[lefile][i] = SynthPresetname[lefile][i];
    }
  }
  SynthPresetname[lefile][fnamesize] = (char)'\0';
  SynthPresetfullpath[lefile][14 + fnamesize] = (char)'\0';
  SynthPresetbase[lefile][fnamesize - 4] = (char)'\0';
}

void listSynthPresetfiles() {
  if (SD.exists(SynthPresetdir.c_str())) {
    File susudir = SD.open(SynthPresetdir.c_str());

    while (true) {
      File subentry = susudir.openNextFile();
      if (!subentry) {
        break;
      }

      if (!subentry.isDirectory()) {
        setleSynthPresetname(presets_count, (char *)subentry.name());
        presets_count++;
      }
      subentry.close();
    }
  }
}

void dosoundlist() {
  if (!initdone) {
    pseudoconsole((char *)"Files on Flash");
  }
  initializeFlashsamplesselected();
  initializesamplesfoldersselectedlist();
  rebuildflashsamplesnames();
  clearsizeofsamplefolder();
  sampledirsregistered = 0;
  if (!initdone) {
    pseudoconsole((char *)"Files on SD");
  }
  setupsamplefoldersregistered();
  initializesamplefullpath();
  initializesamplebase();
  listSoundset();
  for (int i = 1; i < sampledirsregistered; i++) {
    pleasewait(i, sampledirsregistered);
    voidsampledirpath();
    makesoundsetfullpathfromchars(i);
    listSoundsetsubdir(i);
  }
  // printthem();
}

void clearsizeofsamplefolder() {
  for (int i = 0; i < 99; i++) {
    sizeofsamplefolder[i] = 0;
  }
}

void voidsampledirpath() {
  for (int i = 0; i < 99; i++) {
    sampledirpath[i] = (char)'\0';
  }
  for (int i = 0; i < 9; i++) {
    sampledirpath[i] = (char)("SOUNDSET/"[i]);
  }
}

void makesoundsetfullpathfromchars(int eldir) {
  for (int i = 9; i < (int)(strlen((char *)samplefoldersregistered[eldir]) + 9);
       i++) {
    sampledirpath[i] = samplefoldersregistered[eldir][i - 9];
  }
  int lelast = (int)strlen((char *)sampledirpath);
  sampledirpath[lelast] = (char)'/';
  sampledirpath[lelast + 1] = (char)'\0';
  // Serial.println((char*)sampledirpath);
}

void listSoundset() {

  File sounddir = SD.open("SOUNDSET/");

  while (true) {
    File soundentry = sounddir.openNextFile();

    if (!soundentry) {

      break;
    }

    if (soundentry.isDirectory()) {
      addtofolderix((char *)soundentry.name(), sampledirsregistered);
      addtofullsamplerfolderpath(sampledirsregistered,
                                 (char *)soundentry.name());
      sampledirsregistered++;
    }
    soundentry.close();
  }
}

void listSoundsetsubdir(int ledir) {
  if (SD.exists((char *)sampledirpath)) {

    // Serial.println(" dir = ");
    // Serial.println((char*)sampledirpath);

    File susudir = SD.open((char *)sampledirpath);

    while (true) {
      File subentry = susudir.openNextFile();
      if (!subentry) {
        break;
      }

      if (!subentry.isDirectory()) {
        // Serial.println(" 1 = 1 ");
        setlefilenamed(ledir, sizeofsamplefolder[ledir], (char*)subentry.name());

        (sizeofsamplefolder[ledir])++;
        // subentry.close();
      }
      subentry.close();
    }
  }
}

void dosamplerfullpath(int lefolder, int lefile, char *lefilename) {
  // for (int i = 0 ; i< 999 ; i++ ) {
  int stringsize = (strlen((char *)samplefullpath[lefolder][lefile])) +
                   (strlen((char *)lefilename));
  for (int j = 0; j < stringsize; j++) {
    samplefullpath[lefolder][lefile][j + stringsize] = (char)(lefilename[j]);
    // Serial.println((char)(lepathtoadd[i]));
  }
  // samplefullpath[lefolder][i][(strlen((char*)lepath)+9)]=(char*)"/"[0];
  //}
}

void addtofullsamplerfolderpath(int lefolder, char *lepath) {
  for (int i = 0; i < 999; i++) {
    for (int j = 9; j < (int)strlen((char *)lepath) + 9; j++) {
      samplefullpath[lefolder][i][j] = (char)(lepath[j - 9]);
      // Serial.println((char)(lepathtoadd[i]));
    }
    samplefullpath[lefolder][i][(strlen((char *)lepath) + 9)] = (char)("/"[0]);
  }
}

void initializesamplefullpath() {
  for (int i = 0; i < 99; i++) {
    batchclearsamplefullpath(i);
  }
}

void batchclearsamplefullpath(int lefolder) {
  for (int i = 0; i < 999; i++) {
    clearsamplefullpath(lefolder, i);
  }
}

void clearsamplefullpath(int lefolder, int lefile) {
  for (int i = 0; i < 38; i++) {
    samplefullpath[lefolder][lefile][i] = (char)'\0';
  }
  for (int j = 0; j < 9; j++) {
    samplefullpath[lefolder][lefile][j] = (char)("SOUNDSET/"[j]);
  }
}

void initializesamplebase() {
  for (int i = 0; i < 99; i++) {
    batchclearsamplefullpath(i);
  }
}

void batchclearsamplebase(int lefolder) {
  for (int i = 0; i < 999; i++) {
    clearsamplebase(lefolder, i);
  }
}

void clearsamplebase(int lefolder, int lefile) {
  for (int i = 0; i < 9; i++) {
    samplebase[lefolder][lefile][i] = (char)'\0';
  }
}

void addtofolderix(char *lepathtoadd, int ix) {

  for (int i = 0; i < (int)strlen((char *)lepathtoadd); i++) {
    samplefoldersregistered[ix][i] = (char)(lepathtoadd[i]);
  }
}

void setupsamplefoldersregistered() {
  // i = 99 , j = 39
  for (int i = 0; i < szsset; i++) {
    for (int j = 0; j < ssnamsize; j++) {
      samplefoldersregistered[i][j] = (char)'\0';
      // delay(1);
    }
  }
  samplefoldersregistered[0][0] = (char)("/"[0]);
  // delay(1);
  sampledirsregistered++;
  // Serial.println((char*)(samplefoldersregistered[0]));
}

void setupSD() {

  if (!(SD.begin(chipSelect))) {
    Serial.println("initialization SD failed!");
    return;
  }
  // Serial.println("initialization 0 done.");

  // scans Soundset samples folders

  initializesamplesselectedlist();
  pseudoconsole((char *)"Scanning Samples");
  dosoundlist();
  pseudoconsole((char *)"Scanning Presets");
  dopresetlist();
  pseudoconsole((char *)"Scanning Patterns");
  list_patterns_files();
  pseudoconsole((char *)"Scanning Waveforms");
  list_wforms_files();
  pseudoconsole((char *)"Scanning Songs");
  doSonglist();
  // getavailablespace();
}
