#include <RequestBuilder.h>
#include <WiFiClientSecure.h>
#include <WiFiMulti.h>

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
      "POST",
      "httpbin.org",
      "/post");

  // Add headers. Host header is set automatically.
  request->header.add("Accept", "application/json");
  request->header.add("Connection", "close");

  // Add request body
  // When request body is set, the Content-Type header is set to application/x-www-form-urlencoded
  // and the Content-Length header is set automatically
  request->body.add("sender", "arduino");
  request->body.add("message", "Hello HTTPBin!");

  WiFiClientSecure client;

  // Disable certificate validation
  // This is not recommended for production use
  client.setInsecure();

  // Use WiFiClientSecure class to create TLS connection
  client.connect(request->host.c_str(), 443, 10000);

  // Send HTTP request
  client.print(request->getRequest());

  // Release memory
  delete request;

  // Read all the lines of the reply from server and print them to Serial
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    Serial.println(line);
  }
}

void loop() {
}
