#ifndef COOLER_H_
#define COOLER_H_

#include <QObject>
#include <QList>
#include <QStringList>
#include <QMap>
#include <QString>

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
        cooler(QString model, int tdp, int fans, int maxFans, int rads, int h, QStringList sockets, int price);
        
        QString getModel();

        int getTDP();

        int getIncludedFans();

        int getMaxFans();

        int getRadiatorSize();

        int getHeight();

        QStringList supportedSockets();

        int getPrice();

        QString getType();

        int setPrice(int price);

        bool canMount(QString socket);

        bool canCool(int tdp);

        virtual bool canFit(int height, bool rads); // Can fit in a case

        QMap<QString, QString> backup();

        string toString();
};

#endif
