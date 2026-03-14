// pid 5

void brightnessLoop() {
  if (isSetup()) {
    String lines[] = {
      "brightness: " + String(brightness / brightnessDividor),
      "press A"
    };
    centeredPrintRows(lines, 2, SMALL_TEXT);
    updateTimer();
  }
  
  if (isBtnAWasPressed() && checkTimer(100)) {
    brightness -= brightnessDividor;
    if (brightness <= 0 || brightness / brightnessDividor == 0) brightness = brightnessMax;
    setData("brightness", brightness);
    DISP.setBrightness(brightness);

    String lines[] = {
      "brightness: " + String(brightness / brightnessDividor),
      "press A"
    };
    centeredPrintRows(lines, 2, SMALL_TEXT);
  }
  checkExit(3);
  if (isWebDataRequested()) {
    char text[50];
    sprintf(text, "brightness: %d", brightness / brightnessDividor);
    webData = generateWebData("function", generateFunctionElement(text, SMALL_TEXT, "center"));
  }
}