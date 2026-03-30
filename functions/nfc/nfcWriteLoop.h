// pid 23

// Hardcoded UID to write (example: 04:12:34:56:78:90)
// Modify this array with your target UID
uint8_t DEFAULT_KEY[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t originalUid[10];
uint8_t originalUidLength = 0;

uint8_t targetUid[] = { 0x04, 0x12, 0x34, 0x56 };
uint8_t targetUidLength = 4;

uint8_t calculateBCC(uint8_t *uid, uint8_t len) {
	uint8_t bcc = 0;
	for (uint8_t i = 0; i < len; i++) {
		bcc ^= uid[i];
	}
	return bcc;
}

void prepareBlock0(uint8_t *newUID, uint8_t *newBlock0, uint8_t uidLength) {
	// Copy UID
	memcpy(newBlock0, newUID, uidLength);
	
	// If UID 4 bytes - adding BCC
	if (uidLength == 4) {
			newBlock0[4] = calculateBCC(newUID, 4);
			newBlock0[5] = 0x08;  // SAK for MIFARE Classic 1K
			newBlock0[6] = 0x04;  // ATQA least significant byte
			newBlock0[7] = 0x00;  // ATQA most significant byte
	}
	// For 7-byte UID (MIFARE Ultralight) structure is different
	// But for CUID usually 4 bytes are used
	
	// Other bytes filled with zeros (or copied from the original tag)
	for (int i = uidLength + 1; i < 16; i++) {
			newBlock0[i] = 0x00;
	}
}

bool isMifareClassic(uint8_t *uid, uint8_t uidLength) {
	// MIFARE Classic usually have 4 bytes UID
	return (uidLength == 4);
}

bool writeNewUID(uint8_t *newUID, uint8_t newUIDLength) {
	uint8_t uid[10];
	uint8_t uidLength;
	
	// Поиск карты (повторяем, чтобы получить свежие данные)
	uint8_t success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 500);
	if (!success) {
		Serial.println("No tag found for writing");
		return false;
	}
	
	Serial.print("Found tag with UID: ");
	for (int i = 0; i < uidLength; i++) {
		Serial.print(uid[i], HEX);
		Serial.print(" ");
	}
	Serial.println();
	
	// Проверяем, поддерживается ли операция
	if (!isMifareClassic(uid, uidLength)) {
		Serial.println("Tag is not MIFARE Classic (CUID required)");
		return false;
	}
	
	// Сохраняем оригинальный UID на случай ошибки
	memcpy(originalUid, uid, uidLength);
	originalUidLength = uidLength;
	
	// Аутентификация для блока 0
	Serial.println("Authenticating for block 0...");
	success = nfc.mifareclassic_AuthenticateBlock(uid, uidLength, 0, 0, DEFAULT_KEY);
	if (!success) {
		Serial.println("Authentication failed! Make sure this is a CUID tag");
		return false;
	}
	
	// Подготовка новых данных для блока 0
	uint8_t newBlock0[16];
	prepareBlock0(newUID, newBlock0, newUIDLength);
	
	Serial.print("Writing new block 0: ");
	for (int i = 0; i < 16; i++) {
		Serial.print(newBlock0[i], HEX);
		Serial.print(" ");
	}
	Serial.println();
	
	// Запись нового блока 0
	success = nfc.mifareclassic_WriteDataBlock(0, newBlock0);
	if (!success) {
		Serial.println("Write failed! Block 0 write error");
		return false;
	}
	
	Serial.println("Block 0 written successfully");
	
	// Небольшая задержка для завершения записи
	delay(200);
	
	// Проверка: перечитываем карту
	success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 500);
	if (success) {
		Serial.print("Verification - New UID: ");
		for (int i = 0; i < uidLength; i++) {
				Serial.print(uid[i], HEX);
				Serial.print(" ");
		}
		Serial.println();
		
		// Проверяем, совпадает ли новый UID с ожидаемым
		bool uidMatches = true;
		for (int i = 0; i < newUIDLength && i < uidLength; i++) {
			if (uid[i] != newUID[i]) {
				uidMatches = false;
				break;
			}
		}
			
		if (uidMatches) {
			Serial.println("UID verification successful!");
			return true;
		} else {
			Serial.println("UID verification failed!");
			return false;
		}
	}
	
	return false;
}

void nfcWriteLoop() {
	if (isSetup()) {
		String lines[] = {
			"PN532: disconnected",
			"Connecting...",
		};
		centeredPrintRows(lines, 2, SMALL_TEXT);

		if (isPN532Connected()) {
			nfc.begin();
			uint32_t versiondata = nfc.getFirmwareVersion();
			if (versiondata) {
				String lines[] = {
					"PN532: connected",
					"Ready to write..."
				};
				centeredPrintRows(lines, 2, SMALL_TEXT);

				Serial.println("PN532: connected");
				Serial.printf("PN532 firmware version: %lu\n", versiondata);
				Serial.println("Waiting for tag to write...");

			} else displayNotConnectedError();
		} else displayNotConnectedError();
	}

	if (checkTimer(2000)) {
		// Module connection check
		if (!isPN532Connected()) {
			if (nfcModuleWasConnected) displayNotConnectedError();
			return;
		}

		nfc.begin();
		uint32_t versionData = nfc.getFirmwareVersion();

		// Update module status
		if (!versionData) {
			if (nfcModuleWasConnected) displayNotConnectedError();
			return;
		} else {
			if (!nfcModuleWasConnected) {
				nfcModuleWasConnected = true;
				DEVICE.Power.setLed(0);
				DEVICE.Speaker.tone(2000, 200);
				
				DISP.clear();
				String lines[] = {
					"PN532: connected",
					"Scanning..."
				};
				centeredPrintRows(lines, 2, SMALL_TEXT);
				Serial.println("PN532: connected");
			}
		}


		// Scanning and writing
		uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
		uint8_t uidLength;
		
		uint8_t success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 100);

		if (success) {
			char uidStr[32];
			sprintf(uidStr, "Found UID: %02X%02X%02X%02X", uid[0], uid[1], uid[2], uid[3]);
			Serial.println("Tag detected, attempting to write...");
			
			bool writeSuccess = writeNewUID(targetUid, targetUidLength);
			
			if (writeSuccess) {
				clearScreenWithSymbols();
				String lines[] = {
					"Write successful!",
					"UID written to tag"
				};
				centeredPrintRows(lines, 2, SMALL_TEXT);

				Serial.println("Write successful!");
				DEVICE.Speaker.tone(2000, 200);
			} else {
				clearScreenWithSymbols();
				String lines[] = {
					"Write failed!",
					"No tag or write error"
				};
				centeredPrintRows(lines, 2, SMALL_TEXT);
				Serial.println("Write failed!");
				DEVICE.Speaker.tone(1000, 200);
			}
			
			updateTimer();
		}
	}

	if (checkExit()) {
		DEVICE.Power.setLed(0);
		nfcModuleWasConnected = false;
	};
}