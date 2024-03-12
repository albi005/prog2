/**
 *
 * \file string5.cpp
 *
 * Itt kell megvalósítania a hiányzó tagfüggvényeket.
 * Segítségül megadtuk a C++ nem OO eszközeinek felhasználásával készített String-kezelő
 * függvényke neveit.
 *
 * Ha valamit INLINE-ként valósít meg, akkor annak a string5.h-ba kell kerülnie,
 * akár kívül akár osztályon belül definiálja. (Az inline függvényeknek minden
 * fordítási egységben elérhetőknek kell lenniük)
 * *
 * A teszteléskor ne felejtse el beállítani a string5.h állományban az ELKESZULT makrót.
 *
 */

#ifdef _MSC_VER
// MSC ne adjon figyelmeztető üzenetet a C sztringkezelő függvényeire
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>             // Kiíratáshoz
#include <cstring>              // Sztringműveletekhez

#include "memtrace.h"           // a standard headerek után kell lennie
#include "string5.h"


/// Konstruktorok: egy char karakterből (createString)
///                egy nullával lezárt char sorozatból (createString)

/// Másoló konstruktor: String-ből készít (createString)

/// Destruktor (disposeString)

/// operator=

/// [] operátorok: egy megadott indexű elem REFERENCIÁJÁVAL térnek vissza (charAtString)
/// indexhiba esetén const char * kivételt dob!


/// + operátorok:
///                 String-hez jobbról karaktert ad (addString)
///                 String-hez String-et ad (addString)

/// << operator, ami kiír az ostream-re


/// >> operátor, ami beolvas az istream-ről egy szót
String::String(char c) : String((size_t)1) {
    pData[0] = c;
    pData[1] = 0;
}

String::String(const char* s) : String(strlen(s)) { strcpy(pData, s); }

String::String(const String& other) : String(other.len) {
    strcpy(pData, other.pData);
}

String& String::operator=(const String& other) {
    if (this == &other)
        return *this;
    delete[] pData;
    len = other.len;
    pData = new char[len + 1];
    strcpy(pData, other.pData);
    return *this;
}

String::~String() { delete[] pData; }

String String::operator+(const String& b) const {
    String res(len + b.len);
    strcpy(res.pData, pData);
    strcat(res.pData, b.pData);
    return res;
}

String String::operator+(const char c) const { return *this + String(c); }

char& String::operator[](const size_t i) const {
    if (i >= len)
        throw "Index was out of range. Must be non-negative and less than the size of the collection";
    return pData[i];
}

std::ostream& operator<<(std::ostream& os, const String& rhs) {
    for (size_t i = 0; i < rhs.size(); i++) {
        os << rhs[i];
    }
    return os;
}

String operator+(const char c, const String& s) { return String(c) + s; }

