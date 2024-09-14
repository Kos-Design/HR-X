

void init_synth_liners(){
  for (int i = 0; i < liners_count; i++) {
    synth_lines[i] = new SynthLiner(i);
  }
}

byte get_free_liner(byte note) {
  for (byte i = 0; i < liners_count; i++) {
    if (!synth_lines[i]->activated) {
      if (patrecord) {
        //merge liner tracks after recording instead
        if (i + offsetliner < liners_count) {
          return i + offsetliner;
        }
      } else {
        return i;
      }
    }
  }
  return liners_count;
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
  for (int i = 0; i < liners_count; i++) {
    if (linerhasevents(i)) {
      offsetliner = i + 1;
    } else {
      return;
    }
    // stoplengthmesure(i);
    // Serial.println("note available");
  }
}

void setfreqWavelines(float tune, int liner, byte velocityz) {
  // AudioNoInterrupts();
  //TODO adsrlevels correspondance
  for (int i = 0; i < synths_count; i++) {
    waveforms1[liner + (i * liners_count)]->amplitude(velocityz / 127.0);
    waveforms1[liner + (i * liners_count)]->frequency(tune * wavesfreqs[i]);
    waveforms1[liner + (i * liners_count)]->offset((float)(((64.0 - wave1offset[i]) / 64.0)));
    waveforms1[liner + (i * liners_count)]->phase(phaselevelsL[i]);
    FMwaveforms1[liner + (i * liners_count)]->frequency(tune * wavesfreqs[i]);
    FMwaveforms1[liner + (i * liners_count)]->amplitude(velocityz / 127.0);
    FMwaveforms1[liner + (i * liners_count)]->offset((float)(((64.0 - wave1offset[i]) / 64.0)));
    drums1[liner + (i * liners_count)]->length(adsrlevels[1] + adsrlevels[2] + adsrlevels[3]);
    drums1[liner + (i * liners_count)]->frequency(tune * wavesfreqs[i]);
    drums1[liner + (i * liners_count)]->noteOn();
    strings1[liner + (i * liners_count)]->noteOn(tune * wavesfreqs[i],(velocityz / 127.0));
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

void initiatesamplerline(byte lesampleliner, byte channel, byte data1,  byte data2) {
  // float veloc = (int)(data2);
  // printnoteon(channel, data1, data2);
  const char *tobeplayed = (const char *)Flashsamplename[Sampleassigned[(int)(data1)]];
  if (FlashSampler[lesampleliner]->isPlaying()) {
    FlashSampler[lesampleliner]->stop();
  }
  if (!digitalplay) {
    // if ( lesampleliner < 4 ) {
    Flashmixer[int(lesampleliner / 4)]->gain(
        lesampleliner - 4 * int(lesampleliner / 4),
        (smixervknobs[lesampleliner] / 127.0) * (data2 / 127.0));
  } else {
    Flashmixer[int(lesampleliner / 4)]->gain(
        lesampleliner - 4 * int(lesampleliner / 4),
        (smixervknobs[lesampleliner] / 127.0));
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
      if (larpegeline < liners_count) {
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
    playFlashsample((byte)samplermidichannel, data1, data2);
  }
  if (SendMidiOut) {
    // TODO: send midi during sound trigger to use arpegiators (+ note offs if
    // arpegiator doesn't already send Off notes ?)
    MidiUSB.sendMIDI({0x09, statusByte, data1, data2});
    MidiUSB.flush();
  }
}
void allarpegeoffs() {
  for (int i = 0; i < liners_count; i++) {
    calledarpegenote[i][0] = 0;
    calledarpegenote[i][1] = 0;
    for (int j = 0; j < liners_count; j++) {
      playingarpegiator[i][j] = 0;
      arpegnoteoffin[i][j] = 0;
    }
    arpegiatingNote[i] = 0;
  }
  stopallnotes();
}

byte incrementarpegiatingNote(byte lanote) {
  for (int i = 0; i < liners_count; i++) {
    if (arpegiatingNote[i] == 0) {
      arpegiatingNote[i] = lanote;
      return i;
    }
  }
  return liners_count;
}

bool decrementarpegiatingNote() {
  for (int i = 0; i < liners_count; i++) {
    if (arpegiatingNote[i] != 0) {
      arpegiatingNote[i] = 0;
      return 1;
    }
  }
  return 0;
}

void initiatearpegesynthliner(byte larpegeline, byte data1, byte data2) {
  byte free_line = get_free_liner(data1);
  if (free_line < liners_count) {
    for (int i = 0; i < liners_count; i++) {
      if (data1 == calledarpegenote[i][0]) {
        arpegnoteoffin[i][free_line] = arpeglengh + 1;
        playingarpegiator[i][free_line] = data1;
      }
    }
    arpegnoteoffin[larpegeline][free_line] = arpeglengh + 1;
    playingarpegiator[larpegeline][free_line] = data1;
    if (patrecord) {
      recordmidinotes(free_line, synthmidichannel, data1, data2);
    }
    synth_lines[free_line]->liner_on(data1, data2);
  }
}

void initiateasynthliner(byte data1, byte data2) {
  byte free_line = get_free_liner(data1);
  if (free_line < liners_count) {
    if (patrecord) {
      recordmidinotes(free_line, synthmidichannel, data1, data2);
    }
    synth_lines[free_line]->liner_on(data1, data2);
  }
}

void MaProgramchange(byte channel, byte data1) {
  if (debugmidion) {
    debugmidi((char *)"ProgramChange", (int)(channel), (int)(data1));
  }
  int leprogchanged = (int)(data1);
  if (leprogchanged < presets_count) {
    Serial.print(" loading presets outside of menu is currently disabled");
    //parsefile(leprogchanged);
  }
}

byte is_using_note(byte data1) {
  for (int i = 0; i < liners_count; i++) {
    if (data1 == synth_lines[i]->note) {
      return (byte)i;
    }
  }
  return liners_count;
}

void shutlineroff(byte data1) {
  byte active_line = is_using_note(data1);
  if ((active_line < liners_count)) {
    if (patrecord) {
      recordmidinotesOff(active_line, synthmidichannel, data1, 0);
    }
    synth_lines[active_line]->liner_off();
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
  if (lerandom > 50) {

    decrementgamme(larpegeline);
  } else {
    ticklagamme(larpegeline);
  }
}

void tickarpegedown(byte larpegeline) {
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
  // for (int i = 0 ; i < liners_count ; i++ ) {
  // if (arpegiatingNote[larpegeline] == data1 ) {
  // for (int i = 0 ; i < liners_count ; i++ ) {
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
    break;
  }
}

void ticklatriplet(byte larpegeline) {
  ticktriplet[larpegeline]++;
  if (ticktriplet[larpegeline] > 2) {
    ticktriplet[larpegeline] = 0;
    ticklagamme(larpegeline);
  }
}

void ticklagamme(byte larpegeline) {
  if (arpegmode == 4) {
    randomdirtest(larpegeline);
  }
  tickgamme[larpegeline]++;
  if (tickgamme[larpegeline] > arpegnumofnotes - 1) {
    tickgamme[larpegeline] = int(arpegstartoffset / 6);
  }
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
  relativenote = all_arpegios[arpegiatortype][tickgamme[larpegeline]][ticktriplet[larpegeline]];
  // realnotetoplay = (byte)(octave*12 + relativenote) ;
  realnotetoplay = (byte)(arpegiatingNote[larpegeline] + relativenote);
  if (arpegmode == 4) {
    arpegioticker(larpegeline);
  }
  calledarpegenote[larpegeline][0] = realnotetoplay;
  initiatearpegesynthliner(larpegeline, realnotetoplay, calledarpegenote[larpegeline][1]);
  // initiateasynthliner(realnotetoplay, calledarpegenote[larpegeline][1] );
  if (arpegmode != 4) {
    arpegioticker(larpegeline);
  }
}

void MaNoteOff(byte channel, byte data1, byte data2) {
  uint8_t statusByte = static_cast<uint8_t>(0x80 | channel);
  int lachordnote;  
  if (SendMidiOut) {
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
  for (int i = 0; i < liners_count; i++) {
    if (arpegiatingNote[i] == lanote) {
      arpegiatingNote[i] = 0;
      return 1;
    }
  }
  return 0;
}

bool retestarpege() {
  for (int i = 0; i < liners_count; i++) {
    if (arpegiatingNote[i] != 0) {
      return 1;
    }
  }
  return 0;
}

bool isalreadysamenoteinpat(byte lenote) {
  for (int i = 0; i < liners_count; i++) {
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
    for (int i = 0; i < liners_count; i++) {
      if (lanotee == synth_off_pat[i][tickposition + 1][1]) {
        return 1;
      }
    }
  }
  if (modeselect == 1) {
    for (int i = 0; i < liners_count; i++) {
      if (lanotee == synth_off_pat[i][0][1]) {
        return 1;
      }
    }
  }
  if (modeselect == 2) {
    for (int i = 0; i < liners_count; i++) {
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
}

void deactivatelesccsfrompos(int lapos, byte lanote) {
  for (int i = lapos + 1; i < pbars; i++) {
    cc_partition[int(lanote)][i] = 127;
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
  for (int i = 0; i < pbars; i++) {
    if (synth_partition[linei][i][1] == lanotef) {
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
  for (int i = lapos; i < pbars - 1; i++) {
    if (synth_off_pat[linei][i + 1][1] == lanotee) {
      // 0 is liner
      return i + 1;
    }
  }
  return pbars;
}

void clearbouncedoffsafters(int linei, byte lanotef, int lapos) {
  int laposoftheNofafter = anothernOffisonafter(linei, lanotef, lapos);
  // howmany nofs before a non
  if ((laposoftheNofafter < pbars) && (laposoftheNofafter != 0)) {
    bool resultNoteOninbetween =
        testforaNoteOninbetween(linei, lapos, laposoftheNofafter, lanotef);
    if (resultNoteOninbetween) {
      if ((!checkifnonbefore(linei, lanotef, lapos)) && lapos != 0) {
        clearsaniloop = 0;
        // cleardoublon
        synth_off_pat[linei][lapos][0] = (byte)0;
        synth_off_pat[linei][lapos][1] = (byte)0;
      }
      if ((lapos == 0) && ((synth_off_pat[linei][pbars - 1][1] == lanotef) && synth_partition[linei][pbars - 1][1] != lanotef)) {
        // check before if no other On note if none found terminate that off
        clearsaniloop = 0;
        synth_off_pat[linei][0][0] = (byte)0;
        synth_off_pat[linei][0][1] = (byte)0;
      }
    }
    if (!resultNoteOninbetween) {
      clearsaniloop = 0;
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
        //Serial.print("terminated orphan note ");
        //Serial.print(synth_off_pat[linei][i][1]);
        clearsaniloop = 0;
        //Serial.println((int)synth_off_pat[linei][i][1]);
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
  terminateOffz(linei);
  clearlesnofbounces(linei, 0);
}

int getnextposofevent1Off(int linei, byte lanote, int fromi) {
  for (int i = fromi + 1; i < pbars; i++) {
    if (synth_off_pat[linei][i][1] == lanote) {
      return i;
    }
  }
  return (fromi + 1);
}

void tweakfreqlive(int liner, float tune) {
  //AudioNoInterrupts();
  for (int j = 0; j < synths_count; j++) {
    waveforms1[liner + (j * liners_count)]->frequency(tune * wavesfreqs[j]);
    FMwaveforms1[liner + (j * liners_count)]->frequency(tune * wavesfreqs[j]);
    drums1[liner + (j * liners_count)]->frequency(tune * wavesfreqs[j]);
  }
  //AudioInterrupts();
}

void stopglidenote(byte liner) {
  // during loop shift freq & restart freqs interpolating from last note during
  // glide duration hold+atck?
  dogliding[liner] = 0;
  Serial.println(" ");
  Serial.print("note before ");
  Serial.print(note_before);
  note_before += note_difference;
  Serial.print("note now ");
  Serial.println(note_before);
}

void stopglidenoteChords(byte liner) {
  // during loop shift freq & restart freqs interpolating from last note during
  // glide duration hold+atck?
  dogliding[liner] = 0;
  lapreviousnotewCmode[liner] += note_differenceCmode[liner];
}

void startglidenote(byte liner, byte data1) {
  // during loop shift freq & restart freqs interpolating from last note during
  // glide duration hold+atck?
  //glide for this liner activated
  dogliding[liner] = 1;

  note_difference = data1 - note_before;
  freq_difference = notestofreq[data1][1] - notestofreq[note_before][1];
  leglideposition[liner] = millis();
  //Serial.println(note_difference);
}

void startglidenoteChords(byte liner, byte data1) {
  // during loop shift freq & restart freqs interpolating from last note during
  // glide duration hold+atck?
  dogliding[liner] = 1;
  note_differenceCmode[liner] = data1 - lapreviousnotewCmode[liner];
  // Serial.println(note_difference);
  leglidershiftCmode[liner] = notestofreq[data1][1] - notestofreq[lapreviousnotewCmode[liner]][1];
  leglideposition[liner] = millis();
}

void computelenghtmesureoffline() {
  for (int linei = 0; linei < liners_count; linei++) {
    for (int i = 0; i < pbars; i++) {
      if (synth_partition[linei][i][1] != 0) {
        int laposof = getnextposofevent1Off(linei, synth_partition[linei][i][1], i);
        if (laposof < pbars - 1) {
          length0pbars[linei][i] = (laposof - i) * 4;
          templength0pbars[linei][i] = (laposof - i) * 4;
        } else {
          length0pbars[linei][i] = (pbars - i) * 4;
          templength0pbars[linei][i] = (pbars - i) * 4;
        }
        length1notes1[linei][i] = round((length0pbars[linei][i] / 4.0) * millitickinterval);
      }
    }
  }
}

void closeallenvelopes() {
  for (int i = 0; i < liners_count; i++) {
    synth_lines[i]->liner_off();
    /*
    enveloppesL[i]->noteOff();
    enveloppesL[i]->hold(0);
    synth_lines[i]->note = 0;
    synth_lines[i]->activated = 0;
    */
  }
}

bool check_glide_status(byte this_note){
  bool do_glide = 0;
  if (glidemode > 0 ){
    if (millis() - time_of_last_note > 5000) {
      note_before = this_note ;
      time_of_last_note = millis();
    } else {
      do_glide = 1;
    }
  }
  return do_glide ;
}

// TODO adsr check
void Mytickmidi() {
  // Serial.println("mclock");
  advance_tick();
}
void moncontrollercc(byte channel, byte control, byte value) {
  if (value < 127) {
    if (midiknobassigned[control] != 0 && !freezemidicc) {
      if (SendMidiOut) {
        //Serial.println("sending CC");
        uint8_t statusByte = static_cast<uint8_t>(0xB0 | channel);
        MidiUSB.sendMIDI({0x0B, statusByte, control, value});

        MidiUSB.flush();
      }

      controlswitcher(midiknobassigned[control], round((value / 127.0) * 1024.0));
      // AudioInterrupts();
    }
  }
}
void MaControlChange(byte channel, byte control, byte value) {
  bool isignored = noCCrecordlist(control);

  if (debugmidion) {
    debugmidi((char *)("ControlChange"), channel, control, value);
  }

  if (sublevels[0] == 2 && navlevel == 2){
    learn_midi(control);
  }

  moncontrollercc(channel, control, value);

  // Serial.print("Control Change, ch=");
  // Serial.print(lechannel);
  if (stoptick) {

    //Serial.print("CC=");
    //Serial.print(control);
    //Serial.print(" V=");
    //Serial.println(value);
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
    if (cc_partition[lecc][i] != 127) {

      Ccinterpolengh[lecc][0] = tickposition;
      Ccinterpolengh[lecc][1] = i;
      Ccinterpolengh[lecc][2] = i - tickposition;
      activateinterpolatecc[lecc] = 1;
      return;
    }
  }

  for (int i = 0; i < tickposition; i++) {
    if (cc_partition[lecc][i] != 127) {

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
    //if (activateinterpolatecc[i]) {
      continueCCinterpol(i);

    //}
  }
}
