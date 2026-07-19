
class WaveformsMenuRouter : public SectionHolder {
    public:
       
        WaveformsMenuRouter() {
          self = this;
          self->home_navrange=self->wf_labels_count-1;
          self->catalog = new FilesLister("WAVEFORM/","WFORM-",".TXT",wforms_menu,self->home_navrange);
          self->relative_navlevel=1;
          self->max_navlevel=5;
          self->sublevels_address={8,0,0};
        }

        FilesLister *catalog;
        static const byte wf_labels_count = 8;
        static const byte wfn_size = 6; //displayables lines
        String wforms_names[wfn_size];
        byte wforms_indexes[99];
        byte wforms_count = 0 ;
        byte wforms_names_offset = 0 ;

        static void show() {
          _route_nav[navlevel-1]();
        }
        
        static void waveforms_nav_zero(){
          self->catalog->nav_zero();
        }

        static void WaveformParams(){
          
          navrange = 2 ;
          if (navlevel == 3 ){
            navrange = 127;
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

        void set_y_cursor_value(byte la_val){
          if (la_val > 0) {
            cw_change = la_val;
            w_cursor_y = 64 - map(cw_change, 0, 127, 0, 64);
          }
        }

        static void blur_w_graph_region(int16_t *arr, int index, uint8_t intensity) {
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

        static void blur_w_graph_boundary( int16_t *arr,int range) {
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

        static void smooth_w_bounds(){
          blur_w_graph_boundary(arbitrary_waveforms[waveformIndex], 32);
        }

        static void smooth_w_graph(){
          blur_w_graph_region(arbitrary_waveforms[waveformIndex], w_cursor_x, 64);
        }

        static void set_array_at_cursor(int c_pos_w=w_cursor_x){
          int w_graph_y = map(cw_change, 0, 127, -32768, 32767);
          arbitrary_waveforms[waveformIndex][c_pos_w] = w_graph_y;
          arbitrary_waveforms[waveformIndex][(c_pos_w-1)%256] = w_graph_y;
        }

        static void set_x_cursor_value(byte la_val){
          if (la_val > 0) {
            w_cursor_x = map(la_val, 0, 127, 0, 255);
            //arbitrary_waveforms[waveformIndex][w_cursor_x] = map(cw_change, 0, 127, -32768, 32767);
            sublevels[2]=w_cursor_x;
            vraipos = w_cursor_x;
            myEnc.write(vraipos * 4);
            set_array_at_cursor();
          }
        }

        static void draw_wave_graph(){
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

        static void WaveformEditer() {
          navrange = 255;
          dm.clean_title_1();
          
          if (navlevel > 3) {
            trace_waveform = 0 ;
            
            smooth_w_graph();
            returntonav(2,255,sublevels[2]);
          }
          if (navlevel == 3) {
            trace_waveform = 1 ;
            cw_change = map(sublevels[3],0,255,0,127);
            set_array_at_cursor();
          }
          if (trace_waveform) {
            set_array_at_cursor();
            w_cursor_y = map(arbitrary_waveforms[waveformIndex][w_cursor_x], -32768, 32767, 63, 0);
          }
          if (navlevel == 2) {
            w_cursor_x=sublevels[2];
            w_cursor_y = map(arbitrary_waveforms[waveformIndex][w_cursor_x], -32768, 32767, 63, 0);
            sublevels[3] = map(arbitrary_waveforms[waveformIndex][w_cursor_x],-32768, 32767, 0, 255 ) ;
          }
          

          canvasBIG.drawCircle(sublevels[2]/2, w_cursor_y, 2, SSD1306_WHITE);
          draw_wave_graph();
          //canvastitle.print(arbitrary_waveforms[waveformIndex][sublevels[2]]);
          dm.dodisplay();
          //smooth_w_bounds();
        }

        static void wforms_menu() {
          canvastitle.setCursor(0,0);
          char waveformsmenulabels[wf_labels_count][12] = {
              "Save", "Load", "Copy", "Delete", "Edit", "-->", "<--","Params"};
          byte startx = 5;
          byte starty = 16;
          char *textin = (char *)waveformsmenulabels[sublevels[1]];
          canvastitle.setTextSize(2);
          canvasBIG.setTextSize(2);
          canvastitle.println(textin);
          canvasBIG.drawRoundRect(50,25,22,22,3,SSD1306_WHITE);
          canvasBIG.setCursor(56,29);
          canvasBIG.print(waveformIndex+1);
          canvasBIG.setTextSize(1);
          for (int i = 0; i < wf_labels_count - 1 - (sublevels[1]); i++) {
            canvasBIG.setCursor(startx, starty + ((i)*10));
            canvasBIG.println(waveformsmenulabels[sublevels[1] + 1 + i]);
          }
          for (int i = 0; i < sublevels[1]; i++) {
            canvasBIG.setCursor(startx, (10 * (wf_labels_count - sublevels[1]) + 6 + ((i)*10)));
            canvasBIG.println(waveformsmenulabels[i]);
          }
        }

        static void go_previous(){
          if (waveformIndex-1 < 0)
            waveformIndex = 2 ;
          else
            waveformIndex = waveformIndex-1;
      
          returntonav(1,wf_labels_count-1,sublevels[1]);
        }

        static void go_next(){
          waveformIndex = (waveformIndex+1)%3;
          returntonav(1,wf_labels_count-1,sublevels[1]);
        }

        static void writewaveform() {
          if (locked_fileing)
            return;
          locked_fileing = 1 ;
          File waveform_file ;
          if (self->catalog->new_file_mode) {
            waveform_file = SD.open(self->catalog->get_new_file_name().c_str(), FILE_WRITE);
          } else {
            String selected_waveform = self->catalog->get_current_file_path(0);
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
          self->catalog->list_files();
          locked_fileing = 0 ;
        }

        static void writewaveforms(File &filer) {
          filer.write((byte *)arbitrary_waveforms[waveformIndex], sizeof(arbitrary_waveforms[waveformIndex]));
        }

        static void copywaveform() {
          if (locked_fileing)
            return;
          locked_fileing = 1 ;
          File origin_file;
          File target_file;
          String waveform_path = self->catalog->get_current_file_path(0) ;
          if (SD.exists(waveform_path.c_str())) {
            target_file = SD.open(self->catalog->get_new_file_name().c_str(), FILE_WRITE);
            origin_file = SD.open(waveform_path.c_str(), FILE_READ);
            size_t n_size;
            uint8_t buf[64];
            while ((n_size = origin_file.read(buf, sizeof(buf))) > 0) {
              target_file.write(buf, n_size);
            }
          }

          origin_file.close();
          target_file.close();
          self->catalog->list_files();
          
          locked_fileing = 0 ;
        }

        static void deletewaveform() {
          if (locked_fileing)
            return;
          locked_fileing = 1 ;
          if (SD.exists(self->catalog->get_current_file_path(0).c_str())) {
            SD.remove(self->catalog->get_current_file_path(0).c_str());
          }
          self->catalog->list_files();
          locked_fileing = 0 ;
        }

        static void parsewaveformfile() {
          if (locked_fileing)
            return;
          locked_fileing = 1 ;
          File target_waveform = SD.open(self->catalog->get_current_file_path(0).c_str(), FILE_READ);
          target_waveform.read((byte *)arbitrary_waveforms[waveformIndex], sizeof(arbitrary_waveforms[waveformIndex]));
          target_waveform.close();
          locked_fileing = 0 ;
        }
        
        static void wforms_actions(){
          _nav_wforms[sublevels[1]]();
            
        }
        static void remove_wform(){
          lv1_wrapper(self->deletewaveform);
        }

        static void duplicate_wform(){
          lv1_wrapper(self->copywaveform);
        }

        static void load_wform(){
          lv1_wrapper(self->parsewaveformfile);
        }

        static void save_wform(){
          lv1_wrapper(self->writewaveform);         
        } 

        static void lv1_wrapper(void (*func)()) {
          self->catalog->nav_one(0,1);
          if (navlevel >= 3) {
            func();
            returntonav(1, self->wf_labels_count - 1,sublevels[1]);
          }
        }

        static constexpr void (*_route_nav[7])() = {&waveforms_nav_zero, &wforms_actions, &wforms_actions,
                                    &wforms_actions, &wforms_actions, &wforms_actions, &wforms_actions};
        
        static constexpr void  (*_nav_wforms[8])() = {&save_wform, &load_wform, &duplicate_wform,&remove_wform,
                                                                    &WaveformEditer ,&go_next,&go_previous,&WaveformParams};
  
    private:
        static WaveformsMenuRouter* self;
};

WaveformsMenuRouter* WaveformsMenuRouter::self = nullptr;
WaveformsMenuRouter _wf;
