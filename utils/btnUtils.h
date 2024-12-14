bool isBtnBWasPressed() {
  if (btnBWasPressed) {
    btnBWasPressed = false;
    return true;
  } else if (StickCP2.BtnB.wasPressed()) {
    return true;
  } else return false;
}

bool isBtnAWasPressed() {
  if (btnAWasPressed) {
    btnAWasPressed = false;
    return true;
  } else if (StickCP2.BtnA.wasPressed()) {
    return true;
  } else return false;
}

void pressBtnB() {
  btnBWasPressed = true;
}
void pressBtnA() {
  btnAWasPressed = true;
}