#include "./globals/globals.h"
#include "./utils/btnUtils.h"
#include "./utils/displayUtils.h"

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
  {"Wi-Fi ap", 4},
};
int mainMenuSize = sizeof(mainMenu) / sizeof(MENU);

void checkExit(int proc) {
  StickCP2.update();
  if (BtnBWasPressed()) {
    currentProc = proc;
    Serial.printf("Switching to %d process\n", currentProc);
    DISP.clear();
    cursorOnTop();
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

void menuLoop(MENU menu[], int size) {
  StickCP2.update();
  if (BtnBWasPressed()) {
    cursorOnTop();
    cursor++;
    drawMenu(menu, size);
    StickCP2.Speaker.tone(8000, 20);
  }
  if (BtnAWasPressed()) {
    DISP.clear();
    cursorOnTop();
    currentProc = menu[cursor].command;
    Serial.printf("Switching to %d process\n", currentProc);
    isSwitching = true;
  }
}


void mainMenuLoop() {
  menuLoop(mainMenu, mainMenuSize);
}
void mainMenuSetup() {
  cursorOnTop();
  drawMenu(mainMenu, mainMenuSize);
}

int oldSeconds;
void clockLoop() {
  auto dt = StickCP2.Rtc.getDateTime();
  if (dt.time.seconds != oldSeconds) {
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    char formatString[30];
    sprintf(formatString, "%02d:%02d:%02d", dt.time.hours, dt.time.minutes, dt.time.seconds);
    centeredPrint(formatString, SMALL_TEXT);
  }
  oldSeconds = dt.time.seconds;
  checkExit(0);
}
void clockSetup() {
  DISP.setTextSize(SMALL_TEXT);
}

const int batteryInterval = 2000;
int currentMillis;
int previosMillis = 0;
void batteryLoop() {
  currentMillis = millis();
  if (currentMillis - previosMillis > batteryInterval) {
    previosMillis = currentMillis;
    int battery = StickCP2.Power.getBatteryLevel();
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    char text[10];
    sprintf(text, "%d%%", battery);
    centeredPrint(text, SMALL_TEXT);
  }
  checkExit(0);
}
void batterySetup() {
  // reset values for correct first output
  previosMillis = 0;
  currentMillis = 10000;
}

MENU settingsMenu[] = {
  {"back", 0},
  {"brightness", 5},
  {"orientation", 6}
};
int settingsMenuSize = sizeof(settingsMenu) / sizeof(MENU);
void settingsLoop() {
  menuLoop(settingsMenu, settingsMenuSize);
}
void settingsSetup() {
  DISP.setTextSize(SMALL_TEXT);
  cursorOnTop();
  cursor = 0;
  drawMenu(settingsMenu, settingsMenuSize);
}

#define ssid "M5Stick"
IPAddress AP_GATEWAY(172, 0, 0, 1);
void wifiApLoop() {
  centeredPrint("WiFi Ap enabled", SMALL_TEXT);
  checkExit(0);
}
void wifiApSetup() {
  DISP.setTextSize(SMALL_TEXT);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);
  WiFi.softAPConfig(AP_GATEWAY, AP_GATEWAY, IPAddress(255, 255, 255, 0));
}

void brightnessLoop() {
  DISP.setCursor(0, 60, 1);
  int brightness = DISP.getBrightness();
  char text[50];
  sprintf(text, "brightness: %d", brightness);
  centeredPrint(text, SMALL_TEXT);
  checkExit(3);
}


auto lastBatteryCheckTime = StickCP2.Rtc.getDateTime();
void statusBar_batteryLoop() {
  auto currentTime = StickCP2.Rtc.getDateTime();
  if (lastBatteryCheckTime.time.minutes != currentTime.time.minutes) {
    int battery = StickCP2.Power.getBatteryLevel();
    // oldBattery = battery;
    lastBatteryCheckTime = currentTime;
    DISP.setCursor(0, 0);
    DISP.print("            ");
  }
  // battery_drawMenu(oldBattery);
}
void statusBarLoop() {
  DISP.setTextColor(FGCOLOR);
  DISP.setCursor(8, 8, 1);
  DISP.setTextSize(SMALL_TEXT);
  DISP.printf("PID: %d", currentProc);
  DISP.drawLine(0, 30, 250, 30);
  // statusBar_batteryLoop();
}

void setup() {
  auto cfg = M5.config();
  StickCP2.begin(cfg);
  DISP.setRotation(1);
  DISP.setTextSize(SMALL_TEXT);
  // DISP.setTextFont(&fonts::Orbitron_Light_24);
  DISP.setCursor(0, 0, 1);
  drawMenu(mainMenu, mainMenuSize);
  Serial.begin(115200);
}

void loop() {
  

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
      case 4:
        wifiApSetup();
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
    case 4:
      wifiApLoop();
      break;
    case 5:
      brightnessLoop();
      break;
  }
  #if defined(statusBar)
    statusBarLoop();
  #endif
}