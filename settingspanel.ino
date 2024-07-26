char usnotes[12][5] = {"C",  "C#", "D",  "Eb", "E",  "F",
                       "F#", "G",  "G#", "A",  "Bb", "B"};

char eunotes[12][5] = {"Do",  "Do#", "Re",   "Mib", "Mi",  "Fa",
                       "Fa#", "Sol", "Sol#", "La",  "Sib", "Si"};
bool AudioInSource;
float freqtonotes[9 * 12] = {
    16.35, 17.32, 18.35, 19.45, 20.60, 21.83, 23.12, 24.50, 25.96, 27.50, 29.14,
    30.87, 32.70, 34.65, 36.71, 38.89, 41.20, 43.65, 46.25, 49.00, 51.91, 55.00,
    58.27, 61.74, 65.41, 69.30, 73.42, 77.78, 82.41, 87.31, 92.50, 98.00, 103.8,
    110.0, 116.5, 123.5, 130.8, 138.6, 146.8, 155.6, 164.8, 174.6, 185.0, 196.0,
    207.7, 220.0, 233.1, 246.9, 261.6, 277.2, 293.7, 311.1, 329.6, 349.2, 370.0,
    392.0, 415.3, 440.0, 466.2, 493.9, 523.3, 554.4, 587.3, 622.3, 659.3, 698.5,
    740.0, 784.0, 830.6, 880.0, 932.3, 987.8, 1047,  1109,  1175,  1245,  1319,
    1397,  1480,  1568,  1661,  1760,  1865,  1976,  2093,  2217,  2349,  2489,
    2637,  2794,  2960,  3136,  3322,  3520,  3729,  3951,  4186,  4435,  4699,
    4978,  5274,  5588,  5920,  6272,  6645,  7040,  7459,  7902};

void smixerVpanelAction() {
  if (navlevel == 3) {
    navrange = 128;
    smixervknobs[sublevels[2]] = sublevels[3];
  }
  if (navlevel == 2) {
    navrange = 15;
    sublevels[3] = smixervknobs[sublevels[2]];
  }
  if (navlevel > 3) {

    returntonav(2);
  }
}

void smixerVpanelSelector() {
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
    // canvasBIG.drawCircle(centercirclex, centercircley, knobradius-2,
    // SSD1306_WHITE);
  }
  // damp
  if (slct == 1) {

    sublevels[3] = arpegmode;
    // canvasBIG.drawCircle(centercirclex, centercircley, knobradius-2,
    // SSD1306_WHITE);
  }
  if (slct == 2) {

    sublevels[3] = arpegstartoffset;
    // canvasBIG.drawCircle(centercirclex, centercircley, knobradius-2,
    // SSD1306_WHITE);
  }
  if (slct == 3) {

    sublevels[3] = arpegnumofnotes - 1;
    // canvasBIG.drawCircle(centercirclex, centercircley, knobradius-2,
    // SSD1306_WHITE);
  }
  if (slct == 4) {

    sublevels[3] = arpeggridC;
    // canvasBIG.drawCircle(centercirclex, centercircley, knobradius-2,
    // SSD1306_WHITE);
  }
  if (slct == 5) {

    sublevels[3] = arpeggridS;
    // canvasBIG.drawCircle(centercirclex, centercircley, knobradius-2,
    // SSD1306_WHITE);
  }
  if (slct == 6) {

    sublevels[3] = arpeglengh;
    // canvasBIG.drawCircle(centercirclex, centercircley, knobradius-2,
    // SSD1306_WHITE);
  }
}

void smixerVpanel() {

  smixerVpanelAction();

  display.clearDisplay();
  canvastitle.fillScreen(SSD1306_BLACK);
  canvasBIG.fillScreen(SSD1306_BLACK);
  // canvastitle.setCursor(70,0);
  canvasBIG.setTextSize(1);
  canvasBIG.setCursor(0, 0);
  canvasBIG.print(smixervknobs[sublevels[2]]);

  byte centercirclex;
  byte centercircley;
  byte xcentershifter;
  byte knobradius = 6;
  byte trianglepointx;
  byte trianglepointy;
  byte yshifter = 46;
  float coeffangle;
  xcentershifter = (knobradius * 2) + 4;
  byte slct = sublevels[2];

  for (int i = 0; i < 8; i++) {

    coeffangle = (6.2831 - (smixervknobs[i] / 128.0) * 6.2831) + 3.1416;
    centercirclex = knobradius + (xcentershifter * i);
    centercircley = 16 + knobradius;
    canvastitle.setCursor(centercirclex - 5 + 3, 8);
    canvastitle.setTextSize(1);

    canvastitle.print(i + 1);
    // canvastitle.print((char)masterfulllabels[i][2]);

    canvasBIG.drawCircle(centercirclex, centercircley, knobradius,
                         SSD1306_WHITE);

    trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
    trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));

    display.drawLine(centercirclex, centercircley, trianglepointx,
                     trianglepointy, SSD1306_WHITE);
  }

  if (slct < 8) {
    centercirclex = knobradius + (xcentershifter * slct);
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2,
                         SSD1306_WHITE);
    canvastitle.setCursor(95, 0);
    canvastitle.print((smixervknobs[slct] / 128.0) * 100.0, 1);
  }
  centercircley = yshifter + knobradius;
  for (int i = 0; i < 8; i++) {

    coeffangle = (6.2831 - (smixervknobs[i + 8] / 128.0) * 6.2831) + 3.1416;
    centercirclex = knobradius + (xcentershifter * i);
    canvasBIG.setCursor(centercirclex - 5,
                        centercircley - (2 + knobradius * 2) - 1);

    // canvastitle.setCursor(centercirclex-5,8);
    canvasBIG.setTextSize(1);

    canvasBIG.print(i + 1 + 8);
    // canvastitle.print((char)masterfulllabels[i][2]);

    canvasBIG.drawCircle(centercirclex, centercircley, knobradius,
                         SSD1306_WHITE);

    trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
    trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));

    display.drawLine(centercirclex, centercircley, trianglepointx,
                     trianglepointy, SSD1306_WHITE);
  }

  if (slct > 7) {
    centercirclex = knobradius + (xcentershifter * (slct - 8));
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2,
                         SSD1306_WHITE);
    canvastitle.setCursor(95, 0);
    canvastitle.print((smixervknobs[slct] / 128.0) * 100.0, 1);
  }

  // smixerVpanelSelector();
  dodisplay();
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
void printlanote() {
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
    lanotenumber = getnotefromfreq(notep);
    canvastitle.setTextSize(1);
    canvastitle.print(" Hz");
    canvasBIG.setTextSize(2);
    canvasBIG.setCursor(0, 16);

    canvasBIG.print((char *)usnotes[(lanotenumber % 12)]);
    canvasBIG.print(int(lanotenumber / 12.0));
    canvasBIG.print(" (");
    canvasBIG.print((char *)eunotes[(lanotenumber % 12)]);
    canvasBIG.print(int(lanotenumber / 12.0));
    canvasBIG.print(")");
    canvasBIG.setTextSize(1);
    canvasBIG.setCursor(0, 16 + 16);
    canvasBIG.print(probz * 100.0);
    canvasBIG.print("% ");

    dodisplay();
  }
}
void notefreqloop() {
  if (notefreq1.available()) {
    float notep = notefreq1.read();
    float probz = notefreq1.probability();
    Serial.printf("Note: %3.2f | Probability: %.2f\n", notep, probz);
    //  pseudoconsole("Note: %3.2f | Probability: %.2f\n", notep, probz);
  }
}

void arpegiatorVpanelAction() {
   if (navlevel == 3) {
    // AudioNoInterrupts();
    byte slct = (byte)sublevels[2];
    // fq

    if (slct == 0) {
      navrange = 8;
      arpegiatortype = sublevels[3];
      // arpegiatortype = sublevels[2];
      if (arpegiatortype < 8) {
        arpegiatorOn = 1;
        metro0.reset();
      } else {
        arpegiatorOn = 0;
        for (int i = 0; i < nombreofliners; i++) {
          calledarpegenote[i][0] = 0;
          calledarpegenote[i][1] = 0;
          for (int j = 0; j < nombreofliners; j++) {
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

void arpegiatorVpanelSelector() {
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

void arpegiatorVpanel() {

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
  char lesarpegestype[8][12] = {"Ionian",     "Dorian",  "Phrygian", "Lydian",
                                "Mixolydian", "Aeolian", "Harmonic", "Locrian"};
  display.clearDisplay();
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(1);
  canvastitle.print("Arpegiator ");
  if (arpegiatortype < 8) {
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
    // barsize = round(((WetMixMasters[lefilter])*(totbartall-4))) ;
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

char onboards[all_buttonns][8] = {
    "Pot 1",  "Pot 2",  "Pot 3",  "Pot 4",  "Pot 5",  "Pot 6",  "Pot 7",
    "Pot 8",  "Pot 9",  "Fdr 01", "Fdr 02", "Fdr 03", "Pad 01", "Pad 02",
    "Pad 03", "Pad 04", "Pad 05", "Pad 06", "Pad 07", "Pad 08", "Pad 09",
    "Pad 10", "Pad 11", "Pad 12", "Pad 13", "Pad 14", "Pad 15", "Pad 16",
    "But 01", "But 02", "But 03", "But 04", "But 05", "But 06", "But 07",
    "But 08", "But 09", "But 10", "But 11", "But 12", "But 13", "But 14",
    "But 15", "But 16", "But 17", "But 18", "Cfd",    "Jk X",   "Jk Y"};

char ch_lbl_buffer[4]; // Buffer to hold formatted number

void OnBoardVpanelAction() {
  if (navlevel > 3) {
    if (((sublevels[2] <= 11) || (sublevels[2] > 45)) && (navlevel == 4)) {
      Serial.print("index=");
      Serial.println(potsboards[sublevels[2]]);
      muxed_pots[potsboards[sublevels[2]]] = pot_assignements[sublevels[2]];
      Serial.print("muxed_pots ");
      Serial.println(muxed_pots[potsboards[sublevels[2]]]);
    }
    returntonav(2);
  }
}

void OnBoardVpanelSelector() {

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
  sprintf(ch_lbl_buffer, "%02d", but_channel[sublevels[2]]);
  canvasBIG.print(ch_lbl_buffer);

  if (navlevel == 3) {
    sublevels[4] = pot_assignements[sublevels[2]];
    pot_assignements[sublevels[2]] = sublevels[3];
    Serial.print("setting pot ");
    Serial.print(sublevels[2]);
    Serial.print(" to ");
    Serial.println(sublevels[3]);
    if (selecta <= 11) {
      navrange = 128;
    }

    if ((selecta > 11) && (selecta <= 45)) {
      navrange = 128 + 127;
    }
    if (selecta > 45) {
      navrange = 128;
    }
  }

  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(1);
  canvastitle.print(onboards[selecta]);

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

void OnBoardVpanel() {

  OnBoardVpanelAction();
  display.clearDisplay();
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.fillScreen(SSD1306_BLACK);

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

void displaysettingspanel() {

  if (navlevel > 2 && sublevels[1] != 8 && sublevels[1] != 11) {
    if (sublevels[1] == 2 || sublevels[1] == 3 || sublevels[1] == 5 ||
        sublevels[1] == 6 || sublevels[1] == 7) {
      returntonav(1);
    }
    makesettingslist();
    dodisplay();
  }
  if (navlevel == 1) {
    reinitsublevels(2);
    debugmidion = 0;
    noteprint = 0;
    navrange = numbofsettinglabels - 1;
    makesettingslist();
    dodisplay();
  }
  // 2 lines have need this exception for settings menu, find the 2nd
  if (navlevel == 2 && sublevels[1] != 8 && sublevels[1] != 11) {
    // navrange = 2 ;

    switch (sublevels[1]) {

    case 0:
      debugmidion = 1;

      break;

    case 1:
      freezemidicc = !freezemidicc;
      navlevel--;
      break;

    case 2:
      navrange = 16;

      synthmidichannel = (byte)sublevels[2];
      // setuphubusb();
      break;

    case 3:
      navrange = 16;
      samplermidichannel = sublevels[2];

      break;

    case 4:
      digitalplay = !digitalplay;
      navlevel--;
      break;

    case 5:
      navrange = 128;
      tapnote = byte(sublevels[2]);
      // navlevel--;
      break;

    case 6:
      navrange = 190;

      millitickinterval = sublevels[2] + 60;
      setbpms();
      // navlevel--;
      break;
    case 7:
      navrange = 6;

      lasetchord = sublevels[2];
      if (lasetchord < 6) {
        chordson = 1;
      } else {
        chordson = 0;
      }
      // navlevel--;
      break;
    // no case for 8 or 11

    // navlevel--;
    case 9:
      // navrange = 8 ;
      externalticker = !externalticker;
      returntonav(1);
      // navlevel--;
      break;
    case 10:
      // navrange = 8 ;
      noteprint = 1;
      // returntonav(1);
      // navlevel--;
      break;

    case 12:
      // navrange = 8 ;
      AudioInSource = !AudioInSource;
      if (AudioInSource) {
        audioShield.inputSelect(AUDIO_INPUT_MIC);
      } else {
        audioShield.inputSelect(AUDIO_INPUT_LINEIN);
      }
      returntonav(1);
      // navlevel--;
      break;

    case 13:

      SendMidiOut = !SendMidiOut;
      returntonav(1);
      // navlevel--;
      break;

    default:
      break;
    }
    makesettingslist();
    dodisplay();
  }

  if (navlevel >= 2 && sublevels[1] == 8) {
    arpegiatorVpanel();
    dodisplay();
  }
  if (navlevel >= 2 && sublevels[1] == 11) {
    OnBoardVpanel();
    dodisplay();
  }
}

void makesettingslist() {
  char chordslabels[7][12] = {"Major", "Minor", "Diminished", "Augmented",
                              "Sus2",  "Sus4",  "None"};
  char midichlist[17][4] = {"All", "1",  "2",  "3",  "4",  "5",  "6",  "7", "8",
                            "9",   "10", "11", "12", "13", "14", "15", "16"};
  char displaysettingslabels[numbofsettinglabels][24] = {"Echo Midi",
                                                         "Freeze midi CC",
                                                         "Synth midi ch",
                                                         "Sampler midi ch",
                                                         "Sampler analog touch",
                                                         "Set Tap note",
                                                         "Tempo",
                                                         "Chorus",
                                                         "Arpegiator",
                                                         "Ext. Midiclock",
                                                         "Note Spy",
                                                         "OnBoard Knobs",
                                                         "Audio Source",
                                                         "Midi Out"};
  display.clearDisplay();
  canvasBIG.fillScreen(SSD1306_BLACK);
  int startx = 0;
  int starty = 16;
  char *textin = (char *)displaysettingslabels[sublevels[1]];

  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);

  canvastitle.setTextSize(1);

  canvastitle.println(textin);

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
  if (sublevels[1] == 5) {
    canvastitle.setCursor(96, 0);
    canvastitle.println(int(tapnote));
    sublevels[2] = int(tapnote);
  }
  if (sublevels[1] == 6) {
    canvastitle.setCursor(96, 0);
    canvastitle.println(BPMs, 1);
    sublevels[2] = millitickinterval;
  }
  if (sublevels[1] == 7) {
    // canvastitle.setCursor(96,0);
    // canvastitle.println(BPMs,1);

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
    if (AudioInSource) {
      canvastitle.println("Mic");
    } else {
      canvastitle.println("Line");
    }
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

  for (int filer = 0; filer < numbofsettinglabels - 1 - (sublevels[1]);
       filer++) {

    canvasBIG.setCursor(startx, starty + ((filer)*10));
    canvasBIG.println(displaysettingslabels[sublevels[1] + 1 + filer]);
  }
  for (int filer = 0; filer < sublevels[1]; filer++) {

    canvasBIG.setCursor(
        startx, (10 * (numbofsettinglabels - sublevels[1]) + 6 + ((filer)*10)));
    canvasBIG.println(displaysettingslabels[filer]);
  }
}
