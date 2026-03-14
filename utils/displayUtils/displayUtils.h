/**
 * Returns the screen width in characters
 * (How many characters can fit)
 */
int getScreenWidthInSymbols() {
  int size = DISP.getTextSizeY();

  switch (size) {
    case 2:
      return 20;
    case 3:
      return 13;
  }
}


/**
 * print spaces on screen to clear screen
 * (will be removed in future probably)
 */
void clearScreenWithSymbols() {
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  DISP.setTextSize(SMALL_TEXT);
  for (int i = 0; i < 9; i++) {
    DISP.println("                    ");
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

/**
 * Places the cursor at the top of the accessible area
 * (depending on the presence of the status bar)
 */
void cursorOnTop() {
  if (statusBar) {
    DISP.setCursor(0, 39);
  } else {
    DISP.setCursor(0, 0);
  }
}