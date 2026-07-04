
void reinitsublevels(byte fromlei) {
  for (byte i = fromlei; i < 7; i++) {
    sublevels[i] = 0;
  }
}

void learn_midi(byte captured){
  //used to unassign previousely set cc but lets keep it, duplicates are fine
  //midiknobassigned[find_assigned_knob(sublevels[1])] = 0;
  sublevels[2] = captured ;
  midiknobassigned[sublevels[2]] = sublevels[1];
  returntonav(1,allfxes-1,sublevels[1]);
}

class KnobAssigner : public SectionHolder {
  public:
      KnobAssigner() {
                    this->home_navrange=allfxes-1;
                    this->relative_navlevel=1;
                    this->max_navlevel=3;
                    this->sublevels_address={2,0,0};
                    }
 
      static void show() {
        _actionable[navlevel-1]();
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
        navrange = allfxes-1;
        dm.clear_3();
        canvastitle.setCursor(0, 0);
        if (sublevels[1] != 0) {
          canvastitle.setTextSize(2);
          canvastitle.println(ControlList[sublevels[1]]);
          canvasBIG.setTextSize(2);
          canvasBIG.setCursor(0, 40);
          sublevels[2] = find_assigned_knob(sublevels[1]) ;
          if (sublevels[2] != 0) {
            canvasBIG.print("Midi");
            canvasBIG.setTextSize(1);
            canvasBIG.setCursor(50, 47);
            canvasBIG.print("(cc)");
            canvasBIG.setCursor(71, 39);
            canvasBIG.setTextSize(3);
            canvasBIG.print(":");
            canvasBIG.setTextSize(2);
            canvasBIG.setCursor(85, 40);

            canvasBIG.print(sublevels[2]);
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
        dodisplay();

      }

      static void assigner(){
        navrange = 127;
        if (sublevels[1] == 0 ) {
          returntonav(1);
        } else {
          display.clearDisplay();
          canvastitle.fillScreen(SSD1306_BLACK);
          canvasBIG.fillScreen(SSD1306_BLACK);
          canvastitle.setCursor(0, 0);
          canvastitle.setTextSize(2);
          canvastitle.println(ControlList[sublevels[1]]);
          canvasBIG.setTextSize(2);
          canvasBIG.setCursor(0, 40);
          if (sublevels[2] != 0) {
            canvasBIG.print("Midi");
            canvasBIG.setTextSize(1);
            canvasBIG.setCursor(50, 47);
            canvasBIG.print("(cc)");
            canvasBIG.setCursor(71, 39);
            canvasBIG.setTextSize(3);
            canvasBIG.print(":");
            canvasBIG.setTextSize(2);
            canvasBIG.setCursor(85, 40);
            canvasBIG.print(sublevels[2]);
          } else {
            //canvasBIG.setTextSize(1);
            canvasBIG.println("Unassigned");
          }
        }
        dodisplay();
      }

      static void set_it(){
        midiknobassigned[find_assigned_knob(sublevels[1])] = 0;
        midiknobassigned[sublevels[2]] = sublevels[1];
        returntonav(1,allfxes-1,sublevels[1]);
      }


  private:

    static constexpr void (*_actionable[3])() = { &kb_home, &assigner, &set_it };

};

EXTMEM KnobAssigner _ka = KnobAssigner();

class SynthLiner {
  public:
    byte l_index = 0 ;
    bool activated = 0 ;
    byte note = 0 ;
    byte velocity = 0 ;

    SynthLiner(byte line_index = 0 ) : l_index(line_index) {
    }

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

};

SynthLiner* synth_lines[liners_count] = {nullptr};