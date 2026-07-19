#include "MenuClasses.h"



void SectionHolder::set_home(void (*_cb)()){
    _home = _cb;
}

void DisplayManager::display_home() {
    if (ILI_128x64) {
        Serial.println("ILI_128x64 detected");
    }
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
            char menus_lbl[10][11] = {"WaveSynth", "LFOs", "Wav Editor", "Song", "Pattern", "Settings",
                        "MainFX", "Sampler", "Waveformer", "Presets"};
            if (navlevel == 0) {
                previousnavlevel = 0;
                navrange = 9;
                displayleBGimg(menuBG);
            }
            display.drawRoundRect(5 + (sublevels[0]%5)*24, 17+((sublevels[0]/5)*24), 21, 21, 3, SSD1306_WHITE);
            printlabel(menus_lbl[sublevels[0]]);
            display.display();
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
            root_route[sublevels[0]]();
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
                    this->home_navrange=SN_MENU_LABELS_COUNT-1;
                    this->relative_navlevel=1;
                    this->max_navlevel=5;
                    this->sublevels_address={0,0,0};
                        wmixer_tmp_pointers[0]  = &mixlevelsM[0];
                        wmixer_tmp_pointers[1]  = &mixlevelsM[1];
                        wmixer_tmp_pointers[2]  = &mixlevelsM[2];
                        wmixer_tmp_pointers[3]  = &WetMixMasters[1];
                        wmixer_tmp_pointers[4]  = &WetMixMasters[2];
                        wmixer_tmp_pointers[5]  = &WetMixMasters[3];
                        wmixer_tmp_pointers[6]  = &wetins[0];
                        wmixer_tmp_pointers[7]  = &wetins[1];
                        wmixer_tmp_pointers[8]  = &wetins[2];
                        wmixer_tmp_pointers[9]  = &mixlevelsL[0];
                        wmixer_tmp_pointers[10] = &mixlevelsL[1];
                        wmixer_tmp_pointers[11] = &mixlevelsL[2];

                        wmixer_tmp_values[0]  = mixlevelsM[0];
                        wmixer_tmp_values[1]  = mixlevelsM[1];
                        wmixer_tmp_values[2]  = mixlevelsM[2];
                        wmixer_tmp_values[3]  = WetMixMasters[1];
                        wmixer_tmp_values[4]  = WetMixMasters[2];
                        wmixer_tmp_values[5]  = WetMixMasters[3];
                        wmixer_tmp_values[6]  = wetins[0];
                        wmixer_tmp_values[7]  = wetins[1];
                        wmixer_tmp_values[8]  = wetins[2];
                        wmixer_tmp_values[9]  = mixlevelsL[0];
                        wmixer_tmp_values[10] = mixlevelsL[1];
                        wmixer_tmp_values[11] = mixlevelsL[2];
                    }

void GlobalMixer::show(){
      showmixerwaves();
    }

void GlobalMixer::showmixerwaves() {
      char masterfulllabels[12][12] = {
          "Master",     "Synth",      "Sampler",    "FX1",
          "FX2",        "FX3",        "Wet Synth",  "Wet Sampler", "Wet Other",
          "Waveline 1", "Waveline 2", "Waveline 3" };
      navrange = 11;
      byte slct = sublevels[2];

      if (navlevel == 2 && temp_buff_armed) {
        restore_wmixer_from_temp();
      }

      if (slct < 3) {
        actionwmixerM(sublevels[2]);
      }
      if (slct > 2 && slct < 6) {
        actionwet1mixer(sublevels[2] - 3);
      }
      if (slct > 5 && slct < 9) {
        action_dry_mix(sublevels[2] - 6);
      }
      if (slct > 8 && slct < 12) {
        actionwmixer(sublevels[2] - 9);
      }

      display.clearDisplay();
      canvastitle.fillScreen(SSD1306_BLACK);
      canvasBIG.fillScreen(SSD1306_BLACK);
      // canvastitle.setCursor(70,0);
      canvasBIG.setTextSize(1);
      canvasBIG.setCursor(0, 0);
      canvasBIG.print((char *)masterfulllabels[sublevels[2]]);

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

        coeffangle = (6.2831 - (mixlevelsM[i] / 127.0) * 6.2831) + 3.1416;
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
        canvastitle.print((mixlevelsM[slct] / 127.0) * 100.0, 1);
      }

      for (int i = 0; i < 3; i++) {
        coeffangle = (6.2831 - (WetMixMasters[i + 1]/127.0) * 6.2831) + 3.1416;
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
        canvastitle.print((WetMixMasters[slct - 3 + 1]/127.0) * 100.0, 1);
      }

      for (int i = 0; i < 3; i++) {
        coeffangle = (6.2831 - (wetins[i] / 127.0) * 6.2831) + 3.1416;
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
        canvastitle.print((wetins[slct - 6] / 127.0) * 100.0, 1);
      }

      for (int i = 0; i < OSCS_COUNT; i++) {
        coeffangle = (6.2831 - (mixlevelsL[i]/127.0) * 6.2831) + 3.1416;
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
        canvastitle.print((mixlevelsL[slct - 9]/127.0) * 100.0, 1);
      }
      dm.dodisplay();
    }
  
void GlobalMixer::setmastersmixlevel(int lebus) {
      //AudioNoInterrupts();
      switch (lebus) {
        case 0:
          // set mastermixlevel
          //audioShield.volume(mixlevelsM[0] / 127.0);
          ampL.gain(mixlevelsM[0] / 127.0);
          ampR.gain(mixlevelsM[0] / 127.0);
          break;
        case 1:
          // set synth Main
          mixerWAll.gain(1, mixlevelsM[1] / 127.0);
          mixerWAll.gain(0, mixlevelsM[1] / 127.0);
          break;
        case 2:
          // set sampler main
          flashMastermix.gain(0, mixlevelsM[2] / 127.0);
          flashMastermix.gain(1, mixlevelsM[2] / 127.0);
          break;
        default:
        break;
      }
      //AudioInterrupts();
    }



void GlobalMixer::wetmixmastercontrols() {
      for (byte i = 0; i < 4; i++) {
        WetMixMasterL.gain(i, WetMixMasters[i]/127.0);
        WetMixMasterR.gain(i, WetMixMasters[i]/127.0);
      }
    }
void GlobalMixer::restore_wmixer_from_temp() {
          for (int i=0; i<12; i++) {
            sublevels[3] = self->wmixer_tmp_values[i];
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
           temp_buff_armed = 0 ;
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
        MasterL1.gain(2, wetins[0] / 127.0);
        MasterR1.gain(2, wetins[0] / 127.0);
        FXBusL.gain(2, 1 - (wetins[0] / 127.0));
        FXBusR.gain(2, 1 - (wetins[0] / 127.0));

        break;
      case 1:
        // set sampler wetness on fx main bus
        MasterL1.gain(3, wetins[1] / 127.0);
        MasterR1.gain(3, wetins[1] / 127.0);
        FXBusL.gain(1, 1 - (wetins[1] / 127.0));
        FXBusR.gain(1, 1 - (wetins[1] / 127.0));
        break;

      case 2:
        // set wetness for "others" (audio in,SD,metronome) on fx main bus
        MasterL1.gain(0 ,wetins[2] / 127.0);
        MasterR1.gain(0, wetins[2] / 127.0);
        FXBusL.gain(3, 1 - (wetins[2] / 127.0));
        FXBusR.gain(3, 1 - (wetins[2] / 127.0));
        break;

      default:
        break;
      }
      //AudioInterrupts();
    }

void GlobalMixer::actionwet1mixer(int linstru) {

          if (navlevel == 2) {
            sublevels[3] = WetMixMasters[linstru + 1];
          }
          if (navlevel == 3) {
            navrange = 127;
            retroaction = sublevels[2];
            if (!temp_buff_armed) {
              set_wmixer_buff_temp();
              temp_buff_armed = 1 ;
            }
            // wetmain[lafxline] = sublevels[3];
            WetMixMasters[linstru + 1] = sublevels[3] ;
            wetmixmastercontrols();
          }
          if (navlevel == 4) {
            temp_buff_armed = 0 ;
            returntonav(2, 3, sublevels[2]);
          }
          //
        }

void GlobalMixer::action_dry_mix(int linstru) {

          if (navlevel == 2) {
            sublevels[3] = wetins[linstru];
          }
          if (navlevel == 3) {
            retroaction = sublevels[2];
            navrange = 127;
            if (!temp_buff_armed) {
            set_wmixer_buff_temp();
            temp_buff_armed = 1 ;
          }
            wetins[linstru] = sublevels[3];
            set_dry_mix(linstru);
          }
          if (navlevel == 4) {
            temp_buff_armed = 0 ;
            returntonav(2, 3, sublevels[2]);
          }
        }

void GlobalMixer::actionwmixer(byte vknob) {

          if (navlevel == 2) {
            sublevels[3] = mixlevelsL[vknob];
          }
          if (navlevel == 3) {
            navrange = 127;
            retroaction = sublevels[2];
            if (!temp_buff_armed) {
              set_wmixer_buff_temp();
              temp_buff_armed = 1 ;
            }
            mixlevelsL[vknob] = sublevels[3];
            setwavemixlevel();
          }
          if (navlevel == 4) {
            temp_buff_armed = 0 ;
            returntonav(2, 3, sublevels[2]);
          }
          //
        }
        
void GlobalMixer::setwavemixlevel() {
        // AudioNoInterrupts();
          for (int j = 0; j < SYNTH_LINERS_COUNT; j++) {
            Wavesmix[j]->gain(oscillator, mixlevelsL[oscillator]/127.0);
          }
        // AudioInterrupts();

        }
        
void GlobalMixer::actionwmixerM(int lebus) {

          if (navlevel == 2) {
            sublevels[3] = mixlevelsM[lebus];
          }
          if (navlevel == 3) {
            retroaction = sublevels[2];
            if (!temp_buff_armed) {
              set_wmixer_buff_temp();
              temp_buff_armed = 1 ;
            }
            navrange = 127;
            mixlevelsM[lebus] = sublevels[3];

            setmastersmixlevel(lebus);
          }
          if (navlevel == 4) {
            temp_buff_armed = 0 ;
            returntonav(2, 3, sublevels[2]);
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

void SequencerClocker::attach_24(void (*cb)())
        {
            _callback_24 = cb;
        }

void SequencerClocker::attach_16(void (*cb)())
        {
            _callback_16 = cb;
        }

void SequencerClocker::attach_96(void (*cb)())
        {
            _callback_96 = cb;
        }

void SequencerClocker::attach_3(void (*cb)())
        {
            _callback_3 = cb;
        }

void SequencerClocker::stopticker() {
            stoptick = 1;
            recordCC = 0;
            this->stop = 1;
            // if (patrecord) {
            // computelenghtmesureoffline_synth();
            patternOn = 0;
            patrecord = 0;
            // tickposition = 0 ;
        }

void SequencerClocker::startticker() {
            //TODO: reimplement external midi clock use
            //if (!externalticker) {
            // metro0.reset();
            //MsTimer2::set(millitickinterval, advance_tick);
            //MsTimer2::start();

            //}
            stoptick = 0;
            this->stop = 0;
            patternOn = 1;
        }

void SequencerClocker::update(){
    if (_samplesPerTick <= 0.0)
    return;
    _sampleAccumulator += AUDIO_BLOCK_SAMPLES;
    while (_sampleAccumulator >= _samplesPerTick) {
        _sampleAccumulator -= _samplesPerTick;

        tick96++;

        if ((tick96 % (3)) == 0 && _callback_3){
                thirtySecond++;
                _callback_3();
            }

        if ((tick96 % (2)) == 0 && _callback_16){
                quarter++;
                _callback_16();
            }
        if ((tick96 % (96*4)) == 0 && _callback_96){
                eighth++;
                _callback_96();
            }
        if (!stop) {

            if ((tick96 % 24) == 0 && _callback_24){
                sixteenth++;
                _callback_24();
            }
        }
    }
}

    

void SequencerClocker::calculatePPQN() {
            if (_PPQN == 0 || _bpm <= 0.0f)
            return;
            _samplesPerTick =
                AUDIO_SAMPLE_RATE_EXACT *
                60.0 /
                (_bpm * _PPQN);
}

