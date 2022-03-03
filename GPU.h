#ifndef GPU_H_
#define GPU_H_

#include <QObject>
#include <QString>
#include <QStringList>

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
        GPU(QString model, int vram, int pcie, int bclock, int bus, int tdp, int pcieSlots, int height, int length, int price, QStringList inputs, int boost = -1):
            _model(model),
            _vram(vram),
            _pcieGen(pcie),
            _baseClock(bclock),
            _busSize(bus),
            _tdp(tdp),
            _pcieSlots(pcieSlots),
            _height(height),
            _length(length),
            _price(price),
            _inputs(inputs)
            {
                if (boost == -1)
                    _boostClock = _baseClock;
                else 
                    _boostClock = boost;
            };
        ~GPU(){};

        QString getModel() {return _model;}
        int getVram() {return _vram;}
        int getBaseClock() {return _baseClock;}
        int getBoostClock() {return _boostClock;}
        int getBusSize() {return _busSize;}
        int getTDP() {return _tdp;}
        int getSlots() {return _pcieSlots;}
        int getHeight() {return _height;}
        int getLength() {return _length;}
        int getPrice() {return _price;}
        QStringList getInputs() {return _inputs;}
        virtual QString getManu() {return (*this).getManu();}
        virtual bool hasRT() {return (*this).hasRT();}
        virtual bool runsDLSS() {return (*this).runsDLSS();}

        int setPrice(int price)
        {
            if (price < 0)
                return -1;
            _price = price;
            return 1;
        }

        int canFit(int pcieSlots, int height, int length)
        {
            return (pcieSlots >= _pcieSlots && height >= _height && length >= _length);
        }

        virtual string toString()
        {
            return
            "Model: " + _model.toStdString() + "\n" +
            "VRAM: " + to_string(_vram) + "GB\n" +
            "Base Clock: " + to_string(_baseClock) + "MHz\n" +
            "Boost Clock: " + to_string(_boostClock) + "MHz\n" +
            "Bus Size: " + to_string(_busSize) + "bit\n" +
            "TDP: " + to_string(_tdp) + "W\n" +
            "Slots: " + to_string(_pcieSlots) + "\n" +
            "Height: " + to_string(_height) + "\n" +
            "Length: " + to_string(_length) + "\n" +
            "Price: " + to_string(_price) + "\n" + 
            "Inputs: " + _inputs.join(", ").toStdString() + "\n";
        }
};

#endif
