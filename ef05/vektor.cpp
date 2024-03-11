#include "vektor.h"

size_t Vektor::defSize = 21;
double Vektor::defValue = 51;

Vektor::Vektor(const Vektor& other) {
    nElements = other.nElements;
    pVec = new double[nElements];
    for (size_t i = 0; i < nElements; i++)
        pVec[i] = other.pVec[i];
}

Vektor::~Vektor() { delete[] pVec; }

Vektor& Vektor::operator=(const Vektor& other) {
    if (this != &other) {
        delete[] this->pVec;
        nElements = other.nElements;
        pVec = new double[this->nElements];
        for (size_t i = 0; i < nElements; i++)
            pVec[i] = other.pVec[i];
    }
    return *this;
}

double& Vektor::operator[](size_t idx) {
    if (idx >= nElements)
        throw "GL6IFB";
    return pVec[idx];
}

const double& Vektor::operator[](size_t idx) const {
    if (idx >= nElements)
        throw "GL6IFB";
    return pVec[idx];
}

Vektor operator*(double val, const Vektor& vec) {
    Vektor res(vec.size());
    for (size_t i = 0; i < res.size(); i++)
        res[i] = val * vec[i];
    return res;
}
