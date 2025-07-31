#include <iostream>

class ConstExample {
  int value;

public:
  ConstExample(int v) : value(v) {}
  int getValue() const { return value; }
};

int main() {
  ConstExample c(42);
  std::cout << "Const member function returns: " << c.getValue() << std::endl;
  return 0;
}
