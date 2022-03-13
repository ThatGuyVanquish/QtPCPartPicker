#include "../include/sbtestsreceiver.h"

sbtestsreceiver::sbtestsreceiver(QObject *parent)
    : QObject{parent}
{}

void sbtestsreceiver::specs(QList<CPU *> cpus, QList<GPU *> gpus, motherboard *mobo, RAM *ram,
                            QList<storage *> storage, cooler *cooler, pcCase *pcCase)
{
    m_cpus = cpus;
    m_gpus = gpus;
    m_mobo = mobo;
    m_ram = ram;
    m_storage = storage;
    m_cooler = cooler;
    m_case = pcCase;
}
