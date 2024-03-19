#include "ustring.h"

bool UString::UpperCase = false;

std::ostream& operator<<(std::ostream& os, const UString& s) {
    if (!UString::UCase())
        os << String(s);
    else
        for (size_t i = 0; i < s.size(); i++)
            os << (char)std::toupper(s[i]);
    return os;
}
