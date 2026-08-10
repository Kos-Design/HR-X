
void unplugsynth() {

  // unplugfx();
  for (int i = 0; i < SYNTH_LINERS_COUNT*OSCS_COUNT; i++) {

    FMwavecords1[i]->disconnect();
    modulatecords1[i]->disconnect();
    stringcords1[i]->disconnect();
    MDdrumcords1[i]->disconnect();
    drumcords1[i]->disconnect();
    MDstringcords1[i]->disconnect();
    MDwavecords1[i]->disconnect();
    wavelinescords[i]->disconnect();
  }
}

void unplugfx() {

  for (int i = 0; i < PMIX_DM_SIZE; i++) {
    premixesMto[i]->disconnect();
    premixesMtoR[i]->disconnect();
  }
  for (int i = 0; i < FXCORDS_SIZE; i++) {
    fxcording[i]->disconnect();
  }
}
