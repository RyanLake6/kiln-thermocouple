#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <stdlib_noniso.h>

const char* uploadServer    = "";
const char* uploadTCPServer = "";
const uint16_t uploadTCPPort = 5000;

// Initialize the client library
WiFiClient client;

// UploadTemp uploads the provided temp to our server
int UploadTemp(float temp) {
    SendTCP(FormatToJson(temp));
}

// SendTCP Sends the data to the provided uploadTCPServer constant
// See this documentation for more details
// https://www.arduino.cc/en/Reference/WiFiClient
int SendTCP(String data) {
    client.connect(uploadTCPServer, uploadTCPPort);
    client.write(data.c_str());
    client.flush();
    client.stop();
}

// MakePost makes a POST request to our server
int MakePost(String data) {
    //make sure we are connected via wifi
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("make_post");

        //HTTP Method
        HTTPClient http;
        http.begin(uploadServer);
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

String FormatToJson(float temp) {
    return String("{\"temp\":"+String(temp)+"}");
}