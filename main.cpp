#include <iostream>
#include "cmake-config.h"
#include "mysqrt.h"

using namespace std;

int main(int argc, char **argv) {
  cout << "Hello, you're running dynamic loader POC\n";

  string version = to_string(POC_VERSION_MAJOR) + "." + to_string(POC_VERSION_MINOR) + "." + to_string(POC_VERSION_PATCH);
  cout << "Version " << version << endl;

  cout << "sqrt(25) = " << mysqrt(25) << endl;
  return 0;
}