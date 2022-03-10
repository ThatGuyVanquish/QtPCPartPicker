#ifndef PSU_H
#define PSU_H

#include "CPU.h"
#include "GPU.h"

#include <QObject>
#include <QMap>

using namespace std;

enum Efficiency {None, Bronze, Silver, Gold, Platinum, Titanium};

class PSU : public QObject
{
    Q_OBJECT
private:
    QString _model;
    QString _modularity;
    QString _ff; // Currently won't be in use, would need to add psu ff support to pcCase
    Efficiency _efficiency;
    int _wattage;
    bool _fan;
    int _price;
    bool _canPower;
    // Could add ports list but then I'd need to change GPU, motherboard and storage as well.
    // Might add that later on after everything is complete and working as planned.

    double effPercentage();

public:
    explicit PSU(QObject *parent = nullptr);
    PSU(QString model, QString modularity, QString ff, Efficiency efficiency, int wattage, int price, bool fan = true);

    QString getModel();

    QString getModularity();

    QString getFormFactor();

    QString efficiency();

    int getWattage();

    bool hasFan();

    int getPrice();

    bool canPower();

    void resetPower();

    int setPrice(int price);

    QMap<QString, QString> backup();

    virtual string toString();

public slots:
    void couldPower(QList<CPU*> cpus, QList<GPU*> gpus); // Up to 2 CPUs, multiple GPUs

signals:

};

static Efficiency getEfficiency(QString str);

#endif // PSU_H
