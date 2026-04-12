#include "M5StickCPlus2.h"
#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
DNSServer dnsServer;
WebServer webServer(80);
#include <string>
using std::to_string;

// NFC PN532
#include <Adafruit_PN532.h>
#include <Wire.h>
Adafruit_PN532 nfc(G32, G33, &Wire);


#include "conf.h"
#include "version.h"

// For storage utils
#include <Preferences.h>
Preferences preferences;

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

M5Canvas canvas(&DISP);
M5Canvas statusBarCanvas(&DISP);

uint16_t BGCOLOR=TFT_BLACK;
uint16_t FGCOLOR=TFT_WHITE;
uint16_t colors[] = {TFT_WHITE, TFT_NAVY, TFT_DARKGREEN, TFT_DARKCYAN, TFT_MAROON, TFT_PURPLE, TFT_OLIVE, TFT_LIGHTGREY, TFT_DARKGREY, TFT_BLUE, TFT_GREEN, TFT_CYAN, TFT_RED, TFT_MAGENTA, TFT_YELLOW, TFT_ORANGE, TFT_GREENYELLOW, TFT_PINK, TFT_BROWN, TFT_GOLD, TFT_SILVER, TFT_SKYBLUE, TFT_VIOLET};
const char* colorsEntry[] = {"WHITE", "NAVY", "DARK GREEN", "DARK CYAN", "MAROON", "PURPLE", "OLIVE", "LIGHT GREY", "DARK GREY", "BLUE", "GREEN", "CYAN", "RED", "MAGENTA", "YELLOW", "ORANGE", "GREEN YELLOW", "PINK", "BROWN", "GOLD", "SILVER", "SKY BLUE", "VIOLET"};
int colorIndex = 0;

int TINY_TEXT = 1;
int SMALL_TEXT = 2;
int MEDIUM_TEXT = 3;
int BIG_TEXT = 4;

int currentFontIndex = 0;

const lgfx::IFont* systemFonts[] = {
  &fonts::Font0,          // Basic 8x8
  &fonts::lgfxJapanMincho_8,
  &fonts::lgfxJapanMinchoP_8,
  &fonts::lgfxJapanGothic_8,
  &fonts::lgfxJapanGothicP_8,
  // &fonts::Font2,          // 8x16
  // &fonts::Font4,          // 8x16
  // &fonts::Font6,          // 24x32
  // &fonts::Font7,          // 24x48
  // &fonts::Font8,          // 8x16
  // &fonts::AsciiFont8x16,  // Classic 8x16
  // &fonts::AsciiFont24x48  // Classic 24x48
};

const char* fontNames[] = {
  "Default (Font0)",
  "JapanMincho_8",
  "JapanMinchoP_8",
  "JapanGothic_8",
  "JapanGothicP_8"
  // "Font2 (8x16)",
  // "Font4 (8x16 bold)",
  // "Font6 (24x32)",
  // "Font7 (24x48)",
  // "Font8 (8x16 thin)",
  // "Ascii 8x16",
  // "Ascii 24x48"
};

int brightnessMax = 255;
int brightnessStep = 10;
int brightnessDividor = brightnessMax / brightnessStep;
int brightness = 1*brightnessDividor;
int brightnessMin = brightnessDividor;

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