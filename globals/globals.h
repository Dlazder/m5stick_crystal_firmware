#include "M5StickCPlus2.h"
#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
DNSServer dnsServer;
WebServer webServer(80);
#include <string>
using std::to_string;

#define SMALL_TEXT 2
#define MEDIUM_TEXT 3
#define BIG_TEXT 4

struct MENU {
  char name[20];
  int command;
};

int cursor = 0;
int currentProc = 0;
bool isSwitching = true;
int rotation = 1;

#define DISP StickCP2.Display

#define serial

#define statusBar 1

uint16_t BGCOLOR=0x0000;
uint16_t FGCOLOR=0xFFF1;

int brightnessMax = 250;
int brightnessStep = 10;
int brightnessDividor = brightnessMax / brightnessStep;
int brightness = 3*brightnessDividor;

int globalTimer = millis();
int globalPreviousTimer = 0;