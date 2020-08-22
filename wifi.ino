#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

int ConnectToWifi() {
    Serial.print("Now connecting to wifi from my mac: ");
    Serial.print(WiFi.macAddress());
    Serial.print("\n");
    wifi_promiscuous_enable(0);
    wifi_set_opmode(STATION_MODE);
    WiFi.begin(ssid, password);

    uint32_t tries = 0;
    while (WiFi.status() != WL_CONNECTED) {
        tries += 1;
        delay(1000);
        Serial.print(".");
        if (tries > 30) {
            WiFi.begin(ssid, password);
        }
        if (tries > 60) {
            Serial.println("Failed to connect");
            return 1;
        }
    }

    /*
    Serial.println("Connected lets see if we can post");
    if (make_post("{}") != 0) {
      Serial.println("We couldn't!!! That's a fail");
      WiFi.disconnect();
      return -1;
    }
    */

    Serial.println(WiFi.localIP());

    return 0;
}