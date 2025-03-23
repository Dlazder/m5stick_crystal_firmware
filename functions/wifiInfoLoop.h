void wifiInfoLoop() {
	if (isSetup()) {
		DISP.setCursor(0, 50);
		printlnCenter(ssid, SMALL_TEXT);
		printlnCenter(mac, SMALL_TEXT);
		printlnCenter("rssi: " + String(rssi), SMALL_TEXT);
		printlnCenter("channel: " + String(channel), SMALL_TEXT);
	}
	checkExit();
}