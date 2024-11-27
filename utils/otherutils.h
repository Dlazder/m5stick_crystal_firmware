bool isSetup() {
  if (isSwitching) {
    isSwitching = false;
    return true;
  } else {
    return false;
  }
}