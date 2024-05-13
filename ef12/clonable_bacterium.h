#ifndef CLONABLE_BACTERIUM_H
#define CLONABLE_BACTERIUM_H

#include "bacterium.h"
#include "clonable.h"

class ClonableBacterium : public Bacterium, public Clonable {
  public:
    explicit ClonableBacterium(const char* n = "") : Bacterium(n) {}

    ClonableBacterium* clone() const { return new ClonableBacterium(*this); }

    virtual ~ClonableBacterium(){};
};

class ClonableSalmonella : public ClonableBacterium {

    std::string species;
  public:
    explicit ClonableSalmonella(const char* sp)
        : ClonableBacterium("Salmonella"), species(sp) {}

    void show(std::ostream& os) const {
        Bacterium::show(os);
        os << " Fajta: " << species;
    }

    ClonableSalmonella* clone() const { return new ClonableSalmonella(*this); }

    virtual ~ClonableSalmonella(){};
};

class ClonableStreptococcus : public ClonableBacterium {
    char group;
  public:
    ClonableStreptococcus(char grp)
        : ClonableBacterium("Streptococcus"), group(grp) {}

    void show(std::ostream& os) const {
        Bacterium::show(os);
        os << " Csoport: " << group;
    }

    ClonableStreptococcus* clone() const {
        return new ClonableStreptococcus(*this);
    }

    virtual ~ClonableStreptococcus(){};
};

#endif // CLONABLE_BACTERIUM_H
