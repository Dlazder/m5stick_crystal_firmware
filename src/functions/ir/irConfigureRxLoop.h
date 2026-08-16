// PID::IR_CONFIG_RX — pick the GPIO used for IR reception.

static int irRxConfigPinIndex = 0;

// Find the index of the current pin in devicePins; snap to the first pin if absent.
static int _irRxPinIndexFor(uint8_t pin) {
	for (int i = 0; i < devicePinsCount; i++) {
		if (devicePins[i] == pin) return i;
	}
	return 0;
}

static void _irRxConfigDraw(uint8_t pin) {
	String lines[] = {
		"IR RX pin",
		"G" + String(pin),
	};
	centeredPrintRows(lines, 2, MEDIUM_TEXT, true);
	drawHintRange();
}

void irConfigureRxLoop() {
	if (isSetup()) {
		irRxConfigPinIndex = _irRxPinIndexFor(irRxPin);
		_irRxConfigDraw(irRxPin);
		updateTimer();
	}

	if ((isBtnAWasPressed() || isKbRightPressed()) && checkTimer(100)) {
		irRxConfigPinIndex = (irRxConfigPinIndex + 1) % devicePinsCount;
		irRxPin = devicePins[irRxConfigPinIndex];
		setData("irRxPin", irRxPin);
		Serial.printf("IR RX pin: GPIO %d\n", irRxPin);
		_irRxConfigDraw(irRxPin);
	}

	if ((isBtnPWRWasPressed() || isKbLeftPressed()) && checkTimer(100)) {
		irRxConfigPinIndex = (irRxConfigPinIndex <= 0) ? devicePinsCount - 1 : irRxConfigPinIndex - 1;
		irRxPin = devicePins[irRxConfigPinIndex];
		setData("irRxPin", irRxPin);
		Serial.printf("IR RX pin: GPIO %d\n", irRxPin);
		_irRxConfigDraw(irRxPin);
	}

	checkExit();
}
