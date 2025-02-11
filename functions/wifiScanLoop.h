int wifiCount = 0;
MENU* wifiMenu = nullptr;
void wifiScanLoop() {
	if (isSetup()) {
		if (wifiCount == 0 || isMenuItemSelected(8)) {
			cursor = 0;
			centeredPrint("Scanning...", SMALL_TEXT);
			Serial.println("Scanning...");
			wifiCount = WiFi.scanNetworks();
			wifiMenu = new MENU[wifiCount + 2];
			wifiMenu[0].name = "back";
			wifiMenu[0].command = 0;
			wifiMenu[1].name = "rescan";
			wifiMenu[1].command = 8;
			for (int i = 0; i < wifiCount; i++) {
				wifiMenu[i + 2].name = WiFi.SSID(i).substring(0, 12);
				wifiMenu[i + 2].command = 9;
			}
		}
		cursorOnTop();
		drawMenu(wifiMenu, wifiCount + 2);
	}
	menuLoop(wifiMenu, wifiCount + 2, true);
}