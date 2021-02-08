#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <Arduino.h>
#include <vector>

const int cDebounceTime = 500;

struct Button{
  uint8_t pin;
  uint8_t value;
  unsigned long debounceTime;
};

struct Device{
  String deviceName;
  uint8_t relayPin;
  uint8_t ledPin;
  Button button;
  bool state;
};

class DeviceManager{
private:
  std::vector<Device> dev;
public:
  DeviceManager() = default;

  void addDevice(String deviceName, uint8_t relay=0xFF, uint8_t button=0xFF, uint8_t led=0xFF);
  void toggle(String relay);
  bool getState(String relay);
  void checkButtons();
};

#endif
