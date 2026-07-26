

int fakeselector(float smallv, int maxrange) {
  return round(map(smallv, 0, 1, 0, maxrange));
}
//I'm joking somehow, best to derive that from an isEven module
void toggle_that(bool &booler){
  booler = !booler;
}
int oscillisc_timee = 8;
uint8_t osc_framerate = 33 ;
uint8_t osc_refresher_period = 5 ;

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

void stop_spectro(byte unused_cc){
  if (!showing_oscilloscope) return ;

  showing_oscilloscope = false ;
  queue1.end();
  queue1.clear();
}

void start_spectro(byte unused_cc){
  if (showing_oscilloscope) return ;
  queue1.begin();
  showing_oscilloscope = true ;
  
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

#define NUM_BARS    16
#define SCREEN_H    64


float bars[NUM_BARS];
float displayBars[NUM_BARS];
float peaks[NUM_BARS];

const float bandFreq[17] = {
    20, 60, 120, 200,
    320, 500, 750, 1100,
    1600, 2300, 3300, 4700,
    6700, 9500, 13000, 17000,
    22000
};

void UpdateSpectrum(){
  
  if (!showing_eq || !fft256.available()) return;
    
    for (int b = 0; b < 16; b++)
    {
        float level = fft256.read(bandFreq[b], bandFreq[b+1]);

        // Progressive high-frequency boost
        //level *= (1.0f + b * 0.12f);
        level *= sqrtf((float)(b + 1));

        // Smooth
        displayBars[b] = displayBars[b] * 0.75f + level * 0.25f;

        float db = 20.0f * log10f(level + 1e-6f);

        db += 70.0f;          // Shift into visible range

        if (db < 0) db = 0;
        if (db > 63) db = 63;

        bars[b] = db;

        // Peak hold
        if (db > peaks[b])
            peaks[b] = db;
        else if (peaks[b] > 0)
            peaks[b] -= 0.5f;
    }

    DrawSpectrum();
}

void DrawSpectrum()
{
    display.clearDisplay();

    for(int b=0;b<NUM_BARS;b++)
    {
        int x = b * 8;
        int h = (int)bars[b];

        display.fillRect(x, SCREEN_H - h, 7, h, WHITE);

        int py = SCREEN_H - (int)peaks[b];

        display.drawFastHLine( x, py, 7,WHITE);
    }

    display.display();
}