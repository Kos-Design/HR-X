
void unplugsynth() {

  // unplugfx();
  for (int i = 0; i < nombreofliners*numberofsynthsw; i++) {

    FMwavecords1[i]->disconnect();
    modulatecords1[i]->disconnect();
    stringcords1[i]->disconnect();
    MDdrumcords1[i]->disconnect();
    drumcords1[i]->disconnect();
    MDstringcords1[i]->disconnect();
    wavelinescords[i]->disconnect();
  }
  // Serial.println("unplugcalled");
}

void unplugfx() {

  for (int i = 0; i < sizeopremixtoM; i++) {
    premixesMto[i]->disconnect();
  }
  for (int i = 0; i < sizeofxcords; i++) {
    fxcording[i]->disconnect();
  }
}

void setup() {

  // pseudoconsole((char*)"initializing...");
  // settime();

  AudioNoInterrupts();
  unplugsynth();
  unplugfx();
  unpluglfoonfilterz();
  delay(500);
  // metrodrum1.frequency(100);
  // metrodrum1.length(50);

  // metrodrum1.pitchMod(0.9);
  AudioInterrupts();

  initextmems();
  // setupmemtest();
  Serial.begin(9600);
  
  initializeconsolemsg();
  setupscreen();
  pseudoconsole((char *)"initializing...");
  initializesomevars();
  // delay(100);
  // Initialise the AutoVolumeLeveller
  // audioShield.autoVolumeControl(1, 1, 0, -6, 40, 20); // **BUG** with a max
  // gain of 0, turning the AVC off leaves a hung AVC problem where the attack
  // seems to hang in a loop. with it set 1 or 2, this does not occur.
  // audioShield.autoVolumeDisable();
  // audioShield.audioPostProcessorEnable();
  pseudoconsole((char *)"Setting USB Host...");
  delay(100);

  setuphubusb();
  pseudoconsole((char *)"USB Host Ready !");
  delay(50);

  pseudoconsole((char *)"Scanning SD Card");
  delay(100);
  setupSD();
  pseudoconsole((char *)"SD Card OK !");
  //notefreq1.begin(.15);
  // because I set bool isConnected as public instead of protected in
  // AudioStream.h
  // TODO : BAD , better extend class but not really needed
  // if (fxcording[1]->isConnected) {
  //  Serial.print("connected 420");
  // }
  //
  // if (patchCord98.isConnected) {
  //  Serial.print("connected");
  // }
  //delay(10);
  Pads.begin();
  pseudoconsole((char *)"Setting up I/O");
  for (unsigned int i = 0; i < manyinputpins; i++) {

    pinMode(inputpins[i], INPUT_PULLUP);
  }
  /*
   pinMode(A0, INPUT);
   pinMode(A2, INPUT);
   pinMode(A3, INPUT);
   */

  for (int i = 0; i < 128; i++) {

    midiknobassigned[i] = 0;
  }

  pseudoconsole((char *)"I/O Set !");
  pseudoconsole((char *)"Loading Defaults");
  stopticker();
  setupdefaultvalues();
  
  Serial.println("done3");
  // bitcrusher[0]->bits(4); //set the crusher to defaults. This will
  // passthrough clean at 16,44100 bitcrusher[0]->sampleRate(44100/4);
  // pseudoconsole((char*)"done3");
  // delay(100);
  // midiknobassigned[16]=2;

  // const int myInput = AUDIO_INPUT_LINEIN;
  // const int myInput = AUDIO_INPUT_MIC;

  Doautoassign();
  // printclock();
  pseudoconsole((char *)"All Done !");

  // setupextcharix();
  //   lesSelectedsamplescharix[0] = (char*)"SOUNDSET/PACK2/BASST-01.RAW";
  //    delay(500);
  // Serial.println((char*)(lesSelectedsamplescharix[0]));
  //delay(50);
  pseudoconsole((char *)"starting muxer");
  Muxer.start();
  //queue1.begin();
  AudioMemory(1500);
  audioShield.inputSelect(AUDIO_INPUT_LINEIN);
  audioShield.enable();

  audioShield.volume(1.0);
  /*
  
  metro1.begin(intervaltick, interval_ms * 1000);
  metro1.priority(250);
  */
  //metro3.begin(metro30, ( interval_ms /5 ) * 1000);
  //metro3.priority(138);
  //metro3.begin(metro30, 25 * 1000);
  // addtocharix((char*)"SOUNDSET/PACK2/BASST-02.RAW");
  // printthem();

  // new interval

  // playNoteTimer.priority(144);
  //  playNoteTimer.begin(tick2, 125);

  // printfolderix();
  initdone = 1;
  // switchfxes(0, 3) ;
  // switchfxes(1, 4) ;
  // switchfxes(2, 5) ;
  //recorder.begin("SOUNDSET/REC/WAV_01.WAV");
  pseudoconsole((char *)"Enjoy !");
  Serial.print("Device is plugged via usb: ");
  Serial.println(usb_configuration);
  // pseudoconsole((char*)"done !");
  // delay(100);
}

void initializesomevars() { initializepatternonsong(); }
