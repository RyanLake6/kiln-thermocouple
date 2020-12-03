#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

#include "upload_creds.h"

// Initialize the client library
WiFiClientSecure client;

String FormatToJson(double temp) {
    return String("{\"temp\":"+String(temp)+"}");
}

// SendTCP Sends the data to the provided UPLOAD_TCP_SERVER constant
// See this documentation for more details
// https://www.arduino.cc/en/Reference/WiFiClient
int SendTCP(String data) {
    if (!client.connect(UPLOAD_TCP_SERVER, UPLOAD_TCP_PORT)) {
        Serial.println("failed to connect");
        return -1;
    }
    client.print("POST /api/v1/");
    client.print(ACCESS_TOKEN);
    client.println("/telemetry HTTP/1.1");
    client.println("Connection: close");
    client.println("User-Agent: kilnmon-device");
    client.println("Content-Type: application/json");
    client.print("Host: ");
    client.println(UPLOAD_TCP_SERVER);
    client.print("Content-Length: ");
    client.print(data.length());
    client.println();
    client.println();
    client.print(data.c_str());
    client.println();
    client.flush();
    client.stop();

    return 0;
}

// UploadTemp uploads the provided temp to our server
int UploadTemp(double temp) {
    Serial.println("Uploading Temp: "+String(temp));
    SendTCP(FormatToJson(temp));

    return 0;
}


// MakePost makes a POST request to our server
int MakePost(String data) {
    //make sure we are connected via wifi
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("make_post");

        //HTTP Method
        HTTPClient http;
        http.begin(UPLOAD_SERVER);
        http.addHeader("Content-Type", "application/json");
        int httpCode = http.POST(data);
        //String payload = http.getString();
        http.writeToStream(&Serial);
        http.end();
        if (httpCode < 0) {
            Serial.print("Failed to post: ");
            Serial.println(httpCode);
            return -1;
        }
    } else {
        Serial.println("Cannot POST, not connected to wifi");
        return -1;
    }
    return 0;
}
