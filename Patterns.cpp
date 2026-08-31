#include "Constants.h"
#include <cstring>
#include "core_pins.h"
#include "Voices.h"
#include "Patterns.h"
#include "Triggers.h"
#include "Functions.h"
#include "Presets.h"

MasterClock* MasterClock::self = nullptr;

MasterClock::MasterClock() {self = this;
                            self->timee = millis();
                            }

void MasterClock::click() {
            self->tick96++;
            memset(self->tic_toc, 1, sizeof(self->tic_toc));

            //if (!(self->tick96 % 2))
            //self->dispatch_ticks();
        }

void MasterClock::dispatch_ticks() {
    if ((self->tick96 % 96) == 0 && _callback_96 && self->tic_toc[0]){
      self->tic_toc[0] = false;
      _callback_96();
    }
    if ((self->tick96 % (96*4)) == 0 && _callback_long && self->tic_toc[1]){ 
      self->tic_toc[1] = false;
      _callback_long();
      
    }
    if ((self->tick96 % 2) == 0 && _callback_2 && self->tic_toc[2]){
      self->tic_toc[2] = false;
      _callback_2();
    }
    if ((self->tick96 % 24) == 0 && self->tic_toc[3]) {
      self->tic_toc[3] = false;

      if (!self->stop) {
          if (_callback_24){
              _callback_24();
          }
      }
      if (_callback_24_bis){
              _callback_24_bis();
          }
    }
    if ((self->tick96 % gg.period_303 == 0) && _callback_303 && self->tic_toc[4]){
      self->tic_toc[4] = false;
      _callback_303();
    }
    if (self->tick96 % gg.osc_refresher_period == 0 && _callback_oscilloscope && self->tic_toc[5]){
      self->tic_toc[5] = false;
      _callback_oscilloscope();
    }
    if ((self->tick96 % 3) == 0 && _callback_3 && self->tic_toc[6]){
      self->tic_toc[6] = false;
      _callback_3();
    }
    
}

void MasterClock::attach_2(void (*cb)()) {
            _callback_2 = cb;
        }
void MasterClock::attach_3(void (*cb)()) {
            _callback_3 = cb;
        }
void MasterClock::attach_oscilloscope(void (*cb)()) {
            _callback_oscilloscope = cb;
        }
void MasterClock::attach_303(void (*cb)()) {
            _callback_303 = cb;
        }

void MasterClock::attach_long(void (*cb)()) {
            _callback_long = cb;
        }

void MasterClock::attach_24(void (*cb)()) {
            _callback_24 = cb;
        }
void MasterClock::attach_24_bis(void (*cb)()) {
            _callback_24_bis = cb;
        }

void MasterClock::attach_96(void (*cb)()) {
            _callback_96 = cb;
        }

void MasterClock::stopticker() {
            lv.stoptick = 1;
            lv.recordCC = 0;
            self->stop = 1;
            // if (lv.patrecord) {
            // computelenghtmesureoffline();
            lv.patternOn = 0;
            lv.patrecord = 0;
            // lv.tickposition = 0 ;
        }

void MasterClock::startticker() {
    //TODO: reimplement external midi clock use
    //if (!gg.externalticker) {
    lv.stoptick = 0;
    self->stop = 0;
    lv.patternOn = 1;
}


CCEditor* CCEditor::self = nullptr;

CCEditor::CCEditor() {
                    self = this;
                    self->home_navrange=3;
                    self->relative_navlevel=2;
                    self->max_navlevel=5;
                    self->sublevels_address={4,0,0};
                    }

void CCEditor::show() {
          lv.navrange = 127;
          showleditcc();
          editlaccactionpath();
          dm.dodisplay();
        }

void CCEditor::route_navlevel_1(){
            //presets_nav_zero();
        }

void CCEditor::showleditcc() {
          int lavaluecc = 0;
          int lacellwidth = 128 / PBARS;
          int lestartyc = 16;
          float lacellratio = (62 - lestartyc) / 127.0;
          int lacellx = 0;
          int lacelly = 0;
          int lalinex1 = 0;
          int lalinex2 = 0;
          int laliney1 = 0;
          int laliney2 = 0;
          dm.clearDisplay();
          dm.canvasBIG.fillScreen(SSD1306_BLACK);

          if (lv.navlevel == 2) {
            dm.canvastitle.fillScreen(SSD1306_BLACK);
            dm.canvastitle.setCursor(0, 0);
            if (gg.midiknobassigned[lv.sublevels[2]] == 0) {
              dm.canvastitle.setTextSize(2);
              dm.canvastitle.print("Edit CC");
              if (lv.sublevels[2] < 100) {
                dm.canvastitle.print(" ");
              }
              if (lv.sublevels[2] < 10) {
                dm.canvastitle.print(" ");
              }
              dm.canvastitle.print(lv.sublevels[2]);
            } else {
              dm.canvastitle.setTextSize(1);
              dm.canvastitle.print("CC");
              dm.canvastitle.print(lv.sublevels[2]);
              dm.canvastitle.print(" ");
              dm.canvastitle.print((char *)ctl[gg.midiknobassigned[lv.sublevels[2]]].name);
            }
          }
          dm.canvasBIG.drawRect(0, 16, 128, 64, SSD1306_WHITE);

          for (int j = 0; j < PBARS; j++) {

            lavaluecc = (int)pp.cc_partition[lv.sublevels[2]][j];
            lacellx = 1 + j * lacellwidth;
            lacelly = 63 - lacellratio * lavaluecc;
            lalinex1 = lacellx;
            laliney1 = lacelly;
            if (lavaluecc < 128) {
              dm.canvasBIG.fillRect(lacellx, lacelly, 3, 3, SSD1306_WHITE);
              if (j > 0) {
                if ((int)pp.cc_partition[lv.sublevels[2]][j - 1] < 128) {
                  dm.canvasBIG.drawLine(lalinex2, laliney2, lalinex1, laliney1,
                                    SSD1306_WHITE);
                }
              }
            }
            lalinex2 = lalinex1;
            laliney2 = laliney1;
          }
          dm.dodisplay();
        }

void CCEditor::headerccedit() {
          dm.clearDisplay();
          dm.canvastitle.fillScreen(SSD1306_BLACK);
          dm.canvastitle.setCursor(0, 0);
          dm.canvastitle.setTextSize(1);
          dm.canvastitle.print("Edit CC ");
          dm.canvastitle.print(lv.sublevels[2]);
          dm.canvastitle.setCursor(0, 8);
          dm.canvastitle.print("Pos: ");
          dm.canvastitle.print(lv.sublevels[3]);
          dm.canvastitle.setCursor(90, 0);
          dm.canvastitle.setTextSize(2);
          if (pp.cc_partition[lv.sublevels[2]][lv.sublevels[3]] < 128) {
            dm.canvastitle.print(pp.cc_partition[lv.sublevels[2]][lv.sublevels[3]]);
          }
          if (pp.cc_partition[lv.sublevels[2]][lv.sublevels[3]] >= 128) {
            dm.canvastitle.print("Off");
          }
        }

void CCEditor::showvertlinecursor(int lavertpos) {
          dm.drawLine(lavertpos * (128 / PBARS), 16, lavertpos * (128 / PBARS), 64,
                          SSD1306_WHITE);
        }

void CCEditor::editlaccactionpath() {
          if (lv.navlevel == 3) {

            lv.navrange = PBARS - 1;

            lv.sublevels[4] = (int)pp.cc_partition[lv.sublevels[2]][lv.sublevels[3]];
            headerccedit();
            showvertlinecursor(lv.sublevels[3]);
          }
          if (lv.navlevel == 4) {

            lv.navrange = 127;
            pp.cc_partition[lv.sublevels[2]][lv.sublevels[3]] = (byte)lv.sublevels[4];
            headerccedit();
          }
          if (lv.navlevel > 4) {
            dm.returntonav(3,PBARS - 1,lv.sublevels[3]);
          }
        }


extern CCEditor _ce;

PatEditRouter* PatEditRouter::self = nullptr;

PatEditRouter::PatEditRouter() {
                    self = this;
                    self->home_navrange=3;
                    self->relative_navlevel=2;
                    self->max_navlevel=5;
                    self->sublevels_address={4,7,0};
                    }


void PatEditRouter::homer(){
          lv.navrange = TK_TYPES - 1;
          self->track_type = lv.sublevels[self->relative_navlevel];

          drawPatternRow();
          dolistpatternlineblocks();
          dm.setCursor(0, 0);
          String _t_type[TK_TYPES] = {"Synth","Sampler"};
          dm.print(_t_type[self->track_type]);

        }

void PatEditRouter::set_editor_to_synth(byte liner = self->local_line){
          self->_on_part = pp.synth_partition[liner] ;
          self->_off_part =  pp.synth_off_pat[liner] ;
          self->_temp_part = self->temp_synth_partition;
          self->liners_count = SYNTH_LINERS_COUNT;
          self->_length_part = pp.synth_notes_length[liner] ;
        }

void PatEditRouter::set_editor_to_sampler(byte liner = self->local_line){
         self->_on_part = pp.sampler_partition[liner] ;
          self->_off_part = pp.sampler_off_pat;
          self->_temp_part = self->temp_sampler_partition;
          self->liners_count = FLASH_LINERS_COUNT;
          self->_length_part = pp.flash_notes_length[liner] ;
        }

void PatEditRouter::show() {
          dm.clear_3();
          cell_events[lv.navlevel-self->relative_navlevel]();
          dm.dodisplay();
        }

void PatEditRouter::doshownoteline() {
          byte note_width = 4;
          byte note_height = 4;
          byte left_spacer = 0;
          byte top_spacer = 16;
          int ncell_x_length = 4;
          byte note_slct = lv.sublevels[self->relative_navlevel + 2];
          int ncell_y;
          dm.canvasBIG.setCursor(0, 0);
          dm.canvasBIG.print("Note:");
          dm.canvasBIG.print(lv.sublevels[self->relative_navlevel + 2]);
          dm.canvasBIG.print(" Pos:");
          dm.canvasBIG.print(lv.sublevels[self->relative_navlevel + 3]);
          for (int notelines = note_slct; notelines > note_slct - 12; notelines--) {
            for (int i = 0; i < PBARS; i++) {

              if ((bool)self->_temp_part[i].note && (int)self->_temp_part[i].note == notelines) {

                ncell_x_length = max(self->_length_part[i],4);
                ncell_y = top_spacer + (4 * (note_slct - notelines));

                dm.canvasBIG.fillRect(left_spacer + note_width * i, ncell_y,
                                  ncell_x_length, note_height, SSD1306_WHITE);
                dm.canvasBIG.drawLine(left_spacer + note_width * i, ncell_y,
                                  left_spacer + note_width * i, ncell_y + note_height,
                                  SSD1306_BLACK);
              }
            }
          }
        }

void PatEditRouter::drawPatternRow() {
          // rows of audio sources : synth, sampler, others
          dm.canvasBIG.drawFastHLine(0, 16 + lv.sublevels[self->relative_navlevel] * 8 + 3, 128, SSD1306_WHITE);
        }

void PatEditRouter::reshift_tracks_display() {
          //6 is max visible lines of 8px in 48px
          for (int i = 0 ; i < 6 ; i++) {
            set_editor_type[self->track_type]((i + lv.sublevels[self->relative_navlevel+1])%self->liners_count);
            for (int j = 0 ; j < PBARS ; j++) {
              self->visible_tracks[i][j] = (bool)(self->_on_part[j].velocity);
            }
          }
        }

void PatEditRouter::show_lines_events(){
          for (int i = 0 ; i < 6 ; i++) {
             for (int j = 0 ; j < PBARS ; j++) {
                dm.canvasBIG.fillRect( 4 * j, 16+(8*i), 4*((int)self->visible_tracks[i][j]), 8*((int)self->visible_tracks[i][j]), SSD1306_WHITE);
            }
          }
          dm.canvasBIG.drawFastHLine(0, 16 + 5, 128, SSD1306_INVERSE);
        }

void PatEditRouter::clearevented0(int lapatline) {

          for (int j = 0; j < PBARS; j++) {
            pp.track_cells[lapatline][j] = false;
          }
        }

void PatEditRouter::refresh_synth_track() {
          clearevented0(0);
          for (int linerrd = 0; linerrd < SYNTH_LINERS_COUNT; linerrd++) {
            for (int i = 0; i < PBARS; i++) {
              if (pp.synth_partition[linerrd][i].note != 0) {
                pp.track_cells[Synth][i] = true;
              }
            }
          }
        }

void PatEditRouter::refresh_flash_track() {
          clearevented0(1);
          for (int linerrd = 0; linerrd < FLASH_LINERS_COUNT; linerrd++) {

            for (int i = 0; i < PBARS; i++) {

              if (pp.sampler_partition[linerrd][i].note != 0) {
                pp.track_cells[Flash][i] = true;
              }
            }
          }
        }

void PatEditRouter::dolistpatternlineblocks() {
          for (int lapatline = 0; lapatline < TK_TYPES; lapatline++) {
            for (int i = 0; i < PBARS; i++) {
              if (pp.track_cells[lapatline][i]) {
                dm.canvasBIG.fillRect( 4*i + 1,16 + (8*lapatline) + 1, 2,6, SSD1306_INVERSE);
              }
            }
          }
        }

int PatEditRouter::grid_start_note() {
          /*
          byte min_note = 127 ;
          int averagenoteevent = 0;
          int nombrofnoteonliner = 0;
          //TODO: get the most visible notes range to set starting note val
          */
          return 45;
        }

void PatEditRouter::terminatenotesinbetween() {
          for (int i = min(lv.sublevels[self->relative_navlevel + 3] + 1,PBARS-1); i < lv.sublevels[self->relative_navlevel + 4]; i++) {
            self->_on_part[i] = {0,0,0};
            self->_off_part[i] = {0,0,0};
          }
        }

void PatEditRouter::sync_temp() {
          for (int i = 0; i < PBARS; i++) {
            self->_temp_part[i] = self->_on_part[i];
          }
        }

void PatEditRouter::drawCursorCol() {
          int xpos = (lv.sublevels[lv.navlevel] * 4);
          dm.drawLine(xpos, 0, xpos, 64-16, SSD1306_INVERSE);
        }

void PatEditRouter::track_selector() {
          reshift_tracks_display();
          lv.navrange = self->liners_count - 1;
          self->local_line = lv.sublevels[self->relative_navlevel+1];
          set_editor_type[self->track_type](self->local_line);
          show_track_header();
          show_lines_events();
          dm.dodisplay();
          lv.sublevels[self->relative_navlevel + 2] = self->grid_start_note();
        }

void PatEditRouter::show_track_header(){
          self->paterning = false ;

          dm.clearDisplay();
          String head_title[2]={"Synth","Flash"};
          dm.canvastitle.setCursor(0, 0);
          dm.canvastitle.setTextSize(1);
          dm.canvastitle.print(head_title[self->track_type]);
          dm.canvastitle.print(" Track ");
          dm.canvastitle.print(self->local_line + 1);
        }

void PatEditRouter::note_selector() {
          self->paterning = false ;

          dm.clearDisplay();
          lv.navrange = 127;
          sync_temp();
          doshownoteline();
          //dm.canvasBIG.drawLine(0, starty + 2, 127, starty + 2, SSD1306_INVERSE);
          draw_velobars();
          dm.dodisplay();
          lv.sublevels[self->relative_navlevel + 3] = lv.tickposition;
          if (lv.sublevels[self->relative_navlevel+2] == 0 ){
            lv.sublevels[self->relative_navlevel + 2] = self->grid_start_note();
          }
        }

void PatEditRouter::start_cell_setter() {
          self->paterning = true ;

          lv.previousnavlevel = lv.navlevel;
          //last level showing the noteline and its velocity
          dm.clearDisplay();
          lv.navrange = 31;
          dm.canvasBIG.fillRect(0, 32,127,64-32, SSD1306_BLACK);
          lv.sublevels[self->relative_navlevel + 4] = lv.sublevels[self->relative_navlevel + 3];
          sync_temp();
          doshownoteline();
          dm.canvasBIG.drawLine(0, 16 + 2, 127, 16 + 2, SSD1306_WHITE);
          drawCursorCol();
          draw_velobars();
          dm.dodisplay();
          lv.retroaction = lv.sublevels[self->relative_navlevel + 2] ;
        }

void PatEditRouter::draw_velobars(){
          int velobar ;
          for (int i = 0; i < PBARS; i++) {
            velobar = map(self->_temp_part[i].velocity,0,127,0,16);
            dm.canvasBIG.fillRect((i*(128/32)), 64-velobar,4 ,velobar, SSD1306_WHITE);
          }
        }

void PatEditRouter::stretch_cell_length() {
          self->paterning = false ;

          byte note_we_found = self->_on_part[lv.sublevels[self->relative_navlevel + 3]].velocity;
          if (note_we_found) {
            //delete previous key if present
            set_cell_at_pos(0,0,0);
            dm.returntonav(lv.navlevel-1,127,note_we_found);
          } else {
            self->addinglength = 1;
            self->_temp_part[lv.sublevels[self->relative_navlevel + 3]].channel = ((int[2]){gg.synthmidichannel,gg.samplermidichannel})[self->track_type];
            self->_temp_part[lv.sublevels[self->relative_navlevel + 3]].note = (byte)lv.sublevels[self->relative_navlevel + 2];
            self->_temp_part[lv.sublevels[self->relative_navlevel + 3]].velocity = (byte)64;

            lv.navrange = 31;
            self->_length_part[lv.sublevels[self->relative_navlevel + 3]] = max( (lv.sublevels[self->relative_navlevel + 4] - lv.sublevels[self->relative_navlevel + 3]) * 4,4);
            _refresher[self->track_type]();
            dm.clearDisplay();
            lv.sublevels[self->relative_navlevel + 5] = self->_temp_part[lv.sublevels[self->relative_navlevel + 3]].velocity;
            //doshownoteline2();
            doshownoteline();
            dm.canvasBIG.drawLine(0, 16 + 2, 127, 16 + 2, SSD1306_INVERSE);
            drawCursorCol();
            draw_velobars();
            dm.dodisplay();
          }
        }

void PatEditRouter::stretch_cell_velocity() {
          lv.navrange = 127;
          self->paterning = true ;

          self->addinglength = 0;
          self->_temp_part[lv.sublevels[self->relative_navlevel + 3]].velocity = lv.sublevels[self->relative_navlevel + 5];
          dm.clearDisplay();
          doshownoteline();
          dm.canvasBIG.drawLine(0, 16 + 2, 127, 16 + 2, SSD1306_INVERSE);
          draw_velobars();
          dm.dodisplay();
        }

void PatEditRouter::sanitize_synth_partition(){
          bool offUsed[SYNTH_LINERS_COUNT][PBARS] = {false};
          for (int line = 0; line < SYNTH_LINERS_COUNT; line++){
            for (int onStep = 0; onStep < PBARS; onStep++){
              // Skip empty Note On
              if (pp.synth_partition[line][onStep].velocity == 0)
                  continue;
              uint8_t note = pp.synth_partition[line][onStep].note;
              int latestStep = (onStep + (PBARS-1)) & (PBARS-1);
              for (int i = 1; i < PBARS; i++){
                int s = (onStep + i) & (PBARS-1);
                if (pp.synth_partition[line][s].velocity && pp.synth_partition[line][s].note == note) {
                  latestStep = (s + (PBARS-1)) & (PBARS-1);
                  break;
                }
              }
              int foundLine = -1;
              int foundStep = -1;
              bool found = false;
              int s = (onStep + 1) & (PBARS-1);
              while (!found) {
                for (int l = 0; l < SYNTH_LINERS_COUNT; l++) {
                  if (offUsed[l][s])
                    continue;

                  if (pp.synth_off_pat[l][s].note == note){
                    found = true;
                    foundLine = l;
                    foundStep = s;
                    break;
                  }
                }

                if (found || s == latestStep)
                    break;
                s = (s + 1) & (PBARS-1);
              }
              int targetStep = latestStep;
              while (targetStep != onStep) {
                if (pp.synth_off_pat[line][targetStep].note == 0 ||
                  (found && targetStep == foundStep && line == foundLine))
                  break;

                targetStep = (targetStep + (PBARS-1)) & (PBARS-1);
              }
              if (found){
                if (foundLine != line || foundStep != targetStep){
                  pp.synth_off_pat[foundLine][foundStep].channel = 0;
                  pp.synth_off_pat[foundLine][foundStep].note = 0;
                  pp.synth_off_pat[line][targetStep].channel = pp.synth_partition[line][onStep].channel;
                  pp.synth_off_pat[line][targetStep].note = note;
                }

                offUsed[line][targetStep] = true;
              }
              else {
                pp.synth_off_pat[line][targetStep].channel = pp.synth_partition[line][onStep].channel;
                pp.synth_off_pat[line][targetStep].note = note;
                offUsed[line][targetStep] = true;
              }
            }
          }
          for (int line = 0; line < SYNTH_LINERS_COUNT; line++) {
            for (int step = 0; step < PBARS; step++) {
              if (!offUsed[line][step]) {
                pp.synth_off_pat[line][step].channel = 0;
                pp.synth_off_pat[line][step].note = 0;
              }
            }
          }
        }

void PatEditRouter::sanitize_sampler_partition(){

          bool offUsed[FLASH_LINERS_COUNT][PBARS] = {false};

          for (int line = 0; line < FLASH_LINERS_COUNT; line++) {
            for (int onStep = 0; onStep < PBARS; onStep++){
              // Skip empty Note On
              if (pp.sampler_partition[line][onStep].velocity == 0)
                  continue;

              uint8_t note = pp.sampler_partition[line][onStep].note;
              int latestStep = (onStep + (PBARS-1)) & (PBARS-1);

              for (int i = 1; i < PBARS; i++){
                int s = (onStep + i) & (PBARS-1);
                if (pp.sampler_partition[line][s].velocity && pp.sampler_partition[line][s].note == note) {
                  latestStep = (s + (PBARS-1)) & (PBARS-1);
                  break;
                }
              }
              int foundLine = -1;
              int foundStep = -1;
              bool found = false;

              int s = (onStep + 1) & (PBARS-1);

              while (!found) {
                for (int l = 0; l < FLASH_LINERS_COUNT; l++) {
                  if (offUsed[l][s])
                    continue;

                  if (pp.sampler_off_pat[s].note == note){
                    found = true;
                    foundLine = l;
                    foundStep = s;
                    break;
                  }
                }

                if (found || s == latestStep)
                    break;
                s = (s + 1) & (PBARS-1);
              }

              int targetStep = latestStep;
              while (targetStep != onStep){
                if (pp.sampler_off_pat[targetStep].note == 0 ||
                    (found && targetStep == foundStep && line == foundLine))
                    break;

                targetStep = (targetStep + (PBARS-1)) & (PBARS-1);
              }
              if (found){
                if (foundLine != line || foundStep != targetStep) {
                  pp.sampler_off_pat[foundStep].channel = 0;
                  pp.sampler_off_pat[foundStep].note = 0;
                  pp.sampler_off_pat[targetStep].channel = pp.sampler_partition[line][onStep].channel;
                  pp.sampler_off_pat[targetStep].note = note;
                }
                offUsed[line][targetStep] = true;
              }
              else {
                pp.sampler_off_pat[targetStep].channel = pp.sampler_partition[line][onStep].channel;
                pp.sampler_off_pat[targetStep].note = note;
                offUsed[line][targetStep] = true;
              }
            }
          }
          for (int line = 0; line < FLASH_LINERS_COUNT; line++) {
            for (int step = 0; step < PBARS; step++) {
              if (!offUsed[line][step]) {
                pp.sampler_off_pat[step].channel = 0;
                pp.sampler_off_pat[step].note = 0;
              }
            }
          }
        }

void PatEditRouter::set_cell_at_pos(byte ch_, byte nt_, byte ve_){
  byte sub3 = lv.sublevels[self->relative_navlevel + 3];
  byte sub4 = lv.sublevels[self->relative_navlevel + 4];
  self->_on_part[sub3] = {ch_,nt_,ve_};
  byte laOffpos;
  self->_length_part[sub3] = max((sub4 - sub3) * 4,4);

  laOffpos = (sub3 + (self->_length_part[sub3] / 4))%PBARS;
  self->_off_part[laOffpos] = {ch_,nt_,0};
  terminatenotesinbetween();
  //off
  if (!ve_){

    self->_on_part[sub3] = {0,0,0};
    self->_length_part[sub3] = 0 ;
  }
  _sanitizer[self->track_type]();
}

void PatEditRouter::set_cell_velocity() {
  lv.previousnavlevel = lv.navlevel;
  byte sub3 = lv.sublevels[self->relative_navlevel + 3];
  byte sub4 = lv.sublevels[self->relative_navlevel + 4] ;
  set_cell_at_pos(((int[2]){gg.synthmidichannel,gg.samplermidichannel})[self->track_type],lv.sublevels[self->relative_navlevel + 2],self->_temp_part[sub3].velocity);
  if (!self->_temp_part[sub3].velocity){
    set_cell_at_pos(0,0,0);
  }
  _refresher[self->track_type]();
  dm.returntonav(self->relative_navlevel + 3,31,sub4);
}

void PatEditRouter::computelenghtmesureoffline_synth() {
  for (int linei = 0; linei < SYNTH_LINERS_COUNT; linei++) {
    for (int i = 0; i < PBARS; i++) {
      if (pp.synth_partition[linei][i].note != 0) {
        int laposof = self->getnextposofevent1Off_synth(linei, pp.synth_partition[linei][i].note, i);
        if (laposof < PBARS - 1) {
          pp.synth_notes_length[linei][i] = (laposof - i) * 4;
        } else {
          pp.synth_notes_length[linei][i] = (PBARS - i) * 4;
        }
      }
    }
  }
}

int PatEditRouter::getnextposofevent1Off_synth(int linei, byte lanote, int fromi) {
  for (int i = fromi + 1; i < PBARS; i++) {
    if (pp.synth_off_pat[linei][i].note == lanote) {
      return i;
    }
  }
  return (fromi + 1);
}

int PatEditRouter::getnextposofevent1Off_sampler(int linei, byte lanote, int fromi) {
  for (int i = fromi + 1; i < PBARS; i++) {
    if (pp.sampler_off_pat[i].note == lanote) {
      return i;
    }
  }
  return (fromi + 1);
}

void PatEditRouter::computelenghtmesureoffline_sampler() {
  for (int linei = 0; linei < FLASH_LINERS_COUNT; linei++) {
    for (int i = 0; i < PBARS; i++) {
      if (pp.sampler_partition[linei][i].note != 0) {
        int laposof = self->getnextposofevent1Off_sampler(linei, pp.sampler_partition[linei][i].note, i);
        if (laposof < PBARS - 1) {
          pp.flash_notes_length[linei][i] = (laposof - i) * 4;
        } else {
          pp.flash_notes_length[linei][i] = (PBARS - i) * 4;
        }
      }
    }
  }
}

void PatEditRouter::refresh_patterns(){
  _refresher[self->track_type]();
  _sanitizer[self->track_type]();
  computelenghtmesureoffline_synth();
  computelenghtmesureoffline_sampler();
}

extern PatEditRouter _pe;

POptionsRouter* POptionsRouter::self = nullptr;

POptionsRouter::POptionsRouter() {
                    self = this;
                    self->home_navrange = sizeofoptionspattern - 1;
                    self->relative_navlevel=2;
                    self->max_navlevel=5;
                    self->sublevels_address={4,0,0};
                    }

bool POptionsRouter::target_sampler = 1;
bool POptionsRouter::target_synth = 1;
bool POptionsRouter::target_ccs = 0;

bool* POptionsRouter::_targets[3] = {&target_sampler, &target_synth, &target_ccs};

void POptionsRouter::clearlapattern() {
  for (int i=0;i<3;i++) if (*_targets[i] || lv.songplaying) cleaners[i]();
  dm.returntonav(2, self->home_navrange,lv.sublevels[2]);
}

void POptionsRouter::clearCCline() {
  memset(pp.cc_partition, 127, sizeof(pp.cc_partition));
}

void POptionsRouter::clearsynthpatternline() {
  memset(pp.synth_partition, 0, sizeof(pp.synth_partition));
  memset(pp.synth_off_pat, 0, sizeof(pp.synth_off_pat));
  memset(pp.track_cells[Synth], 0, sizeof(pp.track_cells[Synth])); 
}

void POptionsRouter::merge_partitions() {
  for (int i=0;i<2;i++) if (*_targets[i]) mergers[i]();
  dm.returntonav(2, self->home_navrange,lv.sublevels[2]);
}

void POptionsRouter::merge_sampler_partition_liners(){
  byte note_encoutered ;
  byte liner_encoutered[FLASH_LINERS_COUNT] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ;

  for (int j=0;j<PBARS;j++){
    note_encoutered = 0 ;
    for (int i=0;i<FLASH_LINERS_COUNT;i++){
      if(pp.sampler_partition[i][j].note && pp.sampler_partition[i][j].velocity){
        liner_encoutered[note_encoutered] = i ;
        note_encoutered++;
      //si note on same tickpos, open new line, otherwise merge all liners count if one line only is noteon
      }
    }
    for (int i=0;i<note_encoutered;i++){
      if (liner_encoutered[i]!=i){
        //to avoid clearing current stage
        pp.sampler_partition[i][j].note = pp.sampler_partition[liner_encoutered[i]][j].note ;
        pp.sampler_partition[i][j].velocity = pp.sampler_partition[liner_encoutered[i]][j].velocity ;
        pp.sampler_partition[liner_encoutered[i]][j] = {0,0,0};
      }
    }
  }
}

void POptionsRouter::merge_synth_partition_liners(){
  byte note_encoutered ;
  byte liner_encoutered[SYNTH_LINERS_COUNT] = {0,0,0,0,0,0} ;

  for (int j=0;j<PBARS;j++){
    note_encoutered = 0 ;
    for (int i=0;i<SYNTH_LINERS_COUNT;i++){
      if(pp.synth_partition[i][j].note && pp.synth_partition[i][j].velocity){
        liner_encoutered[note_encoutered] = i ;
        note_encoutered++;
      //si note on same tickpos, open new line, otherwise merge all liners count if one line only is noteon
      }
    }
    for (int i=0;i<note_encoutered;i++){
      if (liner_encoutered[i]!=i){
        //to avoid clearing current stage
        pp.synth_partition[i][j].note = pp.synth_partition[liner_encoutered[i]][j].note ;
        pp.synth_partition[i][j].velocity = pp.synth_partition[liner_encoutered[i]][j].velocity ;
        pp.synth_partition[liner_encoutered[i]][j] = {0,0,0};
      }
    }
  }
}

void POptionsRouter::clearsamplerpatternline() {
  memset(pp.sampler_partition, 0, sizeof(pp.sampler_partition));
  memset(pp.sampler_off_pat, 0, sizeof(pp.sampler_off_pat));
  memset(pp.track_cells[Flash], 0, sizeof(pp.track_cells[Flash]));
}

const char* POptionsRouter::optionspatternlabels[] = {"Transpose", "Shift", "Clear", "Target", "Inter CC","Merge Pat"};

void POptionsRouter::show(){
  if (lv.navlevel == 2 ){
    lv.navrange = self->home_navrange ;
    dm.clean_title_2_1();
    dm.main_panel(optionspatternlabels,2,self->home_navrange);
    dm.dodisplay();
  }
  if (lv.navlevel >= 3 ){
    _pat_params[lv.sublevels[2]]();
  }
}

void POptionsRouter::toggle_interpol_cc() {
  self->interpolOn = !self->interpolOn;
  dm.returntonav(2, self->home_navrange,lv.sublevels[2]);
}

void POptionsRouter::dotransposesynth() {
  if (lv.sublevels[3] - 7 > 0) {
    shiftnotes1down(abs(lv.sublevels[3] - 7));
  }
  if (lv.sublevels[3] - 7 < 0) {
    shiftnotes1up(abs(lv.sublevels[3] - 7));
  }
  _pe.refresh_synth_track();
}

void POptionsRouter::dotransposeCC() {
  if (lv.sublevels[3] - 7 > 0) {
    shiftnotesCCdown(abs(lv.sublevels[3] - 7));
  }
  if (lv.sublevels[3] - 7 < 0) {
    shiftnotesCCup(abs(lv.sublevels[3] - 7));
  }
}

void POptionsRouter::doShifterCC() {
  if (lv.sublevels[3] - 16 > 0) {
    shiftnotesCCleft(abs(lv.sublevels[3] - 16));
  }
  if (lv.sublevels[3] - 16 < 0) {
    shiftnotesCCright(abs(lv.sublevels[3] - 16));
  }
}

void POptionsRouter::shiftnotesCCup(int leshifter) {
  for (int shifts = 0; shifts < leshifter; shifts++) {
    for (int i = 0; i < 128; i++) {
      for (int j = 0; j < PBARS; j++) {

        if (((int)pp.cc_partition[i][j] < 127) &&
            ((int)pp.cc_partition[i][j] > 0)) {

          pp.cc_partition[i][j]++;
        }
      }
    }
  }
}

void POptionsRouter::shiftnotesCCdown(int leshifter) {
  for (int shifts = 0; shifts < leshifter; shifts++) {
    for (int i = 0; i < 128; i++) {
      for (int j = 0; j < PBARS; j++) {

        if ((int)pp.cc_partition[i][j] > 0) {

          pp.cc_partition[i][j]--;
        }
      }
    }
  }
}

void POptionsRouter::shiftnotesCCright(int leshifter) {
  byte letempevent1;
  for (int shifts = 0; shifts < leshifter; shifts++) {
    for (int i = 0; i < 128; i++) {
      for (int j = PBARS - 1; j >= 0; j--) {

        if (j == PBARS - 1) {
          letempevent1 = pp.cc_partition[i][PBARS - 1];
          pp.cc_partition[i][j] = pp.cc_partition[i][j - 1];
        }
        if ((j > 0) && (j < PBARS - 1)) {
          pp.cc_partition[i][j] = pp.cc_partition[i][j - 1];
        }

        if (j == 0) {
          pp.cc_partition[i][j] = letempevent1;
        }
      }
    }
  }
}

void POptionsRouter::shiftnotesCCleft(int leshifter) {
  byte letempevent1;
  for (int shifts = 0; shifts < leshifter; shifts++) {
    for (int i = 0; i < 128; i++) {
      for (int j = 0; j < PBARS; j++) {
        if (j == 0) {
          letempevent1 = pp.cc_partition[i][0];
          pp.cc_partition[i][j] = pp.cc_partition[i][j + 1];
        }
        if ((j > 0) && (j < PBARS - 1)) {
          pp.cc_partition[i][j] = pp.cc_partition[i][j + 1];
        }
        if (j == PBARS - 1) {
          pp.cc_partition[i][j] = letempevent1;
        }
      }
    }
  }
}

void POptionsRouter::shiftnotes1up(int leshifter) {
  for (int shifts = 0; shifts < leshifter; shifts++) {
    for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
      for (int j = 0; j < PBARS; j++) {
        if (((int)pp.synth_partition[i][j].note < 127) &&
            ((int)pp.synth_partition[i][j].note > 2)) {
          pp.synth_partition[i][j].note++;
        }
        if (((int)pp.synth_off_pat[i][j].note < 127) &&
            ((int)pp.synth_off_pat[i][j].note > 2)) {
          pp.synth_off_pat[i][j].note++;
        }
      }
    }
  }
}

void POptionsRouter::shiftnotes1down(int leshifter) {
  for (int shifts = 0; shifts < leshifter; shifts++) {
    for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
      for (int j = 0; j < PBARS; j++) {
        if ((int)pp.synth_partition[i][j].note > 1) {
          pp.synth_partition[i][j].note--;
        }
        if ((int)pp.synth_off_pat[i][j].note > 1) {
          pp.synth_off_pat[i][j].note--;
        }
      }
    }
  }
}

void POptionsRouter::shiftnotes1right(int leshifter) {
  MidiEventer letempevent1[2];
  for (int shifts = 0; shifts < leshifter; shifts++) {
    for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
      for (int j = PBARS - 1; j >= 0; j--) {
        if (j == PBARS - 1) {
          pp.synth_partition[i][j] = pp.synth_partition[i][j - 1];
          letempevent1[0] = pp.synth_partition[i][PBARS - 1];
          letempevent1[1] = pp.synth_off_pat[i][PBARS - 1];
          pp.synth_off_pat[i][j] = pp.synth_off_pat[i][j - 1];
        }
        if ((j > 0) && (j < PBARS - 1)) {
          pp.synth_partition[i][j] = pp.synth_partition[i][j - 1];
          pp.synth_off_pat[i][j] = pp.synth_off_pat[i][j - 1];
        }
        if (j == 0) {
          pp.synth_partition[i][j] = letempevent1[0];
          pp.synth_off_pat[i][j] = letempevent1[1];
        }
      }
    }
  }
}

void POptionsRouter::shiftnotes1left(int leshifter) {
  MidiEventer letempevent1[2];
  for (int shifts = 0; shifts < leshifter; shifts++) {
    for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
      for (int j = 0; j < PBARS; j++) {
        if (j == 0) {
          letempevent1[0] = pp.synth_partition[i][0];
          pp.synth_partition[i][j] = pp.synth_partition[i][j + 1];
          letempevent1[1] = pp.synth_off_pat[i][0];
          pp.synth_off_pat[i][j] = pp.synth_off_pat[i][j + 1];
        }
        if ((j > 0) && (j < PBARS - 1)) {
          pp.synth_partition[i][j] = pp.synth_partition[i][j + 1];
          pp.synth_off_pat[i][j] = pp.synth_off_pat[i][j + 1];
        }
        if (j == PBARS - 1) {
          pp.synth_partition[i][j] = letempevent1[0];
          pp.synth_off_pat[i][j] = letempevent1[1];
        }
      }
    }
  }
}

void POptionsRouter::dotransposesampler() {
  if (lv.sublevels[3] - 7 > 0) {
    shiftnotes2down(abs(lv.sublevels[3] - 7));
  }
  if (lv.sublevels[3] - 7 < 0) {
    shiftnotes2up(abs(lv.sublevels[3] - 7));
  }
  _pe.refresh_flash_track();
}

void POptionsRouter::doShiftersampler() {
  if (lv.sublevels[3] - 16 > 0) {
    shiftnotes2left(abs(lv.sublevels[3] - 16));
  }
  if (lv.sublevels[3] - 16 < 0) {
    shiftnotes2right(abs(lv.sublevels[3] - 16));
  }
  _pe.refresh_flash_track();
}

void POptionsRouter::shiftnotes2up(int leshifter) {
  for (int shifts = 0; shifts < leshifter; shifts++) {
    for (int j = 0; j < PBARS; j++) {
      if (((int)pp.sampler_off_pat[j].note < 127) &&
          ((int)pp.sampler_off_pat[j].note > 2)) {
        pp.sampler_off_pat[j].note++;
      }
      for (int i = 0; i < FLASH_LINERS_COUNT; i++) {
        if (((int)pp.sampler_partition[i][j].note < 127) &&
            ((int)pp.sampler_partition[i][j].note > 2)) {
          pp.sampler_partition[i][j].note++;
        }
      }
    }
  }
}

void POptionsRouter::shiftnotes2down(int leshifter) {
  for (int shifts = 0; shifts < leshifter; shifts++) {
    for (int j = 0; j < PBARS; j++) {
      if ((int)pp.sampler_off_pat[j].note > 1) {
        pp.sampler_off_pat[j].note--;
      }
      for (int i = 0; i < FLASH_LINERS_COUNT; i++) {
        if ((int)pp.sampler_partition[i][j].note > 1) {

          pp.sampler_partition[i][j].note--;
        }
      }
    }
  }
}

void POptionsRouter::shiftnotes2right(int leshifter) {
  MidiEventer letempevent2[2];
  for (int shifts = 0; shifts < leshifter; shifts++) {
    for (int j = PBARS - 1; j >= 0; j--) {
      if (j == PBARS - 1) {
        letempevent2[1] = pp.sampler_off_pat[PBARS - 1];
        pp.sampler_off_pat[j] = pp.sampler_off_pat[j - 1];
      }
      if ((j > 0) && (j < PBARS - 1)) {
        pp.sampler_off_pat[j] = pp.sampler_off_pat[j - 1];
      }
      if (j == 0) {
        pp.sampler_off_pat[j] = letempevent2[1];
      }
      for (int i = 0; i < FLASH_LINERS_COUNT; i++) {
        if (j == PBARS - 1) {
          letempevent2[0] = pp.sampler_partition[i][PBARS - 1];
          pp.sampler_partition[i][j] = pp.sampler_partition[i][j - 1];
        }
        if ((j > 0) && (j < PBARS - 1)) {
            pp.sampler_partition[i][j] = pp.sampler_partition[i][j - 1];
        }
        if (j == 0) {
          pp.sampler_partition[i][j] = letempevent2[0];
        }
      }
    }
  }
}

void POptionsRouter::shiftnotes2left(int leshifter) {
  MidiEventer letempevent2[2];
  for (int shifts = 0; shifts < leshifter; shifts++) {
    for (int j = 0; j < PBARS; j++) {
      if (j == 0) {
        letempevent2[1] = pp.sampler_off_pat[0];
        pp.sampler_off_pat[j] = pp.sampler_off_pat[j + 1];
      }
      if ((j > 0) && (j < PBARS - 1)) {
        pp.sampler_off_pat[j] = pp.sampler_off_pat[j + 1];
      }
      if (j == PBARS - 1) {
        pp.sampler_off_pat[j] = letempevent2[1];
      }
      for (int i = 0; i < FLASH_LINERS_COUNT; i++) {
        if (j == 0) {
          letempevent2[0] = pp.sampler_partition[i][0];
          pp.sampler_partition[i][j] = pp.sampler_partition[i][j + 1];
        }
        if ((j > 0) && (j < PBARS - 1)) {
          pp.sampler_partition[i][j] = pp.sampler_partition[i][j + 1];
        }
        if (j == PBARS - 1) {
          pp.sampler_partition[i][j] = letempevent2[0];
        }
      }
    }
  }
}

void POptionsRouter::showtransposedisplays() {
  lv.navrange = 14;
  if (lv.navlevel > 3) {
    for (int i=0;i<3;i++) if (*_targets[i]) transposers[i]();
    dm.returntonav(2, self->home_navrange,lv.sublevels[2]);
    return;
  }

  dm.clean_title_2();
  dm.canvastitle.print((char *)optionspatternlabels[lv.sublevels[2]]);

  int latransposition;
  latransposition = 7 - lv.sublevels[3];
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

void POptionsRouter::doShiftersynth() {
  if (lv.sublevels[3] - 16 > 0) {
    shiftnotes1left(abs(lv.sublevels[3] - 16));
  }
  if (lv.sublevels[3] - 16 < 0) {

    shiftnotes1right(abs(lv.sublevels[3] - 16));
  }
  _pe.refresh_synth_track();
}

void POptionsRouter::showShifterdisplays() {
  lv.navrange = 31;
  if (lv.navlevel > 3) {
    for (int i=0;i<3;i++) if (*_targets[i]) shifters[i]();
    dm.returntonav(2, self->home_navrange,lv.sublevels[2]);
    return;
  }

  dm.clean_title_2();
  dm.canvastitle.print((char *)optionspatternlabels[lv.sublevels[2]]);

  int latransposition;
  latransposition = 16 - lv.sublevels[3];
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

void POptionsRouter::showlestargetdisplays() {
  lv.navrange = 2;
  const char* target_lbl[] = {"Synth","Sampler","CCs"};
  int ipos = lv.sublevels[3];
  //Serial.println((int)*_targets[ipos]);
  if (lv.navlevel > 3) {
    *_targets[ipos] = !*_targets[ipos];
    dm.returntonav(3, 2,ipos);
  }

  dm.clean_title_1_1();
  dm.canvastitle.print((char *)optionspatternlabels[lv.sublevels[2]]);
  for (int i = 0; i < 3; i++) {
    dm.canvasBIG.setCursor(10, i*10 +16);
    dm.canvasBIG.print(target_lbl[i]);
    dm.canvasBIG.drawRect(0, i*10 + 16, 6, 6, SSD1306_WHITE);
    if(*_targets[i]) dm.canvasBIG.fillRect(1, i*10 + 17, 5, 5, SSD1306_WHITE);
  }

  dm.dodisplay();
  dm.fillRect(2, 10*ipos + 18, 4, 4, SSD1306_INVERSE);
  //dm.fillRect(0, 10*ipos + 16, 48, 7, SSD1306_INVERSE);
  dm.display();
}

void POptionsRouter::optionspatterndisplays() {
  dm.clean_title_2();
  dm.canvastitle.print((char *)optionspatternlabels[lv.sublevels[2]]);
  dm.dodisplay();
}

extern POptionsRouter _po;

PatternsMenuRouter::PatternsMenuRouter() {
  self = this;
  self->home_navrange=sizeofpatternlistlabels-1;
  self->catalog = new FilesLister("PATTERNS/","PATTERN",".TXT",doPatternsmenu,self->home_navrange);
  self->catalog->left_margin = 73;
  self->relative_navlevel=1;
  self->max_navlevel=5;
  self->sublevels_address={4,0,0};
}

void PatternsMenuRouter::route_navlevel(){
          _nav_pattern[lv.sublevels[1]]();
        }

void PatternsMenuRouter::show() {
          _route_nav[lv.navlevel-1]();
        }

void PatternsMenuRouter::pattern_nav_zero(){
          _pe.paterning = false ;
          self->catalog->nav_zero();
        }

void PatternsMenuRouter::remove_pattern(){
          lv1_wrapper(self->deletepattern);
        }

void PatternsMenuRouter::duplicate_pattern(){
          lv1_wrapper(self->copypattern);
        }

void PatternsMenuRouter::load_pattern(){
          lv1_wrapper(self->parsepattern);
        }

void PatternsMenuRouter::save_pattern(){
          lv1_wrapper(self->writelemidi);
        }

void PatternsMenuRouter::lv1_wrapper(void (*func)()) {
          self->catalog->nav_one(1,1);

          if (lv.navlevel >= 3) {
            func();
            dm.returntonav(1, self->home_navrange,lv.sublevels[1]);
          }
        }

void PatternsMenuRouter::addnoteoff2next(byte lanotee, byte lapos) {
          if (lapos < PBARS - 1) {
            pp.sampler_off_pat[lapos + 1].channel = gg.samplermidichannel;
            pp.sampler_off_pat[lapos + 1].note = lanotee;
            pp.sampler_off_pat[lapos + 1].velocity = 0;
          }
          if (lapos == PBARS - 1) {
            pp.sampler_off_pat[0].channel = gg.samplermidichannel;
            pp.sampler_off_pat[0].note = lanotee;
            pp.sampler_off_pat[0].velocity = 0;
          }
        }

void PatternsMenuRouter::set_ccs() {
          // has to be reinitialized first
          for (int i = 0; i < PBARS; i++) {
            bb.recorded_ccs[i] = 0 ;
          }
          for (int i = 0; i < PBARS; i++) {
            for (int j = 0; j < 128; j++) {
              if (pp.cc_partition[j][i] != 127){
                for (int k = 0; k < PBARS; k++) {
                    if (bb.recorded_ccs[k] == 0 || bb.recorded_ccs[k] == j){
                      bb.recorded_ccs[k] = j ;
                      bb.pots_controllers[k][i][0] = j;
                      bb.pots_controllers[k][i][1] = pp.cc_partition[j][i];
                    }
                }
              }

            }
          }
        }
void PatternsMenuRouter::parsepattern() {
  
          if (lv.locked_fileing)
            return;
          lv.locked_fileing = 1 ;
          self->catalog->refresh_files_names();
          FsFile lepatternfile = SD.sdfs.open(self->catalog->get_current_file_path(0).c_str(), O_READ);
          if (lepatternfile) {
            lepatternfile.read((uint8_t*)&pp, sizeof(pp));
          }
          lepatternfile.close();
          
          _pe.refresh_patterns();
            set_ccs();
          
          lv.locked_fileing = 0 ;
}

void PatternsMenuRouter::doPatternsmenu() {
          const char* patternlistlabels[] = {
              "Edit", "Save", "Load", "Copy", "Delete", "Params", "Clear", "C-Edit"};
          
          dm.main_panel(patternlistlabels,1,self->home_navrange);
        }

void PatternsMenuRouter::deletepattern() {
  self->catalog->deleteFile();
}

void PatternsMenuRouter::copypattern() {
          File originpatternfile = SD.open(self->catalog->get_current_file_path(0).c_str());
          File mypatterntxtFile = SD.open(self->catalog->get_new_file_name().c_str(), FILE_WRITE);
          size_t n;
          uint8_t buf[64];
          if (originpatternfile) {
            while ((n = originpatternfile.read(buf, sizeof(buf))) > 0) {
              mypatterntxtFile.write(buf, n);
            }
            originpatternfile.close();
          }
          mypatterntxtFile.close();
          self->catalog->list_files();
        }

void PatternsMenuRouter::writelemidi() {
  if (lv.locked_fileing)
    return;
  lv.locked_fileing = 1 ;
  self->catalog->refresh_files_names();
  FsFile pat_filer ;
  if (self->catalog->new_file_mode) {
    pat_filer = SD.sdfs.open(self->catalog->get_new_file_name().c_str(), O_WRITE | O_CREAT | O_TRUNC);
  } else {
    const char* overwritee = self->catalog->get_current_file_path(0).c_str();
    self->catalog->deleteFile();
    pat_filer = SD.sdfs.open(overwritee, O_WRITE | O_CREAT | O_TRUNC);
  }
  if (pat_filer) {
    pat_filer.write((uint8_t*)&pp, sizeof(pp));
    pat_filer.close();

  }
  pat_filer.close();
  self->catalog->list_files();
  lv.locked_fileing = 0;
}

void PatternsMenuRouter::set_arp_type(){
  if (gg.arpegiatortype < ARP_TYPES) {
    gg.arpegiatorOn = 1;
  } else {
    gg.arpegiatorOn = 0;
    _tt.stopallnotes();
  }
}

PatternsMenuRouter* PatternsMenuRouter::self = nullptr;
