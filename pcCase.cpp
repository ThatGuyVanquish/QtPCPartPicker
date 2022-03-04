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

QMap<QString, QString> pcCase::backup()
{
    QMap<QString, QString> ret;
    ret["Model"] = _model;
    ret["Form Factor"] = _formFactor;
    ret["Compatible Motherboards"] = _moboFF.join(", ");
    ret["GPU Length"] = QString::number(_maxGPU);
    ret["Cooler Height"] = QString::number(_maxCooler);
    ret["Expansion Slots"] = QString::number(_expansionSlots);
    ret["Fans"] = QString::number(_fans);
    ret["Fits Radiators"] = QString::number(_radiators);
    ret["HDD Slots"] = QString::number(_hdds);
    ret["SSD Slots"] = QString::number(_ssds);
    ret["USB Ports"] = QString::number(_usbs);
    ret["Front Audio"] = QString::number(_audio);
    ret["Height"] = QString::number(_height);
    ret["Width"] = QString::number(_width);
    ret["Length"] = QString::number(_length);
    ret["Price"] = QString::number(_price);
    return ret;
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
