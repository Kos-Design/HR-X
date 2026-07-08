
File frec;
File frec2;
File looper;

int modeL = 0;
int modeR = 0;
bool autoassign = 0;
// 0=stopped, 1=recording,
bool modestereo = 0;

byte getrecdir() {
  for (byte i = 0; i < sampledirsregistered; i++) {
    if (strcmp(samplefoldersregistered[i], "REC") == 0)
      return i;
    }
  check_rec_folder_path();
  return sampledirsregistered;
}

void trim_it(float start_pos = 0.0f, float end_pos = 1.0f) {
  if (locked_fileing)
  return;
  locked_fileing = 1 ;
    File in = SD.open(newloopedpath.c_str(), FILE_READ);
    if (!in)
        return;

    File out = SD.open(get_new_file_name("SOUNDSET/REC/LOOP","#L.RAW").c_str(), FILE_WRITE);
    if (!out)
    {
        in.close();
        return;
    }

    uint32_t fileSize = in.size();

    // Clamp arguments
    start_pos = constrain(start_pos, 0.0f, 1.0f);
    end_pos   = constrain(end_pos,   0.0f, 1.0f);

    if (start_pos >= end_pos)
    {
        in.close();
        out.close();
        return;
    }

    // Convert percentages to byte offsets
    uint32_t startByte = (uint32_t)(start_pos * fileSize);
    uint32_t endByte   = (uint32_t)(end_pos   * fileSize);

    // Align to 16-bit sample boundaries
    startByte &= ~1;
    endByte   &= ~1;

    // Safety
    if (endByte > fileSize)
        endByte = fileSize;

    if (startByte >= endByte)
    {
        in.close();
        out.close();
        return;
    }

    in.seek(startByte);

    uint32_t remaining = endByte - startByte;
    uint8_t buffer[4096];

    while (remaining)
    {
        uint32_t chunk = min((uint32_t)sizeof(buffer), remaining);

        int bytesRead = in.read(buffer, chunk);
        if (bytesRead <= 0)
            break;

        out.write(buffer, bytesRead);
        remaining -= bytesRead;
    }

    out.close();
    in.close();
    Serial.println("Trimmed");
    locked_fileing = 0 ; 
}

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
          stopRecording();
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
          stopRecording();
        }
      }
    }
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
  dm.clear_buffs();
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

void playrecordsd() {
  if (SD.exists(newloopedpath.c_str())) {
    AudioNoInterrupts();
    playRawL.play(newloopedpath.c_str());
    if (modestereo) {
      playRawR.play(newRecpathR.c_str());
    } else {
      playRawR.play(newloopedpath.c_str());
    }
    AudioInterrupts();
  }
}

void playrecordsd_old() {
  if (SD.exists(newRecpathL.c_str())) {
    AudioNoInterrupts();
    playRawL.play(newRecpathL.c_str());
    if (modestereo) {
      playRawR.play(newRecpathR.c_str());
    } else {
      playRawR.play(newRecpathL.c_str());
    }
    AudioInterrupts();
  }
}

void stopplayrecordsd() {
  //AudioNoInterrupts();
  playRawL.stop();
  playRawR.stop();
  //AudioInterrupts();
}

void check_rec_folder_path(){
  if (!(SD.exists(((String)"SOUNDSET/REC").c_str()))) {
    if (!(SD.exists(((String)"SOUNDSET").c_str()))) {
      SD.mkdir(((String)"SOUNDSET").c_str());
    }
    SD.mkdir(((String)"SOUNDSET/REC").c_str());
  }
}

void startRecording() {
  if (locked_fileing)
    return;
  locked_fileing = 1 ;
  if (!just_pressed_rec){
    just_pressed_rec = true ;;
    check_rec_folder_path();
    tocker = millis();
    newloopedpath = get_new_file_name("SOUNDSET/REC/LOOP","#L.RAW");
    looper = SD.open(newloopedpath.c_str(), FILE_WRITE);
    if (looper) {
      //AudioNoInterrupts();
      queue1.begin();
      pre_record = true;
      //AudioInterrupts();
      //rec_looping = true ;
    } else {
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


void stopRecordingR() {
  // frec2 = SD.open("RECORDR.RAW", FILE_WRITE);
  queue2.end();
  // queue2.end();
  if (modeR == 1) {
    while (queue2.available() > 0) {
      frec2.write((byte *)queue2.readBuffer(), 256);
      queue2.freeBuffer();
    }
    frec2.close();
    modeR = 0;
    queue2.clear();
  }
}

void auto_stop_rec(){
  if (millis() - tocker > 10000) {
    rec_looping = false ;
    stopRecording();
    
  }
}

void continue_looper() {
  if (queue1.available() >= 2) {
    byte rec_buffer[512];
    memcpy(rec_buffer, queue1.readBuffer(), 256);
    queue1.freeBuffer();
    memcpy(rec_buffer+256, queue1.readBuffer(), 256);
    queue1.freeBuffer();
    // write all 512 bytes to the SD card
    //elapsedMicros usec = 0;
    looper.write(rec_buffer, 512);
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

  }
  auto_stop_rec();
}

void stopRecording() {
  
    if (looper) {
    //AudioNoInterrupts();
    queue1.end();
    while (queue1.available() > 0) {
      looper.write((byte *)queue1.readBuffer(), 256);
      queue1.freeBuffer();
    }
    looper.close();
    queue1.clear();
    //AudioInterrupts();
    call_dosoundlist();
    }
    just_pressed_rec = false ;
    pre_record = false;
    if (autoassign) {
      call_loadSampledSound();
    }
    locked_fileing = 0 ;
}

class RecorderMenuRouter : public SectionHolder {
    public:
        RecorderMenuRouter() {
                    self = this;
                    this->home_navrange=self->rec_labels_count - 1;
                    this->relative_navlevel=navrecmenu;
                    this->max_navlevel=5;
                    this->sublevels_address={7,3,0};
                    }

        const byte rec_labels_count = 5;
        
        static void show() {
         _route_nav[navlevel-self->relative_navlevel]();
        }

        static void getthisRecname() {
          byte lerecdiri = getrecdir();
          newRecpathL = samplefullpath(lerecdiri,sublevels[navrecmenu + 1]);
          newloopedpath = newRecpathL ;
        }

        static void dolistofRecs() {
          int startx = 80;
          int starty = 16;
          canvastitle.setCursor(startx, 0);
          canvastitle.setTextSize(1);
          byte lerecdiri = getrecdir();
          if (lerecdiri < sampledirsregistered) {
            canvastitle.print((char *)samplebase[lerecdiri][sublevels[navrecmenu + 1]]);
            for (int i=0;i<sizeofsamplefolder[lerecdiri]-1-(sublevels[navrecmenu + 1]);i++) {
              canvasBIG.setCursor(startx, starty + ((i)*10));
              canvasBIG.println((char *)samplebase[lerecdiri][sublevels[navrecmenu + 1] + 1 + i]);
            }
            for (int i=0; i<sublevels[navrecmenu+1]; i++) {
              canvasBIG.setCursor(startx,(10*(sizeofsamplefolder[lerecdiri]-sublevels[navrecmenu + 1]))+6+(i*10));
              canvasBIG.println((char *)samplebase[lerecdiri][i]);
            }
          }
        }

        static void deleteRec() {
          if (locked_fileing)
            return;
          locked_fileing = 1 ;
          byte lerecdiri = getrecdir();
          if (SD.exists((char *)(samplefullpath(lerecdiri,sublevels[navrecmenu + 1]).c_str()))) {
            SD.remove((char *)(samplefullpath(lerecdiri,sublevels[navrecmenu + 1]).c_str()));
          }
          call_dosoundlist();
          locked_fileing = 0 ;
        }

        static void recorder_menu() {
          char Recmenulabels[self->rec_labels_count][12] = {"Record", "Load", "Delete", "Params","Edit"};
          byte startx = 5;
          byte starty = 16;
          char *textin = (char *)Recmenulabels[sublevels[navrecmenu]];
          canvastitle.println(textin);
          for (int i=0;i<self->rec_labels_count-1-(sublevels[navrecmenu]);i++) {
              canvasBIG.setCursor(startx, starty + ((i)*10));
              canvasBIG.println(Recmenulabels[sublevels[navrecmenu] + 1 + i]);
          }
          for (int i = 0; i < sublevels[navrecmenu]; i++) {
            canvasBIG.setCursor(startx,(10*(self->rec_labels_count-sublevels[navrecmenu])+6+((i)*10)));
            canvasBIG.println(Recmenulabels[i]);
          }
        }

        static void rec_params(){
          dm.clean_title_2_1();
          display.setCursor(0,0);
          display.print("Placeholder");
          dodisplay();
        }

        static void rec_nav_zero(){
          dm.clean_title_2_1();
          navrange = self->home_navrange;
          recorder_menu();
          dolistofRecs();
          dodisplay();
        }

        static void rec_nav_one(){
          byte lerecddir = getrecdir();
              if (lerecddir < sampledirsregistered) {
                navrange = sizeofsamplefolder[lerecddir] - 1;
              } else {
                
                pseudoconsole("No SOUNDSET/REC folder \n on SD card");
                returntonav(self->relative_navlevel, self->home_navrange,sublevels[self->relative_navlevel]);
              }
          recorder_menu();
          dolistofRecs();
        }

        static void lv1_wrapper(void (*func)()) {
          dm.clean_title_2_1();
          rec_nav_one();
          if (navlevel >= self->relative_navlevel + 2) {
            func();
            returntonav(self->relative_navlevel, self->home_navrange,sublevels[self->relative_navlevel]);
          }
          dodisplay();
        }

        static void records_actions(){
          _nav_recs[sublevels[self->relative_navlevel]%self->rec_labels_count]();
        }

        static void remove_record(){
          lv1_wrapper(self->deleteRec);
        }

        static void load_record(){
          lv1_wrapper(self->getthisRecname);
        }

        static void drawWaveform(
                  float startPos = 0.0f,
                  float endPos   = 1.0f,
                  uint16_t width = 128,
                  uint16_t height = 64){
            File wave_file = SD.open(newloopedpath.c_str(), FILE_READ);
            if (!wave_file)
                return;

            uint32_t totalSamples = wave_file.size() / 2; // 16-bit mono
            uint32_t firstSample = (uint32_t)(startPos * totalSamples);
            uint32_t lastSample  = (uint32_t)(endPos   * totalSamples);
            uint32_t visibleSamples = lastSample - firstSample;

            if (visibleSamples == 0)
                return;

            for (uint16_t x = 0; x < width; x++)
            {
                uint32_t start = firstSample +
                    ((uint64_t)x * visibleSamples) / width;

                uint32_t end = firstSample +
                    ((uint64_t)(x + 1) * visibleSamples) / width;

                if (end <= start)
                    end = start + 1;

                wave_file.seek(start * 2);

                int16_t minSample = 32767;
                int16_t maxSample = -32768;

                for (uint32_t i = start; i < end; i++)
                {
                    int16_t sample_selected;
                    wave_file.read((uint8_t *)&sample_selected, sizeof(sample_selected));
                    if (sample_selected < minSample) minSample = sample_selected;
                    if (sample_selected > maxSample) maxSample = sample_selected;
                }

                int yTop = map(maxSample, 32767, -32768, 0, height - 1);
                int yBottom = map(minSample, 32767, -32768, 0, height - 1);

                canvasBIG.drawFastVLine(x, yTop, yBottom - yTop + 1, SSD1306_WHITE);
                
            }
            wave_file.close();
        }
        static void select_cursor() {
          display.clearDisplay();
          dodisplay();
          int cursor_coords[][4] = {{0,0,18,8},{22,0,27,8},{52,0,9,8},{64,0,9,8},{76,0,9,8},{88,0,14,8},{106,0,14,8},{0,8,128,48},
                                    {23,56,14,8},{40,56,21,8},{64,56,20,8},{88,56,27,8}};
          display.fillRect(cursor_coords[sublevels[self->relative_navlevel+1]][0], 
                            cursor_coords[sublevels[self->relative_navlevel+1]][1],
                            cursor_coords[sublevels[self->relative_navlevel+1]][2],
                            cursor_coords[sublevels[self->relative_navlevel+1]][3],
                            SSD1306_INVERSE);
           if (self->wave_selected) {
            redraw_selection_box();
          } 
          display.display();
        }
        static void draw_editor_zones(){
          dm.clean_title_1_1();
          canvastitle.print("Slt");
          canvastitle.print(" Zoom");
          //canvastitle.print(" Play");
          canvastitle.print(" A");//amplify
          canvastitle.print(" R");//reverse
          canvastitle.print(" P");//Pitch
          canvastitle.print(" Fi");//fade In
          canvastitle.print(" Fo");//fade out
          //canvasBIG.drawFastHLine(0, 10, 128, SSD1306_WHITE);
          //canvasBIG.drawFastHLine(0, 53, 128, SSD1306_WHITE);
          canvasBIG.setCursor(0,57);
          canvasBIG.print("Cut In");//trim from start of zone to eof
          canvasBIG.print(" Out");// trim from begining to end of zone
          canvasBIG.print(" Del");// remove selected zone
          canvasBIG.print(" Trim");// keep only selected zone

          
        }

        static void redraw_selection_box(){
          display.fillRect(sublevels[self->relative_navlevel +2], 8, 
                              sublevels[self->relative_navlevel +3],48, SSD1306_INVERSE);
         
        }

        static void edit_record(){
          navrange = 11 ;
           if (navlevel == self->relative_navlevel+1) {
            
            if (!self->wave_buffed) {
              draw_editor_zones();
              self->wave_buffed = 1 ; 
              drawWaveform(0.4,0.5);
              dodisplay();
            }
            select_cursor();
           }
          // select command, zoom command, play
          // write : trim in, out, current zoom | amplify | reverse, filter(?)
          if (navlevel == self->relative_navlevel + 2) {
            self->wave_selected = 0;
            navrange = 127 ;
            display.clearDisplay();
            display.drawFastVLine(sublevels[self->relative_navlevel +2], 8, 48, SSD1306_INVERSE);
            dodisplay();
            //returntonav(self->relative_navlevel + 1, self->home_navrange,0);
          }

          if (navlevel == self->relative_navlevel + 3) {
            navrange = 127 - sublevels[self->relative_navlevel +2] ;
            display.clearDisplay();
            dodisplay();
            display.fillRect(sublevels[self->relative_navlevel +2], 8, 
                              sublevels[self->relative_navlevel +3],48, SSD1306_INVERSE);
            display.display();
            //returntonav(self->relative_navlevel + 1, self->home_navrange,0);
          }
          if (navlevel > self->relative_navlevel +3) {
              returntonav(self->relative_navlevel + 1);
              self->wave_selected = 1;
              }
        } 
        bool wave_buffed = 0 ;
        bool wave_selected = 0 ;
        static constexpr void (*_route_nav[9])() = {&rec_nav_zero, &records_actions, &records_actions,
                                    &records_actions, &records_actions,&records_actions, &records_actions,
                                    &records_actions, &records_actions};
        
        static constexpr void  (*_nav_recs[5])() = {&recordVpanel, &load_record, &remove_record, &rec_params,&edit_record};
        

  private:
    static RecorderMenuRouter* self;
};

RecorderMenuRouter* RecorderMenuRouter::self = nullptr;
RecorderMenuRouter _rd;
       
        
