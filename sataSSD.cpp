#include "storage.h"

class sataSSD: public storage
{
    public:
        sataSSD(QString model, QString size, int read, int write, int cache, int price):
            storage(model, "ssd", "SATA3", size , read, write, cache, price)
            {};
        ~sataSSD(){};
};
