#ifndef INTELGPU_H
#define INTELGPU_H

#include "GPU.h"

class intelGPU: public GPU
{
    private:

    public:
        intelGPU(QString model, int pcie, int vram, int base, int bus, int tdp, int pcieSlots,
                 int height, int length, int price, QStringList inputs, int boost = -1);

        ~intelGPU(){};

        QString getManu();

        bool hasRT();

        bool runsDLSS();

        string toString();

};


#endif // INTELGPU_H
