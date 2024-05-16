#ifndef SPLIT_HPP
#define SPLIT_HPP

#include "allapotgep.hpp"
#include "memtrace.h"
#include <string>

enum class SplitInput { elvalaszto, egyeb };
enum class SplitAllapot { elvalaszto_volt, alap };

class Split final : public Allapotgep<SplitAllapot, SplitInput, char> {
    AllTabla tabla;
    std::vector<std::string> darabok;
    char sep;

    class Kiir : public Nop {
        Split& gep;

      public:
        Kiir(SplitAllapot kovAll, Split& gep) : Nop(kovAll), gep(gep) {}

        void akcio(char ch) override { gep.kiir(ch); }
    };

    class UjDarab : public Nop {
        Split& gep;

      public:
        UjDarab(SplitAllapot kovAll, Split& gep) : Nop(kovAll), gep(gep) {}

        void akcio(char ch) override {
            gep.kov();
            gep.kiir(ch);
        }
    };

  public:
    Split(char sep);

    SplitInput input(char ch) const override {
        if (ch == sep)
            return SplitInput::elvalaszto;
        return SplitInput::egyeb;
    }

    void kiir(char c) { darabok.back().push_back(c); }

    void kov() { darabok.push_back(std::string()); }

    const std::vector<std::string>& get() { return darabok; }
};

#endif