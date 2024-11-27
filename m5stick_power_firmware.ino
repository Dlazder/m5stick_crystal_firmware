#include "./globals/globals.h"
#include "./utils/btnUtils.h"
#include "./utils/displayUtils.h"
#include "./utils/timerUtils.h"
#include "./utils/webServerUtils.h"

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
#include "./functions/batteryLoop.h"
#include "./functions/brightnessLoop.h"
#include "./functions/rotationLoop.h"
#include "./functions/statusBarLoop.h"

void mainMenuLoop() {
  if (isSetup()) {
    cursorOnTop();
    drawMenu(mainMenu, mainMenuSize);
  }
  menuLoop(mainMenu, mainMenuSize);
}


#define ssid "M5Stick"
IPAddress AP_GATEWAY(172, 0, 0, 1);
void wifiApLoop() {
  if (isSetup()) {
    DISP.setTextSize(SMALL_TEXT);
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid);
    WiFi.softAPConfig(AP_GATEWAY, AP_GATEWAY, IPAddress(255, 255, 255, 0));
    webServerLoop();
    centeredPrint("WiFi Ap enabled", SMALL_TEXT);
  }
  webServer.handleClient();
  checkExit(0);
}

void webServerLoop() {
  dnsServer.start(1, "*", AP_GATEWAY);
  webServer.on("/", []() {
    webServer.send(200, "text/html", mainHTML());
  });
  webServer.on("/style.css", []() {
    webServer.send(200, "text/css", mainCSS());
  });
  webServer.on("/index.js", []() {
    webServer.send(200, "text/javascript", mainJS());
  });
  webServer.on("/post", []() {
    
  })
  webServer.begin();
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