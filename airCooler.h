#ifndef AIRCOOLER_H
#define AIRCOOLER_H

#include "cooler.h"

class airCooler: public cooler
{
    public:
        airCooler(QString model, int tdp, int fans, int maxFans, int h, QStringList sockets, int price);

        bool canFit(int height, bool rads);
};

#endif // AIRCOOLER_H
