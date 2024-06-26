
#include "muxer.h"
Muxer Muxer;
//adcHighPassFilterDisable();
#include <Metro.h>
//int startccrecordpos;
//int stopccrecordpos;
const byte sizeofnoCCrecord = 4 ;
//functions that have system or various controls that are ignored for some ops
byte noCCrecord[sizeofnoCCrecord] = {37,39,44,1 };
byte slope1=10;
byte slope2=10;
byte cutoffmode;
byte resonancemode;
byte paramse1;
byte paramse2 ;
bool externalticker;
int starttaptime;
int numberoftaps;
int tapstime[5]={0} ;
float tapaverage ;
int millitickinterval = 125;
Metro metro0 = Metro(millitickinterval); 
Metro metro303 = Metro(25);
//IntervalTimer playNoteTimer;
//Metro metrobuttons = Metro(20); 
long le303start[8] ;
byte smixervknobs[16]={128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128};
int lehalfbeat ;
int le303pulsewidthmultiplier = 8 ;
int le303pulsewidthmultiplier2 = 8 ;
int le303pulsewidth =(int)((le303pulsewidthmultiplier/32.0)*2 * millitickinterval + 50 );
int le303pulsewidth2 =(int)((le303pulsewidthmultiplier2/32.0)*2 * millitickinterval + 50 );
byte offsetliner ;
bool tb303[8] ;
int le303ffilterzVknobs[3];
const byte numberofsynthsw = 4 ;
byte songpage=0;
byte samplelinerspage;
byte lqcurrentpqt = 0;
// LP BP HP 127
int mixle303ffilterzVknobs[3];
byte navrecmenu = 2;
 int laCCduration;
    int letempipolate ;
float interpolcoeff ;
byte settointerpolate[128];
EXTMEM byte leccinterpolated[128] ;
bool interpolOn=1 ;
float le303filterzgainz[3]={1.0,0,0} ;
int le303filterzwet;
float le303filterzfreq = 10000;
float le303filterzreso = 0.7 ;
float le303filterzoctv = 0.25 ;
bool clearsaniloop ;
int le303filterzrange = 10000 ;
//float targetBPM = 120.0 ;
float BPMs = (60000.0/millitickinterval)/4.0 ;
const int pbars = 32 ;
//not sure if used
unsigned long latimeline ;
 //unsigned long latimelineshifter = ((60000/19200)*pbars) ;
bool SendMidiOut ;
// unsigned long tickerf = millis();  ;
#include <MIDIUSB.h>
char arranged_buttons[6][6] = {
  {1,5,9,13,32,23,},
  {2,6,10,14,33,24,},
  {3,7,11,15,34,25,},
  {4,8,12,16,35,36,},
  {26,27,28,29,30,31,},
  {17,18,19,20,21,22}
};
const unsigned short all_buttonns = 49;
int pot_assignements[all_buttonns] = {10};
int muxed_pots[15]={10,12,11,16,15,14,19,18,17,13,24,22,23,21,20};
int potsboards[all_buttonns] = {2,1,9,5,4,3,8,7,6,14,13,11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,12,10};
byte muxed_channels[15]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
bool recorderstop;
bool recorderrecord;
bool recorderplay;

bool patternOn ;

byte but_channel[all_buttonns] = {1,1,1,1,1,1,1,1,1,1,1,1,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,1,1,1};
byte but_velocity[all_buttonns] = {127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,127,127,127};

const int mainmenufxlistsize = 10;
char consolemsg[10][32] ;

int waits=0 ;
char pleasewaitarray[10][32] ;
const int fxiterations = 3;

int delaymultiplier[fxiterations] = {55} ;
const int sizeopremixtoM = 9*fxiterations ;
const int sizeopremixWtoM = 9*fxiterations ;
const int sizeofxcords = 9*fxiterations*2*3 ;
byte fxmoduleiteration ;
bool fxcordingisconnected[sizeofxcords] ;
//wet channel-1 used by effect instance start from 0 4 disabled add 1 for real wet channel
int fxmoduleisconnected[mainmenufxlistsize-1][fxiterations]={fxiterations+1} ;
 //premix , fxcording
int fxslotMaster[3][2];
float interpot;
bool overdubmidi ;
bool noteprint = 0 ;
int moduleonfxline[3][2] = {{mainmenufxlistsize-1,0},{mainmenufxlistsize-1,0},{mainmenufxlistsize-1,0}};
char Patternfiledir[26] = {"PATTERNS/"};
//not EXTMEM for now
EXTMEM char Patternfilename[999][13];
EXTMEM char Patternfilefullpath[999][22];
EXTMEM char Patternfilebase[999][9];
EXTMEM bool Patternfilesselected[999];
byte leeffectID[fxiterations] ;
int numberofPatternfilesselected = 0 ;
int numberofPatternfiles = 0 ;
int patterndizaines = 0 ;
int patternunites = 0 ;
char newpatternpath[28] = {"PATTERNS/PATERN01.TXT"};
bool demimalmode ;
bool addinglenght ;
EXTMEM char sampledirpath[99] = {"SOUNDSET/"};
float freespace;
char SynthPresetdir[32] = {"PRESETS/SYNTH/"};
//not EXTMEM for now
EXTMEM char SynthPresetname[999][13];
EXTMEM char SynthPresetfullpath[999][28];
EXTMEM char SynthPresetbase[999][9];
EXTMEM bool SynthPresetsselected[999];

int numberofSynthPresetsselected = 0 ;
int numberofSynthPresets = 0 ;
int synsetdizaines = 0 ;
int synsetunites = 0 ;
char newpresetpath[28] = {"PRESETS/SYNTH/SYNSET01.TXT"};
char newRecpathL[28] = {"SOUNDSET/REC/RECZ00#L.RAW"};
char newRecpathR[28] = {"SOUNDSET/REC/RECZ00#R.RAW"};
int navlevelvbuttons = 1 ;
const int numberofvbuttonslabels = 8 ;
byte vbuttonsCC[numberofvbuttonslabels+14+17];
byte vPots[17]= {0} ;

//float angleofknob = 3.1416 ;


byte tapnote = byte(3);
bool tapstarted ;

byte preampleswaves = 64;

const byte szsset = 99 ;
const byte ssnamsize = 26 ;
EXTMEM char samplefoldersregistered[szsset][ssnamsize];
EXTMEM char samplename[99][999][13];
EXTMEM char samplefullpath[99][999][38];
EXTMEM char samplebase[99][999][9];
//EXTMEM char lefilenamed[99][999][13];
EXTMEM int sizeofsamplefolder[99];
int sampledirsregistered = 0 ;
EXTMEM bool samplesselected[99][999];
EXTMEM int numberofsamplesselected[99] ;
EXTMEM bool samplesfoldersselected[99];
EXTMEM int numofsamplesfoldersselected = 0 ;
#include "/home/kosmin/HR-X/includes/AudioSetup.ino"
//current stage to configure [lebiquad] instance
const int bqstagesnum = 4 ;
int bqstage[fxiterations] ;
// [lebiquad] [stage]
float bqslope[fxiterations][bqstagesnum] ={0.5} ;
float bqgain[fxiterations][bqstagesnum]  ;
float bqfreq[fxiterations][bqstagesnum]={300}  ;
int bqtype[fxiterations][bqstagesnum] ;
// [lebiquad] [lestage] freq slope gain 
int bqVpot[fxiterations][bqstagesnum][3] ;
// max bqfreq (in Hz) wich will be multiplied by the CC (from 0 to 127) + 300Hz ---> because of the poor biquad response below 400hz
int bqrange = 20000 ;

EXTMEM char Flashsamplename[999][13];
EXTMEM char Flashsamplebase[999][9];
EXTMEM bool Flashsamplesselected[999];
int numberofFlashsamplesselected = 0 ;
int numberofFlashfiles = 0 ;
//changed from int to byte seems fine

int Sampleassigned[128];
char newmkdirpath[18] = {"SOUNDSET/MABANK00"};
char newmksamplefullpath[32] = {"SOUNDSET/MABANK00/SAMPLE00.RAW"};

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Bounce.h>
#include <Encoder.h>
#include "ParserLib.h"
#include "/home/kosmin/HR-X/includes/images.ino"
#include "/home/kosmin/HR-X/includes/notestofrequency.ino"
#include <string.h>
const int nombreofliners = 8 ;
const int nombreofSamplerliners = 16 ;
const int patternlines = 4 ;

EXTMEM byte bufferL[512];
EXTMEM byte bufferR[512];
    
const int numbofsettinglabels = 14 ;
int samplermidichannel = 8 ;
byte synthmidichannel = 16 ;

byte navrec = 3;
//various hard to pass params
int leresultar2[2];
int leresultnons[2];
int availablliner;
//unsigned long capturedlenghtnote[nombreofliners][2];
//int startingPosofNoteonliner[nombreofliners];
int tickposition ;
bool stoptick;

bool arpegiatorOn=0;
// 8 is off
byte arpegiatortype = 8;


byte arpeglengh = 0 ;

//bool gammedirection[nombreofarpeglines] ;
byte arpegmode = 4 ;
byte arpegnumofnotes = 7;
byte arpegstartoffset = 0 ;
byte arpeggridC ;
int lfo303levshiter ;
byte arpeggridS ;
bool stoptickernextcycle ;
//unsigned long millisSincenLinerOn[nombreofliners];
//unsigned long currentnotelength[nombreofliners];
bool patrecord;
byte arpegiatingNote[nombreofliners] ;
//note , veloc
const int nombreofarpeglines = nombreofliners ;
bool tripletdirection[nombreofarpeglines];
byte playingarpegiator[nombreofarpeglines][nombreofliners];
byte calledarpegenote[nombreofarpeglines][2];
byte tickgamme[nombreofarpeglines] ;
byte ticktriplet[nombreofarpeglines] ;
byte arpegnoteoffin[nombreofarpeglines][nombreofliners]={1};
byte arpegnotestick[nombreofarpeglines];
byte arpegemptyticks[nombreofarpeglines];
bool digitalplay = 0 ;
bool lefadout[nombreofliners] ;
bool targetNOsampler ;
bool targetNOsynth ;
bool targetNOcc ;

byte glidemode = 0 ;
byte lapreviousnotew ;
bool dogliding[nombreofliners] ;
int leglidershift;
int leglideposition[nombreofliners] ;
int leglidenoteshift ;
float glidefactor ;

byte lapreviousnotewCmode[nombreofliners] ;
int leglidershiftCmode[nombreofliners];
int leglidenoteshiftCmode[nombreofliners] ;
float glidefactorCmode[nombreofliners] ;
byte ccsynthselector;
byte ccfxlineselector;

//lenght of the current interpolation
// from leinterpolstart to [1] interpole target position
byte Ccinterpolengh[128][3];

const int parsingbuffersize = 8192;
int parsinglength = parsingbuffersize;
EXTMEM char receivedbitinchar[parsingbuffersize];

// = 89.6 ( 1.02678 ) 92 original
//sets analog flashsample player, 1 = digital-onOff, 0 = analog-sensitive 

bool debugmidion = 0 ;
bool freezemidicc = 0 ;
int navlevelpatedit = 2;

bool evented1[patternlines][pbars]={0};

EXTMEM byte event1notes1[nombreofliners][pbars][3];
EXTMEM byte tempevent1notes1[nombreofliners][pbars][3];
EXTMEM byte event1notesOff[nombreofliners][pbars][3];
EXTMEM byte parsedevent1notesOff[nombreofliners][pbars][3];
EXTMEM int length0pbars[nombreofliners][pbars];
EXTMEM int templength0pbars[nombreofliners][pbars];
EXTMEM int length1notes1[nombreofliners][pbars];
byte event1startpos[nombreofliners];

EXTMEM byte event2notes1[nombreofSamplerliners][pbars][3];
EXTMEM byte tempevent2notes1[nombreofSamplerliners][pbars][3];
//EXTMEM unsigned long length2notes1[nombreofSamplerliners][pbars];
//EXTMEM unsigned int length2pbars[nombreofSamplerliners][pbars];
//EXTMEM unsigned int templength2pbars[nombreofSamplerliners][pbars];
EXTMEM byte event2notesOff[pbars][3];

int howmanyactiveccnow ;
int tickerlasttick ;
//EXTMEM short activeevent1controllers[128][pbars];
EXTMEM byte event1controllers[128][pbars];
//EXTMEM short nextevent1controllers[128][pbars];
bool activateinterpolatecc[128] ;
bool recordCC ;
bool ignorethatcc[128] ;
bool ccoverdub ;
bool recpaterninit;
int lavelocity;

int availableliner;
int olderliner;


byte fffnote ;
 byte cellsizer = 3 ;
 byte celltall = 9 ;
 byte startx = 8;
 byte starty = 18 ;


GFXcanvas1 canvasBIG(128, 64);
GFXcanvas1 canvasBIG2(128, 64);
// SD on audio board
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

short lefakeselector ;
//File rootsd;
const int chipSelect = 10;
int numTabs = 0 ;


 GFXcanvas1 canvastitle(128, 16);
 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire2, OLED_RESET);


#define LOGO_HEIGHT   32
#define LOGO_WIDTH    64
//File lesfiles[999];
//EXTMEM char lesfileslist[999][99];
//EXTMEM char lesfolderslist[99][99];
//File lesfolders[99];
File myMidiFile ;
int filecount ;
int keepcount;
Bounce clicked = Bounce( 32, 50 );
//Bounce Menub = Bounce( 29, 5 );
//Bounce Backb = Bounce( 41, 5 );
//Bounce buttonRecord = Bounce(34, 8);
//Bounce buttonStop =   Bounce(35, 8);  // 8 = 8 ms debounce time
//Bounce buttonPlay =  clicked;
Encoder myEnc(30, 31);
const unsigned int manyinputpins = 1 ;
const int inputpins[manyinputpins] = {32};
// which input on the audio shield will be used?
const int myInput = AUDIO_INPUT_LINEIN;
//rotary encoder
int startingnoteline ;

int vraipos = 0 ;
int oldvraipos = 0;
int oldPosition  = -999;
int count = 0;
float notefrequency= 440.0;
int newPosition = 0;
int filelenght;
bool selectedFileorDir ;

//char leselecteddir[99] = {"/"};

int knobs[4] = {0,0,0,0} ;
float smallfloat ;
//short knobcontrolled[4] = {0,1,0,0} ;
const int lesformes[9] PROGMEM = { WAVEFORM_SINE, WAVEFORM_SAWTOOTH, WAVEFORM_SAWTOOTH_REVERSE , WAVEFORM_TRIANGLE , WAVEFORM_TRIANGLE_VARIABLE,
                  WAVEFORM_SQUARE , WAVEFORM_PULSE ,WAVEFORM_ARBITRARY ,WAVEFORM_SAMPLE_HOLD
                  };


const byte truesizeofpresetmenulabels = 5;

byte activewave = 0 ;
byte lavalue ;

const byte leschords[6][12][3] PROGMEM = {{{0,4,7},{1,5,8},{2,6,9},{3,7,10},{4,8,11},{5,9,12},{6,10,13},{7,11,14},{8,12,15},{9,13,16},{10,14,17},{11,15,18}},
                                {{0,3,7},{1,4,8},{2,5,9},{3,6,10},{4,7,11},{5,8,12},{6,9,13},{7,10,14},{8,11,15},{9,12,16},{10,13,17},{11,14,18}},
                                {{0,3,6},{1,4,7},{2,5,8},{3,6,9},{4,7,10},{5,8,11},{6,9,12},{7,10,13},{8,11,14},{9,12,15},{10,13,16},{11,14,17}},
                                {{0,4,8},{1,5,9},{2,6,10},{3,7,11},{4,8,12},{5,9,13},{6,10,14},{7,11,15},{8,12,16},{9,13,17},{10,14,18},{11,15,19}},
                                {{0,2,7},{1,3,8},{2,4,9},{3,5,10},{4,6,11},{5,7,12},{6,8,13},{7,9,14},{8,10,15},{9,11,16},{10,12,17},{11,13,18}},
                                {{0,5,7},{1,6,8},{2,7,9},{3,8,10},{4,9,11},{5,10,12},{6,11,13},{7,12,14},{8,13,15},{9,14,16},{10,15,17},{11,16,18}}
                                                                                                                                                  } ;
  
// C Ionian     { C maj;  D min;  E min;  F maj;  G maj;  A min;  B dim  }
//const chord ionian[7]     = {{0, maj},    {2, minor}, {4, minor}, {5, maj},   {7, maj},   {9, minor}, {11, dim}};
//                            {0,4,7} ,   {2,5,9},    {4,7,11}    {5,9,12},   {7,11,14},   {9,12,16}, {11,14,17}
const byte *event_ionian[7] = { leschords[0][0] , leschords[1][2], leschords[1][4], leschords[0][5], leschords[0][7], leschords[1][9], leschords[2][11] } ;
// C Dorian     { C min;  D min;  D♯ maj; F maj;  G min;  A dim;  A♯ maj  }
//const chord dorian[7]     = {{0, minor},  {2, minor}, {3, maj},   {5, maj},   {7, minor}, {9, dim},   {10, maj}};
const byte *event_dorian[7] = { leschords[1][0] , leschords[1][2] , leschords[0][3] , leschords[0][5] , leschords[1][7] , leschords[2][9] , leschords[0][10] } ;
//C Phrygian    { C min;  C♯ maj; D♯ maj; F min;  G dim;  G♯ maj; A♯ min  }
//const chord phrygian[7]   = {{0, minor},  {1, maj},   {3, maj},   {5, minor}, {7, dim},   {8, maj},   {10, minor}};
const byte *event_phrygian[7] = { leschords[1][0] , leschords[0][1] , leschords[0][3] , leschords[1][5] , leschords[2][7] , leschords[0][8] , leschords[1][10] } ;
//C Lydian      { C maj;  D maj;  E min;  F♯ dim; G maj;  A min;  B min   }
//const chord lydian[7]     = {{0, maj},    {2, maj},   {4, minor}, {6, dim},   {7, maj},   {9, minor}, {11, minor}};
const byte *event_lydian[7] = { leschords[0][0] , leschords[0][2] , leschords[1][4] , leschords[2][6] , leschords[0][7] , leschords[1][9] , leschords[1][11] } ;
//C Mixolydian  { C maj;  D min;  E dim;  F maj;  G min;  A min;  A♯ maj  }
const byte *event_mixolydian[7] = { leschords[0][0] , leschords[1][2] , leschords[2][4] , leschords[0][5] , leschords[1][7] , leschords[1][9] , leschords[0][10] };
//const chord mixolydian[7] = {{0, maj},    {2, minor}, {4, dim},   {5, maj},   {7, minor}, {9, minor}, {10, maj}};
//C Aeolian     { C min;  D dim;  D♯ maj; F min;  G min;  G♯ maj; A♯ maj  }
//const chord aeolian[7]    = {{0, minor},  {2, dim},   {3, maj},   {5, minor}, {7, minor}, {8, maj},   {10, maj}};
const byte *event_aeolian[7] = { leschords[1][0] , leschords[2][2] , leschords[0][3] , leschords[1][5] , leschords[1][7] , leschords[0][8] , leschords[0][10] } ;
//C harmonic    { C min;  D dim;  D♯ aug; F min;  G maj;  G♯ maj; B dim   }
//const chord harmonic[7]   = {{0, minor},  {2, dim},   {3, aug},   {5, minor}, {7, maj},   {8, maj},   {11, dim}};
const byte *event_harmonic[7] = { leschords[1][0] ,  leschords[2][2] ,  leschords[3][3] , leschords[1][5] , leschords[0][7] , leschords[0][8] , leschords[2][11] };     
//C Locrian     { C dim;  C♯ maj; D♯ min; F min;  F♯ maj; G♯ maj; A♯ min  }
//const chord locrian[7]    = {{0, dim},    {1, maj},   {3, minor}, {5, minor}, {6, maj},   {8, maj},   {10, minor}};
const byte *event_locrian[7] = { leschords[2][0] , leschords[0][1] , leschords[1][3] , leschords[1][5] , leschords[0][6] , leschords[0][8] , leschords[1][10] } ; 
//const chord *all_chords[8] = {ionian, dorian, phrygian, lydian, mixolydian, aeolian, harmonic, locrian};
const byte **all_arpegios[8] =  {event_ionian, event_dorian, event_phrygian, event_lydian, event_mixolydian, event_aeolian, event_harmonic, event_locrian  } ;
                                                                                         
                     
bool chordson = 0 ;
  byte chordnotes[3];
  byte chordnotesoff[3];
  //6 is off
  byte lasetchord = 6 ;

const byte truesizeofwavelineslabels = 8;

int phaselevelsL[numberofsynthsw] = {0,0,0,0};

int LFOphase[numberofsynthsw] = {0};
const byte sizeofLFOlabels = 9;

byte LFOmenuroot = 2 ;
int LFOoffset[numberofsynthsw] = {50};
byte LFOformstype[numberofsynthsw] = {0,0,0,0};
float LFOfreqs[numberofsynthsw] = {0.5,1.0,2.0,0.5};
int LFOlevel[numberofsynthsw] = {100} ;
bool LFOsync[numberofsynthsw] ;

byte wave1offset[numberofsynthsw]={64} ;
File mytxtFile ;
//File originefile ;
int adsrlevels[6] = {0,5,0,50,100,60} ;
int mappedattack = 5;
int mappeddecay = 50 ;
int mappedrelease = 60;
int mappedsustain = 100; // divide by 100 to float
int MadsrAttackDelay = 0;
int MadsrHold = 0 ;
int navleveloverwrite = 2 ;
 int knobiprev[numberofsynthsw] = {0,0,0,0} ;

const int  allfxes = 146;

#include "pads.h"
Pads Pads;

//TODO

const char ControlList[allfxes][23] PROGMEM = {
 //0
  "None", "SynthLevel", "Volume", "SDPlayer", "wetsynth", "wetsampler", "WetMixM1", "WetMixM2", "WetMixM3", "Sampler level", 
//10
  "slope1", "slope2", "Record Raw", "Play Recorded", "Stop Play&Rec", "BPM", "le303pulse1","le303pulse2", "le303filterzwet ", "Free", 
//20
 "le303filterzfreq", "le303filterzreso", "le303filterzoctv", "glidemode", "preampleswaves", "le303lfointime",  "le303lfoouttime", "arpegiatortype", "arpegmode", "arpegstartoffset",
//30
  "arpegnumofnotes", "arpeggridC", "arpeggridS", "arpeglengh",  "digitalplay",  "CuePlay", "Start", "Stop", "Metronome" , "Capture", 
//40
  "pausedasong", "stopdasong", "playdasong", "Chords", "RecordCC",  "Synthselector", "wavesfreqs", "mixlevelsL","panLs", "FMmodulated",
//50
  "Waveformstyped", "wave1offset", "phaselevelsL", "LFOlevel", "LFOtype", "LFOfreqs", "LFOphase", "LFOoffset","LFOsync", "Attack Delay",
///60
  "Attack", "Hold", "Decay", "Sustain", "Free", "Release", "le303ffilterzVknobs[0]", "le303filterzgainz[1]", "le303filterzgainz[2]", "FXChannelselector",
//70
  "chorusVknobs[i]", "bqstage[i]", "LFOonfilterz[i]", "bqVpot[i][j][0]","bqVpot[i][j][1]", "bqVpot[i][j][2]", "granularVknobs[i][0]", "granularVknobs[i][1]", "granularVknobs[i][2]", "granularVknobs[i][3]",
//80
   "reverbVknobs[i][0]", "reverbVknobs[i][1]", "bitcrusherVknobs[i][0]", "bitcrusherVknobs[i][1]", "mixfilterVknobs[i][0]", "mixfilterVknob[i][2]", "mixfilterVknob[i][2]", "filterVknob[i][0]", "filterVknobs[i][1]", "filterVknobs[i][2]",
//90
   "flangerVknob[i][0]", "flangerVknob[i][1]", "flangerVknob[i][2]", "delayVknobs[i][0]", "delayVknobs[i][1]", "delayVknobs[i][2]", "bqtype[i][bqstage]", "Audio In level", "Free", "Free", 
//100
  "Pat. Save", "Pat. Load", "Free", "Free", "Free", "Phase1", "Wtype2", "Wmix2", "Free", "Free", "Free",
//110
  "Sp.Track 1", "Sp.Track 2", "Sp.Track 3", "Sp.Track 4", "Sp.Track 5", "Sp.Track 6", "Sp.Track 7", "Sp.Track 8", "Sp.Track 9", "Sp.Track 10", 
//120
  "Sp.Track 11", "Sp.Track 12", "Sp.Track 13", "Sp.Track 14", "Sp.Track 15", "Sp.Track 16", "Free", "Free", "Free", "Free", "Free",
//130
  "Free", "Free", "Free", "Wfreq4", "Pan 4", "Phase4"
  };
  
float WetMixMasters[4] = {1.0,0.0,0.0,0.0};



bool patterninparse ;

char leparsed[3] ;
short lecaractere ;
short letempspattern ;
short linerpat ;
int previousTp ;
const byte sizeofoptionspattern = 5;
const char optionspatternlabels[sizeofoptionspattern][12] PROGMEM = {"Transpose","Shift", "Clear", "Target", "Smooth CC" };
const byte sizeofpatternlistlabels = 8;
byte le303envlfofadintime = 32 ;
byte le303envlfofadouttime = 32 ;
char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

byte bitcrusherVknobs[fxiterations][2] ;
byte granularVknobs[fxiterations][4];
byte flangerVknobs[fxiterations][3];
byte delayVknobs[fxiterations][3];
byte chorusVknobs[fxiterations];
byte reverbVknobs[fxiterations][2];

//char* filespath[] = {(char*)"/",};
const int sizeofsoundlines = 4;
char soundlines[sizeofsoundlines][12] = {"Synth", "Sampler", "AudioIn", "SDcard"};
//4 is none
int LFOonfilterz[fxiterations]={3};
//fq res oct 127
byte ffilterzVknobs[fxiterations][3];
// LP BP HP 127
int mixffilterzVknobs[fxiterations][3];

float filterzgainz[fxiterations][3] ;

float filterzfreq[fxiterations] ;
float filterzreso[fxiterations] = {0.7} ;
float filterzoctv[fxiterations] ;

int filterzrange = 14000 ;


const int mainfxlines = 3;

char masterlabels[3][3] = {"m", "w", "s"};

//int shifts ;
int navlevel = 0;
int previousnavlevel = 0;

int ypos ;
bool plusminusmode = 0;
bool rotamode = 1 ;

int navrange = 2; // starts at 0

byte wetins[2];

char lastpathlisted[50];
//char menuitem ;
int knobassigned[4] = {0,0,0,0};
int midiknobs[128];
//int midiknobiprev[128] ;
int midiknobassigned[128];

int sublevels[9]= {0,0,0,0,0,0,0,0,0};
//make it float

float wavesfreqs[numberofsynthsw] = {1.0,1.0,2.0,0.5};
float panLs[numberofsynthsw] = {1,1,1,1};

float mixlevelsL[numberofsynthsw] = {0.1, 0.0, 0.0, 0.0 } ;
// 0 master , 1synth, 2 sampler, 3 unused
byte mixlevelsM[4] = {128, 128, 38, 128} ;

unsigned int Waveformstyped[numberofsynthsw]= {1,11,11,11};
byte notesOn[nombreofliners] = {0};
byte samplesnotesOn[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

AudioEffectEnvelope *enveloppesL[8] = {&envelopeL0, &envelopeL1, &envelopeL2, &envelopeL3, &envelopeL4, &envelopeL5, &envelopeL6, &envelopeL7} ;

//modulator for 303 mode
float ladiff1 ; 
float ladiff2 ;
int letbfreq;

Adafruit_SSD1306 display(128, 64, &Wire2, -1);
char* toprint = (char*)"Cosmix";

bool initdone ;
byte FMmodulated[numberofsynthsw] = {0} ;
#include "/home/kosmin/HR-X/includes/cablages.ino"

#define FLANGE_DELAY_LENGTH (4*AUDIO_BLOCK_SAMPLES)
#define CHORUS_DELAY_LENGTH (8*AUDIO_BLOCK_SAMPLES)
EXTMEM short chorusdelayline[CHORUS_DELAY_LENGTH];
EXTMEM short chorusdelayline2[CHORUS_DELAY_LENGTH];
EXTMEM short chorusdelayline3[CHORUS_DELAY_LENGTH];
//short chorusdelayline4[CHORUS_DELAY_LENGTH];
int chorusvoices = 4; 

EXTMEM short flangedelay[FLANGE_DELAY_LENGTH];
EXTMEM short flangedelay2[FLANGE_DELAY_LENGTH];
EXTMEM short flangedelay3[FLANGE_DELAY_LENGTH];
//short flangedelay4[FLANGE_DELAY_LENGTH];

int flangeoffset = FLANGE_DELAY_LENGTH/4;
int flangedepth = FLANGE_DELAY_LENGTH/4;

double flangefreq = 0.5;

#define GRANULAR_MEMORY_SIZE 640  // enough for 290 ms at 44.1 kHz
EXTMEM int16_t granularMemory[GRANULAR_MEMORY_SIZE];
EXTMEM int16_t granularMemory2[GRANULAR_MEMORY_SIZE];
EXTMEM int16_t granularMemory3[GRANULAR_MEMORY_SIZE];
//int16_t granularMemory4[GRANULAR_MEMORY_SIZE];



AudioConnection          FMWaveCord01(FMWaveform1L1, 0, WavesL1, 0);
AudioConnection          FMWaveCord02(FMWaveform1L2, 0, WavesL2, 0);
AudioConnection          FMWaveCord03(FMWaveform1L3, 0, WavesL3, 0);
AudioConnection          FMWaveCord04(FMWaveform1L4, 0, WavesL4, 0);
AudioConnection          FMWaveCord05(FMWaveform1L5, 0, WavesL5, 0);
AudioConnection          FMWaveCord06(FMWaveform1L6, 0, WavesL6, 0);
AudioConnection          FMWaveCord07(FMWaveform1L7, 0, WavesL7, 0);
AudioConnection          FMWaveCord08(FMWaveform1L8, 0, WavesL8, 0);
AudioConnection          FMWaveCord09(FMWaveform2L1, 0, WavesL1, 1);
AudioConnection          FMWaveCord10(FMWaveform2L2, 0, WavesL2, 1);
AudioConnection          FMWaveCord11(FMWaveform2L3, 0, WavesL3, 1);
AudioConnection          FMWaveCord12(FMWaveform2L4, 0, WavesL4, 1);
AudioConnection          FMWaveCord13(FMWaveform2L5, 0, WavesL5, 1);
AudioConnection          FMWaveCord14(FMWaveform2L6, 0, WavesL6, 1);
AudioConnection          FMWaveCord15(FMWaveform2L7, 0, WavesL7, 1);
AudioConnection          FMWaveCord16(FMWaveform2L8, 0, WavesL8, 1);
AudioConnection          FMWaveCord17(FMWaveform3L1, 0, WavesL1, 2);
AudioConnection          FMWaveCord18(FMWaveform3L2, 0, WavesL2, 2);
AudioConnection          FMWaveCord19(FMWaveform3L3, 0, WavesL3, 2);
AudioConnection          FMWaveCord20(FMWaveform3L4, 0, WavesL4, 2);
AudioConnection          FMWaveCord21(FMWaveform3L5, 0, WavesL5, 2);
AudioConnection          FMWaveCord22(FMWaveform3L6, 0, WavesL6, 2);
AudioConnection          FMWaveCord23(FMWaveform3L7, 0, WavesL7, 2);
AudioConnection          FMWaveCord24(FMWaveform3L8, 0, WavesL8, 2);
AudioConnection          FMWaveCord25(FMWaveform4L1, 0, WavesL1, 3);
AudioConnection          FMWaveCord26(FMWaveform4L2, 0, WavesL2, 3);
AudioConnection          FMWaveCord27(FMWaveform4L3, 0, WavesL3, 3);
AudioConnection          FMWaveCord28(FMWaveform4L4, 0, WavesL4, 3);
AudioConnection          FMWaveCord29(FMWaveform4L5, 0, WavesL5, 3);
AudioConnection          FMWaveCord30(FMWaveform4L6, 0, WavesL6, 3);
AudioConnection          FMWaveCord31(FMWaveform4L7, 0, WavesL7, 3);
AudioConnection          FMWaveCord32(FMWaveform4L8, 0, WavesL8, 3);

AudioConnection          stringCord01(string1L1, 0, WavesL1, 0);
AudioConnection          stringCord02(string1L2, 0, WavesL2, 0);
AudioConnection          stringCord03(string1L3, 0, WavesL3, 0);
AudioConnection          stringCord04(string1L4, 0, WavesL4, 0);
AudioConnection          stringCord05(string1L5, 0, WavesL5, 0);
AudioConnection          stringCord06(string1L6, 0, WavesL6, 0);
AudioConnection          stringCord07(string1L7, 0, WavesL7, 0);
AudioConnection          stringCord08(string1L8, 0, WavesL8, 0);
AudioConnection          stringCord09(string2L1, 0, WavesL1, 1);
AudioConnection          stringCord10(string2L2, 0, WavesL2, 1);
AudioConnection          stringCord11(string2L3, 0, WavesL3, 1);
AudioConnection          stringCord12(string2L4, 0, WavesL4, 1);
AudioConnection          stringCord13(string2L5, 0, WavesL5, 1);
AudioConnection          stringCord14(string2L6, 0, WavesL6, 1);
AudioConnection          stringCord15(string2L7, 0, WavesL7, 1);
AudioConnection          stringCord16(string2L8, 0, WavesL8, 1);
AudioConnection          stringCord17(string3L1, 0, WavesL1, 2);
AudioConnection          stringCord18(string3L2, 0, WavesL2, 2);
AudioConnection          stringCord19(string3L3, 0, WavesL3, 2);
AudioConnection          stringCord20(string3L4, 0, WavesL4, 2);
AudioConnection          stringCord21(string3L5, 0, WavesL5, 2);
AudioConnection          stringCord22(string3L6, 0, WavesL6, 2);
AudioConnection          stringCord23(string3L7, 0, WavesL7, 2);
AudioConnection          stringCord24(string3L8, 0, WavesL8, 2);
AudioConnection          stringCord25(string4L1, 0, WavesL1, 3);
AudioConnection          stringCord26(string4L2, 0, WavesL2, 3);
AudioConnection          stringCord27(string4L3, 0, WavesL3, 3);
AudioConnection          stringCord28(string4L4, 0, WavesL4, 3);
AudioConnection          stringCord29(string4L5, 0, WavesL5, 3);
AudioConnection          stringCord30(string4L6, 0, WavesL6, 3);
AudioConnection          stringCord31(string4L7, 0, WavesL7, 3);
AudioConnection          stringCord32(string4L8, 0, WavesL8, 3);

AudioConnection          drumCord01(drum1L1, 0, WavesL1, 0);
AudioConnection          drumCord02(drum1L2, 0, WavesL2, 0);
AudioConnection          drumCord03(drum1L3, 0, WavesL3, 0);
AudioConnection          drumCord04(drum1L4, 0, WavesL4, 0);
AudioConnection          drumCord05(drum1L5, 0, WavesL5, 0);
AudioConnection          drumCord06(drum1L6, 0, WavesL6, 0);
AudioConnection          drumCord07(drum1L7, 0, WavesL7, 0);
AudioConnection          drumCord08(drum1L8, 0, WavesL8, 0);
AudioConnection          drumCord09(drum2L1, 0, WavesL1, 1);
AudioConnection          drumCord10(drum2L2, 0, WavesL2, 1);
AudioConnection          drumCord11(drum2L3, 0, WavesL3, 1);
AudioConnection          drumCord12(drum2L4, 0, WavesL4, 1);
AudioConnection          drumCord13(drum2L5, 0, WavesL5, 1);
AudioConnection          drumCord14(drum2L6, 0, WavesL6, 1);
AudioConnection          drumCord15(drum2L7, 0, WavesL7, 1);
AudioConnection          drumCord16(drum2L8, 0, WavesL8, 1);
AudioConnection          drumCord17(drum3L1, 0, WavesL1, 2);
AudioConnection          drumCord18(drum3L2, 0, WavesL2, 2);
AudioConnection          drumCord19(drum3L3, 0, WavesL3, 2);
AudioConnection          drumCord20(drum3L4, 0, WavesL4, 2);
AudioConnection          drumCord21(drum3L5, 0, WavesL5, 2);
AudioConnection          drumCord22(drum3L6, 0, WavesL6, 2);
AudioConnection          drumCord23(drum3L7, 0, WavesL7, 2);
AudioConnection          drumCord24(drum3L8, 0, WavesL8, 2);
AudioConnection          drumCord25(drum4L1, 0, WavesL1, 3);
AudioConnection          drumCord26(drum4L2, 0, WavesL2, 3);
AudioConnection          drumCord27(drum4L3, 0, WavesL3, 3);
AudioConnection          drumCord28(drum4L4, 0, WavesL4, 3);
AudioConnection          drumCord29(drum4L5, 0, WavesL5, 3);
AudioConnection          drumCord30(drum4L6, 0, WavesL6, 3);
AudioConnection          drumCord31(drum4L7, 0, WavesL7, 3);
AudioConnection          drumCord32(drum4L8, 0, WavesL8, 3);


AudioConnection          wavelinecord17(waveform1L7, 0, WavesL7, 0);
AudioConnection          wavelinecord18(waveform1L8, 0, WavesL8, 0);
AudioConnection          wavelinecord19(waveform1L5, 0, WavesL5, 0);
AudioConnection          wavelinecord20(waveform1L6, 0, WavesL6, 0);
AudioConnection          wavelinecord21(waveform1L4, 0, WavesL4, 0);
AudioConnection          wavelinecord22(waveform1L2, 0, WavesL2, 0);
AudioConnection          wavelinecord23(waveform1L3, 0, WavesL3, 0);
AudioConnection          wavelinecord24(waveform1L1, 0, WavesL1, 0);
AudioConnection          wavelinecord25(waveform4L7, 0, WavesL7, 3);
AudioConnection          wavelinecord26(waveform4L8, 0, WavesL8, 3);
AudioConnection          wavelinecord27(waveform2L7, 0, WavesL7, 1);
AudioConnection          wavelinecord28(waveform3L7, 0, WavesL7, 2);
AudioConnection          wavelinecord29(waveform2L8, 0, WavesL8, 1);
AudioConnection          wavelinecord30(waveform3L8, 0, WavesL8, 2);
AudioConnection          wavelinecord31(waveform4L5, 0, WavesL5, 3);
AudioConnection          wavelinecord32(waveform4L6, 0, WavesL6, 3);
AudioConnection          wavelinecord33(waveform2L5, 0, WavesL5, 1);
AudioConnection          wavelinecord34(waveform3L5, 0, WavesL5, 2);
AudioConnection          wavelinecord35(waveform2L6, 0, WavesL6, 1);
AudioConnection          wavelinecord36(waveform3L6, 0, WavesL6, 2);
AudioConnection          wavelinecord37(waveform3L3, 0, WavesL3, 2);
AudioConnection          wavelinecord38(waveform4L4, 0, WavesL4, 3);
AudioConnection          wavelinecord39(waveform2L3, 0, WavesL3, 1);
AudioConnection          wavelinecord40(waveform4L3, 0, WavesL3, 3);
AudioConnection          wavelinecord41(waveform2L4, 0, WavesL4, 1);
AudioConnection          wavelinecord42(waveform3L4, 0, WavesL4, 2);
AudioConnection          wavelinecord43(waveform3L2, 0, WavesL2, 2);
AudioConnection          wavelinecord44(waveform3L1, 0, WavesL1, 2);
AudioConnection          wavelinecord45(waveform2L2, 0, WavesL2, 1);
AudioConnection          wavelinecord46(waveform4L2, 0, WavesL2, 3);
AudioConnection          wavelinecord47(waveform2L1, 0, WavesL1, 1);
AudioConnection          wavelinecord48(waveform4L1, 0, WavesL1, 3);



AudioConnection          modulateCord01(modulate1L1, 0, WavesL1, 0);
AudioConnection          modulateCord02(modulate1L2, 0, WavesL2, 0);
AudioConnection          modulateCord03(modulate1L3, 0, WavesL3, 0);
AudioConnection          modulateCord04(modulate1L4, 0, WavesL4, 0);
AudioConnection          modulateCord05(modulate1L5, 0, WavesL5, 0);
AudioConnection          modulateCord06(modulate1L6, 0, WavesL6, 0);
AudioConnection          modulateCord07(modulate1L7, 0, WavesL7, 0);
AudioConnection          modulateCord08(modulate1L8, 0, WavesL8, 0);
AudioConnection          modulateCord09(modulate2L1, 0, WavesL1, 1);
AudioConnection          modulateCord10(modulate2L2, 0, WavesL2, 1);
AudioConnection          modulateCord11(modulate2L3, 0, WavesL3, 1);
AudioConnection          modulateCord12(modulate2L4, 0, WavesL4, 1);
AudioConnection          modulateCord13(modulate2L5, 0, WavesL5, 1);
AudioConnection          modulateCord14(modulate2L6, 0, WavesL6, 1);
AudioConnection          modulateCord15(modulate2L7, 0, WavesL7, 1);
AudioConnection          modulateCord16(modulate2L8, 0, WavesL8, 1);
AudioConnection          modulateCord17(modulate3L1, 0, WavesL1, 2);
AudioConnection          modulateCord18(modulate3L2, 0, WavesL2, 2);
AudioConnection          modulateCord19(modulate3L3, 0, WavesL3, 2);
AudioConnection          modulateCord20(modulate3L4, 0, WavesL4, 2);
AudioConnection          modulateCord21(modulate3L5, 0, WavesL5, 2);
AudioConnection          modulateCord22(modulate3L6, 0, WavesL6, 2);
AudioConnection          modulateCord23(modulate3L7, 0, WavesL7, 2);
AudioConnection          modulateCord24(modulate3L8, 0, WavesL8, 2);
AudioConnection          modulateCord25(modulate4L1, 0, WavesL1, 3);
AudioConnection          modulateCord26(modulate4L2, 0, WavesL2, 3);
AudioConnection          modulateCord27(modulate4L3, 0, WavesL3, 3);
AudioConnection          modulateCord28(modulate4L4, 0, WavesL4, 3);
AudioConnection          modulateCord29(modulate4L5, 0, WavesL5, 3);
AudioConnection          modulateCord30(modulate4L6, 0, WavesL6, 3);
AudioConnection          modulateCord31(modulate4L7, 0, WavesL7, 3);
AudioConnection          modulateCord32(modulate4L8, 0, WavesL8, 3);

AudioConnection          MDdrumCord01(drum1L1, 0, modulate1L1, 0);
AudioConnection          MDdrumCord02(drum1L2, 0, modulate1L2, 0);
AudioConnection          MDdrumCord03(drum1L3, 0, modulate1L3, 0);
AudioConnection          MDdrumCord04(drum1L4, 0, modulate1L4, 0);
AudioConnection          MDdrumCord05(drum1L5, 0, modulate1L5, 0);
AudioConnection          MDdrumCord06(drum1L6, 0, modulate1L6, 0);
AudioConnection          MDdrumCord07(drum1L7, 0, modulate1L7, 0);
AudioConnection          MDdrumCord08(drum1L8, 0, modulate1L8, 0);
AudioConnection          MDdrumCord09(drum2L1, 0, modulate2L1, 0);
AudioConnection          MDdrumCord10(drum2L2, 0, modulate2L2, 0);
AudioConnection          MDdrumCord11(drum2L3, 0, modulate2L3, 0);
AudioConnection          MDdrumCord12(drum2L4, 0, modulate2L4, 0);
AudioConnection          MDdrumCord13(drum2L5, 0, modulate2L5, 0);
AudioConnection          MDdrumCord14(drum2L6, 0, modulate2L6, 0);
AudioConnection          MDdrumCord15(drum2L7, 0, modulate2L7, 0);
AudioConnection          MDdrumCord16(drum2L8, 0, modulate2L8, 0);
AudioConnection          MDdrumCord17(drum3L1, 0, modulate3L1, 0);
AudioConnection          MDdrumCord18(drum3L2, 0, modulate3L2, 0);
AudioConnection          MDdrumCord19(drum3L3, 0, modulate3L3, 0);
AudioConnection          MDdrumCord20(drum3L4, 0, modulate3L4, 0);
AudioConnection          MDdrumCord21(drum3L5, 0, modulate3L5, 0);
AudioConnection          MDdrumCord22(drum3L6, 0, modulate3L6, 0);
AudioConnection          MDdrumCord23(drum3L7, 0, modulate3L7, 0);
AudioConnection          MDdrumCord24(drum3L8, 0, modulate3L8, 0);
AudioConnection          MDdrumCord25(drum4L1, 0, modulate4L1, 0);
AudioConnection          MDdrumCord26(drum4L2, 0, modulate4L2, 0);
AudioConnection          MDdrumCord27(drum4L3, 0, modulate4L3, 0);
AudioConnection          MDdrumCord28(drum4L4, 0, modulate4L4, 0);
AudioConnection          MDdrumCord29(drum4L5, 0, modulate4L5, 0);
AudioConnection          MDdrumCord30(drum4L6, 0, modulate4L6, 0);
AudioConnection          MDdrumCord31(drum4L7, 0, modulate4L7, 0);
AudioConnection          MDdrumCord32(drum4L8, 0, modulate4L8, 0);

AudioConnection          MDstringCord01(string1L1, 0, modulate1L1, 0);
AudioConnection          MDstringCord02(string1L2, 0, modulate1L2, 0);
AudioConnection          MDstringCord03(string1L3, 0, modulate1L3, 0);
AudioConnection          MDstringCord04(string1L4, 0, modulate1L4, 0);
AudioConnection          MDstringCord05(string1L5, 0, modulate1L5, 0);
AudioConnection          MDstringCord06(string1L6, 0, modulate1L6, 0);
AudioConnection          MDstringCord07(string1L7, 0, modulate1L7, 0);
AudioConnection          MDstringCord08(string1L8, 0, modulate1L8, 0);
AudioConnection          MDstringCord09(string2L1, 0, modulate2L1, 0);
AudioConnection          MDstringCord10(string2L2, 0, modulate2L2, 0);
AudioConnection          MDstringCord11(string2L3, 0, modulate2L3, 0);
AudioConnection          MDstringCord12(string2L4, 0, modulate2L4, 0);
AudioConnection          MDstringCord13(string2L5, 0, modulate2L5, 0);
AudioConnection          MDstringCord14(string2L6, 0, modulate2L6, 0);
AudioConnection          MDstringCord15(string2L7, 0, modulate2L7, 0);
AudioConnection          MDstringCord16(string2L8, 0, modulate2L8, 0);
AudioConnection          MDstringCord17(string3L1, 0, modulate3L1, 0);
AudioConnection          MDstringCord18(string3L2, 0, modulate3L2, 0);
AudioConnection          MDstringCord19(string3L3, 0, modulate3L3, 0);
AudioConnection          MDstringCord20(string3L4, 0, modulate3L4, 0);
AudioConnection          MDstringCord21(string3L5, 0, modulate3L5, 0);
AudioConnection          MDstringCord22(string3L6, 0, modulate3L6, 0);
AudioConnection          MDstringCord23(string3L7, 0, modulate3L7, 0);
AudioConnection          MDstringCord24(string3L8, 0, modulate3L8, 0);
AudioConnection          MDstringCord25(string4L1, 0, modulate4L1, 0);
AudioConnection          MDstringCord26(string4L2, 0, modulate4L2, 0);
AudioConnection          MDstringCord27(string4L3, 0, modulate4L3, 0);
AudioConnection          MDstringCord28(string4L4, 0, modulate4L4, 0);
AudioConnection          MDstringCord29(string4L5, 0, modulate4L5, 0);
AudioConnection          MDstringCord30(string4L6, 0, modulate4L6, 0);
AudioConnection          MDstringCord31(string4L7, 0, modulate4L7, 0);
AudioConnection          MDstringCord32(string4L8, 0, modulate4L8, 0);


AudioConnection *stringcords1[32] = { &stringCord01, &stringCord02, &stringCord03, &stringCord04, &stringCord05, &stringCord06, &stringCord07, &stringCord08,
                                     &stringCord09, &stringCord10, &stringCord11, &stringCord12, &stringCord13, &stringCord14, &stringCord15, &stringCord16,
                                     &stringCord17, &stringCord18, &stringCord19, &stringCord20, &stringCord21, &stringCord22, &stringCord23, &stringCord24,
                                     &stringCord25, &stringCord26, &stringCord27, &stringCord28, &stringCord29, &stringCord30, &stringCord31, &stringCord32
                                    };

AudioConnection *drumcords1[32] = { &drumCord01, &drumCord02, &drumCord03, &drumCord04, &drumCord05, &drumCord06, &drumCord07, &drumCord08,
                                     &drumCord09, &drumCord10, &drumCord11, &drumCord12, &drumCord13, &drumCord14, &drumCord15, &drumCord16,
                                     &drumCord17, &drumCord18, &drumCord19, &drumCord20, &drumCord21, &drumCord22, &drumCord23, &drumCord24,
                                     &drumCord25, &drumCord26, &drumCord27, &drumCord28, &drumCord29, &drumCord30, &drumCord31, &drumCord32
                                    };

AudioConnection *modulatecords1[32] = { &modulateCord01, &modulateCord02, &modulateCord03, &modulateCord04, &modulateCord05, &modulateCord06, &modulateCord07, &modulateCord08,
                                     &modulateCord09, &modulateCord10, &modulateCord11, &modulateCord12, &modulateCord13, &modulateCord14, &modulateCord15, &modulateCord16,
                                     &modulateCord17, &modulateCord18, &modulateCord19, &modulateCord20, &modulateCord21, &modulateCord22, &modulateCord23, &modulateCord24,
                                     &modulateCord25, &modulateCord26, &modulateCord27, &modulateCord28, &modulateCord29, &modulateCord30, &modulateCord31, &modulateCord32
                                    };
                                    
AudioConnection *MDdrumcords1[32] = { &MDdrumCord01, &MDdrumCord02, &MDdrumCord03, &MDdrumCord04, &MDdrumCord05, &MDdrumCord06, &MDdrumCord07, &MDdrumCord08,
                                     &MDdrumCord09, &MDdrumCord10, &MDdrumCord11, &MDdrumCord12, &MDdrumCord13, &MDdrumCord14, &MDdrumCord15, &MDdrumCord16,
                                     &MDdrumCord17, &MDdrumCord18, &MDdrumCord19, &MDdrumCord20, &MDdrumCord21, &MDdrumCord22, &MDdrumCord23, &MDdrumCord24,
                                     &MDdrumCord25, &MDdrumCord26, &MDdrumCord27, &MDdrumCord28, &MDdrumCord29, &MDdrumCord30, &MDdrumCord31, &MDdrumCord32
                                    };
                                    
AudioConnection *MDstringcords1[32] = { &MDstringCord01, &MDstringCord02, &MDstringCord03, &MDstringCord04, &MDstringCord05, &MDstringCord06, &MDstringCord07, &MDstringCord08,
                                     &MDstringCord09, &MDstringCord10, &MDstringCord11, &MDstringCord12, &MDstringCord13, &MDstringCord14, &MDstringCord15, &MDstringCord16,
                                     &MDstringCord17, &MDstringCord18, &MDstringCord19, &MDstringCord20, &MDstringCord21, &MDstringCord22, &MDstringCord23, &MDstringCord24,
                                     &MDstringCord25, &MDstringCord26, &MDstringCord27, &MDstringCord28, &MDstringCord29, &MDstringCord30, &MDstringCord31, &MDstringCord32
                                    };
                                    

AudioConnection *FMwavecords1[32] = { &FMWaveCord01, &FMWaveCord02, &FMWaveCord03, &FMWaveCord04, &FMWaveCord05, &FMWaveCord06, &FMWaveCord07, &FMWaveCord08,
                                     &FMWaveCord09, &FMWaveCord10, &FMWaveCord11, &FMWaveCord12, &FMWaveCord13, &FMWaveCord14, &FMWaveCord15, &FMWaveCord16,
                                     &FMWaveCord17, &FMWaveCord18, &FMWaveCord19, &FMWaveCord20, &FMWaveCord21, &FMWaveCord22, &FMWaveCord23, &FMWaveCord24,
                                     &FMWaveCord25, &FMWaveCord26, &FMWaveCord27, &FMWaveCord28, &FMWaveCord29, &FMWaveCord30, &FMWaveCord31, &FMWaveCord32
                                    };


  AudioConnection *wavelinescords[32] = {&wavelinecord24, &wavelinecord22, &wavelinecord23, &wavelinecord21, &wavelinecord19, &wavelinecord20, &wavelinecord17, &wavelinecord18 ,
                                        &wavelinecord47, &wavelinecord45, &wavelinecord39, &wavelinecord41, &wavelinecord33, &wavelinecord35, &wavelinecord27, &wavelinecord29,
                                        &wavelinecord44, &wavelinecord43, &wavelinecord37, &wavelinecord42, &wavelinecord34, &wavelinecord36, &wavelinecord28, &wavelinecord30,
                                        &wavelinecord48, &wavelinecord46, &wavelinecord40, &wavelinecord38, &wavelinecord31, &wavelinecord32, &wavelinecord25, &wavelinecord26
                                      };

AudioSynthWaveform *waveforms1[32] = {&waveform1L1, &waveform1L2, &waveform1L3, &waveform1L4, &waveform1L5, &waveform1L6, &waveform1L7, &waveform1L8,
                                      &waveform2L1, &waveform2L2, &waveform2L3, &waveform2L4, &waveform2L5, &waveform2L6, &waveform2L7, &waveform2L8,
                                      &waveform3L1, &waveform3L2, &waveform3L3, &waveform3L4, &waveform3L5, &waveform3L6, &waveform3L7, &waveform3L8,
                                      &waveform4L1, &waveform4L2, &waveform4L3, &waveform4L4, &waveform4L5, &waveform4L6, &waveform4L7, &waveform4L8
                                    };
AudioSynthWaveformModulated *FMwaveforms1[32] = {&FMWaveform1L1, &FMWaveform1L2, &FMWaveform1L3, &FMWaveform1L4, &FMWaveform1L5, &FMWaveform1L6, &FMWaveform1L7, &FMWaveform1L8,
                                                &FMWaveform2L1, &FMWaveform2L2, &FMWaveform2L3, &FMWaveform2L4, &FMWaveform2L5, &FMWaveform2L6, &FMWaveform2L7, &FMWaveform2L8,
                                                &FMWaveform3L1, &FMWaveform3L2, &FMWaveform3L3, &FMWaveform3L4, &FMWaveform3L5, &FMWaveform3L6, &FMWaveform3L7, &FMWaveform3L8,
                                                &FMWaveform4L1, &FMWaveform4L2, &FMWaveform4L3, &FMWaveform4L4, &FMWaveform4L5, &FMWaveform4L6, &FMWaveform4L7, &FMWaveform4L8
                                              };
AudioSynthSimpleDrum *drums1[32] = {&drum1L1, &drum1L2, &drum1L3, &drum1L4, &drum1L5, &drum1L6, &drum1L7, &drum1L8,
                                    &drum2L1, &drum2L2, &drum2L3, &drum2L4, &drum2L5, &drum2L6, &drum2L7, &drum2L8,
                                    &drum3L1, &drum3L2, &drum3L3, &drum3L4, &drum3L5, &drum3L6, &drum3L7, &drum3L8,
                                    &drum4L1, &drum4L2, &drum4L3, &drum4L4, &drum4L5, &drum4L6, &drum4L7, &drum4L8
                                              };
AudioSynthKarplusStrong *strings1[32] = {&string1L1, &string1L2, &string1L3, &string1L4, &string1L5, &string1L6, &string1L7, &string1L8,
                                        &string2L1, &string2L2, &string2L3, &string2L4, &string2L5, &string2L6, &string2L7, &string2L8,
                                        &string3L1, &string3L2, &string3L3, &string3L4, &string3L5, &string3L6, &string3L7, &string3L8,
                                        &string4L1, &string4L2, &string4L3, &string4L4, &string4L5, &string4L6, &string4L7, &string4L8
                                              };
AudioMixer4 *Wavesmix[8] = { &WavesL1, &WavesL2, &WavesL3, &WavesL4,&WavesL5, &WavesL6, &WavesL7, &WavesL8};

AudioPlaySerialflashRaw *FlashSampler[16] = {&FlashSampler1, &FlashSampler2, &FlashSampler3, &FlashSampler4, &FlashSampler5, &FlashSampler6, &FlashSampler7, &FlashSampler8,
                                             &FlashSampler9, &FlashSampler10, &FlashSampler11, &FlashSampler12, &FlashSampler13, &FlashSampler14, &FlashSampler15, &FlashSampler16};
                                      
AudioMixer4 *Flashmixer[4] = {&flashmix1, &flashmix2, &flashmix3, &flashmix4};  

AudioAmplifier *Wavespreamp303[8] = {&wavePAmp0, &wavePAmp1, &wavePAmp2, &wavePAmp3, &wavePAmp4, &wavePAmp5, &wavePAmp6, &wavePAmp7};

AudioSynthWaveform *LFOwaveforms1[4]  = { &LFOrm1 , &LFOrm2, &LFOrm3, &LFOrm4 }  ;   

const int16_t waveformed[256] = {
   0,   201,   402,   603,   804,  1005,  1206,  1406,  1607,  1808,  2008,  2209,  2409,  2609,  2809,  3009, 
3209,  3409,  3608,  3808,  4007,  4206,  4405,  4603,  4802,  5000,  5199,  5397,  5594,  5792,  5989,  6186, 
6383,  6580,  6776,  6972,  7168,  7363,  7559,  7753,  7948,  8142,  8336,  8529,  8722,  8915,  9107,  9299, 
9490,  9681,  9871, 10061, 10251, 10440, 10628, 10817, 11004, 11191, 11378, 11564, 11750, 11935, 12119, 12303, 
12487, 12670, 12852, 13034, 13215, 13396, 13576, 13755, 13934, 14112, 14290, 14467, 14643, 14819, 14994, 15168, 
15342, 15515, 15687, 15859, 16030, 16200, 16370, 16539, 16707, 16875, 17042, 17208, 17374, 17539, 17703, 17867, 
18029, 18191, 18353, 18513, 18673, 18832, 18990, 19148, 19304, 19460, 19615, 19770, 19923, 20076, 20228, 20380, 
20530, 20680, 20829, 20977, 21124, 21270, 21416, 21560, 21704, 21847, 21989, 22131, 22271, 22411, 22549, 22687, 
22824, 22960, 23095, 23229, 23362, 23494, 23626, 23756, 23886, 24014, 24142, 24268, 24394, 24518, 24642, 24765, 
24887, 25007, 25127, 25245, 25363, 25479, 25595, 25709, 25823, 25935, 26047, 26157, 26266, 26375, 26482, 26589, 
26694, 26798, 26901, 27004, 27105, 27205, 27304, 27402, 27499, 27595, 27689, 27783, 27876, 27967, 28058, 28147, 
28236, 28323, 28409, 28494, 28578, 28660, 28742, 28823, 28902, 28980, 29057, 29133, 29208, 29281, 29354, 29425, 
29495, 29564, 29632, 29699, 29764, 29828, 29891, 29953, 30014, 30074, 30132, 30189, 30245, 30299, 30353, 30405, 
30456, 30506, 30554, 30601, 30647, 30691, 30735, 30777, 30818, 30857, 30896, 30933, 30968, 31003, 31036, 31068, 
31098, 31127, 31155, 31182, 31207, 31231, 31253, 31275, 31294, 31313, 31330, 31346, 31361, 31374, 31386, 31397, 
31406, 31414, 31420, 31426, 31430, 31433, 31434, 31435, 31434, 31432, 31428, 31423, 31417, 31409, 31400, 31389
};
