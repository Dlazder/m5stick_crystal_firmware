void wifiAttackMenuLoop() {
	if (isSetup()) {
		clearScreenWithSymbols();
		DISP.setCursor(0, 60, 1);
		printlnCenter(wifiMenu[cursor].name, SMALL_TEXT);
		printlnCenter(String(WiFi.RSSI(wifiMenu[cursor].command - 2)), SMALL_TEXT);
	}

	checkExit(8);
}