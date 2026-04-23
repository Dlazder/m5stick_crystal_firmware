// pid 30

MENU systemMenu[] = {
	{29, "back"},
	{33, "shutdown"},
	{34, "info"}
};
int systemMenuSize = sizeof(systemMenu) / sizeof(MENU);


void systemMenuLoop() {
	if (isSetup()) {
		cursor = 0;
		cursorOnTop();
		drawMenu(systemMenu, systemMenuSize);
	}
	menuLoop(systemMenu, systemMenuSize);
}