// pid 24

MENU flashLightMenu[] = {
	{0, "back"},
	{25, "flashlight"},
	{26, "flicker"},
	{5, "brightness"},
	{7, "colors"}
};
int flashLightMenuSize = sizeof(flashLightMenu) / sizeof(MENU);


void flashLightMenuLoop() {
	if (isSetup()) {
		cursor = 0;
		cursorOnTop();
		drawMenu(flashLightMenu, flashLightMenuSize);
	}
	menuLoop(flashLightMenu, flashLightMenuSize);
}