
void displaypanbars(int score) {
  if (navlevel >= 4) {
    if (navlevel == 4) {
      navrange = 20;
      //        int lepan = round(map(sublevels[4],0,1,0,19));
      // setpanlevel(0,lepan);
      setpanlevel(sublevels[2], sublevels[4]);
      // Serial.println(panLs[sublevels[2]]);
      //   Serial.println(panLs[sublevels[2]]);
    }
    if (navlevel >= 5) {
      // Serial.println("nav = 5 panned");
      setpanlevel(sublevels[2], sublevels[4]);
      returntonav(3, 9);

      // lemenuroot();
    }
  }
  int sizepan = map(score, 0, 2, 0, 35);
  wavelinemenuBG(sublevels[2]);
  dolistwavelineparams();
  dodisplay();
  display.drawRect(45, 16, 7, 35, SSD1306_WHITE);
  display.drawRect(57, 16, 7, 35, SSD1306_WHITE);
  display.fillRect(45, 64 - sizepan - 13, 7, sizepan, SSD1306_WHITE);
  display.fillRect(57, 64 - sizepan - 13, 7, sizepan, SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(80, 0);
  display.println(panLs[sublevels[2]]);
  display.display();
}

void displayoffsetwav(int synthi) {
  if (navlevel == 4) {
    navrange = 128;
    wave1offset[synthi] = sublevels[4];

    for (int i = 0; i < nombreofliners; i++) {
      waveforms1[i + (synthi * nombreofliners)]->offset(
          (float)(((64.0 - wave1offset[synthi]) / 64.0)));
      FMwaveforms1[i + (synthi * nombreofliners)]->offset(
          (float)(((64.0 - wave1offset[synthi]) / 64.0)));
    }
  }

  if (navlevel >= 5) {
    returntonav(3, 9);
  }

  //       sizefreq = map(score,0,128,0,35);
  //         wavelinemenuBG(sublevels[2]);
  //        dolistwavelineparams();
  //          dodisplay();
  //        display.drawRect(45, 16, 7, 35, SSD1306_WHITE);
  //        display.drawRect(57, 16, 7, 35, SSD1306_WHITE);
  //        display.fillRect(45, 64-sizefreq-13, 7, sizefreq, SSD1306_WHITE);
  //        display.fillRect(57, 64-sizefreq-13, 7, sizefreq, SSD1306_WHITE);
  //          display.setTextSize(2);
  wavelinemenuBG(sublevels[2]);
  dolistwavelineparams();
  dodisplay();
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setTextSize(2);
  canvastitle.setCursor(75, 0);
  canvastitle.print((float)(((64.0 - wave1offset[synthi]) / 64.0)));
  dodisplay();
}

void displayfreqbars(int score) {
  // weird but usefull behavior to switch encoder resolution between 0 and 1
  if (navlevel >= 4) {

    if (navlevel == 4) {
      navrange = 10;
      if (wavesfreqs[sublevels[2]] == 1) {
        demimalmode = !demimalmode;
      } else {
        if (wavesfreqs[sublevels[2]] <= 1) {
          demimalmode = 1;
        }
      }
      if (!demimalmode) {
        wavesfreqs[sublevels[2]] = sublevels[4];
      }
      if (demimalmode) {
        wavesfreqs[sublevels[2]] = (sublevels[4]) / 10.0;
      }

      // Serial.println("nav = 4 freq");
    }
    if (navlevel >= 5) {
      // Serial.println("nav = 5 freq");
      // wavesfreqs[sublevels[2]] = sublevels[4] ;

      if (demimalmode) {
        wavesfreqs[sublevels[2]] = (sublevels[4]) / 10.0;
      }

      if (!demimalmode) {
        wavesfreqs[sublevels[2]] = sublevels[4];
      }
      returntonav(3, 9);
    }
  }
  
  wavelinemenuBG(sublevels[2]);
  dolistwavelineparams();
  dodisplay();
  //        display.drawRect(45, 16, 7, 35, SSD1306_WHITE);
  //        display.drawRect(57, 16, 7, 35, SSD1306_WHITE);
  //        display.fillRect(45, 64-sizefreq-13, 7, sizefreq, SSD1306_WHITE);
  //        display.fillRect(57, 64-sizefreq-13, 7, sizefreq, SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(65, 0);
  display.println(wavesfreqs[sublevels[2]]);
  display.display();
}

void displayphasebars(int score) {

  if (navlevel >= 4) {
    if (navlevel == 4) {

      navrange = 360;
      phaselevelsL[sublevels[2]] = int(sublevels[4]);

      setphaselevel(sublevels[2]);
      // Serial.println("nav = 4 phase");
    }
    if (navlevel >= 5) {
      setphaselevel(sublevels[2]);

      returntonav(3, 9);
    }
  }

  // int sizephase = map(score,0,360,0,35);
  wavelinemenuBG(sublevels[2]);
  dolistwavelineparams();
  dodisplay();
  //    display.drawRect(45, 16, 7, 35, SSD1306_WHITE);
  //    display.drawRect(57, 16, 7, 35, SSD1306_WHITE);
  //    display.fillRect(45, 64-sizephase-13, 7, sizephase, SSD1306_WHITE);
  //    display.fillRect(57, 64-sizephase-13, 7, sizephase, SSD1306_WHITE);
  display.setCursor(80, 0);
  display.setTextSize(2);
  display.println(phaselevelsL[sublevels[2]]);
  display.display();
}

void displayModulatedbool(int lesynthb) {
  wavelinemenuBG(lesynthb);
  dolistwavelineparams();
  dodisplay();
  display.setCursor(110, 0);
  display.setTextSize(2);
  display.println(FMmodulated[lesynthb]);

  display.display();
}

void setfmtophase(byte lesynth) {
  for (byte i = 0; i < nombreofliners; i++) {
    FMwaveforms1[i + (lesynth * nombreofliners)]->phaseModulation(180);
  }
}

void setfmtofreq(byte lesynth) {
  for (byte i = 0; i < nombreofliners; i++) {
    FMwaveforms1[i + (lesynth * nombreofliners)]->frequencyModulation(10);
  }
}

void wavelineModulatedbool(int lesynthi) {
  if (navlevel == 4) {
    navrange = 2;
    // Serial.println("Setting Mdulation switch");
    FMmodulated[lesynthi] = sublevels[4];
  }
  if (navlevel > 4) {
    if (FMmodulated[lesynthi] == 1) {
      setfmtofreq(lesynthi);
    }
    if (FMmodulated[lesynthi] == 2) {
      setfmtophase(lesynthi);
    }
    setwavetypefromlist(lesynthi, Waveformstyped[lesynthi]);
    returntonav(3);
  }
  displayModulatedbool(lesynthi);
}

void wavelinePhase(int lesynthi) { displayphasebars(phaselevelsL[lesynthi]); }

void wavelineFreq(int lesynthi) { displayfreqbars(wavesfreqs[lesynthi]); }

void wavelinePan(int lesynthi) { displaypanbars(panLs[lesynthi]); }

void wavelineoffset(int lesynthi) {
  // displayoffsetwav(sublevels[4]);
  displayoffsetwav(lesynthi);
}

void displaywaveformicon(int letype, char *lelabelw, const unsigned char img[],
                         int lesinthy, typeof(WAVEFORM_SINE) wavetype) {

  wavelinemenuBG(sublevels[2]);
  dolistwavelineparams();
  dodisplay();
  display.drawBitmap(74, 20, img, 32, 32, SSD1306_WHITE);
  display.setTextSize(1); // Draw 1X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(64, 0);
  dolistwavelineparams();
  dodisplay();
  display.println(lelabelw);
  display.display();
  if (navlevel == 4) {
    navrange = 11;
    // Serial.println("Setting TYPE");
    Waveformstyped[lesinthy] = sublevels[4];
  }

  if (navlevel > 4) {
    setwavetypefromlist(lesinthy, Waveformstyped[lesinthy]);
    if (Waveformstyped[lesinthy] == 11) {
      mixlevelsL[lesinthy] = 0.0;
      setwavemixlevel(lesinthy);
    }
    returntonav(3, 7);
  }
}

void wavelineType(int lesynthi) {

  switch (sublevels[4]) {
  case 0:
    displaywaveformicon(sublevels[4], (char *)"SineWave", sinewave, lesynthi,
                        WAVEFORM_SINE);
    break;
  case 1:
    displaywaveformicon(sublevels[4], (char *)"SawWave", sawtoothwave, lesynthi,
                        WAVEFORM_SAWTOOTH);
    break;
  case 2:
    displaywaveformicon(sublevels[4], (char *)"ReverseSaw", reversesawtoothwave,
                        lesynthi, WAVEFORM_SAWTOOTH_REVERSE);
    break;
  case 3:
    displaywaveformicon(sublevels[4], (char *)"Triangle", trianglewave,
                        lesynthi, WAVEFORM_TRIANGLE);
    break;
  case 4:
    displaywaveformicon(sublevels[4], (char *)"V-Triangle", variabletriangle,
                        lesynthi, WAVEFORM_TRIANGLE_VARIABLE);
    break;
  case 5:
    displaywaveformicon(sublevels[4], (char *)"SquareWave", squarewave,
                        lesynthi, WAVEFORM_SQUARE);
    break;
  case 6:
    displaywaveformicon(sublevels[4], (char *)"PulseWave", pulsewave, lesynthi,
                        WAVEFORM_PULSE);
    break;
  case 7:
    displaywaveformicon(sublevels[4], (char *)"Arbitrary", arbitrarywave,
                        lesynthi, WAVEFORM_ARBITRARY);
    break;
  case 8:
    displaywaveformicon(sublevels[4], (char *)"SampleHold", samplehold,
                        lesynthi, WAVEFORM_SAMPLE_HOLD);
    break;
  case 9:
    displaywaveformicon(sublevels[4], (char *)"Drum", arbitrarywave, lesynthi,
                        WAVEFORM_ARBITRARY);
    break;
  case 10:
    displaywaveformicon(sublevels[4], (char *)"String", samplehold, lesynthi,
                        WAVEFORM_SAMPLE_HOLD);
    break;
  case 11:
    displaywaveformicon(sublevels[4], (char *)"Wave OFF", moonwave, lesynthi,
                        WAVEFORM_SINE);
    break;

  default:
    break;
  }
}

void wavelinepanel(int synthi) {

  switch (sublevels[3]) {

  case 0:

    wavelineType(synthi);

    break;
  case 1:

    wavelineModulatedbool(synthi);

    break;
  case 2:
    displayLFOpanel(synthi);
    break;
  case 3:
    wavelineFreq(synthi);
    break;
  case 4:
    wavelineoffset(synthi);

    break;
  case 5:
    wavelinePhase(synthi);

    break;

  case 7:
    if (sublevels[2] < 3) {
      sublevels[2]++;
    } else {
      sublevels[2] = 0;
    }

    navlevel--;
    lemenuroot();

    // Serial.print("Next");
    break;

  case 6:
    // Serial.print("Previous");
    if (sublevels[2] > 0) {
      sublevels[2]--;
    } else {
      sublevels[2] = 3;
    }
    navlevel--;
    lemenuroot();
    break;

  default:
    break;
  }
}

void wavelinemenuBG(int synthi) {
  display.clearDisplay();
  // display.drawBitmap(35, 64-48+20, wavex, 104, 48, SSD1306_WHITE);
  display.setTextSize(1); // Draw 2X-scale text
  display.setCursor(120, 57);
  display.print(synthi + 1);
  display.setTextSize(1);
}

void wavelinesBG() {
  display.clearDisplay();
  display.drawBitmap(0, 64 - 47, wavesbg2, 128, 47, SSD1306_WHITE);

  display.display();
}

void wavelining(int startx, int starty, char *leprintlabel, int synthi) {
  if (navlevel >= 2) {
    if (navlevel == 2) {

      display.fillRect(startx, starty, 64, 24, SSD1306_INVERSE);
      printlabel(leprintlabel);
      display.display();
    }
    if (navlevel >= 3) {
      if (navlevel == 3) {
        navrange = truesizeofwavelineslabels - 1;

        wavelinemenuBG(sublevels[2]);
        display.display();
        dolistwavelineparams();
        dodisplay();

        if (sublevels[3] == 0) {
          sublevels[4] = Waveformstyped[synthi];
          wavelinepanel(synthi);
        }
        if (sublevels[3] == 1) {
          // Modulated bool switch
          // sublevels[4] = int(mixlevelsL[synthi]*100) ;
          wavelinepanel(synthi);
        }
        
        if (sublevels[3] == 3) {
          sublevels[4] = round(wavesfreqs[synthi]);
          wavelinepanel(synthi);
        }
        if (sublevels[3] == 5) {

          //  Serial.println("phasing");
          sublevels[4] = int(phaselevelsL[synthi]);
          wavelinepanel(synthi);
        }
        if (sublevels[3] == 4) {
          sublevels[4] = wave1offset[synthi];
          wavelinepanel(synthi);

        }
      }
      if (navlevel >= 4) {

        wavelinepanel(synthi);
      }
    }
  }
}


void displayadsrgraph() {
  if (sublevels[2] == 2) {
    navleveloverwrite = 2;
  }
  if (sublevels[1] == 0) {
    navleveloverwrite = 4;
  }

  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(1);

  canvasBIG.setTextSize(1);
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvasBIG.drawLine(2, 61, 2, 18, SSD1306_WHITE);
  canvasBIG.drawLine(2, 61, 125, 61, SSD1306_WHITE);
  canvasBIG.drawLine(125, 59, 127, 61, SSD1306_WHITE);
  canvasBIG.drawLine(125, 63, 127, 61, SSD1306_WHITE);
  canvasBIG.drawLine(2, 16, 0, 18, SSD1306_WHITE);
  canvasBIG.drawLine(2, 16, 4, 18, SSD1306_WHITE);

  // mappedsustain
  int totalliner = mappedattack * 10 + mappeddecay + 100 + mappedrelease +
                   MadsrAttackDelay * 2 + MadsrHold + 5;
  float linerratio = 124.0 / totalliner;
  int a0 = round(MadsrAttackDelay * 10 * linerratio) + 5;
  int a1 = round(mappedattack * 10 * linerratio) + a0;
  int h0 = a1;
  int h1 = a1 + round(MadsrHold * linerratio);
  int d0 = h1;
  int d1 = d0 + round(mappeddecay * linerratio);
  int s0 = d1;
  int s1 = s0 + 100 * linerratio;
  int suY = map(mappedsustain, 0, 100, 37, 0) + 22;
  int r0 = s1;
  int r1 = r0 + mappedrelease * linerratio;
  int startx = 3;
  int starty = 16;

  canvasBIG.drawLine(a0, 61, a1, 24, SSD1306_WHITE);
  canvasBIG.drawLine(h0, 24, h1, 24, SSD1306_WHITE);
  canvasBIG.drawLine(d0, 24, d1, suY, SSD1306_WHITE);
  canvasBIG.drawLine(s0, suY, s1, suY, SSD1306_WHITE);
  canvasBIG.drawLine(r0, suY, r1, 61, SSD1306_WHITE);
  display.clearDisplay();
  dodisplay();

  // preparing for next display loop
  canvastitle.fillScreen(SSD1306_BLACK);

  canvasBIG.fillScreen(SSD1306_BLACK);

  switch (sublevels[navleveloverwrite]) {
  case 0:
    display.fillRect(startx, starty,
                     round(MadsrAttackDelay * 10 * linerratio) + 1, 45,
                     SSD1306_INVERSE);
    display.display();
    sliceDa();
    break;

  case 1:
    display.fillRect(a0, starty, round(mappedattack * 10 * linerratio) + 2, 45,
                     SSD1306_INVERSE);
    display.display();

    sliceA();
    break;

  case 2:
    display.fillRect(h0, starty, round(MadsrHold * linerratio) + 2, 45,
                     SSD1306_INVERSE);
    display.display();

    sliceH();
    break;
  case 3:
    display.fillRect(d0, starty, round(mappeddecay * linerratio) + 1, 45,
                     SSD1306_INVERSE);
    display.display();

    sliceD();
    break;
  case 4:

    display.fillRect(s0, starty, round(95 * linerratio) + 1, 45,
                     SSD1306_INVERSE);
    display.display();

    sliceS();
    break;
  case 5:
    display.fillRect(r0, starty, round(mappedrelease * linerratio) + 1, 45,
                     SSD1306_INVERSE);
    display.display();

    sliceR();
    break;
    
  default:
    break;
  }
  
 
  dodisplay();

  canvastitle.fillScreen(SSD1306_BLACK);

  canvasBIG.fillScreen(SSD1306_BLACK);
}

void GlobalADSR() {
  
  SetADSR();
  ApplyADSR();
    
}

void sliceA() {
  if (navlevel == navleveloverwrite + 1) {
    //stuck here until validation of cursor, try using returnto nav
    sublevels[navlevel + 1] = mappedattack;
    vraipos = sublevels[navlevel + 1];
    myEnc.write(4 * sublevels[navlevel + 1]);
    navlevel = navlevel + 1;
  }

  if (navlevel == navleveloverwrite + 2) {
    navrange = 1024;


    mappedattack = sublevels[navleveloverwrite + 2];
  }
  if (navlevel == navleveloverwrite + 3) {
    // Serial.println("after2clicks");

    if (sublevels[1] == 2) {
      // Serial.println("setting global");
      GlobalADSR();
    }
    returntonav(navleveloverwrite, 5);
    Serial.println("returned twice");

  }
  canvastitle.setTextSize(1);
  canvastitle.setCursor(0, 0);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.println((char *)"Attack ");
  canvastitle.setCursor(55, 0);
  canvastitle.setTextSize(1);
  canvastitle.println(mappedattack);
  // Serial.print("displayd SliceA");
}

void sliceDa() {
  if (navlevel == navleveloverwrite + 1) {

    sublevels[navlevel + 1] = MadsrAttackDelay;
    vraipos = sublevels[navlevel + 1];
    myEnc.write(4 * sublevels[navlevel + 1]);
    navlevel = navlevel + 1;
  }
  if (navlevel == navleveloverwrite + 2) {
    navrange = 100;

    MadsrAttackDelay = sublevels[navleveloverwrite + 2];
  }
  if (navlevel == navleveloverwrite + 3) {
    if (sublevels[1] == 2) {
      // Serial.println("setting global");
      GlobalADSR();
    }

    returntonav(navleveloverwrite, 5);
  }
  canvastitle.setTextSize(1);
  canvastitle.setCursor(0, 0);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.println((char *)"Attack Delay ");
  canvastitle.setCursor(55, 0);
  canvastitle.println(MadsrAttackDelay);
  
}

void sliceH() {
  if (navlevel == navleveloverwrite + 1) {
    sublevels[navlevel + 1] = MadsrHold;
    vraipos = sublevels[navlevel + 1];
    myEnc.write(4 * sublevels[navlevel + 1]);
    navlevel = navlevel + 1;
  }
  if (navlevel == navleveloverwrite + 2) {
    navrange = 100;
    MadsrHold = sublevels[navleveloverwrite + 2];
  }
  if (navlevel == navleveloverwrite + 3) {
    if (sublevels[1] == 2) {
      // Serial.println("setting global");
      GlobalADSR();
    }

    returntonav(navleveloverwrite, 5);
  }
  canvastitle.setTextSize(1);
  canvastitle.setCursor(0, 0);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.println((char *)"Hold ");
  canvastitle.setCursor(55, 0);

  canvastitle.println(MadsrHold);
}

void sliceD() {

  if (navlevel == navleveloverwrite + 1) {
    sublevels[navlevel + 1] = mappeddecay;
    vraipos = sublevels[navlevel + 1];
    myEnc.write(4 * sublevels[navlevel + 1]);
    navlevel = navlevel + 1;
  }
  if (navlevel == navleveloverwrite + 2) {
    navrange = 512;
    mappeddecay = sublevels[navleveloverwrite + 2];
  }
  if (navlevel == navleveloverwrite + 3) {
    if (sublevels[1] == 2) {
      // Serial.println("setting global");
      GlobalADSR();
    }

    returntonav(navleveloverwrite, 5);
  }

  canvastitle.setTextSize(1);
  canvastitle.setCursor(0, 0);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.println((char *)"Decay ");
  canvastitle.setCursor(55, 0);

  canvastitle.println(mappeddecay);
}

void sliceS() {
  if (navlevel == navleveloverwrite + 1) {
    sublevels[navlevel + 1] = mappedsustain;
    vraipos = sublevels[navlevel + 1];
    myEnc.write(4 * sublevels[navlevel + 1]);
    navlevel = navlevel + 1;
  }
  if (navlevel == navleveloverwrite + 2) {
    navrange = 100;
    mappedsustain = sublevels[navleveloverwrite + 2];
  }
  if (navlevel == navleveloverwrite + 3) {
    if (sublevels[1] == 2) {
      // Serial.println("setting global");
      GlobalADSR();
    }

    returntonav(navleveloverwrite, 5);
  }

  canvastitle.setTextSize(1);
  canvastitle.setCursor(0, 0);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.println((char *)"Sustain ");
  canvastitle.setCursor(55, 0);
  canvastitle.println(mappedsustain);
}

void sliceR() {
  if (navlevel == navleveloverwrite + 1) {
    sublevels[navlevel + 1] = mappedrelease;
    vraipos = sublevels[navlevel + 1];
    myEnc.write(4 * sublevels[navlevel + 1]);
    navlevel = navlevel + 1;
  }
  if (navlevel == navleveloverwrite + 2) {
    navrange = 1024;
    mappedrelease = sublevels[navleveloverwrite + 2];
  }
  if (navlevel == navleveloverwrite + 3) {
    if (sublevels[1] == 2) {
      // Serial.println("setting global");
      GlobalADSR();
    }

    returntonav(navleveloverwrite, 5);
  }

  canvastitle.setTextSize(1);
  canvastitle.setCursor(0, 0);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.println((char *)"Release ");
  canvastitle.setCursor(55, 0);
  canvastitle.println(mappedrelease);
}

void dolistwavelineparams() {
  char wavelineslabels[truesizeofwavelineslabels][12] = {
      "Type", "Modulated", "LFO", "Freq", "Offset", "Phase", "<-  ", "  ->"};
  int startx = 5;
  int starty = 16;
  char *textin = (char *)wavelineslabels[sublevels[3]];

  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);

  canvastitle.setTextSize(2);

  canvastitle.println(textin);

  canvasBIG.setTextSize(1);

  canvasBIG.fillScreen(SSD1306_BLACK);

  for (int filer = 0; filer < truesizeofwavelineslabels - 1 - (sublevels[3]);
       filer++) {

    canvasBIG.setCursor(startx, starty + ((filer)*10));
    canvasBIG.println(wavelineslabels[sublevels[3] + 1 + filer]);
  }
  for (int filer = 0; filer < sublevels[3]; filer++) {

    canvasBIG.setCursor(
        startx,
        (10 * (truesizeofwavelineslabels - sublevels[3]) + 6 + ((filer)*10)));
    canvasBIG.println(wavelineslabels[filer]);
  }
}

void dolistsyntmenu() {
  char synthmenulabels[5][12] = {"Synths", "Mixer", "ADSR", "  ", "Filter"};

  // removeExt(textin);
  byte startx = 5;
  byte starty = 16;
  char *textin = (char *)synthmenulabels[sublevels[1]];
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(2);
  canvastitle.println(textin);
  canvasBIG.setTextSize(1);
  canvasBIG.fillScreen(SSD1306_BLACK);
  for (int filer = 0; filer < 4 - (sublevels[1]); filer++) {
    canvasBIG.setCursor(startx, starty + ((filer)*10));
    canvasBIG.println(synthmenulabels[sublevels[1] + 1 + filer]);
  }
  for (int filer = 0; filer < sublevels[1]; filer++) {
    canvasBIG.setCursor(startx, (10 * (5 - sublevels[1])) + 6 + ((filer)*10));
    canvasBIG.println(synthmenulabels[filer]);
  }
}

void synthmenu() {
  if (navlevel == 1) {
    display.clearDisplay();
    reinitsublevels(2);
    dolistsyntmenu();
    dodisplay();
  }

  if (sublevels[1] == 3 && navlevel > 1) {
    navrange = numberofsynthsw-1;
    showsynthparamspanel();
  }
  //adsr section
  if (sublevels[1] == 2) {
    if (navlevel >= 2) {
      if (navlevel == 2) {
        navrange = 5;
      }
      
      navleveloverwrite = 2;
      displayadsrgraph();
    }
  }
  // waves menu
  if (sublevels[1] == 0) {
    if (navlevel >= 2) {
      if (navlevel == 2) {

        navrange = numberofsynthsw-1;
        wavelinesBG();
        sublevels[3] = 0;
      }

      switch (sublevels[2]) {

      case 0:
        toprint = (char *)"Waveline 1";
        wavelining(0, 16, toprint, sublevels[2]);

        break;
      case 1:
        toprint = (char *)"Waveline 2";
        wavelining(64, 16, toprint, sublevels[2]);
        break;
      case 2:
        toprint = (char *)"Waveline 3";
        wavelining(0, 40, toprint, sublevels[2]);
        break;
      
      default:
        break;
      }
    }
  }
  // mixer
  if (sublevels[1] == 1 && navlevel > 1) {
    showmixerwaves();
  }
  if (sublevels[1] == 4 && navlevel > 1) {
    le303filterVpanel();
  }
}

float fxslopedown2(byte curve, float laxval) {
  // 0 to 1 10 vals 1 to 2 10 2 to 3 10
  // float leresult ;
  return pow(laxval, (double)(curve / 128.0));
}

float fxslopedown(byte slope, float laxval) {
  float leresult = 0;
  switch (slope) {
  case 0:
    leresult = 1 - (((1 / (pow(10, (double)laxval))) * 5.55556) - 0.555556) / 5;
    break;
  case 1:
    leresult = laxval;
    break;
  case 2:
    leresult = sqrt(abs(sin(((laxval)) * 3.14159 + 1.57)));
    break;
  case 3:
    leresult = 1.0 - ((sin(laxval * 3.14159 + 1.57)) * 0.5) + 0.5;
    break;

  default:
    break;
  }
  return abs(leresult);
}

void actionsynthparamspanel() {

  if (navlevel == 3) {
    navrange = 128;
    if (sublevels[2] == 0) {
      slope1 = sublevels[3];
    }
    if (sublevels[2] == 1) {
      navrange = 128;
      slope2 = sublevels[3];
    }
  }
  if (navlevel > 3) {
    returntonav(2);
  }
}

void selectsynthparamspanel() {
  if (navlevel == 2) {
    navrange = 1;
    if (sublevels[2] == 0) {
      sublevels[3] = slope1;
      canvasBIG.setCursor(40, 16);
      canvasBIG.print((char)9);
    }
    if (sublevels[2] == 1) {
      sublevels[3] = slope2;
      canvasBIG.setCursor(104, 16);
      canvasBIG.print((char)9);
    }
  }
}

void showsynthparamspanel() {
  actionsynthparamspanel();
  display.clearDisplay();
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.fillScreen(SSD1306_BLACK);
  selectsynthparamspanel();
  canvasBIG.setCursor(0, 16);
  canvasBIG.setTextSize(1);
  canvasBIG.print("Sl1: ");
  canvasBIG.print(slope1);
  canvasBIG.setCursor(64, 16);
  canvasBIG.print("Sl2: ");
  canvasBIG.print(slope2);
  canvasBIG.setCursor(0, 16 + 10);
  canvasBIG.print("C.mode:");
  canvasBIG.print(cutoffmode);
  canvasBIG.setCursor(64, 16 + 10);
  canvasBIG.print("R.mode:");
  canvasBIG.print(resonancemode);
  canvasBIG.setCursor(0, 16 + 20);
  canvasBIG.print("param5:");
  canvasBIG.print(paramse1);
  canvasBIG.setCursor(64, 16 + 20);
  canvasBIG.print("param6:");
  canvasBIG.print(paramse2);
  dodisplay();
}

void setlepulse1() {
  le303pulsewidth = (cutoff_pulse / 32.0) * 2 * millitickinterval;
  if (le303pulsewidth < 50) {
    le303pulsewidth = 50;
  }
}

void setlepulse2() {
  le303pulsewidth2 =
      (reson_pulse / 32.0) * 2 * millitickinterval + 50;
  if (le303pulsewidth2 < 50) {
    le303pulsewidth2 = 50;
  }
}

void le303filterVpanelAction() {
  if (navlevel == 3) {
    // AudioNoInterrupts();
    int slct = sublevels[2];
    // fq
    if (slct == 0) {
      navrange = 128;
      le303ffilterzVknobs[0] = sublevels[3];
      le303filterzfreq = round((le303ffilterzVknobs[0] / 128.0) * 10000);
      le303filterzrange = le303filterzfreq;
    }
    // res
    if (slct == 1) {
      navrange = 128;
      le303ffilterzVknobs[1] = sublevels[3];
      le303filterzreso = ((le303ffilterzVknobs[1]) / 128.0) * 5;
      // if (le303filterzreso < 0.7) {
      //  le303filterzreso = 0.7;
      //  }
    }
    
    // lowpass
    if (slct == 2) {
      navrange = 128;
      mixle303ffilterzVknobs[0] = sublevels[3];
      le303filterzgainz[0] = (mixle303ffilterzVknobs[0]) / 128.0;
    }
    // bandpass
    if (slct == 3) {
      navrange = 128;
      mixle303ffilterzVknobs[1] = sublevels[3];
      le303filterzgainz[1] = (mixle303ffilterzVknobs[1]) / 128.0;
    }
    // high pass
    if (slct == 4) {
      navrange = 128;
      mixle303ffilterzVknobs[2] = sublevels[3];
      le303filterzgainz[2] = (mixle303ffilterzVknobs[2]) / 128.0;
    }
    if (slct == 5) {
      navrange = 100;
      le303filterzwet = sublevels[3];
      // le303filterzwet = (mixle303ffilterzVknobs[2])/128.0 ;
      le303filterzWet();
    }
    if (slct == 6) {
      navrange = 32;
      cutoff_pulse = sublevels[3];
      setlepulse1();
      // le303filterzwet = (mixle303ffilterzVknobs[2])/128.0 ;
    }
    if (slct == 7) {
      navrange = 32;
      reson_pulse = sublevels[3];
      setlepulse2();
      // le303filterzwet = (mixle303ffilterzVknobs[2])/128.0 ;
    }
    if (slct == 8) {
      navrange = 128;
      preampleswaves = sublevels[3];
      Wavespreamp303controls();
    }

    if (slct == 9) {
      navrange = 128;
      glidemode = sublevels[3];
    }
    
    le303filtercontrols();
  }
  if (navlevel > 3) {
    returntonav(2);
  }
}

void Wavespreamp303controls() {
  for (int i = 0; i < nombreofliners; i++) {
    Wavespreamp303[i]->gain(preampleswaves*2 / 128.0);
  }
}

void le303filterzWet() {
  for (int i = 0; i < nombreofliners; i++) {
    les303wet[i]->gain(0, le303filterzwet / 100.0);
    les303wet[i]->gain(1, (1 - (le303filterzwet / 100.0)));
  }
}

void le303filtercontrols() {
  for (int i = 0; i < nombreofliners; i++) {
    setle303filterpass(i);
    
  }
}

void le303filterVpanel() {
  le303filterVpanelAction();
  int knobradius = 9;
  int centercirclex = 5 + knobradius;
  int centercircley = 35 + knobradius;
  int ftVcursorpointx;
  int ftVcursorpointy;
  float coeffangle;
  int totbartall = 37;
  int topwbarstart = 16;
  int wbarwidth = 9;
  int wbarwidth2 = 8;
  int barsize;
  int startlex2 = 67;
  display.clearDisplay();
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(1);
  canvastitle.print("303 ");
  canvastitle.setCursor(22, 0);

  canvastitle.print("In:");
  canvastitle.print((preampleswaves*2 / 128.0) * 100.0, 1);

  coeffangle = (6.2831 - (le303ffilterzVknobs[0] / 128.0) * 6.2831) + 3.1416;
  canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
  ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
  ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
  canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                     ftVcursorpointy, SSD1306_WHITE);
  canvasBIG.setCursor(centercirclex - knobradius + 4,
                      centercircley + knobradius + 4);
  canvasBIG.setTextSize(1);
  canvasBIG.print("FQ");
  if (le303filterzfreq < 1000) {
    canvasBIG.setCursor(centercirclex - knobradius + 1, 25);
    canvasBIG.print(le303filterzfreq, 0);
  }
  if ((round(le303filterzfreq) < 9900) && (le303filterzfreq >= 1000)) {
    canvasBIG.setCursor(centercirclex - knobradius - 1, 25);
    canvasBIG.print(round(le303filterzfreq) / 1000.0, 1);
    canvasBIG.print("k");
  }
  if (le303filterzfreq >= 9900) {
    canvasBIG.setCursor(centercirclex - knobradius - 5, 25);
    canvasBIG.print(le303filterzfreq / 1000.0, 1);
    canvasBIG.print("k");
  }

  // resonnance
  coeffangle = (6.2831 - (le303ffilterzVknobs[1] / 128.0) * 6.2831) + 3.1416;
  centercirclex = knobradius + 30;
  canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
  ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
  ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
  canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                     ftVcursorpointy, SSD1306_WHITE);
  canvasBIG.setCursor(centercirclex - knobradius + 1,
                      centercircley + knobradius + 4);
  canvasBIG.setTextSize(1);
  canvasBIG.print("Res");
  canvasBIG.setCursor(centercirclex - knobradius + 2, 25);
  canvasBIG.print(le303filterzreso, 1);

    /*
    // octave
    coeffangle = (6.2831 - (le303ffilterzVknobs[2] / 128.0) * 6.2831) + 3.1416;
    centercirclex = knobradius + 55;
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
    ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
    ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
    canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                      ftVcursorpointy, SSD1306_WHITE);
    canvasBIG.setCursor(centercirclex - knobradius + 1,
                        centercircley + knobradius + 4);
    canvasBIG.setTextSize(1);
    canvasBIG.print("Oct");
    canvasBIG.setCursor(centercirclex - knobradius + 1, 25);
    canvasBIG.print(le303filterzoctv, 1);
    */

  barsize = round((le303filterzgainz[0] * (totbartall - 4)));
  canvasBIG.drawRoundRect(81, topwbarstart, wbarwidth, totbartall, 2,
                          SSD1306_WHITE);
  canvasBIG.fillRect(81 + 2, (totbartall + topwbarstart - barsize - 2),
                     wbarwidth - 4, barsize, SSD1306_WHITE);
  canvasBIG.setCursor(81, totbartall + topwbarstart + 4);
  canvasBIG.print("LP");
  // canvasBIG.setCursor(80,18);
  // canvasBIG.print(bqgain[0][bqstage[0]]);
  barsize = round((le303filterzgainz[1] * (totbartall - 4)));
  canvasBIG.drawRoundRect(98, topwbarstart, wbarwidth, totbartall, 2, SSD1306_WHITE);
  canvasBIG.fillRect(98 + 2, (totbartall + topwbarstart - barsize - 2), wbarwidth - 4, barsize, SSD1306_WHITE);
  canvasBIG.setCursor(97, totbartall + topwbarstart + 4);
  canvasBIG.print("BP");
  // canvasBIG.setCursor(93,18);
  // canvasBIG.print(bqgain[0][bqstage[0]]);
  barsize = round((le303filterzgainz[2] * (totbartall - 4)));
  canvasBIG.drawRoundRect(115, topwbarstart, wbarwidth, totbartall, 2, SSD1306_WHITE);
  canvasBIG.fillRect(115 + 2, (totbartall + topwbarstart - barsize - 2), wbarwidth - 4, barsize, SSD1306_WHITE);
  canvasBIG.setCursor(114, totbartall + topwbarstart + 4);
  canvasBIG.print("HP");
  // canvasBIG.setCursor(114,18);
  // canvasBIG.print(bqgain[lefilter][bqstage[lefilter]]);
  // wetbar
  barsize = round(((le303filterzwet / 100.0) * (totbartall - 4)));
  canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall, wbarwidth2, 2, SSD1306_WHITE);
  canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4, SSD1306_WHITE);
  canvasBIG.setCursor(startlex2, 0);
  canvasBIG.print("Wet");

  barsize = round(((le303pulsewidth / millitickinterval) * (totbartall - 4)));

  canvasBIG.setCursor(0, 16);
  canvasBIG.print("Xfq ");
  canvasBIG.print(cutoff_pulse);

  canvasBIG.setCursor(40, 16);
  canvasBIG.print("Xres ");
  canvasBIG.print(reson_pulse);

  canvastitle.setCursor(94, 8);
  canvastitle.print("S:");
  if (glidemode > 0 && glidemode < 13) {
    canvastitle.print(".0");
    canvastitle.print(100 * (glidemode / 128.0), 0);
  }
  if (glidemode > 12 && glidemode < 128) {
    canvastitle.print(".");
    canvastitle.print(100 * (glidemode / 128.0), 0);
  }
  if (glidemode == 128) {
    canvastitle.print("1.0");
  }
  if (glidemode == 0) {
    canvastitle.print("Off");
  }

  le303filterVpanelSelector();
  dodisplay();
}

void le303filterVpanelSelector() {

  int knobradius = 9;
  int centercirclex = 5 + knobradius;
  int centercircley = 35 + knobradius;
  int startlex2 = 67;
  int totbartall = 37;
  int topwbarstart = 16;
  int wbarwidth = 9;
  int wbarwidth2 = 8;
  if (navlevel == 2) {
    navrange = 9;
  }
  int slct = sublevels[2];
  // fq
  if (slct == 0) {
    sublevels[3] = le303ffilterzVknobs[0];
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2,
                         SSD1306_WHITE);
  }
  // res
  if (slct == 1) {
    sublevels[3] = le303ffilterzVknobs[1];
    canvasBIG.drawCircle(centercirclex + 25, centercircley, knobradius - 2,
                         SSD1306_WHITE);
  }
  /*
  // oct
  if (slct == 2) {
    sublevels[3] = le303ffilterzVknobs[2];
    canvasBIG.drawCircle(centercirclex + 50, centercircley, knobradius - 2,
                         SSD1306_WHITE);
  }
  */
  // lp
  if (slct == 2) {
    sublevels[3] = mixle303ffilterzVknobs[0];
    canvasBIG.drawRect(83, topwbarstart, wbarwidth - 4, totbartall,
                       SSD1306_WHITE);
  }
  // bp
  if (slct == 3) {
    sublevels[3] = mixle303ffilterzVknobs[1];
    canvasBIG.drawRect(100, topwbarstart, wbarwidth - 4, totbartall,
                       SSD1306_WHITE);
  }
  // hp
  if (slct == 4) {
    sublevels[3] = mixle303ffilterzVknobs[2];
    canvasBIG.drawRect(117, topwbarstart, wbarwidth - 4, totbartall,
                       SSD1306_WHITE);
  }
  // wet
  if (slct == 5) {
    sublevels[3] = le303filterzwet;
    canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall,
                       wbarwidth2 - 4, SSD1306_WHITE);
  }
  if (slct == 6) {
    sublevels[3] = cutoff_pulse;
    canvasBIG.setCursor(21, 16);
    canvasBIG.print((char)9);
  }
  if (slct == 7) {
    sublevels[3] = reson_pulse;
    canvasBIG.setCursor(62, 18);
    canvasBIG.print((char)9);
  }
  if (slct == 8) {
    sublevels[3] = preampleswaves;
    canvasBIG.setCursor(34, 0);
    canvasBIG.print((char)9);
  }

  if (slct == 9) {
    sublevels[3] = glidemode;
    canvasBIG.setCursor(100, 8);
    canvasBIG.print((char)9);
  }

}

void initialize303group() {

  for (int i = 0; i < nombreofliners; i++) {
    setle303filterpass(i);
    les303wet[i]->gain(1, 1);
    les303wet[i]->gain(0, 0);
    les303filterz[i]->frequency(220);
    les303filterz[i]->resonance(5);
  }
}

void setle303filterpass(int linei) {
  les303passes[linei]->gain(0,le303filterzgainz[0]);
  les303passes[linei]->gain(1,le303filterzgainz[1]);
  les303passes[linei]->gain(2,le303filterzgainz[2]);
}

void showmixerwaves() {
  char masterfulllabels[12][12] = {
      "Master",     "Synth",      "Sampler",    "FX1",
      "FX2",        "FX3",        "Wet Synth",  "Wet Sampler", "Wet Other",
      "Waveline 1", "Waveline 2", "Waveline 3" };
  navrange = 11;
  byte slct = sublevels[2];
  if (slct < 3) {
    actionwmixerM(sublevels[2]);
  }
  if (slct > 2 && slct < 6) {
    actionwet1mixer(sublevels[2] - 3);
  }
  if (slct > 5 && slct < 9) {
    action_dry_mix(sublevels[2] - 6);
  }
  if (slct > 8 && slct < 12) {
    actionwmixer(sublevels[2] - 8);
  }

  display.clearDisplay();
  canvastitle.fillScreen(SSD1306_BLACK);
  canvasBIG.fillScreen(SSD1306_BLACK);
  // canvastitle.setCursor(70,0);
  canvasBIG.setTextSize(1);
  canvasBIG.setCursor(0, 0);
  canvasBIG.print((char *)masterfulllabels[sublevels[2]]);

  byte centercirclex;
  byte centercircley;
  byte xcentershifter;
  byte knobradius = 7;
  byte trianglepointx;
  byte trianglepointy;
  byte yshifter = 46;
  float coeffangle;
  xcentershifter = (knobradius * 2) + 6;

  for (int i = 0; i < 3; i++) {

    coeffangle = (6.2831 - (mixlevelsM[i] / 128.0) * 6.2831) + 3.1416;
    centercirclex = knobradius + (xcentershifter * i);
    centercircley = 16 + knobradius;
    canvastitle.setCursor(centercirclex - 5, 8);
    canvastitle.setTextSize(1);
    canvastitle.print((char)masterfulllabels[i][0]);
    canvastitle.print((char)masterfulllabels[i][2]);
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
    trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
    trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));
    display.drawLine(centercirclex, centercircley, trianglepointx, trianglepointy, SSD1306_WHITE);
  }

  if (slct < 3) {
    centercirclex = knobradius + (xcentershifter * slct);
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
    canvastitle.setCursor(95, 0);
    canvastitle.print((mixlevelsM[slct] / 128.0) * 100.0, 1);
  }

  for (int i = 0; i < 3; i++) {
    coeffangle = (6.2831 - (WetMixMasters[i + 1]) * 6.2831) + 3.1416;
    centercirclex = knobradius + (xcentershifter * i) + 5 + (xcentershifter * 3);
    centercircley = 16 + knobradius;
    canvastitle.setCursor(centercirclex - 8, 8);
    canvastitle.setTextSize(1);
    canvastitle.print((char *)masterfulllabels[i + 3]);
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
    trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
    trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));
    display.drawLine(centercirclex, centercircley, trianglepointx, trianglepointy, SSD1306_WHITE);
  }

  if (slct > 2 && slct < 6) {
    centercirclex = knobradius + (xcentershifter * (slct - 3)) + 5 + (xcentershifter * 3);
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
    canvastitle.setCursor(95, 0);
    canvastitle.print(WetMixMasters[slct - 3 + 1] * 100.0, 1);
  }

  for (int i = 0; i < 3; i++) {
    coeffangle = (6.2831 - (wetins[i] / 128.0) * 6.2831) + 3.1416;
    centercirclex = knobradius + (xcentershifter * i);
    centercircley = yshifter + knobradius;
    canvasBIG.setCursor(centercirclex - 7, centercircley - (2 + knobradius * 2));
    canvasBIG.print("Ws");
    canvasBIG.print(i);
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
    trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
    trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));
    display.drawLine(centercirclex, centercircley, trianglepointx, trianglepointy, SSD1306_WHITE);
  }

  if (slct > 5 && slct < 9) {
    centercirclex = knobradius + (xcentershifter * (slct - 6));
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
    canvastitle.setCursor(95, 0);
    canvastitle.print((wetins[slct - 6] / 128.0) * 100.0, 1);
  }
  
  for (int i = 0; i < numberofsynthsw; i++) {
    coeffangle = (6.2831 - (mixlevelsL[i]) * 6.2831) + 3.1416;
    centercirclex = knobradius + (xcentershifter * i) + 25 + (xcentershifter * 2);
    centercircley = yshifter + knobradius;
    canvasBIG.setCursor(centercirclex - 5, centercircley - (2 + knobradius * 2));
    canvasBIG.print("W");
    canvasBIG.print(i);
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
    trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
    trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));
    display.drawLine(centercirclex, centercircley, trianglepointx, trianglepointy, SSD1306_WHITE);
  }

  if (slct > 8 && slct < 12) {
    centercirclex = knobradius + (xcentershifter * (slct - 9)) + 25 + (xcentershifter * 2);
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
    canvastitle.setCursor(95, 0);
    canvastitle.print((mixlevelsL[slct - 9]) * 100.0, 1);
  }
  dodisplay();
}

void setwavemixlevel(int lesynth) {
 // AudioNoInterrupts();
  for (int j = 0; j < nombreofliners; j++) {
    Wavesmix[j]->gain(lesynth, mixlevelsL[lesynth]);
  }
 // AudioInterrupts();
}

void actionwet1mixer(int linstru) {

  if (navlevel == 2) {
    sublevels[3] = round(WetMixMasters[linstru + 1] * 128.0);
  }
  if (navlevel == 3) {
    navrange = 128;
    // wetmain[lafxline] = sublevels[3];
    WetMixMasters[linstru + 1] = sublevels[3] / 128.0;
    wetmixmastercontrols();
  }
  if (navlevel == 4) {
    returntonav(2, 3);
  }
  //
}

void action_dry_mix(int linstru) {

  if (navlevel == 2) {
    sublevels[3] = wetins[linstru];
  }
  if (navlevel == 3) {
    navrange = 128;
    wetins[linstru] = sublevels[3];
    set_dry_mix(linstru);
  }
  if (navlevel == 4) {
    returntonav(2, 3);
  }
}

void wetmixmastercontrols() {
  for (byte i = 0; i < 4; i++) {
    WetMixMasterL.gain(i, WetMixMasters[i]);
    WetMixMasterR.gain(i, WetMixMasters[i]);
  }
}

void set_dry_mix(int lebus) {
  //AudioNoInterrupts();
  //TODO add wetness mix for fxbusL(3 ) <- others dry/wet
  switch (lebus) {
  case 0:
    // set synth wetness on fx main bus
    
    MasterL1.gain(2, wetins[0] / 128.0);
    MasterR1.gain(2, wetins[0] / 128.0);
    FXBusL.gain(2, 1 - (wetins[0] / 128.0));
    FXBusR.gain(2, 1 - (wetins[0] / 128.0));
    
    break;
  case 1:
    // set sampler wetness on fx main bus
    MasterL1.gain(3, wetins[1] / 128.0);
    MasterR1.gain(3, wetins[1] / 128.0);
    FXBusL.gain(1, 1 - (wetins[1] / 128.0));
    FXBusR.gain(1, 1 - (wetins[1] / 128.0));
    break;

  case 2:
    // set wetness for "others" (audio in,SD,metronome) on fx main bus
    MasterL1.gain(0 ,wetins[2] / 128.0);
    MasterR1.gain(0, wetins[2] / 128.0);
    FXBusL.gain(3, 1 - (wetins[2] / 128.0));
    FXBusR.gain(3, 1 - (wetins[2] / 128.0));
    break;

  default:
    break;
  }
  //AudioInterrupts();
}

void actionwmixer(int lesynth) {

  if (navlevel == 2) {
    sublevels[3] = round(mixlevelsL[lesynth] * 128.0);
  }
  if (navlevel == 3) {
    navrange = 128;
    mixlevelsL[lesynth] = sublevels[3] / 128.0;
    setwavemixlevel(lesynth);
  }
  if (navlevel == 4) {
    returntonav(2, 3);
  }
  //
}

void actionwmixerM(int lebus) {

  if (navlevel == 2) {
    sublevels[3] = round(mixlevelsM[lebus]);
  }
  if (navlevel == 3) {
    navrange = 128;
    mixlevelsM[lebus] = sublevels[3];

    setmastersmixlevel(lebus);
  }
  if (navlevel == 4) {
    returntonav(2, 3);
  }
  //
}

void setmastersmixlevel(int lebus) {
  //AudioNoInterrupts();
  switch (lebus) {
  case 0:
    // set mastermixlevel
    //audioShield.volume(mixlevelsM[0] / 128.0);
    ampL.gain(mixlevelsM[0] / 128.0);
    ampR.gain(mixlevelsM[0] / 128.0);
    break;
  case 1:
    // set synth Main
    mixerWAll.gain(1, mixlevelsM[1] / 128.0);
    mixerWAll.gain(0, mixlevelsM[1] / 128.0);
    break;
  case 2:
    // set sampler main
    flashMastermix.gain(0, mixlevelsM[2] / 128.0);
    flashMastermix.gain(1, mixlevelsM[2] / 128.0);
    break;
  default:
    break;
  }
  //AudioInterrupts();
}

void setwavetypefromlist(int lesinthy, int letype) {
  Serial.println("setting wave type");
  AudioNoInterrupts();
  Waveformstyped[lesinthy] = letype;

  if (FMmodulated[lesinthy] == 0) {

    if (letype < 9) {
      for (int i = 0; i < nombreofliners; i++) {

        FMwavecords1[i + (nombreofliners * lesinthy)]->disconnect();
        stringcords1[i + (nombreofliners * lesinthy)]->disconnect();
        modulatecords1[i + (nombreofliners * lesinthy)]->disconnect();
        MDdrumcords1[i + (nombreofliners * lesinthy)]->disconnect();
        MDstringcords1[i + (nombreofliners * lesinthy)]->disconnect();
        drumcords1[i + (nombreofliners * lesinthy)]->disconnect();
        wavelinescords[i + (nombreofliners * lesinthy)]->connect();
        waveforms1[i + (nombreofliners * lesinthy)]->begin(lesformes[letype]);

        if (letype == 7) {
          waveforms1[i + (nombreofliners * lesinthy)]->arbitraryWaveform(arbitrary_waveforms[lesinthy],1.0);
        }
      }

    } else if (letype == 9) {
      for (int i = 0; i < nombreofliners; i++) {
        wavelinescords[i + (lesinthy * nombreofliners)]->disconnect();
        stringcords1[i + (lesinthy * nombreofliners)]->disconnect();
        FMwavecords1[i + (lesinthy * nombreofliners)]->disconnect();
        modulatecords1[i + (nombreofliners * lesinthy)]->disconnect();
        MDdrumcords1[i + (nombreofliners * lesinthy)]->disconnect();
        MDstringcords1[i + (nombreofliners * lesinthy)]->disconnect();
        drumcords1[i + (lesinthy * nombreofliners)]->connect();
      }
    } else if (letype == 10) {

      for (int i = 0; i < nombreofliners; i++) {
        wavelinescords[i + (lesinthy * nombreofliners)]->disconnect();
        drumcords1[i + (lesinthy * nombreofliners)]->disconnect();
        FMwavecords1[i + (lesinthy * nombreofliners)]->disconnect();
        modulatecords1[i + (nombreofliners * lesinthy)]->disconnect();
        MDdrumcords1[i + (nombreofliners * lesinthy)]->disconnect();
        MDstringcords1[i + (nombreofliners * lesinthy)]->disconnect();
        stringcords1[i + (lesinthy * nombreofliners)]->connect();
      }
    }
  }

  else {

    // modulated
    if (FMmodulated[lesinthy] == 1) {
      setfmtofreq(lesinthy);
    }
    if (FMmodulated[lesinthy] == 2) {
      setfmtophase(lesinthy);
    }

    if (letype < 9) {

      for (int i = 0; i < nombreofliners; i++) {
        wavelinescords[i + (nombreofliners * lesinthy)]->disconnect();
        modulatecords1[i + (nombreofliners * lesinthy)]->disconnect();
        MDdrumcords1[i + (nombreofliners * lesinthy)]->disconnect();
        MDstringcords1[i + (nombreofliners * lesinthy)]->disconnect();
        stringcords1[i + (nombreofliners * lesinthy)]->disconnect();
        drumcords1[i + (nombreofliners * lesinthy)]->disconnect();

        FMwavecords1[i + (nombreofliners * lesinthy)]->connect();
        FMwaveforms1[i + (nombreofliners * lesinthy)]->begin(lesformes[letype]);     
        
        // LFO begin
      }
    } else if (letype == 9) {
      // modulated drum
      for (int i = 0; i < nombreofliners; i++) {
        wavelinescords[i + (lesinthy * nombreofliners)]->disconnect();
        stringcords1[i + (lesinthy * nombreofliners)]->disconnect();
        FMwavecords1[i + (lesinthy * nombreofliners)]->disconnect();
        drumcords1[i + (lesinthy * nombreofliners)]->disconnect();
        MDstringcords1[i + (nombreofliners * lesinthy)]->disconnect();

        modulatecords1[i + (nombreofliners * lesinthy)]->connect();
        MDdrumcords1[i + (nombreofliners * lesinthy)]->connect();
      }
    } else if (letype == 10) {
      // modulated string
      for (int i = 0; i < nombreofliners; i++) {
        wavelinescords[i + (lesinthy * nombreofliners)]->disconnect();
        drumcords1[i + (lesinthy * nombreofliners)]->disconnect();
        FMwavecords1[i + (lesinthy * nombreofliners)]->disconnect();
        stringcords1[i + (lesinthy * nombreofliners)]->disconnect();
        MDdrumcords1[i + (nombreofliners * lesinthy)]->disconnect();
        MDstringcords1[i + (nombreofliners * lesinthy)]->connect();
        modulatecords1[i + (nombreofliners * lesinthy)]->connect();
      }
    }
  }

  // synth line off
  if (letype == 11) {
    mixlevelsL[lesinthy] = 0;
    for (int i = 0; i < nombreofliners; i++) {
      wavelinescords[i + (nombreofliners * lesinthy)]->disconnect();
      stringcords1[i + (nombreofliners * lesinthy)]->disconnect();
      drumcords1[i + (nombreofliners * lesinthy)]->disconnect();
      FMwavecords1[i + (nombreofliners * lesinthy)]->disconnect();
      MDdrumcords1[i + (nombreofliners * lesinthy)]->disconnect();
      MDstringcords1[i + (nombreofliners * lesinthy)]->disconnect();
      modulatecords1[i + (nombreofliners * lesinthy)]->disconnect();
    }
  }
  AudioInterrupts();
  setwavemixlevel(lesinthy);
  // printmixlevelsandtype();
}

void setpanlevel(int lesynth, int laval) {
  panLs[lesynth] = map(laval / 10.0, 0, 2, 0, 1);
  // panLs[lesynth] = map( 2-laval/10.0 ,0,2,0,1);
  setwavemixlevel(lesynth);
  // waves : MasterL (1) & R + FXBusL & R (2)
}

void setphaselevel(int lesynth) {
  AudioNoInterrupts();

  for (int i = 0; i < nombreofliners; i++) {
    waveforms1[i + (nombreofliners * lesynth)]->phase(phaselevelsL[lesynth]);
  }

  AudioInterrupts();
}

void setphaser(int lesynth, float laphaze) {
  AudioNoInterrupts();
  phaselevelsL[lesynth] = round(laphaze * 360.0);

  for (int i = 0; i < nombreofliners; i++) {
    waveforms1[i + (nombreofliners * lesynth)]->phase(phaselevelsL[lesynth]);
  }

  AudioInterrupts();
}

void setleLFOfrequency(float tune, int lelfor) {
  LFOwaveforms1[lelfor]->frequency(tune);
}

void setsynthfrequencyi(float tune, int voice, byte velocityz) {
  // AudioNoInterrupts();

  for (int i = 0; i < numberofsynthsw; i++) {

    waveforms1[voice + (i * nombreofliners)]->frequency(tune * wavesfreqs[i - 1]);
    waveforms1[voice + (i * nombreofliners)]->amplitude(velocityz / 128.0);
    //FMwaveforms1[i + voice * 4]->frequency(tune * wavesfreqs[i - 1]);
    //FMwaveforms1[i + voice * 4]->amplitude(velocityz / 128.0);
    FMwaveforms1[voice + (i * nombreofliners)]->frequency(tune * wavesfreqs[i - 1]);
    FMwaveforms1[voice + (i * nombreofliners)]->amplitude(velocityz / 128.0);

    //drums1[i + voice * nombreofliners]->length(velocityz * 5);
    //drums1[i + 4 + voice * nombreofliners]->length(velocityz * 5);
    drums1[voice + (i * nombreofliners)]->length(velocityz * 5);
    //drums1[voice + (i * nombreofliners)]->length(velocityz * 5);
  }

  // AudioInterrupts();
}

void SetADSR() {
  
      adsrlevels[0] = MadsrAttackDelay;
      adsrlevels[4] = mappedsustain;
      adsrlevels[5] = mappedrelease;
      adsrlevels[3] = mappeddecay;
      adsrlevels[1] = mappedattack;
      adsrlevels[2] = MadsrHold;
     
}

void ApplyADSR() {

  for (int i = 0; i < nombreofliners; i++) {
    enveloppesL[i]->delay(adsrlevels[0]);
    enveloppesL[i]->attack(adsrlevels[1]);
    enveloppesL[i]->hold(adsrlevels[2]);
    enveloppesL[i]->decay(adsrlevels[3]);
    enveloppesL[i]->sustain(adsrlevels[4] / 100.0);
    enveloppesL[i]->release(adsrlevels[5]);
  }

  mappedattack = adsrlevels[1];
  mappeddecay = adsrlevels[3];
  mappedrelease = adsrlevels[5];
  mappedsustain = adsrlevels[4];
  MadsrAttackDelay = adsrlevels[0];
  MadsrHold = adsrlevels[2];
  
}

int getwavetyped(int lawavetype) {
  switch (lawavetype) {
  case 0:
    return WAVEFORM_SINE;
    break;
  case 1:
    return WAVEFORM_SAWTOOTH;
    break;
  case 2:
    return WAVEFORM_SAWTOOTH_REVERSE;
    break;
  case 3:
    return WAVEFORM_TRIANGLE;
    break;
  case 4:
    return WAVEFORM_TRIANGLE_VARIABLE;
    break;
  case 5:
    return WAVEFORM_SQUARE;
    break;
  case 6:
    return WAVEFORM_PULSE;
    break;
  case 7:
    return WAVEFORM_ARBITRARY;
    break;
  case 8:
    return WAVEFORM_SAMPLE_HOLD;
    break;
  case 9:
    return WAVEFORM_SINE;
    break;

  default:
    return WAVEFORM_SINE;
    break;
  }
  // Waveformstyped
  // return Wavetype
}
