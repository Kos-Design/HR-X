

String get_preset_name(byte number) {
  char formatted_number[4] ;
  sprintf(formatted_number,"%02d",number);
  return "SYNSET" + (String)formatted_number ;
} 

String get_current_preset_path(){
  return "PRESETS/SYNTH/" + presets_names[0] + ".TXT";
}

void refresh_presets_names() {
  for (int i = 0 ; i < pst_size ; i++) {
    //empty spots are left at the end of the list if it is small, otherwise the names are looped
    presets_names[i] = " ";
    if (presets_names_offset+i < presets_count ) {
      presets_names[i] = get_preset_name(presets_indexes[presets_names_offset+i]);
    } else if (presets_count >= pst_size ){ 
      presets_names[i] = get_preset_name(presets_indexes[((presets_names_offset+i)%presets_count)]); 
    } 
  }
}
          
void list_presets_files() {
  presets_count = 0;
  String presets_dir = "PRESETS/SYNTH/";
  if (SD.exists(presets_dir.c_str())) {
    File preset_filer = SD.open(presets_dir.c_str());
    while (presets_count < 99) {
      File entry = preset_filer.openNextFile();
      if (!entry) {
        break;
      }
      if (!entry.isDirectory()) {
        char* named = (char*)entry.name();
        named[strlen(named) - 4] = '\0';
        //int is at 6 chars after prefix
        presets_indexes[presets_count] = atoi(named+6);
        Serial.println(presets_indexes[presets_count]);
        presets_count++;
      }
      entry.close();
    }
    preset_filer.close();
  }
}

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
      navrange = max(presets_count - 1, 0);
    }
  }
  draw_presets_list();
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

      parsefile();
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
  for (int i = 0; i < truesizeofpresetmenulabels - 1 - (sublevels[1]); i++) {
    canvasBIG.setCursor(startx, starty + ((i)*10));
    canvasBIG.println(presetmenulabels[sublevels[1] + 1 + i]);
  }
  for (int i = 0; i < sublevels[1]; i++) {
    canvasBIG.setCursor(startx, (10 * (truesizeofpresetmenulabels - sublevels[1]) + 6 + i*10));
    canvasBIG.println(presetmenulabels[i]);
  }
}

void writepreset() {
  File preset_filer;
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
    preset_filer = SD.open(new_preset_name.c_str(), FILE_WRITE);

    Serial.println(new_preset_name);
    Serial.println(preset_filer.name());
  } else {
    if (SD.exists(get_current_preset_path().c_str())) {
      SD.remove(get_current_preset_path().c_str());
    }
    preset_filer = SD.open(get_current_preset_path().c_str(), FILE_WRITE);
  }
  if (preset_filer) {
    writesynthpreset(preset_filer);
    preset_filer.close();
  }
  preset_filer.close();
  list_presets_files();
}

void draw_presets_list() {
  int startx = 80;
  int starty = 16;
  presets_names_offset = sublevels[2];
  refresh_presets_names();
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(startx, 0);
  canvastitle.setTextSize(1);
  if (sublevels[2] == presets_count && sublevels[1] == 0) {
    canvastitle.print("New()");
  } else {
    canvastitle.print(presets_names[0]);
  }
  canvastitle.setTextSize(1);
  canvasBIG.setTextSize(1);
  canvasBIG.fillScreen(SSD1306_BLACK);
  if (sublevels[2] == presets_count) {
    for (int i = 0; i < pst_size-1; i++) {
      canvasBIG.setCursor(startx, (10 * (presets_count - sublevels[2])) + 16 + i*10);
      canvasBIG.println(presets_names[i]);
    }
  } else {
    for (int i = 0; i < pst_size - 1 ; i++) {
      canvasBIG.setCursor(startx, starty + i*10);
      canvasBIG.println(presets_names[1 + i]);
    }
  }
}

void setnavrange() {
  if (presets_count < 2) {
    navrange = 2;
    // Serial.println("SOMETHING IS WRONG");
  } else {
    navrange = max(presets_count - 1, 0);
  }
}

void writesynthpreset(File &preset_filer) {
  preset_filer.print("<Presets><Synth>\n");
  insert_int(preset_filer,slope1, (char*)"slope1"); 
  insert_int(preset_filer,slope2, (char*)"slope2");
  insert_int(preset_filer,millitickinterval, (char*)"milli");
  insert_int(preset_filer,cutoff_pulse, (char*)"pulse1");
  insert_int(preset_filer,reson_pulse, (char*)"pulse2");

  for (int i = 0; i < 3; i++) {
    insert_int(preset_filer,le303ffilterzVknobs[i], (char*)"f303vknobs");
    insert_int(preset_filer,mixle303ffilterzVknobs[i], (char*)"mixfilters303");
    insert_float(preset_filer,le303filterzgainz[i], (char*)"filtergainz303");
  }

  insert_int(preset_filer,le303filterzwet, (char*)"le303filterzwet");
  insert_int(preset_filer,le303filterzrange, (char*)"le303range");
  insert_float(preset_filer,le303filterzfreq, (char*)"le303freq");
  insert_float(preset_filer,le303filterzreso, (char*)"le303reso");
  
  insert_float(preset_filer,le303filterzoctv, (char*)"le303octv");
  insert_int(preset_filer,int(glidemode), (char*)"glidemode");
  insert_int(preset_filer,preampleswaves, (char*)"preampleswaves");
  insert_int(preset_filer,int(arpegiatorOn) + 1, (char*)"arpegiatorOn");
  insert_int(preset_filer,arpegiatortype, (char*)"arpegiatortype");
  insert_int(preset_filer,arpeglengh, (char*)"arpeglengh");
  insert_int(preset_filer,arpegmode, (char*)"arpegmode");
  insert_int(preset_filer,arpegnumofnotes, (char*)"arpegnumofnotes");
  insert_int(preset_filer,arpegstartoffset, (char*)"arpegstartoffset");
  insert_int(preset_filer,arpeggridC, (char*)"arpeggridC");
  insert_int(preset_filer,arpeggridS, (char*)"arpeggridS");
  insert_int(preset_filer,int(digitalplay) + 1, (char*)"digitalplay");
  insert_int(preset_filer,int(chordson) + 1, (char*)"chordsOn");
  insert_int(preset_filer,lasetchord, (char*)"lasetchord");
  insert_int(preset_filer,wetins[0], (char*)"wetsynth");
  insert_int(preset_filer,wetins[1], (char*)"wetsampler");
  insert_int(preset_filer,wetins[2], (char*)"wetother");
  insert_int(preset_filer,synthmidichannel, (char*)"synthmidichannel");
  insert_int(preset_filer,samplermidichannel, (char*)"samplermidichannel");
  insert_int(preset_filer,tapnote, (char*)"tapnote");

  for (int i = 0; i < 16; i++) {
    insert_int(preset_filer,smixervknobs[i], (char*)"smixer");
  }

  for (int i = 0; i < 3; i++) {
    insert_int(preset_filer,fx[i]->plugged_fx_type, (char*)"effect");
  }
  for (int i = 0; i < 4; i++) {
    insert_float(preset_filer,WetMixMasters[i], (char*)"wetmixes");
    Serial.println(" ");
    Serial.print("WetMixMasters ");
    Serial.print(WetMixMasters[i]);
    insert_int(preset_filer,mixlevelsM[i], (char*)"mixlevelsM");
  }
  for (int i = 0; i < synths_count; i++) {
    //TODO:wetmix & mixers out of synths_count loop ,still iter to 4
    insert_float(preset_filer,mixlevelsL[i], (char*)"mixlevelsL");
    insert_float(preset_filer,wavesfreqs[i], (char*)"wavefreq");
    insert_float(preset_filer,panLs[i], (char*)"panL");
    insert_int(preset_filer,FMmodulated[i], (char*)"modu");
    insert_int(preset_filer,Waveformstyped[i], (char*)"Waveform");
    insert_int(preset_filer,wave1offset[i], (char*)"offset");
    insert_float(preset_filer,phaselevelsL[i], (char*)"phaselL");
    insert_int(preset_filer,LFOlevel[i], (char*)"lfolevel");
    insert_int(preset_filer,LFOformstype[i], (char*)"lfoType");
    insert_int(preset_filer,LFOfreqs[i], (char*)"lfofreqs");
    insert_int(preset_filer,LFOphase[i], (char*)"lfoPhase");
    insert_int(preset_filer,LFOoffset[i], (char*)"lfoOffset");
    insert_int(preset_filer,LFOsync[i] + 1, (char*)"lfosync");
  }
  
    for (int j = 0; j < 6; j++) {
      insert_int(preset_filer,adsrlevels[j], (char*)"adsr");
    }
  

  for (int i = 0; i < all_buttonns; i++) {
    insert_int(preset_filer,pot_assignements[i], (char*)"pot_assigned");
    insert_int(preset_filer,but_channel[i], (char*)"but_channel");
    insert_int(preset_filer,but_velocity[i], (char*)"but_velocity");
  }
  for (int i = 0; i < 15; i++) {
    insert_int(preset_filer,ordered_pots[i], (char*)"muxed_pots");
    insert_int(preset_filer,muxed_channels[i], (char*)"muxed_channels");
  }
  for (int i = 0; i < 128; i++) {
    insert_int(preset_filer,midiknobassigned[i], (char*)"Midiknobassigned");
    insert_int(preset_filer,Sampleassigned[i], (char*)"Sampleassigned");
  }
  for (int i = 0; i < 17; i++) {
    insert_int(preset_filer,vPots[i], (char*)"vPots");
  }

  for (int i = 0; i < 3; i++) {
    insert_int(preset_filer,chorusVknobs[i], (char*)"chorusV");
    insert_int(preset_filer,bqstage[i], (char*)"bqstage");
    insert_int(preset_filer,LFOonfilterz[i], (char*)"LFOonfilterz");

    for (int j = 0; j < 2; j++) {
      insert_int(preset_filer,reverbVknobs[i][j], (char*)"reverbV");
      insert_int(preset_filer,bitcrusherVknobs[i][j], (char*)"bitcrusherV");
      insert_int(preset_filer,granularVknobs[i][j], (char*)"granularV");
    }

    for (int j = 0; j < 3; j++) {
      insert_int(preset_filer,mixffilterzVknobs[i][j], (char*)"mixffilterzV");
      insert_int(preset_filer,ffilterzVknobs[i][j], (char*)"ffilterzV");
      insert_int(preset_filer,flangerVknobs[i][j], (char*)"flangerV");
      insert_int(preset_filer,delayVknobs[i][j], (char*)"delayV");
    }
    for (int j = 0; j < 4; j++) {
      insert_int(preset_filer,bqtype[i][j], (char*)"bqtypeV");
      for (int k = 0; k < 3; k++) {
        insert_int(preset_filer,bqVpot[i][j][k], (char*)"bqVpot");
      }
    }
  }
  Serial.println(" ");
  Serial.print("bqVpot[1][1][1] ");
  Serial.print(bqVpot[1][1][1]);
}

void insert_int(File &preset_filer, int leint, char *leparam) {
  size_t param_length = strlen(leparam);
  if (param_length > 5 ) {
    leparam[6] = '\0';
  }
  //strncpy(truncated, leparam, 5);
  preset_filer.print((char *)leparam);
  preset_filer.print(" ");
  preset_filer.print("#");
  preset_filer.print(int(leint));
  preset_filer.print("\n");
}

void insert_float(File &preset_filer,float leint, char *leparam) {
  size_t param_length = strlen(leparam);
  if (param_length > 5 ) {
    leparam[6] = '\0';
  }
  preset_filer.print((char *)leparam);
  preset_filer.print(" ");
  preset_filer.print("#");
  preset_filer.print(float(leint));
  preset_filer.print("\n");
}

void parsefile() {
  
  int tmp_fx ;
  byte tmp_mixlevelsM[4];
  float tmp_mixlevelsL[synths_count];
  float tmp_WetMixMasters[4];
  File preset_filer = SD.open(get_current_preset_path().c_str());
  if (preset_filer) {
    Serial.println(preset_filer.name());
    // if already full, increse parsingbuffersize when much more settings are added + reduce total char usage
    for (int i = 0; i < parsingbuffersize; i++) {
      receivedbitinchar[i] = preset_filer.read();
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
  }
  

  for (int i = 0; i < 4; i++) {
    parser.Read_String('#');
    parser.Skip(1);
    WetMixMasters[i] = parser.Read_Float();
    tmp_WetMixMasters[i] = WetMixMasters[i];
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
  preset_filer.close();
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

void copypreset() {
  File origin_file;
  File target_file;
  if (SD.exists(get_current_preset_path().c_str())) {
    target_file = SD.open(get_new_file_name("PRESETS/SYNTH/SYNSET").c_str(), FILE_WRITE);
    origin_file = SD.open(get_current_preset_path().c_str(), FILE_READ);
    size_t n;
    uint8_t buf[64];
    while ((n = origin_file.read(buf, sizeof(buf))) > 0) {
      target_file.write(buf, n);
    }
  }

  origin_file.close();
  target_file.close();
  list_presets_files();
}

void deletepreset() {
  if (SD.exists(get_current_preset_path().c_str())) {
    SD.remove(get_current_preset_path().c_str());
  }
  list_presets_files();
}
