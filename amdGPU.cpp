#include "GPU.h"

class amdGPU: public GPU
{
    private:
        bool _rayAccelerators;

    public:
        amdGPU(QString model, int pcie, int vram, int base, int bus, int tdp, int pcieSlots, int height, int length, int price, QStringList inputs, int boost = -1, bool rays = false):
        GPU(model, vram, pcie, base, bus, tdp, pcieSlots, height, length, price, inputs, boost),
        _rayAccelerators(rays)
        {};
        ~amdGPU(){};
        bool hasRT() {return _rayAccelerators;}
        QString getManu() {return "AMD";}
        string toString()
        {
            return "Manufacturer: AMD\n" + 
            GPU::toString() +
            "Ray Tracing: " + (_rayAccelerators ? "Yes" : "No") + "\n";
        }
        bool runsDLSS() {return false;}

};
