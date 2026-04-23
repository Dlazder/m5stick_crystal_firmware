int webControlUpPressed = false;
int webControlDownPressed = false;
void webControlUp() {
  webControlUpPressed = true;
}
void webControlDown() {
  webControlDownPressed = true;
}
bool isWebControlDownWasPressed() {
  if (webControlDownPressed) {
    webControlDownPressed = false;
    return true;
  } else return false;
}
bool isWebControlUpWasPressed() {
  if (webControlUpPressed) {
    webControlUpPressed = false;
    return true;
  } else return false;
}