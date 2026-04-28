// pid 41

void toggleKbGyroLoop() {
	if (isSetup()) {
		String lines[] = {
			"KB gyro: " + String(getData("kbGyro", kbGyroEnabled) ? "enabled" : "disabled"),
			"press A"
		};
		centeredPrintRows(lines, 2, SMALL_TEXT);
		updateTimer();
	}

	if (isBtnAWasPressed() && checkTimer(100)) {
		kbGyroEnabled = !getData("kbGyro", kbGyroEnabled);
		setData("kbGyro", kbGyroEnabled);
		DISP.clear();

		String lines[] = {
			"KB gyro: " + String(kbGyroEnabled ? "enabled" : "disabled"),
			"press A"
		};
		centeredPrintRows(lines, 2, SMALL_TEXT);
	}

	checkExit();
}
