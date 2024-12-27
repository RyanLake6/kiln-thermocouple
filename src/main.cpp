#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "wifi.h"
#include "upload.h"
#include "temp.h"
#include "switch.h"

extern WiFiClientSecure client;

void setup() {
  Serial.begin(9600);

  client.setInsecure();

  Serial.printf("Init\n");
  WiFi.persistent(false);
  setupThermometer();
  initSwitch();

  ConnectToWifi();
}

void loop() {
  reconnect();
  UploadTempToInfluxDb(readF());
  // UploadTemp(readF());

  // char attributeUpdate[50];
  // sprintf(attributeUpdate, "{\"switch\":%s}", getSwitchStatus()?"true":"false"); // {"switch":false}
  // SendAttributes(attributeUpdate);

  delay(5000);
}