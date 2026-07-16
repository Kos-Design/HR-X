

// rotaencoder library increments 4 steps for 1 and keeps absolute count
void evalrota() {
  newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    count++;
  }

  if (count >= 4) {
    oldPosition = newPosition;
    count = 0;
    vraipos = newPosition / 4;
    if (vraipos > navrange) {

      vraipos = 0;
      myEnc.write(0);
    }
    if (vraipos < 0) {

      vraipos = navrange;
      myEnc.write(navrange * 4);
    }
  }

  if (vraipos != oldvraipos) {
    oldvraipos = vraipos;
    sublevels[navlevel] = vraipos;
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
      vraipos = retroaction;
      myEnc.write(retroaction * 4);
      retroaction = 0;
    }
    dm.show();
    return;
  }
  if (clicked.fallingEdge()) {
    navlevel++;
    vraipos = sublevels[navlevel];
    myEnc.write(sublevels[navlevel] * 4);
    dm.show();
    //printit();
  }
}
