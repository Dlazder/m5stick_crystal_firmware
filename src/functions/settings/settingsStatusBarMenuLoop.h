// PID::SETTINGS_STATUS_BAR

void settingsStatusBarMenuLoop() {
	MENU settingsStatusBarMenu[] = {
		{PID::SETTINGS,              L->MENU_BACK, Icons::back},
		{PID::TOGGLE_STATUS_BAR,     L->MENU_SETTINGS_STATUS_BAR, nullptr, "statusBar"},
		{PID::TOGGLE_STATUS_BAR_PID, L->MENU_SETTINGS_STATUS_BAR_PID, nullptr, "statusBarPid"},
		{PID::PLACEHOLDER, "seconds", nullptr, "sbSeconds"},
	};
	int settingsStatusBarMenuSize = sizeof(settingsStatusBarMenu) / sizeof(MENU);

	if (isSetup()) {
		if (previousProcess == PID::SETTINGS) cursor = 0;
		drawMenu(settingsStatusBarMenu, settingsStatusBarMenuSize);
	}
	menuLoop(settingsStatusBarMenu, settingsStatusBarMenuSize);
}
