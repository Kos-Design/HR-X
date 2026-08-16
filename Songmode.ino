int songedit = 2;
int songselectorX;
int songselectorY;
int patternonsong[99];
int songplayhead = 0;
byte numberofpatonsong;
class PatternsMenuRouter;
//extern SongMenuRouter* self;

extern PatternsMenuRouter _pt;

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
        
        byte songpage = 0;

        //changing_ccs[32][32][2] cc,val
        void light_cc_change() {
          for (int i = 0; i < 32; i++) {
            if (bb.recorded_ccs[i] != 0 && bb.pots_controllers[i][lv.tickposition][1] != 127){
              moncontrollercc(1, bb.pots_controllers[i][lv.tickposition][0], bb.pots_controllers[i][lv.tickposition][1]);
            }

          }
        /*
          for (int i = 0; i < 128; i++) {
            if (pp.cc_partition[i][lv.tickposition] != 127) {
              moncontrollercc(1, i, pp.cc_partition[i][lv.tickposition]);
            }
          }
          */
        }

        void use_pattern(){
          light_cc_change();
          for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
            if (pp.synth_off_pat[i][lv.tickposition].note != 0) {
              synth_lines[i]->liner_off();
            }
            // if ( i < SYNTH_LINERS_COUNT ) {
            if (pp.synth_partition[i][lv.tickposition].note != 0) {
              play_synth_line(i);
            }

          }
          if (pp.sampler_off_pat[lv.tickposition].note != 0) {
            shutlineroff(gg.samplermidichannel,pp.sampler_off_pat[lv.tickposition].note);
              //flash_lines[i]->liner_off();
            }
          for (int i = 0; i < FLASH_LINERS_COUNT; i++) {

            if (pp.sampler_partition[i][lv.tickposition].note != 0) {
              play_sampler_line(i);
            }
          }
        }

        void playdasong() {
          //if (!gg.externalticker) {
            //metro0.reset();
          //}
          lv.songplaying = 1;
          loadsongpattern();
          Tocker.startticker();
        }

        void stopdasong() {
          lv.songplaying = 0;
          songplayhead = 0;
          Tocker.stopticker();
        }

        void pausedasong() {
          lv.songplaying = 0;
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
          if (lv.sublevels[songedit] == 0) {
            stopdasong();
            playdasong();
          }
          if (lv.sublevels[songedit] == 2) {
            stopdasong();
          }
          if (lv.sublevels[songedit] == 3) {
            playdasong();
          }
          dm.returntonav(songedit, lv.navrange,lv.sublevels[songedit]);
        }

        void showsongnavarrows() {
          canvasBIG.setTextSize(2);

          canvasBIG.setCursor(115, 49);
          canvasBIG.print((char)26);
          if (this->songpage > 0) {
            canvasBIG.setCursor(2, 49);
            canvasBIG.print((char)27);
          }
        }
        void setpatterninsong() {
          patternonsong[(this->songpage * 16) + lv.sublevels[songedit] - 8] = lv.sublevels[songedit + 1];
          dm.returntonav(songedit, lv.navrange,lv.sublevels[songedit]);
        }

        void songmodetopbar() {
          display.clearDisplay();
          dm.clear_buffs();
          canvasBIG.setTextSize(1);
          dm.drawtransport();
        }

        void showsongcell() {
          int lasongcell = patternonsong[(this->songpage * 16) + lv.sublevels[songedit] - 8];
          canvastitle.setCursor(0, 0);
          canvastitle.setTextSize(1);
          if (lv.navlevel == songedit) {
            if (lasongcell > 0) {
              canvastitle.print(get_pattern_name_from_pt(lasongcell - 1));
            } else {
              canvastitle.print("Empty");
            }
          }
        }

        void selectormoveX() {
          songselectorX = 8 * (lv.sublevels[songedit] - 8);
        }

        void songTransportSelector() {
          int startyp = 8;
          int ecart = 14;
          display.drawPixel(ecart * (lv.sublevels[songedit]) + 6, startyp + 7, SSD1306_WHITE);
          display.drawPixel(ecart * (lv.sublevels[songedit]) + 7, startyp + 6, SSD1306_WHITE);
          display.drawPixel(ecart * (lv.sublevels[songedit]) + 7, startyp + 7, SSD1306_WHITE);
        }

        void showpatonSongGrid() {
          int lasongcell;
          for (int j = 0; j < 16; j++) {
            lasongcell = patternonsong[(this->songpage * 16) + j];
            if (lasongcell > 0) {
              display.fillRect(j * 8 + 1, 16 + 1, 8 - 2, 12 - 2, SSD1306_WHITE);
            }
          }
        }

        void selectpatterninsong() {
          lv.navrange = _pt.catalog->files_counter;
          canvastitle.setCursor(0, 0);
          canvastitle.setTextSize(1);

          if (lv.sublevels[songedit + 1] > 0) {
            canvastitle.print(get_pattern_name_from_pt(lv.sublevels[songedit + 1] - 1));

          } else {
            canvastitle.print("Empty");
          }
        }

        void update_song_player() {
          if (lv.tickposition == PBARS - 1) {

              if (songplayhead < numberofpatonsong - 1) {
                songplayhead++;
              } else {
                songplayhead = 0;
              }

              loadsongpattern();
            }

        }

        void play_synth_line(int linei) {
          if (pp.synth_partition[linei][lv.tickposition].note != 0) {
            if (!synth_lines[linei]->activated) {
              synth_lines[linei]->liner_on(pp.synth_partition[linei][lv.tickposition].note, pp.synth_partition[linei][lv.tickposition].velocity);
            }
          }
        }

        void play_sampler_line(int linei) {
          if (pp.sampler_partition[linei][lv.tickposition].note != 0) {
            if (gg.Sampleassigned[pp.sampler_partition[linei][lv.tickposition].note] != 0 &&
                ((gg.samplermidichannel == 0) ||
                ((byte)gg.samplermidichannel == pp.sampler_partition[linei][lv.tickposition].channel))) {
                  initiateasamplerliner(pp.sampler_partition[linei][lv.tickposition].note, pp.sampler_partition[linei][lv.tickposition].velocity);
            }
          }
        }

        void selectsongnavarrows() {
          if (lv.navlevel == songedit) {

            if (lv.sublevels[songedit] > 23) {
              canvasBIG.drawRoundRect(113 - (lv.sublevels[songedit] - 24) * 113, 49, 14,
                                      14, 2, SSD1306_WHITE);
            }
          }
          if (lv.navlevel == songedit + 1) {
            if (lv.sublevels[songedit] == 25 && this->songpage > 0) {
              this->songpage--;
            }
            if (lv.sublevels[songedit] == 24 && this->songpage < 6) {
              this->songpage++;
            }
            dm.returntonav(songedit, lv.navrange,lv.sublevels[songedit]);
          }
        }

        void songgridposselector() {
          if (lv.sublevels[songedit] > 7) {
            if (lv.sublevels[songedit] < 24) {

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
          if (lv.navlevel == songedit) {
            if (this->songpage > 0) {
              lv.navrange = 8 + 16 + 1;
            } else {
              lv.navrange = 8 + 16;
            }
            if (lv.sublevels[songedit] > 7) {

              // lv.navrange = 127/8 - 1;
              selectormoveX();
            }

            else {
              // songselectorY = 12 * lv.sublevels[songedit] + 16
              songTransportSelector();
            }
          }
          if (lv.navlevel == songedit + 1) {
            if (lv.sublevels[songedit] > 7) {
              if (lv.sublevels[songedit] < 24) {
                selectpatterninsong();
              } else {
                selectsongnavarrows();
              }
            } else {
              actionSongTransport();
            }
          }
          if (lv.navlevel == songedit + 2) {

            setpatterninsong();
            if (patternonsong[lv.sublevels[songedit] - 8] > 0) {
              numberofpatonsong++;
            } else {
              numberofpatonsong = lv.sublevels[songedit] - 8;
            }
          }

          if (lv.sublevels[songedit] > 7) {
            showsongcell();
          }

          showpatonSongGrid();
          showsongnavarrows();
          dm.dodisplay();
          songgridposselector();
          if (lv.songplaying) {
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
        static constexpr uint8_t sg_labels_count = 8;

        FilesLister *catalog;

        static void show() {
          _route_nav[lv.navlevel-1]();
        }

        static void route_navlevel() {
          _nav_song[lv.sublevels[1]]();
        }

        static void lv1_wrapper(void (*func)()) {
          self->catalog->nav_one(1,1);
          if (lv.navlevel >= 3) {
            func();
            dm.returntonav(1, self->home_navrange,lv.sublevels[1]);
          }
        }
        
        static void save_song(){
          lv1_wrapper(self->writedasong);
        }

        static void writedasong() {
          if (lv.locked_fileing)
            return;
          lv.locked_fileing = 1 ;
          File song_filer ;
          if (self->catalog->new_file_mode) {
            song_filer = SD.open(self->catalog->get_new_file_name().c_str(), FILE_WRITE);
          } else {
            const char* overwritee = self->catalog->get_current_file_path(0).c_str();
            self->catalog->deleteFile();
            song_filer = SD.open(overwritee, FILE_WRITE);
          }
          writeSong(song_filer);
          song_filer.close();
          lv.locked_fileing = 0 ;
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
              
              
            }
            /*
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
            */
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
          if (lv.navlevel >= navSongmenu + 2) {
            if (lv.sublevels[navSongmenu+1] == 1) {
              initializepatternonsong();
            }
            dm.returntonav(navSongmenu, self->home_navrange,lv.sublevels[navSongmenu]);
          }
        }

        static void duplicate_song(){
          lv1_wrapper(self->copySong);
        }

        static void copySong() {
          self->catalog->copyFile();
        }

        static void remove_song(){
          lv1_wrapper(self->deleteSong);
        }
        static void deleteSong() {
          self->catalog->deleteFile();
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
          int shifter=lv.sublevels[3];
          if (shifter - 16 > 0) {
            shiftSongleft(abs(shifter - 16));
          }
          if (shifter - 16 < 0) {
            shiftSongright(abs(shifter - 16));
          }
        }

        static void showSongShifterdisplays() {
          lv.navrange = 32;
          dm.clean_title_1();
          canvastitle.print("Shift Song");
          int latransposition;
          latransposition = 16 - lv.sublevels[navSongmenu + 1];
          lv.sublevels[navSongmenu + 2] = lv.sublevels[navSongmenu + 1];
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
          if (lv.navlevel >= navSongmenu + 2) {
            doSongShifter();
            dm.returntonav(navSongmenu, self->home_navrange,lv.sublevels[navSongmenu]);
          }
        }
        int x_ = 0 ;
        int t_ = 0 ;

        static void midi_clock_accumulator(){
          self->t_ += 1 ;
          if (!(self->t_% 24)) fine_cursor() ;
        }
        static void fine_cursor(){
          self->x_ = (4+self->x_)%128 ;
          display.drawFastVLine(self->x_, 0, 64, INVERSE);
          display.drawFastVLine(self->x_-4, 0, 64, INVERSE);
          display.display();
          self->t_ = 0 ;
        }
        static void show_some_params(){
          lv.navrange = 32;
          dm.clean_title_1();
          canvastitle.print("Params");
          //int latransposition;
          //latransposition = 16 - lv.sublevels[navSongmenu + 1];
          //lv.sublevels[navSongmenu + 2] = lv.sublevels[navSongmenu + 1];
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
          if (lv.navlevel >= navSongmenu + 2) {
            dm.returntonav(navSongmenu, self->home_navrange,lv.sublevels[navSongmenu]);
          }
        }

        static void draw_song_menu(){
          const char* Songmenulabels[] = {
              "Edit", "Save", "Load", "Copy", "Delete", "Clear", "Params", "Shift"};
          dm.main_panel(Songmenulabels,1,sg_labels_count);
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
