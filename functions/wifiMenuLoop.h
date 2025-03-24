MENU wifiMenu[] = {
	{"back", 0},
	{"Wi-Fi AP", 4},
	{"scan", 8}
};

int wifiMenuSize = sizeof(wifiMenu) / sizeof(MENU);

void wifiMenuLoop() {
	if (isSetup()) {
		cursorOnTop();
		drawMenu(wifiMenu, wifiMenuSize);
	}
	menuLoop(wifiMenu, wifiMenuSize);
	checkExit(0);
}