// pid 15


void bluetoothShutterLoop() {
	static bool isBleConnected = false;

	if (isSetup()) {
		bleKeyboard.begin();
		centeredPrint("Waiting connection", SMALL_TEXT);
		updateTimer();
	}

	if (bleKeyboard.isConnected()) {
		if (!isBleConnected) {
			centeredPrint("Connected", SMALL_TEXT);
			DEVICE.Speaker.tone(2000, 200);
			isBleConnected = true;
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
		bleKeyboard.write(KEY_RETURN);
	}

	if (checkExit()) {
		bleKeyboard.end();
		isBleConnected = false;
		centeredPrint("Disconnecting...", SMALL_TEXT);
		// The BLE-KEYboard library does not allow you to disconnect from the device completely.
		//We need to modify the library, but then firmware crashes may occur.
	}
}