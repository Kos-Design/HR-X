#include "KnobAssigner.h"

KnobAssigner* KnobAssigner::self = nullptr;

KnobAssigner::KnobAssigner() {
                    self = this;
                    self->home_navrange=CtlCount-1;
                    self->relative_navlevel=2;
                    self->max_navlevel=3;
                    self->sublevels_address={2,0,0};
                    }
 
void KnobAssigner::KnobAssigner::show() {
        lv.knobsetting = false ;
        _actionable[lv.navlevel-self->relative_navlevel]();
      }
void KnobAssigner::learn_midi(byte captured){
        //used to unassign previousely set cc but lets keep it, duplicates are fine
        //gg.midiknobassigned[find_assigned_knob(lv.sublevels[1])] = 0;
        lv.sublevels[self->relative_navlevel+1] = captured ;
        gg.midiknobassigned[lv.sublevels[self->relative_navlevel+1]] = lv.sublevels[self->relative_navlevel];
        dm.returntonav(self->relative_navlevel,self->home_navrange,lv.sublevels[self->relative_navlevel]);
      }

int KnobAssigner::find_assigned_knob(int k){
        for (int i = 0; i < 128; i++) {
          if (gg.midiknobassigned[i] == k){
            return i;
          }
        }
        return 0 ;
      }

void KnobAssigner::kb_home(){
        lv.navrange = self->home_navrange;
        dm.clean_title_1_2();
        if (lv.sublevels[self->relative_navlevel] != 0) {
          
          canvastitle.println(ctl[lv.sublevels[self->relative_navlevel]].name);
          canvasBIG.setTextSize(2);
          canvasBIG.setCursor(0, 40);
          lv.sublevels[self->relative_navlevel+1] = find_assigned_knob(lv.sublevels[self->relative_navlevel]) ;
          if (lv.sublevels[self->relative_navlevel+1] != 0) {
            canvasBIG.print("Midi");
            canvasBIG.setTextSize(1);
            canvasBIG.setCursor(50, 47);
            canvasBIG.print("(cc)");
            canvasBIG.setCursor(71, 39);
            canvasBIG.setTextSize(3);
            canvasBIG.print(":");
            canvasBIG.setTextSize(2);
            canvasBIG.setCursor(85, 40);

            canvasBIG.print(lv.sublevels[self->relative_navlevel+1]);
          } else {
            //canvasBIG.setTextSize(1);
            canvasBIG.println("Unassigned");
          }
        } else {
          canvastitle.setTextSize(2);
          canvastitle.println("Select");
          canvasBIG.setTextSize(2);
          canvasBIG.setCursor(0, 28);
          canvasBIG.println("Control");
        }
        dm.dodisplay();

      }

void KnobAssigner::assigner(){
        lv.knobsetting = true ;
        lv.navrange = 127;
        if (lv.sublevels[self->relative_navlevel] == 0 ) {
          dm.returntonav(self->relative_navlevel,self->home_navrange,lv.sublevels[self->relative_navlevel]);
        } else {
          dm.clean_title_1_2();
          canvastitle.println(ctl[lv.sublevels[self->relative_navlevel]].name);
          canvasBIG.setCursor(0, 40);
          if (lv.sublevels[self->relative_navlevel+1] != 0) {
            canvasBIG.print("Midi");
            canvasBIG.setTextSize(1);
            canvasBIG.setCursor(50, 47);
            canvasBIG.print("(cc)");
            canvasBIG.setCursor(71, 39);
            canvasBIG.setTextSize(3);
            canvasBIG.print(":");
            canvasBIG.setTextSize(2);
            canvasBIG.setCursor(85, 40);
            canvasBIG.print(lv.sublevels[self->relative_navlevel+1]);
          } else {
            //canvasBIG.setTextSize(1);
            canvasBIG.println("Unassigned");
          }
        }
        dm.dodisplay();
      }
      
void KnobAssigner::set_midi_cc_to_ctl(byte cc_nt, int cc_cl){
        gg.midiknobassigned[cc_nt] = cc_cl;
      }

void KnobAssigner::set_it(){
        lv.knobsetting = false ;
        set_midi_cc_to_ctl(find_assigned_knob(lv.sublevels[self->relative_navlevel]), 0);
        set_midi_cc_to_ctl(lv.sublevels[self->relative_navlevel+1] , lv.sublevels[self->relative_navlevel]);

        dm.returntonav(self->relative_navlevel,self->home_navrange, lv.sublevels[self->relative_navlevel]);
      }


AdsrMenuRouter* AdsrMenuRouter::self = nullptr;

AdsrMenuRouter::AdsrMenuRouter() {
                    self = this;
                    self->home_navrange=SN_MENU_LABELS_COUNT-1;
                    self->relative_navlevel=1;
                    self->max_navlevel=5;
                    self->sublevels_address={0,0,0};
                    }
    
void AdsrMenuRouter::show(){
      displayadsrgraph();
    }

void AdsrMenuRouter::ApplyADSR() {
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
void AdsrMenuRouter::displayadsrgraph() {
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

void AdsrMenuRouter::SetADSR() {
      gg.adsrlevels[AttackDelay] = self->MadsrAttackDelay;
      gg.adsrlevels[Sustain] = self->mappedsustain;
      gg.adsrlevels[Release] = self->mappedrelease;
      gg.adsrlevels[Decay] = self->mappeddecay;
      gg.adsrlevels[Attack] = self->mappedattack;
      gg.adsrlevels[Hold] = self->MadsrHold;
    }

void AdsrMenuRouter::GlobalADSR() {
      SetADSR();
      ApplyADSR();
    }

void AdsrMenuRouter::print_adsr_echo(String titre, int niveau){
      canvastitle.setTextSize(1);
      canvastitle.setCursor(0, 0);
      canvastitle.fillScreen(SSD1306_BLACK);
      canvastitle.println(titre);
      canvastitle.setCursor(55, 0);
      canvastitle.println(niveau);
    }

void AdsrMenuRouter::sliceA() {
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

void AdsrMenuRouter::sliceDa() {
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

void AdsrMenuRouter::sliceH() {
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

void AdsrMenuRouter::sliceD() {

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

void AdsrMenuRouter::sliceS() {
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

void AdsrMenuRouter::sliceR() {
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

