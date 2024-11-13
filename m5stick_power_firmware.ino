#include "M5StickCPlus2.h"
#define DISP StickCP2.Display
#include "./functions/btnUtils.h"

// #define statusBar
#define SMALL_TEXT 2
#define MEDIUM_TEXT 3
#define BIG_TEXT 4

uint16_t BGCOLOR=0x0000; // placeholder
uint16_t FGCOLOR=0xFFF1; // placeholder

struct MENU {
  char name[20];
  int command;
};
int cursor = 0;
int currentProc = 0;
bool isSwitching = true;

MENU mainMenu[] = {
  {"clock", 1},
  {"Battery info", 2},
  {"settings", 3},
  {"settings", 3},
  {"settings", 3},
  {"Battery info", 2},
};

int mainMenuSize = sizeof(mainMenu) / sizeof(MENU);

void checkExit(int proc) {
  StickCP2.update();
  if (BtnBWasPressed()) {
    currentProc = proc;
    DISP.clear();
    DISP.setCursor(0, 0, 1);
    isSwitching = true;
  }
}


void drawMenu(MENU menu[], int size) {
  DISP.setTextSize(MEDIUM_TEXT);
  DISP.fillScreen(BGCOLOR);
  if (cursor == size) cursor = cursor % size;
  if (cursor > 4) {
    for (int i = 0 + (cursor - 4); i < size; i++) {
      if (cursor == i) {
        DISP.setTextColor(BGCOLOR, FGCOLOR);
      }
      DISP.printf(" %-12s\n", menu[i].name);
      DISP.setTextColor(FGCOLOR, BGCOLOR);
    }
  } else {
    for (int i = 0; i < size; i++) {
      if (cursor == i) {
        DISP.setTextColor(BGCOLOR, FGCOLOR);
      }
      DISP.printf(" %-12s\n", menu[i].name);
      DISP.setTextColor(FGCOLOR, BGCOLOR);
    }
  }
}
void mainMenuLoop() {
  StickCP2.update();
  if (BtnBWasPressed()) {
    DISP.setCursor(0, 0, 1);
    cursor++;
    drawMenu(mainMenu, mainMenuSize);
    StickCP2.Speaker.tone(8000, 20);
  }
  if (BtnAWasPressed()) {
    DISP.clear();
    DISP.setCursor(0, 0, 1);
    currentProc = mainMenu[cursor].command;
    isSwitching = true;
  }
}
void mainMenuSetup() {
  DISP.clear();
  DISP.setCursor(0, 0, 1);
  drawMenu(mainMenu, mainMenuSize);
}

int oldSeconds;
void clockLoop() {
  auto dt = StickCP2.Rtc.getDateTime();
  if (dt.time.seconds != oldSeconds) {
    DISP.setCursor(0, 60, 1);
    int padding = (20 - 8) / 2;
    char format_string[30];
    sprintf(format_string, "%02d:%02d:%02d", dt.time.hours, dt.time.minutes, dt.time.seconds);
    DISP.printf("%*s", padding + 8, format_string);
  }
  oldSeconds = dt.time.seconds;
  checkExit(0);
}
void clockSetup() {
  DISP.setTextSize(SMALL_TEXT);
}

int oldBattery;
void battery_drawMenu(int battery) {
  DISP.setCursor(0, 60, 1);
  int screenWidth = 20;
  int length = 3;
  int padding = (screenWidth - length) / 2;
  DISP.printf("%*d%%", padding + length, battery);
}
void batteryLoop() {
  int battery = StickCP2.Power.getBatteryLevel();
  battery_drawMenu(battery);
  oldBattery = battery;
  checkExit(0);
}
void batterySetup() {
  DISP.setTextSize(SMALL_TEXT);
}

bool isPrinted = false;
void settingsLoop() {
  int padding = (20 - 8) / 2;
  DISP.setCursor(0, 60, 1);
  DISP.printf("%*s\n", padding + 8, "Settings");
  checkExit(0);
}
void settingsSetup() {
  DISP.setTextSize(SMALL_TEXT);
}

auto lastBatteryCheckTime = StickCP2.Rtc.getDateTime();
void statusBar_batteryLoop() {
  auto currentTime = StickCP2.Rtc.getDateTime();
  if (lastBatteryCheckTime.time.minutes != currentTime.time.minutes) {
    int battery = StickCP2.Power.getBatteryLevel();
    oldBattery = battery;
    lastBatteryCheckTime = currentTime;
    DISP.setCursor(0, 0);
    DISP.print("            ");
  }
  battery_drawMenu(oldBattery);
}
void statusBarLoop() {
  DISP.drawLine(0, 30, 250, 30);
  statusBar_batteryLoop();
}

void setup() {
  auto cfg = M5.config();
  StickCP2.begin(cfg);
  DISP.setRotation(1);
  DISP.setTextSize(SMALL_TEXT);
  // DISP.setTextFont(&fonts::Orbitron_Light_24);
  DISP.setCursor(0, 0, 1);
  drawMenu(mainMenu, mainMenuSize);
}

void loop() {
  #if defined(statusBar)
    statusBarLoop();
  #endif

  /* process setup functions switcher */
  if (isSwitching) {
    isSwitching = false;
    switch (currentProc) {
      case 0:
        mainMenuSetup();
        break;
      case 1:
        clockSetup();
        break;
      case 2:
        batterySetup();
        break;
      case 3:
        settingsSetup();
        break;
    }
  }

  /* process functions switcher */
  switch (currentProc) {
    case 0:
      mainMenuLoop();
      break;
    case 1:
      clockLoop();
      break;
    case 2:
      batteryLoop();
      break;
    case 3:
      settingsLoop();
      break;
  }
}