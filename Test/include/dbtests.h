#ifndef DBTESTS_H
#define DBTESTS_H

#include "../../include/Database/filewriter.h"
#include "../../include/Database/filereader.h"

#include <QObject>
#include <QDebug>
#include <QTest>
#include <QList>
#include <QMap>

class dbtests : public QObject
{
    Q_OBJECT
public:
    explicit dbtests(QString dir, QObject *parent = nullptr);
    void cpuTests(dataHolder *h);
    void gpuTests(dataHolder *h);
    void moboTests(dataHolder *h);
    void ramTests(dataHolder *h);
    void storageTests(dataHolder *h);
    void coolerTests(dataHolder *h);
    void psuTests(dataHolder *h);
    void caseTests(dataHolder *h);

private:
    QString m_testDir;

public slots:
    void runTests();
};

#endif // DBTESTS_H
