#pragma once
#include <stdint.h>

#define MULTIPLEXED_PADS 1

//(6 * AUDIO_BLOCK_SAMPLES)
constexpr uint16_t FLANGE_DELAY_LENGTH = 768 ;

//(16 * AUDIO_BLOCK_SAMPLES)
constexpr uint16_t  CHORUS_DELAY_LENGTH = 2048;

// 12800 is for 290 ms at 44.1 kHz
constexpr uint16_t  GRANULAR_MEMORY_SIZE = 12800;

constexpr uint8_t  SCREEN_WIDTH = 128;
constexpr uint8_t  SCREEN_HEIGHT = 64;
constexpr uint8_t  SDCARD_CS_PIN = 10;
constexpr uint8_t  SDCARD_MOSI_PIN = 7;
constexpr uint8_t  SDCARD_SCK_PIN = 14;
constexpr uint8_t  MULTIPLEXER_PIN = 32;
constexpr uint8_t  NO_CCREC_SIZE = 11;
constexpr uint8_t  ALL_BUTTONS = 49;
constexpr uint8_t  OSCS_COUNT = 3;
constexpr uint8_t  FXS_COUNT = 3;
constexpr uint8_t  STAGES_BQ = 4;
//9 * FXS_COUNT;
constexpr uint8_t  PMIX_DM_SIZE = 27;
//9 * FXS_COUNT * 2 * 3
constexpr uint8_t  FXCORDS_SIZE = 162;
constexpr uint16_t  SCREEN_ADDRESS = 0x3C;
constexpr uint8_t  SN_MENU_LABELS_COUNT = 6;
constexpr uint8_t  SYNTH_LINERS_COUNT = 6;
constexpr uint8_t  TK_TYPES = 2;
constexpr uint8_t  FLASH_LINERS_COUNT = 16;
constexpr uint8_t  SP_LABELS_COUNT = 4;
constexpr uint8_t  PBARS = 32;
constexpr uint8_t  ALL_FX_TYPES = 10;
constexpr uint8_t  SP_NAME_MAX = 26;
constexpr uint8_t  ARP_TYPES = 8;
constexpr uint8_t  VBUT_LBL_COUNT = 8;
constexpr uint8_t  NUM_BARS = 64;
constexpr uint8_t  SSD1306_BLACK = 0;
constexpr uint8_t  SSD1306_WHITE = 1;
constexpr uint8_t  SSD1306_INVERSE = 2;
constexpr uint8_t  ARP_LINES = 6;

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
