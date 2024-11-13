#include <Arduino.h>
#include <functional>

#define BoolToString(x) ((x) ? "true" : "false")

void replaceAll(String &str, const String &from, const String &to);
