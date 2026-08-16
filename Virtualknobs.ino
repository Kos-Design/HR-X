
class VirtualKnobs : public SectionHolder {
  public:
    VirtualKnobs() { 
            self = this;  
            self->home_navrange=VBUT_LBL_COUNT;
            self->relative_navlevel=2;
            self->max_navlevel=5;
            //self->sublevels_address={9,0,0};
        }

    void doposkselector() {
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

    static void Vbuttonspanel() {
      self->actionvbuttons();
      self->displayonscreenbuttons();
      self->doposkselector();
      dm.dodisplay();
    }

    void actionvbuttons() {

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

    void displayonscreenbuttons() {

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
  private:
    static VirtualKnobs* self;
};

VirtualKnobs* VirtualKnobs::self = nullptr;
VirtualKnobs _vk;        