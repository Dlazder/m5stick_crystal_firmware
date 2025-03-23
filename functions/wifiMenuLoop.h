MENU wifiMenu[] = {
	{"back", 8},
	{"info", 12},
	{"deauth", 11}
};
int wifiMenuSize = sizeof(wifiMenu) / sizeof(MENU);

void wifiMenuLoop() {
	if (isSetup()) {
		if (previousProcess == 8) {
			ssid = WiFi.SSID(cursor - 2);
			mac = WiFi.BSSIDstr(cursor - 2);
			channel = WiFi.channel(cursor - 2);
			bssid = WiFi.BSSID(cursor - 2);
			rssi = WiFi.RSSI(cursor - 2);
			cursor = 0;
		}
		cursorOnTop();
		drawMenu(wifiMenu, wifiMenuSize);
	}
	menuLoop(wifiMenu, wifiMenuSize);
}