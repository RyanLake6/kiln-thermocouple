#include <ESP8266WiFi.h>
#include "wifi.h"

void setup() {
  Serial.begin(9600);

  Serial.printf("Init\n");
  WiFi.persistent(false);

  ConnectToWifi();

  UploadTemp(1.0);
}

void loop() {
}