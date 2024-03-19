#ifndef USTRING_H
#define USTRING_H

#include "string5.h"

class UString : public String {
    static bool UpperCase;

  public:
    UString() {}
    UString(const String& s) : String(s) {}

    static bool UCase() { return UpperCase; }
    static void UCase(bool val) { UpperCase = val; }
};

std::ostream& operator<<(std::ostream& os, const UString& s);

#endif // USTRING_H
