#include <iostream>
#include <memory>
#include <dlfcn.h>
#include "cmake-config.h"
#include "mysqrt.h"
#include "unix-library-loader.h"

using namespace std;

using moduleInitializer = void* (*)(void const *);

// https://en.wikipedia.org/wiki/Dynamic_loading
int main(int argc, char **argv) {
  cout << "Hello, you're running dynamic loader POC\n";

  // Just to get rid of unused variable warnings.
  if (argc > 1)
    cout << *argv[1];

  string version = to_string(POC_VERSION_MAJOR) + "." + to_string(POC_VERSION_MINOR) + "." + to_string(POC_VERSION_PATCH);
  cout << "Version " << version << endl;

  cout << "sqrt(25) = " << mysqrt(25) << endl;

  auto test1 = make_unique<UnixLibraryLoader>("/Users/tiendq/GitHub/dynamic-loader-poc/build/bin/libtest1.dylib");

  if (0 != test1->loadLibrary())
    return -1;

  auto ptr = (moduleInitializer)test1->getFunctionPointer("startMain");

  if (ptr) {
    auto temp = new char;
    ptr(temp);
    delete temp;
  }

  test1->closeLibrary();

  return 0;
}