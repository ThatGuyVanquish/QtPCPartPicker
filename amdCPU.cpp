#include "CPU.h"

class amdCPU: public CPU
{
    public:
        amdCPU(QString model, QString socket, int cores, double base, int l2, int l3, int lanes, int tdp, int price, bool igpu = false,
        bool cooler = false, int threads = -1, double boost = -1):
        CPU(model, socket, cores, base, l2, l3, lanes, tdp, price, igpu, cooler, threads, boost)
        {};
        ~amdCPU(){};

        QString getManu() {return "AMD";}
        bool isUnlocked() {return true;}

        string toString()
        {
            return "Manufacturer: AMD\n" + CPU::toString();
        }

};
