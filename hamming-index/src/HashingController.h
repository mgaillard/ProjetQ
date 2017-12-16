#ifndef HASHINGCONTROLLER_H
#define HASHINGCONTROLLER_H

#include <controller.h>

#include "DAOImage.h"
#include "ImageDownloader.h"

using namespace NodeCpp;

class HashingController : public Controller
{
public:
    HashingController(DAOImage &dao_image);
    ~HashingController();

    void Init();
    void PreDispatch();
    void PostDispatch();

    Response HashUrl(const Request& request);

private:
    DAOImage &dao_image_;

    ImageDownloader image_downloader_;
};


#endif //HASHINGCONTROLLER_H
