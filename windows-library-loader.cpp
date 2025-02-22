#include <iostream>
#include <string>
#include <windows.h>
#include "windows-library-loader.h"

using namespace std;

int WindowsLibraryLoader::loadLibrary() {
  HMODULE handle = LoadLibrary(m_fileName.c_str());

  if (nullptr == handle) {
    DWORD error = GetLastError();

    cerr << "Could not load library " << m_fileName << '\n';
    cerr << "Error: " << error << '\n';
    return -1;
  }

  m_handle = handle;
  return 0;
}

int WindowsLibraryLoader::closeLibrary() {
  if (nullptr == m_handle) {
    cerr << "Invalid library handle" << '\n';
    return -1;
  }

  BOOL success = FreeLibrary((HMODULE)m_handle);

  if (!success) {
    DWORD error = GetLastError();

    cerr << "Could not unload library " << m_fileName << '\n';
    cerr << "Error: " << error << '\n';
    return -1;
  }

  return 0;
}

void* WindowsLibraryLoader::getFunctionPointer(string const &funcName) {
  if (nullptr == m_handle) {
    cerr << "Invalid library handle" << '\n';
    return nullptr;
  }

  void *fp = (void *)GetProcAddress((HMODULE)m_handle, funcName.c_str());

  if (nullptr == fp) {
    DWORD error = GetLastError();

    cerr << "Could not get function pointer for " << funcName << '\n';
    cerr << "Error: " << error << '\n';
    return nullptr;
  }

  return fp;
}
