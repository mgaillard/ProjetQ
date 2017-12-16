#include <mongocxx/instance.hpp>

#include "HammingIndexApplication.h"

int main()
{
    mongocxx::instance inst{};

    HammingIndexApplication app;
    app.Init();
    app.Run();

    return 0;
}
