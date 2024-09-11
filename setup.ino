
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
  //delay(100);
  //Initialise the AutoVolumeLeveller
  //audioShield.autoVolumeControl(1, 1, 0, -6, 40, 20); // **BUG** with a max
  //gain of 0, turning the AVC off leaves a hung AVC problem where the attack
  //seems to hang in a loop. with it set 1 or 2, this does not occur.
  //audioShield.autoVolumeDisable();
  //audioShield.audioPostProcessorEnable();
  pseudoconsole((char *)"Setting USB Host...");
  delay(100);

  setuphubusb();
  pseudoconsole((char *)"USB Host Ready !");
  delay(50);

  pseudoconsole((char *)"Scanning SD Card");
  delay(100);
  setupSD();
  pseudoconsole((char *)"SD Card OK !");
  Pads.begin();
  pseudoconsole((char *)"Setting up I/O");
  for (unsigned int i = 0; i < manyinputpins; i++) {
    pinMode(inputpins[i], INPUT_PULLUP);
  }
  for (int i = 0; i < 128; i++) {
    midiknobassigned[i] = 0;
  }
  pseudoconsole((char *)"I/O Set !");
  pseudoconsole((char *)"Loading Defaults");
  stopticker();
  setupdefaultvalues();
  Serial.println("done3");
  Doautoassign();
  pseudoconsole((char *)"All Done !");
  pseudoconsole((char *)"starting muxer");
  Muxer.start();
  //queue1.begin();
  AudioMemory(1200);
  audioShield.inputSelect(AUDIO_INPUT_LINEIN);
  audioShield.enable();
  audioShield.volume(1.0);
  initdone = 1;
  pseudoconsole((char *)"Enjoy !");
  //Serial.print("Device is plugged via usb: ");
  //Serial.println(usb_configuration);
}

void initializesomevars() { initializepatternonsong(); }
