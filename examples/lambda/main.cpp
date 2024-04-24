#include <functional>
#include <iostream>

int main() {
    {
        int b = 0;
        auto a = [b]() mutable { std::cout << b++ << " aaaaaaaaaa\n"; };
        auto c = a;
        a();
        a();
        a();
        c();
        c();
        c();
    }
    std::cout << "\n";
    {
        int b = 0;
        auto a = [b]() mutable { std::cout << b++ << " aaaaaaaaaa\n"; };
        auto& c = a;
        a();
        a();
        a();
        c();
        c();
        c();
    }
    std::cout << "\n";
    {
        auto a = [](){};
        auto b = a;
        b();
    }
    std::cout << "\n";
    {
        int x = 69;
        std::function<void()> a = [x]() mutable {
            std::cout << x++;
        };
        std::function<void()> b = a;
        a();
        a();
        a();
        b();
        a();
        a();
    }
}
