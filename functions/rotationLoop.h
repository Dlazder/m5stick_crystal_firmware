void rotationLoop() {
  if (isSetup()) {
    DISP.setCursor(0, 60, 1);
    centeredPrint("press A", SMALL_TEXT, true);
    centeredPrint("to change", SMALL_TEXT, true);
    centeredPrint("rotation", SMALL_TEXT, true);
    updateTimer();
  }
  if (BtnAWasPressed() && checkTimer(100)) {
    if (rotation == 1) {
      rotation = 3;
    } else rotation = 1;
    DISP.setRotation(rotation);
    DISP.setCursor(0, 60, 1);
    DISP.clear();
    centeredPrint("press A", SMALL_TEXT, true);
    centeredPrint("to change", SMALL_TEXT, true);
    centeredPrint("rotation", SMALL_TEXT, true);
  }
  checkExit(3);
  if (isStateRequested()) {
    
  }
}