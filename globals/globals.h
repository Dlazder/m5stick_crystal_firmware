#include "M5StickCPlus2.h"
#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
DNSServer dnsServer;
WebServer webServer(80);
#include <string>
using std::to_string;

#include "conf.h"

int SMALL_TEXT = 2;
int MEDIUM_TEXT = 3;
int BIG_TEXT = 4;

struct MENU {
  char name[20];
  int command;
};

int cursor = 0;
int process = 0;
bool isSwitching = true;
int rotation = 1;

#define DISP StickCP2.Display

uint16_t BGCOLOR=0x0000;
uint16_t FGCOLOR=0xFFF1;

int brightnessMax = 255;
int brightnessStep = 10;
int brightnessDividor = brightnessMax / brightnessStep;
int brightness = 1*brightnessDividor;

int globalTimer = millis();
int globalPreviousTimer = 0;

int isWebInterfaceEnabled = false;
int btnAWasPressed = false;
int btnBWasPressed = false;

bool webDataRequested = true;
String responseState = "";