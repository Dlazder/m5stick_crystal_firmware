// pid 17

void toggleStatusBarPidLoop() {
	if (isSetup()) {
		String lines[] = {
			"PID: " + String(getData("statusBarPid", statusBarPid) ? "enabled" : "disabled"),
			"press A"
		};
		centeredPrintRows(lines, 2, SMALL_TEXT);
		updateTimer();
	}

	if (isBtnAWasPressed() && checkTimer(100)) {
		DISP.clear();
		statusBarPid = !getData("statusBarPid", statusBarPid);
		setData("statusBarPid", statusBarPid);
		
		String lines[] = {
			"PID: " + String(getData("statusBarPid", statusBarPid) ? "enabled" : "disabled"),
			"press A"
		};
		centeredPrintRows(lines, 2, SMALL_TEXT);
	}

	checkExit();
}