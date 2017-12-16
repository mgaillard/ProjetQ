#ifndef DAOIMAGE_H
#define DAOIMAGE_H

#include <vector>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include "Image.h"

using namespace std;

class DAOImage
{
public:
    DAOImage(const mongocxx::uri &uri);

    /**
     * Find all indexed images in the database.
     * @param limit Maximum number of image to get
     */
    vector<Image> FindIndexed(int limit);

    /**
     * Find all non-indexed images in the database.
     * @param limit Maximum number of image to get
     */
    vector<Image> FindNonIndexed(int limit);

    /**
     * Update an image in the database.
     * @param image The image to update
     */
    bool Update(const Image &image);

private:
    mongocxx::client client_;
    mongocxx::collection image_collection_;
};


#endif //DAOIMAGE_H