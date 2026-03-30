// pid 21

MENU nfcMenu[] = {
	{0, "back"},
	{22, "read"},
	{23, "write"},
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