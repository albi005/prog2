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

// From https://stackoverflow.com/a/62917051/13695737
int mod(const int a, const int m) { return (a % m + m) % m; }

// CaesarCipher
char caesarEncode(char c, int offset) {
    if (c == ' ')
        return ' ';
    if (c < 'a' || c > 'z')
        throw "GL6IFB";
    int a = c - 'a';
    a += offset;
    a = mod(a, alphabetLength);
    return a + 'a';
}

string CaesarCipher::encode(const string& message) const {
    string res(message.size(), 0);
    for (size_t i = 0; i < res.size(); i++) {
        res[i] = caesarEncode(message[i], shift);
    }
    return res;
}

string CaesarCipher::decode(const std::string& ciphertext) const {
    string res(ciphertext.size(), 0);
    for (size_t i = 0; i < res.size(); i++) {
        char c = ciphertext[i];
        c = caesarEncode(c, -shift);
        res[i] = c;
    }
    return res;
}

Cipher* CaesarCipher::clone() const { return new CaesarCipher(shift); }

// MyCipher
char myCipherEncode(char c, size_t i, string key, int offset,
                    bool invert = false) {
    if (c == ' ')
        return ' ';
    if (c < 'a' || c > 'z')
        throw "GL6IFB";

    int a = c - 'a'; // abs representation: a->0, b->1
    int shift = offset + i + (key[i % key.size()] - 'a');
    if (invert)
        shift *= -1;
    a += shift;
    a = mod(a, alphabetLength);
    return a + 'a';
}

std::string MyCipher::encode(const std::string& message) const {
    string res(message.size(), 0);
    for (size_t i = 0; i < res.size(); i++) {
        res[i] = myCipherEncode(message[i], i, key, offset);
    }
    return res;
}

std::string MyCipher::decode(const std::string& ciphertext) const {
    string res(ciphertext.size(), 0);
    for (size_t i = 0; i < res.size(); i++) {
        res[i] = myCipherEncode(ciphertext[i], i, key, offset, true);
    }
    return res;
}

Cipher* MyCipher::clone() const { return new MyCipher(key, offset); }

MyCipher::~MyCipher() {}

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
