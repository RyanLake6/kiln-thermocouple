#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

#include "upload_creds.h"

// Initialize the client library
WiFiClient client;

String FormatToJson(double temp) {
    return String("{\"temp\":"+String(temp)+"}");
}


// SendTCP Sends the data to the provided UPLOAD_TCP_SERVER constant
// See this documentation for more details
// https://www.arduino.cc/en/Reference/WiFiClient
int SendTCP(String data) {
    client.connect(UPLOAD_TCP_SERVER, UPLOAD_TCP_PORT);
    client.write("POST /api/v1/");
    client.write(ACCESS_TOKEN);
    client.write("/telemetry\n\n  HTTP/1.1");
    client.write(data.c_str());
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
