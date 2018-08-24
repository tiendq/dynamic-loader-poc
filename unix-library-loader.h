#pragma once

#include <iostream>
#include "library-loader-base.h"

class UnixLibraryLoader: public LibraryLoaderBase {
  public:
    UnixLibraryLoader(std::string const &fileName) : LibraryLoaderBase(fileName) {}

    int loadLibrary();
    int closeLibrary();
    void* getFunctionPointer(std::string const &funcName);
};
