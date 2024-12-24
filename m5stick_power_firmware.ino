#include "./globals/globals.h"
#include "./globals/utils.h"

#include "./globals/functions.h"

void setup() {
  auto cfg = M5.config();
  StickCP2.begin(cfg);
  Serial.begin(115200);
  preferences.begin("storage", false);
  
  rotation = getData("rotation", rotation);
  DISP.setRotation(rotation);

  brightness = getData("brightness", brightness);
  DISP.setBrightness(brightness);

  FGCOLOR = getData("color", TFT_WHITE);

  cursorOnTop();
  drawMenu(mainMenu, mainMenuSize);
}

void loop() {
  globalTimer = millis();
  /* process functions switcher */
  switch (process) {
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
    case 7:
      colorsLoop();
      break;
    default:
      defaultLoop();
      break;
  }

  if (statusBar) {
    statusBarLoop();
  }

  // If webDataRequested = true, this means that the process function has not yet updated the response variable.
  // Once the value is updated, the variable will become false. Until this happens, we do not process requests so as not to send outdated information to the client.
  if (isWebInterfaceEnabled && !webDataRequested) {
    webServer.handleClient();
  }
}