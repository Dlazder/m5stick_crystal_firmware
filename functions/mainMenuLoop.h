// pid 0

MENU mainMenu[] = {
	{1, "clock"},
	{21, "NFC"},
	{3, "settings"},
	{13, "Wi-Fi"},
	{14, "Bluetooth"},
	{20, "level tool"},
	{24, "flashlight"},
	{2, "Battery info"},
};
int mainMenuSize = sizeof(mainMenu) / sizeof(MENU);
void mainMenuLoop() {
	if (isSetup()) {
		cursorOnTop();
		drawMenu(mainMenu, mainMenuSize);
	}
	menuLoop(mainMenu, mainMenuSize);
}