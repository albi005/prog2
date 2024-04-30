#ifndef TTT
#define TTT

template <typename T> class T1 {
    T t;
};

template <template <typename> typename T> class T2 {
    T<int> t;
};

template <template <template <typename> typename> typename T> class T3 {
    T<T1> t;
};

class What {
  public:
    template <typename T> static void aaa() {}
};

inline void why() {
    T3<T2> t;
    typedef What W;
    What::aaa<int>();
    W::aaa<int>();
}

// im going insane

#endif
