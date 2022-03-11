#include "../include/specbuildertests.h"

void specBuilderTests::backup(dataHolder *h)
{
    qDebug() << "Backing up dataHolder";
    fileWriter fw(h);
    fw.backup();
}

void specBuilderTests::createCPUs(dataHolder *h)
{
    /*
     * Create 2 of each type for each manufacturer:
     * Server, OC, 8 Cores (different sockets), 6 Cores (different sockets), 2 Cores (different sockets)
    */

    /*
     * Intel CPUs
     *  intelCPU(QString model, QString socket, int cores, double base, int l2, int l3, int lanes, int tdp,
     *      int price, bool igpu = true, bool cooler = false, int threads = -1, double boost = -1,
     *      bool unlocked = false)
    */
    // 2 Cores
    CPU *intel1 = new intelCPU("2 Cores LGA1", "LGA1", 2, 3.0, 10, 10, 16, 30, 30, true, true);
    intel1->setObjectName("Intel 2 Cores LGA1 30$ Cooler");
    h->addCPU(intel1);
    CPU *intel2 = new intelCPU("2 Cores LGA2", "LGA2", 2, 3.0, 10, 10, 16, 30, 50, true, true);
    intel2->setObjectName("Intel 2 Cores LGA2 50$ Cooler");
    h->addCPU(intel2);
    // 6 Cores
    CPU *intel3 = new intelCPU("6 Cores LGA2", "LGA2", 6, 3.5, 10, 10, 16, 50, 100, true, true);
    intel3->setObjectName("Intel 6 Cores LGA2 100$ Cooler");
    h->addCPU(intel3);
    CPU *intel4 = new intelCPU("6 Cores LGA3", "LGA3", 6, 3.8, 15, 15, 20, 65, 140, true, false, 12, 4.3, true);
    intel4->setObjectName("Intel 6 Cores LGA3 140$ OC");
    h->addCPU(intel4);
    // 8 Cores
    CPU *intel5 = new intelCPU("8 Cores LGA2", "LGA2", 8, 3.5, 10, 10, 16, 50, 160, true, true);
    intel5->setObjectName("Intel 8 Cores LGA2 160$ Cooler");
    h->addCPU(intel5);
    CPU *intel6 = new intelCPU("8 Cores LGA3", "LGA3", 8, 4.2, 15, 15, 24, 65, 210, true, false, 16, 4.3, true);
    intel6->setObjectName("Intel 8 Cores LGA3 210$ OC");
    h->addCPU(intel6);
    // OC
    CPU *intel7 = new intelCPU("10 Cores LGA2", "LGA2", 10, 3.5, 10, 10, 16, 90, 300, true, false, 20, 4.5, true);
    intel7->setObjectName("Intel 10 Cores LGA2 300$ OC");
    h->addCPU(intel7);
    CPU *intel8 = new intelCPU("12 Cores LGA3", "LGA3", 12, 4.2, 15, 15, 24, 105, 350, true, false, 24, 4.7, true);
    intel8->setObjectName("Intel 12 Cores LGA3 350$ OC");
    h->addCPU(intel8);
    // Server
    CPU *intel9 = new intelCPU("16 Cores IN1", "IN1", 16, 3.5, 10, 10, 48, 155, 3000, true, false, 32, 4.5, true);
    intel9->setObjectName("Intel 16 Cores IN1 3000$ OC");
    h->addCPU(intel9);
    CPU *intel10 = new intelCPU("32 Cores IN1", "IN1", 32, 4.2, 15, 15, 72, 200, 3500, true, false, 64, 4.7, true);
    intel10->setObjectName("Intel 32 Cores IN1 3500$ OC");
    h->addCPU(intel10);

    /*
     * AMD CPUs
     *  amdCPU(QString model, QString socket, int cores, double base, int l2, int l3, int lanes, int tdp,
     *  int price, bool igpu = false, bool cooler = false, int threads = -1, double boost = -1)
    */
    // 2 Cores
    CPU *amd1 = new amdCPU("2 Cores AM1", "AM1", 2, 3, 10, 10, 16, 30, 20, false, true);
    amd1->setObjectName("AMD 2 Cores AM1 20$ Cooler OC");
    h->addCPU(amd1);
    CPU *amd2 = new amdCPU("2 Cores AM2", "AM2", 2, 3.2, 10, 10, 16, 30, 40, false, true);
    amd2->setObjectName("AMD 2 Cores AM2 40$ Cooler OC");
    h->addCPU(amd2);
    // 6 Cores
    CPU *amd3 = new amdCPU("6 Cores AM1", "AM1", 6, 3.3, 10, 10, 16, 30, 100, true, true, 12, 3.7);
    amd3->setObjectName("AMD 6 Cores AM1 APU 150$ Cooler OC");
    h->addCPU(amd3);
    CPU *amd4 = new amdCPU("6 Cores AM2", "AM2", 6, 3.5, 10, 10, 16, 30, 120, false, true, 12, 3.8);
    amd4->setObjectName("AMD 6 Cores AM2 120$ Cooler OC");
    h->addCPU(amd4);
    // 8 Cores
    CPU *amd5 = new amdCPU("8 Cores AM1", "AM1", 8, 3.3, 10, 10, 16, 60, 250, false, false, 16, 3.7);
    amd5->setObjectName("AMD 8 Cores AM1 250$ OC");
    h->addCPU(amd5);
    CPU *amd6 = new amdCPU("8 Cores AM2", "AM2", 8, 3.5, 10, 10, 16, 75, 300, false, false, 16, 4);
    amd6->setObjectName("AMD 8 Cores AM2 300$ OC");
    h->addCPU(amd6);
    // OC or X variants cause all AMD CPUs are set to unlocked
    CPU *amd7 = new amdCPU("8 Cores AM1", "AM1", 8, 4.1, 10, 10, 16, 120, 350, false, false, 16, 4.7);
    amd7->setObjectName("AMD 8 Cores AM1 350$ OC");
    h->addCPU(amd7);
    CPU *amd8 = new amdCPU("8 Cores AM2", "AM2", 8, 4.3, 10, 10, 16, 150, 400, false, false, 16, 4.8);
    amd8->setObjectName("AMD 8 Cores AM2 400$ OC");
    h->addCPU(amd8);
    // Server
    CPU *amd9 = new amdCPU("16 Cores EP1", "EP1", 16, 3.3, 10, 10, 72, 210, 2000, false, false, 32);
    amd9->setObjectName("AMD 16 Cores EP1 2000$ OC");
    h->addCPU(amd9);
    CPU *amd10 = new amdCPU("32 Cores EP2", "EP2", 32, 3.5, 10, 10, 108, 250, 3300, false, false, 64);
    amd10->setObjectName("AMD 32 Cores EP2 3300$ OC");
    h->addCPU(amd10);
}

void specBuilderTests::createGPUs(dataHolder *h)
{
    /*
     *
     *
    */
}

void specBuilderTests::createDB(dataHolder *h)
{
    createCPUs(h);
    createGPUs(h);
    createMobos(h);
    createRAM(h);
    createCoolers(h);
    createPSUs(h);
    createStorage(h);
    createCases(h);
}

void specBuilderTests::initialize(dataHolder *h)
{
    qDebug() << "Initializing database";
    backup(h);
    createDB(h);

}

void specBuilderTests::restore(dataHolder *h)
{
    qDebug() << "Restoring dataHolder";
    h->clearMaps();
    fileReader fr(h);
    fr.restore();
}

specBuilderTests::specBuilderTests(QString dir, QObject *parent)
    : m_testDir(dir),
      QObject{parent}
{}

void specBuilderTests::testMining(dataHolder *h)
{

}

void specBuilderTests::testServer(dataHolder *h)
{

}

void specBuilderTests::testOffice(dataHolder *h)
{

}

void specBuilderTests::testGaming(dataHolder *h)
{

}

void specBuilderTests::testOverclocking(dataHolder *h)
{

}

void specBuilderTests::testGeneral(dataHolder *h)
{

}

void specBuilderTests::runTests()
{
    dataHolder h("/home/nave/Documents/QtProjects/PCPartPicker/Test/");
    testMining(&h);
    testServer(&h);
    testOffice(&h);
    testGaming(&h);
    testOverclocking(&h);
    testGeneral(&h);
}
