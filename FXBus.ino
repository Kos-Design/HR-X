
class FxBus {
  public:
    byte f_index = 0 ;
    bool active = 0 ;
    byte plugged_fx_type = mainmenufxlistsize-1;
    //find safe off value
    int premixesMto_index = 1000 ;
    int fxcording_index = 1000 ;

    FxBus(byte f_index) : f_index(f_index) {}

    void route_fx(byte selected_fx_type) {
      //remembver to manage avoid_fx_bounce if plugging fx outside of menu
      if (!avoid_fx_bounce){
        avoid_fx_bounce = true ;
        if (plugged_fx_type != (mainmenufxlistsize - 1)) {
          unplug_fx_line();
        }
        if (selected_fx_type != (mainmenufxlistsize - 1)) {
          plug_fx_line(selected_fx_type);
          plugged_fx_type = selected_fx_type;
        }
      }
    }

    void plug_fx_line(byte selected_fx_type){
      AudioNoInterrupts();
      //delay
      if (selected_fx_type == 8) {
        delayCords[f_index]->connect();
      }
      if (selected_fx_type == 4) {
        flange[f_index]->begin(flangedelays[f_index],FLANGE_DELAY_LENGTH,flangeoffset,flangedepth,flangefreq[f_index]);
        flange[f_index]->voices(FLANGE_DELAY_PASSTHRU,0,0);
      }
      if (selected_fx_type == 5) {
        chorus[f_index]->begin(chorusdelaylines[f_index],CHORUS_DELAY_LENGTH,chorusvoices[f_index]) ;
      }
      premixesMto_index = (selected_fx_type * fxs_count) + (f_index);
      fxcording_index = (selected_fx_type*fxs_count*2*3) + (f_index*fxs_count*2) + (2*f_index);
      premixesMto[premixesMto_index]->connect();
      fxcording[fxcording_index]->connect();
      fxcording[fxcording_index + 1]->connect();
      AudioInterrupts();
    }

    void stopdelayline() {

      for (int j = 0; j < 8; j++) {
        lesdelays[f_index]->disable(j);
      }
    }

    void unplug_fx_line() {
      AudioNoInterrupts();
      premixesMto[premixesMto_index]->disconnect();
      fxcording[fxcording_index]->disconnect();
      fxcording[fxcording_index + 1]->disconnect();
      premixesMto_index = 1000;
      fxcording_index = 1000;
      stopdelayline();
      delayCords[f_index]->disconnect();
      AudioInterrupts();
      plugged_fx_type = mainmenufxlistsize-1;
    }
};

FxBus* fx[fxs_count]={nullptr};

class FxMenuRouter : public SectionHolder {
  public:
      FxMenuRouter() {
                      self = this ;
                      self->home_navrange=2;
                      self->relative_navlevel=1;
                      self->max_navlevel=5;
                      self->sublevels_address={6,0,0};
                      //home method not really used yet
                      //this->set_home(call_fx_mainpanel);
                      }

      static void show() {
        _nav_fx[sublevels[1]](); 
      }

      static void dolistMainFxPanel() {
        byte startx = 5;
        byte starty = 16;
        char *textin = (char *)mainmenufxlist[sublevels[navlevel]];
        dm.clear_buffs_2_1();
        canvastitle.println(textin);

        for (int filer = 0; filer < navrange - (sublevels[navlevel]); filer++) {
          canvasBIG.setCursor(startx, starty + (filer*10));
          canvasBIG.println(mainmenufxlist[sublevels[navlevel] + 1 + filer]);
        }
        for (int filer = 0; filer < sublevels[navlevel]; filer++) {
          canvasBIG.setCursor(startx, (10 * (navrange + 1 - sublevels[navlevel])) + 6 + (filer*10));
          canvasBIG.println(mainmenufxlist[filer]);
        }
      }

      static void dolistmainfxlines() {

        char mainfxlineslist[fxs_count][12] = {"FX Line1", "FX Line2", "FX Line3"};
        byte startx = 5;
        byte starty = 16;
        String textin;
        if (fx[sublevels[1]%fxs_count]->plugged_fx_type != (mainmenufxlistsize - 1)) {
          textin = (String)mainmenufxlist[fx[sublevels[1]%fxs_count]->plugged_fx_type];
        } else {
          textin = (String)mainfxlineslist[sublevels[1]%fxs_count];
        }
        dm.clear_buffs_2_1();
        canvastitle.println(textin);
        for (int i = 0; i < fxs_count - 1 - sublevels[1]; i++) {
          canvasBIG.setCursor(startx, starty + ((i)*10));
          if (fx[sublevels[1]%fxs_count + 1 + i]->plugged_fx_type != mainmenufxlistsize-1) {
            canvasBIG.println((String)mainmenufxlist[fx[sublevels[1]%fxs_count + 1 + i]->plugged_fx_type]);
          } else {
            canvasBIG.println(mainfxlineslist[sublevels[1]%fxs_count + 1 + i]);
          }
        }
        for (int i = 0; i < sublevels[1]%fxs_count; i++) {
          canvasBIG.setCursor(startx, (10 * (fxs_count - (sublevels[1]%fxs_count)) + 6 + ((i)*10)));
          if (fx[i]->plugged_fx_type != (mainmenufxlistsize - 1)) {
            canvasBIG.println((String)mainmenufxlist[fx[i]->plugged_fx_type]);
          } else {
            canvasBIG.println(mainfxlineslist[i]);
          }
        }
      }

      static void biquadcontrols(byte lebiquad) {
        // AudioNoInterrupts();

        switch (bqtype[lebiquad][bqstage[lebiquad]]) {
        case 0:

          biquad[lebiquad]->setLowpass(bqstage[lebiquad],
                                      bqfreq[lebiquad][bqstage[lebiquad]],
                                      bqslope[lebiquad][bqstage[lebiquad]]);

          break;
        case 1:

          biquad[lebiquad]->setHighpass(bqstage[lebiquad],
                                        bqfreq[lebiquad][bqstage[lebiquad]],
                                        bqslope[lebiquad][bqstage[lebiquad]]);

          break;
        case 2:

          biquad[lebiquad]->setBandpass(bqstage[lebiquad],
                                        bqfreq[lebiquad][bqstage[lebiquad]],
                                        bqslope[lebiquad][bqstage[lebiquad]]);

          break;
        case 3:

          biquad[lebiquad]->setNotch(bqstage[lebiquad],
                                    bqfreq[lebiquad][bqstage[lebiquad]],
                                    bqslope[lebiquad][bqstage[lebiquad]]);

          break;
        case 4:

          biquad[lebiquad]->setLowShelf(bqstage[lebiquad],
                                        bqfreq[lebiquad][bqstage[lebiquad]],
                                        bqgain[lebiquad][bqstage[lebiquad]],
                                        bqslope[lebiquad][bqstage[lebiquad]]);

          break;
        case 5:

          biquad[lebiquad]->setHighShelf(bqstage[lebiquad],
                                        bqfreq[lebiquad][bqstage[lebiquad]],
                                        bqgain[lebiquad][bqstage[lebiquad]],
                                        bqslope[lebiquad][bqstage[lebiquad]]);

          break;
          break;
        }
        // AudioInterrupts();
      }

      static void delaycontrols(byte ledelayline, int gronint) {

        AudioNoInterrupts();
        if (gronint >= 0 && gronint < 100) {
          interpot = map(gronint, 0, 100, 0, 1);
          delaypremix[2 * ledelayline]->gain(0, 1 - interpot);
          delaypremix[2 * ledelayline]->gain(1, interpot);
        }
        if (gronint >= 100 && gronint < 250) {
          interpot = map(gronint, 100, 250, 0, 1);
          delaypremix[2 * ledelayline]->gain(1, 1 - interpot);
          delaypremix[2 * ledelayline]->gain(2, interpot);
        }
        if (gronint >= 250 && gronint < 400) {
          interpot = map(gronint, 250, 400, 0, 1);
          delaypremix[2 * ledelayline]->gain(2, 1 - interpot);
          delaypremix[2 * ledelayline]->gain(3, interpot);
        }
        if (gronint >= 400 && gronint < 550) {
          interpot = map(gronint, 400, 550, 0, 1);
          delaypremix[2 * ledelayline]->gain(3, 1 - interpot);
          delaypremix[2 * ledelayline + 1]->gain(0, interpot);
        }
        if (gronint >= 550 && gronint < 700) {
          interpot = map(gronint, 550, 700, 0, 1);
          delaypremix[2 * ledelayline + 1]->gain(0, 1 - interpot);
          delaypremix[2 * ledelayline + 1]->gain(1, interpot);
        }
        if (gronint >= 700 && gronint < 850) {
          interpot = map(gronint, 700, 850, 0, 1);
          delaypremix[2 * ledelayline + 1]->gain(1, 1 - interpot);
          delaypremix[2 * ledelayline + 1]->gain(2, interpot);
        }
        if (gronint >= 850 && gronint <= 1024) {
          interpot = map(gronint, 850, 1024, 0, 1);
          delaypremix[2 * ledelayline + 1]->gain(2, 1 - interpot);
          delaypremix[2 * ledelayline + 1]->gain(3, interpot);
        }
        AudioInterrupts();
      }
      
      static void delayfeedback(byte lefilter, float lesmallfloat) {
        // delay feedback
        if (smallfloat <= 0.1) {
          delayprefeed[lefilter]->gain(0, 0);
          delayprefeed[lefilter]->gain(1, 0);
          delayfeedbackmix[lefilter]->gain(0, 1.0);
          delayfeedbackmix[lefilter]->gain(1, 0);
        } else {
          delayprefeed[lefilter]->gain(0, 1.0);
          delayprefeed[lefilter]->gain(1, 1.0);
          delayfeedbackmix[lefilter]->gain(0, 1.0 - lesmallfloat);
          delayfeedbackmix[lefilter]->gain(1, lesmallfloat);
        }
        // restartdelayline(lefilter);
      }

      static void delaytimingselect(int lefilter, int leselecta) {
        int leselectee = map(leselecta, 0, 127, 0, 7);

        for (int j = 0; j < 4; j++) {
          delaypremix[2 * lefilter]->gain(j, 0);
          delaypremix[2 * lefilter + 1]->gain(j, 0);
        }
        if (leselectee < 4) {
          delaypremix[2 * lefilter]->gain(leselectee, 1);
        }
        if (leselectee >= 4) {
          delaypremix[2 * lefilter + 1]->gain(leselectee - 4, 1);
        }
        // restartdelayline(lefilter);
      }

      static void restartdelayline(int lefilter) {

        delaymultiplier[lefilter] = delayVknobs[lefilter][1] + 1;
        delaytimingselect(lefilter, delayVknobs[lefilter][0]);

        delayfeedback(lefilter, (delayVknobs[lefilter][2] / 127.0) * 0.45);
        //8 is delay obj tap channels
        for (int j = 0; j < 8; j++) {

          lesdelays[lefilter]->delay(j, delaymultiplier[lefilter] * (j + 2));
        }
      }
      
      static void changebiquadfreqvalue(byte lebiquad, int valub) {
        // valub range 1024
        bqfreq[lebiquad][bqstage[lebiquad]] = valub * 3;
        biquadcontrols(lebiquad);
      }

      static void displayfxVcontrols(byte fxinstance) {
        //TODO:make switch
        if (sublevels[2] == 6) {
          biquadVpanel(fxinstance);
        }
        if (sublevels[2] == 7) {
          filterVpanel(fxinstance);
        }
        if (sublevels[2] == 8) {
          delayVpanel(fxinstance);
        }
        if (sublevels[2] == 1) {
          reverbVpanel(fxinstance);
        }
        if (sublevels[2] == 3) {
          bitcrusherVpanel(fxinstance);
        }
        if (sublevels[2] == 2) {
          granularVpanel(fxinstance);
        }
        if (sublevels[2] == 5) {
          chorusVpanel(fxinstance);
        }
        if (sublevels[2] == 4) {
          flangerVpanel(fxinstance);
        }
        if (sublevels[2] == 9 || sublevels[2] == 0) {
          navlevel--;
        }
      }
      static void flangercontrols(byte lefilter) {
        flangeoffset =
            round((flangerVknobs[lefilter][0] / 127.0) * FLANGE_DELAY_LENGTH / 4);
        flangedepth =
            round((flangerVknobs[lefilter][1] / 127.0) * FLANGE_DELAY_LENGTH / 4);
        flangefreq[lefilter] = (double)(flangerVknobs[lefilter][2] / 127.0) * 2;
        // AudioNoInterrupts();
        flange[lefilter]->voices(flangeoffset, flangedepth, flangefreq[lefilter]);
        // AudioInterrupts();
      }
      static void flangerVpanelAction(byte lefilter) {
        if (navlevel == 4) {
          // AudioNoInterrupts();
          byte slct = sublevels[3];
          // offset
          if (slct == 0) {
            navrange = 127;
            flangerVknobs[lefilter][0] = sublevels[4];
            flangercontrols(lefilter);
          }
          // depth
          if (slct == 1) {
            navrange = 127;
            flangerVknobs[lefilter][1] = sublevels[4];
            flangercontrols(lefilter);
            // apply
          }
          // delayRate
          // depth
          if (slct == 2) {
            navrange = 127;
            flangerVknobs[lefilter][2] = sublevels[4];
            flangercontrols(lefilter);
            // apply
          }
          if (slct == 3) {
            navrange = 127;
            set_wet_mix_at_sub4(lefilter);
          }
        }
        if (navlevel > 4) {
          returntonav(3);
        }
      }

      static void set_wet_mix_at_sub4(byte i){
        WetMixMasters[i + 1] = sublevels[4] ;
        _mx.wetmixmastercontrols();
      }

      static void flangerVpanelSelector(byte lefilter) {
        byte knobradius = 11;
        byte centercirclex = 15 + knobradius;
        byte centercircley = 16 + knobradius;
        byte startlex2 = 67;
        byte totbartall = 37;
        byte topwbarstart = 16;
        byte wbarwidth2 = 8;
        if (navlevel == 3) {
          navrange = 3;
        }
        byte slct = sublevels[3];
        // size
        if (slct == 0) {
          sublevels[4] = flangerVknobs[lefilter][0];
          canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2,
                              SSD1306_WHITE);
        }
        // damp
        if (slct == 1) {
          sublevels[4] = flangerVknobs[lefilter][1];
          canvasBIG.drawCircle(centercirclex + 40, centercircley, knobradius - 2,
                              SSD1306_WHITE);
        }

        if (slct == 2) {
          sublevels[4] = flangerVknobs[lefilter][2];
          canvasBIG.drawCircle(centercirclex + 40 + 40, centercircley, knobradius - 2,
                              SSD1306_WHITE);
        }

        // wet
        if (slct == 3) {
          sublevels[4] = WetMixMasters[lefilter+ 1];
          canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall, wbarwidth2 - 4, SSD1306_WHITE);
          canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
        }
      }

      static void flangerVpanel(byte lefilter) {

        flangerVpanelAction(lefilter);
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
        canvastitle.print(lefilter + 1);
        //  flangerVknobs[lefilter][0] ;
        // float dephtflange = flangerVknobs[lefilter][1]/127.0 ;
        // float freqflange = flangerVknobs[lefilter][2]/127.0 ;
        // voices(flangeoffset, flangedepth, flangefreq);
        // Roomsize
        coeffangle = (6.2831 - (flangerVknobs[lefilter][0] / 127.0) * 6.2831) + 3.1416;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 1, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);

        canvasBIG.print(round((flangerVknobs[lefilter][0] / 127.0) * FLANGE_DELAY_LENGTH / 4));
        // canvasBIG.setCursor(centercirclex-knobradius+1, 8);
        canvasBIG.setCursor(centercirclex - knobradius - 6, centercircley + knobradius + 4 + 10);
        canvasBIG.print("Offset");

        // damping
        coeffangle = (6.2831 - (flangerVknobs[lefilter][1] / 127.0) * 6.2831) + 3.1416;
        centercirclex = centercirclex + 40;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 1, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print(
            round((flangerVknobs[lefilter][1] / 127.0) * FLANGE_DELAY_LENGTH / 4));
        // canvasBIG.setCursor(centercirclex-knobradius+1, 8);
        canvasBIG.setCursor(centercirclex - knobradius - 2, centercircley + knobradius + 4 + 10);
        canvasBIG.print("Depth");

        coeffangle =
            (6.2831 - (flangerVknobs[lefilter][2] / 127.0) * 6.2831) + 3.1416;
        centercirclex = centercirclex + 40;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 1, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print(((flangerVknobs[lefilter][2] / 127.0) * 2), 2);
        canvasBIG.setCursor(centercirclex - knobradius - 2, centercircley + knobradius + 4 + 10);
        // canvasBIG.setCursor(centercirclex-knobradius+1, 8);
        canvasBIG.print("Delay");

        // wetbar
        barsize = round((WetMixMasters[lefilter + 1] /127.0) * (totbartall - 4));
        canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall, wbarwidth2, 2, SSD1306_WHITE);
        canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4, SSD1306_WHITE);
        canvasBIG.setCursor(startlex2 - 6, 0);
        canvasBIG.print("Wet:");
        flangerVpanelSelector(lefilter);
        dm.dodisplay();
      }

      static void choruscontrols(byte lefilter) {
        chorusvoices[lefilter] = round((chorusVknobs[lefilter] / 127.0) * 8) ;
        chorus[lefilter]->voices(chorusvoices[lefilter]);
      }

      static void chorusVpanelAction(byte lefilter) {
        if (navlevel == 4) {
          // AudioNoInterrupts();
          byte slct = sublevels[3];
          // fq
          if (slct == 0) {
            navrange = 127;
            chorusVknobs[lefilter] = sublevels[4];
            choruscontrols(lefilter);
          }
          // res
          if (slct == 1) {
            navrange = 127;
            set_wet_mix_at_sub4(lefilter);
          }
        }
        if (navlevel > 4) {
          returntonav(3);
        }
      }

      static void chorusVpanelSelector(byte lefilter) {

        byte knobradius = 16;
        byte centercirclex = 48 + knobradius;
        byte centercircley = 16 + knobradius;
        byte startlex2 = 67;
        byte totbartall = 37;
        byte topwbarstart = 16;
        byte wbarwidth2 = 8;
        if (navlevel == 3) {
          navrange = 1;
        }
        int slct = sublevels[3];
        // size
        if (slct == 0) {
          sublevels[4] = chorusVknobs[lefilter];
          canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2,
                              SSD1306_WHITE);
        }

        // wet
        if (slct == 1) {
          sublevels[4] = WetMixMasters[lefilter + 1];
          canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall,
                            wbarwidth2 - 4, SSD1306_WHITE);
          canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
        }
      }

      static void chorusVpanel(byte lefilter) {

        chorusVpanelAction(lefilter);
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
        canvastitle.print(lefilter + 1);

        float leroomsize = chorusVknobs[lefilter] / 127.0;
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
        canvasBIG.print(round((chorusVknobs[lefilter] / 127.0) * 8));
        canvasBIG.setCursor(centercirclex - knobradius - 1, 8);
        canvasBIG.print("Voices");

        // wetbar
        barsize =
            round((WetMixMasters[lefilter + 1]/127.0) *
                  (totbartall - 4));
        canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall,
                                wbarwidth2, 2, SSD1306_WHITE);
        canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4,
                          SSD1306_WHITE);
        canvasBIG.setCursor(startlex2 - 6, 0);
        canvasBIG.print("Wet:");

        chorusVpanelSelector(lefilter);

        dm.dodisplay();
      }

      static void granular_pitch_shift(byte lefilter){
        // up to 1/3 of GRANULAR_MEMORY_SIZE in ms equivalent !!!
        //float leratio = (granularVknobs[lefilter][1] / 127.0) * 3.0;
        int maxgrain = (int)(0.027 * GRANULAR_MEMORY_SIZE );// up to (GRANULAR_MEMORY_SIZE / 290) ms if grain is 12800 so ratio of 0.027 of GRANULAR_MEMORY_SIZE
        float legrainleng = 1.0 * map(granularVknobs[lefilter][0],0,127,1,maxgrain) ;
        if (granular_shifting[lefilter]) {
          if (!granular_freezing[lefilter]) {
            granular[lefilter]->begin(granularMemories[lefilter], GRANULAR_MEMORY_SIZE);
          }
          granularcontrols(lefilter);
          granular[lefilter]->beginPitchShift(legrainleng);
          //octavedown1.begin(120.0, 33.0);

        } else if(granular_freezing[lefilter]){
            granular_freeze(lefilter);
        } else {
          granular[lefilter]->stop();
          //octavedown1.end();
        }
      }

      static void granular_freeze(byte lefilter){
        int maxgrain = (int)(0.027 * GRANULAR_MEMORY_SIZE );// up to (GRANULAR_MEMORY_SIZE / 290) ms if grain is 12800 so ratio of 0.027 of GRANULAR_MEMORY_SIZE
        float legrainleng = 0.75*map(granularVknobs[lefilter][0],0,127,1,maxgrain) ;
        if (granular_freezing[lefilter]) {
          if (!granular_shifting[lefilter]) {
            granular[lefilter]->begin(granularMemories[lefilter], GRANULAR_MEMORY_SIZE);
          }
          granularcontrols(lefilter);
          granular[lefilter]->beginFreeze(legrainleng);
        } else if(granular_shifting[lefilter]){
            //granular_pitch_shift stops the freeze
            granular_pitch_shift(lefilter);
        } else {
          granular[lefilter]->stop();
        }
      }

      static void granularcontrols(byte lefilter) {
        float g_speed = 0.125 + (map(granularVknobs[lefilter][1],0,127,0,7875)/1000.0);
        granular[lefilter]->setSpeed(g_speed);
      }

      static void granularVpanelAction(byte lefilter) {
        if (navlevel == 4) {
          byte slct = sublevels[3];
          // g leng
          if (slct == 0) {
            navrange = 127;
            granularVknobs[lefilter][0] = sublevels[4];
          }
          if (slct == 1) {
            navrange = 127;
            granularVknobs[lefilter][1] = sublevels[4];
            granularcontrols(lefilter);
          }
          // res
          if (slct == 2) {
            toggle_that(granular_freezing[lefilter]);
            granular_freeze(lefilter);
            returntonav(3);
          }
          if (slct == 3) {
            toggle_that(granular_shifting[lefilter]);
            granular_pitch_shift(lefilter);
            returntonav(3);
          }

          if (slct == 4) {
            navrange = 127;
            set_wet_mix_at_sub4(lefilter);
          }
        }

        if (navlevel > 4) {

          returntonav(3);
        }
      }

      static void granularVpanelSelector(byte lefilter) {
        const byte knobradius = 13;
        byte centercirclex = 10 + knobradius;
        byte centercircley = 16 + knobradius;
        const byte startlex2 = 67;
        const byte totbartall = 37;
        const byte topwbarstart = 16;
        const byte wbarwidth2 = 8;
        if (navlevel == 3) {
          navrange = 4;
        }
        byte slct = sublevels[3];
        // size
        if (slct == 0) {
          sublevels[4] = granularVknobs[lefilter][0];
          canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
        }
        // damp
        if (slct == 1) {
          sublevels[4] = granularVknobs[lefilter][1];
          canvasBIG.drawCircle(knobradius + 45, centercircley, knobradius - 2, SSD1306_WHITE);
        }
        if (slct == 2) {
          if (!granular_freezing[lefilter]) {
            canvasBIG.drawRoundRect(82, 18, 128 - 80 - 4, 20 - 4, 2, SSD1306_WHITE);
          } else {
            canvasBIG.drawRoundRect(82, 18, 128 - 80 - 4, 20 - 4, 2, SSD1306_BLACK);
          }
        }
        if (slct == 3) {
          if (!granular_shifting[lefilter]) {
            canvasBIG.drawRoundRect(82, 18 + 20 + 4, 128 - 80 - 4, 20 - 4, 2, SSD1306_WHITE);
          } else {
            canvasBIG.drawRoundRect(82, 18 + 20 + 4, 128 - 80 - 4, 20 - 4, 2, SSD1306_BLACK);
          }
        }
        // wet
        if (slct == 4) {
          sublevels[4] = WetMixMasters[lefilter + 1] ;
          canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall, wbarwidth2 - 4, SSD1306_WHITE);
          canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
        }
      }

      static void granularVpanel(byte lefilter) {

        granularVpanelAction(lefilter);
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
        int legrainleng = map(granularVknobs[lefilter][0],0,127,1,GRANULAR_MEMORY_SIZE);
        float leratio = 0.125 + (map(granularVknobs[lefilter][1],0,127,0,7875)/1000.0);

            dm.clean_title_1();
        canvastitle.print("Granular ");
        canvastitle.print(lefilter + 1);
        float grain_speed = granularVknobs[lefilter][1] / 127.0;
        float grain_size = granularVknobs[lefilter][0] / 127.0;
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
        if (!granular_freezing[lefilter]) {
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
        if (!granular_shifting[lefilter]) {
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
        barsize = round(((WetMixMasters[lefilter + 1]/127.0) * (totbartall - 4)));
        canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall, wbarwidth2, 2, SSD1306_WHITE);
        canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4, SSD1306_WHITE);
        canvasBIG.setCursor(startlex2 - 6, 0);
        canvasBIG.print("Wet:");
        granularVpanelSelector(lefilter);
        dm.dodisplay();
      }

      static void bitcrusherctrl(byte lefilter) {
        bitcrusher[lefilter]->bits(bitcrusherVknobs[lefilter][0]);
        bitcrusher[lefilter]->sampleRate(round((bitcrusherVknobs[lefilter][1] / 127.0) * 44100));
      }

      static void bitcrusherVpanelAction(byte lefilter) {
        if (navlevel == 4) {
          // AudioNoInterrupts();
          byte slct = sublevels[3];
          // fq
          if (slct == 0) {
            navrange = 16;
            bitcrusherVknobs[lefilter][0] = sublevels[4];
            bitcrusherctrl(lefilter);
          }
          // res
          if (slct == 1) {
            navrange = 127;
            bitcrusherVknobs[lefilter][1] = sublevels[4];
            bitcrusherctrl(lefilter);
            // apply
          }

          if (slct == 2) {
            navrange = 127;
            set_wet_mix_at_sub4(lefilter);
          }
        }
        if (navlevel > 4) {
          returntonav(3);
        }
      }

      static void bitcrusherVpanelSelector(byte lefilter) {

        byte knobradius = 14;
        byte centercirclex = 25 + knobradius;
        byte centercircley = 16 + knobradius;
        byte startlex2 = 67;
        byte totbartall = 37;
        byte topwbarstart = 16;
        byte wbarwidth2 = 8;
        if (navlevel == 3) {
          navrange = 2;
        }
        int slct = sublevels[3];
        // size
        if (slct == 0) {
          sublevels[4] = bitcrusherVknobs[lefilter][0];
          canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
        }
        // damp
        if (slct == 1) {
          sublevels[4] = bitcrusherVknobs[lefilter][1];
          canvasBIG.drawCircle(knobradius + 68, centercircley, knobradius - 2, SSD1306_WHITE);
        }

        // wet
        if (slct == 2) {
          sublevels[4] = WetMixMasters[lefilter + 1] ;
          canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall, wbarwidth2 - 4, SSD1306_WHITE);
          canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
        }
      }

      static void bitcrusherVpanel(byte lefilter) {

        bitcrusherVpanelAction(lefilter);
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
        canvastitle.print(lefilter + 1);
        float lesamperate = bitcrusherVknobs[lefilter][1] / 127.0;
        float lebitsz = bitcrusherVknobs[lefilter][0] / 16.0;
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
        barsize = round(((WetMixMasters[lefilter + 1]/127.0) * (totbartall - 4)));
        canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall, wbarwidth2, 2, SSD1306_WHITE);
        canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4, SSD1306_WHITE);
        canvasBIG.setCursor(startlex2 - 6, 0);
        canvasBIG.print("Wet:");
        bitcrusherVpanelSelector(lefilter);
        dm.dodisplay();
      }

      static void freeverbscontrl(byte lefilter) {
        //AudioNoInterrupts();
        //other reverb type, disabled for noisy noise
        //freeverbs[lefilter]->roomsize(reverbVknobs[lefilter][0] / 127.0);
        //freeverbs[lefilter]->damping(reverbVknobs[lefilter][1] / 127.0);
        freeverbs[lefilter]->reverbTime((reverbVknobs[lefilter][0] / 127.0)*10);
        //AudioInterrupts();
      }

      static void reverbVpanelAction(byte lefilter) {
        if (navlevel == 4) {
          // AudioNoInterrupts();
          byte slct = sublevels[3];
          // fq
          if (slct == 0) {
            navrange = 127;
            reverbVknobs[lefilter][0] = sublevels[4];
            freeverbscontrl(lefilter);
          }
          // res
          //if (slct == 1) {
          //  navrange = 127;
          //  reverbVknobs[lefilter][1] = sublevels[4];
          //  freeverbscontrl(lefilter);
          //}
          if (slct == 1) {
            navrange = 127;
            set_wet_mix_at_sub4(lefilter);
          }
        }
        if (navlevel > 4) {

          returntonav(3);
        }
      }

      static void reverbVpanelSelector(byte lefilter) {
        byte knobradius = 14;
        byte centercirclex = 25 + knobradius;
        byte centercircley = 16 + knobradius;
        byte startlex2 = 67;
        byte totbartall = 37;
        byte topwbarstart = 16;
        byte wbarwidth2 = 8;
        if (navlevel == 3) {
          navrange = 1;
        }
        int slct = sublevels[3];
        // second
        if (slct == 0) {
          sublevels[4] = reverbVknobs[lefilter][0];
          canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
        }
        // damp ( disabled , from other freeverb module)
        //if (slct == 1) {
        //  sublevels[4] = reverbVknobs[lefilter][1];
        //  canvasBIG.drawCircle(knobradius + 68, centercircley, knobradius - 2, SSD1306_WHITE);
        //}

        // wet
        if (slct == 1) {
          sublevels[4] = WetMixMasters[lefilter + 1];
          canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall, wbarwidth2 - 4, SSD1306_WHITE);
          canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
        }
      }

      static void reverbVpanel(byte lefilter) {

        reverbVpanelAction(lefilter);
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
        canvastitle.print(lefilter + 1);
        //float ledamping = reverbVknobs[lefilter][1] / 127.0;
        float leroomsize = reverbVknobs[lefilter][0] / 127.0;
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
        barsize = round((WetMixMasters[lefilter + 1]/127.0) * (totbartall - 4));
        canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall, wbarwidth2, 2, SSD1306_WHITE);
        canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4, SSD1306_WHITE);
        canvasBIG.setCursor(startlex2 - 6, 0);
        canvasBIG.print("Wet:");
        reverbVpanelSelector(lefilter);
        dm.dodisplay();
      }

      static void delayVpanelAction(byte lefilter) {
        if (navlevel == 4) {
          // AudioNoInterrupts();
          byte slct = sublevels[3];
          // time
          if (slct == 0) {
            navrange = 127;
            delayVknobs[lefilter][0] = sublevels[4];
            restartdelayline(lefilter);
          }
          // timeX
          if (slct == 1) {
            navrange = 127;
            delayVknobs[lefilter][1] = sublevels[4];
            restartdelayline(lefilter);
          }
          // feedback
          if (slct == 2) {
            navrange = 127;
            delayVknobs[lefilter][2] = sublevels[4];
            restartdelayline(lefilter);
          }
          if (slct == 3) {
            navrange = 127;
            WetMixMasters[lefilter + 1] = sublevels[4] ;
            _mx.wetmixmastercontrols();
          }
        }
        if (navlevel > 4) {
          returntonav(3);
        }
      }

      static void delayVpanelSelector(byte lefilter) {
        byte knobradius = 11;
        byte centercirclex = 15 + knobradius;
        byte centercircley = 16 + knobradius;
        byte startlex2 = 67;
        byte totbartall = 37;
        byte topwbarstart = 16;
        byte wbarwidth2 = 8;
        if (navlevel == 3) {
          navrange = 3;
        }
        byte slct = sublevels[3];
        // size
        if (slct == 0) {
          sublevels[4] = delayVknobs[lefilter][0];
          canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
        }
        // damp
        if (slct == 1) {
          sublevels[4] = delayVknobs[lefilter][1];
          canvasBIG.drawCircle(centercirclex + 40, centercircley, knobradius - 2, SSD1306_WHITE);
        }

        if (slct == 2) {
          sublevels[4] = delayVknobs[lefilter][2];
          canvasBIG.drawCircle(centercirclex + 40 + 40, centercircley, knobradius - 2, SSD1306_WHITE);
        }

        // wet
        if (slct == 3) {
          sublevels[4] = WetMixMasters[lefilter + 1];
          canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall, wbarwidth2 - 4, SSD1306_WHITE);
          canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
        }
      }

      static void delayVpanel(byte lefilter) {

        delayVpanelAction(lefilter);
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
        canvastitle.print(lefilter + 1);
        float delaytime = delayVknobs[lefilter][0] / 127.0;
        float dephtflange = delayVknobs[lefilter][1] / 127.0;
        float freqflange = delayVknobs[lefilter][2] / 127.0;

        // Tsel
        coeffangle = (6.2831 - (delaytime)*6.2831) + 3.1416;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 1, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print(round((delayVknobs[lefilter][0] / 127.0) * 7));
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
        canvasBIG.print(delayVknobs[lefilter][1]);
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
        canvasBIG.print(((delayVknobs[lefilter][2] / 127.0)), 2);
        canvasBIG.setCursor(centercirclex - knobradius - 2, centercircley + knobradius + 4 + 10);
        // canvasBIG.setCursor(centercirclex-knobradius+1, 8);
        canvasBIG.print("Fback");

        // wetbar
        barsize = round(((WetMixMasters[lefilter + 1]/127.0) * (totbartall - 4)));
        canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall, wbarwidth2, 2, SSD1306_WHITE);
        canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4, SSD1306_WHITE);
        canvasBIG.setCursor(startlex2 - 6, 0);
        canvasBIG.print("Wet:");
        delayVpanelSelector(lefilter);

        dm.dodisplay();
      }

      static void filterVpanelAction(byte lefilter) {
        if (navlevel == 3) {
          filter_lfo_option = LFOonfilterz[lefilter] ;
        }
        if (navlevel == 4) {
          byte slct = sublevels[3];
          // fq
          if (slct == 0) {
            navrange = 127;
            ffilterzVknobs[lefilter][0] = sublevels[4];
          }
          // res
          if (slct == 1) {
            navrange = 127;
            ffilterzVknobs[lefilter][1] = sublevels[4];
          }
          // octaves
          if (slct == 2) {
            navrange = 127;
            ffilterzVknobs[lefilter][2] = sublevels[4];
          }
          // lowpass
          if (slct == 3) {
            navrange = 127;
            mixffilterzVknobs[lefilter][0] = sublevels[4];
          }
          // bandpass
          if (slct == 4) {
            navrange = 127;
            mixffilterzVknobs[lefilter][1] = sublevels[4];
          }
          // high pass
          if (slct == 5) {
            navrange = 127;
            mixffilterzVknobs[lefilter][2] = sublevels[4];
          }
          if (slct == 6) {
            //navrange is 3 + 1 for none
            navrange = OSCS_COUNT;
            filter_lfo_option = sublevels[4];
            if (filter_lfo_option < OSCS_COUNT) {
              LFOonfilterz[lefilter] = filter_lfo_option;
            }
          }
          if (slct == 7) {
            navrange = 127;
            set_wet_mix_at_sub4(lefilter);
          }
          filtercontrols(lefilter);
        }
        if (navlevel > 4) {
          returntonav(3);
        }
      }

      static void lfoonfilterreplug(byte lefilter) {
        unpluglfoonfilterz(lefilter);
        if (LFOonfilterz[lefilter] < OSCS_COUNT) {
          LFOtoFilterz[((fxs_count * lefilter) + LFOonfilterz[lefilter])]->connect();
          call_restart_lfo(LFOonfilterz[lefilter]);
        }

      }

      static void unpluglfoonfilterz(byte lefilter) {
        //each line has 3 lfo linked to a filter
        for (int i = 0; i < fxs_count; i++) {
          LFOtoFilterz[lefilter*fxs_count+i]->disconnect();
        }
      }

      static void filtercontrols(byte lefilter) {
        filterzfreq[lefilter] = (ffilterzVknobs[lefilter][0] / 127.0) * filterzrange;
        filterzreso[lefilter] = ((ffilterzVknobs[lefilter][1]) / 127.0) * 5;
        if (filterzreso[lefilter] < 0.7) {
          filterzreso[lefilter] = 0.7;
        }
        filterzoctv[lefilter] = ((ffilterzVknobs[lefilter][2]) / 127.0) * 7;
        filterzgainz[lefilter][0] = (mixffilterzVknobs[lefilter][0]) / 127.0;
        filterzgainz[lefilter][1] = (mixffilterzVknobs[lefilter][1]) / 127.0;
        filterzgainz[lefilter][2] = (mixffilterzVknobs[lefilter][2]) / 127.0;
        unpluglfoonfilterz(lefilter);
        if (sublevels[4] < OSCS_COUNT) {
          lfoonfilterreplug(lefilter);
        }
        for (int i = 0; i < 3; i++) {
          mixfilter[lefilter]->gain(i, filterzgainz[lefilter][i]);
        }
        filterz[lefilter]->frequency(filterzfreq[lefilter]);
        filterz[lefilter]->resonance(filterzreso[lefilter]);
        filterz[lefilter]->octaveControl(filterzoctv[lefilter]);
      }
      static void filterVpanel(byte lefilter) {
        char LFOnamelist[4][6] = {"LFO1", "LFO2", "LFO3", "None"};
        filterVpanelAction(lefilter);
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
        canvastitle.print(lefilter + 1);
        canvastitle.setCursor(0, 8);
        // reflect lebq
        canvastitle.print("Ctrl: ");
        canvastitle.print((char *)LFOnamelist[filter_lfo_option]);

        // bqfreq
        coeffangle = (6.2831 - (ffilterzVknobs[lefilter][0] / 127.0) * 6.2831) + 3.1416;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 4, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print("FQ");
        if (filterzfreq[lefilter] < 1000) {
          canvasBIG.setCursor(centercirclex - knobradius + 1, 24);
          canvasBIG.print(filterzfreq[lefilter], 0);
        }
        if ((round(filterzfreq[lefilter]) < 9900) && (filterzfreq[lefilter] >= 1000)) {
          canvasBIG.setCursor(centercirclex - knobradius - 1, 24);
          canvasBIG.print(round(filterzfreq[lefilter]) / 1000.0, 1);
          canvasBIG.print("k");
        }
        if (filterzfreq[lefilter] >= 9900) {
          canvasBIG.setCursor(centercirclex - knobradius - 5, 24);
          canvasBIG.print(filterzfreq[lefilter] / 1000.0, 1);
          canvasBIG.print("k");
        }

        // resonnance
        coeffangle = (6.2831 - (ffilterzVknobs[lefilter][1] / 127.0) * 6.2831) + 3.1416;
        centercirclex = knobradius + 30;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 1, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print("Res");
        canvasBIG.setCursor(centercirclex - knobradius + 2, 24);
        canvasBIG.print(filterzreso[lefilter], 1);

        // octave
        coeffangle = (6.2831 - (ffilterzVknobs[lefilter][2] / 127.0) * 6.2831) + 3.1416;
        centercirclex = knobradius + 55;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx, ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 1, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print("Oct");
        canvasBIG.setCursor(centercirclex - knobradius + 1, 24);
        canvasBIG.print(filterzoctv[lefilter], 1);

        barsize = round((filterzgainz[lefilter][0] * (totbartall - 4)));
        canvasBIG.drawRoundRect(81, topwbarstart, wbarwidth, totbartall, 2, SSD1306_WHITE);
        canvasBIG.fillRect(81 + 2, (totbartall + topwbarstart - barsize - 2), wbarwidth - 4, barsize, SSD1306_WHITE);
        canvasBIG.setCursor(81, totbartall + topwbarstart + 4);
        canvasBIG.print("LP");

        barsize = round((filterzgainz[lefilter][1] * (totbartall - 4)));
        canvasBIG.drawRoundRect(98, topwbarstart, wbarwidth, totbartall, 2, SSD1306_WHITE);
        canvasBIG.fillRect(98 + 2, (totbartall + topwbarstart - barsize - 2), wbarwidth - 4, barsize, SSD1306_WHITE);
        canvasBIG.setCursor(97, totbartall + topwbarstart + 4);
        canvasBIG.print("BP");

        barsize = round((filterzgainz[lefilter][2] * (totbartall - 4)));
        canvasBIG.drawRoundRect(115, topwbarstart, wbarwidth, totbartall, 2, SSD1306_WHITE);
        canvasBIG.fillRect(115 + 2, (totbartall + topwbarstart - barsize - 2), wbarwidth - 4, barsize, SSD1306_WHITE);
        canvasBIG.setCursor(114, totbartall + topwbarstart + 4);
        canvasBIG.print("HP");

        barsize = round(((WetMixMasters[lefilter + 1]/127.0) * (totbartall - 4)));
        canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall, wbarwidth2, 2, SSD1306_WHITE);
        canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4, SSD1306_WHITE);
        canvasBIG.setCursor(startlex2 - 6, 0);
        canvasBIG.print("Wet:");
        filterVpanelSelector(lefilter);
        dm.dodisplay();
      }

      static void filterVpanelSelector(byte lefilter) {

        byte knobradius = 9;
        byte centercirclex = 5 + knobradius;
        byte centercircley = 35 + knobradius;
        byte totbartall = 37;
        byte topwbarstart = 16;
        byte wbarwidth = 9;
        int wbarwidth2 = 8;
        byte startlex2 = 67;
        if (navlevel == 3) {
          navrange = 8;
        }
        byte slct = sublevels[3];
        // fq
        if (slct == 0) {
          sublevels[4] = ffilterzVknobs[lefilter][0];
          canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
        }
        // res
        if (slct == 1) {
          sublevels[4] = ffilterzVknobs[lefilter][1];
          canvasBIG.drawCircle(centercirclex + 25, centercircley, knobradius - 2, SSD1306_WHITE);
        }
        // oct
        if (slct == 2) {
          sublevels[4] = ffilterzVknobs[lefilter][2];
          canvasBIG.drawCircle(centercirclex + 50, centercircley, knobradius - 2, SSD1306_WHITE);
        }
        // lp
        if (slct == 3) {
          sublevels[4] = mixffilterzVknobs[lefilter][0];
          canvasBIG.drawRect(83, topwbarstart, wbarwidth - 4, totbartall, SSD1306_WHITE);
        }
        // bp
        if (slct == 4) {
          sublevels[4] = mixffilterzVknobs[lefilter][1];
          canvasBIG.drawRect(100, topwbarstart, wbarwidth - 4, totbartall, SSD1306_WHITE);
        }
        // hp
        if (slct == 5) {
          sublevels[4] = mixffilterzVknobs[lefilter][2];
          canvasBIG.drawRect(117, topwbarstart, wbarwidth - 4, totbartall, SSD1306_WHITE);
        }
        // Select LFO
        if (slct == 6) {
          sublevels[4] = filter_lfo_option;
          canvasBIG.setCursor(64, 8);
          canvasBIG.print((char)9);
        }
        if (slct == 7) {
          sublevels[4] = WetMixMasters[lefilter + 1];
          canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0, totbartall, wbarwidth2, SSD1306_WHITE);
          canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
        }
      }

      static void biquadVpanelAction(byte lebiquad) {
        if (navlevel == 4) {
          byte slct = sublevels[3];
          // stage
          if (slct == 0) {
            navrange = 3;
            bqstage[lebiquad] = sublevels[4];
          }
          // mode
          if (slct == 1) {
            navrange = 5;
            bqtype[lebiquad][bqstage[lebiquad]] = sublevels[4];
          }
          // freq
          if (slct == 2) {
            navrange = 127;
            bqVpot[lebiquad][bqstage[lebiquad]][0] = sublevels[4];
            bqfreq[lebiquad][bqstage[lebiquad]] =
                (((bqVpot[lebiquad][bqstage[lebiquad]][0]) / 127.0) * bqrange) + 101;
          }
          // slope or Q
          if (slct == 3) {
            navrange = 127;
            bqVpot[lebiquad][bqstage[lebiquad]][1] = sublevels[4];
            bqslope[lebiquad][bqstage[lebiquad]] =
                (bqVpot[lebiquad][bqstage[lebiquad]][1]) / 127.0;
          }
          // gain
          if (slct == 5) {
            navrange = 127;
            bqVpot[lebiquad][bqstage[lebiquad]][2] = sublevels[4];
            bqgain[lebiquad][bqstage[lebiquad]] =
                (bqVpot[lebiquad][bqstage[lebiquad]][2]) / 127.0;
          }
          // to avoid setting up a stage unconfigured while browsing
          if (bqfreq[lebiquad][bqstage[lebiquad]] >= 101) {
            biquadcontrols(lebiquad);
          }
          if (slct == 4) {
            navrange = 127;
            set_wet_mix_at_sub4(lebiquad);
          }
        }
        if (navlevel > 4) {

          returntonav(3);
        }
      }

      static void biquadVpanel(byte lebiquad) {
        char bqtypeLabels[6][12] = {"Low Pass", "High Pass", "Band Pass",
                                    "Notch",    "LowShelf",  "High Shelf"};
        biquadVpanelAction(lebiquad);
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
        byte barsize = round((bqVpot[lebiquad][bqstage[lebiquad]][2] / 127.0) * (totbartall - 4));
            dm.clean_title_1();
        canvastitle.print("Biquad ");
        canvastitle.print(lebiquad + 1);
        canvastitle.setCursor(107, 8);
        // reflect lebq
        canvastitle.print("s:");
        canvastitle.print(bqstage[lebiquad] + 1);

        canvastitle.setCursor(0, 8);
        canvastitle.print("mode: ");
        canvastitle.print((char *)bqtypeLabels[bqtype[lebiquad][bqstage[lebiquad]]]);
        // bqfreq
        coeffangle = (6.2831 - (bqVpot[lebiquad][bqstage[lebiquad]][0] / 127.0) * 6.2831) + 3.1416;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        bqVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        bqVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, bqVcursorpointx, bqVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print("Freq.");
        if (bqfreq[lebiquad][bqstage[lebiquad]] < 1000) {
          canvasBIG.setCursor(centercirclex - knobradius + 4, 18);
        }
        if ((bqfreq[lebiquad][bqstage[lebiquad]] < 10000) && (bqfreq[lebiquad][bqstage[lebiquad]] >= 1000)) {
          canvasBIG.setCursor(centercirclex - knobradius + 2, 18);
        }
        if (bqfreq[lebiquad][bqstage[lebiquad]] >= 10000) {
          canvasBIG.setCursor(centercirclex - knobradius - 2, 18);
        }
        canvasBIG.print(bqfreq[lebiquad][bqstage[lebiquad]], 0);
        // bqslope
        coeffangle = (6.2831 - (bqVpot[lebiquad][bqstage[lebiquad]][1] / 127.0) * 6.2831) + 3.1416;
        centercirclex = knobradius + 50;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        bqVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        bqVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, bqVcursorpointx, bqVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius, centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print("Slope");
        canvasBIG.setCursor(centercirclex - knobradius, 18);
        canvasBIG.print(bqslope[lebiquad][bqstage[lebiquad]]);
        // gain if  setLowShelf or sethighShelf
        if (bqtype[lebiquad][bqstage[lebiquad]] > 3) {
          canvasBIG.drawRoundRect(95, topwbarstart, wbarwidth, totbartall, 2, SSD1306_WHITE);
          canvasBIG.fillRect(95 + 2, (totbartall + topwbarstart - barsize - 2), wbarwidth - 4, barsize, SSD1306_WHITE);
          canvasBIG.setCursor(90, totbartall + topwbarstart + 4);
          canvasBIG.print("Gain");
          canvasBIG.setCursor(90, 18);
          canvasBIG.print(bqgain[lebiquad][bqstage[lebiquad]]);
        }
        barsize = round(((WetMixMasters[lebiquad + 1]/127.0) * (totbartall + 13 - 4)));
        canvasBIG.drawRoundRect(topwbarstart - 12 + startlex2 + 4, 0, totbartall + 13, wbarwidth2, 2, SSD1306_WHITE);
        canvasBIG.fillRect((topwbarstart - 12 + startlex2 + 6), 2, barsize, wbarwidth2 - 4, SSD1306_WHITE);
        canvasBIG.setCursor(startlex2 - 6, 0);
        canvasBIG.print("Wet:");
        biquadVpanelSelector(lebiquad);
        dm.dodisplay();
      }

      static void biquadVpanelSelector(byte lebiquad) {
        byte startlex2 = 67;
        byte totbartall = 37;
        byte topwbarstart = 16;
        byte wbarwidth2 = 7;
        if (navlevel == 3) {
          navrange = 4;
          if (bqtype[lebiquad][bqstage[lebiquad]] > 3) {
            navrange = 5;
          }
        }
        byte slct = sublevels[3];
        // stage
        if (slct == 0) {
          sublevels[4] = bqstage[lebiquad];
          canvasBIG.setCursor(103, 9);
          canvasBIG.print((char)9);
        }
        // mode
        if (slct == 1) {
          sublevels[4] = bqtype[lebiquad][bqstage[lebiquad]];
          canvasBIG.setCursor(29, 8);
          canvasBIG.print((char)9);
        }
        // freq
        if (slct == 2) {
          sublevels[4] = bqVpot[lebiquad][bqstage[lebiquad]][0];
          canvasBIG.setCursor(20, 36);
          canvasBIG.print((char)9);
        }
        // slope
        if (slct == 3) {
          sublevels[4] = bqVpot[lebiquad][bqstage[lebiquad]][1];
          canvasBIG.setCursor(60, 36);
          canvasBIG.print((char)9);
        }
        // gain
        if (slct == 5) {
          sublevels[4] = bqVpot[lebiquad][bqstage[lebiquad]][2];
          canvasBIG.setCursor(89, 36);
          canvasBIG.print((char)9);
        }

        if (slct == 4) {
          sublevels[4] = WetMixMasters[lebiquad + 1];
          canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall, wbarwidth2 - 4, SSD1306_WHITE);
          canvasBIG.fillRect(55, 2, 3, 3, SSD1306_WHITE);
        }
      }

      static void allfxcontrolled() {
        for (int i = 0; i < 3; i++) {
          switch(fx[i]->plugged_fx_type){
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
              for (int j = 0; j < 4; j++) {
                //to avoid configuring unused biquad filters stages
                if (bqfreq[i][j] >= 303) {
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

      static void fx_nav_zero(){
        reinitsublevels(2);
        navrange = self->home_navrange;
        display.clearDisplay();
        dolistmainfxlines();
        dm.dodisplay();
        sublevels[2] = fx[sublevels[1]%fxs_count]->plugged_fx_type ;
      }

      static void fx_nav_one(){
        avoid_fx_bounce = false ;
        display.clearDisplay();
        navrange = 9;
        dolistMainFxPanel();
        dm.dodisplay();
      }

      static void fx_nav_two(){
        fx[sublevels[1]]->route_fx(sublevels[2]);
        displayfxVcontrols(sublevels[1]);
      }

      static void MainFxPanel() {
        if (sublevels[navlevel] > navrange)
          reinitsublevels(navlevel);

        if (navlevel == 1) {
          fx_nav_zero();
        }
        if (navlevel == 2) {
          fx_nav_one();
        }
        if (navlevel > 2) {
          fx_nav_two();
        }
      }

      static constexpr void (*_nav_fx[5])() = {&fx_nav_one, &fx_nav_one, &fx_nav_one, &fx_nav_one, &fx_nav_one};

  private:
    static FxMenuRouter* self;
};

FxMenuRouter* FxMenuRouter::self = nullptr;
EXTMEM FxMenuRouter _fx;