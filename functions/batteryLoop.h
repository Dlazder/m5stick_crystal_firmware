// pid 2

void batteryLoop() {
	int battery = StickCP2.Power.getBatteryLevel();
	
	DISP.setTextColor(FGCOLOR, BGCOLOR);

	String lines[] = {
		String(battery) + "%",
		String(DEVICE.Power.getBatteryVoltage()) + " V",
	};

	if (isSetup()) {
		centeredPrintRows(lines, 2, MEDIUM_TEXT);
	}

	if (checkTimer(2000)) {
		centeredPrintRows(lines, 2, MEDIUM_TEXT);
	}
	
	checkExit();

	if (isWebDataRequested()) {
		char text[10];
		sprintf(text, "%d%%", battery);
		webData = generateWebData("function", generateFunctionElement(text, MEDIUM_TEXT, "center"));
	}
}