// pid 7

void colorsLoop() {
	if (isSetup()) {
		String lines[] = {"color: " + String(colorsEntry[colorIndex]), "press A"};
		centeredPrintRows(lines, 2, SMALL_TEXT);
		updateTimer();
	}
	if (isBtnAWasPressed() && checkTimer(100)) {
		colorIndex++;
		if (colorIndex == sizeof(colors) / sizeof(colors[0])) {
			colorIndex = 0;
		}
		Serial.printf("current colorIndex: %d\n", colorIndex);
		
		FGCOLOR = colors[colorIndex];
		setData("colorIndex", colorIndex);
		// setData("color", FGCOLOR);
		String lines[] = {"color: " + String(colorsEntry[colorIndex]), "press A"};
		centeredPrintRows(lines, 2, SMALL_TEXT);
	}
	checkExit();
}