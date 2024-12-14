void batteryLoop() {
  if (isSetup()) {
    int battery = StickCP2.Power.getBatteryLevel();
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    char text[10];
    sprintf(text, "%d%%", battery);
    centeredPrint(text, SMALL_TEXT);
  }
  if (checkTimer(3000)) {
    int battery = StickCP2.Power.getBatteryLevel();
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    char text[10];
    sprintf(text, "%d%%", battery);
    centeredPrint(text, SMALL_TEXT);
  }
  checkExit(0);
  if (isStateRequested()) {
    
  }
}