


class CCEditor : public SectionHolder {
  public:
        CCEditor() {
                    self = this;
                    this->home_navrange=3;
                    this->relative_navlevel=2;
                    this->max_navlevel=5;
                    this->sublevels_address={4,0,0};
                    //home method not really used yet
                    //this->set_home(call_fx_mainpanel);
                    }

        static void show() {
          navrange = 127;
          showleditcc();
          editlaccactionpath();
          dm.dodisplay();
        }

        static void route_navlevel_1(){
            //presets_nav_zero();
        }

        static void showleditcc() {
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

        static void headerccedit() {
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

        static void showvertlinecursor(int lavertpos) {
          display.drawLine(lavertpos * (128 / pbars), 16, lavertpos * (128 / pbars), 64,
                          SSD1306_WHITE);
        }

        static void editlaccactionpath() {
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
            navlevel = 3;
            vraipos = sublevels[3];
            myEnc.write(vraipos * 4);
            navrange = pbars - 1;
          }
        }

  private:
      static CCEditor* self;
};

CCEditor* CCEditor::self = nullptr;
EXTMEM CCEditor _ce;

class PatEditRouter : public SectionHolder {
    public:
        PatEditRouter() {
                    self = this;
                    this->home_navrange=3;
                    this->relative_navlevel=2;
                    this->max_navlevel=5;
                    this->sublevels_address={4,7,0};
                    
                    //home method not really used yet
                    //this->set_home(call_fx_mainpanel);
                    }
        bool visible_tracks[6][32];
        byte (*_on_part)[3] = nullptr;
        byte (*_off_part)[3] = nullptr;
        byte (*_temp_part)[3] = nullptr;
        int *_length_part = nullptr;
        byte liners_count = 1 ;
        byte liners_page = 0;
        byte track_type = 0;
        byte local_line = 0;

        static void homer(){
          navrange = patternlines - 1;
          self->track_type = sublevels[navlevelpatedit];
          
          drawPatternRow();
          dolistpatternlineblocks();
          display.setCursor(0, 0);
          String _t_type[patternlines] = {"Synth","Sampler"};
          display.print(_t_type[self->track_type]);
         
        }

        static void set_editor_to_synth(byte liner = self->local_line){
          self->_on_part = synth_partition[liner] ;
          self->_off_part =  synth_off_pat[liner] ;
          self->_temp_part = temp_synth_partition;
          self->liners_count = SYNTH_LINERS_COUNT;
          self->_length_part = synth_notes_length[liner] ;
        }

        static void set_editor_to_sampler(byte liner = self->local_line){
         self->_on_part = sampler_partition[liner] ;
          self->_off_part = sampler_off_pat;
          self->_temp_part = temp_sampler_partition;
          self->liners_count = flash_liners_count;
          self->_length_part = flash_notes_length[liner] ;
        }

        static void show() {
          dm.clear_3();
          cell_events[navlevel-navlevelpatedit]();
          dm.dodisplay();
        }

        static void doshownoteline() {
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

        static void drawPatternRow() {
          // rows of audio sources : synth, sampler, others
          canvasBIG.drawFastHLine(0, 16 + sublevels[navlevelpatedit] * 8 + 3, 128, SSD1306_WHITE);
        }

        static void reshift_tracks_display() {
          //6 is max visible lines of 8px in 48px
          for (int i = 0 ; i < 6 ; i++) {
            set_editor_type[self->track_type]((i + sublevels[navlevelpatedit+1])%self->liners_count);
            for (int j = 0 ; j < pbars ; j++) {
              self->visible_tracks[i][j] = (bool)(self->_on_part[j][2]);
            }
          }
        }
        
        static void show_lines_events(){
          for (int i = 0 ; i < 6 ; i++) {
             for (int j = 0 ; j < pbars ; j++) {
                canvasBIG.fillRect( 4 * j, 16+(8*i), 4*((int)self->visible_tracks[i][j]), 8*((int)self->visible_tracks[i][j]), SSD1306_WHITE);  
            }
          }
          canvasBIG.drawFastHLine(0, 16 + 5, 128, SSD1306_INVERSE);
        }

        static void clearevented0(int lapatline) {

          for (int j = 0; j < pbars; j++) {
            track_cells[lapatline][j] = false;
          }
        }

        static void refresh_synth_track() {
          clearevented0(0);
          for (int linerrd = 0; linerrd < SYNTH_LINERS_COUNT; linerrd++) {
            for (int i = 0; i < pbars; i++) {
              if (synth_partition[linerrd][i][1] != 0) {
                track_cells[0][i] = true;
              }
            }
          }
        }

        static void refresh_flash_track() {
          clearevented0(1);
          for (int linerrd = 0; linerrd < flash_liners_count; linerrd++) {

            for (int i = 0; i < pbars; i++) {

              if (sampler_partition[linerrd][i][1] != 0) {
                track_cells[1][i] = true;
              }
            }
          }
        }

        static void dolistpatternlineblocks() {
          for (int lapatline = 0; lapatline < patternlines; lapatline++) {
            for (int i = 0; i < pbars; i++) {
              if (track_cells[lapatline][i]) {
                canvasBIG.fillRect( 4*i + 1,16 + (8*lapatline) + 1, 2,6, SSD1306_INVERSE);
              }
            }
          }
        }

        int grid_start_note() {
          /*
          byte min_note = 127 ;
          int averagenoteevent = 0;
          int nombrofnoteonliner = 0;
          //TODO: get the most visible notes range to set starting note val
          */
          return 45;
        }

        static void terminatenotesinbetween() {
          for (int i = min(sublevels[navlevelpatedit + 3] + 1,pbars-1); i < sublevels[navlevelpatedit + 4]; i++) {
            self->_on_part[i][0] = 0;
            self->_on_part[i][1] = 0;
            self->_on_part[i][2] = 0;
            self->_off_part[i][1] = 0;
            self->_off_part[i][0] = 0;
          }
        }

        static void sync_temp() {
          for (int i = 0; i < pbars; i++) {
            self->_temp_part[i][0] = self->_on_part[i][0];
            self->_temp_part[i][2] = self->_on_part[i][2];
            self->_temp_part[i][1] = self->_on_part[i][1];
          }
        }
       
        static void drawCursorCol() {
          int xpos = (sublevels[navlevel] * 4);
          display.drawLine(xpos, 0, xpos, 64-16, SSD1306_INVERSE);
        }

        static void track_selector() {
          reshift_tracks_display();
          navrange = self->liners_count - 1;
          self->local_line = sublevels[navlevelpatedit+1];
          set_editor_type[self->track_type](self->local_line);
          show_track_header();
          show_lines_events();
          dm.dodisplay();
          sublevels[navlevelpatedit + 2] = self->grid_start_note();
        }

        static void show_track_header(){
          display.clearDisplay();
          String head_title[2]={"Synth","Flash"};
          canvastitle.setCursor(0, 0);
          canvastitle.setTextSize(1);
          canvastitle.print(head_title[self->track_type]);
          canvastitle.print(" Track ");
          canvastitle.print(self->local_line + 1);
        }

        static void note_selector() {
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

        static void start_cell_setter() {
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

        static void draw_velobars(){
          int velobar ;
          for (int i = 0; i < pbars; i++) {
            velobar = map(self->_temp_part[i][2],0,127,0,16);
            canvasBIG.fillRect((i*(128/32)), 64-velobar,4 ,velobar, SSD1306_WHITE);
          }
        }

        static void stretch_cell_length() {
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

        static void stretch_cell_velocity() {
          navrange = 127;
          addinglenght = 0;
          self->_temp_part[sublevels[navlevelpatedit + 3]][2] = sublevels[navlevelpatedit + 5];
          display.clearDisplay();
          doshownoteline();
          canvasBIG.drawLine(0, 16 + 2, 127, 16 + 2, SSD1306_INVERSE);
          draw_velobars();
          dm.dodisplay();
        }

        static void sanitize_synth_partition(){
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

        static void sanitize_sampler_partition(){
         
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

        static void set_cell_at_pos(byte ch_, byte nt_, byte ve_){
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
        //bonus elswhere
        //if play pattern save played notes & notes off them all on Stop

        static void set_cell_velocity() {
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

        static void refresh_patterns(){
          _refresher[self->track_type]();
          _sanitizer[self->track_type]();
          computelenghtmesureoffline_synth();
          computelenghtmesureoffline_sampler();
        }

        static constexpr void (*cell_events[7])() = {&homer,&track_selector, &note_selector,
                                                    &start_cell_setter, &stretch_cell_length,
                                                    &stretch_cell_velocity, &set_cell_velocity};  
    private:
      static constexpr void (*_refresher[2])() = {&refresh_synth_track, &refresh_flash_track};
      static constexpr void (*set_editor_type[2])(byte) = {&set_editor_to_synth, &set_editor_to_sampler};
      static constexpr void (*_sanitizer[2])() = {&sanitize_synth_partition,&sanitize_sampler_partition};
      static PatEditRouter* self;
};

PatEditRouter* PatEditRouter::self = nullptr;
EXTMEM PatEditRouter _pe;

class POptionsRouter : public SectionHolder {
  public:
        POptionsRouter() {
                    self = this;
                    this->home_navrange=3;
                    this->relative_navlevel=2;
                    this->max_navlevel=5;
                    this->sublevels_address={4,0,0};
                    //home method not really used yet
                    //this->set_home(call_fx_mainpanel);
                    }

        static void clearlapattern() {
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

        static void clearCCline() {
          for (int j = 0; j < pbars; j++) {
            for (int i = 0; i < 128; i++) {

              cc_partition[i][j] = 127;
            }
          }
        }

        static void clearsynthpatternline() {
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
        static void merge_synth_partition_liners(){
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
        static void clearsamplerpatternline() {
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
        static void optionspattern() {
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
              toggle_that(interpolOn);
              returntonav(2, sizeofoptionspattern - 1);
            }
            if (sublevels[2] == 5) {
              // navrange = 14 ;
              merge_synth_partition_liners();
              returntonav(2, sizeofoptionspattern - 1);
            }
            if (sublevels[2] == 2) {
              // navrange = 14 ;
              clearlapattern();
              returntonav(2);
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

            navlevel = 2;
            vraipos = sublevels[2];
            myEnc.write(vraipos * 4);
            navrange = sizeofoptionspattern - 1;
          }
        }

        static void dotranspose() {
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

        static void doShifter() {
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

        static void dotransposesynth() {
          if (sublevels[3] - 7 > 0) {
            shiftnotes1down(abs(sublevels[3] - 7));
          }
          if (sublevels[3] - 7 < 0) {
            shiftnotes1up(abs(sublevels[3] - 7));
          }
          _pe.refresh_synth_track();
        }

        static void dotransposeCC() {
          if (sublevels[3] - 7 > 0) {
            shiftnotesCCdown(abs(sublevels[3] - 7));
          }
          if (sublevels[3] - 7 < 0) {
            shiftnotesCCup(abs(sublevels[3] - 7));
          }
        }

        static void doShifterCC() {
          if (sublevels[3] - 16 > 0) {
            shiftnotesCCleft(abs(sublevels[3] - 16));
          }
          if (sublevels[3] - 16 < 0) {
            shiftnotesCCright(abs(sublevels[3] - 16));
          }
        }

        static void shiftnotesCCup(int leshifter) {
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

        static void shiftnotesCCdown(int leshifter) {

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

        static void shiftnotesCCright(int leshifter) {
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

        static void shiftnotesCCleft(int leshifter) {

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

        static void shiftnotes1up(int leshifter) {
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

        static void shiftnotes1down(int leshifter) {
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

        static void shiftnotes1right(int leshifter) {
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

        static void shiftnotes1left(int leshifter) {

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

        static void dotransposesampler() {
          if (sublevels[3] - 7 > 0) {
            shiftnotes2down(abs(sublevels[3] - 7));
          }
          if (sublevels[3] - 7 < 0) {

            shiftnotes2up(abs(sublevels[3] - 7));
          }
          call_refresh_flash_track();
        }

        static void doShiftersampler() {
          if (sublevels[3] - 16 > 0) {
            shiftnotes2left(abs(sublevels[3] - 16));
          }
          if (sublevels[3] - 16 < 0) {

            shiftnotes2right(abs(sublevels[3] - 16));
          }
          call_refresh_flash_track();
        }

        static void shiftnotes2up(int leshifter) {

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

        static void shiftnotes2down(int leshifter) {
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

        static void shiftnotes2right(int leshifter) {
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

        static void shiftnotes2left(int leshifter) {

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

        static void showtransposedisplays() {
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

        static void doShiftersynth() {
          if (sublevels[3] - 16 > 0) {
            shiftnotes1left(abs(sublevels[3] - 16));
          }
          if (sublevels[3] - 16 < 0) {

            shiftnotes1right(abs(sublevels[3] - 16));
          }
          _pe.refresh_synth_track();
        }

        static void showShifterdisplays() {
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

        static void showlestargetdisplays() {
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

        static void optionspatterndisplays() {
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


  private:
    static POptionsRouter* self;
};

POptionsRouter* POptionsRouter::self = nullptr;
EXTMEM POptionsRouter _po;

class PatternsMenuRouter : public SectionHolder {
  public:
        PatternsMenuRouter() {
                    self = this;
                    this->home_navrange=sizeofpatternlistlabels-1;
                    this->relative_navlevel=1;
                    this->max_navlevel=5;
                    this->sublevels_address={4,0,0};
                    }

        static void route_navlevel(){
          _nav_pattern[sublevels[1]]();
        }

        static void show() {
          _route_nav[navlevel-1]();
        }

        static void pattern_nav_zero(){
          // mode selection
          navrange = sizeofpatternlistlabels - 1;
          displaythelistofpatterns();
          doPatternsmenu();
          dm.dodisplay();
        }

        static void pattern_nav_one(){
          navrange = patterns_count - 1;
          if (sublevels[1] == 1) {
            navrange = patterns_count;
          }
          displaythelistofpatterns();
          doPatternsmenu();
          dm.dodisplay();
        }

        static void remove_pattern(){
          lv1_wrapper(self->deletepattern);
        }

        static void duplicate_pattern(){
          lv1_wrapper(self->copypattern);
        }

        static void load_pattern(){
          lv1_wrapper(self->parsepattern);
        }

        static void save_pattern(){
          lv1_wrapper(self->writelemidi);
        }

        static void lv1_wrapper(void (*func)()) {
          pattern_nav_one();
          if (navlevel >= 3) {
            func();
            returntonav(1, sizeofpatternlistlabels - 1,sublevels[1]);
          }
        }

        static void addnoteoff2next(byte lanotee, byte lapos) {
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

        static void set_ccs() {
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

        static void parsepattern() {
          if (locked_fileing)
            return;
          locked_fileing = 1 ;
          refresh_patterns_names();
          // timescaller should be BPM dependant
          //    latimelineshifter = ((60000/19200)*pbars) ;
          // (60.0/BPMs)*1000)*pbars) = 1 bar millis
          const int pat_parser_size = 32000;
          char received_pattern[pat_parser_size];
          byte laccnote;
          byte parsedchannel;
          int letimescaler = 3125;
          File lepatternfile = SD.open(self->get_current_pattern_path().c_str());
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

        static void list_patterns_files() {
          if (locked_fileing)
            return;
          locked_fileing = 1 ;
          patterns_count = 0;
          String patterns_dir = "PATTERNS/";
          if (SD.exists(patterns_dir.c_str())) {
            File pattern_filer = SD.open(patterns_dir.c_str());
            while (patterns_count < 99) {
              File entry = pattern_filer.openNextFile();
              if (!entry) {
                break;
              }
              if (!entry.isDirectory()) {
                char* named = (char*)entry.name();
                named[strlen(named) - 4] = '\0';
                //int is 7 chars after prefix
                patterns_indexes[patterns_count] = atoi(named+7);
                patterns_count++;
              }
              entry.close();
            }
            pattern_filer.close();
          }
          locked_fileing = 0 ;
        }

        String get_pattern_name(byte number) {
          char formatted_number[4] ;
          sprintf(formatted_number,"%02d",number);
          return "PATTERN" + (String)formatted_number ;
        }

        static void refresh_patterns_names() {
          for (int i = 0 ; i < ptn_size ; i++) {
            //empty spots are left at the end of the list if it is small, otherwise the names are looped
            patterns_names[i] = " ";
            if (patterns_names_offset+i < patterns_count ) {
              patterns_names[i] = self->get_pattern_name(patterns_indexes[patterns_names_offset+i]);
            } else if (patterns_count >= ptn_size ){
              patterns_names[i] = self->get_pattern_name(patterns_indexes[(patterns_names_offset+i)%patterns_count]);
            }
          }
        }

        static void displaythelistofpatterns() {
          dm.clean_title_1_1();
          patterns_names_offset = sublevels[2];
          refresh_patterns_names();
          int startx = 73;
          int starty = 16;
          canvastitle.setCursor(startx, 0);
          if (patterns_names_offset == patterns_count && sublevels[1] == 1) {
            canvastitle.print("New()");
          } else {
            canvastitle.print(patterns_names[0].c_str());
          }
          if (patterns_names_offset == patterns_count) {
            for (int i = 0; i < ptn_size-1; i++) {
              canvasBIG.setCursor(startx, (10 * (patterns_count - patterns_names_offset)) + 16 + i*10);
              canvasBIG.println(patterns_names[i]);
            }
          } else {
            for (int i = 0; i < ptn_size - 1 ; i++) {
              canvasBIG.setCursor(startx, starty + i*10);
              canvasBIG.println(patterns_names[1 + i]);
            }
          }
          //dm.dodisplay();
        }

        static void doPatternsmenu() {
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

        static void deletepattern() {
          Serial.println("");
          Serial.print(self->get_current_pattern_path());
          Serial.print(" = ");
          Serial.print(SD.exists(self->get_current_pattern_path().c_str()));
          if (SD.exists(self->get_current_pattern_path().c_str())) {
            SD.remove(self->get_current_pattern_path().c_str());
          }
          list_patterns_files();
        }

        static void copypattern() {
          File originpatternfile = SD.open(self->get_current_pattern_path().c_str());
          File mypatterntxtFile = SD.open(get_new_file_name("PATTERNS/PATTERN").c_str(), FILE_WRITE);
          size_t n;
          uint8_t buf[64];
          if (originpatternfile) {
            while ((n = originpatternfile.read(buf, sizeof(buf))) > 0) {
              mypatterntxtFile.write(buf, n);
            }
            originpatternfile.close();
          }
          mypatterntxtFile.close();
          list_patterns_files();
        }

        static void midifileliner(File &pat_filer,int liner, int ticker) {

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

        static void midifilelinerSampler(File &pat_filer,int liner, int ticker) {

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

        static void midifilelinerOff(File &pat_filer, int liner, int ticker) {
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

        static void midifileCC(File &pat_filer,int lecc, int ticker) {
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

        static void write_midi_info(File &pat_filer) {
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

        String get_current_pattern_path(){
          //patterns_names array is rearranged on the fly with active in first pos
          return "PATTERNS/" + patterns_names[0] + ".TXT";
        }

        static void writelemidi() {
          if (locked_fileing)
            return;
          locked_fileing = 1 ;
          refresh_patterns_names();
          File pat_filer ;
          if (patterns_names_offset == patterns_count) {
            pat_filer = SD.open(get_new_file_name("PATTERNS/PATTERN").c_str(), FILE_WRITE);
          } else {
            if (SD.exists(self->get_current_pattern_path().c_str())) {
              SD.remove(self->get_current_pattern_path().c_str());
            }
            pat_filer = SD.open(self->get_current_pattern_path().c_str(), FILE_WRITE);
          }
          if (pat_filer) {
            write_midi_info(pat_filer);
            pat_filer.close();
          }
          pat_filer.close();
          list_patterns_files();
          locked_fileing = 0;
        }

        static void arpegiate_synth() {
          for (int i = 0; i < nombreofarpeglines; i++) {
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

        static void call_draw_sequencer(){
          _pe.show();
        }

        static void call_options(){
          _po.optionspattern();
        }

        static void call_edit_ccs(){
          _ce.show();
        }

        static void call_clearpattern(){
           _po.clearlapattern();
        }

        static constexpr void (*_route_nav[7])() = {&pattern_nav_zero, &route_navlevel,
                        &route_navlevel, &route_navlevel, &route_navlevel,
                         &route_navlevel, &route_navlevel};
        static constexpr void (*_nav_pattern[sizeofpatternlistlabels])() = {&call_draw_sequencer,&save_pattern,
                                  &load_pattern, &duplicate_pattern,&remove_pattern,
                                  &call_options,&call_clearpattern,&call_edit_ccs};
  private:
      static PatternsMenuRouter* self;
};

PatternsMenuRouter* PatternsMenuRouter::self = nullptr;
PatternsMenuRouter _pt;

int clean_cursor(int pos){
  if (pos >= pbars ) {
    pos = 0 ;
    return pos;
  } else if (pos < 0 ) {
    pos = pbars - 1 ;
    return pos;
  }
  return pos;
}

void advance_tick(){
  tickposition = clean_cursor(tickposition+1);
  //TODO : remove tickerlasttick logic
  tickerlasttick = millis();
  tick();
}

//should be set after _pt & _se
void tick() {

  if (arpegiatorOn) {
      _pt.arpegiate_synth();
  }
  if (patternOn) {
    _se.use_pattern();
  }

  if (songplaying) {
    _se.update_song_player();
  }

}
