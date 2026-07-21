#define MULTIPLEXED_PADS 1

const int display_lag = 10 ;
const int control_lag = 10 ;
#include "MenuClasses.h"
#include "muxer.h"
#include "ParserLib.h"
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Bounce.h>
#include <Encoder.h>
#include <MIDIUSB.h>
#include <play_sd_mp3.h>
#include <play_sd_flac.h>
#include "play_partial_sd_raw.h"
#include "FilesLister.h"
#include "Patterns.h"

Muxer Muxer;

bool locked_fileing = 0 ;
int retroaction = 0;
const byte sizeofnoCCrecord = 11;

constexpr uint8_t SCREEN_ADDRESS = 0x3C;
constexpr uint8_t OSCS_COUNT = 3;
constexpr uint8_t SN_MENU_LABELS_COUNT = 5 ;
constexpr int SYNTH_LINERS_COUNT = 6 ;
const int available_track_types = 2;
const int pbars = 32;
const int flash_liners_count = 16;
const int sampler_labels_count = 4;
bool track_cells[available_track_types][pbars] = {0};

EXTMEM byte synth_partition[SYNTH_LINERS_COUNT][pbars][3];
EXTMEM byte temp_synth_partition[pbars][3];
EXTMEM byte synth_off_pat[SYNTH_LINERS_COUNT][pbars][3];
EXTMEM int synth_notes_length[SYNTH_LINERS_COUNT][pbars];
byte synth_start_tpos[SYNTH_LINERS_COUNT];
EXTMEM byte sampler_partition[flash_liners_count][pbars][3];
EXTMEM byte temp_sampler_partition[pbars][3];
EXTMEM int flash_notes_length[flash_liners_count][pbars];
byte sampler_off_pat[pbars][3];
bool patternOn;
bool stoptick = true;
bool recordCC;
bool patrecord;
int midiknobassigned[128];
EXTMEM byte cc_partition[128][pbars];

bool setting_on_board = false ;
bool waveforming = false ;
bool assigning_sample_to_note = false ;
bool knobsetting = false ;
bool paterning = false ;

// functions that have system or various controls that are ignored for some ops
//outdated since refactor of ctl[]
byte noCCrecord[sizeofnoCCrecord] = {3,35,36,37, 38,39,40,41,42,44, 1};
byte slope1 = 100;
byte slope2 = 1;
bool mp3_looped = 0 ;
bool externalticker;
int starttaptime;
int numberoftaps;
int tapstime[5] = {0};
float tapaverage;
const byte sg_labels_count = 8;

const byte ps_labels_count = 5;
const byte sizeofLFOlabels = 9;
const byte settings_labels_count = 16;
//doesn't seem to affect arbitrary waveforms... :(
float arbitrary_maxF[3] = { 172.0, 172.0, 172.0} ;
int millitickinterval = 115;
bool avoid_fx_bounce = false;
float interval_ms = millitickinterval ;
byte smixervknobs[16] = {127, 127, 127, 127, 127, 127, 127, 127,
                         127, 127, 127, 127, 127, 127, 127, 127};

byte offsetliner;
byte x_axis_cc = 17 ;
byte y_axis_cc = 18 ;
byte trace_wave_cc = 58 ;
byte *waveform_tracers[3]= {&x_axis_cc,&y_axis_cc,&trace_wave_cc};
bool taptap_on = true;
bool rec_looping;
int tocker ;
byte filter_lfo_option = 3 ;
byte le303ffilterzVknobs[3];

byte songpage = 0;
byte samplelinerspage;

// LP BP HP 127
byte mixle303ffilterzVknobs[3];
byte navrecmenu = 1;
int laCCduration;
int letempipolate;
float interpolcoeff;
byte settointerpolate[128];
EXTMEM byte leccinterpolated[128];
float le303filterzgainz[3] = {1.0, 0.0, 0.0};
byte le303filterzwet = 100;
float le303filterzfreq = 10000;
float le303filterzreso = 2.7;
float le303filterzoctv = 2.5;
bool clearsaniloop;
// float targetBPM = 120.0 ;
float BPMs = (60000.0 / millitickinterval) / 4.0;

float BPM = 130.0;
/*
unsigned long MICROSECONDS_PER_MINUTE = 60000000;
unsigned long MICROSECONDS_PER_BEAT = MICROSECONDS_PER_MINUTE / BPM;
unsigned long MICROSECONDS_PER_MIDI_CLOCK = MICROSECONDS_PER_BEAT / 4; // MIDI clock ticks 24 times per beat
*/
// unsigned long latimelineshifter = ((60000/19200)*pbars) ;
bool SendMidiOut;
char arranged_buttons[6][6] = {{1,  5,  9,  13, 32,  23,},
                               {2,  6,  10, 14, 33,  24,},
                               {3,  7,  11, 15, 34,  25,},
                               {4,  8,  12, 16, 35,  36,},
                               {26, 27, 28, 29, 30,  31,},
                               {17, 18, 19, 20, 21,  22}};
const unsigned short all_buttonns = 49;
int pot_assignements[all_buttonns] = {10};
int ordered_pots[15] = {10, 12, 11, 16, 15, 14, 19, 18,
                      17, 13, 24, 22, 23, 21, 20};
int potsboards[all_buttonns] = {
    2,  1,  9,  5,  4,  3,  8,  7,  6,  14, 13, 11, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0,  12, 10};
byte muxed_channels[15] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
bool recorderstop;
bool recorderrecord;
bool recorderplay;
bool started_patrecord ;
bool trace_waveform = false;
byte but_channel[all_buttonns] = {
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 8,  8,  8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 1,  1,  1};
byte but_velocity[all_buttonns] = {
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 64,  64,  64,  64,  64,  64,  64,  64,  64,  64,  64,
    64,  64,  64,  64,  64,  64,  64,  127, 127, 127};

const int mainmenufxlistsize = 10;
char consolemsg[10][32];
int waits = 0;
char pleasewaitarray[10][32];
const int fxs_count = 3;
bool pre_record = false ;
int delaymultiplier[fxs_count] = {55};
const int sizeopremixtoM = 9 * fxs_count;
const int sizeopremixWtoM = 9 * fxs_count;
const int sizeofxcords = 9 * fxs_count * 2 * 3;

bool noteprint = 0;

bool demimalmode;
bool addinglenght;

int navlevelvbuttons = 2;
const int numberofvbuttonslabels = 8;
byte vbuttonsCC[numberofvbuttonslabels + 14 + 17];
byte vPots[17] = {0};

byte tapnote = byte(3);
bool tapstarted;

byte preampleswaves = 64;
const byte szsset = 99;
const byte ssnamsize = 26;
EXTMEM char samplefoldersregistered[szsset][ssnamsize];
EXTMEM char samplebase[99][999][9];
EXTMEM int sizeofsamplefolder[99];
int sampledirsregistered = 0;
EXTMEM bool samplesselected[99][999];
EXTMEM int numberofsamplesselected[99];
EXTMEM bool samplesfoldersselected[99];
EXTMEM int numofsamplesfoldersselected = 0;

#include "/home/kosmin/HR-X/includes/AudioSetup.ino"

// current stage to configure [lebiquad] instance
const int bqstagesnum = 4;
int bqstage[fxs_count];
// [lebiquad] [stage]
EXTMEM float bqslope[fxs_count][bqstagesnum];
EXTMEM float bqgain[fxs_count][bqstagesnum];
EXTMEM float bqfreq[fxs_count][bqstagesnum];
EXTMEM int bqtype[fxs_count][bqstagesnum];
// [lebiquad] [lestage] freq slope gain
EXTMEM int bqVpot[fxs_count][bqstagesnum][3];
// max bqfreq (in Hz) wich will be multiplied by the CC (from 0 to 127) + 300Hz
// ---> because of the poor biquad response below 400hz
int bqrange = 20000;

EXTMEM char Flashsamplename[999][13];
EXTMEM char Flashsamplebase[999][9];
EXTMEM bool Flashsamplesselected[999];
int numberofFlashsamplesselected = 0;
int numberofFlashfiles = 0;
int Sampleassigned[128];
String newmkdirpath = "SOUNDSET/MABANK01" ;
EXTMEM char sampledirpath[99] = {"SOUNDSET/"};
String newloopedpath = "SOUNDSET/REC/LOOP00#L.RAW";
String newRecpathL = "SOUNDSET/REC/RECZ00#L.RAW";
String newRecpathR = "SOUNDSET/REC/RECZ00#R.RAW";
#include "/home/kosmin/HR-X/includes/images.ino"
#include "/home/kosmin/HR-X/includes/notestofrequency_442.ino"


int samplermidichannel = 8;
//0 is All, channel indexes are thus offset +1
byte synthmidichannel = 0;
bool blocked = false ;
byte navrec = 3;
int tickposition;

bool arpegiatorOn = 0;
// 8 is off
const byte arpeges_types = 8 ;
byte arpegiatortype = 8;

byte arpeglengh = 0;
byte arpegmode = 4;
byte arpegnumofnotes = 7;
byte arpegstartoffset = 0;
byte arpeggridC;

byte arpeggridS;
bool stoptickernextcycle;
byte arpegiatingNote[SYNTH_LINERS_COUNT];
bool tripletdirection[SYNTH_LINERS_COUNT];
byte playingarpegiator[SYNTH_LINERS_COUNT][SYNTH_LINERS_COUNT];
byte calledarpegenote[SYNTH_LINERS_COUNT][2];
byte tickgamme[SYNTH_LINERS_COUNT];
byte ticktriplet[SYNTH_LINERS_COUNT];
byte arpegnoteoffin[SYNTH_LINERS_COUNT][SYNTH_LINERS_COUNT] = {1};
byte arpegnotestick[SYNTH_LINERS_COUNT];
byte arpegemptyticks[SYNTH_LINERS_COUNT];
bool digitalplay = 0;


byte glidemode = 0;
byte note_before;
bool dogliding[SYNTH_LINERS_COUNT];
int freq_difference;
long unsigned int leglideposition[SYNTH_LINERS_COUNT];
int note_difference;
float glidefactor;
int time_of_last_note = 0 ;
byte lapreviousnotewCmode[SYNTH_LINERS_COUNT];
int leglidershiftCmode[SYNTH_LINERS_COUNT];
int note_differenceCmode[SYNTH_LINERS_COUNT];

byte oscillator = 0;
byte cclfoselector = 0 ;
byte ccfxlineselector = 0;

// lenght of the current interpolation
// from leinterpolstart to [1] interpole target position
byte Ccinterpolengh[128][3];

const int parsingbuffersize = 16000;
int parsinglength = parsingbuffersize;
const int pat_parser_size = 32000;

EXTMEM char receivedbitinchar[parsingbuffersize];
bool debugmidion = 0;
bool freezemidicc = 0;
bool temp_buff_armed = 0 ;


bool just_pressed_rec = false ;
int howmanyactiveccnow;
int tickerlasttick;
byte recorded_ccs[32] ;
byte pots_controllers[32][32][2];
byte activateinterpolatecc[8];
//TODO reduce size
// make class to store list and size of just the ignorable or visible CCs?
bool ignorethatcc[128];
EXTMEM GFXcanvas1 canvasBIG(128, 64);
EXTMEM GFXcanvas1 canvastitle(128, 16);

#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 7
#define SDCARD_SCK_PIN 14
// SD on audio board reader on chipSelect 10
const int chipSelect = 10;
//flash player is in 6
const int FlashChipSelect = 6;
int samplesSelected = 0;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
// I, however, use 0x3C maybe because of wire2...
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire2, OLED_RESET);

#define LOGO_HEIGHT 32
#define LOGO_WIDTH 64
Bounce clicked = Bounce(32, 100);
Encoder myEnc(30, 31);
//placeholder
#if MULTIPLEXED_PADS
Bounce Backb = Bounce( 99, 5 );
#else
Bounce Backb = Bounce( 33, 5 );
#endif
const unsigned int manyinputpins = 1;
const int inputpins[manyinputpins] = {32};
int startingnoteline;

float notefrequency = 440.0;

const int lesformes[9] PROGMEM = {
    WAVEFORM_SINE,     WAVEFORM_SAWTOOTH,          WAVEFORM_SAWTOOTH_REVERSE,
    WAVEFORM_TRIANGLE, WAVEFORM_TRIANGLE_VARIABLE, WAVEFORM_SQUARE,
    WAVEFORM_PULSE,    WAVEFORM_ARBITRARY,         WAVEFORM_SAMPLE_HOLD};


byte waveformIndex = 0 ;

EXTMEM int16_t arbitrary_waveforms[OSCS_COUNT][256] ;

byte lavalue;

#define BLUR_W_MAX_RANGE 32

static const uint8_t fake_gauss_kernel[17] = {
      0,   2,   5,  11,
     22,  40,  66, 100,
    140, 185, 220, 240,
    250, 253, 254, 255,
    255
};

int cw_change = 64;
int w_cursor_y = 32;
int w_cursor_x = 0;

const byte leschords[6][12][3] PROGMEM = {{{0, 4, 7},
                                           {1, 5, 8},
                                           {2, 6, 9},
                                           {3, 7, 10},
                                           {4, 8, 11},
                                           {5, 9, 12},
                                           {6, 10, 13},
                                           {7, 11, 14},
                                           {8, 12, 15},
                                           {9, 13, 16},
                                           {10, 14, 17},
                                           {11, 15, 18}},
                                          {{0, 3, 7},
                                           {1, 4, 8},
                                           {2, 5, 9},
                                           {3, 6, 10},
                                           {4, 7, 11},
                                           {5, 8, 12},
                                           {6, 9, 13},
                                           {7, 10, 14},
                                           {8, 11, 15},
                                           {9, 12, 16},
                                           {10, 13, 17},
                                           {11, 14, 18}},
                                          {{0, 3, 6},
                                           {1, 4, 7},
                                           {2, 5, 8},
                                           {3, 6, 9},
                                           {4, 7, 10},
                                           {5, 8, 11},
                                           {6, 9, 12},
                                           {7, 10, 13},
                                           {8, 11, 14},
                                           {9, 12, 15},
                                           {10, 13, 16},
                                           {11, 14, 17}},
                                          {{0, 4, 8},
                                           {1, 5, 9},
                                           {2, 6, 10},
                                           {3, 7, 11},
                                           {4, 8, 12},
                                           {5, 9, 13},
                                           {6, 10, 14},
                                           {7, 11, 15},
                                           {8, 12, 16},
                                           {9, 13, 17},
                                           {10, 14, 18},
                                           {11, 15, 19}},
                                          {{0, 2, 7},
                                           {1, 3, 8},
                                           {2, 4, 9},
                                           {3, 5, 10},
                                           {4, 6, 11},
                                           {5, 7, 12},
                                           {6, 8, 13},
                                           {7, 9, 14},
                                           {8, 10, 15},
                                           {9, 11, 16},
                                           {10, 12, 17},
                                           {11, 13, 18}},
                                          {{0, 5, 7},
                                           {1, 6, 8},
                                           {2, 7, 9},
                                           {3, 8, 10},
                                           {4, 9, 11},
                                           {5, 10, 12},
                                           {6, 11, 13},
                                           {7, 12, 14},
                                           {8, 13, 15},
                                           {9, 14, 16},
                                           {10, 15, 17},
                                           {11, 16, 18}}};

// C Ionian     { C maj;  D min;  E min;  F maj;  G maj;  A min;  B dim  }
// const chord ionian[7]     = {{0, maj},    {2, minor}, {4, minor}, {5, maj},
// {7, maj},   {9, minor}, {11, dim}};
//                            {0,4,7} ,   {2,5,9},    {4,7,11}    {5,9,12},
//                            {7,11,14},   {9,12,16}, {11,14,17}
const byte *event_ionian[7] = {
    leschords[0][0], leschords[1][2], leschords[1][4], leschords[0][5],
    leschords[0][7], leschords[1][9], leschords[2][11]};
// C Dorian     { C min;  D min;  D♯ maj; F maj;  G min;  A dim;  A♯ maj  }
// const chord dorian[7]     = {{0, minor},  {2, minor}, {3, maj},   {5, maj},
// {7, minor}, {9, dim},   {10, maj}};
const byte *event_dorian[7] = {
    leschords[1][0], leschords[1][2], leschords[0][3], leschords[0][5],
    leschords[1][7], leschords[2][9], leschords[0][10]};
// C Phrygian    { C min;  C♯ maj; D♯ maj; F min;  G dim;  G♯ maj; A♯ min  }
// const chord phrygian[7]   = {{0, minor},  {1, maj},   {3, maj},   {5, minor},
// {7, dim},   {8, maj},   {10, minor}};
const byte *event_phrygian[7] = {
    leschords[1][0], leschords[0][1], leschords[0][3], leschords[1][5],
    leschords[2][7], leschords[0][8], leschords[1][10]};
// C Lydian      { C maj;  D maj;  E min;  F♯ dim; G maj;  A min;  B min   }
// const chord lydian[7]     = {{0, maj},    {2, maj},   {4, minor}, {6, dim},
// {7, maj},   {9, minor}, {11, minor}};
const byte *event_lydian[7] = {
    leschords[0][0], leschords[0][2], leschords[1][4], leschords[2][6],
    leschords[0][7], leschords[1][9], leschords[1][11]};
// C Mixolydian  { C maj;  D min;  E dim;  F maj;  G min;  A min;  A♯ maj  }
const byte *event_mixolydian[7] = {
    leschords[0][0], leschords[1][2], leschords[2][4], leschords[0][5],
    leschords[1][7], leschords[1][9], leschords[0][10]};
// const chord mixolydian[7] = {{0, maj},    {2, minor}, {4, dim},   {5, maj},
// {7, minor}, {9, minor}, {10, maj}}; C Aeolian     { C min;  D dim;  D♯ maj; F
// min;  G min;  G♯ maj; A♯ maj  } const chord aeolian[7]    = {{0, minor},  {2,
// dim},   {3, maj},   {5, minor}, {7, minor}, {8, maj},   {10, maj}};
const byte *event_aeolian[7] = {
    leschords[1][0], leschords[2][2], leschords[0][3], leschords[1][5],
    leschords[1][7], leschords[0][8], leschords[0][10]};
// C harmonic    { C min;  D dim;  D♯ aug; F min;  G maj;  G♯ maj; B dim   }
// const chord harmonic[7]   = {{0, minor},  {2, dim},   {3, aug},   {5, minor},
// {7, maj},   {8, maj},   {11, dim}};
const byte *event_harmonic[7] = {
    leschords[1][0], leschords[2][2], leschords[3][3], leschords[1][5],
    leschords[0][7], leschords[0][8], leschords[2][11]};
// C Locrian     { C dim;  C♯ maj; D♯ min; F min;  F♯ maj; G♯ maj; A♯ min  }
// const chord locrian[7]    = {{0, dim},    {1, maj},   {3, minor}, {5, minor},
// {6, maj},   {8, maj},   {10, minor}};
const byte *event_locrian[7] = {
    leschords[2][0], leschords[0][1], leschords[1][3], leschords[1][5],
    leschords[0][6], leschords[0][8], leschords[1][10]};
// const chord *all_chords[8] = {ionian, dorian, phrygian, lydian, mixolydian,
// aeolian, harmonic, locrian};
const byte **all_arpegios[arpeges_types] = {
    event_ionian,     event_dorian,  event_phrygian, event_lydian,
    event_mixolydian, event_aeolian, event_harmonic, event_locrian};

bool chordson = 0;
byte chordnotes[3];
byte chordnotesoff[3];
// 6 is off
byte lasetchord = 6;

const byte synth_params_count = 8;

int phaselevelsL[OSCS_COUNT] = {0, 0, 0};

int LFOphase[OSCS_COUNT] = {0,0,0};


byte LFOmenuroot = 2;
//50 is center 0 for -1  +1 range
int LFOoffset[OSCS_COUNT] = {50,50,50};
byte LFOformstype[OSCS_COUNT] = {0, 0, 0};
byte LFOfreqs[OSCS_COUNT] = {100,100,100};
byte LFOlevel[OSCS_COUNT] = {0,0,0};
bool LFOsync[OSCS_COUNT] = {0,0,0};
//64 is center 0 for -1  +1 range
byte wave1offset[OSCS_COUNT] = {64,64,64};

// File originefile ;
int adsrlevels[6] = {0, 5, 0, 50, 100, 750};

int navleveloverwrite = 2;
int knobiprev[OSCS_COUNT] = {0, 0, 0};

#include "pads.h"
Pads Pads;

char mainmenufxlist[mainmenufxlistsize][12] = {
      "Multiply", "Reverb", "Granular", "BitCrusher", "Flanger",
      "Chorus",   "Biquad", "Filter",   "Delay",      "None"};

byte WetMixMasters[4] = {0, 0, 0, 0};

bool stereo_toggled = false ;

const CcCalls ctl[] = {{"Disabled",nullptr},{"Volume",&Volume_ctl},{"SynthLevel",&SynthVolume_ctl},{"SDLevel",&SDPlayerVolume_ctl},{"FlashLevel",&FlashVolume_ctl},
                      {"FX1 Wet",&Wet1Volume_ctl},{"FX2 Wet",&Wet2Volume_ctl},{"FX3 Wet",&Wet3Volume_ctl},{"Dry Sampler",&DrySampler_ctl},{"Dry Synth",&DrySynth_ctl},
                      //10 ok
                      {"Dry Audio In",&DryAudioIn_ctl},{"CutOff slp.",&Slope1_ctl},{"Reso slp.",&Slope2_ctl},{"Reso Tweak",&ResoTweak_ctl},{"Filter303 Oct.",&Filter303Octave_ctl},
                      {"CutOff Tweak",&CutOffTweak_ctl},{"Stereo On",toggle_stereo},{"Stereo Off",turn_off_stereo},{"Filter303 Lvl.",&Filter303_ctl},{"Filter303 Glide",&Filter303Glide_ctl},
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
                      {"Debug CPU",&DebugCPU_Toggle_ctl},{"Set BPMs",&SetBPMs_ctl},{"Save New Pattern",&SaveToNewPattern_Trigger_ctl},{"Load First Pattern",&LoadFirstPattern_Trigger_ctl},{"Record Audio",&RecordAudio_Trigger_ctl},
                      {"Play Record",&PlayLoadedAudio_Trigger_ctl},{"Stop Recording",&StopRecording_Trigger_ctl},{"Load First Preset",&LoadFirstPreset_Toggle_ctl},{"Arb[] MaxF",&ArbitraryMaxF_ctl},{"Merge Patterns",&MergeSynthPatterns_Trigger_ctl},
                      //120 ok
                      {"Flash Line1 Level",&FlashLineVolume_Knob1_ctl},{"Flash Line2 Level",&FlashLineVolume_Knob2_ctl},{"Flash Line3 Level",&FlashLineVolume_Knob3_ctl},{"Flash Line4 Level",&FlashLineVolume_Knob4_ctl},{"Flash Line5 Level",&FlashLineVolume_Knob5_ctl},
                      {"Flash Line6 Level",&FlashLineVolume_Knob6_ctl},{"Flash Line7 Level",&FlashLineVolume_Knob7_ctl},{"Flash Line8 Level",&FlashLineVolume_Knob8_ctl},{"Flash Line9 Level",&FlashLineVolume_Knob9_ctl},{"Flash Line10 Level",&FlashLineVolume_Knob10_ctl},
                      //130 ok
                      {"Flash Line11 Level",&FlashLineVolume_Knob11_ctl},{"Flash Line12 Level",&FlashLineVolume_Knob12_ctl},{"Flash Line13 Level",&FlashLineVolume_Knob13_ctl},{"Flash Line14 Level",&FlashLineVolume_Knob14_ctl},{"Flash Line15 Level",&FlashLineVolume_Knob15_ctl},
                      {"Flash Line16 Level",&FlashLineVolume_Knob16_ctl},{"start oscilloscope",&start_spectro},{"stop oscilloscope",&stop_spectro},{"USB In Volume",&USB_In_Volume_ctl},{"Fps oscilloscope",&adjust_osc_framerate_ctl},
                      //140 ok
                      {"Time oscilloscope",&adjust_osc_timee_ctl},{"refresh OscScope",&adjust_osc_refresher_period_ctl},{"Wav Editor Pitch",&adjust_waveEditor_pitch_ctl}  

                      };

constexpr uint16_t CtlCount = sizeof(ctl) / sizeof(ctl[0]);

bool patterninparse;

bool granular_shifting[fxs_count] = {0,0,0};
bool granular_freezing[fxs_count] = {0,0,0};
short lecaractere;
short linerpat;

bool debug_cpu = false;
byte bitcrusherVknobs[fxs_count][2];
byte granularVknobs[fxs_count][2];
byte flangerVknobs[fxs_count][3];
byte delayVknobs[fxs_count][3];
byte chorusVknobs[fxs_count];
byte reverbVknobs[fxs_count][2];
File dummy_flash_file ;
File dummyier_file ;
// char* filespath[] = {(char*)"/",};
//tracks of the sequencer
const int sizeofsoundlines = 4;
char soundlines[sizeofsoundlines][12] = {"Synth", "Sampler", "AudioIn",
                                         "SDcard"};
// 4 is none
int LFOonfilterz[fxs_count] = {3,3,3};
// fq res oct 127
byte ffilterzVknobs[fxs_count][3];
// LP BP HP 127
int mixffilterzVknobs[fxs_count][3];

float filterzgainz[fxs_count][3];

float filterzfreq[fxs_count];
float filterzreso[fxs_count] = {0.7};
float filterzoctv[fxs_count];

int filterzrange = 14000;
byte SD_Player_note = 65;
char masterlabels[3][3] = {"m", "w", "s"};

// int shifts ;
int navlevel = 0;
int previousnavlevel = 0;

int ypos;

int navrange = 2; // starts at 0

byte wetins[3]={64,64,64};

char lastpathlisted[50];
// char menuitem ;

int midiknobs[128];

int sublevels[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

float wavesfreqs[OSCS_COUNT] = {1.0, 1.0, 0.5};
float panLs[OSCS_COUNT] = {1, 1, 1};

byte mixlevelsL[OSCS_COUNT] = {126, 64, 64};
// 0 master , 1synth, 2 sampler, 3 unused
byte mixlevelsM[4] = {127, 127, 38, 127};

unsigned int Waveformstyped[OSCS_COUNT] = {1, 0, 1};
byte samplesnotesOn[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

AudioEffectEnvelope *enveloppesL[SYNTH_LINERS_COUNT] = {&envelopeL0, &envelopeL1, &envelopeL2,
                                                     &envelopeL3, &envelopeL4, &envelopeL5};

// modulator for 303 mode
float ladiff1;
float ladiff2;
int letbfreq;

Adafruit_SSD1306 display(128, 64, &Wire2, -1);
char *toprint = (char *)"Cosmix";

bool initdone;
byte FMmodulated[OSCS_COUNT] = {0,0,0};
#include "/home/kosmin/HR-X/includes/cablages.ino"

#define FLANGE_DELAY_LENGTH (6 * AUDIO_BLOCK_SAMPLES)
#define CHORUS_DELAY_LENGTH (16 * AUDIO_BLOCK_SAMPLES)
EXTMEM short chorusdelayline[CHORUS_DELAY_LENGTH];
EXTMEM short chorusdelayline2[CHORUS_DELAY_LENGTH];
EXTMEM short chorusdelayline3[CHORUS_DELAY_LENGTH];

short *chorusdelaylines[3] = {chorusdelayline,chorusdelayline2,chorusdelayline3};
// short chorusdelayline4[CHORUS_DELAY_LENGTH];
int chorusvoices[3] = {2,2,2};

EXTMEM short flangedelay[FLANGE_DELAY_LENGTH];
EXTMEM short flangedelay2[FLANGE_DELAY_LENGTH];
EXTMEM short flangedelay3[FLANGE_DELAY_LENGTH];

short *flangedelays[3] = {flangedelay,flangedelay2,flangedelay3};
// short flangedelay4[FLANGE_DELAY_LENGTH];

int flangeoffset = FLANGE_DELAY_LENGTH / 4;
int flangedepth = FLANGE_DELAY_LENGTH / 4;

double flangefreq[3] = {0.5,0.5,0.5};

String mp3_name = "MP3/Addict.mp3";
String mp3_dir = "MP3/";
bool mp3_paused ;
bool mp3_shuffle ;
int file_index = 0 ;
int next_mp3 = 0 ;
int previous_mp3 = 0 ;


byte mp3_ext ;
bool mp3_continue;

#define GRANULAR_MEMORY_SIZE 12800
// 12800 is for 290 ms at 44.1 kHz
EXTMEM short granularMemory[GRANULAR_MEMORY_SIZE];
EXTMEM short granularMemory2[GRANULAR_MEMORY_SIZE];
EXTMEM short granularMemory3[GRANULAR_MEMORY_SIZE];

short *granularMemories[3] = {granularMemory,granularMemory2,granularMemory3};

EXTMEM AudioConnection delayCord1(feedbackdelay1, delay1);
EXTMEM AudioConnection delayCord2(feedbackdelay2, delay2);
EXTMEM AudioConnection delayCord3(feedbackdelay3, delay3);

EXTMEM AudioConnection Notespy_cable(ampL, notefreq1);

EXTMEM AudioConnection FMWaveCord01(FMWaveform1L1, 0, WavesL1, 0);
EXTMEM AudioConnection FMWaveCord02(FMWaveform1L2, 0, WavesL2, 0);
EXTMEM AudioConnection FMWaveCord03(FMWaveform1L3, 0, WavesL3, 0);
EXTMEM AudioConnection FMWaveCord04(FMWaveform1L4, 0, WavesL4, 0);
EXTMEM AudioConnection FMWaveCord05(FMWaveform1L5, 0, WavesL5, 0);
EXTMEM AudioConnection FMWaveCord06(FMWaveform1L6, 0, WavesL6, 0);

EXTMEM AudioConnection FMWaveCord09(FMWaveform2L1, 0, WavesL1, 1);
EXTMEM AudioConnection FMWaveCord10(FMWaveform2L2, 0, WavesL2, 1);
EXTMEM AudioConnection FMWaveCord11(FMWaveform2L3, 0, WavesL3, 1);
EXTMEM AudioConnection FMWaveCord12(FMWaveform2L4, 0, WavesL4, 1);
EXTMEM AudioConnection FMWaveCord13(FMWaveform2L5, 0, WavesL5, 1);
EXTMEM AudioConnection FMWaveCord14(FMWaveform2L6, 0, WavesL6, 1);

EXTMEM AudioConnection FMWaveCord17(FMWaveform3L1, 0, WavesL1, 2);
EXTMEM AudioConnection FMWaveCord18(FMWaveform3L2, 0, WavesL2, 2);
EXTMEM AudioConnection FMWaveCord19(FMWaveform3L3, 0, WavesL3, 2);
EXTMEM AudioConnection FMWaveCord20(FMWaveform3L4, 0, WavesL4, 2);
EXTMEM AudioConnection FMWaveCord21(FMWaveform3L5, 0, WavesL5, 2);
EXTMEM AudioConnection FMWaveCord22(FMWaveform3L6, 0, WavesL6, 2);

EXTMEM AudioConnection stringCord01(string1L1, 0, WavesL1, 0);
EXTMEM AudioConnection stringCord02(string1L2, 0, WavesL2, 0);
EXTMEM AudioConnection stringCord03(string1L3, 0, WavesL3, 0);
EXTMEM AudioConnection stringCord04(string1L4, 0, WavesL4, 0);
EXTMEM AudioConnection stringCord05(string1L5, 0, WavesL5, 0);
EXTMEM AudioConnection stringCord06(string1L6, 0, WavesL6, 0);

EXTMEM AudioConnection stringCord09(string2L1, 0, WavesL1, 1);
EXTMEM AudioConnection stringCord10(string2L2, 0, WavesL2, 1);
EXTMEM AudioConnection stringCord11(string2L3, 0, WavesL3, 1);
EXTMEM AudioConnection stringCord12(string2L4, 0, WavesL4, 1);
EXTMEM AudioConnection stringCord13(string2L5, 0, WavesL5, 1);
EXTMEM AudioConnection stringCord14(string2L6, 0, WavesL6, 1);

EXTMEM AudioConnection stringCord17(string3L1, 0, WavesL1, 2);
EXTMEM AudioConnection stringCord18(string3L2, 0, WavesL2, 2);
EXTMEM AudioConnection stringCord19(string3L3, 0, WavesL3, 2);
EXTMEM AudioConnection stringCord20(string3L4, 0, WavesL4, 2);
EXTMEM AudioConnection stringCord21(string3L5, 0, WavesL5, 2);
EXTMEM AudioConnection stringCord22(string3L6, 0, WavesL6, 2);

EXTMEM AudioConnection drumCord01(drum1L1, 0, WavesL1, 0);
EXTMEM AudioConnection drumCord02(drum1L2, 0, WavesL2, 0);
EXTMEM AudioConnection drumCord03(drum1L3, 0, WavesL3, 0);
EXTMEM AudioConnection drumCord04(drum1L4, 0, WavesL4, 0);
EXTMEM AudioConnection drumCord05(drum1L5, 0, WavesL5, 0);
EXTMEM AudioConnection drumCord06(drum1L6, 0, WavesL6, 0);

EXTMEM AudioConnection drumCord09(drum2L1, 0, WavesL1, 1);
EXTMEM AudioConnection drumCord10(drum2L2, 0, WavesL2, 1);
EXTMEM AudioConnection drumCord11(drum2L3, 0, WavesL3, 1);
EXTMEM AudioConnection drumCord12(drum2L4, 0, WavesL4, 1);
EXTMEM AudioConnection drumCord13(drum2L5, 0, WavesL5, 1);
EXTMEM AudioConnection drumCord14(drum2L6, 0, WavesL6, 1);

EXTMEM AudioConnection drumCord17(drum3L1, 0, WavesL1, 2);
EXTMEM AudioConnection drumCord18(drum3L2, 0, WavesL2, 2);
EXTMEM AudioConnection drumCord19(drum3L3, 0, WavesL3, 2);
EXTMEM AudioConnection drumCord20(drum3L4, 0, WavesL4, 2);
EXTMEM AudioConnection drumCord21(drum3L5, 0, WavesL5, 2);
EXTMEM AudioConnection drumCord22(drum3L6, 0, WavesL6, 2);

EXTMEM AudioConnection wavelinecord19(waveform1L5, 0, WavesL5, 0);
EXTMEM AudioConnection wavelinecord20(waveform1L6, 0, WavesL6, 0);
EXTMEM AudioConnection wavelinecord21(waveform1L4, 0, WavesL4, 0);
EXTMEM AudioConnection wavelinecord22(waveform1L2, 0, WavesL2, 0);
EXTMEM AudioConnection wavelinecord23(waveform1L3, 0, WavesL3, 0);
EXTMEM AudioConnection wavelinecord24(waveform1L1, 0, WavesL1, 0);

EXTMEM AudioConnection wavelinecord33(waveform2L5, 0, WavesL5, 1);
EXTMEM AudioConnection wavelinecord34(waveform3L5, 0, WavesL5, 2);
EXTMEM AudioConnection wavelinecord35(waveform2L6, 0, WavesL6, 1);
EXTMEM AudioConnection wavelinecord36(waveform3L6, 0, WavesL6, 2);
EXTMEM AudioConnection wavelinecord37(waveform3L3, 0, WavesL3, 2);
EXTMEM AudioConnection wavelinecord39(waveform2L3, 0, WavesL3, 1);
EXTMEM AudioConnection wavelinecord41(waveform2L4, 0, WavesL4, 1);
EXTMEM AudioConnection wavelinecord42(waveform3L4, 0, WavesL4, 2);
EXTMEM AudioConnection wavelinecord43(waveform3L2, 0, WavesL2, 2);
EXTMEM AudioConnection wavelinecord44(waveform3L1, 0, WavesL1, 2);
EXTMEM AudioConnection wavelinecord45(waveform2L2, 0, WavesL2, 1);
EXTMEM AudioConnection wavelinecord47(waveform2L1, 0, WavesL1, 1);

EXTMEM AudioConnection modulateCord01(modulate1L1, 0, WavesL1, 0);
EXTMEM AudioConnection modulateCord02(modulate1L2, 0, WavesL2, 0);
EXTMEM AudioConnection modulateCord03(modulate1L3, 0, WavesL3, 0);
EXTMEM AudioConnection modulateCord04(modulate1L4, 0, WavesL4, 0);
EXTMEM AudioConnection modulateCord05(modulate1L5, 0, WavesL5, 0);
EXTMEM AudioConnection modulateCord06(modulate1L6, 0, WavesL6, 0);
EXTMEM AudioConnection modulateCord09(modulate2L1, 0, WavesL1, 1);
EXTMEM AudioConnection modulateCord10(modulate2L2, 0, WavesL2, 1);
EXTMEM AudioConnection modulateCord11(modulate2L3, 0, WavesL3, 1);
EXTMEM AudioConnection modulateCord12(modulate2L4, 0, WavesL4, 1);
EXTMEM AudioConnection modulateCord13(modulate2L5, 0, WavesL5, 1);
EXTMEM AudioConnection modulateCord14(modulate2L6, 0, WavesL6, 1);
EXTMEM AudioConnection modulateCord17(modulate3L1, 0, WavesL1, 2);
EXTMEM AudioConnection modulateCord18(modulate3L2, 0, WavesL2, 2);
EXTMEM AudioConnection modulateCord19(modulate3L3, 0, WavesL3, 2);
EXTMEM AudioConnection modulateCord20(modulate3L4, 0, WavesL4, 2);
EXTMEM AudioConnection modulateCord21(modulate3L5, 0, WavesL5, 2);
EXTMEM AudioConnection modulateCord22(modulate3L6, 0, WavesL6, 2);

EXTMEM AudioConnection MDwaveCord01(waveform1L1, 0, modulate1L1, 0);
EXTMEM AudioConnection MDwaveCord02(waveform1L2, 0, modulate1L2, 0);
EXTMEM AudioConnection MDwaveCord03(waveform1L3, 0, modulate1L3, 0);
EXTMEM AudioConnection MDwaveCord04(waveform1L4, 0, modulate1L4, 0);
EXTMEM AudioConnection MDwaveCord05(waveform1L5, 0, modulate1L5, 0);
EXTMEM AudioConnection MDwaveCord06(waveform1L6, 0, modulate1L6, 0);

EXTMEM AudioConnection MDwaveCord09(waveform2L1, 0, modulate2L1, 0);
EXTMEM AudioConnection MDwaveCord10(waveform2L2, 0, modulate2L2, 0);
EXTMEM AudioConnection MDwaveCord11(waveform2L3, 0, modulate2L3, 0);
EXTMEM AudioConnection MDwaveCord12(waveform2L4, 0, modulate2L4, 0);
EXTMEM AudioConnection MDwaveCord13(waveform2L5, 0, modulate2L5, 0);
EXTMEM AudioConnection MDwaveCord14(waveform2L6, 0, modulate2L6, 0);

EXTMEM AudioConnection MDwaveCord17(waveform3L1, 0, modulate3L1, 0);
EXTMEM AudioConnection MDwaveCord18(waveform3L2, 0, modulate3L2, 0);
EXTMEM AudioConnection MDwaveCord19(waveform3L3, 0, modulate3L3, 0);
EXTMEM AudioConnection MDwaveCord20(waveform3L4, 0, modulate3L4, 0);
EXTMEM AudioConnection MDwaveCord21(waveform3L5, 0, modulate3L5, 0);
EXTMEM AudioConnection MDwaveCord22(waveform3L6, 0, modulate3L6, 0);



EXTMEM AudioConnection MDdrumCord01(drum1L1, 0, modulate1L1, 0);
EXTMEM AudioConnection MDdrumCord02(drum1L2, 0, modulate1L2, 0);
EXTMEM AudioConnection MDdrumCord03(drum1L3, 0, modulate1L3, 0);
EXTMEM AudioConnection MDdrumCord04(drum1L4, 0, modulate1L4, 0);
EXTMEM AudioConnection MDdrumCord05(drum1L5, 0, modulate1L5, 0);
EXTMEM AudioConnection MDdrumCord06(drum1L6, 0, modulate1L6, 0);

EXTMEM AudioConnection MDdrumCord09(drum2L1, 0, modulate2L1, 0);
EXTMEM AudioConnection MDdrumCord10(drum2L2, 0, modulate2L2, 0);
EXTMEM AudioConnection MDdrumCord11(drum2L3, 0, modulate2L3, 0);
EXTMEM AudioConnection MDdrumCord12(drum2L4, 0, modulate2L4, 0);
EXTMEM AudioConnection MDdrumCord13(drum2L5, 0, modulate2L5, 0);
EXTMEM AudioConnection MDdrumCord14(drum2L6, 0, modulate2L6, 0);

EXTMEM AudioConnection MDdrumCord17(drum3L1, 0, modulate3L1, 0);
EXTMEM AudioConnection MDdrumCord18(drum3L2, 0, modulate3L2, 0);
EXTMEM AudioConnection MDdrumCord19(drum3L3, 0, modulate3L3, 0);
EXTMEM AudioConnection MDdrumCord20(drum3L4, 0, modulate3L4, 0);
EXTMEM AudioConnection MDdrumCord21(drum3L5, 0, modulate3L5, 0);
EXTMEM AudioConnection MDdrumCord22(drum3L6, 0, modulate3L6, 0);

EXTMEM AudioConnection MDstringCord01(string1L1, 0, modulate1L1, 0);
EXTMEM AudioConnection MDstringCord02(string1L2, 0, modulate1L2, 0);
EXTMEM AudioConnection MDstringCord03(string1L3, 0, modulate1L3, 0);
EXTMEM AudioConnection MDstringCord04(string1L4, 0, modulate1L4, 0);
EXTMEM AudioConnection MDstringCord05(string1L5, 0, modulate1L5, 0);
EXTMEM AudioConnection MDstringCord06(string1L6, 0, modulate1L6, 0);

EXTMEM AudioConnection MDstringCord09(string2L1, 0, modulate2L1, 0);
EXTMEM AudioConnection MDstringCord10(string2L2, 0, modulate2L2, 0);
EXTMEM AudioConnection MDstringCord11(string2L3, 0, modulate2L3, 0);
EXTMEM AudioConnection MDstringCord12(string2L4, 0, modulate2L4, 0);
EXTMEM AudioConnection MDstringCord13(string2L5, 0, modulate2L5, 0);
EXTMEM AudioConnection MDstringCord14(string2L6, 0, modulate2L6, 0);

EXTMEM AudioConnection MDstringCord17(string3L1, 0, modulate3L1, 0);
EXTMEM AudioConnection MDstringCord18(string3L2, 0, modulate3L2, 0);
EXTMEM AudioConnection MDstringCord19(string3L3, 0, modulate3L3, 0);
EXTMEM AudioConnection MDstringCord20(string3L4, 0, modulate3L4, 0);
EXTMEM AudioConnection MDstringCord21(string3L5, 0, modulate3L5, 0);
EXTMEM AudioConnection MDstringCord22(string3L6, 0, modulate3L6, 0);

AudioConnection *delayCords[3] = {&delayCord1, &delayCord2, &delayCord3};

AudioConnection *stringcords1[SYNTH_LINERS_COUNT*OSCS_COUNT] = {
    &stringCord01, &stringCord02, &stringCord03, &stringCord04, &stringCord05, &stringCord06,
    &stringCord09, &stringCord10, &stringCord11, &stringCord12, &stringCord13, &stringCord14,
    &stringCord17, &stringCord18, &stringCord19, &stringCord20, &stringCord21, &stringCord22};

AudioConnection *drumcords1[SYNTH_LINERS_COUNT*OSCS_COUNT] = {
    &drumCord01, &drumCord02, &drumCord03, &drumCord04, &drumCord05, &drumCord06,
    &drumCord09, &drumCord10, &drumCord11, &drumCord12, &drumCord13, &drumCord14,
    &drumCord17, &drumCord18, &drumCord19, &drumCord20, &drumCord21, &drumCord22};

AudioConnection *modulatecords1[SYNTH_LINERS_COUNT*OSCS_COUNT] = {
    &modulateCord01, &modulateCord02, &modulateCord03, &modulateCord04, &modulateCord05, &modulateCord06,
    &modulateCord09, &modulateCord10, &modulateCord11, &modulateCord12, &modulateCord13, &modulateCord14,
    &modulateCord17, &modulateCord18, &modulateCord19, &modulateCord20, &modulateCord21, &modulateCord22};

AudioConnection *MDdrumcords1[SYNTH_LINERS_COUNT*OSCS_COUNT] = {
    &MDdrumCord01, &MDdrumCord02, &MDdrumCord03, &MDdrumCord04, &MDdrumCord05, &MDdrumCord06,
    &MDdrumCord09, &MDdrumCord10, &MDdrumCord11, &MDdrumCord12, &MDdrumCord13, &MDdrumCord14,
    &MDdrumCord17, &MDdrumCord18, &MDdrumCord19, &MDdrumCord20, &MDdrumCord21, &MDdrumCord22};

AudioConnection *MDwavecords1[SYNTH_LINERS_COUNT*OSCS_COUNT] = {
    &MDwaveCord01, &MDwaveCord02, &MDwaveCord03, &MDwaveCord04, &MDwaveCord05, &MDwaveCord06,
    &MDwaveCord09, &MDwaveCord10, &MDwaveCord11, &MDwaveCord12, &MDwaveCord13, &MDwaveCord14,
    &MDwaveCord17, &MDwaveCord18, &MDwaveCord19, &MDwaveCord20, &MDwaveCord21, &MDwaveCord22};

AudioConnection *MDstringcords1[SYNTH_LINERS_COUNT*OSCS_COUNT] = {
    &MDstringCord01, &MDstringCord02, &MDstringCord03, &MDstringCord04, &MDstringCord05, &MDstringCord06,
    &MDstringCord09, &MDstringCord10, &MDstringCord11, &MDstringCord12, &MDstringCord13, &MDstringCord14,
    &MDstringCord17, &MDstringCord18, &MDstringCord19, &MDstringCord20, &MDstringCord21, &MDstringCord22};

AudioConnection *FMwavecords1[SYNTH_LINERS_COUNT*OSCS_COUNT] = {
    &FMWaveCord01, &FMWaveCord02, &FMWaveCord03, &FMWaveCord04, &FMWaveCord05, &FMWaveCord06,
    &FMWaveCord09, &FMWaveCord10, &FMWaveCord11, &FMWaveCord12, &FMWaveCord13, &FMWaveCord14,
    &FMWaveCord17, &FMWaveCord18, &FMWaveCord19, &FMWaveCord20, &FMWaveCord21, &FMWaveCord22};

AudioConnection *wavelinescords[SYNTH_LINERS_COUNT*OSCS_COUNT] = {
    &wavelinecord24, &wavelinecord22, &wavelinecord23, &wavelinecord21, &wavelinecord19, &wavelinecord20,
    &wavelinecord47, &wavelinecord45, &wavelinecord39, &wavelinecord41, &wavelinecord33, &wavelinecord35,
    &wavelinecord44, &wavelinecord43, &wavelinecord37, &wavelinecord42, &wavelinecord34, &wavelinecord36};

AudioSynthWaveform *waveforms1[SYNTH_LINERS_COUNT*OSCS_COUNT] = {
    &waveform1L1, &waveform1L2, &waveform1L3, &waveform1L4, &waveform1L5, &waveform1L6,
    &waveform2L1, &waveform2L2, &waveform2L3, &waveform2L4, &waveform2L5, &waveform2L6,
    &waveform3L1, &waveform3L2, &waveform3L3, &waveform3L4, &waveform3L5, &waveform3L6};

AudioSynthWaveformModulated *FMwaveforms1[SYNTH_LINERS_COUNT*OSCS_COUNT] = {
    &FMWaveform1L1, &FMWaveform1L2, &FMWaveform1L3, &FMWaveform1L4, &FMWaveform1L5, &FMWaveform1L6,
    &FMWaveform2L1, &FMWaveform2L2, &FMWaveform2L3, &FMWaveform2L4, &FMWaveform2L5, &FMWaveform2L6,
    &FMWaveform3L1, &FMWaveform3L2, &FMWaveform3L3, &FMWaveform3L4, &FMWaveform3L5, &FMWaveform3L6};

AudioSynthSimpleDrum *drums1[SYNTH_LINERS_COUNT*OSCS_COUNT] = {
    &drum1L1, &drum1L2, &drum1L3, &drum1L4, &drum1L5, &drum1L6,
    &drum2L1, &drum2L2, &drum2L3, &drum2L4, &drum2L5, &drum2L6,
    &drum3L1, &drum3L2, &drum3L3, &drum3L4, &drum3L5, &drum3L6};

AudioSynthKarplusStrong *strings1[SYNTH_LINERS_COUNT*OSCS_COUNT] = {
    &string1L1, &string1L2, &string1L3, &string1L4, &string1L5, &string1L6,
    &string2L1, &string2L2, &string2L3, &string2L4,&string2L5, &string2L6,
    &string3L1, &string3L2, &string3L3, &string3L4, &string3L5, &string3L6};

AudioMixer4 *Wavesmix[SYNTH_LINERS_COUNT] = {&WavesL1, &WavesL2, &WavesL3, &WavesL4, &WavesL5, &WavesL6};

AudioPlayLittleSerialflashRaw *FlashSampler[16] = {
    &FlashSampler1,  &FlashSampler2,  &FlashSampler3,  &FlashSampler4,
    &FlashSampler5,  &FlashSampler6,  &FlashSampler7,  &FlashSampler8,
    &FlashSampler9,  &FlashSampler10, &FlashSampler11, &FlashSampler12,
    &FlashSampler13, &FlashSampler14, &FlashSampler15, &FlashSampler16};

AudioMixer4 *Flashmixer[4] = {&flashmix1, &flashmix2, &flashmix3, &flashmix4};

AudioAmplifier *Wavespreamp303[SYNTH_LINERS_COUNT] = {&wavePAmp0, &wavePAmp1, &wavePAmp2,
                                     &wavePAmp3, &wavePAmp4, &wavePAmp5};

AudioSynthWaveform *LFOwaveforms1[OSCS_COUNT] = {&LFOrm1, &LFOrm2, &LFOrm3};
//
SequencerClocker clocker;

class ClockSink : public AudioStream {
    public:
        ClockSink() : AudioStream(1, inputQueueArray) {}

        void update(void) override {}

    private:
    audio_block_t *inputQueueArray[1];
};

ClockSink sink;

EXTMEM AudioConnection patchCord_sinker(clocker, 0, sink, 0);

DisplayManager dm = DisplayManager();
GlobalMixer _mx = GlobalMixer(audioShield);

int rota_true_pos = 0;

void returntonav(byte lelevel, byte lanavrange = navrange,byte t_vraipos = rota_true_pos) {
    //never returntonav home
  navlevel = lelevel;
  rota_true_pos = t_vraipos;
  myEnc.write(rota_true_pos * 4);
  navrange = lanavrange;
  if (navlevel)
    dm.show();
}

AudioPlaySdMp3           playMp31;
AudioPlaySdFlac          playFlac1;

EXTMEM AudioPlayPartialSdRaw PartialPlayerMono;
EXTMEM AudioMixer4 sd_mixerL ;
EXTMEM AudioMixer4 sd_mixerR ;

EXTMEM AudioConnection          sd_mix_itL(sd_mixerL, 0, InMixL , 2);
EXTMEM AudioConnection          sd_mix_itR(sd_mixerR, 0, InMixR , 2);
EXTMEM AudioConnection          sd_mix_partialL(PartialPlayerMono, 0, sd_mixerL, 0);
EXTMEM AudioConnection          sd_mix_partialR(PartialPlayerMono, 0, sd_mixerR, 0);
EXTMEM AudioConnection          sd_mix_mp3L(playMp31, 0, sd_mixerL, 1);
EXTMEM AudioConnection          sd_mix_mp3R(playMp31, 1, sd_mixerR, 1);
EXTMEM AudioConnection          sd_mix_flacL(playFlac1, 0, sd_mixerL, 2);
EXTMEM AudioConnection          sd_mix_flacR(playFlac1, 1, sd_mixerR, 2);


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
                //thirtySecond++;
                _callback_3();
            }
            if ((tick96 % 96*4) == 0 && _callback_long){
                //quarter++;
                _callback_long();
            }
            if ((tick96 % 2) == 0 && _callback_16){
                //eighth++;
                _callback_16();
            }
            if (!self->stop) {
                if ((tick96 % 24) == 0 && _callback_24){
                    //sixteenth++;
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
            //if (!externalticker) {
            stoptick = 0;
            self->stop = 0;
            patternOn = 1;
        }

    private:

        volatile uint32_t tick96 = 0;
        //volatile uint32_t quarter = 0;
        //volatile uint32_t eighth = 0;
        //volatile uint32_t sixteenth = 0;
        //volatile uint32_t thirtySecond = 0;
        void (*_callback_24)() = nullptr;
        void (*_callback_3)() = nullptr;
        void (*_callback_16)() = nullptr;
        void (*_callback_long)() = nullptr;
        static MasterClock* self;
};

MasterClock* MasterClock::self = nullptr;

MasterClock Tocker;