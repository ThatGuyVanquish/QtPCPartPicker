#include "storage.h"

class hdd: public storage
{
    public:
        hdd(QString model, QString port, QString size, int read, int write, int cache, int price):
            storage(model, "hdd", port, size, read, write, cache, price)
            {};
        ~hdd(){};
};
