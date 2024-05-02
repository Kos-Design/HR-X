

void displayadsrbars(int score) {
  if (navlevel == 3) {
  int sizeadsr = map(score,0,20,0,35);
   wavelinemenuBG(sublevels[2]);
  dolistwavelineparams();
    dodisplay();
  display.drawRect(45, 16, 7, 35, SSD1306_WHITE);
  display.drawRect(57, 16, 7, 35, SSD1306_WHITE);
  display.fillRect(45, 64-sizeadsr-13, 7, sizeadsr, SSD1306_WHITE);
  display.fillRect(57, 64-sizeadsr-13, 7, sizeadsr, SSD1306_WHITE);
   display.setTextSize(1);
    display.setCursor(80,0);
  display.print(adsrlevels[0]);
   display.print(" ");
    display.print(adsrlevels[1]);
     display.print(" ");
    display.print(adsrlevels[2]);
  display.display();
  }
   if (navlevel >= 4 ) {
        //Serial.println("displaying adsr");
      displayadsrgraph();
       // Serial.println("nav = 4 adsr");

  }
}
void displaypanbars(int score) {
   if (navlevel >= 4 ) {
     if (navlevel == 4 ) {
      navrange = 20;
        //        int lepan = round(map(sublevels[4],0,1,0,19));
         // setpanlevel(0,lepan);
      setpanlevel(sublevels[2],sublevels[4]);
       // Serial.println(panLs[sublevels[2]]);
       //   Serial.println(panLs[sublevels[2]]);

            }
  if (navlevel >= 5 ) {
    //Serial.println("nav = 5 panned");
      setpanlevel(sublevels[2],sublevels[4]);
       returntonav(3,9);
        
        // lemenuroot();
       }
   }
  int sizepan = map(score,0,2,0,35);
   wavelinemenuBG(sublevels[2]);
  dolistwavelineparams();
    dodisplay();
  display.drawRect(45, 16, 7, 35, SSD1306_WHITE);
  display.drawRect(57, 16, 7, 35, SSD1306_WHITE);
  display.fillRect(45, 64-sizepan-13, 7, sizepan, SSD1306_WHITE);
  display.fillRect(57, 64-sizepan-13, 7, sizepan, SSD1306_WHITE);
    display.setTextSize(2);
     display.setCursor(80,0);
  display.println(panLs[sublevels[2]]);
  display.display();
}
void displayoffsetwav(int synthi) {
  byte sizefreq ;
      
    if (navlevel == 4 ) {
     navrange = 128;
     wave1offset[synthi] = sublevels[4] ;

for (int i=0 ; i < nombreofliners ; i++ ) {
    waveforms1[i+(synthi*8)]->offset((float)(((64.0-wave1offset[synthi])/64.0)));
    FMwaveforms1[i+(synthi*8)]->offset((float)(((64.0-wave1offset[synthi])/64.0)));
  }
      }
             
  if (navlevel >= 5 ) {
      returntonav(3,9);   

       }
       
//       sizefreq = map(score,0,128,0,35);
//         wavelinemenuBG(sublevels[2]);
//        dolistwavelineparams();
//          dodisplay();
//        display.drawRect(45, 16, 7, 35, SSD1306_WHITE);
//        display.drawRect(57, 16, 7, 35, SSD1306_WHITE);
//        display.fillRect(45, 64-sizefreq-13, 7, sizefreq, SSD1306_WHITE);
//        display.fillRect(57, 64-sizefreq-13, 7, sizefreq, SSD1306_WHITE);
//          display.setTextSize(2);
              wavelinemenuBG(sublevels[2]);
        dolistwavelineparams();
          dodisplay();
           canvastitle.fillScreen(SSD1306_BLACK);
           canvastitle.setTextSize(2);
           canvastitle.setCursor(75,0);
        canvastitle.print((float)(((64.0-wave1offset[synthi])/64.0)));
        dodisplay();
        
}

void displayfreqbars(int score) {
//weird but usefull behavior to switch encoder resolution between 0 and 1 
   if (navlevel >= 4 ) {
      
    if (navlevel == 4 ) {
     navrange = 10;
     if (wavesfreqs[sublevels[2]] == 1) {
        demimalmode = !demimalmode ;
      } else {
      if (wavesfreqs[sublevels[2]] <= 1) {
        demimalmode = 1 ;
      }  
    }
        if (!demimalmode) {
         wavesfreqs[sublevels[2]] = sublevels[4] ;
      }
      if (demimalmode ) {
          wavesfreqs[sublevels[2]] = (sublevels[4])/10.0 ;
      }
        
      //Serial.println("nav = 4 freq");

            }
  if (navlevel >= 5 ) {
   // Serial.println("nav = 5 freq");
      //wavesfreqs[sublevels[2]] = sublevels[4] ;
      
        if (demimalmode) {
           wavesfreqs[sublevels[2]] =  (sublevels[4])/10.0 ;
          }
     
       if (!demimalmode) {
             wavesfreqs[sublevels[2]] =  sublevels[4] ;
          }
      returntonav(3,9);
         }

       }
       int sizefreq = map(score,0,20,0,35);
         wavelinemenuBG(sublevels[2]);
        dolistwavelineparams();
          dodisplay();
//        display.drawRect(45, 16, 7, 35, SSD1306_WHITE);
//        display.drawRect(57, 16, 7, 35, SSD1306_WHITE);
//        display.fillRect(45, 64-sizefreq-13, 7, sizefreq, SSD1306_WHITE);
//        display.fillRect(57, 64-sizefreq-13, 7, sizefreq, SSD1306_WHITE);
          display.setTextSize(2);
           display.setCursor(65,0);
        display.println(wavesfreqs[sublevels[2]]);
        display.display();
        
}


void displayphasebars(int score) {

   if (navlevel >= 4 ) {
      if (navlevel == 4 ) {
    
      navrange = 360;
      phaselevelsL[sublevels[2]] = int(sublevels[4] );
      
      setphaselevel(sublevels[2]);
       // Serial.println("nav = 4 phase");
            }
  if (navlevel >= 5 ) {
   setphaselevel(sublevels[2]);
         
       returntonav(3,9);
        
       }
  }
   
   // int sizephase = map(score,0,360,0,35);
     wavelinemenuBG(sublevels[2]);
    dolistwavelineparams();
      dodisplay();
//    display.drawRect(45, 16, 7, 35, SSD1306_WHITE);
//    display.drawRect(57, 16, 7, 35, SSD1306_WHITE);
//    display.fillRect(45, 64-sizephase-13, 7, sizephase, SSD1306_WHITE);
//    display.fillRect(57, 64-sizephase-13, 7, sizephase, SSD1306_WHITE);
      display.setCursor(80,0);
    display.setTextSize(2);
    display.println(phaselevelsL[sublevels[2]]);
    display.display();
}




void displayModulatedbool(int lesynthb) {
wavelinemenuBG(lesynthb);
 dolistwavelineparams();
    dodisplay();
     display.setCursor(110, 0);
     display.setTextSize(2); 
  display.println(FMmodulated[lesynthb]);
  
  display.display();
  
}
void setfmtophase(byte lesynth){
  for (byte i = 0 ; i < nombreofliners ; i++ ) {
      FMwaveforms1[i+(lesynth*8)]->phaseModulation(180);
  }
}
void setfmtofreq(byte lesynth){
  for (byte i = 0 ; i < nombreofliners ; i++ ) {
      FMwaveforms1[i+(lesynth*8)]->frequencyModulation(10);
  }
}
void wavelineModulatedbool(int lesynthi) {
if (navlevel == 4 ) {
    navrange = 2 ;
       // Serial.println("Setting Mdulation switch");
         FMmodulated[lesynthi] = sublevels[4] ;
  }
         if (navlevel > 4 ) {
          if (FMmodulated[lesynthi] == 1 ) {
          setfmtofreq(lesynthi);
          }
          if (FMmodulated[lesynthi] == 2 ) {
            setfmtophase(lesynthi);
          }
        setwavetypefromlist(lesynthi, Waveformstyped[lesynthi]);
       returntonav(3); 
  }
  displayModulatedbool(lesynthi);

}
void wavelinePhase(int lesynthi) {
  displayphasebars(phaselevelsL[lesynthi]);
}
void wavelineADSR(int lesynthi) {
  displayadsrbars(adsrlevels[0]);

}
void wavelineFreq(int lesynthi) {
  displayfreqbars(wavesfreqs[lesynthi]);

}
void wavelinePan(int lesynthi ) {
  displaypanbars(panLs[lesynthi]);

}
 
void wavelineoffset(int lesynthi) {
  //displayoffsetwav(sublevels[4]);
displayoffsetwav(lesynthi);

}
void displaywaveformicon(int letype, char* lelabelw, const unsigned char img[], int lesinthy, typeof(WAVEFORM_SINE) wavetype )  {

 wavelinemenuBG(sublevels[2]);
  dolistwavelineparams();
    dodisplay();
    display.drawBitmap(74, 20, img, 32, 32, SSD1306_WHITE);
display.setTextSize(1); // Draw 1X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(64, 0);
 dolistwavelineparams();
    dodisplay();
  display.println(lelabelw);
 display.display();
  if (navlevel == 4 ) {
    navrange = 11;
       // Serial.println("Setting TYPE");
       Waveformstyped[lesinthy] = sublevels[4] ;
  
         // sublevels[4] = Waveformstyped[lesinthy] ;
       
        //sublevels[3] = 0;
      
        setwavetypefromlist(lesinthy, Waveformstyped[lesinthy]);
        if ( Waveformstyped[lesinthy] == 11) {
    
          mixlevelsL[lesinthy] = 0 ;
         
           setwavemixlevel(lesinthy);
        }
  }
 if (navlevel > 4 ) {
          returntonav(3,7);
      

       }
     

  
}

void wavelineType(int lesynthi) {

   switch( sublevels[4] ) {
    case 0 :
    displaywaveformicon(sublevels[4],(char*)"SineWave",sinewave, lesynthi, WAVEFORM_SINE);
    break;
    case 1 :
    displaywaveformicon(sublevels[4],(char*)"SawWave",sawtoothwave,lesynthi,WAVEFORM_SAWTOOTH);
    break;
    case 2 :
    displaywaveformicon(sublevels[4],(char*)"ReverseSaw",reversesawtoothwave,lesynthi,WAVEFORM_SAWTOOTH_REVERSE);
    break;
    case 3 :
    displaywaveformicon(sublevels[4],(char*)"Triangle",trianglewave,lesynthi,WAVEFORM_TRIANGLE);
    break;
    case 4 :
    displaywaveformicon(sublevels[4],(char*)"V-Triangle",variabletriangle,lesynthi,WAVEFORM_TRIANGLE_VARIABLE);
    break;
    case 5 :
    displaywaveformicon(sublevels[4],(char*)"SquareWave",squarewave,lesynthi,WAVEFORM_SQUARE);
    break;
    case 6 :
    displaywaveformicon(sublevels[4],(char*)"PulseWave",pulsewave,lesynthi,WAVEFORM_PULSE);
    break;
    case 7 :
    displaywaveformicon(sublevels[4],(char*)"Arbitrary",arbitrarywave,lesynthi,WAVEFORM_ARBITRARY);
    break;
    case 8 :
    displaywaveformicon(sublevels[4],(char*)"SampleHold",samplehold,lesynthi,WAVEFORM_SAMPLE_HOLD);
    break;
    case 9 :
    displaywaveformicon(sublevels[4],(char*)"Drum",arbitrarywave,lesynthi,WAVEFORM_ARBITRARY);
    break;
    case 10 :
    displaywaveformicon(sublevels[4],(char*)"String",samplehold,lesynthi,WAVEFORM_SAMPLE_HOLD);
    break;
    case 11 :
    displaywaveformicon(sublevels[4],(char*)"Wave OFF",moonwave,lesynthi,WAVEFORM_SINE);
    break;

    default:
    break;


      }


}

void wavelinepanel(int synthi) {

switch(sublevels[3]) {

      case 0:

      wavelineType(synthi) ;

      break;
       case 1:
       
      wavelineModulatedbool(synthi);
      
      break;
       case 2:
     displayLFOpanel(synthi);
      break;
       case 3:
       wavelineFreq(synthi) ;
      break;
       case 4:
       wavelineoffset(synthi) ;
    
      break;
      case 5:
      wavelinePhase(synthi) ;

      break;

      case 7:
      if (sublevels[2] < 3 ) {
      sublevels[2]++ ;
      } else {
        sublevels[2] = 0 ;
        }

      navlevel--;
       lemenuroot();

     // Serial.print("Next");
      break;

      case 6:
      //Serial.print("Previous");
        if (sublevels[2] > 0 ) {
      sublevels[2]-- ;
      } else {
        sublevels[2] = 3 ;
        }
      navlevel--;
       lemenuroot();
      break;

      default:
      break;
}

}
void wavelinemenuBG(int synthi) {
  display.clearDisplay();
 // display.drawBitmap(35, 64-48+20, wavex, 104, 48, SSD1306_WHITE);
  display.setTextSize(1); // Draw 2X-scale text
  display.setCursor(120, 57);
  display.print(synthi+1);
 display.setTextSize(1);


}
void wavelinesBG() {
  display.clearDisplay();
  display.drawBitmap(0, 64-47, wavesbg2, 128, 47, SSD1306_WHITE);


 display.display();
}

void wavelining(int startx, int starty, char* leprintlabel, int synthi ) {
  if (navlevel >= 2) {
     if (navlevel == 2) {

   display.fillRect(startx, starty, 64, 24, SSD1306_INVERSE);
  printlabel(leprintlabel);
  display.display();
  }
  if (navlevel >= 3) {
    if (navlevel == 3) {
      navrange = truesizeofwavelineslabels-1 ;

       wavelinemenuBG(sublevels[2]);
       display.display();
    dolistwavelineparams();
    dodisplay();

        if (sublevels[3] == 0){
        sublevels[4] = Waveformstyped[synthi] ;
        wavelinepanel(synthi);
        }
        if (sublevels[3] == 1) {
          //Modulated bool switch
       //sublevels[4] = int(mixlevelsL[synthi]*100) ;
       wavelinepanel(synthi);
        }
        if (sublevels[3] == 2) {
          //LFO1
       //sublevels[4] = int(adsrlevels[synthi][0]) ;
       //wavelinepanel(sublevels[2]);
        }
        if (sublevels[3] == 3) {
       sublevels[4] = round(wavesfreqs[synthi]) ;
       wavelinepanel(synthi);
        }
      if (sublevels[3] == 5) {

      //  Serial.println("phasing");
       sublevels[4] = int(phaselevelsL[synthi]) ;
       wavelinepanel(synthi);
        }
        if (sublevels[3] == 4) {
          sublevels[4] = wave1offset[synthi] ;
           wavelinepanel(synthi);
          
          
      //Offset
      //  Serial.println("Offset");
       //sublevels[4] = int(panLs[synthi]) ;
       //wavelinepanel(sublevels[2]);
        }
   

    }
    if (navlevel >= 4) {
     
    wavelinepanel(synthi);
    }

    }
  }
}
void reinitsublevels(byte fromlei) {
  for (byte i = fromlei ; i < 7 ; i++ ) {
     sublevels[i] = 0 ;
  }
}
void synthmenu() {
  if (navlevel == 1) {
    display.clearDisplay();
    reinitsublevels(2);
    
   // displayleBGimg(wavesbg);
//  selectbox(500,170, wavesbg , (char*)"\0" );
  dolistsyntmenu();
  dodisplay();
  }
  if (sublevels[1] == 3 && navlevel > 1){
    navrange=3;
    showsynthparamspanel();
  }
    if (sublevels[1] == 2) {
      if (navlevel >= 2) {
        if (navlevel == 2) {
          navrange = 5;
            }
            navleveloverwrite = 2 ;
            displayadsrgraph();
        }
    
    }
//waves menu
  if (sublevels[1] == 0) {
  if (navlevel >= 2) {
    if (navlevel == 2) {

     navrange = 3;
    wavelinesBG();
    sublevels[3] = 0 ;
    }
    
    switch(sublevels[2]) {

      case 0:
        toprint = (char*)"Waveline 1";
        wavelining(0,16,toprint,sublevels[2]);
        
      break;
      case 1:
        toprint = (char*)"Waveline 2";
        wavelining(64,16,toprint, sublevels[2]);
      break;
      case 2:
        toprint = (char*)"Waveline 3";
         wavelining(0,40,toprint, sublevels[2]);
      break;
      case 3:
        toprint = (char*)"Waveline 4";
        wavelining(64,40,toprint, sublevels[2]);
      break;

      default:
      break;

    }

    }
  }
  //mixer
  if (sublevels[1] == 1 && navlevel > 1) {
  showmixerwaves();
  }
  if (sublevels[1] == 4 && navlevel > 1) {
  le303filterVpanel();
  }


}

float fxslopedown2(byte curve, float laxval) {
 // 0 to 1 10 vals 1 to 2 10 2 to 3 10
  //float leresult ;
  
  return pow(laxval,(double)(curve/128.0));
}
 float fxslopedown(byte slope, float laxval) {
  float leresult = 0 ;
  switch(slope) {
    case 0: 
    leresult = 1-(((1/(pow(10,(double)laxval)))*5.55556)-0.555556)/5;
    break;
    case 1:
    leresult =  laxval ;
    break;
    case 2:
    leresult =  sqrt( abs(sin(( (laxval))*3.14159 + 1.57))) ;
    break;
    case 3:
    leresult = 1.0 - ((sin(laxval*3.14159+1.57))*0.5)+0.5  ;
    break;
    
    default:
    break;
    
  }
  return abs(leresult);
 //  letbfreq = (((1/(10^x)*5.6)-0.6)/5);
 // letbfreq = (le303filterzrange+100-(le303filterzrange*ladiff1));
//   letbfreq = le303filterzrange+100-(le303filterzrange*( sqrt( abs(sin(( (ladiff1))*3.14159 + 1.57))) ));
 }
void actionsynthparamspanel() {
  
if (navlevel == 3) {
    navrange = 128 ;
  if (sublevels[2]==0 ) {
     slope1 = sublevels[3];
      
  }
   if (sublevels[2]==1 ) {
    navrange = 128 ;
     slope2 = sublevels[3];
      
  }
 }
 if (navlevel > 3) {
 returntonav(2);
 }
}
void selectsynthparamspanel() {
  if (navlevel == 2) {
    navrange = 1 ;
  if (sublevels[2]==0 ) {
    sublevels[3] = slope1 ;
      canvasBIG.setCursor(40,16);
      canvasBIG.print((char)9);
  }
   if (sublevels[2]==1 ) {
    sublevels[3] = slope2 ;
      canvasBIG.setCursor(104,16);
      canvasBIG.print((char)9);
  }
 }
}
void showsynthparamspanel() {
  actionsynthparamspanel();
  display.clearDisplay();
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.fillScreen(SSD1306_BLACK);
selectsynthparamspanel();
  canvasBIG.setCursor(0,16);
canvasBIG.setTextSize(1);
canvasBIG.print("Sl1: ");
canvasBIG.print(slope1);
  canvasBIG.setCursor(64,16);
canvasBIG.print("Sl2: ");
canvasBIG.print(slope2);
  canvasBIG.setCursor(0,16+10);
canvasBIG.print("C.mode:");
canvasBIG.print(cutoffmode);
  canvasBIG.setCursor(64,16+10);
canvasBIG.print("R.mode:");
canvasBIG.print(resonancemode);
  canvasBIG.setCursor(0,16+20);
canvasBIG.print("param5:");
canvasBIG.print(paramse1);
  canvasBIG.setCursor(64,16+20);
canvasBIG.print("param6:");
canvasBIG.print(paramse2);
dodisplay();
}
void lemenuroot() {
  if (navlevel == 0) {
    displaymenu();
  }
  if (navlevel > 0) {
  switch(sublevels[0]) {

      case 0 :

      if (navlevel >= 1) {
        if (navlevel == 1) {
        navrange = 4;
        }
        
          synthmenu();
      }

      break;
      case 1 :
  
       if (navlevel >= 1) {
        if (navlevel == 1) {
        navrange = 4;
        }
        LFOmenu();
      }
      break;
      case 2 :
       
      if (navlevel >= 1) {
        navrange = 128+3 ;
        knobassigner();
          }
      break;
      case 3 :
       
        if (navlevel >= 1) {
        displaySongmenu();
        }
       break;
      case 4 :
    
       if ( navlevel >=1 ) {
        navrange = sizeofpatternlistlabels - 1 ;
        displayPatternmenu();
        }

      break;
      case 5 :
             
      if (navlevel >= 1) {
          
         displaysettingspanel();
      }
      
        break;
        case 6 :
       
          if (navlevel >= 1) {

          MainFxPanel();

       }
       break;
       case 7 :
        
       
        if (navlevel >= 1) {
        displaysamplermenu();
       }
       break;
        case 8 :
       
       if (navlevel >= 1) {
             Vbuttonspanel();
         }
       break;
        case 9 :
        
       if ( navlevel >=1 ) {
        navrange = 4 ;
        displaypresetmenu();
        }
       break;

    default :
   // Serial.println("Invalid" );
    break;
   }
  }
}

void displaymenu() {
 
  if (navlevel == 0) {
    previousnavlevel = 0 ;
    navrange = 9 ;
    rotamode = 1;
    plusminusmode = 0 ;
    displayleBGimg(menuBG);
  }
  
  
  switch(sublevels[0]) {
      case 0 :
      toprint = (char*)"WaveSynth";
       selectbox(5,17);
      break;
     case 1 :
      toprint = (char*)"LFOs";
       selectbox(29,17);  
      break;
      case 2 :
       toprint = (char*)"Set Knobs";
       selectbox(53,17);
      break;
      case 3 :
       toprint = (char*)"Song";
       selectbox(77,17);   
       break;
      case 4 :
       toprint = (char*)"Pattern";
      selectbox(101,17);  
      break;
      case 5 :
       toprint = (char*)"Settings";
       selectbox(5,41);                   
        break;
        case 6 :
       toprint = (char*)"MainFX";
       selectbox(29,41);  
       break;
       case 7 :
       toprint = (char*)"Sampler";
       selectbox(53,41);     
       break;
        case 8 :
       toprint = (char*)"V buttons";
       selectbox(77,41);    
       break;
        case 9 :
       toprint = (char*)"Presets";
       selectbox(101,41);
       break;

    default :
    //Serial.println("Invalid");
    break;
   }
   printlabel(toprint);
   display.display();
  }


void listknobassigner() {

     display.clearDisplay();
canvastitle.fillScreen(SSD1306_BLACK);
canvastitle.setCursor(0,0);
toprint = (char*)"Knob";
canvastitle.setTextSize(2);

canvastitle.println(toprint);
canvastitle.setCursor(85,0);
//toprint = (char*)"Knob";
canvastitle.println(sublevels[1]);

canvasBIG.fillScreen(SSD1306_BLACK);
if (sublevels[1] < 128 ) {
  //Serial.println(sublevels[1]);
  if (midiknobassigned[sublevels[1]] !=0 ) {

  canvasBIG.setTextSize(1);
  canvasBIG.setCursor(85,16);
  canvasBIG.println(midiknobassigned[sublevels[1]]);
  canvasBIG.setCursor(0,40);
  canvasBIG.println(ControlList[midiknobassigned[sublevels[1]]]);
  }
} else {

   if (knobassigned[sublevels[1]-128] !=0 ) {
    // Serial.print("sublevels[1]-128 = ");
  //Serial.println(sublevels[1]-128);
  canvasBIG.setTextSize(2);
  canvasBIG.setCursor(85,16);
  canvasBIG.println(knobassigned[sublevels[1]-128]);
  canvasBIG.setCursor(0,40);

canvasBIG.println(ControlList[knobassigned[sublevels[1]-128]]);
  }
}


}
void knobsettermidi() {
  midiknobassigned[sublevels[1]] = sublevels[2];
}
void knobsetterinternal() {
  knobassigned[sublevels[1]-128] = sublevels[2];
}
void listknobassigner2() {

     display.clearDisplay();
canvastitle.fillScreen(SSD1306_BLACK);
canvastitle.setCursor(0,0);
toprint = (char*)"Knob";
canvastitle.setTextSize(2);

canvastitle.println(toprint);
canvastitle.setCursor(85,0);
//toprint = (char*)"Knob";
canvastitle.println(sublevels[1]);

canvasBIG.fillScreen(SSD1306_BLACK);

  canvasBIG.setTextSize(1);
  canvasBIG.setCursor(85,16);
canvasBIG.println(sublevels[2]);
canvasBIG.setCursor(0,40);
canvasBIG.println(ControlList[sublevels[2]]);



}
void knobassigner() {
   if (navlevel == 1 ) {
    reinitsublevels(2);
    listknobassigner();
    dodisplay();
   }
    if (navlevel == 2 ) {
    navrange =  allfxes ;
    listknobassigner2();
    dodisplay();
   }
   if (navlevel == 3 ) {
        if (sublevels[1] < 128 ) {
        knobsettermidi();
      } else {
        knobsetterinternal();
      }
       returntonav(1);
   }
}
