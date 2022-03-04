#ifndef COOLER_H_
#define COOLER_H_

#include <QString>
#include <QObject>
#include <QList>
#include <QStringList>
#include <QMap>

using namespace std;

class cooler: public QObject
{
    Q_OBJECT
    private:
        QString _model;
        int _tdp;
        int _includedFans;
        int _maxFans;
        int _radiatorSize;
        int _height;
        QStringList _sockets;
        int _price;

    public:
        cooler(QString model, int tdp, int fans, int maxFans, int rads, int h, QStringList sockets, int price):
        _model(model),
        _tdp(tdp),
        _includedFans(fans),
        _maxFans(maxFans),
        _radiatorSize(rads),
        _height(h),
        _sockets(sockets),
        _price(price)
        {};
        
        QString getModel() {return _model;}
        int getTDP() {return _tdp;}
        int getIncludedFans() {return _includedFans;}
        int getMaxFans() {return _maxFans;}
        int getRadiatorSize() {return _radiatorSize;}
        int getHeight() {return _height;}
        QStringList supportedSockets() {return _sockets;}
        int getPrice() {return _price;}
        QString getType()
        {
            if (_radiatorSize > 0)
                return QString("AIO");
            return QString("Air");
        }

        int setPrice(int price)
        {
        if (price < 0)
            return -1;
        _price = price;
        return 1;
        }

        bool canMount(QString socket)
        {
            return _sockets.contains(socket);
        }

        bool canCool(int tdp) {return _tdp > tdp;}

        virtual bool canFit(int height, bool rads) {return (*this).canFit(height, rads);} // Can fit in a case

        QMap<QString, QString> backup()
        {
            QMap<QString, QString> ret;
            ret["Model"] = _model;
            ret["Type"] = getType();
            ret["TDP"] = QString::number(_tdp);
            ret["Included Fans"] = QString::number(_includedFans);
            ret["Maximum Fans"] = QString::number(_maxFans);
            if (ret["Type"] == "AIO")
                ret["Radiator Size"] = QString::number(_radiatorSize);
            else
                ret["Cooler Height"] = QString::number(_height);
            ret["Sockets"] = _sockets.join(", ");
            ret["Price"] = QString::number(_price);
            return ret;
        }

        string toString()
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
};

#endif
