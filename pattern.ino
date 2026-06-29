
class POptionsRouter : public SectionHolder {
    public:
        POptionsRouter() {
                    this->home_navrange=3;
                    this->relative_navlevel=2;
                    this->max_navlevel=5;
                    this->sublevels_address={4,0,0};
                    //home method not really used yet
                    //this->set_home(call_fx_mainpanel);
                    }

        void clearlapattern() {
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

        void clearCCline() {
          for (int j = 0; j < pbars; j++) {
            for (int i = 0; i < 128; i++) {

              cc_partition[i][j] = 127;
            }
          }
        }

        void clearsynthpatternline() {
          for (int j = 0; j < pbars; j++) {
            for (int i = 0; i < liners_count; i++) {

              synth_partition[i][j][1] = 0;
              synth_partition[i][j][2] = 0;
              synth_partition[i][j][0] = 0;
              length1notes1[i][j] = 0;
              synth_off_pat[i][j][0] = 0;
              synth_off_pat[i][j][1] = 0;
            }
            track_cells[0][j] = 0;
          }
        }
        void merge_synth_partition_liners(){
          byte note_encoutered ;
          byte liner_encoutered[liners_count] = {0,0,0,0,0,0} ;

          for (int j=0;j<pbars;j++){
            note_encoutered = 0 ;
            for (int i=0;i<liners_count;i++){
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
        void clearsamplerpatternline() {
          for (int j = 0; j < pbars; j++) {
            for (int i = 0; i < nombreofSamplerliners; i++) {

              sampler_partition[i][j][1] = 0;
              sampler_partition[i][j][2] = 0;
              sampler_partition[i][j][0] = 0;
              //      length2notes1[i][j]= 0;
            }
            track_cells[1][j] = 0;
            sampler_off_pat[j][0] = 0;
            sampler_off_pat[j][1] = 0;
          }
        }
        void optionspattern() {
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

        void dotranspose() {
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

        void doShifter() {
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

        void dotransposesynth() {
          if (sublevels[3] - 7 > 0) {
            shiftnotes1down(abs(sublevels[3] - 7));
          }
          if (sublevels[3] - 7 < 0) {
            shiftnotes1up(abs(sublevels[3] - 7));
          }
          call_refresh_track();
        }

        void dotransposeCC() {
          if (sublevels[3] - 7 > 0) {
            shiftnotesCCdown(abs(sublevels[3] - 7));
          }
          if (sublevels[3] - 7 < 0) {
            shiftnotesCCup(abs(sublevels[3] - 7));
          }
        }

        void doShifterCC() {
          if (sublevels[3] - 16 > 0) {
            shiftnotesCCleft(abs(sublevels[3] - 16));
          }
          if (sublevels[3] - 16 < 0) {
            shiftnotesCCright(abs(sublevels[3] - 16));
          }
        }

        void shiftnotesCCup(int leshifter) {
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

        void shiftnotesCCdown(int leshifter) {

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

        void shiftnotesCCright(int leshifter) {
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

        void shiftnotesCCleft(int leshifter) {

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

        void shiftnotes1up(int leshifter) {
          for (int shifts = 0; shifts < leshifter; shifts++) {
            for (int i = 0; i < liners_count; i++) {
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

        void shiftnotes1down(int leshifter) {
          for (int shifts = 0; shifts < leshifter; shifts++) {

            for (int i = 0; i < liners_count; i++) {
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

        void shiftnotes1right(int leshifter) {
          byte letempevent1[2][3];
          for (int shifts = 0; shifts < leshifter; shifts++) {
            for (int i = 0; i < liners_count; i++) {
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

        void shiftnotes1left(int leshifter) {

          byte letempevent1[2][3];
          for (int shifts = 0; shifts < leshifter; shifts++) {

            for (int i = 0; i < liners_count; i++) {
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

        void dotransposesampler() {
          if (sublevels[3] - 7 > 0) {
            shiftnotes2down(abs(sublevels[3] - 7));
          }
          if (sublevels[3] - 7 < 0) {

            shiftnotes2up(abs(sublevels[3] - 7));
          }
          call_refreshevented2();
        }

        void doShiftersampler() {
          if (sublevels[3] - 16 > 0) {
            shiftnotes2left(abs(sublevels[3] - 16));
          }
          if (sublevels[3] - 16 < 0) {

            shiftnotes2right(abs(sublevels[3] - 16));
          }
          call_refreshevented2();
        }

        void shiftnotes2up(int leshifter) {

          for (int shifts = 0; shifts < leshifter; shifts++) {

            for (int j = 0; j < pbars; j++) {
              if (((int)sampler_off_pat[j][1] < 127) &&
                  ((int)sampler_off_pat[j][1] > 2)) {
                sampler_off_pat[j][1]++;
              }
              for (int i = 0; i < nombreofSamplerliners; i++) {
                if (((int)sampler_partition[i][j][1] < 127) &&
                    ((int)sampler_partition[i][j][1] > 2)) {

                  sampler_partition[i][j][1]++;
                }
              }
            }
          }
        }

        void shiftnotes2down(int leshifter) {
          for (int shifts = 0; shifts < leshifter; shifts++) {
            for (int j = 0; j < pbars; j++) {
              if ((int)sampler_off_pat[j][1] > 1) {
                sampler_off_pat[j][1]--;
              }
              for (int i = 0; i < nombreofSamplerliners; i++) {
                if ((int)sampler_partition[i][j][1] > 1) {

                  sampler_partition[i][j][1]--;
                }
              }
            }
          }
        }

        void shiftnotes2right(int leshifter) {
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
              for (int i = 0; i < nombreofSamplerliners; i++) {
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

        void shiftnotes2left(int leshifter) {

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
              for (int i = 0; i < nombreofSamplerliners; i++) {
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

        void showtransposedisplays() {
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

        void doShiftersynth() {
          if (sublevels[3] - 16 > 0) {
            shiftnotes1left(abs(sublevels[3] - 16));
          }
          if (sublevels[3] - 16 < 0) {

            shiftnotes1right(abs(sublevels[3] - 16));
          }
          call_refresh_track();
        }

        void showShifterdisplays() {
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

        void showlestargetdisplays() {
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

        void optionspatterndisplays() {
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

};

POptionsRouter _po = POptionsRouter();

class CCEditor : public SectionHolder {
    public:
        CCEditor() {
                    this->home_navrange=3;
                    this->relative_navlevel=2;
                    this->max_navlevel=5;
                    this->sublevels_address={4,0,0};
                    //home method not really used yet
                    //this->set_home(call_fx_mainpanel);
                    }

        void show() {
          Serial.println("shown");
          navrange = 127;
          showleditcc();
          editlaccactionpath();
          dodisplay();
        }

        void route_navlevel_1(){
            presets_nav_zero();
        }

        void showleditcc() {
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

        void headerccedit() {
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

        void showvertlinecursor(int lavertpos) {
          display.drawLine(lavertpos * (128 / pbars), 16, lavertpos * (128 / pbars), 64,
                          SSD1306_WHITE);
        }

        void editlaccactionpath() {
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
};

CCEditor _ce = CCEditor();

class PatEditRouter : public SectionHolder {
    public:
        PatEditRouter() {
                    this->home_navrange=3;
                    this->relative_navlevel=2;
                    this->max_navlevel=5;
                    this->sublevels_address={4,7,0};
                    //home method not really used yet
                    //this->set_home(call_fx_mainpanel);
                    }

        void homer(){
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

        void player_selector(){
          cellsizer = 8 * (16 / pbars);
          celltall = 8;
          startx = 0;
          starty = 16;
          navrange = patternlines - 1;
          dm.clear_3();
          _nav_peditors[sublevels[navlevelpatedit]]();
          dodisplay();
        }

        void show() {
           (this->*PatEditRouter::_nav_home_route[navlevel-navlevelpatedit])();
        }

        void doshownoteline_sampler() {
          cellsizer = 4;
          celltall = 4;
          startx = 0;
          starty = 16;
          int lenghtofthenote = 4;
          int decnote;
          int listoffsetter;
          int linern = sublevels[navlevelpatedit + 1];
          startingnoteline = sublevels[navlevelpatedit + 2];
          byte note0;
          canvasBIG.setCursor(0, 0);
          canvasBIG.print("Note = ");
          canvasBIG.print(sublevels[navlevelpatedit + 2]);
          canvasBIG.print(" Pos = ");
          canvasBIG.print(sublevels[navlevelpatedit + 3]);
          for (int notelines = startingnoteline; notelines > startingnoteline - 12;
              notelines--) {
            for (int i = 0; i < pbars; i++) {

              note0 = sampler_partition[linern][i][1];
              decnote = (int)note0;

              if (decnote == notelines && note0 != 0) {
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

        void doshownoteline() {
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
        
        void doshownoteline2() {
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

        void doshownoteline3() {
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
        void doshownoteline3_sampler() {
          cellsizer = 4;
          celltall = 4;
          startx = 0;
          starty = 16;
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

                listoffsetter = starty + (4 * (startingnoteline - notelines));
                canvasBIG.fillRect(startx + cellsizer * i, listoffsetter,
                                  4, celltall, SSD1306_WHITE);
                canvasBIG.drawLine(startx + cellsizer * i, listoffsetter,
                                  startx + cellsizer * i, listoffsetter + celltall,
                                  SSD1306_BLACK);
              }
            }
          }
        }

        void doshownoteline2_sampler() {
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
          canvasBIG.print("Note = ");
          canvasBIG.print(sublevels[navlevelpatedit + 2]);
          canvasBIG.print(" Pos = ");
          canvasBIG.print(sublevels[navlevelpatedit + 4]);
          byte note0;
          for (int notelines = startingnoteline; notelines > startingnoteline - 12;
              notelines--) {
            for (int i = 0; i < pbars; i++) {

              note0 = temp_sampler_partition[linern][i][1];

              decnote = (int)note0;
              if (decnote == notelines && note0 != 0) {

                // lenghtofthenote = templength2pbars[linern][i];

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

        void drawnoteRow() {
          // rows of audio sources : synth, sampler, others
          // listoffsetter
          // display.fillRect(startx, starty+sublevels[navlevelpatedit+2]*celltall,
          // (128-startx), celltall, SSD1306_WHITE);
          canvasBIG.drawLine(0, starty + 2, 127, starty + 2, SSD1306_INVERSE);
        }

        void drawPatternRow() {
          // rows of audio sources : synth, sampler, others
          canvasBIG.drawLine(startx, starty + sublevels[navlevelpatedit] * celltall + 3,
                            (128 - startx),
                            starty + sublevels[navlevelpatedit] * celltall + 3,
                            SSD1306_WHITE);
        }

        void drawEventRow() {
          // row of events (liners) on audio source (patternrow)
          canvasBIG.drawLine(
              0, starty + sublevels[navlevelpatedit + 1] * celltall + 3, 128,
              starty + sublevels[navlevelpatedit + 1] * celltall + 3, SSD1306_INVERSE);
        }

        void drawsamplerEventRow() {
          // row of events (liners) on audio source (patternrow)
          canvasBIG.drawLine(0,starty + (sublevels[navlevelpatedit + 1] - samplelinerspage) * celltall + 3, 128, starty + (sublevels[navlevelpatedit + 1] - samplelinerspage) * celltall + 3,
              SSD1306_INVERSE);
        }

        void drawsynthEventRow() {
          // row of events (liners) on audio source (patternrow)
          canvasBIG.drawLine(0,starty + (sublevels[navlevelpatedit + 1] - synthlinerspage) * celltall + 3, 128, starty + (sublevels[navlevelpatedit + 1] - synthlinerspage) * celltall + 3,
              SSD1306_INVERSE);
        }

        void showblocksofevent() {
          cellsizer = 4;
          celltall = 8;
          startx = 0;
          starty = 0;
          for (int liner = 0; liner < liners_count; liner++) {
            for (int i = 0; i < pbars; i++) {
              if (synth_partition[liner][i][1] != 0) {
                canvasBIG.fillRect(startx + cellsizer * i + 1,
                                  starty + (celltall * liner) + 1, cellsizer - 2,
                                  celltall - 2, SSD1306_INVERSE);
              }
            }
          }
        }
        void showblocksofevent2_synth(){
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
        void showblocksofevent2() {
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

        void clearevented0(int lapatline) {

          for (int j = 0; j < pbars; j++) {
            track_cells[lapatline][j] = false;
          }
        }

        void refresh_track() {
          clearevented0(0);
          for (int linerrd = 0; linerrd < liners_count; linerrd++) {

            for (int i = 0; i < pbars; i++) {

              if (synth_partition[linerrd][i][1] != 0) {
                track_cells[0][i] = true;
              }
            }
          }
        }

        void refreshevented2() {
          clearevented0(1);
          for (int linerrd = 0; linerrd < nombreofSamplerliners; linerrd++) {

            for (int i = 0; i < pbars; i++) {

              if (sampler_partition[linerrd][i][1] != 0) {
                track_cells[1][i] = true;
              }
            }
          }
        }

        void dolistpatternlineblocks() {
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

        int getstartingnoteline() {
          byte min_note = 127 ;
          int averagenoteevent = 0;
          int nombrofnoteonliner = 0;
          // sublevels[navlevelpatedit+2] = 60 ;
          for (int ni = 0; ni < liners_count; ni++) {
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

        int getstartingnoteline2() {
          int averagenoteevent = 0;
          int nombrofnoteonliner = 0;
          // sublevels[navlevelpatedit+2] = 60 ;
          for (int ni = 0; ni < nombreofSamplerliners; ni++) {
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

        void sampler_event_cells() {
          (this->*PatEditRouter::_route_nav_samplers[navlevel-navlevelpatedit-1])();
        }

        void synth_event_cells() {
            (this->*PatEditRouter::_route_nav_synths[navlevel-navlevelpatedit-1])();
        }

        void terminatenotesinbetween() {
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

        void terminatenextnoteoff(byte liner, byte lanoteoff, byte fromi) {

          for (int i = 0; i < pbars; i++) {
            if (!offhasOnbutnototheroff(liner, lanoteoff, fromi)) {
              synth_off_pat[liner][fromi][1] = 0;
            }
          }
        }

        bool offhasOnbutnototheroff(byte liner, byte lanoteoff, byte fromi) {
          // for (int j = 0 ; j < liners_count ; j++ ) {
          for (int i = fromi - 1; i >= 0; i--) {
            if (synth_off_pat[liner][i][1] == lanoteoff) {
              terminatenextnoteoff(liner, lanoteoff, i);
            }
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

        void duplicateevent1() {
          for (int j = 0; j < liners_count; j++) {
            for (int i = 0; i < pbars; i++) {
              temp_synth_partition[j][i][0] = synth_partition[j][i][0];
              temp_synth_partition[j][i][2] = synth_partition[j][i][2];
              temp_synth_partition[j][i][1] = synth_partition[j][i][1];
            }
          }
        }
        void duplicateevent2() {
          for (int j = 0; j < nombreofSamplerliners; j++) {
            for (int i = 0; i < pbars; i++) {
              temp_sampler_partition[j][i][0] = sampler_partition[j][i][0];
              temp_sampler_partition[j][i][2] = sampler_partition[j][i][2];
              temp_sampler_partition[j][i][1] = sampler_partition[j][i][1];
            }
          }
        }

        void drawCursorCol() {
          int xpos = (sublevels[navlevelpatedit + 3] * 4) + 1;
          display.drawLine(xpos, starty, xpos, 64 - (starty), SSD1306_INVERSE);
        }

        void drawCursorCol2() {
          int xpos = (sublevels[navlevelpatedit + 4] * 4) + 1;
          display.drawLine(xpos, starty, xpos, 64 - (starty), SSD1306_INVERSE);
        }

        void duplicatelenghofnotestarray() {
          for (int j = 0; j < liners_count; j++) {
            for (int i = 0; i < pbars; i++) {
              templength0pbars[j][i] = length0pbars[j][i];
            }
          }
        }

        void track_selector() {
          // liners

          // drawguides();
          // if ( sublevels[navlevelpatedit] == 0 ) {
          
          if (sublevels[navlevelpatedit + 1] > 3 && synthlinerspage < liners_count) {
            synthlinerspage = sublevels[navlevelpatedit + 1] - 3;
          } else {
            synthlinerspage = 0;
          }
          
          display.clearDisplay();
          navrange = liners_count - 1;
          show_track_header();
          //showblocksofevent();
          //drawEventRow();
          showblocksofevent2_synth();
          drawsynthEventRow();
          draw_all_velobars();
          dodisplay();
          sublevels[navlevelpatedit + 2] = getstartingnoteline();
     
        }
        void show_track_header(){
          String head_title[2]={"Synth","Flash"};
          canvastitle.setCursor(0, 0);
          canvastitle.setTextSize(1);
          canvastitle.print(head_title[sublevels[navlevelpatedit]]);
          canvastitle.print(" Track ");
          canvastitle.print(sublevels[navlevelpatedit + 1] + 1);
        }

        void track_selector_sampler() {

          if (sublevels[navlevelpatedit + 1] > 3 && samplelinerspage < 16) {
            samplelinerspage = sublevels[navlevelpatedit + 1] - 3;
          } else {
            samplelinerspage = 0;
          }
          display.clearDisplay();
          show_track_header();
          navrange = nombreofSamplerliners - 1;
          showblocksofevent2();
          // samplelinerspage
          drawsamplerEventRow();
          draw_all_sampler_velobars();
          dodisplay();
          sublevels[navlevelpatedit + 2] = getstartingnoteline2();
        }

        void note_selector() {

          // notes of said liner
          display.clearDisplay();
          navrange = 127;
          // some notes not showing checl lenght note computation
          doshownoteline();
          drawnoteRow();
          draw_velobars();
          dodisplay();
          sublevels[navlevelpatedit + 3] = tickposition;
          if (sublevels[navlevelpatedit+2] == 0 ){
            sublevels[navlevelpatedit + 2] = getstartingnoteline();
          }
        }

        void note_selector_sampler() {

          // notes of said liner
          display.clearDisplay();
          navrange = 127;
          // some notes not showing checl lenght note computation
          doshownoteline_sampler();
          drawnoteRow();
          draw_sampler_velobars();
          dodisplay();
          sublevels[navlevelpatedit + 3] = tickposition;
        }

        void start_cell() {
          previousnavlevel = navlevel;

          //last level showing the noteline and its velocity
          display.clearDisplay();
          navrange = 31;
          canvasBIG.fillRect(0, 32,127,64-32, SSD1306_BLACK);
          sublevels[navlevelpatedit + 4] = sublevels[navlevelpatedit + 3];
          duplicatelenghofnotestarray();
          duplicateevent1();

          display.clearDisplay();
          doshownoteline();
          drawnoteRow();
          drawCursorCol();
          draw_velobars();
          dodisplay();
          retroaction = sublevels[navlevelpatedit + 2] ;
        }

        void draw_velobars(byte lvl=sublevels[navlevelpatedit+1]){
          int velobar ;
          for (int i = 0; i < pbars; i++) {
            velobar = map(synth_partition[lvl][i][2],0,127,0,16);
            canvasBIG.fillRect((i*(128/32)), 64-velobar,4 ,velobar, SSD1306_WHITE);
          }
        }

        void draw_all_velobars(){
          for (int i = 0; i < liners_count; i++) {
            draw_velobars(i);
          }
        }

        void draw_sampler_velobars(byte lvl=sublevels[navlevelpatedit+1]){
          int velobar ;
          for (int i = 0; i < pbars; i++) {
            velobar = map(sampler_partition[lvl][i][2],0,127,0,16);
            canvasBIG.fillRect((i*(128/32)), 64-velobar,4 ,velobar, SSD1306_WHITE);
          }
        }

        void draw_all_sampler_velobars(){
          for (int i = 0; i < nombreofSamplerliners; i++) {
            draw_sampler_velobars(i);
          }
        }

        void start_cell_sampler() {
          previousnavlevel = navlevel;
          display.clearDisplay();
          navrange = 31;
          doshownoteline_sampler();
          drawnoteRow();
          drawCursorCol();
          draw_sampler_velobars();

          dodisplay();
          sublevels[navlevelpatedit + 4] = sublevels[navlevelpatedit + 3];

          duplicateevent2();
          retroaction = sublevels[navlevelpatedit + 2] ;

        }

        void killnextnoteoff(byte liner, byte notee, byte fromi) {
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

        void set_sampler_at_pos(byte ch_, byte nt_, byte ve_){
          temp_sampler_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][0] = ch_;
          temp_sampler_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][1] = nt_;
          temp_sampler_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][2] = ve_;
          sampler_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][0] = ch_;
          sampler_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][1] = nt_;
          sampler_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][2] = ve_;
          sampler_off_pat[sublevels[navlevelpatedit + 4]][0] = ch_;
          sampler_off_pat[sublevels[navlevelpatedit + 4]][1] = nt_;
        }

        void set_cell_sampler() {
          previousnavlevel = navlevel;
          refreshevented2();
          stretch_cell_velocity_sampler();
        }

        void fourth_level_sampler(){
          if (previousnavlevel != navlevel) {
              initiatesamplerline(15, samplermidichannel,
                                  sublevels[navlevelpatedit + 2],
                                  byte(mixlevelsM[2] * 127));
              previousnavlevel = navlevel;
            }

            stretch_cell_sampler();
        }

        void fourth_level(){
          if (previousnavlevel != navlevel) {

              initiateasynthliner(sublevels[navlevelpatedit + 2],
                                  byte(mixlevelsM[1] * 127));
              //delay(300);
              shutlineroff(sublevels[navlevelpatedit + 2]);
              previousnavlevel = navlevel;
            }
            stretch_cell();
        }

        void stretch_cell() {
          // clickon liner /note / at tickpos

          byte decednote2 = synth_partition[sublevels[navlevelpatedit + 1]]
                                        [sublevels[navlevelpatedit + 3]][2];
          if (decednote2) {
            //delete previous key if present
            //set_synth_at_pos();
            refresh_track();
            //drawCursorCol2();
            draw_velobars();
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
            refresh_track();
            display.clearDisplay();
            sublevels[navlevelpatedit + 5] = temp_synth_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][2];
            doshownoteline2();
            drawnoteRow();
            drawCursorCol2();
            draw_velobars();
            dodisplay();
          }
        }
        void set_cell() {
          previousnavlevel = navlevel;
          set_synth_at_pos(synthmidichannel,sublevels[navlevelpatedit + 2],64);
          addinglenght = 0;
          refresh_track();
          //
          //sublevels[navlevelpatedit + 3] = sublevels[navlevelpatedit + 4] ;
          //doshownoteline2();
          //drawnoteRow();
          //drawCursorCol2();
          //draw_velobars();
          //dodisplay();
          stretch_cell_velocity();
          //returntonav(navlevelpatedit + 3,31,sublevels[navlevelpatedit + 4]);
          //show();
          // computelenghtmesureoffline();
          //call_pt_show();
          //route_pattern_menu();
        }

        void stretch_cell_sampler() {
          navrange = 31;
          byte decednote2 = sampler_partition[sublevels[navlevelpatedit + 1]]
                                      [sublevels[navlevelpatedit + 3]][2];
          if (decednote2) {
            returntonav(navlevel+1,navrange,decednote2);
          } else {
            set_sampler_at_pos(samplermidichannel,sublevels[navlevelpatedit + 2],64);
            
            refreshevented2();
            returntonav(navlevel+1,127,64);
          }
        }

        void stretch_cell_velocity() {
            navrange = 127;
            temp_synth_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][2] = sublevels[navlevelpatedit + 5];
            synth_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][2] = sublevels[navlevelpatedit + 5];
            refresh_track();
            display.clearDisplay();
            doshownoteline3();
            drawnoteRow();
            draw_velobars();
            dodisplay();
        }
        
        void set_synth_at_pos(byte ch_, byte nt_, byte ve_){
          byte sub1 = sublevels[navlevelpatedit + 1];
          byte sub2 = sublevels[navlevelpatedit + 2];
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
          terminatenotesinbetween();
          // not sure (for orphans but why would there be any?)
          terminateOffz(sub1);
          // just in case
          terminatenextnoteoff(sub1, sub2, laOffpos);

          //off
          if (!ve_){
            killnextnoteoff(sub1,synth_partition[sub1][sub3][1],sub3);
          
            synth_partition[sub1][sub3][0] = 0;
            synth_partition[sub1][sub3][1] = 0;
            synth_partition[sub1][sub3][2] = 0;
          }
        }

        void set_cell_velocity() {
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
          refresh_track();
          sublevels[navlevelpatedit + 3] = sublevels[navlevelpatedit + 4] ;

          returntonav(navlevelpatedit + 3,31,sublevels[navlevelpatedit + 4]);
          //show();
          // computelenghtmesureoffline();
          //call_pt_show();
          //route_pattern_menu();
        }

        void set_cell_velocity_sampler() {
          previousnavlevel = navlevel;

          sampler_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][2] = sublevels[navlevelpatedit + 5];
          if (!(sublevels[navlevelpatedit + 5])){
            set_sampler_at_pos(0,0,0);
          }
          refreshevented2();
          sublevels[navlevelpatedit + 3] = sublevels[navlevelpatedit + 4] ;
          returntonav(navlevelpatedit + 3,31,sublevels[navlevelpatedit + 4]);
          //show();
          // computelenghtmesureoffline();
          //call_pt_show();
          //route_pattern_menu();
        }

        void stretch_cell_velocity_sampler() {

            navrange = 127;
            temp_sampler_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][2] = sublevels[navlevelpatedit + 5];
            sampler_partition[sublevels[navlevelpatedit + 1]][sublevels[navlevelpatedit + 3]][2] = sublevels[navlevelpatedit + 5];
            refreshevented2();
            display.clearDisplay();
            doshownoteline3_sampler();
            drawnoteRow();
            draw_sampler_velobars();
            dodisplay();
        }

        using Action = void (PatEditRouter::*)();
        static constexpr Action _route_nav_synths[6] = {&PatEditRouter::track_selector, &PatEditRouter::note_selector,
                          &PatEditRouter::start_cell, &PatEditRouter::fourth_level, &PatEditRouter::set_cell,
                          &PatEditRouter::set_cell_velocity};
        static constexpr Action _route_nav_samplers[6] = {&PatEditRouter::track_selector_sampler, &PatEditRouter::note_selector_sampler,
                          &PatEditRouter::start_cell_sampler, &PatEditRouter::fourth_level_sampler, &PatEditRouter::set_cell_sampler,
                        &PatEditRouter::set_cell_velocity_sampler};
        //has to be of length 6 to reach last cell click
        static constexpr Action _nav_home_route[7] = {&PatEditRouter::homer,&PatEditRouter::player_selector,&PatEditRouter::player_selector,
                                                  &PatEditRouter::player_selector,&PatEditRouter::player_selector,&PatEditRouter::player_selector,
                                                  &PatEditRouter::player_selector};

    private:
        void (*_nav_peditors[2])() = {call_synth_event_cells,call_sampler_event_cells};
};

PatEditRouter _pe = PatEditRouter();

class PatternsMenuRouter : public SectionHolder {
    public:
        PatternsMenuRouter() {
                    this->home_navrange=sizeofpatternlistlabels-1;
                    this->relative_navlevel=1;
                    this->max_navlevel=5;
                    this->sublevels_address={4,0,0};
                    //home method not really used yet
                    //this->set_home(_pe.home);
                    //attach_menus_patterns();
                    }

        void route_navlevel_2(){
            if (_nav_pattern[sublevels[1]]) {
                (this->*PatternsMenuRouter::_nav_pattern[sublevels[1]])();
            }
        }

        void show() {
            (this->*PatternsMenuRouter::_route_nav[navlevel-1])();
        }

        void pattern_nav_zero(){
            // mode selection
            navrange = sizeofpatternlistlabels - 1;
            displaythelistofpatterns();
            dolistPatternsmenu();
            dodisplay();
        }

        void pattern_nav_one(){
            navrange = patterns_count;
            displaythelistofpatterns();
            dolistPatternsmenu();
            dodisplay();
        }

        void pattern_nav_two(){
            navrange = max(patterns_count - 1, 0);
            displaythelistofpatterns();
            dolistPatternsmenu();
            dodisplay();
        }

        void addnoteoff2next(byte lanotee, byte lapos) {
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

        void set_ccs() {
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

        void parsepattern() {
          refresh_patterns_names();
          // timescaller should be BPM dependant
          //    latimelineshifter = ((60000/19200)*pbars) ;
          // (60.0/BPMs)*1000)*pbars) = 1 bar millis
          const int pat_parser_size = 32000;
          char received_pattern[pat_parser_size];
          byte laccnote;
          byte parsedchannel;
          int letimescaler = 3125;
          File lepatternfile = SD.open(get_current_pattern_path().c_str());
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
                  if ((lenint > liners_count + nombreofSamplerliners - 1) ||
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
                  if ((lenint > liners_count + nombreofSamplerliners - 1) ||
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
                  if ((lenint > liners_count - 1) ||
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
            call_refresh_track();

            computelenghtmesureoffline();
            set_ccs();
          }
        }

        void list_patterns_files() {
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
        }

        String get_pattern_name(byte number) {
          char formatted_number[4] ;
          sprintf(formatted_number,"%02d",number);
          return "PATTERN" + (String)formatted_number ;
        }

        void refresh_patterns_names() {
          for (int i = 0 ; i < ptn_size ; i++) {
            //empty spots are left at the end of the list if it is small, otherwise the names are looped
            patterns_names[i] = " ";
            if (patterns_names_offset+i < patterns_count ) {
              patterns_names[i] = get_pattern_name_from_pt(patterns_indexes[patterns_names_offset+i]);
            } else if (patterns_count >= ptn_size ){
              patterns_names[i] = get_pattern_name_from_pt(patterns_indexes[(patterns_names_offset+i)%patterns_count]);
            }
          }
        }

        void displaythelistofpatterns() {
          display.clearDisplay();
          patterns_names_offset = sublevels[2];
          refresh_patterns_names();
          int startx = 73;
          int starty = 16;
          canvastitle.fillScreen(SSD1306_BLACK);
          canvastitle.setCursor(startx, 0);
          canvastitle.setTextSize(1);
          if (sublevels[2] == patterns_count && sublevels[1] == 1) {
            canvastitle.print("New()");
          } else {
            canvastitle.print(patterns_names[0].c_str());
          }
          canvastitle.setTextSize(1);
          canvasBIG.setTextSize(1);
          canvasBIG.fillScreen(SSD1306_BLACK);
          if (sublevels[2] == patterns_count) {
            for (int i = 0; i < ptn_size-1; i++) {
              canvasBIG.setCursor(startx, (10 * (patterns_count - sublevels[2])) + 16 + i*10);
              canvasBIG.println(patterns_names[i]);
            }
          } else {
            for (int i = 0; i < ptn_size - 1 ; i++) {
              canvasBIG.setCursor(startx, starty + i*10);
              canvasBIG.println(patterns_names[1 + i]);
            }
          }
          dodisplay();
        }

        void dolistPatternsmenu() {
          char patternlistlabels[sizeofpatternlistlabels][12] = {
              "Edit", "Save", "Load", "Copy", "Delete", "Params", "Clear", "C-Edit"};
          byte startx = 5;
          byte starty = 16;
          char *textin = (char *)patternlistlabels[sublevels[1]];
          canvastitle.fillScreen(SSD1306_BLACK);
          canvastitle.setCursor(0, 0);
          canvastitle.setTextSize(2);
          canvastitle.println(textin);
          canvasBIG.setTextSize(1);
          canvasBIG.fillScreen(SSD1306_BLACK);
          for (int i = 0; i < sizeofpatternlistlabels - 1 - (sublevels[1]); i++) {
            canvasBIG.setCursor(startx, starty + ((i)*10));
            canvasBIG.println(patternlistlabels[sublevels[1] + 1 + i]);
          }
          for (int i = 0; i < sublevels[1]; i++) {
            canvasBIG.setCursor(startx, (10 * (sizeofpatternlistlabels - sublevels[1]) + 6 + ((i)*10)));
            canvasBIG.println(patternlistlabels[i]);
          }
        }

        void deletepattern() {
          if (SD.exists(get_current_pattern_path().c_str())) {
            SD.remove(get_current_pattern_path().c_str());
          }
          list_patterns_files();
        }

        void copypattern() {
          File originpatternfile = SD.open(get_current_pattern_path().c_str());
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

        void midifileliner(File &pat_filer,int liner, int ticker) {

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

        void midifilelinerSampler(File &pat_filer,int liner, int ticker) {

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

        void midifilelinerOff(File &pat_filer, int liner, int ticker) {
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

        void midifileCC(File &pat_filer,int lecc, int ticker) {
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

        void write_midi_info(File &pat_filer) {
          latimeline = 0;
          // latimelineshifter = ((60000/19200)*pbars) ;
          // (60.0/BPMs)*1000)*pbars) = 1 bar millis 92 original
          pat_filer.print("MFile 0 1 19200\nMTrk\n");
          // for (int i = 0 ; i<5 ; i++ ) {

          for (int t = 0; t < pbars; t++) {

            latimeline = (3125 * t);
            for (int j = 0; j < liners_count; j++) {
              if (synth_off_pat[j][t][1] != 0) {
                midifilelinerOff(pat_filer,j, t);
              }
            }
            for (int j = 0; j < liners_count; j++) {
              if (synth_partition[j][t][1] != 0) {
                midifileliner(pat_filer,j, t);
              }
            }
            for (int j = 0; j < nombreofSamplerliners; j++) {
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
          return "PATTERNS/" + patterns_names[0] + ".TXT";
        }

        void writelemidi() {
          refresh_patterns_names();
          File pat_filer ;
          if (patterns_names_offset == patterns_count) {
            pat_filer = SD.open(get_new_file_name("PATTERNS/PATTERN").c_str(), FILE_WRITE);
          } else {
            if (SD.exists(get_current_pattern_path().c_str())) {
              SD.remove(get_current_pattern_path().c_str());
            }
            pat_filer = SD.open(get_current_pattern_path().c_str(), FILE_WRITE);
          }
          if (pat_filer) {
            write_midi_info(pat_filer);
            pat_filer.close();
          }
          pat_filer.close();
          list_patterns_files();
        }

        void dosavepattern() { canvastitle.fillScreen(SSD1306_BLACK); }

        void arpegiate() {
          for (int i = 0; i < nombreofarpeglines; i++) {
            calledarpegenote[i][0] = 0;
            for (int j = 0; j < liners_count; j++) {
              if (arpegnoteoffin[i][j] == 1) {
                shutlineroff(playingarpegiator[i][j]);
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

        void call_draw_sequencer(){
          _pe.show();
        }

        void call_options(){
          _po.optionspattern();
        }

        void call_edit_ccs(){
          _ce.show();
        }
        void call_clearpattern(){
           _po.clearlapattern();
        }

        using Action = void (PatternsMenuRouter::*)();
        static constexpr Action _route_nav[7] = {&PatternsMenuRouter::pattern_nav_zero, &PatternsMenuRouter::route_navlevel_2,
                        &PatternsMenuRouter::route_navlevel_2, &PatternsMenuRouter::route_navlevel_2, &PatternsMenuRouter::route_navlevel_2,
                         &PatternsMenuRouter::route_navlevel_2, &PatternsMenuRouter::route_navlevel_2};
        static constexpr Action _nav_pattern[sizeofpatternlistlabels] = {&PatternsMenuRouter::call_draw_sequencer,&PatternsMenuRouter::pattern_nav_one,
                                  &PatternsMenuRouter::pattern_nav_one, &PatternsMenuRouter::pattern_nav_one,
                                  &PatternsMenuRouter::pattern_nav_one,&PatternsMenuRouter::call_options,&PatternsMenuRouter::call_clearpattern,&PatternsMenuRouter::call_edit_ccs};

};

PatternsMenuRouter _pt = PatternsMenuRouter();

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
      _pt.arpegiate();
  }
  if (patternOn) {
    _se.use_pattern();
  }

  if (songplaying) {
    _se.update_song_player();
  }

}
