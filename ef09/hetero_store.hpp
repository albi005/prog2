/**
 * \file: hetero_store.hpp
 *
 */

#ifndef HETEROSTORE_HPP
#define HETEROSTORE_HPP

#include <iostream>
#include <stdexcept>

template <typename T, int TCapacity = 100, typename TEx = std::out_of_range>
class HeteroStore {
    T* data[TCapacity];
    size_t len = 0;

  public:
    HeteroStore() {}

    size_t size() { return len; }
    size_t capacity() { return TCapacity; }
    void add(T* p) {
        if (len == TCapacity) {
            delete p;
            throw TEx("");
        }
        data[len++] = p;
    }

    template <typename Pred> void traverse(Pred func) {
        for (size_t i = 0; i < len; i++)
            func(data[i]);
    }

    void clear() {
        for (size_t i = 0; i < len; i++)
            delete data[i];
        len = 0;
    }

    ~HeteroStore() { clear(); }
};

#endif // HETEROSTORE_HPP
