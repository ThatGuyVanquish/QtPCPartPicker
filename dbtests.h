#ifndef DBTESTS_H
#define DBTESTS_H

#include "fileWriter.h"
#include "filereader.h"

#include <QDebug>
#include <QTest>
#include <QObject>
#include <QList>
#include <QMap>

class dbtests : public QObject
{
    Q_OBJECT
public:
    explicit dbtests(QString dir, QObject *parent = nullptr);

private:
    QString m_testDir;
private slots:
    void cpuTests(dataHolder *h);
    void gpuTests(dataHolder *h);
    void moboTests(dataHolder *h);
    void ramTests(dataHolder *h);
    void storageTests(dataHolder *h);
    void coolerTests(dataHolder *h);
    void psuTests(dataHolder *h);
    void caseTests(dataHolder *h);

    void runTests();
signals:

};

#endif // DBTESTS_H
