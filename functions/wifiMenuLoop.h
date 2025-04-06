MENU wifiMenu[] = {
    {0, "back"},
    {4, "Wi-Fi AP"},
    {8, "scan"}
};

int wifiMenuSize = sizeof(wifiMenu) / sizeof(MENU);

void wifiMenuLoop() {
	if (isSetup()) {
		cursorOnTop();
		drawMenu(wifiMenu, wifiMenuSize);
	}
	menuLoop(wifiMenu, wifiMenuSize);
}