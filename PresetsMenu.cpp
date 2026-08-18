#include "PresetsMenu.h"
#include "Patterns.h"
#include "KnobAssigner.h"
#include "KnobAssigner.h"
#include "FxMenu.h"
#include "SynthMenu.h"

PresetsMenuRouter* PresetsMenuRouter::self = nullptr;

PresetsMenuRouter::PresetsMenuRouter() {
          self = this;
          self->catalog = new FilesLister("PRESETS/SYNTH/","SYNSET",".TXT",presets_menu,self->ps_labels_count-1);

        }

void PresetsMenuRouter::route_navlevel(){
          _nav_presets[lv.sublevels[1]]();
        }

void PresetsMenuRouter::presets_nav_zero(){
          self->catalog->nav_zero();
        }

void PresetsMenuRouter::show() {
          _route_nav[lv.navlevel-1]();
        }

void PresetsMenuRouter::presets_menu() {
          const char* presetmenulabels[] = {
              "Save", "Load", "Copy", "Delete", "Params"};
          dm.main_panel(presetmenulabels,1,self->ps_labels_count);
        }

void PresetsMenuRouter::write_preset() {
          if (lv.locked_fileing)
            return;
          lv.locked_fileing = 1 ;
          FsFile preset_filer;
          if (self->catalog->new_file_mode) {
            String presets_base_path = "PRESETS" ;
            String presets_sub_path = "SYNTH" ;
            self->catalog->make_sub_folder("PRESETS", "SYNTH");
            String new_preset_name = self->catalog->get_new_file_name() ;
            preset_filer = SD.sdfs.open(new_preset_name.c_str(), O_WRITE | O_CREAT | O_TRUNC);
          } else {
            const char* overwritee = self->catalog->get_current_file_path(0).c_str();
            self->catalog->deleteFile();
            preset_filer = SD.sdfs.open(overwritee, O_WRITE | O_CREAT | O_TRUNC);
          }
          if (preset_filer) {
            preset_filer.write((uint8_t*)&gg, sizeof(gg));
            preset_filer.close();

          }
          preset_filer.close();
          lv.locked_fileing = 0 ;
          self->catalog->list_files();
        }

void PresetsMenuRouter::read_preset() {
          if (lv.locked_fileing)
            return;
          lv.locked_fileing = 1 ;
          FsFile preset_filer = SD.sdfs.open(self->catalog->get_current_file_path(0).c_str(), O_READ);
          if (preset_filer) {
           preset_filer.read((uint8_t*)&gg, sizeof(gg));
          } else {
            dm.pseudoconsole("Error with preset file");
            return ;
          }
          preset_filer.close();
          byte tmp_mixlevelsM[4];
          byte tmp_mixlevelsL[OSCS_COUNT];
          byte tmp_WetMixMasters[4];
          memcpy(&tmp_mixlevelsM, &gg.mixlevelsM, sizeof(gg.mixlevelsM));
          memcpy(&tmp_mixlevelsL, &gg.mixlevelsL, sizeof(gg.mixlevelsL));
          memcpy(&tmp_WetMixMasters, &gg.WetMixMasters, sizeof(gg.WetMixMasters));

          for (int i = 0; i < 3; i++) {
            gg.fx[i].route_fx(gg.fx[i].plugged_fx);
            lv.avoid_fx_bounce = false ;
          }

          _pt.setbpms();
          _ad.ApplyADSR();
          _fx.allfxcontrolled();
          _mx.le303filterzWet();
          _mx.Wavespreamp303controls();
          _mx.le303filtercontrols();
          _mx.set_dry_mix(0);
          _mx.set_dry_mix(1);

          for (int i = 0; i < OSCS_COUNT; i++) {
            lv.oscillator = i ;
            _mx.setwavemixlevel();
            _sn.setwavetypefromlist();
            gg.mixlevelsL[i] = tmp_mixlevelsL[i];
            _mx.setwavemixlevel();
          }
          for (int i = 0; i < OSCS_COUNT; i++) {
            lv.oscillator = i ;
            _mx.setwavemixlevel();
            _sn.setwavetypefromlist();
            gg.mixlevelsL[i] = tmp_mixlevelsL[i];
            _mx.setwavemixlevel();
          }
          for (int i = 0; i < 4; i++) {
            gg.WetMixMasters[i] = tmp_WetMixMasters[i];
            gg.mixlevelsM[i] = tmp_mixlevelsM[i];
            //_mx.setmastersmixlevel ignores 4th iteration (3)
            _mx.setmastersmixlevel(i);
          }
          _mx.wetmixmastercontrols();
          lv.locked_fileing = 0 ;
        }

void PresetsMenuRouter::copypreset() {
          self->catalog->copyFile();
        }

void PresetsMenuRouter::deletepreset() {
          self->catalog->deleteFile();
        }

void PresetsMenuRouter::remove_preset(){
          lv1_wrapper(self->deletepreset);
        }

void PresetsMenuRouter::duplicate_preset(){
          lv1_wrapper(self->copypreset);
        }

void PresetsMenuRouter::load_preset(){
          lv1_wrapper(self->read_preset);
        }

void PresetsMenuRouter::save_preset(){
          lv1_wrapper(self->write_preset);         
        }

void PresetsMenuRouter::params_presets(){ 
          //TODO: selection filter to load only some settings
          dm.returntonav(1, self->ps_labels_count-1,lv.sublevels[1]);
        }
        
void PresetsMenuRouter::lv1_wrapper(void (*func)()) {
  self->catalog->nav_one(0,1);
  if (lv.navlevel >= 3) {
    func();
    dm.returntonav(1, self->ps_labels_count-1,lv.sublevels[1]);
  }
}
