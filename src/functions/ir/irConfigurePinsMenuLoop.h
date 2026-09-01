// PID::IR_CONFIG_PINS


void irConfigurePinsMenuLoop() {
	MENU irConfigMenu[] = {
		{PID::IR, L->MENU_BACK, Icons::back},
		{PID::IR_CONFIG_TX, "TX pin"},
		{PID::IR_CONFIG_RX, "RX pin"},
		{PID::IR_CONFIG_RESET, L->MENU_IR_CONFIG_RESET},
	};
	int irConfigMenuSize = sizeof(irConfigMenu) / sizeof(MENU);

	if (isSetup()) {
		if (previousProcess == PID::IR) cursor = 0;
		drawMenu(irConfigMenu, irConfigMenuSize);
	}
	menuLoop(irConfigMenu, irConfigMenuSize);
}
