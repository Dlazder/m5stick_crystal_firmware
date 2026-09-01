// PID::UART_CONFIG_RX — pick the GPIO used for UART reception.

static int _uartRxConfigPinIndex = 0;

static int _uartRxPinIndexFor(uint8_t pin) {
	for (int i = 0; i < devicePinsCount; i++) {
		if (devicePins[i] == pin) return i;
	}
	return 0;
}

static void _uartRxConfigDraw(uint8_t pin) {
	String lines[] = {
		"UART RX pin",
		"G" + String(pin),
	};
	centeredPrintRows(lines, 2, MEDIUM_TEXT, true);
	drawHintRange();
}

void uartConfigRxLoop() {
	if (isSetup()) {
		_uartRxConfigPinIndex = _uartRxPinIndexFor(uartRxPin);
		_uartRxConfigDraw(uartRxPin);
		updateTimer();
	}

	if ((isBtnAWasPressed() || isKbRightPressed()) && checkTimer(100)) {
		_uartRxConfigPinIndex = (_uartRxConfigPinIndex + 1) % devicePinsCount;
		uartRxPin = devicePins[_uartRxConfigPinIndex];
		setData("uartRxPin", uartRxPin);
		_uartRxConfigDraw(uartRxPin);
	}

	if ((isBtnPWRWasPressed() || isKbLeftPressed()) && checkTimer(100)) {
		_uartRxConfigPinIndex = (_uartRxConfigPinIndex <= 0) ? devicePinsCount - 1 : _uartRxConfigPinIndex - 1;
		uartRxPin = devicePins[_uartRxConfigPinIndex];
		setData("uartRxPin", uartRxPin);
		_uartRxConfigDraw(uartRxPin);
	}

	checkExit();
}
