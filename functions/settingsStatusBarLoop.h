void settingsStatusBarLoop() {
	if (isSetup()) {
		centeredPrint("press A", SMALL_TEXT);
		updateTimer();
	}

	if (isBtnAWasPressed() && checkTimer(100)) {
		statusBar = !getData("statusBar", statusBar);
		setData("statusBar", statusBar);
		DISP.clear();
		centeredPrint("press A", SMALL_TEXT);
	}
	checkExit(3);
}