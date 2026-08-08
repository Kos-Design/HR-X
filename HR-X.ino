
#include "muxer.h"
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Bounce.h>
#include <Encoder.h>
#include <play_sd_mp3.h>
#include <play_sd_flac.h>
#include "play_partial_sd_raw.h"
#include "Patterns.h"
#include "Triggers.h"
#include "pads.h"
#include "/home/kosmin/HR-X/includes/images.ino"
#include "/home/kosmin/HR-X/includes/notestofrequency_442.ino"
#include "/home/kosmin/HR-X/includes/AudioSetup.ino"
#include "/home/kosmin/HR-X/includes/cablages.ino"

#define MULTIPLEXED_PADS 1

//(6 * AUDIO_BLOCK_SAMPLES)
#define FLANGE_DELAY_LENGTH 768

//(16 * AUDIO_BLOCK_SAMPLES)
#define CHORUS_DELAY_LENGTH 2048

// 12800 is for 290 ms at 44.1 kHz
#define GRANULAR_MEMORY_SIZE 12800

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 7
#define SDCARD_SCK_PIN 14
#define MULTIPLEXER_PIN 32
const byte sizeofnoCCrecord = 11;

EXTMEM Pattern pp ;

EXTMEM Pads Pads;
Muxer Muxer;
TriggerMessenger _tt;

bool waveforming = false ;
bool locked_fileing = 0 ;
int retroaction = 0;
bool patternOn;
bool stoptick = true;
bool recordCC;
bool patrecord;

// functions that have system or various controls that are ignored for some ops
//outdated since refactor of ctl[]
byte noCCrecord[sizeofnoCCrecord] = {3,35,36,37, 38,39,40,41,42,44,1};
int tocker ;

int laCCduration;
int letempipolate;
float interpolcoeff;
EXTMEM byte leccinterpolated[128];

float BPMs = (60000.0 / gg.millitickinterval) / 4.0;

char consolemsg[10][32];
char pleasewaitarray[10][32];
int navlevelvbuttons = 2;
const int numberofvbuttonslabels = 8;
byte vbuttonsCC[numberofvbuttonslabels + 14 + 17];
const byte ssnamsize = 26;
EXTMEM char samplefoldersregistered[99][ssnamsize];
EXTMEM char samplebase[99][999][9];
EXTMEM int sizeofsamplefolder[99];
EXTMEM int sampledirsregistered = 0;
EXTMEM bool samplesselected[99][999];
EXTMEM int numberofsamplesselected[99];
EXTMEM bool samplesfoldersselected[99];
EXTMEM int numofsamplesfoldersselected = 0;
EXTMEM char Flashsamplename[999][13];
EXTMEM char Flashsamplebase[999][9];
EXTMEM bool Flashsamplesselected[999];
int numberofFlashsamplesselected = 0;
int numberofFlashfiles = 0;

EXTMEM char sampledirpath[99] = {"SOUNDSET/"};
String newloopedpath = "SOUNDSET/REC/LOOP00#L.RAW";
String newRecpathL = "SOUNDSET/REC/RECZ00#L.RAW";
String newRecpathR = "SOUNDSET/REC/RECZ00#R.RAW";
int tickposition;
bool stoptickernextcycle;

EXTMEM Preset gg ;

byte oscillator = 0;
byte cclfoselector = 0 ;
//selector for the Fx bus
byte fidx = 0;

// lenght of the current interpolation
// from leinterpolstart to [1] interpole target position
byte Ccinterpolengh[128][3];

bool temp_buff_armed = 0 ;
int tickerlasttick;
byte recorded_ccs[32] ;
byte pots_controllers[32][32][2];
byte activateinterpolatecc[8];

EXTMEM GFXcanvas1 canvasBIG(128, 64);
EXTMEM GFXcanvas1 canvastitle(128, 16);
EXTMEM Bounce clicked = Bounce(32, 100);
EXTMEM Encoder myEnc(30, 31);
//placeholder
#if MULTIPLEXED_PADS
Bounce Backb = Bounce( 99, 5 );
#else
Bounce Backb = Bounce( 33, 5 );
#endif

const CcCalls ctl[] = {{"Disabled",nullptr},{"Volume",&Volume_ctl},{"SynthLevel",&SynthVolume_ctl},{"SDLevel",&SDPlayerVolume_ctl},{"FlashLevel",&FlashVolume_ctl},
                      {"FX1 Wet",&Wet1Volume_ctl},{"FX2 Wet",&Wet2Volume_ctl},{"FX3 Wet",&Wet3Volume_ctl},{"Dry Sampler",&DrySampler_ctl},{"Dry Synth",&DrySynth_ctl},
                      //10 ok
                      {"Dry Audio In",&DryAudioIn_ctl},{"CutOff slp.",&Slope1_ctl},{"Reso slp.",&Slope2_ctl},{"Reso Tweak",&ResoTweak_ctl},{"FREE",nullptr},
                      {"CutOff Tweak",&CutOffTweak_ctl},{"Stereo On",toggle_stereo},{"Stereo Off",turn_off_stereo},{"Filter303 Lvl.",&Filter303_ctl},{"Portamento time",&set_Portamento_time_ctl},
                      //20 ok
                      {"Filter303 PreAmp",&FilterPreAmp_ctl},{"Synth Index",&SynthIndex_ctl},{"Syth X Lvl.",&SynthXLevel_ctl},{"Synth X Freq",&SynthXFreq_ctl},{"Chords type",&SetChords_ctl},
                      {"Pans Levels",&PansLevels_ctl},{"Metronome Level",&MetroDrumLevel_ctl},{"Play Song",&PlaySong_Trigger_ctl},{"Stop Song",&StopSong_Trigger_ctl},{"Pause Song",&PauseSong_Trigger_ctl},
                      //30 ok
                      {"Record Midi",&RecordPattern_Trigger_ctl},{"Record CC Events",&RecordCCPatern_Trigger_ctl},{"Stop Ticking",&StopTicking_Trigger_ctl},{"Start Ticking",&StartTicking_Trigger_ctl},{"Restart Ticker",&TickFromStart_Trigger_ctl},
                      {"Arpegio Type",&ArpegioType_ctl},{"Arpegio Mode",&ArpegioMode_ctl},{"Arp. Notes Count",&ArpegioNotesCount_ctl},{"Arpegio Offset",&ArpegioStartOffset_ctl},{"Arpegio Grid C.",&ArpegioGridC_ctl},
                      //40 ok
                      {"Arpegio Grid S",&ArpegioGridS_ctl},{"Arpegio Length",&ArpegioLength_ctl},{"SX Modulation type",&SynthXModulationType_ctl},{"Synth X Type",&SynthXtype_ctl},{"Synth X Offset",&SynthXOffset_ctl},
                      {"Synth X Phase",&SynthXPhase_ctl},{"Analog Toggle",&AnalogTouch_Toggle_ctl},{"LFO X Level",&LFOXLevel_ctl},{"LFO X Type",&LFOXType_ctl},{"LFO X Freq",&LFOXFreq_ctl},
                      //50 ok
                      {"LFO X Phase",&LFOXPhase_ctl},{"LFO X Offset",&LFOXOffset_ctl},{"LFO X Sync",&LFOXLSync_Toggle_ctl},{"ADSR Atk. Delay",&AdsrAtckDelay_ctl},{"ADSR Attack",&AdsrAttack_ctl},
                      {"ADSR Hold",&AdsrHold_ctl},{"ADSR Decay",&AdsrDecay_ctl},{"ADSR Sustain",&AdsrSustain_ctl},{"ADSR Release",&AdsrRelease_ctl},{"Filter303 Knob1",&Filter303_Knob1_ctl},
                      //60 ok
                      {"Filter303 Knob2",&Filter303_Knob2_ctl},{"Filter303 Knob3",&Filter303_Knob3_ctl},{"FX Bus select",&FXBusSelector_ctl},{"Chorus Voices",&ChorusVoices_ctl},{"BiQuad Stage",&BiQuadStage_ctl},
                      {"BiQuad Freq.",&BiQuadFreq_ctl},{"BiQuad Slope",&BiQuadSlope_ctl},{"BiQuad Gain",&BiQuadGain_ctl},{"BQuad Type",&BiQuadType_ctl},{"Lfo on Ffilter",&LFOonFilter_ctl},
                      //70 ok
                      {"Ffilter CutOff",&FFilter_Cutoff_Knob1_ctl},{"Ffilter Resonance",&FFilter_Reso_Knob2_ctl},{"Ffilter Octave",&FFilter_Oct_Knob3_ctl},{"Ffilter LowPass",&FFilter_LowPass_Knob4_ctl},{"Ffilter BandPass",&FFilter_BandPass_Knob5_ctl},
                      {"Ffilter HighPass",&FFilter_HighPass_Knob6_ctl},{"Granular Grains",&GranularGrains_Knob1_ctl},{"Granular Speed",&GranularSpeed_Knob2_ctl},{"Granular Freeze",&GranularFreeze_Toggle_ctl},{"Granular Shift",&GranularShifting_Toggle_ctl},
                      //90 ok
                      {"Reverb Size",&ReverbSize_ctl},{"BitCrusher Samples",&BitCrusherSamples_ctl},{"BitCrusher Bits",&BitCrusherBits_ctl},{"Flanger Offset",&FlangerOffset_Knob1_ctl},{"Flanger Depth",&FlangerDepth_Knob2_ctl},
                      {"Flanger Delay",&FlangerDelay_Knob3_ctl},{"Delay Time sel.",&DelayTimeSelection_Knob1_ctl},{"Delay Multiplier",&DelayTimeMultiplier_Knob2_ctl},{"Delay Feedback",&DelayFeedback_Knob3_ctl},{"Audio In Volume",&AudioInVolume_ctl},
                      //100ok
                      {"FREE",nullptr},{"Set BPMs",&SetBPMs_ctl},{"Save New Pattern",&SaveToNewPattern_Trigger_ctl},{"Load First Pattern",&LoadFirstPattern_Trigger_ctl},{"Record Audio",&RecordAudio_Trigger_ctl},
                      {"Play Record",&PlayLoadedAudio_Trigger_ctl},{"Stop Recording",&StopRecording_Trigger_ctl},{"Load First Preset",&LoadFirstPreset_Toggle_ctl},{"Arb[] MaxF",&ArbitraryMaxF_ctl},{"Merge Patterns",&MergeSynthPatterns_Trigger_ctl},
                      //120 ok
                      {"Flash Line1 Level",&FlashLineVolume_Knob1_ctl},{"Flash Line2 Level",&FlashLineVolume_Knob2_ctl},{"Flash Line3 Level",&FlashLineVolume_Knob3_ctl},{"Flash Line4 Level",&FlashLineVolume_Knob4_ctl},{"Flash Line5 Level",&FlashLineVolume_Knob5_ctl},
                      {"Flash Line6 Level",&FlashLineVolume_Knob6_ctl},{"Flash Line7 Level",&FlashLineVolume_Knob7_ctl},{"Flash Line8 Level",&FlashLineVolume_Knob8_ctl},{"Flash Line9 Level",&FlashLineVolume_Knob9_ctl},{"Flash Line10 Level",&FlashLineVolume_Knob10_ctl},
                      //130 ok
                      {"Flash Line11 Level",&FlashLineVolume_Knob11_ctl},{"Flash Line12 Level",&FlashLineVolume_Knob12_ctl},{"Flash Line13 Level",&FlashLineVolume_Knob13_ctl},{"Flash Line14 Level",&FlashLineVolume_Knob14_ctl},{"Flash Line15 Level",&FlashLineVolume_Knob15_ctl},
                      {"Flash Line16 Level",&FlashLineVolume_Knob16_ctl},{"Show oscilloscope",&spectro_Toggle_ctl},{"Show EQ Bars",&eq_display_Toggle_ctl},{"USB In Volume",&USB_In_Volume_ctl},{"Fps oscilloscope",&adjust_osc_framerate_ctl},
                      //140 ok
                      {"Time oscilloscope",&adjust_osc_timee_ctl},{"refresh OscScope",&adjust_osc_refresher_period_ctl},{"Wav Editor Pitch",&adjust_waveEditor_pitch_ctl},{"Rota Nav +",&rota_increase_ctl}, {"Rota Nav -",&adjust_rota_decrease_ctl},      
                      {"Validate Nav",&validate_pushed_ctl},{"Cancel Nav",&cancel_pushed_ctl},{"Pitch Attack",&set_Portamento_height_ctl} 
                      };

constexpr uint16_t CtlCount = sizeof(ctl) / sizeof(ctl[0]);

bool showing_eq = false;

int navlevel = 0;
int previousnavlevel = 0;
int navleveloverwrite = 2;
int navrange = 9;
int rota_true_pos = 0;

int sublevels[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

Adafruit_SSD1306 display(128, 64, &Wire2, -1);

DisplayManager dm = DisplayManager();
GlobalMixer _mx = GlobalMixer(AudioShield);

void returntonav(byte lelevel, byte lanavrange = navrange,byte t_vraipos = rota_true_pos) {
  navlevel = lelevel;
  rota_true_pos = t_vraipos;
  myEnc.write(rota_true_pos * 4);
  navrange = lanavrange;
  if (navlevel) dm.show();
}

CCEditor _ce;
PatEditRouter _pe;
POptionsRouter _po;
PatternsMenuRouter _pt;

class MasterClock {
    public:

        MasterClock() {self = this;}

        bool stop = 1 ;

        static void click() {
            self->tick96++;
            //if (!(self->tick96 % 2))
            //self->dispatch_ticks();
        }

        void dispatch_ticks() {
            
            if ((tick96 % 8) == 0 && _callback_3){
                _callback_3();
            }
            if ((tick96 % 96*4) == 0 && _callback_long){
                _callback_long();
            }
            if ((tick96 % 2) == 0 && _callback_16){
                _callback_16();
            }
            if (!self->stop) {
                if ((tick96 % 24) == 0 && _callback_24){
                    _callback_24();
                }
            }
        }

        void attach_16(void (*cb)()) {
            _callback_16 = cb;
        }

        void attach_long(void (*cb)()) {
            _callback_long = cb;
        }

        void attach_24(void (*cb)()) {
            _callback_24 = cb;
        }

        void attach_3(void (*cb)()) {
            _callback_3 = cb;
        }

        void stopticker() {
            stoptick = 1;
            recordCC = 0;
            self->stop = 1;
            // if (patrecord) {
            // computelenghtmesureoffline();
            patternOn = 0;
            patrecord = 0;
            // tickposition = 0 ;
        }

        void startticker() {
            //TODO: reimplement external midi clock use
            //if (!gg.externalticker) {
            stoptick = 0;
            self->stop = 0;
            patternOn = 1;
        }

    private:

        volatile uint32_t tick96 = 0;
        void (*_callback_24)() = nullptr;
        void (*_callback_3)() = nullptr;
        void (*_callback_16)() = nullptr;
        void (*_callback_long)() = nullptr;
        static MasterClock* self;
};

MasterClock* MasterClock::self = nullptr;

MasterClock Tocker;

DisplayConsoler consoler;
