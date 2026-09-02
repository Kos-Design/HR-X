#pragma once
#include "MenuClasses.h"
#include "FilesLister.h"

class PresetsMenuRouter {
    public:
        PresetsMenuRouter();
        FilesLister *catalog;
        static constexpr byte ps_labels_count = 5;
        static void copypreset();
        static void route_navlevel();
        static void presets_nav_zero();
        static void show();
        static void presets_menu();
        static void write_preset();
        static void read_preset();
        static void preset();
        static void deletepreset();
        static void setbpms();
        static void remove_preset();
        static void duplicate_preset();
        static void load_preset();
        static void save_preset();
        static void params_presets();
        static void lv1_wrapper(void (*func)());
        //arbitrary depth of 5, don't go further
        static constexpr void (*_route_nav[5])() = {&presets_nav_zero, &route_navlevel, &route_navlevel, &route_navlevel, &route_navlevel};
        static constexpr void (*_nav_presets[5])() = {&save_preset,&load_preset,&duplicate_preset,&remove_preset,&params_presets};
  private:
    static PresetsMenuRouter* self;
};

extern PresetsMenuRouter _ps;
