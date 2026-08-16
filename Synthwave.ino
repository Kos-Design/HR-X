

class AdsrMenuRouter : public SectionHolder {
  public:
    AdsrMenuRouter() {
                    self = this;
                    this->home_navrange=SN_MENU_LABELS_COUNT-1;
                    this->relative_navlevel=1;
                    this->max_navlevel=5;
                    this->sublevels_address={0,0,0};
                    }
    
    static void show(){
      displayadsrgraph();
    }

    static void ApplyADSR() {
      for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
        enveloppesL[i]->delay(gg.adsrlevels[AttackDelay]);
        enveloppesL[i]->attack(gg.adsrlevels[Attack]);
        enveloppesL[i]->hold(gg.adsrlevels[Hold]);
        enveloppesL[i]->decay(gg.adsrlevels[Decay]);
        enveloppesL[i]->sustain(gg.adsrlevels[Sustain] / 100.0);
        enveloppesL[i]->release(gg.adsrlevels[Release]);
      }
      self->mappedattack = gg.adsrlevels[Attack];
      self->mappeddecay = gg.adsrlevels[Decay];
      self->mappedrelease = gg.adsrlevels[Release];
      self->mappedsustain = gg.adsrlevels[Sustain];
      self->MadsrAttackDelay = gg.adsrlevels[AttackDelay];
      self->MadsrHold = gg.adsrlevels[Hold];
    }
    static void displayadsrgraph() {
      lv.navrange = 5 ;
      if (lv.sublevels[2] == 2) {
        lv.navleveloverwrite = 2;
      }
      if (lv.sublevels[1] == 0) {
        lv.navleveloverwrite = 4;
      }
      dm.clean_title_1_1();
      canvasBIG.drawLine(2, 61, 2, 18, SSD1306_WHITE);
      canvasBIG.drawLine(2, 61, 125, 61, SSD1306_WHITE);
      canvasBIG.drawLine(125, 59, 127, 61, SSD1306_WHITE);
      canvasBIG.drawLine(125, 63, 127, 61, SSD1306_WHITE);
      canvasBIG.drawLine(2, 16, 0, 18, SSD1306_WHITE);
      canvasBIG.drawLine(2, 16, 4, 18, SSD1306_WHITE);

      // mappedsustain
      int totalliner = self->mappedattack * 10 + self->mappeddecay + 100 + self->mappedrelease +
                      self->MadsrAttackDelay * 2 + self->MadsrHold + 5;
      float linerratio = 124.0 / totalliner;
      int a0 = round(self->MadsrAttackDelay * 10 * linerratio) + 5;
      int a1 = round(self->mappedattack * 10 * linerratio) + a0;
      int h0 = a1;
      int h1 = a1 + round(self->MadsrHold * linerratio);
      int d0 = h1;
      int d1 = d0 + round(self->mappeddecay * linerratio);
      int s0 = d1;
      int s1 = s0 + 100 * linerratio;
      int suY = map(self->mappedsustain, 0, 100, 37, 0) + 22;
      int r0 = s1;
      int r1 = r0 + self->mappedrelease * linerratio;
      int startx = 3;
      int starty = 16;

      canvasBIG.drawLine(a0, 61, a1, 24, SSD1306_WHITE);
      canvasBIG.drawLine(h0, 24, h1, 24, SSD1306_WHITE);
      canvasBIG.drawLine(d0, 24, d1, suY, SSD1306_WHITE);
      canvasBIG.drawLine(s0, suY, s1, suY, SSD1306_WHITE);
      canvasBIG.drawLine(r0, suY, r1, 61, SSD1306_WHITE);
      display.clearDisplay();
      dm.dodisplay();

      // preparing for next display loop
      dm.clear_buffs();

      switch (lv.sublevels[lv.navleveloverwrite]) {
      case 0:
        display.fillRect(startx, starty,
                        round(self->MadsrAttackDelay * 10 * linerratio) + 1, 45,
                        SSD1306_INVERSE);
        display.display();
        sliceDa();
        break;

      case 1:
        display.fillRect(a0, starty, round(self->mappedattack * 10 * linerratio) + 2, 45,
                        SSD1306_INVERSE);
        display.display();

        sliceA();
        break;

      case 2:
        display.fillRect(h0, starty, round(self->MadsrHold * linerratio) + 2, 45,
                        SSD1306_INVERSE);
        display.display();

        sliceH();
        break;
      case 3:
        display.fillRect(d0, starty, round(self->mappeddecay * linerratio) + 1, 45,
                        SSD1306_INVERSE);
        display.display();

        sliceD();
        break;
      case 4:

        display.fillRect(s0, starty, round(95 * linerratio) + 1, 45,
                        SSD1306_INVERSE);
        display.display();

        sliceS();
        break;
      case 5:
        display.fillRect(r0, starty, round(self->mappedrelease * linerratio) + 1, 45,
                        SSD1306_INVERSE);
        display.display();

        sliceR();
        break;

      default:
        break;
      }


      dm.dodisplay();

      dm.clear_buffs();
    }

    static void SetADSR() {
      gg.adsrlevels[AttackDelay] = self->MadsrAttackDelay;
      gg.adsrlevels[Sustain] = self->mappedsustain;
      gg.adsrlevels[Release] = self->mappedrelease;
      gg.adsrlevels[Decay] = self->mappeddecay;
      gg.adsrlevels[Attack] = self->mappedattack;
      gg.adsrlevels[Hold] = self->MadsrHold;
    }

    static void GlobalADSR() {
      SetADSR();
      ApplyADSR();
    }

    static void print_adsr_echo(String titre, int niveau){
      canvastitle.setTextSize(1);
      canvastitle.setCursor(0, 0);
      canvastitle.fillScreen(SSD1306_BLACK);
      canvastitle.println(titre);
      canvastitle.setCursor(55, 0);
      canvastitle.println(niveau);
    }

    static void sliceA() {
      if (lv.navlevel == lv.navleveloverwrite + 1) {
        //stuck here until validation of cursor, try using returnto nav
        lv.sublevels[lv.navlevel + 1] = self->mappedattack;
        dm.returntonav(lv.navlevel + 1, 5,lv.sublevels[lv.navlevel + 1]);
      }

      if (lv.navlevel == lv.navleveloverwrite + 2) {
        lv.navrange = 1024;


        self->mappedattack = lv.sublevels[lv.navleveloverwrite + 2];
      }
      if (lv.navlevel == lv.navleveloverwrite + 3) {
        if (lv.sublevels[1] == 2) {
          GlobalADSR();
        }
        dm.returntonav(lv.navleveloverwrite, 5,lv.sublevels[lv.navleveloverwrite]);

      }
      print_adsr_echo("Attack ",self->mappedattack);
    }

    static void sliceDa() {
      if (lv.navlevel == lv.navleveloverwrite + 1) {

        lv.sublevels[lv.navlevel + 1] = self->MadsrAttackDelay;
        dm.returntonav(lv.navlevel + 1, 5,lv.sublevels[lv.navlevel + 1]);
      }
      if (lv.navlevel == lv.navleveloverwrite + 2) {
        lv.navrange = 100;

        self->MadsrAttackDelay = lv.sublevels[lv.navleveloverwrite + 2];
      }
      if (lv.navlevel == lv.navleveloverwrite + 3) {
        if (lv.sublevels[1] == 2) {
          GlobalADSR();
        }

        dm.returntonav(lv.navleveloverwrite, 5,lv.sublevels[lv.navleveloverwrite]);
      }
      print_adsr_echo("Attack Delay ",self->MadsrAttackDelay);
    }

    static void sliceH() {
      if (lv.navlevel == lv.navleveloverwrite + 1) {
        lv.sublevels[lv.navlevel + 1] = self->MadsrHold;
        dm.returntonav(lv.navlevel + 1, 5,lv.sublevels[lv.navlevel + 1]);
      }
      if (lv.navlevel == lv.navleveloverwrite + 2) {
        lv.navrange = 100;
        self->MadsrHold = lv.sublevels[lv.navleveloverwrite + 2];
      }
      if (lv.navlevel == lv.navleveloverwrite + 3) {
        if (lv.sublevels[1] == 2) {
          GlobalADSR();
        }

        dm.returntonav(lv.navleveloverwrite, 5,lv.sublevels[lv.navleveloverwrite]);
      }
      print_adsr_echo("Hold ",self->MadsrHold);
    }

    static void sliceD() {

      if (lv.navlevel == lv.navleveloverwrite + 1) {
        lv.sublevels[lv.navlevel + 1] = self->mappeddecay;
        dm.returntonav(lv.navlevel + 1, 5,lv.sublevels[lv.navlevel + 1]);
      }
      if (lv.navlevel == lv.navleveloverwrite + 2) {
        lv.navrange = 512;
        self->mappeddecay = lv.sublevels[lv.navleveloverwrite + 2];
      }
      if (lv.navlevel == lv.navleveloverwrite + 3) {
        if (lv.sublevels[1] == 2) {
          GlobalADSR();
        }

        dm.returntonav(lv.navleveloverwrite, 5,lv.sublevels[lv.navleveloverwrite]);
      }


      print_adsr_echo("Decay ",self->mappeddecay);
    }

    static void sliceS() {
      if (lv.navlevel == lv.navleveloverwrite + 1) {
        lv.sublevels[lv.navlevel + 1] = self->mappedsustain;
        dm.returntonav(lv.navlevel + 1, 5,lv.sublevels[lv.navlevel + 1]);
      }
      if (lv.navlevel == lv.navleveloverwrite + 2) {
        lv.navrange = 100;
        self->mappedsustain = lv.sublevels[lv.navleveloverwrite + 2];
      }
      if (lv.navlevel == lv.navleveloverwrite + 3) {
        if (lv.sublevels[1] == 2) {
          GlobalADSR();
        }

        dm.returntonav(lv.navleveloverwrite, 5,lv.sublevels[lv.navleveloverwrite]);
      }
      print_adsr_echo("Sustain ",self->mappedsustain);

    }

    static void sliceR() {
      lv.retroaction = lv.navleveloverwrite ;
      if (lv.navlevel == lv.navleveloverwrite + 1) {
        dm.returntonav(lv.navlevel + 1, 5,lv.sublevels[lv.navlevel + 1]);
        lv.sublevels[lv.navlevel + 1] = self->mappedrelease;
      }
      if (lv.navlevel == lv.navleveloverwrite + 2) {
        lv.navrange = 1024;
        self->mappedrelease = lv.sublevels[lv.navleveloverwrite + 2];
      }
      if (lv.navlevel == lv.navleveloverwrite + 3) {
        if (lv.sublevels[1] == 2) {
          GlobalADSR();
        }

        dm.returntonav(lv.navleveloverwrite, 5,lv.sublevels[lv.navleveloverwrite]);
      }
      print_adsr_echo("Release ",self->mappedrelease);

    }

    int mappedattack = 5;
    int mappeddecay = 50;
    int mappedrelease = 60;
    int mappedsustain = 100; // divide by 100 to float
    int MadsrAttackDelay = 0;
    int MadsrHold = 0;
  private:
    
    static AdsrMenuRouter* self;
};

AdsrMenuRouter* AdsrMenuRouter::self = nullptr;
AdsrMenuRouter _ad;

class GlideMenuRouter : public SectionHolder {
  public:
    GlideMenuRouter() {
                    self = this;
                    self->home_navrange=4-1;
                    self->relative_navlevel=2;
                    self->max_navlevel=5;
                    self->sublevels_address={0,0,0};
                    
                    }

        static constexpr const char* GlideModeLabels[5] = {
            "Off",
            "Portamento",
            "ReversePortamento",
            "PitchAttack",
            "ReversePitchAttack"
        };

        uint8_t *glide_params[4] = {reinterpret_cast<uint8_t*>(&gg.glideMode),&gg.portamento_time,&gg.portamento_height,&gg.glide_slope};

        static void show(){

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

  private:
    
    static GlideMenuRouter* self;
};

GlideMenuRouter* GlideMenuRouter::self = nullptr;
GlideMenuRouter _gd;

class Filter303MenuRouter : public SectionHolder {
  public:
    Filter303MenuRouter() {
                    self = this;
                    self->home_navrange=SN_MENU_LABELS_COUNT-1;
                    self->relative_navlevel=1;
                    self->max_navlevel=5;
                    self->sublevels_address={0,0,0};
    }
    int letbfreq = 450;

    static void setle303filterpass(int linei) {
      les303passes[linei]->gain(0,gg.le303filterzgainz[0]/127.0);
      les303passes[linei]->gain(1,gg.le303filterzgainz[1]/127.0);
      les303passes[linei]->gain(2,gg.le303filterzgainz[2]/127.0);
    }

    static void initialize303group() {
      for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
        setle303filterpass(i);
        les303wet[i]->gain(1.0, 1.0);
        les303wet[i]->gain(0.0, 0.0);
        les303filterz[i]->frequency(1800.5);
        les303filterz[i]->resonance(2.5);
      }
    }

    static void le303filtercontrols() {
      for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
        setle303filterpass(i);
      }
    }

    static void Wavespreamp303controls() {
      for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
        Wavespreamp303[i]->gain((gg.preampleswaves / 127.0)*2);
      }
    }

    static void le303filterzWet() {
      for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
        les303wet[i]->gain(0, gg.le303filterzwet / 127.0);
        les303wet[i]->gain(1, (1 - (gg.le303filterzwet / 127.0)));
      }
    }
    
    static void allpasslevels() {
      mix303L1.gain(0, 1);
      mix303L1.gain(1, 0);
      mix303L1.gain(2, 0);
    }

    float slopelinear[18] = {0.85,0.858334,0.866668,0.875,0.883336,0.89167,0.900004,0.908338,0.916672,0.925006,0.93334,0.941674,0.95,0.958342,0.966676,0.97501,0.983344,0.991678};

    float fxsloper[18] = {0.85,0.88,0.91,0.92,0.93,0.95,0.95,0.96,0.97,0.97,0.98,0.98,0.99,0.99,1.00,1.00,1.00,1.00};

    int lardiff;
    float sloped[18];

    static void pseudo303(byte i) {
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

      static void filter_knob_freq(){
        lv.navrange = 127;
        gg.le303ffilterzVknobs[0] = lv.sublevels[3];
        gg.le303filterzfreq = lround((gg.le303ffilterzVknobs[0] / 127.0) * 14000);
      }

      static void filter_knob_res(){
        lv.navrange = 127;
        gg.le303ffilterzVknobs[1] = lv.sublevels[3];
        gg.le303filterzreso = gg.le303ffilterzVknobs[1];
      }

      static void filter_knob_low(){
        gg.mixle303ffilterzVknobs[0] = lv.sublevels[3];
        gg.le303filterzgainz[0] = gg.mixle303ffilterzVknobs[0];
      }

      static void filter_knob_band(){
        gg.mixle303ffilterzVknobs[1] = lv.sublevels[3];
        gg.le303filterzgainz[1] = gg.mixle303ffilterzVknobs[1];
      }

      static void filter_knob_high(){
        gg.mixle303ffilterzVknobs[2] = lv.sublevels[3];
        gg.le303filterzgainz[2] = gg.mixle303ffilterzVknobs[2];
      }

      static void filter_knob_wet(){
        lv.navrange = 127;
        gg.le303filterzwet = lv.sublevels[3];
        // gg.le303filterzwet = (gg.mixle303ffilterzVknobs[2])/127.0 ;
        le303filterzWet();
      }

      static void filter_knob_preamp(){
        lv.navrange = 127;
        gg.preampleswaves = lv.sublevels[3];
        Wavespreamp303controls();
      }

      static void filter_knob_glide(){
        lv.navrange = 127;
        set_Portamento_time_ctl(lv.sublevels[3]);
      }


      static void le303filterVpanelAction() {

        if (lv.navlevel == 3) {
          lv.retroaction = lv.sublevels[2];
          lv.navrange = 127;
          if (!lv.temp_buff_armed) {
            set_filter_buff_temp();
            lv.temp_buff_armed = 1 ;
          }
          // AudioNoInterrupts();
          (filters_pointers[lv.sublevels[2]])();
          le303filtercontrols();

        }
        if (lv.navlevel > 3) {
          lv.temp_buff_armed = 0 ;
          dm.returntonav(2,7,lv.sublevels[2]);
        }
      }
      static void le303filterVpanel() {

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

    static void le303filterVpanelSelector() {

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
    static void restore_from_temp() {
      for (int i=0; i<8; i++) {
        lv.sublevels[3] = self->filter_tmp_values[i];
        (filters_pointers[i])();
        le303filtercontrols();
        *self->filter_tmp_pointers[i] = self->filter_tmp_values[i] ;
      }
        lv.temp_buff_armed = 0 ;
    }

    static void set_filter_buff_temp() {

      for (int i=0; i<8; i++) {
        self->filter_tmp_values[i] = *self->filter_tmp_pointers[i] ;
      }

    }
    
    void show(){
      le303filterVpanel();
    }

  private:
    static constexpr void (*filters_pointers[8])() = {&filter_knob_freq, &filter_knob_res, &filter_knob_low, &filter_knob_band, &filter_knob_high,
                                            &filter_knob_wet, &filter_knob_preamp, &filter_knob_glide};
                    byte *filter_tmp_pointers[8] = { &gg.le303ffilterzVknobs[0], &gg.le303ffilterzVknobs[1], &gg.mixle303ffilterzVknobs[0], &gg.mixle303ffilterzVknobs[1], &gg.mixle303ffilterzVknobs[2],
                                              &gg.le303filterzwet, &gg.preampleswaves, &gg.portamento_time };

                    byte filter_tmp_values[8] = {gg.le303ffilterzVknobs[0],gg.le303ffilterzVknobs[1],gg.mixle303ffilterzVknobs[0],gg.mixle303ffilterzVknobs[1],gg.mixle303ffilterzVknobs[2],
                                          gg.le303filterzwet,gg.preampleswaves,gg.portamento_time };
    static Filter303MenuRouter* self;
};

Filter303MenuRouter* Filter303MenuRouter::self = nullptr;
Filter303MenuRouter _ft;


class Mp3PlayerRouter : public SectionHolder {
    public:
        Mp3PlayerRouter() {self = this;
                            self->home_navrange=8;
                            self->catalog = new FilesLister("MP3/","LONGFILE#",".MP3",mp3_player_panel,self->home_navrange);
                            self->relative_navlevel=2;
                            self->max_navlevel=5;
                            self->sublevels_address={7,0,0};
                            //home method not really used yet
                            //this->set_home(call_fx_mainpanel);
                    }
        FilesLister *catalog;
        String mp3_name = "MP3/Addict.mp3";
        String mp3_dir = "MP3/";
        uint16_t mp3_count = 0;
        uint16_t file_index = 0 ;
        uint16_t next_mp3 = 0 ;
        uint16_t previous_mp3 = 0 ;
        byte mp3_ext = 0 ;
        bool mp3_looped = 0 ;
        bool mp3_paused = 0 ;
        bool mp3_shuffle = 0 ;
        bool mp3_continue = 0 ;

        static void mp3_player_play(){
          if (!SD.exists((char*)self->mp3_name.c_str())) {
            get_next_mp3();
          }
          playFile((char*)self->mp3_name.c_str());
        }

        static void mp3_player_stop(){
          playMp31.stop();
          self->mp3_continue = 0 ;
        }

        static void mp3_player_continous(){
          self->mp3_continue = !self->mp3_continue ;
        }

        static void mp3_player_pause(){
          self->mp3_paused = playMp31.pause(!self->mp3_paused);
          self->mp3_continue = 0 ;
        }

        static void mp3_player_next(){
          
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

        static void mp3_player_previous(){

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

        static void mp3_player_shuffle(){
          //TODO: make whole list of shuffled numbers the size of their folder files count
          // allow next and previous
          //regenerate on stop / and shuffle toggle 
          self->mp3_shuffle = !self->mp3_shuffle ;
          if (self->mp3_shuffle) {
            self->previous_mp3 = self->next_mp3;

          }
        }
        static void mp3_loop_setter(){
          self->mp3_looped = !self->mp3_looped ;
          self->mp3_continue = self->mp3_looped ;
        }
        static void mp3_player_actions() {
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
        static void get_file_type(){
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

        static void playFile(const char *mp3_file) {
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

        static void get_next_mp3() {
          

          Serial.println("");
          Serial.print("previous now became =");
          Serial.print(self->previous_mp3);

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
            Serial.println(self->mp3_count);
            Serial.println(self->next_mp3);

          }

        }

        static void count_mp3s() {
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
        
        static void transport_selector() {
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

        static void play_flac_file(const char *flac_file) {
          playMp31.stop();
          playFlac1.play(flac_file);
          //playFlac1.setPlaybackCompleteCallback(display_mp3_title);

        }


        static void display_mp3_title(){
          canvasBIG.setCursor(0,40);
          String titler = self->mp3_name;
          titler.remove(0, 4);
          //titler.remove(titler.length() - 4);
          canvasBIG.print((char*)titler.c_str());
        }

        static void mp3_player_panel() {
          dm.clear_3();
          dm.drawtransport();
          mp3_player_actions();
          dm.dodisplay();
          transport_selector();
          display_mp3_title();
          dm.dodisplay();
          //placeholder
        }

   
  private:
      static Mp3PlayerRouter* self;
};

Mp3PlayerRouter* Mp3PlayerRouter::self = nullptr;
Mp3PlayerRouter _mp;


class SynthMenuRouter : public SectionHolder {
    public:
        SynthMenuRouter() {
                    self = this;
                    this->home_navrange=SN_MENU_LABELS_COUNT-1;
                    this->relative_navlevel=1;
                    this->max_navlevel=5;
                    this->sublevels_address={0,0,0};
                    }

        int unit = (int)gg.wavesfreqs[lv.oscillator] % 10;
        int tenth     = ((int)(gg.wavesfreqs[lv.oscillator] * 10)) % 10;
        int hundredth = ((int)(gg.wavesfreqs[lv.oscillator] * 100)) % 10;
        //TODO give default value based on wformtype
        const byte synth_params_count = 8;

        static void show() {
          _route_nav[lv.navlevel-1]();
        }

        static void route_navlevel_1(){
          synth_nav_zero();
        }

        static void route_navlevel_2(){
          lv.retroaction = lv.sublevels[1];
          _nav_synth[lv.sublevels[1]]();
        }

        static void displayoffsetwav() {
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

        static void freqbars_panel_selector() {
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
        static void freqbars_panel_action() {

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

        static void displayfreqbars(){
          dm.clear_3();
          display.setTextSize(2);
          display.setCursor(65, 0);
          display.println(gg.wavesfreqs[lv.oscillator]);
          draw_synth_params();
          dm.dodisplay();
        }

        static void freqbars_panel() {
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

        static void displayphasebars() {
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

        static void displayModulatedbool() {
          char modulation_labels[4][7] = {"Off", "Freq", "Phase", "Ampl"};

          draw_synth_params();
          dm.dodisplay();
          display.setCursor(64, 0);
          display.setTextSize(2);
          display.println(modulation_labels[gg.FMmodulated[lv.oscillator]]);
          draw_synth_params();
          dm.dodisplay();

        }

        static void setfmtophase() {
          for (byte i = 0; i < SYNTH_LINERS_COUNT; i++) {
            //phaseModulation should be based on lfo level
            FMwaveforms1[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->phaseModulation(180);
          }
        }

        static void setfmtofreq() {
          for (byte i = 0; i < SYNTH_LINERS_COUNT; i++) {
            //phaseModulation should be based on lfo level
            FMwaveforms1[i + (lv.oscillator * SYNTH_LINERS_COUNT)]->frequencyModulation(10);
          }
        }

        static void wavelineModulatedbool() {
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

        static void displaywaveformicon(){
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

        static void displayLFOpanel() {
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

        static void go_previous(){
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
        static void go_next(){
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

        static void wavelinesBG() {
          display.clearDisplay();
          display.drawBitmap(0, 64 - 47, wavesbg2, 128, 47, SSD1306_WHITE);
          display.display();
        }

        static void wavelining() {
          lv.retroaction = lv.sublevels[3];
          _synth_params[lv.sublevels[3]]();
        }

        static void draw_synth_params() {
          const char* wavelineslabels[] = {
              "Type", "Mod", "LFO", "Freq", "Offset", "Phase", "<-  ", "  ->"};
          dm.main_panel(wavelineslabels,3,self->synth_params_count);
          canvasBIG.setCursor(120, 57);
          canvasBIG.print(lv.oscillator + 1);
        }

        static void dolistsyntmenu() {
          const char* synthmenulabels[] = {"Synths", "Mixer", "ADSR", "MP3 Player", "Filter", "Glider"};
          dm.main_panel(synthmenulabels,1,SN_MENU_LABELS_COUNT);          
        }

        static void synths_switcher(){
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

        static void wavesline_selector(){
          lv.retroaction = lv.sublevels[lv.navlevel-2] ;
          _waveliners[lv.navlevel-2]();
        }

        static void synth_nav_zero() {
          lv.navrange = self->home_navrange;
          dm.clean_title_2_1();
          //if (!lv.retroaction)
          //  reinitsublevels(2);
          dolistsyntmenu();
          lv.retroaction = lv.sublevels[1] ;
          dm.dodisplay();
        }

        static void plug_no_waves(){
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

        static void plug_waves(){
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

        static void plug_moded_waves(){
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
          call_restart_lfo(lv.oscillator);
        }

        static void plug_ampl_moded_waves(){
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
          call_restart_lfo(lv.oscillator);
        }

        static void plug_strings_waves(){
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

        static void plug_ampl_moded_strings(){
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

        static void plug_drum_waves(){
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

        static void plug_ampl_moded_drums(){
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

        static void no_modulation(){
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

        static void freq_modulation(){
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

        static void phase_modulation(){
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

        static void amplitude_modulation(){
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
            call_restart_lfo(lv.oscillator);
        }

        static void setwavetypefromlist() {
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

        static void setphaselevel() {
          AudioNoInterrupts();
          for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
            waveforms1[i + (SYNTH_LINERS_COUNT * lv.oscillator)]->phase((int)((gg.phaselevelsL[lv.oscillator]/ 127.0) * 360.0));
          }
          AudioInterrupts();
        }

        static constexpr void (*_nav_synth[SN_MENU_LABELS_COUNT])() = {&wavesline_selector,&call_mx_show, &call_ad_show, &_mp.mp3_player_panel, &call_fl_show,&_gd.show};
        static constexpr void (*_waveliners[6])() = {&synths_switcher,&wavelining, &wavelining, &wavelining,&wavelining, &wavelining};
        static constexpr void (*modulation_pointers[4])() = {&no_modulation,&freq_modulation,&phase_modulation,&amplitude_modulation};

        static constexpr void (*_synth_params[8])() = {&displaywaveformicon,&wavelineModulatedbool,&displayLFOpanel,
                                                      &freqbars_panel,&displayoffsetwav,&displayphasebars,&go_previous,&go_next};

        static constexpr void (*_route_nav[7])() = {
            &route_navlevel_1,
            &route_navlevel_2,
            &route_navlevel_2,
            &route_navlevel_2,
            &route_navlevel_2,
            &route_navlevel_2,
            &route_navlevel_2
        };



  private:
    static SynthMenuRouter* self;
};

SynthMenuRouter* SynthMenuRouter::self = nullptr;
SynthMenuRouter _sn;

