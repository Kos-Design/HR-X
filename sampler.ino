

const int FlashChipSelect = 6;

int samplesSelected = 0;

int recupsublevel;

void setlefilenamed(int lefolder, int lefile, char *lefname) {

  int fnamesize = strlen((char *)lefname);
  
  int foldersize = strlen((char *)samplefoldersregistered[lefolder]);

  for (int i = 0; i < fnamesize; i++) {

    samplefullpath[lefolder][lefile][foldersize + 10 + i] = lefname[i];
    if (i < fnamesize - 4) {
      samplebase[lefolder][lefile][i] = lefname[i];
    }
  }

  samplefullpath[lefolder][lefile][foldersize + 10 + fnamesize] = (char)'\0';
  samplebase[lefolder][lefile][fnamesize - 4] = (char)'\0';
}

void voidlastpathlisted() {
  for (int i = 0; i < 50; i++) {
    lastpathlisted[i] = (char)'\0';
  }
}
void setlastpathlisted(char *lepath) {
  voidlastpathlisted();
  for (int i = 0; i < (int)strlen((char *)lepath); i++) {
    lastpathlisted[i] = lepath[i];
  }
}

void playsamplepreview() {
  AudioNoInterrupts();
  playRawL.play((const char *)samplefullpath[sublevels[3]][sublevels[4]]);
  playRawR.play((const char *)samplefullpath[sublevels[3]][sublevels[4]]);
  AudioInterrupts();
}

void playflashsamplepreview() {
  AudioNoInterrupts();
  FlashRaw.play((const char *)Flashsamplename[sublevels[3]]);

  AudioInterrupts();
}
void playflashsamplepreviews4() {
  AudioNoInterrupts();
  FlashRaw.play((const char *)Flashsamplename[sublevels[4]]);

  AudioInterrupts();
}
void makenewmkdirpath() {
  // newSongpath
  synsetunites = 0;
  synsetdizaines = 0;
  Serial.println((char *)newmkdirpath);
  while (SD.exists((char *)newmkdirpath)) {
    findnextmkdirpath();
    Serial.println((char *)newmkdirpath);
  }
}

void findnextmkdirpath() {

  if (synsetunites < 9) {
    synsetunites++;
  } else {
    synsetunites = 0;
    if (synsetdizaines < 9) {
      synsetdizaines++;
    } else {
      synsetdizaines = 0;
    }
  }
  // tot-9  tot-10
  newmkdirpath[15] = synsetdizaines + '0';
  newmkdirpath[16] = synsetunites + '0';

  // "SONGS/SONG#00.TXT"
  // newSongpath[27] = {"/SOUNDSET/REC/REC-00.L.RAW"};
}
void initializenewmksamplefullpath() {
  for (int i = 0; i < 32; i++) {
    newmksamplefullpath[i] = (char)'\0';
  }
}
void makenewdumpedfilename(int leflashfile) {
  for (int i = 0; i < (int)strlen((char *)newmkdirpath); i++) {
    newmksamplefullpath[i] = newmkdirpath[i];
  }
  newmksamplefullpath[strlen((char *)newmkdirpath)] = (char)'/';
  for (int i = 0; i < (int)strlen((char *)Flashsamplename[i]); i++) {
    newmksamplefullpath[i + strlen((char *)newmkdirpath) + 1] =
        Flashsamplename[leflashfile][i];
  }
  Serial.print((char *)newmksamplefullpath);
}
void copybacklaflashfile(int leflashfile) {
  SerialFlashFile originflashfile =
      SerialFlash.open((const char *)Flashsamplename[leflashfile]);
  makenewdumpedfilename(leflashfile);

  File mynewsample = SD.open((char *)newmksamplefullpath, FILE_WRITE);
  size_t n;
  uint8_t buf[64];
  while ((n = originflashfile.read(buf, sizeof(buf))) > 0) {
    mynewsample.write(buf, n);
  }
  // }

  originflashfile.close();
  mynewsample.close();
  dopatternfileslist();
}
void copyflashtoSD() {
  for (int i = 0; i < 128; i++) {
    if (Sampleassigned[i] != 0) {
      copybacklaflashfile(Sampleassigned[i]);
    }
  }
}
void domkdir() {
  makenewmkdirpath();

  if (!(SD.exists((const char *)newmkdirpath))) {
    SD.mkdir((const char *)newmkdirpath);
  }

  copyflashtoSD();
  dosoundlist();
}
void Assingexplorer() {
  if (navlevel > 3) {
    if (sublevels[2] == 1) {
      Sampleassigner();
      playflashsamplepreviews4();
      // return ;
    }
    if (sublevels[2] == 0 && sublevels[3] == 1) {
      autoassignsamples();
      returntonav(2);
      // return ;
    }
    if (sublevels[2] == 2 && sublevels[3] == 1) {
      clearassignedsamples();
      returntonav(2);
      // return ;
    }

    if (sublevels[2] == 3 && sublevels[3] == 1) {
      domkdir();
      dosoundlist();
      returntonav(2);
      // return ;
    }

    if (sublevels[3] == 0) {
      //  Serial.println(" One of the 2 Cancelled");
      returntonav(2);
      // return ;
    }
  }

  if (navlevel == 3) {

    if (sublevels[2] == 2) {
      display.clearDisplay();
      doConfirmClearassign();
      // return ;
    }
    if (sublevels[2] == 3) {
      display.clearDisplay();
      doConfirmmkdir();
      // return ;
    }
    if (sublevels[2] == 0) {
      // autoassignsamples();
      display.clearDisplay();
      // navlevel = 2;
      doConfirmautoassign();
      // return ;
    }
    if (sublevels[2] == 1) {
      navrange = 127;
      Sampleassigner();

      // return ;
    }
  }
}
void samplerexplorer() {
  if (navlevel > 3) {
    if (sublevels[2] == 1) {
      // navrange = 127 ;
      Sampleassigner();

      // return ;
    }
    if (sublevels[2] == 2 && sublevels[3] == 1) {
      //   Serial.println("del selected confirmed");
      loadSelectedSamples();
      // clear selection
      navlevel = 2;
      //  return ;
    }
    if (sublevels[2] == 3 && sublevels[3] == 1) {
      //  Serial.println("clear selection confirmed");
      initializesamplesselectedlist();
      initializesamplesfoldersselectedlist();
      // clear selection
      navlevel = 2;
      // return ;
    }
    //        if ( sublevels[2]== 1  && sublevels[3]== 1) {
    //          Serial.println("Delete All confirmed");
    //          RemoveAllfromFlash();
    //          //clear selection
    //          navlevel = 2;
    //          return ;
    //        }
    if (sublevels[2] != 0 && sublevels[2] != 1 && sublevels[3] == 0) {
      // Serial.println(" One of the 2 Cancelled");
      navlevel = 2;
      // refresh the menu
      displaysamplermenu();
      // return ;
    }

    if (sublevels[2] == 1) {
      if (!samplesfoldersselected[sublevels[3]]) {
        samplesfoldersselected[sublevels[3]] = 1;
        numofsamplesfoldersselected++;
        // playflashsamplepreview();
      } else {
        samplesfoldersselected[sublevels[3]] = 0;
        numofsamplesfoldersselected--;
      }

      returntonav(3);
    }

    if (sublevels[2] == 0) {

      if (previousnavlevel != navlevel) {
        previousnavlevel = navlevel;
        navrange = sizeofsamplefolder[sublevels[3]] - 1;
      }

      if (navlevel > 4) {
        if (samplesselected[sublevels[3]][sublevels[4]] == 0) {
          samplesselected[sublevels[3]][sublevels[4]] = 1;
          numberofsamplesselected[sublevels[3]]++;
          playsamplepreview();
        } else {
          samplesselected[sublevels[3]][sublevels[4]] = 0;
          numberofsamplesselected[sublevels[3]]--;
        }
        navlevel--;
        vraipos = sublevels[4];
        myEnc.write(vraipos * 4);
        // sublevels[navlevel] = sublevels[4] ;
      }

      showsamplerfilesList();
    }
  }

  if (navlevel == 3) {

    if (sublevels[2] == 2) {
      display.clearDisplay();
      doConfirmLoadsamples();

      // return ;
    }
    if (sublevels[2] == 3) {
      display.clearDisplay();
      doConfirmClearList();

      // return;
    }

    if ((sublevels[2] == 0 || sublevels[2] == 1) && (sublevels[1] == 0)) {
      if (previousnavlevel != navlevel) {
        navrange = sampledirsregistered - 1;
      }
      showsamplerfolderList();
    }
  }
}

void Flashsamplerexplorer() {
  if (navlevel > 3) {

    if (sublevels[2] == 2 && sublevels[3] == 1) {
      //   Serial.println("del selected confirmed");
      DelSelectedFlashSamples();
      // clear selection
      navlevel = 2;
      // return ;
    }
    if (sublevels[2] == 3 && sublevels[3] == 1) {
      //    Serial.println("clear selection confirmed");
      initializeFlashsamplesselected();
      // clear selection
      navlevel = 2;
      //  return ;
    }
    if (sublevels[2] == 1 && sublevels[3] == 1) {
      // Serial.println("Delete All confirmed");
      RemoveAllfromFlash();
      // clear selection
      navlevel = 2;
      // return ;
    }
    if (sublevels[2] != 0 && sublevels[3] == 0) {
      // Serial.println(" One of the 3 Cancelled");
      navlevel = 2;
      // refresh the menu
      displaysamplermenu();
      // return ;
    }
    if (sublevels[2] == 0) {
      if (Flashsamplesselected[sublevels[3]] == 0) {
        Flashsamplesselected[sublevels[3]] = 1;
        numberofFlashsamplesselected++;
        playflashsamplepreview();
      } else {
        Flashsamplesselected[sublevels[3]] = 0;
        numberofFlashsamplesselected--;
      }
      myEnc.write(sublevels[3] * 4);
      vraipos = sublevels[3];
      sublevels[navlevel] = sublevels[3];
      navlevel--;
    }
  }
  if (navlevel == 3) {
    if (sublevels[2] == 2) {
      display.clearDisplay();
      doConfirmDelsamples();

      //  return ;
    }
    if (sublevels[2] == 3) {
      display.clearDisplay();
      doConfirmClearSelectedFlashList();

      //  return;
    }
    if (sublevels[2] == 1) {
      display.clearDisplay();
      doConfirmRemoveAll();

      //  return;
    }
    if (sublevels[2] == 0) {
      if (previousnavlevel != navlevel) {
        navrange = numberofFlashfiles - 1;
      }

      showFlashSamplesList();
    }
  }
}

void showsamplerfolderList() {
  drawSamplerFoldersList();
  dodisplay();
}
void showsamplerfilesList() {
  drawsamplerfilesList();
  dodisplay();
}
void showFlashSamplesList() {
  drawFlashSamplesList();
  dodisplay();
}

void drawtickboxflashBIG(int lestartx, int lestarty, int lasizex, int lasizey,
                         typeof(SSD1306_WHITE) lacolor, int lefile) {
  if (Flashsamplesselected[lefile] == 1) {
    canvasBIG.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
  } else {
    canvasBIG.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
  }
}
void drawtickboxflashtitle(int lestartx, int lestarty, int lasizex, int lasizey,
                           typeof(SSD1306_WHITE) lacolor, int lefile) {
  if (Flashsamplesselected[lefile] == 1) {
    canvastitle.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
  } else {
    canvastitle.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
  }
}

void drawtickboxfolderBIG(int lestartx, int lestarty, int lasizex, int lasizey,
                          typeof(SSD1306_WHITE) lacolor, int lefolder) {
  if (samplesfoldersselected[lefolder]) {
    canvasBIG.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
  } else {
    canvasBIG.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
  }
}
void drawtickboxfoldertitle(int lestartx, int lestarty, int lasizex,
                            int lasizey, typeof(SSD1306_WHITE) lacolor,
                            int lefolder) {
  if (samplesfoldersselected[lefolder]) {
    canvastitle.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
  } else {
    canvastitle.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
  }
}

void drawtickboxincanvasBIG(int lestartx, int lestarty, int lasizex,
                            int lasizey, typeof(SSD1306_WHITE) lacolor,
                            int lefolder, int lefile) {
  if (samplesselected[lefolder][lefile] == 1) {
    canvasBIG.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
  } else {
    canvasBIG.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
  }
}
void drawtickboxincanvastitle(int lestartx, int lestarty, int lasizex,
                              int lasizey, typeof(SSD1306_WHITE) lacolor,
                              int lefolder, int lefile) {
  if (samplesselected[lefolder][lefile] == 1) {
    canvastitle.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
  } else {
    canvastitle.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
  }
}

void addtoFlashsamplelist(char *lesample) {
  // files on the flashchip have to be uppercase
  for (int i = 0; i < 13; i++) {
    Flashsamplename[numberofFlashfiles][i] =
        toupper((unsigned char)(lesample[i]));
    if (i < (int)(strlen((char *)lesample) - 4)) {
      Flashsamplebase[numberofFlashfiles][i] =
          toupper((unsigned char)(lesample[i]));
    }
  }
  numberofFlashfiles++;
}

void rebuildflashsamplesnames() {
  initializeFlashsamplename();
  listFlashfiles();
}
void initializeFlashsamplename() {
  numberofFlashfiles = 0;
  for (int i = 0; i < 999; i++) {
    clearFlashsamplename(i);
  }
  initializeFlashsamplebase();
}
void clearFlashsamplename(int lefile) {
  for (int i = 0; i < 13; i++) {
    Flashsamplename[lefile][i] = (char)'\0';
  }
}
void initializeFlashsamplebase() {
  for (int i = 0; i < 999; i++) {
    clearFlashsamplebase(i);
  }
}
void clearFlashsamplebase(int lefile) {
  for (int i = 0; i < 9; i++) {
    Flashsamplebase[lefile][i] = (char)'\0';
  }
}

void initializesamplesfoldersselectedlist() {
  numofsamplesfoldersselected = 0;
  for (int i = 0; i < 99; i++) {
    samplesfoldersselected[i] = 0;
  }
}

void initializeFlashsamplesselected() {
  numberofFlashsamplesselected = 0;
  for (int i = 0; i < 999; i++) {
    Flashsamplesselected[i] = 0;
  }
}

void initializesamplesselectedlist() {

  for (int i = 0; i < 99; i++) {
    clearsamplesselectedlist(i);
    numberofsamplesselected[i] = 0;
  }
}
void clearsamplesselectedlist(int lefolder) {
  for (int i = 0; i < 999; i++) {
    samplesselected[lefolder][i] = 0;
  }
}

void drawFlashSamplesList() {
  // Serial.println("listing samplerList");
  int startx = 15;
  int starty = 16;
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setTextSize(1);
  canvastitle.setCursor(startx, 0);
  canvastitle.print((char *)Flashsamplebase[sublevels[navlevel]]);
  drawtickboxflashtitle(startx - 13, 0, 6, 6, SSD1306_WHITE,
                        sublevels[navlevel]);

  canvasBIG.setTextSize(1);
  canvasBIG.fillScreen(SSD1306_BLACK);
  // Serial.println("doing other part");
  int maxsizefirstpart = numberofFlashfiles - 1 - (sublevels[navlevel]);
  if (maxsizefirstpart > 6) {
    maxsizefirstpart = 6;
  }
  for (int filer = 0; filer < maxsizefirstpart; filer++) {
    canvasBIG.setCursor(startx, starty + ((filer)*10));
    canvasBIG.println((char *)Flashsamplebase[sublevels[navlevel] + 1 + filer]);
    drawtickboxflashBIG(startx - 13, starty + ((filer)*10), 6, 6, SSD1306_WHITE,
                        sublevels[navlevel] + 1 + filer);
  }
  // Serial.println("last part");
  int maxsizelastpart = sublevels[navlevel];
  if (maxsizelastpart > 6) {
    maxsizelastpart = 6;
  }
  for (int filer = 0; filer < maxsizelastpart; filer++) {
    canvasBIG.setCursor(startx,
                        (10 * (numberofFlashfiles - sublevels[navlevel])) + 6 +
                            ((filer)*10));
    canvasBIG.println((char *)Flashsamplebase[filer]);
    drawtickboxflashBIG(startx - 13,
                        (10 * (numberofFlashfiles - sublevels[navlevel])) + 6 +
                            ((filer)*10),
                        6, 6, SSD1306_WHITE, filer);
  }
}

void drawsamplerfilesList() {
  // Serial.println("listing samplerList");
  int startx = 15;
  int starty = 16;
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setTextSize(1);
  canvastitle.setCursor(startx, 0);

  canvastitle.print((char *)samplebase[sublevels[3]][sublevels[navlevel]]);
  drawtickboxincanvastitle(startx - 13, 0, 6, 6, SSD1306_WHITE, sublevels[3],
                           sublevels[navlevel]);
  canvasBIG.setTextSize(1);
  canvasBIG.fillScreen(SSD1306_BLACK);
  // Serial.println("doing other part");
  int maxsizefirstpart =
      sizeofsamplefolder[sublevels[3]] - 1 - (sublevels[navlevel]);
  if (maxsizefirstpart > 6) {
    maxsizefirstpart = 6;
  }
  for (int filer = 0; filer < maxsizefirstpart; filer++) {
    canvasBIG.setCursor(startx, starty + ((filer)*10));
    canvasBIG.println(
        (char *)samplebase[sublevels[3]][sublevels[navlevel] + 1 + filer]);
    drawtickboxincanvasBIG(startx - 13, starty + ((filer)*10), 6, 6,
                           SSD1306_WHITE, sublevels[3],
                           sublevels[navlevel] + 1 + filer);
  }
  // Serial.println("last part");
  int maxsizelastpart = sublevels[navlevel];
  if (maxsizelastpart > 6) {
    maxsizelastpart = 6;
  }
  for (int filer = 0; filer < maxsizelastpart; filer++) {
    canvasBIG.setCursor(startx, (10 * (sizeofsamplefolder[sublevels[3]] -
                                       sublevels[navlevel])) +
                                    6 + ((filer)*10));
    canvasBIG.println((char *)samplebase[sublevels[3]][filer]);
    drawtickboxincanvasBIG(
        startx - 13,
        (10 * (sizeofsamplefolder[sublevels[3]] - sublevels[navlevel])) + 6 +
            ((filer)*10),
        6, 6, SSD1306_WHITE, sublevels[3], filer);
  }
}

void drawSamplerFoldersList() {
  // Serial.println("listing samplerList");
  int startx = 15;
  int starty = 16;
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setTextSize(1);
  canvastitle.setCursor(startx, 0);

  canvastitle.print((char *)samplefoldersregistered[sublevels[navlevel]]);
  // Serial.println("listed title, 1st test");
  // ?? checkbox display ?
  if (sublevels[2] == 1) {

    drawtickboxfoldertitle(startx - 13, 0, 6, 6, SSD1306_WHITE,
                           sublevels[navlevel]);
    // }
  }
  canvasBIG.setTextSize(1);
  canvasBIG.fillScreen(SSD1306_BLACK);
  // Serial.println("doing other part");
  int maxsizefirstpart = sampledirsregistered - 1 - (sublevels[navlevel]);
  if (maxsizefirstpart > 6) {
    maxsizefirstpart = 6;
  }
  for (int filer = 0; filer < maxsizefirstpart; filer++) {
    canvasBIG.setCursor(startx, starty + ((filer)*10));
    canvasBIG.println(
        (char *)samplefoldersregistered[sublevels[navlevel] + 1 + filer]);
    if (sublevels[2] == 1) {
      // if (
      // !(isitadir((char*)samplefoldersregistered[sublevels[navlevel]+1+filer])))
      // {
      drawtickboxfolderBIG(startx - 13, starty + ((filer)*10), 6, 6,
                           SSD1306_WHITE, sublevels[navlevel] + 1 + filer);
      // }
    }
  }
  // Serial.println("last part");
  int maxsizelastpart = sublevels[navlevel];
  if (maxsizelastpart > 6) {
    maxsizelastpart = 6;
  }
  for (int filer = 0; filer < maxsizelastpart; filer++) {
    canvasBIG.setCursor(startx,
                        (10 * (sampledirsregistered - sublevels[navlevel])) +
                            6 + ((filer)*10));
    canvasBIG.println((char *)samplefoldersregistered[filer]);
    // checkbox
    if (sublevels[2] == 1) {

      drawtickboxfolderBIG(startx - 13,
                           (10 * (keepcount - sublevels[navlevel])) + 6 +
                               ((filer)*10),
                           6, 6, SSD1306_WHITE, filer);
      //  }
    }
  }
  // Serial.println("drawn");
}

void dolistLoadSampleMenu() {

  const int sizeofmenuloadsample = 4;
  char menuloadsample[sizeofmenuloadsample][16] = {
      "Select", "Whole pack", "Load Selection", "Clear Selection"};
  int startx = 5;
  int starty = 16;
  char *textin = (char *)menuloadsample[sublevels[2]];
  // Serial.println(textin);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);

  canvastitle.setTextSize(1);

  canvastitle.println(textin);

  // canvastitle.setCursor(45,8);
  // canvastitle.print("free mem:");
  // canvastitle.print(freespace);
  // canvastitle.println("%");
  canvasBIG.setTextSize(1);

  canvasBIG.fillScreen(SSD1306_BLACK);

  for (int filer = 0; filer < sizeofmenuloadsample - 1 - (sublevels[2]);
       filer++) {

    canvasBIG.setCursor(startx, starty + ((filer)*10));
    canvasBIG.println(menuloadsample[sublevels[2] + 1 + filer]);
  }
  for (int filer = 0; filer < sublevels[2]; filer++) {

    canvasBIG.setCursor(startx, (10 * (sizeofmenuloadsample - sublevels[2]) +
                                 6 + ((filer)*10)));
    canvasBIG.println(menuloadsample[filer]);
  }
}
void dolistDelSampleMenu() {
  const int sizeofmenudelsample = 4;
  char menudelsample[sizeofmenudelsample][16] = {
      "Select", "Remove All", "Remove Selected", "Clear Selection"};
  int startx = 5;
  int starty = 16;
  char *textin = (char *)menudelsample[sublevels[2]];
  // Serial.println(textin);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);

  canvastitle.setTextSize(1);

  canvastitle.println(textin);

  canvasBIG.setTextSize(1);

  canvasBIG.fillScreen(SSD1306_BLACK);

  for (int filer = 0; filer < sizeofmenudelsample - 1 - (sublevels[2]);
       filer++) {

    canvasBIG.setCursor(startx, starty + ((filer)*10));
    canvasBIG.println(menudelsample[sublevels[2] + 1 + filer]);
  }
  for (int filer = 0; filer < sublevels[2]; filer++) {

    canvasBIG.setCursor(
        startx, (10 * (sizeofmenudelsample - sublevels[2]) + 6 + ((filer)*10)));
    canvasBIG.println(menudelsample[filer]);
  }
}
void dolistAssignSampleMenu() {

  const int sizeofmenuassignsample = 4;
  char menuassignsample[sizeofmenuassignsample][19] = {
      "Auto-assign", "Individual", "Clear All", "Save assigned"};

  int startx = 5;
  int starty = 16;
  char *textin = (char *)menuassignsample[sublevels[2]];
  // Serial.println(textin);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(1);
  canvastitle.println(textin);
  canvasBIG.setTextSize(1);
  canvasBIG.fillScreen(SSD1306_BLACK);

  for (int filer = 0; filer < sizeofmenuassignsample - 1 - (sublevels[2]);
       filer++) {

    canvasBIG.setCursor(startx, starty + ((filer)*10));
    canvasBIG.println(menuassignsample[sublevels[2] + 1 + filer]);
  }
  for (int filer = 0; filer < sublevels[2]; filer++) {

    canvasBIG.setCursor(startx, (10 * (sizeofmenuassignsample - sublevels[2]) +
                                 6 + ((filer)*10)));
    canvasBIG.println(menuassignsample[filer]);
  }
}
void dolistsamplermenu() {
  const int sizeofsamplerlabels = 5;
  char samplerlabels[sizeofsamplerlabels][12] = {"Load", "Delete", "Assign",
                                                 "Recorder", "Mixer"};
  int startx = 5;
  int starty = 16;
  char *textin = (char *)samplerlabels[sublevels[1]];
  // Serial.println(textin);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);

  canvastitle.setTextSize(2);

  canvastitle.println(textin);

  canvasBIG.setTextSize(1);

  canvasBIG.fillScreen(SSD1306_BLACK);

  for (int filer = 0; filer < sizeofsamplerlabels - 1 - (sublevels[1]);
       filer++) {

    canvasBIG.setCursor(startx, starty + ((filer)*10));
    canvasBIG.println(samplerlabels[sublevels[1] + 1 + filer]);
  }
  for (int filer = 0; filer < sublevels[1]; filer++) {

    canvasBIG.setCursor(
        startx, (10 * (sizeofsamplerlabels - sublevels[1]) + 6 + ((filer)*10)));
    canvasBIG.println(samplerlabels[filer]);
  }
}

void displaysamplermenu() {

  if (navlevel == 1) {
    reinitsublevels(2);
    navrange = 4;
    cellsizer = 4;
    celltall = 8;
    startx = 0;
    starty = 17;
    display.clearDisplay();
    dolistsamplermenu();
    dodisplay();

    display.display();
  }

  if (navlevel == 2) {
    display.clearDisplay();
    switch (sublevels[1]) {

    case 0:
      navrange = 4 - 1;
      dolistLoadSampleMenu();

      break;

    case 1:
      // deletesamples menu
      navrange = 4 - 1;
      dolistDelSampleMenu();
      break;

    case 2:
      // assign samples menu
      navrange = 4 - 1;
      dolistAssignSampleMenu();
      break;
    case 3:
      // assign samples menu
      navrange = 3;
      displayRecmenu();
      break;
    case 4:
      // assign samples menu
      // navrange = 16;
      smixerVpanel();
      break;
    default:
      break;
    }
    // lemenuroot();
    dodisplay();
    display.display();
  }

  if (navlevel >= 3) {
    //  Serial.println("3rd level of menu");
    if (sublevels[1] == 0) {
      display.clearDisplay();
      samplerexplorer();
    }
    if (sublevels[1] == 1) {
      display.clearDisplay();

      Flashsamplerexplorer();
    }
    if (sublevels[1] == 2) {
      display.clearDisplay();

      Assingexplorer();
    }
    if (sublevels[1] == 3) {
      display.clearDisplay();

      displayRecmenu();
    }
    if (sublevels[1] == 4) {
      // display.clearDisplay();

      smixerVpanel();
    }
  }
}

void autoassignsamples() {
  Doautoassign();
  return;
}

void Doautoassign() {
  for (int i = 0; i < numberofFlashfiles - 1; i++) {
    if (i + 4 < 128) {
      Sampleassigned[i + 4] = i;
    } else {
      break;
    }
  }
}
void clearassignedsamples() {
  doclearassign();
  return;
}

void doclearassign() {
  for (int i = 0; i < 128; i++) {
    Sampleassigned[i] = 0;
  }
}

void doConfirmmkdir() {
  char messageconfirm[32] = "Make dir ?";
  doConfirmpanel((char *)messageconfirm);
  // Serial.println("display confirm Clear");
}
void doConfirmClearassign() {
  char messageconfirm[32] = "Clear selection ?";
  doConfirmpanel((char *)messageconfirm);
  // Serial.println("display confirm Clear");
}

void doConfirmClearList() {
  char messageconfirm[32] = "Clear selection ?";
  doConfirmpanel((char *)messageconfirm);
  // Serial.println("display confirm Clear");
}
void doConfirmautoassign() {
  char messageconfirm[32] = "Confirm autoassign ?";
  doConfirmpanel((char *)messageconfirm);
  // Serial.println("display confirm assign");
}

void doConfirmDelsamples() {
  char messageconfirm[32] = "Confirm Delete ?";
  doConfirmpanel((char *)messageconfirm);
}
void doConfirmClearSelectedFlashList() {
  // same
  doConfirmClearList();
}
void doConfirmRemoveAll() {
  // same
  doConfirmDelsamples();
}
void doConfirmLoadsamples() {
  char messageconfirm[32] = "Confirm Loading ?";
  doConfirmpanel((char *)messageconfirm);
}

void doConfirmpanel(char *letitlemsg) {
  navrange = 1;
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(1);
  // canvastitle.print((char*)text);
  canvastitle.print((char *)letitlemsg);
  canvasBIG.setTextSize(1);
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvasBIG.setCursor(20, 28);
  // canvasBIG.print((char*)text);
  canvasBIG.print("NO         YES");
  canvasBIG.drawRect(14 + sublevels[navlevel] * 66, 23,
                     23 + sublevels[navlevel] * 6, 17, SSD1306_WHITE);
  // Serial.println("display confirm load");
  dodisplay();
  display.display();
}

void RemoveAllfromFlash() {
  unsigned long startMillis = millis();
  while (!Serial && (millis() - startMillis < 10000))
    ;
  delay(100);

  if (!SerialFlash.begin(FlashChipSelect)) {
    while (1) {
      pseudoconsole("no SPI Flash chip");
      delay(1000);
    }
  }
  unsigned char id[5];
  SerialFlash.readID(id);
  unsigned long size = SerialFlash.capacity(id);

  if (size > 0) {
    Serial.print("Flash Memory has ");
    Serial.print(size);
    Serial.println(" bytes.");
    Serial.println("Erasing ALL Flash Memory:");
    // Estimate the (lengthy) wait time.
    Serial.print("  estimated wait: ");
    int seconds = (float)size / eraseBytesPerSecond(id) + 0.5;

    Serial.print(seconds);
    Serial.println(" seconds.");
    Serial.println("  Yes, full chip erase is SLOW!");
    SerialFlash.eraseAll();
    unsigned long dotMillis = millis();
    unsigned char dotcount = 0;
    while (SerialFlash.ready() == false) {
      if (millis() - dotMillis > 1000) {
        dotMillis = dotMillis + 1000;
        Serial.print(".");
        dotcount = dotcount + 1;
        pleasewait(dotcount, seconds);
        // if (dotcount >= 60) {
        //   Serial.println();
        //   dotcount = 0;
        // }
      }
    }
    
    if (dotcount > 0) {
      Serial.println();
    Serial.println("Erase completed");
    unsigned long elapsed = millis() - startMillis;
    Serial.print("  actual wait: ");
    Serial.print(elapsed / 1000ul);
    Serial.println(" seconds.");
    lemenuroot();
    }
  }
}

float eraseBytesPerSecond(const unsigned char *id) {
  if (id[0] == 0x20)
    return 152000.0; // Micron
  if (id[0] == 0x01)
    return 500000.0; // Spansion
  if (id[0] == 0xEF)
    return 419430.0; // Winbond
  if (id[0] == 0xC2)
    return 279620.0; // Macronix
  return 320000.0;   // guess?
}

void DelSelectedFlashSamples() {

  for (int j = 0; j < 999; j++) {
    pleasewait(j, 999);
    if (Flashsamplesselected[j] == 1) {
      if (SerialFlash.exists((const char *)Flashsamplename[j])) {
        SerialFlash.remove((const char *)Flashsamplename[j]);
        //  Serial.println("sampledeleted");
      }
    }
  }
  initializeFlashsamplesselected();
  rebuildflashsamplesnames();
}
void addfolderstoselectionset() {
  if (numofsamplesfoldersselected > 0) {

    for (int i = 0; i < 99; i++) {
      if (samplesfoldersselected[i]) {

        for (int j = 0; j < 999; j++) {
          samplesselected[i][j] = 1;
        }
      }
    }
  }
}

bool comparer(typeof(dummyier_file) file_1, typeof(dummy_flash_file) file_2) {
    const size_t buffer_Size = 128; // Define buffer size
    byte buffer_1[buffer_Size];
    byte buffer_2[buffer_Size];

    while (file_1.available() && file_2.available()) {
        size_t size_1 = file_1.read(buffer_1, buffer_Size);
        size_t size_2 = file_2.read(buffer_2, buffer_Size);

        if (size_1 != size_2 || memcmp(buffer_1, buffer_2, size_1) != 0) {
            return false; // Files are not identical
        }
    }

    // Check if both files ended at the same time
    return !file_1.available() && !file_2.available();
}

void loadSelectedSamples() {
  unsigned long lengthz;
  File currentsample;
  SerialFlashFile currentFlashfile;
  addfolderstoselectionset();
  delay(100);
  if (!SerialFlash.begin(FlashChipSelect)) {
    errorsd("Unable to access SPI Flash chip");
  }

  for (int i = 0; i < 99; i++) {
    pleasewait(i, 99);
    for (int j = 0; j < 999; j++) {
      if (samplesselected[i][j] == 1) {

        currentsample = SD.open((const char *)samplefullpath[i][j]);
        if (!currentsample)
          break;
        const char *currentflashname = currentsample.name();
        lengthz = currentsample.size();
        if (SerialFlash.exists(currentflashname)) {
          // Serial.println("  already exists on the Flash chip");
          currentFlashfile = SerialFlash.open(currentflashname);
          if (currentFlashfile &&
              currentFlashfile.size() == currentsample.size()) {
            // Serial.println("  size is the same, comparing data...");
            if (comparer(currentsample, currentFlashfile)) {
              // Serial.println("  files are identical :)");
              currentsample.close();
              currentFlashfile.close();
              continue; // advance to next file
            } else {
              //  Serial.println("  files are different");
            }
          } else {
            //   Serial.print("  size is different, ");
            //   Serial.print(currentFlashfile.size());
            //  Serial.println(" bytes");
          }
          // delete the copy on the Flash chip, if different
          // Serial.println("  delete file from Flash chip");
          SerialFlash.remove(currentflashname);
        }

        // create the file on the Flash chip and copy data
        if (SerialFlash.create(currentflashname, lengthz)) {
          SerialFlashFile currentFlashfile = SerialFlash.open(currentflashname);
          if (currentFlashfile) {
            //  Serial.print("  copying");
            // copy data loop
            unsigned long count = 0;
            unsigned char dotcount = 9;
            while (count < lengthz) {
              char buf[256];
              unsigned int n;
              n = currentsample.read(buf, 256);
              currentFlashfile.write(buf, n);
              count = count + n;
              // Serial.print(".");
              if (++dotcount > 100) {
                //  Serial.println();
                dotcount = 0;
              }
            }
            currentFlashfile.close();
            // if (dotcount > 0) Serial.println();
          } else {
          }
        } else {
          //  Serial.println("  unable to create file");
        }
        currentsample.close();
      }
    }
    delay(10);
  }

  initializesamplesselectedlist();
  initializesamplesfoldersselectedlist();

  listFlashfiles();
}

bool comparemesFiles(typeof(myMidiFile) &file, SerialFlashFile &ffile) {
  file.seek(0);
  ffile.seek(0);
  unsigned long count = file.size();
  while (count > 0) {
    char buf1[128], buf2[128];
    unsigned long n = count;
    if (n > 128)
      n = 128;
    file.read(buf1, n);
    ffile.read(buf2, n);
    if (memcmp(buf1, buf2, n) != 0)
      return false; // differ
    count = count - n;
  }
  return true; // all data identical
}

void errorsd(const char *message) {
  // Serial.println(message);
}

void listFlashfiles() {
  initializeFlashsamplename();
  initializeFlashsamplebase();
  // int laspace ;
  if (!SerialFlash.begin(FlashChipSelect)) {
    errorsd("Unable to access SPI Flash chip");
  }

  SerialFlash.opendir();
  while (1) {
    char flashenamex[13];
    uint32_t flashfilesize;

    if (SerialFlash.readdir(flashenamex, sizeof(flashenamex), flashfilesize)) {
      //  Serial.print("  ");
      //  Serial.print(flashenamex);
      addtoFlashsamplelist(flashenamex);
      //  laspace += flashfilesize ;
      // spacespr(20 - strlen(flashenamex));
      //  Serial.print("  ");
      // Serial.print(flashfilesize);
      // Serial.print(" bytes");
      // Serial.println();
    } else {
      break; // no more files
    }
  }
  //   freespace = ((laspace/16777216.0)*100);
}

void getavailablespace() {
  long laspace = 0;
  SerialFlashFile lefile;
  for (int i = 0; i < numberofFlashfiles; i++) {
    lefile = SerialFlash.open((char *)Flashsamplename[i]);
    if (lefile) {

      if (lefile.size() > 536900000) {

        laspace += lefile.size() - 536900000;
      } else {
        laspace += lefile.size();
      }
      Serial.println(lefile.size());
      lefile.close();
    }
  }
  lefile.close();
  // unsigned char id[5];
  // SerialFlash.readID(id);
  // unsigned long latotsize = SerialFlash.capacity(id);

  // Serial.println(latotsize);
  // Serial.println((laspace/16777216.0)*100);
  freespace = ((laspace / 16777216.0) * 100);
  Serial.print(freespace);
}

void spacespr(int num) {
  for (int i = 0; i < num; i++) {
    // Serial.print(" ");
  }
}

void Sampleassigner() {
  if (navlevel == 3) {
    navrange = 127;
    listsamplesassigner();
    dodisplay();
  }
  if (navlevel == 4) {
    // to avoid the weird last one
    navrange = numberofFlashfiles - 1;
    listsamplesassigner2();
    dodisplay();
  }
  if (navlevel == 5) {

    samplesetter();
    returntonav(3);
  }
}
void listsamplesassigner() {

  display.clearDisplay();
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  toprint = (char *)"Note";
  canvastitle.setTextSize(2);

  canvastitle.println(toprint);
  canvastitle.setCursor(85, 0);
  // toprint = (char*)"Knob";
  canvastitle.println(sublevels[3]);

  canvasBIG.fillScreen(SSD1306_BLACK);
  // if (sublevels[3] < 128 ) {
  // Serial.println(sublevels[3]);
  if (Sampleassigned[sublevels[3]] != 0) {

    canvasBIG.setTextSize(2);
    canvasBIG.setCursor(85, 16);
    canvasBIG.println(Sampleassigned[sublevels[3]]);
    canvasBIG.setCursor(0, 40);
    canvasBIG.println((char *)Flashsamplebase[Sampleassigned[sublevels[3]]]);
  }
  //}
}

void samplesetter() { Sampleassigned[sublevels[3]] = sublevels[4]; }

void listsamplesassigner2() {

  display.clearDisplay();
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  toprint = (char *)"Note";
  canvastitle.setTextSize(2);

  canvastitle.println(toprint);
  canvastitle.setCursor(85, 0);
  // toprint = (char*)"Knob";
  canvastitle.println(sublevels[3]);

  canvasBIG.fillScreen(SSD1306_BLACK);

  canvasBIG.setTextSize(2);
  canvasBIG.setCursor(85, 16);
  canvasBIG.println(sublevels[4]);
  canvasBIG.setCursor(0, 40);
  canvasBIG.println((char *)Flashsamplebase[sublevels[4]]);
}
