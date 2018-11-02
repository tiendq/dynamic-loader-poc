#include <iostream>
#include <memory>
#include <string>
#include <mysqrt.h>
#include "cmake-config.h"

#ifdef __WINDOWS__
  #include "windows-library-loader.h"
#else
  #include "unix-library-loader.h"
#endif // __WINDOWS__

using namespace std;

using moduleInitializer = void* (*)(void const *);

// https://en.wikipedia.org/wiki/Dynamic_loading
int main(int argc, char const *argv[]) {
  cout << "Hello, you're running dynamic loader POC\n";

  // Just to get rid of unused variable warnings.
  if (argc > 1)
    cout << *argv[1];

  string version = to_string(POC_VERSION_MAJOR) + "." + to_string(POC_VERSION_MINOR) + "." + to_string(POC_VERSION_PATCH);
  cout << "Version " << version << '\n';

  cout << "Static library: sqrt(25) = " << mysqrt(25) << '\n';

#if defined(__WINDOWS__)
  string fileName = "test1.dll";
#elif defined(__LINUX__)
  string fileName = "/var/dynamic-loader-poc/build/bin/libtest1.so";
#else // __MACOS__
  // Must be full path, not ~/
  string fileName = "/Users/tiendq/GitHub/dynamic-loader-poc/build/bin/libtest1.dylib";
#endif

  cout << "Loading library " << fileName << '\n';

#ifdef __WINDOWS__
  auto test1 = make_unique<WindowsLibraryLoader>(fileName);
#else
  auto test1 = make_unique<UnixLibraryLoader>(fileName);
#endif // __WINDOWS__

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
