#include <Audio.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Wire.h>

// GUItool: begin automatically generated code
EXTMEM AudioSynthWaveform       LFOrm2;         //xy=156.88333129882812,1057.9999694824219
EXTMEM AudioEffectMultiply      multiply2;      //xy=160.88333129882812,1018
EXTMEM AudioSynthWaveform       LFOrm3;         //xy=172.88333129882812,1288
EXTMEM AudioEffectMultiply      multiply3;      //xy=173.88333129882812,1248
EXTMEM AudioSynthWaveform       LFOrm1;         //xy=205.88333129882812,756.9999694824219
EXTMEM AudioEffectMultiply      multiply1;      //xy=228.88333129882812,685.9999694824219
EXTMEM AudioSynthWaveformModulated FMWaveform1L3;  //xy=507.8833312988281,914
EXTMEM AudioSynthWaveformModulated FMWaveform2L3;  //xy=508.8833312988281,948
EXTMEM AudioSynthWaveformModulated FMWaveform1L2;  //xy=509.8833312988281,776
EXTMEM AudioSynthWaveformModulated FMWaveform2L2;  //xy=510.8833312988281,810
EXTMEM AudioSynthWaveformModulated FMWaveform3L3;  //xy=510.8833312988281,980
EXTMEM AudioSynthWaveformModulated FMWaveform1L4;  //xy=510.8833312988281,1051
EXTMEM AudioSynthWaveformModulated FMWaveform1L1;  //xy=512.8833312988281,637
EXTMEM AudioSynthWaveformModulated FMWaveform2L4;  //xy=512.8833312988281,1085
EXTMEM AudioSynthWaveformModulated FMWaveform2L1;  //xy=514.8833312988281,671
EXTMEM AudioSynthWaveformModulated FMWaveform3L2;  //xy=514.8833312988281,847
EXTMEM AudioSynthWaveformModulated FMWaveform3L4;  //xy=514.8833312988281,1118
EXTMEM AudioSynthWaveformModulated FMWaveform1L5;  //xy=514.8833312988281,1201
EXTMEM AudioSynthWaveformModulated FMWaveform3L1;  //xy=516.8833312988281,703
EXTMEM AudioSynthWaveformModulated FMWaveform2L5;  //xy=516.8833312988281,1235
EXTMEM AudioSynthWaveformModulated FMWaveform3L5;  //xy=518.8833312988281,1268
EXTMEM AudioSynthWaveformModulated FMWaveform1L6;  //xy=528.8833312988281,1350
EXTMEM AudioSynthWaveformModulated FMWaveform2L6;  //xy=530.8833312988281,1384
EXTMEM AudioSynthWaveformModulated FMWaveform3L6;  //xy=532.8833312988281,1417
EXTMEM AudioEffectMultiply      modulate1L6;    //xy=704.8833312988281,1339
EXTMEM AudioEffectMultiply      modulate2L6;    //xy=704.8833312988281,1371
EXTMEM AudioEffectMultiply      modulate3L6;    //xy=706.8833312988281,1402
EXTMEM AudioEffectMultiply      modulate1L2;    //xy=718.8833312988281,799
EXTMEM AudioEffectMultiply      modulate2L2;    //xy=718.8833312988281,831
EXTMEM AudioEffectMultiply      modulate1L3;    //xy=718.8833312988281,933
EXTMEM AudioEffectMultiply      modulate2L3;    //xy=718.8833312988281,965
EXTMEM AudioEffectMultiply      modulate1L5;    //xy=718.8833312988281,1200
EXTMEM AudioEffectMultiply      modulate2L5;    //xy=718.8833312988281,1232
EXTMEM AudioEffectMultiply      modulate3L2;    //xy=720.8833312988281,862
EXTMEM AudioEffectMultiply      modulate3L3;    //xy=720.8833312988281,996
EXTMEM AudioEffectMultiply      modulate3L5;    //xy=720.8833312988281,1263
EXTMEM AudioEffectMultiply      modulate1L4;    //xy=722.8833312988281,1067
EXTMEM AudioEffectMultiply      modulate2L4;    //xy=722.8833312988281,1099
EXTMEM AudioEffectMultiply      modulate3L4;    //xy=724.8833312988281,1130
EXTMEM AudioEffectMultiply      modulate1L1;    //xy=728.8833312988281,670
EXTMEM AudioEffectMultiply      modulate2L1;    //xy=728.8833312988281,702
EXTMEM AudioEffectMultiply      modulate3L1;    //xy=730.8833312988281,733
EXTMEM AudioSynthSimpleDrum     drum3L6;        //xy=927.88330078125,1389
EXTMEM AudioSynthSimpleDrum     drum2L1;        //xy=930.8833312988281,684
EXTMEM AudioSynthSimpleDrum     drum2L6;        //xy=928.8833312988281,1354
EXTMEM AudioSynthSimpleDrum     drum2L5;        //xy=929.8833312988281,1224
EXTMEM AudioSynthSimpleDrum     drum3L1;        //xy=932.8833312988281,717
EXTMEM AudioSynthSimpleDrum     drum1L1;        //xy=933.8833312988281,654
EXTMEM AudioSynthSimpleDrum     drum3L5;        //xy=931.8833312988281,1257
EXTMEM AudioSynthSimpleDrum     drum1L6;        //xy=931.8833312988281,1324
EXTMEM AudioSynthSimpleDrum     drum1L5;        //xy=932.8833312988281,1194
EXTMEM AudioSynthSimpleDrum     drum2L3;        //xy=934.8833312988281,954
EXTMEM AudioSynthSimpleDrum     drum2L4;        //xy=935.8833312988281,1094
EXTMEM AudioSynthSimpleDrum     drum3L3;        //xy=936.8833312988281,987
EXTMEM AudioSynthSimpleDrum     drum1L3;        //xy=937.8833312988281,924
EXTMEM AudioSynthSimpleDrum     drum3L4;        //xy=937.8833312988281,1127
EXTMEM AudioSynthSimpleDrum     drum1L4;        //xy=938.8833312988281,1064
EXTMEM AudioSynthSimpleDrum     drum2L2;        //xy=939.8833312988281,827
EXTMEM AudioSynthSimpleDrum     drum3L2;        //xy=941.8833312988281,860
EXTMEM AudioSynthSimpleDrum     drum1L2;        //xy=942.8833312988281,797
EXTMEM AudioSynthKarplusStrong  string2L6;      //xy=1059.8833312988281,1346
EXTMEM AudioSynthKarplusStrong  string3L6;      //xy=1062.88330078125,1380
EXTMEM AudioSynthKarplusStrong  string3L4;      //xy=1064.8833312988281,1109
EXTMEM AudioSynthKarplusStrong  string2L4;      //xy=1065.8833312988281,1076
EXTMEM AudioSynthKarplusStrong  string1L6;      //xy=1065.8833312988281,1314
EXTMEM AudioSynthKarplusStrong  string3L3;      //xy=1069.8833312988281,976
EXTMEM AudioSynthKarplusStrong  string3L1;      //xy=1071.8833312988281,691
EXTMEM AudioSynthKarplusStrong  string2L3;      //xy=1070.8833312988281,943
EXTMEM AudioSynthKarplusStrong  string2L1;      //xy=1072.8833312988281,658
EXTMEM AudioSynthKarplusStrong  string1L2;      //xy=1072.8833312988281,764
EXTMEM AudioSynthKarplusStrong  string1L4;      //xy=1071.8833312988281,1044
EXTMEM AudioSynthKarplusStrong  string3L2;      //xy=1072.8833312988281,843
EXTMEM AudioSynthKarplusStrong  string2L2;      //xy=1073.8833312988281,810
EXTMEM AudioSynthKarplusStrong  string3L5;      //xy=1075.8833312988281,1245
EXTMEM AudioSynthKarplusStrong  string1L3;      //xy=1077.8833312988281,911
EXTMEM AudioSynthKarplusStrong  string2L5;      //xy=1076.8833312988281,1212
EXTMEM AudioSynthKarplusStrong  string1L1;      //xy=1079.8833312988281,626
EXTMEM AudioSynthKarplusStrong  string1L5;      //xy=1082.8833312988281,1180
EXTMEM AudioSynthWaveform       waveform1L5;    //xy=1260.8833312988281,1194
EXTMEM AudioSynthWaveform       waveform1L6;    //xy=1260.8833312988281,1325
EXTMEM AudioSynthWaveform       waveform2L5;    //xy=1263.8833312988281,1226
EXTMEM AudioSynthWaveform       waveform3L5;    //xy=1263.8833312988281,1255
EXTMEM AudioSynthWaveform       waveform2L6;    //xy=1263.8833312988281,1358
EXTMEM AudioSynthWaveform       waveform3L6;    //xy=1263.8833312988281,1387
EXTMEM AudioSynthWaveform       waveform1L4;    //xy=1268.8833312988281,1041
EXTMEM AudioSynthWaveform       waveform3L3;    //xy=1271.8833312988281,969
EXTMEM AudioSynthWaveform       waveform1L2;    //xy=1272.8833312988281,775
EXTMEM AudioSynthWaveform       waveform2L3;    //xy=1272.8833312988281,939
EXTMEM AudioSynthWaveform       waveform2L4;    //xy=1272.8833312988281,1074
EXTMEM AudioSynthWaveform       waveform3L4;    //xy=1272.8833312988281,1103
EXTMEM AudioSynthWaveform       waveform1L3;    //xy=1273.8833312988281,905
EXTMEM AudioSynthWaveform       waveform3L2;    //xy=1276.8833312988281,835
EXTMEM AudioSynthWaveform       waveform3L1;    //xy=1277.8833312988281,707
EXTMEM AudioSynthWaveform       waveform2L2;    //xy=1277.8833312988281,805
EXTMEM AudioSynthWaveform       waveform2L1;    //xy=1278.8833312988281,677
EXTMEM AudioSynthWaveform       waveform1L1;    //xy=1279.8833312988281,645
EXTMEM AudioMixer4              WavesL5;        //xy=1409.8833312988281,1239
EXTMEM AudioMixer4              WavesL6;        //xy=1409.8833312988281,1371
EXTMEM AudioMixer4              WavesL3;        //xy=1418.8833312988281,952
EXTMEM AudioMixer4              WavesL4;        //xy=1418.8833312988281,1087
EXTMEM AudioMixer4              WavesL2;        //xy=1423.8833312988281,818
EXTMEM AudioMixer4              WavesL1;        //xy=1447.8833312988281,695
//EXTMEM AudioSynthWaveform       LFOrm303;       //xy=1523.8833312988281,1012
EXTMEM AudioEffectEnvelope      envelopeL5;     //xy=1537.8833312988281,1389
EXTMEM AudioEffectEnvelope      envelopeL2;     //xy=1568.8833312988281,951
EXTMEM AudioEffectEnvelope      envelopeL3;     //xy=1576.8833312988281,1086
EXTMEM AudioEffectEnvelope      envelopeL4;     //xy=1581.8833312988281,1233
EXTMEM AudioEffectEnvelope      envelopeL0;     //xy=1592.8833312988281,663
EXTMEM AudioEffectEnvelope      envelopeL1;     //xy=1595.8833312988281,817
EXTMEM AudioAmplifier           fade5;          //xy=1687.5500106811523,1406.0001640319824
EXTMEM AudioAmplifier           wavePAmp5;      //xy=1702.5500106811523,1372.0001640319824
EXTMEM AudioAmplifier           fade0;          //xy=1725.8833312988281,753
EXTMEM AudioPlaySerialflashRaw  FlashSampler1;  //xy=1731.8833312988281,20
EXTMEM AudioPlaySerialflashRaw  FlashSampler2;  //xy=1731.8833312988281,60
EXTMEM AudioPlaySerialflashRaw  FlashSampler5;  //xy=1732.8833312988281,182
EXTMEM AudioPlaySerialflashRaw  FlashSampler6;  //xy=1732.8833312988281,217
EXTMEM AudioPlaySerialflashRaw  FlashSampler4;  //xy=1733.8833312988281,130
EXTMEM AudioPlaySerialflashRaw  FlashSampler9;  //xy=1733.8833312988281,339
EXTMEM AudioPlaySerialflashRaw  FlashSampler3;  //xy=1734.8833312988281,93
EXTMEM AudioPlaySerialflashRaw  FlashSampler10; //xy=1733.8833312988281,374
EXTMEM AudioPlaySerialflashRaw  FlashSampler8;  //xy=1734.8833312988281,287
EXTMEM AudioPlaySerialflashRaw  FlashSampler7;  //xy=1735.8833312988281,250
EXTMEM AudioPlaySerialflashRaw  FlashSampler12; //xy=1735.8833312988281,444
EXTMEM AudioAmplifier           wavePAmp0;      //xy=1734.8833312988281,710
EXTMEM AudioPlaySerialflashRaw  FlashSampler13; //xy=1735.8833312988281,495
EXTMEM AudioPlaySerialflashRaw  FlashSampler14; //xy=1735.8833312988281,530
EXTMEM AudioPlaySerialflashRaw  FlashSampler11; //xy=1736.8833312988281,407
EXTMEM AudioPlaySerialflashRaw  FlashSampler16; //xy=1737.8833312988281,600
EXTMEM AudioPlaySerialflashRaw  FlashSampler15; //xy=1738.8833312988281,563
EXTMEM AudioAmplifier           fade2;          //xy=1737.8833312988281,1000
EXTMEM AudioAmplifier           fade1;          //xy=1741.8833312988281,875
EXTMEM AudioAmplifier           wavePAmp1;      //xy=1744.8833312988281,836
EXTMEM AudioAmplifier           fade3;          //xy=1744.8833312988281,1115
EXTMEM AudioAmplifier           wavePAmp2;      //xy=1746.8833312988281,964
EXTMEM AudioAmplifier           wavePAmp3;      //xy=1751.8833312988281,1079
EXTMEM AudioAmplifier           fade4;          //xy=1770.8833312988281,1288
EXTMEM AudioAmplifier           wavePAmp4;      //xy=1783.8833312988281,1250
AudioFilterStateVariable filter303L6;    //xy=1851.5500106811523,1380.0001640319824
AudioFilterStateVariable filter303L1;    //xy=1880.8833312988281,716
AudioFilterStateVariable filter303L2;    //xy=1889.8833312988281,845
AudioFilterStateVariable filter303L3;    //xy=1894.8833312988281,969
AudioFilterStateVariable filter303L4;    //xy=1905.8833312988281,1093
AudioFilterStateVariable filter303L5;    //xy=1935.8833312988281,1261
EXTMEM AudioMixer4              flashmix1;      //xy=1945.8833312988281,83
EXTMEM AudioMixer4              flashmix2;      //xy=1946.8833312988281,239
EXTMEM AudioMixer4              flashmix3;      //xy=1947.8833312988281,396
EXTMEM AudioMixer4              flashmix4;      //xy=2009.8833312988281,549
EXTMEM AudioMixer4              mix303L6;       //xy=2008.8833312988281,1390
EXTMEM AudioMixer4              mix303L1;       //xy=2036.8833312988281,733
EXTMEM AudioMixer4              mix303L2;       //xy=2036.8833312988281,852
EXTMEM AudioMixer4              mix303L3;       //xy=2053.883331298828,953
EXTMEM AudioMixer4              mix303L4;       //xy=2061.883331298828,1074
EXTMEM AudioMixer4              mix303L5;       //xy=2130.883331298828,1261
EXTMEM AudioMixer4              flashmixMain;   //xy=2146.883331298828,301
EXTMEM AudioInputI2S            AudioIn1;           //xy=2149.85400390625,572.1041259765625
EXTMEM AudioInputUSB            usb1;           //xy=2151.13330078125,466.0000305175781
EXTMEM AudioMixer4              mixerWet303L6;  //xy=2164.883331298828,1382
EXTMEM AudioMixer4              mixerWet303L2;  //xy=2201.883331298828,837
EXTMEM AudioMixer4              mixerWet303L1;  //xy=2214.883331298828,697
EXTMEM AudioMixer4              mixerWet303L3;  //xy=2224.883331298828,931
EXTMEM AudioMixer4              mixerWet303L4;  //xy=2235.883331298828,1057
EXTMEM AudioMixer4              mixerWet303L5;  //xy=2300.883331298828,1238
EXTMEM AudioMixer4              InMixL;         //xy=2342.88330078125,485.0000305175781
EXTMEM AudioMixer4              InMixR;         //xy=2346.88330078125,593
EXTMEM AudioPlaySerialflashRaw  FlashRaw;       //xy=2350.8831787109375,178
EXTMEM AudioMixer4              mixerWL1to4;    //xy=2418.883331298828,923
EXTMEM AudioPlaySdRaw           playRawL;       //xy=2424.8831787109375,424
EXTMEM AudioPlaySdRaw           playRawR;       //xy=2455.8831787109375,745
EXTMEM AudioPlaySdWav           playSdWav1;     //xy=2464.88330078125,536
EXTMEM AudioMixer4              mixerWL5to8;    //xy=2469.883331298828,1396
EXTMEM AudioSynthSimpleDrum     metrodrum1;     //xy=2473.88330078125,656
EXTMEM AudioAmplifier           LineInPreAmpL;  //xy=2496.88330078125,485.0000305175781
EXTMEM AudioAmplifier           LineInPreAmpR;  //xy=2511.88330078125,592
EXTMEM AudioMixer4              flashMastermix; //xy=2603.88330078125,190
EXTMEM AudioMixer4              mixerWAll;      //xy=2605.88330078125,979
EXTMEM AudioMixer4              MasterL;        //xy=2678.8831787109375,419
EXTMEM AudioMixer4              MasterR;        //xy=2697.8831787109375,610
EXTMEM AudioSynthWaveformSine   lfosine3;       //xy=2914.883331298828,1359
EXTMEM AudioSynthWaveformSine   lfosine2;       //xy=2923.883331298828,1307
EXTMEM AudioSynthWaveformSine   lfosine1;       //xy=2927.883331298828,1240
EXTMEM AudioEffectFlange        flange1;        //xy=2932.883331298828,1037
EXTMEM AudioEffectBitcrusher    bitcrusher1;    //xy=2936.883331298828,989
EXTMEM AudioEffectChorus        chorus1;        //xy=2941.883331298828,1080
EXTMEM AudioFilterBiquad        biquad1;        //xy=2942.883331298828,1128
EXTMEM AudioEffectGranular      granular1;      //xy=2949.883331298828,923
EXTMEM AudioMixer4              MasterL1;       //xy=2955.88330078125,459
EXTMEM AudioEffectFreeverb      freeverbs1;     //xy=2954.883331298828,881
EXTMEM AudioMixer4              MasterR1;       //xy=2963.88330078125,553
EXTMEM AudioEffectGranular      granular2;      //xy=3081.883331298828,926
EXTMEM AudioEffectBitcrusher    bitcrusher2;    //xy=3081.883331298828,996
EXTMEM AudioEffectFlange        flange2;        //xy=3086.883331298828,1050
EXTMEM AudioEffectChorus        chorus2;        //xy=3090.883331298828,1094
EXTMEM AudioEffectFreeverb      freeverbs2;     //xy=3095.883331298828,872
EXTMEM AudioFilterBiquad        biquad2;        //xy=3097.883331298828,1141
EXTMEM AudioFilterStateVariable filter3;        //xy=3098.883331298828,1366
EXTMEM AudioFilterStateVariable filter1;        //xy=3100.883331298828,1223
EXTMEM AudioFilterStateVariable filter2;        //xy=3103.883331298828,1294
EXTMEM AudioMixer4              WetMixMasterL;  //xy=3212.883331298828,482
EXTMEM AudioMixer4              WetMixMasterR;  //xy=3213.883331298828,572
EXTMEM AudioEffectGranular      granular3;      //xy=3231.883331298828,934
EXTMEM AudioEffectFlange        flange3;        //xy=3231.883331298828,1048
EXTMEM AudioEffectChorus        chorus3;        //xy=3234.883331298828,1091
EXTMEM AudioFilterBiquad        biquad3;        //xy=3242.883331298828,1139
EXTMEM AudioEffectBitcrusher    bitcrusher3;    //xy=3243.883331298828,996
EXTMEM AudioEffectFreeverb      freeverbs3;     //xy=3244.883331298828,876
EXTMEM AudioMixer4              mixfilter1;     //xy=3256.883331298828,1229
EXTMEM AudioMixer4              mixfilter3;     //xy=3261.883331298828,1366
EXTMEM AudioMixer4              mixfilter2;     //xy=3263.883331298828,1297
EXTMEM AudioMixer4              premixMaster;   //xy=3327.438720703125,805.9999389648438
EXTMEM AudioMixer4              FXBusL;         //xy=3552.88330078125,377
EXTMEM AudioMixer4              FXBusR;         //xy=3567.883331298828,554
EXTMEM AudioMixer4              premixmixx2;    //xy=3616.883331298828,862
EXTMEM AudioMixer4              premixmixx3;    //xy=3622.883331298828,949
EXTMEM AudioMixer4              premixmixx1;    //xy=3628.883331298828,787
EXTMEM AudioAmplifier           ampL;           //xy=3732.883331298828,506
EXTMEM AudioAmplifier           ampR;           //xy=3732.883331298828,554
EXTMEM AudioMixer4              feedbackdelay1; //xy=3844.883331298828,772
AudioRecordQueue         queue2;         //xy=3878.883331298828,607
EXTMEM AudioMixer4              feedbackdelay2; //xy=3884.883331298828,873
EXTMEM AudioMixer4              feedbackdelay3; //xy=3888.883331298828,1026
AudioRecordQueue         queue1;         //xy=3908.883331298828,416
EXTMEM AudioOutputI2S           audioOutput;    //xy=3945.883331298828,529
EXTMEM AudioEffectDelay         delay1;         //xy=4046.883331298828,728
EXTMEM AudioEffectDelay         delay2;         //xy=4070.883331298828,877
EXTMEM AudioEffectDelay         delay3;         //xy=4072.883331298828,1014
EXTMEM AudioAnalyzeNoteFrequency notefreq1;      //xy=4113.883331298828,469
EXTMEM AudioMixer4              delay1pre2;     //xy=4211.883331298828,769
EXTMEM AudioMixer4              delay2pre1;     //xy=4211.883331298828,849
EXTMEM AudioMixer4              delay3pre1;     //xy=4212.883331298828,982
EXTMEM AudioMixer4              delay2pre2;     //xy=4213.883331298828,913
EXTMEM AudioMixer4              delay3pre2;     //xy=4213.883331298828,1052
EXTMEM AudioMixer4              delay1pre1;     //xy=4219.883331298828,674
EXTMEM AudioMixer4              delaymix3;      //xy=4362.883331298828,1020
EXTMEM AudioMixer4              delaymix2;      //xy=4367.883331298828,892
EXTMEM AudioMixer4              delaymix1;      //xy=4383.883331298828,730
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
EXTMEM AudioConnection          patchCord40(WavesL5, envelopeL4);
EXTMEM AudioConnection          patchCord41(WavesL6, envelopeL5);
EXTMEM AudioConnection          patchCord42(WavesL3, envelopeL2);
EXTMEM AudioConnection          patchCord43(WavesL4, envelopeL3);
EXTMEM AudioConnection          patchCord44(WavesL2, envelopeL1);
EXTMEM AudioConnection          patchCord45(WavesL1, envelopeL0);
/*
EXTMEM AudioConnection          patchCord46(LFOrm303, fade1);
EXTMEM AudioConnection          patchCord47(LFOrm303, fade0);
EXTMEM AudioConnection          patchCord48(LFOrm303, fade2);
EXTMEM AudioConnection          patchCord49(LFOrm303, fade3);
EXTMEM AudioConnection          patchCord50(LFOrm303, fade4);
EXTMEM AudioConnection          patchCord51(LFOrm303, fade5);
*/
EXTMEM AudioConnection          patchCord52(envelopeL5, 0, mixerWet303L6, 0);
EXTMEM AudioConnection          patchCord53(envelopeL5, wavePAmp5);
EXTMEM AudioConnection          patchCord54(envelopeL2, 0, mixerWet303L3, 0);
EXTMEM AudioConnection          patchCord55(envelopeL2, wavePAmp2);
EXTMEM AudioConnection          patchCord56(envelopeL3, 0, mixerWet303L4, 0);
EXTMEM AudioConnection          patchCord57(envelopeL3, wavePAmp3);
EXTMEM AudioConnection          patchCord58(envelopeL4, 0, mixerWet303L5, 0);
EXTMEM AudioConnection          patchCord59(envelopeL4, wavePAmp4);
EXTMEM AudioConnection          patchCord60(envelopeL0, wavePAmp0);
EXTMEM AudioConnection          patchCord61(envelopeL0, 0, mixerWet303L1, 0);
EXTMEM AudioConnection          patchCord62(envelopeL1, 0, mixerWet303L2, 0);
EXTMEM AudioConnection          patchCord63(envelopeL1, wavePAmp1);
//lfo303 should be removed
//EXTMEM AudioConnection          patchCord64(fade5, 0, filter303L6, 1);
EXTMEM AudioConnection          patchCord65(wavePAmp5, 0, filter303L6, 0);
//EXTMEM AudioConnection          patchCord66(fade0, 0, filter303L1, 1);
EXTMEM AudioConnection          patchCord67(FlashSampler1, 0, flashmix1, 0);
EXTMEM AudioConnection          patchCord68(FlashSampler2, 0, flashmix1, 1);
EXTMEM AudioConnection          patchCord69(FlashSampler5, 0, flashmix2, 0);
EXTMEM AudioConnection          patchCord70(FlashSampler6, 0, flashmix2, 1);
EXTMEM AudioConnection          patchCord71(FlashSampler4, 0, flashmix1, 3);
EXTMEM AudioConnection          patchCord72(FlashSampler9, 0, flashmix3, 0);
EXTMEM AudioConnection          patchCord73(FlashSampler3, 0, flashmix1, 2);
EXTMEM AudioConnection          patchCord74(FlashSampler10, 0, flashmix3, 1);
EXTMEM AudioConnection          patchCord75(FlashSampler8, 0, flashmix2, 3);
EXTMEM AudioConnection          patchCord76(FlashSampler7, 0, flashmix2, 2);
EXTMEM AudioConnection          patchCord77(FlashSampler12, 0, flashmix3, 3);
EXTMEM AudioConnection          patchCord78(wavePAmp0, 0, filter303L1, 0);
EXTMEM AudioConnection          patchCord79(FlashSampler13, 0, flashmix4, 0);
EXTMEM AudioConnection          patchCord80(FlashSampler14, 0, flashmix4, 1);
EXTMEM AudioConnection          patchCord81(FlashSampler11, 0, flashmix3, 2);
EXTMEM AudioConnection          patchCord82(FlashSampler16, 0, flashmix4, 3);
EXTMEM AudioConnection          patchCord83(FlashSampler15, 0, flashmix4, 2);
//EXTMEM AudioConnection          patchCord84(fade2, 0, filter303L3, 1);
//EXTMEM AudioConnection          patchCord85(fade1, 0, filter303L2, 1);
EXTMEM AudioConnection          patchCord86(wavePAmp1, 0, filter303L2, 0);
//EXTMEM AudioConnection          patchCord87(fade3, 0, filter303L4, 1);
EXTMEM AudioConnection          patchCord88(wavePAmp2, 0, filter303L3, 0);
EXTMEM AudioConnection          patchCord89(wavePAmp3, 0, filter303L4, 0);
//EXTMEM AudioConnection          patchCord90(fade4, 0, filter303L5, 1);
EXTMEM AudioConnection          patchCord91(wavePAmp4, 0, filter303L5, 0);
EXTMEM AudioConnection          patchCord92(filter303L6, 0, mix303L6, 0);
EXTMEM AudioConnection          patchCord93(filter303L6, 1, mix303L6, 1);
EXTMEM AudioConnection          patchCord94(filter303L6, 2, mix303L6, 2);
EXTMEM AudioConnection          patchCord95(filter303L1, 0, mix303L1, 0);
EXTMEM AudioConnection          patchCord96(filter303L1, 1, mix303L1, 1);
EXTMEM AudioConnection          patchCord97(filter303L1, 2, mix303L1, 2);
EXTMEM AudioConnection          patchCord98(filter303L2, 0, mix303L2, 0);
EXTMEM AudioConnection          patchCord99(filter303L2, 1, mix303L2, 1);
EXTMEM AudioConnection          patchCord100(filter303L2, 2, mix303L2, 2);
EXTMEM AudioConnection          patchCord101(filter303L3, 0, mix303L3, 0);
EXTMEM AudioConnection          patchCord102(filter303L3, 1, mix303L3, 1);
EXTMEM AudioConnection          patchCord103(filter303L3, 2, mix303L3, 2);
EXTMEM AudioConnection          patchCord104(filter303L4, 0, mix303L4, 0);
EXTMEM AudioConnection          patchCord105(filter303L4, 1, mix303L4, 1);
EXTMEM AudioConnection          patchCord106(filter303L4, 2, mix303L4, 2);
EXTMEM AudioConnection          patchCord107(filter303L5, 0, mix303L5, 0);
EXTMEM AudioConnection          patchCord108(filter303L5, 1, mix303L5, 1);
EXTMEM AudioConnection          patchCord109(filter303L5, 2, mix303L5, 2);
EXTMEM AudioConnection          patchCord110(flashmix1, 0, flashmixMain, 0);
EXTMEM AudioConnection          patchCord111(flashmix2, 0, flashmixMain, 1);
EXTMEM AudioConnection          patchCord112(flashmix3, 0, flashmixMain, 2);
EXTMEM AudioConnection          patchCord113(flashmix4, 0, flashmixMain, 3);
EXTMEM AudioConnection          patchCord114(mix303L6, 0, mixerWet303L6, 1);
EXTMEM AudioConnection          patchCord115(mix303L1, 0, mixerWet303L1, 1);
EXTMEM AudioConnection          patchCord116(mix303L2, 0, mixerWet303L2, 1);
EXTMEM AudioConnection          patchCord117(mix303L3, 0, mixerWet303L3, 1);
EXTMEM AudioConnection          patchCord118(mix303L4, 0, mixerWet303L4, 1);
EXTMEM AudioConnection          patchCord119(mix303L5, 0, mixerWet303L5, 1);
EXTMEM AudioConnection          patchCord120(flashmixMain, 0, flashMastermix, 0);
EXTMEM AudioConnection          patchCord121(AudioIn1, 0, InMixL, 1);
EXTMEM AudioConnection          patchCord122(AudioIn1, 1, InMixR, 1);
EXTMEM AudioConnection          patchCord123(usb1, 0, InMixL, 0);
EXTMEM AudioConnection          patchCord124(usb1, 1, InMixR, 0);
EXTMEM AudioConnection          patchCord125(mixerWet303L6, 0, mixerWL5to8, 1);
EXTMEM AudioConnection          patchCord126(mixerWet303L2, 0, mixerWL1to4, 1);
EXTMEM AudioConnection          patchCord127(mixerWet303L1, 0, mixerWL1to4, 0);
EXTMEM AudioConnection          patchCord128(mixerWet303L3, 0, mixerWL1to4, 2);
EXTMEM AudioConnection          patchCord129(mixerWet303L4, 0, mixerWL1to4, 3);
EXTMEM AudioConnection          patchCord130(mixerWet303L5, 0, mixerWL5to8, 0);
EXTMEM AudioConnection          patchCord131(InMixL, LineInPreAmpL);
EXTMEM AudioConnection          patchCord132(InMixR, LineInPreAmpR);
EXTMEM AudioConnection          patchCord133(FlashRaw, 0, flashMastermix, 1);
EXTMEM AudioConnection          patchCord134(mixerWL1to4, 0, mixerWAll, 0);
EXTMEM AudioConnection          patchCord135(playRawL, 0, MasterL, 3);
EXTMEM AudioConnection          patchCord136(playRawR, 0, MasterR, 3);
EXTMEM AudioConnection          patchCord137(playSdWav1, 0, MasterL, 0);
EXTMEM AudioConnection          patchCord138(playSdWav1, 1, MasterR, 0);
EXTMEM AudioConnection          patchCord139(mixerWL5to8, 0, mixerWAll, 1);
EXTMEM AudioConnection          patchCord140(metrodrum1, 0, MasterL, 1);
EXTMEM AudioConnection          patchCord141(metrodrum1, 0, MasterR, 1);
EXTMEM AudioConnection          patchCord142(LineInPreAmpL, 0, MasterL, 2);
EXTMEM AudioConnection          patchCord143(LineInPreAmpR, 0, MasterR, 2);
EXTMEM AudioConnection          patchCord144(flashMastermix, 0, MasterL1, 3);
EXTMEM AudioConnection          patchCord145(flashMastermix, 0, MasterR1, 3);
EXTMEM AudioConnection          patchCord146(flashMastermix, 0, FXBusL, 1);
EXTMEM AudioConnection          patchCord147(flashMastermix, 0, FXBusR, 1);
EXTMEM AudioConnection          patchCord148(mixerWAll, 0, FXBusR, 2);
EXTMEM AudioConnection          patchCord149(mixerWAll, 0, FXBusL, 2);
EXTMEM AudioConnection          patchCord150(mixerWAll, 0, MasterL1, 2);
EXTMEM AudioConnection          patchCord151(mixerWAll, 0, MasterR1, 2);
EXTMEM AudioConnection          patchCord152(MasterL, 0, MasterL1, 0);
EXTMEM AudioConnection          patchCord153(MasterL, 0, FXBusL, 3);
EXTMEM AudioConnection          patchCord154(MasterR, 0, MasterR1, 0);
EXTMEM AudioConnection          patchCord155(MasterR, 0, FXBusR, 3);
EXTMEM AudioConnection          patchCord156(MasterL1, 0, premixMaster, 0);
EXTMEM AudioConnection          patchCord157(MasterL1, 0, WetMixMasterL, 0);
EXTMEM AudioConnection          patchCord158(MasterR1, 0, premixMaster, 1);
EXTMEM AudioConnection          patchCord159(MasterR1, 0, WetMixMasterR, 0);
EXTMEM AudioConnection          patchCord160(filter3, 0, mixfilter3, 0);
EXTMEM AudioConnection          patchCord161(filter3, 1, mixfilter3, 1);
EXTMEM AudioConnection          patchCord162(filter3, 2, mixfilter3, 2);
EXTMEM AudioConnection          patchCord163(filter1, 0, mixfilter1, 0);
EXTMEM AudioConnection          patchCord164(filter1, 1, mixfilter1, 1);
EXTMEM AudioConnection          patchCord165(filter1, 2, mixfilter1, 2);
EXTMEM AudioConnection          patchCord166(filter2, 0, mixfilter2, 0);
EXTMEM AudioConnection          patchCord167(filter2, 1, mixfilter2, 1);
EXTMEM AudioConnection          patchCord168(filter2, 2, mixfilter2, 2);
EXTMEM AudioConnection          patchCord169(WetMixMasterL, 0, premixmixx1, 0);
EXTMEM AudioConnection          patchCord170(WetMixMasterL, 0, premixmixx2, 0);
EXTMEM AudioConnection          patchCord171(WetMixMasterL, 0, premixmixx3, 0);
EXTMEM AudioConnection          patchCord172(WetMixMasterL, 0, FXBusL, 0);
EXTMEM AudioConnection          patchCord173(WetMixMasterR, 0, premixmixx1, 1);
EXTMEM AudioConnection          patchCord174(WetMixMasterR, 0, premixmixx2, 1);
EXTMEM AudioConnection          patchCord175(WetMixMasterR, 0, premixmixx3, 1);
EXTMEM AudioConnection          patchCord176(WetMixMasterR, 0, FXBusR, 0);
EXTMEM AudioConnection          patchCord177(FXBusL, ampL);
EXTMEM AudioConnection          patchCord178(FXBusR, ampR);
EXTMEM AudioConnection          patchCord179(premixmixx2, 0, feedbackdelay2, 1);
EXTMEM AudioConnection          patchCord180(premixmixx3, 0, feedbackdelay3, 1);
EXTMEM AudioConnection          patchCord181(premixmixx1, 0, feedbackdelay1, 1);
EXTMEM AudioConnection          patchCord182(ampL, queue1);
EXTMEM AudioConnection          patchCord183(ampL, 0, audioOutput, 0);
EXTMEM AudioConnection          patchCord184(ampR, queue2);
EXTMEM AudioConnection          patchCord185(ampR, 0, audioOutput, 1);
EXTMEM AudioConnection          patchCord186(delay1, 0, delay1pre1, 0);
EXTMEM AudioConnection          patchCord187(delay1, 1, delay1pre1, 1);
EXTMEM AudioConnection          patchCord188(delay1, 2, delay1pre1, 2);
EXTMEM AudioConnection          patchCord189(delay1, 3, delay1pre1, 3);
EXTMEM AudioConnection          patchCord190(delay1, 4, delay1pre2, 0);
EXTMEM AudioConnection          patchCord191(delay1, 5, delay1pre2, 1);
EXTMEM AudioConnection          patchCord192(delay1, 6, delay1pre2, 2);
EXTMEM AudioConnection          patchCord193(delay1, 7, delay1pre2, 3);
EXTMEM AudioConnection          patchCord194(delay2, 0, delay2pre1, 0);
EXTMEM AudioConnection          patchCord195(delay2, 1, delay2pre1, 1);
EXTMEM AudioConnection          patchCord196(delay2, 2, delay2pre1, 2);
EXTMEM AudioConnection          patchCord197(delay2, 3, delay2pre1, 3);
EXTMEM AudioConnection          patchCord198(delay2, 4, delay2pre2, 0);
EXTMEM AudioConnection          patchCord199(delay2, 5, delay2pre2, 1);
EXTMEM AudioConnection          patchCord200(delay2, 6, delay2pre2, 2);
EXTMEM AudioConnection          patchCord201(delay2, 7, delay2pre2, 3);
EXTMEM AudioConnection          patchCord202(delay3, 0, delay3pre1, 0);
EXTMEM AudioConnection          patchCord203(delay3, 1, delay3pre1, 1);
EXTMEM AudioConnection          patchCord204(delay3, 2, delay3pre1, 2);
EXTMEM AudioConnection          patchCord205(delay3, 3, delay3pre1, 3);
EXTMEM AudioConnection          patchCord206(delay3, 4, delay3pre2, 0);
EXTMEM AudioConnection          patchCord207(delay3, 5, delay3pre2, 1);
EXTMEM AudioConnection          patchCord208(delay3, 6, delay3pre2, 2);
EXTMEM AudioConnection          patchCord209(delay3, 7, delay3pre2, 3);
EXTMEM AudioConnection          patchCord210(delay1pre2, 0, delaymix1, 1);
EXTMEM AudioConnection          patchCord211(delay2pre1, 0, delaymix2, 0);
EXTMEM AudioConnection          patchCord212(delay3pre1, 0, delaymix3, 0);
EXTMEM AudioConnection          patchCord213(delay2pre2, 0, delaymix2, 1);
EXTMEM AudioConnection          patchCord214(delay3pre2, 0, delaymix3, 1);
EXTMEM AudioConnection          patchCord215(delay1pre1, 0, delaymix1, 0);
AudioControlSGTL5000     audioShield;    //xy=4115.88330078125,533.9999694824219
// GUItool: end automatically generated code

