void bluetoothPresenterLoop() {
	static bool isBleConnected = false;

	if (isSetup()) {
		bleKeyboard.begin();
		centeredPrint("Wating connection", SMALL_TEXT);
		updateTimer();
	}

	if (bleKeyboard.isConnected()) {
		if (!isBleConnected) {
			isBleConnected = true;
			centeredPrint("Connected", SMALL_TEXT);
			DEVICE.Speaker.tone(2000, 200);
		}
	} else {
		if (isBleConnected) {
			isBleConnected = false;
			clearScreenWithSymbols();
			centeredPrint("Not connected", SMALL_TEXT);
			DEVICE.Speaker.tone(2000, 200);
		}
	}

	if (isBtnAWasPressed() && checkTimer(100, true)) {
		bleKeyboard.write(KEY_RIGHT_ARROW);
	}

	if (isBtnPWRWasPressed() && checkTimer(100, true)) {
		bleKeyboard.write(KEY_LEFT_ARROW);
	}

	if (checkExit()) {
		bleKeyboard.end();
		isBleConnected = false;
		centeredPrint("Disconnecting...", SMALL_TEXT);
	}
}