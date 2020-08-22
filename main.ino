#include <ESP8266WiFi.h>
#include "wifi.h"

void setup() {
  Serial.begin(9600);

  Serial.printf("Init\n");
  WiFi.persistent(false);

  ConnectToWifi();
  //delay(3000);
  //make_post("test");

  // Enable the watchdog incase of failure
  // ESP.wdtEnable(61000);
  UploadTemp(1.0);
}

void loop() {
}