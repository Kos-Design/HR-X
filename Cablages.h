#pragma once

#include "Constants.h"
#include <Audio.h>
#include "Constants.h"
#include <SerialFlash.h>
#include <play_sd_mp3.h>
#include <play_sd_flac.h>
#include "play_partial_sd_raw.h"

// use this to remove declarations from cables: \([A-Za-z_][A-Za-z0-9_]*,\s*\d+,\s*[A-Za-z_][A-Za-z0-9_]*,\s*\d+\)

extern AudioPlaySerialflashRaw  FlashSampler1;  //xy=1731.8833312988281,20
extern AudioPlaySerialflashRaw  FlashSampler2;  //xy=1731.8833312988281,60
extern AudioPlaySerialflashRaw  FlashSampler5;  //xy=1732.8833312988281,182
extern AudioPlaySerialflashRaw  FlashSampler6;  //xy=1732.8833312988281,217
extern AudioPlaySerialflashRaw  FlashSampler4;  //xy=1733.8833312988281,130
extern AudioPlaySerialflashRaw  FlashSampler9;  //xy=1733.8833312988281,339
extern AudioPlaySerialflashRaw  FlashSampler3;  //xy=1734.8833312988281,93
extern AudioPlaySerialflashRaw  FlashSampler10; //xy=1733.8833312988281,374
extern AudioPlaySerialflashRaw  FlashSampler8;  //xy=1734.8833312988281,287
extern AudioPlaySerialflashRaw  FlashSampler7;  //xy=1735.8833312988281,250
extern AudioPlaySerialflashRaw  FlashSampler12; //xy=1735.8833312988281,444
extern AudioPlaySerialflashRaw  FlashSampler13; //xy=1735.8833312988281,495
extern AudioPlaySerialflashRaw  FlashSampler14; //xy=1735.8833312988281,530
extern AudioPlaySerialflashRaw  FlashSampler11; //xy=1736.8833312988281,407
extern AudioPlaySerialflashRaw  FlashSampler16; //xy=1737.8833312988281,600
extern AudioPlaySerialflashRaw  FlashSampler15; //xy=1738.8833312988281,563

extern AudioPlaySerialflashRaw  FlashRaw;       //xy=2350.8831787109375,178
extern AudioMixer4              flashmix1;      //xy=1945.8833312988281,83
extern AudioMixer4              flashmix2;      //xy=1946.8833312988281,239
extern AudioMixer4              flashmix3;      //xy=1947.8833312988281,396
extern AudioMixer4              flashmix4;      //xy=2009.8833312988281,549

extern AudioConnection          apatchCord67;
extern AudioConnection          apatchCord68;
extern AudioConnection          apatchCord69;
extern AudioConnection          apatchCord70;
extern AudioConnection          apatchCord71;
extern AudioConnection          apatchCord72;
extern AudioConnection          apatchCord73;
extern AudioConnection          apatchCord74;
extern AudioConnection          apatchCord75;
extern AudioConnection          apatchCord76;
extern AudioConnection          apatchCord77;
extern AudioConnection          apatchCord79;
extern AudioConnection          apatchCord80;
extern AudioConnection          apatchCord81;
extern AudioConnection          apatchCord82;
extern AudioConnection          apatchCord83;

// GUItool: begin automatically generated code
extern AudioSynthWaveform       LFOrm2;         //xy=57,1009
extern AudioEffectMultiply      multiply2;      //xy=61,970
extern AudioEffectMultiply      multiply2R;      //xy=63,975

extern AudioSynthWaveform       LFOrm3;         //xy=73,1240
extern AudioEffectMultiply      multiply3;      //xy=74,1200
extern AudioEffectMultiply      multiply3R;      //xy=76,1205
extern AudioSynthWaveform       LFOrm1;         //xy=106,708
extern AudioEffectMultiply      multiply1;      //xy=129,637
extern AudioEffectMultiply      multiply1R;      //xy=131,640
extern AudioSynthWaveformModulated FMWaveform1L3;  //xy=408,866
extern AudioSynthWaveformModulated FMWaveform2L3;  //xy=409,900
extern AudioSynthWaveformModulated FMWaveform1L2;  //xy=410,728
extern AudioSynthWaveformModulated FMWaveform2L2;  //xy=411,762
extern AudioSynthWaveformModulated FMWaveform3L3;  //xy=411,932
extern AudioSynthWaveformModulated FMWaveform1L4;  //xy=411,1003
extern AudioSynthWaveformModulated FMWaveform1L1;  //xy=413,589
extern AudioSynthWaveformModulated FMWaveform2L4;  //xy=413,1037
extern AudioSynthWaveformModulated FMWaveform2L1;  //xy=415,623
extern AudioSynthWaveformModulated FMWaveform3L2;  //xy=415,799
extern AudioSynthWaveformModulated FMWaveform3L4;  //xy=415,1070
extern AudioSynthWaveformModulated FMWaveform1L5;  //xy=415,1153
extern AudioSynthWaveformModulated FMWaveform3L1;  //xy=417,655
extern AudioSynthWaveformModulated FMWaveform2L5;  //xy=417,1187
extern AudioSynthWaveformModulated FMWaveform3L5;  //xy=419,1220
extern AudioSynthWaveformModulated FMWaveform1L6;  //xy=429,1302
extern AudioSynthWaveformModulated FMWaveform2L6;  //xy=431,1336
extern AudioSynthWaveformModulated FMWaveform3L6;  //xy=433,1369
extern AudioEffectMultiply      modulate1L6;    //xy=605,1291
extern AudioEffectMultiply      modulate2L6;    //xy=605,1323
extern AudioEffectMultiply      modulate3L6;    //xy=607,1354
extern AudioEffectMultiply      modulate1L2;    //xy=619,751
extern AudioEffectMultiply      modulate2L2;    //xy=619,783
extern AudioEffectMultiply      modulate1L3;    //xy=619,885
extern AudioEffectMultiply      modulate2L3;    //xy=619,917
extern AudioEffectMultiply      modulate1L5;    //xy=619,1152
extern AudioEffectMultiply      modulate2L5;    //xy=619,1184
extern AudioEffectMultiply      modulate3L2;    //xy=621,814
extern AudioEffectMultiply      modulate3L3;    //xy=621,948
extern AudioEffectMultiply      modulate3L5;    //xy=621,1215
extern AudioEffectMultiply      modulate1L4;    //xy=623,1019
extern AudioEffectMultiply      modulate2L4;    //xy=623,1051
extern AudioEffectMultiply      modulate3L4;    //xy=625,1082
extern AudioEffectMultiply      modulate1L1;    //xy=629,622
extern AudioEffectMultiply      modulate2L1;    //xy=629,654
extern AudioEffectMultiply      modulate3L1;    //xy=631,685
extern AudioSynthSimpleDrum     drum3L6;        //xy=828,1341
extern AudioSynthSimpleDrum     drum2L1;        //xy=831,636
extern AudioSynthSimpleDrum     drum2L6;        //xy=829,1306
extern AudioSynthSimpleDrum     drum2L5;        //xy=830,1176
extern AudioSynthSimpleDrum     drum3L1;        //xy=833,669
extern AudioSynthSimpleDrum     drum1L1;        //xy=834,606
extern AudioSynthSimpleDrum     drum3L5;        //xy=832,1209
extern AudioSynthSimpleDrum     drum1L6;        //xy=832,1276
extern AudioSynthSimpleDrum     drum1L5;        //xy=833,1146
extern AudioSynthSimpleDrum     drum2L3;        //xy=835,906
extern AudioSynthSimpleDrum     drum2L4;        //xy=836,1046
extern AudioSynthSimpleDrum     drum3L3;        //xy=837,939
extern AudioSynthSimpleDrum     drum1L3;        //xy=838,876
extern AudioSynthSimpleDrum     drum3L4;        //xy=838,1079
extern AudioSynthSimpleDrum     drum1L4;        //xy=839,1016
extern AudioSynthSimpleDrum     drum2L2;        //xy=840,779
extern AudioSynthSimpleDrum     drum3L2;        //xy=842,812
extern AudioSynthSimpleDrum     drum1L2;        //xy=843,749
extern AudioSynthKarplusStrong  string2L6;      //xy=960,1298
extern AudioSynthKarplusStrong  string3L6;      //xy=963,1332
extern AudioSynthKarplusStrong  string3L4;      //xy=965,1061
extern AudioSynthKarplusStrong  string2L4;      //xy=966,1028
extern AudioSynthKarplusStrong  string1L6;      //xy=966,1266
extern AudioSynthKarplusStrong  string3L3;      //xy=970,928
extern AudioSynthKarplusStrong  string3L1;      //xy=972,643
extern AudioSynthKarplusStrong  string2L3;      //xy=971,895
extern AudioSynthKarplusStrong  string2L1;      //xy=973,610
extern AudioSynthKarplusStrong  string1L2;      //xy=973,716
extern AudioSynthKarplusStrong  string1L4;      //xy=972,996
extern AudioSynthKarplusStrong  string3L2;      //xy=973,795
extern AudioSynthKarplusStrong  string2L2;      //xy=974,762
extern AudioSynthKarplusStrong  string3L5;      //xy=976,1197
extern AudioSynthKarplusStrong  string1L3;      //xy=978,863
extern AudioSynthKarplusStrong  string2L5;      //xy=977,1164
extern AudioSynthKarplusStrong  string1L1;      //xy=980,578
extern AudioSynthKarplusStrong  string1L5;      //xy=983,1132
extern AudioSynthWaveform       waveform1L5;    //xy=1161,1146
extern AudioSynthWaveform       waveform1L6;    //xy=1161,1277
extern AudioSynthWaveform       waveform2L5;    //xy=1164,1178
extern AudioSynthWaveform       waveform3L5;    //xy=1164,1207
extern AudioSynthWaveform       waveform2L6;    //xy=1164,1310
extern AudioSynthWaveform       waveform3L6;    //xy=1164,1339
extern AudioSynthWaveform       waveform1L4;    //xy=1169,993
extern AudioSynthWaveform       waveform3L3;    //xy=1172,921
extern AudioSynthWaveform       waveform1L2;    //xy=1173,727
extern AudioSynthWaveform       waveform2L3;    //xy=1173,891
extern AudioSynthWaveform       waveform2L4;    //xy=1173,1026
extern AudioSynthWaveform       waveform3L4;    //xy=1173,1055
extern AudioSynthWaveform       waveform1L3;    //xy=1174,857
extern AudioSynthWaveform       waveform3L2;    //xy=1177,787
extern AudioSynthWaveform       waveform3L1;    //xy=1178,659
extern AudioSynthWaveform       waveform2L2;    //xy=1178,757
extern AudioSynthWaveform       waveform2L1;    //xy=1179,629
extern AudioSynthWaveform       waveform1L1;    //xy=1180,597
extern AudioMixer4              WavesL5;        //xy=1310,1191
extern AudioMixer4              WavesL6;        //xy=1310,1323
extern AudioMixer4              WavesL3;        //xy=1319,904
extern AudioMixer4              WavesL4;        //xy=1319,1039
extern AudioMixer4              WavesL2;        //xy=1324,770
extern AudioMixer4              WavesL1;        //xy=1348,647
extern AudioEffectEnvelope      envelopeL5;     //xy=1438,1341
extern AudioEffectEnvelope      envelopeL2;     //xy=1469,903
extern AudioEffectEnvelope      envelopeL3;     //xy=1477,1038
extern AudioEffectEnvelope      envelopeL4;     //xy=1482,1185
extern AudioEffectEnvelope      envelopeL0;     //xy=1493,615
extern AudioEffectEnvelope      envelopeL1;     //xy=1496,769
extern AudioAmplifier           fade5;          //xy=1588,1358
extern AudioAmplifier           wavePAmp5;      //xy=1603,1324
extern AudioAmplifier           fade0;          //xy=1626,705
extern AudioAmplifier           wavePAmp0;      //xy=1635,662
extern AudioAmplifier           fade2;          //xy=1638,952
extern AudioAmplifier           fade1;          //xy=1642,827
extern AudioAmplifier           wavePAmp1;      //xy=1645,788
extern AudioAmplifier           fade3;          //xy=1645,1067
extern AudioAmplifier           wavePAmp2;      //xy=1647,916
extern AudioAmplifier           wavePAmp3;      //xy=1652,1031
extern AudioAmplifier           fade4;          //xy=1671,1240
extern AudioAmplifier           wavePAmp4;      //xy=1684,1202
extern AudioFilterStateVariable filter303L6;    //xy=1752,1332
extern AudioFilterStateVariable filter303L1;    //xy=1781,668
extern AudioFilterStateVariable filter303L2;    //xy=1790,797
extern AudioFilterStateVariable filter303L3;    //xy=1795,921
extern AudioFilterStateVariable filter303L4;    //xy=1806,1045
extern AudioFilterStateVariable filter303L5;    //xy=1836,1213
extern AudioMixer4              mix303L6;       //xy=1909,1342
extern AudioMixer4              mix303L1;       //xy=1937,685
extern AudioMixer4              mix303L2;       //xy=1937,804
extern AudioMixer4              mix303L3;       //xy=1954,905
extern AudioMixer4              mix303L4;       //xy=1962,1026
extern AudioMixer4              mix303L5;       //xy=2031,1213
extern AudioMixer4              flashmixMain;   //xy=2047,253
extern AudioInputI2S            AudioIn1;       //xy=2050,524
extern AudioInputUSB            usb1;           //xy=2052,418
extern AudioMixer4              mixerWet303L6;  //xy=2065,1334
extern AudioMixer4              mixerWet303L2;  //xy=2102,789
extern AudioMixer4              mixerWet303L1;  //xy=2115,649
extern AudioMixer4              mixerWet303L3;  //xy=2125,883
extern AudioMixer4              mixerWet303L4;  //xy=2136,1009
extern AudioMixer4              mixerWet303L5;  //xy=2201,1190
extern AudioMixer4              InMixL;         //xy=2243,437
extern AudioMixer4              InMixR;         //xy=2247,545
extern AudioMixer4              mixerWL1to4;    //xy=2319,875
extern AudioPlaySdRaw           playRawL;       //xy=2325,376
extern AudioPlaySdRaw           playRawR;       //xy=2356,697
extern AudioPlaySdWav           playSdWav1;     //xy=2365,488
extern AudioMixer4              mixerWL5to8;    //xy=2370,1348
extern AudioSynthSimpleDrum     metrodrum1;     //xy=2374,608
extern AudioAmplifier           LineInPreAmpL;  //xy=2397,437
extern AudioAmplifier           LineInPreAmpR;  //xy=2412,544
extern AudioMixer4              flashMastermix; //xy=2504,142
extern AudioMixer4              mixerWAll;      //xy=2506,931
extern AudioMixer4              MasterL;        //xy=2579,371
extern AudioMixer4              MasterR;        //xy=2598,562
extern AudioMixer4              MasterR1;       //xy=2830.666618347168,493.3333225250244
extern AudioEffectFlange        flange1;        //xy=2833,989
extern AudioEffectBitcrusher    bitcrusher1;    //xy=2837,941
extern AudioEffectChorus        chorus1;        //xy=2842,1032
extern AudioFilterBiquad        biquad1;        //xy=2843,1080
extern AudioEffectGranular      granular1;      //xy=2850,875
extern AudioMixer4              MasterL1;       //xy=2856,411
extern AudioEffectReverb        freeverbs1;     //xy=2855,833
extern AudioEffectBitcrusher    bitcrusher1R;    //xy=2859.9999389648438,1540.000020980835
extern AudioEffectFlange        flange1R; //xy=2866.66650390625,1591.6666259765625
extern AudioEffectReverb        freeverbs1R; //xy=2871.999954223633,1425.6666011810303
extern AudioEffectChorus        chorus1R; //xy=2875.66650390625,1634.6666259765625
extern AudioFilterBiquad        biquad1R; //xy=2876.66650390625,1682.6666259765625
extern AudioEffectGranular      granular1R;      //xy=2886.6666946411133,1488.3333921432495
extern AudioEffectGranular      granular2;      //xy=2982,878
extern AudioEffectBitcrusher    bitcrusher2;    //xy=2982,948
extern AudioEffectFlange        flange2;        //xy=2987,1002
extern AudioEffectChorus        chorus2;        //xy=2991,1046
extern AudioEffectReverb        freeverbs2;     //xy=2996,824
extern AudioFilterBiquad        biquad2;        //xy=2998,1093
extern AudioFilterStateVariable filter3;        //xy=2999,1318
extern AudioFilterStateVariable filter1;        //xy=3001,1175
extern AudioFilterStateVariable filter2;        //xy=3004,1246
extern AudioEffectBitcrusher    bitcrusher2R;    //xy=3020.0001068115234,1546.6667280197144
extern AudioEffectFlange        flange2R; //xy=3020.66650390625,1604.6666259765625
extern AudioEffectChorus        chorus2R; //xy=3024.66650390625,1648.6666259765625
extern AudioEffectReverb        freeverbs2R; //xy=3029.66650390625,1426.6666259765625
extern AudioFilterBiquad        biquad2R; //xy=3031.66650390625,1695.6666259765625
extern AudioFilterStateVariable filter3R; //xy=3032.66650390625,1920.6666259765625
extern AudioFilterStateVariable filter1R; //xy=3034.66650390625,1777.6666259765625
extern AudioEffectGranular      granular2R;      //xy=3036.6665420532227,1496.6666450500488
extern AudioFilterStateVariable filter2R; //xy=3037.66650390625,1848.6666259765625
extern AudioMixer4              WetMixMasterR;  //xy=3112.3333740234375,530.6666469573975
extern AudioMixer4              WetMixMasterL;  //xy=3113,434
extern AudioEffectGranular      granular3;      //xy=3132,886
extern AudioEffectFlange        flange3;        //xy=3132,1000
extern AudioEffectChorus        chorus3;        //xy=3135,1043
extern AudioFilterBiquad        biquad3;        //xy=3143,1091
extern AudioEffectBitcrusher    bitcrusher3;    //xy=3144,948
extern AudioEffectReverb        freeverbs3;     //xy=3145,828
extern AudioMixer4              mixfilter1;     //xy=3157,1181
extern AudioMixer4              mixfilter3;     //xy=3162,1318
extern AudioMixer4              mixfilter2;     //xy=3164,1249
extern AudioEffectFlange        flange3R; //xy=3165.66650390625,1602.6666259765625
extern AudioEffectChorus        chorus3R; //xy=3168.66650390625,1645.6666259765625
extern AudioFilterBiquad        biquad3R; //xy=3176.66650390625,1693.6666259765625
extern AudioEffectReverb        freeverbs3R; //xy=3178.66650390625,1430.6666259765625
extern AudioEffectBitcrusher    bitcrusher3R;    //xy=3178.3332901000977,1550.0000610351562
extern AudioEffectGranular      granular3R;      //xy=3188.333333333333,1498.333333333333
extern AudioMixer4              mixfilter1R; //xy=3190.66650390625,1783.6666259765625
extern AudioMixer4              mixfilter3R; //xy=3195.66650390625,1920.6666259765625
extern AudioMixer4              mixfilter2R; //xy=3197.66650390625,1851.6666259765625
extern AudioMixer4              FXBusL;         //xy=3453,329
extern AudioMixer4              FXBusR;         //xy=3468,506
extern AudioAmplifier           ampL;           //xy=3633,458
extern AudioAmplifier           ampR;           //xy=3633,506
extern AudioMixer4              feedbackdelay1R; //xy=3746.333335876465,1183.3333339691162
extern AudioMixer4              feedbackdelay1; //xy=3758.333320617676,659.0000076293945
extern AudioRecordQueue         queue2;         //xy=3779,559
extern AudioMixer4              feedbackdelay3R; //xy=3780.333236694336,1382.3333473205566
extern AudioMixer4              feedbackdelay2; //xy=3785,825
extern AudioMixer4              feedbackdelay2R; //xy=3786.333335876465,1284.3333339691162
extern AudioMixer4              feedbackdelay3; //xy=3789,978
extern AudioRecordQueue         queue1;         //xy=3809,368
extern AudioOutputI2S           AudioOutput;    //xy=3846,481
extern AudioEffectDelay         delay1;         //xy=3931.6665802001953,611.6667098999023
extern AudioEffectDelay         delay2;         //xy=3950.6665802001953,770.6666793823242
extern AudioEffectDelay         delay3;         //xy=3954.333164215088,904.3333053588867
extern AudioEffectDelay         delay1R; //xy=3961.66650390625,1171.6666259765625
extern AudioEffectDelay         delay2R; //xy=3962.3330841064453,1327.3333053588867
extern AudioEffectDelay         delay3R; //xy=3970.9996700286865,1460.999855041504
extern AudioAnalyzeNoteFrequency notefreq1;      //xy=4014,421
extern AudioMixer4              delay1pre1;     //xy=4099.666664123535,564.3333358764648
extern AudioMixer4              delay1pre2;     //xy=4100,657.6666870117188
extern AudioMixer4              delay2pre1;     //xy=4100,737.6666870117188
extern AudioMixer4              delay3pre1;     //xy=4101,870.6666870117188
extern AudioMixer4              delay2pre2;     //xy=4102,801.6666870117188
extern AudioMixer4              delay3pre2;     //xy=4102,940.6666870117188
extern AudioMixer4              delay1pre2R; //xy=4126.66650390625,1212.6666259765625
extern AudioMixer4              delay2pre1R; //xy=4126.66650390625,1292.6666259765625
extern AudioMixer4              delay3pre1R; //xy=4127.66650390625,1425.6666259765625
extern AudioMixer4              delay2pre2R; //xy=4128.66650390625,1356.6666259765625
extern AudioMixer4              delay3pre2R; //xy=4128.66650390625,1495.6666259765625
extern AudioMixer4              delay1pre1R; //xy=4134.66650390625,1117.6666259765625
extern AudioMixer4              delaymix3;      //xy=4251,908.6666870117188
extern AudioMixer4              delaymix2;      //xy=4256,780.6666870117188
extern AudioMixer4              delaymix1;      //xy=4272,618.6666870117188
extern AudioMixer4              delaymix3R; //xy=4277.66650390625,1463.6666259765625
extern AudioMixer4              delaymix2R; //xy=4282.66650390625,1335.6666259765625
extern AudioMixer4              delaymix1R; //xy=4298.66650390625,1173.6666259765625

extern AudioConnection          patchCord1;
extern AudioConnection          patchCord2;
extern AudioConnection          patchCord3;
extern AudioConnection          patchCord4;
extern AudioConnection          patchCord5;
extern AudioConnection          patchCord6;
extern AudioConnection          patchCord7;
extern AudioConnection          patchCord8;
extern AudioConnection          patchCord9;
extern AudioConnection          patchCord10;
extern AudioConnection          patchCord11;
extern AudioConnection          patchCord12;
extern AudioConnection          patchCord13;
extern AudioConnection          apatchCord13R;
extern AudioConnection          patchCord14;
extern AudioConnection          patchCord15;
extern AudioConnection          patchCord16;
extern AudioConnection          patchCord17;
extern AudioConnection          patchCord18;
extern AudioConnection          patchCord19;
extern AudioConnection          patchCord20;
extern AudioConnection          patchCord21;
extern AudioConnection          patchCord22;
extern AudioConnection          patchCord23;
extern AudioConnection          patchCord24;
extern AudioConnection          patchCord25;
extern AudioConnection          patchCord26;
extern AudioConnection          apatchCord26R;
extern AudioConnection          patchCord27;
extern AudioConnection          patchCord28;
extern AudioConnection          patchCord29;
extern AudioConnection          patchCord30;
extern AudioConnection          patchCord31;
extern AudioConnection          patchCord32;
extern AudioConnection          patchCord33;
extern AudioConnection          patchCord34;
extern AudioConnection          patchCord35;
extern AudioConnection          patchCord36;
extern AudioConnection          patchCord37;
extern AudioConnection          patchCord38;
extern AudioConnection          patchCord39;
extern AudioConnection          apatchCord39R;
extern AudioConnection          patchCord40;
extern AudioConnection          patchCord41;
extern AudioConnection          patchCord42;
extern AudioConnection          patchCord43;
extern AudioConnection          patchCord44;
extern AudioConnection          patchCord45;
extern AudioConnection          patchCord46;
extern AudioConnection          patchCord47;
extern AudioConnection          patchCord48;
extern AudioConnection          patchCord49;
extern AudioConnection          patchCord50;
extern AudioConnection          patchCord51;
extern AudioConnection          patchCord52;
extern AudioConnection          patchCord53;
extern AudioConnection          patchCord54;
extern AudioConnection          patchCord55;
extern AudioConnection          patchCord56;
extern AudioConnection          patchCord57;
extern AudioConnection          patchCord58;
extern AudioConnection          patchCord59;
extern AudioConnection          patchCord60;
extern AudioConnection          patchCord61;
extern AudioConnection          patchCord62;
extern AudioConnection          patchCord63;
extern AudioConnection          patchCord64;
extern AudioConnection          patchCord65;
extern AudioConnection          patchCord66;
extern AudioConnection          patchCord67;
extern AudioConnection          patchCord68;
extern AudioConnection          patchCord69;
extern AudioConnection          patchCord70;
extern AudioConnection          patchCord71;
extern AudioConnection          patchCord72;
extern AudioConnection          patchCord73;
extern AudioConnection          patchCord74;
extern AudioConnection          patchCord75;
extern AudioConnection          patchCord76;
extern AudioConnection          patchCord77;
extern AudioConnection          patchCord78;
extern AudioConnection          patchCord79;
extern AudioConnection          patchCord80;
extern AudioConnection          patchCord81;
extern AudioConnection          patchCord82;
extern AudioConnection          patchCord83;
extern AudioConnection          patchCord84;
extern AudioConnection          patchCord85;
extern AudioConnection          patchCord86;
extern AudioConnection          patchCord87;
extern AudioConnection          patchCord88;
extern AudioConnection          patchCord89;
extern AudioConnection          patchCord90;
extern AudioConnection          patchCord91;
extern AudioConnection          patchCord92;
extern AudioConnection          patchCord93;
extern AudioConnection          patchCord94;
extern AudioConnection          patchCord95;
extern AudioConnection          patchCord96;
extern AudioConnection          patchCord97;
extern AudioConnection          patchCord98;
extern AudioConnection          patchCord99;
extern AudioConnection          patchCord100;
extern AudioConnection          patchCord101;
extern AudioConnection          patchCord102;
extern AudioConnection          patchCord103;
extern AudioConnection          patchCord104;
extern AudioConnection          patchCord105;
extern AudioConnection          patchCord106;
extern AudioConnection          patchCord107;
extern AudioConnection          patchCord108;
extern AudioConnection          patchCord109;
extern AudioConnection          patchCord110;
extern AudioConnection          patchCord111;
extern AudioConnection          patchCord112;
extern AudioConnection          patchCord113;
extern AudioConnection          patchCord114;
extern AudioConnection          patchCord115;
extern AudioConnection          patchCord116;
extern AudioConnection          patchCord117;
extern AudioConnection          patchCord118;
extern AudioConnection          patchCord119;
extern AudioConnection          patchCord120;
extern AudioConnection          patchCord121;
extern AudioConnection          patchCord122;
extern AudioConnection          patchCord123;
extern AudioConnection          patchCord124;
extern AudioConnection          patchCord125;
extern AudioConnection          patchCord126;
extern AudioConnection          patchCord128;
extern AudioConnection          patchCord131;
extern AudioConnection          patchCord132;
extern AudioConnection          patchCord133;
extern AudioConnection          patchCord134;
extern AudioConnection          patchCord135;
extern AudioConnection          patchCord136;
extern AudioConnection          patchCord137;
extern AudioConnection          patchCord138;
extern AudioConnection          patchCord139;
extern AudioConnection          patchCord140;
extern AudioConnection          patchCord141;
extern AudioConnection          patchCord142;
extern AudioConnection          patchCord143;
extern AudioConnection          patchCord144;
extern AudioConnection          patchCord145;
extern AudioConnection          patchCord146;
extern AudioConnection          patchCord147;
extern AudioConnection          patchCord148;
extern AudioConnection          patchCord149;
extern AudioConnection          patchCord150;
extern AudioConnection          patchCord151;
extern AudioConnection          patchCord152;
extern AudioConnection          patchCord153;
extern AudioConnection          patchCord154;
extern AudioConnection          patchCord155;
extern AudioConnection          patchCord156;
extern AudioConnection          patchCord157;
extern AudioConnection          patchCord158;
extern AudioConnection          patchCord159;
extern AudioConnection          patchCord160;
extern AudioConnection          patchCord161;
extern AudioConnection          patchCord162;
extern AudioConnection          patchCord163;
extern AudioConnection          patchCord164;
extern AudioConnection          patchCord165;
extern AudioConnection          patchCord166;
extern AudioConnection          patchCord167;
extern AudioConnection          patchCord168;
extern AudioConnection          patchCord169;
extern AudioConnection          patchCord170;
extern AudioConnection          patchCord171;
extern AudioConnection          patchCord172;
extern AudioConnection          patchCord173;
extern AudioConnection          patchCord174;
extern AudioConnection          patchCord175;
extern AudioConnection          patchCord176;
extern AudioConnection          patchCord177;
extern AudioConnection          patchCord178;
extern AudioConnection          patchCord179;
extern AudioConnection          patchCord180;
extern AudioConnection          patchCord181;
extern AudioConnection          patchCord182;
extern AudioConnection          patchCord183;
extern AudioConnection          patchCord184;
extern AudioConnection          patchCord185;
extern AudioConnection          patchCord186;
extern AudioConnection          patchCord187;
extern AudioConnection          patchCord188;
extern AudioConnection          patchCord189;
extern AudioConnection          patchCord190;
extern AudioConnection          patchCord191;
extern AudioConnection          patchCord192;
extern AudioConnection          patchCord193;
extern AudioConnection          patchCord194;
extern AudioConnection          patchCord195;
extern AudioConnection          patchCord196;
extern AudioConnection          patchCord197;
extern AudioConnection          patchCord198;
extern AudioConnection          patchCord199;
extern AudioConnection          patchCord200;
extern AudioConnection          patchCord201;
extern AudioConnection          patchCord202;
extern AudioConnection          patchCord203;
extern AudioConnection          patchCord204;
extern AudioConnection          patchCord205;
extern AudioConnection          patchCord206;
extern AudioConnection          patchCord207;
extern AudioConnection          patchCord208;
extern AudioConnection          patchCord209;
extern AudioConnection          patchCord210;
extern AudioConnection          patchCord211;
extern AudioConnection          patchCord212;
extern AudioConnection          patchCord213;
extern AudioConnection          patchCord214;
extern AudioConnection          patchCord215;
extern AudioConnection          patchCord216;
extern AudioConnection          patchCord217;
extern AudioConnection          patchCord218;
extern AudioConnection          patchCord219;
extern AudioConnection          patchCord220;
extern AudioConnection          patchCord221;
extern AudioConnection          patchCord222;
extern AudioConnection          patchCord223;

extern AudioControlSGTL5000     AudioShield;    //xy=4016,485
// GUItool: end automatically generated code

extern AudioAnalyzeFFT256 fft256;

extern AudioConnection patchCordFFT;


extern AudioConnection apatchCord133;

extern AudioConnection delayCord1;
extern AudioConnection delayCord2;
extern AudioConnection delayCord3;


extern AudioConnection delayCord1R;
extern AudioConnection delayCord2R;
extern AudioConnection delayCord3R;
extern AudioConnection premixMtom1;
extern AudioConnection premixMtom2;
extern AudioConnection premixMtom3;
extern AudioConnection premixMtog1;
extern AudioConnection premixMtog2;
extern AudioConnection premixMtog3;
extern AudioConnection premixMtobt1;
extern AudioConnection premixMtobt2;
extern AudioConnection premixMtobt3;
extern AudioConnection premixMtorev1;
extern AudioConnection premixMtorev2;
extern AudioConnection premixMtorev3;
extern AudioConnection premixMtofl1;
extern AudioConnection premixMtofl2;
extern AudioConnection premixMtofl3;
extern AudioConnection premixMtoch1;
extern AudioConnection premixMtoch2;
extern AudioConnection premixMtoch3;
extern AudioConnection premixMtoff1;
extern AudioConnection premixMtobq1;
extern AudioConnection premixMtobq2;
extern AudioConnection premixMtobq3;
extern AudioConnection premixMtoff2;
extern AudioConnection premixMtoff3;
extern AudioConnection premixMtode1;
extern AudioConnection premixMtode2;
extern AudioConnection premixMtode3;

extern AudioConnection premixMtom1R;
extern AudioConnection premixMtom2R;
extern AudioConnection premixMtom3R;
extern AudioConnection premixMtog1R;
extern AudioConnection premixMtog2R;
extern AudioConnection premixMtog3R;
extern AudioConnection premixMtobt1R;
extern AudioConnection premixMtobt2R;
extern AudioConnection premixMtobt3R;
extern AudioConnection premixMtorev1R;
extern AudioConnection premixMtorev2R;
extern AudioConnection premixMtorev3R;
extern AudioConnection premixMtofl1R;
extern AudioConnection premixMtofl2R;
extern AudioConnection premixMtofl3R;
extern AudioConnection premixMtoch1R;
extern AudioConnection premixMtoch2R;
extern AudioConnection premixMtoch3R;
extern AudioConnection premixMtoff1R;
extern AudioConnection premixMtobq1R;
extern AudioConnection premixMtobq2R;
extern AudioConnection premixMtobq3R;
extern AudioConnection premixMtoff2R;
extern AudioConnection premixMtoff3R;
extern AudioConnection premixMtode1R;
extern AudioConnection premixMtode2R;
extern AudioConnection premixMtode3R;

extern AudioConnection mul1towetL1;
extern AudioConnection mul1towetR1;
extern AudioConnection mul2towetL1;
extern AudioConnection mul2towetR1;
extern AudioConnection mul3towetL1;
extern AudioConnection mul3towetR1;

extern AudioConnection mul1towetL2;
extern AudioConnection mul1towetR2;
extern AudioConnection mul2towetL2;
extern AudioConnection mul2towetR2;
extern AudioConnection mul3towetL2;
extern AudioConnection mul3towetR2;

extern AudioConnection mul1towetL3;
extern AudioConnection mul1towetR3;
extern AudioConnection mul2towetL3;
extern AudioConnection mul2towetR3;
extern AudioConnection mul3towetL3;
extern AudioConnection mul3towetR3;


extern AudioConnection g1towetL1;
extern AudioConnection g1towetR1;
extern AudioConnection g2towetL1;
extern AudioConnection g2towetR1;
extern AudioConnection g3towetL1;
extern AudioConnection g3towetR1;

extern AudioConnection g1towetL2;
extern AudioConnection g1towetR2;
extern AudioConnection g2towetL2;
extern AudioConnection g2towetR2;
extern AudioConnection g3towetL2;
extern AudioConnection g3towetR2;

extern AudioConnection g1towetL3;
extern AudioConnection g1towetR3;
extern AudioConnection g2towetL3;
extern AudioConnection g2towetR3;
extern AudioConnection g3towetL3;
extern AudioConnection g3towetR3;


extern AudioConnection bt1towetL1;
extern AudioConnection bt1towetR1;
extern AudioConnection bt2towetL1;
extern AudioConnection bt2towetR1;
extern AudioConnection bt3towetL1;
extern AudioConnection bt3towetR1;

extern AudioConnection bt1towetL2;
extern AudioConnection bt1towetR2;
extern AudioConnection bt2towetL2;
extern AudioConnection bt2towetR2;
extern AudioConnection bt3towetL2;
extern AudioConnection bt3towetR2;

extern AudioConnection bt1towetL3;
extern AudioConnection bt1towetR3;
extern AudioConnection bt2towetL3;
extern AudioConnection bt2towetR3;
extern AudioConnection bt3towetL3;
extern AudioConnection bt3towetR3;


extern AudioConnection rev1towetL1;
extern AudioConnection rev1towetR1;
extern AudioConnection rev2towetL1;
extern AudioConnection rev2towetR1;
extern AudioConnection rev3towetL1;
extern AudioConnection rev3towetR1;

extern AudioConnection rev1towetL2;
extern AudioConnection rev1towetR2;
extern AudioConnection rev2towetL2;
extern AudioConnection rev2towetR2;
extern AudioConnection rev3towetL2;
extern AudioConnection rev3towetR2;

extern AudioConnection rev1towetL3;
extern AudioConnection rev1towetR3;
extern AudioConnection rev2towetL3;
extern AudioConnection rev2towetR3;
extern AudioConnection rev3towetL3;
extern AudioConnection rev3towetR3;


extern AudioConnection fl1towetL1;
extern AudioConnection fl1towetR1;
extern AudioConnection fl2towetL1;
extern AudioConnection fl2towetR1;
extern AudioConnection fl3towetL1;
extern AudioConnection fl3towetR1;

extern AudioConnection fl1towetL2;
extern AudioConnection fl1towetR2;
extern AudioConnection fl2towetL2;
extern AudioConnection fl2towetR2;
extern AudioConnection fl3towetL2;
extern AudioConnection fl3towetR2;

extern AudioConnection fl1towetL3;
extern AudioConnection fl1towetR3;
extern AudioConnection fl2towetL3;
extern AudioConnection fl2towetR3;
extern AudioConnection fl3towetL3;
extern AudioConnection fl3towetR3;


extern AudioConnection ch1towetL1;
extern AudioConnection ch1towetR1;
extern AudioConnection ch2towetL1;
extern AudioConnection ch2towetR1;
extern AudioConnection ch3towetL1;
extern AudioConnection ch3towetR1;

extern AudioConnection ch1towetL2;
extern AudioConnection ch1towetR2;
extern AudioConnection ch2towetL2;
extern AudioConnection ch2towetR2;
extern AudioConnection ch3towetL2;
extern AudioConnection ch3towetR2;

extern AudioConnection ch1towetL3;
extern AudioConnection ch1towetR3;
extern AudioConnection ch2towetL3;
extern AudioConnection ch2towetR3;
extern AudioConnection ch3towetL3;
extern AudioConnection ch3towetR3;

extern AudioConnection bq1towetL1;
extern AudioConnection bq1towetR1;
extern AudioConnection bq2towetL1;
extern AudioConnection bq2towetR1;
extern AudioConnection bq3towetL1;
extern AudioConnection bq3towetR1;

extern AudioConnection bq1towetL2;
extern AudioConnection bq1towetR2;
extern AudioConnection bq2towetL2;
extern AudioConnection bq2towetR2;
extern AudioConnection bq3towetL2;
extern AudioConnection bq3towetR2;

extern AudioConnection bq1towetL3;
extern AudioConnection bq1towetR3;
extern AudioConnection bq2towetL3;
extern AudioConnection bq2towetR3;
extern AudioConnection bq3towetL3;
extern AudioConnection bq3towetR3;


extern AudioConnection ff1towetL1;
extern AudioConnection ff1towetR1;
extern AudioConnection ff2towetL1;
extern AudioConnection ff2towetR1;
extern AudioConnection ff3towetL1;
extern AudioConnection ff3towetR1;

extern AudioConnection ff1towetL2;
extern AudioConnection ff1towetR2;
extern AudioConnection ff2towetL2;
extern AudioConnection ff2towetR2;
extern AudioConnection ff3towetL2;
extern AudioConnection ff3towetR2;

extern AudioConnection ff1towetL3;
extern AudioConnection ff1towetR3;
extern AudioConnection ff2towetL3;
extern AudioConnection ff2towetR3;
extern AudioConnection ff3towetL3;
extern AudioConnection ff3towetR3;

extern AudioConnection de1towetL1;
extern AudioConnection de1towetR1;
extern AudioConnection de2towetL1;
extern AudioConnection de2towetR1;
extern AudioConnection de3towetL1;
extern AudioConnection de3towetR1;

extern AudioConnection de1towetL2;
extern AudioConnection de1towetR2;
extern AudioConnection de2towetL2;
extern AudioConnection de2towetR2;
extern AudioConnection de3towetL2;
extern AudioConnection de3towetR2;

extern AudioConnection de1towetL3;
extern AudioConnection de1towetR3;
extern AudioConnection de2towetL3;
extern AudioConnection de2towetR3;
extern AudioConnection de3towetL3;
extern AudioConnection de3towetR3;

extern AudioConnection LFO1toFilter1;
extern AudioConnection LFO1toFilter2;
extern AudioConnection LFO1toFilter3;

extern AudioConnection LFO2toFilter1;
extern AudioConnection LFO2toFilter2;
extern AudioConnection LFO2toFilter3;

extern AudioConnection LFO3toFilter1;
extern AudioConnection LFO3toFilter2;
extern AudioConnection LFO3toFilter3;

extern AudioConnection LFO1toFilter1R;
extern AudioConnection LFO1toFilter2R;
extern AudioConnection LFO1toFilter3R;

extern AudioConnection LFO2toFilter1R;
extern AudioConnection LFO2toFilter2R;
extern AudioConnection LFO2toFilter3R;

extern AudioConnection LFO3toFilter1R;
extern AudioConnection LFO3toFilter2R;
extern AudioConnection LFO3toFilter3R;

extern AudioConnection *premixesMtoR[PMIX_DM_SIZE] ;

extern AudioConnection *premixesMto[PMIX_DM_SIZE] ;

extern AudioConnection *LFOtoFilterz[FXS_COUNT * FXS_COUNT];

extern AudioConnection *LFOtoFilterzR[FXS_COUNT * FXS_COUNT] ;

extern AudioConnection *fxcording[FXCORDS_SIZE] ;

extern AudioEffectMultiply *multiply[FXS_COUNT];
extern AudioEffectMultiply *multiplyR[FXS_COUNT] ;

extern AudioEffectGranular *granular[FXS_COUNT] ;
extern AudioEffectGranular *granularR[FXS_COUNT] ;


extern AudioEffectFlange *flange[FXS_COUNT];
extern AudioEffectFlange *flangeR[FXS_COUNT] ;


extern AudioEffectChorus *chorus[FXS_COUNT];
extern AudioEffectChorus *chorusR[FXS_COUNT] ;

extern AudioEffectBitcrusher *bitcrusher[FXS_COUNT] ;
extern AudioEffectBitcrusher *bitcrusherR[FXS_COUNT] ;

extern AudioFilterStateVariable *filterz[FXS_COUNT] ;
extern AudioFilterStateVariable *filterzR[FXS_COUNT];

extern AudioFilterBiquad *biquad[FXS_COUNT] ;
extern AudioFilterBiquad *biquadR[FXS_COUNT] ;

extern AudioEffectReverb *freeverbs[FXS_COUNT] ;
extern AudioEffectReverb *freeverbsR[FXS_COUNT];

extern AudioEffectDelay *lesdelays[FXS_COUNT];
extern AudioEffectDelay *lesdelaysR[FXS_COUNT] ;

extern AudioMixer4 *mixfilter[FXS_COUNT] ;
extern AudioMixer4 *mixfilterR[FXS_COUNT] ;

extern AudioMixer4 *delaypremix[FXS_COUNT * 2] ;
extern AudioMixer4 *delaypremixR[FXS_COUNT * 2] ;

extern AudioMixer4 *delayfeedbackmix[FXS_COUNT] ;
extern AudioMixer4 *delayfeedbackmixR[FXS_COUNT] ;

extern AudioMixer4 *delaypostmix[FXS_COUNT] ;
extern AudioMixer4 *delaypostmixR[FXS_COUNT];

extern AudioConnection *delayCords[3] ;
extern AudioConnection *delayCordsR[3];

extern AudioMixer4 *les303passes[SYNTH_LINERS_COUNT];

extern AudioMixer4 *les303wet[SYNTH_LINERS_COUNT];

extern AudioFilterStateVariable *les303filterz[SYNTH_LINERS_COUNT];



extern AudioConnection Notespy_cable;

extern AudioConnection FMWaveCord01;
extern AudioConnection FMWaveCord02;
extern AudioConnection FMWaveCord03;
extern AudioConnection FMWaveCord04;
extern AudioConnection FMWaveCord05;
extern AudioConnection FMWaveCord06;

extern AudioConnection FMWaveCord09;
extern AudioConnection FMWaveCord10;
extern AudioConnection FMWaveCord11;
extern AudioConnection FMWaveCord12;
extern AudioConnection FMWaveCord13;
extern AudioConnection FMWaveCord14;

extern AudioConnection FMWaveCord17;
extern AudioConnection FMWaveCord18;
extern AudioConnection FMWaveCord19;
extern AudioConnection FMWaveCord20;
extern AudioConnection FMWaveCord21;
extern AudioConnection FMWaveCord22;

extern AudioConnection stringCord01;
extern AudioConnection stringCord02;
extern AudioConnection stringCord03;
extern AudioConnection stringCord04;
extern AudioConnection stringCord05;
extern AudioConnection stringCord06;

extern AudioConnection stringCord09;
extern AudioConnection stringCord10;
extern AudioConnection stringCord11;
extern AudioConnection stringCord12;
extern AudioConnection stringCord13;
extern AudioConnection stringCord14;

extern AudioConnection stringCord17;
extern AudioConnection stringCord18;
extern AudioConnection stringCord19;
extern AudioConnection stringCord20;
extern AudioConnection stringCord21;
extern AudioConnection stringCord22;

extern AudioConnection drumCord01;
extern AudioConnection drumCord02;
extern AudioConnection drumCord03;
extern AudioConnection drumCord04;
extern AudioConnection drumCord05;
extern AudioConnection drumCord06;

extern AudioConnection drumCord09;
extern AudioConnection drumCord10;
extern AudioConnection drumCord11;
extern AudioConnection drumCord12;
extern AudioConnection drumCord13;
extern AudioConnection drumCord14;

extern AudioConnection drumCord17;
extern AudioConnection drumCord18;
extern AudioConnection drumCord19;
extern AudioConnection drumCord20;
extern AudioConnection drumCord21;
extern AudioConnection drumCord22;

extern AudioConnection wavelinecord19;
extern AudioConnection wavelinecord20;
extern AudioConnection wavelinecord21;
extern AudioConnection wavelinecord22;
extern AudioConnection wavelinecord23;
extern AudioConnection wavelinecord24;

extern AudioConnection wavelinecord33;
extern AudioConnection wavelinecord34;
extern AudioConnection wavelinecord35;
extern AudioConnection wavelinecord36;
extern AudioConnection wavelinecord37;
extern AudioConnection wavelinecord39;
extern AudioConnection wavelinecord41;
extern AudioConnection wavelinecord42;
extern AudioConnection wavelinecord43;
extern AudioConnection wavelinecord44;
extern AudioConnection wavelinecord45;
extern AudioConnection wavelinecord47;

extern AudioConnection modulateCord01;
extern AudioConnection modulateCord02;
extern AudioConnection modulateCord03;
extern AudioConnection modulateCord04;
extern AudioConnection modulateCord05;
extern AudioConnection modulateCord06;
extern AudioConnection modulateCord09;
extern AudioConnection modulateCord10;
extern AudioConnection modulateCord11;
extern AudioConnection modulateCord12;
extern AudioConnection modulateCord13;
extern AudioConnection modulateCord14;
extern AudioConnection modulateCord17;
extern AudioConnection modulateCord18;
extern AudioConnection modulateCord19;
extern AudioConnection modulateCord20;
extern AudioConnection modulateCord21;
extern AudioConnection modulateCord22;

extern AudioConnection MDwaveCord01;
extern AudioConnection MDwaveCord02;
extern AudioConnection MDwaveCord03;
extern AudioConnection MDwaveCord04;
extern AudioConnection MDwaveCord05;
extern AudioConnection MDwaveCord06;

extern AudioConnection MDwaveCord09;
extern AudioConnection MDwaveCord10;
extern AudioConnection MDwaveCord11;
extern AudioConnection MDwaveCord12;
extern AudioConnection MDwaveCord13;
extern AudioConnection MDwaveCord14;

extern AudioConnection MDwaveCord17;
extern AudioConnection MDwaveCord18;
extern AudioConnection MDwaveCord19;
extern AudioConnection MDwaveCord20;
extern AudioConnection MDwaveCord21;
extern AudioConnection MDwaveCord22;



extern AudioConnection MDdrumCord01;
extern AudioConnection MDdrumCord02;
extern AudioConnection MDdrumCord03;
extern AudioConnection MDdrumCord04;
extern AudioConnection MDdrumCord05;
extern AudioConnection MDdrumCord06;

extern AudioConnection MDdrumCord09;
extern AudioConnection MDdrumCord10;
extern AudioConnection MDdrumCord11;
extern AudioConnection MDdrumCord12;
extern AudioConnection MDdrumCord13;
extern AudioConnection MDdrumCord14;

extern AudioConnection MDdrumCord17;
extern AudioConnection MDdrumCord18;
extern AudioConnection MDdrumCord19;
extern AudioConnection MDdrumCord20;
extern AudioConnection MDdrumCord21;
extern AudioConnection MDdrumCord22;

extern AudioConnection MDstringCord01;
extern AudioConnection MDstringCord02;
extern AudioConnection MDstringCord03;
extern AudioConnection MDstringCord04;
extern AudioConnection MDstringCord05;
extern AudioConnection MDstringCord06;

extern AudioConnection MDstringCord09;
extern AudioConnection MDstringCord10;
extern AudioConnection MDstringCord11;
extern AudioConnection MDstringCord12;
extern AudioConnection MDstringCord13;
extern AudioConnection MDstringCord14;

extern AudioConnection MDstringCord17;
extern AudioConnection MDstringCord18;
extern AudioConnection MDstringCord19;
extern AudioConnection MDstringCord20;
extern AudioConnection MDstringCord21;
extern AudioConnection MDstringCord22;


extern AudioConnection *stringcords1[SYNTH_LINERS_COUNT*OSCS_COUNT] ;

extern AudioConnection *drumcords1[SYNTH_LINERS_COUNT*OSCS_COUNT] ;

extern AudioConnection *modulatecords1[SYNTH_LINERS_COUNT*OSCS_COUNT] ;

extern AudioConnection *MDdrumcords1[SYNTH_LINERS_COUNT*OSCS_COUNT] ;

extern AudioConnection *MDwavecords1[SYNTH_LINERS_COUNT*OSCS_COUNT] ;

extern AudioConnection *MDstringcords1[SYNTH_LINERS_COUNT*OSCS_COUNT] ;

extern AudioConnection *FMwavecords1[SYNTH_LINERS_COUNT*OSCS_COUNT] ;

extern AudioConnection *wavelinescords[SYNTH_LINERS_COUNT*OSCS_COUNT] ;

extern AudioSynthWaveform *waveforms1[SYNTH_LINERS_COUNT*OSCS_COUNT] ;

extern AudioSynthWaveformModulated *FMwaveforms1[SYNTH_LINERS_COUNT*OSCS_COUNT] ;

extern AudioSynthSimpleDrum *drums1[SYNTH_LINERS_COUNT*OSCS_COUNT] ;

extern AudioSynthKarplusStrong *strings1[SYNTH_LINERS_COUNT*OSCS_COUNT];

extern AudioMixer4 *Wavesmix[SYNTH_LINERS_COUNT];

extern AudioPlaySerialflashRaw *FlashSampler[16] ;

extern AudioMixer4 *Flashmixer[4];

extern AudioAmplifier *Wavespreamp303[SYNTH_LINERS_COUNT];

extern AudioSynthWaveform *LFOwaveforms1[OSCS_COUNT];

extern AudioEffectEnvelope *enveloppesL[SYNTH_LINERS_COUNT];


extern AudioPlaySdMp3           playMp31;
extern AudioPlaySdFlac          playFlac1;

extern AudioPlayPartialSdRaw PartialPlayerMono;
extern AudioMixer4 sd_mixerL ;
extern AudioMixer4 sd_mixerR ;

extern AudioConnection          sd_mix_itL;
extern AudioConnection          sd_mix_itR;
extern AudioConnection          sd_mix_partialL;
extern AudioConnection          sd_mix_partialR;
extern AudioConnection          sd_mix_mp3L;
extern AudioConnection          sd_mix_mp3R;
extern AudioConnection          sd_mix_flacL;
extern AudioConnection          sd_mix_flacR;


