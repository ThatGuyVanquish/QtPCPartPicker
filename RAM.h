#ifndef RAM_H_
#define RAM_H_

#include <QObject>
#include <QString>
#include <sstream>
#include <QList>
#include <QMap>

using namespace std;

class RAM: public QObject
{
    Q_OBJECT
    private:
        QString _model;
        QString _version;
        int _size;
        int _dimms;
        int _speed;
        QList<int> _timing;
        bool _heatsink;
        int _price;

    public:
        RAM(QString model, QString version, int size, int dimms, int speed, QList<int> timing, int price, bool hs = true):
            _model(model),
            _version(version),
            _size(size),
            _dimms(dimms),
            _speed(speed),
            _timing(timing),
            _heatsink(hs),
            _price(price)
            {};
        
        QString getModel() {return _model;}
        QString getVersion() {return _version;}
        int getSpeed() {return _speed;}
        int getSize() {return _size;}
        int getDimms() {return _dimms;}
        QList<int> getTimings() {return _timing;}
        bool hasCooling() {return _heatsink;}
        int getPrice() {return _price;}

        int setPrice(int price)
        {
        if (price < 0)
            return -1;
        _price = price;
        return 1;
        }

        bool canFit(QString rv)
        {
            return _version == rv;
        }

        QMap<QString, QString> backup()
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

        string toString()
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
};

#endif
