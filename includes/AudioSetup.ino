#include <Audio.h>
#include <SD.h>

#include <SPI.h>
#include <LittleFS.h>
//#include <SerialFlash.h>
#include <Wire.h>
#include "../play_little_serialflash_raw.h"
//littlefs in seriallittle
//#include <LittleFS.h> // from Paul as well

//AudioPlayLittleSerialflashRaw
LittleFS_SPIFlash thyfs;


EXTMEM AudioPlayLittleSerialflashRaw  FlashSampler1;  //xy=1731.8833312988281,20
EXTMEM AudioPlayLittleSerialflashRaw  FlashSampler2;  //xy=1731.8833312988281,60
EXTMEM AudioPlayLittleSerialflashRaw  FlashSampler5;  //xy=1732.8833312988281,182
EXTMEM AudioPlayLittleSerialflashRaw  FlashSampler6;  //xy=1732.8833312988281,217
EXTMEM AudioPlayLittleSerialflashRaw  FlashSampler4;  //xy=1733.8833312988281,130
EXTMEM AudioPlayLittleSerialflashRaw  FlashSampler9;  //xy=1733.8833312988281,339
EXTMEM AudioPlayLittleSerialflashRaw  FlashSampler3;  //xy=1734.8833312988281,93
EXTMEM AudioPlayLittleSerialflashRaw  FlashSampler10; //xy=1733.8833312988281,374
EXTMEM AudioPlayLittleSerialflashRaw  FlashSampler8;  //xy=1734.8833312988281,287
EXTMEM AudioPlayLittleSerialflashRaw  FlashSampler7;  //xy=1735.8833312988281,250
EXTMEM AudioPlayLittleSerialflashRaw  FlashSampler12; //xy=1735.8833312988281,444
EXTMEM AudioPlayLittleSerialflashRaw  FlashSampler13; //xy=1735.8833312988281,495
EXTMEM AudioPlayLittleSerialflashRaw  FlashSampler14; //xy=1735.8833312988281,530
EXTMEM AudioPlayLittleSerialflashRaw  FlashSampler11; //xy=1736.8833312988281,407
EXTMEM AudioPlayLittleSerialflashRaw  FlashSampler16; //xy=1737.8833312988281,600
EXTMEM AudioPlayLittleSerialflashRaw  FlashSampler15; //xy=1738.8833312988281,563

EXTMEM AudioPlayLittleSerialflashRaw  FlashRaw;       //xy=2350.8831787109375,178
EXTMEM AudioConnection          apatchCord133(FlashRaw, 0, flashMastermix, 1);

EXTMEM AudioMixer4              flashmix1;      //xy=1945.8833312988281,83
EXTMEM AudioMixer4              flashmix2;      //xy=1946.8833312988281,239
EXTMEM AudioMixer4              flashmix3;      //xy=1947.8833312988281,396
EXTMEM AudioMixer4              flashmix4;      //xy=2009.8833312988281,549

EXTMEM AudioConnection          apatchCord67(FlashSampler1, 0, flashmix1, 0);
EXTMEM AudioConnection          apatchCord68(FlashSampler2, 0, flashmix1, 1);
EXTMEM AudioConnection          apatchCord69(FlashSampler5, 0, flashmix2, 0);
EXTMEM AudioConnection          apatchCord70(FlashSampler6, 0, flashmix2, 1);
EXTMEM AudioConnection          apatchCord71(FlashSampler4, 0, flashmix1, 3);
EXTMEM AudioConnection          apatchCord72(FlashSampler9, 0, flashmix3, 0);
EXTMEM AudioConnection          apatchCord73(FlashSampler3, 0, flashmix1, 2);
EXTMEM AudioConnection          apatchCord74(FlashSampler10, 0, flashmix3, 1);
EXTMEM AudioConnection          apatchCord75(FlashSampler8, 0, flashmix2, 3);
EXTMEM AudioConnection          apatchCord76(FlashSampler7, 0, flashmix2, 2);
EXTMEM AudioConnection          apatchCord77(FlashSampler12, 0, flashmix3, 3);
EXTMEM AudioConnection          apatchCord79(FlashSampler13, 0, flashmix4, 0);
EXTMEM AudioConnection          apatchCord80(FlashSampler14, 0, flashmix4, 1);
EXTMEM AudioConnection          apatchCord81(FlashSampler11, 0, flashmix3, 2);
EXTMEM AudioConnection          apatchCord82(FlashSampler16, 0, flashmix4, 3);
EXTMEM AudioConnection          apatchCord83(FlashSampler15, 0, flashmix4, 2);

// GUItool: begin automatically generated code
EXTMEM AudioSynthWaveform       LFOrm2;         //xy=57,1009
EXTMEM AudioEffectMultiply      multiply2;      //xy=61,970
EXTMEM AudioEffectMultiply      multiply2R;      //xy=63,975

EXTMEM AudioSynthWaveform       LFOrm3;         //xy=73,1240
EXTMEM AudioEffectMultiply      multiply3;      //xy=74,1200
EXTMEM AudioEffectMultiply      multiply3R;      //xy=76,1205
EXTMEM AudioSynthWaveform       LFOrm1;         //xy=106,708
EXTMEM AudioEffectMultiply      multiply1;      //xy=129,637
EXTMEM AudioEffectMultiply      multiply1R;      //xy=131,640
EXTMEM AudioSynthWaveformModulated FMWaveform1L3;  //xy=408,866
EXTMEM AudioSynthWaveformModulated FMWaveform2L3;  //xy=409,900
EXTMEM AudioSynthWaveformModulated FMWaveform1L2;  //xy=410,728
EXTMEM AudioSynthWaveformModulated FMWaveform2L2;  //xy=411,762
EXTMEM AudioSynthWaveformModulated FMWaveform3L3;  //xy=411,932
EXTMEM AudioSynthWaveformModulated FMWaveform1L4;  //xy=411,1003
EXTMEM AudioSynthWaveformModulated FMWaveform1L1;  //xy=413,589
EXTMEM AudioSynthWaveformModulated FMWaveform2L4;  //xy=413,1037
EXTMEM AudioSynthWaveformModulated FMWaveform2L1;  //xy=415,623
EXTMEM AudioSynthWaveformModulated FMWaveform3L2;  //xy=415,799
EXTMEM AudioSynthWaveformModulated FMWaveform3L4;  //xy=415,1070
EXTMEM AudioSynthWaveformModulated FMWaveform1L5;  //xy=415,1153
EXTMEM AudioSynthWaveformModulated FMWaveform3L1;  //xy=417,655
EXTMEM AudioSynthWaveformModulated FMWaveform2L5;  //xy=417,1187
EXTMEM AudioSynthWaveformModulated FMWaveform3L5;  //xy=419,1220
EXTMEM AudioSynthWaveformModulated FMWaveform1L6;  //xy=429,1302
EXTMEM AudioSynthWaveformModulated FMWaveform2L6;  //xy=431,1336
EXTMEM AudioSynthWaveformModulated FMWaveform3L6;  //xy=433,1369
EXTMEM AudioEffectMultiply      modulate1L6;    //xy=605,1291
EXTMEM AudioEffectMultiply      modulate2L6;    //xy=605,1323
EXTMEM AudioEffectMultiply      modulate3L6;    //xy=607,1354
EXTMEM AudioEffectMultiply      modulate1L2;    //xy=619,751
EXTMEM AudioEffectMultiply      modulate2L2;    //xy=619,783
EXTMEM AudioEffectMultiply      modulate1L3;    //xy=619,885
EXTMEM AudioEffectMultiply      modulate2L3;    //xy=619,917
EXTMEM AudioEffectMultiply      modulate1L5;    //xy=619,1152
EXTMEM AudioEffectMultiply      modulate2L5;    //xy=619,1184
EXTMEM AudioEffectMultiply      modulate3L2;    //xy=621,814
EXTMEM AudioEffectMultiply      modulate3L3;    //xy=621,948
EXTMEM AudioEffectMultiply      modulate3L5;    //xy=621,1215
EXTMEM AudioEffectMultiply      modulate1L4;    //xy=623,1019
EXTMEM AudioEffectMultiply      modulate2L4;    //xy=623,1051
EXTMEM AudioEffectMultiply      modulate3L4;    //xy=625,1082
EXTMEM AudioEffectMultiply      modulate1L1;    //xy=629,622
EXTMEM AudioEffectMultiply      modulate2L1;    //xy=629,654
EXTMEM AudioEffectMultiply      modulate3L1;    //xy=631,685
EXTMEM AudioSynthSimpleDrum     drum3L6;        //xy=828,1341
EXTMEM AudioSynthSimpleDrum     drum2L1;        //xy=831,636
EXTMEM AudioSynthSimpleDrum     drum2L6;        //xy=829,1306
EXTMEM AudioSynthSimpleDrum     drum2L5;        //xy=830,1176
EXTMEM AudioSynthSimpleDrum     drum3L1;        //xy=833,669
EXTMEM AudioSynthSimpleDrum     drum1L1;        //xy=834,606
EXTMEM AudioSynthSimpleDrum     drum3L5;        //xy=832,1209
EXTMEM AudioSynthSimpleDrum     drum1L6;        //xy=832,1276
EXTMEM AudioSynthSimpleDrum     drum1L5;        //xy=833,1146
EXTMEM AudioSynthSimpleDrum     drum2L3;        //xy=835,906
EXTMEM AudioSynthSimpleDrum     drum2L4;        //xy=836,1046
EXTMEM AudioSynthSimpleDrum     drum3L3;        //xy=837,939
EXTMEM AudioSynthSimpleDrum     drum1L3;        //xy=838,876
EXTMEM AudioSynthSimpleDrum     drum3L4;        //xy=838,1079
EXTMEM AudioSynthSimpleDrum     drum1L4;        //xy=839,1016
EXTMEM AudioSynthSimpleDrum     drum2L2;        //xy=840,779
EXTMEM AudioSynthSimpleDrum     drum3L2;        //xy=842,812
EXTMEM AudioSynthSimpleDrum     drum1L2;        //xy=843,749
EXTMEM AudioSynthKarplusStrong  string2L6;      //xy=960,1298
EXTMEM AudioSynthKarplusStrong  string3L6;      //xy=963,1332
EXTMEM AudioSynthKarplusStrong  string3L4;      //xy=965,1061
EXTMEM AudioSynthKarplusStrong  string2L4;      //xy=966,1028
EXTMEM AudioSynthKarplusStrong  string1L6;      //xy=966,1266
EXTMEM AudioSynthKarplusStrong  string3L3;      //xy=970,928
EXTMEM AudioSynthKarplusStrong  string3L1;      //xy=972,643
EXTMEM AudioSynthKarplusStrong  string2L3;      //xy=971,895
EXTMEM AudioSynthKarplusStrong  string2L1;      //xy=973,610
EXTMEM AudioSynthKarplusStrong  string1L2;      //xy=973,716
EXTMEM AudioSynthKarplusStrong  string1L4;      //xy=972,996
EXTMEM AudioSynthKarplusStrong  string3L2;      //xy=973,795
EXTMEM AudioSynthKarplusStrong  string2L2;      //xy=974,762
EXTMEM AudioSynthKarplusStrong  string3L5;      //xy=976,1197
EXTMEM AudioSynthKarplusStrong  string1L3;      //xy=978,863
EXTMEM AudioSynthKarplusStrong  string2L5;      //xy=977,1164
EXTMEM AudioSynthKarplusStrong  string1L1;      //xy=980,578
EXTMEM AudioSynthKarplusStrong  string1L5;      //xy=983,1132
EXTMEM AudioSynthWaveform       waveform1L5;    //xy=1161,1146
EXTMEM AudioSynthWaveform       waveform1L6;    //xy=1161,1277
EXTMEM AudioSynthWaveform       waveform2L5;    //xy=1164,1178
EXTMEM AudioSynthWaveform       waveform3L5;    //xy=1164,1207
EXTMEM AudioSynthWaveform       waveform2L6;    //xy=1164,1310
EXTMEM AudioSynthWaveform       waveform3L6;    //xy=1164,1339
EXTMEM AudioSynthWaveform       waveform1L4;    //xy=1169,993
EXTMEM AudioSynthWaveform       waveform3L3;    //xy=1172,921
EXTMEM AudioSynthWaveform       waveform1L2;    //xy=1173,727
EXTMEM AudioSynthWaveform       waveform2L3;    //xy=1173,891
EXTMEM AudioSynthWaveform       waveform2L4;    //xy=1173,1026
EXTMEM AudioSynthWaveform       waveform3L4;    //xy=1173,1055
EXTMEM AudioSynthWaveform       waveform1L3;    //xy=1174,857
EXTMEM AudioSynthWaveform       waveform3L2;    //xy=1177,787
EXTMEM AudioSynthWaveform       waveform3L1;    //xy=1178,659
EXTMEM AudioSynthWaveform       waveform2L2;    //xy=1178,757
EXTMEM AudioSynthWaveform       waveform2L1;    //xy=1179,629
EXTMEM AudioSynthWaveform       waveform1L1;    //xy=1180,597
EXTMEM AudioMixer4              WavesL5;        //xy=1310,1191
EXTMEM AudioMixer4              WavesL6;        //xy=1310,1323
EXTMEM AudioMixer4              WavesL3;        //xy=1319,904
EXTMEM AudioMixer4              WavesL4;        //xy=1319,1039
EXTMEM AudioMixer4              WavesL2;        //xy=1324,770
EXTMEM AudioMixer4              WavesL1;        //xy=1348,647
EXTMEM AudioEffectEnvelope      envelopeL5;     //xy=1438,1341
EXTMEM AudioEffectEnvelope      envelopeL2;     //xy=1469,903
EXTMEM AudioEffectEnvelope      envelopeL3;     //xy=1477,1038
EXTMEM AudioEffectEnvelope      envelopeL4;     //xy=1482,1185
EXTMEM AudioEffectEnvelope      envelopeL0;     //xy=1493,615
EXTMEM AudioEffectEnvelope      envelopeL1;     //xy=1496,769
EXTMEM AudioAmplifier           fade5;          //xy=1588,1358
EXTMEM AudioAmplifier           wavePAmp5;      //xy=1603,1324
EXTMEM AudioAmplifier           fade0;          //xy=1626,705
EXTMEM AudioAmplifier           wavePAmp0;      //xy=1635,662
EXTMEM AudioAmplifier           fade2;          //xy=1638,952
EXTMEM AudioAmplifier           fade1;          //xy=1642,827
EXTMEM AudioAmplifier           wavePAmp1;      //xy=1645,788
EXTMEM AudioAmplifier           fade3;          //xy=1645,1067
EXTMEM AudioAmplifier           wavePAmp2;      //xy=1647,916
EXTMEM AudioAmplifier           wavePAmp3;      //xy=1652,1031
EXTMEM AudioAmplifier           fade4;          //xy=1671,1240
EXTMEM AudioAmplifier           wavePAmp4;      //xy=1684,1202
EXTMEM AudioFilterStateVariable filter303L6;    //xy=1752,1332
EXTMEM AudioFilterStateVariable filter303L1;    //xy=1781,668
EXTMEM AudioFilterStateVariable filter303L2;    //xy=1790,797
EXTMEM AudioFilterStateVariable filter303L3;    //xy=1795,921
EXTMEM AudioFilterStateVariable filter303L4;    //xy=1806,1045
EXTMEM AudioFilterStateVariable filter303L5;    //xy=1836,1213
EXTMEM AudioMixer4              mix303L6;       //xy=1909,1342
EXTMEM AudioMixer4              mix303L1;       //xy=1937,685
EXTMEM AudioMixer4              mix303L2;       //xy=1937,804
EXTMEM AudioMixer4              mix303L3;       //xy=1954,905
EXTMEM AudioMixer4              mix303L4;       //xy=1962,1026
EXTMEM AudioMixer4              mix303L5;       //xy=2031,1213
EXTMEM AudioMixer4              flashmixMain;   //xy=2047,253
EXTMEM AudioInputI2S            AudioIn1;       //xy=2050,524
EXTMEM AudioInputUSB            usb1;           //xy=2052,418
EXTMEM AudioMixer4              mixerWet303L6;  //xy=2065,1334
EXTMEM AudioMixer4              mixerWet303L2;  //xy=2102,789
EXTMEM AudioMixer4              mixerWet303L1;  //xy=2115,649
EXTMEM AudioMixer4              mixerWet303L3;  //xy=2125,883
EXTMEM AudioMixer4              mixerWet303L4;  //xy=2136,1009
EXTMEM AudioMixer4              mixerWet303L5;  //xy=2201,1190
EXTMEM AudioMixer4              InMixL;         //xy=2243,437
EXTMEM AudioMixer4              InMixR;         //xy=2247,545
EXTMEM AudioMixer4              mixerWL1to4;    //xy=2319,875
EXTMEM AudioPlaySdRaw           playRawL;       //xy=2325,376
EXTMEM AudioPlaySdRaw           playRawR;       //xy=2356,697
EXTMEM AudioPlaySdWav           playSdWav1;     //xy=2365,488
EXTMEM AudioMixer4              mixerWL5to8;    //xy=2370,1348
EXTMEM AudioSynthSimpleDrum     metrodrum1;     //xy=2374,608
EXTMEM AudioAmplifier           LineInPreAmpL;  //xy=2397,437
EXTMEM AudioAmplifier           LineInPreAmpR;  //xy=2412,544
EXTMEM AudioMixer4              flashMastermix; //xy=2504,142
EXTMEM AudioMixer4              mixerWAll;      //xy=2506,931
EXTMEM AudioMixer4              MasterL;        //xy=2579,371
EXTMEM AudioMixer4              MasterR;        //xy=2598,562
EXTMEM AudioMixer4              MasterR1;       //xy=2830.666618347168,493.3333225250244
AudioEffectFlange        flange1;        //xy=2833,989
EXTMEM AudioEffectBitcrusher    bitcrusher1;    //xy=2837,941
AudioEffectChorus        chorus1;        //xy=2842,1032
EXTMEM AudioFilterBiquad        biquad1;        //xy=2843,1080
EXTMEM AudioEffectGranular      granular1;      //xy=2850,875
EXTMEM AudioMixer4              MasterL1;       //xy=2856,411
EXTMEM AudioEffectReverb        freeverbs1;     //xy=2855,833
EXTMEM AudioEffectBitcrusher    bitcrusher1R;    //xy=2859.9999389648438,1540.000020980835
AudioEffectFlange        flange1R; //xy=2866.66650390625,1591.6666259765625
EXTMEM AudioEffectReverb        freeverbs1R; //xy=2871.999954223633,1425.6666011810303
AudioEffectChorus        chorus1R; //xy=2875.66650390625,1634.6666259765625
EXTMEM AudioFilterBiquad        biquad1R; //xy=2876.66650390625,1682.6666259765625
EXTMEM AudioEffectGranular      granular1R;      //xy=2886.6666946411133,1488.3333921432495
EXTMEM AudioEffectGranular      granular2;      //xy=2982,878
EXTMEM AudioEffectBitcrusher    bitcrusher2;    //xy=2982,948
AudioEffectFlange        flange2;        //xy=2987,1002
AudioEffectChorus        chorus2;        //xy=2991,1046
EXTMEM AudioEffectReverb        freeverbs2;     //xy=2996,824
EXTMEM AudioFilterBiquad        biquad2;        //xy=2998,1093
EXTMEM AudioFilterStateVariable filter3;        //xy=2999,1318
EXTMEM AudioFilterStateVariable filter1;        //xy=3001,1175
EXTMEM AudioFilterStateVariable filter2;        //xy=3004,1246
EXTMEM AudioEffectBitcrusher    bitcrusher2R;    //xy=3020.0001068115234,1546.6667280197144
AudioEffectFlange        flange2R; //xy=3020.66650390625,1604.6666259765625
AudioEffectChorus        chorus2R; //xy=3024.66650390625,1648.6666259765625
EXTMEM AudioEffectReverb        freeverbs2R; //xy=3029.66650390625,1426.6666259765625
EXTMEM AudioFilterBiquad        biquad2R; //xy=3031.66650390625,1695.6666259765625
EXTMEM AudioFilterStateVariable filter3R; //xy=3032.66650390625,1920.6666259765625
EXTMEM AudioFilterStateVariable filter1R; //xy=3034.66650390625,1777.6666259765625
EXTMEM AudioEffectGranular      granular2R;      //xy=3036.6665420532227,1496.6666450500488
EXTMEM AudioFilterStateVariable filter2R; //xy=3037.66650390625,1848.6666259765625
EXTMEM AudioMixer4              WetMixMasterR;  //xy=3112.3333740234375,530.6666469573975
EXTMEM AudioMixer4              WetMixMasterL;  //xy=3113,434
EXTMEM AudioEffectGranular      granular3;      //xy=3132,886
AudioEffectFlange        flange3;        //xy=3132,1000
AudioEffectChorus        chorus3;        //xy=3135,1043
EXTMEM AudioFilterBiquad        biquad3;        //xy=3143,1091
EXTMEM AudioEffectBitcrusher    bitcrusher3;    //xy=3144,948
EXTMEM AudioEffectReverb        freeverbs3;     //xy=3145,828
EXTMEM AudioMixer4              mixfilter1;     //xy=3157,1181
EXTMEM AudioMixer4              mixfilter3;     //xy=3162,1318
EXTMEM AudioMixer4              mixfilter2;     //xy=3164,1249
AudioEffectFlange        flange3R; //xy=3165.66650390625,1602.6666259765625
AudioEffectChorus        chorus3R; //xy=3168.66650390625,1645.6666259765625
EXTMEM AudioFilterBiquad        biquad3R; //xy=3176.66650390625,1693.6666259765625
EXTMEM AudioEffectReverb        freeverbs3R; //xy=3178.66650390625,1430.6666259765625
EXTMEM AudioEffectBitcrusher    bitcrusher3R;    //xy=3178.3332901000977,1550.0000610351562
EXTMEM AudioEffectGranular      granular3R;      //xy=3188.333333333333,1498.333333333333
EXTMEM AudioMixer4              mixfilter1R; //xy=3190.66650390625,1783.6666259765625
EXTMEM AudioMixer4              mixfilter3R; //xy=3195.66650390625,1920.6666259765625
EXTMEM AudioMixer4              mixfilter2R; //xy=3197.66650390625,1851.6666259765625
EXTMEM AudioMixer4              FXBusL;         //xy=3453,329
EXTMEM AudioMixer4              FXBusR;         //xy=3468,506
EXTMEM AudioAmplifier           ampL;           //xy=3633,458
EXTMEM AudioAmplifier           ampR;           //xy=3633,506
EXTMEM AudioMixer4              feedbackdelay1R; //xy=3746.333335876465,1183.3333339691162
EXTMEM AudioMixer4              feedbackdelay1; //xy=3758.333320617676,659.0000076293945
AudioRecordQueue         queue2;         //xy=3779,559
EXTMEM AudioMixer4              feedbackdelay3R; //xy=3780.333236694336,1382.3333473205566
EXTMEM AudioMixer4              feedbackdelay2; //xy=3785,825
EXTMEM AudioMixer4              feedbackdelay2R; //xy=3786.333335876465,1284.3333339691162
EXTMEM AudioMixer4              feedbackdelay3; //xy=3789,978
AudioRecordQueue         queue1;         //xy=3809,368
EXTMEM AudioOutputI2S           AudioOutput;    //xy=3846,481
EXTMEM AudioEffectDelay         delay1;         //xy=3931.6665802001953,611.6667098999023
EXTMEM AudioEffectDelay         delay2;         //xy=3950.6665802001953,770.6666793823242
EXTMEM AudioEffectDelay         delay3;         //xy=3954.333164215088,904.3333053588867
EXTMEM AudioEffectDelay         delay1R; //xy=3961.66650390625,1171.6666259765625
EXTMEM AudioEffectDelay         delay2R; //xy=3962.3330841064453,1327.3333053588867
EXTMEM AudioEffectDelay         delay3R; //xy=3970.9996700286865,1460.999855041504
EXTMEM AudioAnalyzeNoteFrequency notefreq1;      //xy=4014,421
EXTMEM AudioMixer4              delay1pre1;     //xy=4099.666664123535,564.3333358764648
EXTMEM AudioMixer4              delay1pre2;     //xy=4100,657.6666870117188
EXTMEM AudioMixer4              delay2pre1;     //xy=4100,737.6666870117188
EXTMEM AudioMixer4              delay3pre1;     //xy=4101,870.6666870117188
EXTMEM AudioMixer4              delay2pre2;     //xy=4102,801.6666870117188
EXTMEM AudioMixer4              delay3pre2;     //xy=4102,940.6666870117188
EXTMEM AudioMixer4              delay1pre2R; //xy=4126.66650390625,1212.6666259765625
EXTMEM AudioMixer4              delay2pre1R; //xy=4126.66650390625,1292.6666259765625
EXTMEM AudioMixer4              delay3pre1R; //xy=4127.66650390625,1425.6666259765625
EXTMEM AudioMixer4              delay2pre2R; //xy=4128.66650390625,1356.6666259765625
EXTMEM AudioMixer4              delay3pre2R; //xy=4128.66650390625,1495.6666259765625
EXTMEM AudioMixer4              delay1pre1R; //xy=4134.66650390625,1117.6666259765625
EXTMEM AudioMixer4              delaymix3;      //xy=4251,908.6666870117188
EXTMEM AudioMixer4              delaymix2;      //xy=4256,780.6666870117188
EXTMEM AudioMixer4              delaymix1;      //xy=4272,618.6666870117188
EXTMEM AudioMixer4              delaymix3R; //xy=4277.66650390625,1463.6666259765625
EXTMEM AudioMixer4              delaymix2R; //xy=4282.66650390625,1335.6666259765625
EXTMEM AudioMixer4              delaymix1R; //xy=4298.66650390625,1173.6666259765625

EXTMEM AudioConnection          patchCord1(LFOrm2, 0, FMWaveform2L2, 0);
EXTMEM AudioConnection          patchCord2(LFOrm2, 0, FMWaveform2L1, 0);
EXTMEM AudioConnection          patchCord3(LFOrm2, 0, FMWaveform2L3, 0);
EXTMEM AudioConnection          patchCord4(LFOrm2, 0, FMWaveform2L4, 0);
EXTMEM AudioConnection          patchCord5(LFOrm2, 0, FMWaveform2L5, 0);
EXTMEM AudioConnection          patchCord6(LFOrm2, 0, FMWaveform2L6, 0);
EXTMEM AudioConnection          patchCord7(LFOrm2, 0, modulate2L5, 1);
EXTMEM AudioConnection          patchCord8(LFOrm2, 0, modulate2L3, 1);
EXTMEM AudioConnection          patchCord9(LFOrm2, 0, modulate2L6, 1);
EXTMEM AudioConnection          patchCord10(LFOrm2, 0, modulate2L1, 1);
EXTMEM AudioConnection          patchCord11(LFOrm2, 0, modulate2L2, 1);
EXTMEM AudioConnection          patchCord12(LFOrm2, 0, modulate2L4, 1);
EXTMEM AudioConnection          patchCord13(LFOrm2, 0, multiply2, 1);
EXTMEM AudioConnection          apatchCord13R(LFOrm2, 0, multiply2R, 1);
EXTMEM AudioConnection          patchCord14(LFOrm3, 0, FMWaveform3L3, 0);
EXTMEM AudioConnection          patchCord15(LFOrm3, 0, FMWaveform3L1, 0);
EXTMEM AudioConnection          patchCord16(LFOrm3, 0, FMWaveform3L2, 0);
EXTMEM AudioConnection          patchCord17(LFOrm3, 0, FMWaveform3L4, 0);
EXTMEM AudioConnection          patchCord18(LFOrm3, 0, FMWaveform3L5, 0);
EXTMEM AudioConnection          patchCord19(LFOrm3, 0, FMWaveform3L6, 0);
EXTMEM AudioConnection          patchCord20(LFOrm3, 0, modulate3L1, 1);
EXTMEM AudioConnection          patchCord21(LFOrm3, 0, modulate3L2, 1);
EXTMEM AudioConnection          patchCord22(LFOrm3, 0, modulate3L3, 1);
EXTMEM AudioConnection          patchCord23(LFOrm3, 0, modulate3L5, 1);
EXTMEM AudioConnection          patchCord24(LFOrm3, 0, modulate3L4, 1);
EXTMEM AudioConnection          patchCord25(LFOrm3, 0, modulate3L6, 1);
EXTMEM AudioConnection          patchCord26(LFOrm3, 0, multiply3, 1);
EXTMEM AudioConnection          apatchCord26R(LFOrm3, 0, multiply3R, 1);
EXTMEM AudioConnection          patchCord27(LFOrm1, 0, FMWaveform1L1, 0);
EXTMEM AudioConnection          patchCord28(LFOrm1, 0, FMWaveform1L2, 0);
EXTMEM AudioConnection          patchCord29(LFOrm1, 0, FMWaveform1L3, 0);
EXTMEM AudioConnection          patchCord30(LFOrm1, 0, FMWaveform1L4, 0);
EXTMEM AudioConnection          patchCord31(LFOrm1, 0, FMWaveform1L5, 0);
EXTMEM AudioConnection          patchCord32(LFOrm1, 0, FMWaveform1L6, 0);
EXTMEM AudioConnection          patchCord33(LFOrm1, 0, modulate1L1, 1);
EXTMEM AudioConnection          patchCord34(LFOrm1, 0, modulate1L2, 1);
EXTMEM AudioConnection          patchCord35(LFOrm1, 0, modulate1L3, 1);
EXTMEM AudioConnection          patchCord36(LFOrm1, 0, modulate1L4, 1);
EXTMEM AudioConnection          patchCord37(LFOrm1, 0, modulate1L5, 1);
EXTMEM AudioConnection          patchCord38(LFOrm1, 0, modulate1L6, 1);
EXTMEM AudioConnection          patchCord39(LFOrm1, 0, multiply1, 1);
EXTMEM AudioConnection          apatchCord39R(LFOrm1, 0, multiply1R, 1);
EXTMEM AudioConnection          patchCord40(WavesL5, envelopeL4);
EXTMEM AudioConnection          patchCord41(WavesL6, envelopeL5);
EXTMEM AudioConnection          patchCord42(WavesL3, envelopeL2);
EXTMEM AudioConnection          patchCord43(WavesL4, envelopeL3);
EXTMEM AudioConnection          patchCord44(WavesL2, envelopeL1);
EXTMEM AudioConnection          patchCord45(WavesL1, envelopeL0);
EXTMEM AudioConnection          patchCord46(envelopeL5, 0, mixerWet303L6, 0);
EXTMEM AudioConnection          patchCord47(envelopeL5, wavePAmp5);
EXTMEM AudioConnection          patchCord48(envelopeL2, 0, mixerWet303L3, 0);
EXTMEM AudioConnection          patchCord49(envelopeL2, wavePAmp2);
EXTMEM AudioConnection          patchCord50(envelopeL3, 0, mixerWet303L4, 0);
EXTMEM AudioConnection          patchCord51(envelopeL3, wavePAmp3);
EXTMEM AudioConnection          patchCord52(envelopeL4, 0, mixerWet303L5, 0);
EXTMEM AudioConnection          patchCord53(envelopeL4, wavePAmp4);
EXTMEM AudioConnection          patchCord54(envelopeL0, wavePAmp0);
EXTMEM AudioConnection          patchCord55(envelopeL0, 0, mixerWet303L1, 0);
EXTMEM AudioConnection          patchCord56(envelopeL1, 0, mixerWet303L2, 0);
EXTMEM AudioConnection          patchCord57(envelopeL1, wavePAmp1);
EXTMEM AudioConnection          patchCord58(wavePAmp5, 0, filter303L6, 0);
EXTMEM AudioConnection          patchCord59(wavePAmp0, 0, filter303L1, 0);
EXTMEM AudioConnection          patchCord60(wavePAmp1, 0, filter303L2, 0);
EXTMEM AudioConnection          patchCord61(wavePAmp2, 0, filter303L3, 0);
EXTMEM AudioConnection          patchCord62(wavePAmp3, 0, filter303L4, 0);
EXTMEM AudioConnection          patchCord63(wavePAmp4, 0, filter303L5, 0);
EXTMEM AudioConnection          patchCord64(filter303L6, 0, mix303L6, 0);
EXTMEM AudioConnection          patchCord65(filter303L6, 1, mix303L6, 1);
EXTMEM AudioConnection          patchCord66(filter303L6, 2, mix303L6, 2);
EXTMEM AudioConnection          patchCord67(filter303L1, 0, mix303L1, 0);
EXTMEM AudioConnection          patchCord68(filter303L1, 1, mix303L1, 1);
EXTMEM AudioConnection          patchCord69(filter303L1, 2, mix303L1, 2);
EXTMEM AudioConnection          patchCord70(filter303L2, 0, mix303L2, 0);
EXTMEM AudioConnection          patchCord71(filter303L2, 1, mix303L2, 1);
EXTMEM AudioConnection          patchCord72(filter303L2, 2, mix303L2, 2);
EXTMEM AudioConnection          patchCord73(filter303L3, 0, mix303L3, 0);
EXTMEM AudioConnection          patchCord74(filter303L3, 1, mix303L3, 1);
EXTMEM AudioConnection          patchCord75(filter303L3, 2, mix303L3, 2);
EXTMEM AudioConnection          patchCord76(filter303L4, 0, mix303L4, 0);
EXTMEM AudioConnection          patchCord77(filter303L4, 1, mix303L4, 1);
EXTMEM AudioConnection          patchCord78(filter303L4, 2, mix303L4, 2);
EXTMEM AudioConnection          patchCord79(filter303L5, 0, mix303L5, 0);
EXTMEM AudioConnection          patchCord80(filter303L5, 1, mix303L5, 1);
EXTMEM AudioConnection          patchCord81(filter303L5, 2, mix303L5, 2);
EXTMEM AudioConnection          patchCord82(flashmix1, 0, flashmixMain, 0);
EXTMEM AudioConnection          patchCord83(flashmix2, 0, flashmixMain, 1);
EXTMEM AudioConnection          patchCord84(flashmix3, 0, flashmixMain, 2);
EXTMEM AudioConnection          patchCord85(flashmix4, 0, flashmixMain, 3);
EXTMEM AudioConnection          patchCord86(mix303L6, 0, mixerWet303L6, 1);
EXTMEM AudioConnection          patchCord87(mix303L1, 0, mixerWet303L1, 1);
EXTMEM AudioConnection          patchCord88(mix303L2, 0, mixerWet303L2, 1);
EXTMEM AudioConnection          patchCord89(mix303L3, 0, mixerWet303L3, 1);
EXTMEM AudioConnection          patchCord90(mix303L4, 0, mixerWet303L4, 1);
EXTMEM AudioConnection          patchCord91(mix303L5, 0, mixerWet303L5, 1);
EXTMEM AudioConnection          patchCord92(flashmixMain, 0, flashMastermix, 0);
EXTMEM AudioConnection          patchCord93(AudioIn1, 0, InMixL, 1);
EXTMEM AudioConnection          patchCord94(AudioIn1, 1, InMixR, 1);
EXTMEM AudioConnection          patchCord95(usb1, 0, InMixL, 0);
EXTMEM AudioConnection          patchCord96(usb1, 1, InMixR, 0);
EXTMEM AudioConnection          patchCord97(mixerWet303L6, 0, mixerWL5to8, 1);
EXTMEM AudioConnection          patchCord98(mixerWet303L2, 0, mixerWL1to4, 1);
EXTMEM AudioConnection          patchCord99(mixerWet303L1, 0, mixerWL1to4, 0);
EXTMEM AudioConnection          patchCord100(mixerWet303L3, 0, mixerWL1to4, 2);
EXTMEM AudioConnection          patchCord101(mixerWet303L4, 0, mixerWL1to4, 3);
EXTMEM AudioConnection          patchCord102(mixerWet303L5, 0, mixerWL5to8, 0);
EXTMEM AudioConnection          patchCord103(InMixL, LineInPreAmpL);
EXTMEM AudioConnection          patchCord104(InMixR, LineInPreAmpR);
EXTMEM AudioConnection          patchCord105(mixerWL1to4, 0, mixerWAll, 0);
EXTMEM AudioConnection          patchCord106(playRawL, 0, MasterL, 3);
EXTMEM AudioConnection          patchCord107(playRawR, 0, MasterR, 3);
EXTMEM AudioConnection          patchCord108(playSdWav1, 0, MasterL, 0);
EXTMEM AudioConnection          patchCord109(playSdWav1, 1, MasterR, 0);
EXTMEM AudioConnection          patchCord110(mixerWL5to8, 0, mixerWAll, 1);
EXTMEM AudioConnection          patchCord111(metrodrum1, 0, MasterL, 1);
EXTMEM AudioConnection          patchCord112(metrodrum1, 0, MasterR, 1);
EXTMEM AudioConnection          patchCord113(LineInPreAmpL, 0, MasterL, 2);
EXTMEM AudioConnection          patchCord114(LineInPreAmpR, 0, MasterR, 2);
EXTMEM AudioConnection          patchCord115(flashMastermix, 0, MasterL1, 3);
EXTMEM AudioConnection          patchCord116(flashMastermix, 0, MasterR1, 3);
EXTMEM AudioConnection          patchCord117(flashMastermix, 0, FXBusL, 1);
EXTMEM AudioConnection          patchCord118(flashMastermix, 0, FXBusR, 1);
EXTMEM AudioConnection          patchCord119(mixerWAll, 0, FXBusR, 2);
EXTMEM AudioConnection          patchCord120(mixerWAll, 0, FXBusL, 2);
EXTMEM AudioConnection          patchCord121(mixerWAll, 0, MasterL1, 2);
EXTMEM AudioConnection          patchCord122(mixerWAll, 0, MasterR1, 2);
EXTMEM AudioConnection          patchCord123(MasterL, 0, MasterL1, 0);
EXTMEM AudioConnection          patchCord124(MasterL, 0, FXBusL, 3);
EXTMEM AudioConnection          patchCord125(MasterR, 0, MasterR1, 0);
EXTMEM AudioConnection          patchCord126(MasterR, 0, FXBusR, 3);
EXTMEM AudioConnection          patchCord128(MasterR1, 0, WetMixMasterR, 0);
EXTMEM AudioConnection          patchCord131(MasterL1, 0, WetMixMasterL, 0);
EXTMEM AudioConnection          patchCord132(filter3, 0, mixfilter3, 0);
EXTMEM AudioConnection          patchCord133(filter3, 1, mixfilter3, 1);
EXTMEM AudioConnection          patchCord134(filter3, 2, mixfilter3, 2);
EXTMEM AudioConnection          patchCord135(filter1, 0, mixfilter1, 0);
EXTMEM AudioConnection          patchCord136(filter1, 1, mixfilter1, 1);
EXTMEM AudioConnection          patchCord137(filter1, 2, mixfilter1, 2);
EXTMEM AudioConnection          patchCord138(filter2, 0, mixfilter2, 0);
EXTMEM AudioConnection          patchCord139(filter2, 1, mixfilter2, 1);
EXTMEM AudioConnection          patchCord140(filter2, 2, mixfilter2, 2);
EXTMEM AudioConnection          patchCord141(filter3R, 0, mixfilter3R, 0);
EXTMEM AudioConnection          patchCord142(filter3R, 1, mixfilter3R, 1);
EXTMEM AudioConnection          patchCord143(filter3R, 2, mixfilter3R, 2);
EXTMEM AudioConnection          patchCord144(filter1R, 0, mixfilter1R, 0);
EXTMEM AudioConnection          patchCord145(filter1R, 1, mixfilter1R, 1);
EXTMEM AudioConnection          patchCord146(filter1R, 2, mixfilter1R, 2);
EXTMEM AudioConnection          patchCord147(filter2R, 0, mixfilter2R, 0);
EXTMEM AudioConnection          patchCord148(filter2R, 1, mixfilter2R, 1);
EXTMEM AudioConnection          patchCord149(filter2R, 2, mixfilter2R, 2);
EXTMEM AudioConnection          patchCord150(WetMixMasterR, 0, FXBusR, 0);
EXTMEM AudioConnection          patchCord151(WetMixMasterR, 0, feedbackdelay1R, 1);
EXTMEM AudioConnection          patchCord152(WetMixMasterR, 0, feedbackdelay2R, 1);
EXTMEM AudioConnection          patchCord153(WetMixMasterR, 0, feedbackdelay3R, 1);
EXTMEM AudioConnection          patchCord154(WetMixMasterL, 0, FXBusL, 0);
EXTMEM AudioConnection          patchCord155(WetMixMasterL, 0, feedbackdelay1, 1);
EXTMEM AudioConnection          patchCord156(WetMixMasterL, 0, feedbackdelay3, 1);
EXTMEM AudioConnection          patchCord157(WetMixMasterL, 0, feedbackdelay2, 1);
EXTMEM AudioConnection          patchCord158(FXBusL, ampL);
EXTMEM AudioConnection          patchCord159(FXBusR, ampR);
EXTMEM AudioConnection          patchCord160(ampL, queue1);
EXTMEM AudioConnection          patchCord161(ampL, 0, AudioOutput, 0);
EXTMEM AudioConnection          patchCord162(ampR, queue2);
EXTMEM AudioConnection          patchCord163(ampR, 0, AudioOutput, 1);
EXTMEM AudioConnection          patchCord164(delay1, 0, delay1pre1, 0);
EXTMEM AudioConnection          patchCord165(delay1, 1, delay1pre1, 1);
EXTMEM AudioConnection          patchCord166(delay1, 2, delay1pre1, 2);
EXTMEM AudioConnection          patchCord167(delay1, 3, delay1pre1, 3);
EXTMEM AudioConnection          patchCord168(delay1, 4, delay1pre2, 0);
EXTMEM AudioConnection          patchCord169(delay1, 5, delay1pre2, 1);
EXTMEM AudioConnection          patchCord170(delay1, 6, delay1pre2, 2);
EXTMEM AudioConnection          patchCord171(delay1, 7, delay1pre2, 3);
EXTMEM AudioConnection          patchCord172(delay2, 0, delay2pre1, 0);
EXTMEM AudioConnection          patchCord173(delay2, 1, delay2pre1, 1);
EXTMEM AudioConnection          patchCord174(delay2, 2, delay2pre1, 2);
EXTMEM AudioConnection          patchCord175(delay2, 3, delay2pre1, 3);
EXTMEM AudioConnection          patchCord176(delay2, 4, delay2pre2, 0);
EXTMEM AudioConnection          patchCord177(delay2, 5, delay2pre2, 1);
EXTMEM AudioConnection          patchCord178(delay2, 6, delay2pre2, 2);
EXTMEM AudioConnection          patchCord179(delay2, 7, delay2pre2, 3);
EXTMEM AudioConnection          patchCord180(delay3, 0, delay3pre1, 0);
EXTMEM AudioConnection          patchCord181(delay3, 1, delay3pre1, 1);
EXTMEM AudioConnection          patchCord182(delay3, 2, delay3pre1, 2);
EXTMEM AudioConnection          patchCord183(delay3, 3, delay3pre1, 3);
EXTMEM AudioConnection          patchCord184(delay3, 4, delay3pre2, 0);
EXTMEM AudioConnection          patchCord185(delay3, 5, delay3pre2, 1);
EXTMEM AudioConnection          patchCord186(delay3, 6, delay3pre2, 2);
EXTMEM AudioConnection          patchCord187(delay3, 7, delay3pre2, 3);
EXTMEM AudioConnection          patchCord188(delay1R, 0, delay1pre1R, 0);
EXTMEM AudioConnection          patchCord189(delay1R, 1, delay1pre1R, 1);
EXTMEM AudioConnection          patchCord190(delay1R, 2, delay1pre1R, 2);
EXTMEM AudioConnection          patchCord191(delay1R, 3, delay1pre1R, 3);
EXTMEM AudioConnection          patchCord192(delay1R, 4, delay1pre2R, 0);
EXTMEM AudioConnection          patchCord193(delay1R, 5, delay1pre2R, 1);
EXTMEM AudioConnection          patchCord194(delay1R, 6, delay1pre2R, 2);
EXTMEM AudioConnection          patchCord195(delay1R, 7, delay1pre2R, 3);
EXTMEM AudioConnection          patchCord196(delay2R, 0, delay2pre1R, 0);
EXTMEM AudioConnection          patchCord197(delay2R, 1, delay2pre1R, 1);
EXTMEM AudioConnection          patchCord198(delay2R, 2, delay2pre1R, 2);
EXTMEM AudioConnection          patchCord199(delay2R, 3, delay2pre1R, 3);
EXTMEM AudioConnection          patchCord200(delay2R, 4, delay2pre2R, 0);
EXTMEM AudioConnection          patchCord201(delay2R, 5, delay2pre2R, 1);
EXTMEM AudioConnection          patchCord202(delay2R, 6, delay2pre2R, 2);
EXTMEM AudioConnection          patchCord203(delay2R, 7, delay2pre2R, 3);
EXTMEM AudioConnection          patchCord204(delay3R, 0, delay3pre1R, 0);
EXTMEM AudioConnection          patchCord205(delay3R, 1, delay3pre1R, 1);
EXTMEM AudioConnection          patchCord206(delay3R, 2, delay3pre1R, 2);
EXTMEM AudioConnection          patchCord207(delay3R, 3, delay3pre1R, 3);
EXTMEM AudioConnection          patchCord208(delay3R, 4, delay3pre2R, 0);
EXTMEM AudioConnection          patchCord209(delay3R, 5, delay3pre2R, 1);
EXTMEM AudioConnection          patchCord210(delay3R, 6, delay3pre2R, 2);
EXTMEM AudioConnection          patchCord211(delay3R, 7, delay3pre2R, 3);
EXTMEM AudioConnection          patchCord212(delay1pre1, 0, delaymix1, 0);
EXTMEM AudioConnection          patchCord213(delay1pre2, 0, delaymix1, 1);
EXTMEM AudioConnection          patchCord214(delay2pre1, 0, delaymix2, 0);
EXTMEM AudioConnection          patchCord215(delay3pre1, 0, delaymix3, 0);
EXTMEM AudioConnection          patchCord216(delay2pre2, 0, delaymix2, 1);
EXTMEM AudioConnection          patchCord217(delay3pre2, 0, delaymix3, 1);
EXTMEM AudioConnection          patchCord218(delay1pre2R, 0, delaymix1R, 1);
EXTMEM AudioConnection          patchCord219(delay2pre1R, 0, delaymix2R, 0);
EXTMEM AudioConnection          patchCord220(delay3pre1R, 0, delaymix3R, 0);
EXTMEM AudioConnection          patchCord221(delay2pre2R, 0, delaymix2R, 1);
EXTMEM AudioConnection          patchCord222(delay3pre2R, 0, delaymix3R, 1);
EXTMEM AudioConnection          patchCord223(delay1pre1R, 0, delaymix1R, 0);

AudioControlSGTL5000     AudioShield;    //xy=4016,485
// GUItool: end automatically generated code


EXTMEM AudioConnection delayCord1(feedbackdelay1, delay1);
EXTMEM AudioConnection delayCord2(feedbackdelay2, delay2);
EXTMEM AudioConnection delayCord3(feedbackdelay3, delay3);


EXTMEM AudioConnection delayCord1R(feedbackdelay1R, delay1R);
EXTMEM AudioConnection delayCord2R(feedbackdelay2R, delay2R);
EXTMEM AudioConnection delayCord3R(feedbackdelay3R, delay3R);