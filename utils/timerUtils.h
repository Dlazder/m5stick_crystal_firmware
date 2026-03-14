/**
 * Updates the global timer, it starts running again from 0.
 */
void updateTimer(int *previousTimer = nullptr) {
  if (previousTimer == nullptr) previousTimer = &globalPreviousTimer;
  *previousTimer = globalTimer;
}

/**
 * Checks whether the specified time has passed since the global timer was last updated.
 * Useful for preventing accidental clicks when starting your program, or if you just need to perform an action after a certain period of time.
 */
bool checkTimer(int checkingTime, bool updateTimer = true, int *timer = nullptr) {
  if (timer == nullptr) timer = &globalPreviousTimer;

  if (globalTimer - *timer > checkingTime) {
    if (updateTimer) *timer = globalTimer;
    return true;
  } else return false;
}