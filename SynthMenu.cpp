#include "SynthMenu.h"
#include "Voices.h"
#include "LfoMenu.h"

GlideMenuRouter* GlideMenuRouter::self = nullptr;

GlideMenuRouter::GlideMenuRouter() {
  self = this;
  self->home_navrange=4-1;
  self->relative_navlevel=2;
  self->max_navlevel=5;
  self->sublevels_address={0,0,0};
  
}

void GlideMenuRouter::show(){
  lv.navrange = self->home_navrange ;
  if (lv.navlevel == 3 ){
    lv.navrange = 127;
    if (!lv.sublevels[self->relative_navlevel]) lv.navrange = 4;
    *self->glide_params[lv.sublevels[2]] = lv.sublevels[3];
  }
  lv.sublevels[3]=*self->glide_params[lv.sublevels[2]];

  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  
  display.print("Glide Settings");
  display.println(" ");
  display.println(" ");
  display.print("Mode: ");
  display.print(GlideModeLabels[gg.glideMode]);

  display.setCursor(0, 28);
  display.print("Time: ");
  display.print(gg.portamento_time);

  display.setCursor(0, 40);
  display.print("Height: ");
  display.print(64-gg.portamento_height);
  display.setCursor(0, 52);
  display.print("Slope:   ");
  display.print((64-gg.glide_slope)/64.0);
  display.display();
  display.fillRoundRect(0,11+12*lv.sublevels[2], 35, 16, 3, SSD1306_INVERSE);
  display.display();
  
  if (lv.navlevel > 3 ){
    dm.returntonav(self->relative_navlevel,self->home_navrange,lv.sublevels[2]);
  }
}

Filter303MenuRouter* Filter303MenuRouter::self = nullptr;

Filter303MenuRouter::Filter303MenuRouter() {
  self = this;
  self->home_navrange=SN_MENU_LABELS_COUNT-1;
  self->relative_navlevel=1;
  self->max_navlevel=5;
  self->sublevels_address={0,0,0};
}

void Filter303MenuRouter::initialize303group() {
      for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
        _mx.setle303filterpass(i);
        les303wet[i]->gain(1.0, 1.0);
        les303wet[i]->gain(0.0, 0.0);
        les303filterz[i]->frequency(1800.5);
        les303filterz[i]->resonance(2.5);
      }
    }



void Filter303MenuRouter::allpasslevels() {
      mix303L1.gain(0, 1);
      mix303L1.gain(1, 0);
      mix303L1.gain(2, 0);
    }


void Filter303MenuRouter::pseudo303(byte i) {
        if (_rg.active_synths[i]->f303) {
          self->letbfreq = gg.le303filterzfreq + 50 - (gg.le303filterzfreq * self->sloped[_rg.active_synths[i]->sloper_step]);
          if (_rg.active_synths[i]->sloper_step > 18) {
            _rg.active_synths[i]->f303 = 0;
            self->letbfreq = 50 ;
            _rg.active_synths[i]->sloper_step = 0 ;
          }
          les303filterz[_rg.active_synths[i]->l_index]->frequency(self->letbfreq);
          les303filterz[_rg.active_synths[i]->l_index]->resonance(0.1 + ((gg.le303filterzreso/127.0)*5) * self->sloped[_rg.active_synths[i]->sloper_step]);
          _rg.active_synths[i]->sloper_step++;
        }
      
    }

void Filter303MenuRouter::filter_knob_freq(){
      lv.navrange = 127;
      gg.le303ffilterzVknobs[0] = lv.sublevels[3];
      gg.le303filterzfreq = lround((gg.le303ffilterzVknobs[0] / 127.0) * 14000);
    }

void Filter303MenuRouter::filter_knob_res(){
      lv.navrange = 127;
      gg.le303ffilterzVknobs[1] = lv.sublevels[3];
      gg.le303filterzreso = gg.le303ffilterzVknobs[1];
    }

void Filter303MenuRouter::filter_knob_low(){
      gg.mixle303ffilterzVknobs[0] = lv.sublevels[3];
      gg.le303filterzgainz[0] = gg.mixle303ffilterzVknobs[0];
    }

void Filter303MenuRouter::filter_knob_band(){
      gg.mixle303ffilterzVknobs[1] = lv.sublevels[3];
      gg.le303filterzgainz[1] = gg.mixle303ffilterzVknobs[1];
    }

void Filter303MenuRouter::filter_knob_high(){
      gg.mixle303ffilterzVknobs[2] = lv.sublevels[3];
      gg.le303filterzgainz[2] = gg.mixle303ffilterzVknobs[2];
    }

void Filter303MenuRouter::filter_knob_wet(){
      lv.navrange = 127;
      gg.le303filterzwet = lv.sublevels[3];
      // gg.le303filterzwet = (gg.mixle303ffilterzVknobs[2])/127.0 ;
      _mx.le303filterzWet();
    }

void Filter303MenuRouter::filter_knob_preamp(){
      lv.navrange = 127;
      gg.preampleswaves = lv.sublevels[3];
      _mx.Wavespreamp303controls();
    }

void Filter303MenuRouter::filter_knob_glide(){
      lv.navrange = 127;
      gg.portamento_time = lv.sublevels[3] ;   

    }


void Filter303MenuRouter::le303filterVpanelAction() {
  if (lv.navlevel == 3) {
    lv.retroaction = lv.sublevels[2];
    lv.navrange = 127;
    if (!lv.temp_buff_armed) {
      set_filter_buff_temp();
      lv.temp_buff_armed = 1 ;
    }
    // AudioNoInterrupts();
    (filters_pointers[lv.sublevels[2]])();
    _mx.le303filtercontrols();

  }
  if (lv.navlevel > 3) {
    lv.temp_buff_armed = 0 ;
    dm.returntonav(2,7,lv.sublevels[2]);
  }
}

void Filter303MenuRouter::le303filterVpanel() {

  //if back from knob and !  : revert from temp ( all or just the changed one ? -> knob validation updates temps )
  // when set temp
  le303filterVpanelAction();
  if (lv.navlevel == 2 && lv.temp_buff_armed) {
    restore_from_temp();
  }
  int knobradius = 9;
  int centercirclex = 5 + knobradius;
  int centercircley = 35 + knobradius;
  int ftVcursorpointx;
  int ftVcursorpointy;
  float coeffangle;
  int totbartall = 37;
  int topwbarstart = 16;
  int wbarwidth = 9;
  int wbarwidth2 = 8;
  int barsize;
  int startlex2 = 67;
  dm.clean_title_1();
  canvastitle.print("303 ");
  canvastitle.setCursor(22, 0);

  canvastitle.print("In:");
  canvastitle.print((int)((gg.preampleswaves / 127.0) * 200.0));

  coeffangle = (6.2831 - (gg.le303ffilterzVknobs[0] / 127.0) * 6.2831) + 3.1416;
  canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
  ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
  ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
  canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                    ftVcursorpointy, SSD1306_WHITE);
  canvasBIG.setCursor(centercirclex - knobradius + 4,
                      centercircley + knobradius + 4);
  canvasBIG.setTextSize(1);
  canvasBIG.print("FQ");
  if (gg.le303filterzfreq < 1000) {
    canvasBIG.setCursor(centercirclex - knobradius + 1, 25);
    canvasBIG.print(gg.le303filterzfreq);
  }
  if ((gg.le303filterzfreq < 9900) && (gg.le303filterzfreq >= 1000)) {
    canvasBIG.setCursor(centercirclex - knobradius - 1, 25);
    canvasBIG.print(round(gg.le303filterzfreq) / 1000.0, 1);
    canvasBIG.print("k");
  }
  if (gg.le303filterzfreq >= 9900) {
    canvasBIG.setCursor(centercirclex - knobradius - 5, 25);
    canvasBIG.print(gg.le303filterzfreq / 1000.0, 1);
    canvasBIG.print("k");
  }

  // resonnance
  coeffangle = (6.2831 - (gg.le303ffilterzVknobs[1] / 127.0) * 6.2831) + 3.1416;
  centercirclex = knobradius + 30;
  canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
  ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
  ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
  canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                    ftVcursorpointy, SSD1306_WHITE);
  canvasBIG.setCursor(centercirclex - knobradius + 1,
                      centercircley + knobradius + 4);
  canvasBIG.setTextSize(1);
  canvasBIG.print("Res");
  canvasBIG.setCursor(centercirclex - knobradius + 2, 25);
  canvasBIG.print((gg.le303filterzreso/127.0)*5, 1);

  barsize = round(((gg.le303filterzgainz[0]/127.0) * (totbartall - 4)));
  canvasBIG.drawRoundRect(81, topwbarstart, wbarwidth, totbartall, 2,
                          SSD1306_WHITE);
  canvasBIG.fillRect(81 + 2, (totbartall + topwbarstart - barsize - 2),
                    wbarwidth - 4, barsize, SSD1306_WHITE);
  canvasBIG.setCursor(81, totbartall + topwbarstart + 4);
  canvasBIG.print("LP");

  barsize = round(((gg.le303filterzgainz[1]/127.0) * (totbartall - 4)));
  canvasBIG.drawRoundRect(98, topwbarstart, wbarwidth, totbartall, 2, SSD1306_WHITE);
  canvasBIG.fillRect(98 + 2, (totbartall + topwbarstart - barsize - 2), wbarwidth - 4, barsize, SSD1306_WHITE);
  canvasBIG.setCursor(97, totbartall + topwbarstart + 4);
  canvasBIG.print("BP");

  barsize = round(((gg.le303filterzgainz[2]/127.0) * (totbartall - 4)));
  canvasBIG.drawRoundRect(115, topwbarstart, wbarwidth, totbartall, 2, SSD1306_WHITE);
  canvasBIG.fillRect(115 + 2, (totbartall + topwbarstart - barsize - 2), wbarwidth - 4, barsize, SSD1306_WHITE);
  canvasBIG.setCursor(114, totbartall + topwbarstart + 4);
  canvasBIG.print("HP");

  barsize = round(((gg.le303filterzwet / 127.0) * (totbartall - 4)));
  canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall, wbarwidth2, 2, SSD1306_WHITE);
  canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4, SSD1306_WHITE);
  canvasBIG.setCursor(startlex2, 0);
  canvasBIG.print("Wet");

  barsize = round((0.5 * (totbartall - 4)));

  canvastitle.setCursor(54, 8);
  canvastitle.print("Glide: ");
  if (!gg.portamento_time) canvastitle.print("Off");
  else canvastitle.print(gg.portamento_time);
  
  le303filterVpanelSelector();
  dm.dodisplay();
}

void Filter303MenuRouter::le303filterVpanelSelector() {
  int knobradius = 9;
  int centercirclex = 5 + knobradius;
  int centercircley = 35 + knobradius;
  int startlex2 = 67;
  int totbartall = 37;
  int topwbarstart = 16;
  int wbarwidth = 9;
  int wbarwidth2 = 8;
  if (lv.navlevel == 2) {
    lv.navrange = 7;
  }
  int slct = lv.sublevels[2];
  // fq
  if (slct == 0) {
    lv.sublevels[3] = gg.le303ffilterzVknobs[0];
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2,
                        SSD1306_WHITE);
  }
  // res
  if (slct == 1) {
    lv.sublevels[3] = gg.le303ffilterzVknobs[1];
    canvasBIG.drawCircle(centercirclex + 25, centercircley, knobradius - 2,
                        SSD1306_WHITE);
  }
  /*
  // oct
  if (slct == 2) {
    lv.sublevels[3] = gg.le303ffilterzVknobs[2];
    canvasBIG.drawCircle(centercirclex + 50, centercircley, knobradius - 2,
                        SSD1306_WHITE);
  }
  */
  // lp
  if (slct == 2) {
    lv.sublevels[3] = gg.mixle303ffilterzVknobs[0];
    canvasBIG.drawRect(83, topwbarstart, wbarwidth - 4, totbartall,
                      SSD1306_WHITE);
  }
  // bp
  if (slct == 3) {
    lv.sublevels[3] = gg.mixle303ffilterzVknobs[1];
    canvasBIG.drawRect(100, topwbarstart, wbarwidth - 4, totbartall,
                      SSD1306_WHITE);
  }
  // hp
  if (slct == 4) {
    lv.sublevels[3] = gg.mixle303ffilterzVknobs[2];
    canvasBIG.drawRect(117, topwbarstart, wbarwidth - 4, totbartall,
                      SSD1306_WHITE);
  }
  // wet
  if (slct == 5) {
    lv.sublevels[3] = gg.le303filterzwet;
    canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall,
                      wbarwidth2 - 4, SSD1306_WHITE);
  }
  
  if (slct == 6) {
    lv.sublevels[3] = gg.preampleswaves;
    canvasBIG.setCursor(34, 0);
    canvasBIG.print((char)9);
  }

  if (slct == 7) {
    lv.sublevels[3] = gg.portamento_time ;
    canvasBIG.setCursor(100, 8);
    canvasBIG.print((char)9);
  }

}

void Filter303MenuRouter::restore_from_temp() {
      for (int i=0; i<8; i++) {
        lv.sublevels[3] = self->filter_tmp_values[i];
        (filters_pointers[i])();
        _mx.le303filtercontrols();
        *self->filter_tmp_pointers[i] = self->filter_tmp_values[i] ;
      }
        lv.temp_buff_armed = 0 ;
    }

void Filter303MenuRouter::set_filter_buff_temp() {

      for (int i=0; i<8; i++) {
        self->filter_tmp_values[i] = *self->filter_tmp_pointers[i] ;
      }

    }
    
void Filter303MenuRouter::show(){
  le303filterVpanel();
}

Mp3PlayerRouter* Mp3PlayerRouter::self = nullptr;

Mp3PlayerRouter::Mp3PlayerRouter() {
  self = this;
  self->home_navrange=8;
  self->catalog = new FilesLister("MP3/","LONGFILE#",".MP3",mp3_player_panel,self->home_navrange);
  self->relative_navlevel=2;
  self->max_navlevel=5;
  self->sublevels_address={7,0,0};
}

void Mp3PlayerRouter::mp3_player_play(){
      if (!SD.exists((char*)self->mp3_name.c_str())) {
        get_next_mp3();
      }
      playFile((char*)self->mp3_name.c_str());
    }

void Mp3PlayerRouter::mp3_player_stop(){
      playMp31.stop();
      self->mp3_continue = 0 ;
    }

void Mp3PlayerRouter::mp3_player_continous(){
      self->mp3_continue = !self->mp3_continue ;
    }

void Mp3PlayerRouter::mp3_player_pause(){
      self->mp3_paused = playMp31.pause(!self->mp3_paused);
      self->mp3_continue = 0 ;
    }

void Mp3PlayerRouter::mp3_player_next(){
      
      Serial.println("");
      Serial.print("previous =");
      Serial.print(self->previous_mp3);
      
      if (!self->mp3_looped) {
        if (self->mp3_shuffle) {
          self->previous_mp3 = self->next_mp3;

          Serial.println("");
          Serial.print("previous after next =");
          Serial.print(self->previous_mp3);
          
          self->next_mp3 = rand() % self->mp3_count ;
          Serial.println(self->mp3_count);
          Serial.println(self->next_mp3);
        } else {
          self->next_mp3++;
        }
      }
      get_next_mp3();
    }

void Mp3PlayerRouter::mp3_player_previous(){

      Serial.println("");
      Serial.print("previous =");
      Serial.print(self->previous_mp3);

      if (!self->mp3_looped){
        if (self->mp3_shuffle){
          self->next_mp3 = self->previous_mp3 ;
        } else {
          self->next_mp3 -= 2;
        }
      } 
      get_next_mp3();
    }

void Mp3PlayerRouter::mp3_player_shuffle(){
      //TODO: make whole list of shuffled numbers the size of their folder files count
      // allow next and previous
      //regenerate on stop / and shuffle toggle 
      self->mp3_shuffle = !self->mp3_shuffle ;
      if (self->mp3_shuffle) {
        self->previous_mp3 = self->next_mp3;

      }
    }
void Mp3PlayerRouter::mp3_loop_setter(){
      self->mp3_looped = !self->mp3_looped ;
      self->mp3_continue = self->mp3_looped ;
    }
void Mp3PlayerRouter::mp3_player_actions() {
  if (lv.navlevel == 2) {
    lv.navrange = 8;
  }
  if (lv.navlevel >= 3) {
    switch (lv.sublevels[2]) {
      case 0:
        //continous_play
        mp3_player_continous();
      break;

      case 1:
        //previous_play
        mp3_player_previous();
      break;

      case 2:
        //pause_play
        mp3_player_pause();
      break;

      case 3:
        //one_play
        mp3_player_play();
      break;

      case 4:
        //next_play
        mp3_player_next();
      break;

      case 5:
        //shuffle_on
        mp3_player_shuffle();
      break;

      case 6:
        mp3_loop_setter();
      break;

      case 7:
        //stop_it();
        mp3_player_stop();
      break;

    }
    dm.returntonav(2,8,lv.sublevels[2]);
  }
}

void Mp3PlayerRouter::get_file_type(){
  /*
  int dot = self->mp3_name.lastIndexOf('.');
  if (dot >= 0) {
    String extension = self->mp3_name.substring(dot + 1);
  }
  */
  String filenamed = self->mp3_name ;
  filenamed.toLowerCase();
  if (filenamed.endsWith(".mp3"))
      self->mp3_ext = 0 ;
    if (filenamed.endsWith(".flac"))
      self->mp3_ext = 1 ;
}

void Mp3PlayerRouter::playFile(const char *mp3_file) {
  get_file_type();
  switch (self->mp3_ext){
    case 0:
      playFlac1.stop();
      playMp31.play(mp3_file);
    break;

    case 1:
      play_flac_file(mp3_file);

    break;
  }

  //while (playMp31.isPlaying()) {
  //}
}

void Mp3PlayerRouter::get_next_mp3() {
  if (SD.exists("MP3") ) {
    File susudir = SD.open("MP3");
    if (!self->mp3_looped) {
      while (self->file_index <= self->next_mp3) {
        File subentry = susudir.openNextFile();
        if (!subentry) {
          self->file_index = 0 ;
          self->next_mp3 = 0 ;
          return;
        }

        if (!subentry.isDirectory()) {
          self->file_index++;
          self->mp3_name = self->mp3_dir + subentry.name();
        }
        subentry.close();
      }
      self->next_mp3++;
    } else {

      while (self->file_index < self->next_mp3) {
        File subentry = susudir.openNextFile();
        if (!subentry) {
          self->file_index = 0 ;
          return;
        }

        if (!subentry.isDirectory()) {
          self->file_index++;
          self->mp3_name = self->mp3_dir + subentry.name();
        }
        subentry.close();
      }
    }
    self->file_index = 0 ;
    susudir.close();
  }
  if (self->mp3_shuffle) {
    self->next_mp3 = rand() % self->mp3_count ;
  }

}

void Mp3PlayerRouter::count_mp3s() {
  self->mp3_count=0;
  
  if (SD.exists("MP3") ) {
    File susudir = SD.open("MP3");
    
    while (true) {
      File subentry = susudir.openNextFile();
      if (!subentry) {
        return;
      }
      if (!subentry.isDirectory()) {
        self->mp3_count++;
      }
      subentry.close();
    }
  susudir.close();
  }
}

void Mp3PlayerRouter::transport_selector() {
  String _legend[] = {"Play All","Previous","Pause","Play file","Next","Shuffle","Loop","Stop"," "};
  int startyp = 8;
  int ecart = 14;
  display.fillRect(ecart * (lv.sublevels[lv.navlevel])-3, startyp-2, ecart-1, startyp*1.5, SSD1306_INVERSE);
  display.setCursor(0,20);
  display.setTextSize(1);
  display.setTextColor(SSD1306_INVERSE);
  display.print(_legend[lv.sublevels[2]]);
  display.display();
}

void Mp3PlayerRouter::play_flac_file(const char *flac_file) {
  playMp31.stop();
  playFlac1.play(flac_file);
  //playFlac1.setPlaybackCompleteCallback(display_mp3_title);

}


void Mp3PlayerRouter::display_mp3_title(){
  canvasBIG.setCursor(0,40);
  String titler = self->mp3_name;
  titler.remove(0, 4);
  //titler.remove(titler.length() - 4);
  canvasBIG.print((char*)titler.c_str());
}

void Mp3PlayerRouter::mp3_player_panel() {
  dm.clear_3();
  dm.drawtransport();
  mp3_player_actions();
  dm.dodisplay();
  transport_selector();
  display_mp3_title();
  dm.dodisplay();
  //placeholder
}


SynthMenuRouter* SynthMenuRouter::self = nullptr;

SynthMenuRouter::SynthMenuRouter() {
                    self = this;
                    self->home_navrange=SN_MENU_LABELS_COUNT-1;
                    self->relative_navlevel=1;
                    self->max_navlevel=5;
                    self->sublevels_address={0,0,0};
                    }


void SynthMenuRouter::show() {
          _route_nav[lv.navlevel-1]();
        }

void SynthMenuRouter::route_navlevel_1(){
          synth_nav_zero();
        }

void SynthMenuRouter::route_navlevel_2(){
          lv.retroaction = lv.sublevels[1];
          _nav_synth[lv.sublevels[1]]();
        }

void SynthMenuRouter::displayoffsetwav() {
          dm.clear_3();
          if (lv.navlevel == 3) {
            lv.retroaction = lv.sublevels[2];
            lv.navrange = self->synth_params_count - 1;
            lv.sublevels[4] = gg.wave1offset[lv.oscillator];
          }
          if (lv.navlevel == 4) {
            lv.navrange = 127;
            lv.retroaction = lv.sublevels[3];
            gg.wave1offset[lv.oscillator] = lv.sublevels[4];
            for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
              waveforms1[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->offset((float)(((64.0 - gg.wave1offset[lv.oscillator]) / 64.0)));
              FMwaveforms1[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->offset((float)(((64.0 - gg.wave1offset[lv.oscillator]) / 64.0)));
            }
          }
          if (lv.navlevel >= 5) {
            dm.returntonav(3,self->synth_params_count-1,lv.sublevels[3]);
            return;
          }
          display.setTextSize(1);
          display.setCursor(80, 8);
          display.print((float)(((64.0 - gg.wave1offset[lv.oscillator]) / 64.0)));

          draw_synth_params();
          dm.dodisplay();
        }

void SynthMenuRouter::freqbars_panel_selector() {
          if (lv.navlevel == 4) {
            lv.retroaction = lv.sublevels[3];
            switch (lv.sublevels[4]){
              case 0:
                display.fillRect(62, 0, 16, 16, SSD1306_INVERSE);
                self->unit = (int)gg.wavesfreqs[lv.oscillator];
                lv.sublevels[5]=self->unit;
              break;
              case 1:
                display.fillRect(88, 0, 12, 16, SSD1306_INVERSE);
                self->tenth = ((int)(gg.wavesfreqs[lv.oscillator]* 10)) % 10;
                lv.sublevels[5]=self->tenth;
              break;
              case 2:
                display.fillRect(100, 0, 12, 16, SSD1306_INVERSE);
                self->hundredth = ((int)(gg.wavesfreqs[lv.oscillator] * 100)) % 10;
                lv.sublevels[5]=self->hundredth;
              break;
            }
          display.display();
          }
        }
void SynthMenuRouter::freqbars_panel_action() {

          lv.navrange = 9;
          switch (lv.sublevels[4]){
            case 0:
              self->unit = lv.sublevels[5];
            break;
            case 1:
              self->tenth = lv.sublevels[5];
              //Serial.println(self->hundredth);
            break;
            case 2:
              self->hundredth = lv.sublevels[5];
              //Serial.println(self->hundredth);
            break;
          }

          gg.wavesfreqs[lv.oscillator] = (float)(self->unit + self->tenth * 0.1f + self->hundredth * 0.01f);
        }

void SynthMenuRouter::displayfreqbars(){
          dm.clear_3();
          display.setTextSize(2);
          display.setCursor(65, 0);
          display.println(gg.wavesfreqs[lv.oscillator]);
          draw_synth_params();
          dm.dodisplay();
        }

void SynthMenuRouter::freqbars_panel() {
          if (lv.navlevel >= 4) {
            lv.retroaction = lv.sublevels[3];
            if (lv.navlevel == 4) {
              lv.navrange = 2;

            }
            if (lv.navlevel == 5) {
              lv.retroaction = lv.sublevels[4];
              freqbars_panel_action();
            }
            if (lv.navlevel >= 6) {
              dm.returntonav(4,9,lv.sublevels[4]);
            }
            //dm.dodisplay();
          }
          displayfreqbars();
          freqbars_panel_selector();
          if (lv.navlevel == 3) {
            lv.retroaction = lv.sublevels[2];
            lv.navrange = self->synth_params_count - 1;
            //lv.sublevels[4] = round(gg.wavesfreqs[lv.oscillator]);
          }
        }

void SynthMenuRouter::displayphasebars() {
          dm.clear_3();
          if (lv.navlevel == 3) {
            lv.retroaction = lv.sublevels[2];
            lv.navrange = self->synth_params_count - 1;
            lv.sublevels[4] = gg.phaselevelsL[lv.oscillator];
          }
          if (lv.navlevel >= 4) {
            if (lv.navlevel == 4) {
              lv.navrange = 127;
              lv.retroaction = lv.sublevels[3];
              gg.phaselevelsL[lv.oscillator] = lv.sublevels[4];
              setphaselevel();
            }
            if (lv.navlevel >= 5) {
              setphaselevel();
              dm.returntonav(3,self->synth_params_count-1,lv.sublevels[3]);
            }
          }

          draw_synth_params();

          display.setCursor(80, 0);
          display.setTextSize(2);
          display.print(lround((gg.phaselevelsL[lv.oscillator]/127.0)*360));
          //display.print("°");
          dm.dodisplay();
        }

void SynthMenuRouter::displayModulatedbool() {
          char modulation_labels[4][7] = {"Off", "Freq", "Phase", "Ampl"};

          draw_synth_params();
          dm.dodisplay();
          display.setCursor(64, 0);
          display.setTextSize(2);
          display.println(modulation_labels[gg.FMmodulated[lv.oscillator]]);
          draw_synth_params();
          dm.dodisplay();

        }

void SynthMenuRouter::setfmtophase() {
          for (byte i = 0; i < SYNTH_LINERS_COUNT; i++) {
            //phaseModulation should be based on lfo level
            FMwaveforms1[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->phaseModulation(180);
          }
        }

void SynthMenuRouter::setfmtofreq() {
          for (byte i = 0; i < SYNTH_LINERS_COUNT; i++) {
            //phaseModulation should be based on lfo level
            FMwaveforms1[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->frequencyModulation(10);
          }
        }

void SynthMenuRouter::wavelineModulatedbool() {
          dm.clear_3();
          if (lv.navlevel == 3) {
            lv.retroaction = lv.sublevels[2];
            lv.navrange = self->synth_params_count - 1;
          }
          if (lv.navlevel == 4) {
            lv.navrange = 3;
            lv.retroaction = lv.sublevels[3];
            gg.FMmodulated[lv.oscillator] = lv.sublevels[4];
          }
          if (lv.navlevel > 4) {
            setwavetypefromlist();
            dm.returntonav(3,self->synth_params_count-1,lv.sublevels[3]);
          }
          displayModulatedbool();
        }

void SynthMenuRouter::displaywaveformicon(){
          dm.clear_3();
          if (lv.navlevel == 3) {
            lv.retroaction = lv.sublevels[2];
            lv.navrange = self->synth_params_count - 1;
            lv.sublevels[4] = gg.Waveformstyped[lv.oscillator];
          }
          if (lv.navlevel == 4) {
            lv.navrange = 11;
            gg.Waveformstyped[lv.oscillator] = lv.sublevels[4];
            lv.retroaction = lv.sublevels[3];
          }
          if (lv.navlevel > 4) {
            setwavetypefromlist();
            if (gg.Waveformstyped[lv.oscillator] == 11) {
              gg.mixlevelsL[lv.oscillator] = 0;
              _mx.setwavemixlevel();
            }
            dm.returntonav(3,self->synth_params_count-1,lv.sublevels[3]);
            return;
          }
          const unsigned char *_img[12] = { sinewave, sawtoothwave, reversesawtoothwave, trianglewave,
                                        variabletriangle, squarewave, pulsewave,arbitrarywave,
                                        samplehold,arbitrarywave,samplehold,moonwave};
          const char* lelabelw[12] = {"SineWave","SawWave","ReverseSaw" ,"Triangle","V-Triangle","SquareWave",
                              "PulseWave","Arbitrary","SampleHold", "Drum","String", "Wave OFF"};

          display.drawBitmap(74, 20, _img[lv.sublevels[4]], 32, 32, SSD1306_WHITE);
          display.setTextSize(1);
          display.setTextColor(SSD1306_WHITE);
          display.setCursor(64, 0);
          display.println(lelabelw[lv.sublevels[4]]);
          display.setCursor(120, 57);
          display.print(lv.oscillator + 1);
          draw_synth_params();
          dm.dodisplay();
        }

void SynthMenuRouter::displayLFOpanel() {
          dm.clear_3();
          if (lv.navlevel == 3 ) {
            lv.retroaction = lv.sublevels[2];
            lv.navrange = self->synth_params_count - 1;
          }
          draw_synth_params();
            dm.dodisplay();
          if (lv.navlevel >= 4) {
            lv.sublevels[0] = 1;
            lv.sublevels[1] = lv.oscillator;
            lv.sublevels[2] = 0;
            dm.returntonav(lv.navlevel-2,_lf.sizeofLFOlabels - 1,0);
          }
        }

void SynthMenuRouter::go_previous(){
          dm.clear_3();
          if (lv.navlevel == 3) {
            lv.retroaction = lv.sublevels[2];
            lv.navrange = self->synth_params_count - 1;
          }

          if (lv.navlevel >= 4) {
            if (lv.oscillator-1 < 0)
              lv.oscillator = 2 ;
            else
              lv.oscillator = lv.oscillator-1;

            lv.sublevels[2] = lv.oscillator ;
            dm.returntonav(lv.navlevel-1,self->synth_params_count-1,lv.sublevels[3]);
            return;
          }
          draw_synth_params();
          dm.dodisplay();
        }
void SynthMenuRouter::go_next(){
          dm.clear_3();
          if (lv.navlevel == 3) {
            lv.retroaction = lv.sublevels[2];
            lv.navrange = self->synth_params_count - 1;
          }
          if (lv.navlevel >= 4) {
            lv.oscillator = (lv.oscillator+1)%3;
            lv.sublevels[2] = lv.oscillator ;
            dm.returntonav(lv.navlevel-1,self->synth_params_count-1,lv.sublevels[3]);
          }
          draw_synth_params();
          dm.dodisplay();
        }

void SynthMenuRouter::wavelinesBG() {
          display.clearDisplay();
          display.drawBitmap(0, 64 - 47, wavesbg2, 128, 47, SSD1306_WHITE);
          display.display();
        }

void SynthMenuRouter::wavelining() {
          lv.retroaction = lv.sublevels[3];
          _synth_params[lv.sublevels[3]]();
        }

void SynthMenuRouter::draw_synth_params() {
          const char* wavelineslabels[] = {
              "Type", "Mod", "LFO", "Freq", "Offset", "Phase", "<-  ", "  ->"};
          dm.main_panel(wavelineslabels,3,self->synth_params_count);
          canvasBIG.setCursor(120, 57);
          canvasBIG.print(lv.oscillator + 1);
        }

void SynthMenuRouter::dolistsyntmenu() {
          const char* synthmenulabels[] = {"Synths", "Mixer", "ADSR", "MP3 Player", "Filter", "Glider"};
          dm.main_panel(synthmenulabels,1,SN_MENU_LABELS_COUNT);          
        }

void SynthMenuRouter::synths_switcher(){
          String titled = "Waveline ";
          lv.oscillator = lv.sublevels[2]%OSCS_COUNT;
          String synth_num = lv.oscillator + 1 ;
          lv.navrange = OSCS_COUNT-1;
          String leprintlabel = titled + synth_num ;
          wavelinesBG();
          lv.sublevels[3] = 0;
          display.fillRect(0+(lv.oscillator%2)*64, 16+(24*(lv.oscillator/2)), 64, 24, SSD1306_INVERSE);
          dm.printlabel((char*)leprintlabel.c_str());
          display.display();
        }

void SynthMenuRouter::wavesline_selector(){
          lv.retroaction = lv.sublevels[lv.navlevel-2] ;
          _waveliners[lv.navlevel-2]();
        }

void SynthMenuRouter::synth_nav_zero() {
          lv.navrange = self->home_navrange;
          dm.clean_title_2_1();
          //if (!lv.retroaction)
          //  dm.reinitsublevels(2);
          dolistsyntmenu();
          lv.retroaction = lv.sublevels[1] ;
          dm.dodisplay();
        }

void SynthMenuRouter::plug_no_waves(){
          gg.mixlevelsL[lv.oscillator] = 0;
          for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
            wavelinescords[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            stringcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            drumcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            FMwavecords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            MDdrumcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            MDwavecords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            MDstringcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            modulatecords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
          }
        }

void SynthMenuRouter::plug_waves(){
          for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
            FMwavecords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            stringcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            modulatecords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            MDdrumcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            MDstringcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            MDwavecords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            drumcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            wavelinescords[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->connect();
            if (gg.Waveformstyped[lv.oscillator] == WAVEFORM_ARBITRARY) {
              waveforms1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->arbitraryWaveform(gg.arbitrary_waveforms[lv.oscillator],gg.arbitrary_maxF[lv.oscillator]);
            }
            waveforms1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->begin(lesformes[gg.Waveformstyped[lv.oscillator]]);
          }
        }

void SynthMenuRouter::plug_moded_waves(){
          for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
            wavelinescords[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            modulatecords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            MDdrumcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            MDstringcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            stringcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            drumcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            MDwavecords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            FMwavecords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->connect();
            if (gg.Waveformstyped[lv.oscillator] == WAVEFORM_ARBITRARY) {
              FMwaveforms1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->arbitraryWaveform(gg.arbitrary_waveforms[lv.oscillator],gg.arbitrary_maxF[lv.oscillator]);
            }
            FMwaveforms1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->begin(lesformes[gg.Waveformstyped[lv.oscillator]]);
          }
          _lf.restartLFO(lv.oscillator%OSCS_COUNT);
        }

void SynthMenuRouter::plug_ampl_moded_waves(){
          for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
            wavelinescords[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            MDdrumcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            MDstringcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            stringcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            drumcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            FMwavecords1[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            MDwavecords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->connect();
            modulatecords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->connect();
            if (gg.Waveformstyped[lv.oscillator] == WAVEFORM_ARBITRARY) {
              waveforms1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->arbitraryWaveform(gg.arbitrary_waveforms[lv.oscillator],gg.arbitrary_maxF[lv.oscillator]);
            }
            waveforms1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->begin(lesformes[gg.Waveformstyped[lv.oscillator]]);
          }
          _lf.restartLFO(lv.oscillator%OSCS_COUNT);
        }

void SynthMenuRouter::plug_strings_waves(){
          for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
            wavelinescords[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            drumcords1[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            FMwavecords1[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            modulatecords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            MDwavecords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            MDdrumcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            MDstringcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            stringcords1[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->connect();
          }
        }

void SynthMenuRouter::plug_ampl_moded_strings(){
          for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
            wavelinescords[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            drumcords1[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            FMwavecords1[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            stringcords1[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            MDwavecords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            MDdrumcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            MDstringcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->connect();
            modulatecords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->connect();
          }
        }

void SynthMenuRouter::plug_drum_waves(){
          for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
            wavelinescords[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            stringcords1[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            FMwavecords1[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            modulatecords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            MDwavecords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            MDdrumcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            MDstringcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            drumcords1[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->connect();
          }
        }

void SynthMenuRouter::plug_ampl_moded_drums(){
          for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
            wavelinescords[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            stringcords1[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            FMwavecords1[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            drumcords1[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            MDwavecords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            MDstringcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->disconnect();
            //TODO: apply to other types too
            modulatecords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->connect();
            MDdrumcords1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->connect();
          }
        }

void SynthMenuRouter::no_modulation(){
          byte letype = gg.Waveformstyped[lv.oscillator];
          if (letype < 9) {
            gg.audio_obj_type[lv.oscillator] = 1; //       9*4 + drums *2 + string *2 + off
            plug_waves();
          }
          else if (letype == 9) {
            gg.audio_obj_type[lv.oscillator] = 3 ;
            plug_drum_waves();
          }
          else if (letype == 10) {
            gg.audio_obj_type[lv.oscillator] = 4 ;
            plug_strings_waves();
          }
        }

void SynthMenuRouter::freq_modulation(){
          byte letype = gg.Waveformstyped[lv.oscillator];
          if (letype < 9) {
            gg.audio_obj_type[lv.oscillator] = 2;
            plug_moded_waves();
          }
          //no freq modulation on strings or drums
          else if (letype == 9) {
            gg.audio_obj_type[lv.oscillator] = 3;
            plug_drum_waves();
          }
          else if (letype == 10) {
            gg.audio_obj_type[lv.oscillator] = 4;
            plug_strings_waves();
          }
        }

void SynthMenuRouter::phase_modulation(){
          byte letype = gg.Waveformstyped[lv.oscillator];
          if (letype < 9) {
              gg.audio_obj_type[lv.oscillator] = 2;
              plug_moded_waves();
            }
            //no phase modulation on strings or drums
            else if (letype == 9) {
              gg.audio_obj_type[lv.oscillator] = 3;
              plug_drum_waves();
            }
            else if (letype == 10) {
              gg.audio_obj_type[lv.oscillator] = 4;
              plug_strings_waves();
          }
        }

void SynthMenuRouter::amplitude_modulation(){
          byte letype = gg.Waveformstyped[lv.oscillator];
          if (letype < 9) {
              gg.audio_obj_type[lv.oscillator] = 1;
              plug_ampl_moded_waves();
            }
            else if (letype == 9) {
              // amplitude modulated drum
              gg.audio_obj_type[lv.oscillator] = 3;
              //36 + (bool)gg.FMmodulated[lv.oscillator];
              plug_ampl_moded_drums();
            }
            else if (letype == 10) {
              // amplitude modulated string
              gg.audio_obj_type[lv.oscillator] = 4;
              plug_ampl_moded_strings();
            }
            _lf.restartLFO(lv.oscillator%OSCS_COUNT);
        }

void SynthMenuRouter::setwavetypefromlist() {
          AudioNoInterrupts();
          // all normal/freq/phase/ampl when applicable
          //  WAVEFORM_SINE,     WAVEFORM_SAWTOOTH,          WAVEFORM_SAWTOOTH_REVERSE,
          // WAVEFORM_TRIANGLE, WAVEFORM_TRIANGLE_VARIABLE, WAVEFORM_SQUARE,
          // WAVEFORM_PULSE,    WAVEFORM_ARBITRARY,         WAVEFORM_SAMPLE_HOLD};
          // gg.audio_obj_type  9*4 + drums *2 + string *2 + off
          //gg.Waveformstyped + 2*mod + 2*mod*(drum|||string)
          byte letype = gg.Waveformstyped[lv.oscillator];
          if (letype == 11) {
            // synth line off
            plug_no_waves();
            gg.audio_obj_type[lv.oscillator] = 0;
            AudioInterrupts();
            _mx.setwavemixlevel();
            return;
          }
          (modulation_pointers[gg.FMmodulated[lv.oscillator]])();
          AudioInterrupts();
          _mx.setwavemixlevel();
        }

void SynthMenuRouter::setphaselevel() {
          AudioNoInterrupts();
          for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
            waveforms1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->phase((int)((gg.phaselevelsL[lv.oscillator]/ 127.0) * 360.0));
          }
          AudioInterrupts();
        }



