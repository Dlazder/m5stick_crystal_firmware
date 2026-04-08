// pid 25

void flashLightLoop() {
	static bool flashLightStatusBarWasEnabled;

	if (isSetup()) {
		flashLightStatusBarWasEnabled = statusBar;
		statusBar = false;
		DISP.fillScreen(FGCOLOR);
	}

	if (checkExit()) {
		statusBar = flashLightStatusBarWasEnabled;
	}
}