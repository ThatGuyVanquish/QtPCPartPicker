#ifndef AMDGPU_H
#define AMDGPU_H

#include "GPU.h"

class amdGPU: public GPU
{
    private:
        bool _rayAccelerators;

    public:
        amdGPU(QString model, int pcie, int vram, int base, int bus, int tdp, int pcieSlots, int height,
               int length, int price, QStringList inputs, int boost = -1, bool rays = false);
        ~amdGPU(){};

        bool hasRT();
        QString getManu();
        string toString();
        bool runsDLSS();
};


#endif // AMDGPU_H
