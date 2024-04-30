#ifndef SABLOKONOO
#define SABLOKONOO

#ifndef CPORTA
#include "gen_array_iter3.hpp"
#endif
#include <iostream>
#include <ostream>
#include <string>

template <typename TIter>
void printEach(
    TIter begin, TIter end, std::ostream& os = std::cout, std::string sep = ","
) {
    os << *begin;
    ++begin;
    for (TIter i = begin; i != end; ++i)
        os << sep << *i;
    os << std::endl;
}

template <typename TIter> int szamol_ha_negativ(TIter begin, TIter end) {
    int cunt = 0;
    for (TIter i = begin; i != end; ++i)
        if (*i < 0)
            ++cunt;
    return cunt;
}

template <typename T> class nagyobb_mint {
    T val;

  public:
    nagyobb_mint(T val) : val(val) {}

    bool operator()(T x) { return x > val; }
};

template <typename TIter, typename TPred>
int szamol_ha(TIter begin, TIter end, TPred pred) {
    int cunt = 0;
    for (TIter i = begin; i != end; ++i)
        if (pred(*i))
            ++cunt;
    return cunt;
}

template <class T>
void PrintArray(const char* txt, const T& arr, std::ostream& os = std::cout) {
    os << txt << " size=" << arr.size() << " capacity=" << arr.capacity()
       << std::endl;
    os << "\t data=";
    // kiírjuk az adatokat
    printEach(arr.begin(), arr.end(), os);
}

#ifndef CPORTA
template <class T, size_t maxsiz>
typename Array<T, maxsiz>::iterator Array<T, maxsiz>::iterator::operator++(int
) {
    auto res = *this;
    if (idx != p->siz)
        ++idx; // nem engedjük túllépni
    return res;
}
#endif

template <typename TIter, class TFunc>
TFunc forEach(TIter first, TIter last, TFunc func) {
    for (TIter i = first; i != last; ++i)
        func(*i);
    return func;
}

template <typename T> class ostreamFunctor {
    std::ostream& os;
    std::string sep;

  public:
    ostreamFunctor(std::ostream& os, std::string sep) : os(os), sep(sep) {}
    void operator()(T x) { os << x << sep; }
};

#define ELKESZULT 17

#endif
