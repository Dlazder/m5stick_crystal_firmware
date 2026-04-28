// pid 3

MENU settingsMenu[] = {
	{0, "back"},
	{35, "time"},
	{5, "brightness"},
	{6, "rotation"},
	{7, "colors"},
	{10, "status bar"},
	{28, "startup sound"},
	{19, "font"},
	{41, "keyboard gyro"},
};
int settingsMenuSize = sizeof(settingsMenu) / sizeof(MENU);
void settingsMenuLoop() {
	if (isSetup()) {
		DISP.setTextSize(SMALL_TEXT);
		cursorOnTop();
		if (previousProcess == 0) cursor = 0;
		drawMenu(settingsMenu, settingsMenuSize);
	}
	menuLoop(settingsMenu, settingsMenuSize);
}