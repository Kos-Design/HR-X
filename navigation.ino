


void updatebuttons() {
  clicked.update();
//  Menub.update();
  //Backb.update();
  
}   

    


// because the rotaencoder library increments 4 steps for 1 and keeps absolute count
void evalrota() {
  newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    count++;
    
  }
  if (rotamode) {
  if (count >= 4) {
    oldPosition = newPosition;
    count = 0;
    vraipos = newPosition / 4 ;
     if ( vraipos > navrange) {
   
      vraipos = 0 ; 
      myEnc.write(0);
           
    }
  if ( vraipos < 0 ) {
   
      vraipos = navrange ;
      myEnc.write(navrange*4);
           
    }
  }
    }
     if (plusminusmode) {
  if (count >= 4) {
    oldPosition = newPosition;
    count = 0;
    vraipos = newPosition / 4 ;
     if ( vraipos > navrange) {
   
      vraipos = navrange ; 
      myEnc.write(navrange*4);
           
    }
  if ( vraipos < 0 ) {
   
      vraipos = 0 ;
      myEnc.write(0);
           
    }
    }
  }
    if ( vraipos != oldvraipos ) {
      oldvraipos = vraipos ;
      sublevels[navlevel] = vraipos;
//    if ((sublevels[0]==6 )&& (navlevel > 0)){
//      MainFxPanel();
//     } else  {
//      //if ((sublevels[0]==8 )&& (navlevel > 1)){
//       // pacificexplorer();
//     // } 
//     // else {
        lemenuroot();
//      //}
//     }
      printit();
  
  }
 
}

void evalinputs() {
//  if ( Menub.fallingEdge() ) {
//    Serial.println("Menu");
//     rotamode = 1 ;
//     plusminusmode = 0 ;
//      navlevel = 0 ;
//      sublevels[navlevel] = 0 ;
//      navin = 1 ;
//     
//      lemenuroot();
//      
//  }
bool backed = false;
backed = Pads.get_back() ;
  if (backed ) {
    //Backb.fallingEdge()
   // Serial.println("Back");
    
      sublevels[navlevel] = 0 ;
//      if ( playRawL.isPlaying() ) {
//        playRawL.stop();
//      }
//       if ( playSdWav1.isPlaying() ) {
//        playSdWav1.stop();
//      }
     
     if ( navlevel > 0 ) { 
      navlevel--; 
      }
     if (navlevel == 0 ) {
      rotamode = 1 ;
     plusminusmode = 0 ;  
     }

        lemenuroot();

  }
  if ( clicked.fallingEdge() ) {
    //Serial.println("up");
    
     navlevel++;
    vraipos = sublevels[navlevel];
    myEnc.write(sublevels[navlevel]*4);

        lemenuroot();   
  }

 
 }
  
