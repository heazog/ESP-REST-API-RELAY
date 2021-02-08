
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <ESP8266HTTPClient.h>

#include "DeviceManager.h"

ESP8266WebServer webclientHost(80);
ESP8266WebServer apiHost(8080);

DeviceManager devices;

String ip;


void setup(void) {
  
  Serial.begin(115200);

  devices.addDevice("LAMP", 5, 4, 2);
  
  WifiConnect("WIFI_NAME", "WIFI_PASS");
  
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  ApiHttpServerInit();
  WebclientHttpServerInit();
  Serial.println("HTTP server started");
  
}

void loop(void) {
  webclientHost.handleClient();
  apiHost.handleClient();

  MDNS.update();
  devices.checkButtons();
}
