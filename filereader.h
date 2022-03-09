#ifndef FILEREADER_H
#define FILEREADER_H

#include "dataholder.h"

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
    bool restore();

    void restoreCPUs(QFile *f);
    void restoreGPUs(QFile *f);
    void restoreMotherboards(QFile *f);
    void restoreRAM(QFile *f);
    void restoreStorage(QFile *f);
    void restoreCoolers(QFile *f);
    void restoreCases(QFile *f);

signals:

};

#endif // FILEREADER_H
