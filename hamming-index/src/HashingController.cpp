#include <cstdint>
#include <sstream>

#include "HashingController.h"
#include "DctPerceptualHash.h"

HashingController::HashingController(DAOImage &dao_image) :
        dao_image_(dao_image)
{

}

HashingController::~HashingController()
{

}

void HashingController::Init()
{

}

void HashingController::PreDispatch()
{

}

void HashingController::PostDispatch()
{

}

Response HashingController::HashUrl(const Request& request) {
    Response response;

    string image_url = "";
    uint64_t dct_hash = 0;

    image_url = request.GetQueryParameter("url", "");

    if (!image_url.empty()) {
        // Download the image
        vector<char> binary_image = image_downloader_.Download(image_url);

        if (binary_image.size() > 0) {
            dct_hash = DctPerceptualHash(binary_image);

            response.SetStatusCode(200);
            stringstream response_stream;
            response_stream << "{";
            response_stream << "\"dct_hash\": \"" << dct_hash << "\"";
            response_stream << "}";
            response.SetContent(response_stream.str());
        } else {
            // Impossible to download the image
            response.SetStatusCode(404);
        }
    } else {
        // No url given
        response.SetStatusCode(400);
    }

    return response;
}