#include "M5StickCPlus2.h"
#include "esp_wifi.h"
#include "./functions/btnUtils.h"


#include <string>
using std::to_string;
#include <WiFi.h>


#define statusBar 1
#define DISP StickCP2.Display
#define serial
#define SMALL_TEXT 2
#define MEDIUM_TEXT 3
#define BIG_TEXT 4

uint16_t BGCOLOR=0x0000;
uint16_t FGCOLOR=0xFFF1;

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

void cursorOnTop() {
    if (statusBar) {
      DISP.setCursor(0, 30, 1);
    } else {
      DISP.setCursor(0, 0, 1);
    }
}

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
void mainMenuLoop() {
  StickCP2.update();
  if (BtnBWasPressed()) {
    cursorOnTop();
    cursor++;
    drawMenu(mainMenu, mainMenuSize);
    StickCP2.Speaker.tone(8000, 20);
  }
  if (BtnAWasPressed()) {
    DISP.clear();
    cursorOnTop();
    currentProc = mainMenu[cursor].command;
    Serial.printf("Switching to %d process\n", currentProc);
    isSwitching = true;
  }
}
void mainMenuSetup() {
  DISP.clear();
  cursorOnTop();
  drawMenu(mainMenu, mainMenuSize);
}

int oldSeconds;
void clockLoop() {
  auto dt = StickCP2.Rtc.getDateTime();
  if (dt.time.seconds != oldSeconds) {
    DISP.setCursor(0, 60, 1);
    int length = 8;
    int padding = (20 - length) / 2;
    char format_string[30];
    sprintf(format_string, "%02d:%02d:%02d", dt.time.hours, dt.time.minutes, dt.time.seconds);
    DISP.printf("%*s", padding + length, format_string);
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
    DISP.setCursor(0, 60, 1);
    int screenWidth = 12;
    int length = to_string(battery).length() + 1;
    int padding = (screenWidth - length) / 2;
    if (length == 4) {
      DISP.printf("%*d%%", padding + length, battery);
    } else {
      DISP.printf("%*d%% ", padding + length, battery);
    }
  }
  checkExit(0);
}
void batterySetup() {
  DISP.setTextSize(MEDIUM_TEXT);
  // reset values for correct first output
  previosMillis = 0;
  currentMillis = 10000;
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

#define ssid "M5Stick"
IPAddress AP_GATEWAY(172, 0, 0, 1);
void wifiApLoop() {
  checkExit(0);
  DISP.setCursor(0, 60, 1);
  int screenWidth = 20;
  int length = 15;
  int padding = (screenWidth - length) / 2;
  DISP.printf("%*s", padding + length, "WiFi Ap enabled");
}
void wifiApSetup() {
  DISP.setTextSize(SMALL_TEXT);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);
  WiFi.softAPConfig(AP_GATEWAY, AP_GATEWAY, IPAddress(255, 255, 255, 0));
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
  Serial.begin(9600);
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
  }
  #if defined(statusBar)
    statusBarLoop();
  #endif
}