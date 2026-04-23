// pid 3

MENU settingsMenu[] = {
	{0, "back"},
	{35, "clock"},
	{5, "brightness"},
	{6, "rotation"},
	{7, "colors"},
	{10, "status bar"},
	{28, "start sound"},
	{19, "font"},
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