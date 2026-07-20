// ===== DSP Objects =====

AudioFilterStateVariable stereoFilterL;
AudioFilterStateVariable stereoFilterR;

// Optional modulation
AudioSynthWaveform stereoLFO1;
AudioSynthWaveform stereoLFO2;

// ===== Patch Cords =====
// These are NOT connected until connect() is called.

AudioConnection stereoPatch1;
AudioConnection stereoPatch2;
AudioConnection stereoPatch3;
AudioConnection stereoPatch4;
AudioConnection stereoPatch5;
AudioConnection stereoPatch6;
class StereoDualFilter {
  public:

    StereoDualFilter(
        AudioStream& input,
        AudioStream& outL,
        AudioStream& outR,
        AudioStream& outL2,
        AudioStream& outR2,

        AudioFilterStateVariable& filterL,
        AudioFilterStateVariable& filterR,

        AudioConnection& p1,
        AudioConnection& p2,
        AudioConnection& p3,
        AudioConnection& p4,
        AudioConnection& p5,
        AudioConnection& p6)

        :

        mInput(input),
        mOutL(outL),
        mOutR(outR),
        mOutL2(outL2),
        mOutR2(outR2),

        mFilterL(filterL),
        mFilterR(filterR),

        patchInL(p1),
        patchInR(p2),
        patchOutL(p3),
        patchOutR(p4),
        patchOutL2(p5),
        patchOutR2(p6)

    {
    }

    //--------------;------------------------------------
    void disconnect_standard(){
      patchCord150.disconnect();
      patchCord151.disconnect();
      patchCord148.disconnect();
      patchCord149.disconnect();
    }

    void reconnect_standard(){
      patchCord150.connect(mixerWAll, 0, MasterL1, 2);
      patchCord151.connect(mixerWAll, 0, MasterR1, 2);
      patchCord148.connect(mixerWAll, 0, FXBusR, 2);
      patchCord149.connect(mixerWAll, 0, FXBusL, 2);
    }

    void connect()
    {
        disconnect_standard();
        patchInL.connect(mInput,0,mFilterL,0);
        patchInR.connect(mInput,0,mFilterR,0);
        
        patchOutL.connect(mFilterL,0,mOutL,2);
        patchOutR.connect(mFilterR,0,mOutR,2);
        patchOutL2.connect(mFilterL,0,mOutL2,2);
        patchOutR2.connect(mFilterR,0,mOutR2,2);
    }

    //--------------------------------------------------

    void disconnect()
    {
        patchInL.disconnect();
        patchInR.disconnect();

        patchOutL.disconnect();
        patchOutR.disconnect();
        patchOutL2.disconnect();
        patchOutR2.disconnect();
        reconnect_standard();
    }

    //--------------------------------------------------

    void setCutoff(float left,float right)
    {
        mFilterL.frequency(left);
        mFilterR.frequency(right);
        mFilterR.octaveControl(2.5);
        mFilterL.octaveControl(2.5);

    }

    //--------------------------------------------------

    void setResonance(float left,float right)
    {
        mFilterL.resonance(left);
        mFilterR.resonance(right);
    }

  private:

    AudioStream& mInput;

    AudioStream& mOutL;
    AudioStream& mOutR;
    AudioStream& mOutL2;
    AudioStream& mOutR2;

    AudioFilterStateVariable& mFilterL;
    AudioFilterStateVariable& mFilterR;

    AudioConnection& patchInL;
    AudioConnection& patchInR;
    AudioConnection& patchOutL;
    AudioConnection& patchOutR;
    AudioConnection& patchOutL2;
    AudioConnection& patchOutR2;
};

int clean_cursor(int pos){
  if (pos >= pbars ) {
    pos = 0 ;
    return pos;
  } else if (pos < 0 ) {
    pos = pbars - 1 ;
    return pos;
  }
  return pos;
}

void advance_tick(){
  tickposition = clean_cursor(tickposition+1);
  //TODO : remove tickerlasttick logic
  tickerlasttick = millis();
  tick();
}

//should be set after _pt & _se
void tick() {

  if (arpegiatorOn) {
      _pt.arpegiate_synth();
  }
  if (patternOn) {
    _se.use_pattern();
  }

  if (songplaying) {
    _se.update_song_player();
  }

}



StereoDualFilter stereoWidth( mixerWAll,

    MasterL1,
    MasterR1,
    FXBusL,
    FXBusR,

    stereoFilterL,
    stereoFilterR,

    stereoPatch1,
    stereoPatch2,
    stereoPatch3,
    stereoPatch4,
    stereoPatch5,
    stereoPatch6
);

/*
stereoWidth.connect();

stereoWidth.setCutoff(1800,1950);

stereoWidth.setResonance(0.7f,0.8f);
*/