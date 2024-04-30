#ifndef TT
#define TT
#include <vector>

template <template <typename> typename TCollection> class Some {
    TCollection<int> c;
};

template <typename T> class MyCollection {};

inline void some() {
    MyCollection<int> m;
    Some<MyCollection> s;
}
#endif
