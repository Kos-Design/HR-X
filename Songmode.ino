
int songedit = 2;
int songselectorX;
int songselectorY;
int patternonsong[99];
int songplayhead = 0;
byte numberofpatonsong;

bool songplaying;
const byte truesizeofSongmenulabels = 8;
const byte navSongmenu = 1;

byte songs_indexes[99];
byte songs_count = 0 ;
const byte sng_size = 6;
String songs_names[sng_size];
byte songs_names_offset = 0 ;

String get_song_name(byte number) {
  char formatted_number[4] ;
  sprintf(formatted_number,"%02d",number);
  return "SONG#" + (String)formatted_number ;
} 

String get_current_song_path(){
  return "SONGS/" + songs_names[0] + ".TXT";
}

void refresh_songs_names() {
  for (int i = 0 ; i < sng_size ; i++) {
    //empty spots are left at the end of the list if it is small, otherwise the names are looped
    songs_names[i] = " ";
    if (songs_names_offset+i < songs_count ) {
      songs_names[i] = get_song_name(songs_indexes[songs_names_offset+i]);
    } else if (songs_count >= sng_size ){ 
      songs_names[i] = get_song_name(songs_indexes[((songs_names_offset+i)%songs_count)]); 
    } 
  }
}
          
void list_songs_files() {
  songs_count = 0;
  String songs_dir = "SONGS/";
  if (SD.exists(songs_dir.c_str())) {
    File song_filer = SD.open(songs_dir.c_str());
    while (songs_count < 99) {
      File entry = song_filer.openNextFile();
      if (!entry) {
        break;
      }
      if (!entry.isDirectory()) {
        char* named = (char*)entry.name();
        named[strlen(named) - 4] = '\0';
        //int is at 5 chars after prefix
        songs_indexes[songs_count] = atoi(named+5);
        songs_count++;
      }
      entry.close();
    }
    song_filer.close();
  }
}

void writedasong() {
  File song_filer ;
  if (sublevels[navSongmenu + 1] == songs_count) {
    song_filer = SD.open(get_new_file_name("SONGS/SONG#").c_str(), FILE_WRITE);
  } else {
    if (SD.exists(get_current_song_path().c_str())) {
      SD.remove(get_current_song_path().c_str());
    }
    song_filer = SD.open(get_current_song_path().c_str(), FILE_WRITE);
  }
  writeSong(song_filer);
  song_filer.close();
  list_songs_files();
}

void insert_int_in_song_file(File &song_filer,int leint, char *leparam) {
  size_t param_length = strlen(leparam);
  if (param_length > 5 ) {
    leparam[6] = '\0';
  }
  //strncpy(truncated, leparam, 5);
  song_filer.print((char *)leparam);
  song_filer.print(" ");
  song_filer.print("#");
  song_filer.print(int(leint));
  song_filer.print("\n");
}

void writeSong(File &song_filer) {
  song_filer.print("<Song>\n");
  insert_int_in_song_file(song_filer,numberofpatonsong, (char*)"nums");
  for (byte i = 0; i < 99; i++) {
    insert_int_in_song_file(song_filer,patternonsong[i], (char*)"songpat");
  }
}

void parseSong() {
  File song_filer = SD.open(get_current_song_path().c_str());
  if (song_filer) {
    //increse parsingbuffersize if more settings are added
    for (int i = 0; i < parsingbuffersize; i++) {
      receivedbitinchar[i] = song_filer.read();
    }
  }
  Parser parser((byte *)receivedbitinchar, parsinglength);
  parser.Read_String('#');
  parser.Skip(1);
  numberofpatonsong = parser.Read_Int16();
  for (int i = 0; i < 99; i++) {
    parser.Read_String('#');
    parser.Skip(1);
    patternonsong[i] = parser.Read_Int16();
  }
  parser.Reset();
  song_filer.close();
}

void copySong() {
  File origin_file;
  File target_file;
  if (SD.exists(get_current_song_path().c_str())) {
    target_file = SD.open(get_new_file_name("SONGS/SONG#").c_str(), FILE_WRITE);
    origin_file = SD.open(get_current_song_path().c_str(), FILE_READ);
    size_t n;
    uint8_t buf[64];
    while ((n = origin_file.read(buf, sizeof(buf))) > 0) {
      target_file.write(buf, n);
    }
  }
  origin_file.close();
  target_file.close();
  list_songs_files();
}

void deleteSong() {
  if (SD.exists(get_current_song_path().c_str())) {
    SD.remove(get_current_song_path().c_str());
  }
  list_songs_files();
}

void shiftSongright(int leshifter) {
  for (int shifts = 0; shifts < leshifter; shifts++) {
    for (int i = 98; i >= 0; i--) {
      patternonsong[i + 1] = patternonsong[i];
      patternonsong[i] = 0;
    }
  }
}

void shiftSongleft(int leshifter) {
  for (int shifts = 0; shifts < leshifter; shifts++) {
    for (int i = 1; i < 99; i++) {
      patternonsong[i - 1] = patternonsong[i];
      patternonsong[i] = 0;
    }
  }
}

void doSongShifter(int shifter) {
  if (shifter - 16 > 0) {
    shiftSongleft(abs(shifter - 16));
  }
  if (shifter - 16 < 0) {
    shiftSongright(abs(shifter - 16));
  }
}

void showSongShifterdisplays() {
  navrange = 32;
  display.clearDisplay();
  canvastitle.fillScreen(SSD1306_BLACK);
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(2);
  canvastitle.print("Shift Song");
  int latransposition;
  latransposition = 16 - sublevels[2];
  sublevels[3] = sublevels[2];
  canvasBIG.setCursor(0, 16);
  canvasBIG.setTextSize(2);
  if (latransposition > 0) {
    canvasBIG.print("+");
  }
  if (latransposition == 0) {
    canvasBIG.setCursor(8, 16);
  }
  canvasBIG.print(latransposition);
  dodisplay();
}

void displaySongmenu() {
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.fillScreen(SSD1306_BLACK);
  display.clearDisplay();
  SongmenuAction();
  dodisplay();
}

void draw_song_list() {
  int startx = 80;
  int starty = 16;
  songs_names_offset = sublevels[navSongmenu + 1];
  refresh_songs_names();
  canvastitle.setCursor(startx, 0);
  canvastitle.setTextSize(1);
  if (sublevels[navSongmenu + 1] == songs_count && sublevels[navSongmenu] == 1) {
    canvastitle.print("New()");
  } else {
    canvastitle.print(songs_names[0]);
  }
  canvastitle.setTextSize(1);
  canvasBIG.setTextSize(1);
  if (sublevels[navSongmenu + 1] == songs_count) {
    //if cursor is on new(), the sng_size-1 elements are displayed below.
    for (int i = 0; i < sng_size-1; i++) {
      canvasBIG.setCursor(startx, (10 * (songs_count - sublevels[navSongmenu + 1])) + 16 + ((i)*10));
      canvasBIG.println(songs_names[i]);
    }
  } else {
    for (int i = 0; i < sng_size - 1 ; i++) {
      canvasBIG.setCursor(startx, starty + ((i)*10));
      canvasBIG.println(songs_names[i+1]);
    }
  }
}

void SongmenuAction() {

  if (navlevel == navSongmenu) {
    reinitsublevels(navSongmenu + 1);
    navrange = truesizeofSongmenulabels - 1;

    dolistSongdisplay();
    draw_song_list();
  }

  if ((sublevels[navSongmenu] == 0) && (navlevel > navSongmenu)) {
    Songmodepanel();
  }

  if (sublevels[navSongmenu] != 0) {

    if (navlevel > navSongmenu + 1) {

      switch (sublevels[navSongmenu]) {

      case 0:
        Songmodepanel();
        // into edit already ;
        break;
      case 1:
        writedasong();

        // save();
        break;
      case 2:

        parseSong();

        break;
      case 3:
        copySong();

        break;

      case 4:
        deleteSong();

        break;

      case 5:
        initializepatternonsong();

        break;
      case 6:

        break;
      case 7:
        doSongShifter(sublevels[3]);

        break;

      default:
        break;
      }
      // displaySongmenu();
      returntonav(navSongmenu, truesizeofSongmenulabels - 1);
      // returntonav(navSongmenu,truesizeofSongmenulabels-1);
    }

    if (navlevel > navSongmenu) {

      if (sublevels[navSongmenu] == 5) {
        returntonav(navSongmenu, truesizeofSongmenulabels - 1);
      }

      if (sublevels[navSongmenu] == 1) {
        navrange = songs_count;
      } else {
        navrange = max(songs_count - 1 , 0);
      }
      if (sublevels[navSongmenu] == 7) {
        navrange = 32;
        showSongShifterdisplays();
      }
      if (sublevels[navSongmenu] != 7) {
        dolistSongdisplay();
        draw_song_list();
      }
    }

    // if (navlevel == navSongmenu ) {
    // dolistSongdisplay();
    // draw_song_list();

    // }
  }
}

void dolistSongdisplay() {
  char Songmenulabels[truesizeofSongmenulabels][12] = {
      "Edit", "Save", "Load", "Copy", "Delete", "Clear", "Params", "Shift"};
  byte startx = 5;
  byte starty = 16;
  char *textin = (char *)Songmenulabels[sublevels[navSongmenu]];
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(2);
  canvastitle.println(textin);
  canvasBIG.setTextSize(1);
  // canvasBIG.fillScreen(SSD1306_BLACK);
  for (int i = 0; i < truesizeofSongmenulabels - 1 - (sublevels[navSongmenu]); i++) {
    canvasBIG.setCursor(startx, starty + ((i)*10));
    canvasBIG.println(Songmenulabels[sublevels[navSongmenu] + 1 + i]);
  }
  for (int i = 0; i < sublevels[navSongmenu]; i++) {
    canvasBIG.setCursor(startx, (10 * (truesizeofSongmenulabels - sublevels[navSongmenu]) + 6 + ((i)*10)));
    canvasBIG.println(Songmenulabels[i]);
  }
}

void playdasong() {
  if (!externalticker) {
    //metro0.reset();
  }
  songplaying = 1;
  loadsongpattern();
  stoptick = 0;
  patternOn = 1;
}

void stopdasong() {
  songplaying = 0;
  songplayhead = 0;
  stoptick = 1;
  patternOn = 0;
}

void pausedasong() {
  songplaying = 0;
  stoptick = 1;
  patternOn = 0;
}
void showplayheadprogress() {
  display.drawLine(songplayhead * 8, 16, songplayhead * 8, 64, SSD1306_INVERSE);
}
void loadsongpattern() {
  // Serial.println(songplayhead);
  if (patternonsong[songplayhead] > 0) {
    clearlapattern();
    Serial.print("cleared ");
    Serial.print("loading ");
    Serial.println(patternonsong[songplayhead] - 1);
    patterns_names_offset = patternonsong[songplayhead] - 1 ;
    refresh_patterns_names();
    parsepattern();

    Serial.println("Loaded");
  } else {
    stopdasong();
  }
}
void initializepatternonsong() {

  for (int j = 0; j < 99; j++) {
    patternonsong[j] = 0;
  }
}
void actionSongTransport() {
  if (sublevels[songedit] == 0) {
    stopdasong();
    playdasong();
  }
  if (sublevels[songedit] == 2) {
    stopdasong();
  }
  if (sublevels[songedit] == 3) {
    playdasong();
  }

  returntonav(songedit);
}
void Songmodepanel() {
  songselectorY = 16;
  songmodetopbar();
  // drawsonggrid() ;
  // Serial.println("see things?");
  if (navlevel == songedit) {
    if (songpage > 0) {
      navrange = 8 + 16 + 1;
    } else {
      navrange = 8 + 16;
    }
    if (sublevels[songedit] > 7) {

      // navrange = 127/8 - 1;
      selectormoveX();
    }

    else {
      // songselectorY = 12 * sublevels[songedit] + 16
      songTransportSelector();
    }
  }
  if (navlevel == songedit + 1) {
    if (sublevels[songedit] > 7) {
      if (sublevels[songedit] < 24) {
        selectpatterninsong();
      } else {
        selectsongnavarrows();
      }
    } else {
      actionSongTransport();
    }
  }
  if (navlevel == songedit + 2) {

    setpatterninsong();
    if (patternonsong[sublevels[songedit] - 8] > 0) {
      numberofpatonsong++;
    } else {
      numberofpatonsong = sublevels[songedit] - 8;
    }
  }

  if (sublevels[songedit] > 7) {
    showsongcell();
  }

  showpatonSongGrid();
  showsongnavarrows();
  dodisplay();
  songgridposselector();
  if (songplaying) {
    showplayheadprogress();
  }
  dodisplay();
}
void showsongnavarrows() {
  canvasBIG.setTextSize(2);

  canvasBIG.setCursor(115, 49);
  canvasBIG.print((char)26);
  if (songpage > 0) {
    canvasBIG.setCursor(2, 49);
    canvasBIG.print((char)27);
  }
}
void setpatterninsong() {
  Serial.println(songpage);
  patternonsong[(songpage * 16) + sublevels[songedit] - 8] = sublevels[songedit + 1];
  returntonav(songedit);
}

void songmodetopbar() {
  display.clearDisplay();
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvasBIG.setTextSize(1);
  drawtransport();
}

void showsongcell() {
  int lasongcell = patternonsong[(songpage * 16) + sublevels[songedit] - 8];
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(1);
  if (navlevel == songedit) {
    if (lasongcell > 0) {
      canvastitle.print(get_pattern_name(patterns_indexes[lasongcell - 1]));
    } else {
      canvastitle.print("Empty");
    }
  }
}

void selectormoveX() {
  songselectorX = 8 * (sublevels[songedit] - 8);
}

void songTransportSelector() {
  int startyp = 8;
  int ecart = 14;
  display.drawPixel(ecart * (sublevels[songedit]) + 6, startyp + 7, SSD1306_WHITE);
  display.drawPixel(ecart * (sublevels[songedit]) + 7, startyp + 6, SSD1306_WHITE);
  display.drawPixel(ecart * (sublevels[songedit]) + 7, startyp + 7, SSD1306_WHITE);
}

void showpatonSongGrid() {
  int lasongcell;
  for (int j = 0; j < 16; j++) {
    lasongcell = patternonsong[(songpage * 16) + j];
    if (lasongcell > 0) {
      display.fillRect(j * 8 + 1, 16 + 1, 8 - 2, 12 - 2, SSD1306_WHITE);
    }
  }
}

void selectpatterninsong() {
  navrange = patterns_count;
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(1);

  if (sublevels[songedit + 1] > 0) {
    canvastitle.print(get_pattern_name(patterns_indexes[sublevels[songedit + 1] - 1]));

  } else {
    canvastitle.print("Empty");
  }
}

void selectsongnavarrows() {
  if (navlevel == songedit) {

    if (sublevels[songedit] > 23) {
      canvasBIG.drawRoundRect(113 - (sublevels[songedit] - 24) * 113, 49, 14,
                              14, 2, SSD1306_WHITE);
    }
  }
  if (navlevel == songedit + 1) {
    if (sublevels[songedit] == 25 && songpage > 0) {
      songpage--;
      Serial.println(songpage);
    }
    if (sublevels[songedit] == 24 && songpage < 6) {
      songpage++;
      Serial.println(songpage);
    }
    returntonav(songedit);
  }
}

void songgridposselector() {
  if (sublevels[songedit] > 7) {
    if (sublevels[songedit] < 24) {

      // int startxp = 0 ;
      // int startyp = 16;
      int cellsizep = 8;
      int celltallp = 12;
      display.fillRect(songselectorX, songselectorY, cellsizep, celltallp,
                       SSD1306_INVERSE);
    } else {
      selectsongnavarrows();
    }
  }
}
