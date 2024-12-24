int currentColorIndex = 0;
void colorsLoop() {
	if (isSetup()) {
		centeredPrint("press A", SMALL_TEXT);
		updateTimer();
	}
	if (isBtnAWasPressed() && checkTimer(100)) {
		currentColorIndex++;
		if (currentColorIndex == sizeof(colors) / sizeof(colors[0])) {
			currentColorIndex = 0;
		}
		FGCOLOR = colors[currentColorIndex];
		writeData("color", FGCOLOR);
		centeredPrint("press A", SMALL_TEXT);
		Serial.println(currentColorIndex);
	}
	checkExit(3);
}