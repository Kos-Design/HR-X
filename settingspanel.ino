

/*
//TODO: implement in notespy
void notefreqloop() {
  if (notefreq1.available()) {
    float notep = notefreq1.read();
    float probz = notefreq1.probability();
    //  pseudoconsole("Note: %3.2f | Probability: %.2f\n", notep, probz);
  }
}
*/

class SettingsMenuRouter : public SectionHolder {
    public:
        SettingsMenuRouter() {
                    self = this;
                    this->home_navrange=settings_labels_count - 1;
                    this->relative_navlevel=2;
                    this->max_navlevel=5;
                    this->sublevels_address={5,0,0};
                    //home method not really used yet
                    //this->set_home(call_fx_mainpanel);
                    }

        char onboards[all_buttonns][8] = {
          "Pot 1",  "Pot 2",  "Pot 3",  "Pot 4",  "Pot 5",  "Pot 6",  "Pot 7",
          "Pot 8",  "Pot 9",  "Fdr 01", "Fdr 02", "Fdr 03", "Pad 01", "Pad 02",
          "Pad 03", "Pad 04", "Pad 05", "Pad 06", "Pad 07", "Pad 08", "Pad 09",
          "Pad 10", "Pad 11", "Pad 12", "Pad 13", "Pad 14", "Pad 15", "Pad 16",
          "But 01", "But 02", "But 03", "But 04", "But 05", "But 06", "But 07",
          "But 08", "But 09", "But 10", "But 11", "But 12", "But 13", "But 14",
          "But 15", "But 16", "But 17", "But 18", "Cfd",    "Jk X",   "Jk Y"};

        char ch_lbl_buffer[4];

        static void show() {
          if (navlevel == 1) {
            settings_nav_zero();
          }

          // arpegiator has its own panel -> 8 , same for 11 which is OnboardPanel
          if (navlevel >= 2) {
            settings_nav_one();
          }
        }

        static void set_in_source(){
          switch (self->AudioInSource) {
            case 0 :
              audioShield.inputSelect(AUDIO_INPUT_MIC);
              InMixL.gain(1, 0.01);
              InMixR.gain(1, 0.01);
              break;
            case 1 :
              audioShield.inputSelect(AUDIO_INPUT_LINEIN);
              InMixL.gain(1,1.0);
              InMixR.gain(1, 1.0);
              break;
            case 2 :
              InMixL.gain(1, 0.0);
              InMixR.gain(1, 0.0);
              break;

            default :
            break;
          }
        }

        char usnotes[12][5] = {"C",  "C#", "D",  "Eb", "E",  "F",
                       "F#", "G",  "G#", "A",  "Bb", "B"};

        char eunotes[12][5] = {"Do",  "Do#", "Re",   "Mib", "Mi",  "Fa",
                              "Fa#", "Sol", "Sol#", "La",  "Sib", "Si"};
        int AudioInSource = 2;

        float freqtonotes[128] = {
          8.21, 8.70, 9.22, 9.77, 10.35, 10.96, 11.61, 12.31,
          13.04, 13.81, 14.63, 15.50, 16.43, 17.40, 18.44, 19.53,
          20.70, 21.93, 23.23, 24.61, 26.07, 27.63, 29.27, 31.01,
          32.85, 34.81, 36.87, 39.07, 41.39, 43.85, 46.46, 49.22,
          52.15, 55.25, 58.54, 62.02, 65.70, 69.61, 73.75, 78.14,
          82.78, 87.70, 92.92, 98.44, 104.30, 110.50, 117.07, 124.03,
          131.41, 139.22, 147.50, 156.27, 165.56, 175.41, 185.84, 196.89,
          208.60, 221.00, 234.14, 248.06, 262.81, 278.44, 295.00, 312.54,
          331.13, 350.82, 371.68, 393.78, 417.19, 442.00, 468.28, 496.13,
          525.63, 556.89, 590.00, 625.08, 662.25, 701.63, 743.35, 787.55,
          834.38, 884.00, 936.57, 992.26, 1051.26, 1113.77, 1180.00, 1250.16,
          1324.50, 1403.26, 1486.70, 1575.11, 1668.77, 1768.00, 1873.13, 1984.51,
          2102.52, 2227.54, 2360.00, 2500.33, 2649.01, 2806.53, 2973.41, 3150.22,
          3337.54, 3536.00, 3746.26, 3969.03, 4205.04, 4455.08, 4719.99, 5000.66,
          5298.01, 5613.05, 5946.82, 6300.44, 6675.08, 7072.00, 7492.52, 7938.05,
          8410.07, 8910.16, 9439.99, 10001.32, 10596.03, 11226.10, 11893.64, 12600.87
        };

        static void settings_nav_zero(){
          reinitsublevels(2);
          debugmidion = 0;
          noteprint = 0;
          navrange = settings_labels_count - 1;
          makesettingslist();
          dodisplay();
        }

        static void OnBoardVpanelAction() {
          if (navlevel > 3) {
            if (((sublevels[2] <= 11) || (sublevels[2] > 45)) && (navlevel == 4)) {
              ordered_pots[potsboards[sublevels[2]]] = pot_assignements[sublevels[2]];
            }
            returntonav(2);
          }
        }

        static void OnBoardVpanelSelector() {

          int selecta = sublevels[2];
          if (navlevel == 2) {
            navrange = all_buttonns - 1;
            sublevels[3] = pot_assignements[sublevels[2]];
          }

          if (selecta < 9) {
            canvasBIG.drawRoundRect((selecta % 3) * 7 + 22, (selecta / 3) * 7 + 10, 9,
                                    9., 7, SSD1306_WHITE);
          }
          if ((selecta >= 9) && (selecta < 12)) {
            canvasBIG.drawRoundRect(46 + ((selecta - 9) * 8), 10, 8, 23, 3,
                                    SSD1306_WHITE);
          }
          if ((selecta > 11) && (selecta < 28)) {
            canvasBIG.drawRect(((selecta - 12) % 4) * 13 + 70,
                              (((selecta - 12) / 4) % 4) * 13 + 10, 14, 14,
                              SSD1306_WHITE);
          }
          if ((selecta > 27) && (selecta < 46)) {
            canvasBIG.drawRoundRect(((selecta - 28) % 9) * 7 + 5,
                                    ((selecta - 28) / 9) * 7 + 33, 9, 9, 9,
                                    SSD1306_WHITE);
          }
          if (selecta == 46) {
            canvasBIG.drawRoundRect(16, 51, 34, 8, 3, SSD1306_WHITE);
          }
          if (selecta == 47) {
            canvasBIG.setCursor(57, 52);
            canvasBIG.setTextSize(1);
            canvasBIG.print("X");
          }
          if (selecta == 48) {
            canvasBIG.setCursor(57, 52);
            canvasBIG.setTextSize(1);
            canvasBIG.print("Y");
          }

          canvasBIG.setCursor(8, 24);
          // canvasBIG.setTextSize(1);
          sprintf(self->ch_lbl_buffer, "%02d", but_channel[sublevels[2]]);
          canvasBIG.print(self->ch_lbl_buffer);

          if (navlevel == 3) {
            sublevels[4] = pot_assignements[sublevels[2]];
            pot_assignements[sublevels[2]] = sublevels[3];
            if (selecta <= 11) {
              navrange = 127;
            }

            if ((selecta > 11) && (selecta <= 45)) {
              navrange = 128 + 127;
            }
            if (selecta > 45) {
              navrange = 127;
            }
          }

          canvastitle.setCursor(0, 0);
          canvastitle.setTextSize(1);
          canvastitle.print(self->onboards[selecta]);

          canvastitle.setCursor(42, 0);
          if (pot_assignements[sublevels[2]] <= 128) {
            canvastitle.print("CC ");
            canvastitle.print(pot_assignements[sublevels[2]]);
          } else {
            canvastitle.print("Note ");
            canvastitle.print(pot_assignements[sublevels[2]] - 128);
            canvastitle.setCursor(90, 0);
            canvastitle.print("V ");
            canvastitle.print(but_velocity[sublevels[2]]);
          }
        }

        static void OnBoardVpanel() {

          OnBoardVpanelAction();
          display.clearDisplay();
          dm.clear_buffs();

          // channel label
          canvasBIG.setCursor(8, 14);
          canvasBIG.print("Ch");

          // frame
          canvasBIG.drawRoundRect(2, 9, 124, 55, 2, SSD1306_WHITE);

          // pads
          for (int i = 0; i < 16; i++) {
            canvasBIG.fillRect((i % 4) * 13 + 72, ((i / 4) % 4) * 13 + 12, 10, 10,
                              SSD1306_WHITE);
          }

          // switches
          for (int i = 0; i < 18; i++) {
            canvasBIG.drawRoundRect((i % 9) * 7 + 7, (i / 9) * 7 + 35, 5, 5, 4,
                                    SSD1306_WHITE);
          }
          // faders
          canvasBIG.drawRoundRect(48, 12, 4, 19, 2, SSD1306_WHITE);
          canvasBIG.drawRoundRect(56, 12, 4, 19, 2, SSD1306_WHITE);
          canvasBIG.drawRoundRect(64, 12, 4, 19, 2, SSD1306_WHITE);

          // pots
          for (int i = 0; i < 9; i++) {
            canvasBIG.drawRoundRect((i % 3) * 7 + 24, (i / 3) * 7 + 12, 5, 5, 4,
                                    SSD1306_WHITE);
          }
          // joystick
          canvasBIG.drawCircle(59, 55, 5, SSD1306_WHITE);

          // crossfader
          canvasBIG.drawRoundRect(18, 53, 30, 4, 2, SSD1306_WHITE);

          OnBoardVpanelSelector();
          dodisplay();
        }

        static void setbpms() {
          //clocker.setDivision(4);
          //  BPMs = (60000.0/millitickinterval)/4.0 ;
          BPMs = 15000 / millitickinterval;
          clocker.setBPM(BPMs);
        }
        
        static void stopallnotes() {
          for (int i = 0; i < synth_liners_count; i++) {
            // stoplengthmesure(i);
            if (synth_lines[i]->note != 0) {
              MaNoteOff(synthmidichannel, synth_lines[i]->note, 0);
            }
          }
        }

        static void arpegiatorVpanelAction() {
          if (navlevel == 3) {
            // AudioNoInterrupts();
            byte slct = (byte)sublevels[2];
            // fq

            if (slct == 0) {
              navrange = arpeges_types;
              arpegiatortype = sublevels[3];
              // arpegiatortype = sublevels[2];
              if (arpegiatortype < arpeges_types) {
                arpegiatorOn = 1;
                //metro0.reset();
              } else {
                arpegiatorOn = 0;
                for (int i = 0; i < synth_liners_count; i++) {
                  calledarpegenote[i][0] = 0;
                  calledarpegenote[i][1] = 0;
                  for (int j = 0; j < synth_liners_count; j++) {
                    playingarpegiator[i][j] = 0;
                    arpegnoteoffin[i][j] = 0;
                  }
                  arpegiatingNote[i] = 0;
                }
                stopallnotes();
              }
            }
            // damp
            if (slct == 1) {
              navrange = 7;
              arpegmode = sublevels[3];
            }
            if (slct == 2) {
              navrange = 3 * 6;
              arpegstartoffset = sublevels[3];
            }
            if (slct == 3) {
              navrange = 6;
              arpegnumofnotes = 1 + sublevels[3];
            }
            if (slct == 4) {
              navrange = 8;
              arpeggridC = sublevels[3];
            }
            if (slct == 5) {
              navrange = 8;
              arpeggridS = sublevels[3];
            }
            if (slct == 6) {
              navrange = 8;
              arpeglengh = sublevels[3];
            }
          }
          if (navlevel > 3) {

            vraipos = sublevels[2];
            myEnc.write(vraipos * 4);
            navlevel = 2;
          }
        }

        static void arpegiatorVpanelSelector() {
          byte startlex = 4;

          byte ecartl = 19;

          int totbartall = 32;
          int topwbarstart = 16;
          int wbarwidth2 = 7;

          int slct = sublevels[2];
          canvasBIG.drawLine(
              startlex - 2 + slct * ecartl, topwbarstart + totbartall + 2,
              startlex - 2 + slct * ecartl,
              topwbarstart + totbartall + 1 + wbarwidth2 + 3 - 1, SSD1306_WHITE);
          canvasBIG.drawLine(startlex - 2 + 1 + slct * ecartl,
                            topwbarstart + totbartall + wbarwidth2 + 4,
                            wbarwidth2 + 3 + startlex - 4 + slct * ecartl,
                            topwbarstart + totbartall + wbarwidth2 + 4, SSD1306_WHITE);

          if (slct == 0) {

            sublevels[3] = arpegiatortype;
          }
          // damp
          if (slct == 1) {

            sublevels[3] = arpegmode;
          }
          if (slct == 2) {

            sublevels[3] = arpegstartoffset;
          }
          if (slct == 3) {

            sublevels[3] = arpegnumofnotes - 1;
          }
          if (slct == 4) {

            sublevels[3] = arpeggridC;
          }
          if (slct == 5) {

            sublevels[3] = arpeggridS;
          }
          if (slct == 6) {

            sublevels[3] = arpeglengh;
          }
        }

        static void arpegiatorVpanel() {

          arpegiatorVpanelAction();
          if (navlevel == 2) {
            navrange = 6;
          }

          byte startlex = 4;

          byte ecartl = 19;

          byte totbartall = 32;
          byte topwbarstart = 16;
          byte slct = sublevels[2];
          byte wbarwidth2 = 7;
          char lesarpegestype[arpeges_types][12] = {"Ionian",     "Dorian",  "Phrygian", "Lydian",
                                        "Mixolydian", "Aeolian", "Harmonic", "Locrian"};
              dm.clean_title_1();
          canvastitle.print("Arpegiator ");
          if (arpegiatortype < arpeges_types) {
            canvastitle.print((char *)lesarpegestype[arpegiatortype]);
          } else {
            canvastitle.print("disabled");
          }
          float letype = arpegiatortype / 8.0;
          float legridC = arpeggridC / 8.0;
          float legridS = arpeggridS / 8.0;
          float lelengh = arpeglengh / 8.0;
          float lemode = arpegmode / 7.0;
          float lenumofnotes = arpegnumofnotes / 7.0;
          float leoffset = arpegstartoffset / (3 * 6.0);
          byte arpegiovalues[7] = {arpegiatortype,  arpegmode,  arpegstartoffset,
                                  arpegnumofnotes, arpeggridC, arpeggridS,
                                  arpeglengh};
          float lesarparams[7] = {letype,  lemode,  leoffset, lenumofnotes,
                                  legridC, legridS, lelengh};
          char lesbarlabels[7][12] = {"Type",      "Mode",        "Offset",
                                      "Arp. size", "Notes Block", "Empty space",
                                      "Length"};

          char lesarpegesmodes[8][12] = {"Up forward", "Down back",  "Up down f.",
                                        "Down up f.", "Mozart",     "Down up b.",
                                        "Up down b.", "Mandalorian"};
          canvasBIG.setCursor(0, 8);
          canvasBIG.print((char *)lesbarlabels[slct]);
          canvasBIG.print(" = ");
          if (slct == 1) {
            canvasBIG.print((char *)lesarpegesmodes[arpegmode]);
          } else {
            canvasBIG.print(arpegiovalues[slct]);
          }
          // type
          // lengh of notes ( function of grid )
          // mode up
          // noùmbre de notes a jouer par gamme
          // offsetin gamme to start
          // Ng grid  consecutive on
          // Ns grid spaces
          for (int i = 0; i < 7; i++) {
            canvasBIG.drawRoundRect(startlex + i * ecartl, topwbarstart, wbarwidth2,
                                    totbartall, 2, SSD1306_WHITE);
            canvasBIG.fillRect(
                startlex + i * ecartl,
                topwbarstart + 2 +
                    ((totbartall - 7) - (lesarparams[i] * (totbartall - 7))),
                wbarwidth2, 3, SSD1306_WHITE);
            canvasBIG.setCursor(startlex + 1 + i * ecartl,
                                topwbarstart + totbartall + 2);
            canvasBIG.print(lesbarlabels[i][0]);
          }

          arpegiatorVpanelSelector();
          dodisplay();
        }

        static void dotapaverage() {
          int tottaptime = 0;
          for (int i = 0; i < numberoftaps; i++) {
            tottaptime += (tapstime[i] - starttaptime);
          }
          tapaverage = tottaptime / numberoftaps;
          millitickinterval = round(tapaverage / 10.0);
          setbpms();
        }

        static void inittapstime() {
          for (int i = 0; i < 5; i++) {
            tapstime[i] = 0;
          }
        }

        static void starttaptap() {
          tapstarted = 1;
          starttaptime = millis();
        }

        static void resettaptap() {

          tapstarted = 0;
          numberoftaps = 0;
          inittapstime();
        }

        static void taptap() {
          if (!tapstarted) {
            starttaptap();
          } else {
            tapstime[numberoftaps] = millis();
            numberoftaps++;
          }

          if (millis() - starttaptime > 2000 || numberoftaps >= 4) {
            dotapaverage();
            resettaptap();
          }
        }

        static void makesettingslist() {
          char audio_source_lbl[3][5]= {"Mic","Line","Off"};
          char chordslabels[7][12] = {"Major", "Minor", "Diminished", "Augmented",
                                      "Sus2",  "Sus4",  "None"};
          char midichlist[17][4] = {"All", "1",  "2",  "3",  "4",  "5",  "6",  "7", "8",
                                    "9",   "10", "11", "12", "13", "14", "15", "16"};
          char displaysettingslabels[settings_labels_count][18] = {"Echo Midi",
                                                                "Freeze midi CC",
                                                                "Synth midi ch",
                                                                "Sampler midi ch",
                                                                "Analog touch",
                                                                "Set Tap note",
                                                                "Tempo",
                                                                "Chorus",
                                                                "Arpegiator",
                                                                "Ext. Midiclock",
                                                                "Note Spy",
                                                                "OnBoard Knobs",
                                                                "Audio Source",
                                                                "Midi Out",
                                                                "Virtual Knobs",
                                                                "Knobs Setter"};
          display.clearDisplay();
          canvasBIG.fillScreen(SSD1306_BLACK);
          int startx = 0;
          int starty = 16;
          char *textin = (char *)displaysettingslabels[sublevels[1]];

          canvastitle.fillScreen(SSD1306_BLACK);
          canvastitle.setCursor(0, 0);

          canvastitle.setTextSize(1);

          canvastitle.println(textin);

          if (sublevels[1] == 1) {
            canvastitle.setCursor(96, 0);
            if (freezemidicc) {
              canvastitle.println("On");
            } else {
              canvastitle.println("Off");
            }
          }

          if (sublevels[1] == 2) {
            canvastitle.setCursor(96, 0);
            canvastitle.println(midichlist[synthmidichannel]);
            sublevels[2] = (int)synthmidichannel;
          }
          if (sublevels[1] == 3) {
            canvastitle.setCursor(96, 0);
            canvastitle.println(midichlist[samplermidichannel]);
            sublevels[2] = int(samplermidichannel);
          }
          if (sublevels[1] == 4) {
            canvastitle.setCursor(96, 0);
            if (digitalplay) {
              canvastitle.println("On");
            } else {
              canvastitle.println("Off");
            }
          }
          if (sublevels[1] == 5) {
            canvastitle.setCursor(96, 0);
            canvastitle.println(int(tapnote));
            sublevels[2] = int(tapnote);
          }
          if (sublevels[1] == 6) {
            canvastitle.setCursor(96, 0);
            //canvastitle.println(BPMs, 1);
            canvastitle.println(15000 / millitickinterval, 1);
            if (navlevel <= 2) {
              sublevels[2] = millitickinterval;
            }
          }
          if (sublevels[1] == 7) {
            sublevels[2] = lasetchord;
            canvasBIG.setTextSize(1);
            canvasBIG.setCursor(66, 0);
            canvasBIG.println(chordslabels[lasetchord]);
          }
          if (sublevels[1] == 8) {
            canvasBIG.setCursor(96, 0);
            if (arpegiatortype != 8) {
              canvasBIG.print("On");
            } else {
              canvasBIG.print("Off");
            }
          }
          if (sublevels[1] == 9) {
            canvastitle.setCursor(96, 0);
            if (externalticker) {
              canvastitle.println("On");
            } else {
              canvastitle.println("Off");
            }
            canvasBIG.setTextSize(1);
          }

          if (sublevels[1] == 12) {
            canvastitle.setCursor(96, 0);

            canvastitle.println(audio_source_lbl[self->AudioInSource]);

            // canvasBIG.setTextSize(1);
          }

          if (sublevels[1] == 13) {
            canvastitle.setCursor(96, 0);
            if (SendMidiOut) {
              canvastitle.println("On");
            } else {
              canvastitle.println("Off");
            }
            // canvasBIG.setTextSize(1);
          }

          for (int filer = 0; filer < settings_labels_count - 1 - (sublevels[1]);
              filer++) {

            canvasBIG.setCursor(startx, starty + ((filer)*10));
            canvasBIG.println(displaysettingslabels[sublevels[1] + 1 + filer]);
          }
          for (int filer = 0; filer < sublevels[1]; filer++) {

            canvasBIG.setCursor(
                startx, (10 * (settings_labels_count - sublevels[1]) + 6 + ((filer)*10)));
            canvasBIG.println(displaysettingslabels[filer]);
          }
        }

        static void settings_nav_one(){
          
          canvasBIG.setTextSize(1);
          canvastitle.setTextSize(1);
          _settings_menu[sublevels[1]]();
          if (sublevels[1] != 8 && sublevels[1] != 15 && sublevels[1] != 14 && sublevels[1] != 11 ) {
            makesettingslist();
            dodisplay();
          }
          
        }

        byte getnotefromfreq(float lafreq) {
          for (int i = 0; i < 9 * 12; i++) {
            if (lafreq == freqtonotes[i]) {
              return i;
            }
            if (lafreq < freqtonotes[i]) {

              return getclosestnote(i, lafreq);
            }
          }
          return 0 ;
        }

        byte getclosestnote(byte lei, float lafreq) {
          if (lei > 0) {
            if (abs(lafreq - freqtonotes[lei]) <= abs(lafreq - freqtonotes[lei - 1])) {
              return lei;
            } else {
              return lei - 1;
            }
          } else {
            return lei;
          }
        }

        static void printlanote() {
          if (notefreq1.available()) {
            float notep = notefreq1.read();
            float probz = notefreq1.probability();
            byte lanotenumber;
            display.clearDisplay();
            canvastitle.fillScreen(SSD1306_BLACK);
            canvasBIG.fillScreen(SSD1306_BLACK);
            canvastitle.setCursor(0, 0);
            canvastitle.setTextSize(2);
            canvastitle.print("Fq:");
            canvastitle.print(notep, 1);
            lanotenumber = self->getnotefromfreq(notep);
            canvastitle.setTextSize(1);
            canvastitle.print(" Hz");
            canvasBIG.setTextSize(2);
            canvasBIG.setCursor(0, 16);

            canvasBIG.print((char *)self->usnotes[(lanotenumber % 12)]);
            canvasBIG.print(int(lanotenumber / 12.0));
            canvasBIG.print(" (");
            canvasBIG.print((char *)self->eunotes[(lanotenumber % 12)]);
            canvasBIG.print(int(lanotenumber / 12.0));
            canvasBIG.print(")");
            canvasBIG.setTextSize(1);
            canvasBIG.setCursor(0, 16 + 16);
            canvasBIG.print(probz * 100.0);
            canvasBIG.print("% ");

            dodisplay();
          }
        }

      //TODO: unused, maybe fit into a menu somewhere
      static void metronomer() {
        if ((tickposition == 0) || (tickposition == 16)) {
          metrodrum1.frequency(540);
          metrodrum1.noteOn();
          // printpattern();
        }
        if ((tickposition == 4) || (tickposition == 8) || (tickposition == 12) ||
            (tickposition == 20) || (tickposition == 24) || (tickposition == 28)) {

          // printpattern();
          metrodrum1.frequency(440);
          metrodrum1.noteOn();
        }
      }

      static void toggle_echo_midi(){
        toggle_that(debugmidion);
      }

      static void toggle_freeze_midi(){
        toggle_that(freezemidicc);
        returntonav(1,13,1);
      }

      static void set_synth_midi_ch(){
        navrange = 16;
        synthmidichannel = (byte)sublevels[2];
        if (navlevel >= 3) {
          returntonav(1,13,2);
        }
      }

      static void set_sampler_midi_ch(){
        navrange = 16;
        samplermidichannel = sublevels[2];
        if (navlevel >= 3) {
          returntonav(1,13,3);
        }
      }
      
      static void toggle_digital_analog(){
        toggle_that(digitalplay);
        returntonav(1,13,4);
      }
      
      
      static void set_tap_note(){
        navrange = 127;
        tapnote = byte(sublevels[2]);
        if (navlevel >= 3 ){
          returntonav(1,13,5);
        }
      }

      static void set_bpms_interval(){
        navrange = 620;
        millitickinterval = sublevels[2];
        //setbpms();
        if (navlevel >= 3) {
          millitickinterval = sublevels[2];
          self->setbpms();
          //tempo = millitickinterval;
          returntonav(1,13,6);
        }
      }

      static void set_chord_mode(){
        navrange = 6;
        lasetchord = sublevels[2];
        if (lasetchord < 6) {
          chordson = 1;
        } else {
          chordson = 0;
        }
        if (navlevel >= 3) {
          returntonav(1,13,7);
        }
      }

      static void toggle_ext_clock(){
        //externalticker = !externalticker;
        toggle_that(externalticker);
        returntonav(1,13,9);
      }

      static void toggle_note_spy(){
        toggle_that(noteprint);
        if (noteprint) {
          replug_notefreq_from_ampL();
          notefreq1.begin(.15);
        } else {
          unplug_notefreq_from_ampL();
        }
        if (navlevel >= 3) {
          returntonav(1,13,10);
        }
      }

      static void set_audio_source(){
        navrange = 2 ;
        self->AudioInSource = sublevels[2] ;
        if (navlevel >= 3) {
          set_in_source();
          returntonav(1,13,12);
        }
      }

      static void toggle_midi_out(){
        toggle_that(SendMidiOut);
        returntonav(1,13,13);
      }
     
      static constexpr void (*_settings_menu[settings_labels_count])() = {&toggle_echo_midi,&toggle_freeze_midi,&set_synth_midi_ch,&set_sampler_midi_ch,&toggle_digital_analog,
                                                                        &set_tap_note,&set_bpms_interval,&set_chord_mode,&arpegiatorVpanel,&toggle_ext_clock,&toggle_note_spy,
                                                                        &OnBoardVpanel,&set_audio_source,&toggle_midi_out,&Vbuttonspanel,&_ka.show};

      //static constexpr void (*_nav_fx[sampler_labels_count])() = {&fx_nav_one, &fx_nav_one, &fx_nav_one, &fx_nav_one, &fx_nav_one};

  private:
    static SettingsMenuRouter* self;
};

SettingsMenuRouter* SettingsMenuRouter::self = nullptr;
EXTMEM SettingsMenuRouter _st;