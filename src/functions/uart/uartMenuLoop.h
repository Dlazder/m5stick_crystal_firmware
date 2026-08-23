// PID::UART

void uartMenuLoop() {
	MENU uartMenu[] = {
		{PID::MAIN_MENU, L->MENU_BACK, Icons::back},
		{PID::UART_TERMINAL, "terminal", Icons::terminal},
		{PID::UART_CONFIG_BAUD, "baud rate", Icons::settings},
		{PID::UART_CONFIG_RX, "RX pin", Icons::settings},
		{PID::UART_CONFIG_TX, "TX pin", Icons::settings},
	};
	int uartMenuSize = sizeof(uartMenu) / sizeof(MENU);

	if (isSetup()) {
		cursor = 0;
		drawMenu(uartMenu, uartMenuSize);
	}
	menuLoop(uartMenu, uartMenuSize);
}
