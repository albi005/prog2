#include "swap.h"

void swap(bool& a, bool& b) {
    bool tmp = a;
    a = b;
    b = tmp;
}

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void swap(char& a, char& b) {
    char tmp = a;
    a = b;
    b = tmp;
}

void swap(double& a, double& b) {
    double tmp = a;
    a = b;
    b = tmp;
}

void swap(const char*& a, const char*& b) {
    const char* tmp = a;
    a = b;
    b = tmp;
}
