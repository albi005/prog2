#ifndef kiflih
#define kiflih

#include "aru.h"

class Kifli :public Aru {
    String spec;
  public:
    /// Konstruktor beállítja az attribútumokat (ősosztályét is)
    /// @param zsir - tej zsírtartalma
    /// @param ar - tej egységára
    /// @param spec - tej fajtája
    Kifli(double ar, const char *spec = "")
        :Aru("Kifli", "db", ar), spec(spec) {}

    /// Attribútumok kiírása egy stream-re
    /// @param os - output stream referencia
    /// @return output stream referencia
    std::ostream& print(std::ostream& os) const {
        return os << megnevezes << " "
                  << spec << "; "
                  << ar << "Ft/" << egyseg;
    }
};

#endif
