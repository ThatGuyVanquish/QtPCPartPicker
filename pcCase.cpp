#include "pcCase.h"

pcCase::pcCase(QString model, QString ff, QStringList mbff, int gpu, int cooler,
               int pcieSlots, int fans, int hdds, int ssds, int usbs, int height,
               int width, int length, int price, bool rad, bool audio):
    _model(model),
    _formFactor(ff),
    _moboFF(mbff),
    _maxGPU(gpu),
    _maxCooler(cooler),
    _expansionSlots(pcieSlots),
    _fans(fans),
    _radiators(rad),
    _hdds(hdds),
    _ssds(ssds),
    _usbs(usbs),
    _audio(audio),
    _height(height),
    _width(width),
    _length(length),
    _price(price)
{}

QString pcCase::getModel()
{
    return _model;
}

QString pcCase::getFormFactor()
{
    return _formFactor;
}

QStringList pcCase::getMoboSupport()
{
    return _moboFF;
}

int pcCase::getMaxGPULength()
{
    return _maxGPU;
}

int pcCase::getMaxCoolerHeight()
{
    return _maxCooler;
}

int pcCase::getExpansionSlots()
{
    return _expansionSlots;
}

int pcCase::getIncludedFans()
{
    return _fans;
}

bool pcCase::fitsRadiators()
{
    return _radiators;
}

int pcCase::getHDDSlots()
{
    return _hdds;
}

int pcCase::getSSDSlots()
{
    return _ssds;
}

int pcCase::getUSBPorts()
{
    return _usbs;
}

bool pcCase::hasFrontAudio()
{
    return _audio;
}

QList<int> pcCase::getMeasurements()
{
    return QList<int>({_height,_width,_length});
}

int pcCase::getPrice()
{
    return _price;
}

int pcCase::setPrice(int price)
{
    if (price < 0)
        return -1;
    _price = price;
    return 1;
}

string pcCase::toString()
{
    return
            "Model: " + _model.toStdString() + "\n" +
            "Form Factor: " + _formFactor.toStdString() + "\n" +
            "Motherboard Compatibility: " + _moboFF.join(", ").toStdString() + "\n" +
            "Maximum GPU Length: " + to_string(_maxGPU) + "\n" +
            "Maximum CPU Cooler Height: " + to_string(_maxCooler) + "\n" +
            "Expansion Slots: " + to_string(_expansionSlots) + "\n" +
            "Total Fans: " + to_string(_fans) + "\n" +
            "Fits Radiators: " + (_radiators ? "Yes" : "No") + "\n" +
            "Hard Drive Slots: " + to_string(_hdds) + "\n" +
            "SSD Slots: " + to_string(_ssds) + "\n" +
            "USB Ports: " + to_string(_usbs) + "\n" +
            "Front Audio: " + (_audio ? "Yes" : "No") + "\n" +
            "Measurements: (H)" + to_string(_height) + "x(W)" + to_string(_width) + "x(L)" + to_string(_length) + "\n" +
            "Price: " + to_string(_price) + "\n";
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

int pcCase::calculateCaseVolume()
{
    QList<int> mes = this->getMeasurements();
    return mes[0] * mes[1] * mes[2];
}

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


