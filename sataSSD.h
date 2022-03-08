#ifndef SATASSD_H
#define SATASSD_H

#include "storage.h"

class sataSSD: public storage
{
    public:
        sataSSD(QString model, QString size, int read, int write, int cache, int price);

        ~sataSSD(){};
};


#endif // SATASSD_H
