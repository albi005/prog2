#pragma once

#include "string5.h"
#include "serializable.h"

class PString : public String, public Serializable {
  public:
    void write(std::ostream & os) const override;
    void read(std::istream & is) override;
    PString() : String() {}
    PString(const String& s) : String(s) {}
    ~PString() override {}
};