#ifndef CPU_H_
#define CPU_H_

#include <QObject>
#include <QString>
#include <QMap>

using namespace std;

class CPU: public QObject
{
    Q_OBJECT
private:
    QString _model;
    QString _socket;
    int _coreCount;
    int _threadCount;
    double _baseClock;
    double _boostClock;
    int _l2Cache;
    int _l3Cache;
    int _lanes;
    int _tdp;
    int _price;
    bool _cooler;
    bool _igpu;

public:
    explicit CPU(QObject *parent = nullptr){};
    CPU(QString model, QString socket, int cores, double base, int l2, int l3, int lanes, int tdp,
        int price, bool igpu, bool cooler = false, int threads = -1, double boost = -1);
    virtual ~CPU() {}

    QString getModel();
    QString getSocket();
    int getCores();
    int getThreads();
    double getBaseClock();
    double getBoostClock();
    int getL2Cache();
    int getL3Cache();
    int getLanes();
    int getTDP();
    int getPrice();
    bool hasGraphics();
    bool includesCooler();
    virtual QString getManu() = 0;
    virtual bool isUnlocked() = 0;

    int setPrice(int price);

    bool operator>(CPU *other);

    QMap<QString, QString> backup();

    virtual string toString();

signals:

public slots:
    bool canFit(QString socket);
};

#endif
