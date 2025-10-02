// pid: 10
MENU settingsStatusBarMenu[] = {
	{3, "back"},
	{16, "statusBar"},
	{17, "PID"},
	{18, "battery"},
	// {19, "clock"}
};

int settingsStatusBarMenuSize = sizeof(settingsStatusBarMenu) / sizeof(MENU);

void settingsStatusBarLoop() {
	if (isSetup()) {
		if (previousProcess == 3) cursor = 0;
		cursorOnTop();
		drawMenu(settingsStatusBarMenu, settingsStatusBarMenuSize);
	}
	menuLoop(settingsStatusBarMenu, settingsStatusBarMenuSize);
}