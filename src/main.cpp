#include <ESP8266WiFi.h>
#include "wifi.h"
#include "upload.h"
#include "temp.h"

void setup() {
  Serial.begin(9600);

  Serial.printf("Init\n");
  WiFi.persistent(false);
  setupThermometer();

  ConnectToWifi();
}

void loop() {
  reconnect();
  UploadTemp(readF());
  delay(5000);
}