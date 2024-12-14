void checkExit(int proc) {
  StickCP2.update();
  if (isBtnBWasPressed()) {
    btnAWasPressed = false;
    btnBWasPressed = false;
    process = proc;
    Serial.printf("Switching to %d process\n", process);
    DISP.clear();
    cursorOnTop();
    isSwitching = true;

  }
}

bool isSetup() {
  if (isSwitching) {
    isSwitching = false;
    return true;
  } else {
    return false;
  }
}