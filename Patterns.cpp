#include "Patterns.h"
#include "MenuClasses.h"
#include "ParserLib.h"
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "FilesLister.h"

const int navlevelpatedit = 2;
const byte sizeofpatternlistlabels = 8;
const byte sizeofoptionspattern = 6;
const char optionspatternlabels[6][12] = {
    "Transpose", "Shift", "Clear", "Target", "Smooth CC","Merge Pat"};

bool targetNOsampler;
bool targetNOsynth;
bool targetNOcc;
bool interpolOn = 1;
short letempspattern;
int previousTp;
char leparsed[3];
unsigned long latimeline;

extern DisplayManager dm ;

CCEditor* CCEditor::self = nullptr;

CCEditor::CCEditor() {
                    self = this;
                    self->home_navrange=3;
                    self->relative_navlevel=2;
                    self->max_navlevel=5;
                    self->sublevels_address={4,0,0};
                    //home method not really used yet
                    //this->set_home(call_fx_mainpanel);
                    }

void CCEditor::show() {
          navrange = 127;
          showleditcc();
          editlaccactionpath();
          dm.dodisplay();
        }

void CCEditor::route_navlevel_1(){
            //presets_nav_zero();
        }

void CCEditor::showleditcc() {
          int lavaluecc = 0;
          int lacellwidth = 128 / pbars;
          int lestartyc = 16;
          float lacellratio = (62 - lestartyc) / 127.0;
          int lacellx = 0;
          int lacelly = 0;
          int lalinex1 = 0;
          int lalinex2 = 0;
          int laliney1 = 0;
          int laliney2 = 0;
          display.clearDisplay();
          canvasBIG.fillScreen(SSD1306_BLACK);

          if (navlevel == 2) {
            canvastitle.fillScreen(SSD1306_BLACK);
            canvastitle.setCursor(0, 0);
            if (midiknobassigned[sublevels[2]] == 0) {
              canvastitle.setTextSize(2);
              canvastitle.print("Edit CC");
              if (sublevels[2] < 100) {
                canvastitle.print(" ");
              }
              if (sublevels[2] < 10) {
                canvastitle.print(" ");
              }
              canvastitle.print(sublevels[2]);
            } else {
              canvastitle.setTextSize(1);
              canvastitle.print("CC");
              canvastitle.print(sublevels[2]);
              canvastitle.print(" ");
              canvastitle.print((char *)ctl[midiknobassigned[sublevels[2]]].name);
            }
          }
          canvasBIG.drawRect(0, 16, 128, 64, SSD1306_WHITE);

          for (int j = 0; j < pbars; j++) {

            lavaluecc = (int)cc_partition[sublevels[2]][j];
            lacellx = 1 + j * lacellwidth;
            lacelly = 63 - lacellratio * lavaluecc;
            lalinex1 = lacellx;
            laliney1 = lacelly;
            if (lavaluecc < 128) {
              canvasBIG.fillRect(lacellx, lacelly, 3, 3, SSD1306_WHITE);
              if (j > 0) {
                if ((int)cc_partition[sublevels[2]][j - 1] < 128) {
                  canvasBIG.drawLine(lalinex2, laliney2, lalinex1, laliney1,
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
          display.clearDisplay();
          canvastitle.fillScreen(SSD1306_BLACK);
          canvastitle.setCursor(0, 0);
          canvastitle.setTextSize(1);
          canvastitle.print("Edit CC ");
          canvastitle.print(sublevels[2]);
          canvastitle.setCursor(0, 8);
          canvastitle.print("Pos: ");
          canvastitle.print(sublevels[3]);
          canvastitle.setCursor(90, 0);
          canvastitle.setTextSize(2);
          if (cc_partition[sublevels[2]][sublevels[3]] < 128) {
            canvastitle.print(cc_partition[sublevels[2]][sublevels[3]]);
          }
          if (cc_partition[sublevels[2]][sublevels[3]] >= 128) {
            canvastitle.print("Off");
          }
        }

void CCEditor::showvertlinecursor(int lavertpos) {
          display.drawLine(lavertpos * (128 / pbars), 16, lavertpos * (128 / pbars), 64,
                          SSD1306_WHITE);
        }

void CCEditor::editlaccactionpath() {
          if (navlevel == 3) {

            navrange = pbars - 1;

            sublevels[4] = (int)cc_partition[sublevels[2]][sublevels[3]];
            headerccedit();
            showvertlinecursor(sublevels[3]);
          }
          if (navlevel == 4) {

            navrange = 127;
            cc_partition[sublevels[2]][sublevels[3]] = (byte)sublevels[4];
            headerccedit();
          }
          if (navlevel > 4) {
            returntonav(3,pbars - 1,sublevels[3]);
          }
        }


extern CCEditor _ce;

PatEditRouter* PatEditRouter::self = nullptr;

PatEditRouter::PatEditRouter() {
                    self = this;
                    this->home_navrange=3;
                    this->relative_navlevel=2;
                    this->max_navlevel=5;
                    this->sublevels_address={4,7,0};
                    }

void PatEditRouter::homer(){
          navrange = available_track_types - 1;
          self->track_type = sublevels[navlevelpatedit];

          drawPatternRow();
          dolistpatternlineblocks();
          display.setCursor(0, 0);
          String _t_type[available_track_types] = {"Synth","Sampler"};
          display.print(_t_type[self->track_type]);

        }

void PatEditRouter::set_editor_to_synth(byte liner = self->local_line){
          self->_on_part = synth_partition[liner] ;
          self->_off_part =  synth_off_pat[liner] ;
          self->_temp_part = temp_synth_partition;
          self->liners_count = SYNTH_LINERS_COUNT;
          self->_length_part = synth_notes_length[liner] ;
        }

void PatEditRouter::set_editor_to_sampler(byte liner = self->local_line){
         self->_on_part = sampler_partition[liner] ;
          self->_off_part = sampler_off_pat;
          self->_temp_part = temp_sampler_partition;
          self->liners_count = flash_liners_count;
          self->_length_part = flash_notes_length[liner] ;
        }

void PatEditRouter::show() {
          dm.clear_3();
          cell_events[navlevel-navlevelpatedit]();
          dm.dodisplay();
        }

void PatEditRouter::doshownoteline() {
          byte note_width = 4;
          byte note_height = 4;
          byte left_spacer = 0;
          byte top_spacer = 16;
          int ncell_x_length = 4;
          byte note_slct = sublevels[navlevelpatedit + 2];
          int ncell_y;
          canvasBIG.setCursor(0, 0);
          canvasBIG.print("Note:");
          canvasBIG.print(sublevels[navlevelpatedit + 2]);
          canvasBIG.print(" Pos:");
          canvasBIG.print(sublevels[navlevelpatedit + 3]);
          for (int notelines = note_slct; notelines > note_slct - 12; notelines--) {
            for (int i = 0; i < pbars; i++) {

              if ((bool)self->_temp_part[i][1] && (int)self->_temp_part[i][1] == notelines) {

                ncell_x_length = max(self->_length_part[i],4);
                ncell_y = top_spacer + (4 * (note_slct - notelines));

                canvasBIG.fillRect(left_spacer + note_width * i, ncell_y,
                                  ncell_x_length, note_height, SSD1306_WHITE);
                canvasBIG.drawLine(left_spacer + note_width * i, ncell_y,
                                  left_spacer + note_width * i, ncell_y + note_height,
                                  SSD1306_BLACK);
              }
            }
          }
        }

void PatEditRouter::drawPatternRow() {
          // rows of audio sources : synth, sampler, others
          canvasBIG.drawFastHLine(0, 16 + sublevels[navlevelpatedit] * 8 + 3, 128, SSD1306_WHITE);
        }

void PatEditRouter::reshift_tracks_display() {
          //6 is max visible lines of 8px in 48px
          for (int i = 0 ; i < 6 ; i++) {
            set_editor_type[self->track_type]((i + sublevels[navlevelpatedit+1])%self->liners_count);
            for (int j = 0 ; j < pbars ; j++) {
              self->visible_tracks[i][j] = (bool)(self->_on_part[j][2]);
            }
          }
        }

void PatEditRouter::show_lines_events(){
          for (int i = 0 ; i < 6 ; i++) {
             for (int j = 0 ; j < pbars ; j++) {
                canvasBIG.fillRect( 4 * j, 16+(8*i), 4*((int)self->visible_tracks[i][j]), 8*((int)self->visible_tracks[i][j]), SSD1306_WHITE);
            }
          }
          canvasBIG.drawFastHLine(0, 16 + 5, 128, SSD1306_INVERSE);
        }

void PatEditRouter::clearevented0(int lapatline) {

          for (int j = 0; j < pbars; j++) {
            track_cells[lapatline][j] = false;
          }
        }

void PatEditRouter::refresh_synth_track() {
          clearevented0(0);
          for (int linerrd = 0; linerrd < SYNTH_LINERS_COUNT; linerrd++) {
            for (int i = 0; i < pbars; i++) {
              if (synth_partition[linerrd][i][1] != 0) {
                track_cells[0][i] = true;
              }
            }
          }
        }

void PatEditRouter::refresh_flash_track() {
          clearevented0(1);
          for (int linerrd = 0; linerrd < flash_liners_count; linerrd++) {

            for (int i = 0; i < pbars; i++) {

              if (sampler_partition[linerrd][i][1] != 0) {
                track_cells[1][i] = true;
              }
            }
          }
        }

void PatEditRouter::dolistpatternlineblocks() {
          for (int lapatline = 0; lapatline < available_track_types; lapatline++) {
            for (int i = 0; i < pbars; i++) {
              if (track_cells[lapatline][i]) {
                canvasBIG.fillRect( 4*i + 1,16 + (8*lapatline) + 1, 2,6, SSD1306_INVERSE);
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
          for (int i = min(sublevels[navlevelpatedit + 3] + 1,pbars-1); i < sublevels[navlevelpatedit + 4]; i++) {
            self->_on_part[i][0] = 0;
            self->_on_part[i][1] = 0;
            self->_on_part[i][2] = 0;
            self->_off_part[i][1] = 0;
            self->_off_part[i][0] = 0;
          }
        }

void PatEditRouter::sync_temp() {
          for (int i = 0; i < pbars; i++) {
            self->_temp_part[i][0] = self->_on_part[i][0];
            self->_temp_part[i][2] = self->_on_part[i][2];
            self->_temp_part[i][1] = self->_on_part[i][1];
          }
        }

void PatEditRouter::drawCursorCol() {
          int xpos = (sublevels[navlevel] * 4);
          display.drawLine(xpos, 0, xpos, 64-16, SSD1306_INVERSE);
        }

void PatEditRouter::track_selector() {
          reshift_tracks_display();
          navrange = self->liners_count - 1;
          self->local_line = sublevels[navlevelpatedit+1];
          set_editor_type[self->track_type](self->local_line);
          show_track_header();
          show_lines_events();
          dm.dodisplay();
          sublevels[navlevelpatedit + 2] = self->grid_start_note();
        }

void PatEditRouter::show_track_header(){
          paterning = false ;

          display.clearDisplay();
          String head_title[2]={"Synth","Flash"};
          canvastitle.setCursor(0, 0);
          canvastitle.setTextSize(1);
          canvastitle.print(head_title[self->track_type]);
          canvastitle.print(" Track ");
          canvastitle.print(self->local_line + 1);
        }

void PatEditRouter::note_selector() {
          paterning = false ;

          display.clearDisplay();
          navrange = 127;
          sync_temp();
          doshownoteline();
          //canvasBIG.drawLine(0, starty + 2, 127, starty + 2, SSD1306_INVERSE);
          draw_velobars();
          dm.dodisplay();
          sublevels[navlevelpatedit + 3] = tickposition;
          if (sublevels[navlevelpatedit+2] == 0 ){
            sublevels[navlevelpatedit + 2] = self->grid_start_note();
          }
        }

void PatEditRouter::start_cell_setter() {
          paterning = true ;

          previousnavlevel = navlevel;
          //last level showing the noteline and its velocity
          display.clearDisplay();
          navrange = 31;
          canvasBIG.fillRect(0, 32,127,64-32, SSD1306_BLACK);
          sublevels[navlevelpatedit + 4] = sublevels[navlevelpatedit + 3];
          sync_temp();
          doshownoteline();
          canvasBIG.drawLine(0, 16 + 2, 127, 16 + 2, SSD1306_WHITE);
          drawCursorCol();
          draw_velobars();
          dm.dodisplay();
          retroaction = sublevels[navlevelpatedit + 2] ;
        }

void PatEditRouter::draw_velobars(){
          int velobar ;
          for (int i = 0; i < pbars; i++) {
            velobar = map(self->_temp_part[i][2],0,127,0,16);
            canvasBIG.fillRect((i*(128/32)), 64-velobar,4 ,velobar, SSD1306_WHITE);
          }
        }

void PatEditRouter::stretch_cell_length() {
          paterning = false ;

          byte note_we_found = self->_on_part[sublevels[navlevelpatedit + 3]][2];
          if (note_we_found) {
            //delete previous key if present
            set_cell_at_pos(0,0,0);
            returntonav(navlevel-1,127,note_we_found);
          } else {
            addinglenght = 1;
            self->_temp_part[sublevels[navlevelpatedit + 3]][0] = ((int[2]){synthmidichannel,samplermidichannel})[self->track_type];
            self->_temp_part[sublevels[navlevelpatedit + 3]][1] = (byte)sublevels[navlevelpatedit + 2];
            self->_temp_part[sublevels[navlevelpatedit + 3]][2] = (byte)64;

            navrange = 31;
            self->_length_part[sublevels[navlevelpatedit + 3]] = max( (sublevels[navlevelpatedit + 4] - sublevels[navlevelpatedit + 3]) * 4,4);
            _refresher[self->track_type]();
            display.clearDisplay();
            sublevels[navlevelpatedit + 5] = self->_temp_part[sublevels[navlevelpatedit + 3]][2];
            //doshownoteline2();
            doshownoteline();
            canvasBIG.drawLine(0, 16 + 2, 127, 16 + 2, SSD1306_INVERSE);
            drawCursorCol();
            draw_velobars();
            dm.dodisplay();
          }
        }

void PatEditRouter::stretch_cell_velocity() {
          navrange = 127;
          paterning = true ;

          addinglenght = 0;
          self->_temp_part[sublevels[navlevelpatedit + 3]][2] = sublevels[navlevelpatedit + 5];
          display.clearDisplay();
          doshownoteline();
          canvasBIG.drawLine(0, 16 + 2, 127, 16 + 2, SSD1306_INVERSE);
          draw_velobars();
          dm.dodisplay();
        }

void PatEditRouter::sanitize_synth_partition(){
          bool offUsed[SYNTH_LINERS_COUNT][pbars] = {false};
          for (int line = 0; line < SYNTH_LINERS_COUNT; line++){
            for (int onStep = 0; onStep < pbars; onStep++){
              // Skip empty Note On
              if (synth_partition[line][onStep][2] == 0)
                  continue;
              uint8_t note = synth_partition[line][onStep][1];
              int latestStep = (onStep + (pbars-1)) & (pbars-1);
              for (int i = 1; i < pbars; i++){
                int s = (onStep + i) & (pbars-1);
                if (synth_partition[line][s][2] && synth_partition[line][s][1] == note) {
                  latestStep = (s + (pbars-1)) & (pbars-1);
                  break;
                }
              }
              int foundLine = -1;
              int foundStep = -1;
              bool found = false;
              int s = (onStep + 1) & (pbars-1);
              while (!found) {
                for (int l = 0; l < SYNTH_LINERS_COUNT; l++) {
                  if (offUsed[l][s])
                    continue;

                  if (synth_off_pat[l][s][1] == note){
                    found = true;
                    foundLine = l;
                    foundStep = s;
                    break;
                  }
                }

                if (found || s == latestStep)
                    break;
                s = (s + 1) & (pbars-1);
              }
              int targetStep = latestStep;
              while (targetStep != onStep) {
                if (synth_off_pat[line][targetStep][1] == 0 ||
                  (found && targetStep == foundStep && line == foundLine))
                  break;

                targetStep = (targetStep + (pbars-1)) & (pbars-1);
              }
              if (found){
                if (foundLine != line || foundStep != targetStep){
                  synth_off_pat[foundLine][foundStep][0] = 0;
                  synth_off_pat[foundLine][foundStep][1] = 0;
                  synth_off_pat[line][targetStep][0] = synth_partition[line][onStep][0];
                  synth_off_pat[line][targetStep][1] = note;
                }

                offUsed[line][targetStep] = true;
              }
              else {
                synth_off_pat[line][targetStep][0] = synth_partition[line][onStep][0];
                synth_off_pat[line][targetStep][1] = note;
                offUsed[line][targetStep] = true;
              }
            }
          }
          for (int line = 0; line < SYNTH_LINERS_COUNT; line++) {
            for (int step = 0; step < pbars; step++) {
              if (!offUsed[line][step]) {
                synth_off_pat[line][step][0] = 0;
                synth_off_pat[line][step][1] = 0;
              }
            }
          }
        }

void PatEditRouter::sanitize_sampler_partition(){

          bool offUsed[flash_liners_count][pbars] = {false};

          for (int line = 0; line < flash_liners_count; line++) {
            for (int onStep = 0; onStep < pbars; onStep++){
              // Skip empty Note On
              if (sampler_partition[line][onStep][2] == 0)
                  continue;

              uint8_t note = sampler_partition[line][onStep][1];
              int latestStep = (onStep + (pbars-1)) & (pbars-1);

              for (int i = 1; i < pbars; i++){
                int s = (onStep + i) & (pbars-1);
                if (sampler_partition[line][s][2] && sampler_partition[line][s][1] == note) {
                  latestStep = (s + (pbars-1)) & (pbars-1);
                  break;
                }
              }
              int foundLine = -1;
              int foundStep = -1;
              bool found = false;

              int s = (onStep + 1) & (pbars-1);

              while (!found) {
                for (int l = 0; l < flash_liners_count; l++) {
                  if (offUsed[l][s])
                    continue;

                  if (sampler_off_pat[s][1] == note){
                    found = true;
                    foundLine = l;
                    foundStep = s;
                    break;
                  }
                }

                if (found || s == latestStep)
                    break;
                s = (s + 1) & (pbars-1);
              }

              int targetStep = latestStep;
              while (targetStep != onStep){
                if (sampler_off_pat[targetStep][1] == 0 ||
                    (found && targetStep == foundStep && line == foundLine))
                    break;

                targetStep = (targetStep + (pbars-1)) & (pbars-1);
              }
              if (found){
                if (foundLine != line || foundStep != targetStep) {
                  sampler_off_pat[foundStep][0] = 0;
                  sampler_off_pat[foundStep][1] = 0;
                  sampler_off_pat[targetStep][0] = sampler_partition[line][onStep][0];
                  sampler_off_pat[targetStep][1] = note;
                }
                offUsed[line][targetStep] = true;
              }
              else {
                sampler_off_pat[targetStep][0] = sampler_partition[line][onStep][0];
                sampler_off_pat[targetStep][1] = note;
                offUsed[line][targetStep] = true;
              }
            }
          }
          for (int line = 0; line < flash_liners_count; line++) {
            for (int step = 0; step < pbars; step++) {
              if (!offUsed[line][step]) {
                sampler_off_pat[step][0] = 0;
                sampler_off_pat[step][1] = 0;
              }
            }
          }
        }

void PatEditRouter::set_cell_at_pos(byte ch_, byte nt_, byte ve_){
          byte sub3 = sublevels[navlevelpatedit + 3];
          byte sub4 = sublevels[navlevelpatedit + 4];
          self->_on_part[sub3][0] = ch_;
          self->_on_part[sub3][1] = nt_;
          self->_on_part[sub3][2] = ve_;
          byte laOffpos;
          self->_length_part[sub3] = max((sub4 - sub3) * 4,4);

          laOffpos = (sub3 + (self->_length_part[sub3] / 4))%pbars;
          self->_off_part[laOffpos][0] = ch_;
          self->_off_part[laOffpos][1] = nt_;
          self->_off_part[laOffpos][2] = 0;
          terminatenotesinbetween();
          //off
          if (!ve_){

            self->_on_part[sub3][0] = 0;
            self->_on_part[sub3][1] = 0;
            self->_on_part[sub3][2] = 0;
            self->_length_part[sub3] = 0 ;
          }
          _sanitizer[self->track_type]();
        }

void PatEditRouter::set_cell_velocity() {
          previousnavlevel = navlevel;
          byte sub3 = sublevels[navlevelpatedit + 3];
          byte sub4 = sublevels[navlevelpatedit + 4] ;
          set_cell_at_pos(((int[2]){synthmidichannel,samplermidichannel})[self->track_type],sublevels[navlevelpatedit + 2],self->_temp_part[sub3][2]);
          if (!self->_temp_part[sub3][2]){
            set_cell_at_pos(0,0,0);
          }
          _refresher[self->track_type]();
          returntonav(navlevelpatedit + 3,31,sub4);
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
                    this->home_navrange=3;
                    this->relative_navlevel=2;
                    this->max_navlevel=5;
                    this->sublevels_address={4,0,0};
                    //home method not really used yet
                    //this->set_home(call_fx_mainpanel);
                    }

void POptionsRouter::clearlapattern() {
          if (!targetNOsynth || songplaying) {
            clearsynthpatternline();
          }
          if (!targetNOsampler || songplaying) {
            clearsamplerpatternline();
          }
          if (!targetNOcc || songplaying) {
            clearCCline();
          }
          // cc as well
        }

void POptionsRouter::clearCCline() {
          for (int j = 0; j < pbars; j++) {
            for (int i = 0; i < 128; i++) {

              cc_partition[i][j] = 127;
            }
          }
        }

void POptionsRouter::clearsynthpatternline() {
          for (int j = 0; j < pbars; j++) {
            for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {

              synth_partition[i][j][1] = 0;
              synth_partition[i][j][2] = 0;
              synth_partition[i][j][0] = 0;

              synth_off_pat[i][j][0] = 0;
              synth_off_pat[i][j][1] = 0;
            }
            track_cells[0][j] = 0;
          }
        }
void POptionsRouter::merge_synth_partition_liners(){
          byte note_encoutered ;
          byte liner_encoutered[SYNTH_LINERS_COUNT] = {0,0,0,0,0,0} ;

          for (int j=0;j<pbars;j++){
            note_encoutered = 0 ;
            for (int i=0;i<SYNTH_LINERS_COUNT;i++){
              if(synth_partition[i][j][1]!=0 && synth_partition[i][j][2]!=0){
                liner_encoutered[note_encoutered] = i ;
                note_encoutered++;
              //si note on same tickpos, open niw line, otherwise merge all liners count if one line only is noteon
              }
            }
            for (int i=0;i<note_encoutered;i++){
              if (liner_encoutered[i]!=i){
                //to avoid clearing current stage
                synth_partition[i][j][1] = synth_partition[liner_encoutered[i]][j][1] ;
                synth_partition[i][j][2] = synth_partition[liner_encoutered[i]][j][2] ;
                synth_partition[liner_encoutered[i]][j][1] = 0 ;
                synth_partition[liner_encoutered[i]][j][2] = 0 ;
              }
            }
          }
        }
void POptionsRouter::clearsamplerpatternline() {
          for (int j = 0; j < pbars; j++) {
            for (int i = 0; i < flash_liners_count; i++) {

              sampler_partition[i][j][1] = 0;
              sampler_partition[i][j][2] = 0;
              sampler_partition[i][j][0] = 0;
            }
            track_cells[1][j] = 0;
            sampler_off_pat[j][0] = 0;
            sampler_off_pat[j][1] = 0;
          }
        }
void POptionsRouter::optionspattern() {
          // size 4
          //TARGETS !!!
          // char optionspatternlabels[sizeofoptionspattern][12] = {"Transpose","Shift",
          // "Clear", "Target" };
          if (navlevel == 2) {
            navrange = sizeofoptionspattern - 1;
            optionspatterndisplays();

            if (sublevels[2] == 1) {
              sublevels[3] = 16;
            }

            if (sublevels[2] == 0) {
              sublevels[3] = 7;
            }
          }
          if (navlevel == 3) {

            if (sublevels[2] == 4) {
              // navrange = 14 ;
              interpolOn = !interpolOn;
              returntonav(2, sizeofoptionspattern - 1,sublevels[2]);
            }
            if (sublevels[2] == 5) {
              // navrange = 14 ;
              merge_synth_partition_liners();
              returntonav(2, sizeofoptionspattern - 1,sublevels[2]);
            }
            if (sublevels[2] == 2) {
              // navrange = 14 ;
              clearlapattern();
              returntonav(2, sizeofoptionspattern - 1,sublevels[2]);
            }

            if (sublevels[2] == 0) {
              navrange = 14;
              showtransposedisplays();
            }
            if (sublevels[2] == 3) {
              navrange = 6;
              showlestargetdisplays();
            }
            if (sublevels[2] == 1) {
              navrange = 31;
              showShifterdisplays();
            }
          }
          if (navlevel > 3) {
            if (sublevels[2] == 0) {
              dotranspose();
            }

            if (sublevels[2] == 1) {
              doShifter();
            }

            returntonav(2, sizeofoptionspattern - 1,sublevels[2]);

            
          }
        }

void POptionsRouter::dotranspose() {
          if (!targetNOsynth) {
            dotransposesynth();
          }
          if (!targetNOsampler) {
            dotransposesampler();
          }
          if (!targetNOcc) {
            dotransposeCC();
          }
        }

void POptionsRouter::doShifter() {
          if (!targetNOsynth) {
            doShiftersynth();
          }
          if (!targetNOsampler) {
            doShiftersampler();
          }
          if (!targetNOcc) {
            doShifterCC();
          }
        }

void POptionsRouter::dotransposesynth() {
          if (sublevels[3] - 7 > 0) {
            shiftnotes1down(abs(sublevels[3] - 7));
          }
          if (sublevels[3] - 7 < 0) {
            shiftnotes1up(abs(sublevels[3] - 7));
          }
          _pe.refresh_synth_track();
        }

void POptionsRouter::dotransposeCC() {
          if (sublevels[3] - 7 > 0) {
            shiftnotesCCdown(abs(sublevels[3] - 7));
          }
          if (sublevels[3] - 7 < 0) {
            shiftnotesCCup(abs(sublevels[3] - 7));
          }
        }

void POptionsRouter::doShifterCC() {
          if (sublevels[3] - 16 > 0) {
            shiftnotesCCleft(abs(sublevels[3] - 16));
          }
          if (sublevels[3] - 16 < 0) {
            shiftnotesCCright(abs(sublevels[3] - 16));
          }
        }

void POptionsRouter::shiftnotesCCup(int leshifter) {
          for (int shifts = 0; shifts < leshifter; shifts++) {
            for (int i = 0; i < 128; i++) {
              for (int j = 0; j < pbars; j++) {

                if (((int)cc_partition[i][j] < 127) &&
                    ((int)cc_partition[i][j] > 0)) {

                  cc_partition[i][j]++;
                }
              }
            }
          }
        }

void POptionsRouter::shiftnotesCCdown(int leshifter) {

          for (int shifts = 0; shifts < leshifter; shifts++) {
            for (int i = 0; i < 128; i++) {
              for (int j = 0; j < pbars; j++) {

                if ((int)cc_partition[i][j] > 0) {

                  cc_partition[i][j]--;
                }
              }
            }
          }
        }

void POptionsRouter::shiftnotesCCright(int leshifter) {
          byte letempevent1;
          for (int shifts = 0; shifts < leshifter; shifts++) {
            for (int i = 0; i < 128; i++) {
              for (int j = pbars - 1; j >= 0; j--) {

                if (j == pbars - 1) {
                  letempevent1 = cc_partition[i][pbars - 1];
                  cc_partition[i][j] = cc_partition[i][j - 1];
                }
                if ((j > 0) && (j < pbars - 1)) {
                  cc_partition[i][j] = cc_partition[i][j - 1];
                }

                if (j == 0) {
                  cc_partition[i][j] = letempevent1;
                }
              }
            }
          }
        }

void POptionsRouter::shiftnotesCCleft(int leshifter) {

          byte letempevent1;
          for (int shifts = 0; shifts < leshifter; shifts++) {

            for (int i = 0; i < 128; i++) {
              for (int j = 0; j < pbars; j++) {

                if (j == 0) {
                  letempevent1 = cc_partition[i][0];
                  cc_partition[i][j] = cc_partition[i][j + 1];
                }
                if ((j > 0) && (j < pbars - 1)) {
                  cc_partition[i][j] = cc_partition[i][j + 1];
                }
                if (j == pbars - 1) {
                  cc_partition[i][j] = letempevent1;
                }
              }
            }
          }
        }

void POptionsRouter::shiftnotes1up(int leshifter) {
          for (int shifts = 0; shifts < leshifter; shifts++) {
            for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
              for (int j = 0; j < pbars; j++) {
                if (((int)synth_partition[i][j][1] < 127) &&
                    ((int)synth_partition[i][j][1] > 2)) {

                  synth_partition[i][j][1]++;
                }
                if (((int)synth_off_pat[i][j][1] < 127) &&
                    ((int)synth_off_pat[i][j][1] > 2)) {

                  synth_off_pat[i][j][1]++;
                }
              }
            }
          }
        }

void POptionsRouter::shiftnotes1down(int leshifter) {
          for (int shifts = 0; shifts < leshifter; shifts++) {

            for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
              for (int j = 0; j < pbars; j++) {

                if ((int)synth_partition[i][j][1] > 1) {

                  synth_partition[i][j][1]--;
                }
                if ((int)synth_off_pat[i][j][1] > 1) {

                  synth_off_pat[i][j][1]--;
                }
              }
            }
          }
        }

void POptionsRouter::shiftnotes1right(int leshifter) {
          byte letempevent1[2][3];
          for (int shifts = 0; shifts < leshifter; shifts++) {
            for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
              for (int j = pbars - 1; j >= 0; j--) {

                if (j == pbars - 1) {

                  for (int k = 0; k < 3; k++) {
                    letempevent1[0][k] = synth_partition[i][pbars - 1][k];
                    letempevent1[1][k] = synth_off_pat[i][pbars - 1][k];
                    synth_partition[i][j][k] = synth_partition[i][j - 1][k];
                    synth_off_pat[i][j][k] = synth_off_pat[i][j - 1][k];
                  }
                }
                if ((j > 0) && (j < pbars - 1)) {
                  for (int k = 0; k < 3; k++) {
                    synth_partition[i][j][k] = synth_partition[i][j - 1][k];
                    synth_off_pat[i][j][k] = synth_off_pat[i][j - 1][k];
                  }
                }

                if (j == 0) {

                  for (int k = 0; k < 3; k++) {

                    synth_off_pat[i][j][k] = letempevent1[1][k];
                    synth_partition[i][j][k] = letempevent1[0][k];
                  }
                }
              }
            }
          }
        }

void POptionsRouter::shiftnotes1left(int leshifter) {

          byte letempevent1[2][3];
          for (int shifts = 0; shifts < leshifter; shifts++) {

            for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
              for (int j = 0; j < pbars; j++) {

                if (j == 0) {

                  for (int k = 0; k < 3; k++) {
                    letempevent1[0][k] = synth_partition[i][0][k];
                    letempevent1[1][k] = synth_off_pat[i][0][k];

                    synth_partition[i][j][k] = synth_partition[i][j + 1][k];
                    synth_off_pat[i][j][k] = synth_off_pat[i][j + 1][k];
                  }
                }
                if ((j > 0) && (j < pbars - 1)) {
                  for (int k = 0; k < 3; k++) {
                    synth_partition[i][j][k] = synth_partition[i][j + 1][k];
                    synth_off_pat[i][j][k] = synth_off_pat[i][j + 1][k];
                  }
                }

                if (j == pbars - 1) {
                  for (int k = 0; k < 3; k++) {

                    synth_off_pat[i][j][k] = letempevent1[1][k];
                    synth_partition[i][j][k] = letempevent1[0][k];
                  }
                }
              }
            }
          }
        }

void POptionsRouter::dotransposesampler() {
          if (sublevels[3] - 7 > 0) {
            shiftnotes2down(abs(sublevels[3] - 7));
          }
          if (sublevels[3] - 7 < 0) {

            shiftnotes2up(abs(sublevels[3] - 7));
          }
          call_refresh_flash_track();
        }

void POptionsRouter::doShiftersampler() {
          if (sublevels[3] - 16 > 0) {
            shiftnotes2left(abs(sublevels[3] - 16));
          }
          if (sublevels[3] - 16 < 0) {

            shiftnotes2right(abs(sublevels[3] - 16));
          }
          call_refresh_flash_track();
        }

void POptionsRouter::shiftnotes2up(int leshifter) {

          for (int shifts = 0; shifts < leshifter; shifts++) {

            for (int j = 0; j < pbars; j++) {
              if (((int)sampler_off_pat[j][1] < 127) &&
                  ((int)sampler_off_pat[j][1] > 2)) {
                sampler_off_pat[j][1]++;
              }
              for (int i = 0; i < flash_liners_count; i++) {
                if (((int)sampler_partition[i][j][1] < 127) &&
                    ((int)sampler_partition[i][j][1] > 2)) {

                  sampler_partition[i][j][1]++;
                }
              }
            }
          }
        }

void POptionsRouter::shiftnotes2down(int leshifter) {
          for (int shifts = 0; shifts < leshifter; shifts++) {
            for (int j = 0; j < pbars; j++) {
              if ((int)sampler_off_pat[j][1] > 1) {
                sampler_off_pat[j][1]--;
              }
              for (int i = 0; i < flash_liners_count; i++) {
                if ((int)sampler_partition[i][j][1] > 1) {

                  sampler_partition[i][j][1]--;
                }
              }
            }
          }
        }

void POptionsRouter::shiftnotes2right(int leshifter) {
          byte letempevent2[2][3];
          for (int shifts = 0; shifts < leshifter; shifts++) {

            for (int j = pbars - 1; j >= 0; j--) {
              if (j == pbars - 1) {

                for (int k = 0; k < 3; k++) {

                  letempevent2[1][k] = sampler_off_pat[pbars - 1][k];

                  sampler_off_pat[j][k] = sampler_off_pat[j - 1][k];
                }
              }
              if ((j > 0) && (j < pbars - 1)) {
                for (int k = 0; k < 3; k++) {

                  sampler_off_pat[j][k] = sampler_off_pat[j - 1][k];
                }
              }

              if (j == 0) {

                for (int k = 0; k < 3; k++) {
                  sampler_off_pat[j][k] = letempevent2[1][k];
                }
              }
              for (int i = 0; i < flash_liners_count; i++) {
                if (j == pbars - 1) {

                  for (int k = 0; k < 3; k++) {
                    letempevent2[0][k] = sampler_partition[i][pbars - 1][k];
                    sampler_partition[i][j][k] = sampler_partition[i][j - 1][k];
                  }
                }
                if ((j > 0) && (j < pbars - 1)) {
                  for (int k = 0; k < 3; k++) {
                    sampler_partition[i][j][k] = sampler_partition[i][j - 1][k];
                  }
                }

                if (j == 0) {

                  for (int k = 0; k < 3; k++) {

                    sampler_partition[i][j][k] = letempevent2[0][k];
                  }
                }
              }
            }
          }
        }

void POptionsRouter::shiftnotes2left(int leshifter) {

          byte letempevent2[2][3];
          for (int shifts = 0; shifts < leshifter; shifts++) {

            for (int j = 0; j < pbars; j++) {
              if (j == 0) {
                for (int k = 0; k < 3; k++) {
                  letempevent2[1][k] = sampler_off_pat[0][k];
                  sampler_off_pat[j][k] = sampler_off_pat[j + 1][k];
                }
              }
              if ((j > 0) && (j < pbars - 1)) {
                for (int k = 0; k < 3; k++) {

                  sampler_off_pat[j][k] = sampler_off_pat[j + 1][k];
                }
              }

              if (j == pbars - 1) {
                for (int k = 0; k < 3; k++) {
                  sampler_off_pat[j][k] = letempevent2[1][k];
                }
              }
              for (int i = 0; i < flash_liners_count; i++) {
                if (j == 0) {

                  for (int k = 0; k < 3; k++) {
                    letempevent2[0][k] = sampler_partition[i][0][k];
                    sampler_partition[i][j][k] = sampler_partition[i][j + 1][k];
                  }
                }
                if ((j > 0) && (j < pbars - 1)) {
                  for (int k = 0; k < 3; k++) {
                    sampler_partition[i][j][k] = sampler_partition[i][j + 1][k];
                  }
                }

                if (j == pbars - 1) {
                  for (int k = 0; k < 3; k++) {
                    sampler_partition[i][j][k] = letempevent2[0][k];
                  }
                }
              }
            }
          }
        }

void POptionsRouter::showtransposedisplays() {
          dm.clean_title_2();
          canvastitle.print((char *)optionspatternlabels[sublevels[2]]);

          int latransposition;
          latransposition = 7 - sublevels[3];
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

void POptionsRouter::doShiftersynth() {
          if (sublevels[3] - 16 > 0) {
            shiftnotes1left(abs(sublevels[3] - 16));
          }
          if (sublevels[3] - 16 < 0) {

            shiftnotes1right(abs(sublevels[3] - 16));
          }
          _pe.refresh_synth_track();
        }

void POptionsRouter::showShifterdisplays() {
          dm.clean_title_2();
          canvastitle.print((char *)optionspatternlabels[sublevels[2]]);

          int latransposition;
          latransposition = 16 - sublevels[3];
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

void POptionsRouter::showlestargetdisplays() {
          dm.clean_title_2();
          canvastitle.print((char *)optionspatternlabels[sublevels[2]]);

          int latransposition;
          latransposition = sublevels[3];
          canvasBIG.setCursor(0, 16);
          canvasBIG.setTextSize(2);
          switch (latransposition) {
          case 0:
            canvasBIG.print("All");

            targetNOsampler = 0;
            targetNOsynth = 0;
            targetNOcc = 0;
            break;
          case 1:
            // canvasBIG.setTextSize(1);
            canvasBIG.print("Synth");
            targetNOsampler = 1;
            targetNOsynth = 0;
            targetNOcc = 1;
            break;
          case 2:
            canvasBIG.print("Sampler");
            targetNOsampler = 0;
            targetNOsynth = 1;
            targetNOcc = 1;
            break;
          case 3:
            canvasBIG.print("CCs");
            targetNOsampler = 1;
            targetNOsynth = 1;
            targetNOcc = 0;
            break;
          case 4:
            canvasBIG.println("Synth");
            canvasBIG.print(" + CCs");

            targetNOsampler = 1;
            targetNOsynth = 0;
            targetNOcc = 0;
            break;
          case 5:
            canvasBIG.println("Sampler");
            canvasBIG.print(" + CCs");
            targetNOsampler = 0;
            targetNOsynth = 1;
            targetNOcc = 0;
            break;
          case 6:
            canvasBIG.println("Sampler");
            canvasBIG.print("Synth");
            targetNOsampler = 0;
            targetNOsynth = 0;
            targetNOcc = 1;
            break;
          default:
            break;
          }

          // canvasBIG.print(latransposition);
          dm.dodisplay();
        }

void POptionsRouter::optionspatterndisplays() {
          dm.clean_title_2();
          canvastitle.print((char *)optionspatternlabels[sublevels[2]]);
          if (sublevels[2] == 4) {
            canvasBIG.setCursor(0, 16);
            canvasBIG.setTextSize(2);
            if (interpolOn) {
              canvasBIG.print("On");
            } else {
              canvasBIG.print("Off");
            }
          }
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
          _nav_pattern[sublevels[1]]();
        }

void PatternsMenuRouter::show() {
          _route_nav[navlevel-1]();
        }

void PatternsMenuRouter::pattern_nav_zero(){
          paterning = false ;
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

          if (navlevel >= 3) {
            func();
            returntonav(1, self->home_navrange,sublevels[1]);
          }
        }

void PatternsMenuRouter::addnoteoff2next(byte lanotee, byte lapos) {
          if (lapos < pbars - 1) {
            sampler_off_pat[lapos + 1][0] = samplermidichannel;
            sampler_off_pat[lapos + 1][1] = lanotee;
            sampler_off_pat[lapos + 1][2] = 0;
          }
          if (lapos == pbars - 1) {
            sampler_off_pat[0][0] = samplermidichannel;
            sampler_off_pat[0][1] = lanotee;
            sampler_off_pat[0][2] = 0;
          }
        }

void PatternsMenuRouter::set_ccs() {
          // has to be reinitialized first
          for (int i = 0; i < pbars; i++) {
            recorded_ccs[i] = 0 ;
          }
          for (int i = 0; i < pbars; i++) {
            for (int j = 0; j < 128; j++) {
              if (cc_partition[j][i] != 127){
                for (int k = 0; k < pbars; k++) {
                    if (recorded_ccs[k] == 0 || recorded_ccs[k] == j){
                      recorded_ccs[k] = j ;
                      pots_controllers[k][i][0] = j;
                      pots_controllers[k][i][1] = cc_partition[j][i];
                    }
                }
              }

            }
          }
        }

void PatternsMenuRouter::parsepattern() {
          if (locked_fileing)
            return;
          locked_fileing = 1 ;
          self->catalog->refresh_files_names();
          // timescaller should be BPM dependant
          //    latimelineshifter = ((60000/19200)*pbars) ;
          // (60.0/BPMs)*1000)*pbars) = 1 bar millis
          const int pat_parser_size = 32000;
          char received_pattern[pat_parser_size];
          byte laccnote;
          byte parsedchannel;
          int letimescaler = 3125;
          File lepatternfile = SD.open(self->catalog->get_current_file_path(0).c_str());
          if (lepatternfile) {
            for (int i = 0; i < pat_parser_size; i++) {
              received_pattern[i] = lepatternfile.read();
            }
            Parser parserp((byte *)received_pattern, pat_parser_size);
            parserp.Reset();
            letempspattern = 0;
            int lenint = 0;

            previousTp = 5;
            leparsed[2] = (char)'\0';
            leparsed[1] = (char)'1';
            leparsed[0] = (char)'1';
            //TODO dumb way to trigger, looking for f to find 'Off' string...
            if (parserp.Search('f')) {
              parserp.Reset();
              lenint = 0;

              for (int k = 0; k < 128; k++) {
                while (!(leparsed[0] == (char)'O' && leparsed[1] == (char)'f')) {
                  parserp.JumpTo(Parser::IsDigit);
                  letempspattern = round((parserp.Read_Int32() / letimescaler));

                  if (letempspattern > 31) {
                    leparsed[1] = (char)'z';
                    leparsed[0] = (char)'z';
                    break;
                  }

                  parserp.JumpTo(Parser::IsLetter);
                  for (int i = 0; i < 2; i++) {
                    leparsed[i] = parserp.Read_Char();
                  }
                  if ((leparsed[0] == (char)'O' && leparsed[1] == (char)'n') ||
                      (leparsed[0] == (char)'P' && leparsed[1] == (char)'a')) {
                    leparsed[1] = (char)'z';
                    leparsed[0] = (char)'z';

                    parserp.SkipUntil(parserp.IsNewLine);
                  }
                }

                if (leparsed[0] == (char)'O' && leparsed[1] == (char)'n') {
                  leparsed[1] = (char)'z';
                  leparsed[0] = (char)'z';
                  break;
                }
                if (leparsed[0] == (char)'P' && leparsed[1] == (char)'a') {
                  leparsed[1] = (char)'z';
                  leparsed[0] = (char)'z';
                  break;
                }
                if (letempspattern == previousTp) {
                  lenint++;
                  if ((lenint > SYNTH_LINERS_COUNT + flash_liners_count - 1) ||
                      (leparsed[0] == (char)'O' && leparsed[1] == (char)'n') ||
                      (leparsed[0] == (char)'P' && leparsed[1] == (char)'a')) {
                    // parserp.SkipUntil(parserp.IsNewLine);
                    letempspattern = round((parserp.Read_Int32() / letimescaler));
                    lenint = 0;
                  }
                } else {
                  lenint = 0;
                  previousTp = letempspattern;
                }
                if (letempspattern > 31) {
                  leparsed[1] = (char)'z';
                  leparsed[0] = (char)'z';
                  break;
                }

                parserp.JumpTo(Parser::IsDigit);

                parsedchannel = parserp.Read_Int32();
                // not sure why I was using parsedchannel == 0 ||
                if (parsedchannel == samplermidichannel) {
                  leparsed[1] = (char)'z';
                  leparsed[0] = (char)'z';
                  break;
                }

                synth_off_pat[lenint][letempspattern][0] = parsedchannel;
                parserp.JumpTo(Parser::IsDigit);
                synth_off_pat[lenint][letempspattern][1] = parserp.Read_Int32();
                parserp.JumpTo(Parser::IsDigit);
                synth_off_pat[lenint][letempspattern][2] = parserp.Read_Int32();
                synth_off_pat[lenint][letempspattern][2] = 0;
                track_cells[0][letempspattern] = 1;
                leparsed[1] = (char)'z';
                leparsed[0] = (char)'z';
                parserp.SkipUntil(parserp.IsNewLine);
              }
            }

            parserp.Reset();
            letempspattern = 0;
            previousTp = 5;
            leparsed[1] = (char)'z';
            leparsed[0] = (char)'z';
            //TODO dumb way to trigger, looking for n to find 'On' string...
            if (parserp.Search('n')) {
              parserp.Reset();
              lenint = 0;

              for (int k = 0; k < 128; k++) {
                while (!(leparsed[0] == (char)'O' && leparsed[1] == (char)'n')) {
                  parserp.JumpTo(Parser::IsDigit);
                  letempspattern = round((parserp.Read_Int32() / letimescaler));
                  if (letempspattern > 31) {
                    break;
                  }

                  parserp.JumpTo(Parser::IsLetter);
                  for (int i = 0; i < 2; i++) {
                    leparsed[i] = parserp.Read_Char();
                  }
                  if ((leparsed[0] == (char)'O' && leparsed[1] == (char)'f') ||
                      (leparsed[0] == (char)'P' && leparsed[1] == (char)'a')) {
                    leparsed[1] = (char)'z';
                    leparsed[0] = (char)'z';

                    parserp.SkipUntil(parserp.IsNewLine);
                  }
                }

                if (leparsed[0] == (char)'O' && leparsed[1] == (char)'f') {
                  break;
                }
                if (leparsed[0] == (char)'P' && leparsed[1] == (char)'a') {
                  break;
                }
                if (letempspattern == previousTp) {
                  lenint++;
                  if ((lenint > SYNTH_LINERS_COUNT + flash_liners_count - 1) ||
                      (leparsed[0] == (char)'O' && leparsed[1] == (char)'f') ||
                      (leparsed[0] == (char)'P' && leparsed[1] == (char)'a')) {
                    // parserp.SkipUntil(parserp.IsNewLine);
                    letempspattern = round((parserp.Read_Int32() / letimescaler));
                    lenint = 0;
                  }
                } else {
                  lenint = 0;
                  previousTp = letempspattern;
                }
                if (letempspattern > 31) {
                  break;
                }

                parserp.JumpTo(Parser::IsDigit);

                parsedchannel = parserp.Read_Int32();
                //
                //if (parsedchannel == 0) {
                //  break;
                //}
                if (parsedchannel == synthmidichannel) {
                  synth_partition[lenint][letempspattern][0] = parsedchannel;
                  parserp.JumpTo(Parser::IsDigit);
                  synth_partition[lenint][letempspattern][1] = parserp.Read_Int32();
                  parserp.JumpTo(Parser::IsDigit);
                  synth_partition[lenint][letempspattern][2] = parserp.Read_Int32();
                }
                if (parsedchannel == samplermidichannel) {

                  sampler_partition[lenint][letempspattern][0] = parsedchannel;
                  parserp.JumpTo(Parser::IsDigit);
                  sampler_partition[lenint][letempspattern][1] = parserp.Read_Int32();
                  parserp.JumpTo(Parser::IsDigit);
                  sampler_partition[lenint][letempspattern][2] = parserp.Read_Int32();
                  addnoteoff2next(sampler_partition[lenint][letempspattern][1], letempspattern);
                  track_cells[1][letempspattern] = 1;
                }

                track_cells[0][letempspattern] = 1;
                leparsed[1] = (char)'z';
                leparsed[0] = (char)'z';
                parserp.SkipUntil(parserp.IsNewLine);

              }
            }

            parserp.Reset();
            letempspattern = 0;
            previousTp = 5;
            leparsed[1] = (char)'z';
            leparsed[0] = (char)'z';
            //TODO dumb way to trigger, looking for a to find 'Pa' string...
            if (parserp.Search('a')) {
              parserp.Reset();
              lenint = 0;
              bool keep_looping ;
              for (int ittr = 0 ; ittr < 128 ; ittr++ ) {
                keep_looping = true ;
                while (keep_looping && !(leparsed[0] == (char)'P' && leparsed[1] == (char)'a')) {
                  parserp.JumpTo(Parser::IsDigit);
                  letempspattern = round((parserp.Read_Int32() / letimescaler));
                  if (letempspattern > 31) {
                    keep_looping = false ;
                  }

                  parserp.JumpTo(Parser::IsLetter);
                  for (int i = 0; i < 2; i++) {
                    leparsed[i] = parserp.Read_Char();
                  }
                  if ((leparsed[0] == (char)'O' && leparsed[1] == (char)'f') ||
                      (leparsed[0] == (char)'O' && leparsed[1] == (char)'n')) {
                    leparsed[1] = (char)'z';
                    leparsed[0] = (char)'z';
                    parserp.SkipUntil(parserp.IsNewLine);
                  }
                }

                if ((leparsed[0] == (char)'O' && leparsed[1] == (char)'f') ||
                    (leparsed[0] == (char)'O' && leparsed[1] == (char)'n')) {
                  break;
                }

                if (letempspattern == previousTp) {
                  lenint++;
                  if ((lenint > SYNTH_LINERS_COUNT - 1) ||
                      (leparsed[0] == (char)'O' && leparsed[1] == (char)'f') ||
                      (leparsed[0] == (char)'O' && leparsed[1] == (char)'n')) {
                    leparsed[1] = (char)'z';
                    leparsed[0] = (char)'z';
                    parserp.SkipUntil(parserp.IsNewLine);
                    letempspattern = round((parserp.Read_Int32() / letimescaler));
                    lenint = 0;
                  }
                } else {
                  lenint = 0;
                  previousTp = letempspattern;
                }
                if (letempspattern > 31) {
                  break;
                }
                parserp.JumpTo(Parser::IsDigit);
                // skip channel as we dont care
                if (parserp.Read_Int32() == 0) {
                  break;
                }
                parserp.JumpTo(Parser::IsDigit);
                laccnote = parserp.Read_Int32();
                parserp.JumpTo(Parser::IsDigit);
                cc_partition[laccnote][letempspattern] = parserp.Read_Int32();
                leparsed[1] = (char)'z';
                leparsed[0] = (char)'z';
                parserp.SkipUntil(parserp.IsNewLine);
              }
            }
            parserp.Reset();

            letempspattern = 0;
            leparsed[1] = (char)'z';
            leparsed[0] = (char)'z';
            lenint = 0;

            lepatternfile.close();
            _pe.refresh_patterns();
            set_ccs();
          }
          locked_fileing = 0 ;
        }

void PatternsMenuRouter::doPatternsmenu() {
          char patternlistlabels[sizeofpatternlistlabels][12] = {
              "Edit", "Save", "Load", "Copy", "Delete", "Params", "Clear", "C-Edit"};
          byte startx = 5;
          byte starty = 16;
          char *textin = (char *)patternlistlabels[sublevels[1]];
          canvastitle.setCursor(0, 0);
          canvastitle.setTextSize(2);
          canvastitle.println(textin);
          canvasBIG.setTextSize(1);
          for (int i = 0; i < sizeofpatternlistlabels - 1 - (sublevels[1]); i++) {
            canvasBIG.setCursor(startx, starty + ((i)*10));
            canvasBIG.println(patternlistlabels[sublevels[1] + 1 + i]);
          }
          for (int i = 0; i < sublevels[1]; i++) {
            canvasBIG.setCursor(startx, (10 * (sizeofpatternlistlabels - sublevels[1]) + 6 + ((i)*10)));
            canvasBIG.println(patternlistlabels[i]);
          }
        }

void PatternsMenuRouter::deletepattern() {
          Serial.println("");
          Serial.print(self->catalog->get_current_file_path(0));
          Serial.print(" = ");
          Serial.print(SD.exists(self->catalog->get_current_file_path(0).c_str()));
          if (SD.exists(self->catalog->get_current_file_path(0).c_str())) {
            SD.remove(self->catalog->get_current_file_path(0).c_str());
          }
          self->catalog->list_files();
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

void PatternsMenuRouter::midifileliner(File &pat_filer,int liner, int ticker) {

          pat_filer.print(latimeline);
          pat_filer.print(" On ch=");
          int leintc = (int)synth_partition[liner][ticker][0];
          pat_filer.print(leintc);
          pat_filer.print(" n=");
          int leintn = (int)synth_partition[liner][ticker][1];
          pat_filer.print(leintn);
          pat_filer.print(" v=");
          int leintv = (int)synth_partition[liner][ticker][2];
          pat_filer.print(leintv);
          pat_filer.print("\n");
        }

void PatternsMenuRouter::midifilelinerSampler(File &pat_filer,int liner, int ticker) {

          pat_filer.print(latimeline);
          pat_filer.print(" On ch=");
          int leintc = (int)sampler_partition[liner][ticker][0];
          pat_filer.print(leintc);
          pat_filer.print(" n=");
          int leintn = (int)sampler_partition[liner][ticker][1];
          pat_filer.print(leintn);
          pat_filer.print(" v=");
          int leintv = (int)sampler_partition[liner][ticker][2];
          pat_filer.print(leintv);
          pat_filer.print("\n");
        }

void PatternsMenuRouter::midifilelinerOff(File &pat_filer, int liner, int ticker) {
          pat_filer.print(latimeline);
          pat_filer.print(" Off ch=");
          int leintc = (int)synth_off_pat[liner][ticker][0];
          pat_filer.print(leintc);
          pat_filer.print(" n=");
          int leintn = (int)synth_off_pat[liner][ticker][1];
          pat_filer.print(leintn);
          pat_filer.print(" v=");
          int leintv = (int)synth_off_pat[liner][ticker][2];
          pat_filer.print(leintv);
          pat_filer.print("\n");
        }

void PatternsMenuRouter::midifileCC(File &pat_filer,int lecc, int ticker) {
          pat_filer.print(latimeline);
          pat_filer.print(" Par ch=");
          int leintc = (int)synthmidichannel;
          pat_filer.print(leintc);
          pat_filer.print(" c=");
          int leintn = lecc;
          pat_filer.print(leintn);
          pat_filer.print(" v=");
          int leintv = (int)cc_partition[lecc][ticker];
          pat_filer.print(leintv);
          pat_filer.print("\n");
        }

void PatternsMenuRouter::write_midi_info(File &pat_filer) {
          latimeline = 0;
          // latimelineshifter = ((60000/19200)*pbars) ;
          // (60.0/BPMs)*1000)*pbars) = 1 bar millis 92 original
          pat_filer.print("MFile 0 1 19200\nMTrk\n");
          // for (int i = 0 ; i<5 ; i++ ) {

          for (int t = 0; t < pbars; t++) {

            latimeline = (3125 * t);
            for (int j = 0; j < SYNTH_LINERS_COUNT; j++) {
              if (synth_off_pat[j][t][1] != 0) {
                midifilelinerOff(pat_filer,j, t);
              }
            }
            for (int j = 0; j < SYNTH_LINERS_COUNT; j++) {
              if (synth_partition[j][t][1] != 0) {
                midifileliner(pat_filer,j, t);
              }
            }
            for (int j = 0; j < flash_liners_count; j++) {
              if (sampler_partition[j][t][1] != 0) {
                midifilelinerSampler(pat_filer,j, t);
              }
            }

            for (int j = 0; j < 128; j++) {
              if (cc_partition[j][t] != 127) {
                midifileCC(pat_filer,j, t);
              }
            }
          }

          //}
          pat_filer.print(100000);
          pat_filer.print(" Meta TrkEnd\n");
          pat_filer.print("TrkEnd\n");
        }

void PatternsMenuRouter::writelemidi() {
          if (locked_fileing)
            return;
          locked_fileing = 1 ;
          self->catalog->refresh_files_names();
          File pat_filer ;
          if (self->catalog->new_file_mode) {
            pat_filer = SD.open(self->catalog->get_new_file_name().c_str(), FILE_WRITE);
          } else {
            if (SD.exists(self->catalog->get_current_file_path(0).c_str())) {
              SD.remove(self->catalog->get_current_file_path(0).c_str());
            }
            pat_filer = SD.open(self->catalog->get_current_file_path(0).c_str(), FILE_WRITE);
          }
          if (pat_filer) {
            write_midi_info(pat_filer);
            pat_filer.close();
          }
          pat_filer.close();
          self->catalog->list_files();
          locked_fileing = 0;
        }

void PatternsMenuRouter::arpegiate_synth() {
          for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
            calledarpegenote[i][0] = 0;
            for (int j = 0; j < SYNTH_LINERS_COUNT; j++) {
              if (arpegnoteoffin[i][j] == 1) {
                shutlineroff(synthmidichannel,playingarpegiator[i][j]);
                arpegnoteoffin[i][j] = 0;
                playingarpegiator[i][j] = 0;
              }
              if (arpegnoteoffin[i][j] > 1) {
                arpegnoteoffin[i][j]--;
              }
            }
            if (arpegiatingNote[i] != 0) {
              playarpegenote(i);
            }
          }
          if (stoptickernextcycle) {
            closeallenvelopes();
            if (patternOn != 1) {
              stoptick = 1;
            }
            stoptickernextcycle = 0;
          }
        }

void PatternsMenuRouter::call_draw_sequencer(){
          _pe.show();
        }

void PatternsMenuRouter::call_options(){
          _po.optionspattern();
        }

void PatternsMenuRouter::call_edit_ccs(){
          _ce.show();
        }

void PatternsMenuRouter::call_clearpattern(){
           _po.clearlapattern();
        }


PatternsMenuRouter* PatternsMenuRouter::self = nullptr;
