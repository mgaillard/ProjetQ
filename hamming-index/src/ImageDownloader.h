#ifndef IMAGEDOWNLOADER_H
#define IMAGEDOWNLOADER_H

#include <vector>

#include <curl/curl.h>
#include <curl/easy.h>

using namespace std;

class ImageDownloader
{
public:
    ImageDownloader();
    
    ~ImageDownloader();

    vector<char> Download(const string &url);

private:
    CURL* curl_context_;
};

#endif //IMAGEDOWNLOADER_H