// pid 29

MENU otherMenu[] = {
	{0, "back"},
	{1, "clock"},
	{27, "sound level"},
	{24, "flashlight"},
	{20, "level tool"},
	{2, "Battery info"},
	{30, "System info"},
};
int otherMenuSize = sizeof(otherMenu) / sizeof(MENU);

void otherMenuLoop() {
	if (isSetup()) {
		cursor = 0;
		cursorOnTop();
		drawMenu(otherMenu, otherMenuSize);
	}
	menuLoop(otherMenu, otherMenuSize);
}