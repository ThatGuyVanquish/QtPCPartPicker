#include "../../../include/PC_Parts/Storage/m2ssd.h"

m2SSD::m2SSD(QString model, QString size, int read, int write, int cache, int price):
    storage(model, "ssd", "M.2", size, read, write, cache, price)
{}
