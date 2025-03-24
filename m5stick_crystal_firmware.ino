#include "./globals/globals.h"
#include "./globals/utils.h"
#include "./globals/functions.h"
#include "./globals/switcher.h"

void setup() {
  auto cfg = M5.config();
  StickCP2.begin(cfg);
  Serial.begin(115200);
  preferences.begin("storage", false);
  
  rotation = getData("rotation", rotation);
  DISP.setRotation(rotation);

  brightness = getData("brightness", brightness);
  DISP.setBrightness(brightness);

  statusBar = getData("statusBar", statusBar);

  FGCOLOR = getData("color", TFT_WHITE);

  cursorOnTop();
  drawMenu(mainMenu, mainMenuSize);
}

void loop() {
  globalTimer = millis();

  if (statusBar) {
    statusBarLoop();
  }
  
  /* global process functions switcher */
  switcher();

  // If webDataRequested = true, this means that the process function has not yet updated the response variable.
  // Once the value is updated, the variable will become false. Until this happens, we do not process requests so as not to send outdated information to the client.
  if (isWebInterfaceEnabled && !webDataRequested) {
    webServer.handleClient();
  }
}