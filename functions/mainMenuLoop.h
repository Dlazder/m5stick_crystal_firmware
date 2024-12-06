MENU mainMenu[] = {
  {"clock", 1},
  {"Battery info", 2},
  {"settings", 3},
  {"Wi-Fi ap", 4},
};
int mainMenuSize = sizeof(mainMenu) / sizeof(MENU);
void mainMenuLoop() {
  if (isSetup()) {
    cursorOnTop();
    drawMenu(mainMenu, mainMenuSize);
  }
  menuLoop(mainMenu, mainMenuSize);
}