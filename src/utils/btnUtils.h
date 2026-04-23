int btnAWasPressed = false;
int btnBWasPressed = false;
int btnPWRWasPressed = false;

/**
 * Checks physical button B clicks (and clicks from the web interface)
 */
bool isBtnBWasPressed() {
  if (btnBWasPressed) {
    btnBWasPressed = false;
    return true;
  } else if (DEVICE.BtnB.wasPressed()) {
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
  } else if (DEVICE.BtnA.wasPressed()) {
    return true;
  } else return false;
}

/**
 * Checks a physical power button clicks (and clicks from the web interface)
 */ 
bool isBtnPWRWasPressed() {
  if (btnPWRWasPressed) {
    btnPWRWasPressed = false;
    return true;
  } else if (M5.BtnPWR.wasClicked()) {
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

/**
 * Emulates a button PWR press
 */
void pressBtnPWR() {
  btnPWRWasPressed = true;
}