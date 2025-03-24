MENU selectedWifiMenu[] = {
	{"back", 8},
	{"info", 12},
	{"deauth", 11}
};
int selectedWifiMenuSize = sizeof(selectedWifiMenu) / sizeof(MENU);

void selectedWifiMenuLoop() {
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
		drawMenu(selectedWifiMenu, selectedWifiMenuSize);
	}
	menuLoop(selectedWifiMenu, selectedWifiMenuSize);
}