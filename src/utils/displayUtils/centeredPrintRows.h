void centeredPrintRows(String text[], int arraySize, int textSize) {
	DISP.setTextColor(FGCOLOR, BGCOLOR);
	int currentTextSize = DISP.getTextSizeX();

	DISP.setTextSize(textSize);

	bool isStatusBarEnabled = statusBar;
	int statusBarHeight = isStatusBarEnabled ? 30 : 0;

	int displayWidth = DISP.width();
	int displayHeight = DISP.height();

	int textHeight = arraySize * (DISP.fontHeight());
	
	// calculate top indent
	int offsetY = statusBarHeight + ((displayHeight - statusBarHeight) - textHeight) / 2;
	DISP.setCursor(0, offsetY);
	
	clearScreenWithSymbols();

	DISP.setCursor(0, offsetY);
	for (int i = 0; i < arraySize; i++) {
		int textWidth = DISP.textWidth(text[i].c_str());
		int paddingX = (displayWidth - textWidth) / 2;
		int cursorY = DISP.getCursorY();
		DISP.setCursor(paddingX, cursorY);
		DISP.println(text[i].c_str());
	}

	
	DISP.setTextSize(currentTextSize);
}