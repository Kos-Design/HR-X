
void reinitsublevels(byte fromlei) {
  for (byte i = fromlei; i < 9; i++) {
    sublevels[i] = 0;
  }
}

void waveformize(byte l_index,byte osc_idx,float currentFreq,float targetFreq,byte velocity){
  waveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->amplitude(velocity / 127.0);
  waveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->frequency(currentFreq * gg.wavesfreqs[osc_idx]);
  waveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->offset((float)(((64.0 - gg.wave1offset[osc_idx]) / 64.0)));
  waveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->phase((int)((gg.phaselevelsL[osc_idx]/127.0)*360));      
}

void FMformize(byte l_index,byte osc_idx,float currentFreq,float targetFreq,byte velocity){
  FMwaveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->frequency(currentFreq * gg.wavesfreqs[osc_idx]);
  FMwaveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->amplitude(velocity / 127.0);
  FMwaveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->offset((float)(((64.0 - gg.wave1offset[osc_idx]) / 64.0)));
}  

void drumize(byte l_index,byte osc_idx,float currentFreq,float targetFreq,byte velocity){
  //look into pitchMod
  drums1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->length(gg.adsrlevels[1] + gg.adsrlevels[2] + gg.adsrlevels[3]);
  drums1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->frequency(currentFreq * gg.wavesfreqs[osc_idx]);
  drums1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->noteOn();
} 
void stringize(byte l_index,byte osc_idx,float currentFreq,float targetFreq,byte velocity){
  strings1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->noteOn(targetFreq * gg.wavesfreqs[osc_idx],(velocity / 127.0));
}

static constexpr void (*audio_obj_starter[4])(byte,byte,float,float,byte) = {&waveformize, &FMformize, &drumize, &stringize};


void waveform_refresh(byte l_index,byte osc_idx,float currentFreq,byte velocity){
  waveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->amplitude(velocity / 127.0);
  waveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->frequency(currentFreq * gg.wavesfreqs[osc_idx]);
  //waveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->phase((int)((gg.phaselevelsL[osc_idx]/127.0)*360));       
}

void FMform_refresh(byte l_index,byte osc_idx,float currentFreq,byte velocity){
  FMwaveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->frequency(currentFreq * gg.wavesfreqs[osc_idx]);
  FMwaveforms1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->amplitude(velocity / 127.0);
}  

void drum_refresh(byte l_index,byte osc_idx,float currentFreq,byte velocity){
  //look into pitchMod
  drums1[l_index + (osc_idx * SYNTH_LINERS_COUNT)]->frequency(currentFreq * gg.wavesfreqs[osc_idx]);

} 
static constexpr void (*audio_obj_refresher[3])(byte,byte,float,byte) = {&waveform_refresh, &FMform_refresh, &drum_refresh};

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
      bool knobsetting = false ;
 
      static void show() {
        self->knobsetting = false ;
        _actionable[navlevel-self->relative_navlevel]();
      }
      static void learn_midi(byte captured){
        //used to unassign previousely set cc but lets keep it, duplicates are fine
        //gg.midiknobassigned[find_assigned_knob(sublevels[1])] = 0;
        sublevels[self->relative_navlevel+1] = captured ;
        gg.midiknobassigned[sublevels[self->relative_navlevel+1]] = sublevels[self->relative_navlevel];
        returntonav(self->relative_navlevel,CtlCount-1,sublevels[self->relative_navlevel]);
      }

      static int find_assigned_knob(int k){
        for (int i = 0; i < 128; i++) {
          if (gg.midiknobassigned[i] == k){
            return i;
          }
        }
        return 0 ;
      }

      static void kb_home(){
        navrange = CtlCount-1;
        dm.clean_title_1_2();
        if (sublevels[self->relative_navlevel] != 0) {
          
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
        self->knobsetting = true ;
        navrange = 127;
        if (sublevels[self->relative_navlevel] == 0 ) {
          returntonav(self->relative_navlevel,CtlCount-1,sublevels[self->relative_navlevel]);
        } else {
          dm.clean_title_1_2();
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
        gg.midiknobassigned[cc_nt] = cc_cl;
      }

      static void set_it(){
        self->knobsetting = false ;
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
    byte previous_note = 0 ;
    byte velocity = 0 ;
    byte sloper_step = 0;
    float targetFreq;
    float currentFreq = 0;
    float steps = 0 ;
    bool f303 = 0 ;
    int totalUpdates = 0;
    int currentUpdate = 0;
    float startFreq;
    
    SynthLiner(byte line_index = 0 ) : l_index(line_index) { }

    void liner_on(byte data1, byte data2) {
      if (this->activated||data1==this->note) {
        liner_off();
        return;
      }
      this->activated=true;
      this->note=data1;
      this->velocity=data2;
      this->f303=1;

      this->targetFreq = notestofreq[this->note][1];
      int note_diff = ((this->note + (64 - gg.portamento_height)) % 127 + 127) % 127;
      switch (gg.glideMode) {
        case Off:
          this->currentFreq = this->targetFreq ;
        break;

        case Portamento:
        if (gg.portamento_time)  {
          this->currentFreq = notestofreq[this->previous_note][1];
          }
        break;

        case ReversePortamento:
          if (gg.portamento_time)  {
            this->targetFreq = notestofreq[this->previous_note][1];
            this->currentFreq = notestofreq[this->note][1];
          }
        break;

        case PitchAttack:
          this->currentFreq = notestofreq[note_diff][1];
        break;

        case ReversePitchAttack:
          this->currentFreq = this->targetFreq;
          this->targetFreq = notestofreq[note_diff][1];
        break;

      }
      this->startFreq = this->currentFreq;
      this->totalUpdates = max(1, (int)(gg.portamento_time / 0.145));
      //this->steps = (this->targetFreq - this->currentFreq) / this->totalUpdates;
      this->currentUpdate = 0;

     // setPortamentoTime();
      
      setfreqWavelines();
      enveloppesL[this->l_index]->hold(gg.millitickinterval - gg.adsrlevels[3]);
      enveloppesL[this->l_index]->noteOn();
      _rg.add_active_synth(this);
    }

    void update_line_old(){
     // float t = (float)this->currentUpdate / this->totalUpdates;
      this->currentFreq += this->steps;
      if ((this->steps > 0 && this->currentFreq >= this->targetFreq) ||
        (this->steps < 0 && this->currentFreq <= this->targetFreq) ) {
        this->currentFreq = this->targetFreq;
      }
      refreshWavelines(); 
      this->currentUpdate++;
    }

    void update_line(){
      float glide_curve = (64 - gg.glide_slope) / 64.0f ;
        if (this->currentUpdate < this->totalUpdates)
        {
            float t = (float)this->currentUpdate / (float)this->totalUpdates;
            float s = t;
            if (glide_curve > 0.0f) {
              float exp = 1.0f + 4.0f * glide_curve;
              s = powf(t, exp);
            }
            else if (glide_curve < 0.0f)  {
              float exp = 1.0f - 4.0f * glide_curve;
              s = 1.0f - powf(1.0f - t, exp);
            }

            this->currentFreq = this->startFreq + (this->targetFreq - this->startFreq) * s;

            this->currentUpdate++;

            if (this->currentUpdate >= this->totalUpdates)
                this->currentFreq = this->targetFreq;
        }

        refreshWavelines();
    }
    void setPortamentoTime(){
      //float dt = AUDIO_BLOCK_SAMPLES * 1000.0f / AUDIO_SAMPLE_RATE_EXACT;
      //128*1000 / 44100.0f = 2,902494331 ms if we update every audio sample 
      //porta is scaled 20x so 2.9 becomes 0.145 since aproximations are fine
      this->totalUpdates = max(1, (int)(gg.portamento_time / 0.145));
      this->steps = (this->targetFreq - this->currentFreq) / this->totalUpdates;
      this->currentUpdate = 0;
    }
        
    void setfreqWavelines() {
      update_line();
      activateWavelines();
    }
    
    void activateWavelines() {
      //Sample & Hold waveform does not support phase modulation. Attempting to modulate its phase may give random or inconsistent results.
      for (int i = 0; i < OSCS_COUNT; i++) {
        if (gg.audio_obj_type[i]) audio_obj_starter[gg.audio_obj_type[i]-1](this->l_index,i,this->currentFreq,this->targetFreq,this->velocity);
      }
    }

    void refreshWavelines() {
      for (int i = 0; i < OSCS_COUNT; i++) {
        // oscs Offs or of string type do not need refreshing
        if (gg.audio_obj_type[i] && gg.audio_obj_type[i] < 4) {
         audio_obj_refresher[gg.audio_obj_type[i]-1](this->l_index,i,this->currentFreq,this->velocity);
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
      this->previous_note = this->note ;
      this->note = 0 ;

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
      if (!gg.digitalplay) {
        Flashmixer[int(l_index / 4)]->gain(l_index - 4 * int(l_index / 4),(gg.smixervknobs[l_index] / 127.0) * (data2 / 127.0));
      } else {
        Flashmixer[int(l_index / 4)]->gain(l_index - 4 * int(l_index / 4),(gg.smixervknobs[l_index] / 127.0));
      }
      */
      playable_file = (String)Flashsamplename[gg.Sampleassigned[(int)(data1)]];
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
      //FlashSampler[l_index]->stop();
      activated = false;
      note = 0 ;
      velocity = 0 ;
    }
};


FlashLiner *flash_lines[FLASH_LINERS_COUNT] = {nullptr};


