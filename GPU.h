#ifndef GPU_H_
#define GPU_H_

#include <QObject>
#include <QString>
#include <QStringList>
#include <QMap>

using namespace std;

class GPU: public QObject
{
    Q_OBJECT
    private:
        QString _model;
        int _vram;
        int _pcieGen;
        int _baseClock;
        int _boostClock;
        int _busSize;
        int _tdp;
        int _pcieSlots;
        int _height;
        int _length;
        int _price;
        QStringList _inputs;
    
    public:
        GPU(QString model, int vram, int pcie, int bclock, int bus, int tdp, int pcieSlots,
            int height, int length, int price, QStringList inputs, int boost = -1);
        ~GPU(){};

        QString getModel();
        int getVram();
        int getBaseClock();
        int getBoostClock();
        int getBusSize();
        int getTDP();
        int getSlots();
        int getHeight();
        int getLength();
        int getPrice();
        QStringList getInputs();
        virtual QString getManu();
        virtual bool hasRT();
        virtual bool runsDLSS();

        int setPrice(int price);

        int canFit(int pcieSlots, int height, int length);

        QMap<QString, QString> backup();

        virtual string toString();
};

#endif
