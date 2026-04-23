// pid NONE

void statusBarLoop() {
	static int statusBarTimer = 0;
	static int battery = DEVICE.Power.getBatteryLevel();
	
	statusBarCanvas.clear();
	statusBarCanvas.setTextColor(FGCOLOR, BGCOLOR);
	statusBarCanvas.setCursor(5, 4);
	statusBarCanvas.setTextSize(TINY_TEXT);
	
	// PID
	if (getData("statusBarPid", statusBarPid)) {
		statusBarCanvas.printf("#:%d; ", process);
	}
	
	// Clock
	auto dt = DEVICE.Rtc.getDateTime();
	char formatString[30];
	sprintf(formatString, "%02d:%02d:%02d   ", dt.time.hours, dt.time.minutes, dt.time.seconds);
	statusBarCanvas.print(formatString);

	// Battery
	if (checkTimer(3000, true, &statusBarTimer)) {
		battery = DEVICE.Power.getBatteryLevel();
	}
	char batteryText[10];
	sprintf(batteryText, "%d%%", battery);
	int batteryTextWidth = DISP.textWidth(batteryText);
	statusBarCanvas.setCursor(DISP.width() - batteryTextWidth, 4);
	statusBarCanvas.printf("%d%%", battery);

	statusBarCanvas.drawLine(0, 19, DISP.width(), 19, FGCOLOR);
	statusBarCanvas.pushSprite(0, 0);
}
