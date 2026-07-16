

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
        enveloppesL[i]->delay(adsrlevels[0]);
        enveloppesL[i]->attack(adsrlevels[1]);
        enveloppesL[i]->hold(adsrlevels[2]);
        enveloppesL[i]->decay(adsrlevels[3]);
        enveloppesL[i]->sustain(adsrlevels[4] / 100.0);
        enveloppesL[i]->release(adsrlevels[5]);
      }
      self->mappedattack = adsrlevels[1];
      self->mappeddecay = adsrlevels[3];
      self->mappedrelease = adsrlevels[5];
      self->mappedsustain = adsrlevels[4];
      self->MadsrAttackDelay = adsrlevels[0];
      self->MadsrHold = adsrlevels[2];
    }
    static void displayadsrgraph() {
      navrange = 5 ;
      if (sublevels[2] == 2) {
        navleveloverwrite = 2;
      }
      if (sublevels[1] == 0) {
        navleveloverwrite = 4;
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

      switch (sublevels[navleveloverwrite]) {
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
      adsrlevels[0] = self->MadsrAttackDelay;
      adsrlevels[4] = self->mappedsustain;
      adsrlevels[5] = self->mappedrelease;
      adsrlevels[3] = self->mappeddecay;
      adsrlevels[1] = self->mappedattack;
      adsrlevels[2] = self->MadsrHold;
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
      if (navlevel == navleveloverwrite + 1) {
        //stuck here until validation of cursor, try using returnto nav
        sublevels[navlevel + 1] = self->mappedattack;
        returntonav(navlevel + 1, 5,sublevels[navlevel + 1]);
      }

      if (navlevel == navleveloverwrite + 2) {
        navrange = 1024;


        self->mappedattack = sublevels[navleveloverwrite + 2];
      }
      if (navlevel == navleveloverwrite + 3) {
        if (sublevels[1] == 2) {
          GlobalADSR();
        }
        returntonav(navleveloverwrite, 5,sublevels[navleveloverwrite]);

      }
      print_adsr_echo("Attack ",self->mappedattack);
    }

    static void sliceDa() {
      if (navlevel == navleveloverwrite + 1) {

        sublevels[navlevel + 1] = self->MadsrAttackDelay;
        returntonav(navlevel + 1, 5,sublevels[navlevel + 1]);
      }
      if (navlevel == navleveloverwrite + 2) {
        navrange = 100;

        self->MadsrAttackDelay = sublevels[navleveloverwrite + 2];
      }
      if (navlevel == navleveloverwrite + 3) {
        if (sublevels[1] == 2) {
          GlobalADSR();
        }

        returntonav(navleveloverwrite, 5,sublevels[navleveloverwrite]);
      }
      print_adsr_echo("Attack Delay ",self->MadsrAttackDelay);
    }

    static void sliceH() {
      if (navlevel == navleveloverwrite + 1) {
        sublevels[navlevel + 1] = self->MadsrHold;
        returntonav(navlevel + 1, 5,sublevels[navlevel + 1]);
      }
      if (navlevel == navleveloverwrite + 2) {
        navrange = 100;
        self->MadsrHold = sublevels[navleveloverwrite + 2];
      }
      if (navlevel == navleveloverwrite + 3) {
        if (sublevels[1] == 2) {
          GlobalADSR();
        }

        returntonav(navleveloverwrite, 5,sublevels[navleveloverwrite]);
      }
      print_adsr_echo("Hold ",self->MadsrHold);
    }

    static void sliceD() {

      if (navlevel == navleveloverwrite + 1) {
        sublevels[navlevel + 1] = self->mappeddecay;
        returntonav(navlevel + 1, 5,sublevels[navlevel + 1]);
      }
      if (navlevel == navleveloverwrite + 2) {
        navrange = 512;
        self->mappeddecay = sublevels[navleveloverwrite + 2];
      }
      if (navlevel == navleveloverwrite + 3) {
        if (sublevels[1] == 2) {
          GlobalADSR();
        }

        returntonav(navleveloverwrite, 5,sublevels[navleveloverwrite]);
      }


      print_adsr_echo("Decay ",self->mappeddecay);
    }

    static void sliceS() {
      if (navlevel == navleveloverwrite + 1) {
        sublevels[navlevel + 1] = self->mappedsustain;
        returntonav(navlevel + 1, 5,sublevels[navlevel + 1]);
      }
      if (navlevel == navleveloverwrite + 2) {
        navrange = 100;
        self->mappedsustain = sublevels[navleveloverwrite + 2];
      }
      if (navlevel == navleveloverwrite + 3) {
        if (sublevels[1] == 2) {
          GlobalADSR();
        }

        returntonav(navleveloverwrite, 5,sublevels[navleveloverwrite]);
      }
      print_adsr_echo("Sustain ",self->mappedsustain);

    }

    static void sliceR() {
      retroaction = navleveloverwrite ;
      if (navlevel == navleveloverwrite + 1) {
        returntonav(navlevel + 1, 5,sublevels[navlevel + 1]);
        sublevels[navlevel + 1] = self->mappedrelease;
      }
      if (navlevel == navleveloverwrite + 2) {
        navrange = 1024;
        self->mappedrelease = sublevels[navleveloverwrite + 2];
      }
      if (navlevel == navleveloverwrite + 3) {
        if (sublevels[1] == 2) {
          GlobalADSR();
        }

        returntonav(navleveloverwrite, 5,sublevels[navleveloverwrite]);
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
EXTMEM AdsrMenuRouter _ad;


class Filter303MenuRouter : public SectionHolder {
  public:
    Filter303MenuRouter() {
                    self = this;
                    this->home_navrange=SN_MENU_LABELS_COUNT-1;
                    this->relative_navlevel=1;
                    this->max_navlevel=5;
                    this->sublevels_address={0,0,0};
    }

  static void setle303filterpass(int linei) {
    les303passes[linei]->gain(0,le303filterzgainz[0]);
    les303passes[linei]->gain(1,le303filterzgainz[1]);
    les303passes[linei]->gain(2,le303filterzgainz[2]);
  }

  static void initialize303group() {
    for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
      setle303filterpass(i);
      les303wet[i]->gain(1, 1);
      les303wet[i]->gain(0, 0);
      les303filterz[i]->frequency(220);
      les303filterz[i]->resonance(5);
    }
  }

  static void le303filtercontrols() {
    for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
      setle303filterpass(i);
    }
  }

  static void Wavespreamp303controls() {
    for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
      Wavespreamp303[i]->gain(preampleswaves*2 / 127.0);
    }
  }

  static void le303filterzWet() {
    for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
      les303wet[i]->gain(0, le303filterzwet / 100.0);
      les303wet[i]->gain(1, (1 - (le303filterzwet / 100.0)));
    }
  }

  static void setlepulse1() {
    le303pulsewidth = (cutoff_pulse / 32.0) * 2 * millitickinterval;
    if (le303pulsewidth < 50) {
      le303pulsewidth = 50;
    }
    for (int i = 0; i < SYNTH_LINERS_COUNT ; i++) {
      //blink303[i]->setDuration(le303pulsewidth);
      pulsers[i][1]=le303pulsewidth;
    }
  }

  static void setlepulse2() {
    le303pulsewidth2 = (reson_pulse / 32.0) * 2 * millitickinterval + 50;
    if (le303pulsewidth2 < 50) {
      le303pulsewidth2 = 50;
    }
  }

  float fxslopedown2(byte curve, float laxval) {
    return pow(laxval, (double)(curve / 127.0));
  }

    static void filter_knob_freq(){
      navrange = 127;
      le303ffilterzVknobs[0] = sublevels[3];
      le303filterzfreq = round((le303ffilterzVknobs[0] / 127.0) * 10000);
      le303filterzrange = le303filterzfreq;
    }

    static void filter_knob_res(){
      navrange = 127;
      le303ffilterzVknobs[1] = sublevels[3];
      le303filterzreso = ((le303ffilterzVknobs[1]) / 127.0) * 5;
    }

    static void filter_knob_low(){
      mixle303ffilterzVknobs[0] = sublevels[3];
      le303filterzgainz[0] = (mixle303ffilterzVknobs[0]) / 127.0;
    }

    static void filter_knob_band(){
      mixle303ffilterzVknobs[1] = sublevels[3];
      le303filterzgainz[1] = (mixle303ffilterzVknobs[1]) / 127.0;
    }

    static void filter_knob_high(){
      mixle303ffilterzVknobs[2] = sublevels[3];
      le303filterzgainz[2] = (mixle303ffilterzVknobs[2]) / 127.0;
    }

    static void filter_knob_wet(){
      navrange = 100;
      le303filterzwet = sublevels[3];
      // le303filterzwet = (mixle303ffilterzVknobs[2])/127.0 ;
      le303filterzWet();
    }

    static void filter_knob_pulse1(){
      navrange = 32;
      cutoff_pulse = sublevels[3];
      setlepulse1();
      // le303filterzwet = (mixle303ffilterzVknobs[2])/127.0 ;
    }

    static void filter_knob_pulse2(){
      navrange = 32;
      reson_pulse = sublevels[3];
      setlepulse2();
      // le303filterzwet = (mixle303ffilterzVknobs[2])/127.0 ;
    }

    static void filter_knob_preamp(){
      preampleswaves = sublevels[3];
      Wavespreamp303controls();
    }

    static void filter_knob_glide(){
      navrange = 5;
      glidemode = sublevels[3];
    }


    static void le303filterVpanelAction() {

      if (navlevel == 3) {
        retroaction = sublevels[2];
        navrange = 127;
        if (!temp_buff_armed) {
          set_filter_buff_temp();
          temp_buff_armed = 1 ;
        }
        // AudioNoInterrupts();
        (filters_pointers[sublevels[2]])();
        le303filtercontrols();

      }
      if (navlevel > 3) {
        temp_buff_armed = 0 ;
        returntonav(2,9,sublevels[2]);
      }
    }
    static void le303filterVpanel() {

      //if back from knob and !  : revert from temp ( all or just the changed one ? -> knob validation updates temps )
      // when set temp
      le303filterVpanelAction();
      if (navlevel == 2 && temp_buff_armed) {
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
      canvastitle.print((preampleswaves*2 / 127.0) * 100.0, 1);

      coeffangle = (6.2831 - (le303ffilterzVknobs[0] / 127.0) * 6.2831) + 3.1416;
      canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
      ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
      ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
      canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                        ftVcursorpointy, SSD1306_WHITE);
      canvasBIG.setCursor(centercirclex - knobradius + 4,
                          centercircley + knobradius + 4);
      canvasBIG.setTextSize(1);
      canvasBIG.print("FQ");
      if (le303filterzfreq < 1000) {
        canvasBIG.setCursor(centercirclex - knobradius + 1, 25);
        canvasBIG.print(le303filterzfreq, 0);
      }
      if ((round(le303filterzfreq) < 9900) && (le303filterzfreq >= 1000)) {
        canvasBIG.setCursor(centercirclex - knobradius - 1, 25);
        canvasBIG.print(round(le303filterzfreq) / 1000.0, 1);
        canvasBIG.print("k");
      }
      if (le303filterzfreq >= 9900) {
        canvasBIG.setCursor(centercirclex - knobradius - 5, 25);
        canvasBIG.print(le303filterzfreq / 1000.0, 1);
        canvasBIG.print("k");
      }

      // resonnance
      coeffangle = (6.2831 - (le303ffilterzVknobs[1] / 127.0) * 6.2831) + 3.1416;
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
      canvasBIG.print(le303filterzreso, 1);

        /*
        // octave
        coeffangle = (6.2831 - (le303ffilterzVknobs[2] / 127.0) * 6.2831) + 3.1416;
        centercirclex = knobradius + 55;
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        ftVcursorpointx = round(centercirclex + (knobradius * (cos(coeffangle))));
        ftVcursorpointy = round(centercircley - (knobradius * (sin(coeffangle))));
        canvasBIG.drawLine(centercirclex, centercircley, ftVcursorpointx,
                          ftVcursorpointy, SSD1306_WHITE);
        canvasBIG.setCursor(centercirclex - knobradius + 1,
                            centercircley + knobradius + 4);
        canvasBIG.setTextSize(1);
        canvasBIG.print("Oct");
        canvasBIG.setCursor(centercirclex - knobradius + 1, 25);
        canvasBIG.print(le303filterzoctv, 1);
        */

      barsize = round((le303filterzgainz[0] * (totbartall - 4)));
      canvasBIG.drawRoundRect(81, topwbarstart, wbarwidth, totbartall, 2,
                              SSD1306_WHITE);
      canvasBIG.fillRect(81 + 2, (totbartall + topwbarstart - barsize - 2),
                        wbarwidth - 4, barsize, SSD1306_WHITE);
      canvasBIG.setCursor(81, totbartall + topwbarstart + 4);
      canvasBIG.print("LP");
      // canvasBIG.setCursor(80,18);
      // canvasBIG.print(bqgain[0][bqstage[0]]);
      barsize = round((le303filterzgainz[1] * (totbartall - 4)));
      canvasBIG.drawRoundRect(98, topwbarstart, wbarwidth, totbartall, 2, SSD1306_WHITE);
      canvasBIG.fillRect(98 + 2, (totbartall + topwbarstart - barsize - 2), wbarwidth - 4, barsize, SSD1306_WHITE);
      canvasBIG.setCursor(97, totbartall + topwbarstart + 4);
      canvasBIG.print("BP");
      // canvasBIG.setCursor(93,18);
      // canvasBIG.print(bqgain[0][bqstage[0]]);
      barsize = round((le303filterzgainz[2] * (totbartall - 4)));
      canvasBIG.drawRoundRect(115, topwbarstart, wbarwidth, totbartall, 2, SSD1306_WHITE);
      canvasBIG.fillRect(115 + 2, (totbartall + topwbarstart - barsize - 2), wbarwidth - 4, barsize, SSD1306_WHITE);
      canvasBIG.setCursor(114, totbartall + topwbarstart + 4);
      canvasBIG.print("HP");
      // canvasBIG.setCursor(114,18);
      // canvasBIG.print(bqgain[lefilter][bqstage[lefilter]]);
      // wetbar
      barsize = round(((le303filterzwet / 100.0) * (totbartall - 4)));
      canvasBIG.drawRoundRect(topwbarstart + startlex2 + 4, 0, totbartall, wbarwidth2, 2, SSD1306_WHITE);
      canvasBIG.fillRect((topwbarstart + startlex2 + 6), 2, barsize, wbarwidth2 - 4, SSD1306_WHITE);
      canvasBIG.setCursor(startlex2, 0);
      canvasBIG.print("Wet");

      barsize = round(((le303pulsewidth / millitickinterval) * (totbartall - 4)));

      canvasBIG.setCursor(0, 16);
      canvasBIG.print("Xfq ");
      canvasBIG.print(cutoff_pulse);

      canvasBIG.setCursor(40, 16);
      canvasBIG.print("Xres ");
      canvasBIG.print(reson_pulse);

      canvastitle.setCursor(94, 8);
      canvastitle.print("S:");
      if (glidemode > 0 && glidemode < 13) {
        canvastitle.print(".0");
        canvastitle.print(100 * (glidemode / 127.0), 0);
      }
      if (glidemode > 12 && glidemode < 128) {
        canvastitle.print(".");
        canvastitle.print(100 * (glidemode / 127.0), 0);
      }
      if (glidemode == 127) {
        canvastitle.print("1.0");
      }
      if (glidemode == 0) {
        canvastitle.print("Off");
      }

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
      if (navlevel == 2) {
        navrange = 9;
      }
      int slct = sublevels[2];
      // fq
      if (slct == 0) {
        sublevels[3] = le303ffilterzVknobs[0];
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2,
                            SSD1306_WHITE);
      }
      // res
      if (slct == 1) {
        sublevels[3] = le303ffilterzVknobs[1];
        canvasBIG.drawCircle(centercirclex + 25, centercircley, knobradius - 2,
                            SSD1306_WHITE);
      }
      /*
      // oct
      if (slct == 2) {
        sublevels[3] = le303ffilterzVknobs[2];
        canvasBIG.drawCircle(centercirclex + 50, centercircley, knobradius - 2,
                            SSD1306_WHITE);
      }
      */
      // lp
      if (slct == 2) {
        sublevels[3] = mixle303ffilterzVknobs[0];
        canvasBIG.drawRect(83, topwbarstart, wbarwidth - 4, totbartall,
                          SSD1306_WHITE);
      }
      // bp
      if (slct == 3) {
        sublevels[3] = mixle303ffilterzVknobs[1];
        canvasBIG.drawRect(100, topwbarstart, wbarwidth - 4, totbartall,
                          SSD1306_WHITE);
      }
      // hp
      if (slct == 4) {
        sublevels[3] = mixle303ffilterzVknobs[2];
        canvasBIG.drawRect(117, topwbarstart, wbarwidth - 4, totbartall,
                          SSD1306_WHITE);
      }
      // wet
      if (slct == 5) {
        sublevels[3] = le303filterzwet;
        canvasBIG.drawRect(topwbarstart + startlex2 + 4, 0 + 2, totbartall,
                          wbarwidth2 - 4, SSD1306_WHITE);
      }
      if (slct == 6) {
        sublevels[3] = cutoff_pulse;
        canvasBIG.setCursor(21, 16);
        canvasBIG.print((char)9);
      }
      if (slct == 7) {
        sublevels[3] = reson_pulse;
        canvasBIG.setCursor(62, 18);
        canvasBIG.print((char)9);
      }
      if (slct == 8) {
        sublevels[3] = preampleswaves;
        canvasBIG.setCursor(34, 0);
        canvasBIG.print((char)9);
      }

      if (slct == 9) {
        sublevels[3] = glidemode;
        canvasBIG.setCursor(100, 8);
        canvasBIG.print((char)9);
      }

    }
    static void restore_from_temp() {
      for (int i=0; i<10; i++) {
        sublevels[3] = self->filter_tmp_values[i];
        (filters_pointers[i])();
        le303filtercontrols();
        *self->filter_tmp_pointers[i] = self->filter_tmp_values[i] ;
      }
        temp_buff_armed = 0 ;
    }

    static void set_filter_buff_temp() {

      for (int i=0; i<10; i++) {
        self->filter_tmp_values[i] = *self->filter_tmp_pointers[i] ;
      }

    }
    
    void show(){
      le303filterVpanel();
    }

  private:
    static constexpr void (*filters_pointers[10])() = {&filter_knob_freq, &filter_knob_res, &filter_knob_low, &filter_knob_band, &filter_knob_high,
                                            &filter_knob_wet, &filter_knob_pulse1, &filter_knob_pulse2, &filter_knob_preamp, &filter_knob_glide};
                    byte *filter_tmp_pointers[10] = { &le303ffilterzVknobs[0], &le303ffilterzVknobs[1], &mixle303ffilterzVknobs[0], &mixle303ffilterzVknobs[1], &mixle303ffilterzVknobs[2],
                                              &le303filterzwet, &cutoff_pulse, &reson_pulse, &preampleswaves, &glidemode };

                    byte filter_tmp_values[10] = {le303ffilterzVknobs[0],le303ffilterzVknobs[1],mixle303ffilterzVknobs[0],mixle303ffilterzVknobs[1],mixle303ffilterzVknobs[2],
                                          le303filterzwet,cutoff_pulse,reson_pulse,preampleswaves,glidemode };
    static Filter303MenuRouter* self;
};

Filter303MenuRouter* Filter303MenuRouter::self = nullptr;
EXTMEM Filter303MenuRouter _fl;

class SynthMenuRouter : public SectionHolder {
    public:
        SynthMenuRouter() {
                    self = this;
                    this->home_navrange=SN_MENU_LABELS_COUNT-1;
                    this->relative_navlevel=1;
                    this->max_navlevel=5;
                    this->sublevels_address={0,0,0};
                    }

        int unit = (int)wavesfreqs[oscillator] % 10;
        int tenth     = ((int)(wavesfreqs[oscillator] * 10)) % 10;
        int hundredth = ((int)(wavesfreqs[oscillator] * 100)) % 10;

        static void show() {
          _route_nav[navlevel-1]();
        }

        static void route_navlevel_1(){
          synth_nav_zero();
        }

        static void route_navlevel_2(){
          retroaction = sublevels[1];
          _nav_synth[sublevels[1]]();
        }

        static void displayoffsetwav() {
          dm.clear_3();
          if (navlevel == 3) {
            retroaction = sublevels[2];
            navrange = synth_params_count - 1;
            sublevels[4] = wave1offset[oscillator];
          }
          if (navlevel == 4) {
            navrange = 127;
            retroaction = sublevels[3];
            wave1offset[oscillator] = sublevels[4];
            for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
              waveforms1[i + (oscillator * SYNTH_LINERS_COUNT)]->offset((float)(((64.0 - wave1offset[oscillator]) / 64.0)));
              FMwaveforms1[i + (oscillator * SYNTH_LINERS_COUNT)]->offset((float)(((64.0 - wave1offset[oscillator]) / 64.0)));
            }
          }
          if (navlevel >= 5) {
            returntonav(3,synth_params_count-1,sublevels[3]);
            return;
          }
          display.setTextSize(1);
          display.setCursor(80, 8);
          display.print((float)(((64.0 - wave1offset[oscillator]) / 64.0)));

          draw_synth_params();
          dm.dodisplay();
        }

        static void freqbars_panel_selector() {
          if (navlevel == 4) {
            retroaction = sublevels[3];
            switch (sublevels[4]){
              case 0:
                display.fillRect(62, 0, 16, 16, SSD1306_INVERSE);
                self->unit = (int)wavesfreqs[oscillator];
                sublevels[5]=self->unit;
              break;
              case 1:
                display.fillRect(88, 0, 12, 16, SSD1306_INVERSE);
                self->tenth = ((int)(wavesfreqs[oscillator]* 10)) % 10;
                sublevels[5]=self->tenth;
              break;
              case 2:
                display.fillRect(100, 0, 12, 16, SSD1306_INVERSE);
                self->hundredth = ((int)(wavesfreqs[oscillator] * 100)) % 10;
                sublevels[5]=self->hundredth;
              break;
            }
          display.display();
          }
        }
        static void freqbars_panel_action() {

          navrange = 9;
          switch (sublevels[4]){
            case 0:
              self->unit = sublevels[5];
            break;
            case 1:
              self->tenth = sublevels[5];
              //Serial.println(self->hundredth);
            break;
            case 2:
              self->hundredth = sublevels[5];
              //Serial.println(self->hundredth);
            break;
          }

          wavesfreqs[oscillator] = (float)(self->unit + self->tenth * 0.1f + self->hundredth * 0.01f);
        }

        static void displayfreqbars(){
          dm.clear_3();
          display.setTextSize(2);
          display.setCursor(65, 0);
          display.println(wavesfreqs[oscillator]);
          draw_synth_params();
          dm.dodisplay();
        }

        static void freqbars_panel() {
          if (navlevel >= 4) {
            retroaction = sublevels[3];
            if (navlevel == 4) {
              navrange = 2;

            }
            if (navlevel == 5) {
              retroaction = sublevels[4];
              freqbars_panel_action();
            }
            if (navlevel >= 6) {
              returntonav(4,9,sublevels[4]);
            }
            //dm.dodisplay();
          }
          displayfreqbars();
          freqbars_panel_selector();
          if (navlevel == 3) {
            retroaction = sublevels[2];
            navrange = synth_params_count - 1;
            //sublevels[4] = round(wavesfreqs[oscillator]);
          }
        }

        static void displayphasebars() {
          dm.clear_3();
          if (navlevel == 3) {
            retroaction = sublevels[2];
            navrange = synth_params_count - 1;
            sublevels[4] = int(phaselevelsL[oscillator]);
          }
          if (navlevel >= 4) {
            if (navlevel == 4) {
              navrange = 360;
              retroaction = sublevels[3];
              phaselevelsL[oscillator] = int(sublevels[4]);
              setphaselevel();
            }
            if (navlevel >= 5) {
              setphaselevel();
              returntonav(3,synth_params_count-1,sublevels[3]);
            }
          }

          draw_synth_params();

          display.setCursor(80, 0);
          display.setTextSize(2);
          display.println(phaselevelsL[oscillator]);
          dm.dodisplay();
        }

        static void displayModulatedbool() {
          char modulation_labels[4][7] = {"Off", "Freq", "Phase", "Ampl"};

          draw_synth_params();
          dm.dodisplay();
          display.setCursor(64, 0);
          display.setTextSize(2);
          display.println(modulation_labels[FMmodulated[oscillator]]);
          draw_synth_params();
          dm.dodisplay();

        }

        static void setfmtophase() {
          for (byte i = 0; i < SYNTH_LINERS_COUNT; i++) {
            //phaseModulation should be based on lfo level
            FMwaveforms1[i + (oscillator * SYNTH_LINERS_COUNT)]->phaseModulation(180);
          }
        }

        static void setfmtofreq() {
          for (byte i = 0; i < SYNTH_LINERS_COUNT; i++) {
            //phaseModulation should be based on lfo level
            FMwaveforms1[i + (oscillator * SYNTH_LINERS_COUNT)]->frequencyModulation(10);
          }
        }

        static void wavelineModulatedbool() {
          dm.clear_3();
          if (navlevel == 3) {
            retroaction = sublevels[2];
            navrange = synth_params_count - 1;
          }
          if (navlevel == 4) {
            navrange = 3;
            retroaction = sublevels[3];
            FMmodulated[oscillator] = sublevels[4];
          }
          if (navlevel > 4) {
            setwavetypefromlist();
            returntonav(3,synth_params_count-1,sublevels[3]);
          }
          displayModulatedbool();
        }

        static void displaywaveformicon(){
          dm.clear_3();
          if (navlevel == 3) {
            retroaction = sublevels[2];
            navrange = synth_params_count - 1;
            sublevels[4] = Waveformstyped[oscillator];
          }
          if (navlevel == 4) {
            navrange = 11;
            Waveformstyped[oscillator] = sublevels[4];
            retroaction = sublevels[3];
          }
          if (navlevel > 4) {
            setwavetypefromlist();
            if (Waveformstyped[oscillator] == 11) {
              mixlevelsL[oscillator] = 0;
              _mx.setwavemixlevel();
            }
            returntonav(3,synth_params_count-1,sublevels[3]);
            return;
          }
          const unsigned char *_img[12] = { sinewave, sawtoothwave, reversesawtoothwave, trianglewave,
                                        variabletriangle, squarewave, pulsewave,arbitrarywave,
                                        samplehold,arbitrarywave,samplehold,moonwave};
          String lelabelw[12] = {"SineWave","SawWave","ReverseSaw" ,"Triangle","V-Triangle","SquareWave",
                              "PulseWave","Arbitrary","SampleHold", "Drum","String", "Wave OFF"};

          display.drawBitmap(74, 20, _img[sublevels[4]], 32, 32, SSD1306_WHITE);
          display.setTextSize(1);
          display.setTextColor(SSD1306_WHITE);
          display.setCursor(64, 0);
          display.println(lelabelw[sublevels[4]]);
          display.setCursor(120, 57);
          display.print(oscillator + 1);
          draw_synth_params();
          dm.dodisplay();
        }

        static void displayLFOpanel() {
          dm.clear_3();
          if (navlevel == 3 ) {
            retroaction = sublevels[2];
            navrange = synth_params_count - 1;
          }
          draw_synth_params();
            dm.dodisplay();
          if (navlevel >= 4) {
            sublevels[0] = 1;
            sublevels[1] = oscillator;
            sublevels[2] = 0;
            returntonav(navlevel-2,sizeofLFOlabels - 1,0);
          }
        }

        static void go_previous(){
          dm.clear_3();
          if (navlevel == 3) {
            retroaction = sublevels[2];
            navrange = synth_params_count - 1;
          }

          if (navlevel >= 4) {
            if (oscillator-1 < 0)
              oscillator = 2 ;
            else
              oscillator = oscillator-1;

            sublevels[2] = oscillator ;
            returntonav(navlevel-1,synth_params_count-1,sublevels[3]);
            return;
          }
          draw_synth_params();
          dm.dodisplay();
        }
        static void go_next(){
          dm.clear_3();
          if (navlevel == 3) {
            retroaction = sublevels[2];
            navrange = synth_params_count - 1;
          }
          if (navlevel >= 4) {
            oscillator = (oscillator+1)%3;
            sublevels[2] = oscillator ;
            returntonav(navlevel-1,synth_params_count-1,sublevels[3]);
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
          retroaction = sublevels[3];
          _synth_params[sublevels[3]]();
        }

        static void draw_synth_params() {
          char wavelineslabels[synth_params_count][12] = {
              "Type", "Mod", "LFO", "Freq", "Offset", "Phase", "<-  ", "  ->"};

          int startx = 2;
          int starty = 16;
          char *textin = (char *)wavelineslabels[sublevels[3]];
          canvastitle.fillScreen(SSD1306_BLACK);
          canvastitle.setCursor(0, 0);
          canvastitle.setTextSize(2);
          canvastitle.println(textin);
          canvasBIG.setTextSize(1);
          canvasBIG.fillScreen(SSD1306_BLACK);
          for (int i = 0; i < synth_params_count - 1 - (sublevels[3]); i++) {
            canvasBIG.setCursor(startx, starty + ((i)*10));
            canvasBIG.println(wavelineslabels[sublevels[3] + 1 + i]);
          }
          for (int i = 0; i < sublevels[3]; i++) {
            canvasBIG.setCursor(startx,(10 * (synth_params_count - sublevels[3]) + 6 + ((i)*10)));
            canvasBIG.println(wavelineslabels[i]);
          }
          canvasBIG.setCursor(120, 57);
          canvasBIG.print(oscillator + 1);
        }

        static void dolistsyntmenu() {
          char synthmenulabels[SN_MENU_LABELS_COUNT][12] = {"Synths", "Mixer", "ADSR", "MP3 Player", "Filter"};
          byte startx = 5;
          byte starty = 16;
          char *textin = (char *)synthmenulabels[sublevels[1]];
          canvastitle.fillScreen(SSD1306_BLACK);
          canvastitle.setCursor(0, 0);
          canvastitle.setTextSize(2);
          canvastitle.println(textin);
          canvasBIG.setTextSize(1);
          canvasBIG.fillScreen(SSD1306_BLACK);
          for (int i = 0; i < 4 - (sublevels[1]); i++) {
            canvasBIG.setCursor(startx, starty + ((i)*10));
            canvasBIG.println(synthmenulabels[sublevels[1] + 1 + i]);
          }
          for (int i = 0; i < sublevels[1]; i++) {
            canvasBIG.setCursor(startx, (10 * (5 - sublevels[1])) + 6 + ((i)*10));
            canvasBIG.println(synthmenulabels[i]);
          }
        }

        static void synths_switcher(){
          String titled = "Waveline ";
          oscillator = sublevels[2]%OSCS_COUNT;
          String synth_num = oscillator + 1 ;
          navrange = OSCS_COUNT-1;
          String leprintlabel = titled + synth_num ;
          wavelinesBG();
          sublevels[3] = 0;
          display.fillRect(0+(oscillator%2)*64, 16+(24*(oscillator/2)), 64, 24, SSD1306_INVERSE);
          dm.printlabel((char*)leprintlabel.c_str());
          display.display();
        }

        static void wavesline_selector(){
          retroaction = sublevels[navlevel-2] ;
          _waveliners[navlevel-2]();
        }

        static void synth_nav_zero() {
            navrange = 4;
            display.clearDisplay();
            //if (!retroaction)
            //  reinitsublevels(2);
            dolistsyntmenu();
            retroaction = sublevels[1] ;
            dm.dodisplay();
        }

        static void mp3_player_play(){
          if (!SD.exists((char*)mp3_name.c_str())) {
            get_next_mp3();
          }
          playFile((char*)mp3_name.c_str());
        }

        static void mp3_player_stop(){
          playMp31.stop();
          mp3_continue = 0 ;
        }

        static void mp3_player_continous(){
          mp3_continue = !mp3_continue ;
        }

        static void mp3_player_pause(){
          mp3_paused = playMp31.pause(!mp3_paused);
          mp3_continue = 0 ;
        }

        static void mp3_player_next(){
          if (!mp3_looped)
            next_mp3++;
          get_next_mp3();
        }

        static void mp3_player_previous(){
          if (!mp3_looped)
            next_mp3 -= 2;
          get_next_mp3();
        }

        static void mp3_player_shuffle(){
          mp3_shuffle = !mp3_shuffle ;
          //TODO
          //each play next_mp3 is random % total ?
        }
        static void mp3_loop_setter(){
          mp3_looped = !mp3_looped ;
          mp3_continue = mp3_looped ;
        }
        static void mp3_player_actions() {
          if (navlevel == 2) {
            navrange = 8;
          }
          if (navlevel >= 3) {
            switch (sublevels[2]) {
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
            returntonav(2,8,sublevels[2]);
          }
        }
        static void get_file_type(){
          /*
          int dot = mp3_name.lastIndexOf('.');
          if (dot >= 0) {
            String extension = mp3_name.substring(dot + 1);

          }
          */
          String filenamed = mp3_name ;
          filenamed.toLowerCase();
          if (filenamed.endsWith(".mp3"))
              mp3_ext = 0 ;
            if (filenamed.endsWith(".flac"))
              mp3_ext = 1 ;
        }

        static void playFile(const char *mp3_file) {
          get_file_type();
          switch (mp3_ext){
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

          if (SD.exists("MP3") ) {
            File susudir = SD.open("MP3");
            if (!mp3_looped) {
              while (file_index <= next_mp3) {
                File subentry = susudir.openNextFile();
                if (!subentry) {
                  file_index = 0 ;
                  next_mp3 = 0 ;
                  return;
                }

                if (!subentry.isDirectory()) {
                  file_index++;
                  mp3_name = mp3_dir + subentry.name();
                }
                subentry.close();
              }
              next_mp3++;
            } else {

              while (file_index < next_mp3) {
                File subentry = susudir.openNextFile();
                if (!subentry) {
                  file_index = 0 ;
                  return;
                }

                if (!subentry.isDirectory()) {
                  file_index++;
                  mp3_name = mp3_dir + subentry.name();
                }
                subentry.close();
              }

            }
            file_index = 0 ;
            susudir.close();
          }
          //Serial.println((char*)mp3_name.c_str());

        }

        static void transport_selector() {
          String _legend[] = {"Play All","Previous","Pause","Play file","Next","Shuffle","Loop","Stop"," "};
          int startyp = 8;
          int ecart = 14;
          display.fillRect(ecart * (sublevels[navlevel])-3, startyp-2, ecart-1, startyp*1.5, SSD1306_INVERSE);
          display.setCursor(0,20);
          display.setTextSize(1);
          display.setTextColor(SSD1306_INVERSE);
          display.print(_legend[sublevels[2]]);
          display.display();
        }

        static void play_flac_file(const char *flac_file) {
          playMp31.stop();
          playFlac1.play(flac_file);
          //playFlac1.setPlaybackCompleteCallback(display_mp3_title);

        }


        static void display_mp3_title(){
          canvasBIG.setCursor(0,40);
          String titler = mp3_name;
          titler.remove(0, 4);
          //titler.remove(titler.length() - 4);
          canvasBIG.print((char*)titler.c_str());
        }

        static void mp3_player_panel() {
          dm.clear_3();
          drawtransport();
          mp3_player_actions();
          dm.dodisplay();
          transport_selector();
          display_mp3_title();
          dm.dodisplay();
          //placeholder
        }

   

        static void plug_no_waves(){
          mixlevelsL[oscillator] = 0;
          for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
            wavelinescords[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            stringcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            drumcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            FMwavecords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            MDdrumcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            MDwavecords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            MDstringcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            modulatecords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
          }
        }

        static void plug_waves(){
          for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
            FMwavecords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            stringcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            modulatecords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            MDdrumcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            MDstringcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            MDwavecords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            drumcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            wavelinescords[i + (SYNTH_LINERS_COUNT * oscillator)]->connect();
            if (Waveformstyped[oscillator] == 7) {
              waveforms1[i + (SYNTH_LINERS_COUNT * oscillator)]->arbitraryWaveform(arbitrary_waveforms[oscillator],arbitrary_maxF[oscillator]);
            }
            waveforms1[i + (SYNTH_LINERS_COUNT * oscillator)]->begin(lesformes[Waveformstyped[oscillator]]);
          }
        }

        static void plug_moded_waves(){
          for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
            wavelinescords[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            modulatecords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            MDdrumcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            MDstringcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            stringcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            drumcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            MDwavecords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            FMwavecords1[i + (SYNTH_LINERS_COUNT * oscillator)]->connect();
            if (Waveformstyped[oscillator] == 7) {
              FMwaveforms1[i + (SYNTH_LINERS_COUNT * oscillator)]->arbitraryWaveform(arbitrary_waveforms[oscillator],arbitrary_maxF[oscillator]);
            }
            FMwaveforms1[i + (SYNTH_LINERS_COUNT * oscillator)]->begin(lesformes[Waveformstyped[oscillator]]);
          }
          call_restart_lfo(oscillator);
        }

        static void plug_ampl_moded_waves(){
          for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
            wavelinescords[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            MDdrumcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            MDstringcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            stringcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            drumcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            FMwavecords1[i + (oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            MDwavecords1[i + (SYNTH_LINERS_COUNT * oscillator)]->connect();
            modulatecords1[i + (SYNTH_LINERS_COUNT * oscillator)]->connect();
            if (Waveformstyped[oscillator] == 7) {
              waveforms1[i + (SYNTH_LINERS_COUNT * oscillator)]->arbitraryWaveform(arbitrary_waveforms[oscillator],arbitrary_maxF[oscillator]);
            }
            waveforms1[i + (SYNTH_LINERS_COUNT * oscillator)]->begin(lesformes[Waveformstyped[oscillator]]);
          }
          call_restart_lfo(oscillator);
        }

        static void plug_strings_waves(){
          for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
            wavelinescords[i + (oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            drumcords1[i + (oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            FMwavecords1[i + (oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            modulatecords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            MDwavecords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            MDdrumcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            MDstringcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            stringcords1[i + (oscillator * SYNTH_LINERS_COUNT)]->connect();
          }
        }

        static void plug_ampl_moded_strings(){
          for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
            wavelinescords[i + (oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            drumcords1[i + (oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            FMwavecords1[i + (oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            stringcords1[i + (oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            MDwavecords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            MDdrumcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            MDstringcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->connect();
            modulatecords1[i + (SYNTH_LINERS_COUNT * oscillator)]->connect();
          }
        }

        static void plug_drum_waves(){
          for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
            wavelinescords[i + (oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            stringcords1[i + (oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            FMwavecords1[i + (oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            modulatecords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            MDwavecords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            MDdrumcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            MDstringcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            drumcords1[i + (oscillator * SYNTH_LINERS_COUNT)]->connect();
          }
        }

        static void plug_ampl_moded_drums(){
          for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
            wavelinescords[i + (oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            stringcords1[i + (oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            FMwavecords1[i + (oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            drumcords1[i + (oscillator * SYNTH_LINERS_COUNT)]->disconnect();
            MDwavecords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            MDstringcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->disconnect();
            //TODO: apply to other types too
            modulatecords1[i + (SYNTH_LINERS_COUNT * oscillator)]->connect();
            MDdrumcords1[i + (SYNTH_LINERS_COUNT * oscillator)]->connect();
          }
        }

        static void no_modulation(){
              byte letype = Waveformstyped[oscillator];
              if (letype < 9) {
                plug_waves();
              }
              else if (letype == 9) {
                plug_drum_waves();
              }
              else if (letype == 10) {
                plug_strings_waves();
              }
        }

        static void freq_modulation(){
          byte letype = Waveformstyped[oscillator];
          if (letype < 9) {
            plug_moded_waves();
          }
          //no freq modulation on strings or drums
          else if (letype == 9) {
            plug_drum_waves();
          }
          else if (letype == 10) {
            plug_strings_waves();
          }
        }

        static void phase_modulation(){
          byte letype = Waveformstyped[oscillator];
          if (letype < 9) {
              plug_moded_waves();
            }
            //no phase modulation on strings or drums
            else if (letype == 9) {
              plug_drum_waves();
            }
            else if (letype == 10) {
              plug_strings_waves();
          }
        }

        static void amplitude_modulation(){
          byte letype = Waveformstyped[oscillator];
          if (letype < 9) {
              plug_ampl_moded_waves();
            }
            else if (letype == 9) {
              // amplitude modulated drum
              plug_ampl_moded_drums();
            }
            else if (letype == 10) {
              // amplitude modulated string
              plug_ampl_moded_strings();
            }
            call_restart_lfo(oscillator);
        }

        static void setwavetypefromlist() {
          AudioNoInterrupts();
          byte letype = Waveformstyped[oscillator];
          if (letype == 11) {
            // synth line off
            plug_no_waves();
            AudioInterrupts();
            _mx.setwavemixlevel();
            return;
          }
          (modulation_pointers[FMmodulated[oscillator]] )();
          AudioInterrupts();
          _mx.setwavemixlevel();
        }

        static void setphaselevel() {
          AudioNoInterrupts();
          for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
            waveforms1[i + (SYNTH_LINERS_COUNT * oscillator)]->phase(phaselevelsL[oscillator]);
          }
          AudioInterrupts();
        }

        void setsynthfrequencyi(float tune, int voice, byte velocityz) {
          // AudioNoInterrupts();
          for (int i = 0; i < OSCS_COUNT; i++) {
            waveforms1[voice + (i * SYNTH_LINERS_COUNT)]->frequency(tune * wavesfreqs[i - 1]);
            waveforms1[voice + (i * SYNTH_LINERS_COUNT)]->amplitude(velocityz / 127.0);
            FMwaveforms1[voice + (i * SYNTH_LINERS_COUNT)]->frequency(tune * wavesfreqs[i - 1]);
            FMwaveforms1[voice + (i * SYNTH_LINERS_COUNT)]->amplitude(velocityz / 127.0);
            drums1[voice + (i * SYNTH_LINERS_COUNT)]->length(velocityz * 5);
          }
          // AudioInterrupts();
        }



        static constexpr void (*_nav_synth[])() = {&wavesline_selector,&call_mx_show, &call_ad_show, &mp3_player_panel, &call_fl_show};
        static constexpr void (*_waveliners[6])() = {&synths_switcher,&wavelining, &wavelining, &wavelining,&wavelining, &wavelining};
        static constexpr void (*modulation_pointers[4])() = {&no_modulation,&freq_modulation,&phase_modulation,&amplitude_modulation};

        static constexpr void (*_synth_params[synth_params_count])() = {&displaywaveformicon,&wavelineModulatedbool,&displayLFOpanel,
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
EXTMEM SynthMenuRouter _sn;