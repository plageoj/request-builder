#include <RequestBuilder.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>

WiFiMulti wifiMulti;

void setup() {
    Serial.begin(115200);

    // Connect to WiFi network
    // Replace with your network credentials
    wifiMulti.addAP("SSID", "PASSWORD");

    while (wifiMulti.run() != WL_CONNECTED) {
        delay(100);
    }

    // Create a new request
    Request *request = new Request(
        "GET",
        "www.google.com",
        "/search"
    );
    // Add query parameters
    request->queryParam.add("q", "Arduino RequestBuilder");

    WiFiClientSecure client;

    // Use WiFiClientSecure class to create TLS connection
    client.connect(request->host.c_str(), 443, 10000);

    // Send HTTP request
    client.print(request->getRequestString());
    client.print("Host: " + request->host + "\r\n");
    client.print("Connection: close\r\n\r\n");

    // Read all the lines of the reply from server and print them to Serial
    while (client.connected()) {
        String line = client.readStringUntil('\n');
        Serial.println(line);
    }
}

void loop() {
}
