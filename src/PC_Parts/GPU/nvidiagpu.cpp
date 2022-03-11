#include "../../../include/PC_Parts/GPU/nvidiagpu.h"

nvidiaGPU::nvidiaGPU(QString model, int pcie, int vram, int base, int bus, int tdp,
                     int pcieSlots, int height, int length, int price, QStringList inputs,
                     int boost, bool rays, bool dlss):
    GPU(model, vram, pcie, base, bus, tdp, pcieSlots, height, length, price, inputs, boost),
    _rtCores(rays),
    _dlss(dlss)
{}

bool nvidiaGPU::hasRT()
{
    return _rtCores;
}

bool nvidiaGPU::runsDLSS()
{
    return _dlss;
}

QString nvidiaGPU::getManu()
{
    return "Nvidia";
}

string nvidiaGPU::toString()
{
    return "Manufacturer: Nvidia\n" +
            GPU::toString() +
            "Ray Tracing: " + (_rtCores ? "Yes" : "No") + "\n" +
            "DLSS Compatible: " + (_dlss ? "Yes" : "No") + "\n";
}
