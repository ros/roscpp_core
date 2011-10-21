#include <iostream>

#include <foo/foo.hpp>
#include <bar/bar.hpp>

namespace bar {
  void f() {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    foo::f();
  }

}
