#ifndef M2SSD_H
#define M2SSD_H

#include "storage.h"

class m2SSD: public storage
{
    public:
        m2SSD(QString model, QString size, int read, int write, int cache, int price);

        ~m2SSD(){};
};


#endif // M2SSD_H
