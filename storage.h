#ifndef STORAGE_H_
#define STORAGE_H_

#include <QObject>
#include <QString>
#include <QMap>

using namespace std;

class storage: public QObject
{
    Q_OBJECT
    private:
        QString _model;
        QString _type;
        QString _port;
        QString _size;
        int _read;
        int _write;
        int _cache;
        int _price;

    public:
        storage(QString model, QString type, QString port, QString size, int read, int write, int cache, int price):
            _model(model),
            _type(type),
            _port(port),
            _size(size),
            _read(read),
            _write(write),
            _cache(cache),
            _price(price)
            {};
        QString getModel() {return _model;}
        QString getType() {return _type;}
        QString getPort() {return _port;}
        QString getSize() {return _size;}
        int getRead() {return _read;}
        int getWrite() {return _write;}
        int getCache() {return _cache;}
        int getPrice() {return _price;}

        int setPrice(int price)
        {
        if (price < 0)
            return -1;
        _price = price;
        return 1;
        }

        QMap<QString, QString> backup()
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

        string toString()
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
};
#endif
