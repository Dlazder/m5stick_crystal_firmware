// PID::IR_CONFIG_TX — pick the GPIO used for IR transmission.

static int irTxConfigPinIndex = 0;

// Find the index of the current pin in devicePins; snap to the first pin if absent.
static int _irTxPinIndexFor(uint8_t pin) {
	for (int i = 0; i < devicePinsCount; i++) {
		if (devicePins[i] == pin) return i;
	}
	return 0;
}

static void _irTxConfigDraw(uint8_t pin) {
	String lines[] = {
		"IR TX pin",
		"G" + String(pin),
	};
	centeredPrintRows(lines, 2, MEDIUM_TEXT, true);
	drawHintRange();
}

void irConfigureTxLoop() {
	if (isSetup()) {
		irTxConfigPinIndex = _irTxPinIndexFor(irTxPin);
		_irTxConfigDraw(irTxPin);
		updateTimer();
	}

	if ((isBtnAWasPressed() || isKbRightPressed()) && checkTimer(100)) {
		irTxConfigPinIndex = (irTxConfigPinIndex + 1) % devicePinsCount;
		irTxPin = devicePins[irTxConfigPinIndex];
		setData("irTxPin", irTxPin);
		Serial.printf("IR TX pin: GPIO %d\n", irTxPin);
		_irTxConfigDraw(irTxPin);
	}

	if ((isBtnPWRWasPressed() || isKbLeftPressed()) && checkTimer(100)) {
		irTxConfigPinIndex = (irTxConfigPinIndex <= 0) ? devicePinsCount - 1 : irTxConfigPinIndex - 1;
		irTxPin = devicePins[irTxConfigPinIndex];
		setData("irTxPin", irTxPin);
		Serial.printf("IR TX pin: GPIO %d\n", irTxPin);
		_irTxConfigDraw(irTxPin);
	}

	checkExit();
}
