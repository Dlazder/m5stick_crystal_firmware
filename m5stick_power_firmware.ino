#include "./globals/globals.h"
#include "./globals/utils.h"

#include "./globals/functions.h"

void setup() {
  auto cfg = M5.config();
  StickCP2.begin(cfg);
  DISP.setRotation(1);
  DISP.setBrightness(brightness);
  cursorOnTop();
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
    default:
      defaultLoop();
      break;
  }

  if (statusBar) {
    statusBarLoop();
  }

  if (isWebInterfaceEnabled) {
    webServer.handleClient();
  }
}