#ifndef HAMMINGINDEXAPPLICATION_H
#define HAMMINGINDEXAPPLICATION_H

#include <application.h>

#include "DAOImage.h"
#include "HammingIndexController.h"
#include "HashingController.h"

using namespace NodeCpp;

class HammingIndexApplication : public Application
{
public:
    HammingIndexApplication();
    ~HammingIndexApplication();

protected:
    void InitRoutes();

private :
    DAOImage dao_image_;

    HammingIndexController hamming_index_controller_;
    HashingController hashing_controller_;
};

#endif // HAMMINGINDEXAPPLICATION_H
