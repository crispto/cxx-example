#ifndef __ST_HPC_PPL_CORE_PAIR_H_
#define __ST_HPC_PPL_CORE_PAIR_H_

namespace ppl { namespace core {

// keep compatible with std::pair in case we can use STL in the future

template <typename T1, typename T2>
struct Pair {
    Pair() {}
    Pair(const Pair& p) : first(p.first), second(p.second) {}
    Pair(const T1& t1, const T2& t2) : first(t1), second(t2) {}
    T1 first;
    T2 second;
};

template <typename T1, typename T2>
static inline Pair<T1, T2> MakePair(const T1& t1, const T2& t2) {
    return Pair<T1, T2>(t1, t2);
}

}}

#endif
