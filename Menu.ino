
void reinitsublevels(byte fromlei) {
  for (byte i = fromlei; i < 7; i++) {
    sublevels[i] = 0;
  }
}

void lemenuroot() {
  if (navlevel == 0) {
    displaymenu();
  }
  if (navlevel > 0) {
    switch (sublevels[0]) {
    case 0:
      if (navlevel >= 1) {
        if (navlevel == 1) {
          navrange = 4;
        }
        synthmenu();
      }
      break;
    case 1:

      if (navlevel >= 1) {
        if (navlevel == 1) {
          navrange = numberofsynthsw-1;
        }
        LFOmenu();
      }
      break;
    case 2:

      if (navlevel >= 1) {
        navrange = 128 + 3;
        knobassigner();
      }
      break;
    case 3:

      if (navlevel >= 1) {
        displaySongmenu();
      }
      break;
    case 4:

      if (navlevel >= 1) {
        navrange = sizeofpatternlistlabels - 1;
        displayPatternmenu();
      }

      break;
    case 5:

      if (navlevel >= 1) {

        displaysettingspanel();
      }

      break;
    case 6:

      if (navlevel >= 1) {

        MainFxPanel();
      }
      break;
    case 7:

      if (navlevel >= 1) {
        displaysamplermenu();
      }
      break;
    case 8:

      if (navlevel >= 1) {
        // Vbuttonspanel() -> move to settings.
        displaywaveformsmenu();
      }
      break;
    case 9:

      if (navlevel >= 1) {
        navrange = 4;
        displaypresetmenu();
      }
      break;

    default:
      // Serial.println("Invalid" );
      break;
    }
  }
}

void displaymenu() {

  if (navlevel == 0) {
    previousnavlevel = 0;
    navrange = 9;
    rotamode = 1;
    plusminusmode = 0;
    displayleBGimg(menuBG);
  }

  switch (sublevels[0]) {
  case 0:
    toprint = (char *)"WaveSynth";
    selectbox(5, 17);
    break;
  case 1:
    toprint = (char *)"LFOs";
    selectbox(29, 17);
    break;
  case 2:
    toprint = (char *)"Set Knobs";
    selectbox(53, 17);
    break;
  case 3:
    toprint = (char *)"Song";
    selectbox(77, 17);
    break;
  case 4:
    toprint = (char *)"Pattern";
    selectbox(101, 17);
    break;
  case 5:
    toprint = (char *)"Settings";
    selectbox(5, 41);
    break;
  case 6:
    toprint = (char *)"MainFX";
    selectbox(29, 41);
    break;
  case 7:
    toprint = (char *)"Sampler";
    selectbox(53, 41);
    break;
  case 8:
    toprint = (char *)"Waveformer";
    selectbox(77, 41);
    break;
  case 9:
    toprint = (char *)"Presets";
    selectbox(101, 41);
    break;

  default:
    // Serial.println("Invalid");
    break;
  }
  printlabel(toprint);
  display.display();
}

void listknobassigner() {

  display.clearDisplay();
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  toprint = (char *)"Knob";
  canvastitle.setTextSize(2);

  canvastitle.println(toprint);
  canvastitle.setCursor(85, 0);
  // toprint = (char*)"Knob";
  canvastitle.println(sublevels[1]);

  canvasBIG.fillScreen(SSD1306_BLACK);
 
    // Serial.println(sublevels[1]);
    if (midiknobassigned[sublevels[1]] != 0) {

      canvasBIG.setTextSize(1);
      canvasBIG.setCursor(85, 16);
      canvasBIG.println(midiknobassigned[sublevels[1]]);
      canvasBIG.setCursor(0, 40);
      canvasBIG.println(ControlList[midiknobassigned[sublevels[1]]]);
    }
  
}
void knobsettermidi() { midiknobassigned[sublevels[1]] = sublevels[2]; }

void listknobassigner2() {

  display.clearDisplay();
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  toprint = (char *)"Knob";
  canvastitle.setTextSize(2);

  canvastitle.println(toprint);
  canvastitle.setCursor(85, 0);
  // toprint = (char*)"Knob";
  canvastitle.println(sublevels[1]);

  canvasBIG.fillScreen(SSD1306_BLACK);

  canvasBIG.setTextSize(1);
  canvasBIG.setCursor(85, 16);
  canvasBIG.println(sublevels[2]);
  canvasBIG.setCursor(0, 40);
  canvasBIG.println(ControlList[sublevels[2]]);
}
void knobassigner() {
  if (navlevel == 1) {
    navrange = 128-1;
    reinitsublevels(2);
    listknobassigner();
    dodisplay();
  }
  if (navlevel == 2) {
    navrange = allfxes-1;
    listknobassigner2();
    dodisplay();
  }
  if (navlevel == 3) {
    
      knobsettermidi();
    
    returntonav(1);
  }
}
