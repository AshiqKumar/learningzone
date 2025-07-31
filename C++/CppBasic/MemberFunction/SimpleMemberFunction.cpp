#include <iostream>

class Simple {
public:
  void greet() {
    std::cout << "Hello from a simple member function!" << std::endl;
  }
};

int main() {
  Simple s;
  s.greet();
  return 0;
}
