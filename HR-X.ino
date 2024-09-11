

const int display_lag = 10 ;
const int control_lag = 10 ;
#include "muxer.h"
Muxer Muxer;
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
int millitickinterval = 115;
//freeze, can't record wav
//#include <MsTimer2.h>
bool done_once ;
//not precise
//Metro metro0 = Metro(millitickinterval);
//Metro metro303 = Metro(25);
//#include <IntervalTimer.h>

#include <BlockNot.h>

BlockNot blinkTimer(millitickinterval);

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

bool rec_looping;
int tocker ;
byte filter_lfo_option = 3 ;
int le303ffilterzVknobs[3];

byte songpage = 0;
byte samplelinerspage;
byte lqcurrentpqt = 0;
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
const int fxiterations = 3;
bool pre_record = false ;
int delaymultiplier[fxiterations] = {55};
const int sizeopremixtoM = 9 * fxiterations;
const int sizeopremixWtoM = 9 * fxiterations;
const int sizeofxcords = 9 * fxiterations * 2 * 3;
byte fxmoduleiteration;
bool fxcordingisconnected[sizeofxcords];
// wet channel-1 used by effect instance start from 0 4 disabled add 1 for real
// wet channel
int fxmoduleisconnected[mainmenufxlistsize - 1][fxiterations] = {fxiterations +
                                                                 1};
// premix , fxcording
int fxslotMaster[3][2];
float interpot;
bool overdubmidi;
bool noteprint = 0;
int moduleonfxline[3][2] = {{mainmenufxlistsize - 1, 0},
                            {mainmenufxlistsize - 1, 0},
                            {mainmenufxlistsize - 1, 0}};
//char Patternfiledir[26] = {"PATTERNS/"};
String Patternfiledir = "PATTERNS/" ;
// not EXTMEM for now
EXTMEM char Patternfilename[999][13];
EXTMEM char Patternfilefullpath[999][22];
EXTMEM char Patternfilebase[999][9];
EXTMEM bool Patternfilesselected[999];
byte leeffectID[fxiterations];
int numberofPatternfilesselected = 0;
int numberofPatternfiles = 0;
bool demimalmode;
bool addinglenght;
EXTMEM char sampledirpath[99] = {"SOUNDSET/"};
float freespace;
//char SynthPresetdir[32] = {"PRESETS/SYNTH/"};
String SynthPresetdir = "PRESETS/SYNTH/" ;
// not EXTMEM for now
EXTMEM char SynthPresetname[999][13];
EXTMEM char SynthPresetfullpath[999][28];
EXTMEM char SynthPresetbase[999][9];

int presets_count = 0;
const byte truesizeofwaveformsmenulabels = 7;
EXTMEM char Waveformsname[999][13];
EXTMEM char Waveformsfullpath[999][22];
EXTMEM char Waveformsbase[999][9];
EXTMEM bool Waveformsselected[999];
int numberofWaveformsselected = 0;
int numberofWaveforms = 0;
char Waveformsdir[10] = {"WAVEFORM/"};
String newloopedpath = "SOUNDSET/REC/LOOP00#L.RAW";
String newRecpathL = "SOUNDSET/REC/RECZ00#L.RAW";
String newRecpathR = "SOUNDSET/REC/RECZ00#R.RAW";
int navlevelvbuttons = 1;
const int numberofvbuttonslabels = 8;
byte vbuttonsCC[numberofvbuttonslabels + 14 + 17];
byte vPots[17] = {0};

// float angleofknob = 3.1416 ;

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
int bqstage[fxiterations];
// [lebiquad] [stage]
float bqslope[fxiterations][bqstagesnum] = {0.5};
float bqgain[fxiterations][bqstagesnum];
float bqfreq[fxiterations][bqstagesnum] = {300};
int bqtype[fxiterations][bqstagesnum];
// [lebiquad] [lestage] freq slope gain
int bqVpot[fxiterations][bqstagesnum][3];
// max bqfreq (in Hz) wich will be multiplied by the CC (from 0 to 127) + 300Hz
// ---> because of the poor biquad response below 400hz
int bqrange = 20000;

EXTMEM char Flashsamplename[999][13];
EXTMEM char Flashsamplebase[999][9];
EXTMEM bool Flashsamplesselected[999];
int numberofFlashsamplesselected = 0;
int numberofFlashfiles = 0;
// changed from int to byte seems fine

int Sampleassigned[128];
//char newmkdirpath[18] = {"SOUNDSET/MABANK00"};
String newmkdirpath = "SOUNDSET/MABANK01" ;
char newmksamplefullpath[32] = {"SOUNDSET/MABANK01/SAMPLE00.RAW"};

#include "/home/kosmin/HR-X/includes/images.ino"
#include "/home/kosmin/HR-X/includes/notestofrequency.ino"
#include "ParserLib.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Bounce.h>
#include <Encoder.h>
#include <string.h>
const int liners_count = 6;
const int nombreofSamplerliners = 16;
const byte synths_count = 3;
const int patternlines = 4;
bool tb303[liners_count];
long le303start[liners_count];
BlockNot blink303_1(le303pulsewidth);
BlockNot blink303_2(le303pulsewidth);
BlockNot blink303_3(le303pulsewidth);
BlockNot blink303_4(le303pulsewidth);
BlockNot blink303_5(le303pulsewidth);
BlockNot blink303_6(le303pulsewidth);
BlockNot* blink303[liners_count] = {&blink303_1,&blink303_2,&blink303_3,&blink303_4,&blink303_5,&blink303_6};
byte bufferLoop[512];
// used in recording
EXTMEM byte bufferL[512];
EXTMEM byte bufferR[512];

const int numbofsettinglabels = 14;
int samplermidichannel = 8;
byte synthmidichannel = 16;

byte navrec = 3;
// various hard to pass params
int leresultar2[2];
int leresultnons[2];
int availablliner;
// unsigned long capturedlenghtnote[liners_count][2];
// int startingPosofNoteonliner[liners_count];
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
EXTMEM char receivedbitinchar[parsingbuffersize];

// = 89.6 ( 1.02678 ) 92 original
// sets analog flashsample player, 1 = digital-onOff, 0 = analog-sensitive

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
//GFXcanvas1 canvasBIG2(128, 64);
// SD on audio board
#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 7
#define SDCARD_SCK_PIN 14
// idx tick cc,val

short lefakeselector;
// File rootsd;
const int chipSelect = 10;
int numTabs = 0;

GFXcanvas1 canvastitle(128, 16);

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
Bounce clicked = Bounce(32, 50);
// Bounce Menub = Bounce( 29, 5 );
// Bounce Backb = Bounce( 41, 5 );
// Bounce buttonRecord = Bounce(34, 8);
// Bounce buttonStop =   Bounce(35, 8);  // 8 = 8 ms debounce time
// Bounce buttonPlay =  clicked;
Encoder myEnc(30, 31);
const unsigned int manyinputpins = 1;
const int inputpins[manyinputpins] = {32};
// which input on the audio shield will be used?
const int myInput = AUDIO_INPUT_LINEIN;
// rotary encoder
int startingnoteline;

int vraipos = 0;
int oldvraipos = 0;
int oldPosition = -999;
int count = 0;
float notefrequency = 440.0;
int newPosition = 0;
int filelenght;
bool selectedFileorDir;

// char leselecteddir[99] = {"/"};
float smallfloat;
// short knobcontrolled[4] = {0,1,0,0} ;

int16_t myCustomWaveform[256] = {
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  -32768, -32768, -32768, -32768, -32768, -32768, -32768,
    -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
    -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
    -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
    -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
    -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
    -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
    -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
    -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
    -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
    -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
    -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
    -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
    -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
    -32768, -32768, -32768, -32768};

const int lesformes[9] PROGMEM = {
    WAVEFORM_SINE,     WAVEFORM_SAWTOOTH,          WAVEFORM_SAWTOOTH_REVERSE,
    WAVEFORM_TRIANGLE, WAVEFORM_TRIANGLE_VARIABLE, WAVEFORM_SQUARE,
    WAVEFORM_PULSE,    WAVEFORM_ARBITRARY,         WAVEFORM_SAMPLE_HOLD};

const byte truesizeofpresetmenulabels = 5;

byte waveformIndex = 0 ;

int16_t arbitrary_waveforms[synths_count][256] ; 

byte lavalue;

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

const byte truesizeofwavelineslabels = 8;

int phaselevelsL[synths_count] = {0, 0, 0};

int LFOphase[synths_count] = {0,0,0};
const byte sizeofLFOlabels = 9;

byte LFOmenuroot = 2;
// TODO check offset of 50 ?
int LFOoffset[synths_count] = {50,50,50};
byte LFOformstype[synths_count] = {0, 0, 0};
float LFOfreqs[synths_count] = {2.17, 2.17, 2.17};
int LFOlevel[synths_count] = {100,100,100};
bool LFOsync[synths_count];

byte wave1offset[synths_count] = {64,64,64};
File mytxtFile;
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

// TODO
//const char ControlList[allfxes][23] PROGMEM = {
const char ControlList[allfxes][21] = {
    // 0
    "None", "Volume","SynthLevel", "FlashLevel", "AuxLevel", "Fx1Level",
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
    "Attack", "Hold", "Decay", "Sustain", "granularOn", "Release",
    "303ffilterz[0]", "303fgainz[1]", "303fgainz[2]", "FXChannelselector",
    // 70
    "chorusVknobs[i]", "bqstage[i]", "LFOonfilterz[i]", "bqVpot[i][j][0]", "bqVpot[i][j][1]", "bqVpot[i][j][2]",
    "grlrGrain", "grlrRatio", "gShift-T", "gFreeze-T",
    // 80
    "reverbVknobs[i][0]", "reverbVknobs[i][1]", "bitcrush[i][0]",  "bitcrush[i][1]", "mixVknobs[i][0]", 
    "mix[i][1]", "mix[i][2]", "filter[i][0]", "filterVknobs[i][1]", "filterVknobs[i][2]",
    // 90
    "flanger[i][0]", "flanger[i][1]", "flanger[i][2]","DelayFreq[i][0]", "DelayMult[i][1]", "DelayFeed[i][2]",
    "bqtype[i][bqstage]", "Audio In level", "Free", "Free","BPM",
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

bool granular_shifting[fxiterations] = {0,0,0};
bool granular_freezing[fxiterations] = {0,0,0};
bool granular_toggled[fxiterations] = {0,0,0};
char leparsed[3];
short lecaractere;
short letempspattern;
short linerpat;
int previousTp;
const byte sizeofoptionspattern = 5;
const char optionspatternlabels[sizeofoptionspattern][12] PROGMEM = {
    "Transpose", "Shift", "Clear", "Target", "Smooth CC"};
const byte sizeofpatternlistlabels = 8;

const char *monthName[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                       "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
bool debug_cpu = false;
byte bitcrusherVknobs[fxiterations][2];
byte granularVknobs[fxiterations][2];
byte flangerVknobs[fxiterations][3];
byte delayVknobs[fxiterations][3];
byte chorusVknobs[fxiterations];
byte reverbVknobs[fxiterations][2];
SerialFlashFile dummy_flash_file ;
File dummyier_file ;
// char* filespath[] = {(char*)"/",};
//tracks of the sequencer
const int sizeofsoundlines = 4;
char soundlines[sizeofsoundlines][12] = {"Synth", "Sampler", "AudioIn",
                                         "SDcard"};
// 4 is none
int LFOonfilterz[fxiterations] = {3};
// fq res oct 127
byte ffilterzVknobs[fxiterations][3];
// LP BP HP 127
int mixffilterzVknobs[fxiterations][3];

float filterzgainz[fxiterations][3];

float filterzfreq[fxiterations];
float filterzreso[fxiterations] = {0.7};
float filterzoctv[fxiterations];

int filterzrange = 14000;

const int mainfxlines = 3;

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
byte notesOn[liners_count] = {0};
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
// 12800 enough for 290 ms at 44.1 kHz
int16_t granularMemory[GRANULAR_MEMORY_SIZE];
int16_t granularMemory2[GRANULAR_MEMORY_SIZE];
int16_t granularMemory3[GRANULAR_MEMORY_SIZE];
// int16_t granularMemory4[GRANULAR_MEMORY_SIZE];

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

int16_t waveformed_sine[256] = {
    0,     201,   402,   603,   804,   1005,  1206,  1406,  1607,  1808,  2008,
    2209,  2409,  2609,  2809,  3009,  3209,  3409,  3608,  3808,  4007,  4206,
    4405,  4603,  4802,  5000,  5199,  5397,  5594,  5792,  5989,  6186,  6383,
    6580,  6776,  6972,  7168,  7363,  7559,  7753,  7948,  8142,  8336,  8529,
    8722,  8915,  9107,  9299,  9490,  9681,  9871,  10061, 10251, 10440, 10628,
    10817, 11004, 11191, 11378, 11564, 11750, 11935, 12119, 12303, 12487, 12670,
    12852, 13034, 13215, 13396, 13576, 13755, 13934, 14112, 14290, 14467, 14643,
    14819, 14994, 15168, 15342, 15515, 15687, 15859, 16030, 16200, 16370, 16539,
    16707, 16875, 17042, 17208, 17374, 17539, 17703, 17867, 18029, 18191, 18353,
    18513, 18673, 18832, 18990, 19148, 19304, 19460, 19615, 19770, 19923, 20076,
    20228, 20380, 20530, 20680, 20829, 20977, 21124, 21270, 21416, 21560, 21704,
    21847, 21989, 22131, 22271, 22411, 22549, 22687, 22824, 22960, 23095, 23229,
    23362, 23494, 23626, 23756, 23886, 24014, 24142, 24268, 24394, 24518, 24642,
    24765, 24887, 25007, 25127, 25245, 25363, 25479, 25595, 25709, 25823, 25935,
    26047, 26157, 26266, 26375, 26482, 26589, 26694, 26798, 26901, 27004, 27105,
    27205, 27304, 27402, 27499, 27595, 27689, 27783, 27876, 27967, 28058, 28147,
    28236, 28323, 28409, 28494, 28578, 28660, 28742, 28823, 28902, 28980, 29057,
    29133, 29208, 29281, 29354, 29425, 29495, 29564, 29632, 29699, 29764, 29828,
    29891, 29953, 30014, 30074, 30132, 30189, 30245, 30299, 30353, 30405, 30456,
    30506, 30554, 30601, 30647, 30691, 30735, 30777, 30818, 30857, 30896, 30933,
    30968, 31003, 31036, 31068, 31098, 31127, 31155, 31182, 31207, 31231, 31253,
    31275, 31294, 31313, 31330, 31346, 31361, 31374, 31386, 31397, 31406, 31414,
    31420, 31426, 31430, 31433, 31434, 31435, 31434, 31432, 31428, 31423, 31417,
    31409, 31400, 31389};
    
