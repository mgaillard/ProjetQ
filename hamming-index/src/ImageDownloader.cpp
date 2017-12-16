#include <cstdio>
#include <vector>
#include <iostream>

#include "ImageDownloader.h"

ImageDownloader::ImageDownloader()
{
    curl_context_ = curl_easy_init();
    curl_easy_setopt(curl_context_, CURLOPT_FOLLOWLOCATION, 1);
}

ImageDownloader::~ImageDownloader()
{
    curl_easy_cleanup(curl_context_);
}

static size_t WriteCallback(void *content, size_t size, size_t nmemb, void *userp)
{
    vector<char>* binary_image = reinterpret_cast<vector<char>*>(userp);
    char* buffer = static_cast<char*>(content);

    binary_image->insert(binary_image->end(), buffer, buffer + size * nmemb);

    return size * nmemb;
}

vector<char> ImageDownloader::Download(const string &url)
{
    vector<char> binary_image;

    char *decoded_url = curl_easy_unescape(curl_context_, url.c_str(), url.size(), nullptr);

    curl_easy_setopt(curl_context_, CURLOPT_URL, decoded_url);
    curl_easy_setopt(curl_context_, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl_context_, CURLOPT_WRITEDATA, &binary_image);

    CURLcode rc = curl_easy_perform(curl_context_);

    if (rc) {
        cerr << "Failed to download: " << url << endl;
        binary_image.clear();
    }

    long res_code = 0;
    curl_easy_getinfo(curl_context_, CURLINFO_RESPONSE_CODE, &res_code);

    if (!((res_code == 200 || res_code == 201) && rc != CURLE_ABORTED_BY_CALLBACK)) {
        cerr << "Failed to download: " << url << endl;
        cerr << "Response code: " << res_code << endl;
        binary_image.clear();
    }

    curl_free(decoded_url);

    return binary_image;
}
