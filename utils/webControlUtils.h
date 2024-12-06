int webControlUpPressed = false;
int webControlDownPressed = false;
void webControlUp() {
  webControlUpPressed = true;
}
void webControlDown() {
  webControlDownPressed = true;
}
bool webControlDownWasPressed() {
  if (webControlDownPressed) {
    webControlDownPressed = false;
    return true;
  } else return false;
}
bool webControlUpWasPressed() {
  if (webControlUpPressed) {
    webControlUpPressed = false;
    return true;
  } else return false;
}