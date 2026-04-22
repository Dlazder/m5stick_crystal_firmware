// pid 30

void systemInfoLoop() {

	if (isSetup()) {
		centeredPrint("v" + String(FIRMWARE_VERSION), MEDIUM_TEXT);
	}

	checkExit();
}