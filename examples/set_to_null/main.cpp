#include <iostream>
struct A {
    A() { std::cout << "Hello\n"; }
    ~A() { std::cout << "Bye\n"; }
};

struct B {
    A a;
};

int main() {
    B b;
    b.a = NULL;
}
