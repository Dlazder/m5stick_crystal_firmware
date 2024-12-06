void checkExit(int proc) {
  StickCP2.update();
  if (BtnBWasPressed()) {
    btnAWasPressed = false;
    btnBWasPressed = false;
    currentProc = proc;
    Serial.printf("Switching to %d process\n", currentProc);
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