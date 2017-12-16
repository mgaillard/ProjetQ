#include <algorithm>
#include <queue>

#include "HashStore.h"
#include "Hamming.h"

using namespace std;

void HashStore::SetEntries(const vector<uint64_t> entries)
{
    entries_ = entries;
}

void HashStore::AddEntries(const vector<uint64_t> entries)
{
    entries_.insert(entries_.end(), entries.begin(), entries.end());
}

vector<uint64_t> HashStore::Entries() const
{
    return entries_;
}

vector<HashStore::ResultEntry> HashStore::SearchRadius(uint64_t hash, int threshold) const
{
    vector<HashStore::ResultEntry> results;

    #pragma omp parallel for shared(results)
    for (unsigned long i = 0; i < entries_.size(); i++) {
        int dist = HammingDistance(hash, entries_[i]);

        if (dist <= threshold) {
            #pragma omp critical(results_update)
            {
                results.push_back(HashStore::ResultEntry(dist, entries_[i]));
            }
        }
    }

    sort(results.begin(), results.end());

    return results;
}

vector<HashStore::ResultEntry> HashStore::SearchKNearest(uint64_t hash, unsigned int k) const 
{
    priority_queue<HashStore::ResultEntry> k_nearest;

    for (unsigned long i = 0; i < entries_.size(); i++) {
        int dist = HammingDistance(hash, entries_[i]);

        // There is not enough elements in the queue, we add a new element.
        if (k_nearest.size() < k) {
            k_nearest.push(HashStore::ResultEntry(dist, entries_[i]));
        } else if (k_nearest.size() >= k && k_nearest.top().dist > dist) {
            k_nearest.push(HashStore::ResultEntry(dist, entries_[i]));
            k_nearest.pop();
        }
    }

    vector<HashStore::ResultEntry> results;

    while (!k_nearest.empty()) {
        results.push_back(k_nearest.top());
        k_nearest.pop();
    }
    reverse(results.begin(), results.end());

    return results;
}