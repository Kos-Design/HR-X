#pragma once

#include "MenuClasses.h"

class LFOMenuRouter : public SectionHolder {
    public:
        LFOMenuRouter();
        int unit = 1;
        int tenth = 0;
        int hundredth = 0;
        const byte sizeofLFOlabels = 9;

        static void show();
        static void applyLFOrmicon(int lesinthy);
        static void LFOrmType();
        static void displayLFOrmimg(int letype, char *lelabelw, const unsigned char img[],int leLFO, int wavetype);
        static void doLFObool();
        static void gobacktolfoparams();
        static void doLFOparamdisplayval(int laval);
        static void draw_lfo_val(float laval);
        static void doLFOlevel();
        static void doLFOoffset();
        static void doLFOphase();
        static void freqbars_panel_selector();
        static void freqbars_panel_action();
        static void displayfreqbars();
        static void freqbars_panel();
        static void dolistLFOparams();
        static void doLFOallcontrols(byte leLFO);
        static void go_to_synth();
        static void go_previous();
        static void go_next();
        static void restartLFO(int leLFO);
        static void LFOlining();
        static void printLFObanner(int startx, int starty, int leLFO);
        static void LFOlineBG();
        static void lfo_zero();
    private:

        static constexpr void (*_route_nav[9])() = {
            &LFOrmType,
            &doLFOlevel,
            &doLFObool,
            &freqbars_panel,
            &doLFOoffset,
            &doLFOphase,
            &go_to_synth,
            &go_previous,
            &go_next
        };
        static constexpr void (*_nav_lfo[7])() = {&lfo_zero, &LFOlining,&LFOlining,&LFOlining,
                          &LFOlining,&LFOlining,&LFOlining};
        static LFOMenuRouter* self;
};

extern LFOMenuRouter _lf;