
void setupscreen() {

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Screen SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  display.display();
  display.setCursor(0, 0);
  display.setTextSize(1.5);
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();
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

void dodisplay() {
  
  display.drawBitmap(0, 0, canvasBIG.getBuffer(), 128, 64, SSD1306_WHITE);
  display.drawBitmap(0, 0, canvastitle.getBuffer(), 128, 16, SSD1306_WHITE);
  display.display();
  
}

void printlabel(char *toprint) {
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(toprint);
}
void displayleBGimg(const unsigned char *img) {
  display.clearDisplay();
  display.drawBitmap(0, 0, img, 128, 64, SSD1306_WHITE);
}
void selectbox(int posX, int posY) {
  // toprint = (char*)"Menu";
  // display.clearDisplay();
  // display.drawBitmap(0, 0, img, 128, 64, SSD1306_WHITE);
  display.drawRoundRect(posX, posY, 21, 21, 3, SSD1306_WHITE);
}

void dodisplayplayhead() {
  //display.clearDisplay();

  //display.drawBitmap(0, 0, canvasBIG2.getBuffer(), 128, 64, SSD1306_WHITE);
  canvasBIG.drawLine(tickposition * 4, 0, tickposition * 4, 64, SSD1306_INVERSE);
  //display.display();
}

void initializelapleasewaitarray() {

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 32; j++) {
      pleasewaitarray[i][j] = (char)'\0';
    }
  }
}
void shiftlapleasewaitarray() {
  for (int i = 9; i > 0; i--) {
    setlapleasewaitarray(i, (char *)pleasewaitarray[i - 1]);
  }
}
void setlapleasewaitarray(int consoleline, char *lemsg) {

  for (int i = 0; i < 32; i++) {
    pleasewaitarray[consoleline][i] = lemsg[i];
  }
}
void pleasewait(float lewait, float letotwait) {
  // shiftlapleasewaitarray();
  // setlapleasewaitarray(0, (char*)lemsg) ;

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(6, 0);
  display.print("Processing");
  if (letotwait > 0) {
    display.setCursor(4, 20);
    display.setTextSize(2);
    display.print("[");
    display.setTextSize(1);
    display.setCursor(7 + 4, 23);
    for (int i = 0; i < int(18.0 * (lewait / letotwait)); i++) {
      display.print("-");
    }
    display.setCursor(115, 20);
    display.setTextSize(2);
    display.print("]");
  }
  display.setCursor(20, 50);
  display.setTextSize(1);
  display.print("(Please Wait)");
  //   for (int i = 0 ; i < 10 ; i++) {
  //   display.println((char*)pleasewaitarray[i]);
  //   }
  display.display();
  // popukate 6 chars arrays and display/copy them to scroll
}

void pseudoconsole(const char *lemsg) {
  shiftconsolemsgarray();
  setleconsolemsg(0, (char *)lemsg);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  for (int i = 0; i < 10; i++) {
    display.println((char *)consolemsg[i]);
  }
  display.display();
  // popukate 6 chars arrays and display/copy them to scroll
}

void initializeconsolemsg() {

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 32; j++) {
      consolemsg[i][j] = (char)'\0';
    }
  }
}
void shiftconsolemsgarray() {
  for (int i = 9; i > 0; i--) {
    setleconsolemsg(i, (char *)consolemsg[i - 1]);
  }
}
void setleconsolemsg(int consoleline, char *lemsg) {

  for (int i = 0; i < 32; i++) {
    consolemsg[consoleline][i] = lemsg[i];
  }
}
void print_gains(){
  Serial.println(" ");
  Serial.print(" InMixL: ");
  for (int i = 0; i < 4; i++) {
    Serial.print(InMixL.getGain(i));
    Serial.print(" , ");
  } 
   Serial.println(" ");
  Serial.print(" MasterLs: ");
  for (int i = 0; i < 4; i++) {
    Serial.print(MasterL.getGain(i));
    Serial.print(" , ");
  } 
  Serial.println(" ");
  Serial.print(" MasterL1s: ");
  for (int i = 0; i < 4; i++) {
    Serial.print(MasterL1.getGain(i));
    Serial.print(" , ");
  } 
  Serial.println(" ");
  Serial.print(" WetMixMasterLs: ");
  for (int i = 0; i < 4; i++) {
    Serial.print(WetMixMasterL.getGain(i));
    Serial.print(" , ");
  } 
  Serial.println(" ");
  Serial.print(" FXBusLs: ");
  for (int i = 0; i < 4; i++) {
    Serial.print(FXBusL.getGain(i));
    Serial.print(" , ");
  } 
  Serial.println(" ");
  Serial.print(" premixMaster: ");
  for (int i = 0; i < 4; i++) {
    Serial.print(premixMaster.getGain(i));
    Serial.print(" , ");
  } 
 }