void drawScrollbar(int currentCursor, int totalItems, int visibleItems) {
	static int SCROLLBAR_WIDTH = 3;
	static int SCROLLBAR_X = DISP.width() - SCROLLBAR_WIDTH;
	static int SCROLLBAR_Y = getStatusBarOffset();
	static int SCROLLBAR_HEIGHT = DISP.height() - SCROLLBAR_Y;

  if (totalItems <= visibleItems) {
    DISP.fillRect(SCROLLBAR_X, SCROLLBAR_Y, SCROLLBAR_WIDTH, SCROLLBAR_HEIGHT, BGCOLOR);
    return;
  }
  
  int sliderHeight = (SCROLLBAR_HEIGHT * visibleItems) / totalItems;
  if (sliderHeight < 6) sliderHeight = 6;
  
  int availableSpace = SCROLLBAR_HEIGHT - sliderHeight;
  
  int sliderY = SCROLLBAR_Y + (currentCursor * availableSpace) / (totalItems - 1);
  
  DISP.fillRect(SCROLLBAR_X, SCROLLBAR_Y, SCROLLBAR_WIDTH, SCROLLBAR_HEIGHT, BGCOLOR);  
  DISP.fillRect(SCROLLBAR_X, sliderY, SCROLLBAR_WIDTH, sliderHeight, FGCOLOR);
}

void drawMenu(MENU menu[], int size) {
	DISP.setTextSize(2.8);
	if (cursor == size) cursor = cursor % size;
	if (cursor < 0) cursor = size - 1;
	if (cursor > 2 && size <= 2) cursor = 0;
	if (cursor > 2) {

		for (int i = 0 + (cursor - 2); i < size; i++) {
			cursor == i ? DISP.setTextColor(BGCOLOR, FGCOLOR) : DISP.setTextColor(FGCOLOR, BGCOLOR);
			
			DISP.printf(" %-14s\n", menu[i].name);
		}
		
		clearScreenWithSymbols();

	} else {
		for (int i = 0; i < size; i++) {
			cursor == i ? DISP.setTextColor(BGCOLOR, FGCOLOR) : DISP.setTextColor(FGCOLOR, BGCOLOR);

			DISP.printf(" %-14s\n", menu[i].name);
		}
		clearScreenWithSymbols();
	}
	drawScrollbar(cursor, size, 5);
}

int selectedItem = 0;
void menuLoop(MENU menu[], int size, bool updateSelectedItem = false) {
	DEVICE.update();
	if (isBtnBWasPressed() || isWebControlDownWasPressed()) {
		cursorOnTop();
		cursor++;
		drawMenu(menu, size);
	}
	if (isBtnAWasPressed()) {
		cursorOnTop();
		clearScreenWithSymbols();
		cursorOnTop();
		changeProcess(menu[cursor].command);
		if (updateSelectedItem) selectedItem = menu[cursor].command;
		return;
	}
	if (isWebControlUpWasPressed()) {
		cursor--;
		cursorOnTop();
		drawMenu(menu, size);
	}
	if (isWebDataRequested()) {
		webData = generateWebData("menu", generateMenuString(menu, size));
	}
}

bool isMenuItemSelected(int pid) {
	if (pid == selectedItem) {
		selectedItem = -1;
		return true;
	} else return false;
}