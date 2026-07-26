
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

AudioPlaySerialflashRaw *FlashSampler[16] = {
    &FlashSampler1,  &FlashSampler2,  &FlashSampler3,  &FlashSampler4,
    &FlashSampler5,  &FlashSampler6,  &FlashSampler7,  &FlashSampler8,
    &FlashSampler9,  &FlashSampler10, &FlashSampler11, &FlashSampler12,
    &FlashSampler13, &FlashSampler14, &FlashSampler15, &FlashSampler16};

AudioMixer4 *Flashmixer[4] = {&flashmix1, &flashmix2, &flashmix3, &flashmix4};

AudioAmplifier *Wavespreamp303[SYNTH_LINERS_COUNT] = {&wavePAmp0, &wavePAmp1, &wavePAmp2,
                                     &wavePAmp3, &wavePAmp4, &wavePAmp5};

AudioSynthWaveform *LFOwaveforms1[OSCS_COUNT] = {&LFOrm1, &LFOrm2, &LFOrm3};

AudioEffectEnvelope *enveloppesL[SYNTH_LINERS_COUNT] = {&envelopeL0, &envelopeL1, &envelopeL2,
                                                     &envelopeL3, &envelopeL4, &envelopeL5};


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

SequencerClocker clocker;

class ClockSink : public AudioStream {
    public:
        ClockSink() : AudioStream(1, inputQueueArray) {}

        void update(void) override {}

    private:
    audio_block_t *inputQueueArray[1];
};

EXTMEM ClockSink sink;

EXTMEM AudioConnection patchCord_sinker(clocker, 0, sink, 0);