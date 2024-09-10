void printassignedmidi(int lemidiassknob) {
  canvasBIG.setCursor(0, 0);
  canvasBIG.print((char *)ControlList[lemidiassknob]);
}
void doposkselector() {
  char vbuttonslabels[numberofvbuttonslabels][12] = {
      "CuePlay",    "Backward -1", "Stop",   "Play",
      "Forward +1", "Record",      "Thingy", "Exit"};
  byte startyp = 8;
  byte ecart = 14;
  byte knobradius = 7;
  int xcentershifter;
  // navrange = numberofvbuttonslabels-1 +17+14 ;

  // transportpanel
  if (sublevels[navlevelvbuttons] < numberofvbuttonslabels) {
    canvastitle.fillScreen(SSD1306_BLACK);
    canvasBIG.setTextSize(1);
    if (midiknobassigned[(70 + sublevels[navlevelvbuttons] + 1 + (14 + 17))] !=
        0) {
      printassignedmidi(
          midiknobassigned[(70 + sublevels[navlevelvbuttons] + 1 + (14 + 17))]);

    } else {
      canvasBIG.setCursor(0, 0);

      canvasBIG.print((char *)vbuttonslabels[sublevels[navlevelvbuttons]]);
    }
    canvasBIG.setCursor(97, 0);
    canvasBIG.print("CC");
    canvasBIG.print(70 + sublevels[navlevelvbuttons] + 1 + (14 + 17));
    canvasBIG.setCursor(110, 8);
    canvasBIG.print(0);
    canvasBIG.drawPixel(ecart * sublevels[navlevelvbuttons] + 6, startyp + 7,
                        SSD1306_WHITE);
    canvasBIG.drawPixel(ecart * sublevels[navlevelvbuttons] + 7, startyp + 6,
                        SSD1306_WHITE);
    canvasBIG.drawPixel(ecart * sublevels[navlevelvbuttons] + 7, startyp + 7,
                        SSD1306_WHITE);
  } else {

    if (sublevels[navlevelvbuttons] >= numberofvbuttonslabels &&
        sublevels[navlevelvbuttons] < numberofvbuttonslabels + 7) {
      canvasBIG.fillRoundRect(
          108,
          16 + ((sublevels[navlevelvbuttons] - numberofvbuttonslabels) * 7), 9,
          6, 1, SSD1306_WHITE);

      if (midiknobassigned[(70 + sublevels[navlevelvbuttons] + 1 -
                            (numberofvbuttonslabels))] != 0) {
        printassignedmidi(midiknobassigned[(70 + sublevels[navlevelvbuttons] +
                                            1 - (numberofvbuttonslabels))]);

      } else {
        canvasBIG.setCursor(0, 0);
        canvasBIG.print("V.Button ");
        canvasBIG.print(sublevels[navlevelvbuttons] + 1 -
                        (numberofvbuttonslabels));
      }
      canvasBIG.setCursor(97, 0);
      canvasBIG.print("CC");
      canvasBIG.print(70 + sublevels[navlevelvbuttons] + 1 -
                      (numberofvbuttonslabels));
      canvasBIG.setCursor(110, 8);
      canvasBIG.print(0);

    } else {
      if (sublevels[navlevelvbuttons] >= numberofvbuttonslabels + 7 &&
          sublevels[navlevelvbuttons] < numberofvbuttonslabels + 14) {
        // Serial.println( "not a pot");
        canvasBIG.fillRoundRect(
            119,
            16 + ((sublevels[navlevelvbuttons] - numberofvbuttonslabels - 7) *
                  7),
            9, 6, 1, SSD1306_WHITE);
        if (midiknobassigned[(70 + sublevels[navlevelvbuttons] + 1 -
                              (numberofvbuttonslabels))] != 0) {
          printassignedmidi(midiknobassigned[(70 + sublevels[navlevelvbuttons] +
                                              1 - (numberofvbuttonslabels))]);

        } else {
          canvasBIG.setCursor(0, 0);
          canvasBIG.print("V.Button ");
          canvasBIG.print(sublevels[navlevelvbuttons] + 1 -
                          (numberofvbuttonslabels));
        }
        canvasBIG.setCursor(97, 0);
        canvasBIG.print("CC");
        canvasBIG.print(70 + sublevels[navlevelvbuttons] + 1 -
                        (numberofvbuttonslabels));
        canvasBIG.setCursor(110, 8);
        canvasBIG.print(0);

      } else {

        if (sublevels[navlevelvbuttons] >= numberofvbuttonslabels + 14 &&
            sublevels[navlevelvbuttons] < numberofvbuttonslabels + 14 + 6) {
          xcentershifter =
              97 - (((knobradius * 2) + 4) * (sublevels[navlevelvbuttons] -
                                              numberofvbuttonslabels - 14));
          canvasBIG.drawCircle(xcentershifter, 64 - 9, knobradius - 1,
                               SSD1306_WHITE);

          if (midiknobassigned[(sublevels[navlevelvbuttons] + 1 -
                                (numberofvbuttonslabels))] != 0) {
            printassignedmidi(
                midiknobassigned[(70 + sublevels[navlevelvbuttons] + 1 -
                                  (numberofvbuttonslabels))]);

          } else {
            canvasBIG.setCursor(0, 0);
            canvasBIG.print("V.Pot ");
            canvasBIG.print(sublevels[navlevelvbuttons] + 1 -
                            (numberofvbuttonslabels + 14));
          }
          canvasBIG.setCursor(97, 0);
          canvasBIG.print("CC");
          canvasBIG.print(70 + sublevels[navlevelvbuttons] + 1 -
                          (numberofvbuttonslabels));

          canvasBIG.setCursor(110, 8);
          canvasBIG.print(vPots[sublevels[navlevelvbuttons] -
                                (numberofvbuttonslabels + 14)]);
        } else {

          if (sublevels[navlevelvbuttons] >= numberofvbuttonslabels + 14 + 6 &&
              sublevels[navlevelvbuttons] <
                  numberofvbuttonslabels + 14 + 6 + 5) {

            xcentershifter = 16 + (((knobradius * 2) + 4) *
                                   (sublevels[navlevelvbuttons] -
                                    numberofvbuttonslabels - 14 - 6));
            canvasBIG.drawCircle(xcentershifter, 64 - 9 - 16, knobradius - 1,
                                 SSD1306_WHITE);
            if (midiknobassigned[(70 + sublevels[navlevelvbuttons] + 1 -
                                  (numberofvbuttonslabels))] != 0) {
              printassignedmidi(
                  midiknobassigned[(70 + sublevels[navlevelvbuttons] + 1 -
                                    (numberofvbuttonslabels))]);

            } else {
              canvasBIG.setCursor(0, 0);
              canvasBIG.print("V.Pot ");
              canvasBIG.print(sublevels[navlevelvbuttons] + 1 -
                              (numberofvbuttonslabels + 14));
            }
            canvasBIG.setCursor(97, 0);
            canvasBIG.print("CC");
            canvasBIG.print(70 + sublevels[navlevelvbuttons] + 1 -
                            (numberofvbuttonslabels));

            canvasBIG.setCursor(110, 8);
            canvasBIG.print(vPots[sublevels[navlevelvbuttons] -
                                  (numberofvbuttonslabels + 14)]);

          } else {
            if (sublevels[navlevelvbuttons] >=
                    numberofvbuttonslabels + 14 + 6 + 5 &&
                sublevels[navlevelvbuttons] <
                    numberofvbuttonslabels + 14 + 6 + 5 + 6) {

              if (midiknobassigned[(70 + sublevels[navlevelvbuttons] + 1 -
                                    (numberofvbuttonslabels))] != 0) {
                printassignedmidi(
                    midiknobassigned[(70 + sublevels[navlevelvbuttons] + 1 -
                                      (numberofvbuttonslabels))]);

              } else {
                canvasBIG.setCursor(0, 0);
                canvasBIG.print("V.Pot ");
                canvasBIG.print(sublevels[navlevelvbuttons] + 1 -
                                (numberofvbuttonslabels + 14));
              }
              canvasBIG.setCursor(97, 0);
              canvasBIG.print("CC");
              canvasBIG.print(70 + sublevels[navlevelvbuttons] + 1 -
                              (numberofvbuttonslabels));

              canvasBIG.setCursor(110, 8);
              canvasBIG.print(vPots[sublevels[navlevelvbuttons] -
                                    (numberofvbuttonslabels + 14)]);

              xcentershifter = 97 - (((knobradius * 2) + 4) *
                                     (sublevels[navlevelvbuttons] -
                                      numberofvbuttonslabels - 14 - 6 - 5));
              canvasBIG.drawCircle(xcentershifter, 16 + knobradius,
                                   knobradius - 1, SSD1306_WHITE);
            }
          }
        }
      }
    }
  }
  canvasBIG.setCursor(65, 0);
  canvasBIG.print(BPMs, 1);
}

void Vbuttonspanel() {
  actionvbuttons();
  displayonscreenbuttons();
  doposkselector();
  dodisplay();
}

void actionvbuttons() {

  if (sublevels[navlevelvbuttons] < numberofvbuttonslabels + 14) {

    if (navlevel == navlevelvbuttons) {
      navrange = numberofvbuttonslabels - 1 + 17 + 14;
    }
    if (navlevel == navlevelvbuttons + 1) {

      if (sublevels[navlevelvbuttons] < numberofvbuttonslabels) {
        int CClaval0 = 70 + (sublevels[navlevelvbuttons] + 1 + (14 + 17));
        moncontrollercc((byte)1, (byte)CClaval0, (byte)127);
        // Serial.print("sending cc ");
        // Serial.println(CClaval0);
      }

      if (sublevels[navlevelvbuttons] < numberofvbuttonslabels + 14 &&
          sublevels[navlevelvbuttons] >= numberofvbuttonslabels) {
        int CClaval =
            70 + (sublevels[navlevelvbuttons] + 1 - (numberofvbuttonslabels));
        moncontrollercc((byte)1, (byte)CClaval, (byte)127);
        // moncontrollercc( (byte)1,(byte)CClaval, (byte)0);
      }

      returntonav(navlevelvbuttons);
      // Vbuttonspanel();
    }

  } else {

    if (navlevel == navlevelvbuttons) {

      navrange = numberofvbuttonslabels - 1 + 17 + 14;
      sublevels[navlevelvbuttons + 1] =
          vPots[sublevels[navlevelvbuttons] - numberofvbuttonslabels - 14];
      sublevels[navlevelvbuttons + 2] =
          vPots[sublevels[navlevelvbuttons] - numberofvbuttonslabels - 14];
    } else {

      if (navlevel == navlevelvbuttons + 1) {

        navrange = 127;
        vPots[sublevels[navlevelvbuttons] - numberofvbuttonslabels - 14] =
            sublevels[navlevelvbuttons + 1];

        if (sublevels[navlevelvbuttons] > numberofvbuttonslabels + 14) {
          int CClaval2 =
              70 + (sublevels[navlevelvbuttons] + 1 - (numberofvbuttonslabels));
          moncontrollercc((byte)1, (byte)CClaval2,
                          (byte)(vPots[sublevels[navlevelvbuttons] -
                                       numberofvbuttonslabels - 14]));
          // moncontrollercc( (byte)1,(byte)CClaval0, (byte)0);
        }
      }
      if (navlevel >= navlevelvbuttons + 2) {
        Serial.println("Setted pot");
        vPots[sublevels[navlevelvbuttons] - numberofvbuttonslabels - 14] =
            sublevels[navlevelvbuttons + 1];
        sublevels[navlevelvbuttons + 2] = sublevels[navlevelvbuttons];
        // navlevel--;
        //   navlevel--;
        // navrange = numberofvbuttonslabels-1 +17+14 ;
        // vraipos = sublevels[navlevelvbuttons + 2];
        //  myEnc.write(sublevels[navlevelvbuttons]*4);
        returntonav(navlevelvbuttons);
        // Serial.print( "sublevels[1]= ");
        // Serial.println( sublevels[1]);
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

    coeffangle = (6.2831 - ((float)vPots[16 - i] / 127.0) * 6.2831) + 3.1416;

    // Serial.print(i);
    // Serial.print(" ");
    // Serial.print(vPots[16-i]/127.0);
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

    //  float coeffangle = ((float)vPots[6+i]/127.0)*0.05 ;
    // angleofknob = ((360.0 * coeffangle ) - 45.0 );
    coeffangle = (6.2831 - ((float)vPots[6 + i] / 127.0) * 6.2831) + 3.1416;

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

    // float coeffangle = ((float)vPots[5-i]/127.0)*0.05 ;
    coeffangle = (6.2831 - ((float)vPots[5 - i] / 127.0) * 6.2831) + 3.1416;

    trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
    trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));

    canvasBIG.drawCircle(centercirclex, centercircley, knobradius,
                         SSD1306_WHITE);

    display.drawLine(centercirclex, centercircley, trianglepointx,
                     trianglepointy, SSD1306_WHITE);
  }

  drawtransport();
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
void drawtransport() {
  // startxp= 0 ;
  int startyp = 8;
  // for (int i = 0 ; i < 8 ; i++ ) {
  int starx = 1;
  int ecart = 14;
  // canvasBIG.drawRoundRect(i*16, startyp-2, 16, 11, 2, SSD1306_WHITE);
  //}
  // cuestart
  canvasBIG.setCursor(starx + 1, startyp);
  canvasBIG.drawLine(starx + 2, startyp + 1, starx + 2, startyp + 5,
                     SSD1306_WHITE);
  canvasBIG.print(">");
  // exit
  canvasBIG.setCursor(starx + ecart * 7, startyp);
  canvasBIG.print((char)8);
  // backward
  canvasBIG.setCursor(starx + ecart * 1, startyp);
  canvasBIG.print((char)27);
  // canvasBIG.setCursor(5+48,55);
  // stop
  canvasBIG.fillRect(starx + ecart * 2, startyp + 1, 5, 5, SSD1306_WHITE);
  // play
  canvasBIG.setCursor(starx + ecart * 3, startyp);
  canvasBIG.print((char)16);
  // forward
  canvasBIG.setCursor(starx + ecart * 4, startyp);
  canvasBIG.print((char)26);
  // record
  canvasBIG.setCursor(starx + ecart * 5, startyp);
  canvasBIG.print((char)4);
  // music
  canvasBIG.setCursor(starx + ecart * 6, startyp + 1);
  canvasBIG.print((char)14);
}
