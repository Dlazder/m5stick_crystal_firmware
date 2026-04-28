// pid 38

MENU selectedBluetoothMenu[] = {
	{36, "back"},
	{39, "info"},
	{40, "find"},
};
int selectedBluetoothMenuSize = sizeof(selectedBluetoothMenu) / sizeof(MENU);

void selectedBluetoothMenuLoop() {
	if (isSetup()) {
		if (previousProcess == 36) {
			int idx = cursor - 2;
			BLEScanResults results = BLEDevice::getScan()->getResults();
			BLEAdvertisedDevice device = results.getDevice(idx);
			String devName = device.getName().c_str();
			bleAddress = device.getAddress().toString().c_str();
			bleRssi = device.getRSSI();
			bleName = (device.haveName() && devName.length() > 0) ? devName : "unnamed";
			cursor = 0;
		}
		cursorOnTop();
		drawMenu(selectedBluetoothMenu, selectedBluetoothMenuSize);
	}

	menuLoop(selectedBluetoothMenu, selectedBluetoothMenuSize);
}