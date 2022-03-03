#include "motherboard.h"

void motherboard::cpuCompatibility(CPU *cpu)
{
    _cpuFits = cpu->getSocket() == _socket;
}

bool motherboard::cpuFits()
{
    return _cpuFits;
}

void motherboard::resetCPU()
{
    _cpuFits = false;
}

void motherboard::ramCompatibility(RAM *ram)
{
    _ramFits = ram->getModel() == _ramVersion;
}

bool motherboard::ramFits()
{
    return _ramFits;
}

void motherboard::resetRAM()
{
    _ramFits = false;
}

void motherboard::storageCompatibility(storage *storage)
{
    QString port = storage->getPort();
    if (port == "M.2")
        _storageFits = _m2Slots > 0;
    else
        _storageFits = _sataSlots > 0;
}

bool motherboard::storageFits()
{
    return _storageFits;
}

void motherboard::resetStorage()
{
    _storageFits = false;
}

void motherboard::coolerCompatibility(cooler *cooler)
{
    _coolerFits = cooler->canMount(_socket);
}

bool motherboard::coolerFits()
{
    return _coolerFits;
}

void motherboard::resetCooler()
{
    _coolerFits = false;
}
