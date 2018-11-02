#include <iostream>

using namespace std;

#ifdef __WINDOWS__
  #define EXPORTED_FUNCTION __declspec(dllexport)
#else
  #define EXPORTED_FUNCTION
#endif // __WINDOWS__

extern "C" {

  EXPORTED_FUNCTION void* startMain(void const *config) {
    cout << "startMain() called with " << sizeof(config) << '\n';
    return nullptr;
  }

}
