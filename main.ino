#include <ESP8266WiFi.h>
#include "wifi.h"

void setup() {
  Serial.begin(9600);

  Serial.printf("Init\n");
  WiFi.persistent(false);

  ConnectToWifi();
}

void loop() {
  UploadTemp(float(millis()));
  delay(5000);
}