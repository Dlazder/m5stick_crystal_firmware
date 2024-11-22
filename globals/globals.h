#include "M5StickCPlus2.h"
#include <WiFi.h>
#include <string>
using std::to_string;

#define SMALL_TEXT 2
#define MEDIUM_TEXT 3
#define BIG_TEXT 4

#define DISP StickCP2.Display

#define serial

#define statusBar 1

uint16_t BGCOLOR=0x0000;
uint16_t FGCOLOR=0xFFF1;