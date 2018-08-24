#include <iostream>

using namespace std;

void* start(void *config) {
  cout << "Test2 called with " << sizeof(config) << endl;
  return config;
}