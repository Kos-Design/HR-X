#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
EXTMEM AudioEffectMultiply      multiply3;      //xy=124.00012588500977,1159.0000324249268
EXTMEM AudioEffectMultiply      multiply2;      //xy=126.00012588500977,1117.0000324249268
EXTMEM AudioEffectMultiply      multiply1;      //xy=128.00012588500977,1074.0000324249268
EXTMEM AudioSynthWaveform       LFOrm3;         //xy=282.333251953125,1095.999755859375
EXTMEM AudioSynthWaveform       LFOrm4;         //xy=285.333251953125,1317.999755859375
EXTMEM AudioSynthWaveform       LFOrm1;         //xy=290.333251953125,784.999755859375
EXTMEM AudioSynthWaveform       LFOrm2;         //xy=290.333251953125,901.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform1L3;  //xy=547.333251953125,946.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform4L2;  //xy=548.333251953125,914.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform2L3;  //xy=548.333251953125,980.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform1L2;  //xy=549.333251953125,808.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform2L2;  //xy=550.333251953125,842.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform3L3;  //xy=550.333251953125,1012.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform1L4;  //xy=550.333251953125,1083.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform1L1;  //xy=552.333251953125,669.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform4L3;  //xy=552.333251953125,1047.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform2L4;  //xy=552.333251953125,1117.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform2L1;  //xy=554.333251953125,703.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform3L2;  //xy=554.333251953125,879.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform3L4;  //xy=554.333251953125,1150.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform1L5;  //xy=554.333251953125,1233.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform3L1;  //xy=556.333251953125,735.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform4L4;  //xy=555.333251953125,1185.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform4L1;  //xy=557.333251953125,770.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform2L5;  //xy=556.333251953125,1267.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform3L5;  //xy=558.333251953125,1300.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform4L5;  //xy=559.333251953125,1335.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform1L6;  //xy=568.333251953125,1382.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform2L6;  //xy=570.333251953125,1416.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform3L6;  //xy=572.333251953125,1449.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform4L6;  //xy=573.333251953125,1484.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform1L7;  //xy=574.333251953125,1522.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform1L8;  //xy=575.333251953125,1665.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform2L7;  //xy=576.333251953125,1556.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform3L7;  //xy=578.333251953125,1589.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform4L7;  //xy=579.333251953125,1624.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform3L8;  //xy=579.333251953125,1732.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform2L8;  //xy=580.333251953125,1699.999755859375
EXTMEM AudioSynthWaveformModulated FMWaveform4L8;  //xy=580.333251953125,1767.999755859375
EXTMEM AudioEffectMultiply      modulate1L6;    //xy=744.3330917358398,1371.6663808822632
EXTMEM AudioEffectMultiply      modulate2L6;    //xy=744.3330917358398,1403.6663808822632
EXTMEM AudioEffectMultiply      modulate3L6;    //xy=746.3330917358398,1434.6663808822632
EXTMEM AudioEffectMultiply      modulate4L6;    //xy=750.3330917358398,1464.6663808822632
EXTMEM AudioEffectMultiply      modulate1L2;    //xy=758.3330917358398,831.6663808822632
EXTMEM AudioEffectMultiply      modulate2L2;    //xy=758.3330917358398,863.6663808822632
EXTMEM AudioEffectMultiply      modulate1L3;    //xy=758.3330917358398,965.6663808822632
EXTMEM AudioEffectMultiply      modulate2L3;    //xy=758.3330917358398,997.6663808822632
EXTMEM AudioEffectMultiply      modulate1L5;    //xy=758.3330917358398,1232.6663808822632
EXTMEM AudioEffectMultiply      modulate2L5;    //xy=758.3330917358398,1264.6663808822632
EXTMEM AudioEffectMultiply      modulate3L2;    //xy=760.3330917358398,894.6663808822632
EXTMEM AudioEffectMultiply      modulate3L3;    //xy=760.3330917358398,1028.6663808822632
EXTMEM AudioEffectMultiply      modulate3L5;    //xy=760.3330917358398,1295.6663808822632
EXTMEM AudioEffectMultiply      modulate1L4;    //xy=762.3330917358398,1099.6663808822632
EXTMEM AudioEffectMultiply      modulate2L4;    //xy=762.3330917358398,1131.6663808822632
EXTMEM AudioEffectMultiply      modulate4L2;    //xy=764.3330917358398,924.6663808822632
EXTMEM AudioEffectMultiply      modulate4L3;    //xy=764.3330917358398,1058.6663808822632
EXTMEM AudioEffectMultiply      modulate3L4;    //xy=764.3330917358398,1162.6663808822632
EXTMEM AudioEffectMultiply      modulate4L5;    //xy=764.3330917358398,1325.6663808822632
EXTMEM AudioEffectMultiply      modulate1L1;    //xy=768.3330917358398,702.6663808822632
EXTMEM AudioEffectMultiply      modulate2L1;    //xy=768.3330917358398,734.6663808822632
EXTMEM AudioEffectMultiply      modulate4L4;    //xy=768.3330917358398,1192.6663808822632
EXTMEM AudioEffectMultiply      modulate1L7;    //xy=767.3330917358398,1506.6663808822632
EXTMEM AudioEffectMultiply      modulate3L1;    //xy=770.3330917358398,765.6663808822632
EXTMEM AudioEffectMultiply      modulate2L7;    //xy=767.3330917358398,1538.6663808822632
EXTMEM AudioEffectMultiply      modulate3L7;    //xy=769.3330917358398,1569.6663808822632
EXTMEM AudioEffectMultiply      modulate4L1;    //xy=773.3330917358398,796.6663808822632
EXTMEM AudioEffectMultiply      modulate1L8;    //xy=770.3330917358398,1640.6663808822632
EXTMEM AudioEffectMultiply      modulate2L8;    //xy=770.3330917358398,1672.6663808822632
EXTMEM AudioEffectMultiply      modulate4L7;    //xy=771.3330917358398,1600.6663808822632
EXTMEM AudioEffectMultiply      modulate3L8;    //xy=772.3330917358398,1703.6663808822632
EXTMEM AudioEffectMultiply      modulate4L8;    //xy=776.3330917358398,1733.6663808822632
EXTMEM AudioSynthSimpleDrum     drum2L1;        //xy=970.9999198913574,716.6667242050171
EXTMEM AudioSynthSimpleDrum     drum2L6;        //xy=968.6668090820312,1386.0002355575562
EXTMEM AudioSynthSimpleDrum     drum2L5;        //xy=969.6668090820312,1256.0002355575562
EXTMEM AudioSynthSimpleDrum     drum4L1;        //xy=971.9999198913574,779.6667242050171
EXTMEM AudioSynthSimpleDrum     drum4L5;        //xy=970.6668090820312,1319.0002355575562
EXTMEM AudioSynthSimpleDrum     drum3L1;        //xy=972.9999198913574,749.6667242050171
EXTMEM AudioSynthSimpleDrum     drum1L1;        //xy=973.9999198913574,686.6667242050171
EXTMEM AudioSynthSimpleDrum     drum3L5;        //xy=971.6668090820312,1289.0002355575562
EXTMEM AudioSynthSimpleDrum     drum1L6;        //xy=971.6668090820312,1356.0002355575562
EXTMEM AudioSynthSimpleDrum     drum1L5;        //xy=972.6668090820312,1226.0002355575562
EXTMEM AudioSynthSimpleDrum     drum2L3;        //xy=974.6668090820312,986.0002355575562
EXTMEM AudioSynthSimpleDrum     drum4L3;        //xy=975.6668090820312,1049.0002355575562
EXTMEM AudioSynthSimpleDrum     drum2L4;        //xy=975.6668090820312,1126.0002355575562
EXTMEM AudioSynthSimpleDrum     drum3L3;        //xy=976.6668090820312,1019.0002355575562
EXTMEM AudioSynthSimpleDrum     drum4L4;        //xy=976.6668090820312,1189.0002355575562
EXTMEM AudioSynthSimpleDrum     drum1L3;        //xy=977.6668090820312,956.0002355575562
EXTMEM AudioSynthSimpleDrum     drum3L4;        //xy=977.6668090820312,1159.0002355575562
EXTMEM AudioSynthSimpleDrum     drum1L4;        //xy=978.6668090820312,1096.0002355575562
EXTMEM AudioSynthSimpleDrum     drum2L2;        //xy=979.6668090820312,859.0002355575562
EXTMEM AudioSynthSimpleDrum     drum4L2;        //xy=980.6668090820312,922.0002355575562
EXTMEM AudioSynthSimpleDrum     drum2L7;        //xy=978.6667938232422,1532.3336811065674
EXTMEM AudioSynthSimpleDrum     drum3L2;        //xy=981.6668090820312,892.0002355575562
EXTMEM AudioSynthSimpleDrum     drum2L8;        //xy=978.6667938232422,1662.3336811065674
EXTMEM AudioSynthSimpleDrum     drum4L6;        //xy=979.6667938232422,1462.3336811065674
EXTMEM AudioSynthSimpleDrum     drum1L2;        //xy=982.6668090820312,829.0002355575562
EXTMEM AudioSynthSimpleDrum     drum4L7;        //xy=979.6667938232422,1595.3336811065674
EXTMEM AudioSynthSimpleDrum     drum3L6;        //xy=980.6667938232422,1432.3336811065674
EXTMEM AudioSynthSimpleDrum     drum4L8;        //xy=979.6667938232422,1725.3336811065674
EXTMEM AudioSynthSimpleDrum     drum3L7;        //xy=980.6667938232422,1565.3336811065674
EXTMEM AudioSynthSimpleDrum     drum3L8;        //xy=980.6667938232422,1695.3336811065674
EXTMEM AudioSynthSimpleDrum     drum1L7;        //xy=981.6667938232422,1502.3336811065674
EXTMEM AudioSynthSimpleDrum     drum1L8;        //xy=981.6667938232422,1632.3336811065674
EXTMEM AudioSynthKarplusStrong  string3L8;      //xy=1094.6667938232422,1697.3336811065674
EXTMEM AudioSynthKarplusStrong  string2L8;      //xy=1095.6667938232422,1664.3336811065674
EXTMEM AudioSynthKarplusStrong  string4L8;      //xy=1095.6667938232422,1729.3336811065674
EXTMEM AudioSynthKarplusStrong  string2L6;      //xy=1099.6668090820312,1378.0002355575562
EXTMEM AudioSynthKarplusStrong  string3L7;      //xy=1100.6667938232422,1560.3336811065674
EXTMEM AudioSynthKarplusStrong  string2L7;      //xy=1101.6667938232422,1527.3336811065674
EXTMEM AudioSynthKarplusStrong  string4L7;      //xy=1101.6667938232422,1592.3336811065674
EXTMEM AudioSynthKarplusStrong  string1L8;      //xy=1101.6667938232422,1632.3336811065674
EXTMEM AudioSynthKarplusStrong  string3L4;      //xy=1104.6668090820312,1141.0002355575562
EXTMEM AudioSynthKarplusStrong  string2L4;      //xy=1105.6668090820312,1108.0002355575562
EXTMEM AudioSynthKarplusStrong  string4L4;      //xy=1105.6668090820312,1173.0002355575562
EXTMEM AudioSynthKarplusStrong  string1L6;      //xy=1105.6668090820312,1346.0002355575562
EXTMEM AudioSynthKarplusStrong  string1L7;      //xy=1107.6667938232422,1495.3336811065674
EXTMEM AudioSynthKarplusStrong  string3L3;      //xy=1109.6668090820312,1008.0002355575562
EXTMEM AudioSynthKarplusStrong  string3L6;      //xy=1108.6667938232422,1424.3336811065674
EXTMEM AudioSynthKarplusStrong  string2L3;      //xy=1110.6668090820312,975.0002355575562
EXTMEM AudioSynthKarplusStrong  string4L3;      //xy=1110.6668090820312,1040.0002355575562
EXTMEM AudioSynthKarplusStrong  string3L1;      //xy=1111.9999198913574,723.6667242050171
EXTMEM AudioSynthKarplusStrong  string4L6;      //xy=1109.6667938232422,1456.3336811065674
EXTMEM AudioSynthKarplusStrong  string2L1;      //xy=1112.9999198913574,690.6667242050171
EXTMEM AudioSynthKarplusStrong  string1L4;      //xy=1111.6668090820312,1076.0002355575562
EXTMEM AudioSynthKarplusStrong  string4L1;      //xy=1112.9999198913574,755.6667242050171
EXTMEM AudioSynthKarplusStrong  string3L2;      //xy=1112.6668090820312,875.0002355575562
EXTMEM AudioSynthKarplusStrong  string1L2;      //xy=1112.9999198913574,796.6667242050171
EXTMEM AudioSynthKarplusStrong  string2L2;      //xy=1113.6668090820312,842.0002355575562
EXTMEM AudioSynthKarplusStrong  string4L2;      //xy=1113.6668090820312,907.0002355575562
EXTMEM AudioSynthKarplusStrong  string3L5;      //xy=1115.6668090820312,1277.0002355575562
EXTMEM AudioSynthKarplusStrong  string1L3;      //xy=1117.6668090820312,943.0002355575562
EXTMEM AudioSynthKarplusStrong  string2L5;      //xy=1116.6668090820312,1244.0002355575562
EXTMEM AudioSynthKarplusStrong  string4L5;      //xy=1116.6668090820312,1309.0002355575562
EXTMEM AudioSynthKarplusStrong  string1L1;      //xy=1119.9999198913574,658.6667242050171
EXTMEM AudioSynthKarplusStrong  string1L5;      //xy=1122.6668090820312,1212.0002355575562
EXTMEM AudioSynthWaveform       waveform1L7;    //xy=1296.9998474121094,1487.6664772033691
EXTMEM AudioSynthWaveform       waveform1L8;    //xy=1296.9998474121094,1623.6664772033691
EXTMEM AudioSynthWaveform       waveform4L7;    //xy=1298.9998474121094,1575.6664772033691
EXTMEM AudioSynthWaveform       waveform4L8;    //xy=1298.9998474121094,1711.6664772033691
EXTMEM AudioSynthWaveform       waveform1L5;    //xy=1300.9998474121094,1226.6664772033691
EXTMEM AudioSynthWaveform       waveform2L7;    //xy=1299.9998474121094,1520.6664772033691
EXTMEM AudioSynthWaveform       waveform3L7;    //xy=1299.9998474121094,1549.6664772033691
EXTMEM AudioSynthWaveform       waveform1L6;    //xy=1300.9998474121094,1357.6664772033691
EXTMEM AudioSynthWaveform       waveform2L8;    //xy=1299.9998474121094,1656.6664772033691
EXTMEM AudioSynthWaveform       waveform3L8;    //xy=1299.9998474121094,1685.6664772033691
EXTMEM AudioSynthWaveform       waveform4L5;    //xy=1302.9998474121094,1313.6664772033691
EXTMEM AudioSynthWaveform       waveform4L6;    //xy=1302.9998474121094,1445.6664772033691
EXTMEM AudioSynthWaveform       waveform2L5;    //xy=1303.9998474121094,1258.6664772033691
EXTMEM AudioSynthWaveform       waveform3L5;    //xy=1303.9998474121094,1287.6664772033691
EXTMEM AudioSynthWaveform       waveform2L6;    //xy=1303.9998474121094,1390.6664772033691
EXTMEM AudioSynthWaveform       waveform3L6;    //xy=1303.9998474121094,1419.6664772033691
EXTMEM AudioSynthWaveform       waveform1L4;    //xy=1308.9998474121094,1073.6664772033691
EXTMEM AudioSynthWaveform       waveform3L3;    //xy=1311.9998474121094,1001.6664772033691
EXTMEM AudioSynthWaveform       waveform1L2;    //xy=1312.9998474121094,807.6664772033691
EXTMEM AudioSynthWaveform       waveform4L4;    //xy=1311.9998474121094,1161.6664772033691
EXTMEM AudioSynthWaveform       waveform2L3;    //xy=1312.9998474121094,971.6664772033691
EXTMEM AudioSynthWaveform       waveform4L3;    //xy=1312.9998474121094,1028.6664772033691
EXTMEM AudioSynthWaveform       waveform2L4;    //xy=1312.9998474121094,1106.6664772033691
EXTMEM AudioSynthWaveform       waveform3L4;    //xy=1312.9998474121094,1135.6664772033691
EXTMEM AudioSynthWaveform       waveform1L3;    //xy=1313.9998474121094,937.6664772033691
EXTMEM AudioSynthWaveform       waveform3L2;    //xy=1316.9998474121094,867.6664772033691
EXTMEM AudioSynthWaveform       waveform3L1;    //xy=1317.9998474121094,739.6664772033691
EXTMEM AudioSynthWaveform       waveform2L2;    //xy=1317.9998474121094,837.6664772033691
EXTMEM AudioSynthWaveform       waveform4L2;    //xy=1317.9998474121094,894.6664772033691
EXTMEM AudioSynthWaveform       waveform2L1;    //xy=1318.9998474121094,709.6664772033691
EXTMEM AudioSynthWaveform       waveform4L1;    //xy=1318.9998474121094,766.6664772033691
EXTMEM AudioSynthWaveform       waveform1L1;    //xy=1319.9998474121094,677.6664772033691
EXTMEM AudioMixer4              WavesL7;        //xy=1445.9998474121094,1533.6664772033691
EXTMEM AudioMixer4              WavesL8;        //xy=1445.9998474121094,1669.6664772033691
EXTMEM AudioMixer4              WavesL5;        //xy=1449.9998474121094,1271.6664772033691
EXTMEM AudioMixer4              WavesL6;        //xy=1449.9998474121094,1403.6664772033691
EXTMEM AudioMixer4              WavesL3;        //xy=1458.9998474121094,984.6664772033691
EXTMEM AudioMixer4              WavesL4;        //xy=1458.9998474121094,1119.6664772033691
EXTMEM AudioMixer4              WavesL2;        //xy=1463.9998474121094,850.6664772033691
EXTMEM AudioMixer4              WavesL1;        //xy=1487.9998474121094,727.6664772033691
EXTMEM AudioSynthWaveform       LFOrm303; //xy=1563.8572387695312,1044.5714855194092
EXTMEM AudioEffectEnvelope      envelopeL5;     //xy=1577.9998779296875,1421.66650390625
EXTMEM AudioEffectEnvelope      envelopeL2;     //xy=1608.9998474121094,983.6664772033691
EXTMEM AudioEffectEnvelope      envelopeL7;     //xy=1609.9998474121094,1663.6664772033691
EXTMEM AudioEffectEnvelope      envelopeL6;     //xy=1610.9998474121094,1525.6664772033691
EXTMEM AudioEffectEnvelope      envelopeL3;     //xy=1616.9998474121094,1118.6664772033691
EXTMEM AudioEffectEnvelope      envelopeL4;     //xy=1621.9998474121094,1265.6664772033691
EXTMEM AudioEffectEnvelope      envelopeL0;     //xy=1632.6665420532227,695.3330497741699
EXTMEM AudioEffectEnvelope      envelopeL1;     //xy=1635.9998474121094,849.6664772033691
EXTMEM AudioAmplifier           fade5; //xy=1750,1478.5714111328125
EXTMEM AudioAmplifier           fade6; //xy=1755.71435546875,1584.2857666015625
EXTMEM AudioAmplifier           fade0;  //xy=1765.7142295837402,785.71422290802
EXTMEM AudioAmplifier           wavePAmp6; //xy=1765.1427383422852,1546.1427516937256
EXTMEM AudioAmplifier           wavePAmp5; //xy=1765.8570251464844,1444.4285802841187
EXTMEM AudioPlaySerialflashRaw  FlashSampler1;  //xy=1771.5,52.16644287109375
EXTMEM AudioPlaySerialflashRaw  FlashSampler2;  //xy=1771.4999465942383,92.16645050048828
EXTMEM AudioPlaySerialflashRaw  FlashSampler5;  //xy=1772.4999465942383,214.16645050048828
EXTMEM AudioPlaySerialflashRaw  FlashSampler6;  //xy=1772.4999465942383,249.16645050048828
EXTMEM AudioPlaySerialflashRaw  FlashSampler4;  //xy=1773.4999465942383,162.16645050048828
EXTMEM AudioPlaySerialflashRaw  FlashSampler9;  //xy=1773.4999465942383,371.1664505004883
EXTMEM AudioPlaySerialflashRaw  FlashSampler3;  //xy=1774.4999465942383,125.16645050048828
EXTMEM AudioPlaySerialflashRaw  FlashSampler10; //xy=1773.4999465942383,406.1664505004883
EXTMEM AudioPlaySerialflashRaw  FlashSampler8;  //xy=1774.4999465942383,319.1664505004883
EXTMEM AudioAmplifier           wavePAmp7; //xy=1769.428482055664,1673.142807006836
EXTMEM AudioPlaySerialflashRaw  FlashSampler7;  //xy=1775.4999465942383,282.1664505004883
EXTMEM AudioAmplifier           wavePAmp0; //xy=1774.2381210327148,742.4761171340942
EXTMEM AudioPlaySerialflashRaw  FlashSampler12; //xy=1775.4999465942383,476.1664505004883
EXTMEM AudioPlaySerialflashRaw  FlashSampler13; //xy=1775.4999465942383,527.1664505004883
EXTMEM AudioPlaySerialflashRaw  FlashSampler14; //xy=1775.4999465942383,562.1664505004883
EXTMEM AudioPlaySerialflashRaw  FlashSampler11; //xy=1776.4999465942383,439.1664505004883
EXTMEM AudioPlaySerialflashRaw  FlashSampler16; //xy=1777.4999465942383,632.1664505004883
EXTMEM AudioPlaySerialflashRaw  FlashSampler15; //xy=1778.4999465942383,595.1664505004883
EXTMEM AudioAmplifier           fade7; //xy=1774.2857284545898,1708.5714645385742
EXTMEM AudioAmplifier           fade2; //xy=1777.142822265625,1032.857177734375
EXTMEM AudioAmplifier           fade1;  //xy=1781.4285926818848,907.1429042816162
EXTMEM AudioAmplifier           wavePAmp1; //xy=1784.5713119506836,868.7142734527588
EXTMEM AudioAmplifier           fade3; //xy=1784.2857666015625,1147.142822265625
EXTMEM AudioAmplifier           wavePAmp2; //xy=1786.8571472167969,996.1427974700928
EXTMEM AudioAmplifier           wavePAmp3; //xy=1791.7142181396484,1111.9999332427979
EXTMEM AudioAmplifier           fade4; //xy=1810,1320
EXTMEM AudioAmplifier           wavePAmp4; //xy=1823.285789489746,1282.9999418258667
EXTMEM AudioFilterStateVariable filter303L7; //xy=1910.9998626708984,1559.333246231079
EXTMEM AudioFilterStateVariable filter303L6; //xy=1914.66650390625,1452.333251953125
EXTMEM AudioFilterStateVariable filter303L1; //xy=1920.3136444091797,748.7347450256348
EXTMEM AudioFilterStateVariable filter303L8; //xy=1920.285488128662,1680.476110458374
EXTMEM AudioFilterStateVariable filter303L2; //xy=1929.3332633972168,877.6665325164795
EXTMEM AudioFilterStateVariable filter303L3; //xy=1934,1001.3331909179688
EXTMEM AudioFilterStateVariable filter303L4; //xy=1945.9998779296875,1125.333251953125
EXTMEM AudioFilterStateVariable filter303L5; //xy=1975.3331298828125,1293.9998779296875
EXTMEM AudioMixer4              flashmix1;      //xy=1985.4999465942383,115.16645050048828
EXTMEM AudioMixer4              flashmix2;      //xy=1986.4999465942383,271.1664505004883
EXTMEM AudioMixer4              flashmix3;      //xy=1987.4999465942383,428.1664505004883
EXTMEM AudioMixer4              flashmix4;      //xy=2049.4996337890625,581.8330879211426
EXTMEM AudioMixer4              mix303L6; //xy=2048.999885559082,1422.7349853515625
EXTMEM AudioMixer4              mix303L7; //xy=2071.3331604003906,1564.734977722168
EXTMEM AudioMixer4              mix303L2; //xy=2076.333267211914,884.7348937988281
EXTMEM AudioMixer4              mix303L1; //xy=2076.8374252319336,765.8032779693604
EXTMEM AudioMixer4              mix303L8; //xy=2083.6665802001953,1683.068172454834
EXTMEM AudioMixer4              mix303L3; //xy=2093.9998321533203,985.0681953430176
EXTMEM AudioMixer4              mix303L4; //xy=2101.6664962768555,1106.068073272705
AudioInputUSB            usb1;           //xy=2165,547.5
EXTMEM AudioMixer4              mix303L5; //xy=2170.8091354370117,1293.4491214752197
EXTMEM AudioMixer4              flashmixMain;   //xy=2186.4999465942383,333.1664505004883
EXTMEM AudioMixer4              mixerWet303L6; //xy=2204.162338256836,1414.0427722930908
EXTMEM AudioMixer4              mixerWet303L2; //xy=2241.4956436157227,869.3759460449219
EXTMEM AudioMixer4              mixerWet303L7; //xy=2248.1624069213867,1542.7093048095703
EXTMEM AudioMixer4              mixerWet303L1; //xy=2254.6666946411133,729.4443168640137
EXTMEM AudioMixer4              mixerWet303L3; //xy=2264.1623153686523,963.0424785614014
EXTMEM AudioMixer4              mixerWet303L8; //xy=2263.829055786133,1652.7093086242676
EXTMEM AudioMixer4              mixerWet303L4; //xy=2275.162399291992,1089.0423984527588
EXTMEM AudioMixer4              InMixL;         //xy=2318.5000610351562,493.16644287109375
EXTMEM AudioMixer4              InMixR;         //xy=2318,620.4163818359375
EXTMEM AudioMixer4              mixerWet303L5;  //xy=2340.495895385742,1270.70902633667
EXTMEM AudioMixer4              mixerWL1to4;    //xy=2458.9998779296875,955.3331413269043
EXTMEM AudioAmplifier           LineInPreAmpR;  //xy=2485,621.1664619445801
EXTMEM AudioPlaySdWav           playSdWav1;     //xy=2487.7498779296875,574.4164619445801
EXTMEM AudioAmplifier           LineInPreAmpL;  //xy=2502.4998779296875,517.6664009094238
EXTMEM AudioMixer4              mixerWL5to8;    //xy=2509.285575866699,1428.9997119903564
EXTMEM AudioMixer4              mixerWAll;      //xy=2645.4165954589844,1011.9998512268066
EXTMEM AudioSynthSimpleDrum     metrodrum1;     //xy=2687.999954223633,463.6664619445801
EXTMEM AudioMixer4              MasterL;        //xy=2698.999954223633,546.6664619445801
EXTMEM AudioMixer4              MasterR;        //xy=2729.6665649414062,619.333080291748
EXTMEM AudioPlaySdRaw           playRawR;       //xy=2741.333251953125,384.6664390563965
EXTMEM AudioPlaySdRaw           playRawL;       //xy=2741.999954223633,308.6664619445801
EXTMEM AudioPlaySerialflashRaw  FlashRaw;       //xy=2793.7498626708984,239.1664161682129
EXTMEM AudioSynthWaveformSine   lfosine3; //xy=2954.83349609375,1391.333209991455
EXTMEM AudioMixer4              MasterR1;       //xy=2961.999954223633,583.6664619445801
EXTMEM AudioMixer4              MasterL1;       //xy=2966.999954223633,487.6664619445801
EXTMEM AudioSynthWaveformSine   lfosine2; //xy=2963.83349609375,1339.333209991455
EXTMEM AudioSynthWaveformSine   lfosine1;          //xy=2967.83349609375,1272.333209991455
EXTMEM AudioEffectFlange        flange1;        //xy=2972.4999084472656,1069.4998760223389
EXTMEM AudioEffectBitcrusher    bitcrusher1;    //xy=2976.4999084472656,1021.4998760223389
EXTMEM AudioEffectChorus        chorus1;        //xy=2981.4999084472656,1112.4998760223389
EXTMEM AudioFilterBiquad        biquad1;        //xy=2982.4999084472656,1160.4998760223389
EXTMEM AudioEffectGranular      granular1;      //xy=2989.4999084472656,955.4998760223389
EXTMEM AudioEffectFreeverb      freeverbs1;      //xy=2994.0003662109375,913.6667060852051
EXTMEM AudioMixer4              flashMastermix; //xy=3010.0831146240234,185.2497901916504
EXTMEM AudioEffectGranular      granular2;      //xy=3121.833225250244,958.1667928695679
EXTMEM AudioEffectBitcrusher    bitcrusher2;    //xy=3121.833225250244,1028.1667928695679
EXTMEM AudioEffectFlange        flange2;        //xy=3126.833225250244,1082.1667928695679
EXTMEM AudioEffectChorus        chorus2;        //xy=3130.833225250244,1126.1667928695679
EXTMEM AudioMixer4              premixMaster;   //xy=3133.6669921875,825.1664619445801
EXTMEM AudioEffectFreeverb      freeverbs2; //xy=3135.2501106262207,904.9167213439941
EXTMEM AudioFilterBiquad        biquad2;        //xy=3137.833225250244,1173.1667928695679
EXTMEM AudioFilterStateVariable filter3;        //xy=3138.83349609375,1398.333209991455
EXTMEM AudioFilterStateVariable filter1;        //xy=3140.83349609375,1255.333209991455
EXTMEM AudioFilterStateVariable filter2;        //xy=3143.83349609375,1326.333209991455
EXTMEM AudioMixer4              WetMixMasterL;  //xy=3252.999755859375,514.6664009094238
EXTMEM AudioMixer4              WetMixMasterR;  //xy=3253.666259765625,604.9997749328613
EXTMEM AudioEffectGranular      granular3;      //xy=3271.5,966.1667060852051
EXTMEM AudioEffectFlange        flange3;        //xy=3271.5,1080.166706085205
EXTMEM AudioEffectChorus        chorus3;        //xy=3274.5,1123.166706085205
EXTMEM AudioFilterBiquad        biquad3;        //xy=3282.5,1171.166706085205
EXTMEM AudioEffectBitcrusher    bitcrusher3;    //xy=3283.5,1028.166706085205
EXTMEM AudioEffectFreeverb      freeverbs3; //xy=3284.0001106262207,908.6667213439941
EXTMEM AudioMixer4              mixfilter1;     //xy=3296.83349609375,1261.333209991455
EXTMEM AudioMixer4              mixfilter3;     //xy=3301.83349609375,1398.333209991455
EXTMEM AudioMixer4              mixfilter2;     //xy=3303.83349609375,1329.333209991455
EXTMEM AudioMixer4              FXBusL;         //xy=3597.666259765625,470.7776069641113
EXTMEM AudioMixer4              FXBusR;         //xy=3607.416748046875,586.9164009094238
EXTMEM AudioMixer4              premixmixx2;    //xy=3656.333251953125,894.6664619445801
EXTMEM AudioMixer4              premixmixx3;    //xy=3662.333251953125,981.6664619445801
EXTMEM AudioMixer4              premixmixx1;    //xy=3668.833282470703,819.916446685791
EXTMEM AudioAmplifier           ampR;           //xy=3772.3332443237305,586.3330821990967
EXTMEM AudioAmplifier           ampL;           //xy=3772.666732788086,538.333101272583
EXTMEM AudioMixer4              feedbackdelay1; //xy=3884.083221435547,804.6665382385254
EXTMEM AudioRecordQueue         queue2;         //xy=3918.66650390625,639.3331909179688
EXTMEM AudioMixer4              feedbackdelay2; //xy=3924.333251953125,905.6664619445801
EXTMEM AudioMixer4              feedbackdelay3; //xy=3928.333251953125,1058.66646194458
EXTMEM AudioRecordQueue         queue1;         //xy=3948.333251953125,448.66650390625
EXTMEM AudioOutputI2S           audioOutput;    //xy=3985.5,561.8331909179688
EXTMEM AudioEffectDelay         delay1;         //xy=4086.333251953125,760.6664619445801
EXTMEM AudioEffectDelay         delay2;         //xy=4110.333251953125,909.6664619445801
EXTMEM AudioEffectDelay         delay3;         //xy=4112.333251953125,1046.66646194458
EXTMEM AudioAnalyzeNoteFrequency notefreq1;      //xy=4153,501
EXTMEM AudioMixer4              delay1pre2;     //xy=4251.333251953125,801.6664619445801
EXTMEM AudioMixer4              delay2pre1;     //xy=4251.333251953125,881.6664619445801
EXTMEM AudioMixer4              delay3pre1;     //xy=4252.333251953125,1014.6664619445801
EXTMEM AudioMixer4              delay2pre2;     //xy=4253.333251953125,945.6664619445801
EXTMEM AudioMixer4              delay3pre2;     //xy=4253.83349609375,1084.16646194458
EXTMEM AudioMixer4              delay1pre1;     //xy=4259.666397094727,706.3331298828125
EXTMEM AudioMixer4              delaymix3;      //xy=4402.333251953125,1052.66646194458
EXTMEM AudioMixer4              delaymix2;      //xy=4407.333251953125,924.6664619445801
EXTMEM AudioMixer4              delaymix1;      //xy=4423.333343505859,762.6665077209473
EXTMEM AudioConnection          patchCord1(LFOrm3, 0, FMWaveform3L3, 0);
EXTMEM AudioConnection          patchCord2(LFOrm3, 0, FMWaveform3L1, 0);
EXTMEM AudioConnection          patchCord3(LFOrm3, 0, FMWaveform3L2, 0);
EXTMEM AudioConnection          patchCord4(LFOrm3, 0, FMWaveform3L4, 0);
EXTMEM AudioConnection          patchCord5(LFOrm3, 0, FMWaveform3L5, 0);
EXTMEM AudioConnection          patchCord6(LFOrm3, 0, FMWaveform3L6, 0);
EXTMEM AudioConnection          patchCord7(LFOrm3, 0, FMWaveform3L7, 0);
EXTMEM AudioConnection          patchCord8(LFOrm3, 0, FMWaveform3L8, 0);
EXTMEM AudioConnection          patchCord9(LFOrm3, 0, modulate3L1, 1);
EXTMEM AudioConnection          patchCord10(LFOrm3, 0, modulate3L2, 1);
EXTMEM AudioConnection          patchCord11(LFOrm3, 0, modulate3L3, 1);
EXTMEM AudioConnection          patchCord12(LFOrm3, 0, modulate3L5, 1);
EXTMEM AudioConnection          patchCord13(LFOrm3, 0, modulate3L4, 1);
EXTMEM AudioConnection          patchCord14(LFOrm3, 0, modulate3L6, 1);
EXTMEM AudioConnection          patchCord15(LFOrm3, 0, modulate3L8, 1);
EXTMEM AudioConnection          patchCord16(LFOrm3, 0, modulate3L7, 1);
EXTMEM AudioConnection          patchCord17(LFOrm3, 0, multiply3, 1);
EXTMEM AudioConnection          patchCord18(LFOrm4, 0, FMWaveform4L4, 0);
EXTMEM AudioConnection          patchCord19(LFOrm4, 0, FMWaveform4L3, 0);
EXTMEM AudioConnection          patchCord20(LFOrm4, 0, FMWaveform4L2, 0);
EXTMEM AudioConnection          patchCord21(LFOrm4, 0, FMWaveform4L1, 0);
EXTMEM AudioConnection          patchCord22(LFOrm4, 0, FMWaveform4L5, 0);
EXTMEM AudioConnection          patchCord23(LFOrm4, 0, FMWaveform4L6, 0);
EXTMEM AudioConnection          patchCord24(LFOrm4, 0, FMWaveform4L7, 0);
EXTMEM AudioConnection          patchCord25(LFOrm4, 0, FMWaveform4L8, 0);
EXTMEM AudioConnection          patchCord26(LFOrm4, 0, modulate4L8, 1);
EXTMEM AudioConnection          patchCord27(LFOrm4, 0, modulate4L7, 1);
EXTMEM AudioConnection          patchCord28(LFOrm4, 0, modulate4L6, 1);
EXTMEM AudioConnection          patchCord29(LFOrm4, 0, modulate4L5, 1);
EXTMEM AudioConnection          patchCord30(LFOrm4, 0, modulate4L4, 1);
EXTMEM AudioConnection          patchCord31(LFOrm4, 0, modulate4L3, 1);
EXTMEM AudioConnection          patchCord32(LFOrm4, 0, modulate4L2, 1);
EXTMEM AudioConnection          patchCord33(LFOrm4, 0, modulate4L1, 1);
EXTMEM AudioConnection          patchCord34(LFOrm1, 0, FMWaveform1L1, 0);
EXTMEM AudioConnection          patchCord35(LFOrm1, 0, FMWaveform1L2, 0);
EXTMEM AudioConnection          patchCord36(LFOrm1, 0, FMWaveform1L3, 0);
EXTMEM AudioConnection          patchCord37(LFOrm1, 0, FMWaveform1L4, 0);
EXTMEM AudioConnection          patchCord38(LFOrm1, 0, FMWaveform1L5, 0);
EXTMEM AudioConnection          patchCord39(LFOrm1, 0, FMWaveform1L6, 0);
EXTMEM AudioConnection          patchCord40(LFOrm1, 0, FMWaveform1L7, 0);
EXTMEM AudioConnection          patchCord41(LFOrm1, 0, FMWaveform1L8, 0);
EXTMEM AudioConnection          patchCord42(LFOrm1, 0, modulate1L1, 1);
EXTMEM AudioConnection          patchCord43(LFOrm1, 0, modulate1L2, 1);
EXTMEM AudioConnection          patchCord44(LFOrm1, 0, modulate1L3, 1);
EXTMEM AudioConnection          patchCord45(LFOrm1, 0, modulate1L4, 1);
EXTMEM AudioConnection          patchCord46(LFOrm1, 0, modulate1L5, 1);
EXTMEM AudioConnection          patchCord47(LFOrm1, 0, modulate1L6, 1);
EXTMEM AudioConnection          patchCord48(LFOrm1, 0, modulate1L7, 1);
EXTMEM AudioConnection          patchCord49(LFOrm1, 0, modulate1L8, 1);
EXTMEM AudioConnection          patchCord50(LFOrm1, 0, multiply1, 1);
EXTMEM AudioConnection          patchCord51(LFOrm2, 0, FMWaveform2L2, 0);
EXTMEM AudioConnection          patchCord52(LFOrm2, 0, FMWaveform2L1, 0);
EXTMEM AudioConnection          patchCord53(LFOrm2, 0, FMWaveform2L3, 0);
EXTMEM AudioConnection          patchCord54(LFOrm2, 0, FMWaveform2L4, 0);
EXTMEM AudioConnection          patchCord55(LFOrm2, 0, FMWaveform2L5, 0);
EXTMEM AudioConnection          patchCord56(LFOrm2, 0, FMWaveform2L6, 0);
EXTMEM AudioConnection          patchCord57(LFOrm2, 0, FMWaveform2L7, 0);
EXTMEM AudioConnection          patchCord58(LFOrm2, 0, FMWaveform2L8, 0);
EXTMEM AudioConnection          patchCord59(LFOrm2, 0, modulate2L8, 1);
EXTMEM AudioConnection          patchCord60(LFOrm2, 0, modulate2L5, 1);
EXTMEM AudioConnection          patchCord61(LFOrm2, 0, modulate2L3, 1);
EXTMEM AudioConnection          patchCord62(LFOrm2, 0, modulate2L6, 1);
EXTMEM AudioConnection          patchCord63(LFOrm2, 0, modulate2L1, 1);
EXTMEM AudioConnection          patchCord64(LFOrm2, 0, modulate2L2, 1);
EXTMEM AudioConnection          patchCord65(LFOrm2, 0, modulate2L4, 1);
EXTMEM AudioConnection          patchCord66(LFOrm2, 0, modulate2L7, 1);
EXTMEM AudioConnection          patchCord67(LFOrm2, 0, multiply2, 1);
EXTMEM AudioConnection          patchCord68(WavesL7, envelopeL6);
EXTMEM AudioConnection          patchCord69(WavesL8, envelopeL7);
EXTMEM AudioConnection          patchCord70(WavesL5, envelopeL4);
EXTMEM AudioConnection          patchCord71(WavesL6, envelopeL5);
EXTMEM AudioConnection          patchCord72(WavesL3, envelopeL2);
EXTMEM AudioConnection          patchCord73(WavesL4, envelopeL3);
EXTMEM AudioConnection          patchCord74(WavesL2, envelopeL1);
EXTMEM AudioConnection          patchCord75(WavesL1, envelopeL0);
EXTMEM AudioConnection          patchCord76(LFOrm303, fade1);
EXTMEM AudioConnection          patchCord77(LFOrm303, fade0);
EXTMEM AudioConnection          patchCord78(LFOrm303, fade2);
EXTMEM AudioConnection          patchCord79(LFOrm303, fade3);
EXTMEM AudioConnection          patchCord80(LFOrm303, fade4);
EXTMEM AudioConnection          patchCord81(LFOrm303, fade5);
EXTMEM AudioConnection          patchCord82(LFOrm303, fade6);
EXTMEM AudioConnection          patchCord83(LFOrm303, fade7);
EXTMEM AudioConnection          patchCord84(envelopeL5, 0, mixerWet303L6, 0);
EXTMEM AudioConnection          patchCord85(envelopeL5, wavePAmp5);
EXTMEM AudioConnection          patchCord86(envelopeL2, 0, mixerWet303L3, 0);
EXTMEM AudioConnection          patchCord87(envelopeL2, wavePAmp2);
EXTMEM AudioConnection          patchCord88(envelopeL7, 0, mixerWet303L8, 0);
EXTMEM AudioConnection          patchCord89(envelopeL7, wavePAmp7);
EXTMEM AudioConnection          patchCord90(envelopeL6, 0, mixerWet303L7, 0);
EXTMEM AudioConnection          patchCord91(envelopeL6, wavePAmp6);
EXTMEM AudioConnection          patchCord92(envelopeL3, 0, mixerWet303L4, 0);
EXTMEM AudioConnection          patchCord93(envelopeL3, wavePAmp3);
EXTMEM AudioConnection          patchCord94(envelopeL4, 0, mixerWet303L5, 0);
EXTMEM AudioConnection          patchCord95(envelopeL4, wavePAmp4);
EXTMEM AudioConnection          patchCord96(envelopeL0, wavePAmp0);
EXTMEM AudioConnection          patchCord97(envelopeL0, 0, mixerWet303L1, 0);
EXTMEM AudioConnection          patchCord98(envelopeL1, 0, mixerWet303L2, 0);
EXTMEM AudioConnection          patchCord99(envelopeL1, wavePAmp1);
EXTMEM AudioConnection          patchCord100(fade5, 0, filter303L6, 1);
EXTMEM AudioConnection          patchCord101(fade6, 0, filter303L7, 1);
EXTMEM AudioConnection          patchCord102(fade0, 0, filter303L1, 1);
EXTMEM AudioConnection          patchCord103(wavePAmp6, 0, filter303L7, 0);
EXTMEM AudioConnection          patchCord104(wavePAmp5, 0, filter303L6, 0);
EXTMEM AudioConnection          patchCord105(FlashSampler1, 0, flashmix1, 0);
EXTMEM AudioConnection          patchCord106(FlashSampler2, 0, flashmix1, 1);
EXTMEM AudioConnection          patchCord107(FlashSampler5, 0, flashmix2, 0);
EXTMEM AudioConnection          patchCord108(FlashSampler6, 0, flashmix2, 1);
EXTMEM AudioConnection          patchCord109(FlashSampler4, 0, flashmix1, 3);
EXTMEM AudioConnection          patchCord110(FlashSampler9, 0, flashmix3, 0);
EXTMEM AudioConnection          patchCord111(FlashSampler3, 0, flashmix1, 2);
EXTMEM AudioConnection          patchCord112(FlashSampler10, 0, flashmix3, 1);
EXTMEM AudioConnection          patchCord113(FlashSampler8, 0, flashmix2, 3);
EXTMEM AudioConnection          patchCord114(wavePAmp7, 0, filter303L8, 0);
EXTMEM AudioConnection          patchCord115(FlashSampler7, 0, flashmix2, 2);
EXTMEM AudioConnection          patchCord116(wavePAmp0, 0, filter303L1, 0);
EXTMEM AudioConnection          patchCord117(FlashSampler12, 0, flashmix3, 3);
EXTMEM AudioConnection          patchCord118(FlashSampler13, 0, flashmix4, 0);
EXTMEM AudioConnection          patchCord119(FlashSampler14, 0, flashmix4, 1);
EXTMEM AudioConnection          patchCord120(FlashSampler11, 0, flashmix3, 2);
EXTMEM AudioConnection          patchCord121(FlashSampler16, 0, flashmix4, 3);
EXTMEM AudioConnection          patchCord122(FlashSampler15, 0, flashmix4, 2);
EXTMEM AudioConnection          patchCord123(fade7, 0, filter303L8, 1);
EXTMEM AudioConnection          patchCord124(fade2, 0, filter303L3, 1);
EXTMEM AudioConnection          patchCord125(fade1, 0, filter303L2, 1);
EXTMEM AudioConnection          patchCord126(wavePAmp1, 0, filter303L2, 0);
EXTMEM AudioConnection          patchCord127(fade3, 0, filter303L4, 1);
EXTMEM AudioConnection          patchCord128(wavePAmp2, 0, filter303L3, 0);
EXTMEM AudioConnection          patchCord129(wavePAmp3, 0, filter303L4, 0);
EXTMEM AudioConnection          patchCord130(fade4, 0, filter303L5, 1);
EXTMEM AudioConnection          patchCord131(wavePAmp4, 0, filter303L5, 0);
EXTMEM AudioConnection          patchCord132(filter303L7, 0, mix303L7, 0);
EXTMEM AudioConnection          patchCord133(filter303L7, 1, mix303L7, 1);
EXTMEM AudioConnection          patchCord134(filter303L7, 2, mix303L7, 2);
EXTMEM AudioConnection          patchCord135(filter303L6, 0, mix303L6, 0);
EXTMEM AudioConnection          patchCord136(filter303L6, 1, mix303L6, 1);
EXTMEM AudioConnection          patchCord137(filter303L6, 2, mix303L6, 2);
EXTMEM AudioConnection          patchCord138(filter303L1, 0, mix303L1, 0);
EXTMEM AudioConnection          patchCord139(filter303L1, 1, mix303L1, 1);
EXTMEM AudioConnection          patchCord140(filter303L1, 2, mix303L1, 2);
EXTMEM AudioConnection          patchCord141(filter303L8, 0, mix303L8, 0);
EXTMEM AudioConnection          patchCord142(filter303L8, 1, mix303L8, 1);
EXTMEM AudioConnection          patchCord143(filter303L8, 2, mix303L8, 2);
EXTMEM AudioConnection          patchCord144(filter303L2, 0, mix303L2, 0);
EXTMEM AudioConnection          patchCord145(filter303L2, 1, mix303L2, 1);
EXTMEM AudioConnection          patchCord146(filter303L2, 2, mix303L2, 2);
EXTMEM AudioConnection          patchCord147(filter303L3, 0, mix303L3, 0);
EXTMEM AudioConnection          patchCord148(filter303L3, 1, mix303L3, 1);
EXTMEM AudioConnection          patchCord149(filter303L3, 2, mix303L3, 2);
EXTMEM AudioConnection          patchCord150(filter303L4, 0, mix303L4, 0);
EXTMEM AudioConnection          patchCord151(filter303L4, 1, mix303L4, 1);
EXTMEM AudioConnection          patchCord152(filter303L4, 2, mix303L4, 2);
EXTMEM AudioConnection          patchCord153(filter303L5, 0, mix303L5, 0);
EXTMEM AudioConnection          patchCord154(filter303L5, 1, mix303L5, 1);
EXTMEM AudioConnection          patchCord155(filter303L5, 2, mix303L5, 2);
EXTMEM AudioConnection          patchCord156(flashmix1, 0, flashmixMain, 0);
EXTMEM AudioConnection          patchCord157(flashmix2, 0, flashmixMain, 1);
EXTMEM AudioConnection          patchCord158(flashmix3, 0, flashmixMain, 2);
EXTMEM AudioConnection          patchCord159(flashmix4, 0, flashmixMain, 3);
EXTMEM AudioConnection          patchCord160(mix303L6, 0, mixerWet303L6, 1);
EXTMEM AudioConnection          patchCord161(mix303L7, 0, mixerWet303L7, 1);
EXTMEM AudioConnection          patchCord162(mix303L2, 0, mixerWet303L2, 1);
EXTMEM AudioConnection          patchCord163(mix303L1, 0, mixerWet303L1, 1);
EXTMEM AudioConnection          patchCord164(mix303L8, 0, mixerWet303L8, 1);
EXTMEM AudioConnection          patchCord165(mix303L3, 0, mixerWet303L3, 1);
EXTMEM AudioConnection          patchCord166(mix303L4, 0, mixerWet303L4, 1);
AudioConnection          patchCord167(usb1, 0, InMixL, 0);
AudioConnection          patchCord168(usb1, 1, InMixR, 0);
EXTMEM AudioConnection          patchCord169(mix303L5, 0, mixerWet303L5, 1);
EXTMEM AudioConnection          patchCord170(flashmixMain, 0, flashMastermix, 0);
EXTMEM AudioConnection          patchCord171(mixerWet303L6, 0, mixerWL5to8, 1);
EXTMEM AudioConnection          patchCord172(mixerWet303L2, 0, mixerWL1to4, 1);
EXTMEM AudioConnection          patchCord173(mixerWet303L7, 0, mixerWL5to8, 2);
EXTMEM AudioConnection          patchCord174(mixerWet303L1, 0, mixerWL1to4, 0);
EXTMEM AudioConnection          patchCord175(mixerWet303L3, 0, mixerWL1to4, 2);
EXTMEM AudioConnection          patchCord176(mixerWet303L8, 0, mixerWL5to8, 3);
EXTMEM AudioConnection          patchCord177(mixerWet303L4, 0, mixerWL1to4, 3);
EXTMEM AudioConnection          patchCord178(InMixL, LineInPreAmpL);
EXTMEM AudioConnection          patchCord179(InMixR, LineInPreAmpR);
EXTMEM AudioConnection          patchCord180(mixerWet303L5, 0, mixerWL5to8, 0);
EXTMEM AudioConnection          patchCord181(mixerWL1to4, 0, mixerWAll, 0);
EXTMEM AudioConnection          patchCord182(LineInPreAmpR, 0, MasterR, 2);
EXTMEM AudioConnection          patchCord183(playSdWav1, 0, MasterL, 0);
EXTMEM AudioConnection          patchCord184(playSdWav1, 1, MasterR, 0);
EXTMEM AudioConnection          patchCord185(LineInPreAmpL, 0, MasterL, 2);
EXTMEM AudioConnection          patchCord186(mixerWL5to8, 0, mixerWAll, 1);
EXTMEM AudioConnection          patchCord187(mixerWAll, 0, MasterR, 1);
EXTMEM AudioConnection          patchCord188(mixerWAll, 0, MasterL, 1);
EXTMEM AudioConnection          patchCord189(mixerWAll, 0, FXBusR, 2);
EXTMEM AudioConnection          patchCord190(mixerWAll, 0, FXBusL, 2);
EXTMEM AudioConnection          patchCord191(metrodrum1, 0, MasterL1, 2);
EXTMEM AudioConnection          patchCord192(metrodrum1, 0, MasterR1, 2);
EXTMEM AudioConnection          patchCord193(MasterL, 0, MasterL1, 0);
EXTMEM AudioConnection          patchCord194(MasterR, 0, MasterR1, 0);
EXTMEM AudioConnection          patchCord195(playRawR, 0, MasterR1, 1);
EXTMEM AudioConnection          patchCord196(playRawL, 0, MasterL1, 1);
EXTMEM AudioConnection          patchCord197(FlashRaw, 0, flashMastermix, 1);
EXTMEM AudioConnection          patchCord198(MasterR1, 0, premixMaster, 1);
EXTMEM AudioConnection          patchCord199(MasterR1, 0, WetMixMasterR, 0);
EXTMEM AudioConnection          patchCord200(MasterL1, 0, premixMaster, 0);
EXTMEM AudioConnection          patchCord201(MasterL1, 0, WetMixMasterL, 0);
EXTMEM AudioConnection          patchCord202(flashMastermix, 0, MasterL1, 3);
EXTMEM AudioConnection          patchCord203(flashMastermix, 0, MasterR1, 3);
EXTMEM AudioConnection          patchCord204(flashMastermix, 0, FXBusL, 1);
EXTMEM AudioConnection          patchCord205(flashMastermix, 0, FXBusR, 1);
EXTMEM AudioConnection          patchCord206(filter3, 0, mixfilter3, 0);
EXTMEM AudioConnection          patchCord207(filter3, 1, mixfilter3, 1);
EXTMEM AudioConnection          patchCord208(filter3, 2, mixfilter3, 2);
EXTMEM AudioConnection          patchCord209(filter1, 0, mixfilter1, 0);
EXTMEM AudioConnection          patchCord210(filter1, 1, mixfilter1, 1);
EXTMEM AudioConnection          patchCord211(filter1, 2, mixfilter1, 2);
EXTMEM AudioConnection          patchCord212(filter2, 0, mixfilter2, 0);
EXTMEM AudioConnection          patchCord213(filter2, 1, mixfilter2, 1);
EXTMEM AudioConnection          patchCord214(filter2, 2, mixfilter2, 2);
EXTMEM AudioConnection          patchCord215(WetMixMasterL, 0, premixmixx1, 0);
EXTMEM AudioConnection          patchCord216(WetMixMasterL, 0, premixmixx2, 0);
EXTMEM AudioConnection          patchCord217(WetMixMasterL, 0, premixmixx3, 0);
EXTMEM AudioConnection          patchCord218(WetMixMasterL, 0, FXBusL, 0);
EXTMEM AudioConnection          patchCord219(WetMixMasterR, 0, premixmixx1, 1);
EXTMEM AudioConnection          patchCord220(WetMixMasterR, 0, premixmixx2, 1);
EXTMEM AudioConnection          patchCord221(WetMixMasterR, 0, premixmixx3, 1);
EXTMEM AudioConnection          patchCord222(WetMixMasterR, 0, FXBusR, 0);
EXTMEM AudioConnection          patchCord223(FXBusL, ampL);
EXTMEM AudioConnection          patchCord224(FXBusR, ampR);
EXTMEM AudioConnection          patchCord225(premixmixx2, 0, feedbackdelay2, 1);
EXTMEM AudioConnection          patchCord226(premixmixx3, 0, feedbackdelay3, 1);
EXTMEM AudioConnection          patchCord227(premixmixx1, 0, feedbackdelay1, 1);
EXTMEM AudioConnection          patchCord228(ampR, queue2);
EXTMEM AudioConnection          patchCord229(ampR, 0, audioOutput, 1);
EXTMEM AudioConnection          patchCord230(ampL, queue1);
EXTMEM AudioConnection          patchCord231(ampL, 0, audioOutput, 0);
EXTMEM AudioConnection          patchCord232(ampL, notefreq1);
EXTMEM AudioConnection          patchCord233(feedbackdelay1, delay1);
EXTMEM AudioConnection          patchCord234(feedbackdelay2, delay2);
EXTMEM AudioConnection          patchCord235(feedbackdelay3, delay3);
EXTMEM AudioConnection          patchCord236(delay1, 0, delay1pre1, 0);
EXTMEM AudioConnection          patchCord237(delay1, 1, delay1pre1, 1);
EXTMEM AudioConnection          patchCord238(delay1, 2, delay1pre1, 2);
EXTMEM AudioConnection          patchCord239(delay1, 3, delay1pre1, 3);
EXTMEM AudioConnection          patchCord240(delay1, 4, delay1pre2, 0);
EXTMEM AudioConnection          patchCord241(delay1, 5, delay1pre2, 1);
EXTMEM AudioConnection          patchCord242(delay1, 6, delay1pre2, 2);
EXTMEM AudioConnection          patchCord243(delay1, 7, delay1pre2, 3);
EXTMEM AudioConnection          patchCord244(delay2, 0, delay2pre1, 0);
EXTMEM AudioConnection          patchCord245(delay2, 1, delay2pre1, 1);
EXTMEM AudioConnection          patchCord246(delay2, 2, delay2pre1, 2);
EXTMEM AudioConnection          patchCord247(delay2, 3, delay2pre1, 3);
EXTMEM AudioConnection          patchCord248(delay2, 4, delay2pre2, 0);
EXTMEM AudioConnection          patchCord249(delay2, 5, delay2pre2, 1);
EXTMEM AudioConnection          patchCord250(delay2, 6, delay2pre2, 2);
EXTMEM AudioConnection          patchCord251(delay2, 7, delay2pre2, 3);
EXTMEM AudioConnection          patchCord252(delay3, 0, delay3pre1, 0);
EXTMEM AudioConnection          patchCord253(delay3, 1, delay3pre1, 1);
EXTMEM AudioConnection          patchCord254(delay3, 2, delay3pre1, 2);
EXTMEM AudioConnection          patchCord255(delay3, 3, delay3pre1, 3);
EXTMEM AudioConnection          patchCord256(delay3, 4, delay3pre2, 0);
EXTMEM AudioConnection          patchCord257(delay3, 5, delay3pre2, 1);
EXTMEM AudioConnection          patchCord258(delay3, 6, delay3pre2, 2);
EXTMEM AudioConnection          patchCord259(delay3, 7, delay3pre2, 3);
EXTMEM AudioConnection          patchCord260(delay1pre2, 0, delaymix1, 1);
EXTMEM AudioConnection          patchCord261(delay2pre1, 0, delaymix2, 0);
EXTMEM AudioConnection          patchCord262(delay3pre1, 0, delaymix3, 0);
EXTMEM AudioConnection          patchCord263(delay2pre2, 0, delaymix2, 1);
EXTMEM AudioConnection          patchCord264(delay3pre2, 0, delaymix3, 1);
EXTMEM AudioConnection          patchCord265(delay1pre1, 0, delaymix1, 0);
AudioControlSGTL5000     audioShield;    //xy=4117.999984741211,580.832950592041
// GUItool: end automatically generated code

