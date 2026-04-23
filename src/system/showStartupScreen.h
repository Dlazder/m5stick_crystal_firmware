void showStartupScreen() {
	String lines[] = {
    "Crystal",
    "firmware",
		"",
    "v" + String(FIRMWARE_VERSION),
  };
	int textHeight = 4 * DISP.fontHeight();
	int offsetY =  (DISP.height()) / 2 - textHeight;
	DISP.setTextColor(FGCOLOR);
	DISP.setTextSize(2.5);
	DISP.setCursor(0, offsetY);

	for (int i = 0; i < 4; i++) {
		int textWidth = DISP.textWidth(lines[i].c_str());
		int paddingX = (DISP.width() - textWidth) / 2;
		int cursorY = DISP.getCursorY();
		DISP.setCursor(paddingX, cursorY);
		DISP.println(lines[i].c_str());
	}
}