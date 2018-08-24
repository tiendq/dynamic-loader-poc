#include <iostream>
#include <dlfcn.h>
#include "unix-library-loader.h"

using namespace std;

int UnixLibraryLoader::loadLibrary() {
  // https://www.unix.com/man-page/osx/3/dlopen/
  // https://www.safaribooksonline.com/library/view/advanced-mac-os/9780321706560/ch06s06.html
  void *handle = dlopen(m_fileName.c_str(), RTLD_NOW);

  if (nullptr == handle) {
    cerr << "Could not load library " << m_fileName << endl;
    cerr << "Error: " << dlerror() << endl;
    return -1;
  }

  m_handle = handle;
  return 0;
}

int UnixLibraryLoader::closeLibrary() {
  if (nullptr == m_handle) {
    cerr << "Invalid library handle" << endl;
    return -1;
  }

  int n = dlclose(m_handle);

  if (0 != n) {
    cerr << "Could not unload library " << m_fileName << endl;
    cerr << "Error: " << dlerror() << endl;
    return -1;
  }

  return 0;
}

void* UnixLibraryLoader::getFunctionPointer(string const &funcName) {
  if (nullptr == m_handle) {
    cerr << "Invalid library handle" << endl;
    return nullptr;
  }

  // https://www.unix.com/man-page/osx/3/dlsym/
  void *fp = dlsym(m_handle, funcName.c_str());

  if (nullptr == fp) {
    cerr << "Could not get function pointer for " << funcName << endl;
    cerr << "Error: " << dlerror() << endl;
    return nullptr;
  }

  return fp;
}