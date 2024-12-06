void centeredPrint(String text, int textSize) {
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  int currentTextSize = DISP.getTextSizeX();
  DISP.setTextSize(textSize);
  int displayWidth = DISP.width();
  int textWidth = DISP.textWidth(text);
  int padding = (displayWidth - textWidth) / 2;
  DISP.setCursor(0, 60, 1);
  DISP.print("                    ");
  DISP.setCursor(padding, 60, 1);
  DISP.print(text);
  DISP.setTextSize(currentTextSize);
}

void xycenteredPrint(String text, int textSize) {
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  int displayWidth = DISP.width();
  int textWidth = DISP.textWidth(text);
  int paddingX = (displayWidth - textWidth) / 2;
  int displayHeight = DISP.height();
  DISP.setCursor(paddingX, 37, 1);
  DISP.print(text);
  DISP.drawCenterString(text, 125, 67, 1);
  Serial.println(DISP.getCursorY());
}

void cursorOnTop() {
  if (statusBar) {
    DISP.setCursor(0, 31, 1);
  } else {
    DISP.setCursor(0, 0, 1);
  }
}