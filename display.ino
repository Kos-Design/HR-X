
void setupscreen() {

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Screen SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  display.display();
  display.setCursor(0, 0);
  display.setTextSize(1.5);
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();
}


void dodisplay() {
  
  display.drawBitmap(0, 0, canvasBIG.getBuffer(), 128, 64, SSD1306_WHITE);
  display.drawBitmap(0, 0, canvastitle.getBuffer(), 128, 16, SSD1306_WHITE);
  display.display();
  
}

void printlabel(char *toprint) {
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(toprint);
}
void displayleBGimg(const unsigned char *img) {
  display.clearDisplay();
  display.drawBitmap(0, 0, img, 128, 64, SSD1306_WHITE);
}
void selectbox(int posX, int posY) {
  // toprint = (char*)"Menu";
  // display.clearDisplay();
  // display.drawBitmap(0, 0, img, 128, 64, SSD1306_WHITE);
  display.drawRoundRect(posX, posY, 21, 21, 3, SSD1306_WHITE);
}

void dodisplayplayhead() {
  //display.clearDisplay();

  //display.drawBitmap(0, 0, canvasBIG2.getBuffer(), 128, 64, SSD1306_WHITE);
  canvasBIG.drawLine(tickposition * 4, 0, tickposition * 4, 64, SSD1306_INVERSE);
  //display.display();
}

void initializelapleasewaitarray() {

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 32; j++) {
      pleasewaitarray[i][j] = (char)'\0';
    }
  }
}
void shiftlapleasewaitarray() {
  for (int i = 9; i > 0; i--) {
    setlapleasewaitarray(i, (char *)pleasewaitarray[i - 1]);
  }
}
void setlapleasewaitarray(int consoleline, char *lemsg) {

  for (int i = 0; i < 32; i++) {
    pleasewaitarray[consoleline][i] = lemsg[i];
  }
}
void pleasewait(float lewait, float letotwait) {
  // shiftlapleasewaitarray();
  // setlapleasewaitarray(0, (char*)lemsg) ;

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(6, 0);
  display.print("Processing");
  if (letotwait > 0) {
    display.setCursor(4, 20);
    display.setTextSize(2);
    display.print("[");
    display.setTextSize(1);
    display.setCursor(7 + 4, 23);
    for (int i = 0; i < int(18.0 * (lewait / letotwait)); i++) {
      display.print("-");
    }
    display.setCursor(115, 20);
    display.setTextSize(2);
    display.print("]");
  }
  display.setCursor(20, 50);
  display.setTextSize(1);
  display.print("(Please Wait)");
  //   for (int i = 0 ; i < 10 ; i++) {
  //   display.println((char*)pleasewaitarray[i]);
  //   }
  display.display();
  // popukate 6 chars arrays and display/copy them to scroll
}

void pseudoconsole(const char *lemsg) {
  shiftconsolemsgarray();
  setleconsolemsg(0, (char *)lemsg);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  for (int i = 0; i < 10; i++) {
    display.println((char *)consolemsg[i]);
  }
  display.display();
  // popukate 6 chars arrays and display/copy them to scroll
}

void initializeconsolemsg() {

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 32; j++) {
      consolemsg[i][j] = (char)'\0';
    }
  }
}
void shiftconsolemsgarray() {
  for (int i = 9; i > 0; i--) {
    setleconsolemsg(i, (char *)consolemsg[i - 1]);
  }
}
void setleconsolemsg(int consoleline, char *lemsg) {

  for (int i = 0; i < 32; i++) {
    consolemsg[consoleline][i] = lemsg[i];
  }
}

void print_memory_usage(){
  if (Serial.available()) {
    char c = Serial.read();
    if ((c == 'r' || c == 'R')) {
      AudioProcessorUsageMaxReset();
      AudioMemoryUsageMaxReset();
      Serial.println("Reset all max numbers");
      }
      
    }
    
  // print a summary of the current & maximum usage
  Serial.print("CPU: ");
  Serial.print("all=");
  Serial.print(AudioProcessorUsage());
  Serial.print(",");
  Serial.print(AudioProcessorUsageMax());
  Serial.print("    ");
  Serial.print("Memory: ");
  Serial.print(AudioMemoryUsage());
  Serial.print(",");
  Serial.print(AudioMemoryUsageMax());
  Serial.println("    ");

}