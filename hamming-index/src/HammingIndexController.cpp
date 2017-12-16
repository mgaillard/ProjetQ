#include <sstream>

#include "HammingIndexController.h"

using namespace std;

HammingIndexController::HammingIndexController(DAOImage &dao_image) :
    dao_image_(dao_image)
{

}

HammingIndexController::~HammingIndexController()
{

}

void HammingIndexController::Init()
{
    
}

void HammingIndexController::PreDispatch()
{

}

void HammingIndexController::PostDispatch()
{

}

Response HammingIndexController::SearchRadius(const Request& request)
{
    Response response;
    bool valid_query = true;
    uint64_t query_hash = 0;
    int radius = 0;
    
    string str_query_hash = request.GetQueryParameter("query_hash", "0");
    string str_radius = request.GetQueryParameter("radius", "0");
    
    try {
        query_hash = stoull(str_query_hash);
    } catch (const std::invalid_argument& ia) {
        response.SetStatusCode(400);
        response.SetContent("Invalid query hash");
        valid_query = false;
    } catch (const std::out_of_range& oor) {
        response.SetStatusCode(400);
        response.SetContent("Out of range query hash");
        valid_query = false;
    }

    try {
        radius = stoi(str_radius);
    } catch (const std::invalid_argument& ia) {
        response.SetStatusCode(400);
        response.SetContent("Invalid radius");
        valid_query = false;
    } catch (const std::out_of_range& oor) {
        response.SetStatusCode(400);
        response.SetContent("Out of range radius");
        valid_query = false;
    }

    // The radius should be greater than or equal to 0, otherwise the result would be empty.
    if (radius < 0) {
        response.SetStatusCode(400);
        response.SetContent("The radius should be greater than or equal to 0");
        valid_query = false;
    }

    if (valid_query)
    {
        vector<HashStore::ResultEntry> results = hash_store_.SearchRadius(query_hash, radius);

        // Format the results in JSON
        stringstream response_stream;
        response_stream << "[";
        for (unsigned int i = 0; i < results.size(); i++) {
            if (i > 0) {
                response_stream << ", ";
            }
            response_stream << "{\"distance\": " << results[i].dist << ", \"hash\": \"" << results[i].hash << "\"}";
        }
        response_stream << "]";

        response.SetContent(response_stream.str());
    }

    return response;
}

Response HammingIndexController::SearchKNearest(const Request& request)
{
    Response response;
    bool valid_query = true;
    uint64_t query_hash = 0;
    int k = 1;
    
    string str_query_hash = request.GetQueryParameter("query_hash", "0");
    string str_k = request.GetQueryParameter("k", "1");
    
    try {
        query_hash = stoull(str_query_hash);
    } catch (const std::invalid_argument& ia) {
        response.SetStatusCode(400);
        response.SetContent("Invalid query hash");
        valid_query = false;
    } catch (const std::out_of_range& oor) {
        response.SetStatusCode(400);
        response.SetContent("Out of range query hash");
        valid_query = false;
    }

    try {
        k = stoi(str_k);
    } catch (const std::invalid_argument& ia) {
        response.SetStatusCode(400);
        response.SetContent("Invalid k");
        valid_query = false;
    } catch (const std::out_of_range& oor) {
        response.SetStatusCode(400);
        response.SetContent("Out of range k");
        valid_query = false;
    }

    // k should be greater than 0, otherwise the result would be empty.
    if (k <= 0) {
        response.SetStatusCode(400);
        response.SetContent("K should be greater than 0");
        valid_query = false;
    }

    if (valid_query)
    {
        vector<HashStore::ResultEntry> results = hash_store_.SearchKNearest(query_hash, k);

        // Format the results in JSON
        stringstream response_stream;
        response_stream << "[";
        for (unsigned int i = 0; i < results.size(); i++) {
            if (i > 0) {
                response_stream << ", ";
            }
            response_stream << "{\"distance\": " << results[i].dist << ", \"hash\": \"" << results[i].hash << "\"}";
        }
        response_stream << "]";

        response.SetContent(response_stream.str());
    }

    return response;
}

Response HammingIndexController::Update(const Request& request)
{
    Response response;

    vector<uint64_t> hashes;

    vector<Image> images = dao_image_.FindIndexed(0);

    for (const Image& image : images) {
        hashes.push_back(image.dct_hash);
    }

    sort(hashes.begin(), hashes.end());
    hashes.erase(unique(hashes.begin(), hashes.end()), hashes.end());

    hash_store_.SetEntries(hashes);

    response.SetStatusCode(200);
    return response;
}