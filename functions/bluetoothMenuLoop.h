// pid: 14

MENU bluetoothMenu[] = {
	{0, "back"},
	{15, "shutter"},
};
int bluetoothMenuSize = sizeof(bluetoothMenu) / sizeof(MENU);


void bluetoothMenuLoop() {
	if (isSetup()) {
		cursorOnTop();
		drawMenu(bluetoothMenu, bluetoothMenuSize);
	}
	menuLoop(bluetoothMenu, bluetoothMenuSize);
}