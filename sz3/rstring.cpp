/**
 * \file rstring.cpp
 *
 * RString osztály implemntációja
 * Valósítsd meg az osztály metódusait, a leírást a header fájlban találod.
 *
 * Ezt a fájlt be kell adni (fel kell tölteni) a megoldással.
 */

#include "rstring.h"
#include "memtrace.h"
#include <cstring>

RString::RString(size_t capacity) : RString("", capacity) {}

RString::RString(const char* str) : RString(str, std::strlen(str) + 1) {}

RString::RString(const char* str, size_t capacity) {
    _capacity = capacity;
    size_t size = std::strlen(str);
    if (size + 1 > _capacity)
        throw "GL6IFB";
    _data = new char[_capacity];
    std::strcpy(_data, str);
}

size_t RString::size() const { return strlen(_data); }

size_t RString::capacity() const { return _capacity; }

RString::operator char*() const { return _data; }

RString& RString::operator=(const char* str) {
    size_t size = std::strlen(str);
    if (size > _capacity)
        throw "GL6IFB";
    std::strcpy(_data, str);
    return *this;
}

RString::~RString() { delete[] _data; }
