#include "GPU.h"

class nvidiaGPU: public GPU
{
    private:
        bool _rtCores;
        bool _dlss;

    public:
        nvidiaGPU(QString model, int pcie, int vram, int base, int bus, int tdp, int pcieSlots, int height, int length, int price, QStringList inputs, int boost = -1, bool rays = false, bool dlss = true):
        GPU(model, vram, pcie, base, bus, tdp, pcieSlots, height, length, price, inputs, boost),
        _rtCores(rays),
        _dlss(dlss)
        {};
        ~nvidiaGPU(){};
        bool hasRT() {return _rtCores;}
        bool runsDLSS() {return _dlss;}
        QString getManu() {return "Nvidia";}
        string toString()
        {
            return "Manufacturer: Nvidia\n" + 
            GPU::toString() +
            "Ray Tracing: " + (_rtCores ? "Yes" : "No") + "\n" +
            "DLSS Compatible: " + (_dlss ? "Yes" : "No") + "\n"; 
        }
};
