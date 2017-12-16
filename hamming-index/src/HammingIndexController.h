#ifndef HAMMINGINDEXCONTROLLER_H
#define HAMMINGINDEXCONTROLLER_H

#include <controller.h>

#include "HashStore.h"
#include "DAOImage.h"

using namespace NodeCpp;

class HammingIndexController : public Controller
{
public:
    HammingIndexController(DAOImage &dao_image);
    ~HammingIndexController();

    void Init();
    void PreDispatch();
    void PostDispatch();

    Response SearchRadius(const Request& request);

    Response SearchKNearest(const Request& request);

    Response Update(const Request& request);

private:
    DAOImage &dao_image_;
    HashStore hash_store_;
};

#endif // HAMMINGINDEXCONTROLLER_H
