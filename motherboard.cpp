#include "motherboard.h"

void motherboard::cpuCompatibility(CPU *cpu)
{
    _cpuFits = cpu->getSocket() == _socket;
}

QMap<QString, QString> motherboard::backup()
{
    QMap<QString, QString> ret;
    ret["Model"] = _model;
    ret["Socket"] = _socket;
    ret["RAM Slots"] = QString::number(_ram);
    ret["RAM Version"] = _ramVersion;
    ret["Max RAM Size"] = QString::number(_maxRAM);
    ret["PCIE Slots"] = QString::number(_pcieSlots);
    ret["SATA Slots"] = QString::number(_sataSlots);
    ret["M.2 Slots"] = QString::number(_m2Slots);
    ret["Fan Headers"] = QString::number(_fanSlots);
    ret["Form Factor"] = _formFactor;
    ret["Length"] = QString::number(_length);
    ret["Width"] = QString::number(_width);
    ret["USB Slots"] = QString::number(_usbSlots);
    ret["Video Outputs"] = _videoOut.join(", ");
    ret["Audio Outputs"] = _audioOut.join(", ");
    ret["Price"] = QString::number(_price);
    ret["Ethernet"] = QString::number(_ethernet);
    ret["Wifi"] = QString::number(_wifi);
    return ret;
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
