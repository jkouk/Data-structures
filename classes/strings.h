#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string.h>
using namespace std;

class String {
private:
  string str;

public:
  String(string str) { this->str = str; }
  size_t length() { return this->str.length(); }

  char operator[](int pos) { return this->str[pos]; }
  bool operator<(String str) {
    size_t min_length = min(str.length(), this->str.length());
    for (size_t i = 0; i < min_length; i++) {
      if (str[i] > this->str[i])
        return true;
      else
        return false;
    }

    if (this->str.length() == min_length)
      return true;
    return false;
  }
  bool operator>(String str) {
    size_t min_length = min(str.length(), this->str.length());

    for (size_t i = 0; i < min_length; i++) {
      if (str[i] > this->str[i])
        return false;
      else
        return true;
    }

    if (this->str.length() == min_length)
      return false;
    return true;
  }
};
