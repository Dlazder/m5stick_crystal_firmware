// settingsLoop PID: 3
MENU settingsMenu[] = {
	{0, "back"},
	{5, "brightness"},
	{6, "rotation"},
	{7, "colors"},
	{10, "status bar"}
};
int settingsMenuSize = sizeof(settingsMenu) / sizeof(MENU);
void settingsLoop() {
	if (isSetup()) {
		DISP.setTextSize(SMALL_TEXT);
		cursorOnTop();
		cursor = 0;
		drawMenu(settingsMenu, settingsMenuSize);
	}
	menuLoop(settingsMenu, settingsMenuSize);
}