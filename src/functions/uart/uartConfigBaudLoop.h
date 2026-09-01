// PID::UART_CONFIG_BAUD — pick the UART baud rate.

static const uint32_t _uartBauds[] = {
	1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600
};
static const int _uartBaudCount = sizeof(_uartBauds) / sizeof(_uartBauds[0]);

static int _uartBaudIndex = 0;

static int _uartBaudIndexFor(uint32_t baud) {
	for (int i = 0; i < _uartBaudCount; i++) {
		if (_uartBauds[i] == baud) return i;
	}
	return 0;
}

static void _uartBaudDraw(uint32_t baud) {
	String lines[] = {
		"UART baud rate",
		String((unsigned long)baud),
	};
	centeredPrintRows(lines, 2, MEDIUM_TEXT, true);
	drawHintRange();
}

void uartConfigBaudLoop() {
	if (isSetup()) {
		_uartBaudIndex = _uartBaudIndexFor(uartBaud);
		_uartBaudDraw(uartBaud);
		updateTimer();
	}

	if ((isBtnAWasPressed() || isKbRightPressed()) && checkTimer(100)) {
		_uartBaudIndex = (_uartBaudIndex + 1) % _uartBaudCount;
		uartBaud = _uartBauds[_uartBaudIndex];
		setData("uartBaud", uartBaud);
		_uartBaudDraw(uartBaud);
	}

	if ((isBtnPWRWasPressed() || isKbLeftPressed()) && checkTimer(100)) {
		_uartBaudIndex = (_uartBaudIndex <= 0) ? _uartBaudCount - 1 : _uartBaudIndex - 1;
		uartBaud = _uartBauds[_uartBaudIndex];
		setData("uartBaud", uartBaud);
		_uartBaudDraw(uartBaud);
	}

	checkExit();
}
