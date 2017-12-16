#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <cstdint>

using namespace std;

class Image
{
public:
    Image() {}

    Image(const string& url, bool indexed, bool active, uint64_t dct_hash) :
        url(url),
        indexed(indexed),
        active(active),
        dct_hash(dct_hash) {

    }

    string url;
    bool indexed;
    bool active;
    uint64_t dct_hash;
};

#endif //IMAGE_H