

class SamplerMenuRouter : public SectionHolder {
    public:
        SamplerMenuRouter() {
          self = this ;
                    this->home_navrange=sizeofsamplerlabels-1;
                    this->relative_navlevel=1;
                    this->max_navlevel=5;
                    this->sublevels_address={7,0,0};
                    //home method not really used yet
                    //this->set_home(call_fx_mainpanel);
                    }
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
                display.clearDisplay();

                displayRecmenu();
            }
            if (sublevels[1] == 4) {
                // display.clearDisplay();

                smixerVpanel();
            }
        }

        static void sampler_nav_one(){
            display.clearDisplay();
            switch (sublevels[1]) {

                case 0:
                navrange = 4 - 1;
                dolistLoadSampleMenu();

                break;

                case 1:
                // deletesamples menu
                navrange = 4 - 1;
                dolistDelSampleMenu();
                break;

                case 2:
                // assign samples menu
                navrange = 4 - 1;
                dolistAssignSampleMenu();
                break;
                case 3:
                // assign samples menu
                navrange = 3;
                displayRecmenu();
                break;
                case 4:
                // assign samples menu
                // navrange = 16;
                smixerVpanel();
                break;
                default:
                break;
            }
            dodisplay();
            //display.display();
        }

        static void sampler_nav_zero(){
            reinitsublevels(2);
            navrange = 4;
            cellsizer = 4;
            celltall = 8;
            startx = 0;
            starty = 17;
            display.clearDisplay();
            dolistsamplermenu();
            dodisplay();
            display.display();
        }

        static void show() {
          _route_nav[navlevel-1]();
        }

        static void smixerVpanelAction() {
          if (navlevel == 3) {
            navrange = 127;
            smixervknobs[sublevels[2]] = sublevels[3];
          }
          if (navlevel == 2) {
            navrange = 15;
            sublevels[3] = smixervknobs[sublevels[2]];
          }
          if (navlevel > 3) {

            returntonav(2);
          }
        }

        static void smixerVpanelSelector() {
          byte startlex = 4;

          byte ecartl = 19;

          int totbartall = 32;
          int topwbarstart = 16;
          int wbarwidth2 = 7;

          int slct = sublevels[2];
          canvasBIG.drawLine(
              startlex - 2 + slct * ecartl, topwbarstart + totbartall + 2,
              startlex - 2 + slct * ecartl,
              topwbarstart + totbartall + 1 + wbarwidth2 + 3 - 1, SSD1306_WHITE);
          canvasBIG.drawLine(startlex - 2 + 1 + slct * ecartl,
                            topwbarstart + totbartall + wbarwidth2 + 4,
                            wbarwidth2 + 3 + startlex - 4 + slct * ecartl,
                            topwbarstart + totbartall + wbarwidth2 + 4, SSD1306_WHITE);

          if (slct == 0) {

            sublevels[3] = arpegiatortype;
            // canvasBIG.drawCircle(centercirclex, centercircley, knobradius-2,
            // SSD1306_WHITE);
          }
          // damp
          if (slct == 1) {

            sublevels[3] = arpegmode;
            // canvasBIG.drawCircle(centercirclex, centercircley, knobradius-2,
            // SSD1306_WHITE);
          }
          if (slct == 2) {

            sublevels[3] = arpegstartoffset;
            // canvasBIG.drawCircle(centercirclex, centercircley, knobradius-2,
            // SSD1306_WHITE);
          }
          if (slct == 3) {

            sublevels[3] = arpegnumofnotes - 1;
            // canvasBIG.drawCircle(centercirclex, centercircley, knobradius-2,
            // SSD1306_WHITE);
          }
          if (slct == 4) {

            sublevels[3] = arpeggridC;
            // canvasBIG.drawCircle(centercirclex, centercircley, knobradius-2,
            // SSD1306_WHITE);
          }
          if (slct == 5) {

            sublevels[3] = arpeggridS;
            // canvasBIG.drawCircle(centercirclex, centercircley, knobradius-2,
            // SSD1306_WHITE);
          }
          if (slct == 6) {

            sublevels[3] = arpeglengh;
            // canvasBIG.drawCircle(centercirclex, centercircley, knobradius-2,
            // SSD1306_WHITE);
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
          canvasBIG.print(smixervknobs[sublevels[2]]);

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

            coeffangle = (6.2831 - (smixervknobs[i] / 127.0) * 6.2831) + 3.1416;
            centercirclex = knobradius + (xcentershifter * i);
            centercircley = 16 + knobradius;
            canvastitle.setCursor(centercirclex - 5 + 3, 8);
            canvastitle.setTextSize(1);

            canvastitle.print(i + 1);
            // canvastitle.print((char)masterfulllabels[i][2]);

            canvasBIG.drawCircle(centercirclex, centercircley, knobradius,
                                SSD1306_WHITE);

            trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
            trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));

            display.drawLine(centercirclex, centercircley, trianglepointx,
                            trianglepointy, SSD1306_WHITE);
          }

          if (slct < 8) {
            centercirclex = knobradius + (xcentershifter * slct);
            canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2,
                                SSD1306_WHITE);
            canvastitle.setCursor(95, 0);
            canvastitle.print((smixervknobs[slct] / 127.0) * 100.0, 1);
          }
          centercircley = yshifter + knobradius;
          for (int i = 0; i < 8; i++) {

            coeffangle = (6.2831 - (smixervknobs[i + 8] / 127.0) * 6.2831) + 3.1416;
            centercirclex = knobradius + (xcentershifter * i);
            canvasBIG.setCursor(centercirclex - 5,
                                centercircley - (2 + knobradius * 2) - 1);

            // canvastitle.setCursor(centercirclex-5,8);
            canvasBIG.setTextSize(1);

            canvasBIG.print(i + 1 + 8);
            // canvastitle.print((char)masterfulllabels[i][2]);

            canvasBIG.drawCircle(centercirclex, centercircley, knobradius,
                                SSD1306_WHITE);

            trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
            trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));

            display.drawLine(centercirclex, centercircley, trianglepointx,
                            trianglepointy, SSD1306_WHITE);
          }

          if (slct > 7) {
            centercirclex = knobradius + (xcentershifter * (slct - 8));
            canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2,
                                SSD1306_WHITE);
            canvastitle.setCursor(95, 0);
            canvastitle.print((smixervknobs[slct] / 127.0) * 100.0, 1);
          }
          dodisplay();
        }

        static void dolistsamplermenu() {
            
            char samplerlabels[sizeofsamplerlabels][12] = {"Load", "Delete", "Assign",
                                                            "Recorder", "Mixer"};
            int startx = 5;
            int starty = 16;
            char *textin = (char *)samplerlabels[sublevels[1]];
            canvastitle.fillScreen(SSD1306_BLACK);
            canvastitle.setCursor(0, 0);
            canvastitle.setTextSize(2);
            canvastitle.println(textin);
            canvasBIG.setTextSize(1);
            canvasBIG.fillScreen(SSD1306_BLACK);
            for (int i = 0; i < sizeofsamplerlabels - 1 - (sublevels[1]); i++) {
                canvasBIG.setCursor(startx, starty + ((i)*10));
                canvasBIG.println(samplerlabels[sublevels[1] + 1 + i]);
            }
            for (int i = 0; i < sublevels[1]; i++) {
                canvasBIG.setCursor(startx, (10 * (sizeofsamplerlabels - sublevels[1]) + 6 + ((i)*10)));
                canvasBIG.println(samplerlabels[i]);
            }
        }
        


        static void setlefilenamed(int lefolder, int lefile, char *lefname) {
          int fnamesize = strlen((char *)lefname);
          int foldersize = strlen((char *)samplefoldersregistered[lefolder]);
          for (int i = 0; i < fnamesize; i++) {
            samplefullpath[lefolder][lefile][foldersize + 10 + i] = lefname[i];
            if (i < fnamesize - 4) {
              samplebase[lefolder][lefile][i] = lefname[i];
            }
          }
          samplefullpath[lefolder][lefile][foldersize + 10 + fnamesize] = (char)'\0';
          samplebase[lefolder][lefile][fnamesize - 4] = (char)'\0';
        }

        static void voidlastpathlisted() {
          for (int i = 0; i < 50; i++) {
            lastpathlisted[i] = (char)'\0';
          }
        }

        static void setlastpathlisted(char *lepath) {
          voidlastpathlisted();
          for (int i = 0; i < (int)strlen((char *)lepath); i++) {
            lastpathlisted[i] = lepath[i];
          }
        }

        static void playsamplepreview() {
          //AudioNoInterrupts();
          String playable_file = (String)samplefullpath[sublevels[3]][sublevels[4]];
          if (!test_flash_sample_name(playable_file)){
            playable_file = lower_extension_case(playable_file);
          }
          if (!SD.exists(playable_file.c_str())){
            return;
          }
          playRawL.play(playable_file.c_str());
          playRawR.play(playable_file.c_str());
          //AudioInterrupts();
        }

        static void playflashsamplepreview() {
          String playable_file = (String)Flashsamplename[sublevels[3]];
          if (!test_flash_sample_name(playable_file)){
            playable_file = lower_extension_case(playable_file);
          }
          if (!test_flash_sample_name(playable_file)){
            return;
          }
          FlashRaw.play(playable_file.c_str());
        }
        static void playflashsamplepreviews4() {
          //AudioNoInterrupts();
          String playable_file = (String)Flashsamplename[sublevels[4]];
          if (!test_flash_sample_name(playable_file)){
            playable_file = lower_extension_case(playable_file);
          }
          if (!test_flash_sample_name(playable_file)){
            return;
          }
          FlashRaw.play(playable_file.c_str());
        }

        static void initializenewmksamplefullpath() {
          for (int i = 0; i < 32; i++) {
            newmksamplefullpath[i] = (char)'\0';
          }
        }

        static void copybacklaflashfile(int leflashfile) {
          File originflashfile = thyfs.open((const char *)Flashsamplename[leflashfile]);
          String new_name = newmkdirpath + "/" + (String)Flashsamplename[leflashfile];
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
            if (Sampleassigned[i] != 0) {
              copybacklaflashfile(Sampleassigned[i]);
            }
          }
        }
        static void domkdir() {
          newmkdirpath = get_new_dir_name("SOUNDSET/MABANK") ;
          if (!(SD.exists(newmkdirpath.c_str()))) {
            SD.mkdir(newmkdirpath.c_str());
          }
          copyflashtoSD();
          dosoundlist();
        }
        static void Assingexplorer() {
          if (navlevel > 3) {
            if (sublevels[2] == 1) {
              Sampleassigner();
              playflashsamplepreviews4();
              //returntonav(2,127,sublevels[2]);
              // return ;
            }
            if (sublevels[2] == 0 && sublevels[3] == 1) {
              autoassignsamples();
              returntonav(2,127,sublevels[2]);
              // return ;
            }
            if (sublevels[2] == 2 && sublevels[3] == 1) {
              clearassignedsamples();
              returntonav(2,127,sublevels[2]);
              // return ;
            }

            if (sublevels[2] == 3 && sublevels[3] == 1) {
              //saves assigned flash samples to a new folder on SD
              domkdir();
              dosoundlist();
              returntonav(2,127,sublevels[2]);
              // return ;
            }

            if (sublevels[3] == 0) {
              returntonav(2,127,sublevels[2]);
            }
          }

          if (navlevel == 3) {

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
              navlevel = 2;
            }
            if (sublevels[2] == 3 && sublevels[3] == 1) {
              initializesamplesselectedlist();
              initializesamplesfoldersselectedlist();
              navlevel = 2;
            }

            if (sublevels[2] != 0 && sublevels[2] != 1 && sublevels[3] == 0) {
              navlevel = 2;
              // refresh the menu
              call_sp_show();
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
                navlevel--;
                vraipos = sublevels[4];
                myEnc.write(vraipos * 4);
                // sublevels[navlevel] = sublevels[4] ;
              }

              showsamplerfilesList();
            }
          }

          if (navlevel == 3) {

            if (sublevels[2] == 2) {
              display.clearDisplay();
              doConfirmLoadsamples();

              // return ;
            }
            if (sublevels[2] == 3) {
              display.clearDisplay();
              doConfirmClearList();

              // return;
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
              // clear selection
              navlevel = 2;
            }
            if (sublevels[2] == 3 && sublevels[3] == 1) {
              initializeFlashsamplesselected();
              // clear selection
              navlevel = 2;
            }
            if (sublevels[2] == 1 && sublevels[3] == 1) {
              RemoveAllfromFlash();
              // clear selection
              navlevel = 2;
            }
            if (sublevels[2] != 0 && sublevels[3] == 0) {
              navlevel = 2;
              // refresh the menu
              call_sp_show();
            }
            if (sublevels[2] == 0) {
              if (Flashsamplesselected[sublevels[3]] == 0) {
                Flashsamplesselected[sublevels[3]] = 1;
                numberofFlashsamplesselected++;
                playflashsamplepreview();
              } else {
                Flashsamplesselected[sublevels[3]] = 0;
                numberofFlashsamplesselected--;
              }
              myEnc.write(sublevels[3] * 4);
              vraipos = sublevels[3];
              sublevels[navlevel] = sublevels[3];
              navlevel--;
            }
          }
          if (navlevel == 3) {
            if (sublevels[2] == 2) {
              display.clearDisplay();
              doConfirmDelsamples();

              //  return ;
            }
            if (sublevels[2] == 3) {
              display.clearDisplay();
              doConfirmClearSelectedFlashList();

              //  return;
            }
            if (sublevels[2] == 1) {
              display.clearDisplay();
              doConfirmRemoveAll();

              //  return;
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
          dodisplay();
        }
        static void showsamplerfilesList() {
          drawsamplerfilesList();
          dodisplay();
        }
        static void showFlashSamplesList() {
          drawFlashSamplesList();
          dodisplay();
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
              drawtickboxfolderBIG(startx - 13, (10 * (keepcount - sublevels[navlevel])) + 6 + ((i)*10), 6, 6, SSD1306_WHITE, i);
            }
          }
        }

        static void dolistLoadSampleMenu() {
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
              Sampleassigned[i + 4] = i;
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
            Sampleassigned[i] = 0;
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
          /*
          unsigned long startMillis = millis();
          while (!Serial && (millis() - startMillis < 10000))
            ;
          delay(100);

          if (!thyfs.begin(FlashChipSelect)) {
            while (1) {
              pseudoconsole("no SPI Flash chip");
              delay(1000);
            }
          }
          unsigned char id[5];
          //thyfs.readID(id);
          unsigned long size = thyfs.capacity(id);

          if (size > 0) {
            Serial.print("Flash Memory has ");
            Serial.print(size);
            Serial.println(" bytes.");
            Serial.println("Erasing ALL Flash Memory:");
            // Estimate the (lengthy) wait time.
            Serial.print("  estimated wait: ");
            int seconds = (float)size / self->eraseBytesPerSecond(id) + 0.5;

            Serial.print(seconds);
            Serial.println(" seconds.");
            Serial.println("  Yes, full chip erase is SLOW!");
            thyfs.eraseAll();
            unsigned long dotMillis = millis();
            unsigned char dotcount = 0;
            //takes several hours, use pseudo console
            while (thyfs.ready() == false) {
              if (millis() - dotMillis > 1000) {
                dotMillis = dotMillis + 1000;
                Serial.print(".");
                dotcount = dotcount + 1;
                pleasewait(dotcount, seconds);
              }
            }

            if (dotcount > 0) {
              Serial.println();
            Serial.println("Erase completed");
            unsigned long elapsed = millis() - startMillis;
            Serial.print("  actual wait: ");
            Serial.print(elapsed / 1000ul);
            Serial.println(" seconds.");
            dm.lemenuroot();
            }
          }
          */
          dm.lemenuroot();
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

          for (int j = 0; j < 999; j++) {
            pleasewait(j, 999);
            if (Flashsamplesselected[j] == 1) {
              if (thyfs.exists((const char *)Flashsamplename[j])) {
                thyfs.remove((const char *)Flashsamplename[j]);
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

        bool comparer(typeof(dummyier_file) file_1, typeof(dummy_flash_file) file_2) {
            const size_t buffer_Size = 128; // Define buffer size
            byte buffer_1[buffer_Size];
            byte buffer_2[buffer_Size];

            while (file_1.available() && file_2.available()) {
                size_t size_1 = file_1.read(buffer_1, buffer_Size);
                size_t size_2 = file_2.read(buffer_2, buffer_Size);

                if (size_1 != size_2 || memcmp(buffer_1, buffer_2, size_1) != 0) {
                    return false; // Files are not identical
                }
            }

            // Check if both files ended at the same time
            return !file_1.available() && !file_2.available();
        }

        static void loadSelectedSamples() {
          unsigned long lengthz;
          File currentsample;
          File currentFlashfile;
          addfolderstoselectionset();
          delay(100);
          if (!thyfs.begin(FlashChipSelect)) {
            errorsd("Unable to access SPI Flash chip");
          }

          for (int i = 0; i < 99; i++) {
            pleasewait(i, 99);
            for (int j = 0; j < 999; j++) {
              if (samplesselected[i][j] == 1) {
                currentsample = SD.open((const char *)samplefullpath[i][j]);
                if (!currentsample)
                  break;
                const char *currentflashname = currentsample.name();
                lengthz = currentsample.size();
                if (thyfs.exists(currentflashname)) {
                  currentFlashfile = thyfs.open(currentflashname);
                  if (currentFlashfile &&
                      currentFlashfile.size() == currentsample.size()) {
                    if (self->comparer(currentsample, currentFlashfile)) {
                      currentsample.close();
                      currentFlashfile.close();
                      continue; // advance to next file
                    } 
                  } 
                  thyfs.remove(currentflashname);
                }

                //if (thyfs.create(currentflashname, lengthz)) {
                  File currentFlashfile = thyfs.open(currentflashname,FILE_WRITE);
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
                //} 
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
          File currentFlashfile;
          delay(1);
          if (!thyfs.begin(FlashChipSelect)) {
            pseudoconsole("Unable to access SPI Flash chip");
          }
          currentsample = SD.open(newloopedpath.c_str());
          const char *currentflashname = currentsample.name();
          lengthz = currentsample.size();
          if (thyfs.exists(currentflashname)) {
            currentFlashfile = thyfs.open(currentflashname);
            if (currentFlashfile) {
              thyfs.remove(currentflashname);
              delay(1);
              }
            }

          //if (thyfs.create(currentflashname, lengthz)) {
            currentFlashfile = thyfs.open(currentflashname,FILE_WRITE);
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
            //}
          currentsample.close();
          initializesamplesselectedlist();
          initializesamplesfoldersselectedlist();
          listFlashfiles();

        }

        bool comparemesFiles(typeof(myMidiFile) &file, File &ffile) {
          file.seek(0);
          ffile.seek(0);
          unsigned long count = file.size();
          while (count > 0) {
            char buf1[128], buf2[128];
            unsigned long n = count;
            if (n > 127)
              n = 127;
            file.read(buf1, n);
            ffile.read(buf2, n);
            if (memcmp(buf1, buf2, n) != 0)
              return false; // differ
            count = count - n;
          }
          return true; // all data identical
        }

        static void errorsd(const char *message) {
          pseudoconsole(message);
        }

        static void listFlashfiles() {
          initializeFlashsamplename();
          initializeFlashsamplebase();
          if (!thyfs.begin(FlashChipSelect)) {
            errorsd("Unable to access SPI Flash chip");
          }

          File rooter = thyfs.open("/");

          while (true) {
              File file = rooter.openNextFile();
              if (!file) break;

              Serial.print(file.name());
              Serial.print("  ");
              Serial.println(file.size());
              //char flashenamex[13];
            //uint32_t flashfilesize;
           
              addtoFlashsamplelist((char*)file.name());
              file.close();
          }

          rooter.close();

          /*

          thyfs.opendir();
          while (1) {
            char flashenamex[13];
            uint32_t flashfilesize;
            if (thyfs.readdir(flashenamex, sizeof(flashenamex), flashfilesize)) {
              addtoFlashsamplelist(flashenamex);
            } else {
              break; // no more files
            }
          }
          */
        }

        //unused
        static void getavailablespace() {
          long laspace = 0;
          File lefile;
          for (int i = 0; i < numberofFlashfiles; i++) {
            lefile = thyfs.open((char *)Flashsamplename[i]);
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
            navrange = 127;
            listsamplesassigner();
            dodisplay();
          }
          if (navlevel == 4) {
            // to astatic void the weird last one <--- probably an overflow
            navrange = numberofFlashfiles - 1;
            listsamplesassigner2();
            dodisplay();
          }
          if (navlevel >= 5) {

            samplesetter();
            returntonav(3,127,sublevels[3]);
          }
        }
        static void listsamplesassigner() {

          display.clearDisplay();
          canvastitle.fillScreen(SSD1306_BLACK);
          canvastitle.setCursor(0, 0);
          toprint = (char *)"Note";
          canvastitle.setTextSize(2);
          canvastitle.println(toprint);
          canvastitle.setCursor(85, 0);
          canvastitle.println(sublevels[3]);

          canvasBIG.fillScreen(SSD1306_BLACK);
          if (Sampleassigned[sublevels[3]] != 0) {

            canvasBIG.setTextSize(2);
            canvasBIG.setCursor(85, 16);
            canvasBIG.println(Sampleassigned[sublevels[3]]);
            canvasBIG.setCursor(0, 40);
            canvasBIG.println((char *)Flashsamplebase[Sampleassigned[sublevels[3]]]);
          }
          //}
        }

        static void samplesetter() { Sampleassigned[sublevels[3]] = sublevels[4]; }

        static void listsamplesassigner2() {

          display.clearDisplay();
          canvastitle.fillScreen(SSD1306_BLACK);
          canvastitle.setCursor(0, 0);
          toprint = (char *)"Note";
          canvastitle.setTextSize(2);

          canvastitle.println(toprint);
          canvastitle.setCursor(85, 0);
          // toprint = (char*)"Knob";
          canvastitle.println(sublevels[3]);

          canvasBIG.fillScreen(SSD1306_BLACK);

          canvasBIG.setTextSize(2);
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

              if (!subentry.isDirectory()) {
                setlefilenamed(ledir, sizeofsamplefolder[ledir], (char*)subentry.name());
                (sizeofsamplefolder[ledir])++;
              }
              subentry.close();
            }
          }
        }

        static void dosoundlist() {
          if (!initdone) {
            pseudoconsole((char *)"Files on Flash");
          }
          initializeFlashsamplesselected();
          initializesamplesfoldersselectedlist();
          rebuildflashsamplesnames();
          clearsizeofsamplefolder();
          sampledirsregistered = 0;
          if (!initdone) {
            pseudoconsole((char *)"Files on SD");
          }
          setupsamplefoldersregistered();
          initializesamplefullpath();
          initializesamplebase();
          listSoundset();
          for (int i = 1; i < sampledirsregistered; i++) {
            pleasewait(i, sampledirsregistered);
            voidsampledirpath();
            makesoundsetfullpathfromchars(i);
            listSoundsetsubdir(i);
          }
          // printthem();
        }

        static constexpr void (*_route_nav[5])() = {&sampler_nav_zero, &sampler_nav_one, &sampler_nav_two, 
                                                    &sampler_nav_two, &sampler_nav_two};
        
    private:
        
        static constexpr void (*_nav_sampler[sizeofsamplerlabels])() = {&sampler_nav_one, &sampler_nav_one, &sampler_nav_one, &sampler_nav_one, &sampler_nav_one};
        static SamplerMenuRouter* self;
};

SamplerMenuRouter* SamplerMenuRouter::self = nullptr;
EXTMEM SamplerMenuRouter _sp;
