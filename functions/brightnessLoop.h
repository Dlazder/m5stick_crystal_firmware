void brightnessLoop() {
  if (isSetup()) {
    char text[50];
    sprintf(text, "brightness: %d", brightness / brightnessDividor);
    centeredPrint(text, SMALL_TEXT);
    updateTimer();
  }
  if (BtnAWasPressed() && checkTimer(100)) {
    DISP.setCursor(0, 60, 1);
    char text[50];
    sprintf(text, "brightness: %d", brightness);

    brightness -= brightnessDividor;
    if (brightness <= 0) brightness = brightnessMax;
    DISP.setBrightness(brightness);
    sprintf(text, "brightness: %d", brightness / brightnessDividor);
    centeredPrint(text, SMALL_TEXT);
  }
  checkExit(3);
}