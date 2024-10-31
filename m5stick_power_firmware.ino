#include "M5StickCPlus2.h"
#define DISP StickCP2.Display

// #define statusBar
#define SMALL_TEXT 3

uint16_t BGCOLOR=0x0000; // placeholder
uint16_t FGCOLOR=0xFFF1; // placeholder

struct MENU {
  char name[20];
  int command;
};
int cursor = 0;
int currentProc = 0;

MENU mainMenu[] = {
  {"clock", 1},
  {"Battery info", 2},
  {"settings", 3},
  {"settings", 3},
  {"settings", 3},
  {"settings", 3},
  {"settings", 3},
  {"Battery info", 2},
};

int mainMenuSize = sizeof(mainMenu) / sizeof(MENU);

bool checkBtnBPressed() {
  if (StickCP2.BtnB.wasPressed()) {
    return true;
  } else return false;
}
void checkExit(int proc) {
  StickCP2.update();
  if (checkBtnBPressed()) {
    currentProc = proc;
    DISP.clear();
    DISP.setCursor(0, 0, 1);
    drawMenu(mainMenu, mainMenuSize);
  }
}


void drawMenu(MENU menu[], int size) {
  DISP.setTextSize(SMALL_TEXT);
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
  if (StickCP2.BtnB.wasPressed()) {
    DISP.clear();
    DISP.setCursor(0, 0, 1);
    cursor++;
    drawMenu(mainMenu, mainMenuSize);
    StickCP2.Speaker.tone(8000, 20);
  }
  if (StickCP2.BtnA.wasPressed()) {
    DISP.clear();
    DISP.setCursor(0, 0, 1);
    currentProc = mainMenu[cursor].command;
  }
}


int oldSeconds;
void clockLoop() {
  auto dt = StickCP2.Rtc.getDateTime();
  if (dt.time.seconds != oldSeconds) {
    // DISP.clear();
    DISP.setCursor(10, 40, 7);
    M5.Lcd.printf("%02d:%02d:%02d\n", dt.time.hours, dt.time.minutes, dt.time.seconds);
  }
  oldSeconds = dt.time.seconds;
  // checkExit(0);
}

int oldBattery;
void battery_drawMenu(int battery) {
  DISP.setCursor(0, 0, 1);
  DISP.fillScreen(BGCOLOR);
  DISP.print(battery);
}
void batteryLoop() {
  delay(500);
  int battery = StickCP2.Power.getBatteryLevel();
  if (battery != oldBattery) {
    battery_drawMenu(battery);
  }
  oldBattery = battery;
  // checkExit(0, drawMenu(mainMenu, mainMenuSize));
}

bool isPrinted = false;
void settingsLoop() {
  StickCP2.update();

  if (!isPrinted) {
    DISP.setCursor(0, 30);
    DISP.print("Settings");
    // isPrinted = true;
  }
  checkExit(0);
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