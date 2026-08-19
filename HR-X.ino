
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

FlashLiner *flash_lines[FLASH_LINERS_COUNT] = {nullptr};
SynthLiner *synth_lines[SYNTH_LINERS_COUNT] = {nullptr};
LiveState lv;
EXTMEM Preset gg;
AdsrMenuRouter _ad;
EXTMEM BigBuffers bb;
SequencerClocker clocker;
ActiveLinesRegister _rg;
Arpegiator ap;
MidiRecorder md;
VirtualKnobs _vk;        
SettingsMenuRouter _st;
PresetsMenuRouter _ps;
EXTMEM Pattern pp ;
LFOMenuRouter _lf;
GlideMenuRouter _gd;
Filter303MenuRouter _ft;
Mp3PlayerRouter _mp;
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

EXTMEM Bounce clicked = Bounce(32, 100);

#if MULTIPLEXED_PADS
Bounce Backb = Bounce( 99, 5 );
#else
Bounce Backb = Bounce( 33, 5 );
#endif


DisplayManager dm;
GlobalMixer _mx;

CCEditor _ce;
PatEditRouter _pe;
POptionsRouter _po;
PatternsMenuRouter _pt;

MasterClock Tocker;

DisplayConsoler consoler;

//in progress TODO: make options in a menu
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
