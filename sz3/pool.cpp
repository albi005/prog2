/**
 * \file pool.cpp
 *
 * StringPool osztály implemntációja
 * Valósítsd meg az osztály metódusait, a leírást a header fájlban találod.
 *
 * Ezt a fájlt be kell adni (fel kell tölteni) a megoldással.
 */

#include "pool.h"
#include "memtrace.h"
#include <cstring>

void StringPool::insert(RString* rString) {
    size_t cap = rString->capacity();
    for (auto it = _pool.begin(); it != _pool.end(); ++it) {
        if (cap <= (*it)->capacity()) {
            _pool.insert(it, rString);
            return;
        }
    }
    _pool.push_back(rString);
}

StringPool::StringPool(size_t obj_num, size_t init_cap) {
    for (size_t i = 0; i < obj_num; i++)
        insert(new RString(init_cap));
}

RString& StringPool::acquire(size_t capacity) {
    inUseCount++;
    for (auto it = _pool.begin(); it != _pool.end(); ++it) {
        if (capacity <= (*it)->capacity()) {
            auto res = *it;
            _pool.erase(it);
            return *res;
        }
    }
    return *new RString(capacity);
}

RString& StringPool::acquire(const char* str) {
    size_t size = std::strlen(str);
    auto& res = acquire(size + 1);
    std::strcpy(res, str);
    return res;
}

bool StringPool::acquireable(const RString& str) const {
    for (auto it : _pool) {
        if (it == &str)
            return true;
    }
    return false;
}

void StringPool::release(RString& str) {
    if (acquireable(str))
        return;
    inUseCount--;
    str = "";
    insert(&str);
}

RString& StringPool::append(RString& str1, const RString& str2) {
    if (acquireable(str1) || acquireable(str2))
        throw "GL6IFB";
    size_t availableCap = str1.capacity();
    size_t requiredCap = str1.size() + str2.size() + 1;
    if (availableCap >= requiredCap) {
        std::strcat(str1, str2);
        return str1;
    }

    RString& res = acquire(requiredCap);
    std::strcpy(res, str1);
    std::strcat(res, str2);
    return res;
}

size_t StringPool::size() const { return free_size() + inUseCount; }

size_t StringPool::free_size() const { return _pool.size(); }
