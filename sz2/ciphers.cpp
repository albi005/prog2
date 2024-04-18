/**
 * \file ciphers.cpp
 *
 * Ebben a fájlban kell megvalósítania az CaesarCipher, MyCipher, CipherQueue
 * osztályok metódusait.
 *
 * Ezt a fájlt be kell adni (fel kell tölteni) a megoldással.
 */

#include "ciphers.h"

#include "memtrace.h"

using std::string;

const int alphabetLength = 'z' - 'a' + 1;

// BSz1 mod
// from https://stackoverflow.com/a/62917051/13695737
int mod(const int a, const int m) { return (a % m + m) % m; }

char ShiftCipher::encodeChar(char c, size_t index, bool invert) const {
    if (c == ' ')
        return ' ';
    if (c < 'a' || c > 'z')
        throw "GL6IFB";
    int indexFromA = c - 'a';

    int shift = getShift(indexFromA, index);
    if (invert)
        shift *= -1;
    indexFromA += shift;

    indexFromA = mod(indexFromA, alphabetLength);
    return indexFromA + 'a';
}

string ShiftCipher::encode(const string& s, bool invert) const {
    string res(s.size(), 0);
    for (size_t i = 0; i < res.size(); i++) {
        res[i] = encodeChar(s[i], i, invert);
    }
    return res;
}

string ShiftCipher::encode(const string& message) const {
    return encode(message, false);
}

string ShiftCipher::decode(const string& ciphertext) const {
    return encode(ciphertext, true);
}

// CaesarCipher
int CaesarCipher::getShift(char indexFromA, size_t index) const {
    return shift;
}

Cipher* CaesarCipher::clone() const { return new CaesarCipher(shift); }

// MyCipher
int MyCipher::getShift(char indexFromA, size_t index) const {
    return this->offset + index + (key[index % key.size()] - 'a');
}

Cipher* MyCipher::clone() const { return new MyCipher(key, offset); }

// CipherQueue
CipherQueue::CipherQueue(CipherQueue const& other) {
    len = other.len;
    pData = new Cipher*[len];
    for (size_t i = 0; i < len; i++)
        pData[i] = other.pData[i]->clone();
}

void CipherQueue::add(Cipher* cipher) {
    len += 1;
    Cipher** oldData = pData;
    pData = new Cipher*[len];
    for (size_t i = 0; i < len - 1; i++)
        pData[i] = oldData[i];
    pData[len - 1] = cipher;
    delete[] oldData;
}

std::string CipherQueue::encode(const std::string& message) const {
    string res = message;
    for (size_t i = 0; i < len; i++)
        res = pData[i]->encode(res);
    return res;
}

std::string CipherQueue::decode(const std::string& ciphertext) const {
    string res = ciphertext;
    for (size_t i = 0; i < len; i++)
        res = pData[i]->decode(res);
    return res;
}

Cipher* CipherQueue::clone() const { return new CipherQueue(*this); }

CipherQueue::~CipherQueue() {
    for (size_t i = 0; i < len; i++)
        delete pData[i];
    delete[] pData;
}
