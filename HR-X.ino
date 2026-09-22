
#include <Bounce.h>
#include <USBHost_t36.h>
#include "Voices.h"
#include "Patterns.h"
#include "Triggers.h"
#include "SongsMenu.h"
#include "SamplerMenu.h"
#include "PresetsMenu.h"
#include "KnobAssigner.h"
#include "WaveEditorMenu.h"
#include "SettingsMenu.h"
#include "WaveFormer.h"
#include "Functions.h"
#include "SynthMenu.h"
#include "LfoMenu.h"
#include "FxMenu.h"
#include "pads.h"
#include "muxer.h"

USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
USBHub hub3(myusb);
MIDIDevice midi1(myusb);
MIDIDevice midi2(myusb);
MIDIDevice midi3(myusb);
FlashLiner flash_lines[FLASH_LINERS_COUNT] = {
    FlashLiner(0),
    FlashLiner(1),
    FlashLiner(2),
    FlashLiner(3),
    FlashLiner(4),
    FlashLiner(5),
    FlashLiner(6),
    FlashLiner(7),
    FlashLiner(8),
    FlashLiner(9),
    FlashLiner(10),
    FlashLiner(11),
    FlashLiner(12),
    FlashLiner(13),
    FlashLiner(14),
    FlashLiner(15)
};
SynthLiner synth_lines[SYNTH_LINERS_COUNT] = {
  SynthLiner(0),
  SynthLiner(1),
  SynthLiner(2),
  SynthLiner(3),
  SynthLiner(4),
  SynthLiner(5)
};
LiveState mc;
EXTMEM Preset gg;
AdsrMenuRouter _ad;
EXTMEM BigBuffers bb;
SequencerClocker clocker;
ActiveLinesRegister _rg;
Arpegiator ap;
MidiRecorder md;
VirtualKnobs _vk;
MidiMenuRouter _mr;

PresetsMenuRouter _ps;
EXTMEM Pattern pp ;
LFOMenuRouter _lf;
GlideMenuRouter _gd;
Filter303MenuRouter _ft;
EXTMEM Mp3PlayerRouter _mp;
SynthMenuRouter _sn;
KnobAssigner _ka;
RecorderMenuRouter _rd;
SongEditorRouter _se;
SongMenuRouter _sg;
EXTMEM SamplerMenuRouter _sp;
WaveformsMenuRouter _wf;
EXTMEM Pads Padded;
Muxer muxer;
TriggerMessenger _tt;
FxMenuRouter _fx;
DisplayManager dm;
GlobalMixer _mx;
CCEditor _ce;
PatEditRouter _pe;
POptionsRouter _po;
PatternsMenuRouter _pt;
MasterClock Tocker;
DisplayConsoler consoler;
Song ng;
SettingsMenuRouter _st;

StereoDualFilter stereoWidth;

Bounce clicked = Bounce(32, 100);
#if MULTIPLEXED_PADS
Bounce Backb = Bounce( 99, 5 );
#else
Bounce Backb = Bounce( 33, 5 );
#endif
