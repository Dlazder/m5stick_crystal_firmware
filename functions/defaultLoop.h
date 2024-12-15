void defaultLoop() {
	if (isSetup()) {
		DISP.setCursor(0, 60, 1);
		centeredPrint("this PID is not", SMALL_TEXT, true);
		centeredPrint("defined in swicher", SMALL_TEXT, true);
	}
	checkExit(0);
	if (isWebDataRequested()) {
		String res = generateFunctionElement("this PID is not", SMALL_TEXT, "center") + generateFunctionElement("defined in switcher", SMALL_TEXT, "center");
		webData = generateWebData("function", res);
	}
}