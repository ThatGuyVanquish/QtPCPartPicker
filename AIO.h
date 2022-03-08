#ifndef AIO_H
#define AIO_H

#include "cooler.h"

class AIO: public cooler
{
    public:
        AIO(QString model, int tdp, int fans, int maxFans, int rads, int h, QStringList sockets, int price);

        bool canFit(int height, bool rads);
};

#endif // AIO_H
