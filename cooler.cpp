#include "cooler.h"

cooler::cooler(QString model, int tdp, int fans, int maxFans, int rads, int h, QStringList sockets, int price):
    _model(model),
    _tdp(tdp),
    _includedFans(fans),
    _maxFans(maxFans),
    _radiatorSize(rads),
    _height(h),
    _sockets(sockets),
    _price(price)
{}

QString cooler::getModel()
{
    return _model;
}

int cooler::getTDP()
{
    return _tdp;
}

int cooler::getIncludedFans()
{
    return _includedFans;
}

int cooler::getMaxFans()
{
    return _maxFans;
}

int cooler::getRadiatorSize()
{
    return _radiatorSize;
}

int cooler::getHeight()
{
    return _height;
}

QStringList cooler::supportedSockets()
{
    return _sockets;
}

int cooler::getPrice()
{
    return _price;
}

QString cooler::getType()
{
    if (_radiatorSize > 0)
        return QString("AIO");
    return QString("Air");
}

int cooler::setPrice(int price)
{
    if (price < 0)
        return -1;
    _price = price;
    return 1;
}

bool cooler::canMount(QString socket)
{
    return _sockets.contains(socket);
}

bool cooler::canCool(int tdp)
{
    return _tdp > tdp;
}

bool cooler::canFit(int height, bool rads)
{
    return (*this).canFit(height, rads);
}

QMap<QString, QString> cooler::backup()
{
    QMap<QString, QString> ret;
    ret["Model"] = _model;
    ret["Type"] = getType();
    ret["TDP"] = QString::number(_tdp);
    ret["Included Fans"] = QString::number(_includedFans);
    ret["Maximum Fans"] = QString::number(_maxFans);
    if (ret["Type"] == "AIO")
        ret["Radiator Size"] = QString::number(_radiatorSize);
    ret["Cooler Height"] = QString::number(_height);
    ret["Sockets"] = _sockets.join(", ");
    ret["Price"] = QString::number(_price);
    return ret;
}

string cooler::toString()
{
    return
            "Model: " + _model.toStdString() + "\n" +
            "TDP: " + to_string(_tdp) + "\n" +
            "Number of included fans: " + to_string(_includedFans) + "\n" +
            "Maximum fans that can be mounted: " + to_string(_maxFans) + "\n" +
            "Radiator Size: " + to_string(_radiatorSize) + "\n" +
            "Cooler height: " + to_string(_height) + "\n" +
            "Supported sockets: " + _sockets.join(",").toStdString() + "\n" +
            "Price: " + to_string(_price) + "\n";
}
