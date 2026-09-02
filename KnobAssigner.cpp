#include "KnobAssigner.h"
#include "avr/pgmspace.h"
#include "Functions.h"
#include "Presets.h"

KnobAssigner* KnobAssigner::self = nullptr;

KnobAssigner::KnobAssigner() {
                    self = this;
                    self->home_navrange=CtlCount-1;
                    self->relative_navlevel=2;
                    self->max_navlevel=3;
                    self->sublevels_address={2,0,0};
                    }

void KnobAssigner::KnobAssigner::show() {
  lv.knobsetting = false ;
  _actionable[lv.navlevel-self->relative_navlevel]();
}

void KnobAssigner::learn_midi(byte captured){
  lv.sublevels[self->relative_navlevel+1] = captured ;
  gg.midiknobassigned[lv.sublevels[self->relative_navlevel+1]] = lv.sublevels[self->relative_navlevel];
  dm.returntonav(self->relative_navlevel,self->home_navrange,lv.sublevels[self->relative_navlevel]);
}

int KnobAssigner::find_assigned_knob(int k){
  for (int i = 0; i < 128; i++) {
    if (gg.midiknobassigned[i] == k){
      return i;
    }
  }
  return 0 ;
}

void KnobAssigner::show_assignements(){
  if (lv.sublevels[self->relative_navlevel+1] != 0) {
    dm.canvasBIG.print("Midi");
    dm.canvasBIG.setTextSize(1);
    dm.canvasBIG.setCursor(50, 47);
    dm.canvasBIG.print("(cc)");
    dm.canvasBIG.setCursor(71, 39);
    dm.canvasBIG.setTextSize(3);
    dm.canvasBIG.print(":");
    dm.canvasBIG.setTextSize(2);
    dm.canvasBIG.setCursor(85, 40);
    dm.canvasBIG.print(lv.sublevels[self->relative_navlevel+1]);
  } else {
    dm.canvasBIG.println("Unassigned");
  }
}

void KnobAssigner::kb_home(){
  lv.navrange = self->home_navrange;
  dm.clean_title_1_2();
  if (lv.sublevels[self->relative_navlevel] != 0) {
    dm.canvastitle.println(ctl[lv.sublevels[self->relative_navlevel]].name);
    dm.canvasBIG.setTextSize(2);
    dm.canvasBIG.setCursor(0, 40);
    lv.sublevels[self->relative_navlevel+1] = find_assigned_knob(lv.sublevels[self->relative_navlevel]) ;
    show_assignements();
  } else {
    dm.canvastitle.setTextSize(2);
    dm.canvastitle.println("Select");
    dm.canvasBIG.setTextSize(2);
    dm.canvasBIG.setCursor(0, 28);
    dm.canvasBIG.println("Control");
  }
  dm.dodisplay();
}

void KnobAssigner::assigner(){
  lv.knobsetting = true ;
  lv.navrange = 127;
  if (lv.sublevels[self->relative_navlevel] == 0 ) {
    dm.returntonav(self->relative_navlevel,self->home_navrange,lv.sublevels[self->relative_navlevel]);
  } else {
    dm.clean_title_1_2();
    dm.canvastitle.println(ctl[lv.sublevels[self->relative_navlevel]].name);
    dm.canvasBIG.setCursor(0, 40);
    show_assignements();
  }
  dm.dodisplay();
}

void KnobAssigner::set_midi_cc_to_ctl(byte cc_nt, int cc_cl){
  gg.midiknobassigned[cc_nt] = cc_cl;
}

void KnobAssigner::set_it(){
  lv.knobsetting = false ;
  set_midi_cc_to_ctl(find_assigned_knob(lv.sublevels[self->relative_navlevel]), 0);
  set_midi_cc_to_ctl(lv.sublevels[self->relative_navlevel+1] , lv.sublevels[self->relative_navlevel]);
  dm.returntonav(self->relative_navlevel,self->home_navrange, lv.sublevels[self->relative_navlevel]);
}

AdsrMenuRouter* AdsrMenuRouter::self = nullptr;

AdsrMenuRouter::AdsrMenuRouter() {
                    self = this;
                    self->home_navrange=SN_MENU_LABELS_COUNT-1;
                    self->relative_navlevel=1;
                    self->max_navlevel=5;
                    self->sublevels_address={0,0,0};
                    }

void AdsrMenuRouter::show(){
  lv.navrange = 5 ;
  slice_adsr();
  uint16_t lvx = lv.sublevels[lv.navleveloverwrite] ;
  dm.clean_title_1_1();
  draw_frame();
  print_adsr_echo(AdsrLabels[lvx],self->tmp_adsrlevels[lvx]);
  int totalliner = self->tmp_adsrlevels[Attack] * 10 + self->tmp_adsrlevels[Decay] + 100 + self->tmp_adsrlevels[Release] +
                  self->tmp_adsrlevels[AttackDelay] * 2 + self->tmp_adsrlevels[Hold] + 5;
  float linerratio = 124.0 / totalliner;
  uint16_t a0 = round(self->tmp_adsrlevels[AttackDelay] * 10 * linerratio) + 5;
  uint16_t h0 = round(self->tmp_adsrlevels[Attack] * 10 * linerratio) + a0;
  uint16_t d0 = h0 + round(self->tmp_adsrlevels[Hold] * linerratio);
  uint16_t s0 = d0 + round(self->tmp_adsrlevels[Decay] * linerratio);
  uint16_t suY = map(self->tmp_adsrlevels[Sustain], 0, 100, 37, 0) + 22;
  uint16_t r0 = s0 + 100 * linerratio;
  uint16_t r1 = r0 + self->tmp_adsrlevels[Release] * linerratio;
  uint16_t starter_x[6] = {3,a0,h0,d0,s0,r0};
  dm.canvasBIG.drawLine(a0, 61, h0, 24, SSD1306_WHITE);
  dm.canvasBIG.drawLine(h0, 24, d0, 24, SSD1306_WHITE);
  dm.canvasBIG.drawLine(d0, 24, s0, suY, SSD1306_WHITE);
  dm.canvasBIG.drawLine(s0, suY, r0, suY, SSD1306_WHITE);
  dm.canvasBIG.drawLine(r0, suY, r1, 61, SSD1306_WHITE);
  dm.dodisplay();
  if (lvx<2) linerratio *= 10 ;
  dm.fillRect(starter_x[lvx], 16, round(self->tmp_adsrlevels[lvx] * linerratio) + 1, 45, SSD1306_INVERSE);
  dm.display();
}

void AdsrMenuRouter::ApplyADSR() {
  for (int i = 0; i < SYNTH_LINERS_COUNT; i++) {
    enveloppesL[i]->delay(gg.adsrlevels[AttackDelay]);
    enveloppesL[i]->attack(gg.adsrlevels[Attack]);
    enveloppesL[i]->hold(gg.adsrlevels[Hold]);
    enveloppesL[i]->decay(gg.adsrlevels[Decay]);
    enveloppesL[i]->sustain(gg.adsrlevels[Sustain] / 100.0);
    enveloppesL[i]->release(gg.adsrlevels[Release]);
  }
  resync_tmp();
}

void AdsrMenuRouter::draw_frame() {
  dm.canvasBIG.drawLine(2, 61, 2, 18, SSD1306_WHITE);
  dm.canvasBIG.drawLine(2, 61, 125, 61, SSD1306_WHITE);
  dm.canvasBIG.drawLine(125, 59, 127, 61, SSD1306_WHITE);
  dm.canvasBIG.drawLine(125, 63, 127, 61, SSD1306_WHITE);
  dm.canvasBIG.drawLine(2, 16, 0, 18, SSD1306_WHITE);
  dm.canvasBIG.drawLine(2, 16, 4, 18, SSD1306_WHITE);
}

void AdsrMenuRouter::SetADSR() {
  memcpy(gg.adsrlevels, self->tmp_adsrlevels, sizeof(gg.adsrlevels));
}

void AdsrMenuRouter::GlobalADSR() {
  SetADSR();
  ApplyADSR();
}

void AdsrMenuRouter::print_adsr_echo(String titre, int niveau){
  dm.canvastitle.setTextSize(1);
  dm.canvastitle.setCursor(0, 0);
  dm.canvastitle.fillScreen(SSD1306_BLACK);
  dm.canvastitle.println(titre);
  dm.canvastitle.setCursor(55, 0);
  dm.canvastitle.println(niveau);
}

void AdsrMenuRouter::resync_tmp(){
  memcpy(self->tmp_adsrlevels, gg.adsrlevels, sizeof(gg.adsrlevels));
}

void AdsrMenuRouter::slice_adsr(){
  lv.navleveloverwrite = 2;
  if (lv.navlevel == lv.navleveloverwrite ) {
    self->tmp_adsrlevels[lv.sublevels[lv.navleveloverwrite]] = gg.adsrlevels[lv.sublevels[lv.navleveloverwrite]];
    lv.sublevels[lv.navlevel + 1] = self->tmp_adsrlevels[lv.sublevels[lv.navleveloverwrite]];
  }
  if (lv.navlevel == lv.navleveloverwrite + 1) {
    lv.navrange = local_navranges[lv.sublevels[lv.navleveloverwrite]];
    self->tmp_adsrlevels[lv.sublevels[lv.navleveloverwrite]] = lv.sublevels[lv.navleveloverwrite + 1];
  }
  if (lv.navlevel == lv.navleveloverwrite + 2) {
    GlobalADSR();
    dm.returntonav(lv.navleveloverwrite, 5,lv.sublevels[lv.navleveloverwrite]);
  }
}

StereoDualFilter::StereoDualFilter(
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
  patchOutR2(p6){

}

void StereoDualFilter::disconnect_standard(){
  patchCord150.disconnect();
  patchCord151.disconnect();
  patchCord148.disconnect();
  patchCord149.disconnect();
}

void StereoDualFilter::reconnect_standard(){
  patchCord150.connect();
  patchCord151.connect();
  patchCord148.connect();
  patchCord149.connect();
}

void StereoDualFilter::connect(){
  disconnect_standard();
  stereoLFOL.begin(0.4, 0.025, WAVEFORM_SINE);
  stereoLFOR.begin(0.4, 0.025, WAVEFORM_SINE);
  stereoLFOL.phase(180);
  patchInL.connect(mInput,0,mFilterL,0);
  patchInR.connect(mInput,0,mFilterR,0);
  patchOutL.connect(mFilterL,0,mOutL,2);
  patchOutR.connect(mFilterR,0,mOutR,2);
  patchOutL2.connect(mFilterL,0,mOutL2,2);
  patchOutR2.connect(mFilterR,0,mOutR2,2);
}

void StereoDualFilter::disconnect(){
  patchInL.disconnect();
  patchInR.disconnect();
  patchOutL.disconnect();
  patchOutR.disconnect();
  patchOutL2.disconnect();
  patchOutR2.disconnect();
  reconnect_standard();
}

void StereoDualFilter::setCutoff(float left,float right) {
  mFilterL.frequency(left);
  mFilterR.frequency(right);
  mFilterR.octaveControl(2.5);
  mFilterL.octaveControl(2.5);
}

void StereoDualFilter::setResonance(float left,float right)  {
  mFilterL.resonance(left);
  mFilterR.resonance(right);
}


