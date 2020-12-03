#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

#include "upload_creds.h"

// Initialize the client library
WiFiClientSecure client;

String FormatToJson(double temp) {
    return String("{\"temp\":"+String(temp)+"}");
}

// Post makes a post request to the provided path with the provided body.
// The path must have a prefexed "/" and is the path after the thingsboard ACCESS_TOKEN
// ex: /telemetry
// See: https://thingsboard.io/docs/reference/http-api/
int Post(String path, String body) {
    if (!client.connect(UPLOAD_TCP_SERVER, UPLOAD_TCP_PORT)) {
        Serial.println("failed to connect");
        return -1;
    }
    client.print("POST /api/v1/");
    client.print(ACCESS_TOKEN);
    client.print(path);
    client.println(" HTTP/1.1");
    client.println("Connection: close");
    client.println("User-Agent: kilnmon-device");
    client.println("Content-Type: application/json");
    client.print("Host: ");
    client.println(UPLOAD_TCP_SERVER);
    client.print("Content-Length: ");
    client.print(body.length());
    client.println();
    client.println();
    client.print(body.c_str());
    client.println();
    client.flush();
    client.stop();

    return 0;
}

// SendAttributes send the attributes to the server to update them
int SendAttributes(String attributes) {
    return Post("/attributes", attributes);
}

// SendTelemetry Sends telemetry data to the provided UPLOAD_TCP_SERVER constant
// See this documentation for more details
// https://www.arduino.cc/en/Reference/WiFiClient
int SendTelemetry(String data) {
    return Post("/telemetry", data);
}

// UploadTemp uploads the provided temp to our server
int UploadTemp(double temp) {
    Serial.println("Uploading Temp: "+String(temp));
    return SendTelemetry(FormatToJson(temp));
}
