#include "../../../include/PC_Parts/Storage/storage.h"

storage::storage(QString model, QString type, QString port, QString size, int read, int write, int cache, int price):
    _model(model),
    _type(type),
    _port(port),
    _size(size),
    _read(read),
    _write(write),
    _cache(cache),
    _price(price)
{}

QString storage::getModel()
{
    return _model;
}

QString storage::getType()
{
    return _type;
}

QString storage::getPort()
{
    return _port;
}

QString storage::getSize()
{
    return _size;
}

int storage::getSizeNum()
{
    int num = 0;
    QString type = "";
    foreach(QChar ch, _size)
    {
        if(ch.isNumber())
            num = num*10 + ch.digitValue();
        else
            type.append(ch);
    }
    if (type.toLower() == "tb")
        return num * 1000;
    if (type.toLower() == "pb")
        return num * 1000000;
    return num;
}

int storage::getRead()
{
    return _read;
}

int storage::getWrite()
{
    return _write;
}

int storage::getCache()
{
    return _cache;
}

int storage::getPrice()
{
    return _price;
}

int storage::setPrice(int price)
{
    if (price < 0)
        return -1;
    _price = price;
    return 1;
}

string storage::toString()
{
    return
            "Model: " + _model.toStdString() + "\n" +
            "Type: " + _type.toStdString() + "\n" +
            "Port: " + _port.toStdString() + "\n" +
            "Size: " + _size.toStdString() + "\n" +
            "Read Speed: " + to_string(_read) + "\n" +
            "Write Speed: " + to_string(_write) + "\n" +
            "Cache: " + to_string(_cache) + "\n" +
            "Price: " + to_string(_price) + "\n";
}

QMap<QString, QString> storage::backup()
{
    QMap<QString, QString> ret;
    ret["Model"] = _model;
    ret["Type"] = _type;
    ret["Port"] = _port;
    ret["Size"] = _size;
    ret["Read"] = QString::number(_read);
    ret["Write"] = QString::number(_write);
    ret["Cache"] = QString::number(_cache);
    ret["Price"] = QString::number(_price);
    return ret;
}
