
void unplugsynth() {

  // unplugfx();
  for (int i = 0; i < synth_liners_count*synths_count; i++) {

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

  for (int i = 0; i < sizeopremixtoM; i++) {
    premixesMto[i]->disconnect();
  }
  for (int i = 0; i < sizeofxcords; i++) {
    fxcording[i]->disconnect();
  }
}

void init_fxes(){
  for (int i = 0; i < fxs_count; i++) {
    fx[i] = new FxBus(i);
  }
}