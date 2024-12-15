void drawMenu(MENU menu[], int size) {
  DISP.setTextSize(MEDIUM_TEXT);
  if (cursor == size) cursor = cursor % size;
  if (cursor < 0) cursor = size - 1;
  if (cursor > 2) {

    for (int i = 0 + (cursor - 2); i < size; i++) {
      cursor == i ? DISP.setTextColor(BGCOLOR, FGCOLOR) : DISP.setTextColor(FGCOLOR, BGCOLOR);
      
      DISP.printf(" %-12s\n", menu[i].name);
    }
    
    clearScreenWithSymbols();

  } else {
    for (int i = 0; i < size; i++) {
      cursor == i ? DISP.setTextColor(BGCOLOR, FGCOLOR) : DISP.setTextColor(FGCOLOR, BGCOLOR);

      DISP.printf(" %-12s\n", menu[i].name);
    }
    clearScreenWithSymbols();
  }
}

void menuLoop(MENU menu[], int size) {
  StickCP2.update();
  if (isBtnBWasPressed() || isWebControlDownWasPressed()) {
    cursorOnTop();
    cursor++;
    drawMenu(menu, size);
    // StickCP2.Speaker.tone(8000, 20);
  }
  if (isBtnAWasPressed()) {
    cursorOnTop();
    clearScreenWithSymbols();
    cursorOnTop();
    process = menu[cursor].command;
    Serial.printf("Switching to %d process\n", process);
    isSwitching = true;
    return;
  }
  if (isWebControlUpWasPressed()) {
    cursor--;
    
    cursorOnTop();
    drawMenu(menu, size);
  }
  if (isWebDataRequested()) {
    webData = generateWebData("menu", generateMenuString(menu, size));
  }
}