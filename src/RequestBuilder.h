#ifndef _PLAGEOJ_REQUEST_BUILDER_H
#define _PLAGEOJ_REQUEST_BUILDER_H

#include <Arduino.h>
#include <vector>

/**
 * Represents a query/body parameter list.
 */
class Parameter {
public:
  /**
   * Add a key-value pair to the parameter list.
   * @param key The key of the parameter.
   * @param value The value of the parameter.
   * @return The number of parameters in the list.
   */
  size_t add(String, String);
  /**
   * Remove all values of a key from the parameter list.
   * @param key The key of the parameter to search.
   * @return The number of parameters in the list.
   */
  size_t remove(String);
  /**
   * Get all values in the parameter list by concatenating them with the given separator.
   * @param key_glue The separator to use before each key.
   * @param value_glue The separator to use before each value.
   * @return The concatenated string.
   */
  String get(String, String);
  /**
   * Get all values in the parameter list.
   * @return The query string.
   */
  String get() {
    return get("&", "=");
  };

  /**
   * Merge the parameter list with another parameter list.
   * @param param The parameter list to merge.
   */
  void concat(Parameter);
  /**
   * Sort the parameter list by key alphabetically.
   */
  void sort();

private:
  struct KVS {
    String key;
    String value;
  };
  std::vector<KVS> param;
  friend bool operator<(KVS &left, KVS &right) {
    return left.key < right.key;
  }
};

/**
 * Represents a HTTP request.
 */
class Request {
public:
  Request();

  /**
   * Set the HTTP method of the request.
   * @param method The HTTP method to set (like GET, POST).
   */
  Request(String method) {
    this->method = method;
  };
  /**
   * Set the HTTP method and host of the request.
   * @param method The HTTP method to set (like GET, POST).
   * @param path The host of the request (like www.example.com).
   */
  Request(String method, String host) {
    this->method = method;
    this->host = host;
  };
  /**
   * Set the HTTP method, host and path of the request.
   * @param method The HTTP method to set (like GET, POST).
   * @param host The host of the request (like www.example.com).
   * @param path The path of the request (like /path/to/file.html).
   */
  Request(String method, String host, String path) {
    this->method = method;
    this->host = host;
    this->path = path;
  };

  /**
   * @returns The first line of HTTP request.
   */
  String getRequestString();
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
  Parameter queryParam;
  /**
   * The body parameters of the POST request.
   */
  Parameter bodyParam;
  /**
   * The Authorization parameters of the OAuth request.
   */
  Parameter authParam;

private:
};

#endif