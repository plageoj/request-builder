#ifndef _PLAGEOJ_PARAMETER_H
#define _PLAGEOJ_PARAMETER_H

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
  String getRaw(String, String);
  /**
   * Get all values in the parameter list by concatenating them with the given separator, with url encoding.
   * @param key_glue The separator to use before each key.
   * @param value_glue The separator to use before each value.
   * @return The concatenated string.
   */
  String get(String, String);
  /**
   * Get all values in the parameter list.
   * @return The query string.
   */
  String get();

  /**
   * Get the number of parameters in the list.
   * @return The number of parameters in the list.
   */
  size_t size();

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

#endif
