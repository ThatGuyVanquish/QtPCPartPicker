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
        storage(QString model, QString type, QString port, QString size, int read,
                int write, int cache, int price);

        ~storage(){};

        QString getModel();

        QString getType();

        QString getPort();

        QString getSize();

        int getRead();

        int getWrite();

        int getCache();

        int getPrice();

        int setPrice(int price);

        string toString();

        QMap<QString, QString> backup();
};
#endif
