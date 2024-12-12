void drawMenu(MENU menu[], int size) {
  DISP.setTextSize(MEDIUM_TEXT);
  if (cursor == size) cursor = cursor % size;
  if (cursor < 0) cursor = size - 1;
  if (cursor > 2) {

    for (int i = 0 + (cursor - 2); i < size; i++) {
      if (cursor == i) {
        DISP.setTextColor(BGCOLOR, FGCOLOR);
      }
      DISP.printf(" %-12s\n", menu[i].name);
      DISP.setTextColor(FGCOLOR, BGCOLOR);
    }
    
    if (size > 3) {
      for (int i = 0; i < 4; i++) {
        DISP.println("            ");
      }
    }

  } else {
    for (int i = 0; i < size; i++) {
      if (cursor == i) {
        DISP.setTextColor(BGCOLOR, FGCOLOR);
      }
      DISP.printf(" %-12s\n", menu[i].name);
      DISP.setTextColor(FGCOLOR, BGCOLOR);
    }
    if (size > 3) {
      for (int i = 0; i < 4; i++) {
        DISP.println("            ");
      }
    }
  }
}

void menuLoop(MENU menu[], int size) {
  StickCP2.update();
  if (BtnBWasPressed() || webControlDownWasPressed()) {
    cursorOnTop();
    cursor++;
    drawMenu(menu, size);
    // StickCP2.Speaker.tone(8000, 20);
  }
  if (BtnAWasPressed()) {
    DISP.clear();
    cursorOnTop();
    currentProc = menu[cursor].command;
    Serial.printf("Switching to %d process\n", currentProc);
    isSwitching = true;
    return;
  }
  if (webControlUpWasPressed()) {
    cursor--;
    
    cursorOnTop();
    drawMenu(menu, size);
  }
  if (isWebDataRequested) {
    responseState = generateResponse("menu", generateMenuString(menu, size));
    Serial.println(responseState);

    isWebDataRequested = false;
  }
}