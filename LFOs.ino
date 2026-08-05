
class LFOMenuRouter : public SectionHolder {
    public:
        LFOMenuRouter() {
                    self = this;
                    self->home_navrange=2;
                    self->relative_navlevel=1;
                    self->max_navlevel=5;
                    self->sublevels_address={1,0,0};
                    }

        int unit = (int)gg.LFOHz[cclfoselector] % 10;
        int tenth     = ((int)(gg.LFOHz[cclfoselector] * 10)) % 10;
        int hundredth = ((int)(gg.LFOHz[cclfoselector] * 100)) % 10;

        static void show() {
          _nav_lfo[navlevel-1]();
        }

        static void applyLFOrmicon(int lesinthy) {
          // displaywaveformicon(sublevels[4],(char*)"SineWave",sinewave, lesynthi,
          // WAVEFORM_SINE);
          if (navlevel > 3) {
            gg.LFOformstype[lesinthy] = sublevels[3];

            if (navlevel >= 4) {
              returntonav(2, 9);
            }
          }
        }

        static void LFOrmType() {
          int leLFO=cclfoselector;
          if (navlevel == 2){
            sublevels[3] = gg.LFOformstype[leLFO];
          }
          if (navlevel == 3) {
            navrange = 8;
          }

          switch (sublevels[3]) {
          case 0:
            displayLFOrmimg(sublevels[3], (char *)"SineWave", sinewave, leLFO,
                            WAVEFORM_SINE);
            break;
          case 1:
            displayLFOrmimg(sublevels[3], (char *)"SawWave", sawtoothwave, leLFO,
                            WAVEFORM_SAWTOOTH);
            break;
          case 2:
            displayLFOrmimg(sublevels[3], (char *)"ReverseSaw", reversesawtoothwave,
                            leLFO, WAVEFORM_SAWTOOTH_REVERSE);
            break;
          case 3:
            displayLFOrmimg(sublevels[3], (char *)"Triangle", trianglewave, leLFO,
                            WAVEFORM_TRIANGLE);
            break;
          case 4:
            displayLFOrmimg(sublevels[3], (char *)"V-Triangle", variabletriangle, leLFO,
                            WAVEFORM_TRIANGLE_VARIABLE);
            break;
          case 5:
            displayLFOrmimg(sublevels[3], (char *)"SquareWave", squarewave, leLFO,
                            WAVEFORM_SQUARE);
            break;
          case 6:
            displayLFOrmimg(sublevels[3], (char *)"PulseWave", pulsewave, leLFO,
                            WAVEFORM_PULSE);
            break;
          case 7:
            displayLFOrmimg(sublevels[3], (char *)"Arbitrary", arbitrarywave, leLFO,
                            WAVEFORM_ARBITRARY);
            break;
          case 8:
            displayLFOrmimg(sublevels[3], (char *)"SampleHold", samplehold, leLFO,
                            WAVEFORM_SAMPLE_HOLD);
            break;

          default:
            break;
          }
          if (navlevel >= 4) {
            gg.LFOformstype[leLFO] = sublevels[3];
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
          int leLFO=cclfoselector;
          if (navlevel == 3) {
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
          if (navlevel >= 4) {
            returntonav(2, 2);
          }
        }

        static void gobacktolfoparams() { returntonav(2); }

        static void doLFOparamdisplayval(int laval) {
          
        }

        static void draw_lfo_val(float laval) {
          canvastitle.setCursor(80, 0);
          canvastitle.setTextSize(2);
          canvastitle.print(laval);
        }

        static void doLFOlevel() {
          int leLFO=cclfoselector;
          if (navlevel == 3) {
            navrange = 127;
            gg.LFOlevel[leLFO] = sublevels[3];
          } else {
            sublevels[3] = gg.LFOlevel[leLFO];
          }
          if (navlevel >= 4) {
            gobacktolfoparams();
          }
          draw_lfo_val(gg.LFOlevel[leLFO] / 127.0);
        }

        static void doLFOoffset() {
          int leLFO=cclfoselector;
          if (navlevel == 3) {
            navrange = 127;
            gg.LFOoffset[leLFO] = sublevels[3];
            doLFOallcontrols(leLFO);
          } else {
            sublevels[3] = gg.LFOoffset[leLFO];
          }
          if (navlevel >= 4) {
            gobacktolfoparams();
          }
          draw_lfo_val((64.0 - gg.LFOoffset[leLFO]) / 64.0);
        }

        static void doLFOphase() {
          int leLFO=cclfoselector;
          if (navlevel == 3) {
            navrange = 127;
            gg.LFOphase[leLFO] = sublevels[3];
            doLFOallcontrols(leLFO);
            // restartLFO(leLFO);
          } else {
            sublevels[3] = gg.LFOphase[leLFO];
          }
          if (navlevel >= 4) {
            gobacktolfoparams();
          }
          canvastitle.setCursor(80, 0);
          canvastitle.setTextSize(2);
          canvastitle.print((gg.LFOphase[leLFO]/127.0)*360);
        }

        static void freqbars_panel_selector() {
          if (navlevel == 3) {
            retroaction = sublevels[2];
            switch (sublevels[3]){
              case 0:
                display.fillRect(62, 0, 16, 16, SSD1306_INVERSE);
                self->unit = (int)gg.LFOHz[cclfoselector];
                sublevels[4]=self->unit;
              break;
              case 1:
                display.fillRect(88, 0, 12, 16, SSD1306_INVERSE);
                self->tenth = ((int)(gg.LFOHz[cclfoselector]* 10)) % 10;
                sublevels[4]=self->tenth;
              break;
              case 2:
                display.fillRect(100, 0, 12, 16, SSD1306_INVERSE);
                self->hundredth = ((int)(gg.LFOHz[cclfoselector] * 100)) % 10;
                sublevels[4]=self->hundredth;
              break;
            }
          display.display();
          }
        }
        static void freqbars_panel_action() {

          navrange = 9;
          switch (sublevels[3]){
            case 0:
              self->unit = sublevels[4];
            break;
            case 1:
              self->tenth = sublevels[4];
              //Serial.println(self->hundredth);
            break;
            case 2:
              self->hundredth = sublevels[4];
              //Serial.println(self->hundredth);
            break;
          }

          gg.LFOHz[cclfoselector] = (float)(self->unit + self->tenth * 0.1f + self->hundredth * 0.01f);
        }

        static void displayfreqbars(){
          //dm.clear_3();
          display.setTextSize(2);
          display.setCursor(65, 0);
          display.println(gg.LFOHz[cclfoselector]);
          //dolistLFOparams();
          //dm.dodisplay();
        }

        static void freqbars_panel() {
          if (navlevel >= 3) {
            retroaction = sublevels[2];
            if (navlevel == 3) {
              navrange = 2;

            }
            if (navlevel == 4) {
              retroaction = sublevels[3];
              freqbars_panel_action();
            }
            if (navlevel >= 5) {
              returntonav(3,9,sublevels[3]);
            }
            //dm.dodisplay();
          }
          displayfreqbars();
          freqbars_panel_selector();
          if (navlevel == 2) {
            retroaction = sublevels[1];
            navrange = sizeofLFOlabels - 1;
          }
        }



        static void dolistLFOparams() {
          const char* LFOlabels[] = {"Type",  "Level",  "Sync",
                                                "Freq",  "Offset", "Phase",
                                                "Synth", "<-  ",   "  ->"};
          dm.main_panel(LFOlabels, 2, sizeofLFOlabels);

        }

        static void doLFOallcontrols(byte leLFO) {
          restartLFO(leLFO);
          LFOwaveforms1[leLFO]->phase((gg.LFOphase[leLFO]/127.0)*360);
          LFOwaveforms1[leLFO]->offset((float)(((64 - gg.LFOoffset[leLFO]) / 64.0)));
        }
        static void go_to_synth(){
          if (navlevel >= 3) {
            sublevels[0] = 0;
            sublevels[2] = sublevels[1];
            sublevels[1] = 0;
            //wavelinepanel(sublevels[2]);
            returntonav(navlevel+2);
          }
        }
       
        static void go_previous(){
          if (navlevel >= 3) {
            if (cclfoselector-1 < 0)
              cclfoselector = 2 ;
            else
              cclfoselector = cclfoselector-1;
            
            sublevels[1] = cclfoselector ;
            returntonav(navlevel-1,sizeofLFOlabels-1,sublevels[2]);
            }
        }
        static void go_next(){
          if (navlevel >= 3) {
            cclfoselector = (cclfoselector+1)%3;
            sublevels[1] = cclfoselector ;
            returntonav(navlevel-1,sizeofLFOlabels-1,sublevels[2]);
            }
        }
        static void restartLFO(int leLFO=cclfoselector) {
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
            LFOwaveforms1[leLFO]->arbitraryWaveform(arbitrary_waveforms[leLFO],arbitrary_maxF[leLFO]);
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
          navrange = 8;
          dm.clean_title_2_1();
          dolistLFOparams();
          _route_nav[sublevels[2]]();
          canvasBIG.setCursor(122, 58);
          canvasBIG.print(cclfoselector + 1);
          dm.dodisplay();
        }

        static void printLFObanner(int startx, int starty, int leLFO=cclfoselector) {
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
            navrange = OSCS_COUNT-1;
            //TODO:remove maybe
            reinitsublevels(2);

            LFOlineBG();

            switch (sublevels[1]) {
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