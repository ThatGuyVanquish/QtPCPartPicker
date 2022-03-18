#include "../../../include/PC_Parts/Motherboard/motherboard.h"

void motherboard::cpuCompatibility(CPU *cpu)
{
    _cpuFits = cpu->getSocket() == _socket;
}

motherboard::motherboard(QString model, QString cpu, QString socket, int ram,
                         QString ramV, int maxram, int chs, int pcie, int sata,
                         int m2, int fan, QString ff, int l, int w, int usb, QStringList vid,
                         QStringList aud, int price, bool eth, bool wifi):
    _model(model),
    _cpuManu(cpu),
    _socket(socket),
    _ram(ram),
    _ramVersion(ramV),
    _maxRAM(maxram),
    _memChannels(chs),
    _pcieSlots(pcie),
    _sataSlots(sata),
    _m2Slots(m2),
    _fanSlots(fan),
    _formFactor(ff),
    _length(l),
    _width(w),
    _usbSlots(usb),
    _videoOut(vid),
    _audioOut(aud),
    _price(price),
    _ethernet(eth),
    _wifi(wifi),
    _cpuFits(false),
    _ramFits(false),
    _storageFits(false),
    _coolerFits(false)
{}

QString motherboard::getModel()
{
    return _model;
}

QString motherboard::getCPUManufacturer()
{
    return _cpuManu;
}

QString motherboard::getSocket()
{
    return _socket;
}

int motherboard::getRAMSlots()
{
    return _ram;
}

QString motherboard::getRAMVersion()
{
    return _ramVersion;
}

int motherboard::getMaxRAMSize()
{
    return _maxRAM;
}

int motherboard::getPCIeSlots()
{
    return _pcieSlots;
}

int motherboard::getSATASlots()
{
    return _sataSlots;
}

int motherboard::getM2Slots()
{
    return _m2Slots;
}

int motherboard::getFanHeaders()
{
    return _fanSlots;
}

QString motherboard::getFormFactor()
{
    return _formFactor;
}

int motherboard::getLength()
{
    return _length;
}

int motherboard::getWidth()
{
    return _width;
}

int motherboard::getUSBSlots()
{
    return _usbSlots;
}

QStringList motherboard::getVideoOutputs()
{
    return _videoOut;
}

QStringList motherboard::getAudioOutputs()
{
    return _audioOut;
}

int motherboard::getPrice()
{
    return _price;
}

bool motherboard::hasEthernet()
{
    return _ethernet;
}

bool motherboard::hasWifi()
{
    return _wifi;
}

int motherboard::setPrice(int price)
{
    if (price < 0)
        return -1;
    _price = price;
    return 1;
}

bool motherboard::canFit(QStringList formFactors, int l, int w) // Checks whether a case fits @this motherboard
{
    if (getLength() > l || getWidth() > w) // Can't fit due to size limitations
        return false;
    for (QString &ff : formFactors) // Can't fit due to standoffs not available
        if (ff == _formFactor)
            return true;
    return false;
}

string motherboard::toString()
{
    return
    "Model: " + _model.toStdString() + "\n" +
    "Fits CPUs from: " + _cpuManu.toStdString() + "\n" +
    "Socket: " + _socket.toStdString() + "\n" +
    "RAM Version: " + _ramVersion.toStdString() + "\n" +
    "RAM Slots: " + to_string(_ram) + "\n" +
    "Maximum RAM Size: " + to_string(_maxRAM) + "\n" +
    "PCIe Slots: " + to_string(_pcieSlots) + "\n" +
    "SATA Slots: " + to_string(_sataSlots) + "\n" +
    "M.2 Slots: " + to_string(_m2Slots) + "\n" +
    "Fan Headers: " + to_string(_fanSlots) + "\n" +
    "Form Factor: " + _formFactor.toStdString() + "\n" +
    "Length: " + to_string(_length) + "\n" +
    "Width: " + to_string(_width) + "\n" +
    "USB Slots: " + to_string(_usbSlots) + "\n" +
    "Video Outputs: " + _videoOut.join(", ").toStdString()+ "\n" +
    "Audio Outputs: " + _audioOut.join(", ").toStdString() + "\n" +
    "Ethernet: " + (_ethernet ? "Yes" : "No") + "\n" +
    "WiFi: " + (_wifi ? "Yes" : "No") + "\n" +
    "Price: " + to_string(_price) + "\n";
}

QMap<QString, QString> motherboard::backup()
{
    QMap<QString, QString> ret;
    ret["Model"] = _model;
    ret["CPU Manufacturer"] = _cpuManu;
    ret["Socket"] = _socket;
    ret["RAM Slots"] = QString::number(_ram);
    ret["RAM Version"] = _ramVersion;
    ret["Max RAM Size"] = QString::number(_maxRAM);
    ret["RAM Channels"] = QString::number(_memChannels);
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
    _ramFits = ram->getVersion() == _ramVersion;
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
