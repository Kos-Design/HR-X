

void initializeWaveformsselected() {
  numberofWaveformsselected = 0;
  for (int i = 0; i < 999; i++) {
    Waveformsselected[i] = 0;
  }
}

void initializeWaveformsfullpath() {
  numberofWaveforms = 0;

  for (int i = 0; i < 999; i++) {
    for (int j = 0; j < 22; j++) {
      Waveformsfullpath[i][j] = (char)'\0';
      if (j < 9) {
        Waveformsfullpath[i][j] = (char)("WAVEFORM/"[j]);
      }
      if (j < 13) {
        Waveformsname[i][j] = (char)'\0';
      }
      if (j < 9) {
        Waveformsbase[i][j] = (char)'\0';
      }
    }
  }
}

void dowaveformslist() {
  initializeWaveformsselected();
  initializeWaveformsfullpath();
  listWaveformsfiles();
}

void setleWaveformsname(int lefile, const char *lefname) {

  int fnamesize = strlen((char *)lefname);
  for (int i = 0; i < fnamesize; i++) {
    Waveformsname[lefile][i] = lefname[i];
    Waveformsfullpath[lefile][9 + i] = Waveformsname[lefile][i];
    if (i < fnamesize - 4) {
      Waveformsbase[lefile][i] = Waveformsname[lefile][i];
    }
  }
  Waveformsname[lefile][fnamesize] = (char)'\0';
  Waveformsfullpath[lefile][9 + fnamesize] = (char)'\0';
  Waveformsbase[lefile][fnamesize - 4] = (char)'\0';
}

void listWaveformsfiles() {
  if (SD.exists((char *)Waveformsdir)) {
    File susudir = SD.open((char *)Waveformsdir);

    while (true) {
      File subentry = susudir.openNextFile();
      if (!subentry) {
        break;
      }

      if (!subentry.isDirectory()) {
        // Serial.print(subentry.name());
        setleWaveformsname(numberofWaveforms, subentry.name());
        numberofWaveforms++;
      }
      subentry.close();
    }
    susudir.close();
  }
}
// 1
void displaywaveformsmenu() {
  
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.fillScreen(SSD1306_BLACK);

  WaveformsmenuBG();
  if (navlevel <= 1) {
    navrange = 6;
    dolistwaveformsmenu();
  } else if (navlevel > 1 && sublevels[1] != 4) {
    dolistwaveformsmenu();
  }
  dodisplay();
}

void WaveformsmenuBG() {
  display.clearDisplay();
  if (navlevel == 1 && sublevels[1] != 4) {
    reinitsublevels(2);
    navrange = 6;

    dolistofwaveforms();
  }

  if (navlevel >= 2 && sublevels[1] == 4) {
    WaveformEditer();
  }

  if (navlevel > 1 && sublevels[1] < 4)  {
    if (sublevels[1] == 0) {
      navrange = numberofWaveforms;
    } else {
      navrange = numberofWaveforms - 1;
    }

    dolistofwaveforms();
  }
  dodisplay();
  
  if (navlevel >= 2 && sublevels[1] > 4) {
    switch (sublevels[1]) {
    
    case 5:
      waveformIndex ++;
      if ( waveformIndex > 3 ) {
        waveformIndex = 0 ;
      }
      break;

    case 6:
      waveformIndex --;
      if ( waveformIndex < 0 || waveformIndex > 3 ) {
        waveformIndex = 3 ;
      }
      break;

      default:
      break;
    }
    returntonav(1,6);
    displaywaveformsmenu();
  }
  if (navlevel >= 3) {
   
    switch (sublevels[1]) {

    case 0:
      writewaveform();
      break;

    case 1:

      readwaveform();
      break;

    case 2:
      copywaveform();
      break;

    case 3:
      deletewaveform();
      break;

    case 4:
      WaveformEditer();
      break;

    case 5:
      break;

    case 6:
      break;

    default:
      break;
    }
    returntonav(1,6);
    displaywaveformsmenu();
    
  }
}

int cw_change = 0;
int vc_change;
int w_cursor_y = 32;

void WaveformEditer() {
  int16_t y1;
  int16_t y2;
  navrange = 256;
  int w_cursor_x = sublevels[2] / 2;

  canvastitle.fillScreen(SSD1306_BLACK);
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  // draw cursor

  vc_change = Muxer.read_val(6);
  if (vc_change > 0) {
    cw_change = vc_change;
    w_cursor_y = map(cw_change, 0, 1024, 64, 0);
  }
  if (trace_waveform && navlevel >= 2) {
    arbitrary_waveforms[waveformIndex][sublevels[2]] = map(cw_change, 0, 1024, -32768, 32767);
  }
  canvasBIG.drawCircle(w_cursor_x, w_cursor_y, 2, SSD1306_WHITE);

  for (int i = 0; i < 128; i++) {
    if ((i * 2) + 2 < 256) {
      y1 = map(arbitrary_waveforms[waveformIndex][i * 2], -32768, 32767, 63, 0);
      y2 = map(arbitrary_waveforms[waveformIndex][(i * 2) + 2], -32768, 32767, 63, 0);
      canvasBIG.drawLine(i, y1, i + 1, y2, SSD1306_WHITE);
    }
  }
  canvastitle.print(arbitrary_waveforms[waveformIndex][sublevels[2]]);
}

void dolistwaveformsmenu() {
  char waveformsmenulabels[truesizeofwaveformsmenulabels][12] = {
      "Save", "Load", "Copy", "Delete", "Edit", "-->", "<--"};
  byte startx = 5;
  byte starty = 16;
  char *textin = (char *)waveformsmenulabels[sublevels[1]];
  // Serial.println(textin);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(2);
  canvastitle.println(textin);

  canvasBIG.setTextSize(2);
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvasBIG.drawRoundRect(50,25,22,22,3,SSD1306_WHITE);
  canvasBIG.setCursor(56,29);
  canvasBIG.print(waveformIndex+1);
  canvasBIG.setTextSize(1);
  
  for (int filer = 0;
       filer < truesizeofwaveformsmenulabels - 1 - (sublevels[1]); filer++) {

    canvasBIG.setCursor(startx, starty + ((filer)*10));
    canvasBIG.println(waveformsmenulabels[sublevels[1] + 1 + filer]);
  }
  for (int filer = 0; filer < sublevels[1]; filer++) {

    canvasBIG.setCursor(startx,
                        (10 * (truesizeofwaveformsmenulabels - sublevels[1]) +
                         6 + ((filer)*10)));
    canvasBIG.println(waveformsmenulabels[filer]);
  }
}

void writewaveform() {

  if (sublevels[2] == numberofWaveforms) {
    
    mytxtFile = SD.open(get_new_file_name("WAVEFORM/WFORM-").c_str(), FILE_WRITE);
  } else {
    if (SD.exists((char *)Waveformsfullpath[sublevels[2]])) {
      SD.remove((char *)Waveformsfullpath[sublevels[2]]);
    }

    mytxtFile = SD.open((char *)Waveformsfullpath[sublevels[2]], FILE_WRITE);
  }
  // if the file opened okay, write to it:
  if (mytxtFile) {
    Serial.print("Writing to ");
    Serial.println(mytxtFile.name());
    writewaveforms();
    mytxtFile.close();
    // Serial.println("done.");
  }

  mytxtFile.close();
  dowaveformslist();
}

void dolistofwaveforms() {
  int startx = 80;
  int starty = 16;
  // char* textinz = (char*)lesfiles[sublevels[3]].name() ;

  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(startx, 0);
  canvastitle.setTextSize(1);

  if (sublevels[2] == numberofWaveforms && sublevels[1] == 0) {

    canvastitle.print("New()");
  } else {
    canvastitle.print((char *)Waveformsbase[sublevels[2]]);
  }
  canvastitle.setTextSize(1);
  canvasBIG.setTextSize(1);
  canvasBIG.fillScreen(SSD1306_BLACK);
  if (sublevels[2] == numberofWaveforms) {
    for (int filer = 0; filer < sublevels[2] - 1; filer++) {
      canvasBIG.setCursor(startx, (10 * (numberofWaveforms - sublevels[2])) +
                                      16 + ((filer)*10));
      canvasBIG.println((char *)Waveformsbase[filer]);
    }
  } else {
    for (int filer = 0; filer < numberofWaveforms - 1 - (sublevels[2]);
         filer++) {
      canvasBIG.setCursor(startx, starty + ((filer)*10));
      canvasBIG.println((char *)Waveformsbase[sublevels[2] + 1 + filer]);
    }

    for (int filer = 0; filer < sublevels[2]; filer++) {

      canvasBIG.setCursor(startx, (10 * (numberofWaveforms - sublevels[2])) +
                                      6 + ((filer)*10));
      canvasBIG.println((char *)Waveformsbase[filer]);
    }
  }
}

void setwaveformsnavrange() {
  if (numberofWaveforms < 2) {
    navrange = 2;
    // Serial.println("SOMETHING IS WRONG");
  } else {
    navrange = numberofWaveforms - 1;
  }
}

void writewaveforms() {
  size_t writtenBytes =
      mytxtFile.write((byte *)arbitrary_waveforms[waveformIndex], sizeof(arbitrary_waveforms[waveformIndex]));
  if (writtenBytes != sizeof(arbitrary_waveforms[waveformIndex])) {
    Serial.println("Failed to write all waveform data to file");
  } else {
    Serial.println("Waveform data written to file.");
  }
}

void readwaveform() { parsewaveformfile(sublevels[2]); }

void copywaveform() {
  File originefile;
  if (SD.exists((char *)Waveformsfullpath[sublevels[2]])) {
    mytxtFile = SD.open(get_new_file_name("WAVEFORM/WFORM-").c_str(), FILE_WRITE);
    originefile = SD.open((char *)Waveformsfullpath[sublevels[2]], FILE_READ);
    size_t n_size;
    uint8_t buf[64];
    while ((n_size = originefile.read(buf, sizeof(buf))) > 0) {
      mytxtFile.write(buf, n_size);
    }
  }

  originefile.close();
  mytxtFile.close();
  dowaveformslist();
}

void deletewaveform() {
  if (SD.exists((char *)Waveformsfullpath[sublevels[2]])) {
    SD.remove((char *)Waveformsfullpath[sublevels[2]]);
  }
  dowaveformslist();
}

void parsewaveformfile(int presetn) {

  mytxtFile = SD.open((char *)Waveformsfullpath[sublevels[2]], FILE_READ);
  size_t readBytes =
      mytxtFile.read((byte *)arbitrary_waveforms[waveformIndex], sizeof(arbitrary_waveforms[waveformIndex]));

  if (readBytes != sizeof(arbitrary_waveforms[waveformIndex])) {
    Serial.println("Failed to read complete waveform data");
  } else {
    Serial.println("Waveform data read from file:");
    for (int i = 0; i < 256; i++) {
      Serial.println(arbitrary_waveforms[waveformIndex][i]);
    }
  }

  mytxtFile.close();
}
