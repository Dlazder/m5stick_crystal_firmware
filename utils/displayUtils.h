int getScreenWidthInSymbols() {
  int size = DISP.getTextSizeY();

  switch (size) {
    case 2:
      return 20;
    case 3:
      return 13;
  }
}

void clearScreenWithSymbols() {
  DISP.setTextSize(MEDIUM_TEXT);
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  for (int i = 0; i < 5; i++) {
    DISP.println("             ");
  }
}

void centeredPrint(String text, int textSize, bool newLine = false) {
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  int currentTextSize = DISP.getTextSizeX();
  DISP.setTextSize(textSize);
  int displayWidth = DISP.width();
  int textWidth = DISP.textWidth(text);
  int padding = (displayWidth - textWidth) / 2;
  int cursorY = DISP.getCursorY();
  

  if (newLine) {
    DISP.setCursor(0, cursorY, 1);
    for (int i = 0; i < getScreenWidthInSymbols(); i++) {
      DISP.print(" ");
    }
    DISP.setCursor(padding, cursorY, 1);
  } else {
    DISP.setCursor(0, 60, 1);
    for (int i = 0; i < getScreenWidthInSymbols(); i++) {
      DISP.print(" ");
    }
    DISP.setCursor(padding, 60, 1);
  }
  DISP.println(text);
  DISP.setTextSize(currentTextSize);
}

void printlnCenter(String text, int textSize) {
  centeredPrint(text, textSize, true);
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
    DISP.setCursor(0, 39, 1);
  } else {
    DISP.setCursor(0, 0, 1);
  }
}