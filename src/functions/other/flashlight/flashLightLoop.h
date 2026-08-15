// PID::FLASHLIGHT

void flashLightLoop() {
	static bool flashLightStatusBarWasEnabled;

	if (isSetup()) {
		flashLightStatusBarWasEnabled = statusBar;
		statusBar = false;
		DISP.fillScreen(FGCOLOR);
	}

	dimmerWake();

	if (checkExit()) {
		statusBar = flashLightStatusBarWasEnabled;
		canvas.clear();
		canvas.pushSprite(0, getStatusBarHeight());
	}
}