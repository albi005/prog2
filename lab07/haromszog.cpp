/**
 *  \file haromszog.cpp
 *  Haromszog osztály tagfüggvényeinek megvalósítása
 */
#include "haromszog.h"

void Haromszog::rajzol() const {
    std::cout << "Rajzol: " << *this << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Haromszog& h) {
    return os << "Haromszog " << (Alakzat&)h << ",p1=" << h.getp1() << ",p2=" << h.getp2();
}
