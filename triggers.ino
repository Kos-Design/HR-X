

short getNewavailableliner() {

  for (int i = 0; i < nombreofliners; i++) {
    if (notesOn[i] == 0) {
      // stoplengthmesure(i);
      // Serial.println("note available");
      if (patrecord) {
        if (i + offsetliner < nombreofliners) {
          // Serial.print("playing lineroffset");
          // Serial.println(offsetliner);
          return i + offsetliner;
        }
      } else {
        return i;
      }
    }
  }
  //  Serial.println("no notes free");
  return nombreofliners;
}
bool linerhasevents(byte liner) {
  for (int i = 0; i < pbars; i++) {
    if (synth_partition[liner][i][1] != 0) {
      // Serial.println(offsetliner);
      return 1;
    }
  }
  return 0;
}
void getlinerwithoutevents() {
  offsetliner = 0;
  for (int i = 0; i < nombreofliners; i++) {
    if (linerhasevents(i)) {
      offsetliner = i + 1;
    } else {
      return;
    }
    // stoplengthmesure(i);
    // Serial.println("note available");
  }
}

// return nombreofliners;
void setfreqWavelines(float tune, int liner, byte velocityz) {
  // AudioNoInterrupts();

//TODO adsrlevels correspondance
  for (int i = 0; i < 4; i++) {

    waveforms1[liner + (i * 8)]->amplitude(velocityz / 128.0);
    waveforms1[liner + (i * 8)]->frequency(tune * wavesfreqs[i]);
    waveforms1[liner + (i * 8)]->offset(
        (float)(((64.0 - wave1offset[i]) / 64.0)));
    waveforms1[liner + (i * 8)]->phase(phaselevelsL[i]);
    FMwaveforms1[liner + (i * 8)]->frequency(tune * wavesfreqs[i]);
    FMwaveforms1[liner + (i * 8)]->amplitude(velocityz / 128.0);
    FMwaveforms1[liner + (i * 8)]->offset(
        (float)(((64.0 - wave1offset[i]) / 64.0)));
    drums1[liner + (i * 8)]->length(adsrlevels[1] + adsrlevels[2] +
                                    adsrlevels[3]);
    drums1[liner + (i * 8)]->frequency(tune * wavesfreqs[i]);
    drums1[liner + (i * 8)]->noteOn();
    strings1[liner + (i * 8)]->noteOn(tune * wavesfreqs[i],
                                      (velocityz / 128.0));
  }
}

void setchordnotes(byte absolutenote, byte lachord) {

  byte relativenote = ((absolutenote + 12) % 12);

  for (int i = 0; i < 3; i++) {
    chordnotes[i] = leschords[lachord][relativenote][i];
  }
}

void setchordnotesOff(byte absolutenote, byte lachord) {

  byte relativenote = ((absolutenote + 12) % 12);

  for (int i = 0; i < 3; i++) {
    chordnotesoff[i] = leschords[lachord][relativenote][i];
  }
}

byte getNewavailablesampler() {

  for (int i = 0; i < 16; i++) {
    if (!FlashSampler[i]->isPlaying()) {
      // stoplengthmesure(i);
      // Serial.println("note available");
      return i;
    }
  }
  //  Serial.println("no notes free");
  FlashSampler1.stop();

  return 0;
}
void initiatesamplerline(byte lesampleliner, byte channel, byte data1,
                         byte data2) {
  // float veloc = (int)(data2);
  // printnoteon(channel, data1, data2);
  const char *tobeplayed =
      (const char *)Flashsamplename[Sampleassigned[(int)(data1)]];
  if (FlashSampler[lesampleliner]->isPlaying()) {
    FlashSampler[lesampleliner]->stop();
  }

  if (!digitalplay) {
    // if ( lesampleliner < 4 ) {
    Flashmixer[int(lesampleliner / 4)]->gain(
        lesampleliner - 4 * int(lesampleliner / 4),
        (smixervknobs[lesampleliner] / 128.0) * (data2 / 128.0));

    //        Flashmixer[0]->gain(lesampleliner, data2/128.0);
    //      }
    //      if ( (lesampleliner > 3) && (i < 8)) {
    //        Flashmixer[1]->gain(lesampleliner-4, data2/128.0);
    //      }
    //       if ( (lesampleliner > 7) && (i < 12)) {
    //        Flashmixer[2]->gain(lesampleliner-8, data2/128.0);
    //      }
    //       if ( (lesampleliner > 11) && (i < 16)) {
    //        Flashmixer[3]->gain(lesampleliner-12, data2/128.0);
    //      }
  } else {
    Flashmixer[int(lesampleliner / 4)]->gain(
        lesampleliner - 4 * int(lesampleliner / 4),
        (smixervknobs[lesampleliner] / 128.0));
  }

  FlashSampler[lesampleliner]->play(tobeplayed);
}

void playFlashsample(byte channel, byte data1, byte data2) {

  // Serial.print("vel = ");
  // Serial.print(mixergain);
  byte lesampleliner = getNewavailablesampler();
  if (patrecord) {
    recordmidinotes2(lesampleliner, channel, data1, data2);
  }

  initiatesamplerline(lesampleliner, samplermidichannel, data1, data2);
  // if no liners are available stoping player 1 to make room
}

void printnoteon(byte channel, byte data1, byte data2) {
  Serial.print("Note On, ch=");
  Serial.print(channel);
  //  Serial.print(", liner=");
  // Serial.print(availablliner);
  Serial.print(", note=");
  Serial.print(data1);
  Serial.print(", velocity=");
  Serial.println(data2);
}
void MaNoteOn(byte channel, byte data1, byte data2) {
  byte larpegeline;
  int lachordon;
  uint8_t statusByte = static_cast<uint8_t>(0x90 | channel);
  if (data1 == tapnote) {
    taptap();
    return;
  }

  if (debugmidion) {
    debugmidi((char *)"NoteOn", (int)(channel), (int)(data1), (int)(data2));
  }

  // printnoteon(channel, data1, data2);

  if ((channel == synthmidichannel) or (synthmidichannel == -1)) {
    if (!arpegiatorOn) {
      if (!chordson) {
        initiateasynthliner(data1, data2);
      } else {
        // if chords
        setchordnotes(data1, lasetchord);
        for (int i = 0; i < 3; i++) {
          lachordon = chordnotes[i] + ((int(data1 / 12)) * 12);
          initiateasynthliner(lachordon, data2);
        }
      }
    } else {
      larpegeline = incrementarpegiatingNote(data1);
      if (larpegeline < nombreofliners) {
        stoptick = 0;
        // arpegiatethis();
        // initialize arpeg
         //metro0.reset();
        arpegiatethis(data1, data2, larpegeline);
      }
    }
    // arpegiator On

    // enable ticker during notepress
    // if at least one ticker is on keep tick
    // start arpeges based on that note
    // keep track and/or a way to noteoff
  }

  if (Sampleassigned[(int)(data1)] != 0 &&
      ((channel == (byte)samplermidichannel) or (samplermidichannel == -1))) {
    // Serial.println("Sampler On ");
    playFlashsample((byte)samplermidichannel, data1, data2);
  }
  if (SendMidiOut) {
    // TODO: send midi during sound trigger to use arpegiators (+ note offs if
    // arpegiator doesn't already send Off notes ?)
    Serial.println("sending Note On");
    MidiUSB.sendMIDI({0x09, statusByte, data1, data2});
    MidiUSB.flush();
  }
}
void allarpegeoffs() {
  for (int i = 0; i < nombreofliners; i++) {
    calledarpegenote[i][0] = 0;
    calledarpegenote[i][1] = 0;
    for (int j = 0; j < nombreofliners; j++) {
      playingarpegiator[i][j] = 0;
      arpegnoteoffin[i][j] = 0;
    }
    arpegiatingNote[i] = 0;
  }
  stopallnotes();
}
byte incrementarpegiatingNote(byte lanote) {
  for (int i = 0; i < nombreofliners; i++) {
    if (arpegiatingNote[i] == 0) {
      arpegiatingNote[i] = lanote;
      return i;
    }
  }
  return nombreofliners;
}

bool decrementarpegiatingNote() {
  for (int i = 0; i < nombreofliners; i++) {
    if (arpegiatingNote[i] != 0) {
      arpegiatingNote[i] = 0;
      return 1;
    }
  }
  return 0;
}

void initiatearpegesynthliner(byte larpegeline, byte data1, byte data2) {
  Serial.print("arpegeline : ");
  Serial.println(larpegeline);

  availablliner = getNewavailableliner();

  if (availablliner < nombreofliners) {

    for (int i = 0; i < nombreofliners; i++) {
      if (data1 == calledarpegenote[i][0]) {
        arpegnoteoffin[i][availablliner] = arpeglengh + 1;
        playingarpegiator[i][availablliner] = data1;
      }
    }

    // for (int i = 0 ; i < nombreofliners ; i++) {
    // if (data1 == calledarpegenote[i][0] ) {
    arpegnoteoffin[larpegeline][availablliner] = arpeglengh + 1;
    playingarpegiator[larpegeline][availablliner] = data1;
    // }
    // }

    // TODO check above for note leakage from other arpegio lines

    // lineroff(availablliner,(byte)synthmidichannel, data1, data2);
    // AudioNoInterrupts();
    if (patrecord) {
      recordmidinotes(availablliner, synthmidichannel, data1, data2);
    }
    // Serial.print("LinerOn ");
    // Serial.println(availablliner);

    lineron(availablliner, synthmidichannel, data1, data2);
    // AudioInterrupts();
  } else {
    // Serial.print("No Liner not on ");
  }
}

void initiateasynthliner(byte data1, byte data2) {
  availablliner = getNewavailableliner();

  if (availablliner < nombreofliners) {

    // TODO check above for note leakage from other arpegio lines

    // lineroff(availablliner,(byte)synthmidichannel, data1, data2);
    // AudioNoInterrupts();
    if (patrecord) {

      recordmidinotes(availablliner, synthmidichannel, data1, data2);
    }
    // Serial.print("LinerOn ");
    // Serial.println(availablliner);
    lineron(availablliner, synthmidichannel, data1, data2);
    // AudioInterrupts();
  } else {
    // Serial.print("No Liner not on ");
  }
}

void MaProgramchange(byte channel, byte data1) {
  if (debugmidion) {
    debugmidi((char *)"ProgramChange", (int)(channel), (int)(data1));
  }
  int leprogchanged = (int)(data1);
  // if (SD.exists((char*)SynthPresetfullpath[(int)( data1)]) ) {
  if (leprogchanged < numberofSynthPresets) {
    parsefile(leprogchanged);
  }
}
byte checkiflinerhasthatnoteOn(byte data1) {
  // int lechannel = (int)( channel) ;
  // int lenote = (int)( data1) ;
  for (int i = 0; i < nombreofliners; i++) {
    if (data1 == notesOn[i]) {
      // Serial.print("found note active on liner: ");
      // Serial.println(i);
      return (byte)i;
    }
  }
  // Serial.println("no matching notes currently On");
  return nombreofliners;
}
void shutlineroff(byte data1) {
  byte lalinetoOff;
  lalinetoOff = checkiflinerhasthatnoteOn(data1);
  if ((lalinetoOff < nombreofliners)) {
    if (patrecord) {
      // Serial.println("liner off on patrecord ");
      recordmidinotesOff(lalinetoOff, synthmidichannel, data1, 0);

      // recompute lenghtof notes
    }
    lineroff(lalinetoOff, data1);
  }
}

void decrementgamme(byte larpegeline) {

  if (tickgamme[larpegeline] > (int)(arpegstartoffset / 6)) {
    tickgamme[larpegeline]--;
  } else {
    tickgamme[larpegeline] = arpegnumofnotes - 1;
  }
}
void randomdirtest(byte larpegeline) {

  byte lerandom = (byte)random(0, 101);
  // Serial.println(lerandom);
  if (lerandom > 50) {

    tripletdirection[larpegeline] = !tripletdirection[larpegeline];
    // ticklagamme(larpegeline);
  }
  if (arpegmode == 4) {
    randomgammedirtest(larpegeline);
  }
}
void randomgammedirtest(byte larpegeline) {

  byte lerandom = (byte)random(0, 101);
  // Serial.println(lerandom);
  if (lerandom > 50) {

    decrementgamme(larpegeline);
  } else {
    ticklagamme(larpegeline);
  }
}

void tickarpegedown(byte larpegeline) {
  // Serial.println(ticktriplet[larpegeline]);
  // if (ticktriplet[larpegeline] == 2 && arpegmode == 2 || arpegmode == 3 ){
  // randomdirtest(larpegeline);
  //}
  if (ticktriplet[larpegeline] > 0) {
    ticktriplet[larpegeline]--;
  } else {

    ticktriplet[larpegeline] = 2;

    if (arpegmode == 1 || arpegmode == 5 || arpegmode == 4) {
      decrementgamme(larpegeline);
    }
    if (arpegmode == 3) {
      ticklagamme(larpegeline);
      tripletdirection[larpegeline] = 1;
      ticktriplet[larpegeline] = 0;
    }
    if (arpegmode == 2) {
      tripletdirection[larpegeline] = 1;
      ticktriplet[larpegeline] = 0;
    }
    if (arpegmode == 5) {
      tripletdirection[larpegeline] = 1;
      ticktriplet[larpegeline] = 0;
    }
    if (arpegmode == 6) {
      tripletdirection[larpegeline] = 1;
      ticktriplet[larpegeline] = 0;
    }
    if (arpegmode == 4) {
      randomdirtest(larpegeline);
      // randomgammedirtest(larpegeline);
    }
    if (arpegmode == 7) {
      randomdirtest(larpegeline);
      randomgammedirtest(larpegeline);
    }
  }
}

void tickarpege(byte larpegeline) {
  // Serial.println(ticktriplet[larpegeline]);

  ticktriplet[larpegeline]++;

  if (ticktriplet[larpegeline] > 2) {
    ticktriplet[larpegeline] = 0;
    if (arpegmode == 0 || arpegmode == 2 || arpegmode == 3 || arpegmode == 4) {
      ticklagamme(larpegeline);
    }
    if (arpegmode == 3) {
      tripletdirection[larpegeline] = 0;

      ticktriplet[larpegeline] = 2;
    }
    if (arpegmode == 2) {
      tripletdirection[larpegeline] = 0;

      ticktriplet[larpegeline] = 2;
    }
    if (arpegmode == 5) {
      tripletdirection[larpegeline] = 0;

      ticktriplet[larpegeline] = 2;
    }
    if (arpegmode == 6) {
      tripletdirection[larpegeline] = 0;

      ticktriplet[larpegeline] = 2;
      decrementgamme(larpegeline);
    }
    if (arpegmode == 4) {
      randomdirtest(larpegeline);
      //
    }
    if (arpegmode == 7) {
      randomdirtest(larpegeline);
      randomgammedirtest(larpegeline);
    }
  }
}

void arpegiatethis(byte data1, byte data2, byte larpegeline) {
  // for (int i = 0 ; i < nombreofliners ; i++ ) {
  // if (arpegiatingNote[larpegeline] == data1 ) {
  // for (int i = 0 ; i < nombreofliners ; i++ ) {
  calledarpegenote[larpegeline][1] = data2;
  calledarpegenote[larpegeline][0] = 0;
  // }
  if (arpegstartoffset > 0) {
    tickgamme[larpegeline] = (byte)((int)(arpegstartoffset / 3.0));
    ticktriplet[larpegeline] = (byte)((int)(arpegstartoffset % 3));
  } else {
    tickgamme[larpegeline] = 0;
    ticktriplet[larpegeline] = 0;
  }
  arpegemptyticks[larpegeline] = arpeggridS;
  arpegnotestick[larpegeline] = 0;

  // if (arpegstartoffset) {
  //  for (int i = 0 ; i < arpegstartoffset ; i++ ) {
  //  tickarpege(larpegeline) ;
  //  }
  // }
  if (arpegmode == 1 || arpegmode == 5 || arpegmode == 6) {
    tickgamme[larpegeline] = 6;
  }

  if (arpegmode == 0 || arpegmode == 3 || arpegmode == 5) {
    ticktriplet[larpegeline] = 0;
  }
  if (arpegmode == 1 || arpegmode == 2 || arpegmode == 6) {
    tripletdirection[larpegeline] = 0;
    ticktriplet[larpegeline] = 2;
  }

  // printarparams();
}
// modes 0 up , 1 down, 2 up-down , 3 down-up, 4 random
void arpegioticker(byte larpegeline) {
  switch ((int)tripletdirection[larpegeline]) {
  case 0:
    // up
    tickarpegedown(larpegeline);
    break;
  case 1:
    // down
    tickarpege(larpegeline);
    break;

  default:
    // Serial.println("broke ticker");
    break;
  }
}

void ticklatriplet(byte larpegeline) {
  // Serial.println(ticktriplet[larpegeline]);
  ticktriplet[larpegeline]++;
  if (ticktriplet[larpegeline] > 2) {
    ticktriplet[larpegeline] = 0;
    ticklagamme(larpegeline);
  }
}

void ticklagamme(byte larpegeline) {

  // Serial.println(ticktriplet[larpegeline]);
  if (arpegmode == 4) {
    randomdirtest(larpegeline);
  }
  tickgamme[larpegeline]++;
  if (tickgamme[larpegeline] > arpegnumofnotes - 1) {

    tickgamme[larpegeline] = int(arpegstartoffset / 6);
  }
  // if (arpegmode == 2 || arpegmode == 3 ){
  // randomdirtest(larpegeline);
  // }
}

void incrementcs(byte larpegeline) {
  if (arpegnotestick[larpegeline] < arpeggridC) {
    arpegnotestick[larpegeline]++;
  } else {
    arpegemptyticks[larpegeline] = arpeggridS;
    arpegnotestick[larpegeline] = 0;
  }
}

void decrementcrementns(byte larpegeline) {

  if (arpegemptyticks[larpegeline] > 0) {
    arpegemptyticks[larpegeline]--;
  }
}

void playarpegenote(byte larpegeline) {

  if (arpegemptyticks[larpegeline] > 0) {
    decrementcrementns(larpegeline);
    return;
  }
  incrementcs(larpegeline);
  byte relativenote;
  byte realnotetoplay;

  relativenote = all_arpegios[arpegiatortype][tickgamme[larpegeline]]
                             [ticktriplet[larpegeline]];
  // realnotetoplay = (byte)(octave*12 + relativenote) ;
  realnotetoplay = (byte)(arpegiatingNote[larpegeline] + relativenote);
  // Serial.print(realnotetoplay);
  if (arpegmode == 4) {
    arpegioticker(larpegeline);
  }

  //}
  calledarpegenote[larpegeline][0] = realnotetoplay;
  // printarparams();
  // playingarpegiator[larpegeline][0] = realnotetoplay ;
  initiatearpegesynthliner(larpegeline, realnotetoplay,
                           calledarpegenote[larpegeline][1]);
  // initiateasynthliner(realnotetoplay, calledarpegenote[larpegeline][1] );
  if (arpegmode != 4) {
    arpegioticker(larpegeline);
  }
}

void MaNoteOff(byte channel, byte data1, byte data2) {
  uint8_t statusByte = static_cast<uint8_t>(0x80 | channel);
  int lachordnote;
  // if (debugmidion) {debugmidi("NoteOff",(int)( channel),(int)( data1),(int)(
  // data2));}
  Serial.print("Off, ch=");
  Serial.print(channel, DEC);
  Serial.print(", N=");
  Serial.println(data1, DEC);

  if (SendMidiOut) {
    Serial.println("sending Note Off");
    MidiUSB.sendMIDI({0x08, statusByte, data1, data2});
    MidiUSB.flush();
  }
  if (!arpegiatorOn) {
    if (!chordson) {
      shutlineroff(data1);
    } else {
      setchordnotesOff(data1, lasetchord);
      for (int i = 0; i < 3; i++) {
        lachordnote = chordnotesoff[i] + ((int(data1 / 12)) * 12);
        // Serial.print("chordnote=");
        // Serial.println(lachordnote, DEC);
        // working octave =
        shutlineroff(lachordnote);
      }
    }
  } else {
    // decrementarpegiatingNote();
    if (testarpege(data1)) {
      if (!retestarpege()) {
        stoptickernextcycle = 1;
      }
    }
  }
}

bool testarpege(byte lanote) {
  for (int i = 0; i < nombreofliners; i++) {
    if (arpegiatingNote[i] == lanote) {
      arpegiatingNote[i] = 0;
      return 1;
    }
  }
  return 0;
}

bool retestarpege() {
  for (int i = 0; i < nombreofliners; i++) {
    if (arpegiatingNote[i] != 0) {
      return 1;
    }
  }

  return 0;
}

bool isalreadysamenoteinpat(byte lenote) {
  for (int i = 0; i < nombreofliners; i++) {
    if (lenote == synth_partition[i][tickposition][1]) {
      return 1;
    }
  }
  return 0;
}
int tick_for_that(int tick){
  tick -= 1 ; 
  if (tick < 0 ){
    tick = 31 ;
  }
  return tick ;
}
void recordmidinotes(int liner, byte channel, byte lenote, byte velocity) {
  int pos = tick_for_that(tickposition);
  synth_start_tpos[liner] = pos;
  track_cells[0][tickposition] = 1;
  synth_partition[liner][pos][1] = lenote;
  synth_partition[liner][pos][2] = velocity;
  synth_partition[liner][pos][0] = channel;
  
}
bool isalreadysameoffinpat(byte lanotee, byte modeselect) {
  if (modeselect == 0) {
    for (int i = 0; i < nombreofliners; i++) {
      if (lanotee == synth_off_pat[i][tickposition + 1][1]) {
        return 1;
      }
    }
  }
  if (modeselect == 1) {
    for (int i = 0; i < nombreofliners; i++) {
      if (lanotee == synth_off_pat[i][0][1]) {
        return 1;
      }
    }
  }
  if (modeselect == 2) {
    for (int i = 0; i < nombreofliners; i++) {
      if (lanotee == synth_off_pat[i][tickposition][1]) {
        return 1;
      }
    }
  }
  return 0;
}
void recordmidinotesOff(int liner, byte channel, byte lenote, byte velocity) {
int pos = tick_for_that(tickposition);
  if (synth_start_tpos[liner] != pos) {
    synth_off_pat[liner][pos][1] = lenote;
    synth_off_pat[liner][pos][2] = 0;
    synth_off_pat[liner][pos][0] = channel;

  } else {
    if (pos == pbars - 1) {
      synth_off_pat[liner][0][1] = lenote;
      synth_off_pat[liner][0][2] = 0;
      synth_off_pat[liner][0][0] = channel;
    } else {
      synth_off_pat[liner][pos + 1][1] = lenote;
      synth_off_pat[liner][pos + 1][2] = 0;
      synth_off_pat[liner][pos + 1][0] = channel;
    }
  }

}

bool isalreadysameSamplerinpat(byte lenote,int tick) {

  for (int i = 0; i < nombreofSamplerliners; i++) {
    if (lenote == sampler_partition[i][tick][1]) {
      return 1;
    }
  }

  return 0;
}
void recordmidinotes2(int liner, byte channel, byte lenote, byte velocity) {
int pos = tick_for_that(tickposition);
  if (!isalreadysameSamplerinpat(lenote,pos)) {
    track_cells[1][pos] = 1;
    sampler_partition[liner][pos][1] = lenote;
    sampler_partition[liner][pos][2] = velocity;
    sampler_partition[liner][pos][0] = channel;
  }
  // startlengthmesure(liner);
}
void deactivatelesccsfrompos(int lapos, byte lanote) {
  for (int i = lapos + 1; i < pbars; i++) {
    cc_partition[int(lanote)][i] = 128;
  }
}
void recordCCmidinotes(byte channel, byte lanote, byte leccval) {
  int pos = tick_for_that(tickposition);
  for (int i = 0 ; i < 32 ; i++){
    if (recorded_ccs[i] == 0 || recorded_ccs[i] == lanote ) {
        recorded_ccs[i] = lanote ;
        pots_controllers[i][pos][0] = lanote;
        pots_controllers[i][pos][0] = leccval;
        break;
    }
  }
  
  cc_partition[lanote][pos] = leccval;


}

bool terminateorphanseventsOff(int linei, byte lanotef) {
  //---------------if no notes on are even matching remove event off

  for (int i = 0; i < pbars; i++) {
    if (synth_partition[linei][i][1] == lanotef) {
      Serial.print(synth_partition[linei][i][1]);
      Serial.print("=");
      Serial.print(lanotef);

      // at least someone is using it somewhere
      return 0;
    }
  }

  return 1;
}

bool testforaNoteOninbetween(int linei, int lapos0, int lapos2, byte lanotef) {

  for (int i = lapos0; i < lapos2; i++) {
    if (synth_partition[linei][i][1] == lanotef) {
      return 1;
    }
  }
  return 0;
}
int anothernOffisonafter(int linei, byte lanotee, int lapos) {
  // aoffresultarray[0] = 8 ;
  // aoffresultarray[1] = 32 ;

  for (int i = lapos; i < pbars - 1; i++) {
    if (synth_off_pat[linei][i + 1][1] == lanotee) {
      // 0 is liner
      // aoffresultarray[0] = linei ;
      // aoffresultarray[1] = i+1 ;
      //              Serial.print("another note off comes after ");
      //              Serial.println(lapos);
      //              Serial.print(" at pos ");
      //              Serial.print(i+1);
      return i + 1;
    }
  }

  return pbars;
}
void clearbouncedoffsafters(int linei, byte lanotef, int lapos) {
  int laposoftheNofafter = anothernOffisonafter(linei, lanotef, lapos);
  // howmany nofs before a non
  if ((laposoftheNofafter < pbars) && (laposoftheNofafter != 0)) {
    // Serial.println("check if a Non is next ");
    bool resultNoteOninbetween =
        testforaNoteOninbetween(linei, lapos, laposoftheNofafter, lanotef);
    if (resultNoteOninbetween) {

      if ((!checkifnonbefore(linei, lanotef, lapos)) && lapos != 0) {
        //   Serial.print(" terminating dupli off note ");
        clearsaniloop = 0;
        //   Serial.print((int)lanotef);
        //   Serial.print(" on liner ");
        //  Serial.print(linei);
        //   Serial.print(" position ");
        // Serial.println(lapos);
        // Serial.println((int)resultNoteOninbetween);
        // cleardoublon
        synth_off_pat[linei][lapos][0] = (byte)0;
        synth_off_pat[linei][lapos][1] = (byte)0;
      }
      if ((lapos == 0) && ((synth_off_pat[linei][pbars - 1][1] == lanotef) &&
                           synth_partition[linei][pbars - 1][1] != lanotef)) {
        // check before if no other On note if none found terminate that off
        //  Serial.print(" clearing the first off");
        clearsaniloop = 0;
        //  Serial.print((int)lanotef);
        //   Serial.print(" on liner ");
        //   Serial.print(linei);
        //    Serial.print(" position ");
        //   Serial.println(lapos);
        synth_off_pat[linei][0][0] = (byte)0;
        synth_off_pat[linei][0][1] = (byte)0;
      }
    }
    if (!resultNoteOninbetween) {

      //  Serial.print("clear dupli note off ");
      //  Serial.println((int)synth_off_pat[linei][laposoftheNofafter][1]);
      clearsaniloop = 0;
      //    Serial.print(" liner,pos = ");
      //  Serial.print(linei);
      //  Serial.print(" , ");
      //  Serial.print(laposoftheNofafter);
      //   Serial.print(" note On in between = ");
      //  Serial.println((int)resultNoteOninbetween);
      // cleardoublon
      synth_off_pat[linei][laposoftheNofafter][0] = (byte)0;
      synth_off_pat[linei][laposoftheNofafter][1] = (byte)0;
    }
  }
  // if no Nof are next check is done

  // check after if another off of the same note
  // check after if a Non of the same note

  // check before if another note on is on before this one pos
}
bool checkifnonbefore(int linei, byte lanotee, int lapos) {
  for (int i = lapos - 1; i >= 0; i--) {
    if (synth_partition[linei][i][1] == lanotee) {
      return 1;
    }
  }
  return 0;
}

void terminateOffz(int linei) {
  for (int i = 0; i < pbars; i++) {
    if (synth_off_pat[linei][i][1] != 0) {
      if (terminateorphanseventsOff(linei, synth_off_pat[linei][i][1])) {
        Serial.print("terminated orphan note ");
        Serial.print(synth_off_pat[linei][i][1]);
        clearsaniloop = 0;
        //  Serial.println((int)synth_off_pat[linei][i][1]);
        synth_off_pat[linei][i][0] = 0;
        synth_off_pat[linei][i][1] = 0;
      }
    }
  }
}
void clearlesnofbounces(int linei, int fromi) {
  for (int i = fromi; i < pbars; i++) {
    if (synth_off_pat[linei][i][1] != 0) {
      clearbouncedoffsafters(linei, synth_off_pat[linei][i][1], i);
      // not checking before as we are doing it from 0
    }
  }
}
void sanitizeoffline(int linei) {
  // int lelinechecked ;

  // int lelineroftheon ;
  terminateOffz(linei);

  clearlesnofbounces(linei, 0);

  // overlapcheckandshift()
  // fixes NoteOn-NoteOff overlap on same pattern position but the first
}

int getnextposofevent1Off(int linei, byte lanote, int fromi) {

  for (int i = fromi + 1; i < pbars; i++) {
    if (synth_off_pat[linei][i][1] == lanote) {
      return i;
    }
    // if (synth_partition[linei][i][1] == lanote ){
    //}
  }
  return (fromi + 1);
}

void tweakfreqlive(int liner, float tune) {
  AudioNoInterrupts();
  for (int j = 0; j < 4; j++) {
    waveforms1[liner + (j * 8)]->frequency(tune * wavesfreqs[j]);
    FMwaveforms1[liner + (j * 8)]->frequency(tune * wavesfreqs[j]);
    drums1[liner + (j * 8)]->frequency(tune * wavesfreqs[j]);
  }
  AudioInterrupts();
}

void stopglidenote(byte liner) {
  // during loop shift freq & restart freqs interpolating from last note during
  // glide duration hold+atck?
  dogliding[liner] = 0;

  Serial.println(" ");
  Serial.print("note before ");
  Serial.print(lapreviousnotew);

  lapreviousnotew += leglidenoteshift;
  Serial.print("note now ");
  Serial.println(lapreviousnotew);
}
void stopglidenoteChords(byte liner) {
  // during loop shift freq & restart freqs interpolating from last note during
  // glide duration hold+atck?
  dogliding[liner] = 0;

  lapreviousnotewCmode[liner] += leglidenoteshiftCmode[liner];
}
void startglidenote(byte liner, byte data1) {
  // during loop shift freq & restart freqs interpolating from last note during
  // glide duration hold+atck?
  dogliding[liner] = 1;
  leglidenoteshift = data1 - lapreviousnotew;
  Serial.println(leglidenoteshift);
  leglidershift = notestofreq[data1][1] - notestofreq[lapreviousnotew][1];
  leglideposition[liner] = 0;
 
}
void startglidenoteChords(byte liner, byte data1) {
  // during loop shift freq & restart freqs interpolating from last note during
  // glide duration hold+atck?
  dogliding[liner] = 1;
  leglidenoteshiftCmode[liner] = data1 - lapreviousnotewCmode[liner];
  // Serial.println(leglidenoteshift);
  leglidershiftCmode[liner] =
      notestofreq[data1][1] - notestofreq[lapreviousnotewCmode[liner]][1];
  leglideposition[liner] = 0;

}

void computelenghtmesureoffline() {
  for (int linei = 0; linei < nombreofliners; linei++) {
    for (int i = 0; i < pbars; i++) {
      if (synth_partition[linei][i][1] != 0) {

        int laposof =
            getnextposofevent1Off(linei, synth_partition[linei][i][1], i);

        if (laposof < pbars - 1) {
          length0pbars[linei][i] = (laposof - i) * 4;
          templength0pbars[linei][i] = (laposof - i) * 4;

        } else {
          // synth_off_pat[linei][0][0] = synth_partition[linei][i][0] ;
          // synth_off_pat[linei][0][1] = synth_partition[linei][i][1] ;
          length0pbars[linei][i] = (pbars - i) * 4;
          templength0pbars[linei][i] = (pbars - i) * 4;
        }
        length1notes1[linei][i] =
            round((length0pbars[linei][i] / 4.0) * millitickinterval);
      }
    }
  }
}
void closeallenvelopes() {

  for (int i = 0; i < nombreofliners; i++) {
    enveloppesL[i]->noteOff();
    enveloppesL[i]->hold(0);
    notesOn[i] = 0;
  }
}

// TODO adsr check
void lineron(int liner, byte channel, byte data1, byte data2) {

  if (notesOn[liner] == 0) {

    notesOn[liner] = data1;
    AudioNoInterrupts();
    // printlinearparams(availablliner);

    // lavelocity = (int)( velocity);

    if (!tb303[liner]) {
      le303start[liner] = millis();
      tb303[liner] = 1;
    }
    // Serial.print("tb303 set on ");
    // Serial.println(liner);

    enveloppesL[liner]->hold(millitickinterval - adsrlevels[3]);

    //      enveloppesR[liner]->hold(500);
    if (glidemode > 0) {
      //          if (!chordson) {
      //          notefrequency = notestofreq[lapreviousnotew][1];
      //            startglidenote(liner,data1);
      //            setfreqWavelines(notefrequency,liner,data2);
      //          } else {

      notefrequency = notestofreq[lapreviousnotewCmode[liner]][1];
      startglidenoteChords(liner, data1);
      setfreqWavelines(notefrequency, liner, data2);

      // }
    } else {

      notefrequency = notestofreq[data1][1];
      setfreqWavelines(notefrequency, liner, data2);
    }

    enveloppesL[liner]->noteOn();
    // lefadout[liner] = 1 ;
    // faders[liner]->gain(1);
    // faders[liner]->fadeOut(int((millitickinterval*(le303envlfofadintime/128.0))));
    // faders[liner]->fadeIn(adsrlevels[1]);
    // enveloppesR[liner]->noteOn();

    for (int i = 0; i < 4; i++) {
      doLFOallcontrols(i);
    }

    AudioInterrupts();
  }
}

void lineroff(int liner, byte data1) {
  // AudioNoInterrupts();
  if (enveloppesL[liner]->isActive()) {
    // Serial.println("has env active");
    enveloppesL[liner]->hold(0);
    //  for (int j = 0 ; j < 4 ; j++ ) {
    // strings1[i+(j*8)]->noteOff(0);
    // }
    enveloppesL[liner]->noteOff();
    if (tb303[liner]) {
      tb303[liner] = 0;
    }
    // faders[i]->fadeOut(adsrlevels[5]);
    notesOn[liner] = 0;
  }
}
void Mytickmidi() {
  // Serial.println("mclock");
  advance_tick();
}
void moncontrollercc(byte channel, byte control, byte value) {
  if (value < 128) {
    if (midiknobassigned[control] != 0 && !freezemidicc) {
      if (SendMidiOut) {
        Serial.println("sending CC");
        uint8_t statusByte = static_cast<uint8_t>(0xB0 | channel);
        MidiUSB.sendMIDI({0x0B, statusByte, control, value});

        MidiUSB.flush();
      }
      midiknobs[control] = value;
      //why do we convert 0 to 1024 to 1024 ?
      midiknobs[control] = round((midiknobs[control] / 127.0) * 1024.0);
      controlswitcher(midiknobassigned[control], midiknobs[control]);
      // AudioInterrupts();
    }
  }
}
void MaControlChange(byte channel, byte control, byte value) {
  bool isignored = noCCrecordlist(control);

  if (debugmidion) {
    debugmidi((char *)("ControlChange"), channel, control, value);
  }

  moncontrollercc(channel, control, value);

  // Serial.print("Control Change, ch=");
  // Serial.print(lechannel);
  if (stoptick) {

    Serial.print("CC=");
    Serial.print(control);
    Serial.print(" V=");
    Serial.println(value);
  }

  if ((patrecord || recordCC) && !stoptick && !isignored) {
    // Serial.println(int(recordCC));
    recordCCmidinotes(channel, control, value);
  }
  if (!songplaying && !isignored && !debugmidion) {
    lemenuroot();
  }
}

bool noCCrecordlist(byte lanotee) {
  for (byte i = 0; i < sizeofnoCCrecord; i++) {
    if (midiknobassigned[lanotee] == noCCrecord[i]) {
      return 1;
    }
  }
  return 0;
}

void scanfornextcc(byte lecc) {
  for (int i = tickposition + 1; i < pbars; i++) {
    if (cc_partition[lecc][i] != 128) {

      Ccinterpolengh[lecc][0] = tickposition;
      Ccinterpolengh[lecc][1] = i;
      Ccinterpolengh[lecc][2] = i - tickposition;
      activateinterpolatecc[lecc] = 1;
      return;
    }
  }

  for (int i = 0; i < tickposition; i++) {
    if (cc_partition[lecc][i] != 128) {

      Ccinterpolengh[lecc][0] = tickposition;
      Ccinterpolengh[lecc][1] = i;
      Ccinterpolengh[lecc][2] = i + pbars - tickposition;
      activateinterpolatecc[lecc] = 1;
      return;
    }
  }
  Ccinterpolengh[lecc][0] = pbars;
  Ccinterpolengh[lecc][1] = pbars;
  Ccinterpolengh[lecc][2] = 0;
  activateinterpolatecc[lecc] = 0;
}

void continueCCinterpol(byte lecc) {

  laCCduration = Ccinterpolengh[lecc][2] * millitickinterval;
  // if next cc is before pat revolution
  if ((Ccinterpolengh[lecc][1] - Ccinterpolengh[lecc][0]) > 0) {
    interpolcoeff =
        ((((tickposition - Ccinterpolengh[lecc][0]) * millitickinterval) +
          (millis() - tickerlasttick) + millitickinterval) /
         (laCCduration * 1.0));
    letempipolate =
        cc_partition[lecc][Ccinterpolengh[lecc][0]] +
        (interpolcoeff * (cc_partition[lecc][Ccinterpolengh[lecc][1]] -
                          cc_partition[lecc][Ccinterpolengh[lecc][0]]));
  }
  // if next cc is after pat revolution
  else {

    if (tickposition > Ccinterpolengh[lecc][0]) {

      interpolcoeff =
          ((((tickposition - Ccinterpolengh[lecc][0]) * millitickinterval) +
            (millis() - tickerlasttick)) /
           (laCCduration * 1.0));

      letempipolate = cc_partition[lecc][Ccinterpolengh[lecc][0]] +
                      (1.0 * interpolcoeff *
                       (cc_partition[lecc][Ccinterpolengh[lecc][1]] -
                        cc_partition[lecc][Ccinterpolengh[lecc][0]]));

      // leccinterpolated[i] = round(cc_partition[lecc][tickposition] +
      // (((millis() - tickerlasttick)/(laCCduration*1.0))*
      // (cc_partition[lecc][tickposition+1] -
      // cc_partition[lecc][tickposition] ))) ;
    } else {
      interpolcoeff = (((tickposition + pbars - Ccinterpolengh[lecc][0]) *
                        millitickinterval) +
                       (millis() - tickerlasttick)) /
                      (laCCduration * 1.0);

      letempipolate = cc_partition[lecc][Ccinterpolengh[lecc][0]] +
                      (1.0 * interpolcoeff *
                       (cc_partition[lecc][Ccinterpolengh[lecc][1]] -
                        cc_partition[lecc][Ccinterpolengh[lecc][0]]));
    }
  }
  if (tickposition == Ccinterpolengh[lecc][0]) {
    interpolcoeff = ((millis() - tickerlasttick) / (laCCduration * 1.0));
    letempipolate = cc_partition[lecc][tickposition] +
                    (1.0 * interpolcoeff *
                     (cc_partition[lecc][Ccinterpolengh[lecc][1]] -
                      cc_partition[lecc][tickposition]));
  }

  if (leccinterpolated[lecc] != letempipolate) {
    leccinterpolated[lecc] = letempipolate;
    moncontrollercc((byte)1, (byte)lecc, leccinterpolated[lecc]);
    //     Serial.print("Le CC");
    //     Serial.print(lecc);
    //     Serial.print(" = ");
    //     Serial.print(leccinterpolated[lecc]);
    //      Serial.print(" at pos ");
    //     Serial.println(tickposition);
    if (leccinterpolated[lecc] ==
        cc_partition[lecc][Ccinterpolengh[lecc][1]]) {
      activateinterpolatecc[lecc] = 0;
      Ccinterpolengh[lecc][0] = pbars;
      Ccinterpolengh[lecc][1] = pbars;
      Ccinterpolengh[lecc][2] = 0;
    }
  }
}


void checkall128cc() {

  for (int i = 0; i < 128; i++) {
    if (activateinterpolatecc[i]) {
      continueCCinterpol(i);
      // scanfornextcc(tickposition, i);
      // startleCCinterpolation(i);
    }
  }
}
