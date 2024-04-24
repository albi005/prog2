#include <iostream>

int main() {
    // Print the C++ standard version
    #ifdef __cplusplus
        #if __cplusplus == 201703L
            std::cout << "C++17" << std::endl;
        #elif __cplusplus == 201402L
            std::cout << "C++14" << std::endl;
        #elif __cplusplus == 201103L
            std::cout << "C++11" << std::endl;
        #else
            std::cout << "Unknown" << std::endl;
        #endif
    #else
        std::cout << "Error: Not a valid C++ environment" << std::endl;
    #endif

    return 0;
}

