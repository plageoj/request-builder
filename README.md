# Request Builder

An Arduino library for building HTTP requests.

## Usage for POST request

```c++
#include <RequestBuilder.h>

WiFiClient client;

void postRequest(){
    Request *request = new RequestBuilder(
        "POST",
        "example.com",
        "/path/to/resource"
    );

    request->queryParam.add("key", "value");
    request->bodyParam.add("data", "value");

    client.connect(request->host.c_str(), 80);
    client.print(request->getRequestString());
    client.print("Host: " + request->host + "\r\n");
    client.print("Connection: close\r\n\r\n");
    client.print(request->bodyParam.get());

    delete request;
}
```