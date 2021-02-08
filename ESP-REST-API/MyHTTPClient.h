#ifndef MYHTTPCLIENT_H
#define MYHTTPCLIENT_H

#include <ESP8266HTTPClient.h>


class MyHTTPClient{
  private:
    uint8_t fingerprint[20];
  public:
    MyHTTPClient() = default;
    void setFP(const uint8_t* fingerprint);
    String getRequest(const char* serverName);
};

#endif
