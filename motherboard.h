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
        int price, bool eth = true, bool wifi = false):
        _model(model),
        _cpuManu(cpu),
        _socket(socket),
        _ram(ram),
        _ramVersion(ramV),
        _maxRAM(maxram),
        _memChannels(chs),
        _pcieSlots(pcie),
        _sataSlots(sata),
        _m2Slots(m2),
        _fanSlots(fan),
        _formFactor(ff),
        _length(l),
        _width(w),
        _usbSlots(usb),
        _videoOut(vid),
        _audioOut(aud),
        _price(price),
        _ethernet(eth),
        _wifi(wifi),
        _cpuFits(false),
        _ramFits(false),
        _storageFits(false),
        _coolerFits(false)
        {};

        //SHIT TON OF GETTERS
        QString getModel() {return _model;}
        QString getCPUManufacturer() {return _cpuManu;}
        QString getSocket() {return _socket;}
        int getRAMSlots() {return _ram;}
        QString getRAMVersion() {return _ramVersion;}
        int getMaxRAMSize() {return _maxRAM;}
        int getPCIeSlots() {return _pcieSlots;}
        int getSATASlots() {return _sataSlots;}
        int getM2Slots() {return _m2Slots;}
        int getFanHeaders() {return _fanSlots;}
        QString getFormFactor() {return _formFactor;}
        int getLength() {return _length;}
        int getWidth() {return _width;}
        int getUSBSlots() {return _usbSlots;}
        QStringList getVideoOutputs() {return _videoOut;}
        QStringList getAudioOutputs() {return _audioOut;}
        int getPrice() {return _price;}
        bool hasEthernet() {return _ethernet;}
        bool hasWifi() {return _wifi;}

        int setPrice(int price)
        {
        if (price < 0)
            return -1;
        _price = price;
        return 1;
        }

        bool canFit(QStringList formFactors, int l, int w) // Checks whether a case fits @this motherboard
        {
            if (getLength() > l || getWidth() > w) // Can't fit due to size limitations
                return false;
            for (QString ff : formFactors) // Can't fit due to standoffs not available
                if (ff == _formFactor)
                    return true;
            return false;
        }

        string toString()
        {
            return
            "Model: " + _model.toStdString() + "\n" +
            "Fits CPUs from: " + _cpuManu.toStdString() + "\n" +
            "Socket: " + _socket.toStdString() + "\n" +
            "RAM Version: " + _ramVersion.toStdString() + "\n" +
            "RAM Slots: " + to_string(_ram) + "\n" +
            "Maximum RAM Size: " + to_string(_maxRAM) + "\n" +
            "PCIe Slots: " + to_string(_pcieSlots) + "\n" +
            "SATA Slots: " + to_string(_sataSlots) + "\n" +
            "M.2 Slots: " + to_string(_m2Slots) + "\n" +
            "Fan Headers: " + to_string(_fanSlots) + "\n" +
            "Form Factor: " + _formFactor.toStdString() + "\n" +
            "Length: " + to_string(_length) + "\n" +
            "Width: " + to_string(_width) + "\n" +
            "USB Slots: " + to_string(_usbSlots) + "\n" +
            "Video Outputs: " + _videoOut.join(", ").toStdString()+ "\n" +
            "Audio Outputs: " + _audioOut.join(", ").toStdString() + "\n" +
            "Ethernet: " + (_ethernet ? "Yes" : "No") + "\n" +
            "WiFi: " + (_wifi ? "Yes" : "No") + "\n" +
            "Price: " + to_string(_price) + "\n";
        }

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
