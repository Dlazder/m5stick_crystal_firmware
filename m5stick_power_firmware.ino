#include "./globals/globals.h"
#include "./utils/btnUtils.h"
#include "./utils/displayUtils.h"
#include "./utils/timerUtils.h"

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
    // StickCP2.Speaker.tone(8000, 20);
  }
  if (BtnAWasPressed()) {
    DISP.clear();
    cursorOnTop();
    currentProc = menu[cursor].command;
    Serial.printf("Switching to %d process\n", currentProc);
    isSwitching = true;
  }
}


#include "./functions/settingsLoop.h"
#include "./functions/clockLoop.h"

void mainMenuLoop() {
  if (isSetup()) {
    cursorOnTop();
    drawMenu(mainMenu, mainMenuSize);
  }
  menuLoop(mainMenu, mainMenuSize);
}

void batteryLoop() {
  if (checkTimer(3000)) {
    int battery = StickCP2.Power.getBatteryLevel();
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    char text[10];
    sprintf(text, "%d%%", battery);
    centeredPrint(text, SMALL_TEXT);
  }
  checkExit(0);
}

#define ssid "M5Stick"
IPAddress AP_GATEWAY(172, 0, 0, 1);
void wifiApLoop() {
  if (isSetup()) {
    DISP.setTextSize(SMALL_TEXT);
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid);
    WiFi.softAPConfig(AP_GATEWAY, AP_GATEWAY, IPAddress(255, 255, 255, 0));
    centeredPrint("WiFi Ap enabled", SMALL_TEXT);
  }
  checkExit(0);
}


void brightnessLoop() {
  if (isSetup()) {
    char text[50];
    sprintf(text, "brightness: %d", brightness / brightnessDividor);
    centeredPrint(text, SMALL_TEXT);
    updateTimer();
  }
  if (BtnAWasPressed() && checkTimer(100)) {
    DISP.setCursor(0, 60, 1);
    char text[50];
    sprintf(text, "brightness: %d", brightness);

    brightness -= brightnessDividor;
    if (brightness <= 0) brightness = brightnessMax;
    DISP.setBrightness(brightness);
    sprintf(text, "brightness: %d", brightness / brightnessDividor);
    centeredPrint(text, SMALL_TEXT);
  }
  checkExit(3);
}

void rotationLoop() {
  if (isSetup()) {
    DISP.setCursor(0, 60, 1);
    centeredPrint("press A", SMALL_TEXT);
    updateTimer();
  }
  if (BtnAWasPressed() && checkTimer(100)) {
    if (rotation == 1) {
      rotation = 3;
    } else rotation = 1;
    DISP.setRotation(rotation);
    DISP.setCursor(0, 60, 1);
    DISP.clear();
    centeredPrint("press A", SMALL_TEXT);

  }
  checkExit(3);
}

int battery = StickCP2.Power.getBatteryLevel();
int statusBarTimer = 0;
void statusBarLoop() {
  DISP.setTextColor(FGCOLOR);
  DISP.setCursor(8, 8, 1);
  DISP.setTextSize(SMALL_TEXT);
  DISP.printf("PID: %d", currentProc);
  statusBar_batteryLoop();
  DISP.drawLine(0, 30, 250, 30, FGCOLOR);
}
void statusBar_batteryLoop() {
  auto currentTime = StickCP2.Rtc.getDateTime();
  if (checkTimer(3000, true, &statusBarTimer)) battery = StickCP2.Power.getBatteryLevel();
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  DISP.printf(" %d%%", battery);
}

bool isSetup() {
  if (isSwitching) {
    isSwitching = false;
    return true;
  } else {
    return false;
  }
}

void setup() {
  auto cfg = M5.config();
  StickCP2.begin(cfg);
  DISP.setRotation(1);
  DISP.setTextSize(SMALL_TEXT);
  // DISP.setTextFont(&fonts::Orbitron_Light_24);
  DISP.setCursor(0, 0, 1);
  DISP.setBrightness(brightness);
  drawMenu(mainMenu, mainMenuSize);
  Serial.begin(115200);

}

void loop() {
  globalTimer = millis();
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
    case 6:
      rotationLoop();
      break;
  }

  if (statusBar) {
    statusBarLoop();
  }
}