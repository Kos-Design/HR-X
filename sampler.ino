

class SamplerMenuRouter : public SectionHolder {
    public:
        SamplerMenuRouter() {
                    self = this ;
                    self->home_navrange=SP_LABELS_COUNT-1;
                    self->catalog = new FilesLister("SOUNDSET/","SAMPLE#",".RAW",show,self->home_navrange);
                    self->relative_navlevel=1;
                    self->max_navlevel=5;
                    self->sublevels_address={7,0,0};
                    }
        FilesLister *catalog;
        String newmkdirpath = "SOUNDSET/MABANK01" ;
        const byte FlashChipSelect = 6;
        bool assigning_sample_to_note = false ;
        char samplefoldersregistered[99][SP_NAME_MAX]{};
        char sampledirpath[99] = {"SOUNDSET/"};
        char samplebase[99][999][9]{};
        int sizeofsamplefolder[99]{};
        int sampledirsregistered = 0;
        bool samplesselected[99][999]{};
        int numberofsamplesselected[99]{};
        bool samplesfoldersselected[99]{};
        int numofsamplesfoldersselected = 0;
        char Flashsamplebase[999][9]{};
        bool Flashsamplesselected[999]{};
        int numberofFlashsamplesselected = 0;
        int numberofFlashfiles = 0;
        

        static void sampler_nav_two(){
          if (lv.sublevels[1] == 0) {
              display.clearDisplay();
              samplerexplorer();
          }
          if (lv.sublevels[1] == 1) {
              display.clearDisplay();
              Flashsamplerexplorer();
          }
          if (lv.sublevels[1] == 2) {
              display.clearDisplay();
              Assingexplorer();
          }

          if (lv.sublevels[1] == 3) {
              smixerVpanel();
          }
        }

        static void sampler_nav_one(){
          self->assigning_sample_to_note = false ;
          display.clearDisplay();
          _nav_sampler[lv.sublevels[1]]();
          dm.dodisplay();
        }
        
        static void sampler_nav_zero(){
            reinitsublevels(2);
            lv.navrange = SP_LABELS_COUNT - 1;
            display.clearDisplay();
            dolistsamplermenu();
            dm.dodisplay();
            display.display();
        }

        static void show() {
          _route_nav[lv.navlevel-1]();
        }

        static void smixerVpanelAction() {
          if (lv.navlevel == 3) {
            lv.navrange = 127;
            gg.smixervknobs[lv.sublevels[2]] = lv.sublevels[3];
          }
          if (lv.navlevel == 2) {
            lv.navrange = 15;
            lv.sublevels[3] = gg.smixervknobs[lv.sublevels[2]];
          }
          if (lv.navlevel > 3) {
            dm.returntonav(2);
          }
        }

        static void clearsizeofsamplefolder() {
          for (int i = 0; i < 99; i++) {
            self->sizeofsamplefolder[i] = 0;
          }
        }
        static void initializesamplebase() {
          for (int i = 0; i < 99; i++) {
            batchclearsamplebase(i);
          }
        }

        static void batchclearsamplebase(int lefolder) {
          for (int i = 0; i < 999; i++) {
            clearsamplebase(lefolder, i);
          }
        }

        static void clearsamplebase(int lefolder, int lefile) {
          for (int i = 0; i < 9; i++) {
            self->samplebase[lefolder][lefile][i] = (char)'\0';
          }
        }

        String lower_extension_case(String f_name){
          char named[50];  // Ensure the array is large enough
          strcpy(named, f_name.c_str());
          named[strlen(named) - 4] = '\0';
          return (String)named + ".raw";
        }

        bool test_flash_sample_name(String f_s_name){
          return SerialFlash.exists(f_s_name.c_str());
        }

        static void listSoundset() {

          File sounddir = SD.open("SOUNDSET/");

          while (true) {
            File soundentry = sounddir.openNextFile();

            if (!soundentry) {

              break;
            }

            if (soundentry.isDirectory()) {
              
              addtofolderix((char *)soundentry.name(), self->sampledirsregistered);
              //addtofullsamplerfolderpath(self->sampledirsregistered,(char *)soundentry.name());
              self->sampledirsregistered++;
            }
            soundentry.close();
          }
          sounddir.close();
        }

        static void smixerVpanel() {

          smixerVpanelAction();

          display.clearDisplay();
          canvastitle.fillScreen(SSD1306_BLACK);
          canvasBIG.fillScreen(SSD1306_BLACK);
          // canvastitle.setCursor(70,0);
          canvasBIG.setTextSize(1);
          canvasBIG.setCursor(0, 0);
          canvasBIG.print(gg.smixervknobs[lv.sublevels[2]]);

          byte centercirclex;
          byte centercircley;
          byte xcentershifter;
          byte knobradius = 6;
          byte trianglepointx;
          byte trianglepointy;
          byte yshifter = 46;
          float coeffangle;
          xcentershifter = (knobradius * 2) + 4;
          byte slct = lv.sublevels[2];

          for (int i = 0; i < 8; i++) {

            coeffangle = (6.2831 - (gg.smixervknobs[i] / 127.0) * 6.2831) + 3.1416;
            centercirclex = knobradius + (xcentershifter * i);
            centercircley = 16 + knobradius;
            canvastitle.setCursor(centercirclex - 5 + 3, 8);
            canvastitle.setTextSize(1);
            canvastitle.print(i + 1);
            canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
            trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
            trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));
            display.drawLine(centercirclex, centercircley, trianglepointx, trianglepointy, SSD1306_WHITE);
          }

          if (slct < 8) {
            centercirclex = knobradius + (xcentershifter * slct);
            canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
            canvastitle.setCursor(95, 0);
            canvastitle.print((gg.smixervknobs[slct] / 127.0) * 100.0, 1);
          }
          centercircley = yshifter + knobradius;
          for (int i = 0; i < 8; i++) {

            coeffangle = (6.2831 - (gg.smixervknobs[i + 8] / 127.0) * 6.2831) + 3.1416;
            centercirclex = knobradius + (xcentershifter * i);
            canvasBIG.setCursor(centercirclex - 5, centercircley - (2 + knobradius * 2) - 1);
            canvasBIG.setTextSize(1);
            canvasBIG.print(i + 1 + 8);
            canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
            trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
            trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));
            display.drawLine(centercirclex, centercircley, trianglepointx, trianglepointy, SSD1306_WHITE);
          }

          if (slct > 7) {
            centercirclex = knobradius + (xcentershifter * (slct - 8));
            canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
            canvastitle.setCursor(95, 0);
            canvastitle.print((gg.smixervknobs[slct] / 127.0) * 100.0, 1);
          }
          dm.dodisplay();
        }

        static void dolistsamplermenu() {
          char samplerlabels[SP_LABELS_COUNT][12] = {"Load", "Delete", "Assign", "Mixer"};
          int startx = 5;
          int starty = 16;
          char *textin = (char *)samplerlabels[lv.sublevels[1]];
          canvastitle.fillScreen(SSD1306_BLACK);
          canvastitle.setCursor(0, 0);
          canvastitle.setTextSize(2);
          canvastitle.println(textin);
          canvasBIG.setTextSize(1);
          canvasBIG.fillScreen(SSD1306_BLACK);
          for (int i = 0; i < SP_LABELS_COUNT - 1 - (lv.sublevels[1]); i++) {
              canvasBIG.setCursor(startx, starty + ((i)*10));
              canvasBIG.println(samplerlabels[lv.sublevels[1] + 1 + i]);
          }
          for (int i = 0; i < lv.sublevels[1]; i++) {
              canvasBIG.setCursor(startx, (10 * (SP_LABELS_COUNT - lv.sublevels[1]) + 6 + ((i)*10)));
              canvasBIG.println(samplerlabels[i]);
          }
        }
        
        String samplefullpath(int lefolder, int lefile){
          String based = self->samplebase[lefolder][lefile];
          String folded = self->samplefoldersregistered[lefolder] ;
          return "SOUNDSET/" + folded + "/" + based +".RAW";
        }

        static void addtofolderix(char *lepathtoadd, int ix) {

          for (int i = 0; i < (int)strlen((char *)lepathtoadd); i++) {
            self->samplefoldersregistered[ix][i] = (char)(lepathtoadd[i]);
          }
        }

        static void setupsamplefoldersregistered() {
          for (int i = 0; i < 99; i++) {
            for (int j = 0; j < SP_NAME_MAX; j++) {
              self->samplefoldersregistered[i][j] = (char)'\0';
            }
          }
          self->samplefoldersregistered[0][0] = (char)("/"[0]);
          self->sampledirsregistered++;
        }
        static void setlefilenamed(int lefolder, int lefile, char *lefname) {
          int fnamesize = strlen((char *)lefname);         
          for (int i = 0; i < fnamesize; i++) {
            if (i < fnamesize - 4) {
              self->samplebase[lefolder][lefile][i] = lefname[i];
            }
          }
          self->samplebase[lefolder][lefile][fnamesize - 4] = (char)'\0';
        }

        static void playsamplepreview() {
          String playable_file = self->samplefullpath(lv.sublevels[3],lv.sublevels[4]);
          if (!self->test_flash_sample_name(playable_file)){
            playable_file = self->lower_extension_case(playable_file);
          }
          if (!SD.exists(playable_file.c_str())){
            return;
          }
          playRawL.play(playable_file.c_str());
          playRawR.play(playable_file.c_str());
        }

        static void preview_flash_assignee() {
          String playable_file = (String)bb.Flashsamplename[lv.sublevels[4]];
          if (!self->test_flash_sample_name(playable_file)){
            playable_file = self->lower_extension_case(playable_file);

          }
          if (!self->test_flash_sample_name(playable_file)){
            return;
          }
          FlashRaw.play(playable_file.c_str());
        }

        static void copybacklaflashfile(int leflashfile) {
          SerialFlashFile originflashfile = SerialFlash.open((const char *)bb.Flashsamplename[leflashfile]);
          String new_name = self->newmkdirpath + "/" + (String)bb.Flashsamplename[leflashfile];
          File mynewsample = SD.open(new_name.c_str(), FILE_WRITE);
          size_t n_size;
          uint8_t buf[64];
          while ((n_size = originflashfile.read(buf, sizeof(buf))) > 0) {
            mynewsample.write(buf, n_size);
          }
          originflashfile.close();
          mynewsample.close();
        }

        static void copyflashtoSD() {
          for (int i = 0; i < 128; i++) {
            if (gg.Sampleassigned[i] != 0) {
              copybacklaflashfile(gg.Sampleassigned[i]);
            }
          }
        }
        static void domkdir() {
          self->newmkdirpath = get_new_dir_name("SOUNDSET/MABANK") ;
          self->catalog->make_sub_folder("SOUNDSET", self->newmkdirpath.c_str());
          copyflashtoSD();
          dosoundlist();
        }
        static void Assingexplorer() {
          if (lv.navlevel > 3) {
            self->assigning_sample_to_note = false ;
            if (lv.sublevels[2] == 1) {
              Sampleassigner();
              preview_flash_assignee();
            }
            if (lv.sublevels[2] == 0 && lv.sublevels[3] == 1) {
              autoassignsamples();
              dm.returntonav(2,127,lv.sublevels[2]);
            }
            if (lv.sublevels[2] == 2 && lv.sublevels[3] == 1) {
              clearassignedsamples();
              dm.returntonav(2,127,lv.sublevels[2]);
            }

            if (lv.sublevels[2] == 3 && lv.sublevels[3] == 1) {
              //saves assigned flash samples to a new folder on SD
              domkdir();
              dosoundlist();
              dm.returntonav(2,127,lv.sublevels[2]);
            }

            if (lv.sublevels[3] == 0) {
              dm.returntonav(2,127,lv.sublevels[2]);
            }
          }

          if (lv.navlevel == 3) {
            self->assigning_sample_to_note = true ;
            if (lv.sublevels[2] == 2) {
              display.clearDisplay();
              doConfirmClearassign();
            }
            if (lv.sublevels[2] == 3) {
              display.clearDisplay();
              doConfirmmkdir();
            }
            if (lv.sublevels[2] == 0) {
              display.clearDisplay();
              doConfirmautoassign();
            }
            if (lv.sublevels[2] == 1) {
              lv.navrange = 127;
              Sampleassigner();
            }
          }
        }
        static void samplerexplorer() {
          if (lv.navlevel > 3) {
            if (lv.sublevels[2] == 1) {
              Sampleassigner();
            }
            if (lv.sublevels[2] == 2 && lv.sublevels[3] == 1) {
              loadSelectedSamples();
              dm.returntonav(2,3,lv.sublevels[2]);
            }
            if (lv.sublevels[2] == 3 && lv.sublevels[3] == 1) {
              initializesamplesselectedlist();
              initializesamplesfoldersselectedlist();
              dm.returntonav(2,3,lv.sublevels[2]) ;
            }

            if (lv.sublevels[2] != 0 && lv.sublevels[2] != 1 && lv.sublevels[3] == 0) {
              dm.returntonav(2,3,lv.sublevels[2]);
            }

            if (lv.sublevels[2] == 1) {
              if (!self->samplesfoldersselected[lv.sublevels[3]]) {
                self->samplesfoldersselected[lv.sublevels[3]] = 1;
                self->numofsamplesfoldersselected++;
              } else {
                self->samplesfoldersselected[lv.sublevels[3]] = 0;
                self->numofsamplesfoldersselected--;
              }
              dm.returntonav(3);
            }

            if (lv.sublevels[2] == 0) {

              if (lv.previousnavlevel != lv.navlevel) {
                lv.previousnavlevel = lv.navlevel;
                lv.navrange = self->sizeofsamplefolder[lv.sublevels[3]] - 1;
              }

              if (lv.navlevel > 4) {
                if (self->samplesselected[lv.sublevels[3]][lv.sublevels[4]] == 0) {
                  self->samplesselected[lv.sublevels[3]][lv.sublevels[4]] = 1;
                  self->numberofsamplesselected[lv.sublevels[3]]++;
                  playsamplepreview();
                } else {
                  self->samplesselected[lv.sublevels[3]][lv.sublevels[4]] = 0;
                  self->numberofsamplesselected[lv.sublevels[3]]--;
                }
              dm.returntonav(4,lv.navrange,lv.sublevels[4]);
              }
              showsamplerfilesList();
            }
          }

          if (lv.navlevel == 3) {

            if (lv.sublevels[2] == 2) {
              display.clearDisplay();
              doConfirmLoadsamples();
            }

            if (lv.sublevels[2] == 3) {
              display.clearDisplay();
              doConfirmClearList();
            }

            if ((lv.sublevels[2] == 0 || lv.sublevels[2] == 1) && (lv.sublevels[1] == 0)) {
              if (lv.previousnavlevel != lv.navlevel) {
                lv.navrange = self->sampledirsregistered - 1;
              }
              showsamplerfolderList();
            }
          }
        }

        static void Flashsamplerexplorer() {
          if (lv.navlevel > 3) {

            if (lv.sublevels[2] == 2 && lv.sublevels[3] == 1) {
              DelSelectedFlashSamples();
              dm.returntonav(2,3,lv.sublevels[2]);
            }
            if (lv.sublevels[2] == 3 && lv.sublevels[3] == 1) {
              initializeFlashsamplesselected();
              dm.returntonav(2,3,lv.sublevels[2]);
            }
            if (lv.sublevels[2] == 1 && lv.sublevels[3] == 1) {
              RemoveAllfromFlash();
              dm.returntonav(2,3,lv.sublevels[2]);
            }
            if (lv.sublevels[2] != 0 && lv.sublevels[3] == 0) {
              dm.returntonav(2,3,lv.sublevels[2]);

            }
            //if (!test_flash_sample_name(playable_file)){
            //  playable_file = lower_extension_case(playable_file);
            //}
            if (lv.sublevels[2] == 0) {
              if (self->Flashsamplesselected[lv.sublevels[3]] == 0) {
                self->Flashsamplesselected[lv.sublevels[3]] = 1;
                if (SerialFlash.exists((const char *)bb.Flashsamplename[lv.sublevels[3]])) FlashRaw.play((const char *)bb.Flashsamplename[lv.sublevels[3]]);
                self->numberofFlashsamplesselected++;
                
              } else {
                self->Flashsamplesselected[lv.sublevels[3]] = 0;
                self->numberofFlashsamplesselected--;
              }
              dm.returntonav(3,lv.navrange,lv.sublevels[3]);
            }
          }
          if (lv.navlevel == 3) {
            if (lv.sublevels[2] == 2) {
              display.clearDisplay();
              doConfirmDelsamples();
            }
            if (lv.sublevels[2] == 3) {
              display.clearDisplay();
              doConfirmClearSelectedFlashList();
            }
            if (lv.sublevels[2] == 1) {
              display.clearDisplay();
              doConfirmRemoveAll();
            }
            if (lv.sublevels[2] == 0) {
              if (lv.previousnavlevel != lv.navlevel) {
                lv.navrange = self->numberofFlashfiles - 1;
              }

              showFlashSamplesList();
            }
          }
        }

        static void showsamplerfolderList() {
          drawSamplerFoldersList();
          dm.dodisplay();
        }
        static void showsamplerfilesList() {
          drawsamplerfilesList();
          dm.dodisplay();
        }
        static void showFlashSamplesList() {
          drawFlashSamplesList();
          dm.dodisplay();
        }

        static void drawtickboxflashBIG(int lestartx, int lestarty, int lasizex, int lasizey,
                                typeof(SSD1306_WHITE) lacolor, int lefile) {
          if (self->Flashsamplesselected[lefile] == 1) {
            canvasBIG.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          } else {
            canvasBIG.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          }
        }
        static void drawtickboxflashtitle(int lestartx, int lestarty, int lasizex, int lasizey,
                                  typeof(SSD1306_WHITE) lacolor, int lefile) {
          if (self->Flashsamplesselected[lefile] == 1) {
            canvastitle.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          } else {
            canvastitle.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          }
        }

        static void drawtickboxfolderBIG(int lestartx, int lestarty, int lasizex, int lasizey,
                                  typeof(SSD1306_WHITE) lacolor, int lefolder) {
          if (self->samplesfoldersselected[lefolder]) {
            canvasBIG.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          } else {
            canvasBIG.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          }
        }
        static void drawtickboxfoldertitle(int lestartx, int lestarty, int lasizex,
                                    int lasizey, typeof(SSD1306_WHITE) lacolor,
                                    int lefolder) {
          if (self->samplesfoldersselected[lefolder]) {
            canvastitle.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          } else {
            canvastitle.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          }
        }

        static void drawtickboxincanvasBIG(int lestartx, int lestarty, int lasizex,
                                    int lasizey, typeof(SSD1306_WHITE) lacolor,
                                    int lefolder, int lefile) {
          if (self->samplesselected[lefolder][lefile] == 1) {
            canvasBIG.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          } else {
            canvasBIG.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          }
        }
        static void drawtickboxincanvastitle(int lestartx, int lestarty, int lasizex,
                                      int lasizey, typeof(SSD1306_WHITE) lacolor,
                                      int lefolder, int lefile) {
          if (self->samplesselected[lefolder][lefile] == 1) {
            canvastitle.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          } else {
            canvastitle.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          }
        }

        static void addtoFlashsamplelist(char *lesample) {
          // files on the flashchip have to be uppercase
          for (int i = 0; i < 13; i++) {
            bb.Flashsamplename[self->numberofFlashfiles][i] =
                toupper((unsigned char)(lesample[i]));
            if (i < (int)(strlen((char *)lesample) - 4)) {
              self->Flashsamplebase[self->numberofFlashfiles][i] =
                  toupper((unsigned char)(lesample[i]));
            }
          }
          self->numberofFlashfiles++;
        }

        static void rebuildflashsamplesnames() {
          initializeFlashsamplename();
          listFlashfiles();
        }

        static void initializeFlashsamplename() {
          self->numberofFlashfiles = 0;
          for (int i = 0; i < 999; i++) {
            clearFlashsamplename(i);
          }
          initializeFlashsamplebase();
        }

        static void clearFlashsamplename(int lefile) {
          for (int i = 0; i < 13; i++) {
            bb.Flashsamplename[lefile][i] = (char)'\0';
          }
        }

        static void initializeFlashsamplebase() {
          for (int i = 0; i < 999; i++) {
            clearFlashsamplebase(i);
          }
        }

        static void clearFlashsamplebase(int lefile) {
          for (int i = 0; i < 9; i++) {
            self->Flashsamplebase[lefile][i] = (char)'\0';
          }
        }

        static void initializesamplesfoldersselectedlist() {
          self->numofsamplesfoldersselected = 0;
          for (int i = 0; i < 99; i++) {
            self->samplesfoldersselected[i] = 0;
          }
        }

        static void initializeFlashsamplesselected() {
          self->numberofFlashsamplesselected = 0;
          for (int i = 0; i < 999; i++) {
            self->Flashsamplesselected[i] = 0;
          }
        }

        static void initializesamplesselectedlist() {

          for (int i = 0; i < 99; i++) {
            clearsamplesselectedlist(i);
            self->numberofsamplesselected[i] = 0;
          }
        }

        static void clearsamplesselectedlist(int lefolder) {
          for (int i = 0; i < 999; i++) {
            self->samplesselected[lefolder][i] = 0;
          }
        }

        static void drawFlashSamplesList() {

          int startx = 15;
          int starty = 16;
          canvastitle.fillScreen(SSD1306_BLACK);
          canvastitle.setTextSize(1);
          canvastitle.setCursor(startx, 0);
          canvastitle.print((char *)self->Flashsamplebase[lv.sublevels[lv.navlevel]]);
          drawtickboxflashtitle(startx - 13, 0, 6, 6, SSD1306_WHITE, lv.sublevels[lv.navlevel]);
          canvasBIG.setTextSize(1);
          canvasBIG.fillScreen(SSD1306_BLACK);

          int maxsizefirstpart = self->numberofFlashfiles - 1 - (lv.sublevels[lv.navlevel]);
          if (maxsizefirstpart > 6) {
            maxsizefirstpart = 6;
          }
          for (int i = 0; i < maxsizefirstpart; i++) {
            canvasBIG.setCursor(startx, starty + ((i)*10));
            canvasBIG.println((char *)self->Flashsamplebase[lv.sublevels[lv.navlevel] + 1 + i]);
            drawtickboxflashBIG(startx - 13, starty + ((i)*10), 6, 6, SSD1306_WHITE, lv.sublevels[lv.navlevel] + 1 + i);
          }
          int maxsizelastpart = lv.sublevels[lv.navlevel];
          if (maxsizelastpart > 6) {
            maxsizelastpart = 6;
          }
          for (int i = 0; i < maxsizelastpart; i++) {
            canvasBIG.setCursor(startx, (10 * (self->numberofFlashfiles - lv.sublevels[lv.navlevel])) + 6 + ((i)*10));
            canvasBIG.println((char *)self->Flashsamplebase[i]);
            drawtickboxflashBIG(startx - 13, (10 * (self->numberofFlashfiles - lv.sublevels[lv.navlevel])) + 6 + ((i)*10), 6, 6, SSD1306_WHITE, i);
          }
        }

        static void drawsamplerfilesList() {
          int startx = 15;
          int starty = 16;
          canvastitle.fillScreen(SSD1306_BLACK);
          canvastitle.setTextSize(1);
          canvastitle.setCursor(startx, 0);
          canvastitle.print((char *)self->samplebase[lv.sublevels[3]][lv.sublevels[lv.navlevel]]);
          drawtickboxincanvastitle(startx - 13, 0, 6, 6, SSD1306_WHITE, lv.sublevels[3], lv.sublevels[lv.navlevel]);
          canvasBIG.setTextSize(1);
          canvasBIG.fillScreen(SSD1306_BLACK);
          int maxsizefirstpart =
              self->sizeofsamplefolder[lv.sublevels[3]] - 1 - (lv.sublevels[lv.navlevel]);
          if (maxsizefirstpart > 6) {
            maxsizefirstpart = 6;
          }
          for (int i = 0; i < maxsizefirstpart; i++) {
            canvasBIG.setCursor(startx, starty + ((i)*10));
            canvasBIG.println((char *)self->samplebase[lv.sublevels[3]][lv.sublevels[lv.navlevel] + 1 + i]);
            drawtickboxincanvasBIG(startx - 13, starty + ((i)*10), 6, 6, SSD1306_WHITE, lv.sublevels[3], lv.sublevels[lv.navlevel] + 1 + i);
          }
          int maxsizelastpart = lv.sublevels[lv.navlevel];
          if (maxsizelastpart > 6) {
            maxsizelastpart = 6;
          }
          for (int i = 0; i < maxsizelastpart; i++) {
            canvasBIG.setCursor(startx, (10 * (self->sizeofsamplefolder[lv.sublevels[3]] - lv.sublevels[lv.navlevel])) + 6 + ((i)*10));
            canvasBIG.println((char *)self->samplebase[lv.sublevels[3]][i]);
            drawtickboxincanvasBIG(startx - 13, (10 * (self->sizeofsamplefolder[lv.sublevels[3]] - lv.sublevels[lv.navlevel])) + 6 + ((i)*10), 6, 6, SSD1306_WHITE, lv.sublevels[3], i);
          }
        }

        static void drawSamplerFoldersList() {
          int startx = 15;
          int starty = 16;
          canvastitle.fillScreen(SSD1306_BLACK);
          canvastitle.setTextSize(1);
          canvastitle.setCursor(startx, 0);
          canvastitle.print((char *)self->samplefoldersregistered[lv.sublevels[lv.navlevel]]);
          if (lv.sublevels[2] == 1) {
            drawtickboxfoldertitle(startx - 13, 0, 6, 6, SSD1306_WHITE, lv.sublevels[lv.navlevel]);
          }
          canvasBIG.setTextSize(1);
          canvasBIG.fillScreen(SSD1306_BLACK);

          int maxsizefirstpart = self->sampledirsregistered - 1 - (lv.sublevels[lv.navlevel]);
          if (maxsizefirstpart > 6) {
            maxsizefirstpart = 6;
          }
          for (int i = 0; i < maxsizefirstpart; i++) {
            canvasBIG.setCursor(startx, starty + ((i)*10));
            canvasBIG.println((char *)self->samplefoldersregistered[lv.sublevels[lv.navlevel] + 1 + i]);
            if (lv.sublevels[2] == 1) {
              drawtickboxfolderBIG(startx - 13, starty + ((i)*10), 6, 6, SSD1306_WHITE, lv.sublevels[lv.navlevel] + 1 + i);
            }
          }
          int maxsizelastpart = lv.sublevels[lv.navlevel];
          if (maxsizelastpart > 6) {
            maxsizelastpart = 6;
          }
          for (int i = 0; i < maxsizelastpart; i++) {
            canvasBIG.setCursor(startx, (10 * (self->sampledirsregistered - lv.sublevels[lv.navlevel])) + 6 + ((i)*10));
            canvasBIG.println((char *)self->samplefoldersregistered[i]);
            if (lv.sublevels[2] == 1) {
              //TODO: check if all is ok here, was previousely (10 * (keepcount - lv.sublevels[lv.navlevel])) + 6 + ((i)*10)
              drawtickboxfolderBIG(startx - 13, (10 * (lv.sublevels[lv.navlevel])) + 6 + ((i)*10), 6, 6, SSD1306_WHITE, i);
            }
          }
        }

        static void dolistLoadSampleMenu() {
          lv.navrange = 4 - 1;
          const int sizeofmenuloadsample = 4;
          char menuloadsample[sizeofmenuloadsample][16] = {
              "Select", "Whole pack", "Load Selection", "Clear Selection"};
          int startx = 5;
          int starty = 16;
          char *textin = (char *)menuloadsample[lv.sublevels[2]];
          dm.clear_buffs_1_1();
          canvastitle.println(textin);
          for (int i = 0; i < sizeofmenuloadsample - 1 - (lv.sublevels[2]); i++) {
            canvasBIG.setCursor(startx, starty + ((i)*10));
            canvasBIG.println(menuloadsample[lv.sublevels[2] + 1 + i]);
          }
          for (int i = 0; i < lv.sublevels[2]; i++) {
            canvasBIG.setCursor(startx, (10 * (sizeofmenuloadsample - lv.sublevels[2]) + 6 + ((i)*10)));
            canvasBIG.println(menuloadsample[i]);
          }
        }

        static void dolistDelSampleMenu() {
          lv.navrange = 4 - 1;

          const int sizeofmenudelsample = 4;
          char menudelsample[sizeofmenudelsample][16] = {
              "Select", "Remove All", "Remove Selected", "Clear Selection"};
          int startx = 5;
          int starty = 16;
          char *textin = (char *)menudelsample[lv.sublevels[2]];
            dm.clear_buffs_1_1();
          canvastitle.println(textin);
          for (int i = 0; i < sizeofmenudelsample - 1 - (lv.sublevels[2]); i++) {
            canvasBIG.setCursor(startx, starty + ((i)*10));
            canvasBIG.println(menudelsample[lv.sublevels[2] + 1 + i]);
          }
          for (int i = 0; i < lv.sublevels[2]; i++) {
            canvasBIG.setCursor(startx, (10 * (sizeofmenudelsample - lv.sublevels[2]) + 6 + ((i)*10)));
            canvasBIG.println(menudelsample[i]);
          }
        }

        static void dolistAssignSampleMenu() {
          lv.navrange = 4 - 1;
          self->assigning_sample_to_note = false ;
          const int sizeofmenuassignsample = 4;
          char menuassignsample[sizeofmenuassignsample][19] = {
              "Auto-assign", "Individual", "Clear All", "Save assigned"};
          int startx = 5;
          int starty = 16;
          char *textin = (char *)menuassignsample[lv.sublevels[2]];
            dm.clear_buffs_1_1();
          canvastitle.println(textin);
          for (int i = 0; i < sizeofmenuassignsample - 1 - (lv.sublevels[2]); i++) {
            canvasBIG.setCursor(startx, starty + ((i)*10));
            canvasBIG.println(menuassignsample[lv.sublevels[2] + 1 + i]);
          }
          for (int i = 0; i < lv.sublevels[2]; i++) {
            canvasBIG.setCursor(startx, (10 * (sizeofmenuassignsample - lv.sublevels[2]) + 6 + ((i)*10)));
            canvasBIG.println(menuassignsample[i]);
          }
        }

        static void autoassignsamples() {
          Doautoassign();
          return;
        }

        static void Doautoassign() {
          for (int i = 0; i < self->numberofFlashfiles - 1; i++) {
            if (i + 4 < 128) {
              gg.Sampleassigned[i + 4] = i;
            } else {
              break;
            }
          }
        }

        static void clearassignedsamples() {
          doclearassign();
          return;
        }

        static void doclearassign() {
          for (int i = 0; i < 128; i++) {
            gg.Sampleassigned[i] = 0;
          }
        }

        static void doConfirmmkdir() {
          char messageconfirm[32] = "Make dir ?";
          doConfirmpanel((char *)messageconfirm);

        }
        static void doConfirmClearassign() {
          char messageconfirm[32] = "Clear selection ?";
          doConfirmpanel((char *)messageconfirm);

        }

        static void doConfirmClearList() {
          char messageconfirm[32] = "Clear selection ?";
          doConfirmpanel((char *)messageconfirm);

        }
        static void doConfirmautoassign() {
          char messageconfirm[32] = "Confirm autoassign ?";
          doConfirmpanel((char *)messageconfirm);
        }

        static void doConfirmDelsamples() {
          char messageconfirm[32] = "Confirm Delete ?";
          doConfirmpanel((char *)messageconfirm);
        }
        static void doConfirmClearSelectedFlashList() {
          // same
          doConfirmClearList();
        }
        static void doConfirmRemoveAll() {
          // same
          doConfirmDelsamples();
        }

        static void doConfirmLoadsamples() {
          char messageconfirm[32] = "Confirm Loading ?";
          doConfirmpanel((char *)messageconfirm);
        }

        static void RemoveAllfromFlash() {
          initializeconsolemsg();
          consoler.wipe();
          //SerialFlash.quickFormat();
          unsigned long startMillis = millis();
          if (!SerialFlash.begin(self->FlashChipSelect)) return;

          unsigned char id[5];
          SerialFlash.readID(id);
          unsigned long size = SerialFlash.capacity(id);

          if (size > 0) {
            Serial.print(F("Flash Memory has "));
            Serial.print(size);
            Serial.println(F(" bytes."));
            Serial.println(F("Erasing ALL Flash Memory:"));
            // Estimate the (lengthy) wait time.
            Serial.print(F("  estimated wait: "));
            int seconds = (float)size / self->eraseBytesPerSecond(id) + 0.5;
            Serial.print(seconds);
            Serial.println(F(" seconds."));
            Serial.println(F("  Yes, full chip erase is SLOW!"));
            SerialFlash.eraseAll();
            unsigned long dotMillis = millis();
            unsigned char dotcount = 0;
            while (SerialFlash.ready() == false) {
              if (millis() - dotMillis > 1000) {
                dotMillis = dotMillis + 1000;
                Serial.print(".");
                consoler.print(".");
                consoler.refresh();
                //pseudoconsole(" . ",0);
                dotcount = dotcount + 1;
                if (dotcount >= 30) {
                  consoler.print(".");
                  consoler.refresh();
                  Serial.println();
                  dotcount = 0;
                }
              }
            }
            if (dotcount > 0) Serial.println();
            Serial.println(F("Erase completed"));
            unsigned long elapsed = millis() - startMillis;
            Serial.print(F("  actual wait: "));
            Serial.print(elapsed / 1000ul);
            Serial.println(F(" seconds."));
          }
          dm.returntonav(2,3,lv.sublevels[2]);
        }

        float eraseBytesPerSecond(const unsigned char *id) {
          if (id[0] == 0x20)
            return 152000.0; // Micron
          if (id[0] == 0x01)
            return 500000.0; // Spansion
          if (id[0] == 0xEF)
            return 419430.0; // Winbond
          if (id[0] == 0xC2)
            return 279620.0; // Macronix
          return 320000.0;   // guess?
        }

        static void DelSelectedFlashSamples() {
          initializeconsolemsg();
          for (int j = 0; j < 999; j++) {
            //pleasewait(j, 999);
            if (self->Flashsamplesselected[j] == 1) {
              if (SerialFlash.exists((const char *)bb.Flashsamplename[j])) {
                pseudoconsole((const char *)bb.Flashsamplename[j]);
                SerialFlash.remove((const char *)bb.Flashsamplename[j]);
              }
            }
          }
          initializeFlashsamplesselected();
          rebuildflashsamplesnames();
        }

        static void addfolderstoselectionset() {
          if (self->numofsamplesfoldersselected > 0) {
            for (int i = 0; i < 99; i++) {
              if (self->samplesfoldersselected[i]) {
                for (int j = 0; j < 999; j++) {
                  self->samplesselected[i][j] = 1;
                }
              }
            }
          }
        }

        static void loadSelectedSamples() {
          initializeconsolemsg();
          unsigned long lengthz;
          File currentsample;
          SerialFlashFile currentFlashfile;
          addfolderstoselectionset();
          delay(100);
          if (!SerialFlash.begin(self->FlashChipSelect)) {
            pseudoconsole((char *)"Unable to access SPI Flash chip");
          }

          for (int i = 0; i < 99; i++) {
            //pleasewait(i, 99);
            for (int j = 0; j < 999; j++) {
              if (self->samplesselected[i][j]) {
                currentsample = SD.open(self->samplefullpath(i,j).c_str());
                //was break instead of continue
                if (!currentsample) continue;
                const char *currentflashname = currentsample.name();
                if (strlen(currentflashname) > 12) {
                  Serial.print(" Skipping ");
                  Serial.print(currentflashname);
                  Serial.print(" <--- name too long !");
                  continue;
                }
                lengthz = currentsample.size();
                pseudoconsole(currentflashname);
                if (SerialFlash.exists(currentflashname)) continue; 

                if (SerialFlash.create(currentflashname, lengthz)) {
                  SerialFlashFile currentFlashfile = SerialFlash.open(currentflashname);
                  if (currentFlashfile) {
                    unsigned long count = 0;
                    unsigned char dotcount = 9;
                    while (count < lengthz) {
                      char buf[256];
                      unsigned int n;
                      n = currentsample.read(buf, 256);
                      currentFlashfile.write(buf, n);
                      count += n;
                      if (++dotcount > 100) {
                        dotcount = 0;
                      }
                    }
                    currentFlashfile.close();
                  } 
                } 
                currentsample.close();
              }
            }
            delay(10);
          }
          initializesamplesselectedlist();
          initializesamplesfoldersselectedlist();
          listFlashfiles();
        }


        static void loadSampledSound() {
          unsigned long lengthz;
          File currentsample;
          SerialFlashFile currentFlashfile;
          delay(1);
          if (!SerialFlash.begin(self->FlashChipSelect)) {
            pseudoconsole("Unable to access SPI Flash chip");
          }
          currentsample = SD.open(newloopedpath.c_str());
          const char *currentflashname = currentsample.name();
          lengthz = currentsample.size();
          
          if (SerialFlash.exists(currentflashname)) return;

          if (SerialFlash.create(currentflashname, lengthz)) {
            SerialFlashFile currentFlashfile = SerialFlash.open(currentflashname);
            if (currentFlashfile) {
              unsigned long count = 0;
              unsigned char dotcount = 9;
              while (count < lengthz) {
                char buf[256];
                unsigned int n;
                n = currentsample.read(buf, 256);
                currentFlashfile.write(buf, n);
                count = count + n;
                if (++dotcount > 100) {
                  dotcount = 0;
                }
              }
              currentFlashfile.close();
              }
            }
          currentsample.close();
          initializesamplesselectedlist();
          initializesamplesfoldersselectedlist();
          listFlashfiles();
        
        }

        static void listFlashfiles() {
          initializeFlashsamplename();
          initializeFlashsamplebase();
          if (!SerialFlash.begin(self->FlashChipSelect)) {
            pseudoconsole((char *)"Unable to access SPI Flash chip");
          }
          char filename[13];
          uint32_t filesize;
          while (SerialFlash.readdir(filename, sizeof(filename), filesize)) {
              addtoFlashsamplelist(filename);
          }
        }

        //unused
        static void getavailablespace() {
          long laspace = 0;
          SerialFlashFile lefile;
          for (int i = 0; i < self->numberofFlashfiles; i++) {
            lefile = SerialFlash.open((char *)bb.Flashsamplename[i]);
            if (lefile) {
              if (lefile.size() > 536900000) {
                laspace += lefile.size() - 536900000;
              } else {
                laspace += lefile.size();
              }
              lefile.close();
            }
          }
          lefile.close();
          //float freespace = ((laspace / 16777216.0) * 100);
        }

        static void Sampleassigner() {
          if (lv.navlevel == 3) {
            self->assigning_sample_to_note = true ;
            lv.navrange = 127;
            listsamplesassigner();
            dm.dodisplay();
          }
          if (lv.navlevel == 4) {
            lv.navrange = self->numberofFlashfiles - 1;
            listsamplesassigner2();
            dm.dodisplay();
          }
          if (lv.navlevel >= 5) {
            samplesetter();
            dm.returntonav(3,127,lv.sublevels[3]);
          }
        }

        static void listsamplesassigner() {
          dm.clean_title_2_2();
          char *toprint = (char *)"Note";
          canvastitle.println(toprint);
          canvastitle.setCursor(85, 0);
          canvastitle.println(lv.sublevels[3]);
          if (gg.Sampleassigned[lv.sublevels[3]] != 0) {
            canvasBIG.setCursor(85, 16);
            canvasBIG.println(gg.Sampleassigned[lv.sublevels[3]]);
            canvasBIG.setCursor(0, 40);
            canvasBIG.println((char *)self->Flashsamplebase[gg.Sampleassigned[lv.sublevels[3]]]);
          }
        }

        static void samplesetter() { gg.Sampleassigned[lv.sublevels[3]] = lv.sublevels[4]; }

        static void listsamplesassigner2() {
          dm.clean_title_2_2();
          char *toprint = (char *)"Note";
          canvastitle.println(toprint);
          canvastitle.setCursor(85, 0);
          canvastitle.println(lv.sublevels[3]);
          canvasBIG.setCursor(85, 16);
          canvasBIG.println(lv.sublevels[4]);
          canvasBIG.setCursor(0, 40);
          canvasBIG.println((char *)self->Flashsamplebase[lv.sublevels[4]]);
        }

        

        static void listSoundsetsubdir(int ledir) {
          if (SD.exists((char *)self->sampledirpath)) {
            File susudir = SD.open((char *)self->sampledirpath);
            while (true) {
              File subentry = susudir.openNextFile();
              if (!subentry) {
                break;
              }
              char shorter_name[12];
              String new_namer = subentry.name();
              int fnamesize = strlen((char *)subentry.name());
              if (fnamesize > 12) {
                for (int i=fnamesize-11; i < fnamesize; i++) { 
                  shorter_name[i-fnamesize+11] = new_namer[i];
                }
                shorter_name[11] = (char)'\0';
                String full_file = (String)self->sampledirpath + subentry.name();
                String full_new_file = (String)self->sampledirpath + (String)shorter_name;
                SD.rename(full_file.c_str(), full_new_file.c_str());
                continue;
              }
              if (!subentry.isDirectory()) {
                  setlefilenamed(ledir, self->sizeofsamplefolder[ledir], (char*)subentry.name());
                (self->sizeofsamplefolder[ledir])++;
              }
              subentry.close();
            }
            susudir.close();
          }
        }

        static void makesoundsetfullpathfromchars(int eldir) {
          for (int i = 9; i < (int)(strlen((char *)self->samplefoldersregistered[eldir]) + 9);i++) {
            self->sampledirpath[i] = self->samplefoldersregistered[eldir][i - 9];
          }
          int lelast = (int)strlen((char *)self->sampledirpath);
          self->sampledirpath[lelast] = (char)'/';
          self->sampledirpath[lelast + 1] = (char)'\0';
        }
        static void voidsampledirpath() {
          for (int i = 0; i < 99; i++) {
            self->sampledirpath[i] = (char)'\0';
          }
          for (int i = 0; i < 9; i++) {
            self->sampledirpath[i] = (char)("SOUNDSET/"[i]);
          }
        }

        static void dosoundlist() {
          initializeFlashsamplesselected();
          initializesamplesfoldersselectedlist();
          rebuildflashsamplesnames();
          clearsizeofsamplefolder();
          self->sampledirsregistered = 0;
          setupsamplefoldersregistered();

          initializesamplebase();
          listSoundset();
          for (int i = 1; i < self->sampledirsregistered; i++) {
            //pleasewait(i, self->sampledirsregistered);
            voidsampledirpath();
            makesoundsetfullpathfromchars(i);
            listSoundsetsubdir(i);
          }
        }
//TODO: refactor nav routing after using fileslister
        static constexpr void (*_route_nav[7])() = {&sampler_nav_zero, &sampler_nav_one, &sampler_nav_two, 
                                                    &sampler_nav_two, &sampler_nav_two,&sampler_nav_two, &sampler_nav_two};
                                    
        
    private:
        
        static constexpr void (*_nav_sampler[SP_LABELS_COUNT])() = {&dolistLoadSampleMenu, &dolistDelSampleMenu, &dolistAssignSampleMenu, &smixerVpanel};
        static SamplerMenuRouter* self;
};

SamplerMenuRouter* SamplerMenuRouter::self = nullptr;
EXTMEM SamplerMenuRouter _sp;
