#include "AIO.h"



AIO::AIO(QString model, int tdp, int fans, int maxFans, int rads, int h, QStringList sockets, int price):
    cooler(model, tdp, fans, maxFans, rads, h, sockets, price)
{}

bool AIO::canFit(int height, bool rads)
{
    return rads;
}
