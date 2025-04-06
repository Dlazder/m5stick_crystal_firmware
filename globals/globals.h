#include "M5StickCPlus2.h"
#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
DNSServer dnsServer;
WebServer webServer(80);
#include <string>
using std::to_string;

#include "conf.h"

// For storage utils
#include <Preferences.h>
Preferences preferences;

int TINY_TEXT = 1;
int SMALL_TEXT = 2;
int MEDIUM_TEXT = 3;
int BIG_TEXT = 4;

struct MENU {
  int command;
  String name;
};

int cursor = 0;
int process = 0;
int previousProcess = 0;
bool isSwitching = true;
int rotation = 1;

#define DEVICE StickCP2
#define DISP DEVICE.Display

uint16_t BGCOLOR=TFT_BLACK;
uint16_t FGCOLOR=TFT_WHITE;
uint16_t colors[] = {TFT_WHITE, TFT_NAVY, TFT_DARKGREEN, TFT_DARKCYAN, TFT_MAROON, TFT_PURPLE, TFT_OLIVE, TFT_LIGHTGREY, TFT_DARKGREY, TFT_BLUE, TFT_GREEN, TFT_CYAN, TFT_RED, TFT_MAGENTA, TFT_YELLOW, TFT_ORANGE, TFT_GREENYELLOW, TFT_PINK, TFT_BROWN, TFT_GOLD, TFT_SILVER, TFT_SKYBLUE, TFT_VIOLET};

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
String webData = "";
String webDataType = "";

// wifi deauth
String ssid;
String mac;
int channel;
uint8_t* bssid;
int rssi;


// bluetooth
#include <BleKeyboard.h>
BleKeyboard bleKeyboard;