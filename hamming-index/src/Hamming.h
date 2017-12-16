#ifndef HAMMING_H
#define HAMMING_H

#include <cstdint>
#include <nmmintrin.h>

/**
 * @brief HammingDistance Compute a Hamming distance between two preceptual hashes.
 * @param x A 64 bits perceptual hash.
 * @param y A 64 bits perceptual hash.
 * @return An integer distance between 0 and 64.
 */
inline int HammingDistance(uint64_t x, uint64_t y)
{
#if defined(__GNUC__) || defined(__GNUG__)
    return __builtin_popcountll(x ^ y);
#elif defined(_MSC_VER)
    return _mm_popcnt_u64(x ^ y);
#endif
}

#endif // HAMMING_H
