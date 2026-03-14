/**
 * Checks physical button B clicks (and clicks from the web interface)
 */
bool isBtnBWasPressed() {
  if (btnBWasPressed) {
    btnBWasPressed = false;
    return true;
  } else if (StickCP2.BtnB.wasPressed()) {
    return true;
  } else return false;
}

/**
 * Checks physical button A clicks (and clicks from the web interface)
 */
bool isBtnAWasPressed() {
  if (btnAWasPressed) {
    btnAWasPressed = false;
    return true;
  } else if (StickCP2.BtnA.wasPressed()) {
    return true;
  } else return false;
}

/**
 * Emulates a button B press
 */
void pressBtnB() {
  btnBWasPressed = true;
}


/**
 * Emulates a button A press
 */
void pressBtnA() {
  btnAWasPressed = true;
}