#ifndef NVIDIAGPU_H
#define NVIDIAGPU_H

#include "gpu.h"

class nvidiaGPU: public GPU
{
    private:
        bool _rtCores;
        bool _dlss;

    public:
        nvidiaGPU(QString model, int pcie, int vram, int base, int bus, int tdp,
                  int pcieSlots, int height, int length, int price, QStringList inputs,
                  int boost = -1, bool rays = false, bool dlss = true);

        ~nvidiaGPU(){};

        bool hasRT();

        bool runsDLSS();

        QString getManu();

        string toString();
};


#endif // NVIDIAGPU_H
