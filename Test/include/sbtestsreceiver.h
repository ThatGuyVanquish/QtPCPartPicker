#ifndef SBTESTSRECEIVER_H
#define SBTESTSRECEIVER_H

#include "../../include/Database/dataholder.h"

#include <QObject>

class sbtestsreceiver : public QObject
{
    Q_OBJECT

public:
    explicit sbtestsreceiver(QObject *parent = nullptr);

    CPU *m_cpu;
    QList<GPU*> m_gpus;
    RAM *m_ram;
    motherboard *m_mobo;
    cooler *m_cooler;
    PSU *m_psu;
    QList<storage*> m_storage;
    pcCase *m_case;

public slots:
    void specs(CPU *cpu, QList<GPU*> gpus, motherboard *mobo, RAM *ram, QList<storage*> storage,
               cooler *cooler, PSU *psu, pcCase *pcCase);

};

#endif // SBTESTSRECEIVER_H
