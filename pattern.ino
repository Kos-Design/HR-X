
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
            for (int i = 0; i < synth_liners_count; i++) {

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
          byte liner_encoutered[synth_liners_count] = {0,0,0,0,0,0} ;

          for (int j=0;j<pbars;j++){
            note_encoutered = 0 ;
            for (int i=0;i<synth_liners_count;i++){
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
          call_refresh_synth_track();
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
            for (int i = 0; i < synth_liners_count; i++) {
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

            for (int i = 0; i < synth_liners_count; i++) {
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
            for (int i = 0; i < synth_liners_count; i++) {
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

            for (int i = 0; i < synth_liners_count; i++) {
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
          dodisplay();
        }

        static void doShiftersynth() {
          if (sublevels[3] - 16 > 0) {
            shiftnotes1left(abs(sublevels[3] - 16));
          }
          if (sublevels[3] - 16 < 0) {

            shiftnotes1right(abs(sublevels[3] - 16));
          }
          call_refresh_synth_track();
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
          dodisplay();
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
          dodisplay();
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
          dodisplay();
        }


  private:
    static POptionsRouter* self;
};

POptionsRouter* POptionsRouter::self = nullptr;
EXTMEM POptionsRouter _po;

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
          Serial.println("shown");
          navrange = 127;
          showleditcc();
          editlaccactionpath();
          dodisplay();
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
              canvastitle.print((char *)ControlList[midiknobassigned[sublevels[2]]]);
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
          dodisplay();
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

        static void homer(){
          cellsizer = 8 * (16 / pbars);
          celltall = 8;
          startx = 0;
          starty = 16;
          navrange = patternlines - 1;
          dm.clear_3();
          drawPatternRow();
          dolistpatternlineblocks();
          display.setCursor(0, 0);
          if (sublevels[navlevelpatedit] == 0) {
            display.print("Synth");
          }
          if (sublevels[navlevelpatedit] == 1) {
            display.print("Sampler");
          }
          dodisplay();
        }

        static void player_selector(){
          cellsizer = 8 * (16 / pbars);
          celltall = 8;
          startx = 0;
          starty = 16;
          navrange = patternlines - 1;
          dm.clear_3();
          _nav_peditors[sublevels[navlevelpatedit]]();
          dodisplay();
        }

        static void show() {
           _nav_home_route[navlevel-navlevelpatedit]();
        }

        

        static void doshownoteline() {
          // some notes not showing check lenght note computation
          // -----------------------
          // only once, move elsewhere
          // int displayedstart = 60 ;
          // navrange = 128-1 ;
          cellsizer = 4;
          celltall = 4;
          startx = 0;
          starty = 16;
          int lenghtofthenote = 4;
          int decnote;
          // int linersizehold ;
          int linern = sublevels[navlevelpatedit + 1];

          startingnoteline = sublevels[navlevelpatedit + 2];
          // if selector pos > displayedstart + 12
          // display 12 notes range
          // blocks pos y = truenote
          byte note0;
          canvasBIG.setCursor(0, 0);
          canvasBIG.print("Note:");
          canvasBIG.print(sublevels[navlevelpatedit + 2]);
          canvasBIG.print(" Pos:");
          canvasBIG.print(sublevels[navlevelpatedit + 3]);
          for (int notelines = startingnoteline; notelines > startingnoteline - 12;
              notelines--) {
            for (int i = 0; i < pbars; i++) {

              note0 = synth_partition[linern][i][1];
              decnote = (int)note0;

              if (decnote == notelines && note0 != 0) {

                lenghtofthenote = length0pbars[linern][i];

                if (lenghtofthenote < 4) {
                  lenghtofthenote = 4;
                }
                int listoffsetter = starty + (4 * (startingnoteline - notelines));

                canvasBIG.fillRect(startx + cellsizer * i, listoffsetter,
                                  lenghtofthenote, celltall, SSD1306_WHITE);
                canvasBIG.drawLine(startx + cellsizer * i, listoffsetter,
                                  startx + cellsizer * i, listoffsetter + celltall,
                                  SSD1306_BLACK);
              }
            }
          }
        }

        static void doshownoteline2() {
          cellsizer = 4;
          celltall = 4;
          startx = 0;
          starty = 16;
          int lenghtofthenote = 4;
          int decnote;
          int listoffsetter;
          // int linersizehold ;
          int linern = sublevels[navlevelpatedit + 1];
          startingnoteline = sublevels[navlevelpatedit + 2];
          canvasBIG.setCursor(0, 0);
          canvasBIG.print("Note:");
          canvasBIG.print(sublevels[navlevelpatedit + 2]);
          canvasBIG.print(" Pos:");
          canvasBIG.print(sublevels[navlevelpatedit + 4]);
          byte note0;
          for (int notelines = startingnoteline; notelines > startingnoteline - 12;
              notelines--) {
            for (int i = 0; i < pbars; i++) {

              note0 = temp_synth_partition[linern][i][1];

              decnote = (int)note0;
              if (decnote == notelines && note0 != 0) {

                lenghtofthenote = templength0pbars[linern][i];

                if (lenghtofthenote < 4) {
                  lenghtofthenote = 4;
                }
                listoffsetter = starty + (4 * (startingnoteline - notelines));
                canvasBIG.fillRect(startx + cellsizer * i, listoffsetter,
                                  lenghtofthenote, celltall, SSD1306_WHITE);
                canvasBIG.drawLine(startx + cellsizer * i, listoffsetter,
                                  startx + cellsizer * i, listoffsetter + celltall,
                                  SSD1306_BLACK);
              }
            }
          }
        }

        static void doshownoteline3() {
          cellsizer = 4;
          celltall = 4;
          startx = 0;
          starty = 16;
          int lenghtofthenote = 4;
          int decnote;
          int listoffsetter;
          // int linersizehold ;
          int linern = sublevels[navlevelpatedit + 1];
          startingnoteline = sublevels[navlevelpatedit + 2];
          canvasBIG.setCursor(0, 0);
          canvasBIG.print("Note:");
          canvasBIG.print(sublevels[navlevelpatedit + 2]);

          canvasBIG.print(" Vel:");
          canvasBIG.print(sublevels[navlevelpatedit + 5]);
          byte note0;
          for (int notelines = startingnoteline; notelines > startingnoteline - 12;
              notelines--) {
            for (int i = 0; i < pbars; i++) {

              note0 = temp_synth_partition[linern][i][1];

              decnote = (int)note0;
              if (decnote == notelines && note0 != 0) {

                lenghtofthenote = templength0pbars[linern][i];

                if (lenghtofthenote < 4) {
                  lenghtofthenote = 4;
                }
                listoffsetter = starty + (4 * (startingnoteline - notelines));
                canvasBIG.fillRect(startx + cellsizer * i, listoffsetter,
                                  lenghtofthenote, celltall, SSD1306_WHITE);
                canvasBIG.drawLine(startx + cellsizer * i, listoffsetter,
                                  startx + cellsizer * i, listoffsetter + celltall,
                                  SSD1306_BLACK);
              }
            }
          }
        }
       
        static void doshownoteline_sampler() {
            // some notes not showing check lenght note computation
            // -----------------------
            // only once, move elsewhere
            // int displayedstart = 60 ;
            // navrange = 128-1 ;
            cellsizer = 4;
            celltall = 4;
            startx = 0;
            starty = 16;
            int lenghtofthenote = 4;
            int decnote;
            // int linersizehold ;
            int linern = sublevels[navlevelpatedit + 1];

            startingnoteline = sublevels[navlevelpatedit + 2];
            // if selector pos > displayedstart + 12
            // display 12 notes range
            // blocks pos y = truenote
            byte note0;
            canvasBIG.setCursor(0, 0);
            canvasBIG.print("Note:");
            canvasBIG.print(sublevels[navlevelpatedit + 2]);
            canvasBIG.print(" Pos:");
            canvasBIG.print(sublevels[navlevelpatedit + 3]);
            for (int notelines = startingnoteline; notelines > startingnoteline - 12;
                notelines--) {
              for (int i = 0; i < pbars; i++) {

                note0 = sampler_partition[linern][i][1];
                decnote = (int)note0;

                if (decnote == notelines && note0 != 0) {

                  lenghtofthenote = length2pbars[linern][i];

                  if (lenghtofthenote < 4) {
                    lenghtofthenote = 4;
                  }
                  int listoffsetter = starty + (4 * (startingnoteline - notelines));

                  canvasBIG.fillRect(startx + cellsizer * i, listoffsetter,
                                    lenghtofthenote, celltall, SSD1306_WHITE);
                  canvasBIG.drawLine(startx + cellsizer * i, listoffsetter,
                                    startx + cellsizer * i, listoffsetter + celltall,
                                    SSD1306_BLACK);
                }
              }
            }
        }

        static void doshownoteline2_sampler() {
          cellsizer = 4;
          celltall = 4;
          startx = 0;
          starty = 16;
          int lenghtofthenote = 4;
          int decnote;
          int listoffsetter;
          // int linersizehold ;
          int linern = sublevels[navlevelpatedit + 1];
          startingnoteline = sublevels[navlevelpatedit + 2];
          canvasBIG.setCursor(0, 0);
          canvasBIG.print("Note:");
          canvasBIG.print(sublevels[navlevelpatedit + 2]);
          canvasBIG.print(" Pos:");
          canvasBIG.print(sublevels[navlevelpatedit + 4]);
          byte note0;
          for (int notelines = startingnoteline; notelines > startingnoteline - 12;
              notelines--) {
            for (int i = 0; i < pbars; i++) {

              note0 = temp_sampler_partition[linern][i][1];

              decnote = (int)note0;
              if (decnote == notelines && note0 != 0) {

                lenghtofthenote = templength2pbars[linern][i];

                if (lenghtofthenote < 4) {
                  lenghtofthenote = 4;
                }
                listoffsetter = starty + (4 * (startingnoteline - notelines));
                canvasBIG.fillRect(startx + cellsizer * i, listoffsetter,
                                  lenghtofthenote, celltall, SSD1306_WHITE);
                canvasBIG.drawLine(startx + cellsizer * i, listoffsetter,
                                  startx + cellsizer * i, listoffsetter + celltall,
                                  SSD1306_BLACK);
              }
            }
          }
        }

        static void doshownoteline3_sampler() {
          cellsizer = 4;
          celltall = 4;
          startx = 0;
          starty = 16;
          int lenghtofthenote = 4;
          int decnote;
          int listoffsetter;
          // int linersizehold ;
          int linern = sublevels[navlevelpatedit + 1];
          startingnoteline = sublevels[navlevelpatedit + 2];
          canvasBIG.setCursor(0, 0);
          canvasBIG.print("Note:");
          canvasBIG.print(sublevels[navlevelpatedit + 2]);

          canvasBIG.print(" Vel:");
          canvasBIG.print(sublevels[navlevelpatedit + 5]);
          byte note0;
          for (int notelines = startingnoteline; notelines > startingnoteline - 12;
              notelines--) {
            for (int i = 0; i < pbars; i++) {

              note0 = temp_sampler_partition[linern][i][1];

              decnote = (int)note0;
              if (decnote == notelines && note0 != 0) {

                lenghtofthenote = templength2pbars[linern][i];

                if (lenghtofthenote < 4) {
                  lenghtofthenote = 4;
                }
                listoffsetter = starty + (4 * (startingnoteline - notelines));
                canvasBIG.fillRect(startx + cellsizer * i, listoffsetter,
                                  lenghtofthenote, celltall, SSD1306_WHITE);
                canvasBIG.drawLine(startx + cellsizer * i, listoffsetter,
                                  startx + cellsizer * i, listoffsetter + celltall,
                                  SSD1306_BLACK);
              }
            }
          }
        }

        static void drawPatternRow() {
          // rows of audio sources : synth, sampler, others
          canvasBIG.drawLine(startx, starty + sublevels[navlevelpatedit] * celltall + 3,
                            (128 - startx),
                            starty + sublevels[navlevelpatedit] * celltall + 3,
                            SSD1306_WHITE);
        }

        static void drawEventRow() {
          // row of events (liners) on audio source (patternrow)
          canvasBIG.drawLine(
              0, starty + sublevels[navlevelpatedit + 1] * celltall + 3, 128,
              starty + sublevels[navlevelpatedit + 1] * celltall + 3, SSD1306_INVERSE);
        }

        static void drawsamplerEventRow() {
          // row of events (liners) on audio source (patternrow)
          canvasBIG.drawLine(0,starty + (sublevels[navlevelpatedit + 1] - samplelinerspage) * celltall + 3, 128, starty + (sublevels[navlevelpatedit + 1] - samplelinerspage) * celltall + 3,
              SSD1306_INVERSE);
        }

        static void drawsynthEventRow() {
          // row of events (liners) on audio source (patternrow)
          canvasBIG.drawLine(0,starty + (sublevels[navlevelpatedit + 1] - synthlinerspage) * celltall + 3, 128, starty + (sublevels[navlevelpatedit + 1] - synthlinerspage) * celltall + 3,
              SSD1306_INVERSE);
        }

        static void showblocksofevent() {
          cellsizer = 4;
          celltall = 8;
          startx = 0;
          starty = 0;
          for (int liner = 0; liner < synth_liners_count; liner++) {
            for (int i = 0; i < pbars; i++) {
              if (synth_partition[liner][i][1] != 0) {
                canvasBIG.fillRect(startx + cellsizer * i + 1,
                                  starty + (celltall * liner) + 1, cellsizer - 2,
                                  celltall - 2, SSD1306_INVERSE);
              }
            }
          }
        }
        static void showblocksofevent2_synth(){
          cellsizer = 4;
          celltall = 8;
          startx = 0;
          starty = 16;
          for (int liner = 0 + synthlinerspage; liner < 6;
              liner++) {
            for (int i = 0; i < pbars; i++) {
              if (synth_partition[liner][i][1] != 0) {
                canvasBIG.fillRect(startx + cellsizer * i + 1,
                                  starty + (celltall * (liner - synthlinerspage)) + 1,
                                  cellsizer - 2, celltall - 2, SSD1306_INVERSE);
              }
            }
          }
        }
        static void showblocksofevent2() {
          cellsizer = 4;
          celltall = 8;
          startx = 0;
          starty = 16;
          for (int liner = 0 + samplelinerspage; liner < 6 + samplelinerspage;
              liner++) {
            for (int i = 0; i < pbars; i++) {
              if (sampler_partition[liner][i][1] != 0) {
                canvasBIG.fillRect(startx + cellsizer * i + 1,
                                  starty + (celltall * (liner - samplelinerspage)) + 1,
                                  cellsizer - 2, celltall - 2, SSD1306_INVERSE);
              }
            }
          }
        }

        static void clearevented0(int lapatline) {

          for (int j = 0; j < pbars; j++) {
            track_cells[lapatline][j] = false;
          }
        }

        static void refresh_synth_track() {
          clearevented0(0);
          for (int linerrd = 0; linerrd < synth_liners_count; linerrd++) {

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
          cellsizer = 4;
          celltall = 8;
          startx = 0;
          starty = 16;

          for (int lapatline = 0; lapatline < patternlines; lapatline++) {
            for (int i = 0; i < pbars; i++) {
              if (track_cells[lapatline][i]) {
                canvasBIG.fillRect(startx + cellsizer * i + 1,
                                  starty + (8 * lapatline) + 1, cellsizer - 2,
                                  celltall - 2, SSD1306_INVERSE);
              }
            }
          }
        }

        int synth_start_note() {
          byte min_note = 127 ;
          int averagenoteevent = 0;
          int nombrofnoteonliner = 0;
          // sublevels[navlevelpatedit+2] = 60 ;
          for (int ni = 0; ni < synth_liners_count; ni++) {
            int decednote = synth_partition[sublevels[navlevelpatedit + 1]][ni][1];
            if (decednote != 0) {
              Serial.println("finote");
              if ( decednote < min_note ) {
                min_note = decednote ;
              }
              averagenoteevent = averagenoteevent + decednote;
              nombrofnoteonliner++;
            }
          }
          if (nombrofnoteonliner != 0 ) {
            return min_note;
            //round(averagenoteevent / nombrofnoteonliner) + 6;

            // display
          }
          return 70;


        }

        int flash_start_note() {
          int averagenoteevent = 0;
          int nombrofnoteonliner = 0;
          // sublevels[navlevelpatedit+2] = 60 ;
          for (int ni = 0; ni < flash_liners_count; ni++) {
            int decednote = sampler_partition[sublevels[navlevelpatedit + 1]][ni][1];
            if (decednote != 0) {
              averagenoteevent = averagenoteevent + decednote;
              nombrofnoteonliner++;
            }
          }
          if (nombrofnoteonliner != 0) {
            startingnoteline = round(averagenoteevent / nombrofnoteonliner) + 6;

            // display
          } else {
            startingnoteline = 70;
          }
          return startingnoteline;
        }

        static void sampler_event_cells() {
          _route_nav_samplers[navlevel-navlevelpatedit-1]();
        }

        static void synth_event_cells() {
            _route_nav_synths[navlevel-navlevelpatedit-1]();
        }

        static void terminatenotesinbetween_synth() {
          for (int i = sublevels[navlevelpatedit + 3] + 1;
              i < sublevels[navlevelpatedit + 4]; i++) {
            if (synth_partition[sublevels[navlevelpatedit + 1]][i][1] != 0) {
              synth_partition[sublevels[navlevelpatedit + 1]][i][1] = 0;
            }
            if (synth_off_pat[sublevels[navlevelpatedit + 1]][i][1] != 0) {
              synth_off_pat[sublevels[navlevelpatedit + 1]][i][1] = 0;
            }
          }
        }

        static void terminatenotesinbetween_sampler() {
          for (int i = sublevels[navlevelpatedit + 3] + 1;
              i < sublevels[navlevelpatedit + 4]; i++) {
            if (sampler_partition[sublevels[navlevelpatedit + 1]][i][1] != 0) {
              sampler_partition[sublevels[navlevelpatedit + 1]][i][1] = 0;
            }
            if (sampler_off_pat[i][1] != 0) {
              sampler_off_pat[i][1] = 0;
            }
          }
        }

        bool offhasOnbutnototheroff_synth(byte liner, byte lanoteoff, byte fromi) {
          // for (int j = 0 ; j < synth_liners_count ; j++ ) {
          for (int i = fromi - 1; i >= 0; i--) {
            if (synth_partition[liner][i][1] == lanoteoff) {
              return 1;
            }
          }
          for (int i = pbars - 1; i >= fromi; i--) {
            if (synth_off_pat[liner][i][1] == lanoteoff && i > fromi) {
              return 0;
            }
            if (synth_partition[liner][i][1] == lanoteoff) {
              return 1;
            }
          }
          return 0;
        }

        bool offhasOnbutnototheroff_sampler(byte liner, byte lanoteoff, byte fromi) {
          // for (int j = 0 ; j < synth_liners_count ; j++ ) {
          for (int i = fromi - 1; i >= 0; i--) {
            
            if (sampler_partition[liner][i][1] == lanoteoff) {
              return 1;
            }
          }
          for (int i = pbars - 1; i >= fromi; i--) {
            if (sampler_off_pat[i][1] == lanoteoff && i > fromi) {
              return 0;
            }
            if (sampler_partition[liner][i][1] == lanoteoff) {
              return 1;
            }
          }
          return 0;
        }

        static void duplicateevent1() {
          for (int j = 0; j < synth_liners_count; j++) {
            for (int i = 0; i < pbars; i++) {
              temp_synth_partition[j][i][0] = synth_partition[j][i][0];
              temp_synth_partition[j][i][2] = synth_partition[j][i][2];
              temp_synth_partition[j][i][1] = synth_partition[j][i][1];
            }
          }
        }
        static void duplicateevent2() {
          for (int j = 0; j < flash_liners_count; j++) {
            for (int i = 0; i < pbars; i++) {
              temp_sampler_partition[j][i][0] = sampler_partition[j][i][0];
              temp_sampler_partition[j][i][2] = sampler_partition[j][i][2];
              temp_sampler_partition[j][i][1] = sampler_partition[j][i][1];
            }
          }
        }

        static void drawCursorCol() {
          int xpos = (sublevels[navlevelpatedit + 3] * 4) + 1;
          display.drawLine(xpos, starty, xpos, 64 - (starty), SSD1306_INVERSE);
        }

        static void drawCursorCol2() {
          int xpos = (sublevels[navlevelpatedit + 4] * 4) + 1;
          display.drawLine(xpos, starty, xpos, 64 - (starty), SSD1306_INVERSE);
        }

        static void duplicatelenghofnotestarray() {
          for (int j = 0; j < synth_liners_count; j++) {
            for (int i = 0; i < pbars; i++) {
              templength0pbars[j][i] = length0pbars[j][i];
            }
          }
        }

        static void duplicatelenghofnotestarray2() {
          for (int j = 0; j < flash_liners_count; j++) {
            for (int i = 0; i < pbars; i++) {
              templength2pbars[j][i] = length2pbars[j][i];
            }
          }
        }

        static void track_selector_sampler() {
          if (sublevels[navlevelpatedit + 1] > 3 && samplelinerspage < flash_liners_count) {
            samplelinerspage = sublevels[navlevelpatedit + 1] - 3;
          } else {
            samplelinerspage = 0;
          }
          display.clearDisplay();
          show_track_header();
          navrange = flash_liners_count - 1;
          showblocksofevent2();
          // samplelinerspage
          drawsamplerEventRow();
          draw_all_sampler_velobars();
          dodisplay();
          sublevels[navlevelpatedit + 2] = self->flash_start_note();
        }

        static void track_selector_synth() {
          if (sublevels[navlevelpatedit + 1] > 3 && synthlinerspage < synth_liners_count) {
            synthlinerspage = sublevels[navlevelpatedit + 1] - 3;
          } else {
            synthlinerspage = 0;
          }

          display.clearDisplay();
          navrange = synth_liners_count - 1;
          show_track_header();
          //showblocksofevent();
          //drawEventRow();
          showblocksofevent2_synth();
          drawsynthEventRow();
          draw_all_velobars();
          dodisplay();
          sublevels[navlevelpatedit + 2] = self->synth_start_note();

        }

        static void show_track_header(){
          String head_title[2]={"Synth","Flash"};
          canvastitle.setCursor(0, 0);
          canvastitle.setTextSize(1);
          canvastitle.print(head_title[sublevels[navlevelpatedit]]);
          canvastitle.print(" Track ");
          canvastitle.print(sublevels[navlevelpatedit + 1] + 1);
        }



        static void note_selector_synth() {

          // notes of said liner
          display.clearDisplay();
          navrange = 127;
          // some notes not showing checl lenght note computation
          doshownoteline();
          canvasBIG.drawLine(0, starty + 2, 127, starty + 2, SSD1306_INVERSE);
          draw_synth_velobars();
          dodisplay();
          sublevels[navlevelpatedit + 3] = tickposition;
          if (sublevels[navlevelpatedit+2] == 0 ){
            sublevels[navlevelpatedit + 2] = self->synth_start_note();
          }
        }

        static void note_selector_sampler() {

          // notes of said liner
          display.clearDisplay();
          navrange = 127;
          // some notes not showing checl lenght note computation
          doshownoteline_sampler();
          canvasBIG.drawLine(0, starty + 2, 127, starty + 2, SSD1306_INVERSE);
          draw_sampler_velobars();
          dodisplay();
          sublevels[navlevelpatedit + 3] = tickposition;
          if (sublevels[navlevelpatedit+2] == 0 ){
            sublevels[navlevelpatedit + 2] = self->flash_start_note();
          }
        }

        static void start_cell_sampler() {
          previousnavlevel = navlevel;
          display.clearDisplay();
          navrange = 31;
          canvasBIG.fillRect(0, 32,127,64-32, SSD1306_BLACK);
          sublevels[navlevelpatedit + 4] = sublevels[navlevelpatedit + 3];
          duplicatelenghofnotestarray2();
          duplicateevent2();
          display.clearDisplay();
          doshownoteline_sampler();
          canvasBIG.drawLine(0, starty + 2, 127, starty + 2, SSD1306_INVERSE);
          drawCursorCol();
          draw_sampler_velobars();

          dodisplay();
          //sublevels[navlevelpatedit + 4] = sublevels[navlevelpatedit + 3];
          retroaction = sublevels[navlevelpatedit + 2] ;

        }

        static void start_cell_synth() {
          previousnavlevel = navlevel;
          //last level showing the noteline and its velocity
          display.clearDisplay();
          navrange = 31;
          canvasBIG.fillRect(0, 32,127,64-32, SSD1306_BLACK);
          sublevels[navlevelpatedit + 4] = sublevels[navlevelpatedit + 3];
          duplicatelenghofnotestarray();
          duplicateevent1();
          //why
          display.clearDisplay();
          doshownoteline();
          canvasBIG.drawLine(0, starty + 2, 127, starty + 2, SSD1306_INVERSE);
          drawCursorCol();
          draw_synth_velobars();
          dodisplay();
          retroaction = sublevels[navlevelpatedit + 2] ;
        }

        static void draw_synth_velobars(byte lvl=sublevels[navlevelpatedit+1]){
          int velobar ;
          for (int i = 0; i < pbars; i++) {
            velobar = map(synth_partition[lvl][i][2],0,127,0,16);
            canvasBIG.fillRect((i*(128/32)), 64-velobar,4 ,velobar, SSD1306_WHITE);
          }
        }

        static void draw_all_velobars(){
          for (int i = 0; i < synth_liners_count; i++) {
            draw_synth_velobars(i);
          }
        }

        static void draw_sampler_velobars(byte lvl=sublevels[navlevelpatedit+1]){
          int velobar ;
          for (int i = 0; i < pbars; i++) {
            velobar = map(sampler_partition[lvl][i][2],0,127,0,16);
            canvasBIG.fillRect((i*(128/32)), 64-velobar,4 ,velobar, SSD1306_WHITE);
          }
        }

        static void draw_all_sampler_velobars(){
          for (int i = 0; i < flash_liners_count; i++) {
            draw_sampler_velobars(i);
          }
        }

        static void killnextnoteoff_synth(byte liner, byte notee, byte fromi) {
          for (int i = fromi + 1; i < pbars; i++) {
            if (synth_off_pat[liner][i][1] == notee) {
              synth_off_pat[liner][i][1] = 0;
              return;
            }
          }
          for (int i = 0; i < fromi; i++) {
            if (synth_off_pat[liner][i][1] == notee) {
              synth_off_pat[liner][i][1] = 0;
              return;
            }
          }
        }

        static void killnextnoteoff_sampler(byte liner, byte notee, byte fromi) {
          for (int i = fromi + 1; i < pbars; i++) {
            if (sampler_off_pat[i][1] == notee) {
              sampler_off_pat[i][1] = 0;
              return;
            }
          }
          for (int i = 0; i < fromi; i++) {
            if (sampler_off_pat[i][1] == notee) {
              sampler_off_pat[i][1] = 0;
              return;
            }
          }
        }

        static void nogood_set_sampler_at_pos(byte ch_, byte nt_, byte ve_){
          byte sub1 = sublevels[navlevelpatedit + 1];
          //byte sub2 = sublevels[navlevelpatedit + 2];
          byte sub3 = sublevels[navlevelpatedit + 3];
          byte sub4 = sublevels[navlevelpatedit + 4];
          temp_sampler_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][0] = ch_;
          temp_sampler_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][1] = nt_;
          temp_sampler_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][2] = ve_;
          sampler_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][0] = ch_;
          sampler_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][1] = nt_;
          sampler_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][2] = ve_;

          byte laOffpos;
          length2pbars[sub1][sub3] = (sub4 - sub3) * 4;
          if (length2pbars[sub1][sub3] < 0) {
            length2pbars[sub1][sub3] = 4;
          }
          laOffpos = sub3 + (length2pbars[sub1][sub3] / 4);
          if (laOffpos == sub3) {
            laOffpos += 1;
          }
          if (laOffpos > pbars) {
            laOffpos = laOffpos - pbars;
          }
          sampler_off_pat[laOffpos][0] = ch_;
          sampler_off_pat[laOffpos][1] = nt_;
        }

        static void set_cell_sampler() {
          previousnavlevel = navlevel;
          set_sampler_at_pos(samplermidichannel,sublevels[navlevelpatedit + 2],64);
          addinglenght = 0;
          refresh_flash_track();
          stretch_cell_velocity_sampler();
        }

        static void fourth_level_sampler(){
          if (previousnavlevel != navlevel) {
              initiateasamplerliner(sublevels[navlevelpatedit + 2], byte(mixlevelsM[2] * 127));
              shutlineroff(samplermidichannel,sublevels[navlevelpatedit + 2]);                    
              previousnavlevel = navlevel;
            }

            stretch_cell_sampler();
        }

        static void fourth_level_synth(){
          if (previousnavlevel != navlevel) {

              initiateasynthliner(sublevels[navlevelpatedit + 2], byte(mixlevelsM[1] * 127));
              //delay(300);
              shutlineroff(synthmidichannel,sublevels[navlevelpatedit + 2]);
              previousnavlevel = navlevel;
            }
            stretch_cell_synth();
        }

        static void stretch_cell_synth() {
          // clickon liner /note / at tickpos

          byte decednote2 = synth_partition[sublevels[navlevelpatedit + 1]]
                                        [sublevels[navlevelpatedit + 3]][2];
          if (decednote2) {
            //delete previous key if present
            //set_synth_at_pos();
            refresh_synth_track();
            //drawCursorCol2();
            draw_synth_velobars();
            //sublevels[navlevel+1] = decednote2 ;
            //length0pbars[sub1][sub3]
            sublevels[navlevelpatedit + 4] = (length0pbars[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]]/4)+sublevels[navlevelpatedit + 3] ;
            returntonav(navlevel+1,127,decednote2);

          } else {
            addinglenght = 1;
            temp_synth_partition[sublevels[navlevelpatedit + 1]]
                            [sublevels[navlevelpatedit + 3]][0] = synthmidichannel;
            temp_synth_partition[sublevels[navlevelpatedit + 1]]
                            [sublevels[navlevelpatedit + 3]][1] =
                                (byte)sublevels[navlevelpatedit + 2];
            temp_synth_partition[sublevels[navlevelpatedit + 1]]
                            [sublevels[navlevelpatedit + 3]][2] = (byte)64;

            navrange = 31;
            templength0pbars[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]] =
                                (sublevels[navlevelpatedit + 4] - sublevels[navlevelpatedit + 3]) * 4;

            if (templength0pbars[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]] < 0) {
              templength0pbars[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]] = 4;}
            refresh_synth_track();
            display.clearDisplay();
            sublevels[navlevelpatedit + 5] = temp_synth_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][2];
            doshownoteline2();
            canvasBIG.drawLine(0, starty + 2, 127, starty + 2, SSD1306_INVERSE);
            drawCursorCol2();
            draw_synth_velobars();
            dodisplay();
          }
        }

        static void set_cell_synth() {
          previousnavlevel = navlevel;
          set_synth_at_pos(synthmidichannel,sublevels[navlevelpatedit + 2],64);
          addinglenght = 0;
          refresh_synth_track();
          //
          //sublevels[navlevelpatedit + 3] = sublevels[navlevelpatedit + 4] ;
          //doshownoteline2();
          //canvasBIG.drawLine(0, starty + 2, 127, starty + 2, SSD1306_INVERSE);
          //drawCursorCol2();
          //draw_synth_velobars();
          //dodisplay();
          stretch_cell_velocity();
          //returntonav(navlevelpatedit + 3,31,sublevels[navlevelpatedit + 4]);
          //show();
          // computelenghtmesureoffline_synth();
          //call_pt_show();
          //route_pattern_menu();
        }

        static void stretch_cell_sampler() {
          /*
          navrange = 31;
          byte decednote2 = sampler_partition[sublevels[navlevelpatedit + 1]]
                                      [sublevels[navlevelpatedit + 3]][2];
          if (decednote2) {
            returntonav(navlevel+1,navrange,decednote2);
          } else {
            set_sampler_at_pos(samplermidichannel,sublevels[navlevelpatedit + 2],64);

            refresh_flash_track();
            returntonav(navlevel+1,127,64);
          }
          */
          byte decednote2 = sampler_partition[sublevels[navlevelpatedit + 1]]
                                        [sublevels[navlevelpatedit + 3]][2];
          if (decednote2) {
            //delete previous key if present
            //set_synth_at_pos();
            refresh_flash_track();
            //drawCursorCol2();
            draw_sampler_velobars();
            //sublevels[navlevel+1] = decednote2 ;
            //length0pbars[sub1][sub3]
            sublevels[navlevelpatedit + 4] = (length2pbars[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]]/4)+sublevels[navlevelpatedit + 3] ;
            returntonav(navlevel+1,127,decednote2);

          } else {
            addinglenght = 1;
            temp_sampler_partition[sublevels[navlevelpatedit + 1]]
                            [sublevels[navlevelpatedit + 3]][0] = samplermidichannel;
            temp_sampler_partition[sublevels[navlevelpatedit + 1]]
                            [sublevels[navlevelpatedit + 3]][1] =
                                (byte)sublevels[navlevelpatedit + 2];
            temp_sampler_partition[sublevels[navlevelpatedit + 1]]
                            [sublevels[navlevelpatedit + 3]][2] = (byte)64;

            navrange = 31;
            templength2pbars[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]] =
                                (sublevels[navlevelpatedit + 4] - sublevels[navlevelpatedit + 3]) * 4;

            if (templength2pbars[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]] < 0) {
              templength2pbars[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]] = 4;}
            refresh_flash_track();
            display.clearDisplay();
            sublevels[navlevelpatedit + 5] = temp_sampler_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][2];
            doshownoteline2_sampler();
            canvasBIG.drawLine(0, starty + 2, 127, starty + 2, SSD1306_INVERSE);
            drawCursorCol2();
            draw_sampler_velobars();
            dodisplay();
          }
        }

        static void stretch_cell_velocity() {
            navrange = 127;
            temp_synth_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][2] = sublevels[navlevelpatedit + 5];
            synth_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][2] = sublevels[navlevelpatedit + 5];
            refresh_synth_track();
            display.clearDisplay();
            doshownoteline3();
            canvasBIG.drawLine(0, starty + 2, 127, starty + 2, SSD1306_INVERSE);
            draw_synth_velobars();
            dodisplay();
        }

        static void set_synth_at_pos(byte ch_, byte nt_, byte ve_){
          byte sub1 = sublevels[navlevelpatedit + 1];
          //byte sub2 = sublevels[navlevelpatedit + 2];
          byte sub3 = sublevels[navlevelpatedit + 3];
          byte sub4 = sublevels[navlevelpatedit + 4];
          synth_partition[sub1][sub3][0] = ch_;
          synth_partition[sub1][sub3][1] = nt_;
          synth_partition[sub1][sub3][2] = ve_;
          //synth_off_pat[sub1][sub4][0] = ch_;
          //synth_off_pat[sub1][sub4][1] = nt_;

          byte laOffpos;
          /*
          synth_partition[sub1][sub3][0] = synthmidichannel;
          synth_partition[sub1][sub3][1] = sub2;
          synth_partition[sub1][sub3][2] = ve_;
            */

          length0pbars[sub1][sub3] = (sub4 - sub3) * 4;
          if (length0pbars[sub1][sub3] < 0) {
            length0pbars[sub1][sub3] = 4;
          }
          laOffpos = sub3 + (length0pbars[sub1][sub3] / 4);
          if (laOffpos == sub3) {
            laOffpos += 1;
          }
          if (laOffpos > pbars) {
            laOffpos = laOffpos - pbars;
          }
          synth_off_pat[sub1][laOffpos][0] = ch_;
          synth_off_pat[sub1][laOffpos][1] = nt_;
          terminatenotesinbetween_synth();
          // not sure (for orphans but why would there be any?)
          terminateOffz_synth(sub1);
       

          //off
          if (!ve_){
            killnextnoteoff_synth(sub1,synth_partition[sub1][sub3][1],sub3);

            synth_partition[sub1][sub3][0] = 0;
            synth_partition[sub1][sub3][1] = 0;
            synth_partition[sub1][sub3][2] = 0;
          }
        }
        static void terminateOffz_synth(int linei) {
          for (int i = 0; i < pbars; i++) {
            if (synth_off_pat[linei][i][1] != 0) {
              if (self->terminateorphanseventsOff_synth(linei, synth_off_pat[linei][i][1])) {
                clearsaniloop = 0;
                synth_off_pat[linei][i][0] = 0;
                synth_off_pat[linei][i][1] = 0;
              }
            }
          }
        }


        bool terminateorphanseventsOff_synth(int linei, byte lanotef) {
          for (int i = 0; i < pbars; i++) {
            if (synth_partition[linei][i][1] == lanotef) {
              // at least someone is using it somewhere
              return 0;
            }
          }
          return 1;
        }

        bool terminateorphanseventsOff_sampler(int linei, byte lanotef) {
          for (int i = 0; i < pbars; i++) {
            if (sampler_partition[linei][i][1] == lanotef) {
              // at least someone is using it somewhere
              return 0;
            }
          }
          return 1;
        }
        static void terminateOffz_sampler(int linei) {
          for (int i = 0; i < pbars; i++) {
            if (sampler_off_pat[i][1] != 0) {
              if (self->terminateorphanseventsOff_sampler(linei, sampler_off_pat[i][1])) {
                clearsaniloop = 0;
                sampler_off_pat[i][0] = 0;
                sampler_off_pat[i][1] = 0;
              }
            }
          }
        }
        static void set_sampler_at_pos(byte ch_, byte nt_, byte ve_){
          byte sub1 = sublevels[navlevelpatedit + 1];
          //byte sub2 = sublevels[navlevelpatedit + 2];
          byte sub3 = sublevels[navlevelpatedit + 3];
          byte sub4 = sublevels[navlevelpatedit + 4];
          sampler_partition[sub1][sub3][0] = ch_;
          sampler_partition[sub1][sub3][1] = nt_;
          sampler_partition[sub1][sub3][2] = ve_;
          byte laOffpos;
          length2pbars[sub1][sub3] = (sub4 - sub3) * 4;
          if (length2pbars[sub1][sub3] < 0) {
            length2pbars[sub1][sub3] = 4;
          }
          laOffpos = sub3 + (length2pbars[sub1][sub3] / 4);
          if (laOffpos == sub3) {
            laOffpos += 1;
          }
          if (laOffpos > pbars) {
            laOffpos = laOffpos - pbars;
          }
          sampler_off_pat[laOffpos][0] = ch_;
          sampler_off_pat[laOffpos][1] = nt_;
          terminatenotesinbetween_sampler();
          // not sure (for orphans but why would there be any?)
          terminateOffz_sampler(sub1);
          if (!ve_){
            killnextnoteoff_sampler(sub1,sampler_partition[sub1][sub3][1],sub3);
            sampler_partition[sub1][sub3][0] = 0;
            sampler_partition[sub1][sub3][1] = 0;
            sampler_partition[sub1][sub3][2] = 0;
          }
        }

        static void set_cell_velocity() {
          previousnavlevel = navlevel;
          byte sub1 = sublevels[navlevelpatedit + 1];

          byte sub3 = sublevels[navlevelpatedit + 3];
          byte sub5 = sublevels[navlevelpatedit + 5];

          Serial.println(sub5);
          synth_partition[sub1][sub3][2] = sub5;

          addinglenght = 0;

          if (!(sublevels[navlevelpatedit + 5])){
            set_synth_at_pos(0,0,0);
          }
          refresh_synth_track();
          sublevels[navlevelpatedit + 3] = sublevels[navlevelpatedit + 4] ;

          returntonav(navlevelpatedit + 3,31,sublevels[navlevelpatedit + 4]);
          //show();
          // computelenghtmesureoffline_synth();
          //call_pt_show();
          //route_pattern_menu();
        }

        static void set_cell_velocity_sampler() {
          previousnavlevel = navlevel;

          sampler_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][2] = sublevels[navlevelpatedit + 5];
          if (!(sublevels[navlevelpatedit + 5])){
            set_sampler_at_pos(0,0,0);
          }
          refresh_flash_track();
          sublevels[navlevelpatedit + 3] = sublevels[navlevelpatedit + 4] ;
          returntonav(navlevelpatedit + 3,31,sublevels[navlevelpatedit + 4]);
          //show();
          // computelenghtmesureoffline_synth();
          //call_pt_show();
          //route_pattern_menu();
        }

        static void stretch_cell_velocity_sampler() {

            navrange = 127;
            temp_sampler_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][2] = sublevels[navlevelpatedit + 5];
            sampler_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][2] = sublevels[navlevelpatedit + 5];
            refresh_flash_track();
            display.clearDisplay();
            doshownoteline3_sampler();
            canvasBIG.drawLine(0, starty + 2, 127, starty + 2, SSD1306_INVERSE);
            draw_sampler_velobars();
            dodisplay();
        }

        static constexpr void (*_route_nav_synths[6])() = {&track_selector_synth, &note_selector_synth,
                          &start_cell_synth, &fourth_level_synth, &set_cell_synth,
                          &set_cell_velocity};
        static constexpr void (*_route_nav_samplers[6])() = {&track_selector_sampler, &note_selector_sampler,
                          &start_cell_sampler, &fourth_level_sampler, &set_cell_sampler,
                        &set_cell_velocity_sampler};
        //has to be of length 6 to reach last cell click
        static constexpr void (*_nav_home_route[7])() = {&homer,&player_selector,&player_selector,
                                                  &player_selector,&player_selector,&player_selector,
                                                  &player_selector};

    private:
      static constexpr void (*_nav_peditors[2])() = {&call_synth_event_cells,&call_sampler_event_cells};
      static PatEditRouter* self;
};

PatEditRouter* PatEditRouter::self = nullptr;
EXTMEM PatEditRouter _pe;

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
          dodisplay();
        }

        static void pattern_nav_one(){
          navrange = patterns_count - 1;
          if (sublevels[1] == 1) {
            navrange = patterns_count;
          }
          displaythelistofpatterns();
          doPatternsmenu();
          dodisplay();
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
          for (int i = 0; i < 32; i++) {
            recorded_ccs[i] = 0 ;
          }
          for (int i = 0; i < pbars; i++) {
            for (int j = 0; j < 128; j++) {
              if (cc_partition[j][i] != 127){
                for (int k = 0; k < 32; k++) {
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
                  if ((lenint > synth_liners_count + flash_liners_count - 1) ||
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
                if (parsedchannel == 0 || parsedchannel == samplermidichannel) {
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
                  if ((lenint > synth_liners_count + flash_liners_count - 1) ||
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
                if (parsedchannel == 0) {
                  break;
                }
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
                  if ((lenint > synth_liners_count - 1) ||
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
            call_refresh_synth_track();

            computelenghtmesureoffline_synth();
            computelenghtmesureoffline_sampler();
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
          //dodisplay();
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
            for (int j = 0; j < synth_liners_count; j++) {
              if (synth_off_pat[j][t][1] != 0) {
                midifilelinerOff(pat_filer,j, t);
              }
            }
            for (int j = 0; j < synth_liners_count; j++) {
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
            for (int j = 0; j < synth_liners_count; j++) {
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
EXTMEM PatternsMenuRouter _pt;

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
