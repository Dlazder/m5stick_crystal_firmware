// Resets the dimming timer and restores full brightness if the screen was dimmed.
void dimmerWake() {
	if (screenIsDimmed) {
		DISP.setBrightness(brightnessToHw(brightness));
		screenIsDimmed = false;
	}
	updateTimer(&dimmingPreviousTimer);
}

void dimmerUpdate() {
	bool anyInput = isBtnAWasPressed() || isBtnBWasPressed() || isBtnPWRWasPressed() || isAnyKbKeyPressed();
	if (anyInput) {
		dimmerWake();
	}

	if (screenDimTimeout > 0 && !screenIsDimmed) {
		if (checkTimer(screenDimTimeout, false, &dimmingPreviousTimer)) {
			DISP.setBrightness(10);
			screenIsDimmed = true;
		}
	}
}
