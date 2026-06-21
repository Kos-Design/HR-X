
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
dm.clear_buffs();
  if (navlevel >= 2 && sublevels[1] == 7) {
    WaveformParams();
    return;
  }
  WaveformsmenuBG();
  if (navlevel <= 1) {
    navrange = truesizeofwaveformsmenulabels-1;
    dolistwaveformsmenu();
  } else if (navlevel > 1 && sublevels[1] != 4) {
    dolistwaveformsmenu();
  }
  dodisplay();
  
}


void WaveformParams(){
  
  navrange = 2 ;
  if (navlevel == 3 ){
    navrange = 127;
    Serial.println("sel");
    *valz[sublevels[2]]=sublevels[3];
  }
  
  sublevels[3]=*valz[sublevels[2]];
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  //println adds new line each iteration!!!
  display.print("Params");
  display.println(" ");
  display.println(" ");
  display.print("X-Axis CC: ");
  //17
  display.print(x_axis_cc);
  display.println(" ");
  display.println(" ");
  display.print("Y-Axis CC: ");
  display.print(y_axis_cc);
  //18
  display.println(" ");
  display.println(" ");
  display.print("Tracenote: ");
  display.print(trace_wave_cc);
  //note 58
  display.drawRoundRect(62,11+16*sublevels[2], 25, 16, 3, SSD1306_WHITE);
  //display.drawRoundRect(62,11+16, 25, 16, 3, SSD1306_WHITE);
  //display.drawRoundRect(62,11+16 +16, 25, 16, 3, SSD1306_WHITE);
  display.display();
  
  if (navlevel > 3 ){
    returntonav(2,2,sublevels[2]);
  }
}

void WaveformsmenuBG() {
  display.clearDisplay();
  if (navlevel == 1 && sublevels[1] != 4) {
    reinitsublevels(2);
    navrange = truesizeofwaveformsmenulabels-1;
    dolistofwaveforms();
  }
  if (navlevel >= 2 && sublevels[1] == 4) {
    WaveformEditer();
  }
  
  if (navlevel > 1 && sublevels[1] < 4 )  {
    if (sublevels[1] == 0) {
      navrange = wforms_count;
    } else {
      navrange = max(wforms_count - 1, 0);
    }
    dolistofwaveforms();
  }
  dodisplay();
  
  if (navlevel >= 2 && sublevels[1] > 4 && sublevels[1] != 7) {
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
  if (navlevel >= 3 && sublevels[1] != 7) {
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
        smooth_w_bounds();
        break;
      case 5:
      //placeholder next
        break;
      case 6:
      //placeholder prev
        break;
      /* filtered in switch condition already
      case 7:
      //params
        break;
        */
      default:
        break;
    }
    //if (sublevels[1] != 4){
      returntonav(1,6);
    //}
    displaywaveformsmenu();
  }
}

void set_y_cursor_value(byte la_val){
  if (la_val > 0) {
    cw_change = la_val;
    w_cursor_y = 64 - map(cw_change, 0, 127, 0, 64);
  }
}

void blur_w_graph_region(int16_t *arr, int index, uint8_t intensity) {
    int range = (intensity / 255.0)*BLUR_W_MAX_RANGE;
    int temp[2 * BLUR_W_MAX_RANGE + 1];

    if (range > BLUR_W_MAX_RANGE)
        range = BLUR_W_MAX_RANGE;

    // Calculate blurred values
    for (int d = -range; d <= range; d++)
    {
        int pos = index + d;

        if ((unsigned)pos >= 256)
            continue;

        int64_t sum = 0;
        uint32_t wsum = 0;

        for (int k = -range; k <= range; k++)
        {
            int src = pos + k;

            if ((unsigned)src >= 256)
                continue;

            int ak = k < 0 ? -k : k;
            int ki = (ak * 16) / range;

            uint32_t w = fake_gauss_kernel[16 - ki];

            sum += (int64_t)arr[src] * w;
            wsum += w;
        }

        temp[d + range] = (int)(sum / wsum);
    }

    // Blend back according to intensity
    for (int d = -range; d <= range; d++)
    {
        int pos = index + d;

        if ((unsigned)pos >= 256)
            continue;

        int blurred = temp[d + range];

        arr[pos] +=
            ((blurred - arr[pos]) * intensity) >> 8;
    }
}

void blur_w_graph_boundary( int16_t *arr,int range) {
  for (int i = 1; i < range; i++)  {
      // 255 at edge, 0 at end of range
      int pull = ((range - i) * 255) / range;

      arr[i] -= (arr[i] * pull) >> 8;

      int j = 255 - i;
      arr[j] -= (arr[j] * pull) >> 8;
  }
  arr[0]   = 0;
  arr[255] = 0;
}

void smooth_w_bounds(){
  blur_w_graph_boundary(arbitrary_waveforms[waveformIndex], 32);
}

void smooth_w_graph(){
  blur_w_graph_region(arbitrary_waveforms[waveformIndex], w_cursor_x, 64);
}

void set_array_at_cursor(int c_pos_w=w_cursor_x){
  int w_graph_y = map(cw_change, 0, 127, -32768, 32767);
  arbitrary_waveforms[waveformIndex][c_pos_w] = w_graph_y;
  arbitrary_waveforms[waveformIndex][(c_pos_w-1)%256] = w_graph_y;
  smooth_w_graph();
}

void set_x_cursor_value(byte la_val){
  if (la_val > 0) {
    w_cursor_x = map(la_val, 0, 127, 0, 255);
  //arbitrary_waveforms[waveformIndex][w_cursor_x] = map(cw_change, 0, 127, -32768, 32767);
  sublevels[2]=w_cursor_x;
  vraipos = w_cursor_x;
  myEnc.write(vraipos * 4);
  set_array_at_cursor();

 }
}

void draw_wave_graph(){
  int16_t y1;
  int16_t y2;
  for (int i = 0; i < 128; i++) {
    if ((i * 2) + 2 < 256) {
      y1 = map(arbitrary_waveforms[waveformIndex][i * 2], -32768, 32767, 63, 0);
      y2 = map(arbitrary_waveforms[waveformIndex][(i * 2) + 2], -32768, 32767, 63, 0);
      canvasBIG.drawLine(i, y1, i + 1, y2, SSD1306_WHITE);
    }
  }
}

void WaveformEditer() {
  navrange = 255;
  canvastitle.fillScreen(SSD1306_BLACK);
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  if (trace_waveform && navlevel >= 2) {
    w_cursor_x=sublevels[2];
    set_array_at_cursor();
  }
  canvasBIG.drawCircle(sublevels[2]/2, w_cursor_y, 2, SSD1306_WHITE);
  draw_wave_graph();
  //canvastitle.print(arbitrary_waveforms[waveformIndex][sublevels[2]]);
}

void dolistwaveformsmenu() {
  char waveformsmenulabels[truesizeofwaveformsmenulabels][12] = {
      "Save", "Load", "Copy", "Delete", "Edit", "-->", "<--","Params"};
  byte startx = 5;
  byte starty = 16;
  char *textin = (char *)waveformsmenulabels[sublevels[1]];
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
  } else {
    navrange = max(wforms_count - 1, 0);
  }
}

void writewaveforms(File &filer) {
  filer.write((byte *)arbitrary_waveforms[waveformIndex], sizeof(arbitrary_waveforms[waveformIndex]));
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
  target_waveform.read((byte *)arbitrary_waveforms[waveformIndex], sizeof(arbitrary_waveforms[waveformIndex]));
  target_waveform.close();
}
