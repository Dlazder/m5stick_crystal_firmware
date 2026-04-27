// pid 37

const int kbRowCount = 4;
const int kbColCounts[] = { 12, 12, 12, 12 };

const char kbNormal[4][12] = {
	{ '1','2','3','4','5','6','7','8','9','0','-','=' },
	{ 'q','w','e','r','t','y','u','i','o','p','[',']' },
	{ 'a','s','d','f','g','h','j','k','l',';','\'', '`'},
	{ 'z','x','c','v','b','n','m',',','.','?','/','\\'},
};

const char kbShifted[4][12] = {
	{ '!','@','#','$','%','^','&','*','(',')','_','+' },
	{ 'Q','W','E','R','T','Y','U','I','O','P','{','}' },
	{ 'A','S','D','F','G','H','J','K','L',':','"', '~'},
	{ 'Z','X','C','V','B','N','M','<','>','~','/', '|'},
};

const int kbSpecialRow = 4;
const int kbSpecialCount = 4;
const char* kbSpecialLabels[] = { "exit", "CAP", "ENT", "DEL" };

void drawKeyboardUi(int row, int col, const char* inputBuf, bool capsOn) {
	canvas.clear();
	canvas.setTextSize(SMALL_TEXT);

	int fontH = canvas.fontHeight();
	int specH = fontH + 6;
	int cellH = fontH + 1;

	// Input line
	canvas.setTextColor(FGCOLOR, BGCOLOR);
	String display = String(inputBuf);
	if (display.length() > 14) display = display.substring(display.length() - 14);
	canvas.setCursor(4, 2);
	canvas.print(display + "_");

	// Special keys row
	int specY = 2 + fontH + 2;
	int specW = canvas.width() / kbSpecialCount;
	for (int i = 0; i < kbSpecialCount; i++) {
		int x = i * specW;
		bool sel = (row == kbSpecialRow && col == i);
		bool active = (i == 1 && capsOn);
		if (sel || active) {
			canvas.fillRect(x, specY, specW - 1, specH, FGCOLOR);
			canvas.setTextColor(BGCOLOR, FGCOLOR);
		} else {
			canvas.drawRect(x, specY, specW - 1, specH, FGCOLOR);
			canvas.setTextColor(FGCOLOR, BGCOLOR);
		}
		int labelW = canvas.textWidth(kbSpecialLabels[i]);
		canvas.setCursor(x + (specW - labelW) / 2, specY + 3);
		canvas.print(kbSpecialLabels[i]);
	}

	// Keyboard grid
	int startY = specY + specH + 2;
	for (int r = 0; r < kbRowCount; r++) {
		int cols = kbColCounts[r];
		int cellW = canvas.width() / cols;
		int y = startY + r * cellH;
		for (int c = 0; c < cols; c++) {
			int x = c * cellW;
			bool sel = (r == row && c == col);
			if (sel) {
				canvas.fillRect(x, y, cellW, cellH, FGCOLOR);
				canvas.setTextColor(BGCOLOR, FGCOLOR);
			} else {
				canvas.setTextColor(FGCOLOR, BGCOLOR);
			}
			char ch = capsOn ? kbShifted[r][c] : kbNormal[r][c];
			canvas.setCursor(x + (cellW - canvas.textWidth(String(ch))) / 2, y + 1);
			canvas.print(ch);
		}
	}

	canvas.pushSprite(0, getStatusBarHeight());
}

void bluetoothKeyboardLoop() {
	static bool isBleConnected = false;
	static char inputBuf[64];
	static int inputLen = 0;
	static int cursorRow = 0;
	static int cursorCol = 0;
	static bool capsOn = false;

	if (isSetup()) {
		if (!bleCompositeBegan) {
			bleKeyboard.begin();
			bleCompositeBegan = true;
		}
		inputLen = 0;
		inputBuf[0] = '\0';
		cursorRow = 0;
		cursorCol = 0;
		capsOn = false;
		isBleConnected = false;
		centeredPrint("Waiting connection", SMALL_TEXT);
		updateTimer();
	}

	if (bleKeyboard.isConnected()) {
		if (!isBleConnected) {
			isBleConnected = true;
			drawKeyboardUi(cursorRow, cursorCol, inputBuf, capsOn);
			DEVICE.Speaker.tone(2000, 200);
		}
	} else {
		if (isBleConnected) {
			isBleConnected = false;
			centeredPrint("Not connected", SMALL_TEXT);
			DEVICE.Speaker.tone(2000, 200);
		}
		return;
	}

	DEVICE.update();

	if (isBtnAWasPressed() && checkTimer(150, true)) {
		if (cursorRow == kbSpecialRow) {
			if (cursorCol == 0) {
				isBleConnected = false;
				changeProcess(14);
				return;
			} else if (cursorCol == 1) {
				capsOn = !capsOn;
			} else if (cursorCol == 2) {
				bleKeyboard.write(KEY_RETURN);
			} else {
				if (inputLen > 0) {
					inputLen--;
					inputBuf[inputLen] = '\0';
					bleKeyboard.write(KEY_BACKSPACE);
				}
			}
		} else {
			char ch = capsOn ? kbShifted[cursorRow][cursorCol] : kbNormal[cursorRow][cursorCol];
			bleKeyboard.write((uint8_t)ch);
			if (inputLen < 63) {
				inputBuf[inputLen++] = ch;
				inputBuf[inputLen] = '\0';
			}
		}
		drawKeyboardUi(cursorRow, cursorCol, inputBuf, capsOn);
	}

	if (isBtnBWasPressed() && checkTimer(150, true)) {
		if (cursorRow == kbSpecialRow) {
			cursorCol = (cursorCol + 1) % kbSpecialCount;
		} else {
			cursorCol = (cursorCol + 1) % kbColCounts[cursorRow];
		}
		drawKeyboardUi(cursorRow, cursorCol, inputBuf, capsOn);
	}

	if (isBtnPWRWasPressed() && checkTimer(150, true)) {
		cursorRow = (cursorRow + 1) % (kbRowCount + 1);
		if (cursorRow == kbSpecialRow) {
			cursorCol = min(cursorCol, kbSpecialCount - 1);
		} else {
			cursorCol = min(cursorCol, kbColCounts[cursorRow] - 1);
		}
		drawKeyboardUi(cursorRow, cursorCol, inputBuf, capsOn);
	}

	if (!bleCompositeBegan) checkExit();
}
