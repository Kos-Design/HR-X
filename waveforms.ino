
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
  // length of Waveformsdir -1
  int stringsize = 9 + fnamesize ;
  
  for (int i = 0 ; i < fnamesize ; i++ ) {
   
    Waveformsname[lefile][i] = lefname[i];
       
    Waveformsfullpath[lefile][9+i] = Waveformsname[lefile][i] ;
     if (i < fnamesize - 4) {
       Waveformsbase[lefile][i] = Waveformsname[lefile][i] ;
    }
   
  }
  Waveformsname[lefile][fnamesize]= (char)'\0' ;
  Waveformsfullpath[lefile][9+fnamesize]= (char)'\0' ;
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
          //Serial.print(subentry.name());
         setleWaveformsname(numberofWaveforms, subentry.name()) ;
         numberofWaveforms++;
             
       }      
       subentry.close();
     }
     susudir.close();
  }
}
//1
void displaywaveformsmenu() {
  navrange = 4 ;
  canvasBIG.fillScreen(SSD1306_BLACK);
   canvastitle.fillScreen(SSD1306_BLACK);
  
   WaveformsmenuBG();
   if (navlevel <= 1 ) {
      dolistwaveformsmenu(); 
   }
   else if (navlevel > 1 && sublevels[1] != 4) {
      dolistwaveformsmenu(); 
   }
   dodisplay();
            
}

void WaveformsmenuBG() {
  display.clearDisplay();
  if (navlevel == 1 && sublevels[1] != 4  ) {
    reinitsublevels(2);
    navrange = 4 ;
   
    dolistofwaveforms();
  }
 
 if (navlevel >= 2  && sublevels[1] == 4  ) {
 WaveformEditer();
 }
 
     if (navlevel > 1 && sublevels[1] !=4 ) {
         if (sublevels[1] == 0 ) {
           navrange = numberofWaveforms;
         } else {
          navrange = numberofWaveforms - 1;
          }
        
        
     
       
        dolistofwaveforms();
      
     }
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
          WaveformEditer();
          break;

          default:
          break;
        }
         displaywaveformsmenu();
        
         
       }
 
 
}


int cw_change = 0 ;
int vc_change;
int w_cursor_y = 32 ;  

void WaveformEditer() {
    int16_t y1 ;
    int16_t y2 ;
  navrange = 256 ;
  int w_cursor_x = sublevels[2]/2 ;
  

  
  canvastitle.fillScreen(SSD1306_BLACK);
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0,0);
  //draw cursor
  
   
       
        vc_change = Muxer.read_val(6);
        if (vc_change > 0 ) {
          cw_change = vc_change;
           w_cursor_y = map(cw_change, 0 , 1024, 64, 0);
        }
        if (trace_waveform && navlevel >=2 ) {
          myCustomWaveform[sublevels[2]] = map(cw_change, 0 , 1024, -32768, 32767);
      }
  canvasBIG.drawCircle(w_cursor_x,w_cursor_y,2,SSD1306_WHITE);
  
      for (int i = 0 ; i < 128 ; i++) {
         if ((i*2)+2 < 256) {
              y1 = map(myCustomWaveform[i*2], -32768, 32767, 63, 0);
              y2 = map(myCustomWaveform[(i*2)+2], -32768, 32767, 63, 0);
              canvasBIG.drawLine(i, y1, i+1, y2, SSD1306_WHITE);
              
          }
      }
      canvastitle.print(myCustomWaveform[sublevels[2]]);
}

void dolistwaveformsmenu() {
  char waveformsmenulabels[truesizeofwaveformsmenulabels][12] = {"Save", "Load", "Copy", "Delete", "Edit"};
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
  
    for (int filer = 0 ; filer < truesizeofwaveformsmenulabels-1 -(sublevels[1]) ; filer++) {

      canvasBIG.setCursor(startx,starty+((filer)*10));
      canvasBIG.println(waveformsmenulabels[sublevels[1]+1+filer]);
    }
    for (int filer = 0 ; filer < sublevels[1]  ; filer++) {

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


void writewaveforms() {
  size_t writtenBytes = mytxtFile.write((byte*)myCustomWaveform, sizeof(myCustomWaveform));
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

//TODO: change filename selector -> get waveformfullpath working in write and read IN PROGRESS
void parsewaveformfile(int presetn) {
  //File file = SD.open(filename, FILE_READ);
  mytxtFile = SD.open((char*)Waveformsfullpath[sublevels[2]], FILE_READ);
  size_t readBytes = mytxtFile.read((byte*)myCustomWaveform, sizeof(myCustomWaveform));
  
  if (readBytes != sizeof(myCustomWaveform)) {
    Serial.println("Failed to read complete waveform data");
  } else {
    Serial.println("Waveform data read from file:");
    for (int i = 0; i < 256; i++) {
      Serial.println(myCustomWaveform[i]);
    }
  }
    
    mytxtFile.close();
}
