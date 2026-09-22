#include <sys/_stdint.h>
#include <stdint.h>
#include "Patterns.h"
#include "WaveEditorMenu.h"
#include "SamplerMenu.h"
#include "Presets.h"


RecorderMenuRouter* RecorderMenuRouter::self = nullptr;

RecorderMenuRouter::RecorderMenuRouter() : catalog("SOUNDSET/REC/","LOOP","#L.RAW",recorder_menu,5) {
                    self = this;
                    self->home_navrange=self->rec_labels_count - 1;
                    self->relative_navlevel=1;
                    self->max_navlevel=5;
                    self->sublevels_address={7,3,0};
                    }


void RecorderMenuRouter::show() {
  _route_nav[mc.navlevel-self->relative_navlevel]();
}

void RecorderMenuRouter::Load_raw_file() {
  clear_temp_files();
  if (!self->catalog.get_current_file_path(self->newRecpathL, sizeof(self->newRecpathL))) return;
  strcpy(self->newloopedpath, self->newRecpathL);
  //TODO if stereo
  //strcpy(self->newRecpathR, self->newRecpathL);
}

void RecorderMenuRouter::disarm_pre_record(){
  self->rec_looping = true ;
  self->pre_record = false ;
}

void RecorderMenuRouter::startRecording() {
  if (mc.locked_fileing) return;
  mc.locked_fileing = 1 ;
  if (!self->just_pressed_rec){
    self->just_pressed_rec = true ;
    check_rec_folder_path();
    mc.tocker = millis();
    if (!self->catalog.get_new_file_name(self->newloopedpath, sizeof(self->newloopedpath))) return;
    self->looper = SD.sdfs.open((const char*)self->newloopedpath,O_WRITE | O_CREAT | O_TRUNC);
    if (self->looper) {
      queue1.begin();
      self->pre_record = true;
      Tocker.attach_one_shot(disarm_pre_record);
     
    } else {
      self->rec_looping = false ;
    }
      //TODO: pattern synched record
      //start at pat pos
      //rec mono
      // ends in 32 ticks
      //save sample
      // assign saved to note 50
      // set pattern empty and place note 50 on 0
      //clear locks
  }
}


void RecorderMenuRouter::auto_stop_rec(){
  if (millis() - mc.tocker > 10000) {
    self->rec_looping = false ;
    stopRecording();
  }
}

void RecorderMenuRouter::continue_looper() {
  if (queue1.available() >= 2) {
    byte rec_buffer[512];
    memcpy(rec_buffer, queue1.readBuffer(), 256);
    queue1.freeBuffer();
    memcpy(rec_buffer+256, queue1.readBuffer(), 256);
    queue1.freeBuffer();
    // write all 512 bytes to the SD card
    //elapsedMicros usec = 0;
    self->looper.write(rec_buffer, 512);
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

void RecorderMenuRouter::stopRecording() {
  if (self->looper) {
  //AudioNoInterrupts();
  queue1.end();
  while (queue1.available() > 0) {
    self->looper.write((byte *)queue1.readBuffer(), 256);
    queue1.freeBuffer();
  }
  self->looper.close();
  queue1.clear();
  //AudioInterrupts();
  clear_temp_files();

  _sp.dosoundlist();
  }
  self->just_pressed_rec = false ;
  self->pre_record = false;
  if (self->autoassign) {
    _sp.loadSampledSound();
  }
  mc.locked_fileing = 0 ;
}

void RecorderMenuRouter::recordVpanelAction() {
          if (mc.navlevel == self->relative_navlevel + 2) {
            byte slct = mc.sublevels[self->relative_navlevel + 1];
            if (slct == 0) {
              self->recorderrecord = !self->recorderrecord;
              if (self->recorderrecord) {

                if (self->recorderstop) {
                  self->recorderstop = 0;
                }
                if (self->recorderplay) {
                  self->recorderplay = 0;
                  stopplayrecordsd();
                }
                startRecording();
              }
            }

            if (slct == 1) {
              self->recorderplay = !self->recorderplay;
              if (self->recorderplay) {
                if (self->recorderstop) {
                  self->recorderstop = 0;
                }
                if (self->recorderrecord) {
                  self->recorderrecord = 0;
                  stopRecording();
                }
                playrecordsd();
              }
            }
            if (slct == 2) {
              self->recorderstop = !self->recorderstop;
              if (self->recorderstop) {
                if (self->recorderplay) {
                  self->recorderplay = 0;
                  stopplayrecordsd();
                }
                if (self->recorderrecord) {
                  self->recorderrecord = 0;
                  stopRecording();
                }
              }
            }
            dm.returntonav(self->relative_navlevel + 1, 2 , 0);
          }
          if (mc.navlevel > self->relative_navlevel + 1) {
            dm.returntonav(self->relative_navlevel + 1, 2 , 0);
          }
        }

void RecorderMenuRouter::recordVpanelSelector() {
          if (mc.navlevel == self->relative_navlevel + 1) {
            mc.navrange = 2;
          }
          byte slct = mc.sublevels[self->relative_navlevel + 1];

          if (slct == 0) {
            if (!self->recorderrecord) {
              dm.canvasBIG.drawRoundRect(82, 18, 128 - 80 - 4, 20 - 4, 2, SSD1306_WHITE);
            } else {
              dm.canvasBIG.drawRoundRect(82, 18, 128 - 80 - 4, 20 - 4, 2, SSD1306_BLACK);
            }
          }

          if (slct == 1) {
            if (!playRawL.isPlaying()) {
              dm.canvasBIG.drawRoundRect(2, 18, 128 - 90 - 4, 20 - 4, 2, SSD1306_WHITE);
            } else {
              dm.canvasBIG.drawRoundRect(2, 18, 128 - 90 - 4, 20 - 4, 2, SSD1306_BLACK);
            }
          }
          if (slct == 2) {
            if (!self->recorderstop) {
              dm.canvasBIG.drawRoundRect(2, 18 + 20 + 4, 128 - 90 - 4, 20 - 4, 2,
                                      SSD1306_WHITE);
            } else {
              dm.canvasBIG.drawRoundRect(2, 18 + 20 + 4, 128 - 90 - 4, 20 - 4, 2,
                                      SSD1306_BLACK);
            }
          }
        }

void RecorderMenuRouter::recordVpanel() {
          recordVpanelAction();
          dm.clearDisplay();
          dm.clear_buffs();
          if (!self->recorderrecord) {
            dm.canvasBIG.drawRoundRect(80, 16, 128 - 80, 20, 2, SSD1306_WHITE);
            dm.canvasBIG.setTextColor(SSD1306_WHITE);
            dm.canvasBIG.setCursor(87, 16 + 6);
            dm.canvasBIG.print("Rec.");
          } else {
            dm.canvasBIG.fillRoundRect(80, 16, 128 - 80, 20, 2, SSD1306_WHITE);
            dm.canvasBIG.setCursor(87, 16 + 6);
            dm.canvasBIG.setTextColor(SSD1306_BLACK);
            dm.canvasBIG.print("Rec.");
            dm.canvasBIG.setTextColor(SSD1306_WHITE);
          }
          if (!playRawL.isPlaying()) {
            dm.canvasBIG.drawRoundRect(0, 16, 128 - 90, 20, 2, SSD1306_WHITE);
            dm.canvasBIG.setTextColor(SSD1306_WHITE);
            dm.canvasBIG.setCursor(7, 16 + 6);
            dm.canvasBIG.print("Play");
          } else {
            dm.canvasBIG.fillRoundRect(0, 16, 128 - 90, 20, 2, SSD1306_WHITE);
            dm.canvasBIG.setCursor(7, 16 + 6);
            dm.canvasBIG.setTextColor(SSD1306_BLACK);
            dm.canvasBIG.print("Play");
            dm.canvasBIG.setTextColor(SSD1306_WHITE);
          }
          if (!self->recorderstop) {
            dm.canvasBIG.drawRoundRect(0, 16 + 20 + 4, 128 - 90, 20, 2, SSD1306_WHITE);
            dm.canvasBIG.setCursor(7, 6 + 16 + 20 + 4);
            dm.canvasBIG.setTextColor(SSD1306_WHITE);
            dm.canvasBIG.print("Stop");
          } else {
            dm.canvasBIG.fillRoundRect(0, 16 + 20 + 4, 128 - 90, 20, 2, SSD1306_WHITE);
            dm.canvasBIG.setCursor(7, 6 + 16 + 20 + 4);
            dm.canvasBIG.setTextColor(SSD1306_BLACK);
            dm.canvasBIG.print("Stop");
            dm.canvasBIG.setTextColor(SSD1306_WHITE);
          }

          recordVpanelSelector();

          dm.dodisplay();
        }

void RecorderMenuRouter::playrecordsd() {
            //Serial.println(self->newloopedpath);

          if (SD.sdfs.exists(self->newloopedpath)) {
            AudioNoInterrupts();
            playRawL.play(self->newloopedpath);
            if (self->modestereo) {
              playRawR.play(self->newRecpathR);
            } else {
              playRawR.play(self->newloopedpath);
            }
            AudioInterrupts();
          }
        }

void RecorderMenuRouter::playrecordsd_pathed(const char* lepath) {
    //Serial.print(lepath);
  if (SD.sdfs.exists(lepath)) {
    AudioNoInterrupts();
    playRawL.play(lepath);
    if (self->modestereo) {
      playRawR.play(self->newRecpathR);
    } else {
      playRawR.play(lepath);
    }
    AudioInterrupts();
  } else {
    Serial.println("");
    Serial.print("error playing ");
    Serial.print(lepath);
  }
}

void RecorderMenuRouter::stopplayrecordsd() {
  //AudioNoInterrupts();
  playRawL.stop();
  playRawR.stop();
  //AudioInterrupts();
}

void RecorderMenuRouter::check_rec_folder_path(){
  if (!(SD.sdfs.exists("SOUNDSET/REC"))) self->catalog.make_sub_folder("SOUNDSET", "REC");
}

void RecorderMenuRouter::deleteRec() {
  self->catalog.deleteFile();
}

void RecorderMenuRouter::recorder_menu() {
          self->catalog.folders_mode = false ;
          scheddule_wave_rebuild(1,1);
          const char* Recmenulabels[6] = {"Record", "Load", "Delete", "Params","Edit","../"};
          dm.main_panel(Recmenulabels,1,6);
        }

void RecorderMenuRouter::rec_params(){
          dm.clean_title_2_1();
          dm.setCursor(0,0);
          dm.print("Placeholder");
          dm.dodisplay();
        }

void RecorderMenuRouter::rec_nav_zero(){
  mc.navrange = self->home_navrange;
  self->catalog.nav_zero();
}

void RecorderMenuRouter::drawFoldersList(){

          self->catalog.folders_mode = true ;
          //self->catalog.folder_dir = "SOUNDSET/" ;
          strncpy(self->catalog.folder_dir, "SOUNDSET/", 31);
          self->catalog.folder_dir[31] = '\0';
          self->catalog.extension = ".RAW" ;
          if (!self->catalog.folders_already_listed){
            self->catalog.displayable_offset = 0 ;
            self->catalog.list_files();
            //Serial.println("folders listed");
            //set this to false when creating new soundbank or temp
            self->catalog.folders_already_listed = true;
          }
          mc.navrange = max(self->catalog.folders_counter - 1, 0);
          //
          //Serial.println(self->catalog.folder_selected );
          self->catalog.display_folders_list();
          dm.dodisplay();
          //Serial.println(self->catalog.folder_selected);
          if (mc.navlevel > self->relative_navlevel+1){
            char entering_dir[64];
            snprintf(entering_dir, sizeof(entering_dir), "%s%s/", self->catalog.folder_dir, self->catalog.folder_selected);
            if (SD.sdfs.exists(entering_dir)) {
              self->catalog.folders_mode = false;
              strncpy(self->catalog.folder_dir, entering_dir, sizeof(self->catalog.folder_dir) - 1);
              self->catalog.folder_dir[sizeof(self->catalog.folder_dir) - 1] = '\0';
              if (!strcmp(self->catalog.folder_selected, "REC")) self->catalog.extension = "#L.RAW";
            }else {
              Serial.println("error with dir");
              Serial.println(self->catalog.folder_selected);
              dm.returntonav(self->relative_navlevel,self->home_navrange,0);
            }
            self->catalog.list_files();
            self->catalog.folders_already_listed = false;

            dm.returntonav(self->relative_navlevel,self->home_navrange,0);
          }
        }

void RecorderMenuRouter::lv1_wrapper(void (*func)()) {
          dm.clean_title_2_1();
          self->catalog.nav_one(99,1);

          if (mc.navlevel >= self->relative_navlevel + 2) {
            func();
            scheddule_wave_rebuild(true);
            dm.returntonav(self->relative_navlevel, self->home_navrange,mc.sublevels[self->relative_navlevel]);
          }
          dm.dodisplay();
        }

void RecorderMenuRouter::records_actions(){
          _nav_recs[mc.sublevels[self->relative_navlevel]%self->rec_labels_count]();
        }

void RecorderMenuRouter::remove_record(){
  lv1_wrapper(self->deleteRec);
}

void RecorderMenuRouter::load_record(){
          lv1_wrapper(self->Load_raw_file);
        }

void RecorderMenuRouter::drawWaveform(float startPos,float endPos, uint16_t width, uint16_t height){
  FsFile wave_file = SD.sdfs.open(self->newloopedpath, O_READ);
  if (!wave_file) return;
  uint32_t totalSamples = wave_file.size() / 2; // 16-bit mono
  uint32_t firstSample = (uint32_t)(startPos * totalSamples);
  uint32_t lastSample  = (uint32_t)(endPos   * totalSamples);
  uint32_t visibleSamples = lastSample - firstSample;
  if (!visibleSamples) return;
  for (uint16_t x = 0; x < width; x++) {
    uint32_t start = firstSample + ((uint64_t)x * visibleSamples) / width;
    uint32_t end = firstSample + ((uint64_t)(x + 1) * visibleSamples) / width;
    if (end <= start) end = start + 1;
    wave_file.seek(start * 2);
    int16_t minSample = 32767;
    int16_t maxSample = -32768;
    for (uint32_t i = start; i < end; i++) {
      int16_t sample_selected;
      wave_file.read((uint8_t *)&sample_selected, sizeof(sample_selected));
      if (sample_selected < minSample) minSample = sample_selected;
      if (sample_selected > maxSample) maxSample = sample_selected;
    }
    int yTop = map(maxSample, 32767, -32768, 0, height - 1);
    int yBottom = map(minSample, 32767, -32768, 0, height - 1);
    dm.canvasBIG.drawFastVLine(x, yTop + 8, yBottom - yTop + 1, SSD1306_WHITE);
  }
  wave_file.close();
}

void RecorderMenuRouter::select_cursor() {
  const char* _legend[15] = {"Select","Zoom Out","Zoom In","Normalize","Reverse","Pitch x","Fade In","Fade Out",
                      "Preview","Del before","Del after","Del zone","Keep zone","Undo"," "};
  dm.clearDisplay();
  dm.dodisplay();
  int cursor_coords[15][4] = {{0,0,18,8},{22,0,9,8},{38,0,9,8},{52,0,9,8},{64,0,9,8},{76,0,9,8},{88,0,14,8},{106,0,14,8},{0,8,128,48},
                            {23,56,14,8},{40,56,21,8},{64,56,20,8},{88,56,27,8},{116,56,12,8},{128,128,128,128}};
  dm.fillRect(cursor_coords[mc.sublevels[self->relative_navlevel+1]][0],
                    cursor_coords[mc.sublevels[self->relative_navlevel+1]][1],
                    cursor_coords[mc.sublevels[self->relative_navlevel+1]][2],
                    cursor_coords[mc.sublevels[self->relative_navlevel+1]][3],
                    SSD1306_INVERSE);

    if (self->wave_selected) {
    redraw_selection_box();
  }
  dm.setTextSize(1);
  dm.setTextColor(SSD1306_INVERSE);
  dm.setCursor(60,12);
  dm.print(_legend[mc.sublevels[self->relative_navlevel +1]]);
  dm.display();
}

void RecorderMenuRouter::draw_editor_zones(){
  dm.clean_title_1_1();
  dm.canvastitle.print("Slt");
  dm.canvastitle.print(" -  +");
  dm.canvastitle.print(" A");//amplify
  dm.canvastitle.print(" R");//reverse
  dm.canvastitle.print(" P");//Pitch
  dm.canvastitle.print(" Fi");//fade In
  dm.canvastitle.print(" Fo");//fade out
  dm.canvasBIG.setCursor(0,57);
  dm.canvasBIG.print("Cut In");//trim from start of zone to eof
  dm.canvasBIG.print(" Out");// trim from begining to end of zone
  dm.canvasBIG.print(" Del");// remove selected zone
  dm.canvasBIG.print(" Trim");// keep only selected zone
  dm.canvasBIG.print((char)14);// Undo
}

void RecorderMenuRouter::redraw_selection_box(){
  dm.fillRect(mc.sublevels[self->relative_navlevel +2], 8,
                      mc.sublevels[self->relative_navlevel +3],48, SSD1306_INVERSE);

}

void RecorderMenuRouter::zoomRange(float subStart,float subEnd) {
  if (!self->wave_selected) return ;
  float zone_width = self->end_zone - self->start_zone;
  self->end_zone = self->start_zone + subEnd * zone_width;
  self->start_zone = self->start_zone + subStart * zone_width;
}

void RecorderMenuRouter::reverseSection(float startPos, float endPos) {
  self->backup_current();
  //TODO: manage undoables
    Serial.println();
  Serial.print(" setting undoable at index ");
  Serial.print(max(self->catalog.tmp_count-1,0));  
  Serial.print(" to ");
  Serial.print(self->catalog.tmp_index);
  self->undoables[max(self->catalog.tmp_count-1,0)] = self->catalog.tmp_index;
  if (mc.locked_fileing) return;
  const uint16_t sampleSize = 2;
  const uint32_t blockSamples = 512;
  uint8_t buffer[blockSamples * sampleSize];
  FsFile src = SD.sdfs.open(self->newloopedpath, O_READ);
  if (!src) return;
  char new_tmp_path2[64];
  if (!self->catalog.get_new_tmp_name(new_tmp_path2, sizeof(new_tmp_path2),0)) return;

  FsFile dst = SD.sdfs.open(new_tmp_path2, O_WRITE | O_CREAT | O_TRUNC);
  if (!dst) {
    src.close();
    return;
  }
  mc.locked_fileing = 1 ;
  uint32_t fileSize = src.size();
  if (startPos < 0.0f) startPos = 0.0f;
  if (endPos > 1.0f) endPos = 1.0f;
  if (startPos > endPos) {
    float t = startPos;
    startPos = endPos;
    endPos = t;
  }
  uint32_t startByte = (uint32_t)(fileSize * startPos);
  uint32_t endByte   = (uint32_t)(fileSize * endPos);
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
    uint32_t chunk = min((uint32_t)(pos - startByte),(uint32_t)sizeof(buffer));
    chunk = (chunk / sampleSize) * sampleSize;
    pos -= chunk;
    src.seek(pos);
    src.read(buffer, chunk);
    for (uint32_t i = 0; i < chunk; i += sampleSize) {
      uint32_t srcIndex = chunk - sampleSize - i;
      dst.write(buffer + srcIndex, sampleSize);
    }
  }
  src.seek(endByte);
  while (int n = src.read(buffer, sizeof(buffer))) dst.write(buffer, n);
  src.close();
  dst.close();
  mc.locked_fileing = 0 ;
  self->apply_to_file();
}

void RecorderMenuRouter::pitchSection(float startPos, float endPos, float speed) {
  self->backup_current();
  self->undoables[max(self->catalog.tmp_count-1,0)] = self->catalog.tmp_index;
  if (mc.locked_fileing || speed <= 0.0f) return;
  FsFile src = SD.sdfs.open(self->newloopedpath, O_READ);
  if (!src) return;
  char new_tmp_path2[64];
  if (!self->catalog.get_new_tmp_name(new_tmp_path2, sizeof(new_tmp_path2),0)) return;
  FsFile dst = SD.sdfs.open(new_tmp_path2, O_WRITE | O_CREAT | O_TRUNC);
  mc.locked_fileing = 1 ;
  const uint32_t BUFFER_SAMPLES = 1024;
  int16_t buffer[BUFFER_SAMPLES];
  uint32_t fileSize = src.size();
  uint32_t startByte = (uint32_t)(fileSize * startPos);
  uint32_t endByte   = (uint32_t)(fileSize * endPos);
  startByte &= ~1;
  endByte   &= ~1;
  src.seek(0);
  int16_t sample;
  while (src.position() < startByte) {
    src.read((uint8_t *)&sample, 2);
    dst.write((uint8_t *)&sample, 2);
  }
  uint32_t startSample = startByte / 2;
  uint32_t endSample   = endByte / 2;
  uint32_t bufferStart = 0;
  uint32_t samplesInBuffer = 0;

  auto loadBuffer = [&](uint32_t sampleIndex) {
    bufferStart = sampleIndex;
    src.seek(bufferStart * 2);
    samplesInBuffer = src.read((uint8_t *)buffer, BUFFER_SAMPLES * sizeof(int16_t)) / sizeof(int16_t);
  };
  loadBuffer(startSample);
  float pos = (float)startSample;
  while (pos < endSample - 1) {
    uint32_t index = (uint32_t)pos;
    if (index < bufferStart || index + 1 >= bufferStart + samplesInBuffer) {
      loadBuffer(index);
      if (samplesInBuffer < 2) break;
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
  src.seek(endByte);
  while (src.read((uint8_t *)&sample, 2) == 2) dst.write((uint8_t *)&sample, 2);
  src.close();
  dst.close();
  mc.locked_fileing = 0 ;
  self->apply_to_file();
}

void RecorderMenuRouter::backup_current(){
  char new_tmp_path[64];
  if (!self->catalog.get_new_tmp_name(new_tmp_path, sizeof(new_tmp_path))) return;
  Serial.println();
  Serial.print("Backuping from ");
  Serial.print(self->newloopedpath);  
  Serial.print(" to ");
  Serial.print(new_tmp_path);
  self->catalog.copyFileGeneric(self->newloopedpath, new_tmp_path);
}

void RecorderMenuRouter::apply_to_file(){
  char current_tmp_path[64];
  if (!self->catalog.get_full_tmp_file_path(current_tmp_path, sizeof(current_tmp_path),max(self->catalog.tmp_index,0))) return;
  Serial.println();
  Serial.print("Applying to ");
  Serial.print(self->newloopedpath);  
  Serial.print(" from ");
  Serial.print(current_tmp_path);
  self->catalog.move_file(current_tmp_path, self->newloopedpath);
}

void RecorderMenuRouter::trimSection(float start_pos, float end_pos) {
  self->backup_current();
  self->undoables[max(self->catalog.tmp_count-1,0)] = self->catalog.tmp_index;
  if (mc.locked_fileing) return;
  FsFile in = SD.sdfs.open(self->newloopedpath, O_READ);
  if (!in) return;
  char _tmp_path[64];
  if (!self->catalog.get_new_tmp_name(_tmp_path, sizeof(_tmp_path),max(self->catalog.tmp_index,0))) return;
  FsFile out = SD.sdfs.open(_tmp_path, O_WRITE | O_CREAT | O_TRUNC);
  if (!out) {
    in.close();
    mc.locked_fileing = 0 ;
    return;
  }
  mc.locked_fileing = 1 ;
  uint32_t fileSize = in.size();
  start_pos = constrain(start_pos, 0.0f, 1.0f);
  end_pos   = constrain(end_pos,   0.0f, 1.0f);
  if (start_pos >= end_pos) {
    in.close();
    out.close();
    mc.locked_fileing = 0 ;
    return;
  }
  uint32_t startByte = (uint32_t)(start_pos * fileSize);
  uint32_t endByte   = (uint32_t)(end_pos   * fileSize);
  startByte &= ~1;
  endByte   &= ~1;
  if (endByte > fileSize) endByte = fileSize;
  if (startByte >= endByte) {
    in.close();
    out.close();
    mc.locked_fileing = 0 ;
    return;
  }
  in.seek(startByte);
  uint32_t remaining = endByte - startByte;
  uint8_t buffer[4096];
  while (remaining) {
    uint32_t chunk = min((uint32_t)sizeof(buffer), remaining);
    int bytesRead = in.read(buffer, chunk);
    if (bytesRead <= 0) break;
    out.write(buffer, bytesRead);
    remaining -= bytesRead;
  }
  out.close();
  in.close();
  mc.locked_fileing = 0 ;
  self->apply_to_file();
}

void RecorderMenuRouter::normalizeSection(float startPos, float endPos) {
  self->backup_current();
  self->undoables[max(self->catalog.tmp_count-1,0)] = self->catalog.tmp_index;
  if (mc.locked_fileing) return;
  const uint16_t sampleSize = 2;
  const uint32_t bufferSamples = 512;
  int16_t buffer[bufferSamples];
  FsFile src = SD.sdfs.open(self->newloopedpath, O_READ);
  if (!src) return;
  char _tmp_path[64];
  if (!self->catalog.get_new_tmp_name(_tmp_path, sizeof(_tmp_path),max(self->catalog.tmp_index,0))) return;
  FsFile dst = SD.sdfs.open(_tmp_path, O_WRITE | O_CREAT | O_TRUNC);
  mc.locked_fileing = 1 ;
  uint32_t fileSize = src.size();
  if (startPos < 0.0f) startPos = 0.0f;
  if (endPos > 1.0f) endPos = 1.0f;
  if (startPos > endPos) {
    float t = startPos;
    startPos = endPos;
    endPos = t;
  }
  uint32_t startByte = (uint32_t)(fileSize * startPos);
  uint32_t endByte = (uint32_t)(fileSize * endPos);
  startByte = (startByte / sampleSize) * sampleSize;
  endByte = (endByte / sampleSize) * sampleSize;
  int16_t peak = 0;
  src.seek(startByte);
  uint32_t remaining = endByte - startByte;
  while (remaining) {
    uint32_t bytes = min((uint32_t)sizeof(buffer), remaining);
    src.read((uint8_t *)buffer, bytes);
    int samples = bytes / sampleSize;
    for (int i = 0; i < samples; i++) {
        int32_t v = buffer[i];
        if (v < 0) v = -v;
        if (v > peak) peak = v;
    }
    remaining -= bytes;
  }
  if (peak == 0){
    mc.locked_fileing = 0 ;
    return;
  }
  float gain = (32767.0f * 0.99f) / peak;
  src.seek(0);
  remaining = startByte;

  while (remaining) {
    uint32_t bytes = min((uint32_t)sizeof(buffer), remaining);
    src.read((uint8_t *)buffer, bytes);
    dst.write((uint8_t *)buffer, bytes);
    remaining -= bytes;
  }
  src.seek(startByte);
  remaining = endByte - startByte;
  while (remaining) {
    uint32_t bytes = min((uint32_t)sizeof(buffer), remaining);
    src.read((uint8_t *)buffer, bytes);
    int samples = bytes / sampleSize;
    for (int i = 0; i < samples; i++) {
      int32_t s = (int32_t)(buffer[i] * gain);
      if (s > 32767) s = 32767;
      else if (s < -32768) s = -32768;
      buffer[i] = (int16_t)s;
    }
    dst.write((uint8_t *)buffer, bytes);
    remaining -= bytes;
  }
  while (int bn = src.read((uint8_t *)buffer, sizeof(buffer))) dst.write(buffer, bn);
  src.close();
  dst.close();
  mc.locked_fileing = 0 ;
  self->apply_to_file();
}

void RecorderMenuRouter::playSection(){
  PartialPlayerMono.play(self->newloopedpath,self->start_zone,self->end_zone);
  dm.returntonav(self->relative_navlevel + 1,12,mc.sublevels[self->relative_navlevel + 1]);
}

void RecorderMenuRouter::scheddule_wave_rebuild(bool noreturn,bool noreinit){
  self->end_zone = 1.0;
  self->start_zone = 0.0 ;
  self->wave_buffed = 0 ;
  if (!noreinit)
    dm.reinitsublevels(self->relative_navlevel + 1);
  if (!noreturn)
    dm.returntonav(self->relative_navlevel + 1,12,mc.sublevels[self->relative_navlevel + 1]);
  mc.locked_fileing = 0 ;
}

void RecorderMenuRouter::fadeInSection(float startPos, float endPos) {
  self->backup_current();
  self->undoables[max(self->catalog.tmp_count-1,0)] = self->catalog.tmp_index;
  if (mc.locked_fileing) return;
  FsFile src = SD.sdfs.open(self->newloopedpath, O_READ);
  if (!src) return;
  char _tmp_path[64];
  if (!self->catalog.get_new_tmp_name(_tmp_path, sizeof(_tmp_path),max(self->catalog.tmp_index,0))) return;
  FsFile dst = SD.sdfs.open(_tmp_path, O_WRITE | O_CREAT | O_TRUNC);
  mc.locked_fileing = 1 ;
  //const uint16_t sampleSize = 2;
  const uint32_t BUFFER_SAMPLES = 1024;
  int16_t buffer[BUFFER_SAMPLES];
  uint32_t fileSize = src.size();
  uint32_t startByte = (uint32_t)(fileSize * startPos);
  uint32_t endByte   = (uint32_t)(fileSize * endPos);
  startByte &= ~1;
  endByte   &= ~1;
  src.seek(0);
  while (src.position() < startByte) {
    uint32_t bytes = min((uint32_t)sizeof(buffer), startByte - src.position());
    src.read((uint8_t*)buffer, bytes);
    dst.write((uint8_t*)buffer, bytes);
  }
  uint32_t fadeSamples = (endByte - startByte) / 2;
  uint32_t sampleIndex = 0;
  while (sampleIndex < fadeSamples){
    uint32_t samples = min(BUFFER_SAMPLES, fadeSamples - sampleIndex);
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
  while (int bn = src.read((uint8_t *)buffer, sizeof(buffer))) dst.write((uint8_t*)buffer, bn);
  src.close();
  dst.close();
  mc.locked_fileing = 0 ;
  self->apply_to_file();
}

void RecorderMenuRouter::fadeOutSection(float startPos, float endPos) {
  self->backup_current();
  self->undoables[max(self->catalog.tmp_count-1,0)] = self->catalog.tmp_index;
  if (mc.locked_fileing) return;
  FsFile src = SD.sdfs.open(self->newloopedpath, O_READ);
  if (!src) return;
  char _tmp_path[64];
  if (!self->catalog.get_new_tmp_name(_tmp_path, sizeof(_tmp_path),max(self->catalog.tmp_index,0))) return;
  FsFile dst = SD.sdfs.open(_tmp_path, O_WRITE | O_CREAT | O_TRUNC);
  mc.locked_fileing = 1 ;
  const uint32_t BUFFER_SAMPLES = 1024;
  int16_t buffer[BUFFER_SAMPLES];
  uint32_t fileSize = src.size();
  uint32_t startByte = (uint32_t)(fileSize * startPos);
  uint32_t endByte   = (uint32_t)(fileSize * endPos);
  startByte &= ~1;
  endByte   &= ~1;
  src.seek(0);
  while (src.position() < startByte) {
    uint32_t bytes = min((uint32_t)sizeof(buffer), startByte - src.position());
    src.read((uint8_t*)buffer, bytes);
    dst.write((uint8_t*)buffer, bytes);
  }
  uint32_t fadeSamples = (endByte - startByte) / 2;
  uint32_t sampleIndex = 0;
  while (sampleIndex < fadeSamples) {
    uint32_t samples = min(BUFFER_SAMPLES, fadeSamples - sampleIndex);
    src.read((uint8_t*)buffer, samples * 2);
    for (uint32_t i = 0; i < samples; i++) {
      float x = (float)(sampleIndex + i) / (fadeSamples - 1);
      float gain = cosf(x * (PI/2));
      int32_t s = (int32_t)(buffer[i] * gain);
      buffer[i] = (int16_t)s;
    }
    dst.write((uint8_t*)buffer, samples * 2);
    sampleIndex += samples;
  }
  while (int bn = src.read((uint8_t *)buffer, sizeof(buffer))) dst.write((uint8_t*)buffer, bn);
  src.close();
  dst.close();
  mc.locked_fileing = 0 ;
  self->apply_to_file();
}

void RecorderMenuRouter::start_inputting_pitch(){
  mc.navrange = 127 ;
  dm.setCursor(104,12);
  dm.fillRect(104, 12, 30, 10, SSD1306_BLACK);
  self->pitcher = (mc.sublevels[self->relative_navlevel + 2]/127.0) * 2.0;
  dm.print(self->pitcher);
  dm.dodisplay();
  if (mc.navlevel >= self->relative_navlevel+3) {
    pitchSection(self->start_zone,self->end_zone,self->pitcher);
    scheddule_wave_rebuild();
    dm.returntonav(self->relative_navlevel + 1,12,mc.sublevels[self->relative_navlevel + 1]);

  }
}

void RecorderMenuRouter::deleteSection(float startPos, float endPos){
  self->backup_current();
  self->undoables[max(self->catalog.tmp_count-1,0)] = self->catalog.tmp_index;
  if (mc.locked_fileing) return;
  FsFile src = SD.sdfs.open(self->newloopedpath, O_READ);
  if (!src) return;
  char _tmp_path[64];
  if (!self->catalog.get_new_tmp_name(_tmp_path, sizeof(_tmp_path),max(self->catalog.tmp_index,0))) return;
  FsFile dst = SD.sdfs.open(_tmp_path, O_WRITE | O_CREAT | O_TRUNC);
  mc.locked_fileing = 1 ;
  const uint32_t BUFFER_SIZE = 2048;
  uint8_t buffer[BUFFER_SIZE];
  uint32_t fileSize = src.size();
  if (startPos < 0.0f) startPos = 0.0f;
  if (startPos > 1.0f) startPos = 1.0f;
  if (endPos < 0.0f) endPos = 0.0f;
  if (endPos > 1.0f) endPos = 1.0f;
  if (startPos > endPos) {
    float t = startPos;
    startPos = endPos;
    endPos = t;
  }
  uint32_t startByte = (uint32_t)(fileSize * startPos);
  uint32_t endByte   = (uint32_t)(fileSize * endPos);
  startByte &= ~1;
  endByte   &= ~1;
  src.seek(0);
  uint32_t remaining = startByte;
  while (remaining) {
    uint32_t chunk = (remaining > BUFFER_SIZE) ? BUFFER_SIZE : remaining;
    src.read(buffer, chunk);
    dst.write(buffer, chunk);
    remaining -= chunk;
  }
  src.seek(endByte);
  while (int bn = src.read(buffer, BUFFER_SIZE)) dst.write(buffer, bn);
  src.close();
  dst.close();
  mc.locked_fileing = 0 ;
  self->apply_to_file();
}

void RecorderMenuRouter::edit_record(){
          self->catalog.make_temp_folders();
          mc.navrange = 13 ;
           if (mc.navlevel == self->relative_navlevel+1) {
            if (!self->wave_buffed) {
              draw_editor_zones();
              self->wave_buffed = 1 ;
              drawWaveform(self->start_zone,self->end_zone);
              dm.dodisplay();
            }
            select_cursor();
           }
          if (mc.navlevel == self->relative_navlevel + 2) {
            if (mc.sublevels[self->relative_navlevel + 1] == 1){
              scheddule_wave_rebuild();
            }

            //zoom in
            if (mc.sublevels[self->relative_navlevel + 1] == 2){
              zoomRange((mc.sublevels[self->relative_navlevel + 2] / 127.0 ),((mc.sublevels[self->relative_navlevel + 2] + mc.sublevels[self->relative_navlevel + 3] ) / 127.0 ));
              self->wave_buffed = 0 ;
              dm.reinitsublevels(self->relative_navlevel + 2);
              dm.returntonav(self->relative_navlevel + 1,12,mc.sublevels[self->relative_navlevel + 1]);
            }

            //select
            if (mc.sublevels[self->relative_navlevel + 1] == 0){
              self->wave_selected = 0;
              mc.navrange = 127 ;
              dm.clearDisplay();
              dm.drawFastVLine(mc.sublevels[self->relative_navlevel +2], 8, 48, SSD1306_INVERSE);
              dm.dodisplay();
            }

            //normalize
            if (mc.sublevels[self->relative_navlevel + 1] == 3){
              normalizeSection(self->start_zone,self->end_zone);
              scheddule_wave_rebuild();
            }

            //reverse
            if (mc.sublevels[self->relative_navlevel + 1] == 4){
              reverseSection(self->start_zone,self->end_zone);
              scheddule_wave_rebuild();
            }
            //pitching
            if (mc.sublevels[self->relative_navlevel + 1] == 5){
              start_inputting_pitch();
            }

            //trim in
            if (mc.sublevels[self->relative_navlevel + 1] == 9){
              trimSection(self->start_zone,1.0);
              scheddule_wave_rebuild();
            }
            //trim out
            if (mc.sublevels[self->relative_navlevel + 1] == 10){
              trimSection(0.0,self->end_zone);
              scheddule_wave_rebuild();
            }
            //del selected
            if (mc.sublevels[self->relative_navlevel + 1] == 11){
              deleteSection(self->start_zone,self->end_zone);
              scheddule_wave_rebuild();
            }
            //keep selected
            if (mc.sublevels[self->relative_navlevel + 1] == 12){
              trimSection(self->start_zone,self->end_zone);
              scheddule_wave_rebuild();
            }
            //save selected
            if (mc.sublevels[self->relative_navlevel + 1] == 13){
              Undo();
              scheddule_wave_rebuild();
            }
            //fadein
            if (mc.sublevels[self->relative_navlevel + 1] == 6){
              fadeInSection(self->start_zone,self->end_zone);
              scheddule_wave_rebuild();
            }
            //fadeout
            if (mc.sublevels[self->relative_navlevel + 1] == 7){
              fadeOutSection(self->start_zone,self->end_zone);
              scheddule_wave_rebuild();
            }

            //playSection
            if (mc.sublevels[self->relative_navlevel + 1] == 8){
              playSection();
              dm.returntonav(self->relative_navlevel + 1,12,mc.sublevels[self->relative_navlevel + 1]);
            }

          }
          //select end
          if (mc.navlevel == self->relative_navlevel + 3) {
            if (mc.sublevels[self->relative_navlevel + 1] == 0){
              mc.navrange = 127 - mc.sublevels[self->relative_navlevel +2] ;
              dm.clearDisplay();
              dm.dodisplay();
              dm.fillRect(mc.sublevels[self->relative_navlevel +2], 8,
                                mc.sublevels[self->relative_navlevel +3],48, SSD1306_INVERSE);
              dm.display();
            //dm.returntonav(self->relative_navlevel + 1, self->home_navrange,0);
            }

          //5 is pitch
            if (mc.sublevels[self->relative_navlevel + 1] == 5){
              start_inputting_pitch();
            }
          }
          if (mc.navlevel > self->relative_navlevel +3 ) {
              dm.returntonav(self->relative_navlevel + 1,12,mc.sublevels[self->relative_navlevel + 1]);
              self->wave_selected = 1;
              }
        }

void RecorderMenuRouter::redo(){

}

void RecorderMenuRouter::Undo(){

  self->catalog.tmp_index = self->undoables[max(self->catalog.tmp_count-1,0)];
  Serial.println();
  Serial.print(" using undoable from index ");
  Serial.print(max(self->catalog.tmp_count-1,0));  
  Serial.print(" currently: ");
  Serial.print(self->catalog.tmp_index);


  char current_tmp_path[64];
  if (!self->catalog.get_full_tmp_file_path(current_tmp_path, sizeof(current_tmp_path),max(self->catalog.tmp_index,0))) return;
  if (SD.sdfs.exists(current_tmp_path)){
      Serial.print(" thus using ( and decrementing tmp_count ) ");
    Serial.print(current_tmp_path);
    self->catalog.tmp_count--;
    self->catalog.move_file(current_tmp_path, self->newloopedpath);
  } else {
    Serial.println(" no bkp yet");
  }
  scheddule_wave_rebuild();
}

void RecorderMenuRouter::clear_temp_files(){
  if (SD.sdfs.exists(self->catalog.tmp_folder)) {
    FsFile opened_dir = SD.sdfs.open((const char*)self->catalog.tmp_folder);
    while (true) {
      FsFile entry = opened_dir.openNextFile();
      if (!entry) break;
      if (entry.isDirectory()) continue;
      char name[32];
      entry.getName(name, sizeof(name));
      char fullpath[96];
      snprintf(fullpath, sizeof(fullpath), "%s%s", self->catalog.tmp_folder, name);
      entry.close();
      if (SD.sdfs.exists(fullpath)) SD.sdfs.remove(fullpath);
      //this does not work unfortunately
      //entry.remove()
    }
  }
  self->catalog.tmp_index = 0;
  self->catalog.tmp_count = 0;
}
