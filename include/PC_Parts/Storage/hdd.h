#ifndef HDD_H
#define HDD_H

#include "storage.h"

class hdd: public storage
{
    public:
        hdd(QString model, QString port, QString size, int read, int write, int cache, int price);
        ~hdd(){};
};

#endif // HDD_H
