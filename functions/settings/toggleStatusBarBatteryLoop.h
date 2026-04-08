// pid 18

void toggleStatusBarBatteryLoop() {
	if (isSetup()) {
		String lines[] = {
			"battery: " + String(getData("statusBarBattery", statusBarBattery) ? "enabled" : "disabled"),
			"press A"
		};
		centeredPrintRows(lines, 2, SMALL_TEXT);
		updateTimer();
	}

	if (isBtnAWasPressed() && checkTimer(100)) {
		DISP.clear();
		statusBarBattery = !getData("statusBarBattery", statusBarBattery);
		setData("statusBarBattery", statusBarBattery);

		String lines[] = {
			"battery: " + String(getData("statusBarBattery", statusBarBattery) ? "enabled" : "disabled"),
			"press A"
		};
		centeredPrintRows(lines, 2, SMALL_TEXT);
	}

	checkExit();
}