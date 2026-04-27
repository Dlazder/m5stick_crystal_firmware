// pid 39

void bluetoothInfoLoop() {

	String lines[] = {
		bleName,
		bleAddress,
		"rssi: " + String(bleRssi),
	};

	if (isSetup()) {
		centeredPrintRows(lines, 3, SMALL_TEXT);
	}
	checkExit();
}