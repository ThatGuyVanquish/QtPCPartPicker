#ifndef FILEREADER_H
#define FILEREADER_H

#include "dataholder.h"
#include "CPU.h"
#include "GPU.h"
#include "intelCPU.cpp"
#include "intelGPU.cpp"
#include "amdCPU.cpp"
#include "amdGPU.cpp"
#include "nvidiaGPU.cpp"
#include "motherboard.h"
#include "RAM.h"
#include "storage.h"
#include "hdd.cpp"
#include "sataSSD.cpp"
#include "m2SSD.cpp"
#include "pcCase.h"
#include "cooler.h"
#include "AIO.cpp"
#include "airCooler.cpp"

#include <QObject>
#include <QJsonDocument>
#include <QFile>
#include <QMap>
#include <QVariantMap>
#include <QVariant>


class fileReader : public QObject
{
    Q_OBJECT
private:
    dataHolder *m_db;
    QFile m_cpu;
    QFile m_gpu;
    QFile m_mobo;
    QFile m_ram;
    QFile m_storage;
    QFile m_case;
    QFile m_cooler;

public:
    explicit fileReader(QObject *parent = nullptr);
    fileReader(dataHolder *db);

    int openFiles();
    void closeFiles();

    void restoreCPUs();
    void restoreGPUs();
    void restoreMotherboards();
    void restoreRAM();
    void restoreStorage();
    void restoreCoolers();
    void restoreCases();

signals:

};

#endif // FILEREADER_H
