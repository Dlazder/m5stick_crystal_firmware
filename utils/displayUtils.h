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

/**
 * print text on center of the screen
 * @param textSize [TINY_TEXT; SMALL_TEXT; MEDIUM_TEXT; BIG_TEXT] - (1; 2; 3; 4)
 * @param newLine if we printing second text row
 */
void centeredPrint(String text, int textSize, bool newLine = false) {
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  int currentTextSize = DISP.getTextSizeX();

  DISP.setTextSize(textSize);
  int displayWidth = DISP.width();
  int textWidth = DISP.textWidth(text.c_str());
  int padding = (displayWidth - textWidth) / 2;
  int cursorY = DISP.getCursorY();
  

  if (newLine) {

    DISP.setCursor(0, cursorY);
    for (int i = 0; i < getScreenWidthInSymbols(); i++) {
      DISP.print(" ");
    }
    DISP.setCursor(padding, cursorY);

  } else {
    
    // calculate the approximate top indent depending on whether the status bar is enabled
    int offsetY = preferences.getUInt("statusBar", false) ? 70 : 65;

    DISP.setCursor(0, offsetY);
    for (int i = 0; i < getScreenWidthInSymbols(); i++) {
      DISP.print(" ");
    }
    DISP.setCursor(padding, offsetY);

  }

  DISP.println(text.c_str());
  DISP.setTextSize(currentTextSize);
}

void printlnCenter(String text, int textSize) {
  centeredPrint(text, textSize, true);
}

void cursorOnTop() {
  if (statusBar) {
    DISP.setCursor(0, 39);
  } else {
    DISP.setCursor(0, 0);
  }
}