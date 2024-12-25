// The status bar is not displayed when scanning, needs to be fixed.
int wifiCount = 0;
MENU* wifiMenu = nullptr;
bool isWifiSelected = false;
void wifiScanLoop() {
	if (isSetup()) {
		if (wifiCount == 0) {
			centeredPrint("Scanning...", SMALL_TEXT);
			wifiCount = WiFi.scanNetworks();
			wifiMenu = new MENU[wifiCount + 2];
		}
		wifiMenu[0].name = "back";
		wifiMenu[0].command = 0;
		wifiMenu[1].name = "rescan";
		wifiMenu[1].command = 8;
		for (int i = 0; i < wifiCount; i++) {
			wifiMenu[i + 2].name = WiFi.SSID(i).substring(0, 12);
			wifiMenu[i + 2].command = i + 2;
		}
		cursorOnTop();
		drawMenu(wifiMenu, wifiCount);
	}
	// if (!isWifiSelected) {
		functionMenuLoop(wifiMenu, wifiCount);
		if (isItemSelected) {
			isItemSelected = false;
			isWifiSelected = true;
			process = 9;
			isSwitching = true;
		}
	// }
}