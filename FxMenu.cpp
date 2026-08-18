#include "FxMenu.h"
#include "LfoMenu.h"

FxMenuRouter* FxMenuRouter::self = nullptr;


FxMenuRouter::FxMenuRouter() {
                      self = this ;
                      self->home_navrange=2;
                      self->relative_navlevel=1;
                      self->max_navlevel=5;
                      self->sublevels_address={6,0,0};
                      }
      
      /*
void FxMenuRouter::show() {
        _nav_fx[lv.sublevels[1]](); 
      }
      */
void FxMenuRouter::peakingEQ(float freq, float gainDB, float Q, float Fs, double *c) {

          float A = powf(10.0f, gainDB / 40.0f);
          float w0 = 2.0f * PI * freq / Fs;

          float alpha = sinf(w0)/(2.0f*Q);

          float cosw = cosf(w0);

          float b0 = 1 + alpha*A;
          float b1 = -2*cosw;
          float b2 = 1 - alpha*A;

          float a0 = 1 + alpha/A;
          float a1 = -2*cosw;
          float a2 = 1 - alpha/A;
          
          Serial.println("inside");
          Serial.println(b0, 6);
          Serial.println(b1, 6);
          Serial.println(b2, 6);
          Serial.println(a1, 6);
          Serial.println(a2, 6);
          Serial.println("");
          Serial.print("a0 = ");
          Serial.print(a0, 6);
          Serial.println("");

          c[0] = b0/a0;
          c[1] = b1/a0;
          c[2] = b2/a0;
          c[3] = a1/a0;
          c[4] = a2/a0;

          Serial.printf("write c=%p\n", c);
        for (int i = 0; i < 5; i++) {
          Serial.println(c[i], 12);
        }
      }
      
void FxMenuRouter::prepare_coeffs(byte fx_idx){
        peakingEQ(gg.fx[fx_idx].bqfreq[gg.fx[fx_idx].bqstage], gg.fx[fx_idx].bqgain[gg.fx[fx_idx].bqstage], gg.fx[fx_idx].bqslope[gg.fx[fx_idx].bqstage], AUDIO_SAMPLE_RATE, self->coeffs[gg.fx[fx_idx].bqstage]); 
      }

void FxMenuRouter::dolistMainFxPanel() {
        byte startx = 5;
        byte starty = 16;
        char *textin = (char *)self->mainmenufxlist[lv.sublevels[lv.navlevel]];
        dm.clear_buffs_2_1();
        canvastitle.println(textin);

        for (int filer = 0; filer < lv.navrange - (lv.sublevels[lv.navlevel]); filer++) {
          canvasBIG.setCursor(startx, starty + (filer*10));
          canvasBIG.println(self->mainmenufxlist[lv.sublevels[lv.navlevel] + 1 + filer]);
        }
        for (int filer = 0; filer < lv.sublevels[lv.navlevel]; filer++) {
          canvasBIG.setCursor(startx, (10 * (lv.navrange + 1 - lv.sublevels[lv.navlevel])) + 6 + (filer*10));
          canvasBIG.println(self->mainmenufxlist[filer]);
        }
      }

void FxMenuRouter::dolistmainfxlines() {

        char mainfxlineslist[FXS_COUNT][12] = {"FX Line1", "FX Line2", "FX Line3"};
        byte startx = 5;
        byte starty = 16;
        String textin;
        if (gg.fx[lv.sublevels[1]%FXS_COUNT].plugged_fx != (self->mainmenufxlistsize - 1)) {
          textin = (String)self->mainmenufxlist[gg.fx[lv.sublevels[1]%FXS_COUNT].plugged_fx];
        } else {
          textin = (String)mainfxlineslist[lv.sublevels[1]%FXS_COUNT];
        }
        dm.clear_buffs_2_1();
        canvastitle.println(textin);
        for (int i = 0; i < FXS_COUNT - 1 - lv.sublevels[1]; i++) {
          canvasBIG.setCursor(startx, starty + ((i)*10));
          if (gg.fx[lv.sublevels[1]%FXS_COUNT + 1 + i].plugged_fx != self->mainmenufxlistsize-1) {
            canvasBIG.println((String)self->mainmenufxlist[gg.fx[lv.sublevels[1]%FXS_COUNT + 1 + i].plugged_fx]);
          } else {
            canvasBIG.println(mainfxlineslist[lv.sublevels[1]%FXS_COUNT + 1 + i]);
          }
        }
        for (int i = 0; i < lv.sublevels[1]%FXS_COUNT; i++) {
          canvasBIG.setCursor(startx, (10 * (FXS_COUNT - (lv.sublevels[1]%FXS_COUNT)) + 6 + ((i)*10)));
          if (gg.fx[i].plugged_fx != (self->mainmenufxlistsize - 1)) {
            canvasBIG.println((String)self->mainmenufxlist[gg.fx[i].plugged_fx]);
          } else {
            canvasBIG.println(mainfxlineslist[i]);
          }
        }
      }

void FxMenuRouter::biquadcontrols(byte fx_idx) {
        // AudioNoInterrupts();
        switch (gg.fx[fx_idx].bqtype[gg.fx[fx_idx].bqstage]) {
        
          case 0:
            biquad[fx_idx]->setLowpass(gg.fx[fx_idx].bqstage,
                                        gg.fx[fx_idx].bqfreq[gg.fx[fx_idx].bqstage],
                                        gg.fx[fx_idx].bqslope[gg.fx[fx_idx].bqstage]);
            biquadR[fx_idx]->setLowpass(gg.fx[fx_idx].bqstage,
                                        gg.fx[fx_idx].bqfreq[gg.fx[fx_idx].bqstage],
                                        gg.fx[fx_idx].bqslope[gg.fx[fx_idx].bqstage]);
            break;

          case 1:

            biquad[fx_idx]->setHighpass(gg.fx[fx_idx].bqstage,
                                          gg.fx[fx_idx].bqfreq[gg.fx[fx_idx].bqstage],
                                          gg.fx[fx_idx].bqslope[gg.fx[fx_idx].bqstage]);
            biquadR[fx_idx]->setHighpass(gg.fx[fx_idx].bqstage,
                                          gg.fx[fx_idx].bqfreq[gg.fx[fx_idx].bqstage],
                                          gg.fx[fx_idx].bqslope[gg.fx[fx_idx].bqstage]);
            break;

          case 2:
            biquad[fx_idx]->setBandpass(gg.fx[fx_idx].bqstage,
                                          gg.fx[fx_idx].bqfreq[gg.fx[fx_idx].bqstage],
                                          gg.fx[fx_idx].bqslope[gg.fx[fx_idx].bqstage]);
            biquadR[fx_idx]->setBandpass(gg.fx[fx_idx].bqstage,
                                          gg.fx[fx_idx].bqfreq[gg.fx[fx_idx].bqstage],
                                          gg.fx[fx_idx].bqslope[gg.fx[fx_idx].bqstage]);
            break;

          case 3:
            biquad[fx_idx]->setNotch(gg.fx[fx_idx].bqstage,
                                      gg.fx[fx_idx].bqfreq[gg.fx[fx_idx].bqstage],
                                      gg.fx[fx_idx].bqslope[gg.fx[fx_idx].bqstage]);
            biquadR[fx_idx]->setNotch(gg.fx[fx_idx].bqstage,
                                      gg.fx[fx_idx].bqfreq[gg.fx[fx_idx].bqstage],
                                      gg.fx[fx_idx].bqslope[gg.fx[fx_idx].bqstage]);
            break;

          case 4:
            biquad[fx_idx]->setLowShelf(gg.fx[fx_idx].bqstage,
                                          gg.fx[fx_idx].bqfreq[gg.fx[fx_idx].bqstage],
                                          gg.fx[fx_idx].bqgain[gg.fx[fx_idx].bqstage],
                                          gg.fx[fx_idx].bqslope[gg.fx[fx_idx].bqstage]);
            biquadR[fx_idx]->setLowShelf(gg.fx[fx_idx].bqstage,
                                          gg.fx[fx_idx].bqfreq[gg.fx[fx_idx].bqstage],
                                          gg.fx[fx_idx].bqgain[gg.fx[fx_idx].bqstage],
                                          gg.fx[fx_idx].bqslope[gg.fx[fx_idx].bqstage]);
            break;

          case 5:
            biquad[fx_idx]->setHighShelf(gg.fx[fx_idx].bqstage,
                                          gg.fx[fx_idx].bqfreq[gg.fx[fx_idx].bqstage],
                                          gg.fx[fx_idx].bqgain[gg.fx[fx_idx].bqstage],
                                          gg.fx[fx_idx].bqslope[gg.fx[fx_idx].bqstage]);
            biquadR[fx_idx]->setHighShelf(gg.fx[fx_idx].bqstage,
                                          gg.fx[fx_idx].bqfreq[gg.fx[fx_idx].bqstage],
                                          gg.fx[fx_idx].bqgain[gg.fx[fx_idx].bqstage],
                                          gg.fx[fx_idx].bqslope[gg.fx[fx_idx].bqstage]);
            break;

          case 6:
              //set self->coeffs
              Serial.println("");
              Serial.print("Calling biquad");
              Serial.println(fx_idx);

              prepare_coeffs(fx_idx);
              
              biquad[fx_idx]->setCoefficients(gg.fx[fx_idx].bqstage, self->coeffs[gg.fx[fx_idx].bqstage]);
              biquadR[fx_idx]->setCoefficients(gg.fx[fx_idx].bqstage, self->coeffs[gg.fx[fx_idx].bqstage]);
            break;

          default:
            break;
        }
        // AudioInterrupts();
      }
           
void FxMenuRouter::delayfeedback(byte fx_idx, float lesmallfloat) {
        // delay feedback
        if (lesmallfloat <= 0.1) {

          delayfeedbackmix[fx_idx]->gain(0, 1.0);
          delayfeedbackmix[fx_idx]->gain(1, 0);
          delayfeedbackmixR[fx_idx]->gain(0, 1.0);
          delayfeedbackmixR[fx_idx]->gain(1, 0);
        } else {

          delayfeedbackmix[fx_idx]->gain(0, 1.0 - lesmallfloat);
          delayfeedbackmix[fx_idx]->gain(1, lesmallfloat);
          delayfeedbackmixR[fx_idx]->gain(0, 1.0 - lesmallfloat);
          delayfeedbackmixR[fx_idx]->gain(1, lesmallfloat);
        }
        // restartdelayline(fx_idx);
      }

void FxMenuRouter::delaytimingselect(int fx_idx, int leselecta) {
        int leselectee = map(leselecta, 0, 127, 0, 7);

        for (int j = 0; j < 4; j++) {
          delaypremix[2 * fx_idx]->gain(j, 0);
          delaypremix[2 * fx_idx + 1]->gain(j, 0);
          delaypremixR[2 * fx_idx]->gain(j, 0);
          delaypremixR[2 * fx_idx + 1]->gain(j, 0);
        }
        if (leselectee < 4) {
          delaypremix[2 * fx_idx]->gain(leselectee, 1);
          delaypremixR[2 * fx_idx]->gain(leselectee, 1);
        }
        if (leselectee >= 4) {
          delaypremix[2 * fx_idx + 1]->gain(leselectee - 4, 1);
          delaypremixR[2 * fx_idx + 1]->gain(leselectee - 4, 1);
        }
        // restartdelayline(fx_idx);
      }

void FxMenuRouter::restartdelayline(int fx_idx) {

        gg.fx[fx_idx].delaymultiplier = gg.fx[fx_idx].delayVknobs[1] + 1;
        delaytimingselect(fx_idx, gg.fx[fx_idx].delayVknobs[0]);

        delayfeedback(fx_idx, (gg.fx[fx_idx].delayVknobs[2] / 127.0) * 0.45);
        //8 is delay obj tap channels
        for (int j = 0; j < 8; j++) {

          lesdelays[fx_idx]->delay(j, gg.fx[fx_idx].delaymultiplier * (j + 2));
          lesdelaysR[fx_idx]->delay(j, gg.fx[fx_idx].delaymultiplier * (j + 2));

        }
      }
      
void FxMenuRouter::changebiquadfreqvalue(byte fx_idx, int valub) {
        // valub range 1024
        gg.fx[fx_idx].bqfreq[gg.fx[fx_idx].bqstage] = valub * 3;
        biquadcontrols(fx_idx);
      }

void FxMenuRouter::displayfxVcontrols(byte fxinstance) {
        //TODO:make switch
        if (lv.sublevels[2] == 6) {
          biquadVpanel(fxinstance);
        }
        if (lv.sublevels[2] == 7) {
          filterVpanel(fxinstance);
        }
        if (lv.sublevels[2] == 8) {
          delayVpanel(fxinstance);
        }
        if (lv.sublevels[2] == 1) {
          reverbVpanel(fxinstance);
        }
        if (lv.sublevels[2] == 3) {
          bitcrusherVpanel(fxinstance);
        }
        if (lv.sublevels[2] == 2) {
          granularVpanel(fxinstance);
        }
        if (lv.sublevels[2] == 5) {
          chorusVpanel(fxinstance);
        }
        if (lv.sublevels[2] == 4) {
          flangerVpanel(fxinstance);
        }
        if (lv.sublevels[2] == 9 || lv.sublevels[2] == 0) {
          lv.navlevel--;
        }
      }
void FxMenuRouter::flangercontrols(byte fx_idx) {
        gg.fx[fx_idx].flangeoffset =
            round((gg.fx[fx_idx].flangerVknobs[0] / 127.0) * FLANGE_DELAY_LENGTH / 4);
        gg.fx[fx_idx].flangedepth =
            round((gg.fx[fx_idx].flangerVknobs[1] / 127.0) * FLANGE_DELAY_LENGTH / 4);
        gg.fx[fx_idx].flangefreq = (double)(gg.fx[fx_idx].flangerVknobs[2] / 127.0) * 2;
         AudioNoInterrupts();
        flange[fx_idx]->voices(gg.fx[fx_idx].flangeoffset, gg.fx[fx_idx].flangedepth, gg.fx[fx_idx].flangefreq);
        flangeR[fx_idx]->voices(gg.fx[fx_idx].flangeoffset, gg.fx[fx_idx].flangedepth, gg.fx[fx_idx].flangefreq);
         AudioInterrupts();
      }
void FxMenuRouter::flangerVpanelAction(byte fx_idx) {
        if (lv.navlevel == 4) {
          // AudioNoInterrupts();
          byte slct = lv.sublevels[3];
          // offset
          if (slct == 0) {
            lv.navrange = 127;
            gg.fx[fx_idx].flangerVknobs[0] = lv.sublevels[4];
            flangercontrols(fx_idx);
          }
          // depth
          if (slct == 1) {
            lv.navrange = 127;
            gg.fx[fx_idx].flangerVknobs[1] = lv.sublevels[4];
            flangercontrols(fx_idx);
            // apply
          }
          // delayRate
          // depth
          if (slct == 2) {
            lv.navrange = 127;
            gg.fx[fx_idx].flangerVknobs[2] = lv.sublevels[4];
            flangercontrols(fx_idx);
            // apply
          }
          if (slct == 3) {
            lv.navrange = 127;
            set_wet_mix_at_sub4(fx_idx);
          }
        }
        if (lv.navlevel > 4) {
          dm.returntonav(3);
        }
      }

void FxMenuRouter::set_wet_mix_at_sub4(byte i){
        gg.WetMixMasters[i + 1] = lv.sublevels[4] ;
        _mx.wetmixmastercontrols();
      }

void FxMenuRouter::flangerVpanelSelector(byte fx_idx) {
        byte knobradius = 11;
        byte centercirclex = 15 + knobradius;
        byte centercircley = 16 + knobradius;
        byte startlex2 = 67;
        byte totbartall = 37;
        byte topwbarstart = 16;
        byte wbarwidth2 = 8;
        if (lv.navlevel == 3) {
          lv.navrange = 3;
        }
        byte slct = lv.sublevels[3];
        // size
        if (slct == 0) {
          lv.sublevels[4] = gg.fx[fx_idx].flangerVknobs[0];
          canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2,
                              SSD1306_WHITE);
        }
        // damp
        if (slct == 1) {
          lv.sublevels[4] = gg.fx[fx_idx].flangerVknobs[1];
          canvasBIG.drawCircle(centercirclex + 40, centercircley, knobradius - 2,
                              SSD1306_WHITE);
        }

        if (slct == 2) {
          lv.sublevels[4] = gg.fx[fx_idx].flangerVknobs[2];
          canvasBIG.drawCircle(centercirclex + 40 + 40, centercircley, knobradius - 2,
                              SSD1306_WHITE);
        }

        // wet
        if (slct == 3) {
          lv.sublevels[4] = gg.WetMixMasters[fx_idx+ 1];
          canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall, wbarwidth2 - 4, SSD1306_WHITE);
          canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
        }
      }

void FxMenuRouter::flangerVpanel(byte fx_idx) {

        flangerVpanelAction(fx_idx);
        byte knobradius = 11;
        byte centercirclex = 15 + knobradius;
        byte centercircley = 16 + knobradius;
        byte ftVcursorpointx;
        byte ftVcursorpointy;

        float coeffangle;
        byte totbartall = 37;
        byte topwbarstart = 16;
        byte wbarwidth2 = 8;
        byte barsize;
        byte startlex2 = 67;
            dm.clean_title_1();
        canvastitle.print("Flanger ");
        canvastitle.print(fx_idx + 1);
        //  gg.fx[fx_idx].flangerVknobs[0] ;
        // float dephtflange = gg.fx[fx_idx].flangerVknobs[1]/127.0 ;
        // float freqflange = gg.fx[fx_idx].flangerVknobs[2]/127.0 ;
        // voices(gg.fx[fx_idx].flangeoffset, gg.fx[fx_idx].flangedepth, flangefreq);
        // Roomsize
        coeffangle = (6.2831 - (gg.fx[fx_idx].flangerVknobs[0] / 127.0) * 6.2831) + 3.1416;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 1, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);

        canvasBIG.print(round((gg.fx[fx_idx].flangerVknobs[0] / 127.0) * FLANGE_DELAY_LENGTH / 4));
        // canvasBIG.setCursor(centercirclex-knobradius+1, 8);
        canvasBIG.setCursor(centercirclex - knobradius - 6, centercircley + knobradius + 4 + 10);
        canvasBIG.print("Offset");

        // damping
        coeffangle = (6.2831 - (gg.fx[fx_idx].flangerVknobs[1] / 127.0) * 6.2831) + 3.1416;
        centercirclex = centercirclex + 40;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 1, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print(
            round((gg.fx[fx_idx].flangerVknobs[1] / 127.0) * FLANGE_DELAY_LENGTH / 4));
        // canvasBIG.setCursor(centercirclex-knobradius+1, 8);
        canvasBIG.setCursor(centercirclex - knobradius - 2, centercircley + knobradius + 4 + 10);
        canvasBIG.print("Depth");

        coeffangle =
            (6.2831 - (gg.fx[fx_idx].flangerVknobs[2] / 127.0) * 6.2831) + 3.1416;
        centercirclex = centercirclex + 40;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 1, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print(((gg.fx[fx_idx].flangerVknobs[2] / 127.0) * 2), 2);
        canvasBIG.setCursor(centercirclex - knobradius - 2, centercircley + knobradius + 4 + 10);
        // canvasBIG.setCursor(centercirclex-knobradius+1, 8);
        canvasBIG.print("Delay");

        // wetbar
        barsize = round((gg.WetMixMasters[fx_idx + 1] /127.0) * (totbartall - 4));
        canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall, wbarwidth2, 2, SSD1306_WHITE);
        canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4, SSD1306_WHITE);
        canvasBIG.setCursor(startlex2 - 6, 0);
        canvasBIG.print("Wet:");
        flangerVpanelSelector(fx_idx);
        dm.dodisplay();
      }

void FxMenuRouter::choruscontrols(byte fx_idx) {
        gg.fx[fx_idx].chorusvoices = round((gg.fx[fx_idx].chorusVknobs / 127.0) * 8) ;
        chorus[fx_idx]->voices(gg.fx[fx_idx].chorusvoices);
        chorusR[fx_idx]->voices(gg.fx[fx_idx].chorusvoices);
      }

void FxMenuRouter::chorusVpanelAction(byte fx_idx) {
        if (lv.navlevel == 4) {
          // AudioNoInterrupts();
          byte slct = lv.sublevels[3];
          // fq
          if (slct == 0) {
            lv.navrange = 127;
            gg.fx[fx_idx].chorusVknobs = lv.sublevels[4];
            choruscontrols(fx_idx);
          }
          // res
          if (slct == 1) {
            lv.navrange = 127;
            set_wet_mix_at_sub4(fx_idx);
          }
        }
        if (lv.navlevel > 4) {
          dm.returntonav(3);
        }
      }

void FxMenuRouter::chorusVpanelSelector(byte fx_idx) {

        byte knobradius = 16;
        byte centercirclex = 48 + knobradius;
        byte centercircley = 16 + knobradius;
        byte startlex2 = 67;
        byte totbartall = 37;
        byte topwbarstart = 16;
        byte wbarwidth2 = 8;
        if (lv.navlevel == 3) {
          lv.navrange = 1;
        }
        int slct = lv.sublevels[3];
        // size
        if (slct == 0) {
          lv.sublevels[4] = gg.fx[fx_idx].chorusVknobs;
          canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2,
                              SSD1306_WHITE);
        }

        // wet
        if (slct == 1) {
          lv.sublevels[4] = gg.WetMixMasters[fx_idx + 1];
          canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall,
                            wbarwidth2 - 4, SSD1306_WHITE);
          canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
        }
      }

void FxMenuRouter::chorusVpanel(byte fx_idx) {

        chorusVpanelAction(fx_idx);
        byte knobradius = 16;
        byte centercirclex = 48 + knobradius;
        byte centercircley = 16 + knobradius;
        byte ftVcursorpointx;
        byte ftVcursorpointy;

        float coeffangle;
        byte totbartall = 37;
        byte topwbarstart = 16;
        byte wbarwidth2 = 8;
        byte barsize;
        byte startlex2 = 67;
            dm.clean_title_1();
        canvastitle.print("Chorus ");
        canvastitle.print(fx_idx + 1);

        float leroomsize = gg.fx[fx_idx].chorusVknobs / 127.0;
        // Roomsize
        coeffangle = (6.2831 - (leroomsize)*6.2831) + 3.1416;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                          ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 5,
                            centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print(round((gg.fx[fx_idx].chorusVknobs / 127.0) * 8));
        canvasBIG.setCursor(centercirclex - knobradius - 1, 8);
        canvasBIG.print("Voices");

        // wetbar
        barsize =
            round((gg.WetMixMasters[fx_idx + 1]/127.0) *
                  (totbartall - 4));
        canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall,
                                wbarwidth2, 2, SSD1306_WHITE);
        canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4,
                          SSD1306_WHITE);
        canvasBIG.setCursor(startlex2 - 6, 0);
        canvasBIG.print("Wet:");

        chorusVpanelSelector(fx_idx);

        dm.dodisplay();
      }

void FxMenuRouter::granular_pitch_shift(byte fx_idx){
        // up to 1/3 of GRANULAR_MEMORY_SIZE in ms equivalent !!!
        //float leratio = (gg.fx[fx_idx].granularVknobs[1] / 127.0) * 3.0;
        int maxgrain = (int)(0.027 * GRANULAR_MEMORY_SIZE );// up to (GRANULAR_MEMORY_SIZE / 290) ms if grain is 12800 so ratio of 0.027 of GRANULAR_MEMORY_SIZE
        float legrainleng = 1.0 * map(gg.fx[fx_idx].granularVknobs[0],0,127,1,maxgrain) ;
        if (gg.fx[fx_idx].granular_shifting) {
          if (!gg.fx[fx_idx].granular_freezing) {
            granular[fx_idx]->begin(bb.granularMemory[fx_idx], GRANULAR_MEMORY_SIZE);
            granularR[fx_idx]->begin(bb.granularMemory[fx_idx], GRANULAR_MEMORY_SIZE);
          }
          granularcontrols(fx_idx);
          granular[fx_idx]->beginPitchShift(legrainleng);
          granularR[fx_idx]->beginPitchShift(legrainleng);

          //octavedown1.begin(120.0, 33.0);

        } else if(gg.fx[fx_idx].granular_freezing){
            granular_freeze(fx_idx);
        } else {
          granular[fx_idx]->stop();
          granularR[fx_idx]->stop();
          //octavedown1.end();
        }
      }

void FxMenuRouter::granular_freeze(byte fx_idx){
        int maxgrain = (int)(0.027 * GRANULAR_MEMORY_SIZE );// up to (GRANULAR_MEMORY_SIZE / 290) ms if grain is 12800 so ratio of 0.027 of GRANULAR_MEMORY_SIZE
        float legrainleng = 0.75*map(gg.fx[fx_idx].granularVknobs[0],0,127,1,maxgrain) ;
        if (gg.fx[fx_idx].granular_freezing) {
          if (!gg.fx[fx_idx].granular_shifting) {
            granular[fx_idx]->begin(bb.granularMemory[fx_idx], GRANULAR_MEMORY_SIZE);
            granularR[fx_idx]->begin(bb.granularMemory[fx_idx], GRANULAR_MEMORY_SIZE);
          }
          granularcontrols(fx_idx);
          granular[fx_idx]->beginFreeze(legrainleng);
          granularR[fx_idx]->beginFreeze(legrainleng);
        } else if(gg.fx[fx_idx].granular_shifting){
            //granular_pitch_shift stops the freeze
            granular_pitch_shift(fx_idx);
        } else {
          granular[fx_idx]->stop();
          granularR[fx_idx]->stop();
        }
      }

void FxMenuRouter::granularcontrols(byte fx_idx) {
        float g_speed = 0.125 + (map(gg.fx[fx_idx].granularVknobs[1],0,127,0,7875)/1000.0);
        granular[fx_idx]->setSpeed(g_speed);
        granularR[fx_idx]->setSpeed(g_speed);
      }

void FxMenuRouter::granularVpanelAction(byte fx_idx) {
        if (lv.navlevel == 4) {
          byte slct = lv.sublevels[3];
          // g leng
          if (slct == 0) {
            lv.navrange = 127;
            gg.fx[fx_idx].granularVknobs[0] = lv.sublevels[4];
          }
          if (slct == 1) {
            lv.navrange = 127;
            gg.fx[fx_idx].granularVknobs[1] = lv.sublevels[4];
            granularcontrols(fx_idx);
          }
          // res
          if (slct == 2) {
            gg.fx[fx_idx].granular_freezing = !gg.fx[fx_idx].granular_freezing;
            granular_freeze(fx_idx);
            dm.returntonav(3);
          }
          if (slct == 3) {
            gg.fx[fx_idx].granular_shifting = !gg.fx[fx_idx].granular_shifting ;
            granular_pitch_shift(fx_idx);
            dm.returntonav(3);
          }

          if (slct == 4) {
            lv.navrange = 127;
            set_wet_mix_at_sub4(fx_idx);
          }
        }

        if (lv.navlevel > 4) {

          dm.returntonav(3);
        }
      }

void FxMenuRouter::granularVpanelSelector(byte fx_idx) {
        const byte knobradius = 13;
        byte centercirclex = 10 + knobradius;
        byte centercircley = 16 + knobradius;
        const byte startlex2 = 67;
        const byte totbartall = 37;
        const byte topwbarstart = 16;
        const byte wbarwidth2 = 8;
        if (lv.navlevel == 3) {
          lv.navrange = 4;
        }
        byte slct = lv.sublevels[3];
        // size
        if (slct == 0) {
          lv.sublevels[4] = gg.fx[fx_idx].granularVknobs[0];
          canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
        }
        // damp
        if (slct == 1) {
          lv.sublevels[4] = gg.fx[fx_idx].granularVknobs[1];
          canvasBIG.drawCircle(knobradius + 45, centercircley, knobradius - 2, SSD1306_WHITE);
        }
        if (slct == 2) {
          if (!gg.fx[fx_idx].granular_freezing) {
            canvasBIG.drawRoundRect(82, 18, 128 - 80 - 4, 20 - 4, 2, SSD1306_WHITE);
          } else {
            canvasBIG.drawRoundRect(82, 18, 128 - 80 - 4, 20 - 4, 2, SSD1306_BLACK);
          }
        }
        if (slct == 3) {
          if (!gg.fx[fx_idx].granular_shifting) {
            canvasBIG.drawRoundRect(82, 18 + 20 + 4, 128 - 80 - 4, 20 - 4, 2, SSD1306_WHITE);
          } else {
            canvasBIG.drawRoundRect(82, 18 + 20 + 4, 128 - 80 - 4, 20 - 4, 2, SSD1306_BLACK);
          }
        }
        // wet
        if (slct == 4) {
          lv.sublevels[4] = gg.WetMixMasters[fx_idx + 1] ;
          canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall, wbarwidth2 - 4, SSD1306_WHITE);
          canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
        }
      }

void FxMenuRouter::granularVpanel(byte fx_idx) {

        granularVpanelAction(fx_idx);
        const byte knobradius = 13;
        byte centercirclex = 10 + knobradius;
        byte centercircley = 16 + knobradius;
        byte ftVcursorpointx;
        byte ftVcursorpointy;
        float coeffangle;
        const byte totbartall = 37;
        const byte topwbarstart = 16;
        const byte wbarwidth2 = 8;
        byte barsize;
        const byte startlex2 = 67;
        int legrainleng = map(gg.fx[fx_idx].granularVknobs[0],0,127,1,GRANULAR_MEMORY_SIZE);
        float leratio = 0.125 + (map(gg.fx[fx_idx].granularVknobs[1],0,127,0,7875)/1000.0);

            dm.clean_title_1();
        canvastitle.print("Granular ");
        canvastitle.print(fx_idx + 1);
        float grain_speed = gg.fx[fx_idx].granularVknobs[1] / 127.0;
        float grain_size = gg.fx[fx_idx].granularVknobs[0] / 127.0;
        // grain_size
        coeffangle = (6.2831 - (grain_size)*6.2831) + 3.1416;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                          ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 1,
                            centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.setTextColor(SSD1306_WHITE);
        canvasBIG.print(legrainleng);
        canvasBIG.setCursor(centercirclex - knobradius + 1, 8);
        canvasBIG.print("Grain");
        // grain_speed
        coeffangle = (6.2831 - (grain_speed)*6.2831) + 3.1416;
        centercirclex = knobradius + 45;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 1, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print(leratio, 1);
        canvasBIG.setCursor(centercirclex - knobradius + 1, 8);
        canvasBIG.print("Ratio");
        if (!gg.fx[fx_idx].granular_freezing) {
          canvasBIG.drawRoundRect(80, 16, 128 - 80, 20, 2, SSD1306_WHITE);
          canvasBIG.setTextColor(SSD1306_WHITE);
          canvasBIG.setCursor(87, 16 + 6);
          canvasBIG.print("Freeze");
        } else {
          canvasBIG.fillRoundRect(80, 16, 128 - 80, 20, 2, SSD1306_WHITE);
          canvasBIG.setCursor(87, 16 + 6);
          canvasBIG.setTextColor(SSD1306_BLACK);
          canvasBIG.print("Freeze");
          canvasBIG.setTextColor(SSD1306_WHITE);
        }
        if (!gg.fx[fx_idx].granular_shifting) {
          canvasBIG.drawRoundRect(80, 16 + 20 + 4, 128 - 80, 20, 2, SSD1306_WHITE);
          canvasBIG.setCursor(87, 6 + 16 + 20 + 4);
          canvasBIG.setTextColor(SSD1306_WHITE);
          canvasBIG.print("Pitch");
        } else {
          canvasBIG.fillRoundRect(80, 16 + 20 + 4, 128 - 80, 20, 2, SSD1306_WHITE);
          canvasBIG.setCursor(87, 6 + 16 + 20 + 4);
          canvasBIG.setTextColor(SSD1306_BLACK);
          canvasBIG.print("Pitch");
          canvasBIG.setTextColor(SSD1306_WHITE);
        }
        // wetbar
        barsize = round(((gg.WetMixMasters[fx_idx + 1]/127.0) * (totbartall - 4)));
        canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall, wbarwidth2, 2, SSD1306_WHITE);
        canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4, SSD1306_WHITE);
        canvasBIG.setCursor(startlex2 - 6, 0);
        canvasBIG.print("Wet:");
        granularVpanelSelector(fx_idx);
        dm.dodisplay();
      }

void FxMenuRouter::bitcrusherctrl(byte fx_idx) {
        bitcrusher[fx_idx]->bits(gg.fx[fx_idx].bitcrusherVknobs[0]);
        bitcrusher[fx_idx]->sampleRate(round((gg.fx[fx_idx].bitcrusherVknobs[1] / 127.0) * 44100));
        bitcrusherR[fx_idx]->bits(gg.fx[fx_idx].bitcrusherVknobs[0]);
        bitcrusherR[fx_idx]->sampleRate(round((gg.fx[fx_idx].bitcrusherVknobs[1] / 127.0) * 44100));
      }

void FxMenuRouter::bitcrusherVpanelAction(byte fx_idx) {
        if (lv.navlevel == 4) {
          // AudioNoInterrupts();
          byte slct = lv.sublevels[3];
          // fq
          if (slct == 0) {
            lv.navrange = 16;
            gg.fx[fx_idx].bitcrusherVknobs[0] = lv.sublevels[4];
            bitcrusherctrl(fx_idx);
          }
          // res
          if (slct == 1) {
            lv.navrange = 127;
            gg.fx[fx_idx].bitcrusherVknobs[1] = lv.sublevels[4];
            bitcrusherctrl(fx_idx);
            // apply
          }

          if (slct == 2) {
            lv.navrange = 127;
            set_wet_mix_at_sub4(fx_idx);
          }
        }
        if (lv.navlevel > 4) {
          dm.returntonav(3);
        }
      }

void FxMenuRouter::bitcrusherVpanelSelector(byte fx_idx) {

        byte knobradius = 14;
        byte centercirclex = 25 + knobradius;
        byte centercircley = 16 + knobradius;
        byte startlex2 = 67;
        byte totbartall = 37;
        byte topwbarstart = 16;
        byte wbarwidth2 = 8;
        if (lv.navlevel == 3) {
          lv.navrange = 2;
        }
        int slct = lv.sublevels[3];
        // size
        if (slct == 0) {
          lv.sublevels[4] = gg.fx[fx_idx].bitcrusherVknobs[0];
          canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
        }
        // damp
        if (slct == 1) {
          lv.sublevels[4] = gg.fx[fx_idx].bitcrusherVknobs[1];
          canvasBIG.drawCircle(knobradius + 68, centercircley, knobradius - 2, SSD1306_WHITE);
        }

        // wet
        if (slct == 2) {
          lv.sublevels[4] = gg.WetMixMasters[fx_idx + 1] ;
          canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall, wbarwidth2 - 4, SSD1306_WHITE);
          canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
        }
      }

void FxMenuRouter::bitcrusherVpanel(byte fx_idx) {

        bitcrusherVpanelAction(fx_idx);
        byte knobradius = 14;
        byte centercirclex = 25 + knobradius;
        byte centercircley = 16 + knobradius;
        byte ftVcursorpointx;
        byte ftVcursorpointy;

        float coeffangle;
        byte totbartall = 37;
        byte topwbarstart = 16;
        byte wbarwidth2 = 8;
        byte barsize;
        byte startlex2 = 67;
            dm.clean_title_1();
        canvastitle.print("Bitcrusher ");
        canvastitle.print(fx_idx + 1);
        float lesamperate = gg.fx[fx_idx].bitcrusherVknobs[1] / 127.0;
        float lebitsz = gg.fx[fx_idx].bitcrusherVknobs[0] / 16.0;
        // Roomsize
        coeffangle = (6.2831 - (lebitsz)*6.2831) + 3.1416;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 5, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);

        canvasBIG.print(lebitsz * 16, 0);
        canvasBIG.setCursor(centercirclex - knobradius + 1, 8);
        canvasBIG.print("Bits");

        // damping
        coeffangle = (6.2831 - (lesamperate)*6.2831) + 3.1416;
        centercirclex = knobradius + 68;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 2, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print(lesamperate * 44100, 0);
        canvasBIG.setCursor(centercirclex - knobradius, 8);
        canvasBIG.print("S.Rate");

        // wetbar
        barsize = round(((gg.WetMixMasters[fx_idx + 1]/127.0) * (totbartall - 4)));
        canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall, wbarwidth2, 2, SSD1306_WHITE);
        canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4, SSD1306_WHITE);
        canvasBIG.setCursor(startlex2 - 6, 0);
        canvasBIG.print("Wet:");
        bitcrusherVpanelSelector(fx_idx);
        dm.dodisplay();
      }

void FxMenuRouter::freeverbscontrl(byte fx_idx) {
        //AudioNoInterrupts();
        //other reverb type, disabled for noisy noise
        //freeverbs[fx_idx]->roomsize(gg.fx[fx_idx].reverbVknobs[0] / 127.0);
        //freeverbs[fx_idx]->damping(gg.fx[fx_idx].reverbVknobs[1] / 127.0);
        freeverbs[fx_idx]->reverbTime((gg.fx[fx_idx].reverbVknobs[0] / 127.0)*10);
        freeverbsR[fx_idx]->reverbTime((gg.fx[fx_idx].reverbVknobs[0] / 127.0)*10);
        //AudioInterrupts();
      }

void FxMenuRouter::reverbVpanelAction(byte fx_idx) {
        if (lv.navlevel == 4) {
          // AudioNoInterrupts();
          byte slct = lv.sublevels[3];
          // fq
          if (slct == 0) {
            lv.navrange = 127;
            gg.fx[fx_idx].reverbVknobs[0] = lv.sublevels[4];
            freeverbscontrl(fx_idx);
          }
          // res
          //if (slct == 1) {
          //  lv.navrange = 127;
          //  gg.fx[fx_idx].reverbVknobs[1] = lv.sublevels[4];
          //  freeverbscontrl(fx_idx);
          //}
          if (slct == 1) {
            lv.navrange = 127;
            set_wet_mix_at_sub4(fx_idx);
          }
        }
        if (lv.navlevel > 4) {

          dm.returntonav(3);
        }
      }

void FxMenuRouter::reverbVpanelSelector(byte fx_idx) {
        byte knobradius = 14;
        byte centercirclex = 25 + knobradius;
        byte centercircley = 16 + knobradius;
        byte startlex2 = 67;
        byte totbartall = 37;
        byte topwbarstart = 16;
        byte wbarwidth2 = 8;
        if (lv.navlevel == 3) {
          lv.navrange = 1;
        }
        int slct = lv.sublevels[3];
        // second
        if (slct == 0) {
          lv.sublevels[4] = gg.fx[fx_idx].reverbVknobs[0];
          canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
        }
        // damp ( disabled , from other freeverb module)
        //if (slct == 1) {
        //  lv.sublevels[4] = gg.fx[fx_idx].reverbVknobs[1];
        //  canvasBIG.drawCircle(knobradius + 68, centercircley, knobradius - 2, SSD1306_WHITE);
        //}

        // wet
        if (slct == 1) {
          lv.sublevels[4] = gg.WetMixMasters[fx_idx + 1];
          canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall, wbarwidth2 - 4, SSD1306_WHITE);
          canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
        }
      }

void FxMenuRouter::reverbVpanel(byte fx_idx) {
        lv.navrange = 1;
        reverbVpanelAction(fx_idx);
        byte knobradius = 14;
        byte centercirclex = 25 + knobradius;
        byte centercircley = 16 + knobradius;
        byte ftVcursorpointx;
        byte ftVcursorpointy;

        float coeffangle;
        byte totbartall = 37;
        byte topwbarstart = 16;
        byte wbarwidth2 = 8;
        byte barsize;
        byte startlex2 = 67;
            dm.clean_title_1();
        canvastitle.print("Reverb ");
        canvastitle.print(fx_idx + 1);
        //float ledamping = gg.fx[fx_idx].reverbVknobs[1] / 127.0;
        float leroomsize = gg.fx[fx_idx].reverbVknobs[0] / 127.0;
        // Roomsize
        coeffangle = (6.2831 - (leroomsize)*6.2831) + 3.1416;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 1, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print(leroomsize*10, 2);
        canvasBIG.setCursor(centercirclex - knobradius + 1, 8);
        canvasBIG.print("Seconds");

        // damping
        //coeffangle = (6.2831 - (ledamping)*6.2831) + 3.1416;
        //centercirclex = knobradius + 68;
        //canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        //ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        //ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        //canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
        //canvasBIG.setCursor(centercirclex - knobradius + 1, centercircley + knobradius + 4);
        //canvasBIG.setTextSize(1);
        //canvasBIG.print(ledamping, 2);
        //canvasBIG.setCursor(centercirclex - knobradius + 1, 8);
        //canvasBIG.print("Damping");

        // wetbar
        barsize = round((gg.WetMixMasters[fx_idx + 1]/127.0) * (totbartall - 4));
        canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall, wbarwidth2, 2, SSD1306_WHITE);
        canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4, SSD1306_WHITE);
        canvasBIG.setCursor(startlex2 - 6, 0);
        canvasBIG.print("Wet:");
        reverbVpanelSelector(fx_idx);
        dm.dodisplay();
      }

void FxMenuRouter::delayVpanelAction(byte fx_idx) {
        if (lv.navlevel == 4) {
          // AudioNoInterrupts();
          byte slct = lv.sublevels[3];
          // time
          if (slct == 0) {
            lv.navrange = 127;
            gg.fx[fx_idx].delayVknobs[0] = lv.sublevels[4];
            restartdelayline(fx_idx);
          }
          // timeX
          if (slct == 1) {
            lv.navrange = 127;
            gg.fx[fx_idx].delayVknobs[1] = lv.sublevels[4];
            restartdelayline(fx_idx);
          }
          // feedback
          if (slct == 2) {
            lv.navrange = 127;
            gg.fx[fx_idx].delayVknobs[2] = lv.sublevels[4];
            restartdelayline(fx_idx);
          }
          if (slct == 3) {
            lv.navrange = 127;
            gg.WetMixMasters[fx_idx + 1] = lv.sublevels[4] ;
            _mx.wetmixmastercontrols();
          }
        }
        if (lv.navlevel > 4) {
          dm.returntonav(3);
        }
      }

void FxMenuRouter::delayVpanelSelector(byte fx_idx) {
        byte knobradius = 11;
        byte centercirclex = 15 + knobradius;
        byte centercircley = 16 + knobradius;
        byte startlex2 = 67;
        byte totbartall = 37;
        byte topwbarstart = 16;
        byte wbarwidth2 = 8;
        if (lv.navlevel == 3) {
          lv.navrange = 3;
        }
        byte slct = lv.sublevels[3];
        // size
        if (slct == 0) {
          lv.sublevels[4] = gg.fx[fx_idx].delayVknobs[0];
          canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
        }
        // damp
        if (slct == 1) {
          lv.sublevels[4] = gg.fx[fx_idx].delayVknobs[1];
          canvasBIG.drawCircle(centercirclex + 40, centercircley, knobradius - 2, SSD1306_WHITE);
        }

        if (slct == 2) {
          lv.sublevels[4] = gg.fx[fx_idx].delayVknobs[2];
          canvasBIG.drawCircle(centercirclex + 40 + 40, centercircley, knobradius - 2, SSD1306_WHITE);
        }

        // wet
        if (slct == 3) {
          lv.sublevels[4] = gg.WetMixMasters[fx_idx + 1];
          canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall, wbarwidth2 - 4, SSD1306_WHITE);
          canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
        }
      }

void FxMenuRouter::delayVpanel(byte fx_idx) {

        delayVpanelAction(fx_idx);
        byte knobradius = 11;
        byte centercirclex = 15 + knobradius;
        byte centercircley = 16 + knobradius;
        byte ftVcursorpointx;
        byte ftVcursorpointy;

        float coeffangle;
        byte totbartall = 37;
        byte topwbarstart = 16;
        byte wbarwidth2 = 8;
        byte barsize;
        byte startlex2 = 67;
            dm.clean_title_1();
        canvastitle.print("Delay ");
        canvastitle.print(fx_idx + 1);
        float delaytime = gg.fx[fx_idx].delayVknobs[0] / 127.0;
        float dephtflange = gg.fx[fx_idx].delayVknobs[1] / 127.0;
        float freqflange = gg.fx[fx_idx].delayVknobs[2] / 127.0;

        // Tsel
        coeffangle = (6.2831 - (delaytime)*6.2831) + 3.1416;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 1, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print(round((gg.fx[fx_idx].delayVknobs[0] / 127.0) * 7));
        // canvasBIG.setCursor(centercirclex-knobradius+1, 8);
        canvasBIG.setCursor(centercirclex - knobradius - 6, centercircley + knobradius + 4 + 10);
        canvasBIG.print("TSel");

        // TimeX
        coeffangle = (6.2831 - (dephtflange)*6.2831) + 3.1416;
        centercirclex = centercirclex + 40;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 1, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print(gg.fx[fx_idx].delayVknobs[1]);
        // canvasBIG.setCursor(centercirclex-knobradius+1, 8);
        canvasBIG.setCursor(centercirclex - knobradius - 2, centercircley + knobradius + 4 + 10);
        canvasBIG.print("TimeX");
        //feedback
        coeffangle = (6.2831 - (freqflange)*6.2831) + 3.1416;
        centercirclex = centercirclex + 40;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 1, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print(((gg.fx[fx_idx].delayVknobs[2] / 127.0)), 2);
        canvasBIG.setCursor(centercirclex - knobradius - 2, centercircley + knobradius + 4 + 10);
        // canvasBIG.setCursor(centercirclex-knobradius+1, 8);
        canvasBIG.print("Fback");

        // wetbar
        barsize = round(((gg.WetMixMasters[fx_idx + 1]/127.0) * (totbartall - 4)));
        canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall, wbarwidth2, 2, SSD1306_WHITE);
        canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4, SSD1306_WHITE);
        canvasBIG.setCursor(startlex2 - 6, 0);
        canvasBIG.print("Wet:");
        delayVpanelSelector(fx_idx);

        dm.dodisplay();
      }

void FxMenuRouter::filterVpanelAction(byte fx_idx) {
        if (lv.navlevel == 3) {
          self->filter_lfo_option = gg.fx[fx_idx].LFOonfilterz ;
        }
        if (lv.navlevel == 4) {
          byte slct = lv.sublevels[3];
          // fq
          if (slct == 0) {
            lv.navrange = 127;
            gg.fx[fx_idx].ffilterzVknobs[0] = lv.sublevels[4];
          }
          // res
          if (slct == 1) {
            lv.navrange = 127;
            gg.fx[fx_idx].ffilterzVknobs[1] = lv.sublevels[4];
          }
          // octaves
          if (slct == 2) {
            lv.navrange = 127;
            gg.fx[fx_idx].ffilterzVknobs[2] = lv.sublevels[4];
          }
          // lowpass
          if (slct == 3) {
            lv.navrange = 127;
            gg.fx[fx_idx].mixffilterzVknobs[0] = lv.sublevels[4];
          }
          // bandpass
          if (slct == 4) {
            lv.navrange = 127;
            gg.fx[fx_idx].mixffilterzVknobs[1] = lv.sublevels[4];
          }
          // high pass
          if (slct == 5) {
            lv.navrange = 127;
            gg.fx[fx_idx].mixffilterzVknobs[2] = lv.sublevels[4];
          }
          if (slct == 6) {
            //lv.navrange is 3 + 1 for none
            lv.navrange = OSCS_COUNT;
            self->filter_lfo_option = lv.sublevels[4];
            if (self->filter_lfo_option < OSCS_COUNT) {
              gg.fx[fx_idx].LFOonfilterz = self->filter_lfo_option;
            }
          }
          if (slct == 7) {
            lv.navrange = 127;
            set_wet_mix_at_sub4(fx_idx);
          }
          filtercontrols(fx_idx);
        }
        if (lv.navlevel > 4) {
          dm.returntonav(3);
        }
      }

void FxMenuRouter::lfoonfilterreplug(byte fx_idx) {
        unpluglfoonfilterz(fx_idx);
        if (gg.fx[fx_idx].LFOonfilterz < OSCS_COUNT) {
          LFOtoFilterz[((FXS_COUNT * fx_idx) + gg.fx[fx_idx].LFOonfilterz)]->connect();
          LFOtoFilterzR[((FXS_COUNT * fx_idx) + gg.fx[fx_idx].LFOonfilterz)]->connect();
        
          _lf.restartLFO((gg.fx[fx_idx].LFOonfilterz)%OSCS_COUNT);
        }

      }

void FxMenuRouter::unpluglfoonfilterz(byte fx_idx) {
        //each line has 3 lfo linked to a filter
        for (int i = 0; i < FXS_COUNT; i++) {
          LFOtoFilterz[fx_idx*FXS_COUNT+i]->disconnect();
          LFOtoFilterzR[fx_idx*FXS_COUNT+i]->disconnect();
        }
      }

void FxMenuRouter::filtercontrols(byte fx_idx) {
        gg.fx[fx_idx].filterzfreq = (gg.fx[fx_idx].ffilterzVknobs[0] / 127.0) * self->filterzrange;
        gg.fx[fx_idx].filterzreso = ((gg.fx[fx_idx].ffilterzVknobs[1]) / 127.0) * 5;
        if (gg.fx[fx_idx].filterzreso < 0.7) {
          gg.fx[fx_idx].filterzreso = 0.7;
        }
        gg.fx[fx_idx].filterzoctv = ((gg.fx[fx_idx].ffilterzVknobs[2]) / 127.0) * 7;
        gg.fx[fx_idx].filterzgainz[0] = (gg.fx[fx_idx].mixffilterzVknobs[0]) / 127.0;
        gg.fx[fx_idx].filterzgainz[1] = (gg.fx[fx_idx].mixffilterzVknobs[1]) / 127.0;
        gg.fx[fx_idx].filterzgainz[2] = (gg.fx[fx_idx].mixffilterzVknobs[2]) / 127.0;
        unpluglfoonfilterz(fx_idx);
        if (lv.sublevels[4] < OSCS_COUNT) {
          lfoonfilterreplug(fx_idx);
        }
        for (int i = 0; i < 3; i++) {
          mixfilter[fx_idx]->gain(i, gg.fx[fx_idx].filterzgainz[i]);
          mixfilterR[fx_idx]->gain(i, gg.fx[fx_idx].filterzgainz[i]);
        }
        filterz[fx_idx]->frequency(gg.fx[fx_idx].filterzfreq);
        filterz[fx_idx]->resonance(gg.fx[fx_idx].filterzreso);
        filterz[fx_idx]->octaveControl(gg.fx[fx_idx].filterzoctv);
        filterzR[fx_idx]->frequency(gg.fx[fx_idx].filterzfreq);
        filterzR[fx_idx]->resonance(gg.fx[fx_idx].filterzreso);
        filterzR[fx_idx]->octaveControl(gg.fx[fx_idx].filterzoctv);
      }
void FxMenuRouter::filterVpanel(byte fx_idx) {
        char LFOnamelist[4][6] = {"LFO1", "LFO2", "LFO3", "None"};
        filterVpanelAction(fx_idx);
        byte knobradius = 9;
        byte centercirclex = 5 + knobradius;
        byte centercircley = 35 + knobradius;
        byte ftVcursorpointx;
        byte ftVcursorpointy;

        float coeffangle;
        byte totbartall = 37;
        byte topwbarstart = 16;
        byte wbarwidth = 9;
        byte wbarwidth2 = 8;
        byte barsize;
        byte startlex2 = 67;

            dm.clean_title_1();
        canvastitle.print("Filter ");
        canvastitle.print(fx_idx + 1);
        canvastitle.setCursor(0, 8);
        // reflect lebq
        canvastitle.print("Ctrl: ");
        canvastitle.print((char *)LFOnamelist[self->filter_lfo_option]);

        // bqfreq
        coeffangle = (6.2831 - (gg.fx[fx_idx].ffilterzVknobs[0] / 127.0) * 6.2831) + 3.1416;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 4, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print("FQ");
        if (gg.fx[fx_idx].filterzfreq < 1000) {
          canvasBIG.setCursor(centercirclex - knobradius + 1, 24);
          canvasBIG.print(gg.fx[fx_idx].filterzfreq, 0);
        }
        if ((round(gg.fx[fx_idx].filterzfreq) < 9900) && (gg.fx[fx_idx].filterzfreq >= 1000)) {
          canvasBIG.setCursor(centercirclex - knobradius - 1, 24);
          canvasBIG.print(round(gg.fx[fx_idx].filterzfreq) / 1000.0, 1);
          canvasBIG.print("k");
        }
        if (gg.fx[fx_idx].filterzfreq >= 9900) {
          canvasBIG.setCursor(centercirclex - knobradius - 5, 24);
          canvasBIG.print(gg.fx[fx_idx].filterzfreq / 1000.0, 1);
          canvasBIG.print("k");
        }

        // resonnance
        coeffangle = (6.2831 - (gg.fx[fx_idx].ffilterzVknobs[1] / 127.0) * 6.2831) + 3.1416;
        centercirclex = knobradius + 30;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 1, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print("Res");
        canvasBIG.setCursor(centercirclex - knobradius + 2, 24);
        canvasBIG.print(gg.fx[fx_idx].filterzreso, 1);

        // octave
        coeffangle = (6.2831 - (gg.fx[fx_idx].ffilterzVknobs[2] / 127.0) * 6.2831) + 3.1416;
        centercirclex = knobradius + 55;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 1, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print("Oct");
        canvasBIG.setCursor(centercirclex - knobradius + 1, 24);
        canvasBIG.print(gg.fx[fx_idx].filterzoctv, 1);

        barsize = round((gg.fx[fx_idx].filterzgainz[0] * (totbartall - 4)));
        canvasBIG.drawRoundRect(81, topwbarstart, wbarwidth, totbartall, 2, SSD1306_WHITE);
        canvasBIG.fillRect(81 + 2, (totbartall + topwbarstart - barsize - 2), wbarwidth - 4, barsize, SSD1306_WHITE);
        canvasBIG.setCursor(81, totbartall + topwbarstart + 4);
        canvasBIG.print("LP");

        barsize = round((gg.fx[fx_idx].filterzgainz[1] * (totbartall - 4)));
        canvasBIG.drawRoundRect(98, topwbarstart, wbarwidth, totbartall, 2, SSD1306_WHITE);
        canvasBIG.fillRect(98 + 2, (totbartall + topwbarstart - barsize - 2), wbarwidth - 4, barsize, SSD1306_WHITE);
        canvasBIG.setCursor(97, totbartall + topwbarstart + 4);
        canvasBIG.print("BP");

        barsize = round((gg.fx[fx_idx].filterzgainz[2] * (totbartall - 4)));
        canvasBIG.drawRoundRect(115, topwbarstart, wbarwidth, totbartall, 2, SSD1306_WHITE);
        canvasBIG.fillRect(115 + 2, (totbartall + topwbarstart - barsize - 2), wbarwidth - 4, barsize, SSD1306_WHITE);
        canvasBIG.setCursor(114, totbartall + topwbarstart + 4);
        canvasBIG.print("HP");

        barsize = round(((gg.WetMixMasters[fx_idx + 1]/127.0) * (totbartall - 4)));
        canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall, wbarwidth2, 2, SSD1306_WHITE);
        canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4, SSD1306_WHITE);
        canvasBIG.setCursor(startlex2 - 6, 0);
        canvasBIG.print("Wet:");
        filterVpanelSelector(fx_idx);
        dm.dodisplay();
      }

void FxMenuRouter::filterVpanelSelector(byte fx_idx) {

        byte knobradius = 9;
        byte centercirclex = 5 + knobradius;
        byte centercircley = 35 + knobradius;
        byte totbartall = 37;
        byte topwbarstart = 16;
        byte wbarwidth = 9;
        int wbarwidth2 = 8;
        byte startlex2 = 67;
        if (lv.navlevel == 3) {
          lv.navrange = 8;
        }
        byte slct = lv.sublevels[3];
        // fq
        if (slct == 0) {
          lv.sublevels[4] = gg.fx[fx_idx].ffilterzVknobs[0];
          canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
        }
        // res
        if (slct == 1) {
          lv.sublevels[4] = gg.fx[fx_idx].ffilterzVknobs[1];
          canvasBIG.drawCircle(centercirclex + 25, centercircley, knobradius - 2, SSD1306_WHITE);
        }
        // oct
        if (slct == 2) {
          lv.sublevels[4] = gg.fx[fx_idx].ffilterzVknobs[2];
          canvasBIG.drawCircle(centercirclex + 50, centercircley, knobradius - 2, SSD1306_WHITE);
        }
        // lp
        if (slct == 3) {
          lv.sublevels[4] = gg.fx[fx_idx].mixffilterzVknobs[0];
          canvasBIG.drawRect(83, topwbarstart, wbarwidth - 4, totbartall, SSD1306_WHITE);
        }
        // bp
        if (slct == 4) {
          lv.sublevels[4] = gg.fx[fx_idx].mixffilterzVknobs[1];
          canvasBIG.drawRect(100, topwbarstart, wbarwidth - 4, totbartall, SSD1306_WHITE);
        }
        // hp
        if (slct == 5) {
          lv.sublevels[4] = gg.fx[fx_idx].mixffilterzVknobs[2];
          canvasBIG.drawRect(117, topwbarstart, wbarwidth - 4, totbartall, SSD1306_WHITE);
        }
        // Select LFO
        if (slct == 6) {
          lv.sublevels[4] = self->filter_lfo_option;
          canvasBIG.setCursor(64, 8);
          canvasBIG.print((char)9);
        }
        if (slct == 7) {
          lv.sublevels[4] = gg.WetMixMasters[fx_idx + 1];
          canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0, totbartall, wbarwidth2, SSD1306_WHITE);
          canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
        }
      }

void FxMenuRouter::biquadVpanelAction(byte fx_idx) {
        if (lv.navlevel == 4) {
          byte slct = lv.sublevels[3];
          // stage
          if (slct == 0) {
            lv.navrange = 3;
            gg.fx[fx_idx].bqstage = lv.sublevels[4];
          }
          // mode
          if (slct == 1) {
            lv.navrange = 6;
            gg.fx[fx_idx].bqtype[gg.fx[fx_idx].bqstage] = lv.sublevels[4];
          }
          // freq
          if (slct == 2) {
            lv.navrange = 127;
            gg.fx[fx_idx].bqVpot[gg.fx[fx_idx].bqstage][0] = lv.sublevels[4];
            gg.fx[fx_idx].bqfreq[gg.fx[fx_idx].bqstage] =
                (((gg.fx[fx_idx].bqVpot[gg.fx[fx_idx].bqstage][0]) / 127.0) * self->bqrange) + 101;
          }
          // slope or Q
          if (slct == 3) {
            lv.navrange = 127;
            gg.fx[fx_idx].bqVpot[gg.fx[fx_idx].bqstage][1] = lv.sublevels[4];
            gg.fx[fx_idx].bqslope[gg.fx[fx_idx].bqstage] = 0.001 + 5.0 * ((gg.fx[fx_idx].bqVpot[gg.fx[fx_idx].bqstage][1]) / 127.0);
          }
          // gain
          if (slct == 5) {
            lv.navrange = 127;
            gg.fx[fx_idx].bqVpot[gg.fx[fx_idx].bqstage][2] = lv.sublevels[4];
            gg.fx[fx_idx].bqgain[gg.fx[fx_idx].bqstage] = 100.0 - ((gg.fx[fx_idx].bqVpot[gg.fx[fx_idx].bqstage][2]) / 127.0) * 200.0 ;
          }
          // to avoid setting up a stage unconfigured while browsing
          if (gg.fx[fx_idx].bqfreq[gg.fx[fx_idx].bqstage] >= 101) {
            biquadcontrols(fx_idx);
          }
          if (slct == 4) {
            lv.navrange = 127;
            set_wet_mix_at_sub4(fx_idx);
          }
        }
        if (lv.navlevel > 4) {

          dm.returntonav(3);
        }
      }

void FxMenuRouter::biquadVpanel(byte fx_idx) {
        char bqtypeLabels[7][12] = {"Low Pass", "High Pass", "Band Pass",
                                    "Notch",    "LowShelf",  "High Shelf","Param EQ"};
        biquadVpanelAction(fx_idx);
        byte knobradius = 12;
        byte centercirclex = 10 + knobradius;
        byte centercircley = 28 + knobradius;
        byte wbarwidth2 = 7;
        byte bqVcursorpointx;
        byte bqVcursorpointy;
        byte startlex2 = 67;
        float coeffangle;
        byte totbartall = 24;
        byte topwbarstart = 16 + 12;
        byte wbarwidth = 9;
        byte barsize = round((gg.fx[fx_idx].bqVpot[gg.fx[fx_idx].bqstage][2] / 127.0) * (totbartall - 4));
            dm.clean_title_1();
        canvastitle.print("Biquad ");
        canvastitle.print(fx_idx + 1);
        canvastitle.setCursor(107, 8);
        // reflect lebq
        canvastitle.print("s:");
        canvastitle.print(gg.fx[fx_idx].bqstage + 1);

        canvastitle.setCursor(0, 8);
        canvastitle.print("mode: ");
        canvastitle.print((char *)bqtypeLabels[gg.fx[fx_idx].bqtype[gg.fx[fx_idx].bqstage]]);
        // bqfreq
        coeffangle = (6.2831 - (gg.fx[fx_idx].bqVpot[gg.fx[fx_idx].bqstage][0] / 127.0) * 6.2831) + 3.1416;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        bqVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        bqVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, bqVcursorpointx, bqVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print("Freq.");
        if (gg.fx[fx_idx].bqfreq[gg.fx[fx_idx].bqstage] < 1000) {
          canvasBIG.setCursor(centercirclex - knobradius + 4, 18);
        }
        if ((gg.fx[fx_idx].bqfreq[gg.fx[fx_idx].bqstage] < 10000) && (gg.fx[fx_idx].bqfreq[gg.fx[fx_idx].bqstage] >= 1000)) {
          canvasBIG.setCursor(centercirclex - knobradius + 2, 18);
        }
        if (gg.fx[fx_idx].bqfreq[gg.fx[fx_idx].bqstage] >= 10000) {
          canvasBIG.setCursor(centercirclex - knobradius - 2, 18);
        }
        canvasBIG.print(gg.fx[fx_idx].bqfreq[gg.fx[fx_idx].bqstage], 0);
        // bqslope
        coeffangle = (6.2831 - (gg.fx[fx_idx].bqVpot[gg.fx[fx_idx].bqstage][1] / 127.0) * 6.2831) + 3.1416;
        centercirclex = knobradius + 50;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        bqVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        bqVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, bqVcursorpointx, bqVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print("Slope");
        canvasBIG.setCursor(centercirclex - knobradius, 18);
        canvasBIG.print(gg.fx[fx_idx].bqslope[gg.fx[fx_idx].bqstage]);
        // gain if  setLowShelf or sethighShelf
        if (gg.fx[fx_idx].bqtype[gg.fx[fx_idx].bqstage] > 3) {
          canvasBIG.drawRoundRect(95, topwbarstart, wbarwidth, totbartall, 2, SSD1306_WHITE);
          canvasBIG.fillRect(95 + 2, (totbartall + topwbarstart - barsize - 2), wbarwidth - 4, barsize, SSD1306_WHITE);
          canvasBIG.setCursor(90, totbartall + topwbarstart + 4);
          canvasBIG.print("Gain");
          canvasBIG.setCursor(90, 18);
          canvasBIG.print(gg.fx[fx_idx].bqgain[gg.fx[fx_idx].bqstage]);
        }
        barsize = round(((gg.WetMixMasters[fx_idx + 1]/127.0) * (totbartall + 13 - 4)));
        canvasBIG.drawRoundRect(topwbarstart - 12 + startlex2 + 4, 0, totbartall + 13, wbarwidth2, 2, SSD1306_WHITE);
        canvasBIG.fillRect((topwbarstart - 12 + startlex2 + 6), 2, barsize, wbarwidth2 - 4, SSD1306_WHITE);
        canvasBIG.setCursor(startlex2 - 6, 0);
        canvasBIG.print("Wet:");
        biquadVpanelSelector(fx_idx);
        dm.dodisplay();
      }

void FxMenuRouter::biquadVpanelSelector(byte fx_idx) {
        byte startlex2 = 67;
        byte totbartall = 37;
        byte topwbarstart = 16;
        byte wbarwidth2 = 7;
        if (lv.navlevel == 3) {
          lv.navrange = 4;
          if (gg.fx[fx_idx].bqtype[gg.fx[fx_idx].bqstage] > 3) {
            lv.navrange = 5;
          }
        }
        byte slct = lv.sublevels[3];
        // stage
        if (slct == 0) {
          lv.sublevels[4] = gg.fx[fx_idx].bqstage;
          canvasBIG.setCursor(103, 9);
          canvasBIG.print((char)9);
        }
        // mode
        if (slct == 1) {
          lv.sublevels[4] = gg.fx[fx_idx].bqtype[gg.fx[fx_idx].bqstage];
          canvasBIG.setCursor(29, 8);
          canvasBIG.print((char)9);
        }
        // freq
        if (slct == 2) {
          lv.sublevels[4] = gg.fx[fx_idx].bqVpot[gg.fx[fx_idx].bqstage][0];
          canvasBIG.setCursor(20, 36);
          canvasBIG.print((char)9);
        }
        // slope
        if (slct == 3) {
          lv.sublevels[4] = gg.fx[fx_idx].bqVpot[gg.fx[fx_idx].bqstage][1];
          canvasBIG.setCursor(60, 36);
          canvasBIG.print((char)9);
        }
        // gain
        if (slct == 5) {
          lv.sublevels[4] = gg.fx[fx_idx].bqVpot[gg.fx[fx_idx].bqstage][2];
          canvasBIG.setCursor(89, 36);
          canvasBIG.print((char)9);
        }

        if (slct == 4) {
          lv.sublevels[4] = gg.WetMixMasters[fx_idx + 1];
          canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall, wbarwidth2 - 4, SSD1306_WHITE);
          canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
        }
      }

void FxMenuRouter::allfxcontrolled() {
        for (int i = 0; i < 3; i++) {
          switch(gg.fx[i].plugged_fx){
            case 0:
            //multiply
            break;
            case 1:
              freeverbscontrl(i);
            break;
            case 2:
              granularcontrols(i);
            break;
            case 3:
              bitcrusherctrl(i);
            break;
            case 4:
              flangercontrols(i);
            break;
            case 5:
              choruscontrols(i);
            break;
            case 6:
              for (int j = 0; j < STAGES_BQ; j++) {
                //TODO: REDO
                //to avoid configuring unused biquad filters stages
                if (gg.fx[i].bqfreq[j] >= 101) {
                  biquadcontrols(i);
                  break;
                }
              }
            break;
            case 7:
              filtercontrols(i);
            break;
            case 8:
              restartdelayline(i);
            break;

            default:
            break;
          }
        }
      }

void FxMenuRouter::fx_nav_zero(){
        if (lv.navlevel < 2) dm.reinitsublevels(2);
        lv.avoid_fx_bounce = false ;
        lv.navrange = self->home_navrange;
        display.clearDisplay();
        dolistmainfxlines();
        dm.dodisplay();
        lv.sublevels[2] = gg.fx[lv.sublevels[1]%FXS_COUNT].plugged_fx ;
      }

void FxMenuRouter::fx_nav_one(){
        if (lv.navlevel < 2) dm.reinitsublevels(2);
        lv.avoid_fx_bounce = false ;
        display.clearDisplay();
        if (lv.navlevel == 2) lv.navrange = 9;
        dolistMainFxPanel();
        dm.dodisplay();
      }

void FxMenuRouter::fx_nav_two(){
        //remember to manage lv.avoid_fx_bounce if plugging fx outside of menu
        if (!lv.avoid_fx_bounce){
          lv.avoid_fx_bounce = true ;
          gg.fx[lv.sublevels[1]].route_fx(lv.sublevels[2]);
        }
          displayfxVcontrols(lv.sublevels[1]);
      }

void FxMenuRouter::MainFxPanel() {
        //if (lv.sublevels[lv.navlevel] > lv.navrange) dm.reinitsublevels(lv.navlevel);

        if (lv.navlevel == 1) {
          fx_nav_zero();
        }
        if (lv.navlevel == 2) {
          fx_nav_one();
        }
        if (lv.navlevel > 2) {
          fx_nav_two();
        }
      }


