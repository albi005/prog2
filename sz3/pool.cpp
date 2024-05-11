#include "pool.h"
#include "memtrace.h"
#include <cstring>

StringPool::StringPool(size_t obj_num, size_t init_cap) {
    for (size_t i = 0; i < obj_num; i++)
        pool.emplace_back(init_cap);
}

RString& StringPool::acquire(size_t capacity) {
    // Return the first free RString that can accomodate the given capacity.
    // pool is ordered so the first one always has the smallest capacity
    for (auto& entry : pool) {
        if (entry.isAcquireable() && entry.canAccommodate(capacity)) {
            return entry.acquire();
        }
    }

    // add a new RString in the correct position so that pool stays ordered
    for (auto it = pool.begin(); it != pool.end(); ++it) {
        Entry& entry = *it;
        if (entry.canAccommodate(capacity)) {
            return pool.emplace(it, capacity)->acquire();
        }
    }
    pool.emplace_back(capacity);
    return pool.back().acquire();
}

RString& StringPool::acquire(const char* str) {
    size_t size = std::strlen(str);
    auto& res = acquire(size + 1);
    std::strcpy(res, str);
    return res;
}

bool StringPool::acquireable(const RString& str) const {
    return std::any_of(pool.begin(), pool.end(), [&str](const Entry& entry) {
        return entry.contains(str) && entry.isAcquireable();
    });
}

void StringPool::release(RString& str) {
    for (auto& entry : pool) {
        if (entry.contains(str)) {
            entry.release();
            return;
        }
    }
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

size_t StringPool::size() const { return pool.size(); }

size_t StringPool::free_size() const {
    return std::count_if(pool.begin(), pool.end(), [](const Entry& entry) {
        return entry.isAcquireable();
    });
}

StringPool::Entry::Entry(size_t capacity) : rString(capacity) {}

RString& StringPool::Entry::acquire() {
    isInUse = true;
    return rString;
}

void StringPool::Entry::release() {
    isInUse = false;
    rString = "";
}

bool StringPool::Entry::isAcquireable() const { return !isInUse; }

bool StringPool::Entry::canAccommodate(size_t capacity) const {
    return rString.capacity() >= capacity;
}

bool StringPool::Entry::contains(const RString& target) const {
    return &this->rString == &target; // compare pointers
}
