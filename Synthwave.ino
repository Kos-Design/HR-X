
void setlepulse1() {
  le303pulsewidth = (le303pulsewidthmultiplier/32.0)*2 * millitickinterval ;
  if (le303pulsewidth < 50 ) {
    le303pulsewidth = 50 ;
  }
}

void setlepulse2() {
  le303pulsewidth2 = (le303pulsewidthmultiplier2/32.0)*2 * millitickinterval + 50 ;
   if (le303pulsewidth2 < 50 ) {
    le303pulsewidth2 = 50 ;
  }
}

void le303filterVpanelAction() {
  if (navlevel == 3 ) {
   // AudioNoInterrupts();
  int slct = sublevels[2];
//fq
  if (slct == 0) {
    navrange = 128 ;
    le303ffilterzVknobs[0] = sublevels[3];
   le303filterzfreq = round((le303ffilterzVknobs[0]/128.0)*10000)  ;
   le303filterzrange = le303filterzfreq ;
  }
  //res
  if (slct == 1) {
    navrange = 128 ;
    le303ffilterzVknobs[1] = sublevels[3] ;
   le303filterzreso = ((le303ffilterzVknobs[1])/128.0)*5 ;
   // if (le303filterzreso < 0.7) {
   //  le303filterzreso = 0.7;
  //  }
  }
  //octaves
  if (slct == 2) {
    navrange = 128 ;
   le303ffilterzVknobs[2] = sublevels[3] ;
  le303filterzoctv = ((le303ffilterzVknobs[2])/128.0)*7 ;
  }
  //lowpass
  if (slct == 3) {
    navrange = 128 ;
    mixle303ffilterzVknobs[0] = sublevels[3] ;
  le303filterzgainz[0] = (mixle303ffilterzVknobs[0])/128.0 ;
    
  }
  //bandpass
 if (slct == 4) {
  navrange = 128 ;
      mixle303ffilterzVknobs[1] = sublevels[3] ;
     le303filterzgainz[1] = (mixle303ffilterzVknobs[1])/128.0 ;
  }
  //high pass
 if (slct == 5) {
  navrange = 128 ;
      mixle303ffilterzVknobs[2] = sublevels[3] ;
    le303filterzgainz[2] = (mixle303ffilterzVknobs[2])/128.0 ;
  }
  if (slct == 6) {
  navrange = 100 ;
     le303filterzwet = sublevels[3] ;
    //le303filterzwet = (mixle303ffilterzVknobs[2])/128.0 ;
     le303filterzWet();
  }
    if (slct == 7) {
  navrange = 32 ;
     le303pulsewidthmultiplier = sublevels[3] ;
    setlepulse1();
    //le303filterzwet = (mixle303ffilterzVknobs[2])/128.0 ;
     
  }
     if (slct == 8) {
  navrange = 32 ;
     le303pulsewidthmultiplier2 = sublevels[3] ;
    setlepulse2();
    //le303filterzwet = (mixle303ffilterzVknobs[2])/128.0 ;
     
  }
     if (slct == 9) {
    navrange = 128 ;
    preampleswaves = sublevels[3] ;
    Wavespreamp303controls();
    
     
  }
     if (slct == 10) {
   navrange = 128 ;
    le303envlfofadintime =  sublevels[3] ; 
  
  }
  if (slct == 11) {
   navrange = 128 ;
    glidemode = sublevels[3] ; 
   // Wavespreamp303controls();
    // returntonav(2);
     
  }
  if (slct == 12) {
   navrange = 128 ;
    le303envlfofadouttime =  sublevels[3] ;
     
  }
  
     le303filtercontrols();
    }
  if (navlevel > 3) {
     
    returntonav(2);
  }
}

void Wavespreamp303controls() {
  for (int i = 0 ; i < 8 ; i++) {
    Wavespreamp303[i]->gain(preampleswaves/128.0);
  }
}

void le303filterzWet() {
   for (int i = 0 ; i < 8 ; i++) {
    les303wet[i]->gain(0, le303filterzwet/100.0);
    les303wet[i]->gain(1, (1-(le303filterzwet/100.0)));
   }
  
}

void le303filtercontrols() {
  for (int i = 0 ; i < 8 ; i++) {
     setle303filterpass(i,1);
     
   //les303filterz[i]->frequency(le303filterzfreq);
   //les303filterz[i]->resonance(le303filterzreso);
     les303filterz[i]->octaveControl(le303filterzoctv);
  }
}

void le303filterVpanel() {
  
  le303filterVpanelAction();
  int knobradius = 9 ;
  int centercirclex = 5 + knobradius ;
  int centercircley = 35 + knobradius ;
  int ftVcursorpointx ;
  int ftVcursorpointy ; 
   
    float coeffangle ;
    int startley;
    int totbartall = 37;
    int topwbarstart = 16 ;
    int wbarwidth = 9 ;
     int wbarwidth2 = 8 ;
    int barsize ;
    int startlex2= 67;
    display.clearDisplay();
    canvasBIG.fillScreen(SSD1306_BLACK);
    canvastitle.fillScreen(SSD1306_BLACK);
    canvastitle.setCursor(0,0);
    canvastitle.setTextSize(1);
    canvastitle.print("303 ");
        canvastitle.setCursor(22,0);
  
    canvastitle.print("In:");
    canvastitle.print((preampleswaves/128.0)*100.0,1);
    
    coeffangle = (6.2831-(le303ffilterzVknobs[0]/128.0)*6.2831)+3.1416 ;
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
    ftVcursorpointx = round(centercirclex + (knobradius*( cos(coeffangle) )));
    ftVcursorpointy = round(centercircley - (knobradius*( sin(coeffangle) )));
    canvasBIG.drawLine(centercirclex,centercircley,ftVcursorpointx,ftVcursorpointy,SSD1306_WHITE);
    canvasBIG.setCursor(centercirclex-knobradius+4, centercircley+ knobradius + 4);
    canvasBIG.setTextSize(1);
    canvasBIG.print("FQ");
    if (le303filterzfreq < 1000){
    canvasBIG.setCursor(centercirclex-knobradius+1, 25);
     canvasBIG.print(le303filterzfreq,0);
    }
    if (( round(le303filterzfreq ) < 9900) && (le303filterzfreq >= 1000 )){
    canvasBIG.setCursor(centercirclex-knobradius-1, 25);
     canvasBIG.print(round(le303filterzfreq )/1000.0,1);
     canvasBIG.print("k");
    }
    if (le303filterzfreq  >= 9900){
    canvasBIG.setCursor(centercirclex-knobradius-5, 25);
     canvasBIG.print(le303filterzfreq /1000.0,1);
     canvasBIG.print("k");
    }

   
     //resonnance
    coeffangle = (6.2831-(le303ffilterzVknobs[1]/128.0)*6.2831)+3.1416 ;
    centercirclex = knobradius+30 ;
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
    ftVcursorpointx = round(centercirclex + (knobradius*( cos(coeffangle) )));
    ftVcursorpointy = round(centercircley - (knobradius*( sin(coeffangle) )));
    canvasBIG.drawLine(centercirclex,centercircley,ftVcursorpointx,ftVcursorpointy,SSD1306_WHITE);
    canvasBIG.setCursor(centercirclex-knobradius+1, centercircley+ knobradius + 4);
    canvasBIG.setTextSize(1);
    canvasBIG.print("Res");
    canvasBIG.setCursor(centercirclex-knobradius+2, 25);
    canvasBIG.print(le303filterzreso ,1);
   
    //octave
    coeffangle = (6.2831-(le303ffilterzVknobs[2]/128.0)*6.2831)+3.1416 ;
    centercirclex = knobradius+55 ;
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
    ftVcursorpointx = round(centercirclex + (knobradius*( cos(coeffangle) )));
    ftVcursorpointy = round(centercircley - (knobradius*( sin(coeffangle) )));
    canvasBIG.drawLine(centercirclex,centercircley,ftVcursorpointx,ftVcursorpointy,SSD1306_WHITE);
    canvasBIG.setCursor(centercirclex-knobradius+1, centercircley+ knobradius + 4);
    canvasBIG.setTextSize(1);
    canvasBIG.print("Oct");
    canvasBIG.setCursor(centercirclex-knobradius+1, 25);
    canvasBIG.print(le303filterzoctv ,1);


     barsize = round((le303filterzgainz[0]*(totbartall-4))) ;
      canvasBIG.drawRoundRect(81  ,topwbarstart, wbarwidth, totbartall ,2, SSD1306_WHITE ) ;
      canvasBIG.fillRect(81+2 , (totbartall + topwbarstart - barsize -2), wbarwidth-4, barsize , SSD1306_WHITE ) ;
      canvasBIG.setCursor(81,totbartall + topwbarstart + 4);
    canvasBIG.print("LP");
   //canvasBIG.setCursor(80,18);
   // canvasBIG.print(bqgain[0][bqstage[0]]);
      barsize = round((le303filterzgainz[1]*(totbartall-4))) ;
     canvasBIG.drawRoundRect(98  ,topwbarstart, wbarwidth, totbartall ,2, SSD1306_WHITE ) ;
      canvasBIG.fillRect(98+2 , (totbartall + topwbarstart - barsize -2), wbarwidth-4, barsize , SSD1306_WHITE ) ;
      canvasBIG.setCursor(97,totbartall + topwbarstart + 4);
    canvasBIG.print("BP");
   //canvasBIG.setCursor(93,18);
   // canvasBIG.print(bqgain[0][bqstage[0]]);
    barsize = round((le303filterzgainz[2]*(totbartall-4))) ;
     canvasBIG.drawRoundRect(115  ,topwbarstart, wbarwidth, totbartall ,2, SSD1306_WHITE ) ;
      canvasBIG.fillRect(115+2 , (totbartall + topwbarstart - barsize -2), wbarwidth-4, barsize , SSD1306_WHITE ) ;
      canvasBIG.setCursor(114,totbartall + topwbarstart + 4);
    canvasBIG.print("HP");
  // canvasBIG.setCursor(114,18);
   // canvasBIG.print(bqgain[lefilter][bqstage[lefilter]]);
     //wetbar
      barsize = round(((le303filterzwet/100.0)*(totbartall-4))) ;
     canvasBIG.drawRoundRect(topwbarstart+startlex2+4, 0, totbartall, wbarwidth2 ,2, SSD1306_WHITE ) ;
      canvasBIG.fillRect((topwbarstart+startlex2+6), 2 , barsize , wbarwidth2-4,  SSD1306_WHITE ) ;
      canvasBIG.setCursor(startlex2,0);
    canvasBIG.print("Wet");

    barsize = round(((le303pulsewidth/millitickinterval)*(totbartall-4))) ;
     
      canvasBIG.setCursor(0,16);
    canvasBIG.print("Xfq ");
     canvasBIG.print(le303pulsewidthmultiplier);

 canvasBIG.setCursor(40,16);
    canvasBIG.print("Xres ");
     canvasBIG.print(le303pulsewidthmultiplier2);
     
   canvastitle.setCursor(0,8);
    canvastitle.print("Fi:");
    canvastitle.print(le303envlfofadintime/128.0);
     
      canvastitle.setCursor(48,8);
    canvastitle.print("Fo:");
    canvastitle.print(le303envlfofadouttime/128.0);
    
    canvastitle.setCursor(94,8);
    canvastitle.print("S:");
    if (glidemode>0 && glidemode<13 ) {
    canvastitle.print(".0");
    canvastitle.print(100*(glidemode/128.0),0);
    } 
    if (glidemode>12 && glidemode<128 ) {
    canvastitle.print(".");
    canvastitle.print(100*(glidemode/128.0),0);
    } 
    if (glidemode==128 ) {
      canvastitle.print("1.0");
    }
    if (glidemode==0 ) {
      canvastitle.print("Off");
    }

    
   le303filterVpanelSelector();
    dodisplay();
}

void le303filterVpanelSelector() {
  
 int knobradius = 9 ;
  int centercirclex = 5 + knobradius ;
  int centercircley = 35 + knobradius ;
  int startlex2= 67;
   
    float coeffangle ;
    int startley;
    int totbartall = 37;
    int topwbarstart = 16 ;
    int wbarwidth = 9 ;
    int wbarwidth2 = 8 ;
    if (navlevel == 2) {
     navrange = 12 ;
    }
    int slct = sublevels[2];
//fq
  if (slct == 0) {
    sublevels[3] = le303ffilterzVknobs[0] ;
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius-2, SSD1306_WHITE);
   
  }
  //res
  if (slct == 1) {
    sublevels[3] = le303ffilterzVknobs[1] ;
    canvasBIG.drawCircle(centercirclex+25, centercircley, knobradius-2, SSD1306_WHITE);
  }
  //oct
  if (slct == 2) {
    sublevels[3] = le303ffilterzVknobs[2];
    canvasBIG.drawCircle(centercirclex+50, centercircley, knobradius-2, SSD1306_WHITE);
  }
  //lp
  if (slct == 3) {
    sublevels[3] = mixle303ffilterzVknobs[0];
    canvasBIG.drawRect(83  ,topwbarstart, wbarwidth-4, totbartall , SSD1306_WHITE ) ;
    
  }
  //bp
 if (slct == 4) {
    sublevels[3] = mixle303ffilterzVknobs[1];
    canvasBIG.drawRect(100  ,topwbarstart, wbarwidth-4, totbartall , SSD1306_WHITE ) ;
  }
  //hp
   if (slct == 5) {
    sublevels[3] = mixle303ffilterzVknobs[2];
    canvasBIG.drawRect(117  ,topwbarstart, wbarwidth-4, totbartall , SSD1306_WHITE ) ;
  }
  //wet
  if (slct == 6) {
    sublevels[3] = le303filterzwet;
    canvasBIG.drawRect(topwbarstart+startlex2+4, 0+2  , totbartall , wbarwidth2-4, SSD1306_WHITE ) ;
  }
    if (slct == 7) {
    sublevels[3] = le303pulsewidthmultiplier;
    canvasBIG.setCursor(21, 16); 
    canvasBIG.print((char)9) ;
  }
    if (slct == 8) {
    sublevels[3] = le303pulsewidthmultiplier2;
    canvasBIG.setCursor(62, 18); 
    canvasBIG.print((char)9) ;
  }
   if (slct == 9) {
    sublevels[3] = preampleswaves ;
    canvasBIG.setCursor(34, 0); 
    canvasBIG.print((char)9) ;
   }
    if (slct == 10) {
    sublevels[3] = le303envlfofadintime ;
    canvasBIG.setCursor(12, 8); 
    canvasBIG.print((char)9) ;
   }
   if (slct == 11) {
    sublevels[3] = glidemode ;
    canvasBIG.setCursor(100, 8); 
    canvasBIG.print((char)9) ;
   }
    if (slct == 12) {
   sublevels[3] = le303envlfofadouttime ;
    canvasBIG.setCursor(60, 8); 
    canvasBIG.print((char)9) ;
   }
}

void initialize303group() {

  for ( int i = 0 ; i < 8 ; i++) {
    setle303filterpass(i,1.0);
    les303wet[i]->gain(1, 1);
    les303wet[i]->gain(0, 0);
    les303filterz[i]->frequency(220);
    les303filterz[i]->resonance(5);
    les303filterz[i]->octaveControl(7);
  }
}

void setle303filterpass (int linei, float ladiff1 ) {
    les303passes[linei]->gain(0,(le303filterzgainz[0]*((0.01+((128.0-preampleswaves)/128.0))*1+((128.0-preampleswaves)/128.0)) * ladiff1));
    les303passes[linei]->gain(1,(le303filterzgainz[1]*((0.01+((128.0-preampleswaves)/128.0))*1+((128.0-preampleswaves)/128.0)) * ladiff1));
    les303passes[linei]->gain(2,(le303filterzgainz[2]*((0.01+((128.0-preampleswaves)/128.0))*1+((128.0-preampleswaves)/128.0)) * ladiff1));
}

void showmixerwaves() {
  char masterfulllabels[12][12] = {"Master", "Synth", "Sampler","FX1","FX2","FX3","Wet Synth","Wet Sampler","Waveline 1","Waveline 2","Waveline 3","Waveline 4",};
  navrange = 11;
  byte slct = sublevels[2] ;
  if ( slct < 3 ) {
  actionwmixerM(sublevels[2]);
    }
     if (slct>2 && slct<6 ) {
  actionwet1mixer(sublevels[2]-3);
    }
     if (slct>5 && slct<8 ) {
  actionwet2mixer(sublevels[2]-6);
    }
     if (slct>7 && slct<12 ) {
  actionwmixer(sublevels[2]-8);
    }
    

  display.clearDisplay();
   canvastitle.fillScreen(SSD1306_BLACK);
    canvasBIG.fillScreen(SSD1306_BLACK);
   // canvastitle.setCursor(70,0);
    canvasBIG.setTextSize(1);
   canvasBIG.setCursor(0,0);
      canvasBIG.print((char*)masterfulllabels[sublevels[2]]);
    
    byte centercirclex ;
    byte centercircley ;
    byte xcentershifter ;
    byte knobradius = 7 ;
    byte trianglepointx;
    byte trianglepointy ; 
    byte yshifter = 46 ;
     float coeffangle  ;
    xcentershifter = (knobradius * 2 ) + 6 ;


    for (int i = 0 ; i < 3 ; i++ ) {
 
    coeffangle = (6.2831-(mixlevelsM[i]/128.0)*6.2831)+3.1416 ;
    centercirclex = knobradius+(xcentershifter*i);
    centercircley = 16+knobradius ;
    canvastitle.setCursor(centercirclex-5,8);
    canvastitle.setTextSize(1);
 
    canvastitle.print((char)masterfulllabels[i][0]);
    canvastitle.print((char)masterfulllabels[i][2]);
 
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
   
   
    trianglepointx = round(centercirclex + (knobradius*( cos(coeffangle) )));
    trianglepointy = round(centercircley - (knobradius*( sin(coeffangle) )));

    display.drawLine(centercirclex,centercircley,trianglepointx,trianglepointy,SSD1306_WHITE);

    }
    
    if (slct<3) {
    centercirclex = knobradius+(xcentershifter*slct);
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius-2, SSD1306_WHITE);
    canvastitle.setCursor(95,0);
    canvastitle.print((mixlevelsM[slct]/128.0)*100.0,1);
    }
  
    for (int i = 0 ; i < 3 ; i++ ) {
        coeffangle = (6.2831-(WetMixMasters[i+1])*6.2831)+3.1416 ;
        centercirclex = knobradius+(xcentershifter*i)+5+(xcentershifter*3);
        centercircley = 16+knobradius ;
        canvastitle.setCursor(centercirclex-8,8);
        canvastitle.setTextSize(1);
        canvastitle.print((char*)masterfulllabels[i+3]);
        canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
        trianglepointx = round(centercirclex + (knobradius*( cos(coeffangle) )));
        trianglepointy = round(centercircley - (knobradius*( sin(coeffangle) )));

    display.drawLine(centercirclex,centercircley,trianglepointx,trianglepointy,SSD1306_WHITE);

    }
     
   if (slct>2 && slct<6 ) {
      centercirclex = knobradius+(xcentershifter*(slct-3))+5+(xcentershifter*3);
      canvasBIG.drawCircle(centercirclex, centercircley, knobradius-2, SSD1306_WHITE);
      canvastitle.setCursor(95,0);
      canvastitle.print(WetMixMasters[slct-3+1]*100.0,1) ;
    }
   
   for (int i = 0 ; i < 2 ; i++ ) {
 
    coeffangle = (6.2831-(wetins[i]/128.0)*6.2831)+3.1416 ;   
    centercirclex = knobradius+(xcentershifter*i);
    centercircley =yshifter+knobradius ;
    canvasBIG.setCursor(centercirclex-7,centercircley-(2+knobradius*2));
    canvasBIG.print("Ws");
    canvasBIG.print(i);
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
    trianglepointx = round(centercirclex + (knobradius*( cos(coeffangle) )));
    trianglepointy = round(centercircley - (knobradius*( sin(coeffangle) )));

    display.drawLine(centercirclex,centercircley,trianglepointx,trianglepointy,SSD1306_WHITE);

    }
 
    if (slct>5 && slct<8 ) {
    
      centercirclex = knobradius+(xcentershifter*(slct-6));
      canvasBIG.drawCircle(centercirclex, centercircley, knobradius-2, SSD1306_WHITE);
       canvastitle.setCursor(95,0);
      canvastitle.print((wetins[slct-6]/128.0)*100.0,1);
    }
    for (int i = 0 ; i < 4 ; i++ ) {
 
    coeffangle = (6.2831-(mixlevelsL[i])*6.2831)+3.1416 ;
 
    centercirclex = knobradius+(xcentershifter*i)+5+(xcentershifter*2);
    centercircley = yshifter+knobradius ;
    canvasBIG.setCursor(centercirclex-5,centercircley-(2+knobradius*2));
    canvasBIG.print("W");
     canvasBIG.print(i);
    canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
   
   
    trianglepointx = round(centercirclex + (knobradius*( cos(coeffangle) )));
    trianglepointy = round(centercircley - (knobradius*( sin(coeffangle) )));

    display.drawLine(centercirclex,centercircley,trianglepointx,trianglepointy,SSD1306_WHITE);

    }
    
     if (slct>7 && slct<12 ) {
    
      centercirclex = knobradius+(xcentershifter*(slct-8))+5+(xcentershifter*2);
      canvasBIG.drawCircle(centercirclex, centercircley, knobradius-2, SSD1306_WHITE);
       canvastitle.setCursor(95,0);
      canvastitle.print((mixlevelsL[slct-8])*100.0,1);
    }
    dodisplay();
    
}

void setwavemixlevel(int lesynth) {
  AudioNoInterrupts();
  for (int j = 0; j<8 ; j++ ) {
  Wavesmix[j]->gain(lesynth, mixlevelsL[lesynth]);
  }
  AudioInterrupts();
}

void actionwet1mixer(int linstru) {

  if (navlevel == 2 ) {
    sublevels[3]= round(WetMixMasters[linstru+1]*128.0) ;
  }
   if (navlevel == 3 ) {
      navrange = 128 ;
     //wetmain[lafxline] = sublevels[3];
     WetMixMasters[linstru+1] = sublevels[3]/128.0;
     wetmixmastercontrols();
  }
   if (navlevel == 4 ) {
     returntonav(2,3);
  }
//
}

void actionwet2mixer(int linstru) {

  if (navlevel == 2 ) {
    sublevels[3]= wetins[linstru];
  }
   if (navlevel == 3 ) {
      navrange = 128 ;
     wetins[linstru] = sublevels[3];
    setwet2smixlevel(linstru);
  }
   if (navlevel == 4 ) {
     returntonav(2,3);
  }
//
}

void wetmixmastercontrols() {
  
  float sum = WetMixMasters[3]+WetMixMasters[2]+WetMixMasters[1];
  
    // Adjust the values proportionally if the sum is not equal to 1
    if ((sum != 0) && (sum > 1)) {
    WetMixMasters[1] /= sum;
    WetMixMasters[2] /= sum;
    WetMixMasters[3] /= sum;
  }
   WetMixMasters[0] = 1.0-(WetMixMasters[3]+WetMixMasters[2]+WetMixMasters[1]);
    
  for (byte i = 0 ; i < 4 ; i++ ) {
     WetMixMasterL.gain(i,WetMixMasters[i]);
     WetMixMasterR.gain(i,WetMixMasters[i]);
    }
}

void setwet2smixlevel(int lebus) {
  AudioNoInterrupts();
     switch ( lebus ) {
       case 0 :
       //set synth on fx main bus
        
        MasterL1.gain(0,wetins[0]/128.0) ;
         MasterR1.gain(0,wetins[0]/128.0) ;
         FXBusL.gain(2,1-(wetins[0]/128.0)) ;
         FXBusR.gain(2,1-(wetins[0]/128.0)) ;
         break;
            case 1 :
      //set sampler on fx main bus
         MasterL1.gain(3,wetins[1]/128.0) ;
         MasterR1.gain(3,wetins[1]/128.0) ;
         FXBusL.gain(2,1-(wetins[1]/128.0)) ;
         FXBusR.gain(2,1-(wetins[1]/128.0)) ;
         break;
            
        default:
        break;    
     } 
  AudioInterrupts();
}

void actionwmixer(int lesynth) {

  if (navlevel == 2 ) {
    sublevels[3]= round(mixlevelsL[lesynth]*128.0);
  }
   if (navlevel == 3 ) {
      navrange = 128 ;
     mixlevelsL[lesynth] = sublevels[3]/128.0;
     setwavemixlevel(lesynth);
  }
   if (navlevel == 4 ) {
    returntonav(2,3);
  }
//
}

void actionwmixerM(int lebus) {

  if (navlevel == 2 ) {
    sublevels[3]= round(mixlevelsM[lebus]);
  }
   if (navlevel == 3 ) {
      navrange = 128 ;
     mixlevelsM[lebus] = sublevels[3];
     
     
     setmastersmixlevel(lebus);
  }
   if (navlevel == 4 ) {
    returntonav(2,3);
  }
//
}

void setmastersmixlevel(int lebus) {
AudioNoInterrupts();
     switch ( lebus ) {
       case 0 :
       //set mastermixlevel
        audioShield.volume(mixlevelsM[0]/128.0);
         break;
            case 1 :
       //set synth Main
       MasterL.gain(1,mixlevelsM[1]/128.0) ;
       MasterR.gain(1,mixlevelsM[1]/128.0) ;
         break;
            case 2 :
       //set sampler main
        flashMastermix.gain(0,mixlevelsM[2]/128.0) ;
       flashMastermix.gain(0,mixlevelsM[2]/128.0) ;
         break;
        default:
        break;    
     } 
  AudioInterrupts();
}

void setwavetypefromlist(int lesinthy, int letype) {
  Serial.println("setting wave type");
  AudioNoInterrupts();
    Waveformstyped[lesinthy] = letype;
   
  if (FMmodulated[lesinthy] == 0 ) {
  
   if (letype < 9) {
     for (int i = 0 ; i< nombreofliners ; i++ ) {
   
        FMwavecords1[i+(8*lesinthy)]->disconnect();
        stringcords1[i+(8*lesinthy)]->disconnect();
        modulatecords1[i+(8*lesinthy)]->disconnect();
        MDdrumcords1[i+(8*lesinthy)]->disconnect();
        MDstringcords1[i+(8*lesinthy)]->disconnect();
        drumcords1[i+(8*lesinthy)]->disconnect();
        wavelinescords[i+(8*lesinthy)]->connect();
        waveforms1[i+(8*lesinthy)]->begin(lesformes[letype]);
        
      if (letype == 7) {
        waveforms1[i+(8*lesinthy)]->arbitraryWaveform(myCustomWaveform, 1.0);
        }
    }
    
  } 
    else if (letype == 9) {
     for (int i = 0 ; i< nombreofliners ; i++ ) {
        wavelinescords[i+(lesinthy*8)]->disconnect();
         stringcords1[i+(lesinthy*8)]->disconnect();
          FMwavecords1[i+(lesinthy*8)]->disconnect();
           modulatecords1[i+(8*lesinthy)]->disconnect();
        MDdrumcords1[i+(8*lesinthy)]->disconnect();
        MDstringcords1[i+(8*lesinthy)]->disconnect();
          drumcords1[i+(lesinthy*8)]->connect();
          }
  }
    else if (letype == 10) {
  
     for (int i = 0 ; i< nombreofliners ; i++ ) {
        wavelinescords[i+(lesinthy*8)]->disconnect();
            drumcords1[i+(lesinthy*8)]->disconnect();
          FMwavecords1[i+(lesinthy*8)]->disconnect();
        modulatecords1[i+(8*lesinthy)]->disconnect();
          MDdrumcords1[i+(8*lesinthy)]->disconnect();
        MDstringcords1[i+(8*lesinthy)]->disconnect();
          stringcords1[i+(lesinthy*8)]->connect();
          
         }
    }
  }  
  
  else {
    
    //modulated
    if (FMmodulated[lesinthy] == 1 ) {
      setfmtofreq(lesinthy);
      }
    if (FMmodulated[lesinthy] == 2 ) {
      setfmtophase(lesinthy);
    }
     
  
    if (letype < 9) {
          
        for (int i = 0 ; i< nombreofliners ; i++ ) {
        wavelinescords[i+(8*lesinthy)]->disconnect();
        modulatecords1[i+(8*lesinthy)]->disconnect();
        MDdrumcords1[i+(8*lesinthy)]->disconnect();
        MDstringcords1[i+(8*lesinthy)]->disconnect();
        stringcords1[i+(8*lesinthy)]->disconnect();
        drumcords1[i+(8*lesinthy)]->disconnect();
        
        FMwavecords1[i+(8*lesinthy)]->connect();
        FMwaveforms1[i+(8*lesinthy)]->begin(lesformes[letype]); 
        //LFO begin
        
      }
    } 
    else if (letype == 9) {
    //modulated drum
     for (int i = 0 ; i< nombreofliners ; i++ ) {
        wavelinescords[i+(lesinthy*8)]->disconnect();
         stringcords1[i+(lesinthy*8)]->disconnect();
          FMwavecords1[i+(lesinthy*8)]->disconnect();
          drumcords1[i+(lesinthy*8)]->disconnect();
          MDstringcords1[i+(8*lesinthy)]->disconnect();
          
          modulatecords1[i+(8*lesinthy)]->connect();
          MDdrumcords1[i+(8*lesinthy)]->connect();
        
          }
  } 
    else if (letype == 10) {
    //modulated string
     for (int i = 0 ; i< nombreofliners ; i++ ) {
           wavelinescords[i+(lesinthy*8)]->disconnect();
               drumcords1[i+(lesinthy*8)]->disconnect();
             FMwavecords1[i+(lesinthy*8)]->disconnect();
             stringcords1[i+(lesinthy*8)]->disconnect();
             MDdrumcords1[i+(8*lesinthy)]->disconnect();
           MDstringcords1[i+(8*lesinthy)]->connect();
           modulatecords1[i+(8*lesinthy)]->connect();
         
          }
   }
  }
          
  // synth line off
  if (letype == 11) {
    mixlevelsL[lesinthy] = 0;
     for (int i = 0 ; i< nombreofliners ; i++ ) {
       wavelinescords[i+(8*lesinthy)]->disconnect();
         stringcords1[i+(8*lesinthy)]->disconnect();
           drumcords1[i+(8*lesinthy)]->disconnect();
         FMwavecords1[i+(8*lesinthy)]->disconnect();
         MDdrumcords1[i+(8*lesinthy)]->disconnect();
       MDstringcords1[i+(8*lesinthy)]->disconnect();
       modulatecords1[i+(8*lesinthy)]->disconnect();

        }
    }
  AudioInterrupts();  
  setwavemixlevel(lesinthy);
 // printmixlevelsandtype();
}

void setpanlevel(int lesynth, int laval) {
      panLs[lesynth] = map( laval/10.0 ,0,2,0,1);
      // panLs[lesynth] = map( 2-laval/10.0 ,0,2,0,1);
       setwavemixlevel(lesynth);
      //waves : MasterL (1) & R + FXBusL & R (2)
  
}

void setphaselevel(int lesynth) {
  AudioNoInterrupts();
 
    for (int i = 0 ; i< nombreofliners ; i++ ) {
     waveforms1[i+(8*lesynth)]->phase(phaselevelsL[lesynth]);
    }
  
  AudioInterrupts();
}

void setphaser(int lesynth,float laphaze) {
  AudioNoInterrupts();
    phaselevelsL[lesynth]=round(laphaze*360.0);
   
  for (int i = 0 ; i< nombreofliners ; i++ ) {
     waveforms1[i+(8*lesynth)]->phase(phaselevelsL[lesynth]);
    }
  
  AudioInterrupts();
}

void setleLFOfrequency(float tune, int lelfor) {
  LFOwaveforms1[lelfor]->frequency(tune);
 }
   
void setsynthfrequencyi(float tune, int voice, byte velocityz) {
     //AudioNoInterrupts();
    
    for (int i=0 ; i < 4; i++ ) {
     
      waveforms1[voice+(i*8)]->frequency(tune*wavesfreqs[i-1]);
      waveforms1[voice+(i*8)]->amplitude(velocityz/128.0);
        FMwaveforms1[i+voice*4]->frequency(tune*wavesfreqs[i-1]);
        FMwaveforms1[i+voice*4]->amplitude(velocityz/128.0);
      
       
      drums1[i+voice*8]->length(velocityz*5);
      drums1[i+4+voice*8]->length(velocityz*5);
    }

   //AudioInterrupts();
}

void SetADSR() {

           adsrlevels[0]= MadsrAttackDelay ;
           adsrlevels[4]= mappedsustain;
           adsrlevels[5]= mappedrelease ;
           adsrlevels[3]= mappeddecay ;
          adsrlevels[1] =  mappedattack ;
         adsrlevels[2] =   MadsrHold ;
        
  }

void ApplyADSR() {
             
              for ( int i = 0 ; i < 8 ; i++ ) {
              enveloppesL[i]->delay(adsrlevels[0]);
              enveloppesL[i]->attack(adsrlevels[1]);
              enveloppesL[i]->hold(adsrlevels[2]);
              enveloppesL[i]->decay(adsrlevels[3]);
              enveloppesL[i]->sustain(adsrlevels[4]/100.0);
              enveloppesL[i]->release(adsrlevels[5]);
              
 
              }
         
         mappedattack = adsrlevels[1];
         mappeddecay = adsrlevels[3] ;
         mappedrelease = adsrlevels[5];
         mappedsustain = adsrlevels[4]; 
         MadsrAttackDelay = adsrlevels[0];
         MadsrHold = adsrlevels[2] ;   
 }
 
int getwavetyped(int lawavetype) {
  switch(lawavetype ) {
    case 0 :
    return WAVEFORM_SINE;
    break;
    case 1 :
    return WAVEFORM_SAWTOOTH;
    break;
    case 2 :
    return WAVEFORM_SAWTOOTH_REVERSE;
    break;
    case 3 :
    return WAVEFORM_TRIANGLE;
    break;
    case 4 :
    return WAVEFORM_TRIANGLE_VARIABLE;
    break;
    case 5 :
    return WAVEFORM_SQUARE;
    break;
    case 6 :
    return WAVEFORM_PULSE;
    break;
    case 7 :
    return WAVEFORM_ARBITRARY;
    break;   
    case 8 :
    return WAVEFORM_SAMPLE_HOLD;
    break;   
    case 9 :
    return WAVEFORM_SINE;
    break;
      
    default:
    return WAVEFORM_SINE;
    break;
}
//Waveformstyped
//return Wavetype
}
