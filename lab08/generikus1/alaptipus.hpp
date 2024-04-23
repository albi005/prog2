#ifndef ALAPTIPUS_H
#define ALAPTIPUS_H


template <typename T>
class Alaptipus {
    T adat;
public:
    Alaptipus(T i = 0) :adat(i) {}  /// konstruktor és egyben konverziós operátor
    operator T&() { return adat; }/// cast
    operator T() const { return adat; } /// const cast
    T* operator&() {   return &adat; }
    const T* operator&() const {   return &adat; }
    virtual ~Alaptipus() {}
};

#endif // ALAPTIPUS_H
