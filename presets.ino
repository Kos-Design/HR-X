
File preset_file ;

void displaypresetmenu() {
  navrange = 4;
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvastitle.fillScreen(SSD1306_BLACK);

  presetmenuBG();
  dolistpresetsmenu();
  dodisplay();
}

void presetmenuBG() {
  display.clearDisplay();
  if (navlevel == 1) {
    reinitsublevels(2);
    navrange = 4;
  }
  if (navlevel == 2 && sublevels[1] != 4) {
    // Serial.println("got into preset list");
  }
  if (navlevel > 1) {
    if (sublevels[1] == 0) {
      navrange = presets_count;
    } else {
      // setnavrange();
      navrange = presets_count - 1;
    }
  }
  dolistofpresets();
  dodisplay();

  if (navlevel >= 3) {
    // Serial.println("preset action selected");

    navlevel = 1;
    vraipos = sublevels[1];
    myEnc.write(4 * vraipos);
    navrange = 4;

    switch (sublevels[1]) {

    case 0:
      writepreset();
      break;

    case 1:

      readpreset();
      break;

    case 2:
      copypreset();
      break;

    case 3:
      deletepreset();
      break;

    case 4:
      break;

    default:
      break;
    }
    displaypresetmenu();
  }
}

void dolistpresetsmenu() {
  char presetmenulabels[truesizeofpresetmenulabels][12] = {
      "Save", "Load", "Copy", "Delete", "Params"};
  byte startx = 5;
  byte starty = 16;
  char *textin = (char *)presetmenulabels[sublevels[1]];
  // Serial.println(textin);
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(2);
  canvastitle.println(textin);

  canvasBIG.setTextSize(1);
  canvasBIG.fillScreen(SSD1306_BLACK);

  for (int filer = 0; filer < truesizeofpresetmenulabels - 1 - (sublevels[1]);
       filer++) {

    canvasBIG.setCursor(startx, starty + ((filer)*10));
    canvasBIG.println(presetmenulabels[sublevels[1] + 1 + filer]);
  }
  for (int filer = 0; filer < sublevels[1]; filer++) {

    canvasBIG.setCursor(
        startx,
        (10 * (truesizeofpresetmenulabels - sublevels[1]) + 6 + ((filer)*10)));
    canvasBIG.println(presetmenulabels[filer]);
  }
}

void writepreset() {
  if (sublevels[2] == presets_count) {
    String presets_base_path = "PRESETS" ;
    String presets_sub_path = "SYNTH" ;
   
    if (!(SD.exists(presets_base_path.c_str()))) {
      Serial.println("making dir preset");
      SD.mkdir(presets_base_path.c_str());
    }
    
    if (!(SD.exists((presets_base_path+"/"+presets_sub_path).c_str()))) {
      Serial.println("making sub-dir synth");
      SD.mkdir((presets_base_path+"/"+presets_sub_path).c_str());
    }
    
    String new_preset_name = get_new_file_name("PRESETS/SYNTH/SYNSET") ;
   //mytxtFile = SD.open(new_preset_name.c_str(), FILE_WRITE);
    preset_file = SD.open(new_preset_name.c_str(), FILE_WRITE);

    Serial.println(new_preset_name);
    Serial.println(preset_file.name());
  } else {
    if (SD.exists((char *)SynthPresetfullpath[sublevels[2]])) {
      SD.remove((char *)SynthPresetfullpath[sublevels[2]]);
    }
    preset_file = SD.open((char *)SynthPresetfullpath[sublevels[2]], FILE_WRITE);
  }
  // if the file opened okay, write to it:
  if (preset_file) {
    // Serial.print("Writing to ");
    //  Serial.println(preset_file.name());
    writesynthpreset();
    // close the file:
    preset_file.close();
    // Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    // Serial.println("error opening test.txt");
  }
  // listfileslist("/");
  preset_file.close();
  dopresetlist();
}

void dolistofpresets() {
  int startx = 80;
  int starty = 16;
  // char* textinz = (char*)lesfiles[sublevels[3]].name() ;

  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(startx, 0);
  canvastitle.setTextSize(1);

  if (sublevels[2] == presets_count && sublevels[1] == 0) {

    canvastitle.print("New()");
  } else {
    canvastitle.print((char *)SynthPresetbase[sublevels[2]]);
  }
  canvastitle.setTextSize(1);
  canvasBIG.setTextSize(1);
  canvasBIG.fillScreen(SSD1306_BLACK);
  if (sublevels[2] == presets_count) {
    for (int filer = 0; filer < sublevels[2] - 1; filer++) {
      canvasBIG.setCursor(startx, (10 * (presets_count - sublevels[2])) +
                                      16 + ((filer)*10));
      canvasBIG.println((char *)SynthPresetbase[filer]);
    }
  } else {
    for (int filer = 0; filer < presets_count - 1 - (sublevels[2]);
         filer++) {
      canvasBIG.setCursor(startx, starty + ((filer)*10));
      canvasBIG.println((char *)SynthPresetbase[sublevels[2] + 1 + filer]);
    }

    for (int filer = 0; filer < sublevels[2]; filer++) {

      canvasBIG.setCursor(startx, (10 * (presets_count - sublevels[2])) +
                                      6 + ((filer)*10));
      canvasBIG.println((char *)SynthPresetbase[filer]);
    }
  }
}

void setnavrange() {
  if (presets_count < 2) {
    navrange = 2;
    // Serial.println("SOMETHING IS WRONG");
  } else {
    navrange = presets_count - 1;
  }
}

void writesynthpreset() {

  preset_file.print("<Presets><Synth>\n");

  INTinsertmytxtfile(slope1, (char*)"slope1");
     Serial.println(" ");
    Serial.print("slope1 ");
    Serial.print(slope1);
  
  INTinsertmytxtfile(slope2, (char*)"slope2");
  INTinsertmytxtfile(millitickinterval, (char*)"milli");
  INTinsertmytxtfile(cutoff_pulse, (char*)"pulse1");
  INTinsertmytxtfile(reson_pulse, (char*)"pulse2");
        Serial.println(" ");
    Serial.print("reson_pulse ");
    Serial.print(reson_pulse);

  for (int i = 0; i < 3; i++) {
    INTinsertmytxtfile(le303ffilterzVknobs[i], (char*)"f303vknobs");
    INTinsertmytxtfile(mixle303ffilterzVknobs[i], (char*)"mixfilters303");
    FLOATinsertmytxtfile(le303filterzgainz[i], (char*)"filtergainz303");
  }

  INTinsertmytxtfile(le303filterzwet, (char*)"le303filterzwet");
  INTinsertmytxtfile(le303filterzrange, (char*)"le303range");
  FLOATinsertmytxtfile(le303filterzfreq, (char*)"le303freq");
  FLOATinsertmytxtfile(le303filterzreso, (char*)"le303reso");
        Serial.println(" ");
    Serial.print("le303filterzreso ");
    Serial.print(le303filterzreso);

  FLOATinsertmytxtfile(le303filterzoctv, (char*)"le303octv");
  INTinsertmytxtfile(int(glidemode), (char*)"glidemode");
  INTinsertmytxtfile(preampleswaves, (char*)"preampleswaves");
  INTinsertmytxtfile(int(arpegiatorOn) + 1, (char*)"arpegiatorOn");
  INTinsertmytxtfile(arpegiatortype, (char*)"arpegiatortype");
  INTinsertmytxtfile(arpeglengh, (char*)"arpeglengh");
  INTinsertmytxtfile(arpegmode, (char*)"arpegmode");
  INTinsertmytxtfile(arpegnumofnotes, (char*)"arpegnumofnotes");
  INTinsertmytxtfile(arpegstartoffset, (char*)"arpegstartoffset");
  INTinsertmytxtfile(arpeggridC, (char*)"arpeggridC");
  INTinsertmytxtfile(arpeggridS, (char*)"arpeggridS");
  INTinsertmytxtfile(int(digitalplay) + 1, (char*)"digitalplay");
  INTinsertmytxtfile(int(chordson) + 1, (char*)"chordsOn");
  INTinsertmytxtfile(lasetchord, (char*)"lasetchord");
  INTinsertmytxtfile(wetins[0], (char*)"wetsynth");
  INTinsertmytxtfile(wetins[1], (char*)"wetsampler");
  INTinsertmytxtfile(wetins[2], (char*)"wetother");
  INTinsertmytxtfile(synthmidichannel, (char*)"synthmidichannel");
  INTinsertmytxtfile(samplermidichannel, (char*)"samplermidichannel");
  INTinsertmytxtfile(tapnote, (char*)"tapnote");

  for (int i = 0; i < 16; i++) {
    INTinsertmytxtfile(smixervknobs[i], (char*)"smixer");
  }

  for (int i = 0; i < 3; i++) {
    INTinsertmytxtfile(fx[i]->plugged_fx_type, (char*)"effect");
  }
  for (int i = 0; i < 4; i++) {
    FLOATinsertmytxtfile(WetMixMasters[i], (char*)"wetmixes");
    Serial.println(" ");
    Serial.print("WetMixMasters ");
    Serial.print(WetMixMasters[i]);
    INTinsertmytxtfile(mixlevelsM[i], (char*)"mixlevelsM");
  }
  for (int i = 0; i < synths_count; i++) {
    //TODO:wetmix & mixers out of synths_count loop ,still iter to 4
    FLOATinsertmytxtfile(mixlevelsL[i], (char*)"mixlevelsL");
    FLOATinsertmytxtfile(wavesfreqs[i], (char*)"wavefreq");
    FLOATinsertmytxtfile(panLs[i], (char*)"panL");
    INTinsertmytxtfile(FMmodulated[i], (char*)"modu");
    INTinsertmytxtfile(Waveformstyped[i], (char*)"Waveform");
    INTinsertmytxtfile(wave1offset[i], (char*)"offset");
    FLOATinsertmytxtfile(phaselevelsL[i], (char*)"phaselL");
    INTinsertmytxtfile(LFOlevel[i], (char*)"lfolevel");
    INTinsertmytxtfile(LFOformstype[i], (char*)"lfoType");
    INTinsertmytxtfile(LFOfreqs[i], (char*)"lfofreqs");
    INTinsertmytxtfile(LFOphase[i], (char*)"lfoPhase");
    INTinsertmytxtfile(LFOoffset[i], (char*)"lfoOffset");
    INTinsertmytxtfile(LFOsync[i] + 1, (char*)"lfosync");
  }
  
    for (int j = 0; j < 6; j++) {
      INTinsertmytxtfile(adsrlevels[j], (char*)"adsr");
    }
  

  for (int i = 0; i < all_buttonns; i++) {
    INTinsertmytxtfile(pot_assignements[i], (char*)"pot_assigned");
    INTinsertmytxtfile(but_channel[i], (char*)"but_channel");
    INTinsertmytxtfile(but_velocity[i], (char*)"but_velocity");
  }
  for (int i = 0; i < 15; i++) {
    INTinsertmytxtfile(ordered_pots[i], (char*)"muxed_pots");
    INTinsertmytxtfile(muxed_channels[i], (char*)"muxed_channels");
  }
  for (int i = 0; i < 128; i++) {

    Serial.print(", ");
    Serial.println(midiknobassigned[i]);
    INTinsertmytxtfile(midiknobassigned[i], (char*)"Midiknobassigned");
    INTinsertmytxtfile(Sampleassigned[i], (char*)"Sampleassigned");
  }
  for (int i = 0; i < 17; i++) {
    INTinsertmytxtfile(vPots[i], (char*)"vPots");
  }

  for (int i = 0; i < 3; i++) {
    INTinsertmytxtfile(chorusVknobs[i], (char*)"chorusV");
    INTinsertmytxtfile(bqstage[i], (char*)"bqstage");
    INTinsertmytxtfile(LFOonfilterz[i], (char*)"LFOonfilterz");

    for (int j = 0; j < 2; j++) {
      INTinsertmytxtfile(reverbVknobs[i][j], (char*)"reverbV");
      INTinsertmytxtfile(bitcrusherVknobs[i][j], (char*)"bitcrusherV");
      INTinsertmytxtfile(granularVknobs[i][j], (char*)"granularV");
    }

    for (int j = 0; j < 3; j++) {
      INTinsertmytxtfile(mixffilterzVknobs[i][j], (char*)"mixffilterzV");
      INTinsertmytxtfile(ffilterzVknobs[i][j], (char*)"ffilterzV");
      INTinsertmytxtfile(flangerVknobs[i][j], (char*)"flangerV");
      INTinsertmytxtfile(delayVknobs[i][j], (char*)"delayV");
    }
    for (int j = 0; j < 4; j++) {
      INTinsertmytxtfile(bqtype[i][j], (char*)"bqtypeV");
      for (int k = 0; k < 3; k++) {
        INTinsertmytxtfile(bqVpot[i][j][k], (char*)"bqVpot");
      }
    }
  }
  Serial.println(" ");
  Serial.print("bqVpot[1][1][1] ");
  Serial.print(bqVpot[1][1][1]);
}

void INTinsertmytxtfile(int leint, char *leparam) {
  size_t param_length = strlen(leparam);
  if (param_length > 5 ) {
    leparam[6] = '\0';
  }
  //strncpy(truncated, leparam, 5);
  preset_file.print((char *)leparam);
  preset_file.print(" ");
  preset_file.print("#");
  preset_file.print(int(leint));
  preset_file.print("\n");
}

void FLOATinsertmytxtfile(float leint, char *leparam) {
  size_t param_length = strlen(leparam);
  if (param_length > 5 ) {
    leparam[6] = '\0';
  }
  preset_file.print((char *)leparam);
  preset_file.print(" ");
  preset_file.print("#");
  preset_file.print(float(leint));
  preset_file.print("\n");
}

void parsefile(int presetn) {
  int tmp_fx ;
  byte tmp_mixlevelsM[4];
  float tmp_mixlevelsL[synths_count];
  float tmp_WetMixMasters[4];
  preset_file = SD.open((char *)SynthPresetfullpath[presetn]);
  if (preset_file) {
    Serial.println(preset_file.name());
    // if already full, increse parsingbuffersize when much more settings are added + reduce total char usage
    for (int i = 0; i < parsingbuffersize; i++) {
      receivedbitinchar[i] = preset_file.read();
    }
  } else {
    Serial.print("Error with preset file");
    return ;
  }
  Parser parser((byte *)receivedbitinchar, parsinglength);

  parser.Read_String('#');
  parser.Skip(1);
  slope1 = (byte)parser.Read_Int16();
   Serial.println(" ");
    Serial.print("slope1 ");
    Serial.print(slope1);
  
  parser.Read_String('#');
  parser.Skip(1);
  slope2 = parser.Read_Int16();
  
  parser.Read_String('#');
  parser.Skip(1);
  millitickinterval = parser.Read_Int16();
 
  parser.Read_String('#');
  parser.Skip(1);
  cutoff_pulse = parser.Read_Int16();

  parser.Read_String('#');
  parser.Skip(1);
  reson_pulse = parser.Read_Int16();
   Serial.println(" ");
    Serial.print("reson_pulse ");
    Serial.print(reson_pulse);
  for (int i = 0; i < 3; i++) {
    parser.Read_String('#');
    parser.Skip(1);
    le303ffilterzVknobs[i] = parser.Read_Int16();

    parser.Read_String('#');
    parser.Skip(1);
    mixle303ffilterzVknobs[i] = parser.Read_Int16();

    parser.Read_String('#');
    parser.Skip(1);
    le303filterzgainz[i] = parser.Read_Float();
  }

  parser.Read_String('#');
  parser.Skip(1);
  le303filterzwet = parser.Read_Int16();

  parser.Read_String('#');
  parser.Skip(1);
  le303filterzrange = parser.Read_Int16();

  parser.Read_String('#');
  parser.Skip(1);
  le303filterzfreq = parser.Read_Float();

  parser.Read_String('#');
  parser.Skip(1);
  le303filterzreso = parser.Read_Float();
      
      Serial.println(" ");
    Serial.print("le303filterzreso ");
    Serial.print(le303filterzreso);

  parser.Read_String('#');
  parser.Skip(1);
  le303filterzoctv = parser.Read_Float();

  parser.Read_String('#');
  parser.Skip(1);
  glidemode = parser.Read_Int16();

  parser.Read_String('#');
  parser.Skip(1);
  preampleswaves = parser.Read_Int16();

  parser.Read_String('#');
  parser.Skip(1);
  arpegiatorOn = parser.Read_Int16() - 1;

  parser.Read_String('#');
  parser.Skip(1);
  arpegiatortype = parser.Read_Int16();

  parser.Read_String('#');
  parser.Skip(1);
  arpeglengh = parser.Read_Int16();

  parser.Read_String('#');
  parser.Skip(1);
  arpegmode = parser.Read_Int16();

  parser.Read_String('#');
  parser.Skip(1);
  arpegnumofnotes = parser.Read_Int16();

  parser.Read_String('#');
  parser.Skip(1);
  arpegstartoffset = parser.Read_Int16();

  parser.Read_String('#');
  parser.Skip(1);
  arpeggridC = parser.Read_Int16();

  parser.Read_String('#');
  parser.Skip(1);
  arpeggridS = parser.Read_Int16();

  parser.Read_String('#');
  parser.Skip(1);
  digitalplay = parser.Read_Int16();

  parser.Read_String('#');
  parser.Skip(1);
  chordson = parser.Read_Int16() - 1;

  parser.Read_String('#');
  parser.Skip(1);
  lasetchord = parser.Read_Int16();

  parser.Read_String('#');
  parser.Skip(1);
  wetins[0] = parser.Read_Int16();

  parser.Read_String('#');
  parser.Skip(1);
  wetins[1] = parser.Read_Int16();

  parser.Read_String('#');
  parser.Skip(1);
  wetins[2] = parser.Read_Int16();

  parser.Read_String('#');
  parser.Skip(1);
  synthmidichannel = parser.Read_Int16();

  parser.Read_String('#');
  parser.Skip(1);
  samplermidichannel = parser.Read_Int16();

  parser.Read_String('#');
  parser.Skip(1);
  tapnote = parser.Read_Int16();
  Serial.print("tapnote = ");
  Serial.println(tapnote);
  
  for (int i = 0; i < 16; i++) {
    parser.Read_String('#');
    parser.Skip(1);
    smixervknobs[i] = parser.Read_Int16();
  }

  for (int i = 0; i < 3; i++) {
    parser.Read_String('#');
    parser.Skip(1);
    tmp_fx = parser.Read_Int16();
    fx[i]->route_fx(tmp_fx);
    avoid_fx_bounce = false ;
    Serial.println("");
    Serial.print("Plugged in ");
    Serial.print((String)mainmenufxlist[fx[i]->plugged_fx_type]);
  }
  

  for (int i = 0; i < 4; i++) {
    parser.Read_String('#');
    parser.Skip(1);
    WetMixMasters[i] = parser.Read_Float();
    tmp_WetMixMasters[i] = WetMixMasters[i];
    Serial.println(" ");
    Serial.print("WetMixMasters ");
    Serial.print(WetMixMasters[i]);
    parser.Read_String('#');
    parser.Skip(1);
    mixlevelsM[i] = parser.Read_Int16();
    tmp_mixlevelsM[i] = mixlevelsM[i];
  }

  for (int i = 0; i < synths_count; i++) {
    parser.Read_String('#');
    parser.Skip(1);
    mixlevelsL[i] = parser.Read_Float();
    tmp_mixlevelsL[i] = mixlevelsL[i];

    parser.Read_String('#');
    parser.Skip(1);
    wavesfreqs[i] = parser.Read_Float();

    parser.Read_String('#');
    parser.Skip(1);
    panLs[i] = parser.Read_Float();

    parser.Read_String('#');
    parser.Skip(1);
    FMmodulated[i] = parser.Read_Int16();

    parser.Read_String('#');
    parser.Skip(1);
    Waveformstyped[i] = parser.Read_Int16();

    parser.Read_String('#');
    parser.Skip(1);
    wave1offset[i] = parser.Read_Int16();

    parser.Read_String('#');
    parser.Skip(1);
    phaselevelsL[i] = parser.Read_Int16();
    // Serial.println("panLs");
    // Serial.println(panLs[i]);
    parser.Read_String('#');
    parser.Skip(1);
    LFOlevel[i] = parser.Read_Int16();

    parser.Read_String('#');
    parser.Skip(1);
    LFOformstype[i] = parser.Read_Int16();

    parser.Read_String('#');
    parser.Skip(1);
    LFOfreqs[i] = parser.Read_Int16();

    parser.Read_String('#');
    parser.Skip(1);
    LFOphase[i] = parser.Read_Int16();

    parser.Read_String('#');
    parser.Skip(1);
    LFOoffset[i] = parser.Read_Int16();

    parser.Read_String('#');
    parser.Skip(1);
    LFOsync[i] = parser.Read_Int16() - 1;
  }
  
    for (int i = 0; i < 6; i++) {
      parser.Read_String('#');
      parser.Skip(1);
      adsrlevels[i] = parser.Read_Int16();
    }
    
  for (int i = 0; i < all_buttonns; i++) {
    parser.Read_String('#');
    parser.Skip(1);
    pot_assignements[i] = parser.Read_Int16();
    parser.Read_String('#');
    parser.Skip(1);
    but_channel[i] = parser.Read_Int16();
    parser.Read_String('#');
    parser.Skip(1);
    but_velocity[i] = parser.Read_Int16();
  }
  for (int i = 0; i < 15; i++) {
    parser.Read_String('#');
    parser.Skip(1);
    ordered_pots[i] = parser.Read_Int16();
    parser.Read_String('#');
    parser.Skip(1);
    muxed_channels[i] = parser.Read_Int16();
  }

  for (int i = 0; i < 128; i++) {

    parser.Read_String('#');
    parser.Skip(1);
    midiknobassigned[i] = parser.Read_Int16();
    
    parser.Read_String('#');
    parser.Skip(1);
    Sampleassigned[i] = parser.Read_Int16();
  }
  for (int i = 0; i < 17; i++) {
    parser.Read_String('#');
    parser.Skip(1);
    vPots[i] = parser.Read_Int16();
  }

  for (int i = 0; i < 3; i++) {
    parser.Read_String('#');
    parser.Skip(1);
    chorusVknobs[i] = parser.Read_Int16();

    parser.Read_String('#');
    parser.Skip(1);
    bqstage[i] = parser.Read_Int16();

    parser.Read_String('#');
    parser.Skip(1);
    LFOonfilterz[i] = parser.Read_Int16();

    for (int j = 0; j < 2; j++) {
      parser.Read_String('#');
      parser.Skip(1);
      reverbVknobs[i][j] = parser.Read_Int16();

      parser.Read_String('#');
      parser.Skip(1);
      bitcrusherVknobs[i][j] = parser.Read_Int16();

      parser.Read_String('#');
      parser.Skip(1);
      granularVknobs[i][j] = parser.Read_Int16();
    }

    for (int j = 0; j < 3; j++) {
      parser.Read_String('#');
      parser.Skip(1);
      mixffilterzVknobs[i][j] = parser.Read_Int16();

      parser.Read_String('#');
      parser.Skip(1);
      ffilterzVknobs[i][j] = parser.Read_Int16();

      parser.Read_String('#');
      parser.Skip(1);
      flangerVknobs[i][j] = parser.Read_Int16();

      parser.Read_String('#');
      parser.Skip(1);
      delayVknobs[i][j] = parser.Read_Int16();
    }
    for (int j = 0; j < 4; j++) {
      
      parser.Read_String('#');
      parser.Skip(1);
      bqtype[i][j] = parser.Read_Int16();

      for (int k = 0; k < 3; k++) {

        parser.Read_String('#');
        parser.Skip(1);
        bqVpot[i][j][k] = parser.Read_Int16();
      }
    }
  }

  parser.Reset();
  preset_file.close();
  // Serial.println("parsing done");
  setbpms();
  setlepulse1();
  setlepulse2();
  ApplyADSR();
  allfxcontrolled();
  // Serial.println("adsr done");
  le303filterzWet();
  Wavespreamp303controls();
  le303filtercontrols();
  set_dry_mix(0);
  set_dry_mix(1);

  for (int i = 0; i < synths_count; i++) {
    setwavemixlevel(i);
    setwavetypefromlist(i, Waveformstyped[i]);
    mixlevelsL[i] = tmp_mixlevelsL[i];
    setwavemixlevel(i);
  }
  for (int i = 0; i < 4; i++) {
    WetMixMasters[i] = tmp_WetMixMasters[i];
    mixlevelsM[i] = tmp_mixlevelsM[i];
    //setmastersmixlevel ignores 4th iteration (3)
    setmastersmixlevel(i);
  }
  wetmixmastercontrols();
}

void readpreset() { parsefile(sublevels[2]); }

void copypreset() {
  File originefile;
  if (SD.exists((char *)SynthPresetfullpath[sublevels[2]])) {
    mytxtFile = SD.open(get_new_file_name("PRESETS/SYNTH/SYNSET").c_str(), FILE_WRITE);
    originefile = SD.open((char *)SynthPresetfullpath[sublevels[2]], FILE_READ);
    size_t n;
    uint8_t buf[64];
    while ((n = originefile.read(buf, sizeof(buf))) > 0) {
      preset_file.write(buf, n);
    }
  }

  originefile.close();
  preset_file.close();
  dopresetlist();
}

void deletepreset() {
  if (SD.exists((char *)SynthPresetfullpath[sublevels[2]])) {
    SD.remove((char *)SynthPresetfullpath[sublevels[2]]);
  }
  dopresetlist();
}
