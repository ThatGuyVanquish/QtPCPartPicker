#include "../../../include/PC_Parts/GPU/intelgpu.h"

intelGPU::intelGPU(QString model, int pcie, int vram, int base, int bus, int tdp,
                   int pcieSlots, int height, int length, int price, QStringList inputs, int boost):
    GPU(model, vram, pcie, base, bus, tdp, pcieSlots, height, length, price, inputs, boost)
{}

QString intelGPU::getManu()
{
    return "Intel";
}

string intelGPU::toString()
{
    return "Manufacturer: Intel\n" +
            GPU::toString();
}

bool intelGPU::hasRT()
{
    return false;
}

bool intelGPU::runsDLSS()
{
    return false;
}
