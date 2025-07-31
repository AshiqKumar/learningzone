#include <iostream>

class StaticExample {
public:
  static void show() {
    std::cout << "This is a static member function." << std::endl;
  }
};

int main() {
  StaticExample::show();
  return 0;
}
