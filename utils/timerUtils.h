void updateTimer(int *previousTimer = nullptr) {
  if (previousTimer == nullptr) previousTimer = &globalPreviousTimer;
  *previousTimer = globalTimer;
}

bool checkTimer(int checkingTime, bool updateTimer = true, int *timer = nullptr) {
  if (timer == nullptr) timer = &globalPreviousTimer;

  if (globalTimer - *timer > checkingTime) {
    if (updateTimer) *timer = globalTimer;
    return true;
  } else return false;
}