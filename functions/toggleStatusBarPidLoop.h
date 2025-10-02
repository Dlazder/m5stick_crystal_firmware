// pid: 17
void toggleStatusBarPidLoop() {
	if (isSetup()) {
		centeredPrint("press A", SMALL_TEXT);
		updateTimer();
	}

	if (isBtnAWasPressed() && checkTimer(100)) {
		statusBarPid = !getData("statusBarPid", statusBarPid);
		setData("statusBarPid", statusBarPid);
		DISP.clear();
		centeredPrint("press A", SMALL_TEXT);
	}

	checkExit();
}