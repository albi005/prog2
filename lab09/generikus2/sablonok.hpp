#ifndef SABLOKONOO
#define SABLOKONOO

#include <iostream>
#include <ostream>
#include <string>

template <typename TIter>
void printEach(
    TIter begin, TIter end, std::ostream& os = std::cout, std::string sep = ", "
) {
    os << *begin;
    begin++;
    for (TIter i = begin; i != end; i++)
        os << sep << *i;
    os << std::endl;
}

template <typename TIter> int szamol_ha_negativ(TIter begin, TIter end) {
    int cunt = 0;
    for (TIter i = begin; i != end; i++)
        if (*i < 0)
            cunt++;
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
    for (TIter i = begin; i != end; i++)
        if (pred(*i))
            cunt++;
    return cunt;
}

#endif
