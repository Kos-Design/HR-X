

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

        static void sampler_nav_two(){
          if (sublevels[1] == 0) {
              display.clearDisplay();
              samplerexplorer();
          }
          if (sublevels[1] == 1) {
              display.clearDisplay();
              Flashsamplerexplorer();
          }
          if (sublevels[1] == 2) {
              display.clearDisplay();
              Assingexplorer();
          }

          if (sublevels[1] == 3) {
              smixerVpanel();
          }
        }

        static void sampler_nav_one(){
          self->assigning_sample_to_note = false ;
          display.clearDisplay();
          _nav_sampler[sublevels[1]]();
          dm.dodisplay();
        }
        
        static void sampler_nav_zero(){
            reinitsublevels(2);
            navrange = SP_LABELS_COUNT - 1;
            display.clearDisplay();
            dolistsamplermenu();
            dm.dodisplay();
            display.display();
        }

        static void show() {
          _route_nav[navlevel-1]();
        }

        static void smixerVpanelAction() {
          if (navlevel == 3) {
            navrange = 127;
            gg.smixervknobs[sublevels[2]] = sublevels[3];
          }
          if (navlevel == 2) {
            navrange = 15;
            sublevels[3] = gg.smixervknobs[sublevels[2]];
          }
          if (navlevel > 3) {
            returntonav(2);
          }
        }

        static void smixerVpanel() {

          smixerVpanelAction();

          display.clearDisplay();
          canvastitle.fillScreen(SSD1306_BLACK);
          canvasBIG.fillScreen(SSD1306_BLACK);
          // canvastitle.setCursor(70,0);
          canvasBIG.setTextSize(1);
          canvasBIG.setCursor(0, 0);
          canvasBIG.print(gg.smixervknobs[sublevels[2]]);

          byte centercirclex;
          byte centercircley;
          byte xcentershifter;
          byte knobradius = 6;
          byte trianglepointx;
          byte trianglepointy;
          byte yshifter = 46;
          float coeffangle;
          xcentershifter = (knobradius * 2) + 4;
          byte slct = sublevels[2];

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
          char *textin = (char *)samplerlabels[sublevels[1]];
          canvastitle.fillScreen(SSD1306_BLACK);
          canvastitle.setCursor(0, 0);
          canvastitle.setTextSize(2);
          canvastitle.println(textin);
          canvasBIG.setTextSize(1);
          canvasBIG.fillScreen(SSD1306_BLACK);
          for (int i = 0; i < SP_LABELS_COUNT - 1 - (sublevels[1]); i++) {
              canvasBIG.setCursor(startx, starty + ((i)*10));
              canvasBIG.println(samplerlabels[sublevels[1] + 1 + i]);
          }
          for (int i = 0; i < sublevels[1]; i++) {
              canvasBIG.setCursor(startx, (10 * (SP_LABELS_COUNT - sublevels[1]) + 6 + ((i)*10)));
              canvasBIG.println(samplerlabels[i]);
          }
        }
        
        static void setlefilenamed(int lefolder, int lefile, char *lefname) {
          int fnamesize = strlen((char *)lefname);         
          for (int i = 0; i < fnamesize; i++) {
            if (i < fnamesize - 4) {
              samplebase[lefolder][lefile][i] = lefname[i];
            }
          }
          samplebase[lefolder][lefile][fnamesize - 4] = (char)'\0';
        }

        static void playsamplepreview() {
          String playable_file = samplefullpath(sublevels[3],sublevels[4]);
          if (!test_flash_sample_name(playable_file)){
            playable_file = lower_extension_case(playable_file);
          }
          if (!SD.exists(playable_file.c_str())){
            return;
          }
          playRawL.play(playable_file.c_str());
          playRawR.play(playable_file.c_str());
        }

        static void preview_flash_assignee() {
          String playable_file = (String)Flashsamplename[sublevels[4]];
          if (!test_flash_sample_name(playable_file)){
            playable_file = lower_extension_case(playable_file);

          }
          if (!test_flash_sample_name(playable_file)){
            return;
          }
          FlashRaw.play(playable_file.c_str());
        }

        static void copybacklaflashfile(int leflashfile) {
          SerialFlashFile originflashfile = SerialFlash.open((const char *)Flashsamplename[leflashfile]);
          String new_name = self->newmkdirpath + "/" + (String)Flashsamplename[leflashfile];
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
          if (navlevel > 3) {
            self->assigning_sample_to_note = false ;
            if (sublevels[2] == 1) {
              Sampleassigner();
              preview_flash_assignee();
            }
            if (sublevels[2] == 0 && sublevels[3] == 1) {
              autoassignsamples();
              returntonav(2,127,sublevels[2]);
            }
            if (sublevels[2] == 2 && sublevels[3] == 1) {
              clearassignedsamples();
              returntonav(2,127,sublevels[2]);
            }

            if (sublevels[2] == 3 && sublevels[3] == 1) {
              //saves assigned flash samples to a new folder on SD
              domkdir();
              dosoundlist();
              returntonav(2,127,sublevels[2]);
            }

            if (sublevels[3] == 0) {
              returntonav(2,127,sublevels[2]);
            }
          }

          if (navlevel == 3) {
            self->assigning_sample_to_note = true ;
            if (sublevels[2] == 2) {
              display.clearDisplay();
              doConfirmClearassign();
            }
            if (sublevels[2] == 3) {
              display.clearDisplay();
              doConfirmmkdir();
            }
            if (sublevels[2] == 0) {
              display.clearDisplay();
              doConfirmautoassign();
            }
            if (sublevels[2] == 1) {
              navrange = 127;
              Sampleassigner();
            }
          }
        }
        static void samplerexplorer() {
          if (navlevel > 3) {
            if (sublevels[2] == 1) {
              Sampleassigner();
            }
            if (sublevels[2] == 2 && sublevels[3] == 1) {
              loadSelectedSamples();
              returntonav(2,3,sublevels[2]);
            }
            if (sublevels[2] == 3 && sublevels[3] == 1) {
              initializesamplesselectedlist();
              initializesamplesfoldersselectedlist();
              returntonav(2,3,sublevels[2]) ;
            }

            if (sublevels[2] != 0 && sublevels[2] != 1 && sublevels[3] == 0) {
              returntonav(2,3,sublevels[2]);
            }

            if (sublevels[2] == 1) {
              if (!samplesfoldersselected[sublevels[3]]) {
                samplesfoldersselected[sublevels[3]] = 1;
                numofsamplesfoldersselected++;
              } else {
                samplesfoldersselected[sublevels[3]] = 0;
                numofsamplesfoldersselected--;
              }
              returntonav(3);
            }

            if (sublevels[2] == 0) {

              if (previousnavlevel != navlevel) {
                previousnavlevel = navlevel;
                navrange = sizeofsamplefolder[sublevels[3]] - 1;
              }

              if (navlevel > 4) {
                if (samplesselected[sublevels[3]][sublevels[4]] == 0) {
                  samplesselected[sublevels[3]][sublevels[4]] = 1;
                  numberofsamplesselected[sublevels[3]]++;
                  playsamplepreview();
                } else {
                  samplesselected[sublevels[3]][sublevels[4]] = 0;
                  numberofsamplesselected[sublevels[3]]--;
                }
              returntonav(4,navrange,sublevels[4]);
              }
              showsamplerfilesList();
            }
          }

          if (navlevel == 3) {

            if (sublevels[2] == 2) {
              display.clearDisplay();
              doConfirmLoadsamples();
            }

            if (sublevels[2] == 3) {
              display.clearDisplay();
              doConfirmClearList();
            }

            if ((sublevels[2] == 0 || sublevels[2] == 1) && (sublevels[1] == 0)) {
              if (previousnavlevel != navlevel) {
                navrange = sampledirsregistered - 1;
              }
              showsamplerfolderList();
            }
          }
        }

        static void Flashsamplerexplorer() {
          if (navlevel > 3) {

            if (sublevels[2] == 2 && sublevels[3] == 1) {
              DelSelectedFlashSamples();
              returntonav(2,3,sublevels[2]);
            }
            if (sublevels[2] == 3 && sublevels[3] == 1) {
              initializeFlashsamplesselected();
              returntonav(2,3,sublevels[2]);
            }
            if (sublevels[2] == 1 && sublevels[3] == 1) {
              RemoveAllfromFlash();
              returntonav(2,3,sublevels[2]);
            }
            if (sublevels[2] != 0 && sublevels[3] == 0) {
              returntonav(2,3,sublevels[2]);

            }
            if (sublevels[2] == 0) {
              if (Flashsamplesselected[sublevels[3]] == 0) {
                Flashsamplesselected[sublevels[3]] = 1;
                if (SerialFlash.exists((const char *)Flashsamplename[sublevels[3]])) FlashRaw.play((const char *)Flashsamplename[sublevels[3]]);
                numberofFlashsamplesselected++;
                
              } else {
                Flashsamplesselected[sublevels[3]] = 0;
                numberofFlashsamplesselected--;
              }
              returntonav(3,navrange,sublevels[3]);
            }
          }
          if (navlevel == 3) {
            if (sublevels[2] == 2) {
              display.clearDisplay();
              doConfirmDelsamples();
            }
            if (sublevels[2] == 3) {
              display.clearDisplay();
              doConfirmClearSelectedFlashList();
            }
            if (sublevels[2] == 1) {
              display.clearDisplay();
              doConfirmRemoveAll();
            }
            if (sublevels[2] == 0) {
              if (previousnavlevel != navlevel) {
                navrange = numberofFlashfiles - 1;
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
          if (Flashsamplesselected[lefile] == 1) {
            canvasBIG.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          } else {
            canvasBIG.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          }
        }
        static void drawtickboxflashtitle(int lestartx, int lestarty, int lasizex, int lasizey,
                                  typeof(SSD1306_WHITE) lacolor, int lefile) {
          if (Flashsamplesselected[lefile] == 1) {
            canvastitle.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          } else {
            canvastitle.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          }
        }

        static void drawtickboxfolderBIG(int lestartx, int lestarty, int lasizex, int lasizey,
                                  typeof(SSD1306_WHITE) lacolor, int lefolder) {
          if (samplesfoldersselected[lefolder]) {
            canvasBIG.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          } else {
            canvasBIG.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          }
        }
        static void drawtickboxfoldertitle(int lestartx, int lestarty, int lasizex,
                                    int lasizey, typeof(SSD1306_WHITE) lacolor,
                                    int lefolder) {
          if (samplesfoldersselected[lefolder]) {
            canvastitle.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          } else {
            canvastitle.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          }
        }

        static void drawtickboxincanvasBIG(int lestartx, int lestarty, int lasizex,
                                    int lasizey, typeof(SSD1306_WHITE) lacolor,
                                    int lefolder, int lefile) {
          if (samplesselected[lefolder][lefile] == 1) {
            canvasBIG.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          } else {
            canvasBIG.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          }
        }
        static void drawtickboxincanvastitle(int lestartx, int lestarty, int lasizex,
                                      int lasizey, typeof(SSD1306_WHITE) lacolor,
                                      int lefolder, int lefile) {
          if (samplesselected[lefolder][lefile] == 1) {
            canvastitle.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          } else {
            canvastitle.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          }
        }

        static void addtoFlashsamplelist(char *lesample) {
          // files on the flashchip have to be uppercase
          for (int i = 0; i < 13; i++) {
            Flashsamplename[numberofFlashfiles][i] =
                toupper((unsigned char)(lesample[i]));
            if (i < (int)(strlen((char *)lesample) - 4)) {
              Flashsamplebase[numberofFlashfiles][i] =
                  toupper((unsigned char)(lesample[i]));
            }
          }
          numberofFlashfiles++;
        }

        static void rebuildflashsamplesnames() {
          initializeFlashsamplename();
          listFlashfiles();
        }

        static void initializeFlashsamplename() {
          numberofFlashfiles = 0;
          for (int i = 0; i < 999; i++) {
            clearFlashsamplename(i);
          }
          initializeFlashsamplebase();
        }

        static void clearFlashsamplename(int lefile) {
          for (int i = 0; i < 13; i++) {
            Flashsamplename[lefile][i] = (char)'\0';
          }
        }

        static void initializeFlashsamplebase() {
          for (int i = 0; i < 999; i++) {
            clearFlashsamplebase(i);
          }
        }

        static void clearFlashsamplebase(int lefile) {
          for (int i = 0; i < 9; i++) {
            Flashsamplebase[lefile][i] = (char)'\0';
          }
        }

        static void initializesamplesfoldersselectedlist() {
          numofsamplesfoldersselected = 0;
          for (int i = 0; i < 99; i++) {
            samplesfoldersselected[i] = 0;
          }
        }

        static void initializeFlashsamplesselected() {
          numberofFlashsamplesselected = 0;
          for (int i = 0; i < 999; i++) {
            Flashsamplesselected[i] = 0;
          }
        }

        static void initializesamplesselectedlist() {

          for (int i = 0; i < 99; i++) {
            clearsamplesselectedlist(i);
            numberofsamplesselected[i] = 0;
          }
        }

        static void clearsamplesselectedlist(int lefolder) {
          for (int i = 0; i < 999; i++) {
            samplesselected[lefolder][i] = 0;
          }
        }

        static void drawFlashSamplesList() {

          int startx = 15;
          int starty = 16;
          canvastitle.fillScreen(SSD1306_BLACK);
          canvastitle.setTextSize(1);
          canvastitle.setCursor(startx, 0);
          canvastitle.print((char *)Flashsamplebase[sublevels[navlevel]]);
          drawtickboxflashtitle(startx - 13, 0, 6, 6, SSD1306_WHITE, sublevels[navlevel]);
          canvasBIG.setTextSize(1);
          canvasBIG.fillScreen(SSD1306_BLACK);

          int maxsizefirstpart = numberofFlashfiles - 1 - (sublevels[navlevel]);
          if (maxsizefirstpart > 6) {
            maxsizefirstpart = 6;
          }
          for (int i = 0; i < maxsizefirstpart; i++) {
            canvasBIG.setCursor(startx, starty + ((i)*10));
            canvasBIG.println((char *)Flashsamplebase[sublevels[navlevel] + 1 + i]);
            drawtickboxflashBIG(startx - 13, starty + ((i)*10), 6, 6, SSD1306_WHITE, sublevels[navlevel] + 1 + i);
          }
          int maxsizelastpart = sublevels[navlevel];
          if (maxsizelastpart > 6) {
            maxsizelastpart = 6;
          }
          for (int i = 0; i < maxsizelastpart; i++) {
            canvasBIG.setCursor(startx, (10 * (numberofFlashfiles - sublevels[navlevel])) + 6 + ((i)*10));
            canvasBIG.println((char *)Flashsamplebase[i]);
            drawtickboxflashBIG(startx - 13, (10 * (numberofFlashfiles - sublevels[navlevel])) + 6 + ((i)*10), 6, 6, SSD1306_WHITE, i);
          }
        }

        static void drawsamplerfilesList() {
          int startx = 15;
          int starty = 16;
          canvastitle.fillScreen(SSD1306_BLACK);
          canvastitle.setTextSize(1);
          canvastitle.setCursor(startx, 0);
          canvastitle.print((char *)samplebase[sublevels[3]][sublevels[navlevel]]);
          drawtickboxincanvastitle(startx - 13, 0, 6, 6, SSD1306_WHITE, sublevels[3], sublevels[navlevel]);
          canvasBIG.setTextSize(1);
          canvasBIG.fillScreen(SSD1306_BLACK);
          int maxsizefirstpart =
              sizeofsamplefolder[sublevels[3]] - 1 - (sublevels[navlevel]);
          if (maxsizefirstpart > 6) {
            maxsizefirstpart = 6;
          }
          for (int i = 0; i < maxsizefirstpart; i++) {
            canvasBIG.setCursor(startx, starty + ((i)*10));
            canvasBIG.println((char *)samplebase[sublevels[3]][sublevels[navlevel] + 1 + i]);
            drawtickboxincanvasBIG(startx - 13, starty + ((i)*10), 6, 6, SSD1306_WHITE, sublevels[3], sublevels[navlevel] + 1 + i);
          }
          int maxsizelastpart = sublevels[navlevel];
          if (maxsizelastpart > 6) {
            maxsizelastpart = 6;
          }
          for (int i = 0; i < maxsizelastpart; i++) {
            canvasBIG.setCursor(startx, (10 * (sizeofsamplefolder[sublevels[3]] - sublevels[navlevel])) + 6 + ((i)*10));
            canvasBIG.println((char *)samplebase[sublevels[3]][i]);
            drawtickboxincanvasBIG(startx - 13, (10 * (sizeofsamplefolder[sublevels[3]] - sublevels[navlevel])) + 6 + ((i)*10), 6, 6, SSD1306_WHITE, sublevels[3], i);
          }
        }

        static void drawSamplerFoldersList() {
          int startx = 15;
          int starty = 16;
          canvastitle.fillScreen(SSD1306_BLACK);
          canvastitle.setTextSize(1);
          canvastitle.setCursor(startx, 0);
          canvastitle.print((char *)samplefoldersregistered[sublevels[navlevel]]);
          if (sublevels[2] == 1) {
            drawtickboxfoldertitle(startx - 13, 0, 6, 6, SSD1306_WHITE, sublevels[navlevel]);
          }
          canvasBIG.setTextSize(1);
          canvasBIG.fillScreen(SSD1306_BLACK);

          int maxsizefirstpart = sampledirsregistered - 1 - (sublevels[navlevel]);
          if (maxsizefirstpart > 6) {
            maxsizefirstpart = 6;
          }
          for (int i = 0; i < maxsizefirstpart; i++) {
            canvasBIG.setCursor(startx, starty + ((i)*10));
            canvasBIG.println((char *)samplefoldersregistered[sublevels[navlevel] + 1 + i]);
            if (sublevels[2] == 1) {
              drawtickboxfolderBIG(startx - 13, starty + ((i)*10), 6, 6, SSD1306_WHITE, sublevels[navlevel] + 1 + i);
            }
          }
          int maxsizelastpart = sublevels[navlevel];
          if (maxsizelastpart > 6) {
            maxsizelastpart = 6;
          }
          for (int i = 0; i < maxsizelastpart; i++) {
            canvasBIG.setCursor(startx, (10 * (sampledirsregistered - sublevels[navlevel])) + 6 + ((i)*10));
            canvasBIG.println((char *)samplefoldersregistered[i]);
            if (sublevels[2] == 1) {
              //TODO: check if all is ok here, was previousely (10 * (keepcount - sublevels[navlevel])) + 6 + ((i)*10)
              drawtickboxfolderBIG(startx - 13, (10 * (sublevels[navlevel])) + 6 + ((i)*10), 6, 6, SSD1306_WHITE, i);
            }
          }
        }

        static void dolistLoadSampleMenu() {
          navrange = 4 - 1;
          const int sizeofmenuloadsample = 4;
          char menuloadsample[sizeofmenuloadsample][16] = {
              "Select", "Whole pack", "Load Selection", "Clear Selection"};
          int startx = 5;
          int starty = 16;
          char *textin = (char *)menuloadsample[sublevels[2]];
          dm.clear_buffs_1_1();
          canvastitle.println(textin);
          for (int i = 0; i < sizeofmenuloadsample - 1 - (sublevels[2]); i++) {
            canvasBIG.setCursor(startx, starty + ((i)*10));
            canvasBIG.println(menuloadsample[sublevels[2] + 1 + i]);
          }
          for (int i = 0; i < sublevels[2]; i++) {
            canvasBIG.setCursor(startx, (10 * (sizeofmenuloadsample - sublevels[2]) + 6 + ((i)*10)));
            canvasBIG.println(menuloadsample[i]);
          }
        }

        static void dolistDelSampleMenu() {
          navrange = 4 - 1;

          const int sizeofmenudelsample = 4;
          char menudelsample[sizeofmenudelsample][16] = {
              "Select", "Remove All", "Remove Selected", "Clear Selection"};
          int startx = 5;
          int starty = 16;
          char *textin = (char *)menudelsample[sublevels[2]];
            dm.clear_buffs_1_1();
          canvastitle.println(textin);
          for (int i = 0; i < sizeofmenudelsample - 1 - (sublevels[2]); i++) {
            canvasBIG.setCursor(startx, starty + ((i)*10));
            canvasBIG.println(menudelsample[sublevels[2] + 1 + i]);
          }
          for (int i = 0; i < sublevels[2]; i++) {
            canvasBIG.setCursor(startx, (10 * (sizeofmenudelsample - sublevels[2]) + 6 + ((i)*10)));
            canvasBIG.println(menudelsample[i]);
          }
        }

        static void dolistAssignSampleMenu() {
          navrange = 4 - 1;
          self->assigning_sample_to_note = false ;
          const int sizeofmenuassignsample = 4;
          char menuassignsample[sizeofmenuassignsample][19] = {
              "Auto-assign", "Individual", "Clear All", "Save assigned"};
          int startx = 5;
          int starty = 16;
          char *textin = (char *)menuassignsample[sublevels[2]];
            dm.clear_buffs_1_1();
          canvastitle.println(textin);
          for (int i = 0; i < sizeofmenuassignsample - 1 - (sublevels[2]); i++) {
            canvasBIG.setCursor(startx, starty + ((i)*10));
            canvasBIG.println(menuassignsample[sublevels[2] + 1 + i]);
          }
          for (int i = 0; i < sublevels[2]; i++) {
            canvasBIG.setCursor(startx, (10 * (sizeofmenuassignsample - sublevels[2]) + 6 + ((i)*10)));
            canvasBIG.println(menuassignsample[i]);
          }
        }

        static void autoassignsamples() {
          Doautoassign();
          return;
        }

        static void Doautoassign() {
          for (int i = 0; i < numberofFlashfiles - 1; i++) {
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
          returntonav(2,3,sublevels[2]);
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
            if (Flashsamplesselected[j] == 1) {
              if (SerialFlash.exists((const char *)Flashsamplename[j])) {
                pseudoconsole((const char *)Flashsamplename[j]);
                SerialFlash.remove((const char *)Flashsamplename[j]);
              }
            }
          }
          initializeFlashsamplesselected();
          rebuildflashsamplesnames();
        }

        static void addfolderstoselectionset() {
          if (numofsamplesfoldersselected > 0) {
            for (int i = 0; i < 99; i++) {
              if (samplesfoldersselected[i]) {
                for (int j = 0; j < 999; j++) {
                  samplesselected[i][j] = 1;
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
              if (samplesselected[i][j]) {
                currentsample = SD.open(samplefullpath(i,j).c_str());
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
          for (int i = 0; i < numberofFlashfiles; i++) {
            lefile = SerialFlash.open((char *)Flashsamplename[i]);
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
          if (navlevel == 3) {
            self->assigning_sample_to_note = true ;
            navrange = 127;
            listsamplesassigner();
            dm.dodisplay();
          }
          if (navlevel == 4) {
            navrange = numberofFlashfiles - 1;
            listsamplesassigner2();
            dm.dodisplay();
          }
          if (navlevel >= 5) {
            samplesetter();
            returntonav(3,127,sublevels[3]);
          }
        }

        static void listsamplesassigner() {
          dm.clean_title_2_2();
          char *toprint = (char *)"Note";
          canvastitle.println(toprint);
          canvastitle.setCursor(85, 0);
          canvastitle.println(sublevels[3]);
          if (gg.Sampleassigned[sublevels[3]] != 0) {
            canvasBIG.setCursor(85, 16);
            canvasBIG.println(gg.Sampleassigned[sublevels[3]]);
            canvasBIG.setCursor(0, 40);
            canvasBIG.println((char *)Flashsamplebase[gg.Sampleassigned[sublevels[3]]]);
          }
        }

        static void samplesetter() { gg.Sampleassigned[sublevels[3]] = sublevels[4]; }

        static void listsamplesassigner2() {
          dm.clean_title_2_2();
          char *toprint = (char *)"Note";
          canvastitle.println(toprint);
          canvastitle.setCursor(85, 0);
          canvastitle.println(sublevels[3]);
          canvasBIG.setCursor(85, 16);
          canvasBIG.println(sublevels[4]);
          canvasBIG.setCursor(0, 40);
          canvasBIG.println((char *)Flashsamplebase[sublevels[4]]);
        }

        

        static void listSoundsetsubdir(int ledir) {
          if (SD.exists((char *)sampledirpath)) {
            File susudir = SD.open((char *)sampledirpath);
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
                String full_file = (String)sampledirpath + subentry.name();
                String full_new_file = (String)sampledirpath + (String)shorter_name;
                SD.rename(full_file.c_str(), full_new_file.c_str());
                continue;
              }
              if (!subentry.isDirectory()) {
                  setlefilenamed(ledir, sizeofsamplefolder[ledir], (char*)subentry.name());
                (sizeofsamplefolder[ledir])++;
              }
              subentry.close();
            }
            susudir.close();
          }
        }

        static void dosoundlist() {
          initializeFlashsamplesselected();
          initializesamplesfoldersselectedlist();
          rebuildflashsamplesnames();
          clearsizeofsamplefolder();
          sampledirsregistered = 0;
          setupsamplefoldersregistered();

          initializesamplebase();
          listSoundset();
          for (int i = 1; i < sampledirsregistered; i++) {
            //pleasewait(i, sampledirsregistered);
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
SamplerMenuRouter _sp;
