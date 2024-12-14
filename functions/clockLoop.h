int oldSeconds;
void clockLoop() {
  auto dt = StickCP2.Rtc.getDateTime();
  if (dt.time.seconds != oldSeconds) {
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    char formatString[30];
    sprintf(formatString, "%02d:%02d:%02d", dt.time.hours, dt.time.minutes, dt.time.seconds);
    centeredPrint(formatString, SMALL_TEXT);
  }
  oldSeconds = dt.time.seconds;
  checkExit(0);
  if (isStateRequested()) {

  }
}