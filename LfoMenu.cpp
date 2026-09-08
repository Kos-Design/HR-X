#include "LfoMenu.h"
#include "Presets.h"
#include "SynthMenu.h"

LFOMenuRouter* LFOMenuRouter::self = nullptr;

LFOMenuRouter::LFOMenuRouter() {
                    self = this;
                    self->home_navrange=2;
                    self->relative_navlevel=1;
                    self->max_navlevel=5;
                    self->sublevels_address={1,0,0};
                    }


void LFOMenuRouter::show() {
          _nav_lfo[mc.navlevel-1]();
        }

void LFOMenuRouter::applyLFOrmicon(int lesinthy) {
          // displaywaveformicon(mc.sublevels[4],(char*)"SineWave",sinewave, lesynthi,
          // WAVEFORM_SINE);
          if (mc.navlevel > 3) {
            gg.LFOformstype[lesinthy] = mc.sublevels[3];

            if (mc.navlevel >= 4) {
              dm.returntonav(2, 9);
            }
          }
        }

void LFOMenuRouter::LFOrmType() {
          int leLFO=mc.cclfoselector;
          if (mc.navlevel == 2){
            mc.sublevels[3] = gg.LFOformstype[leLFO];
          }
          if (mc.navlevel == 3) {
            mc.navrange = 8;
          }
          displayLFOrmimg();
          if (mc.navlevel >= 4) {
            gg.LFOformstype[leLFO] = mc.sublevels[3];

            restartLFO(leLFO%OSCS_COUNT);
            gobacktolfoparams();
          }
        }

void LFOMenuRouter::displayLFOrmimg() {
  dm.canvasBIG.drawBitmap(70, 20, _img[mc.sublevels[3]], 32, 32, SSD1306_WHITE);
  dm.canvastitle.setTextSize(1); // Draw 1X-scale text
  dm.canvastitle.setTextColor(SSD1306_WHITE);
  dm.canvastitle.setCursor(64, 8);
  dm.canvastitle.println(lelabelw[mc.sublevels[3]]);
}

void LFOMenuRouter::doLFObool() {
          int leLFO=mc.cclfoselector;
          if (mc.navlevel == 3) {
            gg.LFOsync[leLFO] = !gg.LFOsync[leLFO] ;
            restartLFO(leLFO);
          }
          dm.setCursor(55, 0);
          dm.setTextSize(2);
          if (gg.LFOsync[leLFO]) {
            dm.print("Active");
          } else {
            dm.print("Off");
          }
          dm.display();
          if (mc.navlevel >= 4) {
            dm.returntonav(2, 2);
          }
        }

void LFOMenuRouter::gobacktolfoparams() { dm.returntonav(2); }

void LFOMenuRouter::doLFOparamdisplayval(int laval) {

        }

void LFOMenuRouter::draw_lfo_val(float laval) {
          dm.canvastitle.setCursor(80, 0);
          dm.canvastitle.setTextSize(2);
          dm.canvastitle.print(laval);
        }

void LFOMenuRouter::doLFOlevel() {
          int leLFO=mc.cclfoselector;
          if (mc.navlevel == 3) {
            mc.navrange = 127;
            gg.LFOlevel[leLFO] = mc.sublevels[3];
          } else {
            mc.sublevels[3] = gg.LFOlevel[leLFO];
          }
          if (mc.navlevel >= 4) {
            gobacktolfoparams();
          }
          draw_lfo_val(gg.LFOlevel[leLFO] / 127.0);
        }

void LFOMenuRouter::doLFOoffset() {
          int leLFO=mc.cclfoselector;
          if (mc.navlevel == 3) {
            mc.navrange = 127;
            gg.LFOoffset[leLFO] = mc.sublevels[3];
            doLFOallcontrols(leLFO);
          } else {
            mc.sublevels[3] = gg.LFOoffset[leLFO];
          }
          if (mc.navlevel >= 4) {
            gobacktolfoparams();
          }
          draw_lfo_val((64.0 - gg.LFOoffset[leLFO]) / 64.0);
        }

void LFOMenuRouter::doLFOphase() {
          int leLFO=mc.cclfoselector;
          if (mc.navlevel == 3) {
            mc.navrange = 127;
            gg.LFOphase[leLFO] = mc.sublevels[3];
            doLFOallcontrols(leLFO);
            // restartLFO(leLFO);
          } else {
            mc.sublevels[3] = gg.LFOphase[leLFO];
          }
          if (mc.navlevel >= 4) {
            gobacktolfoparams();
          }
          dm.canvastitle.setCursor(80, 0);
          dm.canvastitle.setTextSize(2);
          dm.canvastitle.print((gg.LFOphase[leLFO]/127.0)*360);
        }

void LFOMenuRouter::freqbars_panel_selector() {
          if (mc.navlevel == 3) {
            mc.retroaction = mc.sublevels[2];
            switch (mc.sublevels[3]){
              case 0:
                dm.fillRect(62, 0, 16, 16, SSD1306_INVERSE);
                self->unit = (int)gg.LFOHz[mc.cclfoselector];
                mc.sublevels[4]=self->unit;
              break;
              case 1:
                dm.fillRect(88, 0, 12, 16, SSD1306_INVERSE);
                self->tenth = ((int)(gg.LFOHz[mc.cclfoselector]* 10)) % 10;
                mc.sublevels[4]=self->tenth;
              break;
              case 2:
                dm.fillRect(100, 0, 12, 16, SSD1306_INVERSE);
                self->hundredth = ((int)(gg.LFOHz[mc.cclfoselector] * 100)) % 10;
                mc.sublevels[4]=self->hundredth;
              break;
            }
          dm.display();
          }
        }
void LFOMenuRouter::freqbars_panel_action() {

          mc.navrange = 9;
          switch (mc.sublevels[3]){
            case 0:
              self->unit = mc.sublevels[4];
            break;
            case 1:
              self->tenth = mc.sublevels[4];
              //Serial.println(self->hundredth);
            break;
            case 2:
              self->hundredth = mc.sublevels[4];
              //Serial.println(self->hundredth);
            break;
          }

          gg.LFOHz[mc.cclfoselector] = (float)(self->unit + self->tenth * 0.1f + self->hundredth * 0.01f);
        }

void LFOMenuRouter::displayfreqbars(){
          //dm.clear_3();
          dm.setTextSize(2);
          dm.setCursor(65, 0);
          dm.println(gg.LFOHz[mc.cclfoselector]);
          //dolistLFOparams();
          //dm.dodisplay();
        }

void LFOMenuRouter::freqbars_panel() {
          if (mc.navlevel >= 3) {
            mc.retroaction = mc.sublevels[2];
            if (mc.navlevel == 3) {
              mc.navrange = 2;

            }
            if (mc.navlevel == 4) {
              mc.retroaction = mc.sublevels[3];
              freqbars_panel_action();
            }
            if (mc.navlevel >= 5) {
              dm.returntonav(3,9,mc.sublevels[3]);
            }
            //dm.dodisplay();
          }
          displayfreqbars();
          freqbars_panel_selector();
          if (mc.navlevel == 2) {
            mc.retroaction = mc.sublevels[1];
            mc.navrange = self->sizeofLFOlabels - 1;
          }
        }



void LFOMenuRouter::dolistLFOparams() {
          const char* LFOlabels[] = {"Type",  "Level",  "Sync",
                                                "Freq",  "Offset", "Phase",
                                                "Synth", "<-  ",   "  ->"};
          dm.main_panel(LFOlabels, 2, self->sizeofLFOlabels);

        }

void LFOMenuRouter::doLFOallcontrols(byte leLFO) {
          restartLFO(leLFO);
          LFOwaveforms1[leLFO]->phase((gg.LFOphase[leLFO]/127.0)*360);
          LFOwaveforms1[leLFO]->offset((float)(((64 - gg.LFOoffset[leLFO]) / 64.0)));
        }
void LFOMenuRouter::go_to_synth(){
          if (mc.navlevel >= 3) {
            mc.sublevels[0] = 0;
            mc.sublevels[2] = mc.sublevels[1];
            mc.sublevels[1] = 0;
            //wavelinepanel(mc.sublevels[2]);
            dm.returntonav(mc.navlevel+2);
          }
        }

void LFOMenuRouter::go_previous(){
          if (mc.navlevel >= 3) {
            if (mc.cclfoselector-1 < 0)
              mc.cclfoselector = 2 ;
            else
              mc.cclfoselector = mc.cclfoselector-1;

            mc.sublevels[1] = mc.cclfoselector ;
            dm.returntonav(mc.navlevel-1,self->sizeofLFOlabels-1,mc.sublevels[2]);
            }
        }
void LFOMenuRouter::go_next(){
          if (mc.navlevel >= 3) {
            mc.cclfoselector = (mc.cclfoselector+1)%3;
            mc.sublevels[1] = mc.cclfoselector ;
            dm.returntonav(mc.navlevel-1,self->sizeofLFOlabels-1,mc.sublevels[2]);
            }
        }
void LFOMenuRouter::restartLFO(int leLFO) {
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
void LFOMenuRouter::LFOlining() {
          mc.navrange = 8;
          dm.clean_title_2_1();
          dolistLFOparams();
          _route_nav[mc.sublevels[2]]();
          dm.canvasBIG.setCursor(122, 58);
          dm.canvasBIG.print(mc.cclfoselector + 1);
          dm.dodisplay();
        }

void LFOMenuRouter::printLFObanner(int startx, int starty, int leLFO) {
            dm.fillRect(startx, starty, 64, 24, SSD1306_INVERSE);
            dm.printlabel((char*)"LFO ");
            dm.setCursor(116, 0);
            dm.print(leLFO);
            dm.display();
        }

void LFOMenuRouter::LFOlineBG() {
            dm.clearDisplay();
            dm.drawBitmap(0, 64 - 47, wavesbg2, 128, 47, SSD1306_WHITE);
            byte lfi = mc.sublevels[1];
            //dm.fillRect(0+(lfi%2)*64, 16+(24*(lfi/2)), 64, 24, SSD1306_INVERSE);
            dm.display();
            printLFObanner((lfi%2)*64, 16+(24*(lfi/2)), lfi+1);

        }

void LFOMenuRouter::lfo_zero(){
            mc.navrange = OSCS_COUNT-1;
            //TODO:remove maybe
            dm.reinitsublevels(2);
            LFOlineBG();
        }

