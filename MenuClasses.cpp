#include "MenuClasses.h"
#include "pads.h"
#include <Bounce.h>
#include "SamplerMenu.h"
#include "SynthMenu.h"
#include "PresetsMenu.h"
#include "WaveEditorMenu.h"
#include "WaveFormer.h"
#include "FxMenu.h"
#include "SettingsMenu.h"
#include "SongsMenu.h"
#include "LfoMenu.h"
#include "Patterns.h"
#include "Functions.h"
#include "Presets.h"
#include <Wire.h>

extern Bounce clicked;
extern Bounce Backb;

void cancel_pushed_ctl(byte);
void validate_pushed_ctl(byte);

void SectionHolder::set_home(void (*_cb)()){
    _home = _cb;
}

DisplayManager* DisplayManager::self = nullptr;

DisplayManager::DisplayManager() : Adafruit_SSD1306(128, 64, &Wire2, -1){self = this;};

GFXcanvas1 DisplayManager::canvasBIG(128, 64);
GFXcanvas1 DisplayManager::canvastitle(128, 16);
Encoder DisplayManager::myEnc(30, 31);

void DisplayManager::display_home() {
    if (ILI_128x64) {
        Serial.println("ILI_128x64 detected");
    }
}



void DisplayManager::returntonav(byte lelevel, byte lanavrange, byte t_vraipos) {
  mc.navlevel = lelevel;
  mc.rota_true_pos = t_vraipos;
  myEnc.write(mc.rota_true_pos * 4);
  mc.navrange = lanavrange;
  if (mc.navlevel) show();
}

void DisplayManager::dodisplayplayhead() {
  canvasBIG.drawLine(mc.tickposition * 4, 0, mc.tickposition * 4, 64, SSD1306_INVERSE);
}

void DisplayManager::initializelapleasewaitarray() {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 32; j++) {
      bb.pleasewaitarray[i][j] = (char)'\0';
    }
  }
}

void DisplayManager::shiftlapleasewaitarray() {
  for (int i = 9; i > 0; i--) {
    setlapleasewaitarray(i, (char *)bb.pleasewaitarray[i - 1]);
  }
}

void DisplayManager::setlapleasewaitarray(int consoleline, char *lemsg) {
  for (int i = 0; i < 32; i++) {
    bb.pleasewaitarray[consoleline][i] = lemsg[i];
  }
}

void DisplayManager::pleasewait(float lewait, float letotwait) {
  clearDisplay();
  setTextSize(2);
  setCursor(6, 0);
  print("Processing");
  if (letotwait > 0) {
    setCursor(4, 20);
    setTextSize(2);
    print("[");
    setTextSize(1);
    setCursor(7 + 4, 23);
    for (int i = 0; i < int(18.0 * (lewait / letotwait)); i++) {
      print("-");
    }
    setCursor(115, 20);
    setTextSize(2);
    print("]");
  }
  setCursor(20, 50);
  setTextSize(1);
  print("(Please Wait)");
  display();
}

void DisplayManager::pseudoconsole(const char *lemsg,bool new_lines) {
  if (new_lines) shiftconsolemsgarray();
  setleconsolemsg(0, (char *)lemsg);
  clearDisplay();
  setTextSize(1);
  setCursor(0, 0);
  for (int i = 0; i < 10; i++) {
    println((char *)bb.consolemsg[i]);
  }
  display();
}

void DisplayManager::initializeconsolemsg() {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 32; j++) {
      bb.consolemsg[i][j] = (char)'\0';
    }
  }
}

void DisplayManager::shiftconsolemsgarray() {
  for (int i = 9; i > 0; i--) {
    setleconsolemsg(i, (char *)bb.consolemsg[i - 1]);
  }
}

void DisplayManager::setleconsolemsg(int consoleline, char *lemsg) {
  for (int i = 0; i < 32; i++) {
    bb.consolemsg[consoleline][i] = lemsg[i];
  }
}

void DisplayManager::printnoteon(byte channel, byte data1, byte data2) {
  Serial.print("Note On, ch=");
  Serial.print(channel);
  Serial.print(", note=");
  Serial.print(data1);
  Serial.print(", velocity=");
  Serial.println(data2);
}

void DisplayManager::print_memory_usage(){
  if (Serial.available()) {
    char c = Serial.read();
    if ((c == 'r' || c == 'R')) {
      AudioProcessorUsageMaxReset();
      AudioMemoryUsageMaxReset();
      Serial.println("Reset all max numbers");
      }
    }
  // print a summary of the current & maximum usage
  Serial.print("CPU: ");
  Serial.print("all=");
  Serial.print(AudioProcessorUsage());
  Serial.print(",");
  Serial.print(AudioProcessorUsageMax());
  Serial.print("    ");
  Serial.print("Memory: ");
  Serial.print(AudioMemoryUsage());
  Serial.print(",");
  Serial.print(AudioMemoryUsageMax());
  Serial.println("    ");
}

void DisplayManager::doConfirmpanel(char *letitlemsg) {
  mc.navrange = 1;
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(1);
  // canvastitle.print((char*)text);
  canvastitle.print((char *)letitlemsg);
  canvasBIG.setTextSize(1);
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvasBIG.setCursor(20, 28);
  // canvasBIG.print((char*)text);
  canvasBIG.print("NO         YES");
  canvasBIG.drawRect(14 + mc.sublevels[mc.navlevel] * 66, 23,
                    23 + mc.sublevels[mc.navlevel] * 6, 17, SSD1306_WHITE);
  dm.dodisplay();
  display();
}

void DisplayManager::reinitsublevels(byte fromlei) {
  for (byte i = fromlei; i < 9; i++) {
    mc.sublevels[i] = 0;
  }
}


void DisplayManager::drawtransport() {
  // startxp= 0 ;
  int startyp = 8;
  // for (int i = 0 ; i < 8 ; i++ ) {
  int starx = 1;
  int ecart = 14;
  // canvasBIG.drawRoundRect(i*16, startyp-2, 16, 11, 2, SSD1306_WHITE);
  //}
  // cuestart
  canvasBIG.setCursor(starx + 1, startyp);
  canvasBIG.drawLine(starx + 2, startyp + 1, starx + 2, startyp + 5,
                     SSD1306_WHITE);
  canvasBIG.print(">");
  // exit
  canvasBIG.setCursor(starx + ecart * 7, startyp);
  canvasBIG.print((char)8);
  // backward
  canvasBIG.setCursor(starx + ecart * 1, startyp);
  canvasBIG.print((char)27);
  // canvasBIG.setCursor(5+48,55);
  // stop
  canvasBIG.fillRect(starx + ecart * 2, startyp + 1, 5, 5, SSD1306_WHITE);
  // play
  canvasBIG.setCursor(starx + ecart * 3, startyp);
  canvasBIG.print((char)16);
  // forward
  canvasBIG.setCursor(starx + ecart * 4, startyp);
  canvasBIG.print((char)26);
  // record
  canvasBIG.setCursor(starx + ecart * 5, startyp);
  canvasBIG.print((char)4);
  // music
  canvasBIG.setCursor(starx + ecart * 6, startyp + 1);
  canvasBIG.print((char)14);
}
void DisplayManager::setupscreen(){
  if (ILI_128x64) {
      _setupscreen_ILI();
  }
}
void DisplayManager::printassignedmidi(int lemidiassknob) {
  canvasBIG.setCursor(0, 0);
  canvasBIG.print((char *)ctl[lemidiassknob].name);
}
void DisplayManager::displayleBGimg(const unsigned char *img) {_displayleBGimg(img);}

void DisplayManager::printlabel(char *toprint) {
    setTextSize(2);
    setTextColor(SSD1306_WHITE);
    setCursor(0, 0);
    println(toprint);
}


void DisplayManager::evalrota() {
  rota_enc_new_pos = myEnc.read();
  if (rota_enc_new_pos != rota_old_Pos) {
    rota_enc_count++;
  }

  if (rota_enc_count >= 4) {
    rota_old_Pos = rota_enc_new_pos;
    rota_enc_count = 0;
    mc.rota_true_pos = rota_enc_new_pos / 4;
    if (mc.rota_true_pos > mc.navrange) {
      mc.rota_true_pos = 0;
      myEnc.write(0);
    }
    if (mc.rota_true_pos < 0) {
      mc.rota_true_pos = mc.navrange;
      myEnc.write(mc.navrange * 4);
    }
  }

  if (mc.rota_true_pos != rota_old_vrai_Pos) {
    rota_old_vrai_Pos = mc.rota_true_pos;
    mc.sublevels[mc.navlevel] = mc.rota_true_pos;
    if (!mc.navlevel) {
      dm.displaymenu();
      return;
    }
    dm.show();
    printit();
  }
}
void DisplayManager::printit() {

  Serial.print(" mc.navrange: ");
  Serial.print(mc.navrange);
  Serial.print(" mc.navlevel: ");
  Serial.print(mc.navlevel);
  Serial.print(" sublevel[");
  Serial.print(mc.navlevel);
  Serial.print("]:");
  Serial.println(mc.sublevels[mc.navlevel]);
  Serial.println(" ");
  Serial.print(" s0 = ");
  Serial.print(mc.sublevels[0]);
  Serial.print(" s1 = ");
  Serial.print(mc.sublevels[1]);
  Serial.print(" s2 = ");
  Serial.print(mc.sublevels[2]);
  Serial.print(" s3 = ");
  Serial.print(mc.sublevels[3]);
  Serial.print(" s4 = ");
  Serial.print(mc.sublevels[4]);
  Serial.print(" s5 = ");
  Serial.println(mc.sublevels[5]);

}

void DisplayManager::evalinputs() {

  clicked.update();
  if (!MULTIPLEXED_PADS) {
    Backb.update();
  }

  bool backed = false;
  backed = Padded.get_back();

  if (backed || (!MULTIPLEXED_PADS && Backb.fallingEdge()))  {
    cancel_pushed_ctl(0);
  }
  if (clicked.fallingEdge()) {
    validate_pushed_ctl(0);
    //printit();
  }
}

void DisplayManager::displaymenu() {
  char menus_lbl[10][11] = {"WaveSynth", "LFOs", "CoolEditor", "Song", "Pattern", "Settings",
              "MainFX", "Sampler", "Waveformer", "Presets"};
  if (mc.navlevel == 0) {
      mc.previousnavlevel = 0;
      mc.navrange = 9;
      displayleBGimg(menuBG);
  }
  drawRoundRect(5 + (mc.sublevels[0]%5)*24, 17+((mc.sublevels[0]/5)*24), 21, 21, 3, SSD1306_WHITE);
  printlabel(menus_lbl[mc.sublevels[0]]);
  display();
}

void DisplayManager::main_panel(const char* const* menulabels, int lvl, int menu_lbls_count) {
  if ( mc.navlevel == lvl ) mc.navrange = menu_lbls_count-1;
  byte startx = 5;
  byte starty = 16;
  char *textin = (char *)menulabels[mc.sublevels[lvl]];
  //dm.clean_title_2_1();
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(2);
  canvastitle.println(textin);

  for (int i = 0; i < menu_lbls_count - 1 - (mc.sublevels[lvl]); i++) {
    canvasBIG.setCursor(startx, starty + ((i)*10));
    canvasBIG.println(menulabels[mc.sublevels[lvl] + 1 + i]);
  }
  for (int i = 0; i < mc.sublevels[lvl]; i++) {
    canvasBIG.setCursor(startx, (10 * (menu_lbls_count - mc.sublevels[lvl])) + 6 + ((i)*10));
    canvasBIG.println(menulabels[i]);
  }
}

void DisplayManager::sub_menu( const char* lbls[4], const char* vals[4], byte vals_x ){
  clearDisplay();
  canvasBIG.fillScreen(0);
  canvasBIG.setTextSize(1);
  for (int i = 0; i < 4; i++) {
    canvasBIG.setCursor(0, 16 + 12*i);
    canvasBIG.print(lbls[i]);
    canvasBIG.print(vals[i]);
  }
  dodisplay();
  fillRoundRect(vals_x,15+12*mc.sublevels[2], 6+strlen(vals[mc.sublevels[2]])*6, 10, 2, SSD1306_INVERSE);
  display();
}

void DisplayManager::sub_menu( const char* lbls[4], byte vals[4], byte vals_x ){
  clearDisplay();
  canvasBIG.fillScreen(0);
  canvasBIG.setTextSize(1);
  for (int i = 0; i < 4; i++) {
    canvasBIG.setCursor(0, 16 + 12*i);
    canvasBIG.print(lbls[i]);
    canvasBIG.print(vals[i]);
  }
  dodisplay();
  fillRoundRect(vals_x,15+12*mc.sublevels[2], 23, 10, 2, SSD1306_INVERSE);
  display();
}

void DisplayManager::display_oscilloscope(){
  dm.clear_buffs();
  for (int x = 0; x < 128; x++) {

    int index = (mc.queue_shift + x) & 127;

    //int y = map(bb.rolling_queue_buff[index], -32768, 32767, 63, 0);
    //dirty scalling
    int y = map(bb.rolling_queue_buff[index], -32768/4, 32767/4, 0, 63);

    if (x > 0)
        canvasBIG.drawLine(
            x - 1, mc.last_y_peak,
            x, y,
            SSD1306_WHITE);

    mc.last_y_peak = y;
  }
  clearDisplay();

  dm.dodisplay();
}

void DisplayManager::stop_spectro(){
  queue1.end();
  queue1.clear();
}

void DisplayManager::start_spectro(){
  queue1.begin();
}

void DisplayManager::oscilloscope_loop() {
    if (!mc.showing_oscilloscope) return;
    while (queue1.available()) {

        int16_t *samples = queue1.readBuffer();

        for (int i = 0; i < 128; i += gg.oscilloscope_tscale) {

            bb.rolling_queue_buff[mc.queue_shift] = samples[i];
            mc.queue_shift = (mc.queue_shift + 1) & 127;
        }

        queue1.freeBuffer();
    }

    if (mc.frameTimer >= gg.osc_framerate) {

        self->display_oscilloscope();

        mc.frameTimer = 0;
    }
}

void DisplayManager::UpdateSpectrum(){
  if (!mc.showing_eq || !fft256.available())
      return;
  for (int i = 0; i < NUM_BARS; i++) {
        float level = fft256.read(i + 1);
        level *= fftGain[i];
        // simple smoothing
        eqRawBars[i] = eqRawBars[i] * 0.75f + level * 0.25f;
        int h = eqRawBars[i] * 80.0f;
        if (h > 63) h = 63;
        if (h < 0)  h = 0;
        eqBars[i] = h;
    }
    DrawSpectrum64();
}

void DisplayManager::DrawSpectrum64(){
    clearDisplay();

    for (int i = 0; i < 64; i++)
    {
        int h = eqBars[i];
        drawFastVLine(
            i * 2,
            SCREEN_HEIGHT - h,
            h,
            WHITE);
    }

    display();
}
void DisplayManager::clear_buffs(){
            canvasBIG.fillScreen(SSD1306_BLACK);
            canvastitle.fillScreen(SSD1306_BLACK);
        }
void DisplayManager::clear_buffs_1_1(){
            clear_buffs();
            canvastitle.setCursor(0, 0);
            canvastitle.setTextSize(1);
            canvasBIG.setTextSize(1);
        }
void DisplayManager::clear_buffs_2_1(){
            clear_buffs();
            canvastitle.setCursor(0, 0);
            canvastitle.setTextSize(2);
            canvasBIG.setTextSize(1);
        }
void DisplayManager::clear_buffs_2_2(){
            clear_buffs();
            canvastitle.setCursor(0, 0);
            canvastitle.setTextSize(2);
            canvasBIG.setTextSize(2);
        }
void DisplayManager::clear_3(){
            clear_buffs();
            clearDisplay();
        }

void DisplayManager::clean_title_2(){
            clear_3();
            canvastitle.setCursor(0, 0);
            canvastitle.setTextSize(2);
        }
void DisplayManager::clean_title_2_1(){
            clear_3();
            canvastitle.setCursor(0, 0);
            canvastitle.setTextSize(2);
            canvasBIG.setTextSize(1);
        }
void DisplayManager::clean_title_1_1(){
            clear_3();
            canvastitle.setCursor(0, 0);
            canvastitle.setTextSize(1);
            canvasBIG.setTextSize(1);
        }
void DisplayManager::clean_title_1_2(){
            clear_3();
            canvastitle.setCursor(0, 0);
            canvastitle.setTextSize(1);
            canvasBIG.setTextSize(2);
        }
void DisplayManager::clean_title_2_2(){
            clear_3();
            canvastitle.setCursor(0, 0);
            canvastitle.setTextSize(2);
            canvasBIG.setTextSize(2);
        }
void DisplayManager::clean_title_1(){
            clear_3();
            canvastitle.setCursor(0, 0);
            canvastitle.setTextSize(1);
        }

void DisplayManager::show(){
            root_route[mc.sublevels[0]]();
        }

void (*DisplayManager::root_route[10])() = {&_sn.show,&_lf.show,&_rd.show,&_sg.show,&_pt.show,
                                    &_st.show,&_fx.MainFxPanel,&_sp.show,&_wf.show,&_ps.show};


void DisplayManager::_displayleBGimg(const unsigned char *img) {
            clearDisplay();
            drawBitmap(0, 0, img, 128, 64, SSD1306_WHITE);
        }

void DisplayManager::_setupscreen_ILI() {
    if (!begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("Screen SSD1306 allocation failed"));
        return;
    }
    display();
    setCursor(0, 0);
    setTextSize(1.5);
    setTextColor(SSD1306_WHITE);
    clearDisplay();
}

void DisplayManager::dodisplay() {
  drawBitmap(0, 0, canvasBIG.getBuffer(), 128, 64, SSD1306_WHITE);
  drawBitmap(0, 0, canvastitle.getBuffer(), 128, 16, SSD1306_WHITE);
  display();
}

extern DisplayManager dm ;

GlobalMixer* GlobalMixer::self = nullptr;

GlobalMixer::GlobalMixer(){
    self = this;
    self->home_navrange=11;
    self->relative_navlevel=2;
    self->max_navlevel=5;
    self->sublevels_address={0,1,0};
    wmixer_tmp_pointers[0]  = &gg.mixlevelsM[0];
    wmixer_tmp_pointers[1]  = &gg.mixlevelsM[1];
    wmixer_tmp_pointers[2]  = &gg.mixlevelsM[2];
    wmixer_tmp_pointers[3]  = &gg.WetMixMasters[1];
    wmixer_tmp_pointers[4]  = &gg.WetMixMasters[2];
    wmixer_tmp_pointers[5]  = &gg.WetMixMasters[3];
    wmixer_tmp_pointers[6]  = &gg.wetins[0];
    wmixer_tmp_pointers[7]  = &gg.wetins[1];
    wmixer_tmp_pointers[8]  = &gg.wetins[2];
    wmixer_tmp_pointers[9]  = &gg.mixlevelsL[0];
    wmixer_tmp_pointers[10] = &gg.mixlevelsL[1];
    wmixer_tmp_pointers[11] = &gg.mixlevelsL[2];

    wmixer_tmp_values[0]  = gg.mixlevelsM[0];
    wmixer_tmp_values[1]  = gg.mixlevelsM[1];
    wmixer_tmp_values[2]  = gg.mixlevelsM[2];
    wmixer_tmp_values[3]  = gg.WetMixMasters[1];
    wmixer_tmp_values[4]  = gg.WetMixMasters[2];
    wmixer_tmp_values[5]  = gg.WetMixMasters[3];
    wmixer_tmp_values[6]  = gg.wetins[0];
    wmixer_tmp_values[7]  = gg.wetins[1];
    wmixer_tmp_values[8]  = gg.wetins[2];
    wmixer_tmp_values[9]  = gg.mixlevelsL[0];
    wmixer_tmp_values[10] = gg.mixlevelsL[1];
    wmixer_tmp_values[11] = gg.mixlevelsL[2];
    }

void GlobalMixer::show(){
      showmixerwaves();
    }

void GlobalMixer::showmixerwaves() {
      char masterfulllabels[12][12] = {
          "Master",     "Synth",      "Sampler",    "FX1",
          "FX2",        "FX3",        "Wet Synth",  "Wet Sampler", "Wet Other",
          "Waveline 1", "Waveline 2", "Waveline 3" };
      mc.navrange = 11;
      byte slct = mc.sublevels[2];

      if (mc.navlevel == 2 && mc.temp_buff_armed) {
        restore_wmixer_from_temp();
      }

      if (slct < 3) {
        actionwmixerM(mc.sublevels[2]);
      }
      if (slct > 2 && slct < 6) {
        actionwet1mixer(mc.sublevels[2] - 3);
      }
      if (slct > 5 && slct < 9) {
        action_dry_mix(mc.sublevels[2] - 6);
      }
      if (slct > 8 && slct < 12) {
        actionwmixer(mc.sublevels[2] - 9);
      }

      dm.clearDisplay();
      dm.canvastitle.fillScreen(SSD1306_BLACK);
      dm.canvasBIG.fillScreen(SSD1306_BLACK);
      // dm.canvastitle.setCursor(70,0);
      dm.canvasBIG.setTextSize(1);
      dm.canvasBIG.setCursor(0, 0);
      dm.canvasBIG.print((char *)masterfulllabels[mc.sublevels[2]]);

      byte centercirclex;
      byte centercircley;
      byte xcentershifter;
      byte knobradius = 7;
      byte trianglepointx;
      byte trianglepointy;
      byte yshifter = 46;
      float coeffangle;
      xcentershifter = (knobradius * 2) + 6;

      for (int i = 0; i < 3; i++) {

        coeffangle = (6.2831 - (gg.mixlevelsM[i] / 127.0) * 6.2831) + 3.1416;
        centercirclex = knobradius + (xcentershifter * i);
        centercircley = 16 + knobradius;
        dm.canvastitle.setCursor(centercirclex - 5, 8);
        dm.canvastitle.setTextSize(1);
        dm.canvastitle.print((char)masterfulllabels[i][0]);
        dm.canvastitle.print((char)masterfulllabels[i][2]);
        dm.canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));
        dm.drawLine(centercirclex, centercircley, trianglepointx, trianglepointy, SSD1306_WHITE);
      }

      if (slct < 3) {
        centercirclex = knobradius + (xcentershifter * slct);
        dm.canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
        dm.canvastitle.setCursor(95, 0);
        dm.canvastitle.print((gg.mixlevelsM[slct] / 127.0) * 100.0, 1);
      }

      for (int i = 0; i < 3; i++) {
        coeffangle = (6.2831 - (gg.WetMixMasters[i + 1]/127.0) * 6.2831) + 3.1416;
        centercirclex = knobradius + (xcentershifter * i) + 5 + (xcentershifter * 3);
        centercircley = 16 + knobradius;
        dm.canvastitle.setCursor(centercirclex - 8, 8);
        dm.canvastitle.setTextSize(1);
        dm.canvastitle.print((char *)masterfulllabels[i + 3]);
        dm.canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));
        dm.drawLine(centercirclex, centercircley, trianglepointx, trianglepointy, SSD1306_WHITE);
      }

      if (slct > 2 && slct < 6) {
        centercirclex = knobradius + (xcentershifter * (slct - 3)) + 5 + (xcentershifter * 3);
        dm.canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
        dm.canvastitle.setCursor(95, 0);
        dm.canvastitle.print((gg.WetMixMasters[slct - 3 + 1]/127.0) * 100.0, 1);
      }

      for (int i = 0; i < 3; i++) {
        coeffangle = (6.2831 - (gg.wetins[i] / 127.0) * 6.2831) + 3.1416;
        centercirclex = knobradius + (xcentershifter * i);
        centercircley = yshifter + knobradius;
        dm.canvasBIG.setCursor(centercirclex - 7, centercircley - (2 + knobradius * 2));
        dm.canvasBIG.print("Ws");
        dm.canvasBIG.print(i);
        dm.canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));
        dm.drawLine(centercirclex, centercircley, trianglepointx, trianglepointy, SSD1306_WHITE);
      }

      if (slct > 5 && slct < 9) {
        centercirclex = knobradius + (xcentershifter * (slct - 6));
        dm.canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
        dm.canvastitle.setCursor(95, 0);
        dm.canvastitle.print((gg.wetins[slct - 6] / 127.0) * 100.0, 1);
      }

      for (int i = 0; i < OSCS_COUNT; i++) {
        coeffangle = (6.2831 - (gg.mixlevelsL[i]/127.0) * 6.2831) + 3.1416;
        centercirclex = knobradius + (xcentershifter * i) + 25 + (xcentershifter * 2);
        centercircley = yshifter + knobradius;
        dm.canvasBIG.setCursor(centercirclex - 5, centercircley - (2 + knobradius * 2));
        dm.canvasBIG.print("W");
        dm.canvasBIG.print(i);
        dm.canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));
        dm.drawLine(centercirclex, centercircley, trianglepointx, trianglepointy, SSD1306_WHITE);
      }

      if (slct > 8 && slct < 12) {
        centercirclex = knobradius + (xcentershifter * (slct - 9)) + 25 + (xcentershifter * 2);
        dm.canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
        dm.canvastitle.setCursor(95, 0);
        dm.canvastitle.print((gg.mixlevelsL[slct - 9]/127.0) * 100.0, 1);
      }
      dm.dodisplay();
    }

void GlobalMixer::set_masters_master() {
  // set mastermixlevel
  AudioShield.volume(gg.mixlevelsM[0] / 127.0);
  //ampL & R level should be 1.0 as they are used by queue recorder
  //ampL.gain(gg.mixlevelsM[0] / 127.0);
  //ampR.gain(gg.mixlevelsM[0] / 127.0);
}

void GlobalMixer::set_synth_master() {
  // set synth Main
  mixerWAll.gain(1, gg.mixlevelsM[1] / 127.0);
  mixerWAll.gain(0, gg.mixlevelsM[1] / 127.0);
}

void GlobalMixer::set_flash_master() {
  // set sampler main
  flashMastermix.gain(0, gg.mixlevelsM[2] / 127.0);
  flashMastermix.gain(1, gg.mixlevelsM[2] / 127.0);
}

void GlobalMixer::setmastersmixlevel(byte lebus) {
  //AudioNoInterrupts();
  if (lebus > 2) return;
  _master_mixers[lebus]();
  //AudioInterrupts();
}

void GlobalMixer::wetmixmastercontrols() {
  for (byte i = 0; i < 4; i++) {
    WetMixMasterL.gain(i, gg.WetMixMasters[i]/127.0);
    WetMixMasterR.gain(i, gg.WetMixMasters[i]/127.0);
  }
}

void GlobalMixer::restore_wmixer_from_temp() {
  for (int i=0; i<12; i++) {
    mc.sublevels[3] = self->wmixer_tmp_values[i];
    if (i < 3) {
      actionwmixerM(i);
    }
    if (i > 2 && i < 6) {
      actionwet1mixer(i - 3);
    }
    if (i > 5 && i < 9) {
      action_dry_mix(i - 6);
    }
    if (i > 8 && i < 12) {
      actionwmixer(i - 9);
    }
    *self->wmixer_tmp_pointers[i] = self->wmixer_tmp_values[i] ;
  }
  mc.temp_buff_armed = 0 ;
}

void GlobalMixer::set_303_wetness(byte line,float wetness){
  les303wet[line]->gain(0, wetness);
  les303wet[line]->gain(1, 1.0-wetness);
}

void GlobalMixer::apply_303_wet() {
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    set_303_wetness(i,gg.le303filterzwet / 127.0);
  }
}

void GlobalMixer::set_wmixer_buff_temp() {
  for (int i=0; i<12; i++) {
    self->wmixer_tmp_values[i] = *self->wmixer_tmp_pointers[i] ;
  }
}

void GlobalMixer::set_synth_wet() {
  MasterL1.gain(2, gg.wetins[0] / 127.0);
  MasterR1.gain(2, gg.wetins[0] / 127.0);
  FXBusL.gain(2, 1 - (gg.wetins[0] / 127.0));
  FXBusR.gain(2, 1 - (gg.wetins[0] / 127.0));
}

void GlobalMixer::set_flash_wet() {
  MasterL1.gain(3, gg.wetins[1] / 127.0);
  MasterR1.gain(3, gg.wetins[1] / 127.0);
  FXBusL.gain(1, 1 - (gg.wetins[1] / 127.0));
  FXBusR.gain(1, 1 - (gg.wetins[1] / 127.0));
}

void GlobalMixer::set_other_wet() {
  MasterL1.gain(0 ,gg.wetins[2] / 127.0);
  MasterR1.gain(0, gg.wetins[2] / 127.0);
  FXBusL.gain(3, 1 - (gg.wetins[2] / 127.0));
  FXBusR.gain(3, 1 - (gg.wetins[2] / 127.0));
}

void GlobalMixer::set_dry_mix(byte lebus) {
  _wet_mixers[lebus]();
}

void GlobalMixer::actionwet1mixer(int linstru) {
  if (mc.navlevel == 2) {
    mc.sublevels[3] = gg.WetMixMasters[linstru + 1];
  }
  if (mc.navlevel == 3) {
    mc.navrange = 127;
    mc.retroaction = mc.sublevels[2];
    if (!mc.temp_buff_armed) {
      set_wmixer_buff_temp();
      mc.temp_buff_armed = 1 ;
    }
    // wetmain[lafxline] = mc.sublevels[3];
    gg.WetMixMasters[linstru + 1] = mc.sublevels[3] ;
    wetmixmastercontrols();
  }
  if (mc.navlevel == 4) {
    mc.temp_buff_armed = 0 ;
    dm.returntonav(2, 3, mc.sublevels[2]);
  }
}

void GlobalMixer::action_dry_mix(int linstru) {

          if (mc.navlevel == 2) {
            mc.sublevels[3] = gg.wetins[linstru];
          }
          if (mc.navlevel == 3) {
            mc.retroaction = mc.sublevels[2];
            mc.navrange = 127;
            if (!mc.temp_buff_armed) {
            set_wmixer_buff_temp();
            mc.temp_buff_armed = 1 ;
          }
            gg.wetins[linstru] = mc.sublevels[3];
            set_dry_mix(linstru);
          }
          if (mc.navlevel == 4) {
            mc.temp_buff_armed = 0 ;
            dm.returntonav(2, 3, mc.sublevels[2]);
          }
        }

void GlobalMixer::actionwmixer(byte vknob) {

          if (mc.navlevel == 2) {
            mc.sublevels[3] = gg.mixlevelsL[vknob];
          }
          if (mc.navlevel == 3) {
            mc.navrange = 127;
            mc.retroaction = mc.sublevels[2];
            if (!mc.temp_buff_armed) {
              set_wmixer_buff_temp();
              mc.temp_buff_armed = 1 ;
            }
            gg.mixlevelsL[vknob] = mc.sublevels[3];
            setwavemixlevel();
          }
          if (mc.navlevel == 4) {
            mc.temp_buff_armed = 0 ;
            dm.returntonav(2, 3, mc.sublevels[2]);
          }
          //
        }

void GlobalMixer::setwavemixlevel() {
// AudioNoInterrupts();
  for (int j = 0; j < SYNTH_LINERS_COUNT; j++) {
    Wavesmix[j]->gain(mc.oscillator, gg.mixlevelsL[mc.oscillator]/127.0);
  }
// AudioInterrupts();

}
void GlobalMixer::Wavespreamp303controls() {
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    Wavespreamp303[i]->gain((gg.preampleswaves / 127.0)*2);
  }
}

void GlobalMixer::setle303filterpass(int linei) {
  les303passes[linei]->gain(0,gg.le303filterzgainz[0]/127.0);
  les303passes[linei]->gain(1,gg.le303filterzgainz[1]/127.0);
  les303passes[linei]->gain(2,gg.le303filterzgainz[2]/127.0);
}
void GlobalMixer::le303filtercontrols() {
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    setle303filterpass(i);
  }
}
void GlobalMixer::actionwmixerM(int lebus) {

          if (mc.navlevel == 2) {
            mc.sublevels[3] = gg.mixlevelsM[lebus];
          }
          if (mc.navlevel == 3) {
            mc.retroaction = mc.sublevels[2];
            if (!mc.temp_buff_armed) {
              set_wmixer_buff_temp();
              mc.temp_buff_armed = 1 ;
            }
            mc.navrange = 127;
            gg.mixlevelsM[lebus] = mc.sublevels[3];

            setmastersmixlevel(lebus);
          }
          if (mc.navlevel == 4) {
            mc.temp_buff_armed = 0 ;
            dm.returntonav(2, 3, mc.sublevels[2]);
          }
          //
}

SequencerClocker::SequencerClocker() : AudioStream(0, nullptr) {}

void SequencerClocker::setBPM(float bpm)
        {
            _bpm = bpm;
            calculatePPQN();
        }

void SequencerClocker::setPPQN(uint8_t ppqn) {
            _PPQN = ppqn;
            calculatePPQN();
        }

void SequencerClocker::attach_96(void (*cb)())
        {
            _callback_96 = cb;
        }

void SequencerClocker::update(){
  if (_samplesPerTick <= 0.0)
    return;
  _sampleAccumulator += AUDIO_BLOCK_SAMPLES;
  while (_sampleAccumulator >= _samplesPerTick) {
    _sampleAccumulator -= _samplesPerTick;
    //Tricker.click();
    if (_callback_96){
      _callback_96();
    }
  }
}

void SequencerClocker::calculatePPQN() {
  if (_PPQN == 0 || _bpm <= 0.0f)
    return;
  _samplesPerTick = AUDIO_SAMPLE_RATE_EXACT * 60.0 / (_bpm * _PPQN);
}


EXTMEM ClockSink sink;

EXTMEM AudioConnection patchCord_sinker(clocker, 0, sink, 0);

DisplayConsoler::DisplayConsoler(){
    clearing();
}

void DisplayConsoler::clearing(){
    cursorX = 0;
    cursorY = 0;

    memset(_c_buff, ' ', sizeof(_c_buff));

/*
    dm.clearDisplay();
    dm.setTextColor(SSD1306_WHITE);
    dm.setTextWrap(false);
    dm.setCursor(0,0);

    dm.display();
    */
}

void DisplayConsoler::wipe(){
    cursorX = 0;
    cursorY = 0;

    memset(_c_buff, ' ', sizeof(_c_buff));


    dm.clearDisplay();
    //dm.setTextColor(SSD1306_WHITE);
    //dm.setTextWrap(false);
    dm.setCursor(0,0);

    dm.display();

}
size_t DisplayConsoler::write(uint8_t c){
    if (c == '\r')
        return 1;

    if (c == '\n')
    {
        newLine();
        return 1;
    }

    _c_buff[cursorY][cursorX] = c;

    drawChar(c);

    cursorX++;

    if (cursorX >= COLS)
        newLine();

    return 1;
}

void DisplayConsoler::drawChar(char c){
    dm.setCursor(cursorX * CHAR_W,
                      cursorY * CHAR_H);

    dm.write(c);
}

void DisplayConsoler::newLine(){
    cursorX = 0;

    if (cursorY < ROWS - 1)
    {
        cursorY++;
        return;
    }

    scroll();
}

void DisplayConsoler::scroll(){
    for (uint8_t y = 0; y < ROWS - 1; y++)
    {
        memcpy(_c_buff[y], _c_buff[y + 1], COLS);
    }

    memset(_c_buff[ROWS - 1], ' ', COLS);

    dm.clearDisplay();

    for (uint8_t y = 0; y < ROWS; y++)
    {
        dm.setCursor(0, y * CHAR_H);

        for (uint8_t x = 0; x < COLS; x++)
            dm.write(_c_buff[y][x]);
          continue;
    }

    cursorY = ROWS - 1;
}

void DisplayConsoler::refresh(){
    dm.display();
}
