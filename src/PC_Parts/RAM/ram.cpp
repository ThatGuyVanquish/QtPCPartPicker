#include "../../../include/PC_Parts/RAM/ram.h"

RAM::RAM(QString model, QString version, int size, int dimms, int speed,
         QList<int> timing, int price, bool hs):
    _model(model),
    _version(version),
    _size(size),
    _dimms(dimms),
    _speed(speed),
    _timing(timing),
    _heatsink(hs),
    _price(price)
{}

QString RAM::getModel()
{
    return _model;
}

QString RAM::getVersion()
{
    return _version;
}

int RAM::getSpeed()
{
    return _speed;
}

int RAM::getSize()
{
    return _size;
}

int RAM::getDimms()
{
    return _dimms;
}

QList<int> RAM::getTimings()
{
    return _timing;
}

bool RAM::hasCooling()
{
    return _heatsink;
}

int RAM::getPrice()
{
    return _price;
}

int RAM::setPrice(int price)
{
    if (price < 0)
        return -1;
    _price = price;
    return 1;
}

bool RAM::canFit(QString rv)
{
    return _version == rv;
}

string RAM::toString()
{
    stringstream timings;
    for (int i = 0; i < _timing.size(); i++)
    {
        timings << _timing[i];
        if (i != _timing.size() -1)
            timings << ", ";
    }
    return
            "Model: " + _model.toStdString() + "\n" +
            "Version: " + _version.toStdString() + "\n" +
            "Size: " + to_string(_size) + "GB\n" +
            "DIMMS: " + to_string(_dimms) + "\n" +
            "Speed: " + to_string(_speed) + "MHz\n" +
            "Timings: " + timings.str() + "\n" +
            "Heatsink: " + (_heatsink ? "Yes" : "No") + "\n" +
            "Price: " + to_string(_price) + "\n";
}

QMap<QString, QString> RAM::backup()
{
    QMap<QString, QString> ret;
    ret["Model"] = _model;
    ret["Version"] = _version;
    ret["Size"] = QString::number(_size);
    ret["DIMMS"] = QString::number(_dimms);
    ret["Speed"] = QString::number(_speed);
    QString timings;
    for (int i = 0; i < _timing.size(); i++)
    {
        timings.append(QString::number(_timing[i]));
        if (i != _timing.size() -1)
            timings.append(", ");
    }
    ret["Timings"] = timings;
    ret["Heatsink"] = QString::number(_heatsink);
    ret["Price"] = QString::number(_price);
    return ret;
}
