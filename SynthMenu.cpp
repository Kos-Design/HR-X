#include "SynthMenu.h"
#include "Voices.h"
#include "LfoMenu.h"
#include "KnobAssigner.h"
#include "Triggers.h"

GlideMenuRouter* GlideMenuRouter::self = nullptr;

GlideMenuRouter::GlideMenuRouter() {
  self = this;
  self->home_navrange=4-1;
  self->relative_navlevel=2;
  self->max_navlevel=5;
  self->sublevels_address={0,0,0};
}

void GlideMenuRouter::set_glide_mode_off(byte voice){
  synth_lines[voice]->currentFreq = synth_lines[voice]->targetFreq ;
}

void GlideMenuRouter::set_glide_mode_porta(byte voice){
  if (gg.portamento_time)  {
    synth_lines[voice]->currentFreq = bb.notestofreq[synth_lines[voice]->previous_note];
  }
}

void GlideMenuRouter::set_glide_mode_rporta(byte voice){
  if (gg.portamento_time)  {
    synth_lines[voice]->targetFreq = bb.notestofreq[synth_lines[voice]->previous_note];
    synth_lines[voice]->currentFreq = bb.notestofreq[synth_lines[voice]->note];
  }
}

void GlideMenuRouter::set_glide_mode_patack(byte voice){
  synth_lines[voice]->currentFreq = bb.notestofreq[synth_lines[voice]->note_diff];
}

void GlideMenuRouter::set_glide_mode_rpatack(byte voice){
  synth_lines[voice]->currentFreq = synth_lines[voice]->targetFreq;
  synth_lines[voice]->targetFreq = bb.notestofreq[synth_lines[voice]->note_diff];
}

void GlideMenuRouter::show(){
  lv.navrange = self->home_navrange ;
  if (lv.navlevel == 3 ){
    lv.navrange = 127;
    if (!lv.sublevels[self->relative_navlevel]) lv.navrange = 4;
    *self->glide_params[lv.sublevels[2]] = lv.sublevels[3];
  }
  lv.sublevels[3]=*self->glide_params[lv.sublevels[2]];

  dm.clearDisplay();
  dm.setCursor(0,0);
  dm.setTextSize(1);

  dm.print("Glide Settings");
  dm.println(" ");
  dm.println(" ");
  dm.print("Mode: ");
  dm.print(GlideModeLabels[gg.glideMode]);

  dm.setCursor(0, 28);
  dm.print("Time: ");
  dm.print(gg.portamento_time);

  dm.setCursor(0, 40);
  dm.print("Height: ");
  dm.print(64-gg.portamento_height);
  dm.setCursor(0, 52);
  dm.print("Slope:   ");
  dm.print((64-gg.glide_slope)/64.0);
  dm.display();
  dm.fillRoundRect(0,11+12*lv.sublevels[2], 35, 16, 3, SSD1306_INVERSE);
  dm.display();

  if (lv.navlevel > 3 ){
    dm.returntonav(self->relative_navlevel,self->home_navrange,lv.sublevels[2]);
  }
}

uint8_t *GlideMenuRouter::glide_params[4] = {reinterpret_cast<uint8_t*>(&gg.glideMode),&gg.portamento_time,&gg.portamento_height,&gg.glide_slope};

Filter303MenuRouter* Filter303MenuRouter::self = nullptr;

Filter303MenuRouter::Filter303MenuRouter() {
  self = this;
  self->home_navrange=SN_MENU_LABELS_COUNT-1;
  self->relative_navlevel=1;
  self->max_navlevel=5;
  self->sublevels_address={0,0,0};
  self->avg_slope();
}

void Filter303MenuRouter::initialize303group() {
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    _mx.setle303filterpass(i);
    les303wet[i]->gain(1.0, 1.0);
    les303wet[i]->gain(0.0, 0.0);
    les303filterz[i]->frequency(14800.5);
    les303filterz[i]->resonance(2.5);
  }
}

void Filter303MenuRouter::allpasslevels() {
  mix303L1.gain(0, 1);
  mix303L1.gain(1, 0);
  mix303L1.gain(2, 0);
}

void Filter303MenuRouter::avg_slope(){
  for (int i=0; i<18; i++){
    self->sloped[i] = self->fxsloper[i]*(gg.cut_off_slope/127.0) + self->slopelinear[i]*(1-(gg.cut_off_slope/127.0)) ;
  }
}

void Filter303MenuRouter::pseudo303(byte i) {
  if (_rg.active_synths[i]->f303) {
    if (_rg.active_synths[i]->sloper_step > 17) {
      _rg.active_synths[i]->f303 = 0;
      self->letbfreq = 50 ;
      _rg.active_synths[i]->sloper_step = 0 ;
      return;
    }
    self->letbfreq = gg.le303filterzfreq + 50 - (gg.le303filterzfreq * self->sloped[_rg.active_synths[i]->sloper_step]);
    les303filterz[_rg.active_synths[i]->l_index]->frequency(self->letbfreq);
    //les303filterz[_rg.active_synths[i]->l_index]->resonance(0.1 + ((gg.le303filterzreso/127.0)*5) * self->sloped[_rg.active_synths[i]->sloper_step]);
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
  dm.canvastitle.print("303 ");
  dm.canvastitle.setCursor(22, 0);

  dm.canvastitle.print("In:");
  dm.canvastitle.print((int)((gg.preampleswaves / 127.0) * 200.0));

  coeffangle = (6.2831 - (gg.le303ffilterzVknobs[0] / 127.0) * 6.2831) + 3.1416;
  dm.canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
  ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
  ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
  dm.canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                    ftVcursorpointy, SSD1306_WHITE);
  dm.canvasBIG.setCursor(centercirclex - knobradius + 4,
                      centercircley + knobradius + 4);
  dm.canvasBIG.setTextSize(1);
  dm.canvasBIG.print("FQ");
  if (gg.le303filterzfreq < 1000) {
    dm.canvasBIG.setCursor(centercirclex - knobradius + 1, 25);
    dm.canvasBIG.print(gg.le303filterzfreq);
  }
  if ((gg.le303filterzfreq < 9900) && (gg.le303filterzfreq >= 1000)) {
    dm.canvasBIG.setCursor(centercirclex - knobradius - 1, 25);
    dm.canvasBIG.print(round(gg.le303filterzfreq) / 1000.0, 1);
    dm.canvasBIG.print("k");
  }
  if (gg.le303filterzfreq >= 9900) {
    dm.canvasBIG.setCursor(centercirclex - knobradius - 5, 25);
    dm.canvasBIG.print(gg.le303filterzfreq / 1000.0, 1);
    dm.canvasBIG.print("k");
  }

  // resonnance
  coeffangle = (6.2831 - (gg.le303ffilterzVknobs[1] / 127.0) * 6.2831) + 3.1416;
  centercirclex = knobradius + 30;
  dm.canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
  ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
  ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
  dm.canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                    ftVcursorpointy, SSD1306_WHITE);
  dm.canvasBIG.setCursor(centercirclex - knobradius + 1,
                      centercircley + knobradius + 4);
  dm.canvasBIG.setTextSize(1);
  dm.canvasBIG.print("Res");
  dm.canvasBIG.setCursor(centercirclex - knobradius + 2, 25);
  dm.canvasBIG.print((gg.le303filterzreso/127.0)*5, 1);

  barsize = round(((gg.le303filterzgainz[0]/127.0) * (totbartall - 4)));
  dm.canvasBIG.drawRoundRect(81, topwbarstart, wbarwidth, totbartall, 2,
                          SSD1306_WHITE);
  dm.canvasBIG.fillRect(81 + 2, (totbartall + topwbarstart - barsize - 2),
                    wbarwidth - 4, barsize, SSD1306_WHITE);
  dm.canvasBIG.setCursor(81, totbartall + topwbarstart + 4);
  dm.canvasBIG.print("LP");

  barsize = round(((gg.le303filterzgainz[1]/127.0) * (totbartall - 4)));
  dm.canvasBIG.drawRoundRect(98, topwbarstart, wbarwidth, totbartall, 2, SSD1306_WHITE);
  dm.canvasBIG.fillRect(98 + 2, (totbartall + topwbarstart - barsize - 2), wbarwidth - 4, barsize, SSD1306_WHITE);
  dm.canvasBIG.setCursor(97, totbartall + topwbarstart + 4);
  dm.canvasBIG.print("BP");

  barsize = round(((gg.le303filterzgainz[2]/127.0) * (totbartall - 4)));
  dm.canvasBIG.drawRoundRect(115, topwbarstart, wbarwidth, totbartall, 2, SSD1306_WHITE);
  dm.canvasBIG.fillRect(115 + 2, (totbartall + topwbarstart - barsize - 2), wbarwidth - 4, barsize, SSD1306_WHITE);
  dm.canvasBIG.setCursor(114, totbartall + topwbarstart + 4);
  dm.canvasBIG.print("HP");

  barsize = round(((gg.le303filterzwet / 127.0) * (totbartall - 4)));
  dm.canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall, wbarwidth2, 2, SSD1306_WHITE);
  dm.canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4, SSD1306_WHITE);
  dm.canvasBIG.setCursor(startlex2, 0);
  dm.canvasBIG.print("Wet");

  barsize = round((0.5 * (totbartall - 4)));

  dm.canvastitle.setCursor(54, 8);
  dm.canvastitle.print("Glide: ");
  if (!gg.portamento_time) dm.canvastitle.print("Off");
  else dm.canvastitle.print(gg.portamento_time);

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
    dm.canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2,
                        SSD1306_WHITE);
  }
  // res
  if (slct == 1) {
    lv.sublevels[3] = gg.le303ffilterzVknobs[1];
    dm.canvasBIG.drawCircle(centercirclex + 25, centercircley, knobradius - 2,
                        SSD1306_WHITE);
  }
  /*
  // oct
  if (slct == 2) {
    lv.sublevels[3] = gg.le303ffilterzVknobs[2];
    dm.canvasBIG.drawCircle(centercirclex + 50, centercircley, knobradius - 2,
                        SSD1306_WHITE);
  }
  */
  // lp
  if (slct == 2) {
    lv.sublevels[3] = gg.mixle303ffilterzVknobs[0];
    dm.canvasBIG.drawRect(83, topwbarstart, wbarwidth - 4, totbartall,
                      SSD1306_WHITE);
  }
  // bp
  if (slct == 3) {
    lv.sublevels[3] = gg.mixle303ffilterzVknobs[1];
    dm.canvasBIG.drawRect(100, topwbarstart, wbarwidth - 4, totbartall,
                      SSD1306_WHITE);
  }
  // hp
  if (slct == 4) {
    lv.sublevels[3] = gg.mixle303ffilterzVknobs[2];
    dm.canvasBIG.drawRect(117, topwbarstart, wbarwidth - 4, totbartall,
                      SSD1306_WHITE);
  }
  // wet
  if (slct == 5) {
    lv.sublevels[3] = gg.le303filterzwet;
    dm.canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall,
                      wbarwidth2 - 4, SSD1306_WHITE);
  }

  if (slct == 6) {
    lv.sublevels[3] = gg.preampleswaves;
    dm.canvasBIG.setCursor(34, 0);
    dm.canvasBIG.print((char)9);
  }

  if (slct == 7) {
    lv.sublevels[3] = gg.portamento_time ;
    dm.canvasBIG.setCursor(100, 8);
    dm.canvasBIG.print((char)9);
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

byte *Filter303MenuRouter::filter_tmp_pointers[8] = { &gg.le303ffilterzVknobs[0], &gg.le303ffilterzVknobs[1], &gg.mixle303ffilterzVknobs[0], &gg.mixle303ffilterzVknobs[1], &gg.mixle303ffilterzVknobs[2],
                                              &gg.le303filterzwet, &gg.preampleswaves, &gg.portamento_time };

byte Filter303MenuRouter::filter_tmp_values[8] = {gg.le303ffilterzVknobs[0],gg.le303ffilterzVknobs[1],gg.mixle303ffilterzVknobs[0],gg.mixle303ffilterzVknobs[1],gg.mixle303ffilterzVknobs[2],
                                          gg.le303filterzwet,gg.preampleswaves,gg.portamento_time };

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
      if (!SD.sdfs.exists((char*)self->mp3_name.c_str())) {
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
    _mp3_actions[lv.sublevels[2]]();
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
}

void Mp3PlayerRouter::get_next_mp3() {
  if (SD.sdfs.exists("MP3") ) {
    FsFile susudir = SD.sdfs.open("MP3");
    char mpname[32]{};
    if (!self->mp3_looped) {
      while (self->file_index <= self->next_mp3) {
        FsFile subentry = susudir.openNextFile();
        if (!subentry) {
          self->file_index = 0 ;
          self->next_mp3 = 0 ;
          return;
        }

        if (!subentry.isDirectory()) {
          self->file_index++;
          subentry.getName(mpname, 32);
          self->mp3_name = self->mp3_dir + (String)mpname;
        }
        subentry.close();
      }
      self->next_mp3++;
    } else {
      while (self->file_index < self->next_mp3) {
        FsFile subentry = susudir.openNextFile();
        if (!subentry) {
          self->file_index = 0 ;
          return;
        }

        if (!subentry.isDirectory()) {
          self->file_index++;
          subentry.getName(mpname, 32);
          self->mp3_name = self->mp3_dir + (String)mpname;
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

  if (SD.sdfs.exists("MP3") ) {
    FsFile susudir = SD.sdfs.open("MP3");

    while (true) {
      FsFile subentry = susudir.openNextFile();
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

void Mp3PlayerRouter::selector_clues(){
  byte ecart = 14;
  if (self->mp3_continue) dm.fillRect(0*ecart -3, 6, 13, 12, SSD1306_INVERSE);
  if (self->mp3_shuffle) dm.fillRect(5*ecart -3, 6, 13, 12, SSD1306_INVERSE);
  if (self->mp3_paused) dm.fillRect(2*ecart -3, 6, 13, 12, SSD1306_INVERSE);
  if (self->mp3_looped) dm.fillRect(6*ecart -3, 6, 13, 12, SSD1306_INVERSE);
}

void Mp3PlayerRouter::transport_selector() {
  String _legend[] = {"Play All","Previous","Pause","Play file","Next","Shuffle","Loop","Stop"," "};
  int startyp = 8;
  int ecart = 14;
  dm.fillRect(ecart * (lv.sublevels[lv.navlevel])-3, startyp-2, ecart-1, startyp*1.5, SSD1306_INVERSE);
  dm.setCursor(0,20);
  dm.setTextSize(1);
  dm.setTextColor(SSD1306_INVERSE);
  dm.print(_legend[lv.sublevels[2]]);
}

void Mp3PlayerRouter::play_flac_file(const char *flac_file) {
  playMp31.stop();
  playFlac1.play(flac_file);
}

void Mp3PlayerRouter::display_mp3_title(){
  dm.canvasBIG.setCursor(0,40);
  String titler = self->mp3_name;
  titler.remove(0, 4);
  dm.canvasBIG.print((char*)titler.c_str());
}

void Mp3PlayerRouter::mp3_player_panel() {
  dm.clear_3();
  dm.drawtransport();
  display_mp3_title();
  dm.dodisplay();
  mp3_player_actions();
  selector_clues();
  transport_selector();
  dm.display();
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
  dm.setTextSize(1);
  dm.setCursor(80, 8);
  dm.print((float)(((64.0 - gg.wave1offset[lv.oscillator]) / 64.0)));
  draw_synth_params();
  dm.dodisplay();
}

void SynthMenuRouter::freqbars_panel_selector() {
  if (lv.navlevel == 4) {
    lv.retroaction = lv.sublevels[3];
    switch (lv.sublevels[4]){
      case 0:
        dm.fillRect(62, 0, 16, 16, SSD1306_INVERSE);
        self->unit = (int)gg.wavesfreqs[lv.oscillator];
        lv.sublevels[5]=self->unit;
      break;
      case 1:
        dm.fillRect(88, 0, 12, 16, SSD1306_INVERSE);
        self->tenth = ((int)(gg.wavesfreqs[lv.oscillator]* 10)) % 10;
        lv.sublevels[5]=self->tenth;
      break;
      case 2:
        dm.fillRect(100, 0, 12, 16, SSD1306_INVERSE);
        self->hundredth = ((int)(gg.wavesfreqs[lv.oscillator] * 100)) % 10;
        lv.sublevels[5]=self->hundredth;
      break;
    }
  dm.display();
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
    break;
    case 2:
      self->hundredth = lv.sublevels[5];
    break;
  }
  gg.wavesfreqs[lv.oscillator] = (float)(self->unit + self->tenth * 0.1f + self->hundredth * 0.01f);
}

void SynthMenuRouter::displayfreqbars(){
  dm.clear_3();
  dm.setTextSize(2);
  dm.setCursor(65, 0);
  dm.println(gg.wavesfreqs[lv.oscillator]);
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
  }
  displayfreqbars();
  freqbars_panel_selector();
  if (lv.navlevel == 3) {
    lv.retroaction = lv.sublevels[2];
    lv.navrange = self->synth_params_count - 1;
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
  dm.setCursor(80, 0);
  dm.setTextSize(2);
  dm.print(lround((gg.phaselevelsL[lv.oscillator]/127.0)*360));
  dm.dodisplay();
}

void SynthMenuRouter::displayModulatedbool() {
  char modulation_labels[4][7] = {"Off", "Freq", "Phase", "Ampl"};
  draw_synth_params();
  dm.dodisplay();
  dm.setCursor(64, 0);
  dm.setTextSize(2);
  dm.println(modulation_labels[gg.FMmodulated[lv.oscillator]]);
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



  dm.drawBitmap(74, 20, _img[lv.sublevels[4]], 32, 32, SSD1306_WHITE);
  dm.setTextSize(1);
  dm.setTextColor(SSD1306_WHITE);
  dm.setCursor(64, 0);
  dm.println(lelabelw[lv.sublevels[4]]);
  dm.setCursor(120, 57);
  dm.print(lv.oscillator + 1);
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
  dm.clearDisplay();
  dm.drawBitmap(0, 64 - 47, wavesbg2, 128, 47, SSD1306_WHITE);
  dm.display();
}

void SynthMenuRouter::wavelining() {
  lv.retroaction = lv.sublevels[3];
  _synth_params[lv.sublevels[3]]();
}

void SynthMenuRouter::draw_synth_params() {
  const char* wavelineslabels[] = {
      "Type", "Mod", "LFO", "Freq", "Offset", "Phase", "<-  ", "  ->"};
  dm.main_panel(wavelineslabels,3,self->synth_params_count);
  dm.canvasBIG.setCursor(120, 57);
  dm.canvasBIG.print(lv.oscillator + 1);
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
  dm.fillRect(0+(lv.oscillator%2)*64, 16+(24*(lv.oscillator/2)), 64, 24, SSD1306_INVERSE);
  dm.printlabel((char*)leprintlabel.c_str());
  dm.display();
}

void SynthMenuRouter::wavesline_selector(){
  lv.retroaction = lv.sublevels[lv.navlevel-2] ;
  _waveliners[lv.navlevel-2]();
}

void SynthMenuRouter::synth_nav_zero() {
  lv.navrange = self->home_navrange;
  dm.clean_title_2_1();
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
  _tt.stopallnotes();
  AudioNoInterrupts();
  byte letype = gg.Waveformstyped[lv.oscillator];
  if (letype == 11) {
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

void (*SynthMenuRouter::_nav_synth[SN_MENU_LABELS_COUNT])() = {&wavesline_selector,&_mx.show, &_ad.show, &_mp.mp3_player_panel, &_ft.show,&_gd.show};
