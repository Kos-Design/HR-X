#include "WaveFormer.h"
#include "Presets.h"

WaveformsMenuRouter* WaveformsMenuRouter::self = nullptr;

WaveformsMenuRouter::WaveformsMenuRouter() {
  self = this;
  self->home_navrange=self->wf_labels_count-1;
  self->catalog = new FilesLister("WAVEFORM/","WFORM-",".TXT",wforms_menu,self->home_navrange);
  self->relative_navlevel=1;
  self->max_navlevel=5;
  self->sublevels_address={8,0,0};
}

void WaveformsMenuRouter::show() {
  _route_nav[lv.navlevel-1]();
}
        
void WaveformsMenuRouter::waveforms_nav_zero(){
  lv.waveforming = 0 ;
  self->catalog->nav_zero();
}

void WaveformsMenuRouter::set_tracer(byte control,byte value){
  if (control == self->trace_wave_cc) {
    self->trace_waveform = !self->trace_waveform;
  }
  if (self->trace_waveform){
    if (control == self->y_axis_cc ) {
      set_y_cursor_value(value);
    }
    if (control == self->x_axis_cc ) {
      set_x_cursor_value(value);
    }
  }
}

void WaveformsMenuRouter::WaveformParams(){
          
  lv.navrange = 2 ;
  if (lv.navlevel == 3 ){
    lv.navrange = 127;
    *self->waveform_tracers[lv.sublevels[2]]=lv.sublevels[3];
  }
  
  lv.sublevels[3]=*self->waveform_tracers[lv.sublevels[2]];
  dm.clearDisplay();
  dm.setCursor(0,0);
  dm.setTextSize(1);
  //println adds new line each iteration!!!
  dm.print("Params");
  dm.println(" ");
  dm.println(" ");
  dm.print("X-Axis CC: ");
  //17
  dm.print(self->x_axis_cc);
  dm.println(" ");
  dm.println(" ");
  dm.print("Y-Axis CC: ");
  dm.print(self->y_axis_cc);
  //18
  dm.println(" ");
  dm.println(" ");
  dm.print("Tracenote: ");
  dm.print(self->trace_wave_cc);
  //note 58
  dm.drawRoundRect(62,11+16*lv.sublevels[2], 25, 16, 3, SSD1306_WHITE);
  //dm.drawRoundRect(62,11+16, 25, 16, 3, SSD1306_WHITE);
  //dm.drawRoundRect(62,11+16 +16, 25, 16, 3, SSD1306_WHITE);
  dm.display();
  
  if (lv.navlevel > 3 ){
    dm.returntonav(2,2,lv.sublevels[2]);
  }
}

void WaveformsMenuRouter::set_y_cursor_value(byte la_val){
  if (la_val > 0) {
    self->cw_change = la_val;
    self->w_cursor_y = 64 - map(self->cw_change, 0, 127, 0, 64);
  }
}

void WaveformsMenuRouter::blur_w_graph_region(int16_t *arr, int index, uint8_t intensity) {
    int range = (intensity / 255.0)*self->max_blur;
    int temp[2 * self->max_blur + 1];
    if (range > self->max_blur)
        range = self->max_blur;
    for (int d = -range; d <= range; d++){
        int pos = index + d;
        if ((unsigned)pos >= 256)
            continue;
        int64_t sum = 0;
        uint32_t wsum = 0;
        for (int k = -range; k <= range; k++){
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
    for (int d = -range; d <= range; d++)
    {
        int pos = index + d;
        if ((unsigned)pos >= 256)
            continue;
        int blurred = temp[d + range];
        arr[pos] += ((blurred - arr[pos]) * intensity) >> 8;
    }
}

void WaveformsMenuRouter::blur_w_graph_boundary( int16_t *arr,int range) {
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

void WaveformsMenuRouter::smooth_w_bounds(){
  blur_w_graph_boundary(gg.arbitrary_waveforms[self->widx], 32);
}

void WaveformsMenuRouter::smooth_w_graph(){
  blur_w_graph_region(gg.arbitrary_waveforms[self->widx], self->w_cursor_x, 64);
}

void WaveformsMenuRouter::set_array_at_cursor(int c_pos_w){
  int w_graph_y = map(self->cw_change, 0, 127, -32768, 32767);
  gg.arbitrary_waveforms[self->widx][c_pos_w] = w_graph_y;
  gg.arbitrary_waveforms[self->widx][(c_pos_w-1)%256] = w_graph_y;
}

void WaveformsMenuRouter::set_x_cursor_value(byte la_val){
  if (la_val > 0) {
    self->w_cursor_x = map(la_val, 0, 127, 0, 255);
    //gg.arbitrary_waveforms[self->widx][self->w_cursor_x] = map(self->cw_change, 0, 127, -32768, 32767);
    lv.sublevels[2]=self->w_cursor_x;
    lv.rota_true_pos = self->w_cursor_x;
    dm.myEnc.write(lv.rota_true_pos * 4);
    set_array_at_cursor();
  }
}

void WaveformsMenuRouter::draw_wave_graph(){
  int16_t y1;
  int16_t y2;
  for (int i = 0; i < 128; i++) {
    if ((i * 2) + 2 < 256) {
      y1 = map(gg.arbitrary_waveforms[self->widx][i * 2], -32768, 32767, 63, 0);
      y2 = map(gg.arbitrary_waveforms[self->widx][(i * 2) + 2], -32768, 32767, 63, 0);
      dm.canvasBIG.drawLine(i, y1, i + 1, y2, SSD1306_WHITE);
    }
  }
}

void WaveformsMenuRouter::WaveformEditer() {
  lv.waveforming = 1;
  lv.navrange = 255;
  dm.clean_title_1();
  
  if (lv.navlevel > 3) {
    self->trace_waveform = 0 ;
    
    smooth_w_graph();
    dm.returntonav(2,255,lv.sublevels[2]);
  }
  if (lv.navlevel == 3) {
    self->trace_waveform = 1 ;
    self->cw_change = map(lv.sublevels[3],0,255,0,127);
    set_array_at_cursor();
  }
  if (self->trace_waveform) {
    set_array_at_cursor();
    self->w_cursor_y = map(gg.arbitrary_waveforms[self->widx][self->w_cursor_x], -32768, 32767, 63, 0);
  }
  if (lv.navlevel == 2) {
    self->w_cursor_x=lv.sublevels[2];
    self->w_cursor_y = map(gg.arbitrary_waveforms[self->widx][self->w_cursor_x], -32768, 32767, 63, 0);
    lv.sublevels[3] = map(gg.arbitrary_waveforms[self->widx][self->w_cursor_x],-32768, 32767, 0, 255 ) ;
  }
  dm.canvasBIG.drawCircle(lv.sublevels[2]/2, self->w_cursor_y, 2, SSD1306_WHITE);
  draw_wave_graph();
  //dm.canvastitle.print(gg.arbitrary_waveforms[self->widx][lv.sublevels[2]]);
  dm.dodisplay();
  //smooth_w_bounds();
}

void WaveformsMenuRouter::wforms_menu() {
  const char* waveformsmenulabels[] = {
      "Save", "Load", "Copy", "Delete", "Edit", "-->", "<--","Params"};
  dm.main_panel(waveformsmenulabels, 1, wf_labels_count);
}

void WaveformsMenuRouter::go_previous(){
  if (self->widx-1 < 0)
    self->widx = 2 ;
  else
    self->widx = self->widx-1;

  dm.returntonav(1,wf_labels_count-1,lv.sublevels[1]);
}

void WaveformsMenuRouter::go_next(){
  self->widx = (self->widx+1)%3;
  dm.returntonav(1,wf_labels_count-1,lv.sublevels[1]);
}

void WaveformsMenuRouter::writewaveform() {
  if (lv.locked_fileing)
    return;
  lv.locked_fileing = 1 ;
  FsFile waveform_file ;
  if (self->catalog->new_file_mode) {
    waveform_file = SD.sdfs.open(self->catalog->get_new_file_name().c_str(), O_WRITE | O_CREAT | O_TRUNC);
  } else {
    const char* overwritee = self->catalog->get_current_file_path(0).c_str();
    self->catalog->deleteFile();
    waveform_file = SD.sdfs.open(overwritee, O_WRITE | O_CREAT | O_TRUNC);
  }
  if (waveform_file) {
    waveform_file.write((byte *)gg.arbitrary_waveforms, sizeof(gg.arbitrary_waveforms));
    waveform_file.close();
  }
  waveform_file.close();
  self->catalog->list_files();
  lv.locked_fileing = 0 ;
}

void WaveformsMenuRouter::copywaveform() {
  self->catalog->copyFile();
}

void WaveformsMenuRouter::deletewaveform() {
  self->catalog->deleteFile();
}

void WaveformsMenuRouter::parsewaveformfile() {
  if (lv.locked_fileing)
    return;
  lv.locked_fileing = 1 ;
  FsFile target_waveform = SD.sdfs.open(self->catalog->get_current_file_path(0).c_str(), O_READ);
  target_waveform.read((byte *)gg.arbitrary_waveforms, sizeof(gg.arbitrary_waveforms));
  target_waveform.close();
  lv.locked_fileing = 0 ;
}
        
void WaveformsMenuRouter::wforms_actions(){
  _nav_wforms[lv.sublevels[1]]();  
}

void WaveformsMenuRouter::remove_wform(){
  lv1_wrapper(self->deletewaveform);
}

void WaveformsMenuRouter::duplicate_wform(){
  lv1_wrapper(self->copywaveform);
}

void WaveformsMenuRouter::load_wform(){
  lv1_wrapper(self->parsewaveformfile);
}

void WaveformsMenuRouter::save_wform(){
  lv1_wrapper(self->writewaveform);         
} 

void WaveformsMenuRouter::lv1_wrapper(void (*func)()) {
  self->catalog->nav_one(0,1);
  if (lv.navlevel >= 3) {
    func();
    dm.returntonav(1, self->wf_labels_count - 1,lv.sublevels[1]);
  }
}



