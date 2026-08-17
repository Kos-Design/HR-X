#include "Presets.h"

FxBus::FxBus() {}
    
void FxBus::route_fx(byte selected_fx_type) {
      if (plugged_fx != (ALL_FX_TYPES - 1)) {
        unplug_fx_line();
      }
      if (selected_fx_type != (ALL_FX_TYPES - 1)) {
        plug_fx_line(selected_fx_type);
        plugged_fx = selected_fx_type;
      }
    }
   
void FxBus::plug_fx_line(byte selected_fx_type){
   
      AudioNoInterrupts();
      //delay
      if (selected_fx_type == 8) {
        delayCords[f_index]->connect();
        delayCordsR[f_index]->connect();
      }
      if (selected_fx_type == 4) {
        flange[f_index]->begin(bb.flangedelay[f_index],FLANGE_DELAY_LENGTH,this->flangeoffset,this->flangedepth,this->flangefreq);
        flange[f_index]->voices(FLANGE_DELAY_PASSTHRU,0,0);
        flangeR[f_index]->begin(bb.flangedelay[f_index],FLANGE_DELAY_LENGTH,this->flangeoffset,this->flangedepth,this->flangefreq);
        flangeR[f_index]->voices(FLANGE_DELAY_PASSTHRU,0,0);
      }
      if (selected_fx_type == 5) {
        chorus[f_index]->begin(bb.chorusdelayline[f_index],CHORUS_DELAY_LENGTH,this->chorusvoices) ;
        chorusR[f_index]->begin(bb.chorusdelayline[f_index],CHORUS_DELAY_LENGTH,this->chorusvoices) ;
      }
      premixesMto_index = (selected_fx_type * FXS_COUNT) + (f_index);
      fxcording_index = (selected_fx_type*FXS_COUNT*2*3) + (f_index*FXS_COUNT*2) + (2*f_index);
      premixesMto[premixesMto_index]->connect();
      premixesMtoR[premixesMto_index]->connect();
      fxcording[fxcording_index]->connect();
      fxcording[fxcording_index + 1]->connect();
      AudioInterrupts();
    }

void FxBus::stopdelayline() {

      for (int j = 0; j < 8; j++) {
        lesdelays[f_index]->disable(j);
        lesdelaysR[f_index]->disable(j);

      }
    }

void FxBus::unplug_fx_line() {
  AudioNoInterrupts();
  premixesMto[premixesMto_index]->disconnect();
  premixesMtoR[premixesMto_index]->disconnect();
  fxcording[fxcording_index]->disconnect();
  fxcording[fxcording_index + 1]->disconnect();
  premixesMto_index = 1000;
  fxcording_index = 1000;
  stopdelayline();
  delayCords[f_index]->disconnect();
  delayCordsR[f_index]->disconnect();
  AudioInterrupts();
  plugged_fx = ALL_FX_TYPES-1;
}

