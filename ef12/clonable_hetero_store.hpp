/**
 * \file: clonable_hetero_store.hpp
 *
 */

#ifndef CLONABLE_HETERO_STORE_HPP
#define CLONABLE_HETERO_STORE_HPP

#include <cstddef>
#include <exception>
#include <stdexcept>
#include <vector>

template <
    typename T,
    typename TCollection = std::vector<T*>,
    typename TException = std::out_of_range>
class ClonableHeteroStore {
    TCollection inner;

  public:
    typedef typename TCollection::const_iterator const_iterator;

    std::size_t size() { return inner.size(); }

    void add(T* val) {
        try {
            inner.push_back(val);
        } catch (std::exception&) {
            delete val;
            throw TException("");
        }
    }

    void clear() { inner.clear(); }

    typename TCollection::iterator begin() { return inner.begin(); }

    typename TCollection::iterator end() { return inner.end(); }

    typename TCollection::const_iterator begin() const { return inner.begin(); }

    typename TCollection::const_iterator end() const { return inner.end(); }

    ClonableHeteroStore() {}

    ClonableHeteroStore(const ClonableHeteroStore& other) { *this = other; }

    ClonableHeteroStore& operator=(const ClonableHeteroStore& other) {
        if (this == &other)
            return *this;
        clear();
        for (typename TCollection::const_iterator it = other.begin(); it != other.end(); ++it) {
            add((*it)->clone());
        }
        return *this;
    }

    ~ClonableHeteroStore() {
        for (typename TCollection::iterator it = begin(); it != end(); ++it)
            delete *it;
    }
};

#endif // CLONABLE_HETERO_STORE_HPP
