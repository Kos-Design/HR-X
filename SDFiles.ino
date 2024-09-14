
String make_full_rec_file_name(byte number,String base_path_dir,String suffix="#L.RAW") {
  char formatted_number[4] ;
  sprintf(formatted_number,"%02d",number);
  return(String)(base_path_dir + (String)formatted_number + suffix);
} 

String get_new_rec_file_name(String base_path_dir,String suffix="#L.RAW") {
  byte file_number = 0 ;
  String new_path = base_path_dir + "00" + suffix;
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
  String new_path = base_path_dir + "00" + ".TXT";
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
  String new_path = base_path_dir + "00";
  while (SD.exists(new_path.c_str())) {
    new_path = make_full_dir_name(file_number,base_path_dir);
    file_number++;
  }
  return new_path ;
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
  list_presets_files();
  pseudoconsole((char *)"Scanning Patterns");
  list_patterns_files();
  pseudoconsole((char *)"Scanning Waveforms");
  list_wforms_files();
  pseudoconsole((char *)"Scanning Songs");
  list_songs_files();
  // getavailablespace();
}
