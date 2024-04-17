/**
 *  \file haromszog.h
 *  Haromszog osztály deklarációja
 */
#ifndef HAROMSZOG_H
#define HAROMSZOG_H

/// Ügyeljen arra, hogy a csúcspontokat az alaposztály orgiójához relatívan
/// tárolja!
#include "alakzat.h"
#include "pont.h"

class Haromszog : public Alakzat {
    Pont p1;
    Pont p2;

  public:
    Haromszog(Pont p0, Pont p1, Pont p2, const Szin& sz)
        : Alakzat(p0, sz), p1(p1), p2(p2) {}

    virtual void rajzol() const;

    const Pont& getp1() const { return p1; }
    const Pont& getp2() const { return p2; }
    virtual ~Haromszog() {}
};

std::ostream& operator<<(std::ostream& os, const Haromszog& h);

#endif // KOR_H
