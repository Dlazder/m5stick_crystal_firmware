// pid 14

MENU bluetoothMenu[] = {
	{0, "back"},
	{15, "shutter"},
	{31, "air mouse"},
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