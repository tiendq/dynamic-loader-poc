#include <iostream>

using namespace std;

extern "C" void startMain() {
  cout << "startMain() called on Test1" << endl;
  // cout << "Test1 called with " << sizeof(config) << endl;
  // return config;
}