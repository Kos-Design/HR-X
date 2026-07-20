
int rota_enc_new_pos = 0;
int rota_enc_count = 0;
int rota_old_Pos = -999;
int rota_old_vrai_Pos = 0;
// rotaencoder library increments 4 steps for 1 and keeps absolute count
void evalrota() {
  rota_enc_new_pos = myEnc.read();
  if (rota_enc_new_pos != rota_old_Pos) {
    rota_enc_count++;
  }

  if (rota_enc_count >= 4) {
    rota_old_Pos = rota_enc_new_pos;
    rota_enc_count = 0;
    rota_true_pos = rota_enc_new_pos / 4;
    if (rota_true_pos > navrange) {

      rota_true_pos = 0;
      myEnc.write(0);
    }
    if (rota_true_pos < 0) {

      rota_true_pos = navrange;
      myEnc.write(navrange * 4);
    }
  }

  if (rota_true_pos != rota_old_vrai_Pos) {
    rota_old_vrai_Pos = rota_true_pos;
    sublevels[navlevel] = rota_true_pos;
    if (!navlevel) {
      dm.displaymenu();
      return;
    }
    dm.show();

    printit();
  }
}

void evalinputs() {

  clicked.update();
  if (!MULTIPLEXED_PADS) {
    Backb.update();
  }

  bool backed = false;
  backed = Pads.get_back();

  if (backed || (!MULTIPLEXED_PADS && Backb.fallingEdge()))  {
    //TODO: make overridable back like return to nav
    // one shot self disarming bool, or args in method call
    if (navlevel > 0) {
      navlevel--;
    }
    if (!navlevel) {
      dm.displaymenu();
      return;
    }
    sublevels[navlevel] = 0;
    if (retroaction) {
      sublevels[navlevel] = retroaction ;
      rota_true_pos = retroaction;
      myEnc.write(retroaction * 4);
      retroaction = 0;
    }
    dm.show();
    return;
  }
  if (clicked.fallingEdge()) {
    navlevel++;
    rota_true_pos = sublevels[navlevel];
    myEnc.write(sublevels[navlevel] * 4);
    dm.show();
    //printit();
  }
}
