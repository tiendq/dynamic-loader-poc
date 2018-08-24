#include <iostream>
#include <dlfcn.h>
#include "cmake-config.h"
#include "mysqrt.h"

using namespace std;

// Get the function pointer to the function
void* getFunctionPointer(void *lib, char const *name) {
  // https://www.unix.com/man-page/osx/3/dlsym/
  void *fptr = dlsym(lib, name);

  if (!fptr) {
    cerr << "Could not get function pointer for " << name << endl;
    cerr << "Error: " << dlerror() << endl;

    return nullptr;
  }

  return fptr;
}

int main(int argc, char **argv) {
  cout << "Hello, you're running dynamic loader POC\n";

  // Just to get rid of unused variable warnings.
  if (argc > 1)
    cout << *argv[1];

  string version = to_string(POC_VERSION_MAJOR) + "." + to_string(POC_VERSION_MINOR) + "." + to_string(POC_VERSION_PATCH);
  cout << "Version " << version << endl;

  cout << "sqrt(25) = " << mysqrt(25) << endl;

  void (*ptr)();

  // Open the dynamic library
  // now or RTLD_LAZY?
  // https://www.unix.com/man-page/osx/3/dlopen/
  // https://www.safaribooksonline.com/library/view/advanced-mac-os/9780321706560/ch06s06.html
  void *handle = dlopen("/Users/tiendq/GitHub/dynamic-loader-poc/build/bin/libtest1.dylib", RTLD_NOW);

  if (!handle) {
    cerr << "Could not open libtest1.dylib\n" << endl;
    cerr << "Error: " << dlerror() << endl;
    return 1;
  }

  // Get the pointers to the functions within the library
  // test with "nm -gU libtest1.dylib"
  ptr = (void (*)())getFunctionPointer(handle, "startMain");

  ptr(); // = startMain()

  dlclose(handle);

  return 0;
}