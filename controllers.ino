

int fakeselector(float smallv, int maxrange) {
  return round(map(smallv, 0, 1, 0, maxrange));
}
//I'm joking somehow, best to derive that from an isEven module
void toggle_that(bool &booler){
  booler = !booler;
}

elapsedMillis frameTimer;
int16_t rolling_queue_buff[128];
uint8_t queue_shift = 0;
int last_y_peak ;
bool showing_oscilloscope = false ;

void display_oscilloscope(){
  display.clearDisplay();
  for (int x = 0; x < 128; x++) {

    int index = (queue_shift + x) & 127;

    //int y = map(rolling_queue_buff[index], -32768, 32767, 63, 0);
    //dirty scalling
    int y = map(rolling_queue_buff[index], -12768, 12767, 63, 0);

    if (x > 0)
        display.drawLine(
            x - 1, last_y_peak,
            x, y,
            SSD1306_WHITE);

    last_y_peak = y;
  }
  display.display();
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

        for (int i = 0; i < 128; i += 8) {

            rolling_queue_buff[queue_shift] = samples[i];
            queue_shift = (queue_shift + 1) & 127;
        }

        queue1.freeBuffer();
    }

    if (frameTimer >= 33) {

        display_oscilloscope();

        frameTimer = 0;
    }
}