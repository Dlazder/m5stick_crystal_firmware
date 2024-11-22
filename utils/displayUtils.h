void centeredPrint(String text, int textSize) {
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  int displayWidth = DISP.width();
  int textWidth = DISP.textWidth(text);
  int padding = (displayWidth - textWidth) / 2;
  DISP.setCursor(padding, 60, 1);
  DISP.print(text);
}