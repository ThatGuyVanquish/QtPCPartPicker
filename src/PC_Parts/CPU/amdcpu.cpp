#include "../../../include/PC_Parts/CPU/amdcpu.h"

amdCPU::amdCPU(QString model, QString socket, int cores, double base, int l2, int l3, int lanes, int tdp,
               int price, bool igpu, bool cooler, int threads, double boost):
    CPU(model, socket, cores, base, l2, l3, lanes, tdp, price, igpu, cooler, threads, boost)
{}

QString amdCPU::getManu()
{
    return "AMD";
}

bool amdCPU::isUnlocked()
{
    return true;
}

string amdCPU::toString()
{
    return "Manufacturer: AMD\n" + CPU::toString();
}
