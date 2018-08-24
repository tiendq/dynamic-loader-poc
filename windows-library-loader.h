#pragma once

#include <iostream>
#include "library-loader-base.h"

class WindowsLibraryLoader: public LibraryLoaderBase {
  public:
    WindowsLibraryLoader(std::string const &fileName) : LibraryLoaderBase(fileName) {}

    int loadLibrary();
    int closeLibrary();
    void* getFunctionPointer(std::string const &funcName);
};
