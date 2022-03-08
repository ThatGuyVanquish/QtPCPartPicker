#ifndef INTELCPU_H
#define INTELCPU_H

#include "CPU.h"

class intelCPU: public CPU
{
    private:
        bool _unlocked;

    public:
        intelCPU(QString model, QString socket, int cores, double base, int l2, int l3, int lanes, int tdp,
                 int price, bool igpu = true, bool cooler = false, int threads = -1, double boost = -1,
                 bool unlocked = false);
        ~intelCPU(){};

        bool isUnlocked();

        QString getManu();

        string toString();
};

#endif // INTELCPU_H
