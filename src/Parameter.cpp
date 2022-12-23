#include "Parameter.h"

#include <UrlEncode.h>

size_t Parameter::add(String key, String value) {
  KVS prm;
  prm.key = key;
  prm.value = value;

  this->param.push_back(prm);
  return this->param.size();
}

size_t Parameter::remove(String key) {
  for (auto iter = this->param.begin(); iter != this->param.end(); iter++) {
    if (iter->key == key) {
      this->param.erase(iter);
    }
  }
  return this->param.size();
}

String Parameter::getRaw(String key_glue, String value_glue) {
  String ret = "";
  for (auto &iter : this->param) {
    ret += key_glue + iter.key + value_glue + iter.value;
  }
  ret.remove(0, key_glue.length());
  return ret;
}

String Parameter::get(String key_glue, String value_glue) {
  String ret = "";
  for (auto &iter : this->param) {
    ret += key_glue + urlEncode(iter.key) + value_glue + urlEncode(iter.value);
  }
  ret.remove(0, key_glue.length());
  return ret;
}

String Parameter::get() {
  return this->get("&", "=");
}

size_t Parameter::size() {
  return this->param.size();
}

void Parameter::concat(Parameter param) {
  this->param.insert(this->param.end(), param.param.begin(), param.param.end());
}

void Parameter::sort() {
  std::sort(this->param.begin(), this->param.end());
}
