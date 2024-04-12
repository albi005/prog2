#include <iostream>

class Kerek {
    int atmero;

  public:
    Kerek(int atmero) : atmero(atmero) { std::cout << "\tKerek ctor\n"; }
    Kerek(const Kerek& other) : atmero(other.atmero) { std::cout << "\tKerek copy\n"; }
    virtual ~Kerek() { std::cout << "\tKerek dtor\n"; }
    virtual void kiir() { std::cout << "atmero=" << atmero << std::endl; }
};

class Monocikli {
    Kerek kerek;

  public:
    Monocikli(int atmero) : kerek(16) { std::cout << "\tMonocikli ctor\n"; }
    Monocikli(const Monocikli& other) : kerek(other.kerek) {
        std::cout << "\tMonocikli copy\n";
    }
    void kiir() {
        std::cout << "\tk.";
        kerek.kiir();
    }
};

class Jarmu {
    double vMax;

  public:
    Jarmu(double v) : vMax(v) {
        std::cout << "\tJarmu ctor vMax=" << vMax << "\n";
    }
    Jarmu(const Jarmu& other) : vMax(other.vMax) {
        std::cout << "\tJarmu copy vMax=" << vMax << "\n";
    }
    virtual ~Jarmu() { std::cout << "\tJarmu dtor vMax=" << vMax << "\n"; }
};

class Szan : public Jarmu {
    int kutyakSzama;

  public:
    Szan(double v, int n) : Jarmu(v), kutyakSzama(n) {
        std::cout << "\tSzan ctor kutyakSzama=" << kutyakSzama << "\n";
    }
    Szan(const Szan& other) : Jarmu(other), kutyakSzama(other.kutyakSzama) {
        std::cout << "\tSzan copy kutyakSzama=" << kutyakSzama << "\n";
    }
    ~Szan() { std::cout << "\tSzan dtor kutyakSzama=" << kutyakSzama << "\n"; }
};

class Bicikli : public Jarmu {
    Kerek elso;
    Kerek hatso;

  public:
    Bicikli(double v, int d) : Jarmu(v), elso(d), hatso(d) {
        std::cout << "\tBicikli ctor ";
        hatso.kiir();
    }
    Bicikli(const Bicikli& other)
        : Jarmu(other), elso(other.elso), hatso(other.hatso) {
        std::cout << "\tBicikli copy ";
        hatso.kiir();
    }
    ~Bicikli() {
        std::cout << "\tBicikli dtor ";
        hatso.kiir();
    }
};
