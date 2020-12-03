#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "wifi.h"
#include "upload.h"
#include "temp.h"

extern WiFiClientSecure client;

void setup() {
  Serial.begin(9600);

  client.setInsecure();

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