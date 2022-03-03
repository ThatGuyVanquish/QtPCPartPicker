#include "storage.h"

class sataSSD: public storage
{
    public:
        sataSSD(QString model, int read, int write, int cache, int price):
            storage(model, "ssd", "SATA3", "2.5", read, write, cache, price)
            {};
        ~sataSSD(){};
};
