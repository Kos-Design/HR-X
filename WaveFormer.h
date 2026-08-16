#pragma once

#include "MenuClasses.h"
#include "FilesLister.h"

class WaveformsMenuRouter : public SectionHolder {
    public:
       
        WaveformsMenuRouter();

        FilesLister *catalog;
        static constexpr uint8_t fake_gauss_kernel[17] = {
              0,   2,   5,  11,
            22,  40,  66, 100,
            140, 185, 220, 240,
            250, 253, 254, 255,
            255
        };
        static const byte wf_labels_count = 8;
        static const byte wfn_size = 6; //displayables lines
        static const byte max_blur = 32 ;

        int cw_change = 64;
        int w_cursor_y = 32;
        int w_cursor_x = 0;
        String wforms_names[wfn_size];
        byte wforms_indexes[99];
        byte wforms_count = 0 ;
        byte widx = 0 ;

        byte wforms_names_offset = 0 ;
        byte trace_wave_cc = 58 ;
        byte x_axis_cc = 17 ;
        byte y_axis_cc = 18 ;
        bool trace_waveform = false;


        byte *waveform_tracers[3]= {&x_axis_cc,&y_axis_cc,&trace_wave_cc};

        static void show();
        static void waveforms_nav_zero();

        static void set_tracer(byte control,byte value);
        static void WaveformParams();
        static void set_y_cursor_value(byte la_val);
        static void blur_w_graph_region(int16_t *arr, int index, uint8_t intensity);
        static void blur_w_graph_boundary( int16_t *arr,int range);
        static void smooth_w_bounds();
        static void smooth_w_graph();
        static void set_array_at_cursor(int c_pos_w=self->w_cursor_x);
        static void set_x_cursor_value(byte la_val);

        static void draw_wave_graph();

        static void WaveformEditer();
        static void wforms_menu();
        static void go_previous();
        static void go_next();
        static void writewaveform();
        static void writewaveforms(File &filer);
        static void copywaveform();
        static void deletewaveform();
        static void parsewaveformfile();
        
        static void wforms_actions();
        static void remove_wform();
        static void duplicate_wform();

        static void load_wform();
        static void save_wform();

        static void lv1_wrapper(void (*func)());

        static constexpr void (*_route_nav[7])() = {&waveforms_nav_zero, &wforms_actions, &wforms_actions,
                                    &wforms_actions, &wforms_actions, &wforms_actions, &wforms_actions};
        
        static constexpr void  (*_nav_wforms[8])() = {&save_wform, &load_wform, &duplicate_wform,&remove_wform,
                                                                    &WaveformEditer ,&go_next,&go_previous,&WaveformParams};
  
    private:
        static WaveformsMenuRouter* self;
};

extern WaveformsMenuRouter _wf;
