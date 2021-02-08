#include "MyHTTPClient.h"

String webApp;

void downloadWebclient(){
  MyHTTPClient httpClient;
  const uint8_t fingerprint[20] = {0x70, 0x94, 0xDE, 0xDD, 0xE6, 0xC4, 0x69, 0x48, 0x3A, 0x92, 0x70, 0xA1, 0x48, 0x56, 0x78, 0x2D, 0x18, 0x64, 0xE0, 0xB7};
  httpClient.setFP(fingerprint);
  webApp = httpClient.getRequest("https://raw.githubusercontent.com/heazog/RPI-REST-API-RELAY/main/index.html");
  webApp.replace("10.33.33.109",ip);
}

void handleWebapp(){
  if(webApp.length() == 0){
    webclientHost.send(HTTP_CODE_INTERNAL_SERVER_ERROR, "text/plain", "webapp couldn't be loaded");
  }else{
    webclientHost.send(HTTP_CODE_OK, "text/html", webApp);
  }
}

void WebclientHttpServerInit(){
  downloadWebclient();
  webclientHost.on("/", handleWebapp);
  webclientHost.onNotFound([]() {
    webclientHost.send(HTTP_CODE_NOT_FOUND, "text/plain", "page not found");
  });
  webclientHost.begin();
}
