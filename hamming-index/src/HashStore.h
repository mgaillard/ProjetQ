#ifndef HASHSTORE_H
#define HASHSTORE_H

#include <string>
#include <vector>
#include <cstdint>

using namespace std;

class HashStore
{
public:
    struct ResultEntry {
        int dist;
        uint64_t hash;

        ResultEntry(int d, uint64_t h) : dist(d), hash(h) {}

        bool operator<(const ResultEntry &other) const {
            return dist < other.dist || (dist == other.dist && hash < other.hash);
        }
    };

    /**
     * Set the collection of entries of the hash store.
     * @param entries The collection of hashes.
     */
    void SetEntries(const vector<uint64_t> entries);

    /**
     * Add a collection of entries to the hash store.
     * @param entries The hashes to add.
     */
    void AddEntries(const vector<uint64_t> entries);

    /**
     * Return a vector of all entries in the HashStore.
     * @return A vector of all entries in the HashStore.
     */
    vector<uint64_t> Entries() const;

    /**
     * Search in the store for the hashes that are nearer to the query than a radius.
     * If the distance is equal to the radius the hash is selected.
     * @param hash The query hash.
     * @param threshold The maximum distance between the query and the hashes.
     * @return A vector with all the hashes and their distances to the query in a struct.
     */
    vector<ResultEntry> SearchRadius(uint64_t hash, int threshold) const;

    /**
     * Search in the store for the k nearest hashes to the query.
     * @param hash The query hash.
     * @param k The maximum number of hashes to return.
     * @return A vector with all the hashes and their distances to the query in a struct.
     */
    vector<ResultEntry> SearchKNearest(uint64_t hash, unsigned int k) const;

private:
    vector<uint64_t> entries_;
};

#endif // HASHSTORE_H
