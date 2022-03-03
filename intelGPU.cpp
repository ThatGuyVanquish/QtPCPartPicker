#include "GPU.h"

class intelGPU: public GPU
{
    private:

    public:
        intelGPU(QString model, int pcie, int vram, int base, int bus, int tdp, int pcieSlots, int height, int length, int price, QStringList inputs, int boost = -1):
        GPU(model, vram, pcie, base, bus, tdp, pcieSlots, height, length, price, inputs, boost)
        {};

        ~intelGPU(){};

        QString getManu() {return "Intel";}
        string toString()
        {
            return "Manufacturer: Intel\n" + 
            GPU::toString();
        }
        bool hasRT() {return false;}
        bool runsDLSS() {return false;}
};
