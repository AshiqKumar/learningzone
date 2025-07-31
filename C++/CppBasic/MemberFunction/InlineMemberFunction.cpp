#include <iostream>

class InlineExample {
public:
  inline void print() {
    std::cout << "This is an inline member function." << std::endl;
  }
};

int main() {
  InlineExample obj;
  obj.print();
  return 0;
}
