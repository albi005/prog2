// http://www.hit.bme.hu/~izso/sablon.pdf

#include <cstring>
#include <iostream>

template <class T> bool cmp(T const& a, T const& b) { return a < b; }

template <class T> bool cmp(T* const& a, T* const& b) { return *a < *b; }

bool cmp(const char* a, const char* b) { return strcmp(a, b) < 0; }

template <typename T> class C {
    C() {}

    ~C<T>() {} // wtf is this language
};

template <typename T> class D {};

template <typename T> class D<T (*)(T)> {}; // yep. makes perfect sense. beautiful syntax

int main() { std::cout << cmp("asd", "aasd"); }
