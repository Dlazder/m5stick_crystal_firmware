String ssid = "M5Stick";
IPAddress AP_GATEWAY(172, 0, 0, 1);

void webServerSetup() {
  dnsServer.start(1, "*", AP_GATEWAY);
  webServer.on("/", []() {
    webServer.send(200, "text/html", mainHTML());
  });
  webServer.on("/style.css", []() {
    webServer.send(200, "text/css", mainCSS());
  });
  webServer.on("/index.js", []() {
    webServer.send(200, "text/javascript", mainJS());
  });
  webServer.on("/post", []() {
    String data = webServer.arg("data");
    if (data == "down") {
      webControlDown();
    } else if (data == "up") {
      webControlUp();
    } else if (data == "a") {
      pressBtnA();
    } else if (data == "b") {
      pressBtnB();
    }
    // a.replace("<", "&lt")
    // a.replace(">", "&gt")
  });
  webServer.begin();
}


void wifiApLoop() {
  if (isSetup()) {
    if (!isWebInterfaceEnabled) {
      WiFi.mode(WIFI_AP);
      WiFi.softAP(ssid);
      WiFi.softAPConfig(AP_GATEWAY, AP_GATEWAY, IPAddress(255, 255, 255, 0));
      webServerSetup();
      isWebInterfaceEnabled = true;
    }
    DISP.setTextSize(SMALL_TEXT);
    centeredPrint("WiFi Ap enabled", SMALL_TEXT);
  }
  checkExit(0);
}