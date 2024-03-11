/**
 * \file allapotgep.cpp
 *
 * Ebben a fájlban kell megvalósítania az Allapotgep osztály
 * metódusait, valamint mindazon további osztályokat, melyek szükségesek
 * a feladat megvalósításához.
 *
 * Ezt a fájlt be kell adni (fel kell tölteni) a megoldással.
 */

#include <iostream>
#include <fstream>

#include "allapotgep.h"
#include "memtrace.h"

char* State::getName() const {
    return name;
}

bool State::getOutput() const {
    return output;
}

void Allapotgep::konfigural(const char* fajlnev) {
    std::ifstream f;
    f.open(fajlnev);
    if (f.fail())
        throw "GL6IFB";
    int n;
    f >> n;

    delete[] states;
    states = new State[n];
    for (int i = 0; i < n; i++) {
        states[i].parseOutputAndName(f);
    }
    for (int i = 0; i < n; i++) {
        states[i].parseNextStates(f, states);
    }

    alaphelyzet();

    f.close();
}

void State::parseOutputAndName(std::ifstream& is) {
    char c;
    is >> c;
    if (c != 'I' && c != 'H') throw "GL6IFB";
    output = c == 'I';
    name = new char[20];
    is >> name;
}

void State::parseNextStates(std::ifstream& is, State* states) {
    int stateIndex = 0;
    nextStateIndexes = new int[4];
    while (true) {
        char c;
        is >> c;

        if (c != '0') {
            Bazis bazis = cast(c);
            nextStateIndexes[bazis] = stateIndex;
        }

        if (is.peek() == ' ') {
            is >> std::ws;
            stateIndex++;
        }
        
        if (is.peek() == '\n')
            return;
    }
}

int State::getNextStateIndex(Bazis bazis) const {
    return nextStateIndexes[bazis];
}

const char* Allapotgep::aktualisallapot() {
    return states[currentStateIndex].getName();
}

bool Allapotgep::elfogad() {
    return states[currentStateIndex].getOutput();
}

void Allapotgep::atmenet(Bazis b) {
    currentStateIndex = states[currentStateIndex].getNextStateIndex(b);
}

bool Allapotgep::feldolgoz(const Bazis* b, int n) {
    for (int i = 0; i < n; i++) {
        atmenet(b[i]);
    }
    return elfogad();
}

void Allapotgep::alaphelyzet() {
    currentStateIndex = 0;
}

State::~State() {
    delete[] name;
    delete[] nextStateIndexes;
}

Allapotgep::~Allapotgep() {
    delete[] states;
}
