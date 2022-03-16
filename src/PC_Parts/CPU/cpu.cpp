#include "../../../include/PC_Parts/CPU/cpu.h"

CPU::CPU(QString model, QString socket, int cores, double base, int l2, int l3,
         int lanes, int tdp, int price, bool igpu, bool cooler, int threads, double boost):
    _model(model),
    _socket(socket),
    _coreCount(cores),
    _baseClock(base),
    _l2Cache(l2),
    _l3Cache(l3),
    _lanes(lanes),
    _tdp(tdp),
    _price(price),
    _igpu(igpu),
    _cooler(cooler)
{
    if (boost == -1) _boostClock = _baseClock;
    else _boostClock = boost;
    if (threads == -1) _threadCount = _coreCount;
    else _threadCount = threads;
}

QString CPU::getModel()
{
    return _model;
}

QString CPU::getSocket()
{
    return _socket;
}

int CPU::getCores()
{
    return _coreCount;
}

int CPU::getThreads() {
    return _threadCount;
}

double CPU::getBaseClock()
{
    return _baseClock;
}

double CPU::getBoostClock()
{
    return _boostClock;
}

int CPU::getL2Cache()
{
    return _l2Cache;
}

int CPU::getL3Cache()
{
    return _l3Cache;
}

int CPU::getLanes()
{
    return _lanes;
}

int CPU::getTDP()
{
    return _tdp;
}

int CPU::getPrice()
{
    return _price;
}

bool CPU::hasGraphics()
{
    return _igpu;
}

bool CPU::includesCooler()
{
    return _cooler;
}

int CPU::setPrice(int price)
{
    if (price < 0)
        return -1;
    _price = price;
    return 1;
}

bool CPU::operator>(CPU *other)
{
    return this->_coreCount > other->_coreCount ||
            (this->_coreCount == other->_coreCount && this->_baseClock >= other->_baseClock);
}

QMap<QString, QString> CPU::backup()
{
    QMap<QString, QString> ret;
    ret["Model"] = _model;
    ret["Manufacturer"] = getManu();
    ret["Socket"] = _socket;
    ret["Cores"] = QString::number(_coreCount);
    ret["Threads"] = QString::number(_threadCount);
    ret["BClock"] = QString::number(_baseClock);
    ret["Boost"] = QString::number(_boostClock);
    ret["L2"] = QString::number(_l2Cache);
    ret["L3"] = QString::number(_l3Cache);
    ret["PCIe"] = QString::number(_lanes);
    ret["TDP"] = QString::number(_tdp);
    ret["Price"] = QString::number(_price);
    ret["iGPU"] = QString::number(_igpu);
    ret["Cooler"] = QString::number(_cooler);
    if (ret["Manufacturer"] == "Intel")
        ret["Unlocked"] = QString::number(isUnlocked());
    return ret;
}

string CPU::toString()
{
    return
            "Model: " + _model.toStdString() + "\n" +
            "Socket: " + _socket.toStdString() + "\n" +
            "Number of Cores: " + to_string(_coreCount) + "\n" +
            "Number of Threads: " + to_string(_threadCount) + "\n" +
            "Base Clock: " + to_string(_baseClock) + "GHz\n" +
            "Boost Clock: " + to_string(_boostClock) + "GHz\n" +
            "L2 Cache: " + to_string(_l2Cache) + "MB\n" +
            "L3 Cache: " + to_string(_l3Cache) + "MB\n" +
            "PCIe Lanes: " + to_string(_lanes) + "\n" +
            "TDP: " + to_string(_tdp) + "W\n" +
            "MSRP: " + to_string(_price) + "\n" +
            "iGPU: " + (_igpu ? "Yes" : "No") + "\n" +
            "Cooler Included: " + (_cooler ? "Yes" : "No") + "\n";
}

bool CPU::canFit(QString socket)
{
    return socket == _socket;
}
