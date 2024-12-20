void defaultLoop() {
	if (isSetup()) {
		DISP.setCursor(0, 60, 1);
		printlnCenter("this PID is not", SMALL_TEXT);
		printlnCenter("defined in swicher", SMALL_TEXT);
	}
	checkExit(0);
	if (isWebDataRequested()) {
		String res = generateFunctionElement("this PID is not", SMALL_TEXT, "center") + generateFunctionElement("defined in switcher", SMALL_TEXT, "center");
		webData = generateWebData("function", res);
	}
}