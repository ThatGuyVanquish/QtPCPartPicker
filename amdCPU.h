#ifndef AMDCPU_H
#define AMDCPU_H

#include "CPU.h"

class amdCPU: public CPU
{
    public:
        amdCPU(QString model, QString socket, int cores, double base, int l2, int l3, int lanes, int tdp,
               int price, bool igpu = false, bool cooler = false, int threads = -1, double boost = -1);

        ~amdCPU(){};

        QString getManu();

        bool isUnlocked();

        string toString();
};

#endif // AMDCPU_H
