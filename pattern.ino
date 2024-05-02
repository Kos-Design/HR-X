void tick() {

  tickerlasttick = millis();
  //metronomer();

    tickposition++;
    
   
      
       if (tickposition > pbars-1 ) {
      tickposition=0 ;
    }
     if (patrecord && tickposition == 0) {
        getlinerwithoutevents();
        Serial.println(offsetliner);
        }           
  if (arpegiatorOn) {
      for (int i = 0 ; i < nombreofarpeglines ; i++ ) {
        calledarpegenote[i][0] = 0; 
          for (int j = 0 ; j < nombreofliners ; j++ ) {
                 if ( arpegnoteoffin[i][j] == 1) {
                  shutlineroff(playingarpegiator[i][j]);
                  arpegnoteoffin[i][j] = 0 ;
                  playingarpegiator[i][j]= 0 ;
                     }
                  if (arpegnoteoffin[i][j] > 1) {
                    arpegnoteoffin[i][j]--;
              }         
            }
          if (arpegiatingNote[i] != 0 ) {
              playarpegenote(i);
            }
      }
      if ( stoptickernextcycle ) {
    closeallenvelopes();
    if (patternOn != 1) {
    stoptick = 1 ;
    }
    stoptickernextcycle = 0 ;
    
    //allarpegeoffs();
  } 
  }
  if (patternOn == 1) {
    
    if ( !stoptick ) {
      doesccgonnachangeinpatfromnow();
  //if (  howmanyactiveccnow>0 ) {
    }
 // }

  for (int i=0; i< nombreofliners; i++ ) {
    if ( (event1notesOff[i][tickposition][1] != 0 && event1notesOff[i][tickposition][0] == synthmidichannel  )) {
          event1offs(i);
         }
   // if ( i < nombreofliners ) {
      if ( event1notes1[i][tickposition][1] != 0 ) {
           event1(i);
         }
//     if  ( (millis() - millisSincenLinerOn[i] >= currentnotelength[i] || (millis()-millisSincenLinerOn[i] >= millitickinterval*4  )) && (!patrecord || overdubmidi)) {
//      Serial.println("panic noteoff");
//           MaNoteOff((byte)synthmidichannel, event1lineplayingfrom[i][0], 0);
//      
//        }
   // }
    if ( event2notes1[i][tickposition][1] != 0  ) {
           event2(i);
         }

      
         
    }
     // if ( navlevel >= navlevelpatedit && sublevels[0] == 4  ) {
      //drawsequencer();
      //}
//  }
// 
//  
//}
  }
  if (tickposition == pbars-1 ) {
        if (songplaying ) {
          if ( songplayhead < numberofpatonsong-1 ) {
    songplayhead++;
          } else {
            songplayhead = 0;
          }
        
    loadsongpattern();
   // if ( navlevel > 0 && sublevels[0] == 3 ) {
   // Songmodepanel();
    //}
    
      }
      }
}

void displayPatternmenu() {
   
   if (navlevel == 1) {
  navrange = sizeofpatternlistlabels-1 ;
  PatternmenuBG();
  dolistPatternsmenu();
  dodisplay();
  }
  
   if (navlevel > 1 && sublevels[1] == 0 ) {
    drawsequencer();
    //return;
  } 
 
   if ( navlevel > 1 && sublevels[1] == 5) {
      optionspattern();
      }
   if ( navlevel > 1 && sublevels[1] == 6) {
        //  Serial.println("clearing pattern");
          clearlapattern();
          vraipos = 6;
           myEnc.write(4*vraipos);
           navlevel--;
      }
  if ( navlevel > 1 && sublevels[1] == 7) {
        //  Serial.println("editing CCs");
          
    editlaccninou();
        // when back:
       //   vraipos = 7;
       //    myEnc.write(4*vraipos);
        //   navlevel--;
      }
     
  if (navlevel > 1 && sublevels[1] != 0 && sublevels[1] != 7 && sublevels[1] != 5) {
   navrange = sizeofpatternlistlabels-1 ; 
  PatternmenuBG();
  dolistPatternsmenu();
  dodisplay();
  }

  
 
}       


void PatternmenuBG() {
 
  display.clearDisplay();
  if (navlevel == 1) {
    navrange = sizeofpatternlistlabels -1 ;
  }
 
   if (navlevel > 1 && sublevels[1] !=0) {
       if (sublevels[1] == 1 ) {
         navrange = numberofPatternfiles;
        // lqcurrentpqt =
       } else {
     //setnavrange();
        navrange = numberofPatternfiles - 1;
        lqcurrentpqt = sublevels[2] ;
        }
   }
       displaythelistofpatterns();
       dodisplay();
       
     
  if (navlevel > 2 && (sublevels[1] == 1 || sublevels[1] == 2 || sublevels[1] == 3 || sublevels[1] == 4 )) {
   // Serial.println("preset action selected");
      lqcurrentpqt = sublevels[2] ;
        navlevel = 1;
        //sublevels[3] = 1;
        vraipos = 1;
        myEnc.write(4);
        //navrange = numberofPatternfiles - 1;
        switch (sublevels[1]) {
          
          case 0:
         
          break;
          
          case 1:
          
          writelemidi(sublevels[2]);
          break;
          
          case 2:
          clearlapattern();
          
          parsepattern(sublevels[2]);
          break;
          
          case 3:
          copypattern(sublevels[2]);
          //deletepreset();
          break;
          
          case 4:
          deletepattern(sublevels[2]);
          break;

          case 5:
        // optionspattern();
          break;
          case 6:
        
          break;
          case 7:
          //editlaccninou();
          break;

          default:
          break;
        }
         displayPatternmenu();
        
         
       }
 
 
}
void showleditcc(){
  int lavaluecc ;
  int lacellwidth = 128/pbars;
  int lestartyc = 16 ;
  float lacellratio = (62-lestartyc)/127.0 ;
  int lacellx ;
  int lacelly ;
   int lalinex1 ;
  int lalinex2 ;
     int laliney1 ;
  int laliney2 ;
  int ffg ;
   display.clearDisplay();
    canvasBIG.fillScreen(SSD1306_BLACK);
    
  if (navlevel == 2) {
    canvastitle.fillScreen(SSD1306_BLACK);
    canvastitle.setCursor(0,0);
    if ( midiknobassigned[sublevels[2]] == 0 ) {
    canvastitle.setTextSize(2);
    canvastitle.print("Edit CC");
    if (sublevels[2]<100){
      canvastitle.print(" ");
    }
     if (sublevels[2]<10){
      canvastitle.print(" ");
    }
    canvastitle.print(sublevels[2]);
    } else {
      canvastitle.setTextSize(1);
      canvastitle.print("CC");
      canvastitle.print(sublevels[2]);
       canvastitle.print(" ");
       canvastitle.print((char*)ControlList[midiknobassigned[sublevels[2]]]);
    }
  }
    canvasBIG.drawRect(0,16,128,64,SSD1306_WHITE);
    
    for (int j = 0 ; j < pbars ; j++ ) {
   
          lavaluecc = (int)event1controllers[sublevels[2]][j];
          lacellx = 1+j*lacellwidth ;
          lacelly = 63  - lacellratio*lavaluecc ;
             lalinex1 = lacellx;
             laliney1 = lacelly;
             if( lavaluecc < 128 ) {
            canvasBIG.fillRect(lacellx,lacelly,3,3,SSD1306_WHITE);
            if (j > 0) {
              if( (int)event1controllers[sublevels[2]][j-1] < 128 ) {
            canvasBIG.drawLine(lalinex2,laliney2,lalinex1,laliney1,SSD1306_WHITE);
              }
            }
            }
            
         lalinex2 = lalinex1;
        laliney2 = laliney1;
    }
     
    //canvasBIG.drawLine(0,16,0,64,SSD1306_WHITE);

    
    dodisplay();
}
void editlaccninou() {
 navrange = 127;
  showleditcc();
  editlaccactionpath();
  dodisplay();
}
void headerccedit(){
  display.clearDisplay();
   canvastitle.fillScreen(SSD1306_BLACK);
    canvastitle.setCursor(0,0);
    canvastitle.setTextSize(1);
    canvastitle.print("Edit CC ");
    canvastitle.print(sublevels[2]);
    canvastitle.setCursor(0,8);
    canvastitle.print("Pos: ");
    canvastitle.print(sublevels[3]);
    canvastitle.setCursor(90,0);
    canvastitle.setTextSize(2);
    if(event1controllers[sublevels[2]][sublevels[3]]<128) {
      canvastitle.print(event1controllers[sublevels[2]][sublevels[3]]);
    }
      if(event1controllers[sublevels[2]][sublevels[3]]>=128) {
      canvastitle.print("Off");
    }
    
}
void editlaccactionpath(){
  if (navlevel==3) {
   
    navrange = pbars-1 ;
    
    sublevels[4] = (int)event1controllers[sublevels[2]][sublevels[3]] ;
    headerccedit();
    showvertlinecursor(sublevels[3]); 
  }
  if (navlevel==4) {
   
    navrange = 128 ;
    event1controllers[sublevels[2]][sublevels[3]] = (byte)sublevels[4];
    headerccedit();
  }  
  if (navlevel>4) {
    navlevel = 3 ;
    vraipos = sublevels[3];
    myEnc.write(vraipos*4);
    navrange = pbars-1 ;
  } 
  
}
void showvertlinecursor(int lavertpos) {
   display.drawLine(lavertpos*(128/pbars),16,lavertpos*(128/pbars),64,SSD1306_WHITE);
}
void clearlapattern(){
  if ( !targetNOsynth || songplaying ) {
  clearsynthpatternline();
  }
  if ( !targetNOsampler || songplaying ) {
  clearsamplerpatternline();
  }
  if ( !targetNOcc || songplaying ) {
  clearCCline();
  }
  //cc as well
}
void clearCCline() {
  //Serial.print("clearpatternline ");
  for (int j = 0 ; j < pbars ; j++ ) {
    for (int i = 0 ; i < 128 ; i++ ) {
      
      event1controllers[i][j] = 128;
    }
      
  }
      
}
void clearsynthpatternline() {
  //Serial.print("clearpatternline ");
  for (int j = 0 ; j < pbars ; j++ ) {
    for (int i = 0 ; i < nombreofliners ; i++ ) {
      
      event1notes1[i][j][1]= 0;
      event1notes1[i][j][2]= 0;
      event1notes1[i][j][0]= 0 ;
      length1notes1[i][j]= 0;
      event1notesOff[i][j][0] = 0;
      event1notesOff[i][j][1] = 0;
      parsedevent1notesOff[i][j][1] = 0 ;
      parsedevent1notesOff[i][j][0] = 0 ;
     }
      evented1[0][j] = 0;
      
  }
 
}
void clearsamplerpatternline() {
 // Serial.print("clearpatternline ");
  for (int j = 0 ; j < pbars ; j++ ) {
    for (int i = 0 ; i < nombreofSamplerliners ; i++ ) {
      
      event2notes1[i][j][1]= 0;
      event2notes1[i][j][2]= 0;
      event2notes1[i][j][0]= 0 ;
//      length2notes1[i][j]= 0;
    
     }
      evented1[1][j] = 0;
      event2notesOff[j][0] = 0;
      event2notesOff[j][1] = 0;
  }
}

void optionspattern() {
  
  //size 4
  //char optionspatternlabels[sizeofoptionspattern][12] = {"Transpose","Shift", "Clear", "Target" };
  if ( navlevel == 2  ) {
    navrange = sizeofoptionspattern -1 ;
  optionspatterndisplays();
    
    if ( sublevels[2]==1 ) {
     sublevels[3]=16;
   }
    
    if ( sublevels[2]==0 ) {
     sublevels[3]=7;
   }
  }
  if ( navlevel == 3 ) {
    
    if ( sublevels[2]==4 ) {
        //navrange = 14 ;
    interpolOn = !interpolOn ;
    returntonav(2,sizeofoptionspattern -1);
    
    }
    if ( sublevels[2]==2 ) {
        //navrange = 14 ;
    clearlapattern();
     returntonav(2);
    }
    
      if ( sublevels[2]==0 ) {
        navrange = 14 ;
    showtransposedisplays();
    }
      if ( sublevels[2]==3 ) {
        navrange = 6 ;
    showlestargetdisplays();
    }
    if (sublevels[2]==1 ) {
        navrange = 31 ;
    showShifterdisplays();
     }
  }
  if ( navlevel > 3 ) {
    if ( sublevels[2]==0 ) {
       dotranspose();
     }
      
   if ( sublevels[2]==1 ) {
      doShifter();
      }
     
      navlevel = 2 ;
      vraipos = sublevels[2];
      myEnc.write(vraipos*4);
      navrange = sizeofoptionspattern -1 ;
  
  }
}

void dotranspose(){
  //Serial.print("transposed");
  if ( !targetNOsynth ) { 
  dotransposesynth();
  }
  if ( !targetNOsampler ) {
    dotransposesampler();
  }
  if ( !targetNOcc ) {
   dotransposeCC();
  }
   
}

void doShifter(){
 // Serial.print("Shifterd");
   if ( !targetNOsynth ) { 
  doShiftersynth();
   }
  if ( !targetNOsampler ) {
  doShiftersampler();
  }
  if ( !targetNOcc ) {
  doShifterCC();
  }
}

void dotransposesynth(){
 // Serial.println("synth transposed");
 if (sublevels[3]-7>0) {
  shiftnotes1down(abs(sublevels[3]-7));
       
    }
    if (sublevels[3]-7<0){
 
         shiftnotes1up(abs(sublevels[3]-7)); 
    }
      refreshevented1();
  } 
void dotransposeCC(){
 // Serial.println("synth transposed");
 if (sublevels[3]-7>0) {
  shiftnotesCCdown(abs(sublevels[3]-7));
       
    }
    if (sublevels[3]-7<0){
 
         shiftnotesCCup(abs(sublevels[3]-7)); 
    }
  }  

void doShifterCC(){
  //Serial.println("sampler Shifterd");
 if (sublevels[3]-16>0) {
  shiftnotesCCleft(abs(sublevels[3]-16));
       
    }
    if (sublevels[3]-16<0){
 
         shiftnotesCCright(abs(sublevels[3]-16)); 
    }
  }
void shiftnotesCCup(int leshifter){
  
  
for (int shifts = 0 ; shifts < leshifter ; shifts++) {
  for (int i=0; i<128 ; i++ ) {
    for (int j= 0; j < pbars ; j++ ) {    
    
        if ( ((int)event1controllers[i][j] < 127 ) && ((int)event1controllers[i][j] > 0 ) ) {
      
          event1controllers[i][j]++ ;
    
     
   }
    }
  }
}
}
void shiftnotesCCdown(int leshifter){
  
for (int shifts = 0; shifts < leshifter ; shifts++) {
    for (int i=0; i<128 ; i++ ) {
       for (int j=0; j < pbars ; j++ ) {
 
         if ( (int)event1controllers[i][j] > 0 )  {
      
            event1controllers[i][j]-- ;   
      }
     }
    }
  }
}
         
void shiftnotesCCright(int leshifter){
   byte letempevent1;  
  for (int shifts = 0 ; shifts < leshifter ; shifts++) {
    for (int i=0; i<128 ; i++ ) {
      for (int j= pbars-1; j >= 0 ; j-- ) {
    
      if ( j == pbars - 1 ) {
      letempevent1 = event1controllers[i][pbars-1];   
      event1controllers[i][j] = event1controllers[i][j-1] ;
    }
    if ( (j > 0) && (j < pbars-1 )) {    
         event1controllers[i][j] = event1notesOff[i][j-1] ;    
    }
   
    if ( j == 0 ) {  
        event1controllers[i][j] = letempevent1 ; 
    } 
  
    }
    }
    }
 }

void shiftnotesCCleft(int leshifter){
  
  byte letempevent1;  
for (int shifts = 0; shifts < leshifter ; shifts++) {
   
  for (int i=0; i<128 ; i++ ) {
    for (int j=0; j < pbars ; j++ ) {
    
  if ( j == 0 ) {  
     letempevent1 = event1controllers[i][0];    
    event1controllers[i][j] = event1controllers[i][j+1] ;  
  } 
      if ( (j > 0) && (j < pbars-1 )) {
        event1controllers[i][j] = event1controllers[i][j+1] ;
         
      } 
   if ( j == pbars -1 ) {
    event1controllers[i][j] = letempevent1;
  }
}
  }
}
}

   
void shiftnotes1up(int leshifter){
 for (int shifts = 0 ; shifts < leshifter ; shifts++) {
  for (int i=0; i<nombreofliners ; i++ ) {
    for (int j= 0; j < pbars ; j++ ) {    
     if ( ((int)event1notes1[i][j][1] < 127 ) && ((int)event1notes1[i][j][1] > 2 ) ) {
      
        event1notes1[i][j][1]++ ;
     }
        if ( ((int)event1notesOff[i][j][1] < 127 ) && ((int)event1notesOff[i][j][1] > 2 ) ) {
      
          event1notesOff[i][j][1]++ ;
    
     
   }
    }
  }
}
}
void shiftnotes1down(int leshifter){
  for (int shifts = 0; shifts < leshifter ; shifts++) {
  
   for (int i=0; i<nombreofliners ; i++ ) {
      for (int j=0; j < pbars ; j++ ) {
    
          if ( (int)event1notes1[i][j][1] > 1)  {
              
                 event1notes1[i][j][1]-- ;
             }
        if ( (int)event1notesOff[i][j][1] > 1 )  {
      
        event1notesOff[i][j][1]-- ;
    
    
         }
 
      }
    }
  }
}
         
void shiftnotes1right(int leshifter){
   byte letempevent1[2][3];  
for (int shifts = 0 ; shifts < leshifter ; shifts++) {
  for (int i=0; i<nombreofliners ; i++ ) {
    for (int j= pbars-1; j >= 0 ; j-- ) {
  
    if ( j == pbars - 1 ) {
     
    for (int k=0; k<3 ; k++ ) {
    letempevent1[0][k] = event1notes1[i][pbars-1][k] ; 
     letempevent1[1][k] = event1notesOff[i][pbars-1][k] ; 
    event1notes1[i][j][k] = event1notes1[i][j-1][k] ;
    event1notesOff[i][j][k] = event1notesOff[i][j-1][k] ;
  }
  }
if ( (j > 0) && (j < pbars-1 )) {
   for (int k=0; k<3 ; k++ ) {
     event1notes1[i][j][k] = event1notes1[i][j-1][k] ;
     event1notesOff[i][j][k] = event1notesOff[i][j-1][k] ;
    
    }
}
 
  if ( j == 0 ) {
   
  for (int k=0; k<3 ; k++ ) {
    
     event1notesOff[i][j][k] = letempevent1[1][k] ;
      event1notes1[i][j][k] = letempevent1[0][k] ;
    }
    
  } 

}
  }
}
}

void shiftnotes1left(int leshifter){
  
  byte letempevent1[2][3];  
for (int shifts = 0; shifts < leshifter ; shifts++) {
   
  for (int i=0; i<nombreofliners ; i++ ) {
    for (int j=0; j < pbars ; j++ ) {
    
  if ( j == 0 ) {
    
  for (int k=0; k<3 ; k++ ) {
     letempevent1[0][k] = event1notes1[i][0][k] ; 
     letempevent1[1][k] = event1notesOff[i][0][k] ; 
  
    event1notes1[i][j][k] = event1notes1[i][j+1][k] ;
    event1notesOff[i][j][k] = event1notesOff[i][j+1][k] ;
    }
    
  } 
if ( (j > 0) && (j < pbars-1 )) {
   for (int k=0; k<3 ; k++ ) {
      event1notes1[i][j][k] = event1notes1[i][j+1][k] ;
     event1notesOff[i][j][k] = event1notesOff[i][j+1][k]   ;
    
    }
}
  
   if ( j == pbars -1 ) {
    for (int k=0; k<3 ; k++ ) {
      
     event1notesOff[i][j][k] = letempevent1[1][k] ;
    event1notes1[i][j][k] = letempevent1[0][k] ;
    
  }
  }
}
  }
}
}

 void dotransposesampler(){
 // Serial.println("sampler transposed");
 if (sublevels[3]-7>0) {
  shiftnotes2down(abs(sublevels[3]-7));
       
    }
    if (sublevels[3]-7<0){
 
         shiftnotes2up(abs(sublevels[3]-7)); 
    }
      refreshevented2();
  } 
 void doShiftersampler(){
 // Serial.println("sampler Shifterd");
 if (sublevels[3]-16>0) {
  shiftnotes2left(abs(sublevels[3]-16));
       
    }
    if (sublevels[3]-16<0){
 
         shiftnotes2right(abs(sublevels[3]-16)); 
    }
      refreshevented2();
  } 
              
void shiftnotes2up(int leshifter){
 
for (int shifts = 0 ; shifts < leshifter ; shifts++) {
  
    for (int j= 0; j < pbars ; j++ ) {
      if ( ((int)event2notesOff[j][1] < 127 ) && ((int)event2notesOff[j][1] > 2 ) ) {
          event2notesOff[j][1]++ ;
          }  
      for (int i=0; i<nombreofSamplerliners ; i++ ) {  
     if ( ((int)event2notes1[i][j][1] < 127 ) && ((int)event2notes1[i][j][1] > 2 ) ) {
      
        event2notes1[i][j][1]++ ;
     }
        
    }
  }
}
}
void shiftnotes2down(int leshifter){
  for (int shifts = 0; shifts < leshifter ; shifts++) {
      for (int j=0; j < pbars ; j++ ) {
         if ( (int)event2notesOff[j][1] > 1 )  {
        event2notesOff[j][1]-- ;   
          }
     for (int i=0; i<nombreofSamplerliners ; i++ ) {
          if ( (int)event2notes1[i][j][1] > 1)  {
              
                 event2notes1[i][j][1]-- ;
          }
     
 
        }
    }
  }
}
         
void shiftnotes2right(int leshifter){
   byte letempevent2[2][3];  
for (int shifts = 0 ; shifts < leshifter ; shifts++) {
  
    for (int j= pbars-1; j >= 0 ; j-- ) {
    if ( j == pbars - 1 ) {
     
    for (int k=0; k<3 ; k++ ) {
   
     letempevent2[1][k] = event2notesOff[pbars-1][k] ; 
   
    event2notesOff[j][k] = event2notesOff[j-1][k] ;
  }
  }
if ( (j > 0) && (j < pbars-1 )) {
   for (int k=0; k<3 ; k++ ) {
   
     event2notesOff[j][k] = event2notesOff[j-1][k] ;
    
    }
}
 
  if ( j == 0 ) {
   
  for (int k=0; k<3 ; k++ ) {     
       event2notesOff[j][k] = letempevent2[1][k] ;
    }
    
  } 
    for (int i=0; i<nombreofSamplerliners ; i++ ) {
    if ( j == pbars - 1 ) {
     
    for (int k=0; k<3 ; k++ ) {
    letempevent2[0][k] = event2notes1[i][pbars-1][k] ; 
    event2notes1[i][j][k] = event2notes1[i][j-1][k] ;
   
  }
  }
if ( (j > 0) && (j < pbars-1 )) {
   for (int k=0; k<3 ; k++ ) {
     event2notes1[i][j][k] = event2notes1[i][j-1][k] ;
    
    
    }
}
 
  if ( j == 0 ) {
   
  for (int k=0; k<3 ; k++ ) {
    
    
      event2notes1[i][j][k] = letempevent2[0][k] ;
    }
    
  } 

}
  }
}
}

void shiftnotes2left(int leshifter){
  
  byte letempevent2[2][3];  
for (int shifts = 0; shifts < leshifter ; shifts++) {
   
  
    for (int j=0; j < pbars ; j++ ) {
      if ( j == 0 ) {
         for (int k=0; k<3 ; k++ ) {
           letempevent2[1][k] = event2notesOff[0][k] ; 
           event2notesOff[j][k] = event2notesOff[j+1][k] ;
          }
      }
      if ( (j > 0) && (j < pbars-1 )) {
   for (int k=0; k<3 ; k++ ) {
      
     event2notesOff[j][k] = event2notesOff[j+1][k]   ;
    
    }
}
  
   if ( j == pbars -1 ) {
    for (int k=0; k<3 ; k++ ) {     
     event2notesOff[j][k] = letempevent2[1][k] ;   
  }
  }
    for (int i=0; i<nombreofSamplerliners ; i++ ) {
  if ( j == 0 ) {
    
       for (int k=0; k<3 ; k++ ) {
      letempevent2[0][k] = event2notes1[i][0][k] ; 
       event2notes1[i][j][k] = event2notes1[i][j+1][k] ;
       }
  } 
if ( (j > 0) && (j < pbars-1 )) {
   for (int k=0; k<3 ; k++ ) {
      event2notes1[i][j][k] = event2notes1[i][j+1][k] ; 
    }
}
  
   if ( j == pbars -1 ) {
    for (int k=0; k<3 ; k++ ) {
    event2notes1[i][j][k] = letempevent2[0][k] ;
    
  }
  }
}
  }
}
}

void showtransposedisplays() {
    display.clearDisplay();
   canvastitle.fillScreen(SSD1306_BLACK);
   canvasBIG.fillScreen(SSD1306_BLACK);
       canvastitle.setCursor(0,0);
    canvastitle.setTextSize(2);
    canvastitle.print((char*)optionspatternlabels[sublevels[2]]);
  
    int latransposition ;
    latransposition = 7-sublevels[3];
    canvasBIG.setCursor(0,16);
    canvasBIG.setTextSize(2);
  
     if ( latransposition > 0 ) {
      canvasBIG.print("+");
    }
     if ( latransposition == 0 ) {
      canvasBIG.setCursor(8,16);
    }
    canvasBIG.print(latransposition);
    dodisplay();
  
}

void doShiftersynth(){
  //Serial.println("synth Shifterd");
 if (sublevels[3]-16>0) {
  shiftnotes1left(abs(sublevels[3]-16));
       
    }
    if (sublevels[3]-16<0){
 
         shiftnotes1right(abs(sublevels[3]-16)); 
    }
    refreshevented1();
  } 
  
void showShifterdisplays() {
    display.clearDisplay();
   canvastitle.fillScreen(SSD1306_BLACK);
   canvasBIG.fillScreen(SSD1306_BLACK);
       canvastitle.setCursor(0,0);
    canvastitle.setTextSize(2);
    canvastitle.print((char*)optionspatternlabels[sublevels[2]]);
  
    int latransposition ;
    latransposition = 16-sublevels[3];
    canvasBIG.setCursor(0,16);
    canvasBIG.setTextSize(2);
  
     if ( latransposition > 0 ) {
      canvasBIG.print("+");
    }
     if ( latransposition == 0 ) {
      canvasBIG.setCursor(8,16);
    }
    canvasBIG.print(latransposition);
    dodisplay();
  
}

void showlestargetdisplays() {
  display.clearDisplay();
   canvastitle.fillScreen(SSD1306_BLACK);
   canvasBIG.fillScreen(SSD1306_BLACK);
       canvastitle.setCursor(0,0);
    canvastitle.setTextSize(2);
    canvastitle.print((char*)optionspatternlabels[sublevels[2]]);
  
    int latransposition ;
    latransposition = sublevels[3];
    canvasBIG.setCursor(0,16);
    canvasBIG.setTextSize(2);
  switch ( latransposition ) {
    case 0 :
    canvasBIG.print("All");
  
    targetNOsampler = 0;
    targetNOsynth = 0 ;
    targetNOcc = 0 ;
    break;
     case 1 :
     //canvasBIG.setTextSize(1);
      canvasBIG.print("Synth");
     targetNOsampler = 1;
    targetNOsynth = 0 ;
    targetNOcc = 1 ;
    break;
    case 2 :
     canvasBIG.print("Sampler");
    targetNOsampler = 0;
    targetNOsynth = 1 ;
    targetNOcc = 1 ;
    break;
     case 3 :
      canvasBIG.print("CCs");
     targetNOsampler = 1;
    targetNOsynth = 1 ;
    targetNOcc = 0 ;
    break;
    case 4 :
    canvasBIG.println("Synth");
    canvasBIG.print(" + CCs");
    
    targetNOsampler = 1;
    targetNOsynth = 0 ;
    targetNOcc = 0 ;
    break;
     case 5 :
       canvasBIG.println("Sampler");
    canvasBIG.print(" + CCs");
     targetNOsampler = 0;
    targetNOsynth = 1 ;
    targetNOcc = 0 ;
    break;
    case 6 :
       canvasBIG.println("Sampler");
    canvasBIG.print("Synth");
     targetNOsampler = 0;
    targetNOsynth = 0 ;
    targetNOcc = 1 ;
    break;
    default:
    break;
  }

    //canvasBIG.print(latransposition);
    dodisplay();
  
}
void optionspatterndisplays() {
    display.clearDisplay();
   canvastitle.fillScreen(SSD1306_BLACK);
   canvasBIG.fillScreen(SSD1306_BLACK);
    canvastitle.setCursor(0,0);
    canvastitle.setTextSize(2);
    canvastitle.print((char*)optionspatternlabels[sublevels[2]]);
    if (sublevels[2] == 4 ) {
      canvasBIG.setCursor(0,16);
      canvasBIG.setTextSize(2);
      if (interpolOn) {
      canvasBIG.print("On");
      } else {
         canvasBIG.print("Off");
      }
    }
    dodisplay();
  
}
void displaythelistofpatterns() {
   int startx = 80;
  int starty = 16;
  // char* textinz = (char*)lesfiles[sublevels[3]].name() ;

    canvastitle.fillScreen(SSD1306_BLACK);
    canvastitle.setCursor(startx,0);
    canvastitle.setTextSize(1);

   
    
    if ( sublevels[2] == numberofPatternfiles && sublevels[1] == 1 ) {
             
    canvastitle.print("New()");
    } else {
     canvastitle.print((char*)Patternfilebase[sublevels[2]]);
    }
    canvastitle.setTextSize(1);
    canvasBIG.setTextSize(1);
    canvasBIG.fillScreen(SSD1306_BLACK);
     if ( sublevels[2] == numberofPatternfiles ) {
      for (int filer = 0 ; filer < sublevels[2]-1  ; filer ++) {
        canvasBIG.setCursor(startx,(10*(numberofPatternfiles-sublevels[2]))+16+((filer)*10));
        canvasBIG.println((char*)Patternfilebase[filer]);
      }
        } else {
        for (int filer = 0 ; filer < numberofPatternfiles-1-(sublevels[2]) ; filer ++) {
      canvasBIG.setCursor(startx,starty+((filer)*10));
      canvasBIG.println((char*)Patternfilebase[sublevels[2]+1+filer]);
    }
  
    for (int filer = 0 ; filer < sublevels[2]  ; filer ++) {

        canvasBIG.setCursor(startx,(10*(numberofPatternfiles-sublevels[2]))+6+((filer)*10));
        canvasBIG.println((char*)Patternfilebase[filer]);
       }
     } 
   
}

void findnextPatternname() {
   
  if ( patternunites < 9 ) {
    patternunites++;
  } else {
    patternunites = 0 ;
     if ( synsetdizaines < 9 ) {
    patterndizaines++;
  } else {
    patterndizaines = 0;
  }
    
  }
  newpatternpath[16]=patternunites + '0' ;
  newpatternpath[15]=patterndizaines + '0' ;
 // Serial.println((char*)newpatternpath);
  
}

void makenewpatternfilename() {
 // Serial.println((char*)newpatternpath);
    while (SD.exists((char*)newpatternpath)) {
    //  Serial.println((char*)newpatternpath);
  
      findnextPatternname();
    }
}

void writelemidi(byte lefilenu) {

if (lefilenu == numberofPatternfiles) {
  makenewpatternfilename();
  // Serial.println("writing new.");
  myMidiFile = SD.open((char*)newpatternpath, FILE_WRITE);
} else {
  // Serial.println("overwriting.");
if (SD.exists((char*)Patternfilefullpath[lefilenu])) {
  // Serial.println("removing existing.");
  SD.remove((char*)Patternfilefullpath[lefilenu]);
  // Serial.println("removed.");
  }

  myMidiFile = SD.open((char*)Patternfilefullpath[lefilenu], FILE_WRITE);
} 
  // if the file opened okay, write to it:
  if (SD.exists((char*)Patternfilefullpath[lefilenu]) ) {
    writemidiinfo();
     myMidiFile.close();
   // Serial.println("wrote.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening");
    Serial.println((char*)newpatternpath);
    
    
  }
myMidiFile.close();
dopatternfileslist();
}

void metronomer() {
  if ( (tickposition == 0) || (tickposition == 16) ){
      metrodrum1.frequency(540);
      metrodrum1.noteOn();
//printpattern();
      
  } if  ( (tickposition == 4) || (tickposition == 8) || (tickposition == 12) || (tickposition == 20) || (tickposition == 24) || (tickposition == 28)) {
   
         // printpattern();
      metrodrum1.frequency(440);
      metrodrum1.noteOn();
  }
  

}

void stopallnotes(){
  for (int i=0; i<nombreofliners; i++) {
    //stoplengthmesure(i);
    if(notesOn[i] != 0) {
       MaNoteOff(synthmidichannel, notesOn[i], 0); 
    }
  }
  
}


void stopticker() {

  stoptick = 1;
   recordCC = 0;
    overdubmidi = 0;
    //if (patrecord) {    
        //computelenghtmesureoffline();
    patternOn = 0 ;
    patrecord = 0 ;
  //tickposition = 0 ;
}
void startticker() {
  if (!externalticker) {
  metro0.reset();
  }
  stoptick=0;
  patternOn = 1 ;
}

void setbpms() {
   
//  BPMs = (60000.0/millitickinterval)/4.0 ;
    BPMs = 15000.0/millitickinterval ;

   metro0.interval(millitickinterval) ;
  
  metro303.interval(millitickinterval/5);
  metro303.reset();
  metro0.reset();
  //refresh display
  //lemenuroot();
}

void dotapaverage() {
  int tottaptime = 0;
  for (int i=0; i < numberoftaps; i++ ) {
    tottaptime +=  (tapstime[i] - starttaptime);
  }
  tapaverage = tottaptime / numberoftaps ;
  millitickinterval = round(tapaverage/10.0) ;
  //printf("%0.1f", num);

  setbpms();
  
  Serial.println(BPMs,1);
}
void inittapstime() {
  for (int i=0; i < 5; i++ ) {
    tapstime[i] = 0 ;
  }
}
void starttaptap () {
    tapstarted = 1 ;
   starttaptime = millis() ;
   
}
void resettaptap() {
 
    tapstarted = 0 ;
    numberoftaps = 0 ;
    inittapstime();
}
void taptap() {
  Serial.println("tap");
  if ( !tapstarted ) {
    starttaptap();
  } else {
    tapstime[numberoftaps] = millis() ;
    numberoftaps++ ;
  }

  if ( millis() - starttaptime > 2000 || numberoftaps >= 4 ) {
    dotapaverage();
    resettaptap() ;
    
  }
}

void showplayheadpattern() {
  canvasBIG.drawLine(tickposition*4, 16, tickposition*4, 64, SSD1306_WHITE);
}


void event1offs(int linei) {
 // Serial.println("event1 noteoff");
          lineroff(nombreofliners-1-linei,event1notesOff[linei][tickposition][1]);
}
void doesccgonnachangeinpatfromnow() {
  //guess future lerping duration -> scan all pbars as well
 // howmanyactiveccnow = 0 ;
// int templeng ;

  //if (tickposition < pbars - 1 ) {
  for (int i = 0 ; i < 128 ; i++ ) {
   //activateinterpolatecc[i] = 0;
   
   if ( event1controllers[i][tickposition] != 128 ) {
    if (!noCCrecordlist(i) ) {
    if ( !(interpolOn && !patrecord )) {
          activateinterpolatecc[i] = 0; 
          justdoaCChange(i) ; 
         
          } else {
    
    
             
                scanfornextcc(i);
                if (Ccinterpolengh[i][1] == pbars)  {
                  activateinterpolatecc[i] = 0; 
                  justdoaCChange(i) ; 
                 }
               }
             }
     }
           
 }

}
void event1(int linei) {
 // Serial.println("event1 ");

    if ( event1notes1[linei][tickposition][1] != 0 ){
      if (notesOn[linei] == 0 ){
   // lineron(nombreofliners-1-linei, synthmidichannel, event1notes1[linei][tickposition][1], event1notes1[linei][tickposition][2]) ;
     lineron(nombreofliners-1-linei, synthmidichannel, event1notes1[linei][tickposition][1], event1notes1[linei][tickposition][2]) ;
      } 
      //else {
     // MaNoteOn((byte)synthmidichannel, event1notes1[linei][tickposition][1], event1notes1[linei][tickposition][2]) ;
   // }
    }
}

void event2(int linei) {
 // Serial.println("event2 ");
  //note
 
    if (  event2notes1[linei][tickposition][1] != 0 ) {
//        event2lineplayingfrom[linei][0]= event2notes1[linei][tickposition][1];
   //channel
  //event2lineplayingfrom[linei][1]= event2notes1[linei][tickposition][0];
       if ( Sampleassigned[event2notes1[linei][tickposition][1]] != 0 && ( (samplermidichannel == 0) || ((byte)samplermidichannel == event2notes1[linei][tickposition][0]) ) ) {
        initiatesamplerline(nombreofSamplerliners-1-linei,(byte)samplermidichannel, event2notes1[linei][tickposition][1], event2notes1[linei][tickposition][2] ) ;
 // MaNoteOn( (byte)samplermidichannel, event2notes1[linei][tickposition][1], event2notes1[linei][tickposition][2]) ;
       }
    }
}
void midifileliner(int liner, int ticker ) {
  
          
  myMidiFile.print(latimeline);
  myMidiFile.print(" On ch=");
  int leintc = (int)event1notes1[liner][ticker][0] ;
     myMidiFile.print(leintc);
     myMidiFile.print(" n=");
       int leintn = (int)event1notes1[liner][ticker][1] ;
        myMidiFile.print(leintn);
        myMidiFile.print(" v=");
          int leintv = (int)event1notes1[liner][ticker][2] ;
         myMidiFile.print(leintv);
          myMidiFile.print("\n");
}
void midifilelinerSampler(int liner, int ticker ) {
  
          
  myMidiFile.print(latimeline);
  myMidiFile.print(" On ch=");
  int leintc = (int)event2notes1[liner][ticker][0] ;
     myMidiFile.print(leintc);
     myMidiFile.print(" n=");
       int leintn = (int)event2notes1[liner][ticker][1] ;
        myMidiFile.print(leintn);
        myMidiFile.print(" v=");
          int leintv = (int)event2notes1[liner][ticker][2] ;
         myMidiFile.print(leintv);
          myMidiFile.print("\n");
}

void midifilelinerOff(int liner,int ticker ) {
  myMidiFile.print(latimeline);
  myMidiFile.print(" Off ch=");
   int leintc = (int)event1notesOff[liner][ticker][0] ;
     myMidiFile.print(leintc);
     myMidiFile.print(" n=");
       int leintn = (int)event1notesOff[liner][ticker][1];
        myMidiFile.print(leintn);
        myMidiFile.print(" v=");
          int leintv =  (int)event1notesOff[liner][ticker][2];
         myMidiFile.print(leintv);
          myMidiFile.print("\n");
}
void midifileCC(int lecc,int ticker ) {
  myMidiFile.print(latimeline);
  myMidiFile.print(" Par ch=");
   int leintc = (int)synthmidichannel ;
     myMidiFile.print(leintc);
     myMidiFile.print(" c=");
       int leintn = lecc;
        myMidiFile.print(leintn);
        myMidiFile.print(" v=");
          int leintv =  (int)event1controllers[lecc][ticker];
         myMidiFile.print(leintv);
          myMidiFile.print("\n");
}

void writemidiinfo () {
  latimeline = 0 ;
    //latimelineshifter = ((60000/19200)*pbars) ;
 // (60.0/BPMs)*1000)*pbars) = 1 bar millis 92 original
   myMidiFile.print("MFile 0 1 19200\nMTrk\n");
  //for (int i = 0 ; i<5 ; i++ ) {

    for (int t=0; t<pbars ; t++ ) {
      
      latimeline = (3125*t) ;
      for (int j=0; j<nombreofliners ; j++ ) {
      if ( event1notesOff[j][t][1] != 0 ) {
          midifilelinerOff(j,t);
        }
        
      }
      for (int j=0; j<nombreofliners ; j++ ) {
        if ( event1notes1[j][t][1] != 0) {
          midifileliner(j,t);
        }
      }
      for (int j=0; j<nombreofSamplerliners ; j++ ) {
        if ( event2notes1[j][t][1] != 0) {
          midifilelinerSampler(j,t);
        }
      }

      for (int j=0; j<128 ; j++ ) {
        if ( event1controllers[j][t] != 128) {
          midifileCC(j,t);
        }
      }
   
    }
    
  //}
  myMidiFile.print(100000);
  myMidiFile.print(" Meta TrkEnd\n");
  myMidiFile.print("TrkEnd\n");
  
  

}


int print2digits(int number) {
  if (number >= 0 && number < 10) {
    //Serial.write('0');
  }
  return number ;
}



void drawplaybar() {
  
   display.clearDisplay();
  int xoffset = cellsizer*(tickposition)+startx-1 ;
   canvastitle.fillScreen(SSD1306_BLACK);
   canvastitle.fillTriangle(
      xoffset , 0,
      xoffset+10, 0,
      xoffset+5, 10, SSD1306_WHITE);

  dodisplay();
}

void drawguides(){
   int cellsizer = 3 ;
 int celltall = 9 ;
 int startx = 0;
 int starty = 16 ;
  for (int filer = 0 ; filer < pbars; filer++) {
  canvasBIG.drawLine(startx+(cellsizer*4)*filer, starty-1, cellsizer+startx+(cellsizer*4)*filer, starty-1, SSD1306_WHITE); 
   canvasBIG.drawLine(startx+(cellsizer*4)*filer, (4*celltall)+starty+1, cellsizer+startx+(cellsizer*4)*filer, (4*celltall)+starty+1, SSD1306_WHITE); 
  }
}
void drawpatterngrid (int nombrelines, int collumns, int startx, int starty) {
  
celltall= round((63 - starty)/nombrelines );
cellsizer = round((127 - startx)/collumns );
int listoffsetter ;
 for (int filer = 0 ; filer < nombrelines+1; filer++) {
     listoffsetter = starty+((filer)*celltall);
  //horizontallines
      canvasBIG.drawLine(startx, listoffsetter, startx+cellsizer*pbars, listoffsetter, SSD1306_WHITE);
  }
  for (int filer = 0 ; filer < pbars+1; filer++) {
    //verticalbars
  canvasBIG.drawLine(startx+cellsizer*filer, starty+1, startx+cellsizer*filer, (4*celltall)+starty, SSD1306_WHITE); 
  }
  
   
}
//void notesshow(int liner) {
//    canvasBIG.fillScreen(SSD1306_BLACK);
//  short linersizehold ;
//  int octavestart = 60 ;
//  int yoffsetter ;
//  byte note0 ;
//  int velocitall ;
//  int listoffsetter ;
//  //Why ???
// int filer = 2 ;
//      pianobar();  
//    for (int i = 0; i < pbars; i++ ) {
//      note0 = event1notes1[liner][i][1] ;
//      yoffsetter = ((int)note0) - octavestart;
//     
//      listoffsetter = starty+(yoffsetter*celltall);
//         if (note0) {
//           //Serial.println(yoffsetter);
//               linersizehold = length0pbars[liner][i]*cellsizer ;
//              //(((60.0/BPMs)*1000)*pbars))*128) ;
//                 velocitall = (int)event1notes1[liner][i][2] ;
//               // Serial.println(velocitall);
//                canvasBIG.fillRect(startx+cellsizer*i, starty+celltall*yoffsetter+(celltall - round((celltall-1)*(velocitall/127.0))), linersizehold, round((celltall-1)*(velocitall/127.0)), SSD1306_WHITE); 
//                
//             }
//           }
//           
//}
void pianobar() {
  startx = 0 ;
  starty = 16 ;
  cellsizer = 8 ;
  celltall = 4 ;
  canvasBIG.fillRect(startx,starty,cellsizer,celltall,SSD1306_WHITE);
   canvasBIG.fillRect(startx,starty+celltall,8,celltall,SSD1306_BLACK);
  canvasBIG.fillRect(0,starty+celltall*2,8,celltall,SSD1306_WHITE);
   canvasBIG.fillRect(0,starty+celltall*3,8,celltall,SSD1306_BLACK);
  canvasBIG.fillRect(0,starty+celltall*4,8,celltall,SSD1306_WHITE);
   
  canvasBIG.fillRect(0,starty+celltall*5,8,celltall,SSD1306_WHITE);
   canvasBIG.fillRect(0,starty+celltall*6,8,celltall,SSD1306_BLACK);
  canvasBIG.fillRect(0,starty+celltall*7,8,celltall,SSD1306_WHITE);
   canvasBIG.fillRect(0,starty+celltall*8,8,celltall,SSD1306_BLACK);
  canvasBIG.fillRect(0,starty+celltall*9,8,celltall,SSD1306_WHITE);
   canvasBIG.fillRect(0,starty+celltall*10,8,celltall,SSD1306_BLACK);
  canvasBIG.fillRect(0,starty+celltall*11,8,celltall,SSD1306_WHITE);
}

void doshownotelineB() {
//Serial.print("shownoteline");
     cellsizer = 4;
    celltall = 4 ;
    startx = 0;
    starty = 16 ;
    int lenghtofthenote = 4;
    int decnote ;
     int listoffsetter ;
     int linersizehold ;
    int linern = sublevels[navlevelpatedit+1];
    startingnoteline = sublevels[navlevelpatedit+2] ;
    byte note0 ;
  canvasBIG.setCursor(0,0);
  canvasBIG.print("Note = ");
  canvasBIG.print(sublevels[navlevelpatedit+2] );
  canvasBIG.print(" Pos = ");
  canvasBIG.print( sublevels[navlevelpatedit+3]);
    for (int notelines = startingnoteline ; notelines > startingnoteline -12 ; notelines--) {
      for (int i = 0; i< pbars; i++ ) {
     
        note0 = event2notes1[linern][i][1] ;
        decnote = (int)note0;
 
          if ( decnote == notelines && note0 != 0 ) {
             //linersizehold = ((length1notes1[linern][i]/(((60.0/BPMs)*1000)*pbars))*128) ;
            
              //lenghtofthenote = length2pbars[linern][i];
            
              if (lenghtofthenote < 4) {
                lenghtofthenote = 4 ;
              }
              listoffsetter = starty+(4*(startingnoteline-notelines))  ;
                 canvasBIG.fillRect(startx+cellsizer*i, listoffsetter, lenghtofthenote, celltall, SSD1306_WHITE); 
              canvasBIG.drawLine(startx+cellsizer*i, listoffsetter,startx+cellsizer*i, listoffsetter + celltall, SSD1306_BLACK);
            }
         }
      }
   
}
void doshownoteline() {
//Serial.print("shownoteline");
  // some notes not showing check lenght note computation -----------------------
  
  //only once, move elsewhere
    //int displayedstart = 60 ;
    //navrange = 128-1 ;
    cellsizer = 4;
    celltall = 4 ;
    startx = 0;
    starty = 16 ;
    int lenghtofthenote = 4;
    int decnote ;
     //int linersizehold ;
    int linern = sublevels[navlevelpatedit+1];
  
    startingnoteline = sublevels[navlevelpatedit+2] ;
      //if selector pos > displayedstart + 12 
    //display 12 notes range
    // blocks pos y = truenote
    byte note0 ;
canvasBIG.setCursor(0,0);
  canvasBIG.print("Note = ");
  canvasBIG.print(sublevels[navlevelpatedit+2] );
  canvasBIG.print(" Pos = ");
  canvasBIG.print( sublevels[navlevelpatedit+3]);
    for (int notelines = startingnoteline ; notelines > startingnoteline -12 ; notelines--) {
      for (int i = 0; i< pbars; i++ ) {
       
        note0 = event1notes1[linern][i][1] ;
        decnote = (int)note0;

          if ( decnote == notelines && note0 != 0 ) {
     
              lenghtofthenote = length0pbars[linern][i];
            
              if (lenghtofthenote < 4) {
                lenghtofthenote = 4 ;
              }
             int listoffsetter = starty+(4*(startingnoteline-notelines))  ;

              canvasBIG.fillRect(startx+cellsizer*i, listoffsetter, lenghtofthenote, celltall, SSD1306_WHITE); 
              canvasBIG.drawLine(startx+cellsizer*i, listoffsetter,startx+cellsizer*i, listoffsetter + celltall, SSD1306_BLACK);
            }
         }
      }
   
}
void doshownoteline2() {
  // Serial.println("doshownoteline2 - temp notes during edit");
    cellsizer = 4;
    celltall = 4 ;
    startx = 0;
    starty = 16 ;
    int lenghtofthenote = 4;
    int decnote ;
     int listoffsetter;
    // int linersizehold ;
    int linern = sublevels[navlevelpatedit+1];
    startingnoteline = sublevels[navlevelpatedit+2] ;
canvasBIG.setCursor(0,0);
  canvasBIG.print("Note = ");
  canvasBIG.print(sublevels[navlevelpatedit+2] );
  canvasBIG.print(" Pos = ");
  canvasBIG.print( sublevels[navlevelpatedit+4]);
    byte note0 ;
   for (int notelines = startingnoteline ; notelines > startingnoteline -12 ; notelines--) {
      for (int i = 0; i< pbars; i++ ) {
        
        note0 = tempevent1notes1[linern][i][1] ;
              
        decnote = (int)note0;
          if ( decnote == notelines && note0 != 0 ) {
               
             lenghtofthenote = templength0pbars[linern][i];
           
             if (lenghtofthenote < 4) {
                lenghtofthenote = 4 ;
              }
              listoffsetter = starty+(4*(startingnoteline-notelines))  ;
              canvasBIG.fillRect(startx+cellsizer*i, listoffsetter, lenghtofthenote, celltall, SSD1306_WHITE);
              canvasBIG.drawLine(startx+cellsizer*i, listoffsetter,startx+cellsizer*i, listoffsetter + celltall, SSD1306_BLACK);
            }
         }
      }
   
}
void doshownoteline2B() {
  // Serial.println("doshownoteline2 - temp notes during edit");
    cellsizer = 4;
    celltall = 4 ;
    startx = 0;
    starty = 16 ;
    int lenghtofthenote = 4;
    int decnote ;
    int listoffsetter ;
    // int linersizehold ;
    int linern = sublevels[navlevelpatedit+1];
    startingnoteline = sublevels[navlevelpatedit+2] ;
  canvasBIG.setCursor(0,0);
  canvasBIG.print("Note = ");
  canvasBIG.print(sublevels[navlevelpatedit+2] );
  canvasBIG.print(" Pos = ");
  canvasBIG.print( sublevels[navlevelpatedit+4]);
    byte note0 ;
   for (int notelines = startingnoteline ; notelines > startingnoteline -12 ; notelines--) {
      for (int i = 0; i< pbars; i++ ) {
      
        note0 = tempevent2notes1[linern][i][1] ;
        
        
        decnote = (int)note0;
          if ( decnote == notelines && note0 != 0 ) {
                
             //lenghtofthenote = templength2pbars[linern][i];
                        
              if (lenghtofthenote < 4) {
                lenghtofthenote = 4 ;
              }
              listoffsetter = starty+(4*(startingnoteline-notelines))  ;
              canvasBIG.fillRect(startx+cellsizer*i, listoffsetter, lenghtofthenote, celltall, SSD1306_WHITE);
              canvasBIG.drawLine(startx+cellsizer*i, listoffsetter,startx+cellsizer*i, listoffsetter + celltall, SSD1306_BLACK);
            }
         }
      }
   
}
void drawnoteRow(){
 // Serial.println("drawing PatternRow");
  //rows of audio sources : synth, sampler, others
  //listoffsetter
   // display.fillRect(startx, starty+sublevels[navlevelpatedit+2]*celltall, (128-startx), celltall, SSD1306_WHITE); 
    canvasBIG.drawLine(0, starty+2, 127, starty+2, SSD1306_INVERSE); 
}
void drawPatternRow(){
 // Serial.println("drawing PatternRow");
  //rows of audio sources : synth, sampler, others
    canvasBIG.drawLine(startx, starty+sublevels[navlevelpatedit]*celltall + 3, (128-startx),  starty+sublevels[navlevelpatedit]*celltall + 3, SSD1306_WHITE); 
}
void drawEventRow(){
  //Serial.println("drawing EventRow");
  //row of events (liners) on audio source (patternrow)
   canvasBIG.drawLine(0, starty+sublevels[navlevelpatedit+1]*celltall + 3, 128, starty+sublevels[navlevelpatedit+1]*celltall + 3, SSD1306_INVERSE); 
}
void drawsamplerEventRow(){
  //Serial.println("drawing EventRow");
  //row of events (liners) on audio source (patternrow)
   canvasBIG.drawLine(0, starty+(sublevels[navlevelpatedit+1]-samplelinerspage)*celltall + 3, 128, starty+(sublevels[navlevelpatedit+1]-samplelinerspage)*celltall + 3, SSD1306_INVERSE); 
}
// check  starty+celltall*sublevels[navlevelpatedit+1], was = starty+celltall*sublevels[navlevelpatedit

//nobody calls them two
void drawPatternSlice(){
 // Serial.println("drawing PatternSlice");
  //display.fillRect(startx+cellsizer*(int(sublevels[navlevelpatedit+1])), starty+celltall*sublevels[navlevelpatedit+1], startx, celltall+1, SSD1306_INVERSE); 
}

void showblocksofevent() {
    cellsizer = 4;
    celltall = 8 ;
    startx = 0;
    starty = 0 ;
    for (int liner = 0 ; liner < nombreofliners ; liner++) {
     for (int i = 0; i<pbars; i++ ) {           
         if (event1notes1[liner][i][1] != 0 ) {
             canvasBIG.fillRect(startx+cellsizer*i+1, starty+(celltall*liner)+1, cellsizer-2, celltall-2, SSD1306_INVERSE); 
              }           
          }
       }
}
void showblocksofevent2() {
    cellsizer = 4;
    celltall = 8 ;
    startx = 0;
    starty = 16 ;
    for (int liner = 0 + samplelinerspage ; liner < 6+samplelinerspage ; liner++) {
     for (int i = 0; i<pbars; i++ ) {           
         if (event2notes1[liner][i][1] != 0 ) {
             canvasBIG.fillRect(startx+cellsizer*i+1, starty+(celltall*(liner-samplelinerspage))+1, cellsizer-2, celltall-2, SSD1306_INVERSE); 
              }           
          }
       }
}

void clearevented0(int lapatline) {
  
    for (int j = 0 ; j < pbars; j++) {
      evented1[lapatline][j] = false ;
    }
 
    
}

void refreshevented1() {
   clearevented0(0);
  for (int linerrd = 0 ; linerrd < nombreofliners; linerrd++) {
       
    for (int i = 0 ; i < pbars; i++) {
       
      if (event1notes1[linerrd][i][1] != 0 ) {
      evented1[0][i] = true ;
    }
  }
}
}
void refreshevented2() {
   clearevented0(1);
  for (int linerrd = 0 ; linerrd < nombreofSamplerliners; linerrd++) {
       
    for (int i = 0 ; i < pbars; i++) {
       
      if (event2notes1[linerrd][i][1] != 0 ) {
      evented1[1][i] = true ;
    }
  }
}
}
void dolistpatternlineblocks() {
    cellsizer = 4;
    celltall = 8 ;
    startx = 0;
    starty = 16 ;
    
    for (int lapatline = 0 ; lapatline < patternlines; lapatline++) {
      int listoffsetter = starty+((lapatline)*celltall);
    for (int i = 0; i<pbars; i++ ) {
      if (lapatline == 0 ){
        //Serial.println(evented1[lapatline][i]);
      }
         if (evented1[lapatline][i] ) {
                    canvasBIG.fillRect(startx+cellsizer*i+1, starty+(8*lapatline)+1, cellsizer-2, celltall-2, SSD1306_INVERSE); 
                
             }
           }
      }
   
}
int getstartingnoteline() {
   int averagenoteevent = 0;
 int nombrofnoteonliner = 0 ;
   //sublevels[navlevelpatedit+2] = 60 ;
   for (int ni = 0 ; ni < nombreofliners ; ni ++ ) {
    int decednote = event1notes1[sublevels[navlevelpatedit+1]][ni][1] ;
    if (decednote != 0 ) {
     averagenoteevent = averagenoteevent + decednote;
     nombrofnoteonliner++;
     }
   }
   if ( nombrofnoteonliner != 0 ) {
   startingnoteline = round(averagenoteevent / nombrofnoteonliner)+6  ;
   
    //display
   } else {
    startingnoteline = 70 ;
    
   }
   return startingnoteline;
}
int getstartingnoteline2() {
   int averagenoteevent = 0;
 int nombrofnoteonliner = 0 ;
   //sublevels[navlevelpatedit+2] = 60 ;
   for (int ni = 0 ; ni < nombreofSamplerliners ; ni ++ ) {
    int decednote = event2notes1[sublevels[navlevelpatedit+1]][ni][1] ;
    if (decednote != 0 ) {
     averagenoteevent = averagenoteevent + decednote;
     nombrofnoteonliner++;
     }
   }
   if ( nombrofnoteonliner != 0 ) {
   startingnoteline = round(averagenoteevent / nombrofnoteonliner)+6  ;
   
    //display
   } else {
    startingnoteline = 70 ;
    
   }
   return startingnoteline;
}

void drawsequencer() {
 
    if (patternOn) {
//    display.clearDisplay();
    dodisplayplayhead();
//    canvasBIG.drawBitmap(0, 0, canvasBIG2.getBuffer(), 128, 64, SSD1306_WHITE);
//    display.display();
    //dodisplayplathead();
   } else {
  cellsizer = 8*(16/pbars) ;
    celltall = 8 ;
    startx = 0;
    starty = 16 ;
    navrange = patternlines-1 ;
   canvastitle.fillScreen(SSD1306_BLACK);
  canvasBIG.fillScreen(SSD1306_BLACK);
  //dodisplay();
  display.clearDisplay();
  
 if (navlevel == navlevelpatedit) {
  //pattern lines : Synth, Sampler, Audio in ?
  
        //canvasBIG.fillScreen(SSD1306_BLACK);
        //fill rect line
       // display.clearDisplay();
         drawPatternRow();
        //display.display();
        dolistpatternlineblocks();
        display.setCursor(0,0);
        if (sublevels[navlevelpatedit] == 0 ) {
          display.print("Synth");
        }
        if (sublevels[navlevelpatedit] == 1 ) {
          display.print("Sampler");
        }
        
        
       // setlebuffer();
        //display.display();
        //do display twice to allow invert color
      }
  if (sublevels[navlevelpatedit] == 0) {
  event1cells();
  }
if (sublevels[navlevelpatedit] == 1) {
  event2cells();
}
    //showplayheadpattern() ;
        dodisplay2();
    //setlebuffer();
    //getledisplaybuffer();
   }
}



void event2cells() {
  if (navlevel == navlevelpatedit+1 ) {
    patedit1B();
  }


  if (navlevel == navlevelpatedit+2 ) {
    patedit2B();
   }

   if (navlevel == navlevelpatedit+3 ) {
    patedit3B();
     previousnavlevel = navlevel ;
   }
    if (navlevel == navlevelpatedit+4 ) {
      if (previousnavlevel != navlevel) {
     Serial.println("preview!");
         initiatesamplerline(15 ,samplermidichannel, sublevels[navlevelpatedit+2], byte(mixlevelsM[2]*127)) ;
         previousnavlevel = navlevel ;
    }
      
   patedit4B();
  }
     if (navlevel >= navlevelpatedit+5 ) {
       previousnavlevel = navlevel ;
      patedit5B();
      
   }
}

void event1cells() {
    if (navlevel == navlevelpatedit+1 ) {
    patedit1();
  }
  
if (navlevel == navlevelpatedit+2 ) {
    patedit2();
   }
   if (navlevel == navlevelpatedit+3 ) {
    patedit3();
     previousnavlevel = navlevel ;
   }
     
   if (navlevel == navlevelpatedit+4 ) {
    if (previousnavlevel != navlevel) {
     Serial.println("preview!");
         initiateasynthliner(sublevels[navlevelpatedit+2], byte(mixlevelsM[1]*127)) ;
         delay(300);
         shutlineroff( sublevels[navlevelpatedit+2]) ;
         previousnavlevel = navlevel ;
    }
   patedit4();
   
  }
  
   if (navlevel >= navlevelpatedit+5 ) {
      patedit5();
       previousnavlevel = navlevel ;
   }
}
void patedit1() {
      //liners
     display.clearDisplay();
    navrange = nombreofliners-1 ;
      
  //drawguides();
  //if ( sublevels[navlevelpatedit] == 0 ) {
    showblocksofevent();
 // }
//if ( sublevels[navlevelpatedit] == 1 ) {
//  showblocksofevent2();
//} 

  drawEventRow(); 
  display.display();

   dodisplay(); 
   sublevels[navlevelpatedit+2] = getstartingnoteline() ;
}
void patedit1B() {
  
   if (sublevels[navlevelpatedit+1] > 3 && samplelinerspage < 16 ) {
    samplelinerspage = sublevels[navlevelpatedit+1] - 3 ;
      Serial.println(samplelinerspage);
  } else {
    samplelinerspage = 0 ;
  }
     display.clearDisplay();
     canvastitle.setCursor(0,0);
     canvastitle.setTextSize(2);
     canvastitle.print("Track ");
     canvastitle.print(sublevels[navlevelpatedit+1]+1);
     
    navrange = nombreofSamplerliners-1 ;
 showblocksofevent2();
//samplelinerspage
  drawsamplerEventRow(); 
  display.display();

   dodisplay(); 
   sublevels[navlevelpatedit+2] = getstartingnoteline2() ;
  
}
void patedit2() {
  
    //notes of said liner
     display.clearDisplay();
    navrange = 127 ;
        // some notes not showing checl lenght note computation
    doshownoteline();
    drawnoteRow();
     display.display();
      sublevels[navlevelpatedit+3] = tickposition ;
}
void patedit2B() {
  
    //notes of said liner
     display.clearDisplay();
    navrange = 127 ;
        // some notes not showing checl lenght note computation
    doshownotelineB();
    drawnoteRow();
     display.display();
      sublevels[navlevelpatedit+3] = tickposition ;
}
void patedit3() {
  // Serial.println("navlevelpatedit+3");
     display.clearDisplay();
    navrange = 31 ;

    doshownoteline();
    drawnoteRow();
    drawCursorCol();
     display.display();
     sublevels[navlevelpatedit+4] = sublevels[navlevelpatedit+3] ;
     duplicatelenghofnotestarray();
     duplicateevent1();
}
void patedit3B() {
  // Serial.println("navlevelpatedit+3B");
     display.clearDisplay();
    navrange = 31 ;

    doshownotelineB();
    drawnoteRow();
    drawCursorCol();
     display.display();
     sublevels[navlevelpatedit+4] = sublevels[navlevelpatedit+3] ;
    
     duplicateevent2();
}
void killnextnoteoff (byte liner, byte notee , byte fromi ) {
  for (int i = fromi+1 ; i < pbars ; i++ ) {
    if ( event1notesOff[liner][i][1] == notee ) {
      event1notesOff[liner][i][1] = 0 ;
      return;
    }
  }
  for (int i = 0 ; i < fromi ; i++ ) {
    if ( event1notesOff[liner][i][1] == notee ) {
      event1notesOff[liner][i][1] = 0 ;
      return;
    }
  }
  
}
void patedit4() {
  
    //clickon liner /note / at tickpos
   
    byte decednote2 =  event1notes1[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]][1] ;
    if ( decednote2 == sublevels[navlevelpatedit+2] && decednote2 != 0 && !addinglenght) {
      // Serial.println("navlevelpatedit+4 deleting note");
     killnextnoteoff(sublevels[navlevelpatedit+1],event1notes1[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]][1], sublevels[navlevelpatedit+3 ]);
      event1notes1[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]][0] = 0 ;
       event1notes1[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]][1] = 0 ;
        event1notes1[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]][2] = 0 ;
        
         returntonav(navlevelpatedit+3) ;
         
             refreshevented1();
             
             //computelenghtmesureoffline();
            
    } else {
     // Serial.println("navlevelpatedit+4 adding lenght");
      addinglenght = 1 ;
    tempevent1notes1[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]][0] = synthmidichannel;
       tempevent1notes1[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]][1] = (byte)sublevels[navlevelpatedit+2] ;
        tempevent1notes1[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]][2] = (byte)64 ;
    //  Serial.print("noteset = ");
    //  Serial.println(sublevels[navlevelpatedit+2]);
      
      navrange = 31 ;
     // Serial.println("addanoteonliner");
      templength0pbars[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]] = (sublevels[navlevelpatedit+4] - sublevels[navlevelpatedit+3])*4;
    
    if ( templength0pbars[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]] < 0 ) {
      templength0pbars[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]] = 4 ;
      }
         refreshevented1();
       
        // initiatesamplerline(15 ,samplermidichannel, sublevels[navlevelpatedit+2], byte(mixlevelsM[0]*127)) ;
         //computelenghtmesureoffline();
         //use an alternate temporary length0pbars if adding lenght is cancelled to avoid skipping noteoff -> make doshownoteline2
         //also eventnotes as they are temp if not validated with a noteoff
        display.clearDisplay();
  doshownoteline2();
    drawnoteRow();
    drawCursorCol2();
    display.display();       //displayPatternmenu();
    } 

}
void patedit4B() {
  
    //clickon liner /note / at tickpos
   
    int decednote2 = event2notes1[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]][1] ;
    if ( decednote2 == sublevels[navlevelpatedit+2] && decednote2 != 0 && !addinglenght) {
      // Serial.println("navlevelpatedit+4 deleting note");
      event2notes1[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]][0] = (byte)samplermidichannel ;
       event2notes1[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]][1] = 0 ;
        event2notes1[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]][2] = 0 ;
         vraipos = sublevels[navlevelpatedit+3] ;
         myEnc.write(vraipos*4);
         navlevel--;
             refreshevented2();
             drawsequencer();
             
    } else {
     // Serial.println("navlevelpatedit+4 adding lenght");
      addinglenght = 1 ;
    tempevent2notes1[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]][0] = (byte)samplermidichannel;
       tempevent2notes1[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]][1] = (byte)sublevels[navlevelpatedit+2] ;
        tempevent2notes1[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]][2] = (byte)64 ;
    //  Serial.print("noteset = ");
     // Serial.println(sublevels[navlevelpatedit+2]);
      
      navrange = 31 ;
     // Serial.println("addanoteonliner");
      //templength2pbars[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]] = (sublevels[navlevelpatedit+4] - sublevels[navlevelpatedit+3])*4;
    
//    if ( templength2pbars[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]] < 0 ) {
//      templength2pbars[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]] = 4 ;
//      }
         refreshevented2();
         
         //use an alternate temporary length0pbars if adding lenght is cancelled to avoid skipping noteoff -> make doshownoteline2
         //also eventnotes as they are temp if not validated with a noteoff
        display.clearDisplay();
  doshownoteline2B();
    drawnoteRow();
    drawCursorCol2();
    display.display();       //displayPatternmenu();
    } 

}
void terminatenotesinbetween() {
  for (int i = sublevels[navlevelpatedit+3]+1 ; i < sublevels[navlevelpatedit+4]; i++) {
    if (  event1notes1[sublevels[navlevelpatedit+1]][i][1] != 0) {
       event1notes1[sublevels[navlevelpatedit+1]][i][1] = 0 ;
    }
    if (  event1notesOff[sublevels[navlevelpatedit+1]][i][1] != 0) {
       event1notesOff[sublevels[navlevelpatedit+1]][i][1] = 0 ;
    }
  }
}
void terminatenextnoteoff(byte liner, byte lanoteoff, byte fromi) {
  
  for ( int i = 0 ; i < pbars ; i++ ) {
    if (!offhasOnbutnototheroff(liner, lanoteoff, fromi)){
      event1notesOff[liner][fromi][1] = 0 ;
    }
  }
}
void patedit5() {
  byte sub1 = sublevels[navlevelpatedit+1] ;
  byte sub2 = sublevels[navlevelpatedit+2];
  byte sub3 = sublevels[navlevelpatedit+3];
  byte sub4 = sublevels[navlevelpatedit+4];
  byte laOffpos ;
        event1notes1[sub1][sub3][0] = synthmidichannel;
       event1notes1[sub1][sub3][1] = sub2 ;
        event1notes1[sub1][sub3][2] = (byte)64 ;
        
    length0pbars[sub1][sub3] = (sub4 - sub3)*4;
    if ( length0pbars[sub1][sub3] < 0 ) {
      length0pbars[sub1][sub3] = 4 ;
      }
       laOffpos = sub3+(length0pbars[sub1][sub3]/4) ;
       if (laOffpos == sub3) {
        laOffpos += 1 ;
       }
       if ( laOffpos > pbars ) {
        laOffpos = laOffpos - pbars ;
       }
      event1notesOff[sub1][laOffpos][0] = synthmidichannel;
      event1notesOff[sub1][laOffpos][1] = sub2 ;
    terminatenotesinbetween();
     //not sure (for orphans but why would there be any?)
     terminateOffz(sub1);
     //just in case
     terminatenextnoteoff(sub1,sub2 ,laOffpos);
      
   // Serial.println("navlevelpatedit+5");
    addinglenght = 0 ;
 returntonav(5);
      refreshevented1();
      //computelenghtmesureoffline();
      displayPatternmenu();
}
void patedit5B() {
        event2notes1[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]][0] = (byte)samplermidichannel;
       event2notes1[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]][1] = (byte)sublevels[navlevelpatedit+2] ;
        event2notes1[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]][2] = (byte)64 ;
        
   // length2pbars[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]] = (sublevels[navlevelpatedit+4] - sublevels[navlevelpatedit+3])*4;
//    if ( length2pbars[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]] < 0 ) {
//      length2pbars[sublevels[navlevelpatedit+1]][sublevels[navlevelpatedit+3]] = 4 ;
//      }
      event2notesOff[sublevels[navlevelpatedit+4]][0] = (byte)samplermidichannel; 
      event2notesOff[sublevels[navlevelpatedit+4]][1] = (byte)sublevels[navlevelpatedit+2] ;
  //  Serial.println("navlevelpatedit+5");
    addinglenght = 0 ;
   returntonav(navlevelpatedit+3);
      refreshevented2();
      
      displayPatternmenu();
}
bool offhasOnbutnototheroff(byte liner, byte lanoteoff, byte fromi) {
  //for (int j = 0 ; j < nombreofliners ; j++ ) {
    for (int i = fromi-1 ; i >= 0  ; i-- ) {
      if (event1notesOff[liner][i][1] == lanoteoff) {
        terminatenextnoteoff(liner, lanoteoff, i);
        
      }
      if (event1notes1[liner][i][1] == lanoteoff) {
        return 1 ;
      }
    }
     for (int i = pbars-1 ; i >= fromi  ; i-- ) {
      if (event1notesOff[liner][i][1] == lanoteoff && i > fromi) {
       return 0 ;
      }
      if (event1notes1[liner][i][1] == lanoteoff) {
        return 1 ;
      }
    }
    return 0 ;
}
void duplicatelenghofnotestarray() {
for (int j = 0 ; j < nombreofliners ; j++ ) {
    for (int i = 0 ; i < pbars  ; i++ ) {
      templength0pbars[j][i] = length0pbars[j][i];
    }
}
}

void duplicateevent1() {
for (int j = 0 ; j < nombreofliners ; j++ ) {
    for (int i = 0 ; i < pbars  ; i++ ) {
       tempevent1notes1[j][i][0] = event1notes1[j][i][0] ;
       tempevent1notes1[j][i][2] = event1notes1[j][i][2] ;
       tempevent1notes1[j][i][1] = event1notes1[j][i][1] ;
    }
}
}
void duplicateevent2() {
for (int j = 0 ; j < nombreofSamplerliners ; j++ ) {
    for (int i = 0 ; i < pbars  ; i++ ) {
       tempevent2notes1[j][i][0] = event2notes1[j][i][0] ;
       tempevent2notes1[j][i][2] = event2notes1[j][i][2] ;
       tempevent2notes1[j][i][1] = event2notes1[j][i][1] ;
    }
}
}

void drawCursorCol() {
int xpos = (sublevels[navlevelpatedit+3]*4)+1 ;
  display.drawLine(xpos, starty, xpos, 64-(starty), SSD1306_INVERSE); 
}

void drawCursorCol2() {
int xpos = (sublevels[navlevelpatedit+4]*4)+1 ;
  display.drawLine(xpos, starty, xpos, 64-(starty), SSD1306_INVERSE); 
}

void dolistPatternsmenu() {
  char patternlistlabels[sizeofpatternlistlabels][12] = {"Edit","Save", "Load", "Copy", "Delete", "Options","Clear","C-Edit"};
    byte startx = 5;
  byte starty = 16;
   char* textin = (char*)patternlistlabels[sublevels[1]] ;
// Serial.println(textin);
    canvastitle.fillScreen(SSD1306_BLACK);
    canvastitle.setCursor(0,0);
    
    canvastitle.setTextSize(2);

    canvastitle.println(textin);

     canvasBIG.setTextSize(1);

      canvasBIG.fillScreen(SSD1306_BLACK);
  
    for (int filer = 0 ; filer < sizeofpatternlistlabels-1 -(sublevels[1]) ; filer ++) {

      canvasBIG.setCursor(startx,starty+((filer)*10));
      canvasBIG.println(patternlistlabels[sublevels[1]+1+filer]);
  }
    for (int filer = 0 ; filer < sublevels[1]  ; filer ++) {

        canvasBIG.setCursor(startx,(10*(sizeofpatternlistlabels-sublevels[1])+6+((filer)*10)));
        canvasBIG.println(patternlistlabels[filer]);
    }

}

void deletepattern(int lapattern) {
  if (SD.exists((const char*)Patternfilefullpath[lapattern])) {
   SD.remove((const char*)Patternfilefullpath[lapattern]);
  }
  dopatternfileslist();
}

void copypattern(int lapattern) {
//Serial.println("trying to copy");
     File originpatternfile = SD.open((const char*)Patternfilefullpath[lapattern]);
     makenewpatternfilename();
 
 File mypatterntxtFile = SD.open((char*)newpatternpath, FILE_WRITE);
   size_t n; 
  uint8_t buf[64];
 while ((n = originpatternfile.read(buf, sizeof(buf))) > 0) {
    mypatterntxtFile.write(buf, n);
  }
 // }
  
  originpatternfile.close();
  mypatterntxtFile.close();
  dopatternfileslist();
 // lepatternfile.close();
 // lepatterndir.close();
}

void dosavepattern() {
  canvastitle.fillScreen(SSD1306_BLACK);
  
}

void startparsinginfos() {
  patterninparse=1 ;
}
//    latimelineshifter = ((60000/19200)*pbars) ;
// (60.0/BPMs)*1000)*pbars) = 1 bar millis

void parsepattern(int lapatterne) {
   byte laccnote ;
   int intjustparsed ;
    char charjustparsed[2] ;
    byte parsedchannel ;
//Serial.println("Loading attempt");
  int letimescaler = 3125 ;
   File lepatternfile = SD.open((char*)Patternfilefullpath[lapatterne]);
   
 
 //Serial.println(lepatternfile.name());
  if (SD.exists((char*)Patternfilefullpath[lapatterne])) {
     Serial.println("File OK");
    for (int i=0 ; i < parsinglength ; i++ ) {
  receivedbitinchar[i] = lepatternfile.read() ;
  }

  Parser parserp((byte*)receivedbitinchar, parsinglength);
  parserp.Reset();
  letempspattern = 0 ;
  int lenint = 0;
  
previousTp = 5;
  leparsed[2]= (char)'\0';
leparsed[1] = (char)'1'  ;
 leparsed[0] = (char)'1'  ; 
  if (parserp.Search('Off')) {
    Serial.println(" Off parsing start");
      parserp.Reset();
      lenint = 0 ;
     
   for (int filer = 0 ; filer < 128  ; filer++) {
//Serial.println(filer);
    while(!(leparsed[0] == (char)'O' && leparsed[1] == (char)'f' )) {
     parserp.JumpTo(Parser::IsDigit);
      letempspattern = round((parserp.Read_Int32()/letimescaler) );
     
      if (letempspattern>31) {
         leparsed[1] = (char)'z'  ;
         leparsed[0] = (char)'z'  ;
        break;
        }
          
         parserp.JumpTo(Parser::IsLetter);
       for (int i=0; i<2 ; i++) {
         leparsed[i] = parserp.Read_Char();
          }
           if ( ( leparsed[0] == (char)'O' && leparsed[1] == (char)'n') || ( leparsed[0] == (char)'P' && leparsed[1] == (char)'a') ) {
               leparsed[1] = (char)'z'  ;
                leparsed[0] = (char)'z'  ;

               parserp.SkipUntil(parserp.IsNewLine);
           
              }
      }

    
  if ( leparsed[0] == (char)'O' && leparsed[1] == (char)'n')  {
     leparsed[1] = (char)'z'  ;
      leparsed[0] = (char)'z'  ;
          break;
        }
         if ( leparsed[0] == (char)'P' && leparsed[1] == (char)'a')  {
           leparsed[1] = (char)'z'  ;
          leparsed[0] = (char)'z'  ;
          break;
        }
  if (letempspattern == previousTp) {
        lenint++;
      if (( lenint > nombreofliners+nombreofSamplerliners-1) || (leparsed[0] == (char)'O' && leparsed[1] == (char)'n') || (leparsed[0] == (char)'P' && leparsed[1] == (char)'a')) { 
       // parserp.SkipUntil(parserp.IsNewLine);
        letempspattern = round((parserp.Read_Int32()/letimescaler) );
        lenint = 0 ;
      }
    } else {
        lenint = 0 ;
        previousTp = letempspattern ;
       // Serial.println(previousTp);
      }
     if (letempspattern>31) {
       leparsed[1] = (char)'z'  ;
      leparsed[0] = (char)'z'  ;
    break;
    }

 
 parserp.JumpTo(Parser::IsDigit);
 
 parsedchannel = parserp.Read_Int32();
 if ( parsedchannel == 0 || parsedchannel == samplermidichannel) {
  Serial.println("broke On");
   leparsed[1] = (char)'z'  ;
 leparsed[0] = (char)'z'  ;
            break;
           }
  
           
  event1notesOff[lenint][letempspattern][0] = parsedchannel;                     
 //Serial.println(event1notes1[lenint][letempspattern][0]);
 parserp.JumpTo(Parser::IsDigit);
 event1notesOff[lenint][letempspattern][1] = parserp.Read_Int32();
 //Serial.println(event1notes1[lenint][letempspattern][1]);
 parserp.JumpTo(Parser::IsDigit);
 event1notesOff[lenint][letempspattern][2] = parserp.Read_Int32();
  event1notesOff[lenint][letempspattern][2] = 0;
 //Serial.println(event1notes1[lenint][letempspattern][2]);
  
  

  
 evented1[0][letempspattern] = 1;
 leparsed[1] = (char)'z'  ;
 leparsed[0] = (char)'z'  ;
 parserp.SkipUntil(parserp.IsNewLine);

 Serial.println("newline");
}
 }

 parserp.Reset();
letempspattern = 0;
previousTp = 5;
leparsed[1] = (char)'z'  ;
 leparsed[0] = (char)'z'  ;
 
 if (parserp.Search('On')) {
   Serial.println(" On parsing start");
    parserp.Reset();
    lenint = 0 ;
    
 for (int filer = 0 ; filer < 128  ; filer++) {
//Serial.println(filer);
    while(!(leparsed[0] == (char)'O' && leparsed[1] == (char)'n' )) {
     parserp.JumpTo(Parser::IsDigit);
      letempspattern = round((parserp.Read_Int32()/letimescaler) );
     
      if (letempspattern>31) {
        break;
        }
          
         parserp.JumpTo(Parser::IsLetter);
       for (int i=0; i<2 ; i++) {
         leparsed[i] = parserp.Read_Char();
          }
           if ( ( leparsed[0] == (char)'O' && leparsed[1] == (char)'f') || ( leparsed[0] == (char)'P' && leparsed[1] == (char)'a') ) {
               leparsed[1] = (char)'z'  ;
                leparsed[0] = (char)'z'  ;

               parserp.SkipUntil(parserp.IsNewLine);
           
              }
      }

    
  if ( leparsed[0] == (char)'O' && leparsed[1] == (char)'f')  {
          break;
        }
         if ( leparsed[0] == (char)'P' && leparsed[1] == (char)'a')  {
          break;
        }
  if (letempspattern == previousTp) {
        lenint++;
      if (( lenint > nombreofliners+nombreofSamplerliners-1) || (leparsed[0] == (char)'O' && leparsed[1] == (char)'f') || (leparsed[0] == (char)'P' && leparsed[1] == (char)'a')) { 
       // parserp.SkipUntil(parserp.IsNewLine);
        letempspattern = round((parserp.Read_Int32()/letimescaler) );
        lenint = 0 ;
      }
    } else {
        lenint = 0 ;
        previousTp = letempspattern ;
       // Serial.println(previousTp);
      }
     if (letempspattern>31) {
    break;
    }

 
 parserp.JumpTo(Parser::IsDigit);
 
 parsedchannel = parserp.Read_Int32();
 if ( parsedchannel == 0) {
  Serial.println("broke On");
            break;
           }
  if ( parsedchannel == synthmidichannel) {
           
  event1notes1[lenint][letempspattern][0] = parsedchannel;                     
 //Serial.println(event1notes1[lenint][letempspattern][0]);
 parserp.JumpTo(Parser::IsDigit);
 event1notes1[lenint][letempspattern][1] = parserp.Read_Int32();
 //Serial.println(event1notes1[lenint][letempspattern][1]);
 parserp.JumpTo(Parser::IsDigit);
 event1notes1[lenint][letempspattern][2] = parserp.Read_Int32();
 //Serial.println(event1notes1[lenint][letempspattern][2]);
  }
  if ( parsedchannel == samplermidichannel) {
            
  event2notes1[lenint][letempspattern][0] = parsedchannel;                    
 Serial.println(event2notes1[lenint][letempspattern][0]);
 parserp.JumpTo(Parser::IsDigit);
 event2notes1[lenint][letempspattern][1] = parserp.Read_Int32();
 Serial.println(event2notes1[lenint][letempspattern][1]);
 parserp.JumpTo(Parser::IsDigit);
 event2notes1[lenint][letempspattern][2] = parserp.Read_Int32();
 Serial.println(event2notes1[lenint][letempspattern][2]);
 addnoteoff2next(event2notes1[lenint][letempspattern][1], letempspattern );
 evented1[1][letempspattern]=1;
  }

  
 evented1[0][letempspattern] = 1;
 leparsed[1] = (char)'z'  ;
 leparsed[0] = (char)'z'  ;
 parserp.SkipUntil(parserp.IsNewLine);

 Serial.println("newline");
}
 }
 
 parserp.Reset();
letempspattern = 0;
previousTp = 5;
leparsed[1] = (char)'z'  ;
 leparsed[0] = (char)'z'  ;
 
 if (parserp.Search('Pa')) {
   Serial.println("CC parsing start");
    parserp.Reset();
    lenint = 0 ;
    
 for (int filer = 0 ; filer < 128  ; filer++) {

    while(!(leparsed[0] == (char)'P' && leparsed[1] == (char)'a' )) {
     parserp.JumpTo(Parser::IsDigit);
      letempspattern = round((parserp.Read_Int32()/letimescaler) );
     
      if (letempspattern>31) {
        break;
        }
          
         parserp.JumpTo(Parser::IsLetter);
       for (int i=0; i<2 ; i++) {
         leparsed[i] = parserp.Read_Char();
          }
           if ( ( leparsed[0] == (char)'O' && leparsed[1] == (char)'f') ||  ( leparsed[0] == (char)'O' && leparsed[1] == (char)'n') ) {
                leparsed[1] = (char)'z'  ;
                leparsed[0] = (char)'z'  ;
               parserp.SkipUntil(parserp.IsNewLine);
           
              }
      }

    
  if ( ( leparsed[0] == (char)'O' && leparsed[1] == (char)'f') ||  ( leparsed[0] == (char)'O' && leparsed[1] == (char)'n') ) {
          break;
        }
        
  if (letempspattern == previousTp) {
        lenint++;
      if (( lenint > nombreofliners-1) || (leparsed[0] == (char)'O' && leparsed[1] == (char)'f') || (leparsed[0] == (char)'O' && leparsed[1] == (char)'n')) { 
         leparsed[1] = (char)'z'  ;
                leparsed[0] = (char)'z'  ;
        parserp.SkipUntil(parserp.IsNewLine);
        letempspattern = round((parserp.Read_Int32()/letimescaler) );
        lenint = 0 ;
      }
    } else {
        lenint = 0 ;
        previousTp = letempspattern ;
      }
     if (letempspattern>31) {
    break;
    }
 Serial.print("parsing CCs");

 parserp.JumpTo(Parser::IsDigit);
 //skip channel as we dont care
  if ( parserp.Read_Int32() == 0) {
            break;
           }
 parserp.JumpTo(Parser::IsDigit);
 laccnote = parserp.Read_Int32();
 parserp.JumpTo(Parser::IsDigit);
 event1controllers[laccnote][letempspattern] = parserp.Read_Int32();
 leparsed[1] = (char)'z'  ;
 leparsed[0] = (char)'z'  ;
 parserp.SkipUntil(parserp.IsNewLine);

 
}
 }
 parserp.Reset();
 
letempspattern = 0;
leparsed[1] = (char)'z'  ;
 leparsed[0] = (char)'z'  ;
 lenint = 0 ;

 
  lepatternfile.close();
  refreshevented1();
 // Serial.println("recomputing offs");
  // recomputeparsedeventOffs2();
  // Serial.println(" lenghts ");
    computelenghtmesureoffline();
  
  
  
}
else {
  Serial.println("File not found : ");
  //Serial.print((char*)Patternfilefullpath[lapatterne]);
}

}

void addnoteoff2next(byte lanotee, byte lapos) {
    if ( lapos < pbars-1 ) {
       event2notesOff[lapos+1][0] = samplermidichannel ;
      event2notesOff[lapos+1][1] = lanotee ;
       event2notesOff[lapos+1][2] = 0 ;
    }
    if ( lapos == pbars-1 ) {
      event2notesOff[0][0] = samplermidichannel ;
      event2notesOff[0][1] = lanotee ;
       event2notesOff[0][2] = 0 ;
    }
}
int nextposoffthatnoteoff(byte lanote, int fromi){
  
  for (int linei = 0 ; linei < nombreofliners ; linei++ ) {
        for (int i = fromi+1; i < pbars ; i++ ) {
       
            if (lanote == parsedevent1notesOff[linei][i][1] ){
              
              return i ;
                 }
           
           }
           for (int i = 0; i < fromi ; i++ ) {
       
            if (lanote == parsedevent1notesOff[linei][i][1] ){
              return i ;
                 }
           
           }
     }
  return 0 ;
}
 void recomputeparsedeventOffs2(){
  for (int linei = 0 ; linei < nombreofliners ; linei++ ) {
    for (int i = 0; i < pbars ; i++ ) {
      if (event1notes1[linei][i][1] !=0 ){
        
          int laposofnextOff = nextposoffthatnoteoff(event1notes1[linei][i][1], i);
         event1notesOff[linei][laposofnextOff][0]= event1notes1[linei][i][0] ;
         event1notesOff[linei][laposofnextOff][1]= event1notes1[linei][i][1] ;
         parsedevent1notesOff[linei][laposofnextOff][1] = 0;
        }
      }
  }
}
 void recomputeparsedeventOffs(){
  for (int linei = 0 ; linei < nombreofliners ; linei++ ) {
    for (int i = 0 ; i < pbars ; i++ ) {

   
         event1notesOff[linei][i][1] = parsedevent1notesOff[linei][i][1] ;
        
      }
  }
}

void showallnotes() {
  for (int linei = 0 ; linei < 4 ; linei++ ) {
    Serial.println("  ");
       Serial.print("L");
   Serial.print(linei);
  Serial.print("Ons:");
    for (int i = 0; i < pbars ; i++ ) {
      Serial.print(event1notes1[linei][i][1]);
      Serial.print("  ");
      
    }
    Serial.println("  ");
    Serial.print("Offs: ");
    for (int i = 0; i < pbars ; i++ ) {
      Serial.print(event1notesOff[linei][i][1]);
      Serial.print("  ");
      
    }
     Serial.println("  ");
    Serial.print("prs:  ");
    for (int i = 0; i < pbars ; i++ ) {
      Serial.print(parsedevent1notesOff[linei][i][1]);
      Serial.print("  ");
      
    }
   
  }
}
