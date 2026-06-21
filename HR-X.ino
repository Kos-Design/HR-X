#define MULTIPLEXED_PADS 1
const int display_lag = 10 ;
const int control_lag = 10 ;


//#if MULTIPLEXED_PADS
#include "muxer.h"
Muxer Muxer;
//#endif

byte itr = 0;
int c_change;
int cc_note_num;
// adcHighPassFilterDisable();
bool le_303_On ;

//#include <Metro.h>
// int startccrecordpos;
// int stopccrecordpos;
const byte sizeofnoCCrecord = 11;
// functions that have system or various controls that are ignored for some ops
byte noCCrecord[sizeofnoCCrecord] = {3,35,36,37, 38,39,40,41,42,44, 1};
byte slope1 = 10;
byte slope2 = 10;
byte cutoffmode;
byte resonancemode;
byte paramse1;
byte paramse2;
bool externalticker;
int starttaptime;
int numberoftaps;
int tapstime[5] = {0};
float tapaverage;
const byte truesizeofSongmenulabels = 8;
int millitickinterval = 115;
//freeze, can't record wav
//#include <MsTimer2.h>
bool avoid_fx_bounce = false;
//not precise
//Metro metro0 = Metro(millitickinterval);
//Metro metro303 = Metro(25);
//#include <IntervalTimer.h>
//freezes can't record
//IntervalTimer metro1;
//IntervalTimer metro3;
//float interval_ms = (60000.0 /4.0) / 130.0;  // Calculate the interval in milliseconds
float interval_ms = millitickinterval ;
// IntervalTimer playNoteTimer;
// Metro metrobuttons = Metro(20);

byte smixervknobs[16] = {127, 127, 127, 127, 127, 127, 127, 127,
                         127, 127, 127, 127, 127, 127, 127, 127};
int lehalfbeat;

int cutoff_pulse = 8;
int reson_pulse = 8;
int le303pulsewidth =(int)((cutoff_pulse / 32.0) * 2 * millitickinterval + 50);
int le303pulsewidth2 =(int)((reson_pulse / 32.0) * 2 * millitickinterval + 50);
byte offsetliner;
byte x_axis_cc = 17 ;
byte y_axis_cc = 18 ;
byte trace_wave_cc = 58 ;
byte *valz[3]= {&x_axis_cc,&y_axis_cc,&trace_wave_cc};

bool rec_looping;
int tocker ;
byte filter_lfo_option = 3 ;
int le303ffilterzVknobs[3];

byte songpage = 0;
byte samplelinerspage;
// LP BP HP 127
int mixle303ffilterzVknobs[3];
byte navrecmenu = 2;
int laCCduration;
int letempipolate;
float interpolcoeff;
byte settointerpolate[128];
EXTMEM byte leccinterpolated[128];
bool interpolOn = 1;
float le303filterzgainz[3] = {1.0, 0, 0};
int le303filterzwet;
float le303filterzfreq = 10000;
float le303filterzreso = 0.7;
float le303filterzoctv = 0.25;
bool clearsaniloop;
int le303filterzrange = 10000;
// float targetBPM = 120.0 ;
float BPMs = (60000.0 / millitickinterval) / 4.0;
const int pbars = 32;

float BPM = 130.0;
unsigned long MICROSECONDS_PER_MINUTE = 60000000;
unsigned long MICROSECONDS_PER_BEAT = MICROSECONDS_PER_MINUTE / BPM;
unsigned long MICROSECONDS_PER_MIDI_CLOCK = MICROSECONDS_PER_BEAT / 4; // MIDI clock ticks 24 times per beat

// not sure if used
unsigned long latimeline;
// unsigned long latimelineshifter = ((60000/19200)*pbars) ;
bool SendMidiOut;
// unsigned long tickerf = millis();  ;
#include <MIDIUSB.h>
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
bool patternOn;
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
//add to preset

int waits = 0;
char pleasewaitarray[10][32];
const int fxs_count = 3;
bool pre_record = false ;
int delaymultiplier[fxs_count] = {55};
const int sizeopremixtoM = 9 * fxs_count;
const int sizeopremixWtoM = 9 * fxs_count;
const int sizeofxcords = 9 * fxs_count * 2 * 3;

float interpot;
bool overdubmidi;
bool noteprint = 0;

byte patterns_indexes[99];
byte patterns_count = 0 ;
const byte ptn_size = 6;
String patterns_names[ptn_size];
byte patterns_names_offset = 0 ;

byte presets_indexes[99];
byte presets_count = 0 ;
const byte pst_size = 6;
String presets_names[pst_size];
byte presets_names_offset = 0 ;

bool demimalmode;
bool addinglenght;
EXTMEM char sampledirpath[99] = {"SOUNDSET/"};

const byte truesizeofwaveformsmenulabels = 8;

String newloopedpath = "SOUNDSET/REC/LOOP00#L.RAW";
String newRecpathL = "SOUNDSET/REC/RECZ00#L.RAW";
String newRecpathR = "SOUNDSET/REC/RECZ00#R.RAW";
int navlevelvbuttons = 1;
const int numberofvbuttonslabels = 8;
byte vbuttonsCC[numberofvbuttonslabels + 14 + 17];
byte vPots[17] = {0};

byte tapnote = byte(3);
bool tapstarted;

byte preampleswaves = 64;

const byte szsset = 99;
const byte ssnamsize = 26;
EXTMEM char samplefoldersregistered[szsset][ssnamsize];
EXTMEM char samplename[99][999][13];
EXTMEM char samplefullpath[99][999][38];
EXTMEM char samplebase[99][999][9];
// EXTMEM char lefilenamed[99][999][13];
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
float bqslope[fxs_count][bqstagesnum] = {0.5};
float bqgain[fxs_count][bqstagesnum];
float bqfreq[fxs_count][bqstagesnum] = {300};
int bqtype[fxs_count][bqstagesnum];
// [lebiquad] [lestage] freq slope gain
int bqVpot[fxs_count][bqstagesnum][3];
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
char newmksamplefullpath[32] = {"SOUNDSET/MABANK01/SAMPLE00.RAW"};

#include "/home/kosmin/HR-X/includes/images.ino"
#include "/home/kosmin/HR-X/includes/notestofrequency_442.ino"
#include "ParserLib.h"
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#include <Bounce.h>
#include <Encoder.h>
#include <string.h>
const int liners_count = 6;
const int nombreofSamplerliners = 16;
const byte synths_count = 3;
const int patternlines = 4;
bool tb303[liners_count];
long le303start[liners_count];

EXTMEM unsigned long pulsers[liners_count][2]= { {0,120}, {0,120}, {0,120},{0,120}, {0,120}, {0,120}};

byte bufferLoop[512];
// used in recording
EXTMEM byte bufferL[512];
EXTMEM byte bufferR[512];

const int numbofsettinglabels = 14;
int samplermidichannel = 8;
byte synthmidichannel = 16;
bool blocked = false ;
byte navrec = 3;
// various hard to pass params
int tickposition;
bool stoptick = true;

bool arpegiatorOn = 0;
// 8 is off
const byte arpeges_types = 8 ;
byte arpegiatortype = 8;

byte arpeglengh = 0;

// bool gammedirection[nombreofarpeglines] ;
byte arpegmode = 4;
byte arpegnumofnotes = 7;
byte arpegstartoffset = 0;
byte arpeggridC;

byte arpeggridS;
bool stoptickernextcycle;
// unsigned long millisSincenLinerOn[liners_count];
// unsigned long currentnotelength[liners_count];
bool patrecord;
byte arpegiatingNote[liners_count];
// note , veloc
const int nombreofarpeglines = liners_count;
bool tripletdirection[nombreofarpeglines];
byte playingarpegiator[nombreofarpeglines][liners_count];
byte calledarpegenote[nombreofarpeglines][2];
byte tickgamme[nombreofarpeglines];
byte ticktriplet[nombreofarpeglines];
byte arpegnoteoffin[nombreofarpeglines][liners_count] = {1};
byte arpegnotestick[nombreofarpeglines];
byte arpegemptyticks[nombreofarpeglines];
bool digitalplay = 0;
bool lefadout[liners_count];
bool targetNOsampler;
bool targetNOsynth;
bool targetNOcc;

byte glidemode = 0;
byte note_before;
bool dogliding[liners_count];
int freq_difference;
long unsigned int leglideposition[liners_count];
int note_difference;
float glidefactor;
int time_of_last_note = 0 ;
byte lapreviousnotewCmode[liners_count];
int leglidershiftCmode[liners_count];
int note_differenceCmode[liners_count];

byte ccsynthselector;
byte ccfxlineselector;

// lenght of the current interpolation
// from leinterpolstart to [1] interpole target position
byte Ccinterpolengh[128][3];

const int parsingbuffersize = 16000;
int parsinglength = parsingbuffersize;
const int pat_parser_size = 32000;

EXTMEM char receivedbitinchar[parsingbuffersize];

// = 89.6 ( 1.02678 ) 92 original
bool debugmidion = 0;
bool freezemidicc = 0;
int navlevelpatedit = 2;

bool track_cells[patternlines][pbars] = {0};

EXTMEM byte synth_partition[liners_count][pbars][3];
EXTMEM byte temp_synth_partition[liners_count][pbars][3];
EXTMEM byte synth_off_pat[liners_count][pbars][3];

EXTMEM int length0pbars[liners_count][pbars];
EXTMEM int templength0pbars[liners_count][pbars];
EXTMEM int length1notes1[liners_count][pbars];
byte synth_start_tpos[liners_count];

EXTMEM byte sampler_partition[nombreofSamplerliners][pbars][3];
EXTMEM byte temp_sampler_partition[nombreofSamplerliners][pbars][3];
// EXTMEM unsigned long length2notes1[nombreofSamplerliners][pbars];
// EXTMEM unsigned int length2pbars[nombreofSamplerliners][pbars];
// EXTMEM unsigned int templength2pbars[nombreofSamplerliners][pbars];
EXTMEM byte sampler_off_pat[pbars][3];
bool just_pressed_rec = false ;
int howmanyactiveccnow;
int tickerlasttick;
byte recorded_ccs[32] ;
byte pots_controllers[32][32][2];
EXTMEM byte cc_partition[128][pbars];
byte activateinterpolatecc[8];
bool recordCC;
//TODO reduce size
bool ignorethatcc[128];
bool ccoverdub;
bool recpaterninit;
int lavelocity;
int interpolated_ctrls = 0;
int availableliner;
int olderliner;

byte fffnote;
byte cellsizer = 3;
byte celltall = 9;
byte startx = 8;
byte starty = 18;

GFXcanvas1 canvasBIG(128, 64);
GFXcanvas1 canvastitle(128, 16);
// SD on audio board
#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 7
#define SDCARD_SCK_PIN 14
short lefakeselector;
const int chipSelect = 10;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS                                                         \
  0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire2, OLED_RESET);

#define LOGO_HEIGHT 32
#define LOGO_WIDTH 64
// File lesfiles[999];
// EXTMEM char lesfileslist[999][99];
// EXTMEM char lesfolderslist[99][99];
// File lesfolders[99];
File myMidiFile;
int filecount;
int keepcount;
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
int vraipos = 0;
int oldvraipos = 0;
int oldPosition = -999;
int count = 0;
float notefrequency = 440.0;
int newPosition = 0;
int filelenght;
bool selectedFileorDir;
float smallfloat;

const int lesformes[9] PROGMEM = {
    WAVEFORM_SINE,     WAVEFORM_SAWTOOTH,          WAVEFORM_SAWTOOTH_REVERSE,
    WAVEFORM_TRIANGLE, WAVEFORM_TRIANGLE_VARIABLE, WAVEFORM_SQUARE,
    WAVEFORM_PULSE,    WAVEFORM_ARBITRARY,         WAVEFORM_SAMPLE_HOLD};

const byte truesizeofpresetmenulabels = 5;

byte waveformIndex = 0 ;

int16_t arbitrary_waveforms[synths_count][256] ;

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

int phaselevelsL[synths_count] = {0, 0, 0};

int LFOphase[synths_count] = {0,0,0};
const byte sizeofLFOlabels = 9;

byte LFOmenuroot = 2;
// TODO check offset of 50 ?
int LFOoffset[synths_count] = {50,50,50};
byte LFOformstype[synths_count] = {0, 0, 0};
byte LFOfreqs[synths_count] = {100,100,100};
byte LFOlevel[synths_count] = {100,100,100};
bool LFOsync[synths_count];

byte wave1offset[synths_count] = {64,64,64};

// File originefile ;
int adsrlevels[6] = {0, 5, 0, 50, 100, 60};
int mappedattack = 5;
int mappeddecay = 50;
int mappedrelease = 60;
int mappedsustain = 100; // divide by 100 to float
int MadsrAttackDelay = 0;
int MadsrHold = 0;
int navleveloverwrite = 2;
int knobiprev[synths_count] = {0, 0, 0};

const int allfxes = 146;

#include "pads.h"
Pads Pads;

char mainmenufxlist[mainmenufxlistsize][12] = {
      "Multiply", "Reverb", "Granular", "BitCrusher", "Flanger",
      "Chorus",   "Biquad", "Filter",   "Delay",      "None"};

// TODO
//const char ControlList[allfxes][23] PROGMEM = {
const char ControlList[allfxes][21] = {
    // 0
    "None", "Volume","SynthLevel", "SDLvl", "FlashLevel", "Fx1Level",
    "Fx2Level", "Fx3Level", "SamplerDry","SynthDry",
    // 10
    "AuxDry", "CtoffSlope","ResoSlope","Free", "Free", "Free",
    "CtoffTime", "ResoTime", "FilterLevel ", "Free",
    // 20
    "CutOff", "Resonance", "OctRange", "glidemode", "FilterIn", "free",
    "free", "arpegiatortype", "arpegmode", "arpegstartoffset",
    // 30
    "arpegnumofnotes", "arpeggridC", "arpeggridS", "arpeglengh", "digitalplay",
    "CuePlay", "Start", "Stop", "Metronome", "Capture",
    // 40
    "pausedasong", "stopdasong", "playdasong", "Chords", "RecordCC",
    "Synthselector", "wavesfreqs", "mixlevelsL", "panLs", "FMmodulated",
    // 50
    "Waveformstyped", "wave1offset", "phaselevelsL", "LFOlevel", "LFOtype",
    "LFOfreqs", "LFOphase", "LFOoffset", "LFOsync", "Attack Delay",
    /// 60
    "Attack", "Hold", "Decay", "Sustain", "free", "Release",
    "303ffilterz[0]", "303fgainz[1]", "303fgainz[2]", "FXselector",
    // 70
    "chorusVknobs[i]", "bqstage[i]", "LFOonfilterz[i]", "bqVpot[i][j][0]", "bqVpot[i][j][1]", "bqVpot[i][j][2]",
    "grlrGrain", "grlrRatio", "gShift-T", "gFreeze-T",
    // 80
    "reverbVknobs[i][0]", "reverbVknobs[i][1]", "bitcrush[i][0]",  "bitcrush[i][1]", "mixVknobs[i][0]",
    "mix[i][1]", "mix[i][2]", "fltrVknob[i][0]", "fltrVknob[i][1]", "fltrVknob[i][2]",
    // 90
    "flanger[i][0]", "flanger[i][1]", "flanger[i][2]","DelayFreq[i][0]", "DelayMult[i][1]", "DelayFeed[i][2]",
    "bqtype[i][bq]", "In level", "Free", "Free","BPM",
    // 100
    "Pat. Save", "Pat. Load", "Record Raw", "Play Recorded", "Stop Play&Rec", "Free", "Free",
    "free","Load Pat0", "preset 0", "Loop recorder",
    // 110
    "Sp.Track 1", "Sp.Track 2", "Sp.Track 3", "Sp.Track 4", "Sp.Track 5",
    "Sp.Track 6", "Sp.Track 7", "Sp.Track 8", "Sp.Track 9", "Sp.Track 10",
    // 120
    "Sp.Track 11", "Sp.Track 12", "Sp.Track 13", "Sp.Track 14", "Sp.Track 15",
    "Sp.Track 16", "Free", "Free", "Free", "Free", "Free",
    // 130
    "Free", "Free", "Free", "Wfreq4", "Pan 4", "Phase4"
};

float WetMixMasters[4] = {0.0, 0.0, 0.0, 0.0};

bool patterninparse;

bool granular_shifting[fxs_count] = {0,0,0};
bool granular_freezing[fxs_count] = {0,0,0};
char leparsed[3];
short lecaractere;
short letempspattern;
short linerpat;
int previousTp;
const byte sizeofoptionspattern = 6;
const char optionspatternlabels[sizeofoptionspattern][12] PROGMEM = {
    "Transpose", "Shift", "Clear", "Target", "Smooth CC","Merge Pat"};
const byte sizeofpatternlistlabels = 8;

const char *monthName[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                       "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
bool debug_cpu = false;
byte bitcrusherVknobs[fxs_count][2];
byte granularVknobs[fxs_count][2];
byte flangerVknobs[fxs_count][3];
byte delayVknobs[fxs_count][3];
byte chorusVknobs[fxs_count];
byte reverbVknobs[fxs_count][2];
SerialFlashFile dummy_flash_file ;
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
// int midiknobiprev[128] ;
int midiknobassigned[128];

int sublevels[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
// make it float

float wavesfreqs[synths_count] = {1.0, 1.0, 2.0};
float panLs[synths_count] = {1, 1, 1};

float mixlevelsL[synths_count] = {0.1, 0.0, 0.0};
// 0 master , 1synth, 2 sampler, 3 unused
byte mixlevelsM[4] = {127, 127, 38, 127};

unsigned int Waveformstyped[synths_count] = {1, 11, 11};
byte samplesnotesOn[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

AudioEffectEnvelope *enveloppesL[liners_count] = {&envelopeL0, &envelopeL1, &envelopeL2,
                                                     &envelopeL3, &envelopeL4, &envelopeL5};

// modulator for 303 mode
float ladiff1;
float ladiff2;
int letbfreq;

Adafruit_SSD1306 display(128, 64, &Wire2, -1);
char *toprint = (char *)"Cosmix";

bool initdone;
byte FMmodulated[synths_count] = {0,0,0};
#include "/home/kosmin/HR-X/includes/cablages.ino"

#define FLANGE_DELAY_LENGTH (4 * AUDIO_BLOCK_SAMPLES)
#define CHORUS_DELAY_LENGTH (8 * AUDIO_BLOCK_SAMPLES)
EXTMEM short chorusdelayline[CHORUS_DELAY_LENGTH];
EXTMEM short chorusdelayline2[CHORUS_DELAY_LENGTH];
EXTMEM short chorusdelayline3[CHORUS_DELAY_LENGTH];
// short chorusdelayline4[CHORUS_DELAY_LENGTH];
int chorusvoices = 4;

EXTMEM short flangedelay[FLANGE_DELAY_LENGTH];
EXTMEM short flangedelay2[FLANGE_DELAY_LENGTH];
EXTMEM short flangedelay3[FLANGE_DELAY_LENGTH];
// short flangedelay4[FLANGE_DELAY_LENGTH];

int flangeoffset = FLANGE_DELAY_LENGTH / 4;
int flangedepth = FLANGE_DELAY_LENGTH / 4;

double flangefreq = 0.5;

#define GRANULAR_MEMORY_SIZE 12800
// 12800 is for 290 ms at 44.1 kHz
int16_t granularMemory[GRANULAR_MEMORY_SIZE];
int16_t granularMemory2[GRANULAR_MEMORY_SIZE];
int16_t granularMemory3[GRANULAR_MEMORY_SIZE];

EXTMEM AudioConnection delayCord1(feedbackdelay1, delay1);
EXTMEM AudioConnection delayCord2(feedbackdelay2, delay2);
EXTMEM AudioConnection delayCord3(feedbackdelay3, delay3);

EXTMEM AudioConnection Notespy_cable(ampL, notefreq1);

AudioConnection FMWaveCord01(FMWaveform1L1, 0, WavesL1, 0);
AudioConnection FMWaveCord02(FMWaveform1L2, 0, WavesL2, 0);
AudioConnection FMWaveCord03(FMWaveform1L3, 0, WavesL3, 0);
AudioConnection FMWaveCord04(FMWaveform1L4, 0, WavesL4, 0);
AudioConnection FMWaveCord05(FMWaveform1L5, 0, WavesL5, 0);
AudioConnection FMWaveCord06(FMWaveform1L6, 0, WavesL6, 0);

AudioConnection FMWaveCord09(FMWaveform2L1, 0, WavesL1, 1);
AudioConnection FMWaveCord10(FMWaveform2L2, 0, WavesL2, 1);
AudioConnection FMWaveCord11(FMWaveform2L3, 0, WavesL3, 1);
AudioConnection FMWaveCord12(FMWaveform2L4, 0, WavesL4, 1);
AudioConnection FMWaveCord13(FMWaveform2L5, 0, WavesL5, 1);
AudioConnection FMWaveCord14(FMWaveform2L6, 0, WavesL6, 1);

AudioConnection FMWaveCord17(FMWaveform3L1, 0, WavesL1, 2);
AudioConnection FMWaveCord18(FMWaveform3L2, 0, WavesL2, 2);
AudioConnection FMWaveCord19(FMWaveform3L3, 0, WavesL3, 2);
AudioConnection FMWaveCord20(FMWaveform3L4, 0, WavesL4, 2);
AudioConnection FMWaveCord21(FMWaveform3L5, 0, WavesL5, 2);
AudioConnection FMWaveCord22(FMWaveform3L6, 0, WavesL6, 2);

AudioConnection stringCord01(string1L1, 0, WavesL1, 0);
AudioConnection stringCord02(string1L2, 0, WavesL2, 0);
AudioConnection stringCord03(string1L3, 0, WavesL3, 0);
AudioConnection stringCord04(string1L4, 0, WavesL4, 0);
AudioConnection stringCord05(string1L5, 0, WavesL5, 0);
AudioConnection stringCord06(string1L6, 0, WavesL6, 0);

AudioConnection stringCord09(string2L1, 0, WavesL1, 1);
AudioConnection stringCord10(string2L2, 0, WavesL2, 1);
AudioConnection stringCord11(string2L3, 0, WavesL3, 1);
AudioConnection stringCord12(string2L4, 0, WavesL4, 1);
AudioConnection stringCord13(string2L5, 0, WavesL5, 1);
AudioConnection stringCord14(string2L6, 0, WavesL6, 1);

AudioConnection stringCord17(string3L1, 0, WavesL1, 2);
AudioConnection stringCord18(string3L2, 0, WavesL2, 2);
AudioConnection stringCord19(string3L3, 0, WavesL3, 2);
AudioConnection stringCord20(string3L4, 0, WavesL4, 2);
AudioConnection stringCord21(string3L5, 0, WavesL5, 2);
AudioConnection stringCord22(string3L6, 0, WavesL6, 2);

AudioConnection drumCord01(drum1L1, 0, WavesL1, 0);
AudioConnection drumCord02(drum1L2, 0, WavesL2, 0);
AudioConnection drumCord03(drum1L3, 0, WavesL3, 0);
AudioConnection drumCord04(drum1L4, 0, WavesL4, 0);
AudioConnection drumCord05(drum1L5, 0, WavesL5, 0);
AudioConnection drumCord06(drum1L6, 0, WavesL6, 0);

AudioConnection drumCord09(drum2L1, 0, WavesL1, 1);
AudioConnection drumCord10(drum2L2, 0, WavesL2, 1);
AudioConnection drumCord11(drum2L3, 0, WavesL3, 1);
AudioConnection drumCord12(drum2L4, 0, WavesL4, 1);
AudioConnection drumCord13(drum2L5, 0, WavesL5, 1);
AudioConnection drumCord14(drum2L6, 0, WavesL6, 1);

AudioConnection drumCord17(drum3L1, 0, WavesL1, 2);
AudioConnection drumCord18(drum3L2, 0, WavesL2, 2);
AudioConnection drumCord19(drum3L3, 0, WavesL3, 2);
AudioConnection drumCord20(drum3L4, 0, WavesL4, 2);
AudioConnection drumCord21(drum3L5, 0, WavesL5, 2);
AudioConnection drumCord22(drum3L6, 0, WavesL6, 2);

AudioConnection wavelinecord19(waveform1L5, 0, WavesL5, 0);
AudioConnection wavelinecord20(waveform1L6, 0, WavesL6, 0);
AudioConnection wavelinecord21(waveform1L4, 0, WavesL4, 0);
AudioConnection wavelinecord22(waveform1L2, 0, WavesL2, 0);
AudioConnection wavelinecord23(waveform1L3, 0, WavesL3, 0);
AudioConnection wavelinecord24(waveform1L1, 0, WavesL1, 0);

AudioConnection wavelinecord33(waveform2L5, 0, WavesL5, 1);
AudioConnection wavelinecord34(waveform3L5, 0, WavesL5, 2);
AudioConnection wavelinecord35(waveform2L6, 0, WavesL6, 1);
AudioConnection wavelinecord36(waveform3L6, 0, WavesL6, 2);
AudioConnection wavelinecord37(waveform3L3, 0, WavesL3, 2);
AudioConnection wavelinecord39(waveform2L3, 0, WavesL3, 1);
AudioConnection wavelinecord41(waveform2L4, 0, WavesL4, 1);
AudioConnection wavelinecord42(waveform3L4, 0, WavesL4, 2);
AudioConnection wavelinecord43(waveform3L2, 0, WavesL2, 2);
AudioConnection wavelinecord44(waveform3L1, 0, WavesL1, 2);
AudioConnection wavelinecord45(waveform2L2, 0, WavesL2, 1);
AudioConnection wavelinecord47(waveform2L1, 0, WavesL1, 1);

AudioConnection modulateCord01(modulate1L1, 0, WavesL1, 0);
AudioConnection modulateCord02(modulate1L2, 0, WavesL2, 0);
AudioConnection modulateCord03(modulate1L3, 0, WavesL3, 0);
AudioConnection modulateCord04(modulate1L4, 0, WavesL4, 0);
AudioConnection modulateCord05(modulate1L5, 0, WavesL5, 0);
AudioConnection modulateCord06(modulate1L6, 0, WavesL6, 0);
AudioConnection modulateCord09(modulate2L1, 0, WavesL1, 1);
AudioConnection modulateCord10(modulate2L2, 0, WavesL2, 1);
AudioConnection modulateCord11(modulate2L3, 0, WavesL3, 1);
AudioConnection modulateCord12(modulate2L4, 0, WavesL4, 1);
AudioConnection modulateCord13(modulate2L5, 0, WavesL5, 1);
AudioConnection modulateCord14(modulate2L6, 0, WavesL6, 1);
AudioConnection modulateCord17(modulate3L1, 0, WavesL1, 2);
AudioConnection modulateCord18(modulate3L2, 0, WavesL2, 2);
AudioConnection modulateCord19(modulate3L3, 0, WavesL3, 2);
AudioConnection modulateCord20(modulate3L4, 0, WavesL4, 2);
AudioConnection modulateCord21(modulate3L5, 0, WavesL5, 2);
AudioConnection modulateCord22(modulate3L6, 0, WavesL6, 2);

AudioConnection MDwaveCord01(waveform1L1, 0, modulate1L1, 0);
AudioConnection MDwaveCord02(waveform1L2, 0, modulate1L2, 0);
AudioConnection MDwaveCord03(waveform1L3, 0, modulate1L3, 0);
AudioConnection MDwaveCord04(waveform1L4, 0, modulate1L4, 0);
AudioConnection MDwaveCord05(waveform1L5, 0, modulate1L5, 0);
AudioConnection MDwaveCord06(waveform1L6, 0, modulate1L6, 0);

AudioConnection MDwaveCord09(waveform2L1, 0, modulate2L1, 0);
AudioConnection MDwaveCord10(waveform2L2, 0, modulate2L2, 0);
AudioConnection MDwaveCord11(waveform2L3, 0, modulate2L3, 0);
AudioConnection MDwaveCord12(waveform2L4, 0, modulate2L4, 0);
AudioConnection MDwaveCord13(waveform2L5, 0, modulate2L5, 0);
AudioConnection MDwaveCord14(waveform2L6, 0, modulate2L6, 0);

AudioConnection MDwaveCord17(waveform3L1, 0, modulate3L1, 0);
AudioConnection MDwaveCord18(waveform3L2, 0, modulate3L2, 0);
AudioConnection MDwaveCord19(waveform3L3, 0, modulate3L3, 0);
AudioConnection MDwaveCord20(waveform3L4, 0, modulate3L4, 0);
AudioConnection MDwaveCord21(waveform3L5, 0, modulate3L5, 0);
AudioConnection MDwaveCord22(waveform3L6, 0, modulate3L6, 0);



AudioConnection MDdrumCord01(drum1L1, 0, modulate1L1, 0);
AudioConnection MDdrumCord02(drum1L2, 0, modulate1L2, 0);
AudioConnection MDdrumCord03(drum1L3, 0, modulate1L3, 0);
AudioConnection MDdrumCord04(drum1L4, 0, modulate1L4, 0);
AudioConnection MDdrumCord05(drum1L5, 0, modulate1L5, 0);
AudioConnection MDdrumCord06(drum1L6, 0, modulate1L6, 0);

AudioConnection MDdrumCord09(drum2L1, 0, modulate2L1, 0);
AudioConnection MDdrumCord10(drum2L2, 0, modulate2L2, 0);
AudioConnection MDdrumCord11(drum2L3, 0, modulate2L3, 0);
AudioConnection MDdrumCord12(drum2L4, 0, modulate2L4, 0);
AudioConnection MDdrumCord13(drum2L5, 0, modulate2L5, 0);
AudioConnection MDdrumCord14(drum2L6, 0, modulate2L6, 0);

AudioConnection MDdrumCord17(drum3L1, 0, modulate3L1, 0);
AudioConnection MDdrumCord18(drum3L2, 0, modulate3L2, 0);
AudioConnection MDdrumCord19(drum3L3, 0, modulate3L3, 0);
AudioConnection MDdrumCord20(drum3L4, 0, modulate3L4, 0);
AudioConnection MDdrumCord21(drum3L5, 0, modulate3L5, 0);
AudioConnection MDdrumCord22(drum3L6, 0, modulate3L6, 0);

AudioConnection MDstringCord01(string1L1, 0, modulate1L1, 0);
AudioConnection MDstringCord02(string1L2, 0, modulate1L2, 0);
AudioConnection MDstringCord03(string1L3, 0, modulate1L3, 0);
AudioConnection MDstringCord04(string1L4, 0, modulate1L4, 0);
AudioConnection MDstringCord05(string1L5, 0, modulate1L5, 0);
AudioConnection MDstringCord06(string1L6, 0, modulate1L6, 0);

AudioConnection MDstringCord09(string2L1, 0, modulate2L1, 0);
AudioConnection MDstringCord10(string2L2, 0, modulate2L2, 0);
AudioConnection MDstringCord11(string2L3, 0, modulate2L3, 0);
AudioConnection MDstringCord12(string2L4, 0, modulate2L4, 0);
AudioConnection MDstringCord13(string2L5, 0, modulate2L5, 0);
AudioConnection MDstringCord14(string2L6, 0, modulate2L6, 0);

AudioConnection MDstringCord17(string3L1, 0, modulate3L1, 0);
AudioConnection MDstringCord18(string3L2, 0, modulate3L2, 0);
AudioConnection MDstringCord19(string3L3, 0, modulate3L3, 0);
AudioConnection MDstringCord20(string3L4, 0, modulate3L4, 0);
AudioConnection MDstringCord21(string3L5, 0, modulate3L5, 0);
AudioConnection MDstringCord22(string3L6, 0, modulate3L6, 0);

AudioConnection *delayCords[3] = {&delayCord1, &delayCord2, &delayCord3};

AudioConnection *stringcords1[liners_count*synths_count] = {
    &stringCord01, &stringCord02, &stringCord03, &stringCord04, &stringCord05, &stringCord06,
    &stringCord09, &stringCord10, &stringCord11, &stringCord12, &stringCord13, &stringCord14,
    &stringCord17, &stringCord18, &stringCord19, &stringCord20, &stringCord21, &stringCord22};

AudioConnection *drumcords1[liners_count*synths_count] = {
    &drumCord01, &drumCord02, &drumCord03, &drumCord04, &drumCord05, &drumCord06,
    &drumCord09, &drumCord10, &drumCord11, &drumCord12, &drumCord13, &drumCord14,
    &drumCord17, &drumCord18, &drumCord19, &drumCord20, &drumCord21, &drumCord22};

AudioConnection *modulatecords1[liners_count*synths_count] = {
    &modulateCord01, &modulateCord02, &modulateCord03, &modulateCord04, &modulateCord05, &modulateCord06,
    &modulateCord09, &modulateCord10, &modulateCord11, &modulateCord12, &modulateCord13, &modulateCord14,
    &modulateCord17, &modulateCord18, &modulateCord19, &modulateCord20, &modulateCord21, &modulateCord22};

AudioConnection *MDdrumcords1[liners_count*synths_count] = {
    &MDdrumCord01, &MDdrumCord02, &MDdrumCord03, &MDdrumCord04, &MDdrumCord05, &MDdrumCord06,
    &MDdrumCord09, &MDdrumCord10, &MDdrumCord11, &MDdrumCord12, &MDdrumCord13, &MDdrumCord14,
    &MDdrumCord17, &MDdrumCord18, &MDdrumCord19, &MDdrumCord20, &MDdrumCord21, &MDdrumCord22};

AudioConnection *MDwavecords1[liners_count*synths_count] = {
    &MDwaveCord01, &MDwaveCord02, &MDwaveCord03, &MDwaveCord04, &MDwaveCord05, &MDwaveCord06,
    &MDwaveCord09, &MDwaveCord10, &MDwaveCord11, &MDwaveCord12, &MDwaveCord13, &MDwaveCord14,
    &MDwaveCord17, &MDwaveCord18, &MDwaveCord19, &MDwaveCord20, &MDwaveCord21, &MDwaveCord22};

AudioConnection *MDstringcords1[liners_count*synths_count] = {
    &MDstringCord01, &MDstringCord02, &MDstringCord03, &MDstringCord04, &MDstringCord05, &MDstringCord06,
    &MDstringCord09, &MDstringCord10, &MDstringCord11, &MDstringCord12, &MDstringCord13, &MDstringCord14,
    &MDstringCord17, &MDstringCord18, &MDstringCord19, &MDstringCord20, &MDstringCord21, &MDstringCord22};

AudioConnection *FMwavecords1[liners_count*synths_count] = {
    &FMWaveCord01, &FMWaveCord02, &FMWaveCord03, &FMWaveCord04, &FMWaveCord05, &FMWaveCord06,
    &FMWaveCord09, &FMWaveCord10, &FMWaveCord11, &FMWaveCord12, &FMWaveCord13, &FMWaveCord14,
    &FMWaveCord17, &FMWaveCord18, &FMWaveCord19, &FMWaveCord20, &FMWaveCord21, &FMWaveCord22};

AudioConnection *wavelinescords[liners_count*synths_count] = {
    &wavelinecord24, &wavelinecord22, &wavelinecord23, &wavelinecord21, &wavelinecord19, &wavelinecord20,
    &wavelinecord47, &wavelinecord45, &wavelinecord39, &wavelinecord41, &wavelinecord33, &wavelinecord35,
    &wavelinecord44, &wavelinecord43, &wavelinecord37, &wavelinecord42, &wavelinecord34, &wavelinecord36};

AudioSynthWaveform *waveforms1[liners_count*synths_count] = {
    &waveform1L1, &waveform1L2, &waveform1L3, &waveform1L4, &waveform1L5, &waveform1L6,
    &waveform2L1, &waveform2L2, &waveform2L3, &waveform2L4, &waveform2L5, &waveform2L6,
    &waveform3L1, &waveform3L2, &waveform3L3, &waveform3L4, &waveform3L5, &waveform3L6};

AudioSynthWaveformModulated *FMwaveforms1[liners_count*synths_count] = {
    &FMWaveform1L1, &FMWaveform1L2, &FMWaveform1L3, &FMWaveform1L4, &FMWaveform1L5, &FMWaveform1L6,
    &FMWaveform2L1, &FMWaveform2L2, &FMWaveform2L3, &FMWaveform2L4, &FMWaveform2L5, &FMWaveform2L6,
    &FMWaveform3L1, &FMWaveform3L2, &FMWaveform3L3, &FMWaveform3L4, &FMWaveform3L5, &FMWaveform3L6};

AudioSynthSimpleDrum *drums1[liners_count*synths_count] = {
    &drum1L1, &drum1L2, &drum1L3, &drum1L4, &drum1L5, &drum1L6,
    &drum2L1, &drum2L2, &drum2L3, &drum2L4, &drum2L5, &drum2L6,
    &drum3L1, &drum3L2, &drum3L3, &drum3L4, &drum3L5, &drum3L6};

AudioSynthKarplusStrong *strings1[liners_count*synths_count] = {
    &string1L1, &string1L2, &string1L3, &string1L4, &string1L5, &string1L6,
    &string2L1, &string2L2, &string2L3, &string2L4,&string2L5, &string2L6,
    &string3L1, &string3L2, &string3L3, &string3L4, &string3L5, &string3L6};

AudioMixer4 *Wavesmix[liners_count] = {&WavesL1, &WavesL2, &WavesL3, &WavesL4, &WavesL5, &WavesL6};

AudioPlaySerialflashRaw *FlashSampler[16] = {
    &FlashSampler1,  &FlashSampler2,  &FlashSampler3,  &FlashSampler4,
    &FlashSampler5,  &FlashSampler6,  &FlashSampler7,  &FlashSampler8,
    &FlashSampler9,  &FlashSampler10, &FlashSampler11, &FlashSampler12,
    &FlashSampler13, &FlashSampler14, &FlashSampler15, &FlashSampler16};

AudioMixer4 *Flashmixer[4] = {&flashmix1, &flashmix2, &flashmix3, &flashmix4};

AudioAmplifier *Wavespreamp303[liners_count] = {&wavePAmp0, &wavePAmp1, &wavePAmp2,
                                     &wavePAmp3, &wavePAmp4, &wavePAmp5};

AudioSynthWaveform *LFOwaveforms1[synths_count] = {&LFOrm1, &LFOrm2, &LFOrm3};


class SequencerClocker : public AudioStream
{
public:
    SequencerClocker() : AudioStream(0, nullptr) {}
    bool stop = 1 ;
    void setBPM(float bpm)
    {
        _bpm = bpm;
        calculatePPQN();
    }

    void setPPQN(uint8_t ppqn) {
        _PPQN = ppqn;
        calculatePPQN();
    }

    void attach_24(void (*cb)())
    {
        _callback_24 = cb;
    }

    void attach_6(void (*cb)())
    {
        _callback_6 = cb;
    }

    void attach_48(void (*cb)())
    {
        _callback_48 = cb;
    }

    void attach_3(void (*cb)())
    {
        _callback_3 = cb;
    }

    virtual void update() override {
        if (_samplesPerTick <= 0.0)
        return;
        _sampleAccumulator += AUDIO_BLOCK_SAMPLES;
        while (_sampleAccumulator >= _samplesPerTick) {
            _sampleAccumulator -= _samplesPerTick;

            tick96++;
            if (!stop) {
                if ((tick96 % 6) == 0 && _callback_6){
                    quarter++;
                    _callback_6();
                }

                if ((tick96 % 48) == 0 && _callback_48){
                    eighth++;
                    _callback_48();
                }

                if ((tick96 % 24) == 0 && _callback_24){
                    sixteenth++;
                    _callback_24();
                }

                if ((tick96 % 3) == 0 && _callback_3){
                    thirtySecond++;
                    _callback_3();
                }
            }
        }
    }

private:


    void calculatePPQN() {
        if (_PPQN == 0 || _bpm <= 0.0f)
        return;
        _samplesPerTick =
            AUDIO_SAMPLE_RATE_EXACT *
            60.0 /
            (_bpm * _PPQN);
    }

    volatile uint32_t tick96 = 0;
    volatile uint32_t quarter = 0;
    volatile uint32_t eighth = 0;
    volatile uint32_t sixteenth = 0;
    volatile uint32_t thirtySecond = 0;

    float  _bpm = 120.0f;
    uint8_t _divisionsPerQuarter = 4;
    uint8_t _PPQN = 96 ;
    double _samplesPerTick = 0;
    double _sampleAccumulator = 0;
    void (*_callback_24)() = nullptr;
    void (*_callback_3)() = nullptr;
    void (*_callback_48)() = nullptr;
    void (*_callback_6)() = nullptr;
};

SequencerClocker clocker;

class ClockSink : public AudioStream
{
public:
    ClockSink() : AudioStream(1, inputQueueArray) {}

    void update(void) override {}

private:
    audio_block_t *inputQueueArray[1];
};

ClockSink sink;

AudioConnection patchCord_sinker(clocker, 0, sink, 0);

//these 3 last classes may be overkill but I wanted to try having a clock synched with audio samples
//maybe I was not using IntervalTimer the right way

class DisplayManager{
public:
    DisplayManager() {}

    bool ILI_128x64 = true;

    void display_home()
    {
        if (ILI_128x64) {
            Serial.println("ILI_128x64 detected");
        }
    }
    void setupscreen(){
        if (ILI_128x64) {
            _setupscreen_ILI();
        }
    }

    void lemenuroot() {_lemenuroot();}

    void displayleBGimg(const unsigned char *img) {_displayleBGimg(img);}

    void printlabel(char *toprint) {
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.println(toprint);
    }

    void displaymenu() {
        char menus_lbl[10][11] = {"WaveSynth", "LFOs", "Set Knobs", "Song", "Pattern", "Settings",
                       "MainFX", "Sampler", "Waveformer", "Presets"};
        if (navlevel == 0) {
            previousnavlevel = 0;
            navrange = 9;
            displayleBGimg(menuBG);
        }
        display.drawRoundRect(5 + (sublevels[0]%5)*24, 17+((sublevels[0]/5)*24), 21, 21, 3, SSD1306_WHITE);
        printlabel(menus_lbl[sublevels[0]]);
        display.display();
    }

    void attach_nav_zero(uint8_t index, void (*cb)())
    {
        if (index < 10)
            _nav_zero[index] = cb;
    }
    void clear_buffs(){
        canvasBIG.fillScreen(SSD1306_BLACK);
        canvastitle.fillScreen(SSD1306_BLACK);
    }
    void clear_buffs_1_1(){
        clear_buffs();
        canvastitle.setCursor(0, 0);
        canvastitle.setTextSize(1);
        canvasBIG.setTextSize(1);
    }
    void clear_buffs_2_1(){
        clear_buffs();
        canvastitle.setCursor(0, 0);
        canvastitle.setTextSize(2);
        canvasBIG.setTextSize(1);
    }
    void clear_buffs_2_2(){
        clear_buffs();
        canvastitle.setCursor(0, 0);
        canvastitle.setTextSize(2);
        canvasBIG.setTextSize(2);
    }
    void clear_3(){
        clear_buffs();
        display.clearDisplay();
    }

    void clean_title_2(){
        clear_3();
        canvastitle.setCursor(0, 0);
        canvastitle.setTextSize(2);
    }
    void clean_title_2_1(){
        clear_3();
        canvastitle.setCursor(0, 0);
        canvastitle.setTextSize(2);
        canvasBIG.setTextSize(1);
    }
    void clean_title_2_2(){
        clear_3();
        canvastitle.setCursor(0, 0);
        canvastitle.setTextSize(2);
        canvasBIG.setTextSize(2);
    }
    void clean_title_1(){
        clear_3();
        canvastitle.setCursor(0, 0);
        canvastitle.setTextSize(1);
    }
    //10 menu entries
    void (*_nav_zero[10])() = {nullptr};
private:

    void _displayleBGimg(const unsigned char *img) {
        display.clearDisplay();
        display.drawBitmap(0, 0, img, 128, 64, SSD1306_WHITE);
    }

    void _lemenuroot() {
        if (navlevel == 0) {
            displaymenu();
        }
        if (navlevel > 0) {
            _nav_zero[sublevels[0]]();
        }
    }

    void _setupscreen_ILI() {

        if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
            Serial.println(F("Screen SSD1306 allocation failed"));
            return;
        }
        display.display();
        display.setCursor(0, 0);
        display.setTextSize(1.5);
        display.setTextColor(SSD1306_WHITE);
        display.clearDisplay();
    }


    //10 methods dispatchin using sublevels zero context
    void (*_nav_one[10])() = {nullptr};
    void (**_nav[2])() = {_nav_zero,_nav_one};
};

DisplayManager dm = DisplayManager();

void returntonav(byte lelevel, byte lanavrange = navrange,byte t_vraipos = vraipos) {
  navlevel = lelevel;
  vraipos = t_vraipos;
  myEnc.write(vraipos * 4);
  navrange = lanavrange;
  dm.lemenuroot();
}

typedef struct {const char *key; int value;} MenuPager;

// refresh display --> find context
// context [pages lvl1] -> x10 pointers list of page drawers methods
// --> or sub contextes
// pages list

class SectionHolder{
public:
    SectionHolder() {}
    //categories can't do dicts, so lists of pointers placeholders §?...
    //bool ILI_128x64 = true;
    //typedef struct {int sublevels_address; int char_name; int depth;} Menu_Section;
    //typedef struct {int idx_order; int char_name; int depth;} Paged;
    //typedef struct {const char *key; int value;} DictEntry;
    //const char *pages[]={};
    void home() {
        if(_home){
            this->_home();
        }
    }
    void set_home(void (*cb)())
    {
        this->_home = cb;
    }

private:

void (*_home)() = nullptr;
};

class SynthMenuRouter{
public:
    SynthMenuRouter() {}

    void show() {
        if (_nav_synth[sublevels[1]]) {
            _nav_synth[sublevels[1]]();
        }
    }

    void attach_nav_synth(uint8_t index, void (*cb)())
    {
        if (index < 5)
            _nav_synth[index] = cb;
    }

private:
void (*_nav_synth[5])() = {nullptr};
};

SynthMenuRouter sn = SynthMenuRouter();

class LFOMenuRouter{
    public:
        LFOMenuRouter() {}

        void show() {
            //(ka.*KnobAssigner::actions[0])();
            (this->*LFOMenuRouter::_route_nav[navlevel-1])();
        }

        void route_navlevel_1(){
            home();
        }    
        void route_navlevel_2(){
            _lvl_2();

            //LFOlining();
        }
        void route_navlevel_3(){
            Serial.println("lfo3");        
        }    
        void route_navlevel_4(){
            Serial.println("lfo4");
        }

        void printLFObanner(int startx, int starty, int leLFO) {
            display.fillRect(startx, starty, 64, 24, SSD1306_INVERSE);
            dm.printlabel((char*)"LFO ");
            display.setCursor(116, 0);
            display.print(leLFO);
            display.display();
        }

        void LFOlineBG() {
            display.clearDisplay();
            display.drawBitmap(0, 64 - 47, wavesbg2, 128, 47, SSD1306_WHITE);

            display.display();
        }

        void home(){
            navrange = synths_count-1;
            //TODO:remove maybe
            reinitsublevels(2);

            LFOlineBG();

            switch (sublevels[1]) {
            case 0:
            printLFObanner(0, 16, 1);
            break;

            case 1:
            printLFObanner(64, 16, 2);
            break;

            case 2:
            printLFObanner(0, 40, 3);
            break;

            case 3:
            printLFObanner(64, 40, 4);
            break;

            default:
            break;
            }
        }
        void attach_nav_lfo(uint8_t index, void (*cb)())
        {
            if (index < 5)
                _nav_lfo[index] = cb;
        }
        void attach_lvl_2(void (*cb)())
        {
            _lvl_2 = cb;
        }
    private:
        using Action = void (LFOMenuRouter::*)();

        static constexpr Action _route_nav[4] = {
            &LFOMenuRouter::route_navlevel_1,
            &LFOMenuRouter::route_navlevel_2,
            &LFOMenuRouter::route_navlevel_3,
            &LFOMenuRouter::route_navlevel_4
        };

        //static constexpr void (*_route_nav[4])() = {route_navlevel_1,route_navlevel_2,route_navlevel_3,route_navlevel_4};
        void (*_nav_lfo[3])() = {nullptr};

        void (*_lvl_2)() = nullptr;
};
/*
class old_LFOMenuRouter{
    public:
        LFOMenuRouter() {}

        void show() {
            //(ka.*KnobAssigner::actions[0])();
            (this->*LFOMenuRouter::_route_nav[navlevel-1])();
        }

        void route_navlevel_1(){
            home();
        }    
        void route_navlevel_2(){
            LFOMenuRouter::_nav_lfo[sublevels[1]]();
        }
        void route_navlevel_3(){
            Serial.println("lfo3");        
        }    
        void route_navlevel_4(){
            Serial.println("lfo4");
        }

        void printLFObanner(int startx, int starty, int leLFO) {
            display.fillRect(startx, starty, 64, 24, SSD1306_INVERSE);
            dm.printlabel((char*)"LFO ");
            display.setCursor(116, 0);
            display.print(leLFO);
            display.display();
        }

        void LFOlineBG() {
            display.clearDisplay();
            display.drawBitmap(0, 64 - 47, wavesbg2, 128, 47, SSD1306_WHITE);

            display.display();
        }

        void home(){
            navrange = synths_count-1;
            //TODO:remove maybe
            reinitsublevels(2);

            LFOlineBG();

            switch (sublevels[1]) {
            case 0:
            printLFObanner(0, 16, 1);
            break;

            case 1:
            printLFObanner(64, 16, 2);
            break;

            case 2:
            printLFObanner(0, 40, 3);
            break;

            case 3:
            printLFObanner(64, 40, 4);
            break;

            default:
            break;
            }
        }
        void attach_nav_lfo(uint8_t index, void (*cb)())
        {
            if (index < 5)
                _nav_lfo[index] = cb;
        }

    private:
        using Action = void (LFOMenuRouter::*)();

        static constexpr Action _route_nav[4] = {
            &LFOMenuRouter::route_navlevel_1,
            &LFOMenuRouter::route_navlevel_2,
            &LFOMenuRouter::route_navlevel_3,
            &LFOMenuRouter::route_navlevel_4
        };

        //static constexpr void (*_route_nav[4])() = {route_navlevel_1,route_navlevel_2,route_navlevel_3,route_navlevel_4};
        void (*_nav_lfo[3])() = {nullptr};
};
*/
LFOMenuRouter lf = LFOMenuRouter();

class SongMenuRouter{
public:
    SongMenuRouter() {}

    void show() {
        if (_nav_song[sublevels[1]]) {
            _nav_song[sublevels[1]]();
        }
    }

    void attach_nav_songs_menu(uint8_t index, void (*cb)())
    {
        if (index < truesizeofSongmenulabels)
            _nav_song[index] = cb;
    }

private:
void (*_nav_song[truesizeofSongmenulabels])() = {nullptr};
};

SongMenuRouter sg = SongMenuRouter();
