#ifndef FILEREADER_H
#define FILEREADER_H

#include "dataholder.h"

#include <QObject>
#include <QJsonDocument>
#include <QFile>


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
