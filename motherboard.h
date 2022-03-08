#ifndef MOTHERBOARD_H_
#define MOTHERBOARD_H_

#include "CPU.h"
#include "RAM.h"
#include "storage.h"
#include "cooler.h"

#include <QObject>
#include <QString>
#include <QStringList>

using namespace std;

class motherboard: public QObject
{
    Q_OBJECT
    private:
        QString _model;
        QString _cpuManu;
        QString _socket;
        int _ram;
        int _maxRAM;
        QString _ramVersion;
        int _memChannels;
        int _pcieSlots;
        int _sataSlots;
        int _m2Slots;
        int _fanSlots;
        QString _formFactor;
        int _length;
        int _width;
        int _usbSlots;
        QStringList _videoOut;
        QStringList _audioOut;
        int _price;
        bool _ethernet;
        bool _wifi;
        bool _cpuFits;
        bool _ramFits;
        bool _storageFits;
        bool _coolerFits;

    public:
        motherboard(QString model, QString cpu, QString socket, int ram, QString ramV, int maxram, int chs, int pcie,
        int sata, int m2, int fan, QString ff, int l, int w, int usb, QStringList vid, QStringList aud,
        int price, bool eth = true, bool wifi = false);

        QString getModel();

        QString getCPUManufacturer();

        QString getSocket();

        int getRAMSlots();

        QString getRAMVersion();

        int getMaxRAMSize();

        int getPCIeSlots();

        int getSATASlots();

        int getM2Slots();

        int getFanHeaders();

        QString getFormFactor();

        int getLength();

        int getWidth();

        int getUSBSlots();

        QStringList getVideoOutputs();

        QStringList getAudioOutputs();

        int getPrice();

        bool hasEthernet();

        bool hasWifi();

        int setPrice(int price);

        bool canFit(QStringList formFactors, int l, int w);

        string toString();

    QMap<QString, QString> backup();

    bool cpuFits();
    void resetCPU();
    bool ramFits();
    void resetRAM();
    bool storageFits();
    void resetStorage();
    bool coolerFits();
    void resetCooler();

signals:

public slots:
    void cpuCompatibility(CPU *cpu);
    void ramCompatibility(RAM *ram);
    void storageCompatibility(storage *storage);
    void coolerCompatibility(cooler *cooler);
};

#endif
