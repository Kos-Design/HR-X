
String make_full_rec_file_name(byte number,String base_path_dir,String suffix="#L.RAW") {
  char formatted_number[4] ;
  sprintf(formatted_number,"%02d",number);
  return(String)(base_path_dir + (String)formatted_number + suffix);
}

String make_full_file_name(byte number,String base_path_dir,String ext=".TXT") {
  char formatted_number[4] ;
  sprintf(formatted_number,"%02d",number);
  return(String)(base_path_dir + (String)formatted_number + ext);
}

String get_new_file_name(String base_path_dir, String ext=".TXT") {
  byte file_number = 0 ;
  String new_path = base_path_dir + "00" + ext;
  while (SD.exists(new_path.c_str())) {
    new_path = make_full_file_name(file_number,base_path_dir,ext);
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
      //addtofullsamplerfolderpath(sampledirsregistered,(char *)soundentry.name());
      sampledirsregistered++;
    }
    soundentry.close();
  }
  sounddir.close();
}

String samplefullpath(int lefolder, int lefile){
  String based = samplebase[lefolder][lefile];
  String folded = samplefoldersregistered[lefolder] ;
  return "SOUNDSET/" + folded + "/" + based +".RAW";
}
/*
struct FileEntry
{
    uint16_t parent;
    char name[9];
    bool isDir;
};
sd_content[999]
*/
  //samplefullpath[lefolder][lefile][j + stringsize] = (char)(lefilename[j]);


/*
void addtofullsamplerfolderpath(int lefolder, char *lepath) {
  for (int i = 0; i < 999; i++) {
    for (int j = 9; j < (int)strlen((char *)lepath) + 9; j++) {
      samplefullpath[lefolder][i][j] = (char)(lepath[j - 9]);
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
*/
void initializesamplebase() {
  for (int i = 0; i < 99; i++) {
    batchclearsamplebase(i);
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
    }
  }
  samplefoldersregistered[0][0] = (char)("/"[0]);
  sampledirsregistered++;
}


