#pragma once
#include <stdint.h>

#define MULTIPLEXED_PADS 1

//(6 * AUDIO_BLOCK_SAMPLES)
#define FLANGE_DELAY_LENGTH 768

//(16 * AUDIO_BLOCK_SAMPLES)
#define CHORUS_DELAY_LENGTH 2048

// 12800 is for 290 ms at 44.1 kHz
#define GRANULAR_MEMORY_SIZE 12800

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 7
#define SDCARD_SCK_PIN 14
#define MULTIPLEXER_PIN 32
#define NO_CCREC_SIZE 11
#define ALL_BUTTONS 49
#define OSCS_COUNT 3
#define FXS_COUNT 3
#define STAGES_BQ 4
//9 * FXS_COUNT;
#define PMIX_DM_SIZE 27
//9 * FXS_COUNT * 2 * 3
#define FXCORDS_SIZE 162
#define SCREEN_ADDRESS 0x3C
#define SN_MENU_LABELS_COUNT 6
#define SYNTH_LINERS_COUNT 6
#define TK_TYPES 2
#define FLASH_LINERS_COUNT 16
#define SP_LABELS_COUNT 4
#define PBARS 32
#define ALL_FX_TYPES 10
#define SP_NAME_MAX 26
#define ARP_TYPES 8
#define VBUT_LBL_COUNT 8
#define NUM_BARS 64
#define SSD1306_BLACK 0
#define SSD1306_WHITE 1
#define SSD1306_INVERSE 2

struct MidiEventer{
    uint8_t channel;
    uint8_t note;
    uint8_t velocity;
};

enum TrackTypes : uint8_t  {
    Synth,
    Flash
};

enum GlideMode : uint8_t {
    Off,
    Portamento,
    ReversePortamento,
    PitchAttack,
    ReversePitchAttack
};

enum ADSR : uint8_t  {
    AttackDelay,
    Attack,
    Hold,
    Decay,
    Sustain,
    Release
};
