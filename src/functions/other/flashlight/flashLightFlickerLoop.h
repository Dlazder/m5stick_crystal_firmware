// PID::FLASHLIGHT_FLICKER

void flickerLoop() {
	static bool flickerStatusBarWasEnabled;
	static bool isOn = true;

	if (isSetup()) {
		flickerStatusBarWasEnabled = statusBar;
		statusBar = false;
	}

	if (checkTimer(300)) {
		updateTimer();
		isOn = !isOn;
		DISP.fillScreen(isOn ? FGCOLOR : BGCOLOR);
	}

	dimmerWake();

	if (checkExit()) {
		statusBar = flickerStatusBarWasEnabled;
		canvas.clear();
		canvas.pushSprite(0, getStatusBarHeight());
	}
}