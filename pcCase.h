#ifndef CASE_H_
#define CASE_H_

#include "motherboard.h"
#include "GPU.h"
#include "cooler.h"
#include "storage.h"

#include <QObject>
#include <QString>
#include <QStringList>
#include <QMap>

using namespace std;

class pcCase: public QObject
{
    Q_OBJECT
private:
    QString _model;
    QString _formFactor;
    QStringList _moboFF;
    int _maxGPU;
    int _maxCooler;
    int _expansionSlots;
    int _fans;
    bool _radiators;
    int _hdds;
    int _ssds;
    int _usbs;
    bool _audio;
    int _height;
    int _width;
    int _length;
    int _price;
    bool _moboFits;
    bool _storageFits;
    bool _gpuFits;
    bool _coolerFits;

public:
    pcCase(QString model, QString ff, QStringList mbff, int gpu, int cooler, int pcieSlots, int fans, int hdds, int ssds, int usbs,
    int height, int width, int length, int price, bool rad = false, bool audio = true):
    _model(model),
    _formFactor(ff),
    _moboFF(mbff),
    _maxGPU(gpu),
    _maxCooler(cooler),
    _expansionSlots(pcieSlots),
    _fans(fans),
    _radiators(rad),
    _hdds(hdds),
    _ssds(ssds),
    _usbs(usbs),
    _audio(audio),
    _height(height),
    _width(width),
    _length(length),
    _price(price)
    {};

    QString getModel() {return _model;}
    QString getFormFactor() {return _formFactor;}
    QStringList getMoboSupport() {return _moboFF;}
    int getMaxGPULength() {return _maxGPU;}
    int getMaxCoolerHeight() {return _maxCooler;}
    int getExpansionSlots() {return _expansionSlots;}
    int getIncludedFans() {return _fans;}
    bool fitsRadiators() {return _radiators;}
    int getHDDSlots() {return _hdds;}
    int getSSDSlots() {return _ssds;}
    int getUSBPorts() {return _usbs;}
    bool hasFrontAudio() {return _audio;}
    QList<int> getMeasurements() {return QList<int>({_height,_width,_length});}
    int getPrice() {return _price;}

    int setPrice(int price)
    {
    if (price < 0)
        return -1;
    _price = price;
    return 1;
    }

    QMap<QString, QString> backup();

    string toString()
    {
        return
        "Model: " + _model.toStdString() + "\n" +
        "Form Factor: " + _formFactor.toStdString() + "\n" +
        "Motherboard Compatibility: " + _moboFF.join(", ").toStdString() + "\n" +
        "Maximum GPU Length: " + to_string(_maxGPU) + "\n" +
        "Maximum CPU Cooler Height: " + to_string(_maxCooler) + "\n" +
        "Expansion Slots: " + to_string(_expansionSlots) + "\n" +
        "Total Fans: " + to_string(_fans) + "\n" +
        "Fits Radiators: " + (_radiators ? "Yes" : "No") + "\n" +
        "Hard Drive Slots: " + to_string(_hdds) + "\n" +
        "SSD Slots: " + to_string(_ssds) + "\n" +
        "USB Ports: " + to_string(_usbs) + "\n" +
        "Front Audio: " + (_audio ? "Yes" : "No") + "\n" +
        "Measurements: (H)" + to_string(_height) + "x(W)" + to_string(_width) + "x(L)" + to_string(_length) + "\n" +
        "Price: " + to_string(_price) + "\n";
    }

    int calculateCaseVolume()
    {
        QList<int> mes = this->getMeasurements();
        return mes[0] * mes[1] * mes[2];
    }

    bool moboFits();
    void resetMobo();
    bool storageFits();
    void resetStorage();
    bool gpuFits();
    void resetGPU();
    bool coolerFits();
    void resetCooler();

public slots:
    void motherboardCompatibility(motherboard *mobo);
    void coolerCompatibility(cooler *cooler);
    void gpuCompatibility(GPU *gpu);
    void storageCompatibility(storage *storage);
};

#endif
