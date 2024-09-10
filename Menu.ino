
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

void show_pots_to_assign() {
  if (sublevels[1] == 0 ) {
    returntonav(1);
  } else {
    display.clearDisplay();
    canvastitle.fillScreen(SSD1306_BLACK);
    canvasBIG.fillScreen(SSD1306_BLACK);
    canvastitle.setCursor(0, 0);
    canvastitle.setTextSize(2);
    canvastitle.println(ControlList[sublevels[1]]);
    canvasBIG.setTextSize(2);
    canvasBIG.setCursor(0, 40);
    if (sublevels[2] != 0) {
      canvasBIG.print("Midi");
      canvasBIG.setTextSize(1);
      canvasBIG.setCursor(50, 47);
      canvasBIG.print("(cc)");
      canvasBIG.setCursor(71, 39);
      canvasBIG.setTextSize(3);
      canvasBIG.print(":");
      canvasBIG.setTextSize(2);
      canvasBIG.setCursor(85, 40);
      canvasBIG.print(sublevels[2]);
    } else {
      //canvasBIG.setTextSize(1);
      canvasBIG.println("Unassigned");
    }
  }
}

void knobsettermidi() { 
  midiknobassigned[find_assigned_knob(sublevels[1])] = 0;
  midiknobassigned[sublevels[2]] = sublevels[1]; 
}

int find_assigned_knob(int k){
  for (int i = 0; i < 128; i++) {
    if (midiknobassigned[i] == k){
      return i;
    }
  }
  return 0 ;
}

void learn_midi(byte captured){
  midiknobassigned[find_assigned_knob(sublevels[1])] = 0;
  sublevels[2] = captured ;
  midiknobassigned[sublevels[2]] = sublevels[1];
  returntonav(1);
}

void show_avalable_controls() {
  display.clearDisplay();
  canvastitle.fillScreen(SSD1306_BLACK);
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  if (sublevels[1] != 0) {
    canvastitle.setTextSize(2);
    canvastitle.println(ControlList[sublevels[1]]);
    canvasBIG.setTextSize(2);
    canvasBIG.setCursor(0, 40);
    sublevels[2] = find_assigned_knob(sublevels[1]) ;
    if (sublevels[2] != 0) {
      canvasBIG.print("Midi");
      canvasBIG.setTextSize(1);
      canvasBIG.setCursor(50, 47);
      canvasBIG.print("(cc)");
      canvasBIG.setCursor(71, 39);
      canvasBIG.setTextSize(3);
      canvasBIG.print(":");
      canvasBIG.setTextSize(2);
      canvasBIG.setCursor(85, 40);
      
      canvasBIG.print(sublevels[2]);
    } else {
      //canvasBIG.setTextSize(1);
      canvasBIG.println("Unassigned");
    }
  } else {
    canvastitle.setTextSize(2);
    canvastitle.println("Select");
    canvasBIG.setTextSize(2);
    canvasBIG.setCursor(0, 28);
    canvasBIG.println("Control");
  }
}
void knobassigner() {
  if (navlevel == 2) {
    navrange = 127;
    //reinitsublevels(2);
    show_pots_to_assign();
    dodisplay();
  }
  if (navlevel == 1) {
    navrange = allfxes-1;
    show_avalable_controls();
    dodisplay();
  }
  if (navlevel >= 3) {
    knobsettermidi();
    returntonav(1);
  }
}
