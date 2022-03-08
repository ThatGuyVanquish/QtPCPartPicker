#include "CPU.h"
#include "intelCPU.h"

intelCPU::intelCPU(QString model, QString socket, int cores, double base, int l2,
                   int l3, int lanes, int tdp, int price, bool igpu, bool cooler,
                   int threads, double boost, bool unlocked):
    CPU(model, socket, cores, base, l2, l3, lanes, tdp, price, igpu, cooler, threads, boost),
    _unlocked(unlocked)
{}

bool intelCPU::isUnlocked()
{
    return _unlocked;
}

QString intelCPU::getManu()
{
    return "Intel";
}

string intelCPU::toString()
{
    return "Manufacturer: Intel\n" + CPU::toString() + "Unlocked: " + (_unlocked ? "Yes" : "No") + "\n";
}
