#include <Audio.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Wire.h>

class MyAudioMixer4 : public AudioMixer4 {
public:
    MyAudioMixer4(void) : AudioMixer4() {
        for (int i = 0; i < 4; i++) {
            ch_gain[i] = 1.0f;  // Initialize with default gain values
        }
    }

    void gain(unsigned int channel, float gain) {
        if (channel >= 4) return;
        if (gain > 32767.0f) gain = 32767.0f;
        else if (gain < -32767.0f) gain = -32767.0f;
        AudioMixer4::gain(channel, gain); // Call the base class method
        ch_gain[channel] = gain;  // Store the gain value
    }

    float getGain(unsigned int channel) const {
        if (channel >= 4) return -1.0f; // Invalid channel
        return ch_gain[channel];
    }

private:
    float ch_gain[4];  // Array to store the gain values
};



// GUItool: begin automatically generated code
EXTMEM AudioEffectMultiply multiply3;             // xy=84.88333129882812,1127
EXTMEM AudioEffectMultiply multiply2;             // xy=86.88333129882812,1085
EXTMEM AudioEffectMultiply multiply1;             // xy=88.88333129882812,1042
EXTMEM AudioSynthWaveform LFOrm3;                 // xy=242.88333129882812,1063

EXTMEM AudioSynthWaveform LFOrm1;                 // xy=250.88333129882812,752
EXTMEM AudioSynthWaveform LFOrm2;                 // xy=250.88333129882812,869
EXTMEM AudioSynthWaveformModulated FMWaveform1L3; // xy=507.8833312988281,914
EXTMEM AudioSynthWaveformModulated FMWaveform2L3; // xy=508.8833312988281,948
EXTMEM AudioSynthWaveformModulated FMWaveform1L2; // xy=509.8833312988281,776
EXTMEM AudioSynthWaveformModulated FMWaveform2L2; // xy=510.8833312988281,810
EXTMEM AudioSynthWaveformModulated FMWaveform3L3; // xy=510.8833312988281,980
EXTMEM AudioSynthWaveformModulated FMWaveform1L4; // xy=510.8833312988281,1051
EXTMEM AudioSynthWaveformModulated FMWaveform1L1; // xy=512.8833312988281,637
EXTMEM AudioSynthWaveformModulated FMWaveform2L4; // xy=512.8833312988281,1085
EXTMEM AudioSynthWaveformModulated FMWaveform2L1; // xy=514.8833312988281,671
EXTMEM AudioSynthWaveformModulated FMWaveform3L2; // xy=514.8833312988281,847
EXTMEM AudioSynthWaveformModulated FMWaveform3L4; // xy=514.8833312988281,1118
EXTMEM AudioSynthWaveformModulated FMWaveform1L5; // xy=514.8833312988281,1201
EXTMEM AudioSynthWaveformModulated FMWaveform3L1; // xy=516.8833312988281,703
EXTMEM AudioSynthWaveformModulated FMWaveform2L5; // xy=516.8833312988281,1235
EXTMEM AudioSynthWaveformModulated FMWaveform3L5; // xy=518.8833312988281,1268

EXTMEM AudioSynthWaveformModulated FMWaveform1L6; // xy=528.8833312988281,1350
EXTMEM AudioSynthWaveformModulated FMWaveform2L6; // xy=530.8833312988281,1384
EXTMEM AudioSynthWaveformModulated FMWaveform3L6; // xy=532.8833312988281,1417

EXTMEM AudioEffectMultiply modulate1L6;           // xy=704.8833312988281,1339
EXTMEM AudioEffectMultiply modulate2L6;           // xy=704.8833312988281,1371
EXTMEM AudioEffectMultiply modulate3L6;           // xy=706.8833312988281,1402

EXTMEM AudioEffectMultiply modulate1L2;           // xy=718.8833312988281,799
EXTMEM AudioEffectMultiply modulate2L2;           // xy=718.8833312988281,831
EXTMEM AudioEffectMultiply modulate1L3;           // xy=718.8833312988281,933
EXTMEM AudioEffectMultiply modulate2L3;           // xy=718.8833312988281,965
EXTMEM AudioEffectMultiply modulate1L5;           // xy=718.8833312988281,1200
EXTMEM AudioEffectMultiply modulate2L5;           // xy=718.8833312988281,1232
EXTMEM AudioEffectMultiply modulate3L2;           // xy=720.8833312988281,862
EXTMEM AudioEffectMultiply modulate3L3;           // xy=720.8833312988281,996
EXTMEM AudioEffectMultiply modulate3L5;           // xy=720.8833312988281,1263
EXTMEM AudioEffectMultiply modulate1L4;           // xy=722.8833312988281,1067
EXTMEM AudioEffectMultiply modulate2L4;           // xy=722.8833312988281,1099

EXTMEM AudioEffectMultiply modulate3L4;           // xy=724.8833312988281,1130
EXTMEM AudioEffectMultiply modulate1L1;           // xy=728.8833312988281,670
EXTMEM AudioEffectMultiply modulate2L1;           // xy=728.8833312988281,702
EXTMEM AudioEffectMultiply modulate3L1;           // xy=730.8833312988281,733
EXTMEM AudioSynthSimpleDrum drum2L1;              // xy=930.8833312988281,684
EXTMEM AudioSynthSimpleDrum drum2L6;              // xy=928.8833312988281,1354
EXTMEM AudioSynthSimpleDrum drum2L5;              // xy=929.8833312988281,1224
EXTMEM AudioSynthSimpleDrum drum3L1;              // xy=932.8833312988281,717
EXTMEM AudioSynthSimpleDrum drum1L1;              // xy=933.8833312988281,654
EXTMEM AudioSynthSimpleDrum drum3L5;              // xy=931.8833312988281,1257
EXTMEM AudioSynthSimpleDrum drum1L6;              // xy=931.8833312988281,1324
EXTMEM AudioSynthSimpleDrum drum1L5;              // xy=932.8833312988281,1194
EXTMEM AudioSynthSimpleDrum drum2L3;              // xy=934.8833312988281,954
EXTMEM AudioSynthSimpleDrum drum2L4;              // xy=935.8833312988281,1094
EXTMEM AudioSynthSimpleDrum drum3L3;              // xy=936.8833312988281,987

EXTMEM AudioSynthSimpleDrum drum1L3;              // xy=937.8833312988281,924
EXTMEM AudioSynthSimpleDrum drum3L4;              // xy=937.8833312988281,1127
EXTMEM AudioSynthSimpleDrum drum1L4;              // xy=938.8833312988281,1064
EXTMEM AudioSynthSimpleDrum drum2L2;              // xy=939.8833312988281,827

EXTMEM AudioSynthSimpleDrum drum3L2;              // xy=941.8833312988281,860
EXTMEM AudioSynthSimpleDrum drum1L2;              // xy=942.8833312988281,797
EXTMEM AudioSynthSimpleDrum drum3L6;              // xy=940.8833312988281,1400
EXTMEM AudioSynthKarplusStrong string2L6;         // xy=1059.8833312988281,1346
EXTMEM AudioSynthKarplusStrong string3L4;         // xy=1064.8833312988281,1109
EXTMEM AudioSynthKarplusStrong string2L4;         // xy=1065.8833312988281,1076

EXTMEM AudioSynthKarplusStrong string1L6;         // xy=1065.8833312988281,1314

EXTMEM AudioSynthKarplusStrong string3L3;         // xy=1069.8833312988281,976
EXTMEM AudioSynthKarplusStrong string3L6;         // xy=1068.8833312988281,1392
EXTMEM AudioSynthKarplusStrong string3L1;         // xy=1071.8833312988281,691
EXTMEM AudioSynthKarplusStrong string2L3;         // xy=1070.8833312988281,943

EXTMEM AudioSynthKarplusStrong string2L1;         // xy=1072.8833312988281,658


EXTMEM AudioSynthKarplusStrong string1L2;         // xy=1072.8833312988281,764
EXTMEM AudioSynthKarplusStrong string1L4;         // xy=1071.8833312988281,1044
EXTMEM AudioSynthKarplusStrong string3L2;         // xy=1072.8833312988281,843
EXTMEM AudioSynthKarplusStrong string2L2;         // xy=1073.8833312988281,810

EXTMEM AudioSynthKarplusStrong string3L5;         // xy=1075.8833312988281,1245
EXTMEM AudioSynthKarplusStrong string1L3;         // xy=1077.8833312988281,911
EXTMEM AudioSynthKarplusStrong string2L5;         // xy=1076.8833312988281,1212
//TODO: check cablages lfo
EXTMEM AudioSynthKarplusStrong string1L1;         // xy=1079.8833312988281,626
EXTMEM AudioSynthKarplusStrong string1L5;         // xy=1082.8833312988281,1180

EXTMEM AudioSynthWaveform waveform1L5;            // xy=1260.8833312988281,1194
EXTMEM AudioSynthWaveform waveform1L6;            // xy=1260.8833312988281,1325

EXTMEM AudioSynthWaveform waveform2L5;            // xy=1263.8833312988281,1226
EXTMEM AudioSynthWaveform waveform3L5;            // xy=1263.8833312988281,1255
EXTMEM AudioSynthWaveform waveform2L6;            // xy=1263.8833312988281,1358
EXTMEM AudioSynthWaveform waveform3L6;            // xy=1263.8833312988281,1387
EXTMEM AudioSynthWaveform waveform1L4;            // xy=1268.8833312988281,1041
EXTMEM AudioSynthWaveform waveform3L3;            // xy=1271.8833312988281,969
EXTMEM AudioSynthWaveform waveform1L2;            // xy=1272.8833312988281,775

EXTMEM AudioSynthWaveform waveform2L3;            // xy=1272.8833312988281,939
EXTMEM AudioSynthWaveform waveform2L4;            // xy=1272.8833312988281,1074
EXTMEM AudioSynthWaveform waveform3L4;            // xy=1272.8833312988281,1103
EXTMEM AudioSynthWaveform waveform1L3;            // xy=1273.8833312988281,905
EXTMEM AudioSynthWaveform waveform3L2;            // xy=1276.8833312988281,835
EXTMEM AudioSynthWaveform waveform3L1;            // xy=1277.8833312988281,707
EXTMEM AudioSynthWaveform waveform2L2;            // xy=1277.8833312988281,805

EXTMEM AudioSynthWaveform waveform2L1;            // xy=1278.8833312988281,677
EXTMEM AudioSynthWaveform waveform1L1;            // xy=1279.8833312988281,645

EXTMEM MyAudioMixer4 WavesL5;                       // xy=1409.8833312988281,1239
EXTMEM MyAudioMixer4 WavesL6;                       // xy=1409.8833312988281,1371
EXTMEM MyAudioMixer4 WavesL3;                       // xy=1418.8833312988281,952
EXTMEM MyAudioMixer4 WavesL4;                       // xy=1418.8833312988281,1087
EXTMEM MyAudioMixer4 WavesL2;                       // xy=1423.8833312988281,818
EXTMEM MyAudioMixer4 WavesL1;                       // xy=1447.8833312988281,695
EXTMEM AudioSynthWaveform LFOrm303;               // xy=1523.8833312988281,1012
EXTMEM AudioEffectEnvelope envelopeL5;            // xy=1537.8833312988281,1389
EXTMEM AudioEffectEnvelope envelopeL2;            // xy=1568.8833312988281,951
EXTMEM AudioEffectEnvelope envelopeL3;            // xy=1576.8833312988281,1086
EXTMEM AudioEffectEnvelope envelopeL4;            // xy=1581.8833312988281,1233
EXTMEM AudioEffectEnvelope envelopeL0;            // xy=1592.8833312988281,663
EXTMEM AudioEffectEnvelope envelopeL1;            // xy=1595.8833312988281,817
EXTMEM AudioAmplifier fade5;                      // xy=1710.8833312988281,1446
EXTMEM AudioAmplifier fade6;                      // xy=1715.8833312988281,1552
EXTMEM AudioAmplifier fade0;                      // xy=1725.8833312988281,753
EXTMEM AudioAmplifier wavePAmp5;                  // xy=1725.8833312988281,1412
EXTMEM AudioAmplifier wavePAmp6;                  // xy=1725.8833312988281,1514
EXTMEM AudioPlaySerialflashRaw FlashSampler1;     // xy=1731.8833312988281,20
EXTMEM AudioPlaySerialflashRaw FlashSampler2;     // xy=1731.8833312988281,60
EXTMEM AudioPlaySerialflashRaw FlashSampler5;     // xy=1732.8833312988281,182
EXTMEM AudioPlaySerialflashRaw FlashSampler6;     // xy=1732.8833312988281,217
EXTMEM AudioPlaySerialflashRaw FlashSampler4;     // xy=1733.8833312988281,130
EXTMEM AudioPlaySerialflashRaw FlashSampler9;     // xy=1733.8833312988281,339
EXTMEM AudioPlaySerialflashRaw FlashSampler3;     // xy=1734.8833312988281,93
EXTMEM AudioPlaySerialflashRaw FlashSampler10;    // xy=1733.8833312988281,374
EXTMEM AudioPlaySerialflashRaw FlashSampler8;     // xy=1734.8833312988281,287
EXTMEM AudioAmplifier wavePAmp7;                  // xy=1729.8833312988281,1641
EXTMEM AudioPlaySerialflashRaw FlashSampler7;     // xy=1735.8833312988281,250
EXTMEM AudioPlaySerialflashRaw FlashSampler12;    // xy=1735.8833312988281,444
EXTMEM AudioAmplifier wavePAmp0;                  // xy=1734.8833312988281,710
EXTMEM AudioPlaySerialflashRaw FlashSampler13;    // xy=1735.8833312988281,495
EXTMEM AudioPlaySerialflashRaw FlashSampler14;    // xy=1735.8833312988281,530
EXTMEM AudioPlaySerialflashRaw FlashSampler11;    // xy=1736.8833312988281,407
EXTMEM AudioPlaySerialflashRaw FlashSampler16;    // xy=1737.8833312988281,600
EXTMEM AudioPlaySerialflashRaw FlashSampler15;    // xy=1738.8833312988281,563
EXTMEM AudioAmplifier fade7;                      // xy=1734.8833312988281,1676
EXTMEM AudioAmplifier fade2;                      // xy=1737.8833312988281,1000
EXTMEM AudioAmplifier fade1;                      // xy=1741.8833312988281,875
EXTMEM AudioAmplifier wavePAmp1;                  // xy=1744.8833312988281,836
EXTMEM AudioAmplifier fade3;                      // xy=1744.8833312988281,1115
EXTMEM AudioAmplifier wavePAmp2;                  // xy=1746.8833312988281,964
EXTMEM AudioAmplifier wavePAmp3;                  // xy=1751.8833312988281,1079
EXTMEM AudioAmplifier fade4;                      // xy=1770.8833312988281,1288
EXTMEM AudioAmplifier wavePAmp4;                  // xy=1783.8833312988281,1250

EXTMEM AudioFilterStateVariable filter303L6;      // xy=1874.8833312988281,1420
EXTMEM AudioFilterStateVariable filter303L1;      // xy=1880.8833312988281,716

EXTMEM AudioFilterStateVariable filter303L2;      // xy=1889.8833312988281,845
EXTMEM AudioFilterStateVariable filter303L3;      // xy=1894.8833312988281,969
EXTMEM AudioFilterStateVariable filter303L4;      // xy=1905.8833312988281,1093
EXTMEM AudioFilterStateVariable filter303L5;      // xy=1935.8833312988281,1261
EXTMEM MyAudioMixer4 flashmix1;                     // xy=1945.8833312988281,83
EXTMEM MyAudioMixer4 flashmix2;                     // xy=1946.8833312988281,239
EXTMEM MyAudioMixer4 flashmix3;                     // xy=1947.8833312988281,396
EXTMEM MyAudioMixer4 flashmix4;                     // xy=2009.8833312988281,549
EXTMEM MyAudioMixer4 mix303L6;                      // xy=2008.8833312988281,1390
EXTMEM AudioInputUSB usb1;                        // xy=2012.13330078125,620

EXTMEM MyAudioMixer4 mix303L1;                      // xy=2036.8833312988281,733
EXTMEM MyAudioMixer4 mix303L2;                      // xy=2036.8833312988281,852

EXTMEM MyAudioMixer4 mix303L3;                      // xy=2053.883331298828,953
EXTMEM MyAudioMixer4 mix303L4;                      // xy=2061.883331298828,1074
EXTMEM MyAudioMixer4 mix303L5;                      // xy=2130.883331298828,1261
EXTMEM MyAudioMixer4 flashmixMain;                  // xy=2146.883331298828,301
EXTMEM MyAudioMixer4 mixerWet303L6;                 // xy=2164.883331298828,1382
EXTMEM MyAudioMixer4 mixerWet303L2;                 // xy=2201.883331298828,837
EXTMEM MyAudioMixer4 mixerWet303L1;                 // xy=2214.883331298828,697
EXTMEM MyAudioMixer4 mixerWet303L3;                 // xy=2224.883331298828,931
EXTMEM MyAudioMixer4 mixerWet303L4;                 // xy=2235.883331298828,1057
EXTMEM MyAudioMixer4 InMixL;                        // xy=2278.883331298828,461
EXTMEM MyAudioMixer4 InMixR;                        // xy=2278.883331298828,588
EXTMEM MyAudioMixer4 mixerWet303L5;                 // xy=2300.883331298828,1238
EXTMEM AudioInputI2S AudioIn1;       // xy=2304.8541259765625,371.1041564941406
EXTMEM MyAudioMixer4 mixerWL1to4;      // xy=2418.883331298828,923
EXTMEM AudioAmplifier LineInPreAmpR; // xy=2445.883331298828,589
EXTMEM AudioPlaySdWav playSdWav1;    // xy=2447.883331298828,542
EXTMEM AudioAmplifier LineInPreAmpL; // xy=2462.883331298828,485
EXTMEM MyAudioMixer4 mixerWL5to8;      // xy=2469.883331298828,1396
EXTMEM MyAudioMixer4 mixerWAll;        // xy=2605.883331298828,979
EXTMEM AudioSynthSimpleDrum metrodrum1;     // xy=2647.883331298828,431
EXTMEM MyAudioMixer4 MasterL;                 // xy=2658.883331298828,514
EXTMEM MyAudioMixer4 MasterR;                 // xy=2689.883331298828,587
EXTMEM AudioPlaySdRaw playRawL;             // xy=2701.883331298828,276
EXTMEM AudioPlaySdRaw playRawR;             // xy=2701.883331298828,352
EXTMEM AudioPlaySerialflashRaw FlashRaw;    // xy=2753.883331298828,207
EXTMEM AudioSynthWaveformSine lfosine3;     // xy=2914.883331298828,1359
EXTMEM MyAudioMixer4 MasterR1;                // xy=2921.883331298828,551
EXTMEM MyAudioMixer4 MasterL1;                // xy=2926.883331298828,455
EXTMEM AudioSynthWaveformSine lfosine2;     // xy=2923.883331298828,1307
EXTMEM AudioSynthWaveformSine lfosine1;     // xy=2927.883331298828,1240
EXTMEM AudioEffectFlange flange1;           // xy=2932.883331298828,1037
EXTMEM AudioEffectBitcrusher bitcrusher1;   // xy=2936.883331298828,989
EXTMEM AudioEffectChorus chorus1;           // xy=2941.883331298828,1080
EXTMEM AudioFilterBiquad biquad1;           // xy=2942.883331298828,1128
EXTMEM AudioEffectGranular granular1;       // xy=2949.883331298828,923
EXTMEM AudioEffectFreeverb freeverbs1;      // xy=2954.883331298828,881
EXTMEM MyAudioMixer4 flashMastermix;          // xy=2970.883331298828,153
EXTMEM AudioEffectGranular granular2;       // xy=3081.883331298828,926
EXTMEM AudioEffectBitcrusher bitcrusher2;   // xy=3081.883331298828,996
EXTMEM AudioEffectFlange flange2;           // xy=3086.883331298828,1050
EXTMEM AudioEffectChorus chorus2;           // xy=3090.883331298828,1094
EXTMEM MyAudioMixer4 premixMaster;            // xy=3093.883331298828,793
EXTMEM AudioEffectFreeverb freeverbs2;      // xy=3095.883331298828,872
EXTMEM AudioFilterBiquad biquad2;           // xy=3097.883331298828,1141
EXTMEM AudioFilterStateVariable filter3;    // xy=3098.883331298828,1366
EXTMEM AudioFilterStateVariable filter1;    // xy=3100.883331298828,1223
EXTMEM AudioFilterStateVariable filter2;    // xy=3103.883331298828,1294
EXTMEM MyAudioMixer4 WetMixMasterL;           // xy=3212.883331298828,482
EXTMEM MyAudioMixer4 WetMixMasterR;           // xy=3213.883331298828,572
EXTMEM AudioEffectGranular granular3;       // xy=3231.883331298828,934
EXTMEM AudioEffectFlange flange3;           // xy=3231.883331298828,1048
EXTMEM AudioEffectChorus chorus3;           // xy=3234.883331298828,1091
EXTMEM AudioFilterBiquad biquad3;           // xy=3242.883331298828,1139
EXTMEM AudioEffectBitcrusher bitcrusher3;   // xy=3243.883331298828,996
EXTMEM AudioEffectFreeverb freeverbs3;      // xy=3244.883331298828,876
EXTMEM MyAudioMixer4 mixfilter1;              // xy=3256.883331298828,1229
EXTMEM MyAudioMixer4 mixfilter3;              // xy=3261.883331298828,1366
EXTMEM MyAudioMixer4 mixfilter2;              // xy=3263.883331298828,1297
EXTMEM MyAudioMixer4 FXBusL;                  // xy=3557.883331298828,438
EXTMEM MyAudioMixer4 FXBusR;                  // xy=3567.883331298828,554
EXTMEM MyAudioMixer4 premixmixx2;             // xy=3616.883331298828,862
EXTMEM MyAudioMixer4 premixmixx3;             // xy=3622.883331298828,949
EXTMEM MyAudioMixer4 premixmixx1;             // xy=3628.883331298828,787
EXTMEM AudioAmplifier ampL;                 // xy=3732.883331298828,506
EXTMEM AudioAmplifier ampR;                 // xy=3732.883331298828,554
EXTMEM MyAudioMixer4 feedbackdelay1;          // xy=3844.883331298828,772
EXTMEM AudioRecordQueue queue2;             // xy=3878.883331298828,607
EXTMEM MyAudioMixer4 feedbackdelay2;          // xy=3884.883331298828,873
EXTMEM MyAudioMixer4 feedbackdelay3;          // xy=3888.883331298828,1026
EXTMEM AudioRecordQueue queue1;             // xy=3908.883331298828,416
EXTMEM AudioOutputI2S audioOutput;          // xy=3945.883331298828,529
EXTMEM AudioEffectDelay delay1;             // xy=4046.883331298828,728
EXTMEM AudioEffectDelay delay2;             // xy=4070.883331298828,877
EXTMEM AudioEffectDelay delay3;             // xy=4072.883331298828,1014
EXTMEM AudioAnalyzeNoteFrequency notefreq1; // xy=4113.883331298828,469
EXTMEM MyAudioMixer4 delay1pre2;              // xy=4211.883331298828,769
EXTMEM MyAudioMixer4 delay2pre1;              // xy=4211.883331298828,849
EXTMEM MyAudioMixer4 delay3pre1;              // xy=4212.883331298828,982
EXTMEM MyAudioMixer4 delay2pre2;              // xy=4213.883331298828,913
EXTMEM MyAudioMixer4 delay3pre2;              // xy=4213.883331298828,1052
EXTMEM MyAudioMixer4 delay1pre1;              // xy=4219.883331298828,674
EXTMEM MyAudioMixer4 delaymix3;               // xy=4362.883331298828,1020
EXTMEM MyAudioMixer4 delaymix2;               // xy=4367.883331298828,892
EXTMEM MyAudioMixer4 delaymix1;               // xy=4383.883331298828,730
EXTMEM AudioConnection patchCord1(LFOrm3, 0, FMWaveform3L3, 0);
EXTMEM AudioConnection patchCord2(LFOrm3, 0, FMWaveform3L1, 0);
EXTMEM AudioConnection patchCord3(LFOrm3, 0, FMWaveform3L2, 0);
EXTMEM AudioConnection patchCord4(LFOrm3, 0, FMWaveform3L4, 0);
EXTMEM AudioConnection patchCord5(LFOrm3, 0, FMWaveform3L5, 0);
EXTMEM AudioConnection patchCord6(LFOrm3, 0, FMWaveform3L6, 0);
EXTMEM AudioConnection patchCord9(LFOrm3, 0, modulate3L1, 1);
EXTMEM AudioConnection patchCord10(LFOrm3, 0, modulate3L2, 1);
EXTMEM AudioConnection patchCord11(LFOrm3, 0, modulate3L3, 1);
EXTMEM AudioConnection patchCord12(LFOrm3, 0, modulate3L5, 1);
EXTMEM AudioConnection patchCord13(LFOrm3, 0, modulate3L4, 1);
EXTMEM AudioConnection patchCord14(LFOrm3, 0, modulate3L6, 1);
EXTMEM AudioConnection patchCord17(LFOrm3, 0, multiply3, 1);

EXTMEM AudioConnection patchCord34(LFOrm1, 0, FMWaveform1L1, 0);
EXTMEM AudioConnection patchCord35(LFOrm1, 0, FMWaveform1L2, 0);
EXTMEM AudioConnection patchCord36(LFOrm1, 0, FMWaveform1L3, 0);
EXTMEM AudioConnection patchCord37(LFOrm1, 0, FMWaveform1L4, 0);
EXTMEM AudioConnection patchCord38(LFOrm1, 0, FMWaveform1L5, 0);
EXTMEM AudioConnection patchCord39(LFOrm1, 0, FMWaveform1L6, 0);

EXTMEM AudioConnection patchCord42(LFOrm1, 0, modulate1L1, 1);
EXTMEM AudioConnection patchCord43(LFOrm1, 0, modulate1L2, 1);
EXTMEM AudioConnection patchCord44(LFOrm1, 0, modulate1L3, 1);
EXTMEM AudioConnection patchCord45(LFOrm1, 0, modulate1L4, 1);
EXTMEM AudioConnection patchCord46(LFOrm1, 0, modulate1L5, 1);
EXTMEM AudioConnection patchCord47(LFOrm1, 0, modulate1L6, 1);

EXTMEM AudioConnection patchCord50(LFOrm1, 0, multiply1, 1);
EXTMEM AudioConnection patchCord51(LFOrm2, 0, FMWaveform2L2, 0);
EXTMEM AudioConnection patchCord52(LFOrm2, 0, FMWaveform2L1, 0);
EXTMEM AudioConnection patchCord53(LFOrm2, 0, FMWaveform2L3, 0);
EXTMEM AudioConnection patchCord54(LFOrm2, 0, FMWaveform2L4, 0);
EXTMEM AudioConnection patchCord55(LFOrm2, 0, FMWaveform2L5, 0);
EXTMEM AudioConnection patchCord56(LFOrm2, 0, FMWaveform2L6, 0);

EXTMEM AudioConnection patchCord60(LFOrm2, 0, modulate2L5, 1);
EXTMEM AudioConnection patchCord61(LFOrm2, 0, modulate2L3, 1);
EXTMEM AudioConnection patchCord62(LFOrm2, 0, modulate2L6, 1);
EXTMEM AudioConnection patchCord63(LFOrm2, 0, modulate2L1, 1);
EXTMEM AudioConnection patchCord64(LFOrm2, 0, modulate2L2, 1);
EXTMEM AudioConnection patchCord65(LFOrm2, 0, modulate2L4, 1);
EXTMEM AudioConnection patchCord67(LFOrm2, 0, multiply2, 1);

EXTMEM AudioConnection patchCord70(WavesL5, envelopeL4);
EXTMEM AudioConnection patchCord71(WavesL6, envelopeL5);
EXTMEM AudioConnection patchCord72(WavesL3, envelopeL2);
EXTMEM AudioConnection patchCord73(WavesL4, envelopeL3);
EXTMEM AudioConnection patchCord74(WavesL2, envelopeL1);
EXTMEM AudioConnection patchCord75(WavesL1, envelopeL0);
EXTMEM AudioConnection patchCord76(LFOrm303, fade1);
EXTMEM AudioConnection patchCord77(LFOrm303, fade0);
EXTMEM AudioConnection patchCord78(LFOrm303, fade2);
EXTMEM AudioConnection patchCord79(LFOrm303, fade3);
EXTMEM AudioConnection patchCord80(LFOrm303, fade4);
EXTMEM AudioConnection patchCord81(LFOrm303, fade5);

EXTMEM AudioConnection patchCord84(envelopeL5, 0, mixerWet303L6, 0);
EXTMEM AudioConnection patchCord85(envelopeL5, wavePAmp5);
EXTMEM AudioConnection patchCord86(envelopeL2, 0, mixerWet303L3, 0);
EXTMEM AudioConnection patchCord87(envelopeL2, wavePAmp2);

EXTMEM AudioConnection patchCord92(envelopeL3, 0, mixerWet303L4, 0);
EXTMEM AudioConnection patchCord93(envelopeL3, wavePAmp3);
EXTMEM AudioConnection patchCord94(envelopeL4, 0, mixerWet303L5, 0);
EXTMEM AudioConnection patchCord95(envelopeL4, wavePAmp4);
EXTMEM AudioConnection patchCord96(envelopeL0, wavePAmp0);
EXTMEM AudioConnection patchCord97(envelopeL0, 0, mixerWet303L1, 0);
EXTMEM AudioConnection patchCord98(envelopeL1, 0, mixerWet303L2, 0);
EXTMEM AudioConnection patchCord99(envelopeL1, wavePAmp1);
EXTMEM AudioConnection patchCord100(fade5, 0, filter303L6, 1);

EXTMEM AudioConnection patchCord102(fade0, 0, filter303L1, 1);
EXTMEM AudioConnection patchCord103(wavePAmp5, 0, filter303L6, 0);

EXTMEM AudioConnection patchCord105(FlashSampler1, 0, flashmix1, 0);
EXTMEM AudioConnection patchCord106(FlashSampler2, 0, flashmix1, 1);
EXTMEM AudioConnection patchCord107(FlashSampler5, 0, flashmix2, 0);
EXTMEM AudioConnection patchCord108(FlashSampler6, 0, flashmix2, 1);
EXTMEM AudioConnection patchCord109(FlashSampler4, 0, flashmix1, 3);
EXTMEM AudioConnection patchCord110(FlashSampler9, 0, flashmix3, 0);
EXTMEM AudioConnection patchCord111(FlashSampler3, 0, flashmix1, 2);
EXTMEM AudioConnection patchCord112(FlashSampler10, 0, flashmix3, 1);
EXTMEM AudioConnection patchCord113(FlashSampler8, 0, flashmix2, 3);

EXTMEM AudioConnection patchCord115(FlashSampler7, 0, flashmix2, 2);
EXTMEM AudioConnection patchCord116(FlashSampler12, 0, flashmix3, 3);
EXTMEM AudioConnection patchCord117(wavePAmp0, 0, filter303L1, 0);
EXTMEM AudioConnection patchCord118(FlashSampler13, 0, flashmix4, 0);
EXTMEM AudioConnection patchCord119(FlashSampler14, 0, flashmix4, 1);
EXTMEM AudioConnection patchCord120(FlashSampler11, 0, flashmix3, 2);
EXTMEM AudioConnection patchCord121(FlashSampler16, 0, flashmix4, 3);
EXTMEM AudioConnection patchCord122(FlashSampler15, 0, flashmix4, 2);

EXTMEM AudioConnection patchCord124(fade2, 0, filter303L3, 1);
EXTMEM AudioConnection patchCord125(fade1, 0, filter303L2, 1);
EXTMEM AudioConnection patchCord126(wavePAmp1, 0, filter303L2, 0);
EXTMEM AudioConnection patchCord127(fade3, 0, filter303L4, 1);
EXTMEM AudioConnection patchCord128(wavePAmp2, 0, filter303L3, 0);
EXTMEM AudioConnection patchCord129(wavePAmp3, 0, filter303L4, 0);
EXTMEM AudioConnection patchCord130(fade4, 0, filter303L5, 1);
EXTMEM AudioConnection patchCord131(wavePAmp4, 0, filter303L5, 0);

EXTMEM AudioConnection patchCord135(filter303L6, 0, mix303L6, 0);
EXTMEM AudioConnection patchCord136(filter303L6, 1, mix303L6, 1);
EXTMEM AudioConnection patchCord137(filter303L6, 2, mix303L6, 2);
EXTMEM AudioConnection patchCord138(filter303L1, 0, mix303L1, 0);
EXTMEM AudioConnection patchCord139(filter303L1, 1, mix303L1, 1);
EXTMEM AudioConnection patchCord140(filter303L1, 2, mix303L1, 2);

EXTMEM AudioConnection patchCord144(filter303L2, 0, mix303L2, 0);
EXTMEM AudioConnection patchCord145(filter303L2, 1, mix303L2, 1);
EXTMEM AudioConnection patchCord146(filter303L2, 2, mix303L2, 2);
EXTMEM AudioConnection patchCord147(filter303L3, 0, mix303L3, 0);
EXTMEM AudioConnection patchCord148(filter303L3, 1, mix303L3, 1);
EXTMEM AudioConnection patchCord149(filter303L3, 2, mix303L3, 2);
EXTMEM AudioConnection patchCord150(filter303L4, 0, mix303L4, 0);
EXTMEM AudioConnection patchCord151(filter303L4, 1, mix303L4, 1);
EXTMEM AudioConnection patchCord152(filter303L4, 2, mix303L4, 2);
EXTMEM AudioConnection patchCord153(filter303L5, 0, mix303L5, 0);
EXTMEM AudioConnection patchCord154(filter303L5, 1, mix303L5, 1);
EXTMEM AudioConnection patchCord155(filter303L5, 2, mix303L5, 2);
EXTMEM AudioConnection patchCord156(flashmix1, 0, flashmixMain, 0);
EXTMEM AudioConnection patchCord157(flashmix2, 0, flashmixMain, 1);
EXTMEM AudioConnection patchCord158(flashmix3, 0, flashmixMain, 2);
EXTMEM AudioConnection patchCord159(flashmix4, 0, flashmixMain, 3);
EXTMEM AudioConnection patchCord160(mix303L6, 0, mixerWet303L6, 1);
EXTMEM AudioConnection patchCord161(usb1, 0, InMixL, 0);
EXTMEM AudioConnection patchCord162(usb1, 1, InMixR, 0);

EXTMEM AudioConnection patchCord164(mix303L1, 0, mixerWet303L1, 1);
EXTMEM AudioConnection patchCord165(mix303L2, 0, mixerWet303L2, 1);

EXTMEM AudioConnection patchCord167(mix303L3, 0, mixerWet303L3, 1);
EXTMEM AudioConnection patchCord168(mix303L4, 0, mixerWet303L4, 1);
EXTMEM AudioConnection patchCord169(mix303L5, 0, mixerWet303L5, 1);
EXTMEM AudioConnection patchCord170(flashmixMain, 0, flashMastermix, 0);
EXTMEM AudioConnection patchCord171(mixerWet303L6, 0, mixerWL5to8, 1);
EXTMEM AudioConnection patchCord172(mixerWet303L2, 0, mixerWL1to4, 1);

EXTMEM AudioConnection patchCord174(mixerWet303L1, 0, mixerWL1to4, 0);
EXTMEM AudioConnection patchCord175(mixerWet303L3, 0, mixerWL1to4, 2);

EXTMEM AudioConnection patchCord177(mixerWet303L4, 0, mixerWL1to4, 3);
EXTMEM AudioConnection patchCord178(InMixL, LineInPreAmpL);
EXTMEM AudioConnection patchCord179(InMixR, LineInPreAmpR);
EXTMEM AudioConnection patchCord180(mixerWet303L5, 0, mixerWL5to8, 0);
EXTMEM AudioConnection patchCord181(AudioIn1, 0, InMixL, 1);
EXTMEM AudioConnection patchCord182(AudioIn1, 1, InMixR, 1);
EXTMEM AudioConnection patchCord183(mixerWL1to4, 0, mixerWAll, 0);
EXTMEM AudioConnection patchCord184(LineInPreAmpR, 0, MasterR, 2);
EXTMEM AudioConnection patchCord185(playSdWav1, 0, MasterL, 0);
EXTMEM AudioConnection patchCord186(playSdWav1, 1, MasterR, 0);
EXTMEM AudioConnection patchCord187(LineInPreAmpL, 0, MasterL, 2);
EXTMEM AudioConnection patchCord188(mixerWL5to8, 0, mixerWAll, 1);
EXTMEM AudioConnection patchCord189(mixerWAll, 0, MasterR, 1);
EXTMEM AudioConnection patchCord190(mixerWAll, 0, MasterL, 1);
EXTMEM AudioConnection patchCord191(mixerWAll, 0, FXBusR, 2);
EXTMEM AudioConnection patchCord192(mixerWAll, 0, FXBusL, 2);
EXTMEM AudioConnection patchCord193(metrodrum1, 0, MasterL1, 2);
EXTMEM AudioConnection patchCord194(metrodrum1, 0, MasterR1, 2);
EXTMEM AudioConnection patchCord195(MasterL, 0, MasterL1, 0);
EXTMEM AudioConnection patchCord196(MasterR, 0, MasterR1, 0);
EXTMEM AudioConnection patchCord197(playRawL, 0, MasterL1, 1);
EXTMEM AudioConnection patchCord198(playRawR, 0, MasterR1, 1);
EXTMEM AudioConnection patchCord199(FlashRaw, 0, flashMastermix, 1);
EXTMEM AudioConnection patchCord200(MasterR1, 0, premixMaster, 1);
EXTMEM AudioConnection patchCord201(MasterR1, 0, WetMixMasterR, 0);
EXTMEM AudioConnection patchCord202(MasterL1, 0, premixMaster, 0);
EXTMEM AudioConnection patchCord203(MasterL1, 0, WetMixMasterL, 0);
EXTMEM AudioConnection patchCord204(flashMastermix, 0, MasterL1, 3);
EXTMEM AudioConnection patchCord205(flashMastermix, 0, MasterR1, 3);
EXTMEM AudioConnection patchCord206(flashMastermix, 0, FXBusL, 1);
EXTMEM AudioConnection patchCord207(flashMastermix, 0, FXBusR, 1);
EXTMEM AudioConnection patchCord208(filter3, 0, mixfilter3, 0);
EXTMEM AudioConnection patchCord209(filter3, 1, mixfilter3, 1);
EXTMEM AudioConnection patchCord210(filter3, 2, mixfilter3, 2);
EXTMEM AudioConnection patchCord211(filter1, 0, mixfilter1, 0);
EXTMEM AudioConnection patchCord212(filter1, 1, mixfilter1, 1);
EXTMEM AudioConnection patchCord213(filter1, 2, mixfilter1, 2);
EXTMEM AudioConnection patchCord214(filter2, 0, mixfilter2, 0);
EXTMEM AudioConnection patchCord215(filter2, 1, mixfilter2, 1);
EXTMEM AudioConnection patchCord216(filter2, 2, mixfilter2, 2);
EXTMEM AudioConnection patchCord217(WetMixMasterL, 0, premixmixx1, 0);
EXTMEM AudioConnection patchCord218(WetMixMasterL, 0, premixmixx2, 0);
EXTMEM AudioConnection patchCord219(WetMixMasterL, 0, premixmixx3, 0);
EXTMEM AudioConnection patchCord220(WetMixMasterL, 0, FXBusL, 0);
EXTMEM AudioConnection patchCord221(WetMixMasterR, 0, premixmixx1, 1);
EXTMEM AudioConnection patchCord222(WetMixMasterR, 0, premixmixx2, 1);
EXTMEM AudioConnection patchCord223(WetMixMasterR, 0, premixmixx3, 1);
EXTMEM AudioConnection patchCord224(WetMixMasterR, 0, FXBusR, 0);
EXTMEM AudioConnection patchCord225(FXBusL, ampL);
EXTMEM AudioConnection patchCord226(FXBusR, ampR);
EXTMEM AudioConnection patchCord227(premixmixx2, 0, feedbackdelay2, 1);
EXTMEM AudioConnection patchCord228(premixmixx3, 0, feedbackdelay3, 1);
EXTMEM AudioConnection patchCord229(premixmixx1, 0, feedbackdelay1, 1);
EXTMEM AudioConnection patchCord230(ampL, queue1);
EXTMEM AudioConnection patchCord231(ampL, 0, audioOutput, 0);

EXTMEM AudioConnection patchCord233(ampR, queue2);
EXTMEM AudioConnection patchCord234(ampR, 0, audioOutput, 1);

EXTMEM AudioConnection patchCord238(delay1, 0, delay1pre1, 0);
EXTMEM AudioConnection patchCord239(delay1, 1, delay1pre1, 1);
EXTMEM AudioConnection patchCord240(delay1, 2, delay1pre1, 2);
EXTMEM AudioConnection patchCord241(delay1, 3, delay1pre1, 3);
EXTMEM AudioConnection patchCord242(delay1, 4, delay1pre2, 0);
EXTMEM AudioConnection patchCord243(delay1, 5, delay1pre2, 1);
EXTMEM AudioConnection patchCord244(delay1, 6, delay1pre2, 2);
EXTMEM AudioConnection patchCord245(delay1, 7, delay1pre2, 3);
EXTMEM AudioConnection patchCord246(delay2, 0, delay2pre1, 0);
EXTMEM AudioConnection patchCord247(delay2, 1, delay2pre1, 1);
EXTMEM AudioConnection patchCord248(delay2, 2, delay2pre1, 2);
EXTMEM AudioConnection patchCord249(delay2, 3, delay2pre1, 3);
EXTMEM AudioConnection patchCord250(delay2, 4, delay2pre2, 0);
EXTMEM AudioConnection patchCord251(delay2, 5, delay2pre2, 1);
EXTMEM AudioConnection patchCord252(delay2, 6, delay2pre2, 2);
EXTMEM AudioConnection patchCord253(delay2, 7, delay2pre2, 3);
EXTMEM AudioConnection patchCord254(delay3, 0, delay3pre1, 0);
EXTMEM AudioConnection patchCord255(delay3, 1, delay3pre1, 1);
EXTMEM AudioConnection patchCord256(delay3, 2, delay3pre1, 2);
EXTMEM AudioConnection patchCord257(delay3, 3, delay3pre1, 3);
EXTMEM AudioConnection patchCord258(delay3, 4, delay3pre2, 0);
EXTMEM AudioConnection patchCord259(delay3, 5, delay3pre2, 1);
EXTMEM AudioConnection patchCord260(delay3, 6, delay3pre2, 2);
EXTMEM AudioConnection patchCord261(delay3, 7, delay3pre2, 3);
EXTMEM AudioConnection patchCord262(delay1pre2, 0, delaymix1, 1);
EXTMEM AudioConnection patchCord263(delay2pre1, 0, delaymix2, 0);
EXTMEM AudioConnection patchCord264(delay3pre1, 0, delaymix3, 0);
EXTMEM AudioConnection patchCord265(delay2pre2, 0, delaymix2, 1);
EXTMEM AudioConnection patchCord266(delay3pre2, 0, delaymix3, 1);
EXTMEM AudioConnection patchCord267(delay1pre1, 0, delaymix1, 0);
EXTMEM AudioControlSGTL5000 audioShield; // xy=4077.883331298828,548
                 // GUItool: end automatically generated code
