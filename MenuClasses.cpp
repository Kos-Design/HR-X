#include "MenuClasses.h"
#include <Audio.h>
#include <Encoder.h>

extern Encoder myEnc;

extern AudioControlSGTL5000 AudioShield;

void SectionHolder::set_home(void (*_cb)()){
    _home = _cb;
}

void DisplayManager::display_home() {
    if (ILI_128x64) {
        Serial.println("ILI_128x64 detected");
    }
}
void DisplayManager::returntonav(byte lelevel, byte lanavrange, byte t_vraipos) {
  lv.navlevel = lelevel;
  lv.rota_true_pos = t_vraipos;
  myEnc.write(lv.rota_true_pos * 4);
  lv.navrange = lanavrange;
  if (lv.navlevel) show();
}

void DisplayManager::setupscreen(){
            if (ILI_128x64) {
                _setupscreen_ILI();
            }
        }

void DisplayManager::displayleBGimg(const unsigned char *img) {_displayleBGimg(img);}

void DisplayManager::printlabel(char *toprint) {
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(toprint);
}

void DisplayManager::displaymenu() {
  char menus_lbl[10][11] = {"WaveSynth", "LFOs", "CoolEditor", "Song", "Pattern", "Settings",
              "MainFX", "Sampler", "Waveformer", "Presets"};
  if (lv.navlevel == 0) {
      lv.previousnavlevel = 0;
      lv.navrange = 9;
      displayleBGimg(menuBG);
  }
  display.drawRoundRect(5 + (lv.sublevels[0]%5)*24, 17+((lv.sublevels[0]/5)*24), 21, 21, 3, SSD1306_WHITE);
  printlabel(menus_lbl[lv.sublevels[0]]);
  display.display();
}

void DisplayManager::main_panel(const char* const* menulabels, int lvl, int menu_lbls_count) {
  if ( lv.navlevel == lvl ) lv.navrange = menu_lbls_count-1;
  byte startx = 5;
  byte starty = 16;
  char *textin = (char *)menulabels[lv.sublevels[lvl]];
  //dm.clean_title_2_1();
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(2);
  canvastitle.println(textin);

  for (int i = 0; i < menu_lbls_count - 1 - (lv.sublevels[lvl]); i++) {
    canvasBIG.setCursor(startx, starty + ((i)*10));
    canvasBIG.println(menulabels[lv.sublevels[lvl] + 1 + i]);
  }
  for (int i = 0; i < lv.sublevels[lvl]; i++) {
    canvasBIG.setCursor(startx, (10 * (menu_lbls_count - lv.sublevels[lvl])) + 6 + ((i)*10));
    canvasBIG.println(menulabels[i]);
  }
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
            display.clearDisplay();
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
            root_route[lv.sublevels[0]]();
        }

void (*DisplayManager::root_route[10])() = {&call_sn_show,&call_lf_show,&call_rd_show,&call_sg_show,&call_pt_show,
                                    &call_st_show,&call_fx_show,&call_sp_show,&call_wf_show,&call_ps_show};


void DisplayManager::_displayleBGimg(const unsigned char *img) {
            display.clearDisplay();
            display.drawBitmap(0, 0, img, 128, 64, SSD1306_WHITE);
        }

void DisplayManager::_setupscreen_ILI() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("Screen SSD1306 allocation failed"));
        return;
    }
    display.display();
    display.setCursor(0, 0);
    display.setTextSize(1.5);
    display.setTextColor(SSD1306_WHITE);
    display.clearDisplay();
}

void DisplayManager::dodisplay() {
  display.drawBitmap(0, 0, canvasBIG.getBuffer(), 128, 64, SSD1306_WHITE);
  display.drawBitmap(0, 0, canvastitle.getBuffer(), 128, 16, SSD1306_WHITE);
  display.display();
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
      lv.navrange = 11;
      byte slct = lv.sublevels[2];

      if (lv.navlevel == 2 && lv.temp_buff_armed) {
        restore_wmixer_from_temp();
      }

      if (slct < 3) {
        actionwmixerM(lv.sublevels[2]);
      }
      if (slct > 2 && slct < 6) {
        actionwet1mixer(lv.sublevels[2] - 3);
      }
      if (slct > 5 && slct < 9) {
        action_dry_mix(lv.sublevels[2] - 6);
      }
      if (slct > 8 && slct < 12) {
        actionwmixer(lv.sublevels[2] - 9);
      }

      display.clearDisplay();
      canvastitle.fillScreen(SSD1306_BLACK);
      canvasBIG.fillScreen(SSD1306_BLACK);
      // canvastitle.setCursor(70,0);
      canvasBIG.setTextSize(1);
      canvasBIG.setCursor(0, 0);
      canvasBIG.print((char *)masterfulllabels[lv.sublevels[2]]);

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
        canvastitle.setCursor(centercirclex - 5, 8);
        canvastitle.setTextSize(1);
        canvastitle.print((char)masterfulllabels[i][0]);
        canvastitle.print((char)masterfulllabels[i][2]);
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));
        display.drawLine(centercirclex, centercircley, trianglepointx, trianglepointy, SSD1306_WHITE);
      }

      if (slct < 3) {
        centercirclex = knobradius + (xcentershifter * slct);
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
        canvastitle.setCursor(95, 0);
        canvastitle.print((gg.mixlevelsM[slct] / 127.0) * 100.0, 1);
      }

      for (int i = 0; i < 3; i++) {
        coeffangle = (6.2831 - (gg.WetMixMasters[i + 1]/127.0) * 6.2831) + 3.1416;
        centercirclex = knobradius + (xcentershifter * i) + 5 + (xcentershifter * 3);
        centercircley = 16 + knobradius;
        canvastitle.setCursor(centercirclex - 8, 8);
        canvastitle.setTextSize(1);
        canvastitle.print((char *)masterfulllabels[i + 3]);
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));
        display.drawLine(centercirclex, centercircley, trianglepointx, trianglepointy, SSD1306_WHITE);
      }

      if (slct > 2 && slct < 6) {
        centercirclex = knobradius + (xcentershifter * (slct - 3)) + 5 + (xcentershifter * 3);
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
        canvastitle.setCursor(95, 0);
        canvastitle.print((gg.WetMixMasters[slct - 3 + 1]/127.0) * 100.0, 1);
      }

      for (int i = 0; i < 3; i++) {
        coeffangle = (6.2831 - (gg.wetins[i] / 127.0) * 6.2831) + 3.1416;
        centercirclex = knobradius + (xcentershifter * i);
        centercircley = yshifter + knobradius;
        canvasBIG.setCursor(centercirclex - 7, centercircley - (2 + knobradius * 2));
        canvasBIG.print("Ws");
        canvasBIG.print(i);
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));
        display.drawLine(centercirclex, centercircley, trianglepointx, trianglepointy, SSD1306_WHITE);
      }

      if (slct > 5 && slct < 9) {
        centercirclex = knobradius + (xcentershifter * (slct - 6));
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
        canvastitle.setCursor(95, 0);
        canvastitle.print((gg.wetins[slct - 6] / 127.0) * 100.0, 1);
      }

      for (int i = 0; i < OSCS_COUNT; i++) {
        coeffangle = (6.2831 - (gg.mixlevelsL[i]/127.0) * 6.2831) + 3.1416;
        centercirclex = knobradius + (xcentershifter * i) + 25 + (xcentershifter * 2);
        centercircley = yshifter + knobradius;
        canvasBIG.setCursor(centercirclex - 5, centercircley - (2 + knobradius * 2));
        canvasBIG.print("W");
        canvasBIG.print(i);
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));
        display.drawLine(centercirclex, centercircley, trianglepointx, trianglepointy, SSD1306_WHITE);
      }

      if (slct > 8 && slct < 12) {
        centercirclex = knobradius + (xcentershifter * (slct - 9)) + 25 + (xcentershifter * 2);
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
        canvastitle.setCursor(95, 0);
        canvastitle.print((gg.mixlevelsL[slct - 9]/127.0) * 100.0, 1);
      }
      dm.dodisplay();
    }
  
void GlobalMixer::setmastersmixlevel(int lebus) {
      //AudioNoInterrupts();
      switch (lebus) {
        case 0:
          // set mastermixlevel
          AudioShield.volume(gg.mixlevelsM[0] / 127.0);
          //ampL & R level should be 1.0 as they are used by queue recorder
          //ampL.gain(gg.mixlevelsM[0] / 127.0);
          //ampR.gain(gg.mixlevelsM[0] / 127.0);
          break;
        case 1:
          // set synth Main
          mixerWAll.gain(1, gg.mixlevelsM[1] / 127.0);
          mixerWAll.gain(0, gg.mixlevelsM[1] / 127.0);
          break;
        case 2:
          // set sampler main
          flashMastermix.gain(0, gg.mixlevelsM[2] / 127.0);
          flashMastermix.gain(1, gg.mixlevelsM[2] / 127.0);
          break;
        default:
        break;
      }
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
            lv.sublevels[3] = self->wmixer_tmp_values[i];
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
           lv.temp_buff_armed = 0 ;
        }

void GlobalMixer::set_wmixer_buff_temp() {
          //Serial.println("buffing");
          for (int i=0; i<12; i++) {
            self->wmixer_tmp_values[i] = *self->wmixer_tmp_pointers[i] ;
          }

        }

void GlobalMixer::set_dry_mix(int lebus) {

      switch (lebus) {
      case 0:
        // set synth wetness on fx main bus
        MasterL1.gain(2, gg.wetins[0] / 127.0);
        MasterR1.gain(2, gg.wetins[0] / 127.0);
        FXBusL.gain(2, 1 - (gg.wetins[0] / 127.0));
        FXBusR.gain(2, 1 - (gg.wetins[0] / 127.0));

        break;
      case 1:
        // set sampler wetness on fx main bus
        MasterL1.gain(3, gg.wetins[1] / 127.0);
        MasterR1.gain(3, gg.wetins[1] / 127.0);
        FXBusL.gain(1, 1 - (gg.wetins[1] / 127.0));
        FXBusR.gain(1, 1 - (gg.wetins[1] / 127.0));
        break;

      case 2:
        // set wetness for "others" (audio in,SD,metronome) on fx main bus
        MasterL1.gain(0 ,gg.wetins[2] / 127.0);
        MasterR1.gain(0, gg.wetins[2] / 127.0);
        FXBusL.gain(3, 1 - (gg.wetins[2] / 127.0));
        FXBusR.gain(3, 1 - (gg.wetins[2] / 127.0));
        break;

      default:
        break;
      }
      //AudioInterrupts();
    }

void GlobalMixer::actionwet1mixer(int linstru) {

          if (lv.navlevel == 2) {
            lv.sublevels[3] = gg.WetMixMasters[linstru + 1];
          }
          if (lv.navlevel == 3) {
            lv.navrange = 127;
            lv.retroaction = lv.sublevels[2];
            if (!lv.temp_buff_armed) {
              set_wmixer_buff_temp();
              lv.temp_buff_armed = 1 ;
            }
            // wetmain[lafxline] = lv.sublevels[3];
            gg.WetMixMasters[linstru + 1] = lv.sublevels[3] ;
            wetmixmastercontrols();
          }
          if (lv.navlevel == 4) {
            lv.temp_buff_armed = 0 ;
            dm.returntonav(2, 3, lv.sublevels[2]);
          }
          //
        }

void GlobalMixer::action_dry_mix(int linstru) {

          if (lv.navlevel == 2) {
            lv.sublevels[3] = gg.wetins[linstru];
          }
          if (lv.navlevel == 3) {
            lv.retroaction = lv.sublevels[2];
            lv.navrange = 127;
            if (!lv.temp_buff_armed) {
            set_wmixer_buff_temp();
            lv.temp_buff_armed = 1 ;
          }
            gg.wetins[linstru] = lv.sublevels[3];
            set_dry_mix(linstru);
          }
          if (lv.navlevel == 4) {
            lv.temp_buff_armed = 0 ;
            dm.returntonav(2, 3, lv.sublevels[2]);
          }
        }

void GlobalMixer::actionwmixer(byte vknob) {

          if (lv.navlevel == 2) {
            lv.sublevels[3] = gg.mixlevelsL[vknob];
          }
          if (lv.navlevel == 3) {
            lv.navrange = 127;
            lv.retroaction = lv.sublevels[2];
            if (!lv.temp_buff_armed) {
              set_wmixer_buff_temp();
              lv.temp_buff_armed = 1 ;
            }
            gg.mixlevelsL[vknob] = lv.sublevels[3];
            setwavemixlevel();
          }
          if (lv.navlevel == 4) {
            lv.temp_buff_armed = 0 ;
            dm.returntonav(2, 3, lv.sublevels[2]);
          }
          //
        }
        
void GlobalMixer::setwavemixlevel() {
        // AudioNoInterrupts();
          for (int j = 0; j < SYNTH_LINERS_COUNT; j++) {
            Wavesmix[j]->gain(lv.oscillator, gg.mixlevelsL[lv.oscillator]/127.0);
          }
        // AudioInterrupts();

        }
        
void GlobalMixer::actionwmixerM(int lebus) {

          if (lv.navlevel == 2) {
            lv.sublevels[3] = gg.mixlevelsM[lebus];
          }
          if (lv.navlevel == 3) {
            lv.retroaction = lv.sublevels[2];
            if (!lv.temp_buff_armed) {
              set_wmixer_buff_temp();
              lv.temp_buff_armed = 1 ;
            }
            lv.navrange = 127;
            gg.mixlevelsM[lebus] = lv.sublevels[3];

            setmastersmixlevel(lebus);
          }
          if (lv.navlevel == 4) {
            lv.temp_buff_armed = 0 ;
            dm.returntonav(2, 3, lv.sublevels[2]);
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
    if (_callback_96 && !gg.externalticker){
      _callback_96();
    }
  }
}

void SequencerClocker::calculatePPQN() {
  if (_PPQN == 0 || _bpm <= 0.0f)
    return;
  _samplesPerTick = AUDIO_SAMPLE_RATE_EXACT * 60.0 / (_bpm * _PPQN);
}

extern SequencerClocker clocker;

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
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextWrap(false);
    display.setCursor(0,0);

    display.display();
    */
}

void DisplayConsoler::wipe(){
    cursorX = 0;
    cursorY = 0;

    memset(_c_buff, ' ', sizeof(_c_buff));


    display.clearDisplay();
    //display.setTextColor(SSD1306_WHITE);
    //display.setTextWrap(false);
    display.setCursor(0,0);

    display.display();
    
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
    display.setCursor(cursorX * CHAR_W,
                      cursorY * CHAR_H);

    display.write(c);
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

    display.clearDisplay();

    for (uint8_t y = 0; y < ROWS; y++)
    {
        display.setCursor(0, y * CHAR_H);

        for (uint8_t x = 0; x < COLS; x++)
            display.write(_c_buff[y][x]);
          continue;
    }

    cursorY = ROWS - 1;
}

void DisplayConsoler::refresh(){
    display.display();
}
