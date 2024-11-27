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