// PID::IR_CONFIG_RESET

void irConfigureResetLoop() {
	if (isSetup()) {
		String lines[] = {
			"Reset IR pins?",
			"TX: G" + String(irTxPin) + "  RX: G" + String(irRxPin),
		};
		centeredPrintRows(lines, 2, MEDIUM_TEXT, true);
		drawHintCustom("enter: confirm", "A: confirm");
		updateTimer();
	}

	if ((isBtnAWasPressed() || isKbEnterPressed()) && checkTimer(100)) {
		irTxPin = IR_SEND_PIN;
		irRxPin = IR_RECEIVE_PIN;
		setData("irTxPin", irTxPin);
		setData("irRxPin", irRxPin);
		Serial.printf("IR pins reset: TX=%d RX=%d\n", irTxPin, irRxPin);
		
		String lines[] = {
			"IR pins reset",
			"TX: G" + String(irTxPin) + "  RX: G" + String(irRxPin),
		};
		centeredPrintRows(lines, 2, MEDIUM_TEXT);
		soundSuccess();
	}

	checkExit();
}
