

class SettingsMenuRouter : public SectionHolder {
    public:
        SettingsMenuRouter() {
                    self = this;
                    self->home_navrange=settings_labels_count - 1;
                    self->relative_navlevel=2;
                    self->max_navlevel=5;
                    self->sublevels_address={5,0,0};
                    }
                    
        static constexpr uint8_t settings_labels_count = 17;
        bool noteprint = 0;

        char onboards[ALL_BUTTONS][8] = {
          "Pot 1",  "Pot 2",  "Pot 3",  "Pot 4",  "Pot 5",  "Pot 6",  "Pot 7",
          "Pot 8",  "Pot 9",  "Fdr 01", "Fdr 02", "Fdr 03", "Pad 01", "Pad 02",
          "Pad 03", "Pad 04", "Pad 05", "Pad 06", "Pad 07", "Pad 08", "Pad 09",
          "Pad 10", "Pad 11", "Pad 12", "Pad 13", "Pad 14", "Pad 15", "Pad 16",
          "But 01", "But 02", "But 03", "But 04", "But 05", "But 06", "But 07",
          "But 08", "But 09", "But 10", "But 11", "But 12", "But 13", "But 14",
          "But 15", "But 16", "But 17", "But 18", "Cfd",    "Jk X",   "Jk Y"};

        char ch_lbl_buffer[4];


        static void show() {
          if (lv.navlevel == 1) {
            lv.setting_on_board = false ;
            settings_nav_zero();
          }

          // arpegiator has its own panel -> 8 , same for 11 which is OnboardPanel
          if (lv.navlevel >= 2) {
            settings_nav_one();
          }
        }

        static void apply_alt_ctl(){
          //TODO implement learn midi
          for (int i = 0; i < 4; i++) {
            _ka.set_midi_cc_to_ctl(_ka.find_assigned_knob(gg.alt_nav[i]),0);
            //hope that ctl index of rota_increase_ctl doesn't change
            _ka.set_midi_cc_to_ctl(gg.alt_nav[i],123+i);
          }
        }
        static void set_alternative_rota(){

          lv.navrange = 3 ;
          if (lv.navlevel == 3 ){
            lv.navrange = 127;
            gg.alt_nav[lv.sublevels[2]]=lv.sublevels[3];
          }
          
          lv.sublevels[3]=gg.alt_nav[lv.sublevels[2]];
          display.clearDisplay();
          display.setCursor(0,0);
          display.setTextSize(1);
         
          display.print("Set Nav Controls");
          display.println(" ");
          display.println(" ");
          display.print("Increase: ");
          display.print(gg.alt_nav[0]);

          display.setCursor(0, 28);
          display.print("Decrease: ");
          display.print(gg.alt_nav[1]);

          display.setCursor(0, 40);
          display.print("Validate: ");
          display.print(gg.alt_nav[2]);

          display.setCursor(0, 52);
          display.print("Cancel:   ");
          display.print(gg.alt_nav[3]);

          display.drawRoundRect(56,11+12*lv.sublevels[2], 25, 16, 3, SSD1306_WHITE);
          display.display();
          
          if (lv.navlevel > 3 ){
            apply_alt_ctl();
            dm.returntonav(2,3,lv.sublevels[2]);
          }
        }

        /*
        //TODO: implement in notespy
        void notefreqloop() {
          if (notefreq1.available()) {
            float notep = notefreq1.read();
            float probz = notefreq1.probability();
            //  dm.pseudoconsole("Note: %3.2f | Probability: %.2f\n", notep, probz);
          }
        }
        */

        static void set_in_source(){
          switch (self->AudioInSource) {
            case 0 :
              AudioShield.inputSelect(AUDIO_INPUT_MIC);
              InMixL.gain(1, 0.01);
              InMixR.gain(1, 0.01);
              break;
            case 1 :
              AudioShield.inputSelect(AUDIO_INPUT_LINEIN);
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
          dm.reinitsublevels(2);
          dm.clean_title_1_1();
          _tt.debugmidion = 0;
          self->noteprint = 0;
          lv.navrange = settings_labels_count - 1;
          makesettingslist();
          dm.dodisplay();
        }

        static void OnBoardVpanelAction() {
          if (lv.navlevel > 3) {
            if (((lv.sublevels[2] <= 11) || (lv.sublevels[2] > 45)) && (lv.navlevel == 4)) {
              gg.ordered_pots[Pads.potsboards[lv.sublevels[2]]] = gg.pot_assignements[lv.sublevels[2]];
            }
            dm.returntonav(2);
          }
        }

        static void OnBoardVpanelSelector() {

          int selecta = lv.sublevels[2];
          if (lv.navlevel == 2) {
            lv.navrange = ALL_BUTTONS - 1;
            lv.sublevels[3] = gg.pot_assignements[lv.sublevels[2]];
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
          sprintf(self->ch_lbl_buffer, "%02d", gg.but_channel[lv.sublevels[2]]);
          canvasBIG.print(self->ch_lbl_buffer);

          if (lv.navlevel == 3) {
            lv.sublevels[4] = gg.pot_assignements[lv.sublevels[2]];
            gg.pot_assignements[lv.sublevels[2]] = lv.sublevels[3];
            if (selecta <= 11) {
              lv.navrange = 127;
            }

            if ((selecta > 11) && (selecta <= 45)) {
              lv.navrange = 128 + 127;
            }
            if (selecta > 45) {
              lv.navrange = 127;
            }
          }

          canvastitle.setCursor(0, 0);
          canvastitle.setTextSize(1);
          canvastitle.print(self->onboards[selecta]);

          canvastitle.setCursor(42, 0);
          if (gg.pot_assignements[lv.sublevels[2]] <= 128) {
            canvastitle.print("CC ");
            canvastitle.print(gg.pot_assignements[lv.sublevels[2]]);
          } else {
            canvastitle.print("Note ");
            canvastitle.print(gg.pot_assignements[lv.sublevels[2]] - 128);
            canvastitle.setCursor(90, 0);
            canvastitle.print("V ");
            canvastitle.print(gg.but_velocity[lv.sublevels[2]]);
          }
        }

        static void OnBoardVpanel() {
          lv.setting_on_board = true ;
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
          dm.dodisplay();
        }

        static void setbpms() {
          //clocker.setDivision(4);
          //  lv.BPMs = (60000.0/gg.millitickinterval)/4.0 ;
          lv.BPMs = 15000 / gg.millitickinterval;
          clocker.setBPM(lv.BPMs);
        }
        
        

        static void arpegiatorVpanelAction() {
          if (lv.navlevel == 3) {
            // AudioNoInterrupts();
            byte slct = (byte)lv.sublevels[2];
            // fq

            if (slct == 0) {
              lv.navrange = ARP_TYPES;
              gg.arpegiatortype = lv.sublevels[3];
              // gg.arpegiatortype = lv.sublevels[2];
              _pt.set_arp_type();
            }
            // damp
            if (slct == 1) {
              lv.navrange = 7;
              gg.arpegmode = lv.sublevels[3];
            }
            if (slct == 2) {
              lv.navrange = 3 * 6;
              gg.arpegstartoffset = lv.sublevels[3];
            }
            if (slct == 3) {
              lv.navrange = 6;
              gg.arpegnumofnotes = 1 + lv.sublevels[3];
            }
            if (slct == 4) {
              lv.navrange = 8;
              gg.arpeggridC = lv.sublevels[3];
            }
            if (slct == 5) {
              lv.navrange = 8;
              gg.arpeggridS = lv.sublevels[3];
            }
            if (slct == 6) {
              lv.navrange = 8;
              gg.arpeglengh = lv.sublevels[3];
            }
          }
          if (lv.navlevel > 3) {

            dm.returntonav(2,6,lv.sublevels[2]);

          }
        }

        static void arpegiatorVpanelSelector() {
          byte startlex = 4;

          byte ecartl = 19;

          int totbartall = 32;
          int topwbarstart = 16;
          int wbarwidth2 = 7;

          int slct = lv.sublevels[2];
          canvasBIG.drawLine(
              startlex - 2 + slct * ecartl, topwbarstart + totbartall + 2,
              startlex - 2 + slct * ecartl,
              topwbarstart + totbartall + 1 + wbarwidth2 + 3 - 1, SSD1306_WHITE);
          canvasBIG.drawLine(startlex - 2 + 1 + slct * ecartl,
                            topwbarstart + totbartall + wbarwidth2 + 4,
                            wbarwidth2 + 3 + startlex - 4 + slct * ecartl,
                            topwbarstart + totbartall + wbarwidth2 + 4, SSD1306_WHITE);

          if (slct == 0) {

            lv.sublevels[3] = gg.arpegiatortype;
          }
          // damp
          if (slct == 1) {

            lv.sublevels[3] = gg.arpegmode;
          }
          if (slct == 2) {

            lv.sublevels[3] = gg.arpegstartoffset;
          }
          if (slct == 3) {

            lv.sublevels[3] = gg.arpegnumofnotes - 1;
          }
          if (slct == 4) {

            lv.sublevels[3] = gg.arpeggridC;
          }
          if (slct == 5) {

            lv.sublevels[3] = gg.arpeggridS;
          }
          if (slct == 6) {

            lv.sublevels[3] = gg.arpeglengh;
          }
        }

        static void arpegiatorVpanel() {

          arpegiatorVpanelAction();
          if (lv.navlevel == 2) {
            lv.navrange = 6;
          }

          byte startlex = 4;

          byte ecartl = 19;

          byte totbartall = 32;
          byte topwbarstart = 16;
          byte slct = lv.sublevels[2];
          byte wbarwidth2 = 7;
          char lesarpegestype[ARP_TYPES][12] = {"Ionian",     "Dorian",  "Phrygian", "Lydian",
                                        "Mixolydian", "Aeolian", "Harmonic", "Locrian"};
              dm.clean_title_1();
          canvastitle.print("Arpegiator ");
          if (gg.arpegiatortype < ARP_TYPES) {
            canvastitle.print((char *)lesarpegestype[gg.arpegiatortype]);
          } else {
            canvastitle.print("disabled");
          }
          float letype = gg.arpegiatortype / 8.0;
          float legridC = gg.arpeggridC / 8.0;
          float legridS = gg.arpeggridS / 8.0;
          float lelengh = gg.arpeglengh / 8.0;
          float lemode = gg.arpegmode / 7.0;
          float lenumofnotes = gg.arpegnumofnotes / 7.0;
          float leoffset = gg.arpegstartoffset / (3 * 6.0);
          byte arpegiovalues[7] = {gg.arpegiatortype,  gg.arpegmode,  gg.arpegstartoffset,
                                  gg.arpegnumofnotes, gg.arpeggridC, gg.arpeggridS,
                                  gg.arpeglengh};
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
            canvasBIG.print((char *)lesarpegesmodes[gg.arpegmode]);
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
          dm.dodisplay();
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
                                                                "Knobs Setter",
                                                                "Nav Config"};
          display.clearDisplay();
          canvasBIG.fillScreen(SSD1306_BLACK);
          int startx = 0;
          int starty = 16;
          char *textin = (char *)displaysettingslabels[lv.sublevels[1]];

          canvastitle.fillScreen(SSD1306_BLACK);
          canvastitle.setCursor(0, 0);

          canvastitle.setTextSize(1);

          canvastitle.println(textin);

          if (lv.sublevels[1] == 1) {
            canvastitle.setCursor(96, 0);
            if (lv.freezemidicc) {
              canvastitle.println("On");
            } else {
              canvastitle.println("Off");
            }
          }

          if (lv.sublevels[1] == 2) {
            canvastitle.setCursor(96, 0);
            canvastitle.println(midichlist[gg.synthmidichannel]);
            lv.sublevels[2] = (int)gg.synthmidichannel;
          }
          if (lv.sublevels[1] == 3) {
            canvastitle.setCursor(96, 0);
            canvastitle.println(midichlist[gg.samplermidichannel]);
            lv.sublevels[2] = int(gg.samplermidichannel);
          }
          if (lv.sublevels[1] == 4) {
            canvastitle.setCursor(96, 0);
            if (gg.digitalplay) {
              canvastitle.println("On");
            } else {
              canvastitle.println("Off");
            }
          }
          if (lv.sublevels[1] == 5) {
            canvastitle.setCursor(96, 0);
            canvastitle.println(int(gg.tapnote));
            lv.sublevels[2] = int(gg.tapnote);
          }
          if (lv.sublevels[1] == 6) {
            canvastitle.setCursor(96, 0);
            //canvastitle.println(lv.BPMs, 1);
            canvastitle.println(15000 / gg.millitickinterval, 1);
            if (lv.navlevel <= 2) {
              lv.sublevels[2] = gg.millitickinterval;
            }
          }
          if (lv.sublevels[1] == 7) {
            lv.sublevels[2] = gg.lasetchord;
            canvasBIG.setTextSize(1);
            canvasBIG.setCursor(66, 0);
            canvasBIG.println(chordslabels[gg.lasetchord]);
          }
          if (lv.sublevels[1] == 8) {
            canvasBIG.setCursor(96, 0);
            if (gg.arpegiatortype != 8) {
              canvasBIG.print("On");
            } else {
              canvasBIG.print("Off");
            }
          }
          if (lv.sublevels[1] == 9) {
            canvastitle.setCursor(96, 0);
            if (gg.externalticker) {
              canvastitle.println("On");
            } else {
              canvastitle.println("Off");
            }
            canvasBIG.setTextSize(1);
          }

          if (lv.sublevels[1] == 12) {
            canvastitle.setCursor(96, 0);

            canvastitle.println(audio_source_lbl[self->AudioInSource]);

            // canvasBIG.setTextSize(1);
          }

          if (lv.sublevels[1] == 13) {
            canvastitle.setCursor(96, 0);
            if (gg.SendMidiOut) {
              canvastitle.println("On");
            } else {
              canvastitle.println("Off");
            }
            // canvasBIG.setTextSize(1);
          }
          
          for (int filer = 0; filer < settings_labels_count - 1 - (lv.sublevels[1]);
              filer++) {

            canvasBIG.setCursor(startx, starty + ((filer)*10));
            canvasBIG.println(displaysettingslabels[lv.sublevels[1] + 1 + filer]);
          }
          for (int filer = 0; filer < lv.sublevels[1]; filer++) {

            canvasBIG.setCursor(
                startx, (10 * (settings_labels_count - lv.sublevels[1]) + 6 + ((filer)*10)));
            canvasBIG.println(displaysettingslabels[filer]);
          }
        }

        static void settings_nav_one(){
          
          canvasBIG.setTextSize(1);
          canvastitle.setTextSize(1);
          _settings_menu[lv.sublevels[1]]();
          if (lv.sublevels[1] != 8 && lv.sublevels[1] != 15 && lv.sublevels[1] != 14 && lv.sublevels[1] != 16 && lv.sublevels[1] != 11 ) {
            makesettingslist();
            dm.dodisplay();
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

            dm.dodisplay();
          }
        }

      //TODO: unused, maybe fit into a menu somewhere
      static void metronomer() {
        if ((lv.tickposition == 0) || (lv.tickposition == 16)) {
          metrodrum1.frequency(540);
          metrodrum1.noteOn();
          // printpattern();
        }
        if ((lv.tickposition == 4) || (lv.tickposition == 8) || (lv.tickposition == 12) ||
            (lv.tickposition == 20) || (lv.tickposition == 24) || (lv.tickposition == 28)) {

          // printpattern();
          metrodrum1.frequency(440);
          metrodrum1.noteOn();
        }
      }

      static void toggle_echo_midi(){
        _tt.debugmidion = !_tt.debugmidion;
      }

      static void toggle_freeze_midi(){
        lv.freezemidicc = !lv.freezemidicc;
        dm.returntonav(1,self->home_navrange,1);
      }

      static void set_synth_midi_ch(){
        lv.navrange = 16;
        gg.synthmidichannel = (byte)lv.sublevels[2];
        if (lv.navlevel >= 3) {
          dm.returntonav(1,self->home_navrange,2);
        }
      }

      static void set_sampler_midi_ch(){
        lv.navrange = 16;
        gg.samplermidichannel = lv.sublevels[2];
        if (lv.navlevel >= 3) {
          dm.returntonav(1,self->home_navrange,3);
        }
      }
      
      static void toggle_digital_analog(){
        gg.digitalplay = !gg.digitalplay;
        dm.returntonav(1,self->home_navrange,4);
      }
      
      
      static void set_tap_note(){
        lv.navrange = 127;
        gg.tapnote = byte(lv.sublevels[2]);
        if (lv.navlevel >= 3 ){
          dm.returntonav(1,self->home_navrange,5);
        }
      }

      static void set_bpms_interval(){
        lv.navrange = 620;
        gg.millitickinterval = lv.sublevels[2];
        //setbpms();
        if (lv.navlevel >= 3) {
          gg.millitickinterval = lv.sublevels[2];
          self->setbpms();
          //tempo = gg.millitickinterval;
          dm.returntonav(1,self->home_navrange,6);
        }
      }

      static void set_chord_mode(){
        lv.navrange = 6;
        gg.lasetchord = lv.sublevels[2];
        if (gg.lasetchord < 6) {
          gg.chordson = 1;
        } else {
          gg.chordson = 0;
        }
        if (lv.navlevel >= 3) {
          dm.returntonav(1,self->home_navrange,7);
        }
      }

      static void toggle_ext_clock(){
        //gg.externalticker = !gg.externalticker;
        gg.externalticker = !gg.externalticker;
        dm.returntonav(1,self->home_navrange,9);
      }

      static void toggle_note_spy(){
        self->noteprint = !self->noteprint;
        if (self->noteprint) {
          replug_notefreq_from_ampL();
          notefreq1.begin(.15);
        } else {
          unplug_notefreq_from_ampL();
        }
        if (lv.navlevel >= 3) {
          dm.returntonav(1,self->home_navrange,10);
        }
      }

      static void set_audio_source(){
        lv.navrange = 2 ;
        self->AudioInSource = lv.sublevels[2] ;
        if (lv.navlevel >= 3) {
          set_in_source();
          dm.returntonav(1,self->home_navrange,12);
        }
      }

      static void toggle_midi_out(){
        gg.SendMidiOut = !gg.SendMidiOut ;
        dm.returntonav(1,self->home_navrange,13);
      }
     
      static constexpr void (*_settings_menu[settings_labels_count])() = {&toggle_echo_midi,&toggle_freeze_midi,&set_synth_midi_ch,&set_sampler_midi_ch,&toggle_digital_analog,
                                                                        &set_tap_note,&set_bpms_interval,&set_chord_mode,&arpegiatorVpanel,&toggle_ext_clock,&toggle_note_spy,
                                                                        &OnBoardVpanel,&set_audio_source,&toggle_midi_out,&_vk.Vbuttonspanel,&_ka.show,&set_alternative_rota};

      //static constexpr void (*_nav_fx[SP_LABELS_COUNT])() = {&fx_nav_one, &fx_nav_one, &fx_nav_one, &fx_nav_one, &fx_nav_one};

  private:
    static SettingsMenuRouter* self;
};

SettingsMenuRouter* SettingsMenuRouter::self = nullptr;
SettingsMenuRouter _st;