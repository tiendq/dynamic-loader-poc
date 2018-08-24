#include <iostream>

using namespace std;

extern "C" void* startMain(void const *config) {
  cout << "startMain() called with " << sizeof(config) << endl;
  return nullptr;
}