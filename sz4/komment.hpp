#ifndef KOMMENT_HPP
#define KOMMENT_HPP

#include "allapotgep.hpp"
#include "memtrace.h"
#include <string>

enum class KommentInput { per, csillag, egyeb };

enum class KommentAllapot { alap, per_volt, komment, komment_csillag_volt };

class Komment final : public Allapotgep<KommentAllapot, KommentInput, char> {
    AllTabla tabla;
    std::string s;

    class Kiir : public Nop {
        Komment& gep;

        void akcio(char ch) override { gep.kiir(ch); }

      public:
        Kiir(KommentAllapot kovAll, Komment& gep) : Nop(kovAll), gep(gep) {}
    };

    class KiirKonst : public Nop {
        Komment& gep;
        const char c;

        void akcio(char ch) override { gep.kiir(c); }

      public:
        KiirKonst(KommentAllapot kovAll, Komment& gep, char c)
            : Nop(kovAll), gep(gep), c(c) {}
    };

    class KiirKonstEsKiir : public Nop {
        Komment& gep;
        const char c;

        void akcio(char ch) override {
            gep.kiir(c);
            gep.kiir(ch);
        }

      public:
        KiirKonstEsKiir(KommentAllapot kovAll, Komment& gep, char c)
            : Nop(kovAll), gep(gep), c(c) {}
    };

    void kiir(char ch) { s.push_back(ch); }

  public:
    Komment();

    std::string get() { return s; }

    KommentInput input(char ch) const override {
        switch (ch) {
            case '/':
                return KommentInput::per;
            case '*':
                return KommentInput::csillag;
            default:
                return KommentInput::egyeb;
        }
    }
};

#endif