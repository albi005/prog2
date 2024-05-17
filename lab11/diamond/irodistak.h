/**
 * \file irodistak.h
 * Minden származtatott osztály deklarációját ebbe a fájlba tettük.
 * Az egyszerűség kedvéért minden tagfüggvényt inline valósítottunk meg.
 *
 */
#ifndef IRODISTAK_H
#define IRODISTAK_H

#include <iostream>
#include <string>

#include "alkalmazott.h"

typedef int csop_t; // csoport típusa

/**
 * Csoportvezető
 */
class CsopVez : public virtual Alkalmazott {
    csop_t csoport; // csoport azon.
  public:
    CsopVez(const std::string& n, double f, csop_t cs)
        : Alkalmazott(n, f), // alaposztály inicializálása
          csoport(cs)        // csoport inicializálás
    {}

    CsopVez(const Alkalmazott& a, csop_t cs)
        : Alkalmazott(a), // alaposztály inicializálása
          csoport(cs)     // csoport inicializálás
    {}

    csop_t getCs() const { // csoport lekérdezése
        return csoport;
    }

    void setCs(csop_t cs) { csoport = cs; }

    void kiir(std::ostream& os = std::cout) const {
        os << "CsopVez: ";
        Alkalmazott::kiir(os);
    }
};

/**
 * Határozott idejű alkalmazott
 */
class HatIdeju : public virtual Alkalmazott {
  protected:
    time_t ido; // szerződése lejár ekkor
  public:
    HatIdeju(const std::string& n, double f, time_t t)
        : Alkalmazott(n, f), // alaposztály inicializálása
          ido(t)             // ido inicializálás
    {}

    HatIdeju(const Alkalmazott& a, time_t t)
        : Alkalmazott(a), // alaposztály inicializálása
          ido(t)          // ido inicializálás
    {}

    time_t getIdo() const { return ido; }

    void setIdo(time_t t) { ido = t; }

    void kiir(std::ostream& os = std::cout) const {
        std::cout << "HatIdeju: ";
        Alkalmazott::kiir(os);
    }
};

/**
 * Határozott idejű csoportvezető
 */
class HatIdCsV : public CsopVez, public HatIdeju {
  public:
    HatIdCsV(const std::string& n, double f, csop_t cs, time_t t)
        : Alkalmazott(n, f),
          CsopVez(n, f * 2, cs), // szándékosan más fizetést kap,
          HatIdeju(n, f * 10, t) // hogy látható legyen az adatduplikáció
    {}

    void kiir(std::ostream& os = std::cout) const {
        std::cout << "HatIdCsv:" << std::endl << "   ";
        CsopVez::kiir(os);
        std::cout << "   ";
        HatIdeju::kiir(os);
    }
};

/**
 * Határozott idejű csoportvezető helyettes
 */
class HatIdCsVezH : public HatIdCsV {
  public:
    HatIdCsVezH(const std::string& n, double f, time_t t, CsopVez& kit)
        : Alkalmazott(n, f), HatIdCsV(n, f, kit.getCs(), t) // alaposztály
    {}

    void kiir(std::ostream& os = std::cout) const {
        std::cout << "HatIdCsVezH: ";
        HatIdCsV::kiir(os);
    }
};

#endif // IRODISTAK_H
