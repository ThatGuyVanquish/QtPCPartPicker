#include "../../../include/PC_Parts/GPU/amdgpu.h"

amdGPU::amdGPU(QString model, int pcie, int vram, int base, int bus, int tdp, int pcieSlots,
               int height, int length, int price, QStringList inputs, int boost, bool rays):
    GPU(model, vram, pcie, base, bus, tdp, pcieSlots, height, length, price, inputs, boost),
    _rayAccelerators(rays)
{}

bool amdGPU::hasRT()
{
    return _rayAccelerators;
}

QString amdGPU::getManu()
{
    return "AMD";
}

string amdGPU::toString()
{
    return "Manufacturer: AMD\n" +
            GPU::toString() +
            "Ray Tracing: " + (_rayAccelerators ? "Yes" : "No") + "\n";
}

bool amdGPU::runsDLSS()
{
    return false;
}
