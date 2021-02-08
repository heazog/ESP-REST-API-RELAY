#include "DeviceManager.h"

void DeviceManager::addDevice(String deviceName, uint8_t relay, uint8_t button, uint8_t led){
  Button btn = {button, HIGH, 0};
  this->dev.push_back({deviceName, relay, led, btn, false});
  digitalWrite(relay, HIGH);
  digitalWrite(led, HIGH);
  pinMode(relay, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
}

void DeviceManager::toggle(String relay){
  for(Device& device: dev){
    if(device.deviceName == relay){
      device.state = !device.state;
      digitalWrite(device.relayPin, (device.state ? LOW : HIGH));
      digitalWrite(device.ledPin, (device.state ? LOW : HIGH));
    }
  }
}

bool DeviceManager::getState(String relay){
  for(Device& device: dev){
    if(device.deviceName == relay){
      return device.state;
    }
  }
}

void DeviceManager::checkButtons(){
  for(Device& device: dev){
    int newVal = digitalRead(device.button.pin);
    if(device.button.value != newVal){
      if(millis()-device.button.debounceTime > cDebounceTime){
        device.button.debounceTime = millis();
        device.button.value = newVal;
        if(newVal == LOW){
          toggle(device.deviceName); 
        }
      }
    }
  }
}
