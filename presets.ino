
class PresetsMenuRouter : public SectionHolder {
    public:
        PresetsMenuRouter() {
                    self = this;
                    self->home_navrange=self->ps_labels_count-1;
                    self->catalog = new FilesLister("PRESETS/SYNTH/","SYNSET",".TXT",presets_menu,self->home_navrange);
                    self->relative_navlevel=1;
                    self->max_navlevel=5;
                    self->sublevels_address={9,0,0};
                    //home method not really used yet
                    //this->set_home(call_fx_mainpanel);
        }
        FilesLister *catalog;
        const byte ps_labels_count = 5;

        static void route_navlevel(){
          _nav_presets[lv.sublevels[1]]();
        }

        static void presets_nav_zero(){
          self->catalog->nav_zero();
        }

        static void show() {
          _route_nav[lv.navlevel-1]();
        }

        static void presets_menu() {
          const char* presetmenulabels[] = {
              "Save", "Load", "Copy", "Delete", "Params"};
          dm.main_panel(presetmenulabels,1,self->ps_labels_count);
        }

        static void write_preset() {
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

        static void read_preset() {
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
            _fx.avoid_fx_bounce = false ;
          }

          call_set_bpms();
          _ad.ApplyADSR();
          call_allfxcontrolled();
          _ft.le303filterzWet();
          _ft.Wavespreamp303controls();
          _ft.le303filtercontrols();
          _mx.set_dry_mix(0);
          _mx.set_dry_mix(1);

          for (int i = 0; i < OSCS_COUNT; i++) {
            lv.oscillator = i ;
            call_setwavemixlevel();
            call_setwavetypefromlist();
            gg.mixlevelsL[i] = tmp_mixlevelsL[i];
            call_setwavemixlevel();
          }
          for (int i = 0; i < OSCS_COUNT; i++) {
            lv.oscillator = i ;
            call_setwavemixlevel();
            call_setwavetypefromlist();
            gg.mixlevelsL[i] = tmp_mixlevelsL[i];
            call_setwavemixlevel();
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

        static void copypreset() {
          self->catalog->copyFile();
        }

        static void deletepreset() {
          self->catalog->deleteFile();
        }

        static void remove_preset(){
          lv1_wrapper(self->deletepreset);
        }

        static void duplicate_preset(){
          lv1_wrapper(self->copypreset);
        }

        static void load_preset(){
          lv1_wrapper(self->read_preset);
        }

        static void save_preset(){
          lv1_wrapper(self->write_preset);         
        }

        static void params_presets(){ 
          //TODO: selection filter to load only some settings
          dm.returntonav(1, self->home_navrange,lv.sublevels[1]);
        }
        
        static void lv1_wrapper(void (*func)()) {
          self->catalog->nav_one(0,1);
          if (lv.navlevel >= 3) {
            func();
            dm.returntonav(1, self->home_navrange,lv.sublevels[1]);
          }
        }

        //arbitrary depth of 5, don't go further
        static constexpr void (*_route_nav[5])() = {&presets_nav_zero, &route_navlevel, &route_navlevel, &route_navlevel, &route_navlevel};
        static constexpr void (*_nav_presets[5])() = {&save_preset,&load_preset,&duplicate_preset,&remove_preset,&params_presets};
  private:
    static PresetsMenuRouter* self;
};

//
PresetsMenuRouter* PresetsMenuRouter::self = nullptr;
PresetsMenuRouter _ps;