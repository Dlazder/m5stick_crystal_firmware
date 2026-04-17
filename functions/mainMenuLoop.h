// pid 0

MENU mainMenu[] = {
	{13, "Wi-Fi"},
	{14, "Bluetooth"},
	{21, "NFC"},
	{3, "settings"},
	{29, "other"},
};
int mainMenuSize = sizeof(mainMenu) / sizeof(MENU);

void mainMenuLoop() {
	if (isSetup()) {
		cursorOnTop();
		drawMenu(mainMenu, mainMenuSize);
	}
	menuLoop(mainMenu, mainMenuSize);
}