#include "HammingIndexApplication.h"

HammingIndexApplication::HammingIndexApplication() :
    dao_image_(mongocxx::uri("mongodb://mongodb:27017")),
    hamming_index_controller_(dao_image_),
    hashing_controller_(dao_image_)
{
    
}

HammingIndexApplication::~HammingIndexApplication()
{

}

void HammingIndexApplication::InitRoutes()
{
    AddRoute("/api/search_radius", NODECPP_ACTION(HammingIndexController::SearchRadius), &hamming_index_controller_);
    AddRoute("/api/search_knearest", NODECPP_ACTION(HammingIndexController::SearchKNearest), &hamming_index_controller_);
    AddRoute("/api/update", NODECPP_ACTION(HammingIndexController::Update), &hamming_index_controller_);

    AddRoute("/api/hash_url", NODECPP_ACTION(HashingController::HashUrl), &hashing_controller_);
}

