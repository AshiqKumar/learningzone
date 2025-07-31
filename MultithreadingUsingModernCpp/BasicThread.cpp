#include <iostream>
#include <thread>
using namespace std;

// Function pointer target
void hello(int id) {
  cout << "Hello from function pointer thread " << id << endl;
}

// Function object (functor)
struct HelloFunctor {
  void operator()(int id) const {
    cout << "Hello from functor thread " << id << endl;
  }
};

int main() {
  // Using a function pointer
  std::thread t1(hello, 1);

  // Using a function object (functor)  //or --> std::thread t2(HelloFunctor (), 2);
  HelloFunctor f;
  std::thread t2(f, 2);

  // Alternatively, we can use a lambda function directly (1st way)
  auto lf = [](int id) { cout << "Hello from lambda thread " << id << endl; };
  std::thread t3(lf, 3);

  // Using a lambda function (2nd way)
  std::thread t4(
      [](int id) { cout << "Hello from lambda thread " << id << endl; }, 4);

  std::thread::id id1 = t1.get_id();
  std::thread::id id2 = t2.get_id();
  std::thread::id id3 = t3.get_id();
  std::thread::id id4 = t4.get_id();
  cout << "Thread IDs: " << id1 << ", " << id2 << ", " << id3 << ", " << id4
       << endl;
  cout << "Main thread ID: " << std::this_thread::get_id() << endl;
  t1.join();
  t2.join();
  t3.join();
  t4.join();

  cout << "Main thread done." << endl;
  return 0;
}