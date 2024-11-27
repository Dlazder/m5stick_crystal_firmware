MENU settingsMenu[] = {
  {"back", 0},
  {"brightness", 5},
  {"orientation", 6}
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