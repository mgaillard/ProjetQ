#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include "DAOImage.h"

using namespace std;

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::close_document;

DAOImage::DAOImage(const mongocxx::uri &uri) : client_(uri)
{
    image_collection_ = client_["prod"]["images"];
}

vector<Image> DAOImage::FindNonIndexed(int limit)
{
    vector<Image> images;

    mongocxx::options::find find_args;
    if (limit > 0) {
        find_args.limit(limit);
    }

    auto cursor = image_collection_.find(document{} << "indexed" << false << "active" << true << finalize, find_args);

    for (auto&& doc : cursor) {
        Image image;
        image.url = doc["url"].get_utf8().value.to_string();
        image.indexed = doc["indexed"].get_bool();
        image.active = doc["active"].get_bool();
        image.dct_hash = static_cast<uint64_t>(doc["dct_hash"].get_int64());

        images.push_back(image);
    }

    return images;
}

vector<Image> DAOImage::FindIndexed(int limit)
{
    vector<Image> images;

    mongocxx::options::find find_args;
    if (limit > 0) {
        find_args.limit(limit);
    }

    auto cursor = image_collection_.find(document{} << "indexed" << true << "active" << true << finalize, find_args);

    for (auto&& doc : cursor) {
        Image image;
        image.url = doc["url"].get_utf8().value.to_string();
        image.indexed = doc["indexed"].get_bool();
        image.active = doc["active"].get_bool();
        image.dct_hash = static_cast<uint64_t>(doc["dct_hash"].get_int64());

        images.push_back(image);
    }

    return images;
}

bool DAOImage::Update(const Image &image)
{
    bsoncxx::document::value url_filter = document{} << "url" << image.url << finalize;
    bsoncxx::document::value update_doc = document{} << "$set"
                                            << open_document
                                                << "indexed" << image.indexed
                                                << "active" << image.active
                                                << "dct_hash" << static_cast<int64_t>(image.dct_hash)
                                            << close_document
                                            << finalize;

    bsoncxx::document::view url_filter_view = url_filter.view();
    bsoncxx::document::view update_doc_view = update_doc.view();

    mongocxx::stdx::optional<mongocxx::result::update> result = image_collection_.update_one(url_filter_view, update_doc_view);

    return result->modified_count() == 1;
}