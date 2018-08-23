#include <iostream>
#include "cmake-config.h"
#include "mysqrt.h"

using namespace std;

int main(int argc, char **argv) {
  cout << "Hello, you're running dynamic loader POC\n";

  // Just to get rid of unused variable warnings.
  if (argc > 1)
    cout << *argv[1];

  string version = to_string(POC_VERSION_MAJOR) + "." + to_string(POC_VERSION_MINOR) + "." + to_string(POC_VERSION_PATCH);
  cout << "Version " << version << endl;

  cout << "sqrt(25) = " << mysqrt(25) << endl;
  return 0;
}