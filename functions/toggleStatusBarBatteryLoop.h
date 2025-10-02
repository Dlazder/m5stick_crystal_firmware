// pid: 18
void toggleStatusBarBatteryLoop() {
	if (isSetup()) {
		centeredPrint("press A", SMALL_TEXT);
		updateTimer();
	}

	if (isBtnAWasPressed() && checkTimer(100)) {
		statusBarBattery = !getData("statusBarBattery", statusBarBattery);
		setData("statusBarBattery", statusBarBattery);
		DISP.clear();
		centeredPrint("press A", SMALL_TEXT);
	}

	checkExit();
}