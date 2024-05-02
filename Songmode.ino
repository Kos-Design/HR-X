int songedit = 2;
int songselectorX;
int songselectorY;
int patternonsong[99];
int songplayhead = 0 ;
byte numberofpatonsong ;

bool songplaying ;

byte numberofSongs = 0 ;
 char Songdir[7] = {"SONGS/"};
 char Songname[99][13];
 char Songfullpath[99][22];
 char Songbase[99][9];
 bool Songsselected[99];
char newSongpath[22]= {"SONGS/SONG#00.TXT"} ;
const byte truesizeofSongmenulabels = 8 ;
const byte navSongmenu = 1 ;


void doSonglist() {
  
   initializeSongfullpath();

   listSongs() ;


}
void writedasong() {
   
if (sublevels[navSongmenu+1] == numberofSongs) {
 // if (1==1) {
  makenewSongname();
 // Serial.print("newnamed ");
  Serial.print("trying to open ");
  Serial.println((char*)newSongpath);
  
  
  mytxtFile = SD.open((char*)newSongpath, FILE_WRITE);
} 
else {
if (SD.exists((char*)Songfullpath[sublevels[navSongmenu+1]])) {
  SD.remove((char*)Songfullpath[sublevels[navSongmenu+1]]);
  }

  mytxtFile = SD.open((char*)Songfullpath[sublevels[navSongmenu+1]], FILE_WRITE);
} 
  // if the file opened okay, write to it:
 // if (mytxtFile) {
    Serial.println("writing");
   // Serial.print("Writing to ");
  //  Serial.println(mytxtFile.name());
    writeSong();
  // close the file:
    mytxtFile.close();
    //Serial.println("done.");
    doSonglist();
 // } else {
    // if the file didn't open, print an error:
   // Serial.println("error opening test.txt");
//  }
//listfileslist("/");
  // mytxtFile.close();
   
}

void writeSong() {
  mytxtFile.print("<Song>\n");
//patternonsong[sublevels[songedit]][sublevels[songedit+1]]

  INTinsertmytxtfile(numberofpatonsong,"nums");
  for (byte i=0; i<99 ; i++ ) {
  INTinsertmytxtfile(patternonsong[i],"songpat");
  }
  Serial.println("wrote");

}

void parseSong(int Songn) {
 mytxtFile = SD.open((char*)Songfullpath[Songn]);
  if (mytxtFile) {
    //already full, increse parsingbuffersize if more settings are added
    for (int i = 0 ; i < parsingbuffersize ; i++ ) {
  receivedbitinchar[i] = mytxtFile.read() ;
  }
}
Parser parser((byte*)receivedbitinchar, parsinglength);

    
  parser.Read_String('#'); 
  parser.Skip(1); 
  numberofpatonsong = parser.Read_Int16();
    
    for (int i = 0 ; i < 99 ; i++ ) {
      parser.Read_String('#'); 
      parser.Skip(1); 
      patternonsong[i] = parser.Read_Int16();
    }
   

//}
   parser.Reset();
   mytxtFile.close();
//Serial.println("parsing done");
   
}
void readSong() {

  parseSong(sublevels[navSongmenu+1]);

}

void copySong() {
  File originefile ;
     makenewSongname();
if (SD.exists((char*)Songfullpath[sublevels[navSongmenu+1]])) {
  mytxtFile = SD.open((char*)newSongpath, FILE_WRITE); 
  originefile = SD.open((char*)Songfullpath[sublevels[navSongmenu+1]], FILE_READ);
   size_t n; 
  uint8_t buf[64];
 while ((n = originefile.read(buf, sizeof(buf))) > 0) {
    mytxtFile.write(buf, n);
  }
  }
  
  originefile.close();
  mytxtFile.close();
  doSonglist();
}

void deleteSong() {
 if (SD.exists((char*)Songfullpath[sublevels[2]])) {
  SD.remove((char*)Songfullpath[sublevels[2]]);
  }
  doSonglist();
}

        
void shiftSongright(int leshifter){
     Serial.print("song right Shifterd");
   Serial.println(leshifter);
for (int shifts = 0 ; shifts < leshifter ; shifts++) {
  for (int i = 98; i >= 0 ; i--) {
  
    patternonsong[i+1] = patternonsong[i];
    patternonsong[i]=0;
  }
 }
}

void shiftSongleft(int leshifter){
  Serial.print("song left Shifterd");
   Serial.println(leshifter);
for (int shifts = 0; shifts < leshifter ; shifts++) {
  for (int i = 1 ; i < 99 ; i++) {
  
    patternonsong[i-1] = patternonsong[i];
    patternonsong[i]=0;
  }

}
}

void doSongShifter(int shifter){
  Serial.println(shifter);
 if (shifter-16>0) {
  shiftSongleft(abs(shifter-16));
       
    }
    if (shifter-16<0){
 
         shiftSongright(abs(shifter-16)); 
    }
 
  } 
  
void showSongShifterdisplays() {
  Serial.println("shifterz");
  navrange = 32 ;
//  if (navlevel > 2 ) {
//    doSongShifter();
//    returntonav(navSongmenu);
//  }
    display.clearDisplay();
   canvastitle.fillScreen(SSD1306_BLACK);
   canvasBIG.fillScreen(SSD1306_BLACK);
       canvastitle.setCursor(0,0);
    canvastitle.setTextSize(2);
    //canvastitle.print((char*)optionspatternlabels[sublevels[2]]);
  canvastitle.print("Shift Song");
    int latransposition ;
    latransposition = 16-sublevels[2];
    sublevels[3] = sublevels[2];
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

    
void initializeSongfullpath() {
    numberofSongs = 0 ;
    
   for (int i = 0 ; i < 99 ; i++ ) {
      for (int j = 0 ; j < 22 ; j++ ) {
        Songfullpath[i][j] = (char)'\0';
       if (j < 6 ) {
       Songfullpath[i][j] = (char*)"SONGS/"[j];
        }
       if (j < 13 ) { 
        Songname[i][j]= (char)'\0'; 
       }
       if (j < 9 ) { 
       Songbase[i][j]=  (char)'\0'; 
       }
     }  
  }
}
//  SONGS/SONG#00.TXT
 void setleSongname(int lefile, char* lefname) {
 
  int fnamesize = strlen((char*)lefname) ;
  int stringsize = 6 + fnamesize ;
  for (int i = 0 ; i < fnamesize ; i++ ) {
   
    Songname[lefile][i] = lefname[i];
       
    Songfullpath[lefile][6+i] = Songname[lefile][i] ;
     if (i < fnamesize - 4) {
       Songbase[lefile][i] = Songname[lefile][i] ;
    }
   
  }
  Songname[lefile][fnamesize]= (char)'\0' ;
  Songfullpath[lefile][6+fnamesize]= (char)'\0' ;
  Songbase[lefile][fnamesize-4] = (char)'\0' ;
    
  }

void listSongs() {
   if (SD.exists((char*)Songdir)) {
  File susudir = SD.open((char*)Songdir);
 
     while(true) {
       File subentry =  susudir.openNextFile();
        if (! subentry) {
           break;
       }
      
        if ( !subentry.isDirectory() ) {
         setleSongname(numberofSongs, subentry.name()) ;
         numberofSongs++;
          //Serial.print("adding song");
          //Serial.println(subentry.name());   
       }      
       subentry.close();
     }
  }
}
void displaySongmenu() {
  Serial.println("displaySongmenu");
  //navrange = 4 ;
  canvasBIG.fillScreen(SSD1306_BLACK);
   canvastitle.fillScreen(SSD1306_BLACK);
    display.clearDisplay();
   
   SongmenuAction();
  
   dodisplay();
      //getSongdir()   ;   
}
void dolistofSongs() {
   int startx = 80;
  int starty = 16;
  // char* textinz = (char*)less[sublevels[3]].name() ;

    canvastitle.setCursor(startx,0);
    canvastitle.setTextSize(1);
 
    if ( sublevels[navSongmenu+1] == numberofSongs && sublevels[navSongmenu] == 1 ) {
             
    canvastitle.print("New()");
    } else {
     canvastitle.print((char*)Songbase[sublevels[navSongmenu+1]]);
    }
    canvastitle.setTextSize(1);
    canvasBIG.setTextSize(1);
    //canvasBIG.fillScreen(SSD1306_BLACK);
     if ( sublevels[navSongmenu+1] == numberofSongs ) {
      for (int filer = 0 ; filer < sublevels[navSongmenu+1]-1  ; filer ++) {
        canvasBIG.setCursor(startx,(10*(numberofSongs-sublevels[navSongmenu+1]))+16+((filer)*10));
        canvasBIG.println((char*)Songbase[filer]);
      }
        } else {
        for (int filer = 0 ; filer < numberofSongs-1-(sublevels[navSongmenu+1]) ; filer ++) {
      canvasBIG.setCursor(startx,starty+((filer)*10));
      canvasBIG.println((char*)Songbase[sublevels[navSongmenu+1]+1+filer]);
    }
  
    for (int filer = 0 ; filer < sublevels[navSongmenu+1]  ; filer ++) {

        canvasBIG.setCursor(startx,(10*(numberofSongs-sublevels[navSongmenu+1]))+6+((filer)*10));
        canvasBIG.println((char*)Songbase[filer]);
       }
     } 

}



void SongmenuAction() {
 
      if (navlevel == navSongmenu) {
         reinitsublevels(navSongmenu+1);
        navrange = truesizeofSongmenulabels-1 ;
        
    dolistSongdisplay();
    dolistofSongs();
      }
      
  if ((sublevels[navSongmenu] == 0) && (navlevel > navSongmenu )) {
   Songmodepanel();
  }
  
   if (sublevels[navSongmenu] != 0) {
 
      if (navlevel > navSongmenu+1 ) {
             
      
        switch (sublevels[navSongmenu]) {
                
          case 0:
          Songmodepanel();
          //into edit already ;
          break;
          case 1:
          writedasong();
         
          //save();
          break;
          case 2:
          
          readSong();
         
          break;
          case 3:
          copySong();
         
          break;
          
          case 4:
          deleteSong();
          
          break;
          
          case 5:
          initializepatternonsong();
          
          break;
          case 6 :
          
          break;
          case 7:
           doSongShifter(sublevels[3]);
          
          break;
         
          default:
          break;
        }
         //displaySongmenu();
        returntonav(navSongmenu,truesizeofSongmenulabels-1);
        //returntonav(navSongmenu,truesizeofSongmenulabels-1); 
       }
   
       if (navlevel > navSongmenu ) {

        if (sublevels[navSongmenu] == 5) {
          returntonav(navSongmenu,truesizeofSongmenulabels-1);
        }
        
        if (sublevels[navSongmenu] == 1) {
        navrange = numberofSongs; 
        } else {
          navrange = numberofSongs -1 ;
        }
        if (sublevels[navSongmenu] == 7) {
           navrange = 32;
          showSongShifterdisplays();
          
        }
        if (sublevels[navSongmenu] != 7) {
         dolistSongdisplay();
         dolistofSongs();
        }
       }

       
       //if (navlevel == navSongmenu ) {
   // dolistSongdisplay();
    // dolistofSongs();
     
      // }
       
   }


}

void dolistSongdisplay() {
  
  char Songmenulabels[truesizeofSongmenulabels][12] = {"Edit", "Save", "Load", "Copy", "Delete", "Clear","Params","Shift"};
    byte startx = 5;
  byte starty = 16;
   char* textin = (char*)Songmenulabels[sublevels[navSongmenu]] ;
 //Serial.println(textin);
    //canvastitle.fillScreen(SSD1306_BLACK);
    canvastitle.setCursor(0,0);
    canvastitle.setTextSize(2);
    canvastitle.println(textin);
    
    canvasBIG.setTextSize(1);
    //canvasBIG.fillScreen(SSD1306_BLACK);
  
    for (int filer = 0 ; filer < truesizeofSongmenulabels-1 -(sublevels[navSongmenu]) ; filer++) {

      canvasBIG.setCursor(startx,starty+((filer)*10));
      canvasBIG.println(Songmenulabels[sublevels[navSongmenu]+1+filer]);
    }
    for (int filer = 0 ; filer < sublevels[navSongmenu]  ; filer++) {

      canvasBIG.setCursor(startx,(10*(truesizeofSongmenulabels-sublevels[navSongmenu])+6+((filer)*10)));
      canvasBIG.println(Songmenulabels[filer]);
    }

}

void makenewSongname() {
  //newSongpath
   synsetunites = 0 ;
  synsetdizaines = 0 ;
  Serial.println((char*)newSongpath);
    while (SD.exists((char*)newSongpath)) {
      findnextSongname();
      Serial.println((char*)newSongpath);
    }
}

void findnextSongname() {
   
  if ( synsetunites < 9 ) {
    synsetunites++;
  } else {
    synsetunites = 0 ;
     if ( synsetdizaines < 9 ) {
    synsetdizaines++;
  } else {
    synsetdizaines = 0;
  }
    
  }   
  // tot-9  tot-10
  newSongpath[12]=synsetunites + '0' ;
  newSongpath[11]=synsetdizaines + '0' ;

 // "SONGS/SONG#00.TXT"
  //newSongpath[27] = {"/SOUNDSET/REC/REC-00.L.RAW"};
}


void playdasong() {
  if (!externalticker) {
  metro0.reset();
  }
  songplaying = 1 ;
  loadsongpattern();
  stoptick = 0 ;
  patternOn = 1 ;
}

void stopdasong() {
  songplaying = 0 ;
  songplayhead = 0 ;
  stoptick = 1 ;
  patternOn = 0 ;
}

void pausedasong() {
  songplaying = 0 ;
  stoptick = 1 ;
  patternOn = 0 ;
}
void showplayheadprogress() {
  display.drawLine(songplayhead*8, 16, songplayhead*8, 64, SSD1306_INVERSE);
}
void loadsongpattern() {
  
  // Serial.println(songplayhead);
  if (patternonsong[songplayhead] > 0 ) {
   
    clearlapattern();
     Serial.print("cleared ");
     Serial.print("loading ");
      Serial.println(patternonsong[songplayhead]-1);
    parsepattern(patternonsong[songplayhead]-1);
     Serial.println("Loaded");
  } else {
    stopdasong();
  }
}
void initializepatternonsong() {
  
    for (int j = 0 ; j < 99 ; j++ ) {
      patternonsong[j] = 0 ;
    }
  
}
void actionSongTransport() {
    if ( sublevels[songedit] == 0 ) {
      stopdasong();
      playdasong();
    }
      if ( sublevels[songedit] == 2 ) {
      stopdasong();
    }
      if ( sublevels[songedit] == 3 ) {
      playdasong();
    }
  
        returntonav(songedit);
}
void Songmodepanel() {
     songselectorY = 16 ;
    songmodetopbar();
    //drawsonggrid() ;
    //Serial.println("see things?");
    if (navlevel == songedit ) {
      if (songpage>0) {
      navrange = 8+16+1 ;
    }else {
      navrange = 8+16 ;
    }
      if ( sublevels[songedit]>7 ) {
       
      //navrange = 128/8 - 1;
      selectormoveX();
      } 
      
      else {
       // songselectorY = 12 * sublevels[songedit] + 16 
        songTransportSelector();
      }
    }
    if (navlevel == songedit+1 ) {
      if ( sublevels[songedit]>7 ) {
        if ( sublevels[songedit]<24 ) {
        selectpatterninsong();
        } else {
          selectsongnavarrows();
        }
      } else {
        actionSongTransport();
      }
    }
    if (navlevel == songedit+2 ) {
      
      setpatterninsong();
     if ( patternonsong[sublevels[songedit]-8] > 0 ) {
      numberofpatonsong++;
     } else {
      numberofpatonsong = sublevels[songedit]-8 ;
     }
     
    }
    
    
    if ( sublevels[songedit]>7 ) {
     showsongcell();
    }
    
    showpatonSongGrid();
    showsongnavarrows();
    dodisplay();
    songgridposselector();
    if (songplaying ) {
      showplayheadprogress();
    }
    dodisplay(); 
}
void showsongnavarrows() {
   canvasBIG.setTextSize(2);
   
  canvasBIG.setCursor(115,49);
   canvasBIG.print((char)26);
    if (songpage > 0 ) {
  canvasBIG.setCursor(2,49);
    canvasBIG.print((char)27);
    }
}
void setpatterninsong() {
Serial.println(songpage);
  patternonsong[(songpage*16)+sublevels[songedit]-8] = sublevels[songedit+1] ;
  returntonav(songedit);
}

void songmodetopbar() {
      display.clearDisplay();
      canvasBIG.fillScreen(SSD1306_BLACK);
      canvastitle.fillScreen(SSD1306_BLACK);
      canvasBIG.setTextSize(1);
      drawtransport();
      
}

void showsongcell() {
  int lasongcell = patternonsong[(songpage*16)+sublevels[songedit]-8];
  canvastitle.setCursor(0,0);
  canvastitle.setTextSize(1);
  if (navlevel == songedit ) {
   if (lasongcell>0) {
  
  
    canvastitle.print((char*)Patternfilebase[lasongcell-1]);
  
  } else {
     canvastitle.print("Empty");
  }
  }
}



void selectormoveX() {
  songselectorX = 8 * (sublevels[songedit]-8) ;
 // if (sublevels[songedit]-8 >15 ) {
}


void songTransportSelector() {
   int startyp = 8 ;
   int starx = 1 ;
   int ecart = 14 ;
   
   
   
   display.drawPixel(ecart*(sublevels[songedit] )+6, startyp+7, SSD1306_WHITE);
 display.drawPixel(ecart*(sublevels[songedit] )+7 , startyp+6, SSD1306_WHITE);
 display.drawPixel(ecart*(sublevels[songedit] )+7 , startyp+7, SSD1306_WHITE);
}
void showpatonSongGrid() {
  int lasongcell; 

 
    for (int j = 0 ; j < 16 ; j++ ) {
      lasongcell = patternonsong[(songpage*16) +j];
  
      if (lasongcell > 0 ) {
      display.fillRect(j*8 + 1, 16+1, 8-2 , 12-2 , SSD1306_WHITE);
    }
  
}
}
void selectpatterninsong() {
  navrange = numberofPatternfiles  ;
  canvastitle.setCursor(0,0);
  canvastitle.setTextSize(1);
   
  if (sublevels[songedit+1] > 0 ) {
    canvastitle.print((char*)Patternfilebase[sublevels[songedit+1]-1]);
  
  } else {
     canvastitle.print("Empty");
  }
  
}
void selectsongnavarrows() {
  if (navlevel == songedit ) {
    
    if (sublevels[songedit]>23 ) {
      canvasBIG.drawRoundRect(113-(sublevels[songedit]-24)*113 ,49,14,14,2,SSD1306_WHITE);
    }
  }
  if (navlevel == songedit+1 ) {
if (sublevels[songedit]==25 && songpage > 0 ) {
  songpage--;
   Serial.println(songpage);
}
if (sublevels[songedit]==24 && songpage < 6) {
  songpage++;
  Serial.println(songpage);
}
    returntonav(songedit);
  }
}
void songgridposselector() {
  if ( sublevels[songedit]>7) {
    if ( sublevels[songedit]<24 ) {
  
  //int startxp = 0 ;
  //int startyp = 16;
  int cellsizep = 8 ;
  int celltallp = 12 ;
   display.fillRect(songselectorX, songselectorY, cellsizep , celltallp , SSD1306_INVERSE); 
    } else {
      selectsongnavarrows();
    }
  } 
}
