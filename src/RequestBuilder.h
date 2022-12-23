#ifndef _PLAGEOJ_REQUEST_BUILDER_H
#define _PLAGEOJ_REQUEST_BUILDER_H

#include <Arduino.h>

#include "Parameter.h"

/**
 * Represents a HTTP request.
 */
class RequestBuilder {
public:
  RequestBuilder();

  /**
   * Set the HTTP method of the request.
   * @param method The HTTP method to set (like GET, POST).
   */
  RequestBuilder(String method) {
    this->method = method;
  };
  /**
   * Set the HTTP method and host of the request.
   * @param method The HTTP method to set (like GET, POST).
   * @param path The host of the request (like www.example.com).
   */
  RequestBuilder(String method, String host) {
    this->method = method;
    this->host = host;
  };
  /**
   * Set the HTTP method, host and path of the request.
   * @param method The HTTP method to set (like GET, POST).
   * @param host The host of the request (like www.example.com).
   * @param path The path of the request (like /path/to/file.html).
   */
  RequestBuilder(String method, String host, String path) {
    this->method = method;
    this->host = host;
    this->path = path;
  };

  /**
   * Get the HTTP request line.
   * @returns The first line of HTTP request.
   */
  String getRequestLine();
  /**
   * Get the request header block.
   * Host header is added automatically.
   * When the request has a body, Content-Length and Content-Type headers are added automatically.
   * @returns The request header block.
   */
  String getRequestHeader();
  /**
   * Get the complete request including request line, header block and body.
   * @returns The complete request.
   */
  String getRequest();
  /**
   * Merge and sort all parameters in the
   * query/body/Authorization-header of the request.
   * @returns Sorted parameters as query string.
   */
  String getParameterString();
  /**
   * Returns URL without query string.
   * @param protocol The protocol to use (like https).
   * @returns The URL of the request.
   */
  String getUrl(String);

  /**
   * The destination host of the request.
   */
  String host;
  /**
   * The request method.
   */
  String method;
  /**
   * The path of the request.
   */
  String path;
  /**
   * The query parameters of the request.
   */
  Parameter query;
  /**
   * The request headers.
   */
  Parameter header;
  /**
   * The body parameters of the POST request.
   */
  Parameter body;
  /**
   * The Authorization parameters of the OAuth request.
   */
  Parameter auth;

private:
};

#endif