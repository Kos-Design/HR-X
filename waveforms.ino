
byte wforms_indexes[99];
byte wforms_count = 0 ;
const byte wfn_size = 6;
String wforms_names[wfn_size];
byte wforms_names_offset = 0 ;

String get_wform_name(byte number) {
  char formatted_number[4] ;
  sprintf(formatted_number,"%02d",number);
  return "WFORM-" + (String)formatted_number ;
} 

String get_current_waveform_path(){
  return "WAVEFORM/" + wforms_names[0] + ".TXT";
}

void refresh_wforms_names() {
  for (int i = 0 ; i < wfn_size ; i++) {
    //empty spots are left at the end of the list if it is small, otherwise the names are looped
    wforms_names[i] = " ";
    if (wforms_names_offset+i < wforms_count ) {
      wforms_names[i] = get_wform_name(wforms_indexes[wforms_names_offset+i]);
    } else if (wforms_count >= wfn_size ){ 
      wforms_names[i] = get_wform_name(wforms_indexes[((wforms_names_offset+i)%wforms_count) ]); 
    } 
  }
}
          
void list_wforms_files() {
  wforms_count = 0;
  String wforms_dir = "WAVEFORM/";
  if (SD.exists(wforms_dir.c_str())) {
    File wform_filer = SD.open(wforms_dir.c_str());
    while (wforms_count < 99) {
      File entry = wform_filer.openNextFile();
      if (!entry) {
        break;
      }
      if (!entry.isDirectory()) {
        char* named = (char*)entry.name();
        named[strlen(named) - 4] = '\0';
        //int is at 6 chars after prefix
        wforms_indexes[wforms_count] = atoi(named+6);
        wforms_count++;
      }
      entry.close();
    }
    wform_filer.close();
  }
  //refresh_wforms_names();
}

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
      navrange = wforms_count;
    } else {
      navrange = max(wforms_count - 1, 0);
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

void WaveformEditer() {
  int cw_change = 0;
  int vc_change;
  int w_cursor_y = 32;
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
  for (int i = 0; i < truesizeofwaveformsmenulabels - 1 - (sublevels[1]); i++) {
    canvasBIG.setCursor(startx, starty + ((i)*10));
    canvasBIG.println(waveformsmenulabels[sublevels[1] + 1 + i]);
  }
  for (int i = 0; i < sublevels[1]; i++) {
    canvasBIG.setCursor(startx, (10 * (truesizeofwaveformsmenulabels - sublevels[1]) + 6 + ((i)*10)));
    canvasBIG.println(waveformsmenulabels[i]);
  }
}

void writewaveform() {
  File waveform_file ;
  if (sublevels[2] == wforms_count) {
    waveform_file = SD.open(get_new_file_name("WAVEFORM/WFORM-").c_str(), FILE_WRITE);
  } else {
    String selected_waveform = get_current_waveform_path();
    if (SD.exists(selected_waveform.c_str())) {
      SD.remove(selected_waveform.c_str());
    }
    waveform_file = SD.open(selected_waveform.c_str(), FILE_WRITE);
  }
  if (waveform_file) {
    Serial.print("Writing to ");
    Serial.println(waveform_file.name());
    writewaveforms(waveform_file);
    waveform_file.close();
  }
  waveform_file.close();
  list_wforms_files();
}

void dolistofwaveforms() {
  //check navrange
  int startx = 80;
  int starty = 16;
  wforms_names_offset = sublevels[2] ;
  refresh_wforms_names();
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(startx, 0);
  canvastitle.setTextSize(1);
  if (sublevels[2] == wforms_count && sublevels[1] == 0) {
    canvastitle.print("New()");
  } else {
    canvastitle.print(wforms_names[0]);
  }
  canvastitle.setTextSize(1);
  canvasBIG.setTextSize(1);
  canvasBIG.fillScreen(SSD1306_BLACK);
    
  if (sublevels[2] == wforms_count) {
    //if cursor is on new(), the wfn_size-1 elements are displayed below.
    for (int i = 0; i < wfn_size-1; i++) {
      canvasBIG.setCursor(startx, (10 * (wforms_count - sublevels[2])) + 16 + ((i)*10));
      canvasBIG.println(wforms_names[i]);
    }
  } else {
    //rest of indexes after title (refresh_wforms_names handles list population)
    for (int i = 0; i < wfn_size - 1 ; i++) {
      canvasBIG.setCursor(startx, starty + i*10);
      canvasBIG.println(wforms_names[1 + i]);
    }
  }
}

void setwaveformsnavrange() {
  if (wforms_count < 2) {
    navrange = 2;
    // Serial.println("SOMETHING IS WRONG");
  } else {
    navrange = max(wforms_count - 1, 0);
  }
}

void writewaveforms(File &filer) {
  size_t writtenBytes = filer.write((byte *)arbitrary_waveforms[waveformIndex], sizeof(arbitrary_waveforms[waveformIndex]));
  if (writtenBytes != sizeof(arbitrary_waveforms[waveformIndex])) {
    Serial.println("Error while writing waveform data to file");
  } else {
    Serial.println("Waveform data written to file.");
  }
}

void readwaveform() { parsewaveformfile(sublevels[2]); }

void copywaveform() {
  File origin_file;
  File target_file;
  String waveform_path = get_current_waveform_path() ;
  if (SD.exists(waveform_path.c_str())) {
    target_file = SD.open(get_new_file_name("WAVEFORM/WFORM-").c_str(), FILE_WRITE);
    origin_file = SD.open(waveform_path.c_str(), FILE_READ);
    size_t n_size;
    uint8_t buf[64];
    while ((n_size = origin_file.read(buf, sizeof(buf))) > 0) {
      target_file.write(buf, n_size);
    }
  }

  origin_file.close();
  target_file.close();
  list_wforms_files();
}

void deletewaveform() {
  if (SD.exists(get_current_waveform_path().c_str())) {
    SD.remove(get_current_waveform_path().c_str());
  }
  list_wforms_files();
}

void parsewaveformfile(int presetn) {
  File target_waveform = SD.open(get_current_waveform_path().c_str(), FILE_READ);
  size_t readBytes = target_waveform.read((byte *)arbitrary_waveforms[waveformIndex], sizeof(arbitrary_waveforms[waveformIndex]));
  if (readBytes != sizeof(arbitrary_waveforms[waveformIndex])) {
    Serial.println("Failed to read complete waveform data");
  } else {
    Serial.println("Waveform data read from file:");
    for (int i = 0; i < 256; i++) {
      Serial.println(arbitrary_waveforms[waveformIndex][i]);
    }
  }
  target_waveform.close();
}
