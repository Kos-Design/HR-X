
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
 // Serial.print("newnamed ");
 // Serial.println((char*)newWaveformspath);
  
  
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

void writewaveforms() {
  
  mytxtFile.print("<WAVEFORM><WFORM>\n");

  INTinsertwform(slope1,"slope1");
  
}

void readwaveform () {

  parsefile(sublevels[2]);

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


//CHANGE
void INTinsertwform(int leint, char* leparam ) {
  mytxtFile.print((char*)leparam);
  mytxtFile.print(" ");
    mytxtFile.print("#");
  mytxtFile.print(int(leint));
  mytxtFile.print("\n");
}
/*

//CHANGE
void FLOATinsertmytxtfile(float leint, char* leparam ) {
  mytxtFile.print((char*)leparam);
  mytxtFile.print(" ");
    mytxtFile.print("#");
  mytxtFile.print(float(leint));
  mytxtFile.print("\n");
}


//CHANGE
void parsefile(int presetn) {
    byte tmp_mixlevelsM[4];
    float tmp_mixlevelsL[4];
    float tmp_WetMixMasters[4];
    mytxtFile = SD.open((char*)Waveformsfullpath[presetn]);
    if (mytxtFile) {
    //already full, increse parsingbuffersize if more settings are added
    for (int i=0 ; i < parsingbuffersize ; i++ ) {
      receivedbitinchar[i] = mytxtFile.read() ;
      }
    }

  Parser parser((byte*)receivedbitinchar, parsinglength);
 
  parser.Read_String('#'); 
  parser.Skip(1); 
  slope1 = parser.Read_Int16();

   parser.Reset();
   mytxtFile.close();
   //Serial.println("parsing done");
  setbpms();
  setlepulse1();
   setlepulse2();
   ApplyADSR();
  // Serial.println("adsr done");
  le303filterzWet();
  Wavespreamp303controls();
  
    le303filtercontrols();
  setwet2smixlevel(0);
  setwet2smixlevel(1);
    
}
*/
          
