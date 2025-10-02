// pid: 10
MENU settingsStatusBarMenu[] = {
	{16, "statusBar"},
	{17, "PID"},
	{18, "battery"},
	{19, "clock"}
};

int settingsStatusBarMenuSize = sizeof(settingsStatusBarMenu) / sizeof(MENU);

void settingsStatusBarLoop() {
	if (isSetup()) {
		cursorOnTop();
		drawMenu(settingsStatusBarMenu, settingsStatusBarMenuSize);
	}
	menuLoop(settingsStatusBarMenu, settingsStatusBarMenuSize);
}