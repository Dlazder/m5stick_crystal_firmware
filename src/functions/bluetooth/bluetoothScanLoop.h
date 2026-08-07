// PID::BT_SCAN

#include <esp_wifi.h>

int bleCount = 0;
MENU* bleScanMenu = nullptr;
static bool _bleScanning = false;
static bool _bleScanDone = false;
static TaskHandle_t _bleScanTask = NULL;

// Background task: pauses WiFi, runs the blocking BLE scan, signals completion.
void bleScanTaskFunc(void* param) {
	esp_wifi_stop();
	delay(20);

	BLEDevice::init("");
	BLEScan* pScan = BLEDevice::getScan();
	pScan->setActiveScan(true);
	pScan->setInterval(100);
	pScan->setWindow(99);
	pScan->clearResults();

	BLEScanResults results = pScan->start(8, false);
	bleCount = results.getCount();
	_bleScanDone = true;
	vTaskDelete(NULL);
}

// Build menu from current scan results (called on completion or late discovery).
static void _bleBuildMenu() {
	_bleScanning = false;
	_bleScanTask = NULL;
	esp_wifi_start();

	BLEScanResults results = BLEDevice::getScan()->getResults();
	bleCount = results.getCount();

	Serial.printf("=== BLE Scan done: %d devices ===\n", bleCount);
	for (int i = 0; i < bleCount; i++) {
		BLEAdvertisedDevice device = results.getDevice(i);
		Serial.printf("  [%d] %s / %s (rssi=%d)\n", i,
			device.getName().c_str(),
			device.getAddress().toString().c_str(),
			device.getRSSI());
	}

	delete[] bleScanMenu;
	bleScanMenu = new MENU[bleCount + 2];
	bleScanMenu[0].name = L->MENU_BACK;
	bleScanMenu[0].command = PID::BLUETOOTH;
	bleScanMenu[0].icon = Icons::back;
	bleScanMenu[0].settingKey = nullptr;
	bleScanMenu[1].name = L->MENU_RESCAN;
	bleScanMenu[1].command = PID::BT_SCAN;
	bleScanMenu[1].icon = Icons::find;
	bleScanMenu[1].settingKey = nullptr;

	for (int i = 0; i < bleCount; i++) {
		BLEAdvertisedDevice device = results.getDevice(i);
		String devName = device.getName().c_str();
		String name = (device.haveName() && devName.length() > 0)
			? devName.substring(0, 14)
			: String(device.getAddress().toString().c_str());

		bleScanMenu[i + 2].name = name;
		bleScanMenu[i + 2].command = PID::BT_SELECTED;
		bleScanMenu[i + 2].icon = nullptr;
		bleScanMenu[i + 2].settingKey = nullptr;
	}

	cursor = 0;
	drawMenu(bleScanMenu, bleCount + 2);
}

void bluetoothScanLoop() {
	if (isSetup()) {
		// Start a fresh scan only on first entry or explicit rescan
		if ((bleCount == 0 || previousProcess == PID::BT_SCAN) && !_bleScanning) {
			delete[] bleScanMenu;
			bleScanMenu = nullptr;
			cursor = 0;
			Serial.println("=== BLE Scan starting (WiFi paused) ===");

			_bleScanDone = false;
			_bleScanning = true;
			xTaskCreate(bleScanTaskFunc, "bleScan", 6144, NULL, 1, &_bleScanTask);
		}

		// If scan finished while we were in another menu — build menu now
		if (!_bleScanning && bleScanMenu == nullptr && _bleScanDone) {
			_bleBuildMenu();
		}

		// Show cached results
		if (!_bleScanning && bleScanMenu != nullptr) {
			drawMenu(bleScanMenu, bleCount + 2);
		}
	}

	// ---- Async scan polling (exactly like WiFi) ----
	if (_bleScanning) {
		if (_bleScanDone) {
			_bleBuildMenu();
		} else {
			centeredPrint(L->TXT_SCANNING, MEDIUM_TEXT, true);
			drawSpinner();
			canvas.pushSprite(0, getStatusBarHeight());

			// Exit leaves scan running — _bleScanning stays true
			if (checkExit(PID::BLUETOOTH)) {
				return;  // Don't kill the task, let it finish in background
			}
			return;
		}
	}

	// ---- Menu navigation ----
	if (!_bleScanning && bleScanMenu != nullptr) {
		menuLoop(bleScanMenu, bleCount + 2);
	}
}
