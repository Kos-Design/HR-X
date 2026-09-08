#include "Functions.h"
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
  mc.navrange = self->home_navrange ;
  uint8_t local_navranges[4]={4,127,127,127};
  if (mc.navlevel == 3 ){
    mc.navrange = local_navranges[mc.sublevels[self->relative_navlevel]];
    *self->glide_params[mc.sublevels[2]] = mc.sublevels[3];
  }
  mc.sublevels[3]=*self->glide_params[mc.sublevels[2]];
  if (mc.navlevel > 3 ){
    dm.returntonav(self->relative_navlevel,self->home_navrange,mc.sublevels[2]);
  }

  char tbuffer[4];
  snprintf(tbuffer, sizeof(tbuffer), "%u", gg.portamento_time);
  char pbuffer[6];
  snprintf(pbuffer, sizeof(pbuffer), "%d", 64-gg.portamento_height);
  char sbuffer[6];
  snprintf(sbuffer, sizeof(sbuffer), "%.2f", (64-gg.glide_slope)/64.0);
  const char* _lbls[4] = {"Mode   ","Time   ","Height ","Slope  "};
  const char* _vals[4] = {(const char*)GlideModeLabels[gg.glideMode],(const char*)tbuffer,(const char*)pbuffer,(const char*)sbuffer};
  dm.sub_menu(_lbls,_vals,39);
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



void Filter303MenuRouter::avg_slope(){
  for (int i=0; i<18; i++){
    self->sloped[i] = self->fxsloper[i]*(gg.cut_off_slope/127.0) + self->slopelinear[i]*(1-(gg.cut_off_slope/127.0)) ;
  }
}

void Filter303MenuRouter::pseudo303(byte i) {
  float letbfreq = 100.0;

  if (_rg.active_synths[i]->f303) {
    
    if (_rg.active_synths[i]->sloper_step > 17) {
      _rg.active_synths[i]->f303 = 0;
      _rg.active_synths[i]->sloper_step = 0 ;
      _rg.active_synths[i]->slope_normalized = 0.0;
      return;
    }

    //slope is optimized for cutoff
    //_rg.active_synths[i]->slope_normalized += 0.0625;
    _rg.active_synths[i]->slope_normalized += 0.0588;
    letbfreq = gg.le303filterzfreq + 100.0 - (gg.le303filterzfreq * self->sloped[_rg.active_synths[i]->sloper_step]);
    //sletbfreq = gg.le303filterzfreq + 100 - (gg.le303filterzfreq * map(_rg.active_synths[i]->slope_normalized*100,0,100,80,100)/100.0);

    //let some unfiltered first before filter decay
    les303filterz[_rg.active_synths[i]->l_index]->frequency(letbfreq);
    les303filterz[_rg.active_synths[i]->l_index]->resonance(0.1 + ((gg.le303filterzreso/127.0)*5) * _rg.active_synths[i]->slope_normalized);
    les303passes[_rg.active_synths[i]->l_index]->gain(2,1.0-_rg.active_synths[i]->slope_normalized);

    //mixle303ffilterzVknobs[2]->gain(0.1 + ((gg.le303filterzreso/127.0)*5) * _rg.active_synths[i]->slope_normalized);
    
    //almost immediate since liner_on just set it few micro seconds before;
    // but enough to be audible ;)
    //_mx.set_303_wetness(_rg.active_synths[i]->l_index,gg.le303filterzwet/127.0); 
    _rg.active_synths[i]->sloper_step++;
  }
}

void Filter303MenuRouter::filter_knob_freq(){
  mc.navrange = 127;
  CutOffTweak_ctl(mc.sublevels[3]);
}

void Filter303MenuRouter::filter_knob_res(){
  mc.navrange = 127;
  ResoTweak_ctl(mc.sublevels[3]);
}

void Filter303MenuRouter::filter_knob_low(){
      gg.mixle303ffilterzVknobs[0] = mc.sublevels[3];
      gg.le303filterzgainz[0] = gg.mixle303ffilterzVknobs[0];
    }

void Filter303MenuRouter::filter_knob_band(){
      gg.mixle303ffilterzVknobs[1] = mc.sublevels[3];
      gg.le303filterzgainz[1] = gg.mixle303ffilterzVknobs[1];
    }

void Filter303MenuRouter::filter_knob_high(){
      gg.mixle303ffilterzVknobs[2] = mc.sublevels[3];
      gg.le303filterzgainz[2] = gg.mixle303ffilterzVknobs[2];
    }

void Filter303MenuRouter::filter_knob_wet(){
      mc.navrange = 127;
      gg.le303filterzwet = mc.sublevels[3];
      _mx.apply_303_wet();
    }

void Filter303MenuRouter::filter_knob_preamp(){
      mc.navrange = 127;
      gg.preampleswaves = mc.sublevels[3];
      _mx.Wavespreamp303controls();
    }

void Filter303MenuRouter::le303filterVpanelAction() {
  if (mc.navlevel == 3) {
    mc.retroaction = mc.sublevels[2];
    mc.navrange = 127;
    if (!mc.temp_buff_armed) {
      set_filter_buff_temp();
      mc.temp_buff_armed = 1 ;
    }
    (filters_pointers[mc.sublevels[2]])();
    _mx.le303filtercontrols();
  }
  if (mc.navlevel > 3) {
    mc.temp_buff_armed = 0 ;
    dm.returntonav(2,7,mc.sublevels[2]);
  }
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
  if (mc.navlevel == 2) {
    mc.navrange = 7;
  }
  int slct = mc.sublevels[2];
  // fq
  if (slct == 0) {
    mc.sublevels[3] = gg.le303ffilterzVknobs[0];
    dm.canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
  }
  // res
  if (slct == 1) {
    mc.sublevels[3] = gg.le303ffilterzVknobs[1];
    dm.canvasBIG.drawCircle(centercirclex + 25, centercircley, knobradius - 2, SSD1306_WHITE);
  }
  /*
  // oct
  if (slct == 2) {
    mc.sublevels[3] = gg.le303ffilterzVknobs[2];
    dm.canvasBIG.drawCircle(centercirclex + 50, centercircley, knobradius - 2,
                        SSD1306_WHITE);
  }
  */
  // lp
  if (slct == 2) {
    mc.sublevels[3] = gg.mixle303ffilterzVknobs[0];
    dm.canvasBIG.drawRect(83, topwbarstart, wbarwidth - 4, totbartall, SSD1306_WHITE);
  }
  // bp
  if (slct == 3) {
    mc.sublevels[3] = gg.mixle303ffilterzVknobs[1];
    dm.canvasBIG.drawRect(100, topwbarstart, wbarwidth - 4, totbartall, SSD1306_WHITE);
  }
  // hp
  if (slct == 4) {
    mc.sublevels[3] = gg.mixle303ffilterzVknobs[2];
    dm.canvasBIG.drawRect(117, topwbarstart, wbarwidth - 4, totbartall, SSD1306_WHITE);
  }
  // wet
  if (slct == 5) {
    mc.sublevels[3] = gg.le303filterzwet;
    dm.canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall, wbarwidth2 - 4, SSD1306_WHITE);
  }

  if (slct == 6) {
    mc.sublevels[3] = gg.preampleswaves;
    dm.canvasBIG.setCursor(34, 0);
    dm.canvasBIG.print((char)9);
  }

  if (slct == 7) {
    mc.sublevels[3] = gg.period_303 ;
    dm.canvasBIG.setCursor(100, 8);
    dm.canvasBIG.print((char)9);
  }
}

void Filter303MenuRouter::set_filter_speed(){
  mc.navrange = 127;
  impulse_length_ctl((byte)mc.sublevels[3]);
  if (mc.navlevel > 3 ) dm.returntonav(2);
}

void Filter303MenuRouter::restore_from_temp() {
  for (int i=0; i<8; i++) {
    mc.sublevels[3] = self->filter_tmp_values[i];
    (filters_pointers[i])();
    _mx.le303filtercontrols();
    *self->filter_tmp_pointers[i] = self->filter_tmp_values[i] ;
  }
  mc.temp_buff_armed = 0 ;
}

void Filter303MenuRouter::set_filter_buff_temp() {
  for (int i=0; i<8; i++) {
    self->filter_tmp_values[i] = *self->filter_tmp_pointers[i] ;
  }
}

void Filter303MenuRouter::show(){
  le303filterVpanelAction();
  if (mc.navlevel == 2 && mc.temp_buff_armed) {
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
  dm.canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
  dm.canvasBIG.setCursor(centercirclex - knobradius + 4,  centercircley + knobradius + 4);
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
  dm.canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
  dm.canvasBIG.setCursor(centercirclex - knobradius + 1, centercircley + knobradius + 4);
  dm.canvasBIG.setTextSize(1);
  dm.canvasBIG.print("Res");
  dm.canvasBIG.setCursor(centercirclex - knobradius + 2, 25);
  dm.canvasBIG.print((gg.le303filterzreso/127.0)*5, 1);

  barsize = round(((gg.le303filterzgainz[0]/127.0) * (totbartall - 4)));
  dm.canvasBIG.drawRoundRect(81, topwbarstart, wbarwidth, totbartall, 2, SSD1306_WHITE);
  dm.canvasBIG.fillRect(81 + 2, (totbartall + topwbarstart - barsize - 2), wbarwidth - 4, barsize, SSD1306_WHITE);
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
  dm.canvastitle.print("Speed: ");
  dm.canvastitle.print(gg.period_303);
  le303filterVpanelSelector();
  dm.dodisplay();
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
  if (mc.navlevel == 2) {
    mc.navrange = 8;
  }
  if (mc.navlevel >= 3) {
    _mp3_actions[mc.sublevels[2]]();
    dm.returntonav(2,8,mc.sublevels[2]);
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
  dm.fillRect(ecart * (mc.sublevels[mc.navlevel])-3, startyp-2, ecart-1, startyp*1.5, SSD1306_INVERSE);
  dm.setCursor(0,20);
  dm.setTextSize(1);
  dm.setTextColor(SSD1306_INVERSE);
  dm.print(_legend[mc.sublevels[2]]);
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
  _route_nav[mc.navlevel-1]();
}

void SynthMenuRouter::route_navlevel_1(){
  synth_nav_zero();
}

void SynthMenuRouter::route_navlevel_2(){
  mc.retroaction = mc.sublevels[1];
  _nav_synth[mc.sublevels[1]]();
}

void SynthMenuRouter::displayoffsetwav() {
  dm.clear_3();
  if (mc.navlevel == 3) {
    mc.retroaction = mc.sublevels[2];
    mc.navrange = self->synth_params_count - 1;
    mc.sublevels[4] = gg.wave1offset[mc.oscillator];
  }
  if (mc.navlevel == 4) {
    mc.navrange = 127;
    mc.retroaction = mc.sublevels[3];
    gg.wave1offset[mc.oscillator] = mc.sublevels[4];
    for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
      waveforms1[i + (mc.oscillator * SYNTH_LINERS_COUNT)]->offset((float)(((64.0 - gg.wave1offset[mc.oscillator]) / 64.0)));
      FMwaveforms1[i + (mc.oscillator * SYNTH_LINERS_COUNT)]->offset((float)(((64.0 - gg.wave1offset[mc.oscillator]) / 64.0)));
    }
  }
  if (mc.navlevel >= 5) {
    dm.returntonav(3,self->synth_params_count-1,mc.sublevels[3]);
    return;
  }
  dm.setTextSize(1);
  dm.setCursor(80, 8);
  dm.print((float)(((64.0 - gg.wave1offset[mc.oscillator]) / 64.0)));
  draw_synth_params();
  dm.dodisplay();
}

void SynthMenuRouter::freqbars_panel_selector() {
  if (mc.navlevel == 4) {
    mc.retroaction = mc.sublevels[3];
    switch (mc.sublevels[4]){
      case 0:
        dm.fillRect(62, 0, 16, 16, SSD1306_INVERSE);
        self->unit = (int)gg.wavesfreqs[mc.oscillator];
        mc.sublevels[5]=self->unit;
      break;
      case 1:
        dm.fillRect(88, 0, 12, 16, SSD1306_INVERSE);
        self->tenth = ((int)(gg.wavesfreqs[mc.oscillator]* 10)) % 10;
        mc.sublevels[5]=self->tenth;
      break;
      case 2:
        dm.fillRect(100, 0, 12, 16, SSD1306_INVERSE);
        self->hundredth = ((int)(gg.wavesfreqs[mc.oscillator] * 100)) % 10;
        mc.sublevels[5]=self->hundredth;
      break;
    }
  dm.display();
  }
}

void SynthMenuRouter::freqbars_panel_action() {
  mc.navrange = 9;
  switch (mc.sublevels[4]){
    case 0:
      self->unit = mc.sublevels[5];
    break;
    case 1:
      self->tenth = mc.sublevels[5];
    break;
    case 2:
      self->hundredth = mc.sublevels[5];
    break;
  }
  gg.wavesfreqs[mc.oscillator] = (float)(self->unit + self->tenth * 0.1f + self->hundredth * 0.01f);
}

void SynthMenuRouter::displayfreqbars(){
  dm.clear_3();
  dm.setTextSize(2);
  dm.setCursor(65, 0);
  dm.println(gg.wavesfreqs[mc.oscillator]);
  draw_synth_params();
  dm.dodisplay();
}

void SynthMenuRouter::freqbars_panel() {
  if (mc.navlevel >= 4) {
    mc.retroaction = mc.sublevels[3];
    if (mc.navlevel == 4) {
      mc.navrange = 2;
    }
    if (mc.navlevel == 5) {
      mc.retroaction = mc.sublevels[4];
      freqbars_panel_action();
    }
    if (mc.navlevel >= 6) {
      dm.returntonav(4,9,mc.sublevels[4]);
    }
  }
  displayfreqbars();
  freqbars_panel_selector();
  if (mc.navlevel == 3) {
    mc.retroaction = mc.sublevels[2];
    mc.navrange = self->synth_params_count - 1;
  }
}

void SynthMenuRouter::displayphasebars() {
  dm.clear_3();
  if (mc.navlevel == 3) {
    mc.retroaction = mc.sublevels[2];
    mc.navrange = self->synth_params_count - 1;
    mc.sublevels[4] = gg.phaselevelsL[mc.oscillator];
  }
  if (mc.navlevel >= 4) {
    if (mc.navlevel == 4) {
      mc.navrange = 127;
      mc.retroaction = mc.sublevels[3];
      gg.phaselevelsL[mc.oscillator] = mc.sublevels[4];
      setphaselevel();
    }
    if (mc.navlevel >= 5) {
      setphaselevel();
      dm.returntonav(3,self->synth_params_count-1,mc.sublevels[3]);
    }
  }
  draw_synth_params();
  dm.setCursor(80, 0);
  dm.setTextSize(2);
  dm.print(lround((gg.phaselevelsL[mc.oscillator]/127.0)*360));
  dm.dodisplay();
}

void SynthMenuRouter::displayModulatedbool() {
  char modulation_labels[4][7] = {"Off", "Freq", "Phase", "Ampl"};
  draw_synth_params();
  dm.dodisplay();
  dm.setCursor(64, 0);
  dm.setTextSize(2);
  dm.println(modulation_labels[gg.FMmodulated[mc.oscillator]]);
  draw_synth_params();
  dm.dodisplay();
}

void SynthMenuRouter::setfmtophase() {
  for (byte i = 0; i < SYNTH_LINERS_COUNT; i++) {
    //phaseModulation should be based on lfo level
    FMwaveforms1[i + (mc.oscillator * SYNTH_LINERS_COUNT)]->phaseModulation(180);
  }
}

void SynthMenuRouter::setfmtofreq() {
  for (byte i = 0; i < SYNTH_LINERS_COUNT; i++) {
    //phaseModulation should be based on lfo level
    FMwaveforms1[i + (mc.oscillator * SYNTH_LINERS_COUNT)]->frequencyModulation(10);
  }
}

void SynthMenuRouter::wavelineModulatedbool() {
  dm.clear_3();
  if (mc.navlevel == 3) {
    mc.retroaction = mc.sublevels[2];
    mc.navrange = self->synth_params_count - 1;
  }
  if (mc.navlevel == 4) {
    mc.navrange = 3;
    mc.retroaction = mc.sublevels[3];
    gg.FMmodulated[mc.oscillator] = mc.sublevels[4];
  }
  if (mc.navlevel > 4) {
    setwavetypefromlist();
    dm.returntonav(3,self->synth_params_count-1,mc.sublevels[3]);
  }
  displayModulatedbool();
}

void SynthMenuRouter::displaywaveformicon(){
  dm.clear_3();
  if (mc.navlevel == 3) {
    mc.retroaction = mc.sublevels[2];
    mc.navrange = self->synth_params_count - 1;
    mc.sublevels[4] = gg.Waveformstyped[mc.oscillator];
  }
  if (mc.navlevel == 4) {
    mc.navrange = 11;
    gg.Waveformstyped[mc.oscillator] = mc.sublevels[4];
    mc.retroaction = mc.sublevels[3];
  }
  if (mc.navlevel > 4) {
    setwavetypefromlist();
    if (gg.Waveformstyped[mc.oscillator] == 11) {
      gg.mixlevelsL[mc.oscillator] = 0;
      _mx.setwavemixlevel();
    }
    dm.returntonav(3,self->synth_params_count-1,mc.sublevels[3]);
    return;
  }



  dm.drawBitmap(74, 20, _img[mc.sublevels[4]], 32, 32, SSD1306_WHITE);
  dm.setTextSize(1);
  dm.setTextColor(SSD1306_WHITE);
  dm.setCursor(64, 0);
  dm.println(lelabelw[mc.sublevels[4]]);
  dm.setCursor(120, 57);
  dm.print(mc.oscillator + 1);
  draw_synth_params();
  dm.dodisplay();
}

void SynthMenuRouter::displayLFOpanel() {
  dm.clear_3();
  if (mc.navlevel == 3 ) {
    mc.retroaction = mc.sublevels[2];
    mc.navrange = self->synth_params_count - 1;
  }
  draw_synth_params();
    dm.dodisplay();
  if (mc.navlevel >= 4) {
    mc.sublevels[0] = 1;
    mc.sublevels[1] = mc.oscillator;
    mc.sublevels[2] = 0;
    dm.returntonav(mc.navlevel-2,_lf.sizeofLFOlabels - 1,0);
  }
}

void SynthMenuRouter::go_previous(){
  dm.clear_3();
  if (mc.navlevel == 3) {
    mc.retroaction = mc.sublevels[2];
    mc.navrange = self->synth_params_count - 1;
  }

  if (mc.navlevel >= 4) {
    if (mc.oscillator-1 < 0)
      mc.oscillator = 2 ;
    else
      mc.oscillator = mc.oscillator-1;

    mc.sublevels[2] = mc.oscillator ;
    dm.returntonav(mc.navlevel-1,self->synth_params_count-1,mc.sublevels[3]);
    return;
  }
  draw_synth_params();
  dm.dodisplay();
}

void SynthMenuRouter::go_next(){
  dm.clear_3();
  if (mc.navlevel == 3) {
    mc.retroaction = mc.sublevels[2];
    mc.navrange = self->synth_params_count - 1;
  }
  if (mc.navlevel >= 4) {
    mc.oscillator = (mc.oscillator+1)%3;
    mc.sublevels[2] = mc.oscillator ;
    dm.returntonav(mc.navlevel-1,self->synth_params_count-1,mc.sublevels[3]);
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
  mc.retroaction = mc.sublevels[3];
  _synth_params[mc.sublevels[3]]();
}

void SynthMenuRouter::draw_synth_params() {
  const char* wavelineslabels[] = {
      "Type", "Mod", "LFO", "Freq", "Offset", "Phase", "<-  ", "  ->"};
  dm.main_panel(wavelineslabels,3,self->synth_params_count);
  dm.canvasBIG.setCursor(120, 57);
  dm.canvasBIG.print(mc.oscillator + 1);
}

void SynthMenuRouter::dolistsyntmenu() {
  const char* synthmenulabels[] = {"Synths", "Mixer", "ADSR", "MP3 Player", "Filter", "Glider"};
  dm.main_panel(synthmenulabels,1,SN_MENU_LABELS_COUNT);
}

void SynthMenuRouter::synths_switcher(){
  String titled = "Waveline ";
  mc.oscillator = mc.sublevels[2]%OSCS_COUNT;
  String synth_num = mc.oscillator + 1 ;
  mc.navrange = OSCS_COUNT-1;
  String leprintlabel = titled + synth_num ;
  wavelinesBG();
  mc.sublevels[3] = 0;
  dm.fillRect(0+(mc.oscillator%2)*64, 16+(24*(mc.oscillator/2)), 64, 24, SSD1306_INVERSE);
  dm.printlabel((char*)leprintlabel.c_str());
  dm.display();
}

void SynthMenuRouter::wavesline_selector(){
  mc.retroaction = mc.sublevels[mc.navlevel-2] ;
  _waveliners[mc.navlevel-2]();
}

void SynthMenuRouter::synth_nav_zero() {
  mc.navrange = self->home_navrange;
  dm.clean_title_2_1();
  dolistsyntmenu();
  mc.retroaction = mc.sublevels[1] ;
  dm.dodisplay();
}

void SynthMenuRouter::plug_no_waves(){
  gg.mixlevelsL[mc.oscillator] = 0;
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    wavelinescords[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    stringcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    drumcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    FMwavecords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    MDdrumcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    MDwavecords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    MDstringcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    modulatecords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
  }
}

void SynthMenuRouter::plug_waves(){
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    FMwavecords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    stringcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    modulatecords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    MDdrumcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    MDstringcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    MDwavecords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    drumcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    wavelinescords[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->connect();
    if (gg.Waveformstyped[mc.oscillator] == WAVEFORM_ARBITRARY) {
      waveforms1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->arbitraryWaveform(gg.arbitrary_waveforms[mc.oscillator],gg.arbitrary_maxF[mc.oscillator]);
    }
    waveforms1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->begin(lesformes[gg.Waveformstyped[mc.oscillator]]);
  }
}

void SynthMenuRouter::plug_moded_waves(){
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    wavelinescords[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    modulatecords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    MDdrumcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    MDstringcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    stringcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    drumcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    MDwavecords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    FMwavecords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->connect();
    if (gg.Waveformstyped[mc.oscillator] == WAVEFORM_ARBITRARY) {
      FMwaveforms1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->arbitraryWaveform(gg.arbitrary_waveforms[mc.oscillator],gg.arbitrary_maxF[mc.oscillator]);
    }
    FMwaveforms1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->begin(lesformes[gg.Waveformstyped[mc.oscillator]]);
  }
  _lf.restartLFO(mc.oscillator%OSCS_COUNT);
}

void SynthMenuRouter::plug_ampl_moded_waves(){
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    wavelinescords[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    MDdrumcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    MDstringcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    stringcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    drumcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    FMwavecords1[i + (mc.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
    MDwavecords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->connect();
    modulatecords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->connect();
    if (gg.Waveformstyped[mc.oscillator] == WAVEFORM_ARBITRARY) {
      waveforms1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->arbitraryWaveform(gg.arbitrary_waveforms[mc.oscillator],gg.arbitrary_maxF[mc.oscillator]);
    }
    waveforms1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->begin(lesformes[gg.Waveformstyped[mc.oscillator]]);
  }
  _lf.restartLFO(mc.oscillator%OSCS_COUNT);
}

void SynthMenuRouter::plug_strings_waves(){
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    wavelinescords[i + (mc.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
    drumcords1[i + (mc.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
    FMwavecords1[i + (mc.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
    modulatecords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    MDwavecords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    MDdrumcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    MDstringcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    stringcords1[i + (mc.oscillator * SYNTH_LINERS_COUNT)]->connect();
  }
}

void SynthMenuRouter::plug_ampl_moded_strings(){
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    wavelinescords[i + (mc.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
    drumcords1[i + (mc.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
    FMwavecords1[i + (mc.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
    stringcords1[i + (mc.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
    MDwavecords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    MDdrumcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    MDstringcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->connect();
    modulatecords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->connect();
  }
}

void SynthMenuRouter::plug_drum_waves(){
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    wavelinescords[i + (mc.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
    stringcords1[i + (mc.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
    FMwavecords1[i + (mc.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
    modulatecords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    MDwavecords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    MDdrumcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    MDstringcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    drumcords1[i + (mc.oscillator * SYNTH_LINERS_COUNT)]->connect();
  }
}

void SynthMenuRouter::plug_ampl_moded_drums(){
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    wavelinescords[i + (mc.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
    stringcords1[i + (mc.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
    FMwavecords1[i + (mc.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
    drumcords1[i + (mc.oscillator * SYNTH_LINERS_COUNT)]->disconnect();
    MDwavecords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    MDstringcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->disconnect();
    //TODO: apply to other types too
    modulatecords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->connect();
    MDdrumcords1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->connect();
  }
}

void SynthMenuRouter::no_modulation(){
  byte letype = gg.Waveformstyped[mc.oscillator];
  if (letype < 9) {
    gg.audio_obj_type[mc.oscillator] = 1; //       9*4 + drums *2 + string *2 + off
    plug_waves();
  }
  else if (letype == 9) {
    gg.audio_obj_type[mc.oscillator] = 3 ;
    plug_drum_waves();
  }
  else if (letype == 10) {
    gg.audio_obj_type[mc.oscillator] = 4 ;
    plug_strings_waves();
  }
}

void SynthMenuRouter::freq_modulation(){
  byte letype = gg.Waveformstyped[mc.oscillator];
  if (letype < 9) {
    gg.audio_obj_type[mc.oscillator] = 2;
    plug_moded_waves();
  }
  //no freq modulation on strings or drums
  else if (letype == 9) {
    gg.audio_obj_type[mc.oscillator] = 3;
    plug_drum_waves();
  }
  else if (letype == 10) {
    gg.audio_obj_type[mc.oscillator] = 4;
    plug_strings_waves();
  }
}

void SynthMenuRouter::phase_modulation(){
  byte letype = gg.Waveformstyped[mc.oscillator];
  if (letype < 9) {
      gg.audio_obj_type[mc.oscillator] = 2;
      plug_moded_waves();
    }
    //no phase modulation on strings or drums
    else if (letype == 9) {
      gg.audio_obj_type[mc.oscillator] = 3;
      plug_drum_waves();
    }
    else if (letype == 10) {
      gg.audio_obj_type[mc.oscillator] = 4;
      plug_strings_waves();
  }
}

void SynthMenuRouter::amplitude_modulation(){
  byte letype = gg.Waveformstyped[mc.oscillator];
  if (letype < 9) {
    gg.audio_obj_type[mc.oscillator] = 1;
    plug_ampl_moded_waves();
  }
  else if (letype == 9) {
    // amplitude modulated drum
    gg.audio_obj_type[mc.oscillator] = 3;
    //36 + (bool)gg.FMmodulated[mc.oscillator];
    plug_ampl_moded_drums();
  }
  else if (letype == 10) {
    // amplitude modulated string
    gg.audio_obj_type[mc.oscillator] = 4;
    plug_ampl_moded_strings();
  }
  _lf.restartLFO(mc.oscillator%OSCS_COUNT);
}

void SynthMenuRouter::setwavetypefromlist() {
  _tt.stopallnotes();
  AudioNoInterrupts();
  byte letype = gg.Waveformstyped[mc.oscillator];
  if (letype == 11) {
    plug_no_waves();
    gg.audio_obj_type[mc.oscillator] = 0;
    AudioInterrupts();
    _mx.setwavemixlevel();
    return;
  }
  (modulation_pointers[gg.FMmodulated[mc.oscillator]])();
  AudioInterrupts();
  _mx.setwavemixlevel();
}

void SynthMenuRouter::setphaselevel() {
  AudioNoInterrupts();
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    waveforms1[i + (SYNTH_LINERS_COUNT * mc.oscillator)]->phase((int)((gg.phaselevelsL[mc.oscillator]/ 127.0) * 360.0));
  }
  AudioInterrupts();
}

void (*SynthMenuRouter::_nav_synth[SN_MENU_LABELS_COUNT])() = {&wavesline_selector,&_mx.show, &_ad.show, &_mp.mp3_player_panel, &_ft.show,&_gd.show};
