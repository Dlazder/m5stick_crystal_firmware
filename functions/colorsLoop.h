// pid 7

int currentColorIndex = 0;
void colorsLoop() {
	if (isSetup()) {
		String lines[] = {"color: " + String(FGCOLOR), "press A"};
		centeredPrintRows(lines, 2, SMALL_TEXT);
		updateTimer();
	}
	if (isBtnAWasPressed() && checkTimer(100)) {
		currentColorIndex++;
		if (currentColorIndex == sizeof(colors) / sizeof(colors[0])) {
			currentColorIndex = 0;
		}
		Serial.printf("current colorIndex: %d\n", currentColorIndex);
		
		FGCOLOR = colors[currentColorIndex];
		setData("color", FGCOLOR);
		String lines[] = {"color: " + String(FGCOLOR), "press A"};
		centeredPrintRows(lines, 2, SMALL_TEXT);
	}
	checkExit(3);
}