#include "dbtests.h"

dbtests::dbtests(QString dir, QObject *parent)
    : m_testDir(dir),
      QObject{parent}
{

}

void dbtests::cpuTests(dataHolder *h)
{
    /*
     *  intelCPU(QString model, QString socket, int cores, double base, int l2, int l3, int lanes,
     *      int tdp, int price, bool igpu = true, bool cooler = false, int threads = -1,
     *      double boost = -1, bool unlocked = false)
     *
     * amdCPU(QString model, QString socket, int cores, double base, int l2, int l3, int lanes,
     *         int tdp, int price, bool igpu, bool cooler, int threads, double boost)
     *
     *         Tests should include:
     *         Insertion into:
     *         Intel+PC, Intel+Server, AMD+PC, AMD+Server, Odd cores (PC), Dual core (PC),
     *         Even cores from 4-16, Odd cores (Server)
     *
     *         Backup
     *         Restore
     *         Make sure everything's back where it's suppose to be
    */
    qDebug() << "Unit Testing CPU database";
    fileWriter fw(h);
    QMap<QString, QList<CPU*>> *cpus = h->CPUMap();
    foreach(QString key, cpus->keys())
        if (!cpus->value(key).isEmpty())
        {
            qWarning() << "CPU DB wasn't empty before testing, backing up and clearing";
            QFile backup(m_testDir + "/Backups/CPU.JSON");
            backup.open(QIODevice::WriteOnly);
            fw.cpuBackup(&backup);
            backup.close();
            break;
        }
    CPU *cpu1 = new intelCPU("4 Cores Intel", "LGA1150", 4, 3.4, 15, 10, 20, 90, 200, true, false, -1, 4.2, true);
    cpu1->setObjectName("Quad Core -> Intel, PC, 4 Cores");
    h->addCPU(cpu1);
    QVERIFY2(cpus->value("Intel").contains(cpu1), "Intel CPU wasn't inserted to intel list");
    QVERIFY2(!cpus->value("AMD").contains(cpu1), "Intel CPU was inserted to AMD list");
    QVERIFY2(cpus->value("PC").contains(cpu1), "<=16 Cores wasn't inserted to PC list");
    QVERIFY2(!cpus->value("Server").contains(cpu1), "<=16 Cores was inserted to Server list");
    QVERIFY2(cpus->value("4 Cores").contains(cpu1), "4 Core CPU wasn't inserted to 4 core list");

    CPU *cpu2 = new intelCPU("18 Core Intel", "LGA1151", 18, 3.8, 25, 15, 24, 90, 300, true, false, 36, 4.5, true);
    cpu2->setObjectName("18 Cores -> Intel, Server");
    h->addCPU(cpu2);
    QVERIFY2(cpus->value("Intel").contains(cpu2), "Intel CPU wasn't inserted to intel list");
    QVERIFY2(!cpus->value("AMD").contains(cpu2), "Intel CPU was inserted to AMD list");
    QVERIFY2(cpus->value("Server").contains(cpu2), ">16 Cores wasn't inserted to Server list");
    QVERIFY2(!cpus->value("PC").contains(cpu2), ">16 Cores inserted to PC list");

    CPU *cpu3 = new amdCPU("7 Cores AMD", "AM3+", 7, 3.4, 30, 15, 40, 150, 800, false, false, 7, 4.0);
    cpu3->setObjectName("7 Cores -> AMD, PC");
    h->addCPU(cpu3);
    QVERIFY2(cpus->value("AMD").contains(cpu3), "AMD CPU wasn't inserted to AMD list");
    QVERIFY2(!cpus->value("Intel").contains(cpu3), "AMD CPU was inserted to Intel list");
    QVERIFY2(!cpus->value("Server").contains(cpu3), "<=16 Cores was inserted to Server list");
    QVERIFY2(cpus->value("PC").contains(cpu3), "<=16 Cores wasn't inserted to PC list");

    CPU *cpu4 = new amdCPU("64 Cores AMD", "SP3", 64, 2.45, 512, 256, 128, 280, 4000, false, false, 128, 3.5);
    cpu4->setObjectName("64 Cores -> AMD, Server");
    h->addCPU(cpu4);
    QVERIFY2(cpus->value("AMD").contains(cpu4), "AMD CPU wasn't inserted to AMD list");
    QVERIFY2(!cpus->value("Intel").contains(cpu4), "AMD CPU was inserted to Intel list");
    QVERIFY2(cpus->value("Server").contains(cpu4), ">16 Cores wasn't inserted to Server list");
    QVERIFY2(!cpus->value("PC").contains(cpu4), ">16 Cores was inserted to PC list");

    CPU *cpu5 = new intelCPU("2 Cores Intel", "LGA1366", 2, 3.4, 15, 10, 20, 90, 200, true, false, -1);
    cpu5->setObjectName("2 Cores -> Intel, PC");
    h->addCPU(cpu5);
    QVERIFY2(cpus->value("Intel").contains(cpu5), "Intel CPU wasn't inserted to intel list");
    QVERIFY2(!cpus->value("AMD").contains(cpu5), "Intel CPU was inserted to AMD list");
    QVERIFY2(!cpus->value("Server").contains(cpu5), "<=16 Cores was inserted to Server list");
    QVERIFY2(cpus->value("PC").contains(cpu5), "<=16 Cores wasn't inserted to PC list");

    CPU *cpu6 = new intelCPU("6 Cores Intel", "t", 6, 3.2, 10, 10, 10, 10, 10);
    cpu6->setObjectName("6 Cores -> Intel, PC, 6 Cores"); // If reached here, only care about even core lists
    h->addCPU(cpu6);
    QVERIFY2(cpus->value("6 Cores").contains(cpu6), "6 Core CPU wasn't inserted into proper map");

    CPU *cpu7 = new intelCPU("8 Cores Intel", "t", 8, 3.2, 10, 10, 10, 10, 10);
    cpu6->setObjectName("8 Cores -> Intel, PC, 8 Cores"); // If reached here, only care about even core lists
    h->addCPU(cpu7);
    QVERIFY2(cpus->value("8 Cores").contains(cpu7), "8 Core CPU wasn't inserted into proper map");

    CPU *cpu8 = new intelCPU("10 Cores Intel", "t", 10, 3.2, 10, 10, 10, 10, 10);
    cpu6->setObjectName("10 Cores -> Intel, PC, 10 Cores"); // If reached here, only care about even core lists
    h->addCPU(cpu8);
    QVERIFY2(cpus->value("10 Cores").contains(cpu8), "10 Core CPU wasn't inserted into proper map");

    CPU *cpu9 = new intelCPU("12 Cores Intel", "t", 12, 3.2, 10, 10, 10, 10, 10);
    cpu6->setObjectName("12 Cores -> Intel, PC, 12 Cores"); // If reached here, only care about even core lists
    h->addCPU(cpu9);
    QVERIFY2(cpus->value("12 Cores").contains(cpu9), "12 Core CPU wasn't inserted into proper map");

    CPU *cpu10 = new intelCPU("14 Cores Intel", "t", 14, 3.2, 10, 10, 10, 10, 10);
    cpu6->setObjectName("14 Cores -> Intel, PC, 14 Cores"); // If reached here, only care about even core lists
    h->addCPU(cpu10);
    QVERIFY2(cpus->value("14 Cores").contains(cpu8), "14 Core CPU wasn't inserted into proper map");

    CPU *cpu11 = new intelCPU("16 Cores Intel", "t", 16, 3.2, 10, 10, 10, 10, 10);
    cpu6->setObjectName("16 Cores -> Intel, PC, 16 Cores"); // If reached here, only care about even core lists
    h->addCPU(cpu11);
    QVERIFY2(cpus->value("16 Cores").contains(cpu9), "16 Core CPU wasn't inserted into proper map");

    QFile db(m_testDir + "/Database/CPU.JSON");
    db.open(QIODevice::ReadWrite);
    fw.cpuBackup(&db);
    bool empty = true;
    foreach(QString key, cpus->keys())
    {
        empty = cpus->value(key).isEmpty();
        if (!empty)
        {
            qWarning() << key << " CPU Map wasn't completely backed up";
        }
    }
    QVERIFY2(empty, "One or more lists weren't backed up properly or weren't emptied");
    fileReader fr(h);
    fr.restoreCPUs(&db);
    db.close();

    qDebug() << "Verification after restoration";
    // CPU1 4 Cores, Intel, PC
    QVERIFY2(cpus->value("Intel").contains(cpu1), "Intel CPU wasn't inserted to intel list");
    QVERIFY2(!cpus->value("AMD").contains(cpu1), "Intel CPU was inserted to AMD list");
    QVERIFY2(cpus->value("PC").contains(cpu1), "<=16 Cores wasn't inserted to PC list");
    QVERIFY2(!cpus->value("Server").contains(cpu1), "<=16 Cores was inserted to Server list");
    QVERIFY2(cpus->value("4 Cores").contains(cpu1), "4 Core CPU wasn't inserted to 4 core list");
    // CPU2 Intel, Server
    QVERIFY2(cpus->value("Intel").contains(cpu2), "Intel CPU wasn't inserted to intel list");
    QVERIFY2(!cpus->value("AMD").contains(cpu2), "Intel CPU was inserted to AMD list");
    QVERIFY2(cpus->value("Server").contains(cpu2), ">16 Cores wasn't inserted to Server list");
    QVERIFY2(!cpus->value("PC").contains(cpu2), ">16 Cores inserted to PC list");
    // CPU3 AMD, PC
    QVERIFY2(cpus->value("AMD").contains(cpu3), "AMD CPU wasn't inserted to AMD list");
    QVERIFY2(!cpus->value("Intel").contains(cpu3), "AMD CPU was inserted to Intel list");
    QVERIFY2(!cpus->value("Server").contains(cpu3), "<=16 Cores was inserted to Server list");
    QVERIFY2(cpus->value("PC").contains(cpu3), "<=16 Cores wasn't inserted to PC list");
    // CPU4 AMD, Server
    QVERIFY2(cpus->value("AMD").contains(cpu4), "AMD CPU wasn't inserted to AMD list");
    QVERIFY2(!cpus->value("Intel").contains(cpu4), "AMD CPU was inserted to Intel list");
    QVERIFY2(cpus->value("Server").contains(cpu4), ">16 Cores wasn't inserted to Server list");
    QVERIFY2(!cpus->value("PC").contains(cpu4), ">16 Cores was inserted to PC list");
    // CPU5 Intel, PC
    QVERIFY2(cpus->value("Intel").contains(cpu5), "Intel CPU wasn't inserted to intel list");
    QVERIFY2(!cpus->value("AMD").contains(cpu5), "Intel CPU was inserted to AMD list");
    QVERIFY2(!cpus->value("Server").contains(cpu5), "<=16 Cores was inserted to Server list");
    QVERIFY2(cpus->value("PC").contains(cpu5), "<=16 Cores wasn't inserted to PC list");
    // CPU6 6 Cores
    QVERIFY2(cpus->value("6 Cores").contains(cpu6), "6 Core CPU wasn't inserted into proper map");
    // CPU7 8 Cores
    QVERIFY2(cpus->value("8 Cores").contains(cpu7), "8 Core CPU wasn't inserted into proper map");
    // CPU8 10 Cores
    QVERIFY2(cpus->value("10 Cores").contains(cpu8), "10 Core CPU wasn't inserted into proper map");
    // CPU9 12 Cores
    QVERIFY2(cpus->value("12 Cores").contains(cpu9), "12 Core CPU wasn't inserted into proper map");
    // CPU10 14 Cores
    QVERIFY2(cpus->value("14 Cores").contains(cpu8), "14 Core CPU wasn't inserted into proper map");
    // CPU11 16 Cores
    QVERIFY2(cpus->value("16 Cores").contains(cpu9), "16 Core CPU wasn't inserted into proper map");

    qInfo() << "End of CPU Unit Tests, passed successfully";
    // CPU is a QObject so will be deleted here
}

void dbtests::gpuTests(dataHolder *h)
{
    /*
     *  nvidiaGPU(QString model, int pcie, int vram, int base, int bus, int tdp,
     *      int pcieSlots, int height, int length, int price, QStringList inputs,
     *      int boost = -1, bool rays = false, bool dlss = true)
     *
     *  amdGPU(QString model, int pcie, int vram, int base, int bus, int tdp, int pcieSlots, int height,
     *      int length, int price, QStringList inputs, int boost = -1, bool rays = false)
     *
     *  intelGPU(QString model, int pcie, int vram, int base, int bus, int tdp, int pcieSlots,
     *      int height, int length, int price, QStringList inputs, int boost = -1)
     *
     *         Tests should include:
     *         Insertion into:
     *         Intel, AMD + RT, Nvidia + RT + DLSS
     *
     *         Backup
     *         Restore
     *         Make sure everything's back where it's suppose to be
    */

    qDebug() << "Unit Testing GPU database";
    fileWriter fw(h);
    QMap<QString, QList<GPU*>> *gpus = h->GPUMap();
    foreach(QString key, gpus->keys())
        if (!gpus->value(key).isEmpty())
        {
            qWarning() << "GPU DB wasn't empty before testing, backing up and clearing";
            QFile backup(m_testDir + "/Backups/GPU.JSON");
            backup.open(QIODevice::WriteOnly);
            fw.cpuBackup(&backup);
            backup.close();
            break;
        }
    GPU *gpu1 = new intelGPU("Intel GPU", 4, 8, 1800, 32, 40, 1, 3, 3, 43, {"HDMI"});
    gpu1->setObjectName("Intel GPU");
    h->addGPU(gpu1);
    QVERIFY2(gpus->value("Intel").contains(gpu1), "Intel list doesn't contain Intel gpu");
    QVERIFY2(!gpus->value("AMD").contains(gpu1), "AMD list contains Intel gpu");
    QVERIFY2(!gpus->value("Nvidia").contains(gpu1), "Nvidia list contains Intel gpu");
    QVERIFY2(!gpus->value("DLSS").contains(gpu1), "DLSS list contains Intel gpu");
    QVERIFY2(!gpus->value("Ray Tracing").contains(gpu1), "RT list contains Intel gpu");

    GPU *gpu2 = new amdGPU("AMD + RT", 4, 8, 1200, 64, 250, 2, 20, 28, 800, {"DisplayPort 2.1"}, 1450, true);
    gpu2->setObjectName("AMD GPU + RT");
    h->addGPU(gpu2);
    QVERIFY2(!gpus->value("Intel").contains(gpu2), "Intel list contains AMD gpu");
    QVERIFY2(gpus->value("AMD").contains(gpu2), "AMD list doesn't contain AMD gpu");
    QVERIFY2(!gpus->value("Nvidia").contains(gpu2), "Nvidia list contains AMD gpu");
    QVERIFY2(!gpus->value("DLSS").contains(gpu2), "DLSS list contains AMD gpu");
    QVERIFY2(gpus->value("Ray Tracing").contains(gpu2), "RT list doesn't contain RT capable gpu");

    GPU *gpu3 = new nvidiaGPU("Nvidia + RT + DLSS", 4, 16, 1950, 512, 350, 3, 21, 30, 1400, {"DVI-D"}, 2134, true);
    gpu3->setObjectName("Nvidia GPU + RT + DLSS");
    h->addGPU(gpu3);
    QVERIFY2(!gpus->value("Intel").contains(gpu3), "Intel list contains Nvidia gpu");
    QVERIFY2(!gpus->value("AMD").contains(gpu3), "AMD list contains Nvidia gpu");
    QVERIFY2(gpus->value("Nvidia").contains(gpu3), "Nvidia list doesn't contain Nvidia gpu");
    QVERIFY2(gpus->value("DLSS").contains(gpu3), "DLSS list doesn't contain DLSS capable gpu");
    QVERIFY2(gpus->value("Ray Tracing").contains(gpu3), "RT list doesn't contain RT capable gpu");

    QFile db(m_testDir + "/Database/GPU.JSON");
    db.open(QIODevice::ReadWrite);
    fw.cpuBackup(&db);
    bool empty = true;
    foreach(QString key, gpus->keys())
    {
        empty = gpus->value(key).isEmpty();
        if (!empty)
        {
            qWarning() << key << " GPU Map wasn't completely backed up";
        }
    }
    QVERIFY2(empty, "One or more lists weren't backed up properly or weren't emptied");
    fileReader fr(h);
    fr.restoreGPUs(&db);
    db.close();

    qDebug() << "Verification after restoration";
    // GPU1 Intel
    QVERIFY2(gpus->value("Intel").contains(gpu1), "Intel list doesn't contain Intel gpu");
    QVERIFY2(!gpus->value("AMD").contains(gpu1), "AMD list contains Intel gpu");
    QVERIFY2(!gpus->value("Nvidia").contains(gpu1), "Nvidia list contains Intel gpu");
    QVERIFY2(!gpus->value("DLSS").contains(gpu1), "DLSS list contains Intel gpu");
    QVERIFY2(!gpus->value("Ray Tracing").contains(gpu1), "RT list contains Intel gpu");
    // GPU2 AMD + RT
    QVERIFY2(!gpus->value("Intel").contains(gpu2), "Intel list contains AMD gpu");
    QVERIFY2(gpus->value("AMD").contains(gpu2), "AMD list doesn't contain AMD gpu");
    QVERIFY2(!gpus->value("Nvidia").contains(gpu2), "Nvidia list contains AMD gpu");
    QVERIFY2(!gpus->value("DLSS").contains(gpu2), "DLSS list contains AMD gpu");
    QVERIFY2(gpus->value("Ray Tracing").contains(gpu2), "RT list doesn't contain RT capable gpu");
    // GPU3 Nvidia + RT + DLSS
    QVERIFY2(!gpus->value("Intel").contains(gpu3), "Intel list contains Nvidia gpu");
    QVERIFY2(!gpus->value("AMD").contains(gpu3), "AMD list contains Nvidia gpu");
    QVERIFY2(gpus->value("Nvidia").contains(gpu3), "Nvidia list doesn't contain Nvidia gpu");
    QVERIFY2(gpus->value("DLSS").contains(gpu3), "DLSS list doesn't contain DLSS capable gpu");
    QVERIFY2(gpus->value("Ray Tracing").contains(gpu3), "RT list doesn't contain RT capable gpu");

    qInfo() << "End of GPU Unit Tests, passed successfully";
    // GPU is a QObject so will be deleted here
}

void dbtests::moboTests(dataHolder *h)
{
    motherboard *m1 = new motherboard("MSI Z590 Godlike", "Intel", "LGA1700", 4, "DDR5", 128, 2, 4, 8, 4, 8, "ATX", 20, 34, 8, {"HDMI", "USB C"}, {"Left","Right"}, 1200);
    motherboard *m2 = new motherboard("ASUS ROG Hero EXTREME 9", "AMD", "AM4", 4, "DDR4", 64, 2, 3, 6, 2, 8, "ATX", 15, 43, 6, {"HDMI"}, {"Optical"}, 1000, true, true);
    h->addMotherboard(m1);
    h->addMotherboard(m2);
}

void dbtests::ramTests(dataHolder *h)
{
    RAM *r1 = new RAM("GSkill TridentZ", "DDR4", 16, 2, 3600, {15, 15, 17, 34}, 250);
    RAM *r2 = new RAM("Corsair Vengeance", "DDR5", 32, 4, 5133, {34, 35, 34, 40}, 659);
    h->addRAM(r1);
    h->addRAM(r2);
}

void dbtests::storageTests(dataHolder *h)
{
    storage *s1 = new hdd("Seagate Barracuda", "SATA3", "2TB", 500, 400, 32, 60);
    storage *s2 = new sataSSD("Samsung 840 EVO", "1TB", 800, 650, 64, 110);
    storage *s3 = new m2SSD("Samsung 970 Pro", "512GB", 3500, 3200, 256, 350);
    h->addStorage(s1);
    h->addStorage(s2);
    h->addStorage(s3);
}

void dbtests::coolerTests(dataHolder *h)
{
    cooler *c1 = new airCooler("Noctua NH-D15", 250, 2, 2, 168, {"LGA1150", "LGA1151", "LGA1700", "AM4"}, 150);
    cooler *c2 = new AIO("Fractal Design Something", 200, 2, 4, 240, 5, {"LGA1150", "LGA1151", "LGA1700", "TR4"}, 300);
    h->addCooler(c1);
    h->addCooler(c2);
}

void dbtests::caseTests(dataHolder *h)
{
    bool empty = true;
    QMap<QString, QList<pcCase*>> *cases = h->CASEMap();
    foreach(QString key, cases->keys())
        if (!cases->value(key).isEmpty())
        {
            empty = false;
            break;
        }
    QVERIFY2(empty, "Case map isn't empty before tests");
    pcCase *case1 = new pcCase("Fractal Design Define R7", "Mid Tower", {"ATX", "mATX", "ITX"}, 34, 17, 8, 3, 7, 2, 4, 60, 32, 58, 150, true, true);
    pcCase *case2 = new pcCase("Lian Li PC-O11", "Full Tower", {"E-ATX", "ATX", "mATX", "ITX"}, 41, 22, 8, 5, 7, 2, 2, 60, 32, 58, 250, true, true);
    h->addCase(case1);
    h->addCase(case2);
    QVERIFY2(cases->value("Price").size() == 2, "Case insertion failed");
    fileWriter fw(h);
    fw.backup();
    foreach(QString key, cases->keys())
        if (!cases->value(key).isEmpty())
        {
            empty = false;
            break;
        }
    QVERIFY2(empty, "Case map isn't empty after backup");
    fileReader fr(h);
    if (!fr.restore())
        qWarning() << "Failed to restore";
    QVERIFY2(cases->value("Price").size() == 2, "Case restoration failed");
}

void dbtests::runTests()
{
    dataHolder h("/home/nave/Documents/QtProjects/build-PCPartPicker-Desktop_Qt_6_0_4_GCC_64bit-Debug/Unit-Tests/");
}
