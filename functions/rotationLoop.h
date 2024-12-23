void rotationLoop() {
  if (isSetup()) {
    DISP.setCursor(0, 60, 1);
    printlnCenter("press A", SMALL_TEXT);
    printlnCenter("to change", SMALL_TEXT);
    printlnCenter("rotation", SMALL_TEXT);
    updateTimer();
  }
  if (isBtnAWasPressed() && checkTimer(100)) {
    if (rotation == 1) {
      rotation = 3;
    } else rotation = 1;
    writeData("rotation", rotation);
    DISP.setRotation(rotation);
    DISP.setCursor(0, 60, 1);
    DISP.clear();
    printlnCenter("press A", SMALL_TEXT);
    printlnCenter("to change", SMALL_TEXT);
    printlnCenter("rotation", SMALL_TEXT);
  }
  checkExit(3);
  if (isWebDataRequested()) {
    String res = generateFunctionElement("press A<br>to change<br>rotation", SMALL_TEXT, "center");
    webData = generateWebData("function", res);
  }
}