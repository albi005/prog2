#ifndef EMBER_H
#define EMBER_H

class Ember {
  protected:
    int szulEv;
    char* nev;

  public:
    Ember() : Ember("GL6IFB", 2004) {}
    Ember(const char* n, int ev);
    Ember(const Ember& e);
    Ember& operator=(const Ember& e);
    const char* getNev() const;
    virtual int getKor(int ev) const;
    virtual const char* foglalkozas() const;
    virtual ~Ember();
};

#endif
