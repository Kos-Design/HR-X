#include <cstring>
#include "SamplerMenu.h"
#include "WaveEditorMenu.h"
#include "Presets.h"

SamplerMenuRouter* SamplerMenuRouter::self = nullptr;

SamplerMenuRouter::SamplerMenuRouter() {
                    self = this ;
                    self->home_navrange=SP_LABELS_COUNT-1;
                    self->catalog = new FilesLister("SOUNDSET/","SAMPLE#",".RAW",show,self->home_navrange);
                    self->relative_navlevel=1;
                    self->max_navlevel=5;
                    self->sublevels_address={7,0,0};
                    }

void SamplerMenuRouter::sampler_nav_two(){
          if (lv.sublevels[1] == 0) {
              dm.clearDisplay();
              samplerexplorer();
          }
          if (lv.sublevels[1] == 1) {
              dm.clearDisplay();
              Flashsamplerexplorer();
          }
          if (lv.sublevels[1] == 2) {
              dm.clearDisplay();
              Assingexplorer();
          }

          if (lv.sublevels[1] == 3) {
              smixerVpanel();
          }
        }

void SamplerMenuRouter::sampler_nav_one(){
          lv.assigning_sample_to_note = false ;
          dm.clearDisplay();
          _nav_sampler[lv.sublevels[1]]();
          dm.dodisplay();
        }
        
void SamplerMenuRouter::sampler_nav_zero(){
            dm.reinitsublevels(2);
            lv.navrange = SP_LABELS_COUNT - 1;
            dm.clearDisplay();
            dolistsamplermenu();
            dm.dodisplay();
            dm.display();
        }

void SamplerMenuRouter::show() {
          _route_nav[lv.navlevel-1]();
        }

void SamplerMenuRouter::smixerVpanelAction() {
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

void SamplerMenuRouter::clearsizeofsamplefolder() {
  memset(self->sizeofsamplefolder,0,sizeof(self->sizeofsamplefolder));
}

void SamplerMenuRouter::initializesamplebase() {
  memset(self->samplebase,0,sizeof(self->samplebase));
}

String SamplerMenuRouter::lower_extension_case(String f_name){
  char named[50];  // Ensure the array is large enough
  strcpy(named, f_name.c_str());
  named[strlen(named) - 4] = '\0';
  return (String)named + ".raw";
}

bool SamplerMenuRouter::test_flash_sample_name(String f_s_name){
  return SerialFlash.exists(f_s_name.c_str());
}

void SamplerMenuRouter::listSoundset() {
  FsFile sounddir = SD.sdfs.open("SOUNDSET/");
  char _tnamer[16];
  while (FsFile soundentry = sounddir.openNextFile()){
    if (soundentry.isDirectory()) {
      soundentry.getName(_tnamer, 16);
      addtofolderix(_tnamer, self->sampledirsregistered);
      //addtofullsamplerfolderpath(self->sampledirsregistered,(char *)soundentry.name());
      self->sampledirsregistered++;
    }
    soundentry.close();
  }
  sounddir.close();
}

void SamplerMenuRouter::smixerVpanel() {
  smixerVpanelAction();
  dm.clean_title_1_1();
  dm.canvasBIG.print(gg.smixervknobs[lv.sublevels[2]]);
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
    dm.canvastitle.setCursor(centercirclex - 5 + 3, 8);
    dm.canvastitle.setTextSize(1);
    dm.canvastitle.print(i + 1);
    dm.canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
    trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
    trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));
    dm.drawLine(centercirclex, centercircley, trianglepointx, trianglepointy, SSD1306_WHITE);
  }
  if (slct < 8) {
    centercirclex = knobradius + (xcentershifter * slct);
    dm.canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
    dm.canvastitle.setCursor(95, 0);
    dm.canvastitle.print((gg.smixervknobs[slct] / 127.0) * 100.0, 1);
  }
  centercircley = yshifter + knobradius;
  for (int i = 0; i < 8; i++) {
    coeffangle = (6.2831 - (gg.smixervknobs[i + 8] / 127.0) * 6.2831) + 3.1416;
    centercirclex = knobradius + (xcentershifter * i);
    dm.canvasBIG.setCursor(centercirclex - 5, centercircley - (2 + knobradius * 2) - 1);
    dm.canvasBIG.setTextSize(1);
    dm.canvasBIG.print(i + 1 + 8);
    dm.canvasBIG.drawCircle(centercirclex, centercircley, knobradius, SSD1306_WHITE);
    trianglepointx = round(centercirclex + (knobradius * (cos(coeffangle))));
    trianglepointy = round(centercircley - (knobradius * (sin(coeffangle))));
    dm.drawLine(centercirclex, centercircley, trianglepointx, trianglepointy, SSD1306_WHITE);
  }
  if (slct > 7) {
    centercirclex = knobradius + (xcentershifter * (slct - 8));
    dm.canvasBIG.drawCircle(centercirclex, centercircley, knobradius - 2, SSD1306_WHITE);
    dm.canvastitle.setCursor(95, 0);
    dm.canvastitle.print((gg.smixervknobs[slct] / 127.0) * 100.0, 1);
  }
  dm.dodisplay();
}

void SamplerMenuRouter::dolistsamplermenu() {
  char samplerlabels[SP_LABELS_COUNT][12] = {"Load", "Delete", "Assign", "Mixer"};
  int startx = 5;
  int starty = 16;
  char *textin = (char *)samplerlabels[lv.sublevels[1]];
  dm.canvastitle.fillScreen(SSD1306_BLACK);
  dm.canvastitle.setCursor(0, 0);
  dm.canvastitle.setTextSize(2);
  dm.canvastitle.println(textin);
  dm.canvasBIG.setTextSize(1);
  dm.canvasBIG.fillScreen(SSD1306_BLACK);
  for (int i = 0; i < SP_LABELS_COUNT - 1 - (lv.sublevels[1]); i++) {
      dm.canvasBIG.setCursor(startx, starty + ((i)*10));
      dm.canvasBIG.println(samplerlabels[lv.sublevels[1] + 1 + i]);
  }
  for (int i = 0; i < lv.sublevels[1]; i++) {
      dm.canvasBIG.setCursor(startx, (10 * (SP_LABELS_COUNT - lv.sublevels[1]) + 6 + ((i)*10)));
      dm.canvasBIG.println(samplerlabels[i]);
  }
}
        
String SamplerMenuRouter::samplefullpath(int lefolder, int lefile){
  String based = self->samplebase[lefolder][lefile];
  String folded = self->samplefoldersregistered[lefolder] ;
  return "SOUNDSET/" + folded + "/" + based +".RAW";
}

void SamplerMenuRouter::addtofolderix(char *lepathtoadd, int ix) {
  for (int i = 0; i < (int)strlen((char *)lepathtoadd); i++) {
    self->samplefoldersregistered[ix][i] = (char)(lepathtoadd[i]);
  }
}

void SamplerMenuRouter::setupsamplefoldersregistered() {
  memset(self->samplefoldersregistered, (char)'\0', sizeof(self->samplefoldersregistered));
  self->samplefoldersregistered[0][0] = (char)("/"[0]);
  self->sampledirsregistered++;
}

void SamplerMenuRouter::setlefilenamed(int lefolder, int lefile, char *lefname) {
  int fnamesize = strlen((char *)lefname);         
  for (int i = 0; i < fnamesize; i++) {
    if (i < fnamesize - 4) {
      self->samplebase[lefolder][lefile][i] = lefname[i];
    }
  }
  self->samplebase[lefolder][lefile][fnamesize - 4] = (char)'\0';
}

void SamplerMenuRouter::playsamplepreview() {
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

void SamplerMenuRouter::preview_flash_assignee() {
  String playable_file = (String)bb.Flashsamplename[lv.sublevels[4]];
  if (!self->test_flash_sample_name(playable_file)){
    playable_file = self->lower_extension_case(playable_file);
  }
  if (!self->test_flash_sample_name(playable_file)){
    return;
  }
  FlashRaw.play(playable_file.c_str());
}

void SamplerMenuRouter::copybacklaflashfile(int leflashfile) {
  SerialFlashFile originflashfile = SerialFlash.open((const char *)bb.Flashsamplename[leflashfile]);
  String new_name = self->newmkdirpath + "/" + (String)bb.Flashsamplename[leflashfile];
  FsFile mynewsample = SD.sdfs.open(new_name.c_str(), O_WRITE | O_CREAT | O_TRUNC);
  size_t n_size;
  uint8_t buf[512];
  while ((n_size = originflashfile.read(buf, sizeof(buf))) > 0) {
    mynewsample.write(buf, n_size);
  }
  originflashfile.close();
  mynewsample.close();
}

void SamplerMenuRouter::copyflashtoSD() {
  for (int i = 0; i < 128; i++) {
    if (gg.Sampleassigned[i] != 0) {
      copybacklaflashfile(gg.Sampleassigned[i]);
    }
  }
}

String SamplerMenuRouter::make_full_dir_name(byte number,String base_path_dir) {
  char formatted_number[4] ;
  sprintf(formatted_number,"%02d",number);
  return(String)(base_path_dir + (String)formatted_number);
}


String SamplerMenuRouter::get_new_dir_name(String base_path_dir) {
  byte file_number = 0 ;
  String new_path = base_path_dir + "00";
  while (SD.sdfs.exists(new_path.c_str())) {
    new_path = self->make_full_dir_name(file_number,base_path_dir);
    file_number++;
  }
  return new_path ;
}

void SamplerMenuRouter::domkdir() {
  self->newmkdirpath = self->get_new_dir_name("SOUNDSET/MABANK") ;
  self->catalog->make_sub_folder("SOUNDSET", self->newmkdirpath.c_str());
  copyflashtoSD();
  dosoundlist();
}

void SamplerMenuRouter::Assingexplorer() {
          if (lv.navlevel > 3) {
            lv.assigning_sample_to_note = false ;
            if (lv.sublevels[2] == 1) {
              Sampleassigner();
              preview_flash_assignee();
            }
            if (lv.sublevels[2] == 0 && lv.sublevels[3] == 1) {
              Doautoassign();
              dm.returntonav(2,127,lv.sublevels[2]);
            }
            if (lv.sublevels[2] == 2 && lv.sublevels[3] == 1) {
              doclearassign();
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
            lv.assigning_sample_to_note = true ;
            if (lv.sublevels[2] == 2) {
              dm.clearDisplay();
              doConfirmClearassign();
            }
            if (lv.sublevels[2] == 3) {
              dm.clearDisplay();
              doConfirmmkdir();
            }
            if (lv.sublevels[2] == 0) {
              dm.clearDisplay();
              doConfirmautoassign();
            }
            if (lv.sublevels[2] == 1) {
              lv.navrange = 127;
              Sampleassigner();
            }
          }
        }

void SamplerMenuRouter::samplerexplorer() {
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
              dm.clearDisplay();
              doConfirmLoadsamples();
            }

            if (lv.sublevels[2] == 3) {
              dm.clearDisplay();
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

void SamplerMenuRouter::Flashsamplerexplorer() {
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
              dm.clearDisplay();
              doConfirmDelsamples();
            }
            if (lv.sublevels[2] == 3) {
              dm.clearDisplay();
              doConfirmClearSelectedFlashList();
            }
            if (lv.sublevels[2] == 1) {
              dm.clearDisplay();
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

void SamplerMenuRouter::showsamplerfolderList() {
          drawSamplerFoldersList();
          dm.dodisplay();
        }
void SamplerMenuRouter::showsamplerfilesList() {
          drawsamplerfilesList();
          dm.dodisplay();
        }
void SamplerMenuRouter::showFlashSamplesList() {
          drawFlashSamplesList();
          dm.dodisplay();
        }

void SamplerMenuRouter::drawtickboxflashBIG(int lestartx, int lestarty, int lasizex, int lasizey,
                                int lacolor, int lefile) {
          if (self->Flashsamplesselected[lefile] == 1) {
            dm.canvasBIG.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          } else {
            dm.canvasBIG.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          }
        }
void SamplerMenuRouter::drawtickboxflashtitle(int lestartx, int lestarty, int lasizex, int lasizey,
                                  int lacolor, int lefile) {
          if (self->Flashsamplesselected[lefile] == 1) {
            dm.canvastitle.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          } else {
            dm.canvastitle.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          }
        }

void SamplerMenuRouter::drawtickboxfolderBIG(int lestartx, int lestarty, int lasizex, int lasizey,
                                  int lacolor, int lefolder) {
          if (self->samplesfoldersselected[lefolder]) {
            dm.canvasBIG.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          } else {
            dm.canvasBIG.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          }
        }
void SamplerMenuRouter::drawtickboxfoldertitle(int lestartx, int lestarty, int lasizex,
                                    int lasizey, int lacolor,
                                    int lefolder) {
          if (self->samplesfoldersselected[lefolder]) {
            dm.canvastitle.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          } else {
            dm.canvastitle.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          }
        }

void SamplerMenuRouter::drawtickboxincanvasBIG(int lestartx, int lestarty, int lasizex,
                                    int lasizey, int lacolor,
                                    int lefolder, int lefile) {
          if (self->samplesselected[lefolder][lefile] == 1) {
            dm.canvasBIG.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          } else {
            dm.canvasBIG.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          }
        }
void SamplerMenuRouter::drawtickboxincanvastitle(int lestartx, int lestarty, int lasizex,
                                      int lasizey, int lacolor,
                                      int lefolder, int lefile) {
          if (self->samplesselected[lefolder][lefile] == 1) {
            dm.canvastitle.fillRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          } else {
            dm.canvastitle.drawRect(lestartx, lestarty, lasizex, lasizey, lacolor);
          }
        }

void SamplerMenuRouter::addtoFlashsamplelist(char *lesample) {
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

void SamplerMenuRouter::initializeFlashsamplename() {
  self->numberofFlashfiles = 0;
  memset(bb.Flashsamplename, (char)'\0', sizeof(bb.Flashsamplename));
  memset(self->Flashsamplebase, (char)'\0', sizeof(self->Flashsamplebase));
}

void SamplerMenuRouter::initializesamplesfoldersselectedlist() {
  memset(self->samplesfoldersselected, 0, sizeof(self->samplesfoldersselected));
  self->numofsamplesfoldersselected = 0;
}

void SamplerMenuRouter::initializeFlashsamplesselected() {
  self->numberofFlashsamplesselected = 0;
  memset(self->Flashsamplesselected, 0, sizeof(self->Flashsamplesselected));
}

void SamplerMenuRouter::initializesamplesselectedlist() {
  memset(self->numberofsamplesselected, 0, sizeof(self->numberofsamplesselected));
  memset(self->samplesselected, 0, sizeof(self->samplesselected));
}

void SamplerMenuRouter::drawFlashSamplesList() {

          int startx = 15;
          int starty = 16;
          dm.canvastitle.fillScreen(SSD1306_BLACK);
          dm.canvastitle.setTextSize(1);
          dm.canvastitle.setCursor(startx, 0);
          dm.canvastitle.print((char *)self->Flashsamplebase[lv.sublevels[lv.navlevel]]);
          drawtickboxflashtitle(startx - 13, 0, 6, 6, SSD1306_WHITE, lv.sublevels[lv.navlevel]);
          dm.canvasBIG.setTextSize(1);
          dm.canvasBIG.fillScreen(SSD1306_BLACK);

          int maxsizefirstpart = self->numberofFlashfiles - 1 - (lv.sublevels[lv.navlevel]);
          if (maxsizefirstpart > 6) {
            maxsizefirstpart = 6;
          }
          for (int i = 0; i < maxsizefirstpart; i++) {
            dm.canvasBIG.setCursor(startx, starty + ((i)*10));
            dm.canvasBIG.println((char *)self->Flashsamplebase[lv.sublevels[lv.navlevel] + 1 + i]);
            drawtickboxflashBIG(startx - 13, starty + ((i)*10), 6, 6, SSD1306_WHITE, lv.sublevels[lv.navlevel] + 1 + i);
          }
          int maxsizelastpart = lv.sublevels[lv.navlevel];
          if (maxsizelastpart > 6) {
            maxsizelastpart = 6;
          }
          for (int i = 0; i < maxsizelastpart; i++) {
            dm.canvasBIG.setCursor(startx, (10 * (self->numberofFlashfiles - lv.sublevels[lv.navlevel])) + 6 + ((i)*10));
            dm.canvasBIG.println((char *)self->Flashsamplebase[i]);
            drawtickboxflashBIG(startx - 13, (10 * (self->numberofFlashfiles - lv.sublevels[lv.navlevel])) + 6 + ((i)*10), 6, 6, SSD1306_WHITE, i);
          }
        }

void SamplerMenuRouter::drawsamplerfilesList() {
          int startx = 15;
          int starty = 16;
          dm.canvastitle.fillScreen(SSD1306_BLACK);
          dm.canvastitle.setTextSize(1);
          dm.canvastitle.setCursor(startx, 0);
          dm.canvastitle.print((char *)self->samplebase[lv.sublevels[3]][lv.sublevels[lv.navlevel]]);
          drawtickboxincanvastitle(startx - 13, 0, 6, 6, SSD1306_WHITE, lv.sublevels[3], lv.sublevels[lv.navlevel]);
          dm.canvasBIG.setTextSize(1);
          dm.canvasBIG.fillScreen(SSD1306_BLACK);
          int maxsizefirstpart =
              self->sizeofsamplefolder[lv.sublevels[3]] - 1 - (lv.sublevels[lv.navlevel]);
          if (maxsizefirstpart > 6) {
            maxsizefirstpart = 6;
          }
          for (int i = 0; i < maxsizefirstpart; i++) {
            dm.canvasBIG.setCursor(startx, starty + ((i)*10));
            dm.canvasBIG.println((char *)self->samplebase[lv.sublevels[3]][lv.sublevels[lv.navlevel] + 1 + i]);
            drawtickboxincanvasBIG(startx - 13, starty + ((i)*10), 6, 6, SSD1306_WHITE, lv.sublevels[3], lv.sublevels[lv.navlevel] + 1 + i);
          }
          int maxsizelastpart = lv.sublevels[lv.navlevel];
          if (maxsizelastpart > 6) {
            maxsizelastpart = 6;
          }
          for (int i = 0; i < maxsizelastpart; i++) {
            dm.canvasBIG.setCursor(startx, (10 * (self->sizeofsamplefolder[lv.sublevels[3]] - lv.sublevels[lv.navlevel])) + 6 + ((i)*10));
            dm.canvasBIG.println((char *)self->samplebase[lv.sublevels[3]][i]);
            drawtickboxincanvasBIG(startx - 13, (10 * (self->sizeofsamplefolder[lv.sublevels[3]] - lv.sublevels[lv.navlevel])) + 6 + ((i)*10), 6, 6, SSD1306_WHITE, lv.sublevels[3], i);
          }
        }

void SamplerMenuRouter::drawSamplerFoldersList() {
          int startx = 15;
          int starty = 16;
          dm.canvastitle.fillScreen(SSD1306_BLACK);
          dm.canvastitle.setTextSize(1);
          dm.canvastitle.setCursor(startx, 0);
          dm.canvastitle.print((char *)self->samplefoldersregistered[lv.sublevels[lv.navlevel]]);
          if (lv.sublevels[2] == 1) {
            drawtickboxfoldertitle(startx - 13, 0, 6, 6, SSD1306_WHITE, lv.sublevels[lv.navlevel]);
          }
          dm.canvasBIG.setTextSize(1);
          dm.canvasBIG.fillScreen(SSD1306_BLACK);

          int maxsizefirstpart = self->sampledirsregistered - 1 - (lv.sublevels[lv.navlevel]);
          if (maxsizefirstpart > 6) {
            maxsizefirstpart = 6;
          }
          for (int i = 0; i < maxsizefirstpart; i++) {
            dm.canvasBIG.setCursor(startx, starty + ((i)*10));
            dm.canvasBIG.println((char *)self->samplefoldersregistered[lv.sublevels[lv.navlevel] + 1 + i]);
            if (lv.sublevels[2] == 1) {
              drawtickboxfolderBIG(startx - 13, starty + ((i)*10), 6, 6, SSD1306_WHITE, lv.sublevels[lv.navlevel] + 1 + i);
            }
          }
          int maxsizelastpart = lv.sublevels[lv.navlevel];
          if (maxsizelastpart > 6) {
            maxsizelastpart = 6;
          }
          for (int i = 0; i < maxsizelastpart; i++) {
            dm.canvasBIG.setCursor(startx, (10 * (self->sampledirsregistered - lv.sublevels[lv.navlevel])) + 6 + ((i)*10));
            dm.canvasBIG.println((char *)self->samplefoldersregistered[i]);
            if (lv.sublevels[2] == 1) {
              //TODO: check if all is ok here, was previousely (10 * (keepcount - lv.sublevels[lv.navlevel])) + 6 + ((i)*10)
              drawtickboxfolderBIG(startx - 13, (10 * (lv.sublevels[lv.navlevel])) + 6 + ((i)*10), 6, 6, SSD1306_WHITE, i);
            }
          }
        }

void SamplerMenuRouter::dolistLoadSampleMenu() {
          lv.navrange = 4 - 1;
          const int sizeofmenuloadsample = 4;
          char menuloadsample[sizeofmenuloadsample][16] = {
              "Select", "Whole pack", "Load Selection", "Clear Selection"};
          int startx = 5;
          int starty = 16;
          char *textin = (char *)menuloadsample[lv.sublevels[2]];
          dm.clear_buffs_1_1();
          dm.canvastitle.println(textin);
          for (int i = 0; i < sizeofmenuloadsample - 1 - (lv.sublevels[2]); i++) {
            dm.canvasBIG.setCursor(startx, starty + ((i)*10));
            dm.canvasBIG.println(menuloadsample[lv.sublevels[2] + 1 + i]);
          }
          for (int i = 0; i < lv.sublevels[2]; i++) {
            dm.canvasBIG.setCursor(startx, (10 * (sizeofmenuloadsample - lv.sublevels[2]) + 6 + ((i)*10)));
            dm.canvasBIG.println(menuloadsample[i]);
          }
        }

void SamplerMenuRouter::dolistDelSampleMenu() {
          lv.navrange = 4 - 1;

          const int sizeofmenudelsample = 4;
          char menudelsample[sizeofmenudelsample][16] = {
              "Select", "Remove All", "Remove Selected", "Clear Selection"};
          int startx = 5;
          int starty = 16;
          char *textin = (char *)menudelsample[lv.sublevels[2]];
            dm.clear_buffs_1_1();
          dm.canvastitle.println(textin);
          for (int i = 0; i < sizeofmenudelsample - 1 - (lv.sublevels[2]); i++) {
            dm.canvasBIG.setCursor(startx, starty + ((i)*10));
            dm.canvasBIG.println(menudelsample[lv.sublevels[2] + 1 + i]);
          }
          for (int i = 0; i < lv.sublevels[2]; i++) {
            dm.canvasBIG.setCursor(startx, (10 * (sizeofmenudelsample - lv.sublevels[2]) + 6 + ((i)*10)));
            dm.canvasBIG.println(menudelsample[i]);
          }
        }

void SamplerMenuRouter::dolistAssignSampleMenu() {
          lv.navrange = 4 - 1;
          lv.assigning_sample_to_note = false ;
          const int sizeofmenuassignsample = 4;
          char menuassignsample[sizeofmenuassignsample][19] = {
              "Auto-assign", "Individual", "Clear All", "Save assigned"};
          int startx = 5;
          int starty = 16;
          char *textin = (char *)menuassignsample[lv.sublevels[2]];
            dm.clear_buffs_1_1();
          dm.canvastitle.println(textin);
          for (int i = 0; i < sizeofmenuassignsample - 1 - (lv.sublevels[2]); i++) {
            dm.canvasBIG.setCursor(startx, starty + ((i)*10));
            dm.canvasBIG.println(menuassignsample[lv.sublevels[2] + 1 + i]);
          }
          for (int i = 0; i < lv.sublevels[2]; i++) {
            dm.canvasBIG.setCursor(startx, (10 * (sizeofmenuassignsample - lv.sublevels[2]) + 6 + ((i)*10)));
            dm.canvasBIG.println(menuassignsample[i]);
          }
        }


void SamplerMenuRouter::Doautoassign() {
          for (int i = 0; i < self->numberofFlashfiles - 1; i++) {
            if (i + 4 < 128) {
              gg.Sampleassigned[i + 4] = i;
            } else {
              break;
            }
          }
        }

void SamplerMenuRouter::doclearassign() {
  memset(gg.Sampleassigned, 0, sizeof(gg.Sampleassigned));
}

void SamplerMenuRouter::doConfirmmkdir() {
  char messageconfirm[32] = "Make dir ?";
  dm.doConfirmpanel((char *)messageconfirm);
}

void SamplerMenuRouter::doConfirmClearassign() {
  char messageconfirm[32] = "Clear selection ?";
  dm.doConfirmpanel((char *)messageconfirm);
}

void SamplerMenuRouter::doConfirmClearList() {
  char messageconfirm[32] = "Clear selection ?";
  dm.doConfirmpanel((char *)messageconfirm);
}

void SamplerMenuRouter::doConfirmautoassign() {
  char messageconfirm[32] = "Confirm autoassign ?";
  dm.doConfirmpanel((char *)messageconfirm);
}

void SamplerMenuRouter::doConfirmDelsamples() {
  char messageconfirm[32] = "Confirm Delete ?";
  dm.doConfirmpanel((char *)messageconfirm);
}

void SamplerMenuRouter::doConfirmClearSelectedFlashList() {
  // same
  doConfirmClearList();
}

void SamplerMenuRouter::doConfirmRemoveAll() {
  // same
  doConfirmDelsamples();
}

void SamplerMenuRouter::doConfirmLoadsamples() {
  char messageconfirm[32] = "Confirm Loading ?";
  dm.doConfirmpanel((char *)messageconfirm);
}

void SamplerMenuRouter::RemoveAllfromFlash() {
  dm.initializeconsolemsg();
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
        //dm.pseudoconsole(" . ",0);
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

float SamplerMenuRouter::eraseBytesPerSecond(const unsigned char *id) {
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

void SamplerMenuRouter::DelSelectedFlashSamples() {
          dm.initializeconsolemsg();
          for (int j = 0; j < 999; j++) {
            //dm.pleasewait(j, 999);
            if (self->Flashsamplesselected[j] == 1) {
              if (SerialFlash.exists((const char *)bb.Flashsamplename[j])) {
                dm.pseudoconsole((const char *)bb.Flashsamplename[j]);
                SerialFlash.remove((const char *)bb.Flashsamplename[j]);
              }
            }
          }
          initializeFlashsamplesselected();
          listFlashfiles();
        }

void SamplerMenuRouter::addfolderstoselectionset() {
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

void SamplerMenuRouter::loadSelectedSamples() {
          dm.initializeconsolemsg();
          unsigned long lengthz;
          FsFile currentsample;
          SerialFlashFile currentFlashfile;
          addfolderstoselectionset();
          delay(100);
          if (!SerialFlash.begin(self->FlashChipSelect)) {
            dm.pseudoconsole((char *)"Unable to access SPI Flash chip");
          }
          char currentflashname[12]; 
          for (int i = 0; i < 99; i++) {
            //dm.pleasewait(i, 99);
            for (int j = 0; j < 999; j++) {
              if (self->samplesselected[i][j]) {
                currentsample = SD.sdfs.open(self->samplefullpath(i,j).c_str());
                //was break instead of continue
                if (!currentsample) continue;

                currentsample.getName(currentflashname, 12);
                if (strlen(currentflashname) > 12) {
                  Serial.print(" Skipping ");
                  Serial.print(currentflashname);
                  Serial.print(" <--- name too long !");
                  continue;
                }
                lengthz = currentsample.size();
                dm.pseudoconsole(currentflashname);
                if (SerialFlash.exists((const char*)currentflashname)) continue; 

                if (SerialFlash.create((const char*)currentflashname, lengthz)) {
                  SerialFlashFile currentFlashfile = SerialFlash.open((const char*)currentflashname);
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


void SamplerMenuRouter::loadSampledSound() {
          unsigned long lengthz;
          FsFile currentsample;
          SerialFlashFile currentFlashfile;
          delay(1);
          if (!SerialFlash.begin(self->FlashChipSelect)) {
            dm.pseudoconsole("Unable to access SPI Flash chip");
          }
          currentsample = SD.sdfs.open(_rd.newloopedpath.c_str());
          char currentflashname[12]; 
          currentsample.getName(currentflashname, 12);
          lengthz = currentsample.size();
          
          if (SerialFlash.exists((const char*)currentflashname)) return;

          if (SerialFlash.create((const char*)currentflashname, lengthz)) {
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

void SamplerMenuRouter::listFlashfiles() {
          initializeFlashsamplename();
          if (!SerialFlash.begin(self->FlashChipSelect)) {
            dm.pseudoconsole((char *)"Unable to access SPI Flash chip");
          }
          char filename[13];
          uint32_t filesize;
          while (SerialFlash.readdir(filename, sizeof(filename), filesize)) {
              addtoFlashsamplelist(filename);
          }
        }

        //unused
void SamplerMenuRouter::getavailablespace() {
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

void SamplerMenuRouter::Sampleassigner() {
          if (lv.navlevel == 3) {
            lv.assigning_sample_to_note = true ;
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

void SamplerMenuRouter::listsamplesassigner() {
          dm.clean_title_2_2();
          char *toprint = (char *)"Note";
          dm.canvastitle.println(toprint);
          dm.canvastitle.setCursor(85, 0);
          dm.canvastitle.println(lv.sublevels[3]);
          if (gg.Sampleassigned[lv.sublevels[3]] != 0) {
            dm.canvasBIG.setCursor(85, 16);
            dm.canvasBIG.println(gg.Sampleassigned[lv.sublevels[3]]);
            dm.canvasBIG.setCursor(0, 40);
            dm.canvasBIG.println((char *)self->Flashsamplebase[gg.Sampleassigned[lv.sublevels[3]]]);
          }
        }

void SamplerMenuRouter::samplesetter() { gg.Sampleassigned[lv.sublevels[3]] = lv.sublevels[4]; }

void SamplerMenuRouter::listsamplesassigner2() {
  dm.clean_title_2_2();
  char *toprint = (char *)"Note";
  dm.canvastitle.println(toprint);
  dm.canvastitle.setCursor(85, 0);
  dm.canvastitle.println(lv.sublevels[3]);
  dm.canvasBIG.setCursor(85, 16);
  dm.canvasBIG.println(lv.sublevels[4]);
  dm.canvasBIG.setCursor(0, 40);
  dm.canvasBIG.println((char *)self->Flashsamplebase[lv.sublevels[4]]);
}

void SamplerMenuRouter::listSoundsetsubdir(int ledir) {
  if (SD.sdfs.exists((const char *)self->sampledirpath)) {
    FsFile susudir = SD.sdfs.open((const char *)self->sampledirpath);
    while (true) {
      FsFile subentry = susudir.openNextFile();
      if (!subentry) {
        break;
      }
      char shorter_name[13];
      subentry.getName(shorter_name, 13);
      shorter_name[12] = (char)'\0';

      //int fnamesize = strlen((char *)subentry.name());
      /*
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
      */
      if (!subentry.isDirectory()) {
          setlefilenamed(ledir, self->sizeofsamplefolder[ledir], (char*)shorter_name);
        (self->sizeofsamplefolder[ledir])++;
      }
      subentry.close();
    }
    susudir.close();
  }
}

void SamplerMenuRouter::makesoundsetfullpathfromchars(int eldir) {
  for (int i = 9; i < (int)(strlen((char *)self->samplefoldersregistered[eldir]) + 9);i++) {
    self->sampledirpath[i] = self->samplefoldersregistered[eldir][i - 9];
  }
  int lelast = (int)strlen((char *)self->sampledirpath);
  self->sampledirpath[lelast] = (char)'/';
  self->sampledirpath[lelast + 1] = (char)'\0';
}

void SamplerMenuRouter::voidsampledirpath() {
  memset(self->sampledirpath, (char)'\0', sizeof(self->sampledirpath));
  for (int i = 0; i < 9; i++) {
    self->sampledirpath[i] = (char)("SOUNDSET/"[i]);
  }
}

void SamplerMenuRouter::dosoundlist() {
  initializeFlashsamplesselected();
  initializesamplesfoldersselectedlist();
  listFlashfiles();
  clearsizeofsamplefolder();
  self->sampledirsregistered = 0;
  setupsamplefoldersregistered();

  initializesamplebase();
  listSoundset();
  for (int i = 1; i < self->sampledirsregistered; i++) {
    //dm.pleasewait(i, self->sampledirsregistered);
    voidsampledirpath();
    makesoundsetfullpathfromchars(i);
    listSoundsetsubdir(i);
  }
}

