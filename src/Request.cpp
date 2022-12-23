#include "Request.h"
#include <algorithm>

#include <UrlEncode.h>

Request::Request() {
}

String Request::getRequestLine() {
  String ret = this->method + " " + this->path;
  String paramStr = this->query.get();
  if (!paramStr.isEmpty()) {
    ret += "?" + paramStr;
  }
  ret += " HTTP/1.1\r\n";
  return ret;
}

String Request::getRequestHeader() {
  this->header.add("Host", this->host);
  if (this->body.size() > 0) {
    this->header.add("Content-Type", "application/x-www-form-urlencoded");
    this->header.add("Content-Length", String(this->body.get().length()));
  }
  return this->header.getRaw("\r\n", ": ") + "\r\n";
}

String Request::getRequest() {
  String ret = this->getRequestLine();
  ret += this->getRequestHeader();
  ret += "\r\n";
  ret += this->body.get();
  return ret;
}

String Request::getParameterString() {
  Parameter temp;
  temp.concat(this->auth);
  temp.concat(this->query);
  temp.concat(this->body);
  temp.sort();
  return temp.get();
}

String Request::getUrl(String protocol) {
  return protocol + "://" + this->host + this->path;
}