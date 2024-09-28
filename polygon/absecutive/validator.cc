/**
 * (c) 2024 Diego Sogari
 */
#include "testlib.h"

constexpr int maxt = 1e3, maxa = 1e9;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);
  auto t = inf.readInt(1, maxt, "t");
  inf.readEoln();
  for (int i = 0; i < t; i++) {
    setTestCase(i + 1);
    auto l = inf.readInt(-maxa, maxa, "l");
    inf.readSpace();
    inf.readInt(l, maxa, "r");
    inf.readEoln();
  }
  inf.readEof();
}
