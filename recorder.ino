                   
File frec;
File frec2;
File looper;

int modeL = 0;
int modeR = 0;
// 0=stopped, 1=recording,
bool modestereo = 0;

byte getrecdir() {

  for (byte i = 0; i < sampledirsregistered; i++) {
    if ((samplefoldersregistered[i][0] == 'R') &&
        (samplefoldersregistered[i][1] == 'E') &&
        (samplefoldersregistered[i][2] == 'C')) {

      return i;
    }

    // Serial.print("folder = ");
    // Serial.println((char*)samplefoldersregistered[i]);
  }
  return sampledirsregistered;
}

void displayRecmenu() {
  Serial.println("displayRecmenu");
  navrange = 4;
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.fillScreen(SSD1306_BLACK);
  display.clearDisplay();

  RecmenuAction();

  dodisplay();
  // getrecdir()   ;
}
void dolistofRecs() {
  int startx = 80;
  int starty = 16;
  // char* textinz = (char*)lesfiles[sublevels[3]].name() ;

  canvastitle.setCursor(startx, 0);
  canvastitle.setTextSize(1);

  byte lerecdiri = getrecdir();
  if (lerecdiri < sampledirsregistered) {

    canvastitle.print((char *)samplebase[lerecdiri][sublevels[navrecmenu + 1]]);

    canvastitle.setTextSize(1);
    canvasBIG.setTextSize(1);

    for (int filer = 0; filer < sizeofsamplefolder[lerecdiri] - 1 -
                                    (sublevels[navrecmenu + 1]);
         filer++) {
      canvasBIG.setCursor(startx, starty + ((filer)*10));
      canvasBIG.println(
          (char *)samplebase[lerecdiri][sublevels[navrecmenu + 1] + 1 + filer]);
    }

    for (int filer = 0; filer < sublevels[navrecmenu + 1]; filer++) {

      canvasBIG.setCursor(startx, (10 * (sizeofsamplefolder[lerecdiri] -
                                         sublevels[navrecmenu + 1])) +
                                      6 + ((filer)*10));
      canvasBIG.println((char *)samplebase[lerecdiri][filer]);
    }
  }
}

void deleteRec() {

  byte lerecdiri = getrecdir();
  if (SD.exists((char *)samplefullpath[lerecdiri][sublevels[navrecmenu + 1]])) {
    SD.remove((char *)samplefullpath[lerecdiri][sublevels[navrecmenu + 1]]);
  }
  dosoundlist();
}
void copyRec() { Serial.println("why copy?"); }
void getthisRecname() {

  byte lerecdiri = getrecdir();
  for (int i = 0;
       i < (int)strlen((char *)samplefullpath[lerecdiri][sublevels[navrecmenu + 1]]);
       i++) {
    newRecpathL[i] = samplefullpath[lerecdiri][sublevels[navrecmenu + 1]][i];
  }
  // Serial.println((char*)newRecpathL);
}
void RecmenuAction() {
  byte lerecddir;
  if (navlevel == navrecmenu) {
    navrange = 4;

    dolistRecdisplay();
  }

  if ((sublevels[navrecmenu] == 0) && (navlevel > navrecmenu)) {
    recordVpanel();
  }

  if (sublevels[navrecmenu] != 0) {

    if (navlevel > navrecmenu + 1) {

      navlevel = navrecmenu;

      vraipos = sublevels[navrecmenu];
      myEnc.write(4 * vraipos);
      navrange = 4;

      switch (sublevels[navrecmenu]) {

      case 1:

        getthisRecname();
        break;

      case 2:
        copyRec();
        break;

      case 3:
        deleteRec();
        break;

      case 4:
        break;

      default:
        break;
      }
      displayRecmenu();
    }

    if (navlevel > navrecmenu) {
      lerecddir = getrecdir();
      if (lerecddir < sampledirsregistered) {
        navrange = sizeofsamplefolder[lerecddir] - 1;
      } else {
        Serial.println("bug1");
      }
      dolistRecdisplay();
    }

    if (navlevel >= navrecmenu) {
      // dolistRecdisplay();
      dolistofRecs();
    }
  }
}

void dolistRecdisplay() {

  const byte truesizeofRecmenulabels = 5;
  char Recmenulabels[truesizeofRecmenulabels][12] = {"Record", "Load", "Copy",
                                                     "Delete", "Params"};
  byte startx = 5;
  byte starty = 16;
  char *textin = (char *)Recmenulabels[sublevels[navrecmenu]];
  // Serial.println(textin);
  // canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(2);
  canvastitle.println(textin);

  canvasBIG.setTextSize(1);
  // canvasBIG.fillScreen(SSD1306_BLACK);

  for (int filer = 0;
       filer < truesizeofRecmenulabels - 1 - (sublevels[navrecmenu]); filer++) {

    canvasBIG.setCursor(startx, starty + ((filer)*10));
    canvasBIG.println(Recmenulabels[sublevels[navrecmenu] + 1 + filer]);
  }
  for (int filer = 0; filer < sublevels[navrecmenu]; filer++) {

    canvasBIG.setCursor(
        startx, (10 * (truesizeofRecmenulabels - sublevels[navrecmenu]) + 6 +
                 ((filer)*10)));
    canvasBIG.println(Recmenulabels[filer]);
  }
}

void makenewRecename() {
  recunites = 0;
  recdizaines = 0;
  while (SD.exists((char *)newRecpathL)) {
    findnextRecname();
  }
}

void makenewloopname() {
  recunites = 0;
  recdizaines = 0;
  while (SD.exists((char *)newloopedpath)) {
    findnextloopname();
  }
}

void findnextRecname() {

  rec_incrementer();
  // tot-9  tot-10
  newRecpathL[18] = recunites + '0';
  newRecpathL[17] = recdizaines + '0';
  newRecpathR[18] = recunites + '0';
  newRecpathR[17] = recdizaines + '0';

}
void rec_incrementer(){
  if (recunites < 9) {
    recunites++;
  } else {
    recunites = 0;
    if (recdizaines < 9) {
      recdizaines++;
    } else {
      recdizaines = 0;
    }
  }
}
void findnextloopname() {

  rec_incrementer();
  // tot-9  tot-10
  newloopedpath[18] = recunites + '0';
  newloopedpath[17] = recdizaines + '0';
  newloopedpath[18] = recunites + '0';
  newloopedpath[17] = recdizaines + '0';

}

void recordcontrols() { Serial.print("rec controlled"); }

void recordVpanelAction() {

  if (navlevel == navrec + 1) {
    byte slct = sublevels[navrec];

    if (slct == 0) {
      recorderrecord = !recorderrecord;
      if (recorderrecord) {

        if (recorderstop) {
          recorderstop = 0;
        }
        if (recorderplay) {
          recorderplay = 0;
          stopplayrecordsd();
        }
        startRecording();
        // makenewRecename();
      }
    }

    if (slct == 1) {
      recorderplay = !recorderplay;
      if (recorderplay) {

        if (recorderstop) {
          recorderstop = 0;
        }
        if (recorderrecord) {
          recorderrecord = 0;
          stopRecordingL();
          stopRecordingR();
        }
        playrecordsd();
      }
    }
    if (slct == 2) {
      recorderstop = !recorderstop;
      if (recorderstop) {

        if (recorderplay) {
          recorderplay = 0;
          stopplayrecordsd();
        }
        if (recorderrecord) {
          recorderrecord = 0;
          stopRecordingL();
        }
      }
    }

    recordcontrols();
    returntonav(navrec);
  }

  if (navlevel > navrec) {

    returntonav(navrec);
  }
}

void recordVpanelSelector() {

  if (navlevel == navrec) {
    navrange = 2;
  }
  byte slct = sublevels[navrec];

  if (slct == 0) {
    if (!recorderrecord) {
      canvasBIG.drawRoundRect(82, 18, 128 - 80 - 4, 20 - 4, 2, SSD1306_WHITE);
    } else {
      canvasBIG.drawRoundRect(82, 18, 128 - 80 - 4, 20 - 4, 2, SSD1306_BLACK);
    }
  }

  if (slct == 1) {
    if (!playRawL.isPlaying()) {
      canvasBIG.drawRoundRect(2, 18, 128 - 90 - 4, 20 - 4, 2, SSD1306_WHITE);
    } else {
      canvasBIG.drawRoundRect(2, 18, 128 - 90 - 4, 20 - 4, 2, SSD1306_BLACK);
    }
  }
  if (slct == 2) {
    if (!recorderstop) {
      canvasBIG.drawRoundRect(2, 18 + 20 + 4, 128 - 90 - 4, 20 - 4, 2,
                              SSD1306_WHITE);
    } else {
      canvasBIG.drawRoundRect(2, 18 + 20 + 4, 128 - 90 - 4, 20 - 4, 2,
                              SSD1306_BLACK);
    }
  }
}

void recordVpanel() {

  recordVpanelAction();

  display.clearDisplay();
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.fillScreen(SSD1306_BLACK);

  if (!recorderrecord) {
    canvasBIG.drawRoundRect(80, 16, 128 - 80, 20, 2, SSD1306_WHITE);
    canvasBIG.setTextColor(SSD1306_WHITE);
    canvasBIG.setCursor(87, 16 + 6);
    canvasBIG.print("Rec.");
  } else {
    canvasBIG.fillRoundRect(80, 16, 128 - 80, 20, 2, SSD1306_WHITE);
    canvasBIG.setCursor(87, 16 + 6);
    canvasBIG.setTextColor(SSD1306_BLACK);
    canvasBIG.print("Rec.");
    canvasBIG.setTextColor(SSD1306_WHITE);
  }
  if (!playRawL.isPlaying()) {
    canvasBIG.drawRoundRect(0, 16, 128 - 90, 20, 2, SSD1306_WHITE);
    canvasBIG.setTextColor(SSD1306_WHITE);
    canvasBIG.setCursor(7, 16 + 6);
    canvasBIG.print("Play");
  } else {
    canvasBIG.fillRoundRect(0, 16, 128 - 90, 20, 2, SSD1306_WHITE);
    canvasBIG.setCursor(7, 16 + 6);
    canvasBIG.setTextColor(SSD1306_BLACK);
    canvasBIG.print("Play");
    canvasBIG.setTextColor(SSD1306_WHITE);
  }
  if (!recorderstop) {
    canvasBIG.drawRoundRect(0, 16 + 20 + 4, 128 - 90, 20, 2, SSD1306_WHITE);
    canvasBIG.setCursor(7, 6 + 16 + 20 + 4);
    canvasBIG.setTextColor(SSD1306_WHITE);
    canvasBIG.print("Stop");
  } else {
    canvasBIG.fillRoundRect(0, 16 + 20 + 4, 128 - 90, 20, 2, SSD1306_WHITE);
    canvasBIG.setCursor(7, 6 + 16 + 20 + 4);
    canvasBIG.setTextColor(SSD1306_BLACK);
    canvasBIG.print("Stop");
    canvasBIG.setTextColor(SSD1306_WHITE);
  }

  recordVpanelSelector();

  dodisplay();
}

void loopRecorder() {
  // First, read the buttons
  // buttonRecord.update();
  // buttonStop.update();

  // Respond to button presses
  // if (buttonRecord.fallingEdge()) {
  // If we're playing or recording, carry on...
  if (modeL == 1) {
    continueRecording();
    // continueRecordingR();
  }

  // when using a microphone, continuously adjust gain
  // if (myInput == AUDIO_INPUT_MIC) adjustMicLevel();
}

void playrecordsd() {
  // Serial.println((char*)newRecpathL);
  if (SD.exists((char *)newRecpathL)) {
    AudioNoInterrupts();

    playRawL.play((char *)newRecpathL);
    if (modestereo) {
      playRawR.play((char *)newRecpathR);
    } else {
      playRawR.play((char *)newRecpathL);
    }
    AudioInterrupts();
  }
}

void stopplayrecordsd() {

  AudioNoInterrupts();
  playRawL.stop();
  playRawR.stop();
  AudioInterrupts();
}

void startRecording() {
  makenewRecename();
  Serial.println("startRecording");
  // AudioNoInterrupts();
  if (SD.exists((char *)newRecpathL)) {
    // The SD library writes new data to the end of the
    // file, so to start a new recording, the old file
    // must be deleted before new data is written.
    SD.remove((char *)newRecpathL);
  }

  if ((SD.exists((char *)newRecpathR)) && (modestereo)) {
    // The SD library writes new data to the end of the
    // file, so to start a new recording, the old file
    // must be deleted before new data is written.
    // Serial.print((char*)newRecpathR);
    // Serial.println(" removed");
    SD.remove((char *)newRecpathR);
  }

  // mytxtFile = SD.open((char*)newpresetpath, FILE_WRITE);
  frec = SD.open((char *)newRecpathL, FILE_WRITE);
  // delay(15);
  if (frec) {
    modeL = 1;
    queue1.begin();
    Serial.println("Freq opened");
    if (modestereo) {
      frec2 = SD.open((char *)newRecpathR, FILE_WRITE);
      if (frec2) {
        Serial.println("Frec2 opened");
        modeR = 1;
        queue2.begin();
      }
    }
  }
  // AudioInterrupts();
}

void continueRecording() {

  if (queue1.available() >= 2) {

    if (frec) {

      // Fetch 2 blocks from the audio library and copy
      // into a 512 byte buffer.  The Arduino SD library
      // is most efficient when full 512 byte sector size
      // writes are used.
      memcpy(bufferL, queue1.readBuffer(), 256);
      queue1.freeBuffer();
      memcpy(bufferL + 256, queue1.readBuffer(), 256);
      queue1.freeBuffer();
      // write all 512 bytes to the SD card
      // elapsedMicros usec = 0;
      frec.write(bufferL, 512);
      //  Serial.println("DumpedL");
      //  delay(round((knobs[3]*10)));
      // Uncomment these lines to see how long SD writes
      // are taking.  A pair of audio blocks arrives every
      // 5802 microseconds, so hopefully most of the writes
      // take well under 5802 us.  Some will take more, as
      // the SD library also must write to the FAT tables
      // and the SD card controller manages media erase and
      // wear leveling.  The queue1 object can buffer
      // approximately 301700 us of audio, to allow time
      // for occasional high SD card latency, as long as
      // the average write time is under 5802 us.
      // Serial.print("SD write, us=");
      // Serial.println(usec);

      // if ( modestereo) {
      // frec.close();
      //}
      // Serial.println("Buffer_L Dumped");
    }
  }
  if (modestereo) {
    if (queue2.available() >= 2) {
      // frec2 = SD.open("RECORDR.RAW", FILE_WRITE);
      if (frec2) {

        memcpy(bufferR, queue2.readBuffer(), 256);
        queue2.freeBuffer();
        memcpy(bufferR + 256, queue2.readBuffer(), 256);
        queue2.freeBuffer();
        // write all 512 bytes to the SD card
        // elapsedMicros usec = 0;
        frec2.write(bufferR, 512);
        //  Serial.println("DumpedR");
        // delay(round((knobs[3]*10)));
        // frec2.close();
        // Serial.println("Buffer_R Dumped");
      }
    }
  }
  // if (frec2) {  Serial.println("Frec2 still opened");}
  // if (frec) {Serial.println("Frec1 still opened");}
  // delay(3000);
}

void stopRecordingL() {
  // if ( !frec ) {
  //  frec = SD.open("RECORDL.RAW", FILE_WRITE);
  //}

  queue1.end();
  // synchro !

  if (modeL == 1) {
    while (queue1.available() > 0) {
      frec.write((byte *)queue1.readBuffer(), 256);
      queue1.freeBuffer();
      // Serial.println("Freeing L Buffer");
    }
    frec.close();
    modeL = 0;
    queue1.clear();
    // Serial.println("stopRecordingL");
  }
  if (modestereo) {
    stopRecordingR();
  }
  dosoundlist();
}

void stopRecordingR() {

  // frec2 = SD.open("RECORDR.RAW", FILE_WRITE);

  queue2.end();

  // queue2.end();
  if (modeR == 1) {
    while (queue2.available() > 0) {
      frec2.write((byte *)queue2.readBuffer(), 256);
      queue2.freeBuffer();

      // Serial.println("Freeing R Buffer");
    }
    frec2.close();
    modeR = 0;
    queue2.clear();
    Serial.println("stopRecordingR");
  }
}
void auto_stop_rec(){
  if (millis() - tocker > 10000) {
        rec_looping = false ;
        end_sample_in_place();
      }
}

void continue_looper(){
  
  if (queue1.available() >= 2 && looper ) {
        //for (int i = 0; i < 2; i++) {
      //      looper.write((byte*)queue1.readBuffer(), 256);
       //     queue1.freeBuffer();
      //  }
      memcpy(bufferLoop, queue1.readBuffer(), 256);
      queue1.freeBuffer();
      memcpy(bufferLoop + 256, queue1.readBuffer(), 256);
      queue1.freeBuffer();
      looper.write(bufferLoop, 512);
  }
  auto_stop_rec();
}

void start_sample_in_place() {
  if (!just_pressed_rec){

      just_pressed_rec = true ;
    tocker = millis();
   Serial.println("looping");
  
  makenewloopname();
  if (SD.exists((const char *)newloopedpath)) {
      SD.remove((const char *)newloopedpath);
    }
    looper = SD.open((const char *)newloopedpath, FILE_WRITE);
  if (looper) {
    Serial.println("start rec looper ");
    Serial.print(looper.name());
    Serial.println("");
    AudioNoInterrupts();
    queue1.begin();
    AudioInterrupts();
    rec_looping = true ;
  } else {
      String formattedString = "error opening " + String((const char *)newloopedpath);
      Serial.println(formattedString);
      rec_looping = false ;
    }
    
//start at pat pos
//rec mono
// ends in 32 ticks
//save sample
// assign saved to note 50
// set pattern empty and place note 50 on 0
//clear locks
  
}
}

void end_sample_in_place() {
    if (looper) {
      Serial.println("stop rec looper ");
    Serial.print(looper.name());
    Serial.println("");
    AudioNoInterrupts();
    queue1.end();
    AudioInterrupts();
    
    while (queue1.available() > 0) {
      looper.write((byte *)queue1.readBuffer(), 256);
      queue1.freeBuffer();
      
    }
    looper.close();
    queue1.clear();

    dosoundlist();
    }
    just_pressed_rec = false ;
}

  //rien  SOUNDSET/REC/WAV_01.WAV
  // in setup : 
  // recorder.begin("SOUNDSET/REC/WAV_01.WAV");
  
void wav_record_loop() {
  // Check if the recorder is active and has new data
  if (true) {
 
}
  //}
}

void startVHSRecording() {
  //recorder.start();
}

void stopVHSRecording() {
 // recorder.stop();
  Serial.println("Recording stopped");
}

 