void wifiAttackMenuLoop() {
	if (isSetup()) {
		cursorOnTop();
		clearScreenWithSymbols();
		DISP.setCursor(0, 60, 1);
		printlnCenter(wifiMenu[cursor].name, SMALL_TEXT);
		printlnCenter(String(WiFi.RSSI(cursor - 2)), SMALL_TEXT);
	}

	checkExit();
}