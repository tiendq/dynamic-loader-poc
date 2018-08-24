#pragma once

#include <iostream>

class LibraryLoaderBase {
  public:
    LibraryLoaderBase(std::string const &fileName) : m_fileName(fileName) {
      m_handle = nullptr;
    }

    virtual ~LibraryLoaderBase() {
      m_handle = nullptr;
    }

    virtual int loadLibrary() = 0;
    virtual int closeLibrary() = 0;
    virtual void* getFunctionPointer(std::string const &funcName) = 0;

  protected:
    std::string m_fileName;
    void *m_handle;
};