#ifndef SPECBUILDERTESTS_H
#define SPECBUILDERTESTS_H

#include "../../include/Database/filewriter.h"
#include "../../include/Database/filereader.h"

#include <QObject>

class specBuilderTests : public QObject
{
    Q_OBJECT

private:
    QString m_testDir;
    void backup(dataHolder *h);
    void createCPUs(dataHolder *h);
    void createGPUs(dataHolder *h);
    void createMobos(dataHolder *h);
    void createRAM(dataHolder *h);
    void createCoolers(dataHolder *h);
    void createPSUs(dataHolder *h);
    void createStorage(dataHolder *h);
    void createCases(dataHolder *h);
    void createDB(dataHolder *h);
    void initialize(dataHolder *h);
    void restore(dataHolder *h);

public:
    explicit specBuilderTests(QString dir, QObject *parent = nullptr);
    void testMining(dataHolder *h);
    void testServer(dataHolder *h);
    void testOffice(dataHolder *h);
    void testGaming(dataHolder *h);
    void testOverclocking(dataHolder *h);
    void testGeneral(dataHolder *h);

public slots:

    void runTests();
};

#endif // SPECBUILDERTESTS_H
