#include "cooler.h"

class airCooler: public cooler
{
    public:
        airCooler(QString model, int tdp, int fans, int maxFans, int h, QStringList sockets, int price):
        cooler(model, tdp, fans, maxFans, 0, h, sockets, price)
        {};
        bool canFit(int height, bool rads)
        {
            return this->getHeight() <= height;
        }
};
