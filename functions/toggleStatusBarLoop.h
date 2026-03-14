// pid 16

void toggleStatusBarLoop() {
	if (isSetup()) {
		String lines[] = {
			"status bar: " + String(getData("statusBar", statusBar) ? "enabled" : "disabled"),
			"press A"
		};
		centeredPrintRows(lines, 2, SMALL_TEXT);
		updateTimer();
	}

	if (isBtnAWasPressed() && checkTimer(100)) {
		statusBar = !getData("statusBar", statusBar);
		setData("statusBar", statusBar);
		DISP.clear();


		String lines[] = {
			"status bar: " + String(statusBar ? "enabled" : "disabled"),
			"press A"
		};
		centeredPrintRows(lines, 2, SMALL_TEXT);
	}

	checkExit();
}