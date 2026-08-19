#include "SongsMenu.h"
#include "Triggers.h"
#include "Patterns.h"
#include "Voices.h"

SongEditorRouter* SongEditorRouter::self = nullptr;

SongEditorRouter::SongEditorRouter() {
                    self = this;
                    self->home_navrange=8 + 16;
                    self->relative_navlevel=2;
                    self->max_navlevel=5;
                    self->sublevels_address={3,0,0};
                    }
        

void SongEditorRouter::light_cc_change() {
          for (int i = 0; i < 32; i++) {
            if (bb.recorded_ccs[i] != 0 && bb.pots_controllers[i][lv.tickposition][1] != 127){
              _tt.moncontrollercc(1, bb.pots_controllers[i][lv.tickposition][0], bb.pots_controllers[i][lv.tickposition][1]);
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

void SongEditorRouter::use_pattern(){
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
            _tt.shutlineroff(gg.samplermidichannel,pp.sampler_off_pat[lv.tickposition].note);
              //flash_lines[i]->liner_off();
            }
          for (int i = 0; i < FLASH_LINERS_COUNT; i++) {

            if (pp.sampler_partition[i][lv.tickposition].note != 0) {
              play_sampler_line(i);
            }
          }
        }

void SongEditorRouter::playdasong() {
          //if (!gg.externalticker) {
            //metro0.reset();
          //}
          lv.songplaying = 1;
          loadsongpattern();
          Tocker.startticker();
        }

void SongEditorRouter::stopdasong() {
          lv.songplaying = 0;
          songplayhead = 0;
          Tocker.stopticker();
        }

void SongEditorRouter::pausedasong() {
          lv.songplaying = 0;
          Tocker.stopticker();
        }
void SongEditorRouter::showplayheadprogress() {
          dm.drawLine(songplayhead * 8, 16, songplayhead * 8, 64, SSD1306_INVERSE);
        }
void SongEditorRouter::loadsongpattern() {
  if (patternonsong[songplayhead] > 0) {
    _pt.catalog->displayable_offset = patternonsong[songplayhead] - 1  ;
    _pt.parsepattern();
  } else {
    stopdasong();
  }
}

void SongEditorRouter::actionSongTransport() {
          if (lv.sublevels[self->relative_navlevel] == 0) {
            stopdasong();
            playdasong();
          }
          if (lv.sublevels[self->relative_navlevel] == 2) {
            stopdasong();
          }
          if (lv.sublevels[self->relative_navlevel] == 3) {
            playdasong();
          }
          dm.returntonav(self->relative_navlevel, lv.navrange,lv.sublevels[self->relative_navlevel]);
        }

void SongEditorRouter::showsongnavarrows() {
          dm.canvasBIG.setTextSize(2);

          dm.canvasBIG.setCursor(115, 49);
          dm.canvasBIG.print((char)26);
          if (self->songpage > 0) {
            dm.canvasBIG.setCursor(2, 49);
            dm.canvasBIG.print((char)27);
          }
        }
void SongEditorRouter::setpatterninsong() {
          patternonsong[(self->songpage * 16) + lv.sublevels[self->relative_navlevel] - 8] = lv.sublevels[self->relative_navlevel + 1];
          dm.returntonav(self->relative_navlevel, lv.navrange,lv.sublevels[self->relative_navlevel]);
        }

void SongEditorRouter::songmodetopbar() {
          dm.clearDisplay();
          dm.clear_buffs();
          dm.canvasBIG.setTextSize(1);
          dm.drawtransport();
        }

void SongEditorRouter::showsongcell() {
          int lasongcell = patternonsong[(self->songpage * 16) + lv.sublevels[self->relative_navlevel] - 8];
          dm.canvastitle.setCursor(0, 0);
          dm.canvastitle.setTextSize(1);
          if (lv.navlevel == self->relative_navlevel) {
            if (lasongcell > 0) {
              dm.canvastitle.print(_pt.catalog->get_file_name(_pt.catalog->files_indexed[(lasongcell - 1)])); 
            } else {
              dm.canvastitle.print("Empty");
            }
          }
        }

void SongEditorRouter::selectormoveX() {
          songselectorX = 8 * (lv.sublevels[self->relative_navlevel] - 8);
        }

void SongEditorRouter::songTransportSelector() {
          int startyp = 8;
          int ecart = 14;
          dm.drawPixel(ecart * (lv.sublevels[self->relative_navlevel]) + 6, startyp + 7, SSD1306_WHITE);
          dm.drawPixel(ecart * (lv.sublevels[self->relative_navlevel]) + 7, startyp + 6, SSD1306_WHITE);
          dm.drawPixel(ecart * (lv.sublevels[self->relative_navlevel]) + 7, startyp + 7, SSD1306_WHITE);
        }

void SongEditorRouter::showpatonSongGrid() {
          int lasongcell;
          for (int j = 0; j < 16; j++) {
            lasongcell = patternonsong[(self->songpage * 16) + j];
            if (lasongcell > 0) {
              dm.fillRect(j * 8 + 1, 16 + 1, 8 - 2, 12 - 2, SSD1306_WHITE);
            }
          }
        }

void SongEditorRouter::selectpatterninsong() {
          lv.navrange = _pt.catalog->files_counter;
          dm.canvastitle.setCursor(0, 0);
          dm.canvastitle.setTextSize(1);

          if (lv.sublevels[self->relative_navlevel + 1] > 0) {
            dm.canvastitle.print(_pt.catalog->get_file_name(_pt.catalog->files_indexed[(lv.sublevels[self->relative_navlevel + 1] - 1)])); 
          } else {
            dm.canvastitle.print("Empty");
          }
        }

void SongEditorRouter::update_song_player() {
          if (lv.tickposition == PBARS - 1) {

              if (songplayhead < numberofpatonsong - 1) {
                songplayhead++;
              } else {
                songplayhead = 0;
              }

              loadsongpattern();
            }

        }

void SongEditorRouter::play_synth_line(int linei) {
          if (pp.synth_partition[linei][lv.tickposition].note != 0) {
            if (!synth_lines[linei]->activated) {
              synth_lines[linei]->liner_on(pp.synth_partition[linei][lv.tickposition].note, pp.synth_partition[linei][lv.tickposition].velocity);
            }
          }
        }

void SongEditorRouter::play_sampler_line(int linei) {
          if (pp.sampler_partition[linei][lv.tickposition].note != 0) {
            if (gg.Sampleassigned[pp.sampler_partition[linei][lv.tickposition].note] != 0 &&
                ((gg.samplermidichannel == 0) ||
                ((byte)gg.samplermidichannel == pp.sampler_partition[linei][lv.tickposition].channel))) {
                  _tt.initiateasamplerliner(pp.sampler_partition[linei][lv.tickposition].note, pp.sampler_partition[linei][lv.tickposition].velocity);
            }
          }
        }

void SongEditorRouter::selectsongnavarrows() {
          if (lv.navlevel == self->relative_navlevel) {

            if (lv.sublevels[self->relative_navlevel] > 23) {
              dm.canvasBIG.drawRoundRect(113 - (lv.sublevels[self->relative_navlevel] - 24) * 113, 49, 14,
                                      14, 2, SSD1306_WHITE);
            }
          }
          if (lv.navlevel == self->relative_navlevel + 1) {
            if (lv.sublevels[self->relative_navlevel] == 25 && self->songpage > 0) {
              self->songpage--;
            }
            if (lv.sublevels[self->relative_navlevel] == 24 && self->songpage < 6) {
              self->songpage++;
            }
            dm.returntonav(self->relative_navlevel, lv.navrange,lv.sublevels[self->relative_navlevel]);
          }
        }

void SongEditorRouter::songgridposselector() {
          if (lv.sublevels[self->relative_navlevel] > 7) {
            if (lv.sublevels[self->relative_navlevel] < 24) {

              // int startxp = 0 ;
              // int startyp = 16;
              int cellsizep = 8;
              int celltallp = 12;
              dm.fillRect(songselectorX, songselectorY, cellsizep, celltallp,
                              SSD1306_INVERSE);
            } else {
              selectsongnavarrows();
            }
          }
        }

void SongEditorRouter::Songmodepanel() {
  self->songselectorY = 16;
  self->songmodetopbar();
  if (lv.navlevel == self->relative_navlevel) {
    if (self->songpage > 0) {
      lv.navrange = 8 + 16 + 1;
    } else {
      lv.navrange = 8 + 16;
    }
    if (lv.sublevels[self->relative_navlevel] > 7) {

      // lv.navrange = 127/8 - 1;
      self->selectormoveX();
    }

    else {
      // songselectorY = 12 * lv.sublevels[self->relative_navlevel] + 16
      self->songTransportSelector();
    }
  }
  if (lv.navlevel == self->relative_navlevel + 1) {
    if (lv.sublevels[self->relative_navlevel] > 7) {
      if (lv.sublevels[self->relative_navlevel] < 24) {
        self->selectpatterninsong();
      } else {
        self->selectsongnavarrows();
      }
    } else {
      self->actionSongTransport();
    }
  }
  if (lv.navlevel == self->relative_navlevel + 2) {

    self->setpatterninsong();
    if (self->patternonsong[lv.sublevels[self->relative_navlevel] - 8] > 0) {
      self->numberofpatonsong++;
    } else {
      self->numberofpatonsong = lv.sublevels[self->relative_navlevel] - 8;
    }
  }

  if (lv.sublevels[self->relative_navlevel] > 7) {
    self->showsongcell();
  }

  self->showpatonSongGrid();
  self->showsongnavarrows();
  dm.dodisplay();
  self->songgridposselector();
  if (lv.songplaying) {
    self->showplayheadprogress();
  }
  dm.dodisplay();
}

SongMenuRouter* SongMenuRouter::self = nullptr;

SongMenuRouter::SongMenuRouter() {
          self = this;
          self->home_navrange=sg_labels_count-1;
          self->catalog = new FilesLister("SONGS/","SONG#",".TXT",draw_song_menu,self->home_navrange);
          self->relative_navlevel=1;
          self->max_navlevel=5;
          self->sublevels_address={3,0,0};
        }
void SongMenuRouter::show() {
          _route_nav[lv.navlevel-1]();
        }

void SongMenuRouter::route_navlevel() {
          _nav_song[lv.sublevels[1]]();
        }

void SongMenuRouter::lv1_wrapper(void (*func)()) {
          self->catalog->nav_one(1,1);
          if (lv.navlevel >= 3) {
            func();
            dm.returntonav(1, self->home_navrange,lv.sublevels[1]);
          }
        }
        
void SongMenuRouter::save_song(){
          lv1_wrapper(self->writedasong);
        }

void SongMenuRouter::writedasong() {
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

void SongMenuRouter::insert_int_in_song_file(File &song_filer,int leint, char *leparam) {
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

void SongMenuRouter::writeSong(File &song_filer) {
          song_filer.print("<Song>\n");
          insert_int_in_song_file(song_filer,_se.numberofpatonsong, (char*)"nums");
          for (byte i = 0; i < 99; i++) {
            insert_int_in_song_file(song_filer,_se.patternonsong[i], (char*)"songpat");
          }
        }
        
void SongMenuRouter::parseSong(){
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
              _se.patternonsong[i] = parser.Read_Int16();
            }
            parser.Reset();
            */
            song_filer.close();
        }

void SongMenuRouter::load_song() {
          lv1_wrapper(self->parseSong);
        }

void SongMenuRouter::song_nav_zero(){
          self->catalog->nav_zero();
        }

void SongMenuRouter::initializepatternonsong() {
          for (int j = 0; j < 99; j++) {
            _se.patternonsong[j] = 0;
          }
        }

void SongMenuRouter::clear_song_popup(){
          dm.clear_3();
          char messageconfirm[32] = "Delete Song ?";
          dm.doConfirmpanel((char *)messageconfirm);
          if (lv.navlevel >= self->relative_navlevel + 2) {
            if (lv.sublevels[self->relative_navlevel+1] == 1) {
              initializepatternonsong();
            }
            dm.returntonav(self->relative_navlevel, self->home_navrange,lv.sublevels[self->relative_navlevel]);
          }
        }

void SongMenuRouter::duplicate_song(){
          lv1_wrapper(self->copySong);
        }

void SongMenuRouter::copySong() {
          self->catalog->copyFile();
        }

void SongMenuRouter::remove_song(){
          lv1_wrapper(self->deleteSong);
        }
void SongMenuRouter::deleteSong() {
          self->catalog->deleteFile();
        }


void SongMenuRouter::shiftSongright(int leshifter) {
          for (int shifts = 0; shifts < leshifter; shifts++) {
            for (int i = 98; i >= 0; i--) {
              _se.patternonsong[i + 1] = _se.patternonsong[i];
              _se.patternonsong[i] = 0;
            }
          }
        }

void SongMenuRouter::shiftSongleft(int leshifter) {
          for (int shifts = 0; shifts < leshifter; shifts++) {
            for (int i = 1; i < 99; i++) {
              _se.patternonsong[i - 1] = _se.patternonsong[i];
              _se.patternonsong[i] = 0;
            }
          }
        }

void SongMenuRouter::doSongShifter() {
          int shifter=lv.sublevels[3];
          if (shifter - 16 > 0) {
            shiftSongleft(abs(shifter - 16));
          }
          if (shifter - 16 < 0) {
            shiftSongright(abs(shifter - 16));
          }
        }

void SongMenuRouter::showSongShifterdisplays() {
          lv.navrange = 32;
          dm.clean_title_1();
          dm.canvastitle.print("Shift Song");
          int latransposition;
          latransposition = 16 - lv.sublevels[self->relative_navlevel + 1];
          lv.sublevels[self->relative_navlevel + 2] = lv.sublevels[self->relative_navlevel + 1];
          dm.canvasBIG.setCursor(0, 16);
          dm.canvasBIG.setTextSize(2);
          if (latransposition > 0) {
            dm.canvasBIG.print("+");
          }
          if (latransposition == 0) {
            dm.canvasBIG.setCursor(8, 16);
          }
          dm.canvasBIG.print(latransposition);
          dm.dodisplay();
        }

void SongMenuRouter::shift_song(){
           showSongShifterdisplays();
          if (lv.navlevel >= self->relative_navlevel + 2) {
            doSongShifter();
            dm.returntonav(self->relative_navlevel, self->home_navrange,lv.sublevels[self->relative_navlevel]);
          }
        }


void SongMenuRouter::midi_clock_accumulator(){
          self->t_ += 1 ;
          if (!(self->t_% 24)) fine_cursor() ;
        }
void SongMenuRouter::fine_cursor(){
          self->x_ = (4+self->x_)%128 ;
          dm.drawFastVLine(self->x_, 0, 64, INVERSE);
          dm.drawFastVLine(self->x_-4, 0, 64, INVERSE);
          dm.display();
          self->t_ = 0 ;
        }
void SongMenuRouter::show_some_params(){
          lv.navrange = 32;
          dm.clean_title_1();
          dm.canvastitle.print("Params");
          //int latransposition;
          //latransposition = 16 - lv.sublevels[self->relative_navlevel + 1];
          //lv.sublevels[self->relative_navlevel + 2] = lv.sublevels[self->relative_navlevel + 1];
          dm.canvasBIG.setCursor(0, 16);
          dm.canvasBIG.setTextSize(1);
          dm.canvasBIG.setCursor(8, 16);
          dm.canvasBIG.print("block controls");
          dm.canvasBIG.setCursor(8, 16+10);
          dm.canvasBIG.print("Bpms");
          dm.canvasBIG.setCursor(8, 16+20);
          dm.canvasBIG.print("quantize");
          dm.canvasBIG.setCursor(8, 16+30);
          dm.canvasBIG.print("external clock");
          dm.dodisplay();
        }

void SongMenuRouter::song_params_panel(){
            show_some_params();
          if (lv.navlevel >= self->relative_navlevel + 2) {
            dm.returntonav(self->relative_navlevel, self->home_navrange,lv.sublevels[self->relative_navlevel]);
          }
        }

void SongMenuRouter::draw_song_menu(){
          const char* Songmenulabels[] = {
              "Edit", "Save", "Load", "Copy", "Delete", "Clear", "Params", "Shift"};
          dm.main_panel(Songmenulabels,1,sg_labels_count);
        }


