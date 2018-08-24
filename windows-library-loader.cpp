#include <iostream>
#include <windows.h>
#include "windows-library-loader.h"

using namespace std;

int WindowsLibraryLoader::loadLibrary() {
  void *handle = dlopen(m_fileName.c_str(), RTLD_NOW);

  if (nullptr == handle) {
    cerr << "Could not load library " << m_fileName << endl;
    cerr << "Error: " << dlerror() << endl;
    return -1;
  }

  m_handle = handle;
  return 0;
}

int WindowsLibraryLoader::closeLibrary() {
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

void* WindowsLibraryLoader::getFunctionPointer(string const &funcName) {
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
