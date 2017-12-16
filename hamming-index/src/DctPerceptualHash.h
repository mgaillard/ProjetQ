#ifndef DCTPERCEPTUALHASH_H
#define DCTPERCEPTUALHASH_H

#include <vector>
#include <cstdint>

using namespace std;

/**
 * @brief DctPerceptualHash
 * @param binary_image A binary image stored in a vector
 * @return
 */
uint64_t DctPerceptualHash(vector<char>& binary_image);

/**
 * @brief DctPerceptualHashDistance Compute a Hamming distance between two DCT perceptual hashes.
 * @param x A 64 bits DCT perceptual hash.
 * @param y A 64 bits DCT perceptual hash.
 * @return An integer distance between 0 and 64.
 */
int DctPerceptualHashDistance(uint64_t x, uint64_t y);

#endif // DCTPERCEPTUALHASH_H
