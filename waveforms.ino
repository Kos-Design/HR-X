
/*
EXTMEM char Waveformsname[999][13];
EXTMEM char Waveformsfullpath[999][28];
EXTMEM char Waveformsbase[999][9];
EXTMEM bool Waveformsselected[999];
int numberofWaveformsselected = 0 ;
int numberofWaveforms = 0 ;
int Waveformsdizaines = 0 ;
int Waveformsunites = 0 ;
char newWaveformspath[28] = {"PRESETS/SYNTH/SYNSET01.TXT"};
char Waveformsdir[32] = {"PRESETS/SYNTH/"};
*/

void initializeWaveformsselected(){
  numberofWaveformsselected = 0 ;
  for (int i = 0 ; i < 999 ; i++ ) {
  Waveformsselected[i] = 0 ;
  }
}

void initializeWaveformsfullpath() {
    numberofWaveforms = 0 ;
    
   for (int i = 0 ; i < 999 ; i++ ) {
      for (int j = 0 ; j < 22 ; j++ ) {
        Waveformsfullpath[i][j] = (char)'\0';
       if (j < 9 ) {
       Waveformsfullpath[i][j] = (char*)"WAVEFORM/"[j];
        }
       if (j < 13 ) { 
        Waveformsname[i][j]= (char)'\0'; 
       }
       if (j < 9 ) { 
       Waveformsbase[i][j]=  (char)'\0'; 
       }
     }  
  }
}

void dowaveformslist() {
   initializeWaveformsselected();
   initializeWaveformsfullpath();
   listWaveformsfiles() ;

}

void setleWaveformsname(int lefile, char* lefname) {
 
  int fnamesize = strlen((char*)lefname) ;
  int stringsize = 14 + fnamesize ;
  
  for (int i = 0 ; i < fnamesize ; i++ ) {
   
    Waveformsname[lefile][i] = lefname[i];
       
    Waveformsfullpath[lefile][14+i] = Waveformsname[lefile][i] ;
     if (i < fnamesize - 4) {
       Waveformsbase[lefile][i] = Waveformsname[lefile][i] ;
    }
   
  }
  Waveformsname[lefile][fnamesize]= (char)'\0' ;
  Waveformsfullpath[lefile][14+fnamesize]= (char)'\0' ;
  Waveformsbase[lefile][fnamesize-4] = (char)'\0' ;
    
  }

void listWaveformsfiles() {
   if (SD.exists((char*)Waveformsdir)) {
  File susudir = SD.open((char*)Waveformsdir);
 
     while(true) {
       File subentry =  susudir.openNextFile();
        if (! subentry) {
           break;
       }
      
        if ( !subentry.isDirectory() ) {
         setleWaveformsname(numberofWaveforms, subentry.name()) ;
         numberofWaveforms++;
             
       }      
       subentry.close();
     }
  }
}
//1
void displaywaveformsmenu() {
  navrange = 4 ;
  canvasBIG.fillScreen(SSD1306_BLACK);
   canvastitle.fillScreen(SSD1306_BLACK);
    
   WaveformsmenuBG();
   dolistwaveformsmenu();
   dodisplay();
            
}

const char* lofolderPath = "/WAVEFORM";

void WaveformsmenuBG() {
  display.clearDisplay();
  if (navlevel == 1) {
    reinitsublevels(2);
    navrange = 4 ;
  }
 if (navlevel == 2  && sublevels[1] !=4 ) {
  //Serial.println("got into preset list");
 }
   if (navlevel > 1) {
       if (sublevels[1] == 0 ) {
         navrange = numberofWaveforms;
       } else {
     //setwaveformsnavrange();
        navrange = numberofWaveforms - 1;
        }
   }
       dolistofwaveforms();
       dodisplay();
       
      
  if (navlevel >= 3 ) {
   // Serial.println("preset action selected");
      
        navlevel = 1;
        vraipos =  sublevels[1];
        myEnc.write(4*vraipos);
        navrange = 4;
        
        switch (sublevels[1]) {
          
          case 0:
          writewaveform();
          break;
          
          case 1:
          
          readwaveform();
          break;
          
          case 2:
          copywaveform();
          break;
          
          case 3:
          deletewaveform();
          break;
          
          case 4:
          break;

          default:
          break;
        }
         displaywaveformsmenu();
        
         
       }
 
 
}

void dolistwaveformsmenu() {
  char waveformsmenulabels[truesizeofwaveformsmenulabels][12] = {"Save", "Load", "Copy", "Delete", "Params"};
    byte startx = 5;
  byte starty = 16;
   char* textin = (char*)waveformsmenulabels[sublevels[1]] ;
 //Serial.println(textin);
    canvastitle.fillScreen(SSD1306_BLACK);
    canvastitle.setCursor(0,0);
    canvastitle.setTextSize(2);
    canvastitle.println(textin);
    
    canvasBIG.setTextSize(1);
    canvasBIG.fillScreen(SSD1306_BLACK);
  
    for (int filer = 0 ; filer < truesizeofwaveformsmenulabels-1 -(sublevels[1]) ; filer ++) {

      canvasBIG.setCursor(startx,starty+((filer)*10));
      canvasBIG.println(waveformsmenulabels[sublevels[1]+1+filer]);
    }
    for (int filer = 0 ; filer < sublevels[1]  ; filer ++) {

      canvasBIG.setCursor(startx,(10*(truesizeofwaveformsmenulabels-sublevels[1])+6+((filer)*10)));
      canvasBIG.println(waveformsmenulabels[filer]);
    }

}

void makenewwformfilename() {
  //newWaveformspath
   Waveformsunites = 0 ;
  Waveformsdizaines = 0 ;
    while (SD.exists((char*)newWaveformspath)) {
     // Serial.println("current exists");
  
      findnextavailablewformname();
    }
}

void findnextavailablewformname() {
   
  if ( Waveformsunites < 9 ) {
    Waveformsunites++;
  } else {
    Waveformsunites = 0 ;
     if ( Waveformsdizaines < 9 ) {
    Waveformsdizaines++;
  } else {
    Waveformsdizaines = 0;
  }
    
  }
  
  newWaveformspath[16]=Waveformsunites + '0' ;
  newWaveformspath[15]=Waveformsdizaines + '0' ;
  //Serial.println((char*)newWaveformspath);
  
}

void writewaveform() {
  
    if (sublevels[2] == numberofWaveforms) {
      makenewwformfilename(); 
      mytxtFile = SD.open((char*)newWaveformspath, FILE_WRITE);
    } else {
    if (SD.exists((char*)Waveformsfullpath[sublevels[2]])) {
      SD.remove((char*)Waveformsfullpath[sublevels[2]]);
      }
    
      mytxtFile = SD.open((char*)Waveformsfullpath[sublevels[2]], FILE_WRITE);
    } 
      // if the file opened okay, write to it:
      if (mytxtFile) {
        Serial.print("Writing to ");
        Serial.println(mytxtFile.name());
        writewaveforms();
        mytxtFile.close();
        //Serial.println("done.");
      } 
    
   mytxtFile.close();
   dowaveformslist();
}  

void dolistofwaveforms() {
   int startx = 80;
  int starty = 16;
  // char* textinz = (char*)lesfiles[sublevels[3]].name() ;

    canvastitle.fillScreen(SSD1306_BLACK);
    canvastitle.setCursor(startx,0);
    canvastitle.setTextSize(1);

   
    
    if ( sublevels[2] == numberofWaveforms && sublevels[1] == 0 ) {
             
    canvastitle.print("New()");
    } else {
     canvastitle.print((char*)Waveformsbase[sublevels[2]]);
    }
    canvastitle.setTextSize(1);
    canvasBIG.setTextSize(1);
    canvasBIG.fillScreen(SSD1306_BLACK);
     if ( sublevels[2] == numberofWaveforms ) {
      for (int filer = 0 ; filer < sublevels[2]-1  ; filer ++) {
        canvasBIG.setCursor(startx,(10*(numberofWaveforms-sublevels[2]))+16+((filer)*10));
        canvasBIG.println((char*)Waveformsbase[filer]);
      }
        } else {
        for (int filer = 0 ; filer < numberofWaveforms-1-(sublevels[2]) ; filer ++) {
      canvasBIG.setCursor(startx,starty+((filer)*10));
      canvasBIG.println((char*)Waveformsbase[sublevels[2]+1+filer]);
    }
  
    for (int filer = 0 ; filer < sublevels[2]  ; filer ++) {

        canvasBIG.setCursor(startx,(10*(numberofWaveforms-sublevels[2]))+6+((filer)*10));
        canvasBIG.println((char*)Waveformsbase[filer]);
       }
     } 
   
}

void setwaveformsnavrange() {
  if (numberofWaveforms < 2) {
  navrange = 2 ;
 // Serial.println("SOMETHING IS WRONG");
  } else {
   navrange = numberofWaveforms - 1 ;
  }
  
}

int16_t myCustomWaveform[256] = { 
  // Example waveform data
  0,  201,  402,  603,  804,  1005,  1206,  1406,  1607,  1808,  2008,  2209,  2409,  2609,  2809,  3009, 
  3209,  3409,  3608,  3808,  4007,  4206,  4405,  4603,  4802,  5000,  5199,  5397,  5594,  5792,  5989,  6186, 
  6383,  6580,  6776,  6972,  7168,  7363,  7559,  7753,  7948,  8142,  8336,  8529,  8722,  8915,  9107,  9299, 
  9490,  9681,  9871,  10061,  10251,  10440,  10628,  10817,  11004,  11191,  11378,  11564,  11750,  11935,  12119,  12303, 
  12487,  12670,  12852,  13034,  13215,  13396,  13576,  13755,  13934,  14112,  14290,  14467,  14643,  14819,  14994,  15168, 
  15342,  15515,  15687,  15859,  16030,  16200,  16370,  16539,  16707,  16875,  17042,  17208,  17374,  17539,  17703,  17867, 
  18029,  18191,  18353,  18513,  18673,  18832,  18990,  19148,  19304,  19460,  19615,  19770,  19923,  20076,  20228,  20380, 
  20530,  20680,  20829,  20977,  21124,  21270,  21416,  21560,  21704,  21847,  21989,  22131,  22271,  22411,  22549,  22687, 
  22824,  22960,  23095,  23229,  23362,  23494,  23626,  23756,  23886,  24014,  24142,  24268,  24394,  24518,  24642,  24765, 
  24887,  25007,  25127,  25245,  25363,  25479,  25595,  25709,  25823,  25935,  26047,  26157,  26266,  26375,  26482,  26589, 
  26694,  26798,  26901,  27004,  27105,  27205,  27304,  27402,  27499,  27595,  27689,  27783,  27876,  27967,  28058,  28147, 
  28236,  28323,  28409,  28494,  28578,  28660,  28742,  28823,  28902,  28980,  29057,  29133,  29208,  29281,  29354,  29425, 
  29495,  29564,  29632,  29699,  29764,  29828,  29891,  29953,  30014,  30074,  30132,  30189,  30245,  30299,  30353,  30405, 
  30456,  30506,  30554,  30601,  30647,  30691,  30735,  30777,  30818,  30857,  30896,  30933,  30968,  31003,  31036,  31068, 
  31098,  31127,  31155,  31182,  31207,  31231,  31253,  31275,  31294,  31313,  31330,  31346,  31361,  31374,  31386,  31397, 
  31406,  31414,  31420,  31426,  31430,  31433,  31434,  31435,  31434,  31432,  31428,  31423,  31417,  31409,  31400,  31389
};

int16_t myNEWCustomWaveform[256] ;

void writewaveforms() {
  //mytxtFile.print("<WAVEFORM><WFORM>\n");
  size_t writtenBytes = mytxtFile.write((byte*)myCustomWaveform, sizeof(myCustomWaveform));
  //mytxtFile.write((byte*)waveformed_sine, sizeof(waveformed_sine));
  if (writtenBytes != sizeof(myCustomWaveform)) {
    Serial.println("Failed to write all waveform data to file");
  } else {
    Serial.println("Waveform data written to file.");
  }
}

void readwaveform () {
  parsewaveformfile(sublevels[2]);

}

void copywaveform() {
  File originefile ;
     findnextavailablewformname();
if (SD.exists((char*)Waveformsfullpath[sublevels[2]])) {
  mytxtFile = SD.open((char*)newWaveformspath, FILE_WRITE); 
  originefile = SD.open((char*)Waveformsfullpath[sublevels[2]], FILE_READ);
   size_t n; 
  uint8_t buf[64];
 while ((n = originefile.read(buf, sizeof(buf))) > 0) {
    mytxtFile.write(buf, n);
  }
  }
  
  originefile.close();
  mytxtFile.close();
  dowaveformslist();
}

void deletewaveform() {
 if (SD.exists((char*)Waveformsfullpath[sublevels[2]])) {
  SD.remove((char*)Waveformsfullpath[sublevels[2]]);
  }
  dowaveformslist();
}

//TODO: change filename selector -> only works with newfilename, get waveformfullpath working in write and read
void parsewaveformfile(int presetn) {
  //File file = SD.open(filename, FILE_READ);
  mytxtFile = SD.open((char*)newWaveformspath, FILE_READ);
  size_t readBytes = mytxtFile.read((byte*)myNEWCustomWaveform, sizeof(myNEWCustomWaveform));
  
  if (readBytes != sizeof(myCustomWaveform)) {
    Serial.println("Failed to read complete waveform data");
  } else {
    Serial.println("Waveform data read from file:");
    for (int i = 0; i < 256; i++) {
      Serial.println(myNEWCustomWaveform[i]);
    }
  }
    
    mytxtFile.close();
}
