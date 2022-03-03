#include "pcCase.h"

void pcCase::motherboardCompatibility(motherboard *mobo)
{
    foreach (QString ff, _moboFF)
    {
        if (ff == mobo->getFormFactor())
        {
            _moboFits = true;
            break;
        }
    }
}

bool pcCase::moboFits()
{
    return _moboFits;
}

void pcCase::resetMobo()
{
    _moboFits = false;
}

void pcCase::coolerCompatibility(cooler *cooler)
{
    _coolerFits = cooler->canFit(_height, _radiators);
}

bool pcCase::coolerFits()
{
    return _coolerFits;
}

void pcCase::resetCooler()
{
    _coolerFits = false;
}

void pcCase::gpuCompatibility(GPU *gpu)
{
    _gpuFits = gpu->canFit(_expansionSlots, _width, _maxGPU);
}

bool pcCase::gpuFits()
{
    return _gpuFits;
}

void pcCase::resetGPU()
{
    _gpuFits = false;
}

void pcCase::storageCompatibility(storage *storage)
{
    if (storage->getType() == "hdd" && _hdds > 0)
        _storageFits = true;
    else if (storage->getType() == "ssd" && storage->getPort() == "SATA3")
    {
        if (_ssds > 0 || _hdds > 0)
            _storageFits = true;
    }
    else
        _storageFits = false;
}

bool pcCase::storageFits()
{
    return _storageFits;
}

void pcCase::resetStorage()
{
    _storageFits = false;
}
