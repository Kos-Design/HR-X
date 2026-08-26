#include "Voices.h"
#include "Frequencies.h"
#include "MenuClasses.h"
#include "Presets.h"


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

ActiveLinesRegister::ActiveLinesRegister() { }

void ActiveLinesRegister::add_active_synth(SynthLiner *snth){
    active_synths[synth_lines_active] = snth ;
    synth_lines_active++;
}

void ActiveLinesRegister::remove_inactive_synth(SynthLiner *snth){
    for (uint8_t i = 0; i < synth_lines_active; i++) {
        if (active_synths[i] == snth) {
          active_synths[i] = active_synths[synth_lines_active - 1];
          synth_lines_active--;
          return;
        }
    }
}

void ActiveLinesRegister::init_synth_liners(){
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    synth_lines[i] = new SynthLiner(i);
  }
}

void ActiveLinesRegister::init_flash_liners(){
  for (int i = 0; i < FLASH_LINERS_COUNT; i++) {
    flash_lines[i] = new FlashLiner(i);
  }
}

SynthLiner::SynthLiner(byte line_index ) : l_index(line_index) { }

void SynthLiner::liner_on(byte data1, byte data2) {
    if (this->activated||data1==this->note) {
    liner_off();
    return;
    }
    this->activated=true;
    this->note=data1;
    this->velocity=data2;
    this->f303=1;

    this->targetFreq = bb.notestofreq[this->note];
    int note_diff = ((this->note + (64 - gg.portamento_height)) % 127 + 127) % 127;
    switch (gg.glideMode) {
      case Off:
          this->currentFreq = this->targetFreq ;
      break;

      case Portamento:
      if (gg.portamento_time)  {
          this->currentFreq = bb.notestofreq[this->previous_note];
          }
      break;

      case ReversePortamento:
          if (gg.portamento_time)  {
          this->targetFreq = bb.notestofreq[this->previous_note];
          this->currentFreq = bb.notestofreq[this->note];
          }
      break;

      case PitchAttack:
          this->currentFreq = bb.notestofreq[note_diff];
      break;

      case ReversePitchAttack:
          this->currentFreq = this->targetFreq;
          this->targetFreq = bb.notestofreq[note_diff];
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
    
    Serial.println();
    Serial.print("liner played = ");
    Serial.print(this->l_index);
    Serial.print(" is arp_starter = ");

    Serial.print(this->arp_starter);
    Serial.print(" note onned = ");
    Serial.print(this->note);
    Serial.print(" next arp note = ");
    Serial.print(this->next_arp_note);
    Serial.print(" arp_length = ");
    Serial.print(this->length_in_arp);
    

}

void SynthLiner::update_line_old(){
    // float t = (float)this->currentUpdate / this->totalUpdates;
    this->currentFreq += this->steps;
    if ((this->steps > 0 && this->currentFreq >= this->targetFreq) ||
    (this->steps < 0 && this->currentFreq <= this->targetFreq) ) {
    this->currentFreq = this->targetFreq;
    }
    refreshWavelines();
    this->currentUpdate++;
}

void SynthLiner::update_line(){
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
void SynthLiner::setPortamentoTime(){
    //float dt = AUDIO_BLOCK_SAMPLES * 1000.0f / AUDIO_SAMPLE_RATE_EXACT;
    //128*1000 / 44100.0f = 2,902494331 ms if we update every audio sample
    //porta is scaled 20x so 2.9 becomes 0.145 since aproximations are fine
    this->totalUpdates = max(1, (int)(gg.portamento_time / 0.145));
    this->steps = (this->targetFreq - this->currentFreq) / this->totalUpdates;
    this->currentUpdate = 0;
}

void SynthLiner::setfreqWavelines() {
    update_line();
    activateWavelines();
}

void SynthLiner::activateWavelines() {
    static constexpr void (*audio_obj_starter[4])(byte,byte,float,float,byte) = {&waveformize, &FMformize, &drumize, &stringize};

    //Sample & Hold waveform does not support phase modulation. Attempting to modulate its phase may give random or inconsistent results.
    for (int i = 0; i < OSCS_COUNT; i++) {
        if (gg.audio_obj_type[i]) audio_obj_starter[gg.audio_obj_type[i]-1](this->l_index,i,this->currentFreq,this->targetFreq,this->velocity);
    }
}

void SynthLiner::refreshWavelines() {
    for (int i = 0; i < OSCS_COUNT; i++) {
    // oscs Offs or of string type do not need refreshing
        if (gg.audio_obj_type[i] && gg.audio_obj_type[i] < 4) {
            audio_obj_refresher[gg.audio_obj_type[i]-1](this->l_index,i,this->currentFreq,this->velocity);
        }
    }
}

void SynthLiner::liner_off() {
      // AudioNoInterrupts();
      //if (enveloppesL[this->l_index]->isActive()) {
      enveloppesL[this->l_index]->hold(0);
      enveloppesL[this->l_index]->noteOff();
      this->f303 = 0;
      this->activated = false;
      _rg.remove_inactive_synth(this);
      this->previous_note = this->note ;
      /*
      Serial.println();
      Serial.print(" note offed = ");
      Serial.print(this->note);
      */
      this->note = 0 ;
      this->length_in_arp = 0 ;
      this->arp_starter = 0 ;
      this->next_arp_note = 0 ;
      
    }


FlashLiner::FlashLiner(byte line_index) : l_index(line_index) {  }

void FlashLiner::liner_on(byte data1, byte data2) {

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
    FlashSampler[l_index]->play((const char*)bb.Flashsamplename[gg.Sampleassigned[(int)(data1)]]);

    //playRaw(playable_file.c_str());
    activated=true;
    note=data1;
    velocity=data2;

}

void FlashLiner::liner_off() {
    //FlashSampler[l_index]->stop();
    activated = false;
    note = 0 ;
    velocity = 0 ;
}


