
void initialize303group() {

  for (int i = 0; i < liners_count; i++) {
    setle303filterpass(i);
    les303wet[i]->gain(1, 1);
    les303wet[i]->gain(0, 0);
    les303filterz[i]->frequency(220);
    les303filterz[i]->resonance(5);
  }
}

void setmastersmixlevel(int lebus) {
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
void ApplyADSR() {
  for (int i = 0; i < liners_count; i++) {
    enveloppesL[i]->delay(adsrlevels[0]);
    enveloppesL[i]->attack(adsrlevels[1]);
    enveloppesL[i]->hold(adsrlevels[2]);
    enveloppesL[i]->decay(adsrlevels[3]);
    enveloppesL[i]->sustain(adsrlevels[4] / 100.0);
    enveloppesL[i]->release(adsrlevels[5]);
  }
  mappedattack = adsrlevels[1];
  mappeddecay = adsrlevels[3];
  mappedrelease = adsrlevels[5];
  mappedsustain = adsrlevels[4];
  MadsrAttackDelay = adsrlevels[0];
  MadsrHold = adsrlevels[2];
}

void setle303filterpass(int linei) {
  les303passes[linei]->gain(0,le303filterzgainz[0]);
  les303passes[linei]->gain(1,le303filterzgainz[1]);
  les303passes[linei]->gain(2,le303filterzgainz[2]);
}
void le303filtercontrols() {
  for (int i = 0; i < liners_count; i++) {
    setle303filterpass(i);

  }
}

void Wavespreamp303controls() {
  for (int i = 0; i < liners_count; i++) {
    Wavespreamp303[i]->gain(preampleswaves*2 / 127.0);
  }
}

void le303filterzWet() {
  for (int i = 0; i < liners_count; i++) {
    les303wet[i]->gain(0, le303filterzwet / 100.0);
    les303wet[i]->gain(1, (1 - (le303filterzwet / 100.0)));
  }
}

void setlepulse1() {
  le303pulsewidth = (cutoff_pulse / 32.0) * 2 * millitickinterval;
  if (le303pulsewidth < 50) {
    le303pulsewidth = 50;
  }
  for (int i = 0; i < liners_count ; i++) {
    //blink303[i]->setDuration(le303pulsewidth);
    pulsers[i][1]=le303pulsewidth;
  }
}

void setlepulse2() {
  le303pulsewidth2 = (reson_pulse / 32.0) * 2 * millitickinterval + 50;
  if (le303pulsewidth2 < 50) {
    le303pulsewidth2 = 50;
  }
}

float fxslopedown2(byte curve, float laxval) {
  return pow(laxval, (double)(curve / 127.0));
}

void wetmixmastercontrols() {
  for (byte i = 0; i < 4; i++) {
    WetMixMasterL.gain(i, WetMixMasters[i]/127.0);
    WetMixMasterR.gain(i, WetMixMasters[i]/127.0);
  }
}



void set_dry_mix(int lebus) {

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

class SynthMenuRouter : public SectionHolder {
    public:
        SynthMenuRouter() {
                    this->home_navrange=truesizeofsynthmenulabels-1;
                    this->relative_navlevel=1;
                    this->max_navlevel=5;
                    this->sublevels_address={0,0,0};
                    }

        using sn = void (SynthMenuRouter::*)();

        void show() {
            (this->*SynthMenuRouter::_route_nav[navlevel-1])();
        }

        void route_navlevel_1(){
            synth_nav_zero();
        }

        void route_navlevel_2(){
          retroaction = sublevels[1] ;
            _nav_synth[sublevels[1]]();
        }

        static void displayoffsetwav() {
          dm.clear_3();
          if (navlevel == 3) {
            retroaction = sublevels[2];
            navrange = synth_params_count - 1; 
            sublevels[4] = wave1offset[ccsynthselector];
          }
          if (navlevel == 4) {
            navrange = 127;
            retroaction = sublevels[3];
            wave1offset[ccsynthselector] = sublevels[4];
            for (int i = 0; i < liners_count; i++) {
              waveforms1[i + (ccsynthselector * liners_count)]->offset((float)(((64.0 - wave1offset[ccsynthselector]) / 64.0)));
              FMwaveforms1[i + (ccsynthselector * liners_count)]->offset((float)(((64.0 - wave1offset[ccsynthselector]) / 64.0)));
            }
          }
          if (navlevel >= 5) {
            returntonav(3,synth_params_count-1,sublevels[3]);
            return;
          }
          display.setTextSize(1);
          display.setCursor(80, 8);
          display.print((float)(((64.0 - wave1offset[ccsynthselector]) / 64.0)));
          
          draw_synth_params();
          dodisplay();
        }

        static void displayfreqbars() {
          int score = wavesfreqs[ccsynthselector] ;
          dm.clear_3();
          if (navlevel == 3) {
            retroaction = sublevels[2];
            navrange = synth_params_count - 1; 
            sublevels[4] = round(wavesfreqs[ccsynthselector]);
          }
          // weird but usefull behavior to switch encoder resolution between 0 and 1
          if (navlevel >= 4) {
            if (navlevel == 4) {
              retroaction = sublevels[3];
              navrange = 10;
              if (wavesfreqs[ccsynthselector] == 1) { demimalmode = !demimalmode;}
              else { if (wavesfreqs[ccsynthselector] <= 1) {demimalmode = 1; } }
              if (!demimalmode) {wavesfreqs[ccsynthselector] = sublevels[4]; }
              if (demimalmode) {wavesfreqs[ccsynthselector] = (sublevels[4]) / 10.0; }
            }
            if (navlevel >= 5) {
              if (demimalmode) { wavesfreqs[ccsynthselector] = (sublevels[4]) / 10.0; }
              if (!demimalmode) { wavesfreqs[ccsynthselector] = sublevels[4]; }
              returntonav(3,synth_params_count-1,sublevels[3]);
            }
            
          }
          
          
          display.setTextSize(2);
          display.setCursor(65, 0);
          display.println(wavesfreqs[ccsynthselector]);
          draw_synth_params();
          dodisplay();
        }

        static void displayphasebars() {
          dm.clear_3();
          if (navlevel == 3) {
            retroaction = sublevels[2];
            navrange = synth_params_count - 1; 
            sublevels[4] = int(phaselevelsL[ccsynthselector]);
          }
          if (navlevel >= 4) {
            if (navlevel == 4) {
              navrange = 360;
              retroaction = sublevels[3];
              phaselevelsL[ccsynthselector] = int(sublevels[4]);
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
          display.println(phaselevelsL[ccsynthselector]);
          dodisplay();
        }

        static void displayModulatedbool() {
          char modulation_labels[4][7] = {"Off", "Freq", "Phase", "Ampl"};
          
          draw_synth_params();
          dodisplay();
          display.setCursor(64, 0);
          display.setTextSize(2);
          display.println(modulation_labels[FMmodulated[ccsynthselector]]);
          draw_synth_params();
          dodisplay();
          
        }

        static void setfmtophase() {
          for (byte i = 0; i < liners_count; i++) {
            //phaseModulation should be based on lfo level
            FMwaveforms1[i + (ccsynthselector * liners_count)]->phaseModulation(180);
          }
        }

        static void setfmtofreq() {
          for (byte i = 0; i < liners_count; i++) {
            //phaseModulation should be based on lfo level
            FMwaveforms1[i + (ccsynthselector * liners_count)]->frequencyModulation(10);
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
            FMmodulated[ccsynthselector] = sublevels[4];
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
            sublevels[4] = Waveformstyped[ccsynthselector];
          }
          if (navlevel == 4) {
            navrange = 11;
            Waveformstyped[ccsynthselector] = sublevels[4];
            retroaction = sublevels[3];
          }
          if (navlevel > 4) {
            setwavetypefromlist();
            if (Waveformstyped[ccsynthselector] == 11) {
              mixlevelsL[ccsynthselector] = 0;
              setwavemixlevel();
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
          display.print(ccsynthselector + 1);
          draw_synth_params();
          dodisplay();
        }

        static void displayLFOpanel() {
          dm.clear_3();
          if (navlevel == 3 ) {
            retroaction = sublevels[2];
            navrange = synth_params_count - 1; 
          }
          draw_synth_params();
            dodisplay();
          if (navlevel >= 4) {
            sublevels[0] = 1;
            sublevels[1] = ccsynthselector;
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
            ccsynthselector = (ccsynthselector-1)%3;
            sublevels[2] = ccsynthselector ;
            returntonav(navlevel-1,synth_params_count-1,sublevels[3]);
            return;
          }
          draw_synth_params();
          dodisplay();
        }
        static void go_next(){
          dm.clear_3();
          if (navlevel == 3) {
            retroaction = sublevels[2];
            navrange = synth_params_count - 1; 
          }    
          if (navlevel >= 4) {
            ccsynthselector = (ccsynthselector+1)%3;
            sublevels[2] = ccsynthselector ;
            returntonav(navlevel-1,synth_params_count-1,sublevels[3]);
          }
          draw_synth_params();
          dodisplay();
        }

        static void wavelinesBG() {
          display.clearDisplay();
          display.drawBitmap(0, 64 - 47, wavesbg2, 128, 47, SSD1306_WHITE);
          display.display();
        }
    
        static void wavelining() {
          _synth_params[sublevels[3]]();
        }
        
        static void displayadsrgraph() {
          if (sublevels[2] == 2) {
            navleveloverwrite = 2;
          }
          if (sublevels[1] == 0) {
            navleveloverwrite = 4;
          }

          canvastitle.fillScreen(SSD1306_BLACK);
          canvastitle.setCursor(0, 0);
          canvastitle.setTextSize(1);

          canvasBIG.setTextSize(1);
          canvasBIG.fillScreen(SSD1306_BLACK);
          canvasBIG.drawLine(2, 61, 2, 18, SSD1306_WHITE);
          canvasBIG.drawLine(2, 61, 125, 61, SSD1306_WHITE);
          canvasBIG.drawLine(125, 59, 127, 61, SSD1306_WHITE);
          canvasBIG.drawLine(125, 63, 127, 61, SSD1306_WHITE);
          canvasBIG.drawLine(2, 16, 0, 18, SSD1306_WHITE);
          canvasBIG.drawLine(2, 16, 4, 18, SSD1306_WHITE);

          // mappedsustain
          int totalliner = mappedattack * 10 + mappeddecay + 100 + mappedrelease +
                          MadsrAttackDelay * 2 + MadsrHold + 5;
          float linerratio = 124.0 / totalliner;
          int a0 = round(MadsrAttackDelay * 10 * linerratio) + 5;
          int a1 = round(mappedattack * 10 * linerratio) + a0;
          int h0 = a1;
          int h1 = a1 + round(MadsrHold * linerratio);
          int d0 = h1;
          int d1 = d0 + round(mappeddecay * linerratio);
          int s0 = d1;
          int s1 = s0 + 100 * linerratio;
          int suY = map(mappedsustain, 0, 100, 37, 0) + 22;
          int r0 = s1;
          int r1 = r0 + mappedrelease * linerratio;
          int startx = 3;
          int starty = 16;

          canvasBIG.drawLine(a0, 61, a1, 24, SSD1306_WHITE);
          canvasBIG.drawLine(h0, 24, h1, 24, SSD1306_WHITE);
          canvasBIG.drawLine(d0, 24, d1, suY, SSD1306_WHITE);
          canvasBIG.drawLine(s0, suY, s1, suY, SSD1306_WHITE);
          canvasBIG.drawLine(r0, suY, r1, 61, SSD1306_WHITE);
          display.clearDisplay();
          dodisplay();

          // preparing for next display loop
          dm.clear_buffs();

          switch (sublevels[navleveloverwrite]) {
          case 0:
            display.fillRect(startx, starty,
                            round(MadsrAttackDelay * 10 * linerratio) + 1, 45,
                            SSD1306_INVERSE);
            display.display();
            sliceDa();
            break;

          case 1:
            display.fillRect(a0, starty, round(mappedattack * 10 * linerratio) + 2, 45,
                            SSD1306_INVERSE);
            display.display();

            sliceA();
            break;

          case 2:
            display.fillRect(h0, starty, round(MadsrHold * linerratio) + 2, 45,
                            SSD1306_INVERSE);
            display.display();

            sliceH();
            break;
          case 3:
            display.fillRect(d0, starty, round(mappeddecay * linerratio) + 1, 45,
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
            display.fillRect(r0, starty, round(mappedrelease * linerratio) + 1, 45,
                            SSD1306_INVERSE);
            display.display();

            sliceR();
            break;

          default:
            break;
          }


          dodisplay();

          dm.clear_buffs();
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
            sublevels[navlevel + 1] = mappedattack;
            returntonav(navlevel + 1, 5,sublevels[navlevel + 1]);
          }

          if (navlevel == navleveloverwrite + 2) {
            navrange = 1024;


            mappedattack = sublevels[navleveloverwrite + 2];
          }
          if (navlevel == navleveloverwrite + 3) {
            if (sublevels[1] == 2) {
              GlobalADSR();
            }
            returntonav(navleveloverwrite, 5,sublevels[navleveloverwrite]);

          }
          print_adsr_echo("Attack ",mappedattack);
        }

        static void sliceDa() {
          if (navlevel == navleveloverwrite + 1) {

            sublevels[navlevel + 1] = MadsrAttackDelay;
            returntonav(navlevel + 1, 5,sublevels[navlevel + 1]);
          }
          if (navlevel == navleveloverwrite + 2) {
            navrange = 100;

            MadsrAttackDelay = sublevels[navleveloverwrite + 2];
          }
          if (navlevel == navleveloverwrite + 3) {
            if (sublevels[1] == 2) {
              GlobalADSR();
            }

            returntonav(navleveloverwrite, 5,sublevels[navleveloverwrite]);
          }
          print_adsr_echo("Attack Delay ",MadsrAttackDelay);
        }

        static void sliceH() {
          if (navlevel == navleveloverwrite + 1) {
            sublevels[navlevel + 1] = MadsrHold;
            returntonav(navlevel + 1, 5,sublevels[navlevel + 1]);
          }
          if (navlevel == navleveloverwrite + 2) {
            navrange = 100;
            MadsrHold = sublevels[navleveloverwrite + 2];
          }
          if (navlevel == navleveloverwrite + 3) {
            if (sublevels[1] == 2) {
              GlobalADSR();
            }

            returntonav(navleveloverwrite, 5,sublevels[navleveloverwrite]);
          }
          print_adsr_echo("Hold ",MadsrHold);
        }

        static void sliceD() {

          if (navlevel == navleveloverwrite + 1) {
            sublevels[navlevel + 1] = mappeddecay;
            returntonav(navlevel + 1, 5,sublevels[navlevel + 1]);
          }
          if (navlevel == navleveloverwrite + 2) {
            navrange = 512;
            mappeddecay = sublevels[navleveloverwrite + 2];
          }
          if (navlevel == navleveloverwrite + 3) {
            if (sublevels[1] == 2) {
              GlobalADSR();
            }

            returntonav(navleveloverwrite, 5,sublevels[navleveloverwrite]);
          }


          print_adsr_echo("Decay ",mappeddecay);
        }

        static void sliceS() {
          if (navlevel == navleveloverwrite + 1) {
            sublevels[navlevel + 1] = mappedsustain;
            returntonav(navlevel + 1, 5,sublevels[navlevel + 1]);
          }
          if (navlevel == navleveloverwrite + 2) {
            navrange = 100;
            mappedsustain = sublevels[navleveloverwrite + 2];
          }
          if (navlevel == navleveloverwrite + 3) {
            if (sublevels[1] == 2) {
              GlobalADSR();
            }

            returntonav(navleveloverwrite, 5,sublevels[navleveloverwrite]);
          }
          print_adsr_echo("Sustain ",mappedsustain);

        }

        static void sliceR() {
          retroaction = navleveloverwrite ;
          if (navlevel == navleveloverwrite + 1) {
            returntonav(navlevel + 1, 5,sublevels[navlevel + 1]);
            sublevels[navlevel + 1] = mappedrelease;
          }
          if (navlevel == navleveloverwrite + 2) {
            navrange = 1024;
            mappedrelease = sublevels[navleveloverwrite + 2];
          }
          if (navlevel == navleveloverwrite + 3) {
            if (sublevels[1] == 2) {
              GlobalADSR();
            }

            returntonav(navleveloverwrite, 5,sublevels[navleveloverwrite]);
          }
          print_adsr_echo("Release ",mappedrelease);
          
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
          canvasBIG.print(ccsynthselector + 1);
        }

        static void dolistsyntmenu() {
          char synthmenulabels[truesizeofsynthmenulabels][12] = {"Synths", "Mixer", "ADSR", "MP3 Player", "Filter"};
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
          ccsynthselector = sublevels[2]%synths_count;
          String synth_num = ccsynthselector + 1 ;
          navrange = synths_count-1;
          String leprintlabel = titled + synth_num ;
          wavelinesBG();
          sublevels[3] = 0;
          display.fillRect(0+(ccsynthselector%2)*64, 16+(24*(ccsynthselector/2)), 64, 24, SSD1306_INVERSE);
          dm.printlabel((char*)leprintlabel.c_str());
          display.display();
        }

        static void wavesline_selector(){
          _waveliners[navlevel-2]();
        }
        
        void synth_nav_zero() {
            navrange = 4;
            display.clearDisplay();
            reinitsublevels(2);
            dolistsyntmenu();
            retroaction = sublevels[1] ;
            dodisplay();
        }

        static void mp3_player_play(){
          if (!SD.exists((char*)mp3_name.c_str())) {
            get_next_mp3();
          }
          playFile((char*)mp3_name.c_str());
        }

        static void mp3_player_stop(){
          playMp31.stop();
        }

         static void mp3_player_continous(){
          mp3_continue = !mp3_continue ;
        }

        static void mp3_player_pause(){
          mp3_paused = playMp31.pause(!mp3_paused);
        }

        static void mp3_player_next(){
          next_mp3++;
          get_next_mp3();
        }

        static void mp3_player_previous(){
          next_mp3--;
          next_mp3--;
          get_next_mp3();
        }

        static void mp3_player_shuffle(){
          mp3_shuffle = !mp3_shuffle ;
          //TODO
          //each play next_mp3 is random % total ?
        }

        static void mp3_player_actions() {
          if (navlevel == 2) {
            navrange = 8;
          }
          if (navlevel >= 3) {
            switch (sublevels[2]) {
              case 0:
                //continous_play
                mp3_player_play();
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
                //loop_it();
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
            file_index = 0 ;
          }
          //Serial.println((char*)mp3_name.c_str());
          
        }

        static void transport_selector() {
          int startyp = 8;
          int ecart = 14;
          display.fillRect(ecart * (sublevels[navlevel])-3, startyp-2, ecart-1, startyp*1.5, SSD1306_INVERSE);
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
          dodisplay();
          transport_selector();
          display_mp3_title();
          dodisplay();
          //placeholder
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

        static void restore_from_temp() {
          for (int i=0; i<10; i++) {
            sublevels[3] = filter_tmp_values[i];
            (filters_pointers[i])();
            le303filtercontrols();
            *filter_tmp_pointers[i] = filter_tmp_values[i] ;
          }
           temp_buff_armed = 0 ;
        }

        static void set_filter_buff_temp() {

          for (int i=0; i<10; i++) {
            filter_tmp_values[i] = *filter_tmp_pointers[i] ;
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
          dodisplay();
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

        static void restore_wmixer_from_temp() {
          for (int i=0; i<12; i++) {
            sublevels[3] = wmixer_tmp_values[i];
            //(filters_pointers[i])();
            //le303filtercontrols();
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
            *wmixer_tmp_pointers[i] = wmixer_tmp_values[i] ;
          }
           temp_buff_armed = 0 ;
        }

        static void set_wmixer_buff_temp() {
          Serial.println("buffing");
          for (int i=0; i<12; i++) {
            wmixer_tmp_values[i] = *wmixer_tmp_pointers[i] ;
          }
         
        }

        static void showmixerwaves() {
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

          for (int i = 0; i < synths_count; i++) {
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
          dodisplay();
        }

        static void setwavemixlevel() {
        // AudioNoInterrupts();
          for (int j = 0; j < liners_count; j++) {
            Wavesmix[j]->gain(ccsynthselector, mixlevelsL[ccsynthselector]/127.0);
          }
        // AudioInterrupts();
        }

        static void actionwet1mixer(int linstru) {

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

        static void action_dry_mix(int linstru) {

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

        static void actionwmixer(byte vknob) {

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

        static void actionwmixerM(int lebus) {

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

        static void plug_no_waves(){
          mixlevelsL[ccsynthselector] = 0;
          for (int i = 0; i < liners_count; i++) {
            wavelinescords[i + (liners_count * ccsynthselector)]->disconnect();
            stringcords1[i + (liners_count * ccsynthselector)]->disconnect();
            drumcords1[i + (liners_count * ccsynthselector)]->disconnect();
            FMwavecords1[i + (liners_count * ccsynthselector)]->disconnect();
            MDdrumcords1[i + (liners_count * ccsynthselector)]->disconnect();
            MDwavecords1[i + (liners_count * ccsynthselector)]->disconnect();
            MDstringcords1[i + (liners_count * ccsynthselector)]->disconnect();
            modulatecords1[i + (liners_count * ccsynthselector)]->disconnect();
          }
        }

        static void plug_waves(){
          for (int i = 0; i < liners_count; i++) {
            FMwavecords1[i + (liners_count * ccsynthselector)]->disconnect();
            stringcords1[i + (liners_count * ccsynthselector)]->disconnect();
            modulatecords1[i + (liners_count * ccsynthselector)]->disconnect();
            MDdrumcords1[i + (liners_count * ccsynthselector)]->disconnect();
            MDstringcords1[i + (liners_count * ccsynthselector)]->disconnect();
            MDwavecords1[i + (liners_count * ccsynthselector)]->disconnect();
            drumcords1[i + (liners_count * ccsynthselector)]->disconnect();
            wavelinescords[i + (liners_count * ccsynthselector)]->connect();
            if (Waveformstyped[ccsynthselector] == 7) {
              waveforms1[i + (liners_count * ccsynthselector)]->arbitraryWaveform(arbitrary_waveforms[ccsynthselector],1.0);
            }
            waveforms1[i + (liners_count * ccsynthselector)]->begin(lesformes[Waveformstyped[ccsynthselector]]);
          }
        }

        static void plug_moded_waves(){
          for (int i = 0; i < liners_count; i++) {
            wavelinescords[i + (liners_count * ccsynthselector)]->disconnect();
            modulatecords1[i + (liners_count * ccsynthselector)]->disconnect();
            MDdrumcords1[i + (liners_count * ccsynthselector)]->disconnect();
            MDstringcords1[i + (liners_count * ccsynthselector)]->disconnect();
            stringcords1[i + (liners_count * ccsynthselector)]->disconnect();
            drumcords1[i + (liners_count * ccsynthselector)]->disconnect();
            MDwavecords1[i + (liners_count * ccsynthselector)]->disconnect();
            FMwavecords1[i + (liners_count * ccsynthselector)]->connect();
            if (Waveformstyped[ccsynthselector] == 7) {
              //waveforms1[i + (liners_count * ccsynthselector)]->arbitraryWaveform(arbitrary_waveforms[ccsynthselector],1.0);
              FMwaveforms1[i + (liners_count * ccsynthselector)]->arbitraryWaveform(arbitrary_waveforms[ccsynthselector],1.0);
            }
            FMwaveforms1[i + (liners_count * ccsynthselector)]->begin(lesformes[Waveformstyped[ccsynthselector]]);
          }
          call_restart_lfo(ccsynthselector);
        }

        static void plug_ampl_moded_waves(){
          for (int i = 0; i < liners_count; i++) {
            wavelinescords[i + (liners_count * ccsynthselector)]->disconnect();
            MDdrumcords1[i + (liners_count * ccsynthselector)]->disconnect();
            MDstringcords1[i + (liners_count * ccsynthselector)]->disconnect();
            stringcords1[i + (liners_count * ccsynthselector)]->disconnect();
            drumcords1[i + (liners_count * ccsynthselector)]->disconnect();
            FMwavecords1[i + (ccsynthselector * liners_count)]->disconnect();
            MDwavecords1[i + (liners_count * ccsynthselector)]->connect();
            modulatecords1[i + (liners_count * ccsynthselector)]->connect();
            if (Waveformstyped[ccsynthselector] == 7) {
              waveforms1[i + (liners_count * ccsynthselector)]->arbitraryWaveform(arbitrary_waveforms[ccsynthselector],1.0);
            }
            waveforms1[i + (liners_count * ccsynthselector)]->begin(lesformes[Waveformstyped[ccsynthselector]]);
          }
          call_restart_lfo(ccsynthselector);
        }

        static void plug_strings_waves(){
          for (int i = 0; i < liners_count; i++) {
            wavelinescords[i + (ccsynthselector * liners_count)]->disconnect();
            drumcords1[i + (ccsynthselector * liners_count)]->disconnect();
            FMwavecords1[i + (ccsynthselector * liners_count)]->disconnect();
            modulatecords1[i + (liners_count * ccsynthselector)]->disconnect();
            MDwavecords1[i + (liners_count * ccsynthselector)]->disconnect();
            MDdrumcords1[i + (liners_count * ccsynthselector)]->disconnect();
            MDstringcords1[i + (liners_count * ccsynthselector)]->disconnect();
            stringcords1[i + (ccsynthselector * liners_count)]->connect();
          }
        }

        static void plug_ampl_moded_strings(){
          for (int i = 0; i < liners_count; i++) {
            wavelinescords[i + (ccsynthselector * liners_count)]->disconnect();
            drumcords1[i + (ccsynthselector * liners_count)]->disconnect();
            FMwavecords1[i + (ccsynthselector * liners_count)]->disconnect();
            stringcords1[i + (ccsynthselector * liners_count)]->disconnect();
            MDwavecords1[i + (liners_count * ccsynthselector)]->disconnect();
            MDdrumcords1[i + (liners_count * ccsynthselector)]->disconnect();
            MDstringcords1[i + (liners_count * ccsynthselector)]->connect();
            modulatecords1[i + (liners_count * ccsynthselector)]->connect();
          }
        }

        static void plug_drum_waves(){
          for (int i = 0; i < liners_count; i++) {
            wavelinescords[i + (ccsynthselector * liners_count)]->disconnect();
            stringcords1[i + (ccsynthselector * liners_count)]->disconnect();
            FMwavecords1[i + (ccsynthselector * liners_count)]->disconnect();
            modulatecords1[i + (liners_count * ccsynthselector)]->disconnect();
            MDwavecords1[i + (liners_count * ccsynthselector)]->disconnect();
            MDdrumcords1[i + (liners_count * ccsynthselector)]->disconnect();
            MDstringcords1[i + (liners_count * ccsynthselector)]->disconnect();
            drumcords1[i + (ccsynthselector * liners_count)]->connect();
          }
        }

        static void plug_ampl_moded_drums(){
          for (int i = 0; i < liners_count; i++) {
            wavelinescords[i + (ccsynthselector * liners_count)]->disconnect();
            stringcords1[i + (ccsynthselector * liners_count)]->disconnect();
            FMwavecords1[i + (ccsynthselector * liners_count)]->disconnect();
            drumcords1[i + (ccsynthselector * liners_count)]->disconnect();
            MDwavecords1[i + (liners_count * ccsynthselector)]->disconnect();
            MDstringcords1[i + (liners_count * ccsynthselector)]->disconnect();
            //TODO: apply to other types too
            modulatecords1[i + (liners_count * ccsynthselector)]->connect();
            MDdrumcords1[i + (liners_count * ccsynthselector)]->connect();
          }
        }

        static void no_modulation(){
              byte letype = Waveformstyped[ccsynthselector];
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
          byte letype = Waveformstyped[ccsynthselector];
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
          byte letype = Waveformstyped[ccsynthselector];
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
          byte letype = Waveformstyped[ccsynthselector];
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
            call_restart_lfo(ccsynthselector);
        }

        static void setwavetypefromlist() {
          AudioNoInterrupts();
          byte letype = Waveformstyped[ccsynthselector];
          if (letype == 11) {
            // synth line off
            plug_no_waves();
            AudioInterrupts();
            setwavemixlevel();
            return;
          }
          (modulation_pointers[FMmodulated[ccsynthselector]] )();
          AudioInterrupts();
          setwavemixlevel();
        }

        static void setphaselevel() {
          AudioNoInterrupts();
          for (int i = 0; i < liners_count; i++) {
            waveforms1[i + (liners_count * ccsynthselector)]->phase(phaselevelsL[ccsynthselector]);
          }
          AudioInterrupts();
        }

        void setsynthfrequencyi(float tune, int voice, byte velocityz) {
          // AudioNoInterrupts();
          for (int i = 0; i < synths_count; i++) {
            waveforms1[voice + (i * liners_count)]->frequency(tune * wavesfreqs[i - 1]);
            waveforms1[voice + (i * liners_count)]->amplitude(velocityz / 127.0);
            FMwaveforms1[voice + (i * liners_count)]->frequency(tune * wavesfreqs[i - 1]);
            FMwaveforms1[voice + (i * liners_count)]->amplitude(velocityz / 127.0);
            drums1[voice + (i * liners_count)]->length(velocityz * 5);
          }
          // AudioInterrupts();
        }

        static void SetADSR() {
          adsrlevels[0] = MadsrAttackDelay;
          adsrlevels[4] = mappedsustain;
          adsrlevels[5] = mappedrelease;
          adsrlevels[3] = mappeddecay;
          adsrlevels[1] = mappedattack;
          adsrlevels[2] = MadsrHold;
        }

        static constexpr void (*_nav_synth[])() = {&wavesline_selector,&showmixerwaves, &displayadsrgraph, &mp3_player_panel ,&le303filterVpanel};
        static constexpr void (*_waveliners[6])() = {&synths_switcher,&wavelining, &wavelining, &wavelining,&wavelining, &wavelining};
        static constexpr void (*modulation_pointers[4])() = {&no_modulation,&freq_modulation,&phase_modulation,&amplitude_modulation};

        static constexpr void (*filters_pointers[10])() = {&filter_knob_freq, &filter_knob_res, &filter_knob_low, &filter_knob_band, &filter_knob_high,
                                                &filter_knob_wet, &filter_knob_pulse1, &filter_knob_pulse2, &filter_knob_preamp, &filter_knob_glide};

        static constexpr void (*_synth_params[synth_params_count])() = {&displaywaveformicon,&wavelineModulatedbool,&displayLFOpanel,
                                                      &displayfreqbars,&displayoffsetwav,&displayphasebars,&go_previous,&go_next};
         
        static constexpr sn _route_nav[7] = {
            &SynthMenuRouter::route_navlevel_1,
            &SynthMenuRouter::route_navlevel_2,
            &SynthMenuRouter::route_navlevel_2,
            &SynthMenuRouter::route_navlevel_2,
            &SynthMenuRouter::route_navlevel_2,
            &SynthMenuRouter::route_navlevel_2,
            &SynthMenuRouter::route_navlevel_2
        };
};

SynthMenuRouter _sn = SynthMenuRouter();

