// pid: 15

bool isBleShutterConnected = false;

void bluetoothShutterLoop() {
	if (isSetup()) {
		bleKeyboard.begin();
		if (!bleKeyboard.isConnected()) {
			centeredPrint("Not connected", SMALL_TEXT);
		} else {
			centeredPrint("Connected", SMALL_TEXT);
			isBleShutterConnected = true;
		}
		
	}
	if (!isBleShutterConnected) {
		if (bleKeyboard.isConnected()) {
			clearScreenWithSymbols();
			centeredPrint("Connected", SMALL_TEXT);
			isBleShutterConnected = true;
		}
	}
	if (isBtnAWasPressed()) {
		bleKeyboard.write(KEY_RETURN);
	}

	if (checkExit()) {
		// The BLE-KEYboard library does not allow you to disconnect from the device.
	}
}