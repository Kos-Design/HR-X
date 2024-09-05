
AudioConnection premixMtom1(premixMaster, 0, multiply1, 0);
AudioConnection premixMtom2(premixMaster, 0, multiply2, 0);
AudioConnection premixMtom3(premixMaster, 0, multiply3, 0);

AudioConnection mul1towetL1(multiply1, 0, WetMixMasterL, 1);
AudioConnection mul1towetR1(multiply1, 0, WetMixMasterR, 1);
AudioConnection mul2towetL1(multiply2, 0, WetMixMasterL, 1);
AudioConnection mul2towetR1(multiply2, 0, WetMixMasterR, 1);
AudioConnection mul3towetL1(multiply3, 0, WetMixMasterL, 1);
AudioConnection mul3towetR1(multiply3, 0, WetMixMasterR, 1);

AudioConnection mul1towetL2(multiply1, 0, WetMixMasterL, 2);
AudioConnection mul1towetR2(multiply1, 0, WetMixMasterR, 2);
AudioConnection mul2towetL2(multiply2, 0, WetMixMasterL, 2);
AudioConnection mul2towetR2(multiply2, 0, WetMixMasterR, 2);
AudioConnection mul3towetL2(multiply3, 0, WetMixMasterL, 2);
AudioConnection mul3towetR2(multiply3, 0, WetMixMasterR, 2);

AudioConnection mul1towetL3(multiply1, 0, WetMixMasterL, 3);
AudioConnection mul1towetR3(multiply1, 0, WetMixMasterR, 3);
AudioConnection mul2towetL3(multiply2, 0, WetMixMasterL, 3);
AudioConnection mul2towetR3(multiply2, 0, WetMixMasterR, 3);
AudioConnection mul3towetL3(multiply3, 0, WetMixMasterL, 3);
AudioConnection mul3towetR3(multiply3, 0, WetMixMasterR, 3);

AudioConnection premixMtog1(premixMaster, 0, granular1, 0);
AudioConnection premixMtog2(premixMaster, 0, granular2, 0);
AudioConnection premixMtog3(premixMaster, 0, granular3, 0);

AudioConnection g1towetL1(granular1, 0, WetMixMasterL, 1);
AudioConnection g1towetR1(granular1, 0, WetMixMasterR, 1);
AudioConnection g2towetL1(granular2, 0, WetMixMasterL, 1);
AudioConnection g2towetR1(granular2, 0, WetMixMasterR, 1);
AudioConnection g3towetL1(granular3, 0, WetMixMasterL, 1);
AudioConnection g3towetR1(granular3, 0, WetMixMasterR, 1);

AudioConnection g1towetL2(granular1, 0, WetMixMasterL, 2);
AudioConnection g1towetR2(granular1, 0, WetMixMasterR, 2);
AudioConnection g2towetL2(granular2, 0, WetMixMasterL, 2);
AudioConnection g2towetR2(granular2, 0, WetMixMasterR, 2);
AudioConnection g3towetL2(granular3, 0, WetMixMasterL, 2);
AudioConnection g3towetR2(granular3, 0, WetMixMasterR, 2);

AudioConnection g1towetL3(granular1, 0, WetMixMasterL, 3);
AudioConnection g1towetR3(granular1, 0, WetMixMasterR, 3);
AudioConnection g2towetL3(granular2, 0, WetMixMasterL, 3);
AudioConnection g2towetR3(granular2, 0, WetMixMasterR, 3);
AudioConnection g3towetL3(granular3, 0, WetMixMasterL, 3);
AudioConnection g3towetR3(granular3, 0, WetMixMasterR, 3);

AudioConnection premixMtobt1(premixMaster, 0, bitcrusher1, 0);
AudioConnection premixMtobt2(premixMaster, 0, bitcrusher2, 0);
AudioConnection premixMtobt3(premixMaster, 0, bitcrusher3, 0);

AudioConnection bt1towetL1(bitcrusher1, 0, WetMixMasterL, 1);
AudioConnection bt1towetR1(bitcrusher1, 0, WetMixMasterR, 1);
AudioConnection bt2towetL1(bitcrusher2, 0, WetMixMasterL, 1);
AudioConnection bt2towetR1(bitcrusher2, 0, WetMixMasterR, 1);
AudioConnection bt3towetL1(bitcrusher3, 0, WetMixMasterL, 1);
AudioConnection bt3towetR1(bitcrusher3, 0, WetMixMasterR, 1);

AudioConnection bt1towetL2(bitcrusher1, 0, WetMixMasterL, 2);
AudioConnection bt1towetR2(bitcrusher1, 0, WetMixMasterR, 2);
AudioConnection bt2towetL2(bitcrusher2, 0, WetMixMasterL, 2);
AudioConnection bt2towetR2(bitcrusher2, 0, WetMixMasterR, 2);
AudioConnection bt3towetL2(bitcrusher3, 0, WetMixMasterL, 2);
AudioConnection bt3towetR2(bitcrusher3, 0, WetMixMasterR, 2);

AudioConnection bt1towetL3(bitcrusher1, 0, WetMixMasterL, 3);
AudioConnection bt1towetR3(bitcrusher1, 0, WetMixMasterR, 3);
AudioConnection bt2towetL3(bitcrusher2, 0, WetMixMasterL, 3);
AudioConnection bt2towetR3(bitcrusher2, 0, WetMixMasterR, 3);
AudioConnection bt3towetL3(bitcrusher3, 0, WetMixMasterL, 3);
AudioConnection bt3towetR3(bitcrusher3, 0, WetMixMasterR, 3);

AudioConnection premixMtorev1(premixMaster, 0, freeverbs1, 0);
AudioConnection premixMtorev2(premixMaster, 0, freeverbs2, 0);
AudioConnection premixMtorev3(premixMaster, 0, freeverbs3, 0);

AudioConnection rev1towetL1(freeverbs1, 0, WetMixMasterL, 1);
AudioConnection rev1towetR1(freeverbs1, 0, WetMixMasterR, 1);
AudioConnection rev2towetL1(freeverbs2, 0, WetMixMasterL, 1);
AudioConnection rev2towetR1(freeverbs2, 0, WetMixMasterR, 1);
AudioConnection rev3towetL1(freeverbs3, 0, WetMixMasterL, 1);
AudioConnection rev3towetR1(freeverbs3, 0, WetMixMasterR, 1);

AudioConnection rev1towetL2(freeverbs1, 0, WetMixMasterL, 2);
AudioConnection rev1towetR2(freeverbs1, 0, WetMixMasterR, 2);
AudioConnection rev2towetL2(freeverbs2, 0, WetMixMasterL, 2);
AudioConnection rev2towetR2(freeverbs2, 0, WetMixMasterR, 2);
AudioConnection rev3towetL2(freeverbs3, 0, WetMixMasterL, 2);
AudioConnection rev3towetR2(freeverbs3, 0, WetMixMasterR, 2);

AudioConnection rev1towetL3(freeverbs1, 0, WetMixMasterL, 3);
AudioConnection rev1towetR3(freeverbs1, 0, WetMixMasterR, 3);
AudioConnection rev2towetL3(freeverbs2, 0, WetMixMasterL, 3);
AudioConnection rev2towetR3(freeverbs2, 0, WetMixMasterR, 3);
AudioConnection rev3towetL3(freeverbs3, 0, WetMixMasterL, 3);
AudioConnection rev3towetR3(freeverbs3, 0, WetMixMasterR, 3);

AudioConnection premixMtofl1(premixMaster, 0, flange1, 0);
AudioConnection premixMtofl2(premixMaster, 0, flange2, 0);
AudioConnection premixMtofl3(premixMaster, 0, flange3, 0);

AudioConnection fl1towetL1(flange1, 0, WetMixMasterL, 1);
AudioConnection fl1towetR1(flange1, 0, WetMixMasterR, 1);
AudioConnection fl2towetL1(flange2, 0, WetMixMasterL, 1);
AudioConnection fl2towetR1(flange2, 0, WetMixMasterR, 1);
AudioConnection fl3towetL1(flange3, 0, WetMixMasterL, 1);
AudioConnection fl3towetR1(flange3, 0, WetMixMasterR, 1);

AudioConnection fl1towetL2(flange1, 0, WetMixMasterL, 2);
AudioConnection fl1towetR2(flange1, 0, WetMixMasterR, 2);
AudioConnection fl2towetL2(flange2, 0, WetMixMasterL, 2);
AudioConnection fl2towetR2(flange2, 0, WetMixMasterR, 2);
AudioConnection fl3towetL2(flange3, 0, WetMixMasterL, 2);
AudioConnection fl3towetR2(flange3, 0, WetMixMasterR, 2);

AudioConnection fl1towetL3(flange1, 0, WetMixMasterL, 3);
AudioConnection fl1towetR3(flange1, 0, WetMixMasterR, 3);
AudioConnection fl2towetL3(flange2, 0, WetMixMasterL, 3);
AudioConnection fl2towetR3(flange2, 0, WetMixMasterR, 3);
AudioConnection fl3towetL3(flange3, 0, WetMixMasterL, 3);
AudioConnection fl3towetR3(flange3, 0, WetMixMasterR, 3);

AudioConnection premixMtoch1(premixMaster, 0, chorus1, 0);
AudioConnection premixMtoch2(premixMaster, 0, chorus2, 0);
AudioConnection premixMtoch3(premixMaster, 0, chorus3, 0);

AudioConnection ch1towetL1(chorus1, 0, WetMixMasterL, 1);
AudioConnection ch1towetR1(chorus1, 0, WetMixMasterR, 1);
AudioConnection ch2towetL1(chorus2, 0, WetMixMasterL, 1);
AudioConnection ch2towetR1(chorus2, 0, WetMixMasterR, 1);
AudioConnection ch3towetL1(chorus3, 0, WetMixMasterL, 1);
AudioConnection ch3towetR1(chorus3, 0, WetMixMasterR, 1);

AudioConnection ch1towetL2(chorus1, 0, WetMixMasterL, 2);
AudioConnection ch1towetR2(chorus1, 0, WetMixMasterR, 2);
AudioConnection ch2towetL2(chorus2, 0, WetMixMasterL, 2);
AudioConnection ch2towetR2(chorus2, 0, WetMixMasterR, 2);
AudioConnection ch3towetL2(chorus3, 0, WetMixMasterL, 2);
AudioConnection ch3towetR2(chorus3, 0, WetMixMasterR, 2);

AudioConnection ch1towetL3(chorus1, 0, WetMixMasterL, 3);
AudioConnection ch1towetR3(chorus1, 0, WetMixMasterR, 3);
AudioConnection ch2towetL3(chorus2, 0, WetMixMasterL, 3);
AudioConnection ch2towetR3(chorus2, 0, WetMixMasterR, 3);
AudioConnection ch3towetL3(chorus3, 0, WetMixMasterL, 3);
AudioConnection ch3towetR3(chorus3, 0, WetMixMasterR, 3);

AudioConnection premixMtobq1(premixMaster, 0, biquad1, 0);
AudioConnection premixMtobq2(premixMaster, 0, biquad2, 0);
AudioConnection premixMtobq3(premixMaster, 0, biquad3, 0);

AudioConnection bq1towetL1(biquad1, 0, WetMixMasterL, 1);
AudioConnection bq1towetR1(biquad1, 0, WetMixMasterR, 1);
AudioConnection bq2towetL1(biquad2, 0, WetMixMasterL, 1);
AudioConnection bq2towetR1(biquad2, 0, WetMixMasterR, 1);
AudioConnection bq3towetL1(biquad3, 0, WetMixMasterL, 1);
AudioConnection bq3towetR1(biquad3, 0, WetMixMasterR, 1);

AudioConnection bq1towetL2(biquad1, 0, WetMixMasterL, 2);
AudioConnection bq1towetR2(biquad1, 0, WetMixMasterR, 2);
AudioConnection bq2towetL2(biquad2, 0, WetMixMasterL, 2);
AudioConnection bq2towetR2(biquad2, 0, WetMixMasterR, 2);
AudioConnection bq3towetL2(biquad3, 0, WetMixMasterL, 2);
AudioConnection bq3towetR2(biquad3, 0, WetMixMasterR, 2);

AudioConnection bq1towetL3(biquad1, 0, WetMixMasterL, 3);
AudioConnection bq1towetR3(biquad1, 0, WetMixMasterR, 3);
AudioConnection bq2towetL3(biquad2, 0, WetMixMasterL, 3);
AudioConnection bq2towetR3(biquad2, 0, WetMixMasterR, 3);
AudioConnection bq3towetL3(biquad3, 0, WetMixMasterL, 3);
AudioConnection bq3towetR3(biquad3, 0, WetMixMasterR, 3);

AudioConnection premixMtoff1(premixMaster, 0, filter1, 0);
AudioConnection premixMtoff2(premixMaster, 0, filter2, 0);
AudioConnection premixMtoff3(premixMaster, 0, filter3, 0);

AudioConnection ff1towetL1(mixfilter1, 0, WetMixMasterL, 1);
AudioConnection ff1towetR1(mixfilter1, 0, WetMixMasterR, 1);
AudioConnection ff2towetL1(mixfilter2, 0, WetMixMasterL, 1);
AudioConnection ff2towetR1(mixfilter2, 0, WetMixMasterR, 1);
AudioConnection ff3towetL1(mixfilter3, 0, WetMixMasterL, 1);
AudioConnection ff3towetR1(mixfilter3, 0, WetMixMasterR, 1);

AudioConnection ff1towetL2(mixfilter1, 0, WetMixMasterL, 2);
AudioConnection ff1towetR2(mixfilter1, 0, WetMixMasterR, 2);
AudioConnection ff2towetL2(mixfilter2, 0, WetMixMasterL, 2);
AudioConnection ff2towetR2(mixfilter2, 0, WetMixMasterR, 2);
AudioConnection ff3towetL2(mixfilter3, 0, WetMixMasterL, 2);
AudioConnection ff3towetR2(mixfilter3, 0, WetMixMasterR, 2);

AudioConnection ff1towetL3(mixfilter1, 0, WetMixMasterL, 3);
AudioConnection ff1towetR3(mixfilter1, 0, WetMixMasterR, 3);
AudioConnection ff2towetL3(mixfilter2, 0, WetMixMasterL, 3);
AudioConnection ff2towetR3(mixfilter2, 0, WetMixMasterR, 3);
AudioConnection ff3towetL3(mixfilter3, 0, WetMixMasterL, 3);
AudioConnection ff3towetR3(mixfilter3, 0, WetMixMasterR, 3);

AudioConnection premixMtode1(premixMaster, 0, feedbackdelay1, 0);
AudioConnection premixMtode2(premixMaster, 0, feedbackdelay2, 0);
AudioConnection premixMtode3(premixMaster, 0, feedbackdelay3, 0);

AudioConnection de1towetL1(delaymix1, 0, WetMixMasterL, 1);
AudioConnection de1towetR1(delaymix1, 0, WetMixMasterR, 1);
AudioConnection de2towetL1(delaymix2, 0, WetMixMasterL, 1);
AudioConnection de2towetR1(delaymix2, 0, WetMixMasterR, 1);
AudioConnection de3towetL1(delaymix3, 0, WetMixMasterL, 1);
AudioConnection de3towetR1(delaymix3, 0, WetMixMasterR, 1);

AudioConnection de1towetL2(delaymix1, 0, WetMixMasterL, 2);
AudioConnection de1towetR2(delaymix1, 0, WetMixMasterR, 2);
AudioConnection de2towetL2(delaymix2, 0, WetMixMasterL, 2);
AudioConnection de2towetR2(delaymix2, 0, WetMixMasterR, 2);
AudioConnection de3towetL2(delaymix3, 0, WetMixMasterL, 2);
AudioConnection de3towetR2(delaymix3, 0, WetMixMasterR, 2);

AudioConnection de1towetL3(delaymix1, 0, WetMixMasterL, 3);
AudioConnection de1towetR3(delaymix1, 0, WetMixMasterR, 3);
AudioConnection de2towetL3(delaymix2, 0, WetMixMasterL, 3);
AudioConnection de2towetR3(delaymix2, 0, WetMixMasterR, 3);
AudioConnection de3towetL3(delaymix3, 0, WetMixMasterL, 3);
AudioConnection de3towetR3(delaymix3, 0, WetMixMasterR, 3);

AudioConnection LFO1toFilter1(LFOrm1, 0, filter1, 1);
AudioConnection LFO1toFilter2(LFOrm1, 0, filter2, 1);
AudioConnection LFO1toFilter3(LFOrm1, 0, filter3, 1);

AudioConnection LFO2toFilter1(LFOrm2, 0, filter1, 1);
AudioConnection LFO2toFilter2(LFOrm2, 0, filter2, 1);
AudioConnection LFO2toFilter3(LFOrm2, 0, filter3, 1);

AudioConnection LFO3toFilter1(LFOrm3, 0, filter1, 1);
AudioConnection LFO3toFilter2(LFOrm3, 0, filter2, 1);
AudioConnection LFO3toFilter3(LFOrm3, 0, filter3, 1);

AudioConnection *premixesMto[sizeopremixtoM] = {

    &premixMtom1,   &premixMtom2,   &premixMtom3,  &premixMtorev1,
    &premixMtorev2, &premixMtorev3, &premixMtog1,  &premixMtog2,
    &premixMtog3,   &premixMtobt1,  &premixMtobt2, &premixMtobt3,
    &premixMtofl1,  &premixMtofl2,  &premixMtofl3, &premixMtoch1,
    &premixMtoch2,  &premixMtoch3,  &premixMtobq1, &premixMtobq2,
    &premixMtobq3,  &premixMtoff1,  &premixMtoff2, &premixMtoff3,
    &premixMtode1,  &premixMtode2,  &premixMtode3};

AudioConnection *LFOtoFilterz[fxiterations * fxiterations] = {
    &LFO1toFilter1, &LFO2toFilter1, &LFO3toFilter1,
    &LFO1toFilter2, &LFO2toFilter2, &LFO3toFilter2,
    &LFO1toFilter3, &LFO2toFilter3, &LFO3toFilter3};

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

AudioEffectMultiply *multiply[fxiterations] = {&multiply1, &multiply2, &multiply3};

AudioEffectGranular *granular[fxiterations] = {&granular1, &granular2, &granular3};

AudioEffectFlange *flange[fxiterations] = {&flange1, &flange2, &flange3};

AudioEffectChorus *chorus[fxiterations] = {&chorus1, &chorus2, &chorus3};

AudioEffectBitcrusher *bitcrusher[fxiterations] = {&bitcrusher1, &bitcrusher2, &bitcrusher3};

AudioFilterStateVariable *filterz[fxiterations] = {&filter1, &filter2, &filter3};

AudioFilterBiquad *biquad[fxiterations] = {&biquad1, &biquad2, &biquad3};

AudioEffectFreeverb *freeverbs[fxiterations] = {&freeverbs1, &freeverbs2, &freeverbs3};

AudioEffectDelay *lesdelays[fxiterations] = {&delay1, &delay2, &delay3};

AudioMixer4 *mixfilter[fxiterations] = {&mixfilter1, &mixfilter2, &mixfilter3};

AudioMixer4 *delaypremix[fxiterations * 2] = {&delay1pre1, &delay1pre2,
                                              &delay2pre1, &delay2pre2,
                                              &delay3pre1, &delay3pre2};

AudioMixer4 *delayfeedbackmix[fxiterations] = {&feedbackdelay1, &feedbackdelay2, &feedbackdelay3};

AudioMixer4 *delaypostmix[fxiterations] = {&delaymix1, &delaymix2, &delaymix3};

AudioMixer4 *delayprefeed[fxiterations] = {&premixmixx1, &premixmixx2, &premixmixx3};

//AudioAmplifier *faders[nombreofliners] = {&fade0, &fade1, &fade2, &fade3, &fade4, &fade5};

//AudioSynthWaveformSine *lfosinez[fxiterations] = {&lfosine1, &lfosine2, &lfosine3};

AudioMixer4 *les303passes[nombreofliners] = {&mix303L1, &mix303L2, &mix303L3, &mix303L4, &mix303L5, &mix303L6};

AudioMixer4 *les303wet[nombreofliners] = {&mixerWet303L1, &mixerWet303L2, &mixerWet303L3,
                             &mixerWet303L4, &mixerWet303L5, &mixerWet303L6};

AudioFilterStateVariable *les303filterz[nombreofliners] = {
    &filter303L1, &filter303L2, &filter303L3, &filter303L4, &filter303L5, &filter303L6};
