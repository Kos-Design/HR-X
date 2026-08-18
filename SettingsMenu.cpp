
#include "SettingsMenu.h"
#include "Triggers.h"
#include "pads.h"
#include "Patterns.h"
#include "Presets.h"
#include "KnobAssigner.h"
#include "PresetsMenu.h"

VirtualKnobs* VirtualKnobs::self = nullptr;

VirtualKnobs::VirtualKnobs() { 
            self = this;  
            self->home_navrange=VBUT_LBL_COUNT;
            self->relative_navlevel=2;
            self->max_navlevel=5;
            //self->sublevels_address={9,0,0};
        }

void VirtualKnobs::doposkselector() {
      char vbuttonslabels[VBUT_LBL_COUNT][12] = {
          "CuePlay",    "Backward -1", "Stop",   "Play",
          "Forward +1", "Record",      "Thingy", "Exit"};
      byte startyp = 8;
      byte ecart = 14;
      byte knobradius = 7;
      int xcentershifter;
      // lv.navrange = VBUT_LBL_COUNT-1 +17+14 ;

      // transportpanel
      if (lv.sublevels[self->relative_navlevel] < VBUT_LBL_COUNT) {
        canvastitle.fillScreen(SSD1306_BLACK);
        canvasBIG.setTextSize(1);
        if (gg.midiknobassigned[(70 + lv.sublevels[self->relative_navlevel] + 1 + (14 + 17))] !=
            0) {
          dm.printassignedmidi(
              gg.midiknobassigned[(70 + lv.sublevels[self->relative_navlevel] + 1 + (14 + 17))]);

        } else {
          canvasBIG.setCursor(0, 0);

          canvasBIG.print((char *)vbuttonslabels[lv.sublevels[self->relative_navlevel]]);
        }
        canvasBIG.setCursor(97, 0);
        canvasBIG.print("CC");
        canvasBIG.print(70 + lv.sublevels[self->relative_navlevel] + 1 + (14 + 17));
        canvasBIG.setCursor(110, 8);
        canvasBIG.print(0);
        canvasBIG.drawPixel(ecart * lv.sublevels[self->relative_navlevel] + 6, startyp + 7,
                            SSD1306_WHITE);
        canvasBIG.drawPixel(ecart * lv.sublevels[self->relative_navlevel] + 7, startyp + 6,
                            SSD1306_WHITE);
        canvasBIG.drawPixel(ecart * lv.sublevels[self->relative_navlevel] + 7, startyp + 7,
                            SSD1306_WHITE);
      } else {

        if (lv.sublevels[self->relative_navlevel] >= VBUT_LBL_COUNT &&
            lv.sublevels[self->relative_navlevel] < VBUT_LBL_COUNT + 7) {
          canvasBIG.fillRoundRect(
              108,
              16 + ((lv.sublevels[self->relative_navlevel] - VBUT_LBL_COUNT) * 7), 9,
              6, 1, SSD1306_WHITE);

          if (gg.midiknobassigned[(70 + lv.sublevels[self->relative_navlevel] + 1 -
                                (VBUT_LBL_COUNT))] != 0) {
            dm.printassignedmidi(gg.midiknobassigned[(70 + lv.sublevels[self->relative_navlevel] +
                                                1 - (VBUT_LBL_COUNT))]);

          } else {
            canvasBIG.setCursor(0, 0);
            canvasBIG.print("V.Button ");
            canvasBIG.print(lv.sublevels[self->relative_navlevel] + 1 -
                            (VBUT_LBL_COUNT));
          }
          canvasBIG.setCursor(97, 0);
          canvasBIG.print("CC");
          canvasBIG.print(70 + lv.sublevels[self->relative_navlevel] + 1 -
                          (VBUT_LBL_COUNT));
          canvasBIG.setCursor(110, 8);
          canvasBIG.print(0);

        } else {
          if (lv.sublevels[self->relative_navlevel] >= VBUT_LBL_COUNT + 7 &&
              lv.sublevels[self->relative_navlevel] < VBUT_LBL_COUNT + 14) {
            canvasBIG.fillRoundRect(
                119,
                16 + ((lv.sublevels[self->relative_navlevel] - VBUT_LBL_COUNT - 7) *
                      7),
                9, 6, 1, SSD1306_WHITE);
            if (gg.midiknobassigned[(70 + lv.sublevels[self->relative_navlevel] + 1 -
                                  (VBUT_LBL_COUNT))] != 0) {
              dm.printassignedmidi(gg.midiknobassigned[(70 + lv.sublevels[self->relative_navlevel] +
                                                  1 - (VBUT_LBL_COUNT))]);

            } else {
              canvasBIG.setCursor(0, 0);
              canvasBIG.print("V.Button ");
              canvasBIG.print(lv.sublevels[self->relative_navlevel] + 1 -
                              (VBUT_LBL_COUNT));
            }
            canvasBIG.setCursor(97, 0);
            canvasBIG.print("CC");
            canvasBIG.print(70 + lv.sublevels[self->relative_navlevel] + 1 -
                            (VBUT_LBL_COUNT));
            canvasBIG.setCursor(110, 8);
            canvasBIG.print(0);

          } else {

            if (lv.sublevels[self->relative_navlevel] >= VBUT_LBL_COUNT + 14 &&
                lv.sublevels[self->relative_navlevel] < VBUT_LBL_COUNT + 14 + 6) {
              xcentershifter =
                  97 - (((knobradius * 2) + 4) * (lv.sublevels[self->relative_navlevel] -
                                                  VBUT_LBL_COUNT - 14));
              canvasBIG.drawCircle(xcentershifter, 64 - 9, knobradius - 1,
                                  SSD1306_WHITE);

              if (gg.midiknobassigned[(lv.sublevels[self->relative_navlevel] + 1 -
                                    (VBUT_LBL_COUNT))] != 0) {
                dm.printassignedmidi(
                    gg.midiknobassigned[(70 + lv.sublevels[self->relative_navlevel] + 1 -
                                      (VBUT_LBL_COUNT))]);

              } else {
                canvasBIG.setCursor(0, 0);
                canvasBIG.print("V.Pot ");
                canvasBIG.print(lv.sublevels[self->relative_navlevel] + 1 -
                                (VBUT_LBL_COUNT + 14));
              }
              canvasBIG.setCursor(97, 0);
              canvasBIG.print("CC");
              canvasBIG.print(70 + lv.sublevels[self->relative_navlevel] + 1 -
                              (VBUT_LBL_COUNT));

              canvasBIG.setCursor(110, 8);
              canvasBIG.print(gg.vPots[lv.sublevels[self->relative_navlevel] -
                                    (VBUT_LBL_COUNT + 14)]);
            } else {

              if (lv.sublevels[self->relative_navlevel] >= VBUT_LBL_COUNT + 14 + 6 &&
                  lv.sublevels[self->relative_navlevel] <
                      VBUT_LBL_COUNT + 14 + 6 + 5) {

                xcentershifter = 16 + (((knobradius * 2) + 4) *
                                      (lv.sublevels[self->relative_navlevel] -
                                        VBUT_LBL_COUNT - 14 - 6));
                canvasBIG.drawCircle(xcentershifter, 64 - 9 - 16, knobradius - 1,
                                    SSD1306_WHITE);
                if (gg.midiknobassigned[(70 + lv.sublevels[self->relative_navlevel] + 1 -
                                      (VBUT_LBL_COUNT))] != 0) {
                  dm.printassignedmidi(
                      gg.midiknobassigned[(70 + lv.sublevels[self->relative_navlevel] + 1 -
                                        (VBUT_LBL_COUNT))]);

                } else {
                  canvasBIG.setCursor(0, 0);
                  canvasBIG.print("V.Pot ");
                  canvasBIG.print(lv.sublevels[self->relative_navlevel] + 1 -
                                  (VBUT_LBL_COUNT + 14));
                }
                canvasBIG.setCursor(97, 0);
                canvasBIG.print("CC");
                canvasBIG.print(70 + lv.sublevels[self->relative_navlevel] + 1 -
                                (VBUT_LBL_COUNT));

                canvasBIG.setCursor(110, 8);
                canvasBIG.print(gg.vPots[lv.sublevels[self->relative_navlevel] -
                                      (VBUT_LBL_COUNT + 14)]);

              } else {
                if (lv.sublevels[self->relative_navlevel] >=
                        VBUT_LBL_COUNT + 14 + 6 + 5 &&
                    lv.sublevels[self->relative_navlevel] <
                        VBUT_LBL_COUNT + 14 + 6 + 5 + 6) {

                  if (gg.midiknobassigned[(70 + lv.sublevels[self->relative_navlevel] + 1 -
                                        (VBUT_LBL_COUNT))] != 0) {
                    dm.printassignedmidi(
                        gg.midiknobassigned[(70 + lv.sublevels[self->relative_navlevel] + 1 -
                                          (VBUT_LBL_COUNT))]);

                  } else {
                    canvasBIG.setCursor(0, 0);
                    canvasBIG.print("V.Pot ");
                    canvasBIG.print(lv.sublevels[self->relative_navlevel] + 1 -
                                    (VBUT_LBL_COUNT + 14));
                  }
                  canvasBIG.setCursor(97, 0);
                  canvasBIG.print("CC");
                  canvasBIG.print(70 + lv.sublevels[self->relative_navlevel] + 1 -
                                  (VBUT_LBL_COUNT));

                  canvasBIG.setCursor(110, 8);
                  canvasBIG.print(gg.vPots[lv.sublevels[self->relative_navlevel] -
                                        (VBUT_LBL_COUNT + 14)]);

                  xcentershifter = 97 - (((knobradius * 2) + 4) *
                                        (lv.sublevels[self->relative_navlevel] -
                                          VBUT_LBL_COUNT - 14 - 6 - 5));
                  canvasBIG.drawCircle(xcentershifter, 16 + knobradius,
                                      knobradius - 1, SSD1306_WHITE);
                }
              }
            }
          }
        }
      }
      canvasBIG.setCursor(65, 0);
      canvasBIG.print(lv.BPMs, 1);
    }

void VirtualKnobs::Vbuttonspanel() {
      self->actionvbuttons();
      self->displayonscreenbuttons();
      self->doposkselector();
      dm.dodisplay();
    }

void VirtualKnobs::actionvbuttons() {

      if (lv.sublevels[self->relative_navlevel] < VBUT_LBL_COUNT + 14) {

        if (lv.navlevel == self->relative_navlevel) {
          lv.navrange = VBUT_LBL_COUNT - 1 + 17 + 14;
        }
        if (lv.navlevel == self->relative_navlevel + 1) {

          if (lv.sublevels[self->relative_navlevel] < VBUT_LBL_COUNT) {
            int CClaval0 = 70 + (lv.sublevels[self->relative_navlevel] + 1 + (14 + 17));
            _tt.moncontrollercc((byte)1, (byte)CClaval0, (byte)127);
            // Serial.print("sending cc ");
            // Serial.println(CClaval0);
          }

          if (lv.sublevels[self->relative_navlevel] < VBUT_LBL_COUNT + 14 &&
              lv.sublevels[self->relative_navlevel] >= VBUT_LBL_COUNT) {
            int CClaval =
                70 + (lv.sublevels[self->relative_navlevel] + 1 - (VBUT_LBL_COUNT));
            _tt.moncontrollercc((byte)1, (byte)CClaval, (byte)127);
            // moncontrollercc( (byte)1,(byte)CClaval, (byte)0);
          }

          dm.returntonav(self->relative_navlevel);
          // Vbuttonspanel();
        }

      } else {

        if (lv.navlevel == self->relative_navlevel) {

          lv.navrange = VBUT_LBL_COUNT - 1 + 17 + 14;
          lv.sublevels[self->relative_navlevel + 1] =
              gg.vPots[lv.sublevels[self->relative_navlevel] - VBUT_LBL_COUNT - 14];
          lv.sublevels[self->relative_navlevel + 2] =
              gg.vPots[lv.sublevels[self->relative_navlevel] - VBUT_LBL_COUNT - 14];
        } else {

          if (lv.navlevel == self->relative_navlevel + 1) {

            lv.navrange = 127;
            gg.vPots[lv.sublevels[self->relative_navlevel] - VBUT_LBL_COUNT - 14] =
                lv.sublevels[self->relative_navlevel + 1];

            if (lv.sublevels[self->relative_navlevel] > VBUT_LBL_COUNT + 14) {
              int CClaval2 =
                  70 + (lv.sublevels[self->relative_navlevel] + 1 - (VBUT_LBL_COUNT));
              _tt.moncontrollercc((byte)1, (byte)CClaval2,
                              (byte)(gg.vPots[lv.sublevels[self->relative_navlevel] -
                                          VBUT_LBL_COUNT - 14]));
              // moncontrollercc( (byte)1,(byte)CClaval0, (byte)0);
            }
          }
          if (lv.navlevel >= self->relative_navlevel + 2) {
            gg.vPots[lv.sublevels[self->relative_navlevel] - VBUT_LBL_COUNT - 14] =
                lv.sublevels[self->relative_navlevel + 1];
            lv.sublevels[self->relative_navlevel + 2] = lv.sublevels[self->relative_navlevel];
            // lv.navlevel--;
            //   lv.navlevel--;
            // lv.navrange = VBUT_LBL_COUNT-1 +17+14 ;
            // lv.rota_true_pos = lv.sublevels[self->relative_navlevel + 2];
            //  myEnc.write(lv.sublevels[self->relative_navlevel]*4);
            dm.returntonav(self->relative_navlevel);
            // Serial.print( "lv.sublevels[1]= ");
            // Serial.println( lv.sublevels[1]);
            // Vbuttonspanel();
          }
        }
      }
    }

void VirtualKnobs::displayonscreenbuttons() {

  byte centercirclex;
  byte centercircley;
  byte xcentershifter;
  byte knobradius = 7;
  // angleofknob = (0.3*360.0)-90 ;

  byte trianglepointx;
  byte trianglepointy;

  float coeffangle;
  display.clearDisplay();

  canvasBIG.fillScreen(SSD1306_BLACK);
  canvasBIG.setCursor(0, 0);
  canvasBIG.setTextSize(1);

  for (int i = 0; i < 8; i++) {
    // canvasBIG.drawLine(0, 52, 128, 52, SSD1306_WHITE) ;
    canvasBIG.drawRoundRect(108, 16 + (i * 7), 9, 6, 1, SSD1306_WHITE);
  }

  for (int i = 0; i < 8; i++) {

    canvasBIG.drawRoundRect(119, 16 + (i * 7), 9, 6, 1, SSD1306_WHITE);
  }
  for (int i = 0; i < 6; i++) {

    coeffangle = (6.2831 - ((float)gg.vPots[16 - i] / 127.0) * 6.2831) + 3.1416;

    // Serial.print(i);
    // Serial.print(" ");
    // Serial.print(gg.vPots[16-i]/127.0);
    //   Serial.print(" angle ");
    // Serial.println(angleofknob);

    xcentershifter = (knobradius * 2) + 4;
    centercirclex = knobradius + (xcentershifter * i);
    centercircley = 16 + knobradius;

    canvasBIG.drawCircle(centercirclex, centercircley, knobradius,
                        SSD1306_WHITE);

    trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
    trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));

    display.drawLine(centercirclex, centercircley, trianglepointx,
                    trianglepointy, SSD1306_WHITE);
  }
  centercircley += 19 - (knobradius / 2);
  for (int i = 0; i < 5; i++) {

    //  float coeffangle = ((float)gg.vPots[6+i]/127.0)*0.05 ;
    // angleofknob = ((360.0 * coeffangle ) - 45.0 );
    coeffangle = (6.2831 - ((float)gg.vPots[6 + i] / 127.0) * 6.2831) + 3.1416;

    xcentershifter = (knobradius * 2) + 4;
    centercirclex = knobradius + (xcentershifter * i);

    trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle)))) +
                    knobradius + 2;
    trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));

    canvasBIG.drawCircle(centercirclex + knobradius + 2, centercircley,
                        knobradius, SSD1306_WHITE);
    display.drawLine(centercirclex + knobradius + 2, centercircley,
                    trianglepointx, trianglepointy, SSD1306_WHITE);
  }
  centercircley += 16;
  for (int i = 0; i < 6; i++) {
    xcentershifter = (knobradius * 2) + 4;
    centercirclex = knobradius + (xcentershifter * i);

    // float coeffangle = ((float)gg.vPots[5-i]/127.0)*0.05 ;
    coeffangle = (6.2831 - ((float)gg.vPots[5 - i] / 127.0) * 6.2831) + 3.1416;

    trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
    trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));

    canvasBIG.drawCircle(centercirclex, centercircley, knobradius,
                        SSD1306_WHITE);

    display.drawLine(centercirclex, centercircley, trianglepointx,
                    trianglepointy, SSD1306_WHITE);
  }

  dm.drawtransport();
  // maison - cursor upsidedown (char)127)
  // ç (char)128
  // fleche haut bas (char)18
  // sortede s bizarre (char)21
  // ankh (char)12
  // sorte de rond (char) 9
  // porte percee  (char)8
  // trefle (char)5
  // fleche hautbas underscoree  (char)23
  // fleche droite (char)26
  // fleche droitegauche (char)29
  // rien  (char)32

  // u trema  (char)129)
  // sorte de rectangle petit (char200
  // !! doublexclamation(char)19
  // pi (char)20
  // rien (char)13
  // rien (char)10
  // rondplein (char)7
  // losange  (char)4
  // face unhappy  (char)1
  // fleche bas (char)25
  // sortede L (char)28
  // cursor bas  (char)31

  // megastar (char)15)
  // playbutton (char)16
  // play backward button (char)17
  // underscore (char)22
  // music double  (char)14
  // male (char)11
  // pique  (char)6
  // coeur (char)3
  // face happy (char)2
  // fleche haut (char)24
  // fleche gauche  (char)27
  // cursor haut  (char)30
}


SettingsMenuRouter* SettingsMenuRouter::self = nullptr;


SettingsMenuRouter::SettingsMenuRouter() {
                    self = this;
                    self->home_navrange=settings_labels_count - 1;
                    self->relative_navlevel=2;
                    self->max_navlevel=5;
                    self->sublevels_address={5,0,0};
                    }
                  

void SettingsMenuRouter::show() {
          if (lv.navlevel == 1) {
            lv.setting_on_board = false ;
            settings_nav_zero();
          }

          // arpegiator has its own panel -> 8 , same for 11 which is OnboardPanel
          if (lv.navlevel >= 2) {
            settings_nav_one();
          }
        }

void SettingsMenuRouter::apply_alt_ctl(){
          //TODO implement learn midi
          for (int i = 0; i < 4; i++) {
            _ka.set_midi_cc_to_ctl(_ka.find_assigned_knob(gg.alt_nav[i]),0);
            //hope that ctl index of rota_increase_ctl doesn't change
            _ka.set_midi_cc_to_ctl(gg.alt_nav[i],123+i);
          }
        }
void SettingsMenuRouter::set_alternative_rota(){

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

void SettingsMenuRouter::set_in_source(){
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

void SettingsMenuRouter::settings_nav_zero(){
          dm.reinitsublevels(2);
          dm.clean_title_1_1();
          _tt.debugmidion = 0;
          self->noteprint = 0;
          lv.navrange = settings_labels_count - 1;
          makesettingslist();
          dm.dodisplay();
        }

void SettingsMenuRouter::OnBoardVpanelAction() {
          if (lv.navlevel > 3) {
            if (((lv.sublevels[2] <= 11) || (lv.sublevels[2] > 45)) && (lv.navlevel == 4)) {
              gg.ordered_pots[Padded.potsboards[lv.sublevels[2]]] = gg.pot_assignements[lv.sublevels[2]];
            }
            dm.returntonav(2);
          }
        }

void SettingsMenuRouter::OnBoardVpanelSelector() {

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

void SettingsMenuRouter::OnBoardVpanel() {
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


        
        

void SettingsMenuRouter::arpegiatorVpanelAction() {
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

void SettingsMenuRouter::arpegiatorVpanelSelector() {
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

void SettingsMenuRouter::arpegiatorVpanel() {

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



void SettingsMenuRouter::makesettingslist() {
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

void SettingsMenuRouter::settings_nav_one(){
          
          canvasBIG.setTextSize(1);
          canvastitle.setTextSize(1);
          _settings_menu[lv.sublevels[1]]();
          if (lv.sublevels[1] != 8 && lv.sublevels[1] != 15 && lv.sublevels[1] != 14 && lv.sublevels[1] != 16 && lv.sublevels[1] != 11 ) {
            makesettingslist();
            dm.dodisplay();
          }
          
        }

byte SettingsMenuRouter::getnotefromfreq(float lafreq) {
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

byte SettingsMenuRouter::getclosestnote(byte lei, float lafreq) {
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

void SettingsMenuRouter::printlanote() {
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
void SettingsMenuRouter::metronomer() {
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

void SettingsMenuRouter::toggle_echo_midi(){
        _tt.debugmidion = !_tt.debugmidion;
      }

void SettingsMenuRouter::toggle_freeze_midi(){
        lv.freezemidicc = !lv.freezemidicc;
        dm.returntonav(1,self->home_navrange,1);
      }

void SettingsMenuRouter::set_synth_midi_ch(){
        lv.navrange = 16;
        gg.synthmidichannel = (byte)lv.sublevels[2];
        if (lv.navlevel >= 3) {
          dm.returntonav(1,self->home_navrange,2);
        }
      }

void SettingsMenuRouter::set_sampler_midi_ch(){
        lv.navrange = 16;
        gg.samplermidichannel = lv.sublevels[2];
        if (lv.navlevel >= 3) {
          dm.returntonav(1,self->home_navrange,3);
        }
      }
      
void SettingsMenuRouter::toggle_digital_analog(){
        gg.digitalplay = !gg.digitalplay;
        dm.returntonav(1,self->home_navrange,4);
      }
      
      
void SettingsMenuRouter::set_tap_note(){
        lv.navrange = 127;
        gg.tapnote = byte(lv.sublevels[2]);
        if (lv.navlevel >= 3 ){
          dm.returntonav(1,self->home_navrange,5);
        }
      }

void SettingsMenuRouter::set_bpms_interval(){
        lv.navrange = 620;
        gg.millitickinterval = lv.sublevels[2];
        //setbpms();
        if (lv.navlevel >= 3) {
          gg.millitickinterval = lv.sublevels[2];
          _ps.setbpms();
          //tempo = gg.millitickinterval;
          dm.returntonav(1,self->home_navrange,6);
        }
      }

void SettingsMenuRouter::set_chord_mode(){
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

void SettingsMenuRouter::toggle_ext_clock(){
        //gg.externalticker = !gg.externalticker;
        gg.externalticker = !gg.externalticker;
        dm.returntonav(1,self->home_navrange,9);
      }
void SettingsMenuRouter::unplug_notefreq_from_ampL(){
  Notespy_cable.disconnect();
}
void SettingsMenuRouter::replug_notefreq_from_ampL(){
  Notespy_cable.connect();
}
void SettingsMenuRouter::toggle_note_spy(){
        self->noteprint = !self->noteprint;
        if (self->noteprint) {
          self->replug_notefreq_from_ampL();
          notefreq1.begin(.15);
        } else {
          self->unplug_notefreq_from_ampL();
        }
        if (lv.navlevel >= 3) {
          dm.returntonav(1,self->home_navrange,10);
        }
      }

void SettingsMenuRouter::set_audio_source(){
        lv.navrange = 2 ;
        self->AudioInSource = lv.sublevels[2] ;
        if (lv.navlevel >= 3) {
          set_in_source();
          dm.returntonav(1,self->home_navrange,12);
        }
      }

void SettingsMenuRouter::toggle_midi_out(){
  gg.SendMidiOut = !gg.SendMidiOut ;
  dm.returntonav(1,self->home_navrange,13);
}

void (*SettingsMenuRouter::_settings_menu[settings_labels_count])() = {&toggle_echo_midi,&toggle_freeze_midi,&set_synth_midi_ch,&set_sampler_midi_ch,&toggle_digital_analog,
                                                                        &set_tap_note,&set_bpms_interval,&set_chord_mode,&arpegiatorVpanel,&toggle_ext_clock,&toggle_note_spy,
                                                                        &OnBoardVpanel,&set_audio_source,&toggle_midi_out,&_vk.Vbuttonspanel,&_ka.show,&set_alternative_rota};

     

     /*static void (*root_route[10])();
void (*DisplayManager::root_route[10])() = {&_sn.show,&_lf.show,&_rd.show,&_sg.show,&_pt.show,
                                    &_st.show,&_fx.MainFxPanel,&_sp.show,&_wf.show,&_ps.show};
*/