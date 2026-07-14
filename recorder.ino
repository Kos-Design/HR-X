
File frec;
File frec2;
File looper;

int modeL = 0;
int modeR = 0;
bool autoassign = 0;
// 0=stopped, 1=recording,
bool modestereo = 0;


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
          byte lerecdiri = self->getrecdir();
          newRecpathL = samplefullpath(lerecdiri,sublevels[navrecmenu + 1]);
          newloopedpath = newRecpathL ;
          //not the same file if stereo
          //newRecpathR = newRecpathL ;
        }

        byte getrecdir() {
          for (byte i = 0; i < sampledirsregistered; i++) {
            if (strcmp(samplefoldersregistered[i], "REC") == 0)
              return i;
            }
          check_rec_folder_path();
          return sampledirsregistered;
        }


        static void startRecording() {
          if (locked_fileing)
            return;
          locked_fileing = 1 ;
          if (!just_pressed_rec){
            just_pressed_rec = true ;
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


        static void stopRecordingR() {
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

        static void auto_stop_rec(){
          if (millis() - tocker > 10000) {
            rec_looping = false ;
            stopRecording();
            
          }
        }

        static void continue_looper() {
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

        static void stopRecording() {
          
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


        static void recordVpanelAction() {
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

        static void recordVpanelSelector() {
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

        static void recordVpanel() {
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

        static void playrecordsd() {
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

        static void playrecordsd_old() {
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

        static void stopplayrecordsd() {
          //AudioNoInterrupts();
          playRawL.stop();
          playRawR.stop();
          //AudioInterrupts();
        }

        static void check_rec_folder_path(){
          if (!(SD.exists(((String)"SOUNDSET/REC").c_str()))) {
            if (!(SD.exists(((String)"SOUNDSET").c_str()))) {
              SD.mkdir(((String)"SOUNDSET").c_str());
            }
            SD.mkdir(((String)"SOUNDSET/REC").c_str());
          }
        }

        static void dolistofRecs() {
          int startx = 80;
          int starty = 16;
          canvastitle.setCursor(startx, 0);
          canvastitle.setTextSize(1);
          byte lerecdiri = self->getrecdir();
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
          byte lerecdiri = self->getrecdir();
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
          byte lerecddir = self->getrecdir();
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
            scheddule_wave_rebuild(true);
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
                  uint16_t height = 48){
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

                canvasBIG.drawFastVLine(x, yTop + 8, yBottom - yTop + 1, SSD1306_WHITE);
                
            }
            wave_file.close();
        }

        static void select_cursor() {
          String _legend[] = {"Select","Zoom Out","Zoom In","Normalize","Reverse","Pitch","Fade In","Fade Out","Preview","Del before","Del after","Del zone","Keep zone"," "," "};

          display.clearDisplay();
          dodisplay();
          int cursor_coords[][4] = {{0,0,18,8},{22,0,9,8},{38,0,9,8},{52,0,9,8},{64,0,9,8},{76,0,9,8},{88,0,14,8},{106,0,14,8},{0,8,128,48},
                                    {23,56,14,8},{40,56,21,8},{64,56,20,8},{88,56,27,8}};
          display.fillRect(cursor_coords[sublevels[self->relative_navlevel+1]][0], 
                            cursor_coords[sublevels[self->relative_navlevel+1]][1],
                            cursor_coords[sublevels[self->relative_navlevel+1]][2],
                            cursor_coords[sublevels[self->relative_navlevel+1]][3],
                            SSD1306_INVERSE);

           if (self->wave_selected) {
            redraw_selection_box();
          } 
          //display.fillRect(80,16, 38, 10, SSD1306_INVERSE);
          display.setTextSize(1);
          display.setTextColor(SSD1306_INVERSE);
          display.setCursor(68,12);
          display.print(_legend[sublevels[self->relative_navlevel +1]]);
          display.display();
        }

        static void draw_editor_zones(){
          dm.clean_title_1_1();
          canvastitle.print("Slt");
          canvastitle.print(" -  +");
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

        static void zoomRange(float subStart,float subEnd) {
          if (!self->wave_selected) return ;
          float zone_width = self->end_zone - self->start_zone;
          self->end_zone = self->start_zone + subEnd * zone_width;
          self->start_zone = self->start_zone + subStart * zone_width;
        }

        /*
        static void getRange(float startPos, float endPos,
              uint32_t &startByte,
              uint32_t &endByte,
              uint32_t sampleSize){ 

            uint32_t fileSize = src.size();
            startPos = constrain(startPos, 0.0f, 1.0f);
            endPos   = constrain(endPos, 0.0f, 1.0f);

            if (startPos > endPos)
                swap(startPos, endPos);

            startByte = ((uint32_t)(fileSize * startPos) / sampleSize) * sampleSize;
            endByte   = ((uint32_t)(fileSize * endPos) / sampleSize) * sampleSize;
        }
        */

        static void reverseSection(float startPos, float endPos) {
          if (locked_fileing)
          return;
          locked_fileing = 1 ;
            const uint16_t sampleSize = 2;      // 16-bit RAW
            const uint32_t blockSamples = 512;  // 1024-byte buffer
            uint8_t buffer[blockSamples * sampleSize];

            File src = SD.open(newloopedpath.c_str(), FILE_READ);
            if (!src) return;
            
            String new_file = get_new_file_name("SOUNDSET/REC/LOOP","#L.RAW") ;
            File dst = SD.open(new_file.c_str(), FILE_WRITE);
            if (!dst) {
                src.close();
                return;
            }

            uint32_t fileSize = src.size();

            // Clamp
            if (startPos < 0.0f) startPos = 0.0f;
            if (endPos > 1.0f) endPos = 1.0f;
            if (startPos > endPos) {
                float t = startPos;
                startPos = endPos;
                endPos = t;
            }

            uint32_t startByte = (uint32_t)(fileSize * startPos);
            uint32_t endByte   = (uint32_t)(fileSize * endPos);

            // Align to sample boundaries
            startByte = (startByte / sampleSize) * sampleSize;
            endByte   = (endByte / sampleSize) * sampleSize;

            src.seek(0);

            uint32_t remaining = startByte;

            while (remaining) {
                uint32_t n = min((uint32_t)sizeof(buffer), remaining);
                src.read(buffer, n);
                dst.write(buffer, n);
                remaining -= n;
            }

            int32_t pos = endByte;

            while (pos > (int32_t)startByte) {

                uint32_t chunk = min((uint32_t)(pos - startByte),
                                    (uint32_t)sizeof(buffer));

                // Keep sample alignment
                chunk = (chunk / sampleSize) * sampleSize;

                pos -= chunk;

                src.seek(pos);
                src.read(buffer, chunk);

                // Reverse samples inside buffer
                for (uint32_t i = 0; i < chunk; i += sampleSize) {

                    uint32_t srcIndex = chunk - sampleSize - i;

                    dst.write(buffer + srcIndex, sampleSize);
                }
            }

            src.seek(endByte);

            while (true) {
                int n = src.read(buffer, sizeof(buffer));
                if (n <= 0) break;
                dst.write(buffer, n);
            }

            src.close();
            dst.close();

            newloopedpath = new_file ;
            locked_fileing = 0 ;

        }

        static void pitchSection(float startPos, float endPos, float speed) {
          if (locked_fileing)
          return;
          locked_fileing = 1 ;
            if (speed <= 0.0f) return;

          File src = SD.open(newloopedpath.c_str(), FILE_READ);
          if (!src) return;
          
          String new_file = get_new_file_name("SOUNDSET/REC/LOOP","#L.RAW") ;
          File dst = SD.open(new_file.c_str(), FILE_WRITE);
          const uint32_t BUFFER_SAMPLES = 1024;
          int16_t buffer[BUFFER_SAMPLES];

          uint32_t fileSize = src.size();

          uint32_t startByte = (uint32_t)(fileSize * startPos);
          uint32_t endByte   = (uint32_t)(fileSize * endPos);

          startByte &= ~1;
          endByte   &= ~1;

          //----------------------------------------------------
          // Copy beginning
          //----------------------------------------------------

          src.seek(0);

          int16_t sample;

          while (src.position() < startByte)
          {
              src.read((uint8_t *)&sample, 2);
              dst.write((uint8_t *)&sample, 2);
          }

          //----------------------------------------------------
          // Buffered resampling
          //----------------------------------------------------

          uint32_t startSample = startByte / 2;
          uint32_t endSample   = endByte / 2;

          uint32_t bufferStart = 0;
          uint32_t samplesInBuffer = 0;

          auto loadBuffer = [&](uint32_t sampleIndex)
          {
              bufferStart = sampleIndex;

              src.seek(bufferStart * 2);

              samplesInBuffer =
                  src.read((uint8_t *)buffer,
                          BUFFER_SAMPLES * sizeof(int16_t))
                  / sizeof(int16_t);
          };

          loadBuffer(startSample);

          float pos = (float)startSample;

          while (pos < endSample - 1)
          {
              uint32_t index = (uint32_t)pos;

              // Need a new buffer?
              if (index < bufferStart ||
                  index + 1 >= bufferStart + samplesInBuffer)
              {
                  loadBuffer(index);

                  if (samplesInBuffer < 2)
                      break;
              }

              uint32_t local = index - bufferStart;

              float frac = pos - index;

              float s0 = buffer[local];
              float s1 = buffer[local + 1];

              float out = s0 + (s1 - s0) * frac;

              int16_t result = (int16_t)out;

              dst.write((uint8_t *)&result, 2);

              pos += speed;
          }

          //----------------------------------------------------
          // Copy end
          //----------------------------------------------------

          src.seek(endByte);

          while (src.read((uint8_t *)&sample, 2) == 2)
              dst.write((uint8_t *)&sample, 2);
          
          src.close();
          dst.close();
          newloopedpath = new_file ;
          locked_fileing = 0 ;
        }

        static void trimSection(float start_pos = 0.0f, float end_pos = 1.0f) {
          if (locked_fileing)
          return;
          locked_fileing = 1 ;
            File in = SD.open(newloopedpath.c_str(), FILE_READ);
            if (!in)
                return;

            String new_file = get_new_file_name("SOUNDSET/REC/LOOP","#L.RAW") ;
            File out = SD.open(new_file.c_str(), FILE_WRITE);
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
            locked_fileing = 0 ; 
            newloopedpath = new_file ;
        }
   
        static void normalizeSection(float startPos, float endPos) {
          if (locked_fileing)
          return;
          locked_fileing = 1 ;
            const uint16_t sampleSize = 2;      // 16-bit mono
            const uint32_t bufferSamples = 512;
            int16_t buffer[bufferSamples];

            File src = SD.open(newloopedpath.c_str(), FILE_READ);
            if (!src) return;
            
            String new_file = get_new_file_name("SOUNDSET/REC/LOOP","#L.RAW") ;
            File dst = SD.open(new_file.c_str(), FILE_WRITE);

            uint32_t fileSize = src.size();

            // Clamp
            if (startPos < 0.0f) startPos = 0.0f;
            if (endPos > 1.0f) endPos = 1.0f;

            if (startPos > endPos)
            {
                float t = startPos;
                startPos = endPos;
                endPos = t;
            }

            uint32_t startByte = (uint32_t)(fileSize * startPos);
            uint32_t endByte   = (uint32_t)(fileSize * endPos);

            startByte = (startByte / sampleSize) * sampleSize;
            endByte   = (endByte / sampleSize) * sampleSize;

            //----------------------------------------------------
            // PASS 1 : Find peak
            //----------------------------------------------------

            int16_t peak = 0;

            src.seek(startByte);

            uint32_t remaining = endByte - startByte;

            while (remaining)
            {
                uint32_t bytes = min((uint32_t)sizeof(buffer), remaining);

                src.read((uint8_t *)buffer, bytes);

                int samples = bytes / sampleSize;

                for (int i = 0; i < samples; i++)
                {
                    int32_t v = buffer[i];

                    if (v < 0)
                        v = -v;

                    if (v > peak)
                        peak = v;
                }

                remaining -= bytes;
            }

            if (peak == 0)
                return;

            float gain = (32767.0f * 0.99f) / peak;

            //----------------------------------------------------
            // Copy beginning unchanged
            //----------------------------------------------------

            src.seek(0);

            remaining = startByte;

            while (remaining)
            {
                uint32_t bytes = min((uint32_t)sizeof(buffer), remaining);

                src.read((uint8_t *)buffer, bytes);
                dst.write((uint8_t *)buffer, bytes);

                remaining -= bytes;
            }

            //----------------------------------------------------
            // PASS 2 : Normalize selected region
            //----------------------------------------------------

            src.seek(startByte);

            remaining = endByte - startByte;

            while (remaining)
            {
                uint32_t bytes = min((uint32_t)sizeof(buffer), remaining);

                src.read((uint8_t *)buffer, bytes);

                int samples = bytes / sampleSize;

                for (int i = 0; i < samples; i++)
                {
                    int32_t s = (int32_t)(buffer[i] * gain);

                    if (s > 32767)
                        s = 32767;
                    else if (s < -32768)
                        s = -32768;

                    buffer[i] = (int16_t)s;
                }

                dst.write((uint8_t *)buffer, bytes);

                remaining -= bytes;
            }

            //----------------------------------------------------
            // Copy end unchanged
            //----------------------------------------------------

            while (true)
            {
                int bytes = src.read((uint8_t *)buffer, sizeof(buffer));

                if (bytes <= 0)
                    break;

                dst.write((uint8_t *)buffer, bytes);
            }
          src.close();
          dst.close();
          newloopedpath = new_file ;
          locked_fileing = 0 ;
        }

        static void playSection(){
          PartialPlayerMono.play(newloopedpath.c_str(),self->start_zone,self->end_zone);
          returntonav(self->relative_navlevel + 1,11,sublevels[self->relative_navlevel + 1]);
        }

        static void scheddule_wave_rebuild(bool noreturn = 0){
          self->end_zone = 1.0;
          self->start_zone = 0.0 ;
          self->wave_buffed = 0 ;
          reinitsublevels(self->relative_navlevel + 1); 
          if (!noreturn)
            returntonav(self->relative_navlevel + 1,11,sublevels[self->relative_navlevel + 1]);
          locked_fileing = 0 ; 
        }

        static void fadeInSection(float startPos, float endPos) {
          if (locked_fileing)
          return;
          locked_fileing = 1 ;

          File src = SD.open(newloopedpath.c_str(), FILE_READ);
          if (!src) return;
          
          String new_file = get_new_file_name("SOUNDSET/REC/LOOP","#L.RAW") ;
          File dst = SD.open(new_file.c_str(), FILE_WRITE);
          //const uint16_t sampleSize = 2;
          const uint32_t BUFFER_SAMPLES = 1024;

          int16_t buffer[BUFFER_SAMPLES];

          uint32_t fileSize = src.size();

          uint32_t startByte = (uint32_t)(fileSize * startPos);
          uint32_t endByte   = (uint32_t)(fileSize * endPos);

          startByte &= ~1;
          endByte   &= ~1;

          //--------------------------------------------------
          // Copy beginning
          //--------------------------------------------------

          src.seek(0);

          while (src.position() < startByte)
          {
              uint32_t bytes = min((uint32_t)sizeof(buffer),
                                  startByte - src.position());

              src.read((uint8_t*)buffer, bytes);
              dst.write((uint8_t*)buffer, bytes);
          }

          //--------------------------------------------------
          // Fade
          //--------------------------------------------------

          uint32_t fadeSamples = (endByte - startByte) / 2;
          uint32_t sampleIndex = 0;

          while (sampleIndex < fadeSamples){
              uint32_t samples = min(BUFFER_SAMPLES,
                                    fadeSamples - sampleIndex);

              src.read((uint8_t*)buffer, samples * 2);

              for (uint32_t i = 0; i < samples; i++) {   
                  float x = (float)(sampleIndex + i) / (fadeSamples - 1);
                  float gain = sinf(x * (PI/2.0));

                  int32_t s = (int32_t)(buffer[i] * gain);


                  buffer[i] = (int16_t)s;
              }

              dst.write((uint8_t*)buffer, samples * 2);

              sampleIndex += samples;
          }

          //--------------------------------------------------
          // Copy remainder
          //--------------------------------------------------

          while (true)
          {
              int bytes = src.read((uint8_t*)buffer, sizeof(buffer));

              if (bytes <= 0)
                  break;

              dst.write((uint8_t*)buffer, bytes);
          }

          src.close();
          dst.close();
          newloopedpath = new_file ;
          locked_fileing = 0 ;
        }

        //TODO yes I know it's not very optimized to use 2 methods...
        static void fadeOutSection(float startPos, float endPos) {
          if (locked_fileing)
          return;
          locked_fileing = 1 ;

          File src = SD.open(newloopedpath.c_str(), FILE_READ);
          if (!src) return;
          
          String new_file = get_new_file_name("SOUNDSET/REC/LOOP","#L.RAW") ;
          File dst = SD.open(new_file.c_str(), FILE_WRITE);

          //const uint16_t sampleSize = 2;
          const uint32_t BUFFER_SAMPLES = 1024;

          int16_t buffer[BUFFER_SAMPLES];

          uint32_t fileSize = src.size();

          uint32_t startByte = (uint32_t)(fileSize * startPos);
          uint32_t endByte   = (uint32_t)(fileSize * endPos);

          startByte &= ~1;
          endByte   &= ~1;

          //--------------------------------------------------
          // Copy beginning
          //--------------------------------------------------

          src.seek(0);

          while (src.position() < startByte)
          {
              uint32_t bytes = min((uint32_t)sizeof(buffer),
                                  startByte - src.position());

              src.read((uint8_t*)buffer, bytes);
              dst.write((uint8_t*)buffer, bytes);
          }

          //--------------------------------------------------
          // Fade
          //--------------------------------------------------

          uint32_t fadeSamples = (endByte - startByte) / 2;
          uint32_t sampleIndex = 0;

          while (sampleIndex < fadeSamples)
          {
              uint32_t samples = min(BUFFER_SAMPLES,
                                    fadeSamples - sampleIndex);

              src.read((uint8_t*)buffer, samples * 2);

              for (uint32_t i = 0; i < samples; i++)
              {
                  float x = (float)(sampleIndex + i) / (fadeSamples - 1);
                  float gain = cosf(x * (PI/2));

                  int32_t s = (int32_t)(buffer[i] * gain);

                  buffer[i] = (int16_t)s;
              }

              dst.write((uint8_t*)buffer, samples * 2);

              sampleIndex += samples;
          }

          //--------------------------------------------------
          // Copy remainder
          //--------------------------------------------------

          while (true)
          {
              int bytes = src.read((uint8_t*)buffer, sizeof(buffer));

              if (bytes <= 0)
                  break;

              dst.write((uint8_t*)buffer, bytes);
          }
          src.close();
          dst.close();
          newloopedpath = new_file ;
          locked_fileing = 0 ;
        }

        static void deleteSection(float startPos, float endPos){
          if (locked_fileing)
          return;
          locked_fileing = 1 ;

          File src = SD.open(newloopedpath.c_str(), FILE_READ);
          if (!src) return;
          
          String new_file = get_new_file_name("SOUNDSET/REC/LOOP","#L.RAW") ;
          File dst = SD.open(new_file.c_str(), FILE_WRITE);
          const uint32_t BUFFER_SIZE = 2048;
          uint8_t buffer[BUFFER_SIZE];

          uint32_t fileSize = src.size();

          // Clamp
          if (startPos < 0.0f) startPos = 0.0f;
          if (startPos > 1.0f) startPos = 1.0f;

          if (endPos < 0.0f) endPos = 0.0f;
          if (endPos > 1.0f) endPos = 1.0f;

          // Ensure start <= end
          if (startPos > endPos)
          {
              float t = startPos;
              startPos = endPos;
              endPos = t;
          }

          uint32_t startByte = (uint32_t)(fileSize * startPos);
          uint32_t endByte   = (uint32_t)(fileSize * endPos);

          // Align to 16-bit samples
          startByte &= ~1;
          endByte   &= ~1;

          //--------------------------------------------------
          // Copy everything before the deleted section
          //--------------------------------------------------

          src.seek(0);

          uint32_t remaining = startByte;

          while (remaining)
          {
              uint32_t chunk = (remaining > BUFFER_SIZE) ? BUFFER_SIZE : remaining;

              src.read(buffer, chunk);
              dst.write(buffer, chunk);

              remaining -= chunk;
          }

          //--------------------------------------------------
          // Skip the deleted section
          //--------------------------------------------------

          src.seek(endByte);

          //--------------------------------------------------
          // Copy everything after the deleted section
          //--------------------------------------------------

          while (true)
          {
              int bytesRead = src.read(buffer, BUFFER_SIZE);

              if (bytesRead <= 0)
                  break;

              dst.write(buffer, bytesRead);
          }

          src.close();
          dst.close();
          newloopedpath = new_file ;
          locked_fileing = 0 ;
        }

        static void edit_record(){
          navrange = 12 ;
           if (navlevel == self->relative_navlevel+1) {
            
            if (!self->wave_buffed) {
              draw_editor_zones();
              self->wave_buffed = 1 ; 
              drawWaveform(self->start_zone,self->end_zone);
              dodisplay();
            }
            select_cursor();
           }
          //filter(?)
          if (navlevel == self->relative_navlevel + 2) {
            //TODO make undo / redo system via temp sd file
            //dezoom
            if (sublevels[self->relative_navlevel + 1] == 1){
              scheddule_wave_rebuild();
            }
            
            //zoom in
            if (sublevels[self->relative_navlevel + 1] == 2){
              zoomRange((sublevels[self->relative_navlevel + 2] / 127.0 ),((sublevels[self->relative_navlevel + 2] + sublevels[self->relative_navlevel + 3] ) / 127.0 ));
              self->wave_buffed = 0 ;
              reinitsublevels(self->relative_navlevel + 2);
              returntonav(self->relative_navlevel + 1,11,sublevels[self->relative_navlevel + 1]);
            }

            //select
            if (sublevels[self->relative_navlevel + 1] == 0){
              self->wave_selected = 0;
              navrange = 127 ;
              display.clearDisplay();
              display.drawFastVLine(sublevels[self->relative_navlevel +2], 8, 48, SSD1306_INVERSE);
              dodisplay();
            }
            
            //normalize
            if (sublevels[self->relative_navlevel + 1] == 3){
              normalizeSection(self->start_zone,self->end_zone);
              scheddule_wave_rebuild();
            }

            //reverse
            if (sublevels[self->relative_navlevel + 1] == 4){
              reverseSection(self->start_zone,self->end_zone);
              scheddule_wave_rebuild();
            }
            //pitching
            if (sublevels[self->relative_navlevel + 1] == 5){
              pitchSection(self->start_zone,self->end_zone,0.5);
              scheddule_wave_rebuild();
            }

            //trim in
            if (sublevels[self->relative_navlevel + 1] == 9){
              trimSection(self->start_zone,1.0);
              scheddule_wave_rebuild();
            }
            //trim out
            if (sublevels[self->relative_navlevel + 1] == 10){
              trimSection(0.0,self->end_zone);
              scheddule_wave_rebuild();
            }
            //del selected
            if (sublevels[self->relative_navlevel + 1] == 11){
              deleteSection(self->start_zone,self->end_zone);
              scheddule_wave_rebuild();
            }
            //keep selected
            if (sublevels[self->relative_navlevel + 1] == 12){
              trimSection(self->start_zone,self->end_zone);
              scheddule_wave_rebuild();
            }
            //fadein
            if (sublevels[self->relative_navlevel + 1] == 6){
              fadeInSection(self->start_zone,self->end_zone);
              scheddule_wave_rebuild();
            }
            //fadeout
            if (sublevels[self->relative_navlevel + 1] == 7){
              fadeOutSection(self->start_zone,self->end_zone);
              scheddule_wave_rebuild();
            }
            
            //playSection
            if (sublevels[self->relative_navlevel + 1] == 8){
              playSection();
              returntonav(self->relative_navlevel + 1,11,sublevels[self->relative_navlevel + 1]);
            }

          }
          //select end
          if (navlevel == self->relative_navlevel + 3) {
            if (sublevels[self->relative_navlevel + 1] == 0){
              navrange = 127 - sublevels[self->relative_navlevel +2] ;
              display.clearDisplay();
              dodisplay();
              display.fillRect(sublevels[self->relative_navlevel +2], 8, 
                                sublevels[self->relative_navlevel +3],48, SSD1306_INVERSE);
              display.display();
            //returntonav(self->relative_navlevel + 1, self->home_navrange,0);
            }
          }
          if (navlevel > self->relative_navlevel +3) {
              returntonav(self->relative_navlevel + 1,11,sublevels[self->relative_navlevel + 1]);
              self->wave_selected = 1;
              }
        }
        float previous_offset = 0.0f ;
        float start_zone = 0.0f ;
        float end_zone = 1.0f ; 
        bool wave_buffed = 0 ;
        bool wave_selected = 0 ;
        static constexpr void (*_route_nav[9])() = {&rec_nav_zero, &records_actions, &records_actions,
                                    &records_actions, &records_actions,&records_actions, &records_actions,
                                    &records_actions, &records_actions};
        
        static constexpr void  (*_nav_recs[5])() = {&recordVpanel, &load_record, &remove_record, &rec_params, &edit_record};
        

  private:
    static RecorderMenuRouter* self;
};

RecorderMenuRouter* RecorderMenuRouter::self = nullptr;
EXTMEM RecorderMenuRouter _rd;
       
        
