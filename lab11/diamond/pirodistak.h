/**
 * \file pirodistak.h
 * Minden származtatott irodista osztály perzisztens változatának deklarációját
 * ebbe a fájlba tegye! Az egyszerűség kedvéért minden tagfüggvényt inline
 * valósítson meg!
 *
 */
#ifndef PIRODISTAK_H
#define PIRODISTAK_H

#include "irodistak.h"
#include "palkalmazott.h"
#include <stdexcept>

/**
 * Perzisztens csoportvezető
 */
class PCsopVez : public CsopVez, public Serializable {
  public:
    PCsopVez(const std::string& n, double f, csop_t cs)
        : Alkalmazott(n, f), CsopVez(n, f, cs) {}

    explicit PCsopVez(const CsopVez& cv) : Alkalmazott(cv), CsopVez(cv) {}

    void write(std::ostream& os) const {
        os << "PCsopVez" << std::endl;
        os << getNev() << std::endl;
        os << getFiz() << std::endl;
        os << getCs() << std::endl;
    }

    void read(std::istream& is) {
        std::string tmp;
        (is >> tmp).ignore(1);
        if (tmp != "PCsopVez")
            throw std::out_of_range("PCsopVez_R: " + tmp);
        std::string n;
        getline(is, n);
        setNev(n);
        double f;
        (is >> f).ignore(1);
        setFiz(f);
        csop_t cs;
        (is >> cs).ignore(1);
        setCs(cs);
    }
};

/**
 * Perzisztens Határozott idejű alkalmazott
 */
class PHatIdeju : public HatIdeju, public Serializable {
  public:
    PHatIdeju(const std::string& n, double f, time_t t)
        : Alkalmazott(n, f), HatIdeju(n, f, t) {}

    explicit PHatIdeju(const HatIdeju& hi) : Alkalmazott(hi), HatIdeju(hi) {}

    void write(std::ostream& os) const {
        os << "PHatIdeju" << std::endl;
        os << getNev() << std::endl;
        os << getFiz() << std::endl;
        os << getIdo() << std::endl;
    }

    void read(std::istream& is) {
        std::string tmp;
        (is >> tmp).ignore(1);
        if (tmp != "PHatIdeju")
            throw std::out_of_range("PHatIdeju_R: " + tmp);
        std::string n;
        getline(is, n);
        setNev(n);
        double f;
        (is >> f).ignore(1);
        setFiz(f);
        time_t t;
        (is >> t).ignore(1);
        setIdo(t);
    }
};

/**
 * Perzisztens Határozott idejű csoportvezető
 */

/**
 * Perzisztens Határozott idejű csoportvezető helyettes
 */

#endif // IRODISTAK_H
