
EXTMEM AudioConnection premixMtom1(MasterL1, 0, multiply1, 0);
EXTMEM AudioConnection premixMtom2(MasterL1, 0, multiply2, 0);
EXTMEM AudioConnection premixMtom3(MasterL1, 0, multiply3, 0);
EXTMEM AudioConnection premixMtog1(MasterL1, 0, granular1, 0);
EXTMEM AudioConnection premixMtog2(MasterL1, 0, granular2, 0);
EXTMEM AudioConnection premixMtog3(MasterL1, 0, granular3, 0);
EXTMEM AudioConnection premixMtobt1(MasterL1, 0, bitcrusher1, 0);
EXTMEM AudioConnection premixMtobt2(MasterL1, 0, bitcrusher2, 0);
EXTMEM AudioConnection premixMtobt3(MasterL1, 0, bitcrusher3, 0);
EXTMEM AudioConnection premixMtorev1(MasterL1, 0, freeverbs1, 0);
EXTMEM AudioConnection premixMtorev2(MasterL1, 0, freeverbs2, 0);
EXTMEM AudioConnection premixMtorev3(MasterL1, 0, freeverbs3, 0);
EXTMEM AudioConnection premixMtofl1(MasterL1, 0, flange1, 0);
EXTMEM AudioConnection premixMtofl2(MasterL1, 0, flange2, 0);
EXTMEM AudioConnection premixMtofl3(MasterL1, 0, flange3, 0);
EXTMEM AudioConnection premixMtoch1(MasterL1, 0, chorus1, 0);
EXTMEM AudioConnection premixMtoch2(MasterL1, 0, chorus2, 0);
EXTMEM AudioConnection premixMtoch3(MasterL1, 0, chorus3, 0);
EXTMEM AudioConnection premixMtoff1(MasterL1, 0, filter1, 0);
EXTMEM AudioConnection premixMtobq1(MasterL1, 0, biquad1, 0);
EXTMEM AudioConnection premixMtobq2(MasterL1, 0, biquad2, 0);
EXTMEM AudioConnection premixMtobq3(MasterL1, 0, biquad3, 0);
EXTMEM AudioConnection premixMtoff2(MasterL1, 0, filter2, 0);
EXTMEM AudioConnection premixMtoff3(MasterL1, 0, filter3, 0);
EXTMEM AudioConnection premixMtode1(MasterL1, 0, feedbackdelay1, 0);
EXTMEM AudioConnection premixMtode2(MasterL1, 0, feedbackdelay2, 0);
EXTMEM AudioConnection premixMtode3(MasterL1, 0, feedbackdelay3, 0);

EXTMEM AudioConnection premixMtom1R(MasterR1, 0, multiply1R, 0);
EXTMEM AudioConnection premixMtom2R(MasterR1, 0, multiply2R, 0);
EXTMEM AudioConnection premixMtom3R(MasterR1, 0, multiply3R, 0);
EXTMEM AudioConnection premixMtog1R(MasterR1, 0, granular1R, 0);
EXTMEM AudioConnection premixMtog2R(MasterR1, 0, granular2R, 0);
EXTMEM AudioConnection premixMtog3R(MasterR1, 0, granular3R, 0);
EXTMEM AudioConnection premixMtobt1R(MasterR1, 0, bitcrusher1R, 0);
EXTMEM AudioConnection premixMtobt2R(MasterR1, 0, bitcrusher2R, 0);
EXTMEM AudioConnection premixMtobt3R(MasterR1, 0, bitcrusher3R, 0);
EXTMEM AudioConnection premixMtorev1R(MasterR1, 0, freeverbs1R, 0);
EXTMEM AudioConnection premixMtorev2R(MasterR1, 0, freeverbs2R, 0);
EXTMEM AudioConnection premixMtorev3R(MasterR1, 0, freeverbs3R, 0);
EXTMEM AudioConnection premixMtofl1R(MasterR1, 0, flange1R, 0);
EXTMEM AudioConnection premixMtofl2R(MasterR1, 0, flange2R, 0);
EXTMEM AudioConnection premixMtofl3R(MasterR1, 0, flange3R, 0);
EXTMEM AudioConnection premixMtoch1R(MasterR1, 0, chorus1R, 0);
EXTMEM AudioConnection premixMtoch2R(MasterR1, 0, chorus2R, 0);
EXTMEM AudioConnection premixMtoch3R(MasterR1, 0, chorus3R, 0);
EXTMEM AudioConnection premixMtoff1R(MasterR1, 0, filter1R, 0);
EXTMEM AudioConnection premixMtobq1R(MasterR1, 0, biquad1R, 0);
EXTMEM AudioConnection premixMtobq2R(MasterR1, 0, biquad2R, 0);
EXTMEM AudioConnection premixMtobq3R(MasterR1, 0, biquad3R, 0);
EXTMEM AudioConnection premixMtoff2R(MasterR1, 0, filter2R, 0);
EXTMEM AudioConnection premixMtoff3R(MasterR1, 0, filter3R, 0);
EXTMEM AudioConnection premixMtode1R(MasterR1, 0, feedbackdelay1R, 0);
EXTMEM AudioConnection premixMtode2R(MasterR1, 0, feedbackdelay2R, 0);
EXTMEM AudioConnection premixMtode3R(MasterR1, 0, feedbackdelay3R, 0);

EXTMEM AudioConnection mul1towetL1(multiply1, 0, WetMixMasterL, 1);
EXTMEM AudioConnection mul1towetR1(multiply1R, 0, WetMixMasterR, 1);
EXTMEM AudioConnection mul2towetL1(multiply2, 0, WetMixMasterL, 1);
EXTMEM AudioConnection mul2towetR1(multiply2R, 0, WetMixMasterR, 1);
EXTMEM AudioConnection mul3towetL1(multiply3, 0, WetMixMasterL, 1);
EXTMEM AudioConnection mul3towetR1(multiply3R, 0, WetMixMasterR, 1);

EXTMEM AudioConnection mul1towetL2(multiply1, 0, WetMixMasterL, 2);
EXTMEM AudioConnection mul1towetR2(multiply1R, 0, WetMixMasterR, 2);
EXTMEM AudioConnection mul2towetL2(multiply2, 0, WetMixMasterL, 2);
EXTMEM AudioConnection mul2towetR2(multiply2R, 0, WetMixMasterR, 2);
EXTMEM AudioConnection mul3towetL2(multiply3, 0, WetMixMasterL, 2);
EXTMEM AudioConnection mul3towetR2(multiply3R, 0, WetMixMasterR, 2);

EXTMEM AudioConnection mul1towetL3(multiply1, 0, WetMixMasterL, 3);
EXTMEM AudioConnection mul1towetR3(multiply1R, 0, WetMixMasterR, 3);
EXTMEM AudioConnection mul2towetL3(multiply2, 0, WetMixMasterL, 3);
EXTMEM AudioConnection mul2towetR3(multiply2R, 0, WetMixMasterR, 3);
EXTMEM AudioConnection mul3towetL3(multiply3, 0, WetMixMasterL, 3);
EXTMEM AudioConnection mul3towetR3(multiply3R, 0, WetMixMasterR, 3);


EXTMEM AudioConnection g1towetL1(granular1, 0, WetMixMasterL, 1);
EXTMEM AudioConnection g1towetR1(granular1R, 0, WetMixMasterR, 1);
EXTMEM AudioConnection g2towetL1(granular2, 0, WetMixMasterL, 1);
EXTMEM AudioConnection g2towetR1(granular2R, 0, WetMixMasterR, 1);
EXTMEM AudioConnection g3towetL1(granular3, 0, WetMixMasterL, 1);
EXTMEM AudioConnection g3towetR1(granular3R, 0, WetMixMasterR, 1);

EXTMEM AudioConnection g1towetL2(granular1, 0, WetMixMasterL, 2);
EXTMEM AudioConnection g1towetR2(granular1R, 0, WetMixMasterR, 2);
EXTMEM AudioConnection g2towetL2(granular2, 0, WetMixMasterL, 2);
EXTMEM AudioConnection g2towetR2(granular2R, 0, WetMixMasterR, 2);
EXTMEM AudioConnection g3towetL2(granular3, 0, WetMixMasterL, 2);
EXTMEM AudioConnection g3towetR2(granular3R, 0, WetMixMasterR, 2);

EXTMEM AudioConnection g1towetL3(granular1, 0, WetMixMasterL, 3);
EXTMEM AudioConnection g1towetR3(granular1R, 0, WetMixMasterR, 3);
EXTMEM AudioConnection g2towetL3(granular2, 0, WetMixMasterL, 3);
EXTMEM AudioConnection g2towetR3(granular2R, 0, WetMixMasterR, 3);
EXTMEM AudioConnection g3towetL3(granular3, 0, WetMixMasterL, 3);
EXTMEM AudioConnection g3towetR3(granular3R, 0, WetMixMasterR, 3);


EXTMEM AudioConnection bt1towetL1(bitcrusher1, 0, WetMixMasterL, 1);
EXTMEM AudioConnection bt1towetR1(bitcrusher1R, 0, WetMixMasterR, 1);
EXTMEM AudioConnection bt2towetL1(bitcrusher2, 0, WetMixMasterL, 1);
EXTMEM AudioConnection bt2towetR1(bitcrusher2R, 0, WetMixMasterR, 1);
EXTMEM AudioConnection bt3towetL1(bitcrusher3, 0, WetMixMasterL, 1);
EXTMEM AudioConnection bt3towetR1(bitcrusher3R, 0, WetMixMasterR, 1);

EXTMEM AudioConnection bt1towetL2(bitcrusher1, 0, WetMixMasterL, 2);
EXTMEM AudioConnection bt1towetR2(bitcrusher1R, 0, WetMixMasterR, 2);
EXTMEM AudioConnection bt2towetL2(bitcrusher2, 0, WetMixMasterL, 2);
EXTMEM AudioConnection bt2towetR2(bitcrusher2R, 0, WetMixMasterR, 2);
EXTMEM AudioConnection bt3towetL2(bitcrusher3, 0, WetMixMasterL, 2);
EXTMEM AudioConnection bt3towetR2(bitcrusher3R, 0, WetMixMasterR, 2);

EXTMEM AudioConnection bt1towetL3(bitcrusher1, 0, WetMixMasterL, 3);
EXTMEM AudioConnection bt1towetR3(bitcrusher1R, 0, WetMixMasterR, 3);
EXTMEM AudioConnection bt2towetL3(bitcrusher2, 0, WetMixMasterL, 3);
EXTMEM AudioConnection bt2towetR3(bitcrusher2R, 0, WetMixMasterR, 3);
EXTMEM AudioConnection bt3towetL3(bitcrusher3, 0, WetMixMasterL, 3);
EXTMEM AudioConnection bt3towetR3(bitcrusher3R, 0, WetMixMasterR, 3);


EXTMEM AudioConnection rev1towetL1(freeverbs1, 0, WetMixMasterL, 1);
EXTMEM AudioConnection rev1towetR1(freeverbs1R, 0, WetMixMasterR, 1);
EXTMEM AudioConnection rev2towetL1(freeverbs2, 0, WetMixMasterL, 1);
EXTMEM AudioConnection rev2towetR1(freeverbs2R, 0, WetMixMasterR, 1);
EXTMEM AudioConnection rev3towetL1(freeverbs3, 0, WetMixMasterL, 1);
EXTMEM AudioConnection rev3towetR1(freeverbs3R, 0, WetMixMasterR, 1);

EXTMEM AudioConnection rev1towetL2(freeverbs1, 0, WetMixMasterL, 2);
EXTMEM AudioConnection rev1towetR2(freeverbs1R, 0, WetMixMasterR, 2);
EXTMEM AudioConnection rev2towetL2(freeverbs2, 0, WetMixMasterL, 2);
EXTMEM AudioConnection rev2towetR2(freeverbs2R, 0, WetMixMasterR, 2);
EXTMEM AudioConnection rev3towetL2(freeverbs3, 0, WetMixMasterL, 2);
EXTMEM AudioConnection rev3towetR2(freeverbs3R, 0, WetMixMasterR, 2);

EXTMEM AudioConnection rev1towetL3(freeverbs1, 0, WetMixMasterL, 3);
EXTMEM AudioConnection rev1towetR3(freeverbs1R, 0, WetMixMasterR, 3);
EXTMEM AudioConnection rev2towetL3(freeverbs2, 0, WetMixMasterL, 3);
EXTMEM AudioConnection rev2towetR3(freeverbs2R, 0, WetMixMasterR, 3);
EXTMEM AudioConnection rev3towetL3(freeverbs3, 0, WetMixMasterL, 3);
EXTMEM AudioConnection rev3towetR3(freeverbs3R, 0, WetMixMasterR, 3);


AudioConnection fl1towetL1(flange1, 0, WetMixMasterL, 1);
AudioConnection fl1towetR1(flange1R, 0, WetMixMasterR, 1);
AudioConnection fl2towetL1(flange2, 0, WetMixMasterL, 1);
AudioConnection fl2towetR1(flange2R, 0, WetMixMasterR, 1);
AudioConnection fl3towetL1(flange3, 0, WetMixMasterL, 1);
AudioConnection fl3towetR1(flange3R, 0, WetMixMasterR, 1);

EXTMEM AudioConnection fl1towetL2(flange1, 0, WetMixMasterL, 2);
EXTMEM AudioConnection fl1towetR2(flange1R, 0, WetMixMasterR, 2);
EXTMEM AudioConnection fl2towetL2(flange2, 0, WetMixMasterL, 2);
EXTMEM AudioConnection fl2towetR2(flange2R, 0, WetMixMasterR, 2);
EXTMEM AudioConnection fl3towetL2(flange3, 0, WetMixMasterL, 2);
EXTMEM AudioConnection fl3towetR2(flange3R, 0, WetMixMasterR, 2);

EXTMEM AudioConnection fl1towetL3(flange1, 0, WetMixMasterL, 3);
EXTMEM AudioConnection fl1towetR3(flange1R, 0, WetMixMasterR, 3);
EXTMEM AudioConnection fl2towetL3(flange2, 0, WetMixMasterL, 3);
EXTMEM AudioConnection fl2towetR3(flange2R, 0, WetMixMasterR, 3);
EXTMEM AudioConnection fl3towetL3(flange3, 0, WetMixMasterL, 3);
EXTMEM AudioConnection fl3towetR3(flange3R, 0, WetMixMasterR, 3);


EXTMEM AudioConnection ch1towetL1(chorus1, 0, WetMixMasterL, 1);
EXTMEM AudioConnection ch1towetR1(chorus1R, 0, WetMixMasterR, 1);
EXTMEM AudioConnection ch2towetL1(chorus2, 0, WetMixMasterL, 1);
EXTMEM AudioConnection ch2towetR1(chorus2R, 0, WetMixMasterR, 1);
EXTMEM AudioConnection ch3towetL1(chorus3, 0, WetMixMasterL, 1);
EXTMEM AudioConnection ch3towetR1(chorus3R, 0, WetMixMasterR, 1);

EXTMEM AudioConnection ch1towetL2(chorus1, 0, WetMixMasterL, 2);
EXTMEM AudioConnection ch1towetR2(chorus1R, 0, WetMixMasterR, 2);
EXTMEM AudioConnection ch2towetL2(chorus2, 0, WetMixMasterL, 2);
EXTMEM AudioConnection ch2towetR2(chorus2R, 0, WetMixMasterR, 2);
EXTMEM AudioConnection ch3towetL2(chorus3, 0, WetMixMasterL, 2);
EXTMEM AudioConnection ch3towetR2(chorus3R, 0, WetMixMasterR, 2);

EXTMEM AudioConnection ch1towetL3(chorus1, 0, WetMixMasterL, 3);
EXTMEM AudioConnection ch1towetR3(chorus1R, 0, WetMixMasterR, 3);
EXTMEM AudioConnection ch2towetL3(chorus2, 0, WetMixMasterL, 3);
EXTMEM AudioConnection ch2towetR3(chorus2R, 0, WetMixMasterR, 3);
EXTMEM AudioConnection ch3towetL3(chorus3, 0, WetMixMasterL, 3);
EXTMEM AudioConnection ch3towetR3(chorus3R, 0, WetMixMasterR, 3);

EXTMEM AudioConnection bq1towetL1(biquad1, 0, WetMixMasterL, 1);
EXTMEM AudioConnection bq1towetR1(biquad1R, 0, WetMixMasterR, 1);
EXTMEM AudioConnection bq2towetL1(biquad2, 0, WetMixMasterL, 1);
EXTMEM AudioConnection bq2towetR1(biquad2R, 0, WetMixMasterR, 1);
EXTMEM AudioConnection bq3towetL1(biquad3, 0, WetMixMasterL, 1);
EXTMEM AudioConnection bq3towetR1(biquad3R, 0, WetMixMasterR, 1);

EXTMEM AudioConnection bq1towetL2(biquad1, 0, WetMixMasterL, 2);
EXTMEM AudioConnection bq1towetR2(biquad1R, 0, WetMixMasterR, 2);
EXTMEM AudioConnection bq2towetL2(biquad2, 0, WetMixMasterL, 2);
EXTMEM AudioConnection bq2towetR2(biquad2R, 0, WetMixMasterR, 2);
EXTMEM AudioConnection bq3towetL2(biquad3, 0, WetMixMasterL, 2);
EXTMEM AudioConnection bq3towetR2(biquad3R, 0, WetMixMasterR, 2);

EXTMEM AudioConnection bq1towetL3(biquad1, 0, WetMixMasterL, 3);
EXTMEM AudioConnection bq1towetR3(biquad1R, 0, WetMixMasterR, 3);
EXTMEM AudioConnection bq2towetL3(biquad2, 0, WetMixMasterL, 3);
EXTMEM AudioConnection bq2towetR3(biquad2R, 0, WetMixMasterR, 3);
EXTMEM AudioConnection bq3towetL3(biquad3, 0, WetMixMasterL, 3);
EXTMEM AudioConnection bq3towetR3(biquad3R, 0, WetMixMasterR, 3);


EXTMEM AudioConnection ff1towetL1(mixfilter1, 0, WetMixMasterL, 1);
EXTMEM AudioConnection ff1towetR1(mixfilter1R, 0, WetMixMasterR, 1);
EXTMEM AudioConnection ff2towetL1(mixfilter2, 0, WetMixMasterL, 1);
EXTMEM AudioConnection ff2towetR1(mixfilter2R, 0, WetMixMasterR, 1);
EXTMEM AudioConnection ff3towetL1(mixfilter3, 0, WetMixMasterL, 1);
EXTMEM AudioConnection ff3towetR1(mixfilter3R, 0, WetMixMasterR, 1);

EXTMEM AudioConnection ff1towetL2(mixfilter1, 0, WetMixMasterL, 2);
EXTMEM AudioConnection ff1towetR2(mixfilter1R, 0, WetMixMasterR, 2);
EXTMEM AudioConnection ff2towetL2(mixfilter2, 0, WetMixMasterL, 2);
EXTMEM AudioConnection ff2towetR2(mixfilter2R, 0, WetMixMasterR, 2);
EXTMEM AudioConnection ff3towetL2(mixfilter3, 0, WetMixMasterL, 2);
EXTMEM AudioConnection ff3towetR2(mixfilter3R, 0, WetMixMasterR, 2);

EXTMEM AudioConnection ff1towetL3(mixfilter1, 0, WetMixMasterL, 3);
EXTMEM AudioConnection ff1towetR3(mixfilter1R, 0, WetMixMasterR, 3);
EXTMEM AudioConnection ff2towetL3(mixfilter2, 0, WetMixMasterL, 3);
EXTMEM AudioConnection ff2towetR3(mixfilter2R, 0, WetMixMasterR, 3);
EXTMEM AudioConnection ff3towetL3(mixfilter3, 0, WetMixMasterL, 3);
EXTMEM AudioConnection ff3towetR3(mixfilter3R, 0, WetMixMasterR, 3);

EXTMEM AudioConnection de1towetL1(delaymix1, 0, WetMixMasterL, 1);
EXTMEM AudioConnection de1towetR1(delaymix1R, 0, WetMixMasterR, 1);
EXTMEM AudioConnection de2towetL1(delaymix2, 0, WetMixMasterL, 1);
EXTMEM AudioConnection de2towetR1(delaymix2R, 0, WetMixMasterR, 1);
EXTMEM AudioConnection de3towetL1(delaymix3, 0, WetMixMasterL, 1);
EXTMEM AudioConnection de3towetR1(delaymix3R, 0, WetMixMasterR, 1);

EXTMEM AudioConnection de1towetL2(delaymix1, 0, WetMixMasterL, 2);
EXTMEM AudioConnection de1towetR2(delaymix1R, 0, WetMixMasterR, 2);
EXTMEM AudioConnection de2towetL2(delaymix2, 0, WetMixMasterL, 2);
EXTMEM AudioConnection de2towetR2(delaymix2R, 0, WetMixMasterR, 2);
EXTMEM AudioConnection de3towetL2(delaymix3, 0, WetMixMasterL, 2);
EXTMEM AudioConnection de3towetR2(delaymix3R, 0, WetMixMasterR, 2);

EXTMEM AudioConnection de1towetL3(delaymix1, 0, WetMixMasterL, 3);
EXTMEM AudioConnection de1towetR3(delaymix1R, 0, WetMixMasterR, 3);
EXTMEM AudioConnection de2towetL3(delaymix2, 0, WetMixMasterL, 3);
EXTMEM AudioConnection de2towetR3(delaymix2R, 0, WetMixMasterR, 3);
EXTMEM AudioConnection de3towetL3(delaymix3, 0, WetMixMasterL, 3);
EXTMEM AudioConnection de3towetR3(delaymix3R, 0, WetMixMasterR, 3);

EXTMEM AudioConnection LFO1toFilter1(LFOrm1, 0, filter1, 1);
EXTMEM AudioConnection LFO1toFilter2(LFOrm1, 0, filter2, 1);
EXTMEM AudioConnection LFO1toFilter3(LFOrm1, 0, filter3, 1);

EXTMEM AudioConnection LFO2toFilter1(LFOrm2, 0, filter1, 1);
EXTMEM AudioConnection LFO2toFilter2(LFOrm2, 0, filter2, 1);
EXTMEM AudioConnection LFO2toFilter3(LFOrm2, 0, filter3, 1);

EXTMEM AudioConnection LFO3toFilter1(LFOrm3, 0, filter1, 1);
EXTMEM AudioConnection LFO3toFilter2(LFOrm3, 0, filter2, 1);
EXTMEM AudioConnection LFO3toFilter3(LFOrm3, 0, filter3, 1);

EXTMEM AudioConnection LFO1toFilter1R(LFOrm1, 0, filter1R, 1);
EXTMEM AudioConnection LFO1toFilter2R(LFOrm1, 0, filter2R, 1);
EXTMEM AudioConnection LFO1toFilter3R(LFOrm1, 0, filter3R, 1);

EXTMEM AudioConnection LFO2toFilter1R(LFOrm2, 0, filter1R, 1);
EXTMEM AudioConnection LFO2toFilter2R(LFOrm2, 0, filter2R, 1);
EXTMEM AudioConnection LFO2toFilter3R(LFOrm2, 0, filter3R, 1);

EXTMEM AudioConnection LFO3toFilter1R(LFOrm3, 0, filter1R, 1);
EXTMEM AudioConnection LFO3toFilter2R(LFOrm3, 0, filter2R, 1);
EXTMEM AudioConnection LFO3toFilter3R(LFOrm3, 0, filter3R, 1);

AudioConnection *premixesMtoR[sizeopremixtoM] = {
    &premixMtom1R,   &premixMtom2R,   &premixMtom3R,  &premixMtorev1R,
    &premixMtorev2R, &premixMtorev3R, &premixMtog1R,  &premixMtog2R,
    &premixMtog3R,   &premixMtobt1R,  &premixMtobt2R, &premixMtobt3R,
    &premixMtofl1R,  &premixMtofl2R,  &premixMtofl3R, &premixMtoch1R,
    &premixMtoch2R,  &premixMtoch3R,  &premixMtobq1R, &premixMtobq2R,
    &premixMtobq3R,  &premixMtoff1R,  &premixMtoff2R, &premixMtoff3R,
    &premixMtode1R,  &premixMtode2R,  &premixMtode3R};

AudioConnection *premixesMto[sizeopremixtoM] = {
    &premixMtom1,   &premixMtom2,   &premixMtom3,  &premixMtorev1,
    &premixMtorev2, &premixMtorev3, &premixMtog1,  &premixMtog2,
    &premixMtog3,   &premixMtobt1,  &premixMtobt2, &premixMtobt3,
    &premixMtofl1,  &premixMtofl2,  &premixMtofl3, &premixMtoch1,
    &premixMtoch2,  &premixMtoch3,  &premixMtobq1, &premixMtobq2,
    &premixMtobq3,  &premixMtoff1,  &premixMtoff2, &premixMtoff3,
    &premixMtode1,  &premixMtode2,  &premixMtode3};

AudioConnection *LFOtoFilterz[fxs_count * fxs_count] = {
    &LFO1toFilter1, &LFO2toFilter1, &LFO3toFilter1,
    &LFO1toFilter2, &LFO2toFilter2, &LFO3toFilter2,
    &LFO1toFilter3, &LFO2toFilter3, &LFO3toFilter3};

AudioConnection *LFOtoFilterzR[fxs_count * fxs_count] = {
    &LFO1toFilter1R, &LFO2toFilter1R, &LFO3toFilter1R,
    &LFO1toFilter2R, &LFO2toFilter2R, &LFO3toFilter2R,
    &LFO1toFilter3R, &LFO2toFilter3R, &LFO3toFilter3R};

AudioConnection *fxcording[sizeofxcords] = {
    &mul1towetL1, &mul1towetR1, &mul2towetL1, &mul2towetR1, &mul3towetL1,
    &mul3towetR1, &mul1towetL2, &mul1towetR2, &mul2towetL2, &mul2towetR2,
    &mul3towetL2, &mul3towetR2, &mul1towetL3, &mul1towetR3, &mul2towetL3,
    &mul2towetR3, &mul3towetL3, &mul3towetR3, &rev1towetL1, &rev1towetR1,
    &rev2towetL1, &rev2towetR1, &rev3towetL1, &rev3towetR1, &rev1towetL2,
    &rev1towetR2, &rev2towetL2, &rev2towetR2, &rev3towetL2, &rev3towetR2,
    &rev1towetL3, &rev1towetR3, &rev2towetL3, &rev2towetR3, &rev3towetL3,
    &rev3towetR3, &g1towetL1,   &g1towetR1,   &g2towetL1,   &g2towetR1,
    &g3towetL1,   &g3towetR1,   &g1towetL2,   &g1towetR2,   &g2towetL2,
    &g2towetR2,   &g3towetL2,   &g3towetR2,   &g1towetL3,   &g1towetR3,
    &g2towetL3,   &g2towetR3,   &g3towetL3,   &g3towetR3,   &bt1towetL1,
    &bt1towetR1,  &bt2towetL1,  &bt2towetR1,  &bt3towetL1,  &bt3towetR1,
    &bt1towetL2,  &bt1towetR2,  &bt2towetL2,  &bt2towetR2,  &bt3towetL2,
    &bt3towetR2,  &bt1towetL3,  &bt1towetR3,  &bt2towetL3,  &bt2towetR3,
    &bt3towetL3,  &bt3towetR3,  &fl1towetL1,  &fl1towetR1,  &fl2towetL1,
    &fl2towetR1,  &fl3towetL1,  &fl3towetR1,  &fl1towetL2,  &fl1towetR2,
    &fl2towetL2,  &fl2towetR2,  &fl3towetL2,  &fl3towetR2,  &fl1towetL3,
    &fl1towetR3,  &fl2towetL3,  &fl2towetR3,  &fl3towetL3,  &fl3towetR3,
    &ch1towetL1,  &ch1towetR1,  &ch2towetL1,  &ch2towetR1,  &ch3towetL1,
    &ch3towetR1,  &ch1towetL2,  &ch1towetR2,  &ch2towetL2,  &ch2towetR2,
    &ch3towetL2,  &ch3towetR2,  &ch1towetL3,  &ch1towetR3,  &ch2towetL3,
    &ch2towetR3,  &ch3towetL3,  &ch3towetR3,  &bq1towetL1,  &bq1towetR1,
    &bq2towetL1,  &bq2towetR1,  &bq3towetL1,  &bq3towetR1,  &bq1towetL2,
    &bq1towetR2,  &bq2towetL2,  &bq2towetR2,  &bq3towetL2,  &bq3towetR2,
    &bq1towetL3,  &bq1towetR3,  &bq2towetL3,  &bq2towetR3,  &bq3towetL3,
    &bq3towetR3,  &ff1towetL1,  &ff1towetR1,  &ff2towetL1,  &ff2towetR1,
    &ff3towetL1,  &ff3towetR1,  &ff1towetL2,  &ff1towetR2,  &ff2towetL2,
    &ff2towetR2,  &ff3towetL2,  &ff3towetR2,  &ff1towetL3,  &ff1towetR3,
    &ff2towetL3,  &ff2towetR3,  &ff3towetL3,  &ff3towetR3,  &de1towetL1,
    &de1towetR1,  &de2towetL1,  &de2towetR1,  &de3towetL1,  &de3towetR1,
    &de1towetL2,  &de1towetR2,  &de2towetL2,  &de2towetR2,  &de3towetL2,
    &de3towetR2,  &de1towetL3,  &de1towetR3,  &de2towetL3,  &de2towetR3,
    &de3towetL3,  &de3towetR3

};

AudioEffectMultiply *multiply[fxs_count] = {&multiply1, &multiply2, &multiply3};
AudioEffectMultiply *multiplyR[fxs_count] = {&multiply1R, &multiply2R, &multiply3R};

AudioEffectGranular *granular[fxs_count] = {&granular1, &granular2, &granular3};
AudioEffectGranular *granularR[fxs_count] = {&granular1R, &granular2R, &granular3R};


AudioEffectFlange *flange[fxs_count] = {&flange1, &flange2, &flange3};
AudioEffectFlange *flangeR[fxs_count] = {&flange1R, &flange2R, &flange3R};


AudioEffectChorus *chorus[fxs_count] = {&chorus1, &chorus2, &chorus3};
AudioEffectChorus *chorusR[fxs_count] = {&chorus1, &chorus2R, &chorus3R};

AudioEffectBitcrusher *bitcrusher[fxs_count] = {&bitcrusher1, &bitcrusher2, &bitcrusher3};
AudioEffectBitcrusher *bitcrusherR[fxs_count] = {&bitcrusher1R, &bitcrusher2R, &bitcrusher3R};

AudioFilterStateVariable *filterz[fxs_count] = {&filter1, &filter2, &filter3};
AudioFilterStateVariable *filterzR[fxs_count] = {&filter1R, &filter2R, &filter3R};

AudioFilterBiquad *biquad[fxs_count] = {&biquad1, &biquad2, &biquad3};
AudioFilterBiquad *biquadR[fxs_count] = {&biquad1R, &biquad2R, &biquad3R};

AudioEffectReverb *freeverbs[fxs_count] = {&freeverbs1, &freeverbs2, &freeverbs3};
AudioEffectReverb *freeverbsR[fxs_count] = {&freeverbs1R, &freeverbs2R, &freeverbs3R};

AudioEffectDelay *lesdelays[fxs_count] = {&delay1, &delay2, &delay3};
AudioEffectDelay *lesdelaysR[fxs_count] = {&delay1R, &delay2R, &delay3R};

AudioMixer4 *mixfilter[fxs_count] = {&mixfilter1, &mixfilter2, &mixfilter3};
AudioMixer4 *mixfilterR[fxs_count] = {&mixfilter1R, &mixfilter2R, &mixfilter3R};

AudioMixer4 *delaypremix[fxs_count * 2] = {&delay1pre1, &delay1pre2,
                                              &delay2pre1, &delay2pre2,
                                              &delay3pre1, &delay3pre2};
AudioMixer4 *delaypremixR[fxs_count * 2] = {&delay1pre1R, &delay1pre2R,
                                              &delay2pre1R, &delay2pre2R,
                                              &delay3pre1R, &delay3pre2R};

AudioMixer4 *delayfeedbackmix[fxs_count] = {&feedbackdelay1, &feedbackdelay2, &feedbackdelay3};
AudioMixer4 *delayfeedbackmixR[fxs_count] = {&feedbackdelay1R, &feedbackdelay2R, &feedbackdelay3R};

AudioMixer4 *delaypostmix[fxs_count] = {&delaymix1, &delaymix2, &delaymix3};
AudioMixer4 *delaypostmixR[fxs_count] = {&delaymix1R, &delaymix2R, &delaymix3R};

AudioConnection *delayCords[3] = {&delayCord1, &delayCord2, &delayCord3};
AudioConnection *delayCordsR[3] = {&delayCord1R, &delayCord2R, &delayCord3R};

//AudioAmplifier *faders[SYNTH_LINERS_COUNT] = {&fade0, &fade1, &fade2, &fade3, &fade4, &fade5};


AudioMixer4 *les303passes[SYNTH_LINERS_COUNT] = {&mix303L1, &mix303L2, &mix303L3, &mix303L4, &mix303L5, &mix303L6};

AudioMixer4 *les303wet[SYNTH_LINERS_COUNT] = {&mixerWet303L1, &mixerWet303L2, &mixerWet303L3,
                             &mixerWet303L4, &mixerWet303L5, &mixerWet303L6};

AudioFilterStateVariable *les303filterz[SYNTH_LINERS_COUNT] = {
    &filter303L1, &filter303L2, &filter303L3, &filter303L4, &filter303L5, &filter303L6};
