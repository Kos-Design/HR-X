
class LFOMenuRouter : public SectionHolder {
    public:
        LFOMenuRouter() {
                    self = this;
                    self->home_navrange=2;
                    self->relative_navlevel=1;
                    self->max_navlevel=5;
                    self->sublevels_address={1,0,0};
                    }

        int unit = (int)gg.LFOHz[lv.cclfoselector] % 10;
        int tenth     = ((int)(gg.LFOHz[lv.cclfoselector] * 10)) % 10;
        int hundredth = ((int)(gg.LFOHz[lv.cclfoselector] * 100)) % 10;
        const byte sizeofLFOlabels = 9;

        static void show() {
          _nav_lfo[lv.navlevel-1]();
        }

        static void applyLFOrmicon(int lesinthy) {
          // displaywaveformicon(lv.sublevels[4],(char*)"SineWave",sinewave, lesynthi,
          // WAVEFORM_SINE);
          if (lv.navlevel > 3) {
            gg.LFOformstype[lesinthy] = lv.sublevels[3];

            if (lv.navlevel >= 4) {
              dm.returntonav(2, 9);
            }
          }
        }

        static void LFOrmType() {
          int leLFO=lv.cclfoselector;
          if (lv.navlevel == 2){
            lv.sublevels[3] = gg.LFOformstype[leLFO];
          }
          if (lv.navlevel == 3) {
            lv.navrange = 8;
          }

          switch (lv.sublevels[3]) {
          case 0:
            displayLFOrmimg(lv.sublevels[3], (char *)"SineWave", sinewave, leLFO,
                            WAVEFORM_SINE);
            break;
          case 1:
            displayLFOrmimg(lv.sublevels[3], (char *)"SawWave", sawtoothwave, leLFO,
                            WAVEFORM_SAWTOOTH);
            break;
          case 2:
            displayLFOrmimg(lv.sublevels[3], (char *)"ReverseSaw", reversesawtoothwave,
                            leLFO, WAVEFORM_SAWTOOTH_REVERSE);
            break;
          case 3:
            displayLFOrmimg(lv.sublevels[3], (char *)"Triangle", trianglewave, leLFO,
                            WAVEFORM_TRIANGLE);
            break;
          case 4:
            displayLFOrmimg(lv.sublevels[3], (char *)"V-Triangle", variabletriangle, leLFO,
                            WAVEFORM_TRIANGLE_VARIABLE);
            break;
          case 5:
            displayLFOrmimg(lv.sublevels[3], (char *)"SquareWave", squarewave, leLFO,
                            WAVEFORM_SQUARE);
            break;
          case 6:
            displayLFOrmimg(lv.sublevels[3], (char *)"PulseWave", pulsewave, leLFO,
                            WAVEFORM_PULSE);
            break;
          case 7:
            displayLFOrmimg(lv.sublevels[3], (char *)"Arbitrary", arbitrarywave, leLFO,
                            WAVEFORM_ARBITRARY);
            break;
          case 8:
            displayLFOrmimg(lv.sublevels[3], (char *)"SampleHold", samplehold, leLFO,
                            WAVEFORM_SAMPLE_HOLD);
            break;

          default:
            break;
          }
          if (lv.navlevel >= 4) {
            gg.LFOformstype[leLFO] = lv.sublevels[3];
            call_restart_lfo(leLFO);
            gobacktolfoparams();
          }
        }

        static void displayLFOrmimg(int letype, char *lelabelw, const unsigned char img[],int leLFO, typeof(WAVEFORM_SINE) wavetype) {

          canvasBIG.drawBitmap(70, 20, img, 32, 32, SSD1306_WHITE);
          canvastitle.setTextSize(1); // Draw 1X-scale text
          canvastitle.setTextColor(SSD1306_WHITE);
          canvastitle.setCursor(64, 8);
          canvastitle.println(lelabelw);
          // dm.dodisplay();
        }

        static void doLFObool() {
          int leLFO=lv.cclfoselector;
          if (lv.navlevel == 3) {
            gg.LFOsync[leLFO] = !gg.LFOsync[leLFO] ;
            restartLFO(leLFO);
          }
          display.setCursor(55, 0);
          display.setTextSize(2);
          if (gg.LFOsync[leLFO]) {
            display.print("Active");
          } else {
            display.print("Off");
          }
          display.display();
          if (lv.navlevel >= 4) {
            dm.returntonav(2, 2);
          }
        }

        static void gobacktolfoparams() { dm.returntonav(2); }

        static void doLFOparamdisplayval(int laval) {
          
        }

        static void draw_lfo_val(float laval) {
          canvastitle.setCursor(80, 0);
          canvastitle.setTextSize(2);
          canvastitle.print(laval);
        }

        static void doLFOlevel() {
          int leLFO=lv.cclfoselector;
          if (lv.navlevel == 3) {
            lv.navrange = 127;
            gg.LFOlevel[leLFO] = lv.sublevels[3];
          } else {
            lv.sublevels[3] = gg.LFOlevel[leLFO];
          }
          if (lv.navlevel >= 4) {
            gobacktolfoparams();
          }
          draw_lfo_val(gg.LFOlevel[leLFO] / 127.0);
        }

        static void doLFOoffset() {
          int leLFO=lv.cclfoselector;
          if (lv.navlevel == 3) {
            lv.navrange = 127;
            gg.LFOoffset[leLFO] = lv.sublevels[3];
            doLFOallcontrols(leLFO);
          } else {
            lv.sublevels[3] = gg.LFOoffset[leLFO];
          }
          if (lv.navlevel >= 4) {
            gobacktolfoparams();
          }
          draw_lfo_val((64.0 - gg.LFOoffset[leLFO]) / 64.0);
        }

        static void doLFOphase() {
          int leLFO=lv.cclfoselector;
          if (lv.navlevel == 3) {
            lv.navrange = 127;
            gg.LFOphase[leLFO] = lv.sublevels[3];
            doLFOallcontrols(leLFO);
            // restartLFO(leLFO);
          } else {
            lv.sublevels[3] = gg.LFOphase[leLFO];
          }
          if (lv.navlevel >= 4) {
            gobacktolfoparams();
          }
          canvastitle.setCursor(80, 0);
          canvastitle.setTextSize(2);
          canvastitle.print((gg.LFOphase[leLFO]/127.0)*360);
        }

        static void freqbars_panel_selector() {
          if (lv.navlevel == 3) {
            lv.retroaction = lv.sublevels[2];
            switch (lv.sublevels[3]){
              case 0:
                display.fillRect(62, 0, 16, 16, SSD1306_INVERSE);
                self->unit = (int)gg.LFOHz[lv.cclfoselector];
                lv.sublevels[4]=self->unit;
              break;
              case 1:
                display.fillRect(88, 0, 12, 16, SSD1306_INVERSE);
                self->tenth = ((int)(gg.LFOHz[lv.cclfoselector]* 10)) % 10;
                lv.sublevels[4]=self->tenth;
              break;
              case 2:
                display.fillRect(100, 0, 12, 16, SSD1306_INVERSE);
                self->hundredth = ((int)(gg.LFOHz[lv.cclfoselector] * 100)) % 10;
                lv.sublevels[4]=self->hundredth;
              break;
            }
          display.display();
          }
        }
        static void freqbars_panel_action() {

          lv.navrange = 9;
          switch (lv.sublevels[3]){
            case 0:
              self->unit = lv.sublevels[4];
            break;
            case 1:
              self->tenth = lv.sublevels[4];
              //Serial.println(self->hundredth);
            break;
            case 2:
              self->hundredth = lv.sublevels[4];
              //Serial.println(self->hundredth);
            break;
          }

          gg.LFOHz[lv.cclfoselector] = (float)(self->unit + self->tenth * 0.1f + self->hundredth * 0.01f);
        }

        static void displayfreqbars(){
          //dm.clear_3();
          display.setTextSize(2);
          display.setCursor(65, 0);
          display.println(gg.LFOHz[lv.cclfoselector]);
          //dolistLFOparams();
          //dm.dodisplay();
        }

        static void freqbars_panel() {
          if (lv.navlevel >= 3) {
            lv.retroaction = lv.sublevels[2];
            if (lv.navlevel == 3) {
              lv.navrange = 2;

            }
            if (lv.navlevel == 4) {
              lv.retroaction = lv.sublevels[3];
              freqbars_panel_action();
            }
            if (lv.navlevel >= 5) {
              dm.returntonav(3,9,lv.sublevels[3]);
            }
            //dm.dodisplay();
          }
          displayfreqbars();
          freqbars_panel_selector();
          if (lv.navlevel == 2) {
            lv.retroaction = lv.sublevels[1];
            lv.navrange = self->sizeofLFOlabels - 1;
          }
        }



        static void dolistLFOparams() {
          const char* LFOlabels[] = {"Type",  "Level",  "Sync",
                                                "Freq",  "Offset", "Phase",
                                                "Synth", "<-  ",   "  ->"};
          dm.main_panel(LFOlabels, 2, self->sizeofLFOlabels);

        }

        static void doLFOallcontrols(byte leLFO) {
          restartLFO(leLFO);
          LFOwaveforms1[leLFO]->phase((gg.LFOphase[leLFO]/127.0)*360);
          LFOwaveforms1[leLFO]->offset((float)(((64 - gg.LFOoffset[leLFO]) / 64.0)));
        }
        static void go_to_synth(){
          if (lv.navlevel >= 3) {
            lv.sublevels[0] = 0;
            lv.sublevels[2] = lv.sublevels[1];
            lv.sublevels[1] = 0;
            //wavelinepanel(lv.sublevels[2]);
            dm.returntonav(lv.navlevel+2);
          }
        }
       
        static void go_previous(){
          if (lv.navlevel >= 3) {
            if (lv.cclfoselector-1 < 0)
              lv.cclfoselector = 2 ;
            else
              lv.cclfoselector = lv.cclfoselector-1;
            
            lv.sublevels[1] = lv.cclfoselector ;
            dm.returntonav(lv.navlevel-1,self->sizeofLFOlabels-1,lv.sublevels[2]);
            }
        }
        static void go_next(){
          if (lv.navlevel >= 3) {
            lv.cclfoselector = (lv.cclfoselector+1)%3;
            lv.sublevels[1] = lv.cclfoselector ;
            dm.returntonav(lv.navlevel-1,self->sizeofLFOlabels-1,lv.sublevels[2]);
            }
        }
        static void restartLFO(int leLFO=lv.cclfoselector) {
          AudioNoInterrupts();
          if (gg.LFOsync[leLFO]) {
            float syncher = 1.0 ;
            if (gg.millitickinterval) {
              syncher = (1000.00/(gg.millitickinterval+1));
            }

            LFOwaveforms1[leLFO]->begin((float)(gg.LFOlevel[leLFO]/127.00), gg.LFOHz[leLFO]*syncher, lesformes[gg.LFOformstype[leLFO]]);
          } else {
            LFOwaveforms1[leLFO]->begin((float)(gg.LFOlevel[leLFO]/127.00), gg.LFOHz[leLFO]*2, lesformes[gg.LFOformstype[leLFO]]);
          }
          if (gg.LFOformstype[leLFO] == 7) {
            LFOwaveforms1[leLFO]->arbitraryWaveform(gg.arbitrary_waveforms[leLFO],gg.arbitrary_maxF[leLFO]);
          }

          for (byte i = 0; i < SYNTH_LINERS_COUNT; i++) {
            if (gg.FMmodulated[leLFO] == 1) {
              //phaseModulation should be based on lfo level
              FMwaveforms1[i + (leLFO * SYNTH_LINERS_COUNT)]->frequencyModulation((gg.LFOlevel[leLFO]/127.00)*10);
            }
            else if (gg.FMmodulated[leLFO] == 2) {
              FMwaveforms1[i + (leLFO * SYNTH_LINERS_COUNT)]->phaseModulation((gg.LFOlevel[leLFO]/127.00) * 360 - 180);
            }
          }

          AudioInterrupts();
        }
        static void LFOlining() {
          lv.navrange = 8;
          dm.clean_title_2_1();
          dolistLFOparams();
          _route_nav[lv.sublevels[2]]();
          canvasBIG.setCursor(122, 58);
          canvasBIG.print(lv.cclfoselector + 1);
          dm.dodisplay();
        }

        static void printLFObanner(int startx, int starty, int leLFO=lv.cclfoselector) {
            display.fillRect(startx, starty, 64, 24, SSD1306_INVERSE);
            dm.printlabel((char*)"LFO ");
            display.setCursor(116, 0);
            display.print(leLFO);
            display.display();
        }

        static void LFOlineBG() {
            display.clearDisplay();
            display.drawBitmap(0, 64 - 47, wavesbg2, 128, 47, SSD1306_WHITE);

            display.display();
        }

        static void lfo_zero(){
            lv.navrange = OSCS_COUNT-1;
            //TODO:remove maybe
            reinitsublevels(2);

            LFOlineBG();

            switch (lv.sublevels[1]) {
            case 0:
            printLFObanner(0, 16, 1);
            break;

            case 1:
            printLFObanner(64, 16, 2);
            break;

            case 2:
            printLFObanner(0, 40, 3);
            break;

            case 3:
            printLFObanner(64, 40, 4);
            break;

            default:
            break;
            }
        }
       
    private:

        static constexpr void (*_route_nav[9])() = {
            &LFOrmType,
            &doLFOlevel,
            &doLFObool,
            &freqbars_panel,
            &doLFOoffset,
            &doLFOphase,
            &go_to_synth,
            &go_previous,
            &go_next
        };
        static constexpr void (*_nav_lfo[7])() = {&lfo_zero, &LFOlining,&LFOlining,&LFOlining,
                          &LFOlining,&LFOlining,&LFOlining};
        static LFOMenuRouter* self;
};

LFOMenuRouter* LFOMenuRouter::self = nullptr;
LFOMenuRouter _lf;