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
    PSU(QString model, QString modularity, Efficiency efficiency, int wattage, int price, bool fan = true);

    QString getModel();

    QString getModularity();

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
    void couldPower(CPU *cpu, GPU *gpu); // 1 CPU, up to 1 GPU
    void couldPower(QList<CPU*> cpus, GPU *gpu); // up to 2 CPUs, up to 1 GPU
    void couldPower(QList<CPU*> cpus, QList<GPU*> gpus); // Up to 2 CPUs, multiple GPUs
    void couldPower(CPU *cpu, QList<GPU*> gpus); // 1 CPU, multiple GPUs

signals:

};

#endif // PSU_H
