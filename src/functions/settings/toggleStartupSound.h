// pid 28

void toggleStartupSound() {
	if (isSetup()) {
		String lines[] = {
			"Sound: " + String(getData("startupSound", startupSound) ? "enabled": "disabled"),
			"press A"
		};
		centeredPrintRows(lines, 2, SMALL_TEXT);
		updateTimer();
	}

	if (isBtnAWasPressed() && checkTimer(100)) {
		DISP.clear();
		startupSound = !getData("startupSound", startupSound);
		setData("startupSound", startupSound);

		String lines[] = {
			"Sound: " + String(getData("startupSound", startupSound) ? "enabled": "disabled"),
			"press A"
		};
		centeredPrintRows(lines, 2, SMALL_TEXT);
	}

	checkExit();
}