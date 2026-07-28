// PID::WIFI_INFO

void wifiInfoLoop() {
	if (isSetup()) {
		wiuBegin(bssid, channel);
	}
	wiuUpdate();

	String lines[] = {
		ssid,
		"MAC: " + mac,
		"Security: " + String(wiuAuthStr(wifiAuthMode)),
		"WPS: "     + String(wiuDone() ? (wiuHasWps() ? "ON" : "OFF") : "..."),
		"FT-PSK: "  + String(wiuDone() ? (wiuHasFt()  ? "ON" : "OFF") : "..."),
		"Ch:" + String(channel) + "  RSSI:" + String(rssi),
	};
	centeredPrintRows(lines, 6, TINY_TEXT);

	if (checkExit()) {
		wiuCleanup();
	}
}
