void batteryLoop() {
  if (checkTimer(3000)) {
    int battery = StickCP2.Power.getBatteryLevel();
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    char text[10];
    sprintf(text, "%d%%", battery);
    centeredPrint(text, SMALL_TEXT);
  }
  checkExit(0);
}