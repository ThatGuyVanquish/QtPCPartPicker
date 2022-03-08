#ifndef FILEWRITER_H
#define FILEWRITER_H

#include "dataholder.h"

#include <fstream>
#include <QObject>
#include <QFile>
#include <QVariant>
#include <QVariantMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QIODevice>
#include <QDebug>

class fileWriter
{
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
    fileWriter(dataHolder *db);
    ~fileWriter(){}

    void closeFiles();
    int openFiles();

    void cpuBackup();
    void gpuBackup();
    void moboBackup();
    void ramBackup();
    void storageBackup();
    void coolerBackup();
    void caseBackup();

    bool backup ();

};


#endif // FILEWRITER_H
