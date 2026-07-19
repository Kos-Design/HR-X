
class LFOMenuRouter : public SectionHolder {
    public:
        LFOMenuRouter() {
                    self = this;
                    self->home_navrange=2;
                    self->relative_navlevel=1;
                    self->max_navlevel=5;
                    self->sublevels_address={1,0,0};
                    
                    }

        static void show() {
          _nav_lfo[navlevel-1]();
        }

        static void LFOmenuBG() {
          int leLFO=cclfoselector;
          canvasBIG.setTextSize(1);
          canvasBIG.setCursor(122, 58);
          canvasBIG.print(leLFO + 1);
        }

        static void applyLFOrmicon(int lesinthy) {
          // displaywaveformicon(sublevels[4],(char*)"SineWave",sinewave, lesynthi,
          // WAVEFORM_SINE);
          if (navlevel > 3) {
            LFOformstype[lesinthy] = sublevels[3];

            if (navlevel >= 4) {
              returntonav(2, 9);
            }
          }
        }

        static void LFOrmType() {
          int leLFO=cclfoselector;
          if (navlevel == 2){
            sublevels[3] = LFOformstype[leLFO];
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
            LFOformstype[leLFO] = sublevels[3];
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
            toggle_that(LFOsync[leLFO]);
            restartLFO(leLFO);
          }
          display.setCursor(55, 0);
          display.setTextSize(2);
          if (LFOsync[leLFO]) {
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
          canvastitle.setCursor(80, 0);
          canvastitle.setTextSize(2);
          canvastitle.print(laval);
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
            LFOlevel[leLFO] = sublevels[3];
          } else {
            sublevels[3] = LFOlevel[leLFO];
          }
          if (navlevel >= 4) {
            gobacktolfoparams();
          }
          draw_lfo_val(LFOlevel[leLFO] / 127.0);
        }

        static void doLFOoffset() {
          int leLFO=cclfoselector;
          if (navlevel == 3) {
            navrange = 100;
            LFOoffset[leLFO] = sublevels[3];
            doLFOallcontrols(leLFO);
          } else {
            sublevels[3] = LFOoffset[leLFO];
          }
          if (navlevel >= 4) {
            gobacktolfoparams();
          }
          draw_lfo_val(((50.0 - LFOoffset[leLFO]) / 50.0));
        }

        static void doLFOphase() {
          int leLFO=cclfoselector;
          if (navlevel == 3) {
            navrange = 100;
            LFOphase[leLFO] = sublevels[3];
            doLFOallcontrols(leLFO);
            // restartLFO(leLFO);
          } else {
            sublevels[3] = LFOphase[leLFO];
          }
          if (navlevel >= 4) {
            gobacktolfoparams();
          }
          doLFOparamdisplayval(LFOphase[leLFO]);
        }

        static void doLFOfreqd() {
          int leLFO=cclfoselector;
          if (navlevel == 3) {
            navrange = 127;
            LFOfreqs[leLFO] = sublevels[3];
            doLFOallcontrols(leLFO);
          } else {
            sublevels[3] = LFOfreqs[leLFO];
          }
          if (navlevel >= 4) {
            gobacktolfoparams();
          }
          doLFOparamdisplayval(LFOfreqs[leLFO]);
        }

        static void dolistLFOparams() {
          char LFOlabels[sizeofLFOlabels][12] = {"Type",  "Level",  "Sync",
                                                "Freq",  "Offset", "Phase",
                                                "Synth", "<-  ",   "  ->"};
          display.clearDisplay();
          int startx = 5;
          int starty = 16;
          char *textin = (char *)LFOlabels[sublevels[2]];

          dm.clean_title_2();
          canvastitle.println(textin);

          canvasBIG.setTextSize(1);



          for (int filer = 0; filer < sizeofLFOlabels - 1 - (sublevels[2]); filer++) {

            canvasBIG.setCursor(startx, starty + ((filer)*10));
            canvasBIG.println(LFOlabels[sublevels[2] + 1 + filer]);
          }
          for (int filer = 0; filer < sublevels[2]; filer++) {

            canvasBIG.setCursor(
                startx, (10 * (sizeofLFOlabels - sublevels[2]) + 6 + ((filer)*10)));
            canvasBIG.println(LFOlabels[filer]);
          }
        }

        static void doLFOallcontrols(byte leLFO) {
          restartLFO(leLFO);
          LFOwaveforms1[leLFO]->phase(0.36 * LFOphase[leLFO]);
          LFOwaveforms1[leLFO]->offset((float)(((50.0 - LFOoffset[leLFO]) / 50.0)));
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
          if (LFOsync[leLFO]) {
            float syncher = 1.0 ;
            if (millitickinterval) {
              syncher = (1000.00/(millitickinterval+1));
            }

            LFOwaveforms1[leLFO]->begin((float)(LFOlevel[leLFO]/127.00), (LFOfreqs[leLFO]/127.0)*syncher, lesformes[LFOformstype[leLFO]]);
          } else {
            LFOwaveforms1[leLFO]->begin((float)(LFOlevel[leLFO]/127.00), (LFOfreqs[leLFO]/127.0)*2, lesformes[LFOformstype[leLFO]]);
          }
          if (LFOformstype[leLFO] == 7) {
            LFOwaveforms1[leLFO]->arbitraryWaveform(arbitrary_waveforms[leLFO],arbitrary_maxF[leLFO]);
          }

          for (byte i = 0; i < SYNTH_LINERS_COUNT; i++) {
            if (FMmodulated[leLFO] == 1) {
              //phaseModulation should be based on lfo level
              FMwaveforms1[i + (leLFO * SYNTH_LINERS_COUNT)]->frequencyModulation((LFOlevel[leLFO]/127.00)*10);
            }
            else if (FMmodulated[leLFO] == 2) {
              FMwaveforms1[i + (leLFO * SYNTH_LINERS_COUNT)]->phaseModulation((LFOlevel[leLFO]/127.00) * 360 - 180);
            }
          }

          AudioInterrupts();
        }
        static void LFOlining() {
          navrange = 8;
          //int leLFO = sublevels[1]%3;
          dolistLFOparams();
          _route_nav[sublevels[2]]();
          LFOmenuBG();
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
            &doLFOfreqd,
            &doLFOoffset,
            &doLFOphase,
            &go_to_synth,
            &go_previous,
            &go_next
        };
        //void (LFOMenuRouter::*_nav_lfo[7])() = {nullptr};
        static constexpr void (*_nav_lfo[7])() = {&lfo_zero, &LFOlining,&LFOlining,&LFOlining,
                          &LFOlining,&LFOlining,&LFOlining};
        static LFOMenuRouter* self;
};

LFOMenuRouter* LFOMenuRouter::self = nullptr;
EXTMEM LFOMenuRouter _lf;