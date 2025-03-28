void brightnessLoop() {
  if (isSetup()) {
    char text[50];
    sprintf(text, "brightness: %d", brightness / brightnessDividor);
    centeredPrint(text, SMALL_TEXT);
    updateTimer();
  }
  if (isBtnAWasPressed() && checkTimer(100)) {
    DISP.setCursor(0, 60, 1);
    char text[50];
    sprintf(text, "brightness: %d", brightness);

    brightness -= brightnessDividor;
    if (brightness <= 0 || brightness / brightnessDividor == 0) brightness = brightnessMax;
    setData("brightness", brightness);
    DISP.setBrightness(brightness);
    sprintf(text, "brightness: %d", brightness / brightnessDividor);
    centeredPrint(text, SMALL_TEXT);
  }
  checkExit(3);
  if (isWebDataRequested()) {
    char text[50];
    sprintf(text, "brightness: %d", brightness / brightnessDividor);
    webData = generateWebData("function", generateFunctionElement(text, SMALL_TEXT, "center"));
  }
}