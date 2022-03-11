#include "../../../include/PC_Parts/Cooler/aircooler.h"

airCooler::airCooler(QString model, int tdp, int fans, int maxFans, int h, QStringList sockets, int price):
    cooler(model, tdp, fans, maxFans, 0, h, sockets, price)
{}

bool airCooler::canFit(int height, bool rads)
{
    return this->getHeight() <= height;
}
