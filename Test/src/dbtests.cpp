#include "../include/dbtests.h"

dbtests::dbtests(QString dir, QObject *parent)
    : m_testDir(dir),
      QObject{parent}
{}

void dbtests::cpuTests(dataHolder *h)
{
    /*
     *  intelCPU(QString model, QString socket, int cores, double base, int l2, int l3, int lanes,
     *      int tdp, int price, bool igpu = true, bool cooler = false, int threads = -1,
     *      double boost = -1, bool unlocked = false)
     *
     *  amdCPU(QString model, QString socket, int cores, double base, int l2, int l3, int lanes, int tdp,
     *      int price, bool igpu = false, bool cooler = false, int threads = -1, double boost = -1)
     *
     *  cpuMap["Intel"]
     *  cpuMap["AMD"]
     *  cpuMap["4 Cores"]
     *  cpuMap["6 Cores"]
     *  cpuMap["8 Cores"]
     *  cpuMap["10 Cores"]
     *  cpuMap["12 Cores"]
     *  cpuMap["14 Cores"]
     *  cpuMap["16 Cores"]
     *  cpuMap["Server"]
     *  cpuMap["PC"]
     *
     *         Tests should include:
     *         Insertion into:
     *         Intel+PC, Intel+Server, AMD+PC, AMD+Server, Odd cores (PC), Dual core (PC),
     *         Even cores from 4-16, Odd cores (Server)
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
     *  gpuMap["Intel"]
     *  gpuMap["AMD"]
     *  gpuMap["Nvidia"]
     *  gpuMap["Ray Tracing"]
     *  gpuMap["DLSS"]
     *
     *         Tests should include:
     *         Insertion into:
     *         Intel, AMD + RT, Nvidia + RT + DLSS
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
    fw.gpuBackup(&db);
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
    /*
     *  motherboard(QString model, QString cpu, QString socket, int ram, QString ramV, int maxram, int chs, int pcie,
     *      int sata, int m2, int fan, QString ff, int l, int w, int usb, QStringList vid, QStringList aud,
     *      int price, bool eth = true, bool wifi = false)
     *
     *  moboMap["Intel"]
     *  moboMap["AMD"]
     *  moboMap["DDR3"]
     *  moboMap["DDR4"]
     *  moboMap["DDR5"]
     *  moboMap["Server"]
     *  moboMap["Mining"]
     *  moboMap["Overclocking"]
     *  moboMap["Price"]
     *
     *         Tests should include:
     *         Insertion into:
     *         Intel, AMD, DDR3->5, Purpose of server, mining, overclocking
     *         Backup
     *         Restore
     *         Make sure everything's back where it's suppose to be
    */

    qDebug() << "Unit Testing Motherboard database";
    fileWriter fw(h);
    QMap<QString, QList<motherboard*>> *mobos = h->MOBOMap();
    foreach(QString key, mobos->keys())
        if (!mobos->value(key).isEmpty())
        {
            qWarning() << "Motherboard DB wasn't empty before testing, backing up and clearing";
            QFile backup(m_testDir + "/Backups/Motherboard.JSON");
            backup.open(QIODevice::WriteOnly);
            fw.moboBackup(&backup);
            backup.close();
            break;
        }
    motherboard *m1 = new motherboard("Intel Server DDR5", "Intel", "LGA1700", 4, "DDR5", 128, 2, 4, 8, 4, 8, "ATX", 20, 34, 8, {"HDMI", "USB C"}, {"Left","Right"}, 1200);
    m1->setObjectName("Intel, Server, DDR5");
    h->addMotherboard(m1, "SeRvEr");
    QVERIFY2(mobos->value("Intel").contains(m1), "Intel list doesn't contain Intel motherboard");
    QVERIFY2(!mobos->value("AMD").contains(m1), "AMD list contains Intel motherboard");
    QVERIFY2(!mobos->value("Mining").contains(m1), "Mining list contains non mining motherboard");
    QVERIFY2(!mobos->value("Overclocking").contains(m1), "Overclocking list contains non overclocking motherboard");
    QVERIFY2(mobos->value("Server").contains(m1), "Server list doesn't contain server motherboard");
    QVERIFY2(mobos->value("DDR5").contains(m1), "DDR5 list doesn't contain DDR5 motherboard");
    QVERIFY2(!mobos->value("DDR4").contains(m1), "DDR4 list contains DDR5 motherboard");
    QVERIFY2(!mobos->value("DDR3").contains(m1), "DDR3 list contains DDR5 motherboard");

    motherboard *m2 = new motherboard("AMD OC DDR4", "AMD", "AM4", 4, "DDR4", 64, 2, 3, 6, 2, 8, "ATX", 15, 43, 6, {"HDMI"}, {"Optical"}, 1000, true, true);
    m2->setObjectName("AMD, Overclocking, DDR4");
    h->addMotherboard(m2, "OvercCLoCKIng");
    QVERIFY2(!mobos->value("Intel").contains(m2), "Intel list contains AMD motherboard");
    QVERIFY2(mobos->value("AMD").contains(m2), "AMD list doesn't contain AMD motherboard");
    QVERIFY2(!mobos->value("Mining").contains(m2), "Mining list contains non mining motherboard");
    QVERIFY2(mobos->value("Overclocking").contains(m2), "Overclocking list doesn't contain overclocking motherboard");
    QVERIFY2(!mobos->value("Server").contains(m2), "Server list contains non server motherboard");
    QVERIFY2(!mobos->value("DDR5").contains(m2), "DDR5 list contains DDR4 motherboard");
    QVERIFY2(mobos->value("DDR4").contains(m2), "DDR4 list doesn't contain DDR4 motherboard");
    QVERIFY2(!mobos->value("DDR3").contains(m2), "DDR3 list contains DDR4 motherboard");

    motherboard *m3 = new motherboard("Intel Mining DDR3", "Intel", "LGA1151", 2, "DDR3", 64, 2, 12, 2, 0, 4, "ATX", 20, 34, 4, {}, {}, 400);
    m3->setObjectName("Intel, Mining, DDR3");
    h->addMotherboard(m3, "Mining");
    QVERIFY2(mobos->value("Intel").contains(m3), "Intel list doesn't contain Intel motherboard");
    QVERIFY2(!mobos->value("AMD").contains(m3), "AMD list contains Intel motherboard");
    QVERIFY2(mobos->value("Mining").contains(m3), "Mining list doesn't contain mining motherboard");
    QVERIFY2(!mobos->value("Overclocking").contains(m3), "Overclocking list contains non overclocking motherboard");
    QVERIFY2(!mobos->value("Server").contains(m3), "Server list contains non server motherboard");
    QVERIFY2(!mobos->value("DDR5").contains(m3), "DDR5 list contains DDR3 motherboard");
    QVERIFY2(!mobos->value("DDR4").contains(m3), "DDR4 list contains DDR3 motherboard");
    QVERIFY2(mobos->value("DDR3").contains(m3), "DDR3 list doesn't contain DDR3 motherboard");

    motherboard *m4 = new motherboard("Intel DDR3", "Intel", "LGA1151", 2, "DDR3", 64, 2, 12, 2, 0, 4, "ATX", 20, 34, 4, {}, {}, 400);
    m4->setObjectName("Intel, DDR3");
    h->addMotherboard(m4);
    QVERIFY2(mobos->value("Intel").contains(m4), "Intel list doesn't contain Intel motherboard");
    QVERIFY2(!mobos->value("AMD").contains(m4), "AMD list contains Intel motherboard");
    QVERIFY2(!mobos->value("Mining").contains(m4), "Mining list contains non mining motherboard");
    QVERIFY2(!mobos->value("Overclocking").contains(m4), "Overclocking list contains non overclocking motherboard");
    QVERIFY2(!mobos->value("Server").contains(m4), "Server list contains non server motherboard");
    QVERIFY2(!mobos->value("DDR5").contains(m4), "DDR5 list contains DDR3 motherboard");
    QVERIFY2(!mobos->value("DDR4").contains(m4), "DDR4 list contains DDR3 motherboard");
    QVERIFY2(mobos->value("DDR3").contains(m4), "DDR3 list doesn't contain DDR3 motherboard");

    QFile db(m_testDir + "/Database/Motherboard.JSON");
    db.open(QIODevice::ReadWrite);
    fw.moboBackup(&db);
    bool empty = true;
    foreach(QString key, mobos->keys())
    {
        empty = mobos->value(key).isEmpty();
        if (!empty)
        {
            qWarning() << key << " Motherboard Map wasn't completely backed up";
        }
    }
    QVERIFY2(empty, "One or more lists weren't backed up properly or weren't emptied");
    fileReader fr(h);
    fr.restoreMotherboards(&db);
    db.close();

    qDebug() << "Verification after restoration";
    // Mobo1 Intel, Server, DDR5
    QVERIFY2(mobos->value("Intel").contains(m1), "Intel list doesn't contain Intel motherboard");
    QVERIFY2(!mobos->value("AMD").contains(m1), "AMD list contains Intel motherboard");
    QVERIFY2(!mobos->value("Mining").contains(m1), "Mining list contains non mining motherboard");
    QVERIFY2(!mobos->value("Overclocking").contains(m1), "Overclocking list contains non overclocking motherboard");
    QVERIFY2(mobos->value("Server").contains(m1), "Server list doesn't contain server motherboard");
    QVERIFY2(mobos->value("DDR5").contains(m1), "DDR5 list doesn't contain DDR5 motherboard");
    QVERIFY2(!mobos->value("DDR4").contains(m1), "DDR4 list contains DDR5 motherboard");
    QVERIFY2(!mobos->value("DDR3").contains(m1), "DDR3 list contains DDR5 motherboard");
    // Mobo2 AMD, OC, DDR4
    QVERIFY2(!mobos->value("Intel").contains(m2), "Intel list contains AMD motherboard");
    QVERIFY2(mobos->value("AMD").contains(m2), "AMD list doesn't contain AMD motherboard");
    QVERIFY2(!mobos->value("Mining").contains(m2), "Mining list contains non mining motherboard");
    QVERIFY2(mobos->value("Overclocking").contains(m2), "Overclocking list doesn't contain overclocking motherboard");
    QVERIFY2(!mobos->value("Server").contains(m2), "Server list contains non server motherboard");
    QVERIFY2(!mobos->value("DDR5").contains(m2), "DDR5 list contains DDR4 motherboard");
    QVERIFY2(mobos->value("DDR4").contains(m2), "DDR4 list doesn't contain DDR4 motherboard");
    QVERIFY2(!mobos->value("DDR3").contains(m2), "DDR3 list contains DDR4 motherboard");
    // Mobo3 Intel, Mining, DDR3
    QVERIFY2(mobos->value("Intel").contains(m3), "Intel list doesn't contain Intel motherboard");
    QVERIFY2(!mobos->value("AMD").contains(m3), "AMD list contains Intel motherboard");
    QVERIFY2(mobos->value("Mining").contains(m3), "Mining list doesn't contain mining motherboard");
    QVERIFY2(!mobos->value("Overclocking").contains(m3), "Overclocking list contains non overclocking motherboard");
    QVERIFY2(!mobos->value("Server").contains(m3), "Server list contains non server motherboard");
    QVERIFY2(!mobos->value("DDR5").contains(m3), "DDR5 list contains DDR3 motherboard");
    QVERIFY2(!mobos->value("DDR4").contains(m3), "DDR4 list contains DDR3 motherboard");
    QVERIFY2(mobos->value("DDR3").contains(m3), "DDR3 list doesn't contain DDR3 motherboard");
    // Mobo4 Intel, DDR3
    QVERIFY2(mobos->value("Intel").contains(m4), "Intel list doesn't contain Intel motherboard");
    QVERIFY2(!mobos->value("AMD").contains(m4), "AMD list contains Intel motherboard");
    QVERIFY2(!mobos->value("Mining").contains(m4), "Mining list contains non mining motherboard");
    QVERIFY2(!mobos->value("Overclocking").contains(m4), "Overclocking list contains non overclocking motherboard");
    QVERIFY2(!mobos->value("Server").contains(m4), "Server list contains non server motherboard");
    QVERIFY2(!mobos->value("DDR5").contains(m4), "DDR5 list contains DDR3 motherboard");
    QVERIFY2(!mobos->value("DDR4").contains(m4), "DDR4 list contains DDR3 motherboard");
    QVERIFY2(mobos->value("DDR3").contains(m4), "DDR3 list doesn't contain DDR3 motherboard");

    qInfo() << "End of Motherboard Unit Tests, passed successfully";
    // motherboard is a QObject so will be deleted here
}

void dbtests::ramTests(dataHolder *h)
{
    /*
     *  RAM(QString model, QString version, int size, int dimms, int speed,
     *      QList<int> timing, int price, bool hs = true)
     *
     *  ramMap["DDR3"]
     *  ramMap["DDR4"]
     *  ramMap["DDR5"]
     *
     *         Tests should include:
     *         Insertion into:
     *         DDR3->5
     *         Backup
     *         Restore
     *         Make sure everything's back where it's suppose to be
    */

    qDebug() << "Unit Testing RAM database";
    fileWriter fw(h);
    QMap<QString, QList<RAM*>> *rams = h->RAMMap();
    foreach(QString key, rams->keys())
        if (!rams->value(key).isEmpty())
        {
            qWarning() << "RAM DB wasn't empty before testing, backing up and clearing";
            QFile backup(m_testDir + "/Backups/RAM.JSON");
            backup.open(QIODevice::WriteOnly);
            fw.ramBackup(&backup);
            backup.close();
            break;
        }
    RAM *r1 = new RAM("Corsair Vengeance", "DDR5", 32, 4, 5133, {34, 35, 34, 40}, 659);
    r1->setObjectName("DDR5");
    h->addRAM(r1);
    QVERIFY2(rams->value("DDR5").contains(r1), "DDR5 list doesn't contain DDR5 RAM");
    QVERIFY2(!rams->value("DDR4").contains(r1), "DDR4 list contains DDR5 RAM");
    QVERIFY2(!rams->value("DDR3").contains(r1), "DDR3 list contains DDR5 RAM");

    RAM *r2 = new RAM("DDR4", "DDR4", 16, 2, 3600, {15, 15, 17, 34}, 250);
    r2->setObjectName("DDR4");
    h->addRAM(r2);
    QVERIFY2(!rams->value("DDR5").contains(r2), "DDR5 list contains DDR4 RAM");
    QVERIFY2(rams->value("DDR4").contains(r2), "DDR4 list doesn't contain DDR4 RAM");
    QVERIFY2(!rams->value("DDR3").contains(r2), "DDR3 list contains DDR4 RAM");

    RAM *r3 = new RAM("DDR3", "DDR3", 16, 2, 2400, {9,8,8,15}, 100);
    r3->setObjectName("DDR3");
    h->addRAM(r3);
    QVERIFY2(!rams->value("DDR5").contains(r3), "DDR5 list contains DDR3 RAM");
    QVERIFY2(!rams->value("DDR4").contains(r3), "DDR4 list contains DDR3 RAM");
    QVERIFY2(rams->value("DDR3").contains(r3), "DDR3 list doesn't contain DDR3 RAM");

    QFile db(m_testDir + "/Database/RAM.JSON");
    db.open(QIODevice::ReadWrite);
    fw.ramBackup(&db);
    bool empty = true;
    foreach(QString key, rams->keys())
    {
        empty = rams->value(key).isEmpty();
        if (!empty)
        {
            qWarning() << key << " RAM Map wasn't completely backed up";
        }
    }
    QVERIFY2(empty, "One or more lists weren't backed up properly or weren't emptied");
    fileReader fr(h);
    fr.restoreRAM(&db);
    db.close();

    qDebug() << "Verification after restoration";
    // DDR5
    QVERIFY2(rams->value("DDR5").contains(r1), "DDR5 list doesn't contain DDR5 RAM");
    QVERIFY2(!rams->value("DDR4").contains(r1), "DDR4 list contains DDR5 RAM");
    QVERIFY2(!rams->value("DDR3").contains(r1), "DDR3 list contains DDR5 RAM");
    // DDR4
    QVERIFY2(!rams->value("DDR5").contains(r2), "DDR5 list contains DDR4 RAM");
    QVERIFY2(rams->value("DDR4").contains(r2), "DDR4 list doesn't contain DDR4 RAM");
    QVERIFY2(!rams->value("DDR3").contains(r2), "DDR3 list contains DDR4 RAM");
    // DDR3
    QVERIFY2(!rams->value("DDR5").contains(r3), "DDR5 list contains DDR3 RAM");
    QVERIFY2(!rams->value("DDR4").contains(r3), "DDR4 list contains DDR3 RAM");
    QVERIFY2(rams->value("DDR3").contains(r3), "DDR3 list doesn't contain DDR3 RAM");

    qInfo() << "End of RAM Unit Tests, passed successfully";
    // RAM is a QObject so will be deleted here
}

void dbtests::storageTests(dataHolder *h)
{
    /*
     *  hdd(QString model, QString port, QString size, int read, int write, int cache, int price)
     *  m2SSD(QString model, QString size, int read, int write, int cache, int price)
     *  sataSSD(QString model, QString size, int read, int write, int cache, int price)
     *
     *  storageMap["HDD"]
     *  storageMap["M.2"]
     *  storageMap["SSD"]
     *  storageMap["Size"]
     *
     *         Tests should include:
     *         Insertion into:
     *         HDD, M.2, SSD, make sure all in size map
     *         Backup
     *         Restore
     *         Make sure everything's back where it's suppose to be
    */

    qDebug() << "Unit Testing storage database";
    fileWriter fw(h);
    QMap<QString, QList<storage*>> *drives = h->STORAGEMap();
    foreach(QString key, drives->keys())
        if (!drives->value(key).isEmpty())
        {
            qWarning() << "Storage DB wasn't empty before testing, backing up and clearing";
            QFile backup(m_testDir + "/Backups/Storage.JSON");
            backup.open(QIODevice::WriteOnly);
            fw.storageBackup(&backup);
            backup.close();
            break;
        }
    storage *s1 = new hdd("Seagate Barracuda", "SATA3", "2TB", 500, 400, 32, 60);
    s1->setObjectName("HDD");
    h->addStorage(s1);
    QVERIFY2(drives->value("HDD").contains(s1), "HDD list doesn't contain HDD");
    QVERIFY2(!drives->value("SSD").contains(s1), "SSD list contains HDD");
    QVERIFY2(!drives->value("M.2").contains(s1), "M.2 list contains HDD");
    QVERIFY2(drives->value("Size").contains(s1), "Size list doesn't contain HDD");

    storage *s2 = new sataSSD("Samsung 840 EVO", "1TB", 800, 650, 64, 110);
    s2->setObjectName("SATA SSD");
    h->addStorage(s2);
    QVERIFY2(!drives->value("HDD").contains(s2), "HDD list contains SATA SSD");
    QVERIFY2(drives->value("SSD").contains(s2), "SSD list doesn't contain SATA SSD");
    QVERIFY2(!drives->value("M.2").contains(s2), "M.2 list contains SATA SSD");
    QVERIFY2(drives->value("Size").contains(s2), "Size list doesn't contain SATA SSD");

    storage *s3 = new m2SSD("Samsung 970 Pro", "512GB", 3500, 3200, 256, 350);
    s3->setObjectName("M.2");
    h->addStorage(s3);
    QVERIFY2(!drives->value("HDD").contains(s3), "HDD list contains M.2");
    QVERIFY2(!drives->value("SSD").contains(s3), "SSD list contains M.2");
    QVERIFY2(drives->value("M.2").contains(s3), "M.2 list doesn't contain M.2");
    QVERIFY2(drives->value("Size").contains(s3), "Size list doesn't contain M.2");

    QFile db(m_testDir + "/Database/Storage.JSON");
    db.open(QIODevice::ReadWrite);
    fw.storageBackup(&db);
    bool empty = true;
    foreach(QString key, drives->keys())
    {
        empty = drives->value(key).isEmpty();
        if (!empty)
        {
            qWarning() << key << " Storage Map wasn't completely backed up";
        }
    }
    QVERIFY2(empty, "One or more lists weren't backed up properly or weren't emptied");
    fileReader fr(h);
    fr.restoreStorage(&db);
    db.close();

    qDebug() << "Verification after restoration";
    // HDD
    QVERIFY2(drives->value("HDD").contains(s1), "HDD list doesn't contain HDD");
    QVERIFY2(!drives->value("SSD").contains(s1), "SSD list contains HDD");
    QVERIFY2(!drives->value("M.2").contains(s1), "M.2 list contains HDD");
    QVERIFY2(drives->value("Size").contains(s1), "Size list doesn't contain HDD");
    // Sata SSD
    QVERIFY2(!drives->value("HDD").contains(s2), "HDD list contains SATA SSD");
    QVERIFY2(drives->value("SSD").contains(s2), "SSD list doesn't contain SATA SSD");
    QVERIFY2(!drives->value("M.2").contains(s2), "M.2 list contains SATA SSD");
    QVERIFY2(drives->value("Size").contains(s2), "Size list doesn't contain SATA SSD");
    // M.2
    QVERIFY2(!drives->value("HDD").contains(s3), "HDD list contains M.2");
    QVERIFY2(!drives->value("SSD").contains(s3), "SSD list contains M.2");
    QVERIFY2(drives->value("M.2").contains(s3), "M.2 list doesn't contain M.2");
    QVERIFY2(drives->value("Size").contains(s3), "Size list doesn't contain M.2");

    qInfo() << "End of Storage Unit Tests, passed successfully";
    // storage is a QObject so will be deleted here
}

void dbtests::coolerTests(dataHolder *h)
{
    /*
     *  AIO(QString model, int tdp, int fans, int maxFans, int rads, int h, QStringList sockets, int price)
     *  airCooler(QString model, int tdp, int fans, int maxFans, int h, QStringList sockets, int price)
     *
     *  coolerMap["AIO"]
     *  coolerMap["Air"]
     *  coolerMap["TDP"]
     *
     *         Tests should include:
     *         Insertion into:
     *         AIO, Air, make sure all in tdp map
     *         Backup
     *         Restore
     *         Make sure everything's back where it's suppose to be
    */

    qDebug() << "Unit Testing Cooler database";
    fileWriter fw(h);
    QMap<QString, QList<cooler*>> *coolers = h->COOLERMap();
    foreach(QString key, coolers->keys())
        if (!coolers->value(key).isEmpty())
        {
            qWarning() << "Cooler DB wasn't empty before testing, backing up and clearing";
            QFile backup(m_testDir + "/Backups/Cooler.JSON");
            backup.open(QIODevice::WriteOnly);
            fw.coolerBackup(&backup);
            backup.close();
            break;
        }

    cooler *c1 = new airCooler("Air Cooler", 250, 2, 2, 168, {"LGA1150", "LGA1151", "LGA1700", "AM4"}, 150);
    c1->setObjectName("Air cooler");
    h->addCooler(c1);
    QVERIFY2(coolers->value("Air").contains(c1), "Air Cooler list doesn't contain Air Cooler");
    QVERIFY2(!coolers->value("AIO").contains(c1), "AIO list contains Air Cooler");
    QVERIFY2(coolers->value("TDP").contains(c1), "TDP list doesn't contain Air Cooler");

    cooler *c2 = new AIO("AIO", 200, 2, 4, 240, 5, {"LGA1150", "LGA1151", "LGA1700", "TR4"}, 300);
    c2->setObjectName("AIO");
    h->addCooler(c2);
    QVERIFY2(!coolers->value("Air").contains(c2), "Air Cooler list contains AIO");
    QVERIFY2(coolers->value("AIO").contains(c2), "AIO list doesn't contain AIO");
    QVERIFY2(coolers->value("TDP").contains(c2), "TDP list doesn't contain AIO");

    QFile db(m_testDir + "/Database/Cooler.JSON");
    db.open(QIODevice::ReadWrite);
    fw.coolerBackup(&db);
    bool empty = true;
    foreach(QString key, coolers->keys())
    {
        empty = coolers->value(key).isEmpty();
        if (!empty)
        {
            qWarning() << key << " Cooler Map wasn't completely backed up";
        }
    }
    QVERIFY2(empty, "One or more lists weren't backed up properly or weren't emptied");
    fileReader fr(h);
    fr.restoreCoolers(&db);
    db.close();

    qDebug() << "Verification after restoration";
    // Air Cooler
    QVERIFY2(coolers->value("Air").contains(c1), "Air Cooler list doesn't contain Air Cooler");
    QVERIFY2(!coolers->value("AIO").contains(c1), "AIO list contains Air Cooler");
    QVERIFY2(coolers->value("TDP").contains(c1), "TDP list doesn't contain Air Cooler");
    // AIO
    QVERIFY2(!coolers->value("Air").contains(c2), "Air Cooler list contains AIO");
    QVERIFY2(coolers->value("AIO").contains(c2), "AIO list doesn't contain AIO");
    QVERIFY2(coolers->value("TDP").contains(c2), "TDP list doesn't contain AIO");

    qInfo() << "End of Cooler Unit Tests, passed successfully";
    // cooler is a QObject so will be deleted here
}

void dbtests::psuTests(dataHolder *h)
{
    /*
     * PSU(QString model, QString modularity, QString ff, Efficiency efficiency, int wattage,
     * int price, bool fan = true)
     *
     *  psuMap["Low W"]
     *  psuMap["Mid W"]
     *  psuMap["High W"]
     *  psuMap["SFF"]
     *  psuMap["ATX"]
     *  psuMap["Server"]
     *  psuMap["Price"]
     *
     *         Tests should include:
     *         Insertion into:
     *         Wattage based lists, form factor based lists
     *         Backup
     *         Restore
     *         Make sure everything's back where it's suppose to be
    */

    qDebug() << "Unit Testing PSU database";
    fileWriter fw(h);
    QMap<QString, QList<PSU*>> *psus = h->PSUMap();
    foreach(QString key, psus->keys())
        if (!psus->value(key).isEmpty())
        {
            qWarning() << "PSU DB wasn't empty before testing, backing up and clearing";
            QFile backup(m_testDir + "/Backups/PSU.JSON");
            backup.open(QIODevice::WriteOnly);
            fw.caseBackup(&backup);
            backup.close();
            break;
        }

    PSU *psu1 = new PSU("SFF 500W", "Modular", "SFF", Efficiency::Platinum, 500, 60);
    psu1->setObjectName("500W, SFF");
    h->addPSU(psu1);
    QVERIFY2(psus->value("Low W").contains(psu1), "Low W map doesn't contain Low W PSU");
    QVERIFY2(!psus->value("Mid W").contains(psu1), "Mid W map contains Low W PSU");
    QVERIFY2(!psus->value("High W").contains(psu1), "High W map contains Low W PSU");
    QVERIFY2(psus->value("SFF").contains(psu1), "SFF map doesn't contain SFF PSU");
    QVERIFY2(!psus->value("ATX").contains(psu1), "ATX map contains SFF PSU");
    QVERIFY2(!psus->value("Server").contains(psu1), "Server map contains SFF PSU");

    PSU *psu2 = new PSU("ATX 700W", "Modular", "ATX", Efficiency::Platinum, 700, 60);
    psu2->setObjectName("700W, ATX");
    h->addPSU(psu2);
    QVERIFY2(!psus->value("Low W").contains(psu2), "Low W map contains Mid W PSU");
    QVERIFY2(psus->value("Mid W").contains(psu2), "Mid W map doesn't contain Mid W PSU");
    QVERIFY2(!psus->value("High W").contains(psu2), "High W map contains Mid W PSU");
    QVERIFY2(!psus->value("SFF").contains(psu2), "SFF map contains ATX PSU");
    QVERIFY2(psus->value("ATX").contains(psu2), "ATX map doesn't contain ATX PSU");
    QVERIFY2(!psus->value("Server").contains(psu2), "Server map contains ATX PSU");

    PSU *psu3 = new PSU("Server 1200W", "Not Modular", "Server", Efficiency::Silver, 1200, 506);
    psu3->setObjectName("1200W, Server");
    h->addPSU(psu3);
    QVERIFY2(!psus->value("Low W").contains(psu3), "Low W map contains High W PSU");
    QVERIFY2(!psus->value("Mid W").contains(psu3), "Mid W map contains High W PSU");
    QVERIFY2(psus->value("High W").contains(psu3), "High W map doesn't contain Low W PSU");
    QVERIFY2(!psus->value("SFF").contains(psu3), "SFF map contains Server PSU");
    QVERIFY2(!psus->value("ATX").contains(psu3), "ATX map contains Server PSU");
    QVERIFY2(psus->value("Server").contains(psu3), "Server map doesn't contain Server PSU");

    QFile db(m_testDir + "/Database/PSU.JSON");
    db.open(QIODevice::ReadWrite);
    fw.psuBackup(&db);
    bool empty = true;
    foreach(QString key, psus->keys())
    {
        empty = psus->value(key).isEmpty();
        if (!empty)
        {
            qWarning() << key << " PSU Map wasn't completely backed up";
        }
    }
    QVERIFY2(empty, "One or more lists weren't backed up properly or weren't emptied");
    fileReader fr(h);
    fr.restorePSUs(&db);
    db.close();

    qDebug() << "Verification after restoration";
    // Low W SFF PSU
    QVERIFY2(psus->value("Low W").contains(psu1), "Low W map doesn't contain Low W PSU");
    QVERIFY2(!psus->value("Mid W").contains(psu1), "Mid W map contains Low W PSU");
    QVERIFY2(!psus->value("High W").contains(psu1), "High W map contains Low W PSU");
    QVERIFY2(psus->value("SFF").contains(psu1), "SFF map doesn't contain SFF PSU");
    QVERIFY2(!psus->value("ATX").contains(psu1), "ATX map contains SFF PSU");
    QVERIFY2(!psus->value("Server").contains(psu1), "Server map contains SFF PSU");
    // Mid W ATX PSU
    QVERIFY2(!psus->value("Low W").contains(psu2), "Low W map contains Mid W PSU");
    QVERIFY2(psus->value("Mid W").contains(psu2), "Mid W map doesn't contain Mid W PSU");
    QVERIFY2(!psus->value("High W").contains(psu2), "High W map contains Mid W PSU");
    QVERIFY2(!psus->value("SFF").contains(psu2), "SFF map contains ATX PSU");
    QVERIFY2(psus->value("ATX").contains(psu2), "ATX map doesn't contain ATX PSU");
    QVERIFY2(!psus->value("Server").contains(psu2), "Server map contains ATX PSU");
    // High W Server PSU
    QVERIFY2(!psus->value("Low W").contains(psu3), "Low W map contains High W PSU");
    QVERIFY2(!psus->value("Mid W").contains(psu3), "Mid W map contains High W PSU");
    QVERIFY2(psus->value("High W").contains(psu3), "High W map doesn't contain Low W PSU");
    QVERIFY2(!psus->value("SFF").contains(psu3), "SFF map contains Server PSU");
    QVERIFY2(!psus->value("ATX").contains(psu3), "ATX map contains Server PSU");
    QVERIFY2(psus->value("Server").contains(psu3), "Server map doesn't contain Server PSU");

    qInfo() << "End of PSU Unit Tests, passed successfully";
    // PSU is a QObject so will be deleted here

}

void dbtests::caseTests(dataHolder *h)
{
    /*
     *  pcCase(QString model, QString ff, QStringList mbff, int gpu, int cooler, int pcieSlots,
     *      int fans, int hdds, int ssds, int usbs, int height, int width, int length,
     *      int price, bool rad = false, bool audio = true)
     *
     *  caseMap["ITX"]
     *  caseMap["mATX"]
     *  caseMap["ATX"]
     *  caseMap["E-ATX"]
     *  caseMap["Volume"]
     *
     *         Tests should include:
     *         Insertion into:
     *         ITX, mATX, ATX, E-ATX, make sure insertion into volume works
     *         Backup
     *         Restore
     *         Make sure everything's back where it's suppose to be
    */

    qDebug() << "Unit Testing Case database";
    fileWriter fw(h);
    QMap<QString, QList<pcCase*>> *cases = h->CASEMap();
    foreach(QString key, cases->keys())
        if (!cases->value(key).isEmpty())
        {
            qWarning() << "Case DB wasn't empty before testing, backing up and clearing";
            QFile backup(m_testDir + "/Backups/Case.JSON");
            backup.open(QIODevice::WriteOnly);
            fw.caseBackup(&backup);
            backup.close();
            break;
        }

    pcCase *case1 = new pcCase("ATX", "Mid Tower", {"ATX"}, 34, 17, 8, 3, 7, 2, 4, 60, 32, 58, 150, true, true);
    case1->setObjectName("ATX");
    h->addCase(case1);
    QVERIFY2(!cases->value("ITX").contains(case1), "ITX list contains non ITX case");
    QVERIFY2(!cases->value("mATX").contains(case1), "mATX list contains non mATX case");
    QVERIFY2(cases->value("ATX").contains(case1), "ATX list doesn't contain ATX case");
    QVERIFY2(!cases->value("E-ATX").contains(case1), "E-ATX list contains non E-ATX case");
    QVERIFY2(cases->value("Volume").contains(case1), "Volume list doesn't contain ATX case");

    pcCase *case2 = new pcCase("Lian Li PC-O11", "Full Tower", {"E-ATX", "mATX", "ITX"}, 41, 22, 8, 5, 7, 2, 2, 60, 32, 58, 250, true, true);
    case2->setObjectName("All but ATX");
    h->addCase(case2);
    QVERIFY2(cases->value("ITX").contains(case2), "ITX list doesn't contain ITX case");
    QVERIFY2(cases->value("mATX").contains(case2), "mATX list doesn't contain mATX case");
    QVERIFY2(!cases->value("ATX").contains(case2), "ATX list contains non ATX case");
    QVERIFY2(cases->value("E-ATX").contains(case2), "E-ATX list doesn't contain E-ATX case");
    QVERIFY2(cases->value("Volume").contains(case2), "Volume list doesn't contain All but ATX case");

    QFile db(m_testDir + "/Database/Case.JSON");
    db.open(QIODevice::ReadWrite);
    fw.caseBackup(&db);
    bool empty = true;
    foreach(QString key, cases->keys())
    {
        empty = cases->value(key).isEmpty();
        if (!empty)
        {
            qWarning() << key << " Case Map wasn't completely backed up";
        }
    }
    QVERIFY2(empty, "One or more lists weren't backed up properly or weren't emptied");
    fileReader fr(h);
    fr.restoreCases(&db);
    db.close();

    qDebug() << "Verification after restoration";
    // ATX case
    QVERIFY2(!cases->value("ITX").contains(case1), "ITX list contains non ITX case");
    QVERIFY2(!cases->value("mATX").contains(case1), "mATX list contains non mATX case");
    QVERIFY2(cases->value("ATX").contains(case1), "ATX list doesn't contain ATX case");
    QVERIFY2(!cases->value("E-ATX").contains(case1), "E-ATX list contains non E-ATX case");
    QVERIFY2(cases->value("Volume").contains(case1), "Volume list doesn't contain ATX case");
    // All but ATX case
    QVERIFY2(cases->value("ITX").contains(case2), "ITX list doesn't contain ITX case");
    QVERIFY2(cases->value("mATX").contains(case2), "mATX list doesn't contain mATX case");
    QVERIFY2(!cases->value("ATX").contains(case2), "ATX list contains non ATX case");
    QVERIFY2(cases->value("E-ATX").contains(case2), "E-ATX list doesn't contain E-ATX case");
    QVERIFY2(cases->value("Volume").contains(case2), "Volume list doesn't contain All but ATX case");

    qInfo() << "End of Case Unit Tests, passed successfully";
    // pcCase is a QObject so will be deleted here
}

void dbtests::runTests()
{
    dataHolder h("/home/nave/Documents/QtProjects/PCPartPicker/Test/");
    cpuTests(&h);
    gpuTests(&h);
    moboTests(&h);
    ramTests(&h);
    coolerTests(&h);
    psuTests(&h);
    storageTests(&h);
    caseTests(&h);
}
