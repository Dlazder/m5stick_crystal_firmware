// PID::UART_CONFIG_TX — pick the GPIO used for UART transmission.

static int _uartTxConfigPinIndex = 0;

static int _uartTxPinIndexFor(uint8_t pin) {
	for (int i = 0; i < devicePinsCount; i++) {
		if (devicePins[i] == pin) return i;
	}
	return 0;
}

static void _uartTxConfigDraw(uint8_t pin) {
	String lines[] = {
		"UART TX pin",
		"G" + String(pin),
	};
	centeredPrintRows(lines, 2, MEDIUM_TEXT, true);
	drawHintRange();
}

void uartConfigTxLoop() {
	if (isSetup()) {
		_uartTxConfigPinIndex = _uartTxPinIndexFor(uartTxPin);
		_uartTxConfigDraw(uartTxPin);
		updateTimer();
	}

	if ((isBtnAWasPressed() || isKbRightPressed()) && checkTimer(100)) {
		_uartTxConfigPinIndex = (_uartTxConfigPinIndex + 1) % devicePinsCount;
		uartTxPin = devicePins[_uartTxConfigPinIndex];
		setData("uartTxPin", uartTxPin);
		_uartTxConfigDraw(uartTxPin);
	}

	if ((isBtnPWRWasPressed() || isKbLeftPressed()) && checkTimer(100)) {
		_uartTxConfigPinIndex = (_uartTxConfigPinIndex <= 0) ? devicePinsCount - 1 : _uartTxConfigPinIndex - 1;
		uartTxPin = devicePins[_uartTxConfigPinIndex];
		setData("uartTxPin", uartTxPin);
		_uartTxConfigDraw(uartTxPin);
	}

	checkExit();
}
