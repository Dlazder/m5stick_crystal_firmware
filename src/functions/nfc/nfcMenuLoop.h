// pid 21

MENU nfcMenu[] = {
	{0, "back"},
	{22, "read UID"},
	{23, "write UID"},
	// {19, "clock"}
};

int nfcMenuSize = sizeof(nfcMenu) / sizeof(MENU);

void nfcMenuLoop() {
	if (isSetup()) {
		cursor = 0;
		cursorOnTop();
		drawMenu(nfcMenu, nfcMenuSize);
	}
	menuLoop(nfcMenu, nfcMenuSize);
}