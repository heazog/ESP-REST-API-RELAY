

void handleToggleRelay(){
  if(apiHost.args() == 1 && apiHost.argName(0) == "relay"){
    String relay = apiHost.arg(0);
    devices.toggle(relay);
    if(devices.getState(relay)){
      apiHost.send(HTTP_CODE_OK, "text/json", "{\"msg\": \"Relay will be turned on\", \"state\": true, \"error\": 0}");
    } else {
      apiHost.send(HTTP_CODE_OK, "text/json", "{\"msg\": \"Relay will be turned off\", \"state\": false, \"error\": 0}");
    }
  } else{
    apiHost.send(HTTP_CODE_OK, "text/json", "{\"msg\": \"Relay not found!\", \"error\": 1}"); 
  }
  
}


void handleGetRelay(){
  if(apiHost.args() == 1 && apiHost.argName(0) == "relay"){
    String relay = apiHost.arg(0);
    if(devices.getState(relay)){
      apiHost.send(HTTP_CODE_OK, "text/json", "{\"msg\": \"Relay is on\", \"state\": true, \"error\": 0}");
    } else {
      apiHost.send(HTTP_CODE_OK, "text/json", "{\"msg\": \"Relay is off\", \"state\": false, \"error\": 0}");
    }
  } else{
    apiHost.send(HTTP_CODE_OK, "text/json", "{\"msg\": \"Relay not found!\", \"error\": 1}"); 
  }
  
}

void ApiHttpServerInit(){
  apiHost.enableCORS(true);
  apiHost.on("/togglerelay", handleToggleRelay);
  apiHost.on("/getrelay", handleGetRelay);
  apiHost.onNotFound([]() {
    apiHost.send(HTTP_CODE_NOT_FOUND, "text/plain", "page not found");
  });
  apiHost.begin();
}
