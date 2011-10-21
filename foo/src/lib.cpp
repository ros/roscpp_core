#include <iostream>

namespace foo {
  void f() {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
}
