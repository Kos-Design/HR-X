
int pad_result;

void allpasslevels(){
    mix303L1.gain(0, 1);
  mix303L1.gain(1, 0);
  mix303L1.gain(2, 0);
}


void pseudo303() {
  
    for ( int i = 0 ; i < 8 ; i++ ) {
            
           
      
       if(glidemode>0 && dogliding[i]){

       glidefactorCmode[i] = leglideposition[i]/(millitickinterval*1.0) ;
      
       notefrequency = ( glidefactorCmode[i])*leglidershiftCmode[i] + notestofreq[lapreviousnotewCmode[i]][1] ;
         
         tweakfreqlive(i,notefrequency);
         
    if ( leglideposition[i] < (millitickinterval*2.0*(glidemode/128.0)/2.0) ) {
      leglideposition[i]++ ;
      //Serial.print(leglideposition[i]);
      } else {
        stopglidenoteChords(i);
        
      }
      
   // }
       }

     if (!stoptick ){
            checkall128cc();
            }     
         
    
    
   if ( tb303[i]==1 ) {
     

    int letimerz303 = millis()-le303start[i] ;
    if (letimerz303>le303pulsewidth){
  
      tb303[i]=0;
      le303start[0];
      letimerz303=le303pulsewidth;
    }
  
    ladiff1 = (letimerz303*1.0/le303pulsewidth);
    ladiff2 = (letimerz303*1.0/le303pulsewidth2);
   
    letbfreq = le303filterzrange+100-(le303filterzrange*( fxslopedown2(slope1, ladiff1)));
     //AudioNoInterrupts();
     les303filterz[i]->frequency(letbfreq);
     
    if ( ladiff2 <= 1) {
      
   les303filterz[i]->resonance( 0.1+(le303filterzreso)*( fxslopedown2(slope2, ladiff2) ));
    }
    lfo303levshiter = fxslopedown2(slope2, ladiff2) ;
   LFOrm303.amplitude((float)(LFOlevel[3]/512.00)*(1-lfo303levshiter));
     //les303passes[i]->gain(2,sin(((le303filterzgainz[2]* (letimerz303*1.0/le303pulsewidth2)))*3.14159));
    // Serial.println("fading out"); 
   
   }
   
  
    }
  
  
}

byte itr = 0;
int c_change ;
int cc_note_num ;
void loop() {
PadResult pad_result = Pads.padloop();
int paddered = arranged_buttons[pad_result.pad_result[0]][pad_result.pad_result[1]] ;
 cc_note_num = pot_assignements[9+paddered] - allfxes;
      //Serial.print(" received ");
      //Serial.print(c_change);
//36 is the cancel button, should not trigger another note or control.
if ((pad_result.pad_result[2] == 1 ) && (paddered != 36)) {
  Serial.println(" ");
      Serial.print("paddered ");
      Serial.print(paddered);
        Serial.println(" ");
      Serial.print("pot_assignements ([9+paddered])=");
      Serial.print(cc_note_num);
   
  MaNoteOn(16,cc_note_num,64);
} else if ((pad_result.pad_result[2] == 0 ) && (paddered != 36)) {
  MaNoteOff(16,cc_note_num,0);
}
 if (initdone) {
  if (noteprint) {
  printlanote();
  }
 loopRecorder();
  if (!stoptick ) {
    if (!externalticker && metro0.check() == 1)  {
      //Serial.println("from loop tick");
      tick();
    }

  }
 if ( metro303.check() == 1 ) {
    
 pseudo303();

  }

  updatebuttons();
  evalinputs();
  evalrota();
  }
  
  //usbhost queries
   loopmidihost();
  loopusbHub();
  
    if (( millis() % 10 ) == 0) {
      
     c_change = Muxer.read_val(itr);
     if (c_change > 0 )  {
      if (itr < 15 ) {
   
      MaControlChange(16, (byte)pot_assignements[itr], (byte)((c_change/1024.0)*128)) ;
     /*
     //10 & 12 = joystick
     //11,13,14 = equalizer faders
     //15 = crossfader
     // if ((itr !=11) && (itr !=13) && (itr !=14) && (itr !=15) ){
      Serial.println(" ");
      Serial.print("mux ");
      Serial.print(itr);
      Serial.print(" received ");
      Serial.print(c_change);
      Serial.print(" = ");
      Serial.print((byte)((c_change/1024.0)*128));
      Serial.print(" assigned to ");
      Serial.print((byte)pot_assignements[itr]);
      Serial.print(" = ");
      Serial.print(ControlList[(byte)pot_assignements[itr]]);
     */
     }
    }
     itr++;
     if (itr >= 16 ) {
      itr = 0 ;  
     }
}
//hdd_check();
}

void printit() {
  Serial.print(" navrange: ");
  Serial.print(navrange);
   Serial.print(" navlevel: ");
  Serial.print(navlevel);
  Serial.print(" sublevel[");
   Serial.print(navlevel);
    Serial.print("]:");
  Serial.println(sublevels[navlevel]);
  Serial.println(" ");
  Serial.print(" s0 = ");
  Serial.print(sublevels[0]);
  Serial.print(" s1 = ");
  Serial.print(sublevels[1]);
  Serial.print(" s2 = ");
  Serial.print(sublevels[2]);
  Serial.print(" s3 = ");
  Serial.print(sublevels[3]);
  Serial.print(" s4 = ");
  Serial.print(sublevels[4]);
  Serial.print(" s5 = ");
  Serial.println(sublevels[5]);



}
