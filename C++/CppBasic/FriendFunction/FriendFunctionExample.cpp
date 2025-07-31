#include <iostream>

class Rectangle {
  int width, height;

public:
  Rectangle(int w, int h) : width(w), height(h) {}
  friend int area(const Rectangle &r);
};

int area(const Rectangle &r) { return r.width * r.height; }

int main() {
  Rectangle rect(5, 3);
  std::cout << "Area: " << area(rect) << std::endl;
  return 0;
}
