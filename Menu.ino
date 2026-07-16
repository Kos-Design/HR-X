
void reinitsublevels(byte fromlei) {
  for (byte i = fromlei; i < 9; i++) {
    sublevels[i] = 0;
  }
}

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

      static void set_it(){
        midiknobassigned[find_assigned_knob(sublevels[self->relative_navlevel])] = 0;
        midiknobassigned[sublevels[self->relative_navlevel+1]] = sublevels[self->relative_navlevel];
        returntonav(self->relative_navlevel,CtlCount-1,sublevels[self->relative_navlevel]);
      }


  private:

    static constexpr void (*_actionable[3])() = { &kb_home, &assigner, &set_it };
    static KnobAssigner* self;
};


KnobAssigner* KnobAssigner::self = nullptr;
EXTMEM KnobAssigner _ka;

class SynthLiner {
  public:
    byte l_index = 0 ;
    bool activated = 0 ;
    byte note = 0 ;
    byte velocity = 0 ;

    SynthLiner(byte line_index = 0 ) : l_index(line_index) { self = this; }

    void liner_on(byte data1, byte data2) {
      if (activated||data1==note) {
        liner_off();
      }
      activated=true;
      note=data1;
      velocity=data2;
      //to avoid bounces and midi panik !
      if (!enveloppesL[l_index]->isActive()){
        if (!tb303[l_index]) {
          pulsers[l_index][0]=millis();
          tb303[l_index] = 1;
        }
        enveloppesL[l_index]->hold(millitickinterval - adsrlevels[3]);
        //enveloppesR[liner]->hold(500);
        if (check_glide_status(note)){
          if (!chordson) {
            notefrequency = notestofreq[note_before][1];
            setfreqWavelines(notefrequency,l_index,velocity);
            startglidenote(l_index,note);
          } else {
            notefrequency = notestofreq[lapreviousnotewCmode[l_index]][1];
            startglidenoteChords(l_index, note);
            setfreqWavelines(notefrequency, l_index, velocity);
          }
          note_before = note ;
        } else {
          notefrequency = notestofreq[note][1];
          setfreqWavelines(notefrequency, l_index, velocity);
        }
        enveloppesL[l_index]->noteOn();
      } else {
        liner_off();
      }
    }

    void liner_off() {
      // AudioNoInterrupts();
      //if (enveloppesL[l_index]->isActive()) {
        enveloppesL[l_index]->hold(0);
        enveloppesL[l_index]->noteOff();
        if (tb303[l_index]) {
          tb303[l_index] = 0;
        }
        activated = false;
        note = 0 ;
      }
    //}
    static SynthLiner* self;
};
SynthLiner* SynthLiner::self = nullptr;

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
      if (FlashSampler[l_index]->isPlaying()) {
        FlashSampler[l_index]->stop();
      }
      if (!digitalplay) {
        Flashmixer[int(l_index / 4)]->gain(l_index - 4 * int(l_index / 4),(smixervknobs[l_index] / 127.0) * (data2 / 127.0));
      } else {
        Flashmixer[int(l_index / 4)]->gain(l_index - 4 * int(l_index / 4),(smixervknobs[l_index] / 127.0));
      }
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


FlashLiner *flash_lines[flash_liners_count] = {nullptr};

