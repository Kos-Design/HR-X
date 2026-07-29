
void reinitsublevels(byte fromlei) {
  for (byte i = fromlei; i < 9; i++) {
    sublevels[i] = 0;
  }
}

void waveformize(byte l_index,byte osc_idx,byte currentFreq,byte targetFreq,byte velocity){
  waveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->amplitude(velocity / 127.0);
  waveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->frequency(currentFreq * wavesfreqs[osc_idx]);
  waveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->offset((float)(((64.0 - wave1offset[osc_idx]) / 64.0)));
  waveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->phase(phaselevelsL[osc_idx]);       
}

void FMformize(byte l_index,byte osc_idx,byte currentFreq,byte targetFreq,byte velocity){
  FMwaveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->frequency(currentFreq * wavesfreqs[osc_idx]);
  FMwaveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->amplitude(velocity / 127.0);
  FMwaveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->offset((float)(((64.0 - wave1offset[osc_idx]) / 64.0)));
}  

void drumize(byte l_index,byte osc_idx,byte currentFreq,byte targetFreq,byte velocity){
  //look into pitchMod
  drums1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->length(adsrlevels[1] + adsrlevels[2] + adsrlevels[3]);
  drums1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->frequency(currentFreq * wavesfreqs[osc_idx]);
  drums1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->noteOn();
} 
void stringize(byte l_index,byte osc_idx,byte currentFreq,byte targetFreq,byte velocity){
  strings1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->noteOn(targetFreq * wavesfreqs[osc_idx],(velocity / 127.0));
}

//byte l_index, byte osc_idx, byte currentFreq, byte velocity
static constexpr void (*audio_obj_starter[4])(byte,byte,byte,byte,byte) = {&waveformize, &FMformize, &drumize, &stringize};


void waveform_refresh(byte l_index,byte osc_idx,byte currentFreq,byte velocity){
  waveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->amplitude(velocity / 127.0);
  waveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->frequency(currentFreq * wavesfreqs[osc_idx]);
  //waveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->phase(phaselevelsL[osc_idx]);       
}

void FMform_refresh(byte l_index,byte osc_idx,byte currentFreq,byte velocity){
  FMwaveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->frequency(currentFreq * wavesfreqs[osc_idx]);
  FMwaveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->amplitude(velocity / 127.0);
}  

void drum_refresh(byte l_index,byte osc_idx,byte currentFreq,byte velocity){
  //look into pitchMod
  drums1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->frequency(currentFreq * wavesfreqs[osc_idx]);

} 
static constexpr void (*audio_obj_refresher[3])(byte,byte,byte,byte) = {&waveform_refresh, &FMform_refresh, &drum_refresh};

class SynthLiner;

class ActiveLinesRegister {
    public:
        ActiveLinesRegister() { }
        int synth_lines_active = 0 ;

        void add_active_synth(SynthLiner *snth){
          active_synths[synth_lines_active] = snth ;
          synth_lines_active++;
        }

        void remove_inactive_synth(SynthLiner *snth){
          
          for (uint8_t i = 0; i < synth_lines_active; i++) {
            if (active_synths[i] == snth) {
                active_synths[i] = active_synths[synth_lines_active - 1];
                synth_lines_active--;
                return;
            }
          }
        }

        SynthLiner *active_synths[SYNTH_LINERS_COUNT];
};

ActiveLinesRegister _rg;

class KnobAssigner : public SectionHolder {
  public:
      KnobAssigner() {
                    self = this;
                    this->home_navrange=CtlCount-1;
                    this->relative_navlevel=2;
                    this->max_navlevel=3;
                    this->sublevels_address={2,0,0};
                    }
 
      static void show() {
        knobsetting = false ;
        _actionable[navlevel-self->relative_navlevel]();
      }
      static void learn_midi(byte captured){
        //used to unassign previousely set cc but lets keep it, duplicates are fine
        //midiknobassigned[find_assigned_knob(sublevels[1])] = 0;
        sublevels[self->relative_navlevel+1] = captured ;
        midiknobassigned[sublevels[self->relative_navlevel+1]] = sublevels[self->relative_navlevel];
        returntonav(self->relative_navlevel,CtlCount-1,sublevels[self->relative_navlevel]);
      }

      static int find_assigned_knob(int k){
        for (int i = 0; i < 128; i++) {
          if (midiknobassigned[i] == k){
            return i;
          }
        }
        return 0 ;
      }

      static void kb_home(){
        navrange = CtlCount-1;
        dm.clear_3();
        canvastitle.setCursor(0, 0);
        if (sublevels[self->relative_navlevel] != 0) {
          canvastitle.setTextSize(2);
          canvastitle.println(ctl[sublevels[self->relative_navlevel]].name);
          canvasBIG.setTextSize(2);
          canvasBIG.setCursor(0, 40);
          sublevels[self->relative_navlevel+1] = find_assigned_knob(sublevels[self->relative_navlevel]) ;
          if (sublevels[self->relative_navlevel+1] != 0) {
            canvasBIG.print("Midi");
            canvasBIG.setTextSize(1);
            canvasBIG.setCursor(50, 47);
            canvasBIG.print("(cc)");
            canvasBIG.setCursor(71, 39);
            canvasBIG.setTextSize(3);
            canvasBIG.print(":");
            canvasBIG.setTextSize(2);
            canvasBIG.setCursor(85, 40);

            canvasBIG.print(sublevels[self->relative_navlevel+1]);
          } else {
            //canvasBIG.setTextSize(1);
            canvasBIG.println("Unassigned");
          }
        } else {
          canvastitle.setTextSize(2);
          canvastitle.println("Select");
          canvasBIG.setTextSize(2);
          canvasBIG.setCursor(0, 28);
          canvasBIG.println("Control");
        }
        dm.dodisplay();

      }

      static void assigner(){
        knobsetting = true ;
        navrange = 127;
        if (sublevels[self->relative_navlevel] == 0 ) {
          returntonav(self->relative_navlevel,CtlCount-1,sublevels[self->relative_navlevel]);
        } else {
          dm.clean_title_2_2();
          canvastitle.println(ctl[sublevels[self->relative_navlevel]].name);
          canvasBIG.setCursor(0, 40);
          if (sublevels[self->relative_navlevel+1] != 0) {
            canvasBIG.print("Midi");
            canvasBIG.setTextSize(1);
            canvasBIG.setCursor(50, 47);
            canvasBIG.print("(cc)");
            canvasBIG.setCursor(71, 39);
            canvasBIG.setTextSize(3);
            canvasBIG.print(":");
            canvasBIG.setTextSize(2);
            canvasBIG.setCursor(85, 40);
            canvasBIG.print(sublevels[self->relative_navlevel+1]);
          } else {
            //canvasBIG.setTextSize(1);
            canvasBIG.println("Unassigned");
          }
        }
        dm.dodisplay();
      }
      
      static void set_midi_cc_to_ctl(byte cc_nt, int cc_cl){
        midiknobassigned[cc_nt] = cc_cl;
      }

      static void set_it(){
        knobsetting = false ;
        set_midi_cc_to_ctl(find_assigned_knob(sublevels[self->relative_navlevel]), 0);
        set_midi_cc_to_ctl(sublevels[self->relative_navlevel+1] , sublevels[self->relative_navlevel]);

        returntonav(self->relative_navlevel,CtlCount-1, sublevels[self->relative_navlevel]);
      }


  private:

    static constexpr void (*_actionable[3])() = { &kb_home, &assigner, &set_it };
    static KnobAssigner* self;
};

KnobAssigner* KnobAssigner::self = nullptr;
KnobAssigner _ka;

class SynthLiner {
  public:
    byte l_index = 0 ;
    bool activated = 0 ;
    byte note = 0 ;
    byte velocity = 0 ;
    byte sloper_step = 0;
    float targetFreq;
    float currentFreq = 0;
    float steps = 0 ;
    bool f303 = 0 ;

    SynthLiner(byte line_index = 0 ) : l_index(line_index) { }

    void liner_on(byte data1, byte data2) {
      if (this->activated||data1==this->note) {
        liner_off();
      }
      this->activated=true;
      this->note=data1;
      this->velocity=data2;
      this->f303=1;
      //enveloppesR[liner]->hold(500);

      // if same note as previousely
      this->targetFreq = notestofreq[this->note][1];
      setPortamentoTime();

      setfreqWavelines();
      enveloppesL[this->l_index]->hold(millitickinterval - adsrlevels[3]);
      enveloppesL[this->l_index]->noteOn();
      _rg.add_active_synth(this);
    }

    void setPortamentoTime(){
      float glideTime = map(portamento_time, 0, 127, 0, 2000);
      float dt = AUDIO_BLOCK_SAMPLES * 1000.0f / AUDIO_SAMPLE_RATE_EXACT;
      int updates = max(1, (int)(glideTime / dt));
      this->steps = (this->targetFreq - this->currentFreq) / updates;
    } 
        
    void setfreqWavelines() {
      //this->currentFreq = this->targetFreq +1000; <--- evil space sound
      update_line();
      activateWavelines();
    }
    
    void activateWavelines() {
      //Sample & Hold waveform does not support phase modulation. Attempting to modulate its phase may give random or inconsistent results.
      for (int i = 0; i < OSCS_COUNT; i++) {
        if (audio_obj_type[i]) audio_obj_starter[audio_obj_type[i]-1](this->l_index,i,this->currentFreq,this->targetFreq,this->velocity);
      }
    }

    void refreshWavelines() {
      for (int i = 0; i < OSCS_COUNT; i++) {
        if (audio_obj_type[i] && audio_obj_type[i] < 4) {
         audio_obj_refresher[audio_obj_type[i]-1](this->l_index,i,this->currentFreq,this->velocity);
        }
      }
    }

    void liner_off() {
      // AudioNoInterrupts();
      //if (enveloppesL[this->l_index]->isActive()) {
      enveloppesL[this->l_index]->hold(0);
      enveloppesL[this->l_index]->noteOff();
      this->f303 = 0;
      this->activated = false;
      _rg.remove_inactive_synth(this);
      this->note = 0 ;
      //should reinitialize to something
      //this->currentFreq = max(this->targetFreq - 1000, 1000.0);
    }

    //call in loop
    void update_line(){
      this->currentFreq += this->steps;
      if ((this->steps > 0 && this->currentFreq >= this->targetFreq) ||
          (this->steps < 0 && this->currentFreq <= this->targetFreq) ) {
          this->currentFreq = this->targetFreq;
      }
      refreshWavelines(); 
    }
};

SynthLiner *synth_lines[SYNTH_LINERS_COUNT] = {nullptr};

class FlashLiner {
  public:
    FlashLiner(byte line_index = 0 ) : l_index(line_index) {  }
    
    byte l_index = 0 ;
    bool activated = 0 ;
    byte note = 0 ;
    byte velocity = 0 ;

    String playable_file = "";

    void liner_on(byte data1, byte data2) {
      
      if (activated)
        return;
        //liner_off();
      if (data1==note) {
        liner_off();
      }
      //if (FlashSampler[l_index]->isPlaying()) {
      //  FlashSampler[l_index]->stop();
      //}
      /*
      if (!digitalplay) {
        Flashmixer[int(l_index / 4)]->gain(l_index - 4 * int(l_index / 4),(smixervknobs[l_index] / 127.0) * (data2 / 127.0));
      } else {
        Flashmixer[int(l_index / 4)]->gain(l_index - 4 * int(l_index / 4),(smixervknobs[l_index] / 127.0));
      }
      */
      playable_file = (String)Flashsamplename[Sampleassigned[(int)(data1)]];
      if (!test_flash_sample_name(playable_file)){
        playable_file = lower_extension_case(playable_file);
      }

      FlashSampler[l_index]->play(playable_file.c_str());
      
      //playRaw(playable_file.c_str());
      activated=true;
      note=data1;
      velocity=data2;

    }

    void liner_off() {
      FlashSampler[l_index]->stop();
      activated = false;
      note = 0 ;
      velocity = 0 ;
    }
};


FlashLiner *flash_lines[FLASH_LINERS_COUNT] = {nullptr};


