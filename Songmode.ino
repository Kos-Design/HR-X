int songedit = 2;
int songselectorX;
int songselectorY;
int patternonsong[99];
int songplayhead = 0;
byte numberofpatonsong;
class PatternsMenuRouter;
//extern SongMenuRouter* self;

extern PatternsMenuRouter _pt;
bool songplaying;

const byte navSongmenu = 1;

byte songs_indexes[99];
byte songs_count = 0 ;
const byte sng_size = 6;
String songs_names[sng_size];
byte songs_names_offset = 0 ;


class SongEditorRouter : public SectionHolder {
    public:
        SongEditorRouter() {
                    this->home_navrange=8 + 16;
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
          for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
            if (synth_off_pat[i][tickposition][1] != 0) {
              synth_lines[i]->liner_off();
            }
            // if ( i < SYNTH_LINERS_COUNT ) {
            if (synth_partition[i][tickposition][1] != 0) {
              play_synth_line(i);
            }

          }
          if (sampler_off_pat[tickposition][1] != 0) {
            shutlineroff(samplermidichannel,sampler_off_pat[tickposition][1]);
              //flash_lines[i]->liner_off();
            }
          for (int i = 0; i < flash_liners_count; i++) {

            if (sampler_partition[i][tickposition][1] != 0) {
              play_sampler_line(i);
            }
          }
        }

        void playdasong() {
          //if (!externalticker) {
            //metro0.reset();
          //}
          songplaying = 1;
          loadsongpattern();
          Tocker.startticker();
        }

        void stopdasong() {
          songplaying = 0;
          songplayhead = 0;
          Tocker.stopticker();
        }

        void pausedasong() {
          songplaying = 0;
          Tocker.stopticker();
        }
        void showplayheadprogress() {
          display.drawLine(songplayhead * 8, 16, songplayhead * 8, 64, SSD1306_INVERSE);
        }
        void loadsongpattern() {

          if (patternonsong[songplayhead] > 0) {
            call_set_pt_offset(patternonsong[songplayhead] - 1 );
            _pt.parsepattern();
          } else {
            stopdasong();
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
              canvastitle.print(get_pattern_name_from_pt(lasongcell - 1));
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
          navrange = _pt.catalog->files_counter;
          canvastitle.setCursor(0, 0);
          canvastitle.setTextSize(1);

          if (sublevels[songedit + 1] > 0) {
            canvastitle.print(get_pattern_name_from_pt(sublevels[songedit + 1] - 1));

          } else {
            canvastitle.print("Empty");
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
            if (Sampleassigned[sampler_partition[linei][tickposition][1]] != 0 &&
                ((samplermidichannel == 0) ||
                ((byte)samplermidichannel == sampler_partition[linei][tickposition][0]))) {
                  initiateasamplerliner(sampler_partition[linei][tickposition][1], sampler_partition[linei][tickposition][2]);
            }
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
          dm.dodisplay();
          songgridposselector();
          if (songplaying) {
            showplayheadprogress();
          }
          dm.dodisplay();
        }
};

SongEditorRouter _se = SongEditorRouter();

class SongMenuRouter : public SectionHolder {
    public:
        SongMenuRouter() {
          self = this;
          self->home_navrange=sg_labels_count-1;
          self->catalog = new FilesLister("SONGS/","SONG#",".TXT",draw_song_menu,self->home_navrange);
          self->relative_navlevel=1;
          self->max_navlevel=5;
          self->sublevels_address={3,0,0};
        }

        FilesLister *catalog;

        static void show() {
          _route_nav[navlevel-1]();
        }

        static void route_navlevel() {
          _nav_song[sublevels[1]]();
        }

        static void lv1_wrapper(void (*func)()) {
          self->catalog->nav_one(1,1);
          if (navlevel >= 3) {
            func();
            returntonav(1, self->home_navrange,sublevels[1]);
          }
        }
        
        static void save_song(){
          lv1_wrapper(self->writedasong);
        }

        static void writedasong() {
          if (locked_fileing)
            return;
          locked_fileing = 1 ;
          File song_filer ;
          if (self->catalog->new_file_mode) {
            song_filer = SD.open(self->catalog->get_new_file_name().c_str(), FILE_WRITE);
          } else {
            if (SD.exists(self->catalog->get_current_file_path(0).c_str())) {
              SD.remove(self->catalog->get_current_file_path(0).c_str());
            }
            song_filer = SD.open(self->catalog->get_current_file_path(0).c_str(), FILE_WRITE);
          }
          writeSong(song_filer);
          song_filer.close();
          locked_fileing = 0 ;
          self->catalog->list_files();
        }

        static void insert_int_in_song_file(File &song_filer,int leint, char *leparam) {
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

        static void writeSong(File &song_filer) {
          song_filer.print("<Song>\n");
          insert_int_in_song_file(song_filer,numberofpatonsong, (char*)"nums");
          for (byte i = 0; i < 99; i++) {
            insert_int_in_song_file(song_filer,patternonsong[i], (char*)"songpat");
          }
        }
        
        static void parseSong(){
          File song_filer = SD.open(self->catalog->get_current_file_path(0).c_str());
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

        static void load_song() {
          lv1_wrapper(self->parseSong);
        }

        static void song_nav_zero(){
          self->catalog->nav_zero();
        }

        static void initializepatternonsong() {
          for (int j = 0; j < 99; j++) {
            patternonsong[j] = 0;
          }
        }

        static void clear_song_popup(){
          dm.clear_3();
          char messageconfirm[32] = "Delete Song ?";
          doConfirmpanel((char *)messageconfirm);
          if (navlevel >= navSongmenu + 2) {
            if (sublevels[navSongmenu+1] == 1) {
              initializepatternonsong();
            }
            returntonav(navSongmenu, self->home_navrange,sublevels[navSongmenu]);
          }
        }

        static void duplicate_song(){
          lv1_wrapper(self->copySong);
        }

        static void copySong() {
          if (locked_fileing)
            return;
          locked_fileing = 1 ;
          File origin_file;
          File target_file;
          if (SD.exists(self->catalog->get_current_file_path(0).c_str())) {
            target_file = SD.open(self->catalog->get_new_file_name().c_str(), FILE_WRITE);
            origin_file = SD.open(self->catalog->get_current_file_path(0).c_str(), FILE_READ);
            size_t n;
            uint8_t buf[64];
            while ((n = origin_file.read(buf, sizeof(buf))) > 0) {
              target_file.write(buf, n);
            }
          }
          origin_file.close();
          target_file.close();
          locked_fileing = 0 ;
          self->catalog->list_files();

        }

        static void remove_song(){
          lv1_wrapper(self->deleteSong);
        }
        static void deleteSong() {
          if (SD.exists(self->catalog->get_current_file_path(0).c_str())) {
            SD.remove(self->catalog->get_current_file_path(0).c_str());
          }
        }


        static void shiftSongright(int leshifter) {
          for (int shifts = 0; shifts < leshifter; shifts++) {
            for (int i = 98; i >= 0; i--) {
              patternonsong[i + 1] = patternonsong[i];
              patternonsong[i] = 0;
            }
          }
        }

        static void shiftSongleft(int leshifter) {
          for (int shifts = 0; shifts < leshifter; shifts++) {
            for (int i = 1; i < 99; i++) {
              patternonsong[i - 1] = patternonsong[i];
              patternonsong[i] = 0;
            }
          }
        }

        static void doSongShifter() {
          int shifter=sublevels[3];
          if (shifter - 16 > 0) {
            shiftSongleft(abs(shifter - 16));
          }
          if (shifter - 16 < 0) {
            shiftSongright(abs(shifter - 16));
          }
        }

        static void showSongShifterdisplays() {
          navrange = 32;
          dm.clean_title_1();
          canvastitle.print("Shift Song");
          int latransposition;
          latransposition = 16 - sublevels[navSongmenu + 1];
          sublevels[navSongmenu + 2] = sublevels[navSongmenu + 1];
          canvasBIG.setCursor(0, 16);
          canvasBIG.setTextSize(2);
          if (latransposition > 0) {
            canvasBIG.print("+");
          }
          if (latransposition == 0) {
            canvasBIG.setCursor(8, 16);
          }
          canvasBIG.print(latransposition);
          dm.dodisplay();
        }

        static void shift_song(){
           showSongShifterdisplays();
          if (navlevel >= navSongmenu + 2) {
            doSongShifter();
            returntonav(navSongmenu, self->home_navrange,sublevels[navSongmenu]);
          }
        }

        static void show_some_params(){
          navrange = 32;
          dm.clean_title_1();
          canvastitle.print("Params");
          //int latransposition;
          //latransposition = 16 - sublevels[navSongmenu + 1];
          //sublevels[navSongmenu + 2] = sublevels[navSongmenu + 1];
          canvasBIG.setCursor(0, 16);
          canvasBIG.setTextSize(1);
          canvasBIG.setCursor(8, 16);
          canvasBIG.print("block controls");
          canvasBIG.setCursor(8, 16+10);
          canvasBIG.print("Bpms");
          canvasBIG.setCursor(8, 16+20);
          canvasBIG.print("quantize");
          canvasBIG.setCursor(8, 16+30);
          canvasBIG.print("external clock");
          dm.dodisplay();
        }

        static void song_params_panel(){
            show_some_params();
          if (navlevel >= navSongmenu + 2) {
            returntonav(navSongmenu, self->home_navrange,sublevels[navSongmenu]);
          }
        }

        static void draw_song_menu(){
          char Songmenulabels[sg_labels_count][12] = {
              "Edit", "Save", "Load", "Copy", "Delete", "Clear", "Params", "Shift"};
          byte startx = 5;
          byte starty = 16;
          char *textin = (char *)Songmenulabels[sublevels[navSongmenu]];
          canvastitle.setCursor(0, 0);
          canvastitle.setTextSize(2);
          canvastitle.println(textin);
          canvasBIG.setTextSize(1);
          // canvasBIG.fillScreen(SSD1306_BLACK);
          for (int i = 0; i < self->home_navrange - (sublevels[navSongmenu]); i++) {
            canvasBIG.setCursor(startx, starty + ((i)*10));
            canvasBIG.println(Songmenulabels[sublevels[navSongmenu] + 1 + i]);
          }
          for (int i = 0; i < sublevels[navSongmenu]; i++) {
            canvasBIG.setCursor(startx, (10 * (sg_labels_count - sublevels[navSongmenu]) + 6 + ((i)*10)));
            canvasBIG.println(Songmenulabels[i]);
          }

        }

        static constexpr void (*_route_nav[5])() = {&song_nav_zero, &route_navlevel,
                                                &route_navlevel, &route_navlevel, &route_navlevel};

    private:

      static constexpr void (*_nav_song[sg_labels_count])() = {&call_songeditor,&save_song, &load_song, &duplicate_song,
                                                      &remove_song, &clear_song_popup, &song_params_panel, &shift_song};
      static SongMenuRouter* self;
};

SongMenuRouter* SongMenuRouter::self = nullptr;
SongMenuRouter _sg;
