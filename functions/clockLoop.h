// pid 1

void clockLoop() {
  static int oldSeconds;
  auto dt = StickCP2.Rtc.getDateTime();
  char formatString[30];
  sprintf(formatString, "%02d:%02d:%02d", dt.time.hours, dt.time.minutes, dt.time.seconds);
  if (dt.time.seconds != oldSeconds) {
    oldSeconds = dt.time.seconds;
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    canvas.clear();
    canvas.setTextSize(MEDIUM_TEXT);
    canvas.drawCenterString(formatString, DISP.width() / 2, ((DISP.height() - getStatusBarHeight()) - DISP.fontHeight()) / 2);
    canvas.pushSprite(0, getStatusBarHeight());
  }
  checkExit();
  
  if (isWebDataRequested()) {
    webData = generateWebData("function", generateFunctionElement(formatString, SMALL_TEXT, "center"));
  }
}