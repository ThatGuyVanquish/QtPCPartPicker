#ifndef RAM_H_
#define RAM_H_

#include <QObject>
#include <QList>
#include <QMap>
#include <QString>
#include <sstream>

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
        RAM(QString model, QString version, int size, int dimms, int speed,
            QList<int> timing, int price, bool hs = true);
        
        ~RAM(){};

        QString getModel();

        QString getVersion();

        int getSpeed();

        int getSize();

        int getDimms();

        QList<int> getTimings();

        bool hasCooling();

        int getPrice();

        int setPrice(int price);

        bool canFit(QString rv);

        string toString();

        QMap<QString, QString> backup();
};

#endif
