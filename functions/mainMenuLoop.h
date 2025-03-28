MENU mainMenu[] = {
	{1, "clock"},
	{2, "Battery info"},
	{3, "settings"},
	{13, "Wi-Fi"}
};
int mainMenuSize = sizeof(mainMenu) / sizeof(MENU);
void mainMenuLoop() {
	if (isSetup()) {
		cursorOnTop();
		drawMenu(mainMenu, mainMenuSize);
	}
	menuLoop(mainMenu, mainMenuSize);
}