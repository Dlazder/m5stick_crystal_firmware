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

int selectedItem = 0;
void menuLoop(MENU menu[], int size, bool updateSelectedItem = false) {
  StickCP2.update();
  if (isBtnBWasPressed() || isWebControlDownWasPressed()) {
    cursorOnTop();
    cursor++;
    drawMenu(menu, size);
  }
  if (isBtnAWasPressed()) {
    cursorOnTop();
    clearScreenWithSymbols();
    cursorOnTop();
    changeProcess(menu[cursor].command);
    if (updateSelectedItem) selectedItem = menu[cursor].command;
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

bool isMenuItemSelected(int pid) {
  if (pid == selectedItem) {
    selectedItem = -1;
    return true;
  } else return false;
}