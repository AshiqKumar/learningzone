#include <iostream>

class Base {
public:
  virtual void speak() { std::cout << "Base speaking." << std::endl; }
};

class Derived : public Base {
public:
  void speak() override { std::cout << "Derived speaking." << std::endl; }
};

int main() {
  Base *b = new Derived();
  b->speak();
  delete b;
  return 0;
}
