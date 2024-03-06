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

bool State::getValue() const {
    return value;
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
        states[i].parseValueAndName(f);
    }
    for (int i = 0; i < n; i++) {
        states[i].parseNextStates(f, states);
    }

    alaphelyzet();

    f.close();
}

void State::parseValueAndName(std::ifstream& is) {
    char c;
    is >> c;
    if (c != 'I' && c != 'H') throw "GL6IFB";
    value = c == 'I';
    name = new char[20];
    is >> name;
}

void State::parseNextStates(std::ifstream& is, State* states) {
    int stateIndex = 0;
    nextStates = new State*[4];
    while (true) {
        char c;
        is >> c;

        if (c != '0') {
            Bazis bazis = cast(c);
            nextStates[bazis] = states + stateIndex;
        }

        if (is.peek() == ' ') {
            is >> std::ws;
            stateIndex++;
        }
        
        if (is.peek() == '\n')
            return;
    }
}

State& State::getNextState(Bazis bazis) const {
    return *nextStates[bazis];
}

const char* Allapotgep::aktualisallapot() {
    return currentState->getName();
}

bool Allapotgep::elfogad() {
    return currentState->getValue();
}

void Allapotgep::atmenet(Bazis b) {
    currentState = &currentState->getNextState(b);
}

bool Allapotgep::feldolgoz(const Bazis* b, int n) {
    for (int i = 0; i < n; i++) {
        atmenet(b[i]);
    }
    return elfogad();
}

void Allapotgep::alaphelyzet() {
    currentState = states;
}

State::~State() {
    delete[] name;
    delete[] nextStates;
}

Allapotgep::~Allapotgep() {
    delete[] states;
}
