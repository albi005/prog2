/**
 * \file komplex.cpp
 *
 * Komplex osztályt megvalósító függvények definíciója.
 *
 * Folytassa a megvalósítást sorrendben a komplex.h fájlban levő feladatoknak megfelelően!
 *
 */


#include <iostream>         // Valószínű, hogy a kiíráshoz majd kell
#include <iomanip>          // ... és ez is.
#include <cmath>            // az sqrt miatt kell.

#include "komplex.h"        // Ebben van a Komplex osztály, és néhány globális függvény deklarációja

///using namespace std;  // ha nagyon kell, akkor csak itt nyissuk ki a névteret, a headerben soha!

/// Előre elkészített tagfüggvények

/// 0, 1 és 2 paraméteres konstruktor
/// Figyelje meg, hogy a default argumentumokat CSAK a deklarációnál
/// adtuk meg!
Komplex::Komplex(double r, double im) {
    re = r; // ha nincs névütközés, nem kell kiírni a this-t
    this->im = im;
}

///---- Egy példa a konstans tagfüggvényre, ehhez hasonlóan kell
///     elkészíteni a gettereket az 1. feladatban (ELKESZULT=1)
/// Abszolút érték lekérdezése
/// @return - abszolút érték
double Komplex::abs() const { return sqrt(re*re + im*im); }

#if ELKESZULT >= 3
// 3. feladathoz (ELKESZULT 3)
// összehasonlítás
/// Egyenlőtlenség vizsgálat
/// @param rhs_k - jobb oldali operandus (Komplex)
/// @return hamis - ha a képzetes és a valós rész is azonos, egyébként false
bool Komplex::operator!=(const Komplex& rhs_k) const {  // visszavezetjük az egyenlőség vizsgálatra
    return !(*this == rhs_k);
}
#endif

#if ELKESZULT >= 6
// 6. feladathoz (ELKESZULT 6)
// a += művelet viszont módosítja önmagát!
/// Komplex + double
/// @param rhs_d - jobb oldali operandus (double)
/// @return eredeti (bal oldali) objektum ref., amihez hozzáadtuk rhd_d-t
Komplex& Komplex::operator+=(double rhs_d) {
    re += rhs_d;
    return *this;
}
#endif

// ------------------------ Eddig elkészítettük -------------------------
// TODO: A hiányzó tag- és globális függvények itt következnek
bool Komplex::operator==(const Komplex& rhs_k) const {
    return (this->re == rhs_k.re && this->im == rhs_k.im);
}

double Komplex::getRe() const {
    return this->re;
}

double Komplex::getIm() const {
    return this->im;
}

void Komplex::setRe(double re) {
    this->re = re;
}

void Komplex::setIm(double im) {
    this->im = im;
}

Komplex Komplex::operator+(const Komplex& rhs_k) const {
    return Komplex(this->re + rhs_k.re, this->im + rhs_k.im);
}

Komplex Komplex::operator+(double rhs_d) const {
    return Komplex(this->re + rhs_d, this->im);
}

Komplex operator+(double lhs_d, const Komplex& rhs_k) {
    return Komplex(lhs_d + rhs_k.getRe(), rhs_k.getIm());
}

Komplex& Komplex::operator+=(const Komplex& rhs_k) {
    this->re += rhs_k.re;
    this->im += rhs_k.im;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Komplex& rhs_k) {
    os << rhs_k.getRe();
    if (rhs_k.getIm() > 0)
        os << '+';
    if (rhs_k.getIm() != 0)
        os << rhs_k.getIm() << 'j';
    return os;
}

std::istream& operator>>(std::istream& is, Komplex& rhs_k) {
    double re, im;
    char trash;
    is >> re >> im >> trash;
    rhs_k.setRe(re);
    rhs_k.setIm(im);
    return is;
}

Komplex Komplex::operator~() const {
    return Komplex(this->re, -this->im);
}

Komplex Komplex::operator*(const Komplex& rhs_k) const
{
    // https://byjus.com/maths/multiplication-of-complex-numbers/
    double a = this->re, b = this->im, c = rhs_k.re, d = rhs_k.im;
    return Komplex(a * c - b * d, a * d + b * c);
}

Komplex Komplex::operator*(double rhs_d) const
{
    return *this * Komplex(rhs_d);
}

Komplex& Komplex::operator*=(const Komplex& rhs_k)
{
    Komplex tmp = *this * rhs_k;
    this->re = tmp.re;
    this->im = tmp.im;
    return *this;
}

Komplex& Komplex::operator*=(double rhs_d)
{
    return *this *= Komplex(rhs_d);
}

Komplex operator*(double lhs_d, const Komplex& rhs_k)
{
    return rhs_k * lhs_d;
}

