void displayLFOpanel(int lesynth) {
  sublevels[0] = 1;
  sublevels[1] = lesynth;
  sublevels[2] = 0;
  navrange = sizeofLFOlabels - 1;
  navlevel = 2;
  LFOlining(lesynth);
  // type
  // amplitude
  // offset
  // phase
  // sync
}

void LFOmenu() {
  //  if (navlevel == 1) {
  //  selectbox(500,170, wavesbg , (char*)"\0" );

  //  dodisplay();
  //  }

  if (navlevel == 1) {
    reinitsublevels(2);
    navrange = synths_count - 1;
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
  if (navlevel > 1) {
    LFOlining(sublevels[1]);
  }
}

void printLFObanner(int startx, int starty, int leLFO) {
  display.fillRect(startx, starty, 64, 24, SSD1306_INVERSE);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("LFO ");
  display.setCursor(116, 0);
  display.print(leLFO);
  // display.println(leLFO);
  display.display();
}

void LFOlineBG() {
  display.clearDisplay();
  display.drawBitmap(0, 64 - 47, wavesbg2, 128, 47, SSD1306_WHITE);

  display.display();
}

void LFOmenuBG(int leLFO) {
  canvasBIG.setTextSize(1); // Draw 2X-scale text
  canvasBIG.setCursor(122, 58);
  canvasBIG.print(leLFO + 1);
  canvasBIG.setTextSize(1);
}

void applyLFOrmicon(int lesinthy) {
  // displaywaveformicon(sublevels[4],(char*)"SineWave",sinewave, lesynthi,
  // WAVEFORM_SINE);
  if (navlevel > 3) {
    // Serial.println("Setting TYPE");
    LFOformstype[lesinthy] = sublevels[3];

    if (navlevel >= 4) {
      returntonav(2, 9);
    }
  }
}

void LFOrmType(int leLFO) {
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
    restartLFO(leLFO);
    gobacktolfoparams();
  }
}

void restartLFO(int leLFO) {
  AudioNoInterrupts() ;
  if (LFOsync[leLFO]) {
    // lfosinez[leLFO]->frequency(((LFOfreqs[leLFO]/100.0)*(1000/millitickinterval)));
    LFOwaveforms1[leLFO]->begin(
        (float)(LFOlevel[leLFO] / 512.00),
        ((LFOfreqs[leLFO] / 100.0) * (1000 / millitickinterval)),
        lesformes[LFOformstype[leLFO]]);
  } else {
    LFOwaveforms1[leLFO]->begin((float)(LFOlevel[leLFO] / 512.00),
                                (LFOfreqs[leLFO] / 100.0) * 0.5,
                                lesformes[LFOformstype[leLFO]]);
    // lfosinez[leLFO]->frequency((LFOfreqs[leLFO]/100.0)*0.5);
  }
 
  
  if (LFOformstype[leLFO] == 7 ) {
    LFOwaveforms1[leLFO]->arbitraryWaveform(arbitrary_waveforms[leLFO],1.0);
  }
  // lfosinez[leLFO]->amplitude((LFOlevel[leLFO]/127.0)*0.5);

  AudioInterrupts() ;
}
void displayLFOrmimg(int letype, char *lelabelw, const unsigned char img[],int leLFO, typeof(WAVEFORM_SINE) wavetype) {

  canvasBIG.drawBitmap(70, 20, img, 32, 32, SSD1306_WHITE);
  canvastitle.setTextSize(1); // Draw 1X-scale text
  canvastitle.setTextColor(SSD1306_WHITE);
  canvastitle.setCursor(64, 8);
  canvastitle.println(lelabelw);
  // dodisplay();
}

void syncLFO(int leLFO) {
  //  if ( LFOsync[leLFO] ) {
  //         LFOfreqs[leLFO] = (1.0/(BPMs/4.0))*1000.0;
  //         Serial.println(LFOfreqs[leLFO]);
  restartLFO(leLFO);
  //  } else {
  //    LFOfreqs[leLFO] = 1 ;
  //  }
}
void doLFObool(int leLFO) {

  // dolistLFOparams();
  // dodisplay();

  if (navlevel >= 3) {
    //  Serial.println("Setting Sync switch");
    LFOsync[leLFO] = !LFOsync[leLFO];
    syncLFO(leLFO);
    returntonav(2);
  }
  display.setCursor(55, 0);

  display.setTextSize(2);

  if (LFOsync[leLFO]) {

    display.print("Active");
  } else {
    display.print("Off");
  }

  display.display();
}
void gobacktolfoparams() { returntonav(2); }

void doLFOparamdisplayval(int laval) {
  canvastitle.setCursor(80, 0);
  canvastitle.setTextSize(2);
  canvastitle.print(laval);
  // dodisplay();
  //   canvastitle.display();
}
void doFloatLFOparamdisplayval(float laval) {
  canvastitle.setCursor(80, 0);
  canvastitle.setTextSize(2);
  canvastitle.print(laval);
  // dodisplay();
  //   canvastitle.display();
}
void doLFOlevel(int leLFO) {
  if (navlevel == 3) {
    // Serial.println("Setting LFO level");
    navrange = 512;
    LFOlevel[leLFO] = sublevels[3];
    // restartLFO(leLFO);
  } else {
    sublevels[3] = LFOlevel[leLFO];
  }
  if (navlevel >= 4) {
    gobacktolfoparams();
  }
  doFloatLFOparamdisplayval(LFOlevel[leLFO] / 512.0);
}

void doLFOoffset(int leLFO) {
  if (navlevel == 3) {
    //  Serial.println(((50-LFOoffset[leLFO])/50));
    navrange = 100;
    LFOoffset[leLFO] = sublevels[3];
    doLFOallcontrols(leLFO);
    // restartLFO(leLFO);
  } else {
    sublevels[3] = LFOoffset[leLFO];
  }
  if (navlevel >= 4) {
    gobacktolfoparams();
  }
  doFloatLFOparamdisplayval(((50.0 - LFOoffset[leLFO]) / 50.0));
}

void doLFOphase(int leLFO) {
  if (navlevel == 3) {
    // Serial.println("Setting LFO phase");
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
void doLFOfreqd(int leLFO) {
  // set lfosine1 lfosinez[leLFO]->
  if (navlevel == 3) {
    // Serial.println("Setting LFO freq");
    navrange = 100;
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
void dolistLFOparams() {
  char LFOlabels[sizeofLFOlabels][12] = {"Type",  "Level",  "Sync",
                                         "Freq",  "Offset", "Phase",
                                         "Synth", "<-  ",   "  ->"};
  display.clearDisplay();
  int startx = 5;
  int starty = 16;
  char *textin = (char *)LFOlabels[sublevels[2]];

  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);

  canvastitle.setTextSize(2);

  canvastitle.println(textin);

  canvasBIG.setTextSize(1);

  canvasBIG.fillScreen(SSD1306_BLACK);

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
void doLFOallcontrols(byte leLFO) {
  restartLFO(leLFO);
  LFOwaveforms1[leLFO]->phase(0.36 * LFOphase[leLFO]);
  LFOwaveforms1[leLFO]->offset((float)(((50.0 - LFOoffset[leLFO]) / 50.0)));
}
void LFOlining(int leLFO) {
  // LFOmenuroot is 2

  dolistLFOparams();
  //  if (navlevel >= LFOmenuroot) {
  if (navlevel >= LFOmenuroot) {
    navrange = sizeofLFOlabels - 1;

    if (sublevels[2] == 0) {
      
      LFOrmType(leLFO);
    }

    if (sublevels[2] == 1) {
      doLFOlevel(leLFO);
    }

    if (sublevels[2] == 2) {
      doLFObool(leLFO);
    }

    if (sublevels[2] == 3) {
      doLFOfreqd(leLFO);
    }

    if (sublevels[2] == 4) {
      doLFOoffset(leLFO);
    }

    if (sublevels[2] == 5) {
      doLFOphase(leLFO);
    }

    if (sublevels[2] == 6) {
      if (navlevel >= 3) {
        // go to synth
        sublevels[0] = 0;
        sublevels[2] = sublevels[1];
        wavelinepanel(sublevels[2]);
      }
    }
    if (sublevels[2] == 7) {
      if (navlevel >= 3) {
        // Serial.print("Previous");
        if (leLFO > 0) {
          sublevels[1]--;
        } else {
          sublevels[1] = 3;
        }
        navlevel--;
        // Serial.println("back to menu");
        lemenuroot();
      }
    }
    if (sublevels[2] == 8) {
      if (navlevel >= 3) {
        if (leLFO < 3) {
          sublevels[1]++;
        } else {
          sublevels[1] = 0;
        }

        navlevel--;
        lemenuroot();
      }
    }
    LFOmenuBG(leLFO);
    dodisplay();
  }
}
