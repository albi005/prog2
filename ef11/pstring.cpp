#include "pstring.h"

void PString::write(std::ostream& os) const {
    os << size() << " " << c_str();
}

void PString::read(std::istream& is) {
    size_t len;
    is >> len;
    is.ignore(1);
    std::cout << is.peek();
    char* s = new char[len + 1];
    is.read(s, len);
    s[len] = 0;
    *this = String(s);
    delete[] s;
}
