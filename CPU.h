#ifndef CPU_H_
#define CPU_H_

#include <QString>
#include <QObject>
#include <QFuture>

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
    CPU(QString model, QString socket, int cores, double base, int l2, int l3, int lanes, int tdp, int price, bool igpu, bool cooler = false,
    int threads = -1, double boost = -1):
        _model(model),
        _socket(socket),
        _coreCount(cores),
        _baseClock(base),
        _l2Cache(l2),
        _l3Cache(l3),
        _lanes(lanes),
        _tdp(tdp),
        _price(price),
        _igpu(igpu),
        _cooler(cooler)
    {
        if (boost == -1) _boostClock = _baseClock;
        else _boostClock = boost;
        if (threads == -1) _threadCount = _coreCount;
        else _threadCount = threads;
    }
    virtual ~CPU() {}

    // Getters
    QString getModel() {return _model;}
    QString getSocket() {return _socket;}
    int getCores() {return _coreCount;}
    int getThreads() {return _threadCount;}
    double getBaseClock() {return _baseClock;}
    double getBoostClock() {return _boostClock;} 
    int getL2Cache() {return _l2Cache;}
    int getL3Cache() {return _l3Cache;}
    int getLanes() {return _lanes;}
    int getTDP() {return _tdp;}
    int getPrice() {return _price;}
    bool hasGraphics() {return _igpu;}
    bool includesCooler() {return _cooler;}
    virtual QString getManu() {return (*this).getManu();}


    int setPrice(int price)
    {
        if (price < 0)
            return -1;
        _price = price;
        return 1;
    }

    virtual string toString() // Is this necessary? especially if I write to JSON
    {   
        return
        "Model: " + _model.toStdString() + "\n" +
        "Socket: " + _socket.toStdString() + "\n" +
        "Number of Cores: " + to_string(_coreCount) + "\n" +
        "Number of Threads: " + to_string(_threadCount) + "\n" +
        "Base Clock: " + to_string(_baseClock) + "GHz\n" +
        "Boost Clock: " + to_string(_boostClock) + "GHz\n" +
        "L2 Cache: " + to_string(_l2Cache) + "MB\n" +
        "L3 Cache: " + to_string(_l3Cache) + "MB\n" +
        "PCIe Lanes: " + to_string(_lanes) + "\n" +
        "TDP: " + to_string(_tdp) + "W\n" +
        "MSRP: " + to_string(_price) + "\n" +
        "iGPU: " + (_igpu ? "Yes" : "No") + "\n" +
        "Cooler Included: " + (_cooler ? "Yes" : "No") + "\n";
    }

signals:
    void insert(CPU* cpu);

public slots:
    bool canFit(QString socket) {return socket == _socket;}
};

#endif
