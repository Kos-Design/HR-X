

int fakeselector(float smallv, int maxrange) {
  return round(map(smallv, 0, 1, 0, maxrange));
}
//I'm joking somehow, best to derive that from an isEven module
void toggle_that(bool &booler){
  booler = !booler;
}
int oscillisc_timee = 8;
uint8_t osc_framerate = 33 ;
uint8_t osc_refresher_period = 3 ;

elapsedMillis frameTimer;
int16_t rolling_queue_buff[128];
uint8_t queue_shift = 0;
int last_y_peak ;
bool showing_oscilloscope = false ;

void display_oscilloscope(){
  dm.clear_buffs();
  for (int x = 0; x < 128; x++) {

    int index = (queue_shift + x) & 127;

    //int y = map(rolling_queue_buff[index], -32768, 32767, 63, 0);
    //dirty scalling
    int y = map(rolling_queue_buff[index], -32768/4, 32767/4, 0, 63);

    if (x > 0)
        canvasBIG.drawLine(
            x - 1, last_y_peak,
            x, y,
            SSD1306_WHITE);

    last_y_peak = y;
  }
  display.clearDisplay();

  dm.dodisplay();
}

void stop_spectro(){
  queue1.end();
  queue1.clear();
}

void start_spectro(){
  queue1.begin();
}

void oscilloscope_loop() {
    if (!showing_oscilloscope) return;
    while (queue1.available()) {

        int16_t *samples = queue1.readBuffer();

        for (int i = 0; i < 128; i += oscillisc_timee) {

            rolling_queue_buff[queue_shift] = samples[i];
            queue_shift = (queue_shift + 1) & 127;
        }

        queue1.freeBuffer();
    }

    if (frameTimer >= osc_framerate) {

        display_oscilloscope();

        frameTimer = 0;
    }
}

#define NUM_BARS 64
#define SCREEN_H 64
float displayBars[NUM_BARS];
uint8_t bars[NUM_BARS];
const uint8_t dbScale[65] = {
     0,  8, 12, 15, 18, 20, 22, 24,
    26, 28, 30, 31, 33, 34, 36, 37,
    38, 39, 41, 42, 43, 44, 45, 46,
    47, 48, 49, 50, 51, 52, 53, 54,
    55, 55, 56, 57, 58, 58, 59, 60,
    60, 61, 61, 62, 62, 62, 63, 63,
    63, 63, 63, 63, 63, 63, 63, 63,
    63, 63, 63, 63, 63, 63, 63, 63,
    63
};
float fftGain[NUM_BARS] = {
    // bass
    
   // bass
    15.0f,17.7f,45.82f,58.825f,
    65.2f,92.575f,98.6f,106.92f,
    
    117.12f,127.255f,136.5f,
    144.71f,151.9f,157.95f,
    
    163.15f,167.25f,180.0f,181.47f,
    181.94f,181.44f,180.0f, 193.8f,

    // upper mids
   200.5f, 206.9f, 213.0f, 218.8f,
   224.3f, 229.5f, 234.4f, 239.0f,

    // presence
   243.2f, 247.1f, 250.6f, 253.8f,
   256.6f, 259.0f, 260.9f, 262.5f,

    // highs
   263.6f, 264.3f, 264.6f, 264.5f,
   263.9f, 262.9f, 261.5f, 259.7f,

    // air
    240.0f, 249.6f, 259.3f, 269.3f,
    279.5f, 289.8f, 300.3f, 311.1f,
    
    322.0f, 333.1f, 344.4f, 355.9f,
    367.5f, 379.4f, 391.4f, 403.6f
};

void UpdateSpectrum(){
  if (!showing_eq || !fft256.available())
      return;
  for (int i = 0; i < NUM_BARS; i++) {
        float level = fft256.read(i + 1);
        level *= fftGain[i];
        // simple smoothing
        displayBars[i] = displayBars[i] * 0.75f + level * 0.25f;
        int h = displayBars[i] * 80.0f;
        if (h > 63) h = 63;
        if (h < 0)  h = 0;
        bars[i] = h;
    }
    DrawSpectrum64();
}

void DrawSpectrum64(){
    display.clearDisplay();

    for (int i = 0; i < 64; i++)
    {
        int h = bars[i];
        display.drawFastVLine(
            i * 2,
            SCREEN_H - h,
            h,
            WHITE);
    }

    display.display();
}