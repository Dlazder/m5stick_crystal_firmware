// pid 14

MENU bluetoothMenu[] = {
	{0, "back"},
	{36, "scan"},
	{31, "air mouse"},
	{32, "presenter"},
	{15, "shutter"},
};
int bluetoothMenuSize = sizeof(bluetoothMenu) / sizeof(MENU);


void bluetoothMenuLoop() {
	if (isSetup()) {
		cursor = 0;
		cursorOnTop();
		drawMenu(bluetoothMenu, bluetoothMenuSize);
	}
	menuLoop(bluetoothMenu, bluetoothMenuSize);
}