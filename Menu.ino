
void reinitsublevels(byte fromlei) {
  for (byte i = fromlei; i < 7; i++) {
    sublevels[i] = 0;
  }
}

void show_pots_to_assign() {
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
}

void knobsettermidi() { 
  midiknobassigned[find_assigned_knob(sublevels[1])] = 0;
  midiknobassigned[sublevels[2]] = sublevels[1]; 
}

int find_assigned_knob(int k){
  for (int i = 0; i < 128; i++) {
    if (midiknobassigned[i] == k){
      return i;
    }
  }
  return 0 ;
}

void learn_midi(byte captured){
  midiknobassigned[find_assigned_knob(sublevels[1])] = 0;
  sublevels[2] = captured ;
  midiknobassigned[sublevels[2]] = sublevels[1];
  returntonav(1);
}

void show_avalable_controls() {
  display.clearDisplay();
  canvastitle.fillScreen(SSD1306_BLACK);
  canvasBIG.fillScreen(SSD1306_BLACK);
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
}
void knobassigner() {
  if (navlevel == 2) {
    navrange = 127;
    //reinitsublevels(2);
    show_pots_to_assign();
    dodisplay();
  }
  if (navlevel == 1) {
    navrange = allfxes-1;
    show_avalable_controls();
    dodisplay();
  }
  if (navlevel >= 3) {
    knobsettermidi();
    returntonav(1);
  }
}
