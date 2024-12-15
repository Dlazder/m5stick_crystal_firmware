int oldSeconds;
void clockLoop() {
  auto dt = StickCP2.Rtc.getDateTime();
  char formatString[30];
  sprintf(formatString, "%02d:%02d:%02d", dt.time.hours, dt.time.minutes, dt.time.seconds);
  if (dt.time.seconds != oldSeconds) {
    oldSeconds = dt.time.seconds;
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    centeredPrint(formatString, SMALL_TEXT);
  }
  checkExit(0);
  if (isWebDataRequested()) {
    webData = generateWebData("function", generateFunctionElement(formatString, SMALL_TEXT, "center"));
  }
}