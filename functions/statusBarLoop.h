int battery = 100;
int statusBarTimer = 0;

void statusBar_batteryLoop() {
  auto currentTime = StickCP2.Rtc.getDateTime();
  if (checkTimer(3000, true, &statusBarTimer)) battery = StickCP2.Power.getBatteryLevel();
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  DISP.printf("%d%%; ", battery);
}

void statusBarLoop() {
  DISP.setTextColor(FGCOLOR);
  DISP.setCursor(8, 8, 1);
  DISP.setTextSize(SMALL_TEXT);
  DISP.printf("PID: %d; ", currentProc);
  statusBar_batteryLoop();
  DISP.drawLine(0, 30, 250, 30, FGCOLOR);
}
