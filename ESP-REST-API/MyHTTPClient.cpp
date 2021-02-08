#include "MyHTTPClient.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>


void MyHTTPClient::setFP(const uint8_t* fingerprint){
  memcpy(this->fingerprint, fingerprint, 20);
}


String MyHTTPClient::getRequest(const char* serverName){

    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

    client->setFingerprint(this->fingerprint);

    HTTPClient https;

    String payload = "--";

    Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, serverName)) {  // HTTPS

      Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      int httpCode = https.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          payload = https.getString();
          //Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      https.end();

    }
    return payload;
}
