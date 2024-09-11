void returntonav(byte lelevel, byte lanavrange = navrange) {
  navlevel = lelevel;
  vraipos = sublevels[lelevel];
  myEnc.write(vraipos * 4);
  navrange = lanavrange;
  lemenuroot();
}

byte getavailablefx(byte leeffect) {
  for (int i = 0; i < fxiterations; i++) {
    if (fxmoduleisconnected[leeffect][i] == fxiterations + 1) {
      return i + 1;
    }
  }
  // Serial.print("Found none available");
  return 0;
}

  //for (int i = 0; i < sizeopremixtoM; i++) {
    //premixesMto[i]->disconnect();
  //}
  //for (int i = 0; i < sizeofxcords; i++) {
    //fxcording[i]->disconnect();
  //}

void switchfxes(byte lafxline, byte leeffect) {
    if (!done_once){
      done_once = true ;
  // Serial.println("Before: ");
  // listfxmoduleconnectionstate(leeffect);
 

  if (moduleonfxline[lafxline][0] != (mainmenufxlistsize - 1)) {
     Serial.print("Disconnecting existing ");
    disconnectfxline(lafxline);
  }
  // if effect on liner is different or same, is a slot of the 3 modules of the
  // leeffect used here -> clean and do if le effect has one slot used but not
  // used here ignore and let getavailable do its job

  if (leeffect != (mainmenufxlistsize - 1)) {

    fxmoduleiteration = getavailablefx(leeffect);
    Serial.println(" availablefx(leeffect)= ");
    Serial.print(fxmoduleiteration);
    // 0 is off so -1

    if (fxmoduleiteration > 0) {
       AudioNoInterrupts();
       //delay
       if (leeffect == 8) {
        Serial.println("replugging delay line");
        replug_delays_from_feedback(lafxline);
       }
      fxslotMaster[lafxline][1] = (leeffect * (fxiterations * 2 * 3)) + (lafxline * (fxiterations * 2)) + (2 * (fxmoduleiteration - 1));
      fxslotMaster[lafxline][0] = (leeffect * fxiterations) + (fxmoduleiteration - 1);
      premixesMto[fxslotMaster[lafxline][0]]->connect();
      fxcording[fxslotMaster[lafxline][1]]->connect();
      fxcording[fxslotMaster[lafxline][1] + 1]->connect();
      fxmoduleisconnected[leeffect][fxmoduleiteration - 1] = lafxline;
      moduleonfxline[lafxline][0] = leeffect;
      moduleonfxline[lafxline][1] = fxmoduleiteration - 1;
      AudioInterrupts();

      Serial.print(" premixesMto ");
      Serial.print(fxslotMaster[lafxline][0]);
      Serial.print(" connected , ");
      Serial.print(" fxcording ");
      Serial.print(fxslotMaster[lafxline][1]);
      Serial.print(" & ");
      Serial.print(fxslotMaster[lafxline][1] + 1);
      Serial.print(" connected");
      Serial.println(" ");
      Serial.print(" fxmoduleisconnected[");
      Serial.print(leeffect);
      Serial.print("][");
      Serial.print(fxmoduleiteration - 1);
      Serial.print("] = ");
      Serial.print(lafxline);
      Serial.println(" ");
      Serial.print(" moduleonfxline[");
      Serial.print(lafxline);
      Serial.print("][0] = ");
      Serial.print(leeffect);
      Serial.print(" ");
      Serial.print(" moduleonfxline[");
      Serial.print(lafxline);
      Serial.print("][1] = ");
      Serial.print(fxmoduleiteration - 1);
      Serial.println(" ");

    }
  } else {
      Serial.println(" Selected effect is None ");
    if (lafxline < fxiterations - 1) {
      WetMixMasters[lafxline + 1] = 0;
      wetmixmastercontrols();
      Serial.print(" lafxline < fxiterations - 1, so WetMixMasters[");
      Serial.print(lafxline + 1);
      Serial.print("] set to 0 ");
      //already disconnected, could crash if reattempting while not connected!!!
      // NO disconnectfxline(lafxline);
      Serial.println(" ");
      Serial.print(" disconnected");
      Serial.print(lafxline);
      
    }
  }

  // Serial.println("After: ");
  // listfxmoduleconnectionstate(leeffect);
    }
}

void initializefxmoduleisconnected() {
  // Serial.print("initializefxmoduleisconnected");
  for (int i = 0; i < mainmenufxlistsize - 1; i++) {
    for (int j = 0; j < fxiterations; j++) {
      fxmoduleisconnected[i][j] = fxiterations + 1;
    }
  }
}
void disconnectfxline(byte lafxline) {
  AudioNoInterrupts();
  Serial.println("disconnecting Fxes");
  premixesMto[fxslotMaster[lafxline][0]]->disconnect();
  fxcording[fxslotMaster[lafxline][1]]->disconnect();
  fxcording[fxslotMaster[lafxline][1] + 1]->disconnect();
  fxmoduleisconnected[moduleonfxline[lafxline][0]][moduleonfxline[lafxline][1]] = fxiterations + 1;
  moduleonfxline[lafxline][0] = mainmenufxlistsize - 1;
  moduleonfxline[lafxline][1] = 0;
  fxslotMaster[lafxline][0] = 1000;
  fxslotMaster[lafxline][1] = 1000;
  stopdelayline((int)lafxline);
  unplug_delays_from_feedback((int)lafxline);
  AudioInterrupts();
  
}
void dolistMainFxPanel() {
  char mainmenufxlist[mainmenufxlistsize][12] = {
      "Multiply", "Reverb", "Granular", "BitCrusher", "Flanger",
      "Chorus",   "Biquad", "Filter",   "Delay",      "None"};
  byte startx = 5;
  byte starty = 16;
  char *textin = (char *)mainmenufxlist[sublevels[navlevel]];
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(2);
  canvastitle.println(textin);
  canvasBIG.setTextSize(1);
  canvasBIG.fillScreen(SSD1306_BLACK);

  for (int filer = 0; filer < navrange - (sublevels[navlevel]); filer++) {
    canvasBIG.setCursor(startx, starty + ((filer)*10));
    canvasBIG.println(mainmenufxlist[sublevels[navlevel] + 1 + filer]);
  }
  for (int filer = 0; filer < sublevels[navlevel]; filer++) {
    canvasBIG.setCursor(startx, (10 * (navrange + 1 - sublevels[navlevel])) +
                                    6 + ((filer)*10));
    canvasBIG.println(mainmenufxlist[filer]);
  }
}
void dolistmainfxlines() {
  char mainmenufxlist[mainmenufxlistsize][12] = {
      "Multiply", "Reverb", "Granular", "BitCrusher", "Flanger",
      "Chorus",   "Biquad", "Filter",   "Delay",      "None"};
  char mainfxlineslist[mainfxlines][12] = {"FX Line1", "FX Line2", "FX Line3"};
  byte startx = 5;
  byte starty = 16;
  String textin;
  if (moduleonfxline[sublevels[1]][0] != (mainmenufxlistsize - 1)) {
    textin = (String)mainmenufxlist[moduleonfxline[sublevels[1]][0]];
  } else {
    textin = (String)mainfxlineslist[sublevels[1]];
  }
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(2);
  canvastitle.println(textin);
  canvasBIG.setTextSize(1);
  canvasBIG.fillScreen(SSD1306_BLACK);

  for (int filer = 0; filer < mainfxlines - 1 - (sublevels[1]); filer++) {

    canvasBIG.setCursor(startx, starty + ((filer)*10));

    if (moduleonfxline[sublevels[1] + 1 + filer][0] !=
        (mainmenufxlistsize - 1)) {
      canvasBIG.println(
          (String)mainmenufxlist[moduleonfxline[sublevels[1] + 1 + filer][0]]);
      // textin = (char*)mainmenufxlist[moduleonfxline[sublevels[1]][0]];
    } else {
      canvasBIG.println(mainfxlineslist[sublevels[1] + 1 + filer]);
    }
  }
  for (int filer = 0; filer < sublevels[1]; filer++) {

    canvasBIG.setCursor(startx,
                        (10 * (mainfxlines - sublevels[1]) + 6 + ((filer)*10)));
    if (moduleonfxline[filer][0] != (mainmenufxlistsize - 1)) {
      canvasBIG.println((String)mainmenufxlist[moduleonfxline[filer][0]]);
      // textin = (char*)mainmenufxlist[moduleonfxline[sublevels[1]][0]];
    } else {
      canvasBIG.println(mainfxlineslist[filer]);
    }
  }
}

void MainFxPanel() {
 
  if (navlevel == 1) {
    reinitsublevels(2);
    navrange = 2;
    display.clearDisplay();
    dolistmainfxlines();
    dodisplay();
    sublevels[2] = moduleonfxline[sublevels[1]][0];
  }
  if (navlevel == 2) {
    done_once = false ;
    display.clearDisplay();
    navrange = 9;
    dolistMainFxPanel();
    dodisplay();
  }
  if (navlevel > 2) {
    //do once
    switchfxes(sublevels[1], sublevels[2]);
    displayfxVcontrols(fxmoduleiteration - 1);
  }
}

void biquadcontrols(byte lebiquad) {
  // AudioNoInterrupts();

  switch (bqtype[lebiquad][bqstage[lebiquad]]) {
  case 0:

    biquad[lebiquad]->setLowpass(bqstage[lebiquad],
                                 bqfreq[lebiquad][bqstage[lebiquad]],
                                 bqslope[lebiquad][bqstage[lebiquad]]);

    break;
  case 1:

    biquad[lebiquad]->setHighpass(bqstage[lebiquad],
                                  bqfreq[lebiquad][bqstage[lebiquad]],
                                  bqslope[lebiquad][bqstage[lebiquad]]);

    break;
  case 2:

    biquad[lebiquad]->setBandpass(bqstage[lebiquad],
                                  bqfreq[lebiquad][bqstage[lebiquad]],
                                  bqslope[lebiquad][bqstage[lebiquad]]);

    break;
  case 3:

    biquad[lebiquad]->setNotch(bqstage[lebiquad],
                               bqfreq[lebiquad][bqstage[lebiquad]],
                               bqslope[lebiquad][bqstage[lebiquad]]);

    break;
  case 4:

    biquad[lebiquad]->setLowShelf(bqstage[lebiquad],
                                  bqfreq[lebiquad][bqstage[lebiquad]],
                                  bqgain[lebiquad][bqstage[lebiquad]],
                                  bqslope[lebiquad][bqstage[lebiquad]]);

    break;
  case 5:

    biquad[lebiquad]->setHighShelf(bqstage[lebiquad],
                                   bqfreq[lebiquad][bqstage[lebiquad]],
                                   bqgain[lebiquad][bqstage[lebiquad]],
                                   bqslope[lebiquad][bqstage[lebiquad]]);

    break;
    break;
  }
  // AudioInterrupts();
}

void delaycontrols(byte ledelayline, int gronint) {

  AudioNoInterrupts();
  if (gronint >= 0 && gronint < 100) {
    interpot = map(gronint, 0, 100, 0, 1);
    delaypremix[2 * ledelayline]->gain(0, 1 - interpot);
    delaypremix[2 * ledelayline]->gain(1, interpot);
  }
  if (gronint >= 100 && gronint < 250) {
    interpot = map(gronint, 100, 250, 0, 1);
    delaypremix[2 * ledelayline]->gain(1, 1 - interpot);
    delaypremix[2 * ledelayline]->gain(2, interpot);
  }
  if (gronint >= 250 && gronint < 400) {
    interpot = map(gronint, 250, 400, 0, 1);
    delaypremix[2 * ledelayline]->gain(2, 1 - interpot);
    delaypremix[2 * ledelayline]->gain(3, interpot);
  }
  if (gronint >= 400 && gronint < 550) {
    interpot = map(gronint, 400, 550, 0, 1);
    delaypremix[2 * ledelayline]->gain(3, 1 - interpot);
    delaypremix[2 * ledelayline + 1]->gain(0, interpot);
  }
  if (gronint >= 550 && gronint < 700) {
    interpot = map(gronint, 550, 700, 0, 1);
    delaypremix[2 * ledelayline + 1]->gain(0, 1 - interpot);
    delaypremix[2 * ledelayline + 1]->gain(1, interpot);
  }
  if (gronint >= 700 && gronint < 850) {
    interpot = map(gronint, 700, 850, 0, 1);
    delaypremix[2 * ledelayline + 1]->gain(1, 1 - interpot);
    delaypremix[2 * ledelayline + 1]->gain(2, interpot);
  }
  if (gronint >= 850 && gronint <= 1024) {
    interpot = map(gronint, 850, 1024, 0, 1);
    delaypremix[2 * ledelayline + 1]->gain(2, 1 - interpot);
    delaypremix[2 * ledelayline + 1]->gain(3, interpot);
  }
  AudioInterrupts();
}
void delayfeedback(byte lefilter, float lesmallfloat) {
  // delay feedback
  if (smallfloat <= 0.1) {
    delayprefeed[lefilter]->gain(0, 0);
    delayprefeed[lefilter]->gain(1, 0);
    delayfeedbackmix[lefilter]->gain(0, 1.0);
    delayfeedbackmix[lefilter]->gain(1, 0);
  } else {
    delayprefeed[lefilter]->gain(0, 1.0);
    delayprefeed[lefilter]->gain(1, 1.0);
    delayfeedbackmix[lefilter]->gain(0, 1.0 - lesmallfloat);
    delayfeedbackmix[lefilter]->gain(1, lesmallfloat);
  }
  // restartdelayline(lefilter);
}

void delaytimingselect(int lefilter, int leselecta) {
  int leselectee = map(leselecta, 0, 127, 0, 7);

  for (int j = 0; j < 4; j++) {
    delaypremix[2 * lefilter]->gain(j, 0);
    delaypremix[2 * lefilter + 1]->gain(j, 0);
  }
  if (leselectee < 4) {
    delaypremix[2 * lefilter]->gain(leselectee, 1);
  }
  if (leselectee >= 4) {
    delaypremix[2 * lefilter + 1]->gain(leselectee - 4, 1);
  }
  // restartdelayline(lefilter);
}

void restartdelayline(int lefilter) {
  
  delaymultiplier[lefilter] = delayVknobs[lefilter][1] + 1;
  delaytimingselect(lefilter, delayVknobs[lefilter][0]);

  delayfeedback(lefilter, (delayVknobs[lefilter][2] / 127.0) * 0.45);
  //8 is delay obj tap channels
  for (int j = 0; j < 8; j++) {

    lesdelays[lefilter]->delay(j, delaymultiplier[lefilter] * (j + 2));
  }
}
void stopdelayline(int lefilter) {

  for (int j = 0; j < 8; j++) {
    lesdelays[lefilter]->disable(j);
  }
}

void changebiquadfreqvalue(byte lebiquad, int valub) {
  // valub range 1024
  bqfreq[lebiquad][bqstage[lebiquad]] = valub * 3;
  biquadcontrols(lebiquad);
}

void displayfxVcontrols(byte fxinstance) {
  if (sublevels[2] == 6) {
    // Serial.print("selected biquad") ;
    biquadVpanel(fxinstance);
  }

  if (sublevels[2] == 7) {
    //  Serial.print("selected filter") ;
    filterVpanel(fxinstance);
  }
  if (sublevels[2] == 8) {
    //  Serial.print("selected delay") ;
    delayVpanel(fxinstance);
  }

  if (sublevels[2] == 1) {
    //   Serial.print("selected reverb") ;
    reverbVpanel(fxinstance);
  }
  if (sublevels[2] == 3) {
    //   Serial.print("selected bitcrusher") ;
    bitcrusherVpanel(fxinstance);
  }
  if (sublevels[2] == 2) {
    //   Serial.print("selected granular") ;
    granularVpanel(fxinstance);
  }
  if (sublevels[2] == 5) {
    //   Serial.print("selected granular") ;
    chorusVpanel(fxinstance);
  }
  if (sublevels[2] == 4) {
    //   Serial.print("selected granular") ;
    flangerVpanel(fxinstance);
  }
  if (sublevels[2] == 9 || sublevels[2] == 0) {
    navlevel--;
  }
}
void flangercontrols(byte lefilter) {
  flangeoffset =
      round((flangerVknobs[lefilter][0] / 127.0) * FLANGE_DELAY_LENGTH / 4);
  flangedepth =
      round((flangerVknobs[lefilter][1] / 127.0) * FLANGE_DELAY_LENGTH / 4);
  flangefreq = (double)(flangerVknobs[lefilter][2] / 127.0) * 2;
  // AudioNoInterrupts();
  flange[lefilter]->voices(flangeoffset, flangedepth, flangefreq);
  // AudioInterrupts();
}
void flangerVpanelAction(byte lefilter) {
  if (navlevel == 4) {
    // AudioNoInterrupts();
    byte slct = sublevels[3];
    // offset
    if (slct == 0) {
      navrange = 127;
      flangerVknobs[lefilter][0] = sublevels[4];
      flangercontrols(lefilter);
    }
    // depth
    if (slct == 1) {
      navrange = 127;
      flangerVknobs[lefilter][1] = sublevels[4];
      flangercontrols(lefilter);
      // apply
    }
    // delayRate
    // depth
    if (slct == 2) {
      navrange = 127;
      flangerVknobs[lefilter][2] = sublevels[4];
      flangercontrols(lefilter);
      // apply
    }
    if (slct == 3) {
      navrange = 100;

      WetMixMasters[(fxmoduleisconnected[sublevels[2]][lefilter] + 1)] = sublevels[4] / 100.0;
      wetmixmastercontrols();
      // le303filterzwet = (mixle303ffilterzVknobs[2])/127.0 ;
      // applygain
      // le303filterzWet();
    }
  }

  // to avoid setting up a stage unconfigured while browsing
  // if (bqfreq[0][bqstage[0]] >= 303) {
  // TODO filtercontrols like biquad control
  //  le303filtercontrols();
  // AudioInterrupts();
  //}

  if (navlevel > 4) {

    returntonav(3);
  }
}

void flangerVpanelSelector(byte lefilter) {
  byte knobradius = 11;
  byte centercirclex = 15 + knobradius;
  byte centercircley = 16 + knobradius;
  byte startlex2 = 67;
  byte totbartall = 37;
  byte topwbarstart = 16;
  byte wbarwidth2 = 8;
  if (navlevel == 3) {
    navrange = 3;
  }
  byte slct = sublevels[3];
  // size
  if (slct == 0) {
    sublevels[4] = flangerVknobs[lefilter][0];
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2,
                         SSD1306_WHITE);
  }
  // damp
  if (slct == 1) {
    sublevels[4] = flangerVknobs[lefilter][1];
    canvasBIG.drawCircle(centercirclex + 40, centercircley, knobradius - 2,
                         SSD1306_WHITE);
  }

  if (slct == 2) {
    sublevels[4] = flangerVknobs[lefilter][2];
    canvasBIG.drawCircle(centercirclex + 40 + 40, centercircley, knobradius - 2,
                         SSD1306_WHITE);
  }

  // wet
  if (slct == 3) {
    sublevels[4] =
        round(WetMixMasters[(fxmoduleisconnected[sublevels[2]][lefilter] + 1)] *
              100.0);
    canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall,
                       wbarwidth2 - 4, SSD1306_WHITE);
    canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
  }
}

void flangerVpanel(byte lefilter) {

  flangerVpanelAction(lefilter);
  byte knobradius = 11;
  byte centercirclex = 15 + knobradius;
  byte centercircley = 16 + knobradius;
  byte ftVcursorpointx;
  byte ftVcursorpointy;

  float coeffangle;
  byte totbartall = 37;
  byte topwbarstart = 16;
  byte wbarwidth2 = 8;
  byte barsize;
  byte startlex2 = 67;
  display.clearDisplay();
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(1);
  canvastitle.print("Flanger ");
  canvastitle.print(lefilter + 1);
  //  flangerVknobs[lefilter][0] ;
  // float dephtflange = flangerVknobs[lefilter][1]/127.0 ;
  // float freqflange = flangerVknobs[lefilter][2]/127.0 ;
  // voices(flangeoffset, flangedepth, flangefreq);
  // Roomsize
  coeffangle =
      (6.2831 - (flangerVknobs[lefilter][0] / 127.0) * 6.2831) + 3.1416;
  canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
  ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
  ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
  canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                     ftVcursorpointy, SSD1306_WHITE);
  canvasBIG.setCursor(centercirclex - knobradius + 1,
                      centercircley + knobradius + 4);
  canvasBIG.setTextSize(1);

  canvasBIG.print(
      round((flangerVknobs[lefilter][0] / 127.0) * FLANGE_DELAY_LENGTH / 4));
  // canvasBIG.setCursor(centercirclex-knobradius+1, 8);
  canvasBIG.setCursor(centercirclex - knobradius - 6,
                      centercircley + knobradius + 4 + 10);
  canvasBIG.print("Offset");

  // damping
  coeffangle =
      (6.2831 - (flangerVknobs[lefilter][1] / 127.0) * 6.2831) + 3.1416;
  centercirclex = centercirclex + 40;
  canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
  ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
  ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
  canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                     ftVcursorpointy, SSD1306_WHITE);
  canvasBIG.setCursor(centercirclex - knobradius + 1,
                      centercircley + knobradius + 4);
  canvasBIG.setTextSize(1);
  canvasBIG.print(
      round((flangerVknobs[lefilter][1] / 127.0) * FLANGE_DELAY_LENGTH / 4));
  // canvasBIG.setCursor(centercirclex-knobradius+1, 8);
  canvasBIG.setCursor(centercirclex - knobradius - 2,
                      centercircley + knobradius + 4 + 10);
  canvasBIG.print("Depth");

  coeffangle =
      (6.2831 - (flangerVknobs[lefilter][2] / 127.0) * 6.2831) + 3.1416;
  centercirclex = centercirclex + 40;
  canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
  ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
  ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
  canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                     ftVcursorpointy, SSD1306_WHITE);
  canvasBIG.setCursor(centercirclex - knobradius + 1,
                      centercircley + knobradius + 4);
  canvasBIG.setTextSize(1);
  canvasBIG.print(((flangerVknobs[lefilter][2] / 127.0) * 2), 2);
  canvasBIG.setCursor(centercirclex - knobradius - 2,
                      centercircley + knobradius + 4 + 10);
  // canvasBIG.setCursor(centercirclex-knobradius+1, 8);
  canvasBIG.print("Delay");

  // wetbar
  barsize =
      round(WetMixMasters[(fxmoduleisconnected[sublevels[2]][lefilter] + 1)] *
            (totbartall - 4));
  canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall,
                          wbarwidth2, 2, SSD1306_WHITE);
  canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4,
                     SSD1306_WHITE);
  canvasBIG.setCursor(startlex2 - 6, 0);
  canvasBIG.print("Wet:");

  flangerVpanelSelector(lefilter);

  dodisplay();
}

void choruscontrols(byte lefilter) {
  chorus[lefilter]->voices(round((chorusVknobs[lefilter] / 127.0) * 8));
}

void chorusVpanelAction(byte lefilter) {
  if (navlevel == 4) {
    // AudioNoInterrupts();
    byte slct = sublevels[3];
    // fq
    if (slct == 0) {
      navrange = 127;
      chorusVknobs[lefilter] = sublevels[4];
      choruscontrols(lefilter);
    }
    // res

    if (slct == 1) {
      navrange = 100;
      WetMixMasters[(fxmoduleisconnected[sublevels[2]][lefilter] + 1)] =
          sublevels[4] / 100.0;

      wetmixmastercontrols();
      // le303filterzwet = (mixle303ffilterzVknobs[2])/127.0 ;
      // applygain
      // le303filterzWet();
    }
  }

  // to avoid setting up a stage unconfigured while browsing
  // if (bqfreq[0][bqstage[0]] >= 303) {
  // TODO filtercontrols like biquad control
  //  le303filtercontrols();
  // AudioInterrupts();
  //}

  if (navlevel > 4) {

    returntonav(3);
  }
}

void chorusVpanelSelector(byte lefilter) {

  byte knobradius = 16;
  byte centercirclex = 48 + knobradius;
  byte centercircley = 16 + knobradius;
  byte startlex2 = 67;
  byte totbartall = 37;
  byte topwbarstart = 16;
  byte wbarwidth2 = 8;
  if (navlevel == 3) {
    navrange = 1;
  }
  int slct = sublevels[3];
  // size
  if (slct == 0) {
    sublevels[4] = chorusVknobs[lefilter];
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2,
                         SSD1306_WHITE);
  }

  // wet
  if (slct == 1) {
    sublevels[4] =
        round(WetMixMasters[(fxmoduleisconnected[sublevels[2]][lefilter] + 1)] *
              100.0);
    canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall,
                       wbarwidth2 - 4, SSD1306_WHITE);
    canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
  }
}

void chorusVpanel(byte lefilter) {

  chorusVpanelAction(lefilter);
  byte knobradius = 16;
  byte centercirclex = 48 + knobradius;
  byte centercircley = 16 + knobradius;
  byte ftVcursorpointx;
  byte ftVcursorpointy;

  float coeffangle;
  byte totbartall = 37;
  byte topwbarstart = 16;
  byte wbarwidth2 = 8;
  byte barsize;
  byte startlex2 = 67;
  display.clearDisplay();
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(1);
  canvastitle.print("Chorus ");
  canvastitle.print(lefilter + 1);

  float leroomsize = chorusVknobs[lefilter] / 127.0;
  // Roomsize
  coeffangle = (6.2831 - (leroomsize)*6.2831) + 3.1416;
  canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
  ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
  ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
  canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                     ftVcursorpointy, SSD1306_WHITE);
  canvasBIG.setCursor(centercirclex - knobradius + 5,
                      centercircley + knobradius + 4);
  canvasBIG.setTextSize(1);
  canvasBIG.print(round((chorusVknobs[lefilter] / 127.0) * 8));
  canvasBIG.setCursor(centercirclex - knobradius - 1, 8);
  canvasBIG.print("Voices");

  // wetbar
  barsize =
      round(WetMixMasters[(fxmoduleisconnected[sublevels[2]][lefilter] + 1)] *
            (totbartall - 4));
  canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall,
                          wbarwidth2, 2, SSD1306_WHITE);
  canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4,
                     SSD1306_WHITE);
  canvasBIG.setCursor(startlex2 - 6, 0);
  canvasBIG.print("Wet:");

  chorusVpanelSelector(lefilter);

  dodisplay();
}

void toggle_granular(byte lefilter){
  if (granular_toggled[lefilter]) {
    granular[lefilter]->begin(granularMemory, GRANULAR_MEMORY_SIZE);
    // speed in 0.125 to 8.0,
    float g_speed = 0.125 + (map(granularVknobs[lefilter][1],0,127,0,7875)/1000.0);
    Serial.println(g_speed);
    granular[lefilter]->setSpeed(g_speed);
  } else {
    granular[lefilter]->stop();
  }
}

void granular_pitch_shift(byte lefilter){
  // up to 1/3 of GRANULAR_MEMORY_SIZE 
  //float leratio = (granularVknobs[lefilter][1] / 127.0) * 3.0;
  int maxgrain = (int)(0.027 * GRANULAR_MEMORY_SIZE );// up to (GRANULAR_MEMORY_SIZE / 290) ms if grain is 12800 so ratio of 0.027 of GRANULAR_MEMORY_SIZE
  
  float legrainleng = 1.0 * map(granularVknobs[lefilter][0],0,127,1,maxgrain) ;
   if (granular_shifting[lefilter]) {
    
    granular[lefilter]->begin(granularMemory, GRANULAR_MEMORY_SIZE);
    float speed_gra = 0.125 + (map(granularVknobs[lefilter][1],0,127,0,7875)/1000.0);
    granular[lefilter]->setSpeed(speed_gra);
    granular[lefilter]->beginPitchShift(legrainleng);
  } else {
    granular[lefilter]->stop();
  }
  Serial.println("");
  Serial.print("granular shifting ");
  Serial.print(granular_shifting[ccfxlineselector]);
}

void granular_freeze(byte lefilter){
  int maxgrain = (int)(0.027 * GRANULAR_MEMORY_SIZE );// up to (GRANULAR_MEMORY_SIZE / 290) ms if grain is 12800 so ratio of 0.027 of GRANULAR_MEMORY_SIZE
  float legrainleng = 0.75*map(granularVknobs[lefilter][0],0,127,1,maxgrain) ;
  if (granular_freezing[lefilter]) {
    granular[lefilter]->begin(granularMemory, GRANULAR_MEMORY_SIZE);
    float speed_gra = 0.125 + (map(granularVknobs[lefilter][1],0,127,0,7875)/1000.0);
    granular[lefilter]->setSpeed(speed_gra);
    granular[lefilter]->beginFreeze(legrainleng);
      Serial.println("");
  Serial.print(legrainleng);

  } else {
    granular[lefilter]->stop();
  }
}

void granularcontrols(byte lefilter) {

    float g_speed = 0.125 + (map(granularVknobs[lefilter][1],0,127,0,7875)/1000.0);
    Serial.println(g_speed);
    granular[lefilter]->setSpeed(g_speed);
  //map(
  //granular[lefilter]->stop();
}

void granularVpanelAction(byte lefilter) {
  //  float leratio;
  //
  //  int legrainleng ;
  //  legrainleng = (granularVknobs[lefilter][0] / 127.0) * 2000  ;
  //    legrainleng = (granularVknobs[lefilter][1] / 127.0)*(1/3.0)*larrayleng ;
  //    leratio = (granularVknobs[lefilter][1] / 127.0)*2.0 ;
  if (navlevel == 4) {
    // AudioNoInterrupts();
    // leng 0 grainleng 1 speed 2 , frrezemode 3 , picthshit 4
    // g1= x0-1 *1/3 l0
    byte slct = sublevels[3];
    // g leng
    if (slct == 0) {
      navrange = 127;

      granularVknobs[lefilter][0] = sublevels[4];
      //granularcontrols(lefilter);
    }
    if (slct == 1) {
      navrange = 127;
      granularVknobs[lefilter][1] = sublevels[4];
      //granularcontrols(lefilter);
    }
    // res
    if (slct == 2) {
      granular_freezing[lefilter] = !granular_freezing[lefilter];
      granular_freeze(lefilter);
      returntonav(3);
    }
    if (slct == 3) {
      granular_shifting[lefilter] = !granular_shifting[lefilter];
      granular_pitch_shift(lefilter);
      returntonav(3);
    }

    if (slct == 4) {
      navrange = 100;
      //WetMixMasters[(fxmoduleisconnected[sublevels[2]][lefilter] + 1)] = sublevels[4] / 100.0;
      WetMixMasters[lefilter+1] = sublevels[4] / 100.0;
      wetmixmastercontrols();
    }
  }

  if (navlevel > 4) {

    returntonav(3);
  }
}

void granularVpanelSelector(byte lefilter) {

  const byte knobradius = 13;
  byte centercirclex = 10 + knobradius;
  byte centercircley = 16 + knobradius;
  const byte startlex2 = 67;
  const byte totbartall = 37;
  const byte topwbarstart = 16;
  const byte wbarwidth2 = 8;
  if (navlevel == 3) {
    navrange = 4;
  }
  byte slct = sublevels[3];
  // size
  if (slct == 0) {
    sublevels[4] = granularVknobs[lefilter][0];
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
  }
  // damp
  if (slct == 1) {
    sublevels[4] = granularVknobs[lefilter][1];
    canvasBIG.drawCircle(knobradius + 45, centercircley, knobradius - 2, SSD1306_WHITE);
  }
  if (slct == 2) {
    if (!granular_freezing[lefilter]) {
      canvasBIG.drawRoundRect(82, 18, 128 - 80 - 4, 20 - 4, 2, SSD1306_WHITE);
    } else {
      canvasBIG.drawRoundRect(82, 18, 128 - 80 - 4, 20 - 4, 2, SSD1306_BLACK);
    }
  }
  if (slct == 3) {
    if (!granular_shifting[lefilter]) {
      canvasBIG.drawRoundRect(82, 18 + 20 + 4, 128 - 80 - 4, 20 - 4, 2, SSD1306_WHITE);
    } else {
      canvasBIG.drawRoundRect(82, 18 + 20 + 4, 128 - 80 - 4, 20 - 4, 2, SSD1306_BLACK);
    }
  }

  // wet
  if (slct == 4) {
    sublevels[4] =
        round(WetMixMasters[(fxmoduleisconnected[sublevels[2]][lefilter] + 1)] *
              100.0);
    canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall,
                       wbarwidth2 - 4, SSD1306_WHITE);
    canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
  }
}

void granularVpanel(byte lefilter) {

  granularVpanelAction(lefilter);
  const byte knobradius = 13;
  byte centercirclex = 10 + knobradius;
  byte centercircley = 16 + knobradius;
  byte ftVcursorpointx;
  byte ftVcursorpointy;
  float coeffangle;
  const byte totbartall = 37;
  const byte topwbarstart = 16;
  const byte wbarwidth2 = 8;
  byte barsize;
  const byte startlex2 = 67;

  // legrainleng = round(((int)granularVknobs[lefilter][0] / 127.0)*(1/3.0)) ;
  int legrainleng = map(granularVknobs[lefilter][0],0,127,1,GRANULAR_MEMORY_SIZE);
  float leratio = 0.125 + (map(granularVknobs[lefilter][1],0,127,0,7875)/1000.0);

  display.clearDisplay();
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(1);
  canvastitle.print("Granular ");
  canvastitle.print(lefilter + 1);
  float ledamping = granularVknobs[lefilter][1] / 127.0;
  float leroomsize = granularVknobs[lefilter][0] / 127.0;
  // Roomsize
  coeffangle = (6.2831 - (leroomsize)*6.2831) + 3.1416;
  canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
  ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
  ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
  canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                     ftVcursorpointy, SSD1306_WHITE);
  canvasBIG.setCursor(centercirclex - knobradius + 1,
                      centercircley + knobradius + 4);
  canvasBIG.setTextSize(1);
  canvasBIG.setTextColor(SSD1306_WHITE);
  canvasBIG.print(legrainleng);
  canvasBIG.setCursor(centercirclex - knobradius + 1, 8);
  canvasBIG.print("Grain");

  // damping
  coeffangle = (6.2831 - (ledamping)*6.2831) + 3.1416;
  centercirclex = knobradius + 45;
  canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
  ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
  ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
  canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                     ftVcursorpointy, SSD1306_WHITE);
  canvasBIG.setCursor(centercirclex - knobradius + 1,
                      centercircley + knobradius + 4);
  canvasBIG.setTextSize(1);
  canvasBIG.print(leratio, 1);
  canvasBIG.setCursor(centercirclex - knobradius + 1, 8);
  canvasBIG.print("Ratio");
  if (!granular_freezing[lefilter]) {
    canvasBIG.drawRoundRect(80, 16, 128 - 80, 20, 2, SSD1306_WHITE);
    canvasBIG.setTextColor(SSD1306_WHITE);
    canvasBIG.setCursor(87, 16 + 6);
    canvasBIG.print("Freeze");
  } else {
    canvasBIG.fillRoundRect(80, 16, 128 - 80, 20, 2, SSD1306_WHITE);
    canvasBIG.setCursor(87, 16 + 6);
    canvasBIG.setTextColor(SSD1306_BLACK);
    canvasBIG.print("Freeze");
    canvasBIG.setTextColor(SSD1306_WHITE);
  }
  if (!granular_shifting[lefilter]) {
    canvasBIG.drawRoundRect(80, 16 + 20 + 4, 128 - 80, 20, 2, SSD1306_WHITE);
    canvasBIG.setCursor(87, 6 + 16 + 20 + 4);
    canvasBIG.setTextColor(SSD1306_WHITE);
    canvasBIG.print("Pitch");
  } else {
    canvasBIG.fillRoundRect(80, 16 + 20 + 4, 128 - 80, 20, 2, SSD1306_WHITE);
    canvasBIG.setCursor(87, 6 + 16 + 20 + 4);
    canvasBIG.setTextColor(SSD1306_BLACK);
    canvasBIG.print("Pitch");
    canvasBIG.setTextColor(SSD1306_WHITE);
  }
  // wetbar
  barsize = round(((WetMixMasters[(fxmoduleisconnected[sublevels[2]][lefilter] + 1)]) * (totbartall - 4)));
  //barsize = round(((WetMixMasters[lefilter+1]) * (totbartall - 4)));
  canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall, wbarwidth2, 2, SSD1306_WHITE);
  canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4, SSD1306_WHITE);
  canvasBIG.setCursor(startlex2 - 6, 0);
  canvasBIG.print("Wet:");
  granularVpanelSelector(lefilter);
  dodisplay();
}

void bitcrusherctrl(byte lefilter) {
  bitcrusher[lefilter]->bits(bitcrusherVknobs[lefilter][0]);
  bitcrusher[lefilter]->sampleRate(
      round((bitcrusherVknobs[lefilter][1] / 127.0) * 44100));
}

void bitcrusherVpanelAction(byte lefilter) {
  if (navlevel == 4) {
    // AudioNoInterrupts();
    byte slct = sublevels[3];
    // fq
    if (slct == 0) {
      navrange = 16;
      bitcrusherVknobs[lefilter][0] = sublevels[4];
      bitcrusherctrl(lefilter);
    }
    // res
    if (slct == 1) {
      navrange = 127;
      bitcrusherVknobs[lefilter][1] = sublevels[4];
      bitcrusherctrl(lefilter);
      // apply
    }

    if (slct == 2) {
      navrange = 100;
      WetMixMasters[(fxmoduleisconnected[sublevels[2]][lefilter] + 1)] = sublevels[4] / 100.0;
      wetmixmastercontrols();
      // le303filterzwet = (mixle303ffilterzVknobs[2])/127.0 ;
      // applygain
      // le303filterzWet();
    }
  }

  // to avoid setting up a stage unconfigured while browsing
  // if (bqfreq[0][bqstage[0]] >= 303) {
  // TODO filtercontrols like biquad control
  //  le303filtercontrols();
  // AudioInterrupts();
  //}

  if (navlevel > 4) {

    returntonav(3);
  }
}

void bitcrusherVpanelSelector(byte lefilter) {

  byte knobradius = 14;
  byte centercirclex = 25 + knobradius;
  byte centercircley = 16 + knobradius;
  byte startlex2 = 67;
  byte totbartall = 37;
  byte topwbarstart = 16;
  byte wbarwidth2 = 8;
  if (navlevel == 3) {
    navrange = 2;
  }
  int slct = sublevels[3];
  // size
  if (slct == 0) {
    sublevels[4] = bitcrusherVknobs[lefilter][0];
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
  }
  // damp
  if (slct == 1) {
    sublevels[4] = bitcrusherVknobs[lefilter][1];
    canvasBIG.drawCircle(knobradius + 68, centercircley, knobradius - 2, SSD1306_WHITE);
  }

  // wet
  if (slct == 2) {
    sublevels[4] = round(WetMixMasters[(fxmoduleisconnected[sublevels[2]][lefilter] + 1)] * 100.0);
    canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall, wbarwidth2 - 4, SSD1306_WHITE);
    canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
  }
}

void bitcrusherVpanel(byte lefilter) {

  bitcrusherVpanelAction(lefilter);
  byte knobradius = 14;
  byte centercirclex = 25 + knobradius;
  byte centercircley = 16 + knobradius;
  byte ftVcursorpointx;
  byte ftVcursorpointy;

  float coeffangle;
  byte totbartall = 37;
  byte topwbarstart = 16;
  byte wbarwidth2 = 8;
  byte barsize;
  byte startlex2 = 67;
  display.clearDisplay();
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(1);
  canvastitle.print("Bitcrusher ");
  canvastitle.print(lefilter + 1);
  float lesamperate = bitcrusherVknobs[lefilter][1] / 127.0;
  float lebitsz = bitcrusherVknobs[lefilter][0] / 16.0;
  // Roomsize
  coeffangle = (6.2831 - (lebitsz)*6.2831) + 3.1416;
  canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
  ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
  ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
  canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                     ftVcursorpointy, SSD1306_WHITE);
  canvasBIG.setCursor(centercirclex - knobradius + 5,
                      centercircley + knobradius + 4);
  canvasBIG.setTextSize(1);

  canvasBIG.print(lebitsz * 16, 0);
  canvasBIG.setCursor(centercirclex - knobradius + 1, 8);
  canvasBIG.print("Bits");

  // damping
  coeffangle = (6.2831 - (lesamperate)*6.2831) + 3.1416;
  centercirclex = knobradius + 68;
  canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
  ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
  ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
  canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                     ftVcursorpointy, SSD1306_WHITE);
  canvasBIG.setCursor(centercirclex - knobradius + 2,
                      centercircley + knobradius + 4);
  canvasBIG.setTextSize(1);
  canvasBIG.print(lesamperate * 44100, 0);
  canvasBIG.setCursor(centercirclex - knobradius, 8);
  canvasBIG.print("S.Rate");

  // wetbar
  barsize = round(
      ((WetMixMasters[(fxmoduleisconnected[sublevels[2]][lefilter] + 1)]) *
       (totbartall - 4)));
  canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall,
                          wbarwidth2, 2, SSD1306_WHITE);
  canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4,
                     SSD1306_WHITE);
  canvasBIG.setCursor(startlex2 - 6, 0);
  canvasBIG.print("Wet:");

  bitcrusherVpanelSelector(lefilter);

  dodisplay();
}

void freeverbscontrl(byte lefilter) {
  //AudioNoInterrupts();
  freeverbs[lefilter]->roomsize(reverbVknobs[lefilter][0] / 127.0);
  freeverbs[lefilter]->damping(reverbVknobs[lefilter][1] / 127.0);
  //AudioInterrupts();
}
void reverbVpanelAction(byte lefilter) {
  if (navlevel == 4) {
    // AudioNoInterrupts();
    byte slct = sublevels[3];
    // fq
    if (slct == 0) {
      navrange = 127;
      reverbVknobs[lefilter][0] = sublevels[4];
      freeverbscontrl(lefilter);
    }
    // res
    if (slct == 1) {
      navrange = 127;
      reverbVknobs[lefilter][1] = sublevels[4];
      freeverbscontrl(lefilter);
      // apply
    }

    if (slct == 2) {
      navrange = 100;
      WetMixMasters[(fxmoduleisconnected[sublevels[2]][lefilter] + 1)] =
          sublevels[4] / 100.0;
      wetmixmastercontrols();
      // le303filterzwet = (mixle303ffilterzVknobs[2])/127.0 ;
      // applygain
      // le303filterzWet();
    }
  }

  // to avoid setting up a stage unconfigured while browsing
  // if (bqfreq[0][bqstage[0]] >= 303) {
  // TODO filtercontrols like biquad control
  //  le303filtercontrols();
  // AudioInterrupts();
  //}

  if (navlevel > 4) {

    returntonav(3);
  }
}

void reverbVpanelSelector(byte lefilter) {

  byte knobradius = 14;
  byte centercirclex = 25 + knobradius;
  byte centercircley = 16 + knobradius;
  byte startlex2 = 67;
  byte totbartall = 37;
  byte topwbarstart = 16;
  byte wbarwidth2 = 8;
  if (navlevel == 3) {
    navrange = 2;
  }
  int slct = sublevels[3];
  // size
  if (slct == 0) {
    sublevels[4] = reverbVknobs[lefilter][0];
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2,
                         SSD1306_WHITE);
  }
  // damp
  if (slct == 1) {
    sublevels[4] = reverbVknobs[lefilter][1];
    canvasBIG.drawCircle(knobradius + 68, centercircley, knobradius - 2,
                         SSD1306_WHITE);
  }

  // wet
  if (slct == 2) {
    sublevels[4] =
        round(WetMixMasters[(fxmoduleisconnected[sublevels[2]][lefilter] + 1)] *
              100.0);
    canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall,
                       wbarwidth2 - 4, SSD1306_WHITE);
    canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
  }
}

void reverbVpanel(byte lefilter) {

  reverbVpanelAction(lefilter);
  byte knobradius = 14;
  byte centercirclex = 25 + knobradius;
  byte centercircley = 16 + knobradius;
  byte ftVcursorpointx;
  byte ftVcursorpointy;

  float coeffangle;
  byte totbartall = 37;
  byte topwbarstart = 16;
  byte wbarwidth2 = 8;
  byte barsize;
  byte startlex2 = 67;
  display.clearDisplay();
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(1);
  canvastitle.print("Reverb ");
  canvastitle.print(lefilter + 1);
  float ledamping = reverbVknobs[lefilter][1] / 127.0;
  float leroomsize = reverbVknobs[lefilter][0] / 127.0;
  // Roomsize
  coeffangle = (6.2831 - (leroomsize)*6.2831) + 3.1416;
  canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
  ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
  ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
  canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                     ftVcursorpointy, SSD1306_WHITE);
  canvasBIG.setCursor(centercirclex - knobradius + 1,
                      centercircley + knobradius + 4);
  canvasBIG.setTextSize(1);
  canvasBIG.print(leroomsize, 2);
  canvasBIG.setCursor(centercirclex - knobradius + 1, 8);
  canvasBIG.print("Size");

  // damping
  coeffangle = (6.2831 - (ledamping)*6.2831) + 3.1416;
  centercirclex = knobradius + 68;
  canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
  ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
  ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
  canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                     ftVcursorpointy, SSD1306_WHITE);
  canvasBIG.setCursor(centercirclex - knobradius + 1,
                      centercircley + knobradius + 4);
  canvasBIG.setTextSize(1);
  canvasBIG.print(ledamping, 2);
  canvasBIG.setCursor(centercirclex - knobradius + 1, 8);
  canvasBIG.print("Damping");

  // wetbar
  barsize = round(
      ((WetMixMasters[(fxmoduleisconnected[sublevels[2]][lefilter] + 1)]) *
       (totbartall - 4)));
  canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall,
                          wbarwidth2, 2, SSD1306_WHITE);
  canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4,
                     SSD1306_WHITE);
  canvasBIG.setCursor(startlex2 - 6, 0);
  canvasBIG.print("Wet:");

  reverbVpanelSelector(lefilter);

  dodisplay();
}

// delaytimingselect(int lefilter, float leselecta)
// delayfeedback(int lefilter, float leselecta)
// delaymultiplier

void delayVpanelAction(byte lefilter) {
  if (navlevel == 4) {
    // AudioNoInterrupts();
    byte slct = sublevels[3];
    // time
    if (slct == 0) {
      navrange = 127;
      delayVknobs[lefilter][0] = sublevels[4];
      // delaytimingselect(lefilter, delayVknobs[lefilter][0]);
      restartdelayline(lefilter);
    }
    // timeX
    if (slct == 1) {
      navrange = 127;
      delayVknobs[lefilter][1] = sublevels[4];

      restartdelayline(lefilter);
      // apply
    }
    // feedback
    // depth
    if (slct == 2) {
      navrange = 127;
      delayVknobs[lefilter][2] = sublevels[4];
      // delayfeedback(lefilter, (delayVknobs[lefilter][2]/127.0)*0.45);
      restartdelayline(lefilter);
      // apply
    }
    if (slct == 3) {
      navrange = 100;
      WetMixMasters[(fxmoduleisconnected[sublevels[2]][lefilter] + 1)] =
          sublevels[4] / 100.0;
      wetmixmastercontrols();
      // le303filterzwet = (mixle303ffilterzVknobs[2])/127.0 ;
      // applygain
      // le303filterzWet();
    }
  }

  // to avoid setting up a stage unconfigured while browsing
  // if (bqfreq[0][bqstage[0]] >= 303) {
  // TODO filtercontrols like biquad control
  //  le303filtercontrols();
  // AudioInterrupts();
  //}

  if (navlevel > 4) {

    returntonav(3);
  }
}

void delayVpanelSelector(byte lefilter) {
  byte knobradius = 11;
  byte centercirclex = 15 + knobradius;
  byte centercircley = 16 + knobradius;
  byte startlex2 = 67;
  byte totbartall = 37;
  byte topwbarstart = 16;
  byte wbarwidth2 = 8;
  if (navlevel == 3) {
    navrange = 3;
  }
  byte slct = sublevels[3];
  // size
  if (slct == 0) {
    sublevels[4] = delayVknobs[lefilter][0];
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2,
                         SSD1306_WHITE);
  }
  // damp
  if (slct == 1) {
    sublevels[4] = delayVknobs[lefilter][1];
    canvasBIG.drawCircle(centercirclex + 40, centercircley, knobradius - 2,
                         SSD1306_WHITE);
  }

  if (slct == 2) {
    sublevels[4] = delayVknobs[lefilter][2];
    canvasBIG.drawCircle(centercirclex + 40 + 40, centercircley, knobradius - 2,
                         SSD1306_WHITE);
  }

  // wet
  if (slct == 3) {
    sublevels[4] =
        round(WetMixMasters[(fxmoduleisconnected[sublevels[2]][lefilter] + 1)] *
              100.0);
    canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall,
                       wbarwidth2 - 4, SSD1306_WHITE);
    canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
  }
}

void delayVpanel(byte lefilter) {

  delayVpanelAction(lefilter);
  byte knobradius = 11;
  byte centercirclex = 15 + knobradius;
  byte centercircley = 16 + knobradius;
  byte ftVcursorpointx;
  byte ftVcursorpointy;

  float coeffangle;
  byte totbartall = 37;
  byte topwbarstart = 16;
  byte wbarwidth2 = 8;
  byte barsize;
  byte startlex2 = 67;
  display.clearDisplay();
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(1);
  canvastitle.print("Delay ");
  canvastitle.print(lefilter + 1);
  float delaytime = delayVknobs[lefilter][0] / 127.0;
  float dephtflange = delayVknobs[lefilter][1] / 127.0;
  float freqflange = delayVknobs[lefilter][2] / 127.0;
  // voices(flangeoffset, flangedepth, flangefreq);
  // Roomsize
  coeffangle = (6.2831 - (delaytime)*6.2831) + 3.1416;
  canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
  ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
  ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
  canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                     ftVcursorpointy, SSD1306_WHITE);
  canvasBIG.setCursor(centercirclex - knobradius + 1,
                      centercircley + knobradius + 4);
  canvasBIG.setTextSize(1);

  canvasBIG.print(round((delayVknobs[lefilter][0] / 127.0) * 7));
  // canvasBIG.setCursor(centercirclex-knobradius+1, 8);
  canvasBIG.setCursor(centercirclex - knobradius - 6,
                      centercircley + knobradius + 4 + 10);
  canvasBIG.print("TSel");

  // damping
  coeffangle = (6.2831 - (dephtflange)*6.2831) + 3.1416;
  centercirclex = centercirclex + 40;
  canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
  ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
  ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
  canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                     ftVcursorpointy, SSD1306_WHITE);
  canvasBIG.setCursor(centercirclex - knobradius + 1,
                      centercircley + knobradius + 4);
  canvasBIG.setTextSize(1);
  canvasBIG.print(delayVknobs[lefilter][1]);
  // canvasBIG.setCursor(centercirclex-knobradius+1, 8);
  canvasBIG.setCursor(centercirclex - knobradius - 2,
                      centercircley + knobradius + 4 + 10);
  canvasBIG.print("TimeX");

  coeffangle = (6.2831 - (freqflange)*6.2831) + 3.1416;
  centercirclex = centercirclex + 40;
  canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
  ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
  ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
  canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                     ftVcursorpointy, SSD1306_WHITE);
  canvasBIG.setCursor(centercirclex - knobradius + 1,
                      centercircley + knobradius + 4);
  canvasBIG.setTextSize(1);
  canvasBIG.print(((delayVknobs[lefilter][2] / 127.0)), 2);
  canvasBIG.setCursor(centercirclex - knobradius - 2,
                      centercircley + knobradius + 4 + 10);
  // canvasBIG.setCursor(centercirclex-knobradius+1, 8);
  canvasBIG.print("Fback");

  // wetbar
  barsize = round(((WetMixMasters[(fxmoduleisconnected[sublevels[2]][lefilter] + 1)]) * (totbartall - 4)));
  canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall, wbarwidth2, 2, SSD1306_WHITE);
  canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4,
                     SSD1306_WHITE);
  canvasBIG.setCursor(startlex2 - 6, 0);
  canvasBIG.print("Wet:");

  delayVpanelSelector(lefilter);

  dodisplay();
}

void filterVpanelAction(byte lefilter) {
  if (navlevel == 4) {
    AudioNoInterrupts();
    byte slct = sublevels[3];
    // fq
    if (slct == 0) {
      navrange = 127;
      ffilterzVknobs[lefilter][0] = sublevels[4];
    }
    // res
    if (slct == 1) {
      navrange = 127;
      ffilterzVknobs[lefilter][1] = sublevels[4];
    }
    // octaves
    if (slct == 2) {
      navrange = 127;
      ffilterzVknobs[lefilter][2] = sublevels[4];
    }
    // lowpass
    if (slct == 3) {
      navrange = 127;
      mixffilterzVknobs[lefilter][0] = sublevels[4];
    }
    // bandpass
    if (slct == 4) {
      navrange = 127;
      mixffilterzVknobs[lefilter][1] = sublevels[4];
    }
    // high pass
    if (slct == 5) {
      navrange = 127;
      mixffilterzVknobs[lefilter][2] = sublevels[4];
    }
    if (slct == 6) {
      //navrange is 3 + 1 for none
      navrange = synths_count;
      filter_lfo_option = sublevels[4];
      if (filter_lfo_option < synths_count) {
        LFOonfilterz[lefilter] = filter_lfo_option;
      }
    }
    if (slct == 7) {
      navrange = 100;
      WetMixMasters[(fxmoduleisconnected[sublevels[2]][lefilter] + 1)] = sublevels[4] / 100.0;
      wetmixmastercontrols();
    }
    // to avoid setting up a stage unconfigured while browsing
    // if (bqfreq[lefilter][bqstage[lefilter]] >= 303) {
    // TODO filtercontrols like biquad control
    filtercontrols(lefilter);
    AudioInterrupts();
    //}
  }
  if (navlevel > 4) {

    returntonav(3);
  }
}

void lfoonfilterreplug(byte lefilter) {

  for (int i = 0; i < fxiterations; i++) {
    // Serial.print("disconnecting lfos ");
    // Serial.println(((4*lefilter)+i));
    LFOtoFilterz[((fxiterations * lefilter) + i)]->disconnect();
  }
  // LFO1toFilter1.disconnect();
  // Serial.println(LFO1toFilter1.isConnected);
  if (LFOonfilterz[lefilter] < 3) {
    LFOtoFilterz[((fxiterations * lefilter) + LFOonfilterz[lefilter])]
        ->connect();
  }
}
// TODO Fix this , fxlines have fixed lfos or at least persistent
// this currently unplugs lfos for all other fxlines who may have it == BAD
void unpluglfoonfilterz() {
  // fxiterations*fxiterations = 9
  for (int i = 0; i < 9; i++) {
    LFOtoFilterz[i]->disconnect();
  }
}

void filtercontrols(byte lefilter) {
  filterzfreq[lefilter] = (ffilterzVknobs[lefilter][0] / 127.0) * filterzrange;
  filterzreso[lefilter] = ((ffilterzVknobs[lefilter][1]) / 127.0) * 5;
  if (filterzreso[lefilter] < 0.7) {
    filterzreso[lefilter] = 0.7;
  }
  filterzoctv[lefilter] = ((ffilterzVknobs[lefilter][2]) / 127.0) * 7;
  filterzgainz[lefilter][0] = (mixffilterzVknobs[lefilter][0]) / 127.0;
  filterzgainz[lefilter][1] = (mixffilterzVknobs[lefilter][1]) / 127.0;
  filterzgainz[lefilter][2] = (mixffilterzVknobs[lefilter][2]) / 127.0;
  unpluglfoonfilterz();
  if (sublevels[4] < synths_count) {
    lfoonfilterreplug(lefilter);
  }
  for (int i = 0; i < 3; i++) {
    mixfilter[lefilter]->gain(i, filterzgainz[lefilter][i]);
  }
  filterz[lefilter]->frequency(filterzfreq[lefilter]);
  filterz[lefilter]->resonance(filterzreso[lefilter]);
  filterz[lefilter]->octaveControl(filterzoctv[lefilter]);
}
void filterVpanel(byte lefilter) {
  char LFOnamelist[4][6] = {"LFO1", "LFO2", "LFO3", "None"};
  filterVpanelAction(lefilter);
  byte knobradius = 9;
  byte centercirclex = 5 + knobradius;
  byte centercircley = 35 + knobradius;
  byte ftVcursorpointx;
  byte ftVcursorpointy;

  float coeffangle;
  byte totbartall = 37;
  byte topwbarstart = 16;
  byte wbarwidth = 9;
  byte wbarwidth2 = 8;
  byte barsize;
  byte startlex2 = 67;

  display.clearDisplay();
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(1);
  canvastitle.print("Filter ");
  canvastitle.print(lefilter + 1);
  canvastitle.setCursor(0, 8);
  // reflect lebq
  canvastitle.print("Ctrl: ");
  canvastitle.print((char *)LFOnamelist[filter_lfo_option]);

  //    canvastitle.setCursor(0,8);
  //    canvastitle.print("mode: ");
  //    canvastitle.print((char*)bqtypeLabels[bqtype[lefilter][bqstage[lefilter]]]);

  // bqfreq
  coeffangle =
      (6.2831 - (ffilterzVknobs[lefilter][0] / 127.0) * 6.2831) + 3.1416;
  canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
  ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
  ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
  canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                     ftVcursorpointy, SSD1306_WHITE);
  canvasBIG.setCursor(centercirclex - knobradius + 4,
                      centercircley + knobradius + 4);
  canvasBIG.setTextSize(1);
  canvasBIG.print("FQ");
  if (filterzfreq[lefilter] < 1000) {
    canvasBIG.setCursor(centercirclex - knobradius + 1, 24);
    canvasBIG.print(filterzfreq[lefilter], 0);
  }
  if ((round(filterzfreq[lefilter]) < 9900) &&
      (filterzfreq[lefilter] >= 1000)) {
    canvasBIG.setCursor(centercirclex - knobradius - 1, 24);
    canvasBIG.print(round(filterzfreq[lefilter]) / 1000.0, 1);
    canvasBIG.print("k");
  }
  if (filterzfreq[lefilter] >= 9900) {
    canvasBIG.setCursor(centercirclex - knobradius - 5, 24);
    canvasBIG.print(filterzfreq[lefilter] / 1000.0, 1);
    canvasBIG.print("k");
  }

  // resonnance
  coeffangle =
      (6.2831 - (ffilterzVknobs[lefilter][1] / 127.0) * 6.2831) + 3.1416;
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
  canvasBIG.setCursor(centercirclex - knobradius + 2, 24);
  canvasBIG.print(filterzreso[lefilter], 1);

  // octave
  coeffangle =
      (6.2831 - (ffilterzVknobs[lefilter][2] / 127.0) * 6.2831) + 3.1416;
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
  canvasBIG.setCursor(centercirclex - knobradius + 1, 24);
  canvasBIG.print(filterzoctv[lefilter], 1);

  barsize = round((filterzgainz[lefilter][0] * (totbartall - 4)));
  canvasBIG.drawRoundRect(81, topwbarstart, wbarwidth, totbartall, 2,
                          SSD1306_WHITE);
  canvasBIG.fillRect(81 + 2, (totbartall + topwbarstart - barsize - 2),
                     wbarwidth - 4, barsize, SSD1306_WHITE);
  canvasBIG.setCursor(81, totbartall + topwbarstart + 4);
  canvasBIG.print("LP");
  // canvasBIG.setCursor(80,18);
  // canvasBIG.print(bqgain[lefilter][bqstage[lefilter]]);
  barsize = round((filterzgainz[lefilter][1] * (totbartall - 4)));
  canvasBIG.drawRoundRect(98, topwbarstart, wbarwidth, totbartall, 2,
                          SSD1306_WHITE);
  canvasBIG.fillRect(98 + 2, (totbartall + topwbarstart - barsize - 2),
                     wbarwidth - 4, barsize, SSD1306_WHITE);
  canvasBIG.setCursor(97, totbartall + topwbarstart + 4);
  canvasBIG.print("BP");
  // canvasBIG.setCursor(93,18);
  // canvasBIG.print(bqgain[lefilter][bqstage[lefilter]]);
  barsize = round((filterzgainz[lefilter][2] * (totbartall - 4)));
  canvasBIG.drawRoundRect(115, topwbarstart, wbarwidth, totbartall, 2,
                          SSD1306_WHITE);
  canvasBIG.fillRect(115 + 2, (totbartall + topwbarstart - barsize - 2),
                     wbarwidth - 4, barsize, SSD1306_WHITE);
  canvasBIG.setCursor(114, totbartall + topwbarstart + 4);
  canvasBIG.print("HP");

  barsize = round(
      ((WetMixMasters[(fxmoduleisconnected[sublevels[2]][lefilter] + 1)]) *
       (totbartall - 4)));
  canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall,
                          wbarwidth2, 2, SSD1306_WHITE);
  canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4,
                     SSD1306_WHITE);
  canvasBIG.setCursor(startlex2 - 6, 0);
  canvasBIG.print("Wet:");
  // canvasBIG.setCursor(114,18);
  // canvasBIG.print(bqgain[lefilter][bqstage[lefilter]]);

  filterVpanelSelector(lefilter);

  dodisplay();
}

void filterVpanelSelector(byte lefilter) {

  byte knobradius = 9;
  byte centercirclex = 5 + knobradius;
  byte centercircley = 35 + knobradius;
  byte totbartall = 37;
  byte topwbarstart = 16;
  byte wbarwidth = 9;
  int wbarwidth2 = 8;
  byte startlex2 = 67;
  if (navlevel == 3) {
    navrange = 8;
  }
  byte slct = sublevels[3];
  // fq
  if (slct == 0) {
    sublevels[4] = ffilterzVknobs[lefilter][0];
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2,
                         SSD1306_WHITE);
  }
  // res
  if (slct == 1) {
    sublevels[4] = ffilterzVknobs[lefilter][1];
    canvasBIG.drawCircle(centercirclex + 25, centercircley, knobradius - 2,
                         SSD1306_WHITE);
  }
  // oct
  if (slct == 2) {
    sublevels[4] = ffilterzVknobs[lefilter][2];
    canvasBIG.drawCircle(centercirclex + 50, centercircley, knobradius - 2,
                         SSD1306_WHITE);
  }
  // lp
  if (slct == 3) {
    sublevels[4] = mixffilterzVknobs[lefilter][0];
    canvasBIG.drawRect(83, topwbarstart, wbarwidth - 4, totbartall,
                       SSD1306_WHITE);
  }
  // bp
  if (slct == 4) {
    sublevels[4] = mixffilterzVknobs[lefilter][1];
    canvasBIG.drawRect(100, topwbarstart, wbarwidth - 4, totbartall,
                       SSD1306_WHITE);
  }
  // hp
  if (slct == 5) {
    sublevels[4] = mixffilterzVknobs[lefilter][2];
    canvasBIG.drawRect(117, topwbarstart, wbarwidth - 4, totbartall,
                       SSD1306_WHITE);
  }
  // Select LFO
  if (slct == 6) {
    sublevels[4] = filter_lfo_option;
    canvasBIG.setCursor(64, 8);
    canvasBIG.print((char)9);
  }
  if (slct == 7) {
    sublevels[4] = round(WetMixMasters[(fxmoduleisconnected[sublevels[2]][lefilter] + 1)] * 100.0);
    canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0, totbartall, wbarwidth2, SSD1306_WHITE);
    canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
  }
}

void biquadVpanelAction(byte lebiquad) {
  if (navlevel == 4) {
    byte slct = sublevels[3];
    // stage
    if (slct == 0) {
      navrange = 3;
      bqstage[lebiquad] = sublevels[4];
    }
    // mode
    if (slct == 1) {
      navrange = 5;
      bqtype[lebiquad][bqstage[lebiquad]] = sublevels[4];
    }
    // freq
    if (slct == 2) {
      navrange = 127;
      bqVpot[lebiquad][bqstage[lebiquad]][0] = sublevels[4];
      bqfreq[lebiquad][bqstage[lebiquad]] =
          (((bqVpot[lebiquad][bqstage[lebiquad]][0]) / 127.0) * bqrange) + 101;
    }
    // slope or Q
    if (slct == 3) {
      navrange = 127;
      bqVpot[lebiquad][bqstage[lebiquad]][1] = sublevels[4];
      bqslope[lebiquad][bqstage[lebiquad]] =
          (bqVpot[lebiquad][bqstage[lebiquad]][1]) / 127.0;
    }
    // gain
    if (slct == 5) {
      navrange = 127;
      bqVpot[lebiquad][bqstage[lebiquad]][2] = sublevels[4];
      bqgain[lebiquad][bqstage[lebiquad]] =
          (bqVpot[lebiquad][bqstage[lebiquad]][2]) / 127.0;
    }
    // to avoid setting up a stage unconfigured while browsing
    if (bqfreq[lebiquad][bqstage[lebiquad]] >= 101) {
      biquadcontrols(lebiquad);
    }

    if (slct == 4) {
      navrange = 100;
      WetMixMasters[(fxmoduleisconnected[sublevels[2]][lebiquad] + 1)] =
          sublevels[4] / 100.0;
      wetmixmastercontrols();
      // le303filterzwet = (mixle303ffilterzVknobs[2])/127.0 ;
      // applygain
      // le303filterzWet();
    }
  }
  if (navlevel > 4) {

    returntonav(3);
  }
}

void biquadVpanel(byte lebiquad) {
  char bqtypeLabels[6][12] = {"Low Pass", "High Pass", "Band Pass",
                              "Notch",    "LowShelf",  "High Shelf"};
  biquadVpanelAction(lebiquad);
  byte knobradius = 12;
  byte centercirclex = 10 + knobradius;
  byte centercircley = 28 + knobradius;
  byte wbarwidth2 = 7;
  byte bqVcursorpointx;
  byte bqVcursorpointy;
  byte startlex2 = 67;
  float coeffangle;
  byte totbartall = 24;
  byte topwbarstart = 16 + 12;
  byte wbarwidth = 9;
  byte barsize = round((bqVpot[lebiquad][bqstage[lebiquad]][2] / 127.0) *
                       (totbartall - 4));

  display.clearDisplay();
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(1);
  canvastitle.print("Biquad ");
  canvastitle.print(lebiquad + 1);
  canvastitle.setCursor(107, 8);
  // reflect lebq
  canvastitle.print("s:");
  canvastitle.print(bqstage[lebiquad] + 1);

  canvastitle.setCursor(0, 8);
  canvastitle.print("mode: ");
  canvastitle.print((char *)bqtypeLabels[bqtype[lebiquad][bqstage[lebiquad]]]);
  // bqfreq
  coeffangle =
      (6.2831 - (bqVpot[lebiquad][bqstage[lebiquad]][0] / 127.0) * 6.2831) +
      3.1416;
  canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
  bqVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
  bqVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
  canvasBIG.drawLine(centercirclex, centercircley, bqVcursorpointx,
                     bqVcursorpointy, SSD1306_WHITE);
  canvasBIG.setCursor(centercirclex - knobradius,
                      centercircley + knobradius + 4);
  canvasBIG.setTextSize(1);
  canvasBIG.print("Freq.");
  if (bqfreq[lebiquad][bqstage[lebiquad]] < 1000) {
    canvasBIG.setCursor(centercirclex - knobradius + 4, 18);
  }
  if ((bqfreq[lebiquad][bqstage[lebiquad]] < 10000) &&
      (bqfreq[lebiquad][bqstage[lebiquad]] >= 1000)) {
    canvasBIG.setCursor(centercirclex - knobradius + 2, 18);
  }
  if (bqfreq[lebiquad][bqstage[lebiquad]] >= 10000) {
    canvasBIG.setCursor(centercirclex - knobradius - 2, 18);
  }
  canvasBIG.print(bqfreq[lebiquad][bqstage[lebiquad]], 0);
  // bqslope
  coeffangle =
      (6.2831 - (bqVpot[lebiquad][bqstage[lebiquad]][1] / 127.0) * 6.2831) +
      3.1416;
  centercirclex = knobradius + 50;
  canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
  bqVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
  bqVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
  canvasBIG.drawLine(centercirclex, centercircley, bqVcursorpointx,
                     bqVcursorpointy, SSD1306_WHITE);
  canvasBIG.setCursor(centercirclex - knobradius,
                      centercircley + knobradius + 4);
  canvasBIG.setTextSize(1);
  canvasBIG.print("Slope");
  canvasBIG.setCursor(centercirclex - knobradius, 18);
  canvasBIG.print(bqslope[lebiquad][bqstage[lebiquad]]);
  // gain if  setLowShelf or sethighShelf
  if (bqtype[lebiquad][bqstage[lebiquad]] > 3) {
    canvasBIG.drawRoundRect(95, topwbarstart, wbarwidth, totbartall, 2,
                            SSD1306_WHITE);
    canvasBIG.fillRect(95 + 2, (totbartall + topwbarstart - barsize - 2),
                       wbarwidth - 4, barsize, SSD1306_WHITE);
    canvasBIG.setCursor(90, totbartall + topwbarstart + 4);
    canvasBIG.print("Gain");
    canvasBIG.setCursor(90, 18);
    canvasBIG.print(bqgain[lebiquad][bqstage[lebiquad]]);
  }
  barsize = round(
      ((WetMixMasters[(fxmoduleisconnected[sublevels[2]][lebiquad] + 1)]) *
       (totbartall + 13 - 4)));
  canvasBIG.drawRoundRect(topwbarstart - 12 + startlex2 + 4, 0, totbartall + 13,
                          wbarwidth2, 2, SSD1306_WHITE);
  canvasBIG.fillRect((topwbarstart - 12 + startlex2 + 6), 2, barsize,
                     wbarwidth2 - 4, SSD1306_WHITE);
  canvasBIG.setCursor(startlex2 - 6, 0);
  canvasBIG.print("Wet:");

  biquadVpanelSelector(lebiquad);

  dodisplay();
}

void biquadVpanelSelector(byte lebiquad) {
  byte startlex2 = 67;
  byte totbartall = 37;
  byte topwbarstart = 16;
  byte wbarwidth2 = 7;
  if (navlevel == 3) {
    navrange = 4;
    if (bqtype[lebiquad][bqstage[lebiquad]] > 3) {
      navrange = 5;
    }
  }
  byte slct = sublevels[3];
  // stage
  if (slct == 0) {
    sublevels[4] = bqstage[lebiquad];
    canvasBIG.setCursor(103, 9);
    canvasBIG.print((char)9);
  }
  // mode
  if (slct == 1) {
    sublevels[4] = bqtype[lebiquad][bqstage[lebiquad]];
    canvasBIG.setCursor(29, 8);
    canvasBIG.print((char)9);
  }
  // freq
  if (slct == 2) {
    sublevels[4] = bqVpot[lebiquad][bqstage[lebiquad]][0];
    canvasBIG.setCursor(20, 36);
    canvasBIG.print((char)9);
  }
  // slope
  if (slct == 3) {
    sublevels[4] = bqVpot[lebiquad][bqstage[lebiquad]][1];
    canvasBIG.setCursor(60, 36);
    canvasBIG.print((char)9);
  }
  // gain
  if (slct == 5) {
    sublevels[4] = bqVpot[lebiquad][bqstage[lebiquad]][2];
    canvasBIG.setCursor(89, 36);
    canvasBIG.print((char)9);
  }

  if (slct == 4) {
    sublevels[4] =
        round(WetMixMasters[(fxmoduleisconnected[sublevels[2]][lebiquad] + 1)] *
              100.0);
    canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall,
                       wbarwidth2 - 4, SSD1306_WHITE);
    canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
  }
}

void allfxcontrolled() {

  for (int i = 0; i < 3; i++) {
    if (bqfreq[i][bqstage[i]] >= 303) {
      biquadcontrols(i);
    }

    filtercontrols(i);
    restartdelayline(i);
    freeverbscontrl(i);
    bitcrusherctrl(i);
    //granularcontrols(i);
    choruscontrols(i);
    flangercontrols(i);
  }
}
