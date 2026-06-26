
int songedit = 2;
int songselectorX;
int songselectorY;
int patternonsong[99];
int songplayhead = 0;
byte numberofpatonsong;

bool songplaying;

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
}

void deleteSong() {
  if (SD.exists(get_current_song_path().c_str())) {
    SD.remove(get_current_song_path().c_str());
  }
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

void doSongShifter() {
  int shifter=sublevels[3];
  if (shifter - 16 > 0) {
    shiftSongleft(abs(shifter - 16));
  }
  if (shifter - 16 < 0) {
    shiftSongright(abs(shifter - 16));
  }
}

void showSongShifterdisplays() {
  navrange = 32;
  dm.clean_title_2();
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

void song_nav_zero(){
  dm.clear_3();
  reinitsublevels(navSongmenu + 1);
  navrange = truesizeofSongmenulabels - 1;
  use_song_list();
  dodisplay();

}

void song_nav_one(){
  dm.clear_3();
  reinitsublevels(navSongmenu + 1);
  navrange = songs_count;
  use_song_list();
  dodisplay();

}

void song_nav_two(){
  dm.clear_3();
  reinitsublevels(navSongmenu + 1);
  navrange = max(songs_count - 1 , 0);
  use_song_list();
  dodisplay();

}

void song_nav_three(){
  switch (sublevels[navSongmenu]) {
    //returntonav(navSongmenu, truesizeofSongmenulabels - 1);
    case 0:
      call_songeditor();
      // into edit already ;
      break;
    case 1:
      writedasong();
      returntonav(navSongmenu, truesizeofSongmenulabels - 1);
      // save();
      break;
    case 2:

      parseSong();
      returntonav(navSongmenu, truesizeofSongmenulabels - 1);
      break;
    case 3:
      copySong();
      returntonav(navSongmenu, truesizeofSongmenulabels - 1);
      break;

    case 4:
      deleteSong();
      returntonav(navSongmenu, truesizeofSongmenulabels - 1);
      break;

    case 5:
      initializepatternonsong();

      break;
    case 6:

      break;
    case 7:
      doSongShifter();

      break;

    default:
      break;
  }
  returntonav(navSongmenu, truesizeofSongmenulabels - 1,sublevels[navSongmenu]);
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

void clear_song_popup(){
  char messageconfirm[32] = "Delete Song ?";
  doConfirmpanel((char *)messageconfirm);
}
void song_params_panel(){
  byte tmp__;
}

void use_song_list(){
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
  draw_song_list();
}


void playdasong() {
  //if (!externalticker) {
    //metro0.reset();
  //}
  songplaying = 1;
  loadsongpattern();
  clocker.startticker();
}

void stopdasong() {
  songplaying = 0;
  songplayhead = 0;
  clocker.stopticker();
}

void pausedasong() {
  songplaying = 0;
  clocker.stopticker();
}
void showplayheadprogress() {
  display.drawLine(songplayhead * 8, 16, songplayhead * 8, 64, SSD1306_INVERSE);
}
void loadsongpattern() {

  if (patternonsong[songplayhead] > 0) {
    patterns_names_offset = patternonsong[songplayhead] - 1 ;
    call_parsepattern();
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
  returntonav(songedit, navrange,sublevels[songedit]);
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
  patternonsong[(songpage * 16) + sublevels[songedit] - 8] = sublevels[songedit + 1];
  returntonav(songedit, navrange,sublevels[songedit]);
}

void songmodetopbar() {
  display.clearDisplay();
  dm.clear_buffs();
  canvasBIG.setTextSize(1);
  drawtransport();
}

void showsongcell() {
  int lasongcell = patternonsong[(songpage * 16) + sublevels[songedit] - 8];
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(1);
  if (navlevel == songedit) {
    if (lasongcell > 0) {
      canvastitle.print(get_pattern_name_from_pt(patterns_indexes[lasongcell - 1]));
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
    canvastitle.print(get_pattern_name_from_pt(patterns_indexes[sublevels[songedit + 1] - 1]));

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
    }
    if (sublevels[songedit] == 24 && songpage < 6) {
      songpage++;
    }
    returntonav(songedit, navrange,sublevels[songedit]);
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



class SongEditorRouter : public SectionHolder {
    public:
        SongEditorRouter() {
                    this->home_navrange=truesizeofSongmenulabels-1;
                    this->relative_navlevel=1;
                    this->max_navlevel=5;
                    this->sublevels_address={3,0,0};
                    //home method not really used yet
                    //this->set_home(call_song_home);
                    }

        //changing_ccs[32][32][2] cc,val
        void light_cc_change() {
          for (int i = 0; i < 32; i++) {
            if (recorded_ccs[i] != 0 && pots_controllers[i][tickposition][1] != 127){
              moncontrollercc(1, pots_controllers[i][tickposition][0], pots_controllers[i][tickposition][1]);
            }

          }
        /*
          for (int i = 0; i < 128; i++) {
            if (cc_partition[i][tickposition] != 127) {
              moncontrollercc(1, i, cc_partition[i][tickposition]);
            }
          }
          */
        }

        void use_pattern(){
          light_cc_change();
          for (int i = 0; i < liners_count; i++) {
            if ((synth_off_pat[i][tickposition][1] != 0 && synth_off_pat[i][tickposition][0] == synthmidichannel)) {
              synth_lines[i]->liner_off();
            }
            // if ( i < liners_count ) {
            if (synth_partition[i][tickposition][1] != 0) {
              play_synth_line(i);
            }

            if (sampler_partition[i][tickposition][1] != 0) {
              play_sampler_line(i);
            }
          }
        }

        void update_song_player() {
          if (tickposition == pbars - 1) {

              if (songplayhead < numberofpatonsong - 1) {
                songplayhead++;
              } else {
                songplayhead = 0;
              }

              loadsongpattern();
            }

        }

        void play_synth_line(int linei) {
          if (synth_partition[linei][tickposition][1] != 0) {
            if (!synth_lines[linei]->activated) {
              synth_lines[linei]->liner_on(synth_partition[linei][tickposition][1], synth_partition[linei][tickposition][2]);
            }
          }
        }

        void play_sampler_line(int linei) {
          if (sampler_partition[linei][tickposition][1] != 0) {
            //        event2lineplayingfrom[linei][0]=
            //        sampler_partition[linei][tickposition][1];
            // channel
            // event2lineplayingfrom[linei][1]= sampler_partition[linei][tickposition][0];
            if (Sampleassigned[sampler_partition[linei][tickposition][1]] != 0 &&
                ((samplermidichannel == 0) ||
                ((byte)samplermidichannel == sampler_partition[linei][tickposition][0]))) {
              initiatesamplerline(nombreofSamplerliners - 1 - linei,
                                  (byte)samplermidichannel,
                                  sampler_partition[linei][tickposition][1],
                                  sampler_partition[linei][tickposition][2]);
              // MaNoteOn( (byte)samplermidichannel,
              // sampler_partition[linei][tickposition][1],
              // sampler_partition[linei][tickposition][2]) ;
            }
          }
        }

        void Songmodepanel() {
          songselectorY = 16;
          songmodetopbar();
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
};

SongEditorRouter _se = SongEditorRouter();


class SongMenuRouter : public SectionHolder {
    public:
        SongMenuRouter() {
                    this->home_navrange=truesizeofSongmenulabels-1;
                    this->relative_navlevel=1;
                    this->max_navlevel=5;
                    this->sublevels_address={3,0,0};
                    //home method not really used yet
                    this->set_home(call_song_home);
                    }

        void route_navlevel_1(){
            song_home();
        }
        void route_navlevel_2(){
            _lvl_2();
        }
        void displaySongmenu() {
          dm.clear_3();
          if (navlevel == navSongmenu) {
            song_nav_zero();
          }

          if ((sublevels[navSongmenu] == 0) && (navlevel > navSongmenu)) {
            call_songeditor();
          }
          if ((sublevels[navSongmenu] == 7) && (navlevel > navSongmenu)) {
            navrange = 32;
            showSongShifterdisplays();
            }

          if (sublevels[navSongmenu] != 0) {

            if (navlevel > navSongmenu + 1) {
              song_nav_three();
            }

            if (navlevel > navSongmenu) {

              if (sublevels[navSongmenu] >= 5) {
                returntonav(navSongmenu, truesizeofSongmenulabels - 1);
              }

              if (sublevels[navSongmenu] == 1) {
                navrange = songs_count;
              } else {
                navrange = max(songs_count - 1 , 0);
              }

              if (sublevels[navSongmenu] != 7) {
                use_song_list();
              }
            }

            // if (navlevel == navSongmenu ) {
            // dolistSongdisplay();
            // draw_song_list();

            // }
          }
          dodisplay();
        }

        void show() {
            (this->*SongMenuRouter::_route_nav[navlevel-1])();
        }

        void song_home(){
            _lvl_2();
        }
        void _lvl_2() {
            if (_nav_song[sublevels[1]]) {
                _nav_song[sublevels[1]]();
            }
        }

        void attach_nav_songs_menu(uint8_t index, void (*cb)())
        {
            if (index < truesizeofSongmenulabels)
                _nav_song[index] = cb;
        }

        using Action = void (SongMenuRouter::*)();
        static constexpr Action _route_nav[5] = {&SongMenuRouter::route_navlevel_1, &SongMenuRouter::route_navlevel_2,
                                                &SongMenuRouter::route_navlevel_2, &SongMenuRouter::route_navlevel_2, &SongMenuRouter::route_navlevel_2};

    private:

        void (*_nav_song[truesizeofSongmenulabels])() = {nullptr};
};

SongMenuRouter _sg = SongMenuRouter();


