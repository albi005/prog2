#ifndef MONOTON_HPP
#define MONOTON_HPP

template <typename TIterator, typename TCompare>
bool monoton(TIterator begin, TIterator end, TCompare compare) {
    while (begin != end) {
        TIterator prev = begin;
        begin++;
        if (begin == end) return true;
        if (!compare(*begin, *prev))
            return false;
    }
    return true;
}

#endif
