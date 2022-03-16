#ifndef CASE_H_
#define CASE_H_

#include "../Motherboard/motherboard.h"
#include "../GPU/gpu.h"
#include "../Cooler/cooler.h"
#include "../Storage/storage.h"

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
    pcCase(QString model, QString ff, QStringList mbff, int gpu, int cooler, int pcieSlots,
           int fans, int hdds, int ssds, int usbs, int height, int width, int length,
           int price, bool rad = false, bool audio = true);

    QString getModel();

    QString getFormFactor();

    QStringList getMoboSupport();

    int getMaxGPULength();

    int getMaxCoolerHeight();

    int getExpansionSlots();

    int getIncludedFans();

    bool fitsRadiators();

    int getHDDSlots();

    int getSSDSlots();

    int getUSBPorts();

    bool hasFrontAudio();

    QList<int> getMeasurements();

    int getPrice();

    int setPrice(int price);

    string toString();

    QMap<QString, QString> backup();

    int calculateCaseVolume();

    bool fitsCooler(cooler *cooler);
    bool fitsMobo(motherboard *mobo);
    bool fitsGPU(GPU *gpu);

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
