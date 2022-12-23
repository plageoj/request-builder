# Request Builder

An Arduino library for building HTTP requests.

## Usage for POST request

```c++
#include <RequestBuilder.h>

WiFiClient client;

void postRequest(){
    RequestBuilder *request = new RequestBuilder(
        "POST",
        "example.com",
        "/path/to/resource"
    );

    // Add query parameters
    request->query.add("key", "value");
    // Add request body form data
    request->body.add("data", "value");

    // Establish connection
    client.connect(request->host.c_str(), 80);
    // Send request
    client.print(request->getRequest());

    delete request;

    // Read response and print to serial
    while (client.connected()) {
        String line = client.readStringUntil('\r');
        Serial.println(line);
    }
}
```

For more examples, see the [examples](examples) directory.

## Documentation

### Parameter

A class for storing key-value pairs. Used for storing query parameters and request body form data.

#### add(key, value)

Add a key-value pair to the parameter.

#### remove(key)

Remove a key-value pair with specified key from the parameter.

#### get(key_grue, value_grue)

Get all url-encoded key-value pairs containing with given grue string in `key` `value_grue` `value` `key_grue` `key` ... format.

#### get()

A short-hand of `get("&", "=")`. Get all key-value pairs in `key=value&key=value` format.

#### getRaw(key_grue, value_grue)

Similar to `get(key_grue, value_grue)`, but does not encode the key-value pairs.

#### size()

Get the number of key-value pairs in the parameter.

#### concat(parameter)

Concatenate two parameters, overwriting the original parameter.

#### sort()

Sort the parameter by key alphabetically.

### RequestBuilder

A class for building HTTP requests.

#### new Request(method, host, path)

Create a new request with specified method, host and path.
All parameters can be omitted.

#### host

The host of the request.

#### path

The path of the request.

#### method

The method of the request.

#### query : Parameter

The query parameters of the request.

#### body : Parameter

The request body form data of the request.

#### auth : Parameter

The authentication parameters of the request. Used for making OAuth 1.0 requests.

#### getRequestLine()

Get the request line of the request.
ex: `GET /path/to/resource?key=value&key2=value2 HTTP/1.1`

#### getRequestHeader();

Get all request headers of the request.
The `Host` header is automatically set with the host set at initialization.
When the request has a body, the `Content-Type` header is set to `application/x-www-form-urlencoded` and `Content-Length` header is set to the length of the body.

#### getRequest()

Get the full request content.

#### getParameterString()

This concatenates all the auth, query, body parameters and returns a string in `key=value&key=value` format, sorted by key alphabetically. This is used for generating the signature base string for OAuth 1.0 requests.

#### getUrl(protocol)

Get the URL of the request without query string.
ex: `getUrl("http") ==> http://example.com/path/to/resource`

