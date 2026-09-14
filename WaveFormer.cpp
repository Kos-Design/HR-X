#include "SerialFlash.h"
#include <stdint.h>
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
  _route_nav[mc.navlevel-1]();
}

void WaveformsMenuRouter::waveforms_nav_zero(){
  mc.waveforming = 0 ;
  self->catalog->nav_zero();
}

void WaveformsMenuRouter::set_tracer(byte control,byte value){
  if (control == gg.waveform_tracers.trace) {

    self->trace_waveform = !self->trace_waveform;
      Serial.println(self->trace_waveform );

  }
  if (self->trace_waveform){
    if (control == gg.waveform_tracers.y_poser ) {
      Serial.println("ysett");
      set_y_cursor_value(value);
    }
    if (control == gg.waveform_tracers.x_poser ) {
      Serial.println("xsett");
      set_x_cursor_value(value);
    }
  }
}

void WaveformsMenuRouter::WaveformParams(){
  dm.clean_title_1_1();
  mc.navrange = 3 ;
  uint8_t* wf_helper = reinterpret_cast<uint8_t*>(&gg.waveform_tracers);
  if (mc.navlevel == 3 ){
    mc.navrange = 127;
    wf_helper[mc.sublevels[2]]=(uint8_t)mc.sublevels[3];
  }
  
  mc.sublevels[3]=wf_helper[mc.sublevels[2]];
 
  if (mc.navlevel > 3 ){
    dm.returntonav(2,3,mc.sublevels[2]);
  }
  //uint8_t wtt[4];
  //memcpy(wtt, &gg.waveform_tracers, sizeof(wtt));
  const char* _lbls[4] = {"X-Axis CC ","Y-Axis CC ","Tracenote ","Blur Radius "};
  dm.sub_menu(_lbls,wf_helper,79);

}

void WaveformsMenuRouter::set_y_cursor_value(byte la_val){
  if (la_val > 0) {
    self->cw_change = la_val;
    self->w_cursor_y = 64 - map(self->cw_change, 0, 127, 0, 64);
  }
}

void WaveformsMenuRouter::blur_w_graph_region(int16_t *arr, int index, uint8_t intensity) {
    int range = (intensity / 127.0)*self->max_blur;
    int temp[2 * self->max_blur + 1];
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
  blur_w_graph_boundary(gg.arbitrary_waveforms[self->widx], gg.waveform_tracers.blur_radius/2);
}

void WaveformsMenuRouter::smooth_w_graph(){
  blur_w_graph_region(gg.arbitrary_waveforms[self->widx], self->w_cursor_x, gg.waveform_tracers.blur_radius);
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
    mc.sublevels[2]=self->w_cursor_x;
    mc.rota_true_pos = self->w_cursor_x;
    dm.myEnc.write(mc.rota_true_pos * 4);
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
  mc.navrange = 255;
  dm.clean_title_1();
  mc.waveforming = 0;

  if (mc.navlevel > 3) {
    self->trace_waveform = 0 ;
    mc.waveforming = 0;
    smooth_w_graph();
    smooth_w_bounds();
    dm.returntonav(2,255,mc.sublevels[2]);
  }
  if (mc.navlevel == 3) {
    mc.waveforming = 1;
    if (self->trace_waveform) {
      set_array_at_cursor();
      self->w_cursor_y = map(gg.arbitrary_waveforms[self->widx][self->w_cursor_x], -32768, 32767, 63, 0);
    } else {
      self->cw_change = map(mc.sublevels[3],0,255,0,127);
      set_array_at_cursor();
    }
  }
  if (mc.navlevel == 2) {
    self->trace_waveform = 0 ;
    self->w_cursor_x=mc.sublevels[2];
    self->w_cursor_y = map(gg.arbitrary_waveforms[self->widx][self->w_cursor_x], -32768, 32767, 63, 0);
    mc.sublevels[3] = map(gg.arbitrary_waveforms[self->widx][self->w_cursor_x],-32768, 32767, 0, 255 ) ;
  }
  dm.canvasBIG.drawCircle(mc.sublevels[2]/2, self->w_cursor_y, 2, SSD1306_WHITE);
  draw_wave_graph();
  dm.dodisplay();
  
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

  dm.returntonav(1,wf_labels_count-1,mc.sublevels[1]);
}

void WaveformsMenuRouter::go_next(){
  self->widx = (self->widx+1)%3;
  dm.returntonav(1,wf_labels_count-1,mc.sublevels[1]);
}

void WaveformsMenuRouter::writewaveform() {
  if (mc.locked_fileing)
    return;
  mc.locked_fileing = 1 ;
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
  mc.locked_fileing = 0 ;
}

void WaveformsMenuRouter::copywaveform() {
  self->catalog->copyFile();
}

void WaveformsMenuRouter::deletewaveform() {
  self->catalog->deleteFile();
}

void WaveformsMenuRouter::parsewaveformfile() {
  if (mc.locked_fileing)
    return;
  mc.locked_fileing = 1 ;
  FsFile target_waveform = SD.sdfs.open(self->catalog->get_current_file_path(0).c_str(), O_READ);
  target_waveform.read((byte *)gg.arbitrary_waveforms, sizeof(gg.arbitrary_waveforms));
  target_waveform.close();
  mc.locked_fileing = 0 ;
}

void WaveformsMenuRouter::wforms_actions(){
  _nav_wforms[mc.sublevels[1]]();
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
  if (mc.navlevel >= 3) {
    func();
    dm.returntonav(1, self->wf_labels_count - 1,mc.sublevels[1]);
  }
}



