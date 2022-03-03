#include "storage.h"

class m2SSD: public storage
{
    public:
        m2SSD(QString model, QString size, int read, int write, int cache, int price):
            storage(model, "ssd", "M.2", size, read, write, cache, price)
            {};
        ~m2SSD(){};
};
