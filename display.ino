
void dodisplay() {
  display.drawBitmap(0, 0, canvasBIG.getBuffer(), 128, 64, SSD1306_WHITE);
  display.drawBitmap(0, 0, canvastitle.getBuffer(), 128, 16, SSD1306_WHITE);
  display.display();
}

        
void doConfirmpanel(char *letitlemsg) {
  navrange = 1;
  canvastitle.fillScreen(SSD1306_BLACK);
  canvastitle.setCursor(0, 0);
  canvastitle.setTextSize(1);
  // canvastitle.print((char*)text);
  canvastitle.print((char *)letitlemsg);
  canvasBIG.setTextSize(1);
  canvasBIG.fillScreen(SSD1306_BLACK);
  canvasBIG.setCursor(20, 28);
  // canvasBIG.print((char*)text);
  canvasBIG.print("NO         YES");
  canvasBIG.drawRect(14 + sublevels[navlevel] * 66, 23,
                    23 + sublevels[navlevel] * 6, 17, SSD1306_WHITE);
  dodisplay();
  display.display();
}

void dodisplayplayhead() {
  canvasBIG.drawLine(tickposition * 4, 0, tickposition * 4, 64, SSD1306_INVERSE);
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
  display.display();
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

void printnoteon(byte channel, byte data1, byte data2) {
  Serial.print("Note On, ch=");
  Serial.print(channel);
  Serial.print(", note=");
  Serial.print(data1);
  Serial.print(", velocity=");
  Serial.println(data2);
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
