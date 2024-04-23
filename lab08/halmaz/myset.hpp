#ifndef MYSET_HPP
#define MYSET_HPP

#include "point.h"
#include <cstddef>

#define ELKESZULT 5

template <typename T>
bool equal(const T& a, const T& b) { return a == b; }

inline bool Xequal(const Point& a, const Point& b) {
    return a.getX() == b.getX();
}

template <typename T, size_t TCapacity = 100, bool TEqual(const T&, const T&) = equal<T>>
class Set {
    T data[TCapacity];
    size_t len = 0;

  public:
    Set() {}
    size_t size() { return len; }
    bool isElement(T element) {
        for (size_t i = 0; i < len; i++)
            if (TEqual(data[i], element))
                return true;
        return false;
    }
    void insert(T element) {
        if (isElement(element))
            return;
        if (len == TCapacity)
            throw "GL6IFB";
        data[len++] = element;
    }
};

inline bool operator==(const Point& a, const Point& b) {
    return a.getX() == b.getX() && a.getY() == b.getY();
}

#endif
