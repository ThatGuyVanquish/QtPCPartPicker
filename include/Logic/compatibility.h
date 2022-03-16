#ifndef COMPATIBILITY_H
#define COMPATIBILITY_H

#include "../Database/dataholder.h"
#include <QObject>

class Compatibility : public QObject
{
    Q_OBJECT

private:
    dataHolder *m_data;
public:
    explicit Compatibility(QObject *parent = nullptr);
    Compatibility(dataHolder *data):
        m_data(data)
        {};

    bool testCompatibility(motherboard *mobo, CPU *cpu);
    bool testCompatibility(motherboard *mobo, RAM *ram);
    bool testCompatibility(motherboard *mobo, cooler *cooler);
    bool testCompatibility(motherboard *mobo, storage *storage);
    bool testCompatibility(pcCase *pcCase, motherboard *mobo);
    bool testCompatibility(pcCase *pcCase, storage *storage);
    bool testCompatibility(pcCase *pcCase, GPU *gpu);
    bool testCompatibility(pcCase *pcCase, cooler *cooler);
    bool testCompatibility(PSU *psu, CPU *cpu, QList<GPU*> gpus);

signals:

public slots:

};

#endif // COMPATIBILITY_H
