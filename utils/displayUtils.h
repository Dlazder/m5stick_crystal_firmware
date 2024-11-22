void centeredPrint(String text, int textSize) {
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  int displayWidth = DISP.width();
  int textWidth = DISP.textWidth(text);
  int padding = (displayWidth - textWidth) / 2;
  DISP.setCursor(padding, 60, 1);
  DISP.print(text);
}

void cursorOnTop() {
  if (statusBar) {
    DISP.setCursor(0, 30, 1);
  } else {
    DISP.setCursor(0, 0, 1);
  }
}