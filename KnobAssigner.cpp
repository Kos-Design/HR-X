#include "KnobAssigner.h"
KnobAssigner* KnobAssigner::self = nullptr;

KnobAssigner::KnobAssigner() {
                    self = this;
                    self->home_navrange=CtlCount-1;
                    self->relative_navlevel=2;
                    self->max_navlevel=3;
                    self->sublevels_address={2,0,0};
                    }
 
void KnobAssigner::KnobAssigner::show() {
        lv.knobsetting = false ;
        _actionable[lv.navlevel-self->relative_navlevel]();
      }
void KnobAssigner::learn_midi(byte captured){
        //used to unassign previousely set cc but lets keep it, duplicates are fine
        //gg.midiknobassigned[find_assigned_knob(lv.sublevels[1])] = 0;
        lv.sublevels[self->relative_navlevel+1] = captured ;
        gg.midiknobassigned[lv.sublevels[self->relative_navlevel+1]] = lv.sublevels[self->relative_navlevel];
        dm.returntonav(self->relative_navlevel,self->home_navrange,lv.sublevels[self->relative_navlevel]);
      }

int KnobAssigner::find_assigned_knob(int k){
        for (int i = 0; i < 128; i++) {
          if (gg.midiknobassigned[i] == k){
            return i;
          }
        }
        return 0 ;
      }

void KnobAssigner::kb_home(){
        lv.navrange = self->home_navrange;
        dm.clean_title_1_2();
        if (lv.sublevels[self->relative_navlevel] != 0) {
          
          canvastitle.println(ctl[lv.sublevels[self->relative_navlevel]].name);
          canvasBIG.setTextSize(2);
          canvasBIG.setCursor(0, 40);
          lv.sublevels[self->relative_navlevel+1] = find_assigned_knob(lv.sublevels[self->relative_navlevel]) ;
          if (lv.sublevels[self->relative_navlevel+1] != 0) {
            canvasBIG.print("Midi");
            canvasBIG.setTextSize(1);
            canvasBIG.setCursor(50, 47);
            canvasBIG.print("(cc)");
            canvasBIG.setCursor(71, 39);
            canvasBIG.setTextSize(3);
            canvasBIG.print(":");
            canvasBIG.setTextSize(2);
            canvasBIG.setCursor(85, 40);

            canvasBIG.print(lv.sublevels[self->relative_navlevel+1]);
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

void KnobAssigner::assigner(){
        lv.knobsetting = true ;
        lv.navrange = 127;
        if (lv.sublevels[self->relative_navlevel] == 0 ) {
          dm.returntonav(self->relative_navlevel,self->home_navrange,lv.sublevels[self->relative_navlevel]);
        } else {
          dm.clean_title_1_2();
          canvastitle.println(ctl[lv.sublevels[self->relative_navlevel]].name);
          canvasBIG.setCursor(0, 40);
          if (lv.sublevels[self->relative_navlevel+1] != 0) {
            canvasBIG.print("Midi");
            canvasBIG.setTextSize(1);
            canvasBIG.setCursor(50, 47);
            canvasBIG.print("(cc)");
            canvasBIG.setCursor(71, 39);
            canvasBIG.setTextSize(3);
            canvasBIG.print(":");
            canvasBIG.setTextSize(2);
            canvasBIG.setCursor(85, 40);
            canvasBIG.print(lv.sublevels[self->relative_navlevel+1]);
          } else {
            //canvasBIG.setTextSize(1);
            canvasBIG.println("Unassigned");
          }
        }
        dm.dodisplay();
      }
      
void KnobAssigner::set_midi_cc_to_ctl(byte cc_nt, int cc_cl){
        gg.midiknobassigned[cc_nt] = cc_cl;
      }

void KnobAssigner::set_it(){
        lv.knobsetting = false ;
        set_midi_cc_to_ctl(find_assigned_knob(lv.sublevels[self->relative_navlevel]), 0);
        set_midi_cc_to_ctl(lv.sublevels[self->relative_navlevel+1] , lv.sublevels[self->relative_navlevel]);

        dm.returntonav(self->relative_navlevel,self->home_navrange, lv.sublevels[self->relative_navlevel]);
      }

