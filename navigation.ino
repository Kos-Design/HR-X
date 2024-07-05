

void updatebuttons() {
  clicked.update();
  //  Menub.update();
  // Backb.update();
}

// because the rotaencoder library increments 4 steps for 1 and keeps absolute
// count
void evalrota() {
  newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    count++;
  }
  if (rotamode) {
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
  }
  if (plusminusmode) {
    if (count >= 4) {
      oldPosition = newPosition;
      count = 0;
      vraipos = newPosition / 4;
      if (vraipos > navrange) {

        vraipos = navrange;
        myEnc.write(navrange * 4);
      }
      if (vraipos < 0) {

        vraipos = 0;
        myEnc.write(0);
      }
    }
  }
  if (vraipos != oldvraipos) {
    oldvraipos = vraipos;
    sublevels[navlevel] = vraipos;
    lemenuroot();

    //printit();
  }
}

void evalinputs() {

  bool backed = false;
  backed = Pads.get_back();
  if (backed) {

    sublevels[navlevel] = 0;

    if (navlevel > 0) {
      navlevel--;
    }
    if (navlevel == 0) {
      rotamode = 1;
      plusminusmode = 0;
    }

    lemenuroot();
    //printit();
  }
  if (clicked.fallingEdge()) {
    navlevel++;
    vraipos = sublevels[navlevel];
    myEnc.write(sublevels[navlevel] * 4);
    lemenuroot();
    //printit();
  }
}
