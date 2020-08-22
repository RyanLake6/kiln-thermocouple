#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <stdlib_noniso.h>

const char* uploadServer    = "http://10.0.0.37:12345/test";

// UploadTemp uploads the provided temp to our server
int UploadTemp(float temp) {
    MakePost(FormatToJson(temp));
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