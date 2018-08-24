#include <iostream>
#include "test1.h"
#include "test3.h"

void Test1::start() {
  std::cout << "Test1 started\n";

  Test3 t3;
  t3.start();
}