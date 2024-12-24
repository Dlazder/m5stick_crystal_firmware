// settingsLoop PID: 3
MENU settingsMenu[] = {
  {"back", 0},
  {"brightness", 5},
  {"rotation", 6},
  {"colors", 7}
};
int settingsMenuSize = sizeof(settingsMenu) / sizeof(MENU);
void settingsLoop() {
  if (isSetup()) {
    DISP.setTextSize(SMALL_TEXT);
    cursorOnTop();
    cursor = 0;
    drawMenu(settingsMenu, settingsMenuSize);
  }
  menuLoop(settingsMenu, settingsMenuSize);
}