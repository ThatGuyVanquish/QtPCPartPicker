﻿#include "../include/specbuildertests.h"

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
    intel1->setObjectName("Intel 2 Cores LGA1 30W 30$ Cooler");
    h->addCPU(intel1);
    CPU *intel2 = new intelCPU("2 Cores LGA2", "LGA2", 2, 3.0, 10, 10, 16, 30, 50, true, true);
    intel2->setObjectName("Intel 2 Cores LGA2 30W 50$ Cooler");
    h->addCPU(intel2);

    // 6 Cores
    CPU *intel3 = new intelCPU("6 Cores LGA2", "LGA2", 6, 3.5, 10, 10, 16, 50, 100, true, true);
    intel3->setObjectName("Intel 6 Cores LGA2 50W 100$ Cooler");
    h->addCPU(intel3);
    CPU *intel4 = new intelCPU("6 Cores LGA3", "LGA3", 6, 3.8, 15, 15, 20, 65, 140, true, false, 12, 4.3, true);
    intel4->setObjectName("Intel 6 Cores LGA3 65W 140$ OC");
    h->addCPU(intel4);

    // 8 Cores
    CPU *intel5 = new intelCPU("8 Cores LGA2", "LGA2", 8, 3.5, 10, 10, 16, 50, 160, true, true);
    intel5->setObjectName("Intel 8 Cores LGA2 50W 160$ Cooler");
    h->addCPU(intel5);
    CPU *intel6 = new intelCPU("8 Cores LGA3", "LGA3", 8, 4.2, 15, 15, 24, 65, 210, true, false, 16, 4.3, true);
    intel6->setObjectName("Intel 8 Cores LGA3 65W 210$ OC");
    h->addCPU(intel6);

    // OC
    CPU *intel7 = new intelCPU("10 Cores LGA2", "LGA2", 10, 3.5, 10, 10, 16, 90, 300, true, false, 20, 4.5, true);
    intel7->setObjectName("Intel 10 Cores LGA2 90W 300$ OC");
    h->addCPU(intel7);
    CPU *intel8 = new intelCPU("12 Cores LGA3", "LGA3", 12, 4.2, 15, 15, 24, 105, 350, true, false, 24, 4.7, true);
    intel8->setObjectName("Intel 12 Cores LGA3 105W 350$ OC");
    h->addCPU(intel8);

    // Server
    CPU *intel9 = new intelCPU("16 Cores IN1", "IN1", 16, 3.5, 10, 10, 48, 155, 3000, true, false, 32, 4.5, true);
    intel9->setObjectName("Intel 16 Cores IN1 155W 3000$ OC");
    h->addCPU(intel9);
    CPU *intel10 = new intelCPU("32 Cores IN1", "IN1", 32, 4.2, 15, 15, 72, 200, 3500, true, false, 64, 4.7, true);
    intel10->setObjectName("Intel 32 Cores IN1 200W 3500$ OC");
    h->addCPU(intel10);

    /*
     * AMD CPUs
     *  amdCPU(QString model, QString socket, int cores, double base, int l2, int l3, int lanes, int tdp,
     *  int price, bool igpu = false, bool cooler = false, int threads = -1, double boost = -1)
    */
    // 2 Cores
    CPU *amd1 = new amdCPU("2 Cores AM1", "AM1", 2, 3, 10, 10, 16, 30, 20, false, true);
    amd1->setObjectName("AMD 2 Cores AM1 30W 20$ Cooler OC");
    h->addCPU(amd1);
    CPU *amd2 = new amdCPU("2 Cores AM2", "AM2", 2, 3.2, 10, 10, 16, 30, 40, false, true);
    amd2->setObjectName("AMD 2 Cores AM2 30W 40$ Cooler OC");
    h->addCPU(amd2);

    // 6 Cores
    CPU *amd3 = new amdCPU("6 Cores AM1", "AM1", 6, 3.3, 10, 10, 16, 30, 100, true, true, 12, 3.7);
    amd3->setObjectName("AMD 6 Cores AM1 APU 30W 150$ Cooler OC");
    h->addCPU(amd3);
    CPU *amd4 = new amdCPU("6 Cores AM2", "AM2", 6, 3.5, 10, 10, 16, 30, 120, false, true, 12, 3.8);
    amd4->setObjectName("AMD 6 Cores AM2 30W 120$ Cooler OC");
    h->addCPU(amd4);

    // 8 Cores
    CPU *amd5 = new amdCPU("8 Cores AM1", "AM1", 8, 3.3, 10, 10, 16, 60, 250, false, false, 16, 3.7);
    amd5->setObjectName("AMD 8 Cores AM1 60W 250$ OC");
    h->addCPU(amd5);
    CPU *amd6 = new amdCPU("8 Cores AM2", "AM2", 8, 3.5, 10, 10, 16, 75, 300, false, false, 16, 4);
    amd6->setObjectName("AMD 8 Cores AM2 75W 300$ OC");
    h->addCPU(amd6);

    // OC or X variants cause all AMD CPUs are set to unlocked
    CPU *amd7 = new amdCPU("8 Cores AM1", "AM1", 8, 4.1, 10, 10, 16, 120, 350, false, false, 16, 4.7);
    amd7->setObjectName("AMD 8 Cores AM1 120W 350$ OC");
    h->addCPU(amd7);
    CPU *amd8 = new amdCPU("8 Cores AM2", "AM2", 8, 4.3, 10, 10, 16, 150, 400, false, false, 16, 4.8);
    amd8->setObjectName("AMD 8 Cores AM2 150W 400$ OC");
    h->addCPU(amd8);

    // Server
    CPU *amd9 = new amdCPU("16 Cores EP1", "EP1", 16, 3.3, 10, 10, 72, 210, 2000, false, false, 32);
    amd9->setObjectName("AMD 16 Cores EP1 210W 2000$ OC");
    h->addCPU(amd9);
    CPU *amd10 = new amdCPU("32 Cores EP2", "EP2", 32, 3.5, 10, 10, 108, 250, 3300, false, false, 64);
    amd10->setObjectName("AMD 32 Cores EP2 250W 3300$ OC");
    h->addCPU(amd10);
}

void specBuilderTests::createGPUs(dataHolder *h)
{
    /*
     * 2 Intel GPUs
     * 3 AMD GPUs, two with RT
     * 4 Nvidia GPUs, 1 basic, 3 with DLSS, out of which 2 with RT
     *
    */

    /*
     * Intel GPUs
     *  intelGPU(QString model, int pcie, int vram, int base, int bus, int tdp, int pcieSlots,
     *      int height, int length, int price, QStringList inputs, int boost = -1)
     *
    */
    GPU *intel1 = new intelGPU("PCIE4 30W 50$", 4, 4, 1600, 24, 30, 2, 15, 25, 50, {"HDMI"});
    intel1->setObjectName("Intel PCIE4 30W 50$");
    h->addGPU(intel1);
    GPU *intel2 = new intelGPU("PCIE4 50W 100$", 4, 4, 1600, 24, 50, 2, 15, 25, 100, {"HDMI"});
    intel2->setObjectName("Intel PCIE4 50W 100$");
    h->addGPU(intel2);

    /*
     * AMD GPUs
     *  amdGPU(QString model, int pcie, int vram, int base, int bus, int tdp, int pcieSlots, int height,
     *      int length, int price, QStringList inputs, int boost = -1, bool rays = false)
     *
    */
    GPU *amd1 = new amdGPU("PCIE3 30W 40$", 3, 2, 1300, 32, 30, 1, 15, 23, 40, {"HDMI"});
    amd1->setObjectName("AMD PCIE3 30W 40$");
    h->addGPU(amd1);
    GPU *amd2 = new amdGPU("PCIE3 30W 40$ RT", 3, 8, 1887, 128, 210, 3, 18, 31, 400, {"HDMI"}, 2070, true);
    amd2->setObjectName("AMD PCIE3 210W 400$ RT");
    h->addGPU(amd2);
    GPU *amd3 = new amdGPU("PCIE4 250W 600$ RT", 4, 12, 1948, 256, 250, 2, 17, 29, 600, {"HDMI"}, 2110, true);
    amd3->setObjectName("AMD PCIE4 250W 600$ RT");
    h->addGPU(amd3);

    /*
     * NVIDIA GPUs
     *  nvidiaGPU(QString model, int pcie, int vram, int base, int bus, int tdp,
     *      int pcieSlots, int height, int length, int price, QStringList inputs,
     *      int boost = -1, bool rays = false, bool dlss = true)
    */
    GPU *nv1 = new nvidiaGPU("PCIE3 20W 50$", 3, 2, 1650, 32, 20, 1, 11, 12, 50, {"HDMI"}, 1698, false, false);
    nv1->setObjectName("Nvidia PCIE3 20W 50$");
    h->addGPU(nv1);
    GPU *nv2 = new nvidiaGPU("PCIE3 150W 350$ DLSS", 3, 8, 1850, 128, 150, 2, 17, 28, 350, {"HDMI"}, 2008, false);
    nv2->setObjectName("Nvidia PCIE3 150W 350$ DLSS");
    h->addGPU(nv2);
    GPU *nv3 = new nvidiaGPU("PCIE4 300W 650$ RT DLSS", 4, 12, 1887, 256, 300, 1, 17, 31, 650, {"HDMI"}, 2187, true);
    nv3->setObjectName("Nvidia PCIE4 300W 650$ RT DLSS");
    h->addGPU(nv3);
    GPU *nv4 = new nvidiaGPU("PCIE4 400W 950$ RT DLSS", 4, 24, 1995, 512, 400, 1, 18, 32, 950, {"HDMI"}, 2230, true);
    nv4->setObjectName("Nvidia PCIE4 400W 950$RT DLSS");
    h->addGPU(nv4);
}

void specBuilderTests::createMobos(dataHolder *h)
{
    /*
    * Need:
    * LGA1 (DDR3) -> 1 mATX, 1 OC (ATX), 1 ITX with 2 dimm slots
    * LGA2 (DDR4) -> 1 mATX, 1 OC (ATX), 1 ITX with 2 dimm slots
    * LGA3 (DDR5) -> 1 mATX, 1 OC (ATX), 1 ITX with 2 dimm slots
    * IN1 (DDR4), OC -> 2 with 4 dimm slots and 2 with 6
    * AM1 (DDR4) -> 1 mATX, 1 ATX, 1 ITX with 2 dimm slots
    * AM2 (DDR5) -> 1 mATX, 1 ATX, 1 ITX with 2 dimm slots
    * EP1 (DDR4) -> 2 with 4 dimm slots and 2 with 6
    * EP2 (DDR5) -> 2 with 4 dimm slots and 2 with 6
    *
    * LGA2 mATX mining board (10 pcie slots)
    * AM1 ATX mining board (10 pcie slots)
    *
    * motherboard(QString model, QString cpu, QString socket, int ram, QString ramV, int maxram, int chs, int pcie,
    *     int sata, int m2, int fan, QString ff, int l, int w, int usb, QStringList vid, QStringList aud,
    *     int price, bool eth = true, bool wifi = false)
    */

    // Intel mobos
    // LGA1
    motherboard *intel1 = new motherboard("Intel LGA1 mATX DDR3 4 DIMMs 50$", "Intel", "LGA1", 4, "DDR3", 32, 2, 3,
                                          3, 3, 5, "mATX", 24, 24, 6, {"HDMI"}, {}, 50);
    intel1->setObjectName("Intel LGA1 mATX DDR3 4 DIMMs 50$");
    h->addMotherboard(intel1);
    motherboard *intel2 = new motherboard("Intel LGA1 ATX DDR3 4 DIMMs 150$ OC", "Intel", "LGA1", 4, "DDR3", 64, 2, 3,
                                          3, 1, 5, "ATX", 30, 24, 6, {"HDMI"}, {}, 150);
    intel2->setObjectName("Intel LGA1 ATX DDR3 4 DIMMs 150$ OC");
    h->addMotherboard(intel2);
    motherboard *intel3 = new motherboard("Intel LGA1 ITX DDR3 2 DIMMs 150$", "Intel", "LGA1", 2, "DDR3", 32, 2, 5,
                                          6, 3, 7, "ITX", 17, 17, 6, {"HDMI"}, {}, 150);
    intel3->setObjectName("Intel LGA1 ITX DDR3 2 DIMMs 150$");
    h->addMotherboard(intel3);

    // LGA2
    motherboard *intel4 = new motherboard("Intel LGA2 mATX DDR4 4 DIMMs 75$", "Intel", "LGA2", 4, "DDR4", 32, 2, 3,
                                          3, 3, 5, "mATX", 24, 24, 6, {"HDMI"}, {}, 50);
    intel4->setObjectName("Intel LGA2 mATX DDR4 4 DIMMs 75$");
    h->addMotherboard(intel4);
    motherboard *intel5 = new motherboard("Intel LGA2 ATX DDR4 4 DIMMs 200$ OC", "Intel", "LGA2", 4, "DDR4", 64, 2, 3,
                                          3, 1, 5, "ATX", 30, 24, 6, {"HDMI"}, {}, 225);
    intel5->setObjectName("Intel LGA2 ATX DDR4 4 DIMMs 225$ OC");
    h->addMotherboard(intel5);
    motherboard *intel6 = new motherboard("Intel LGA2 ITX DDR4 2 DIMMs 250$", "Intel", "LGA2", 2, "DDR4", 32, 2, 5,
                                          6, 3, 7, "ITX", 17, 17, 6, {"HDMI"}, {}, 250);
    intel6->setObjectName("Intel LGA2 ITX DDR4 2 DIMMs 250$");
    h->addMotherboard(intel6);

    // LGA3
    motherboard *intel7 = new motherboard("Intel LGA3 mATX DDR5 4 DIMMs 110$", "Intel", "LGA3", 4, "DDR5", 32, 2, 3,
                                          3, 3, 5, "mATX", 24, 24, 6, {"HDMI"}, {}, 110);
    intel7->setObjectName("Intel LGA3 mATX DDR5 4 DIMMs 110$");
    h->addMotherboard(intel7);
    motherboard *intel8 = new motherboard("Intel LGA3 ATX DDR5 4 DIMMs 275$ OC", "Intel", "LGA3", 4, "DDR5", 64, 2, 3,
                                          3, 1, 5, "ATX", 30, 24, 6, {"HDMI"}, {}, 275);
    intel8->setObjectName("Intel LGA3 ATX DDR5 4 DIMMs 275$ OC");
    h->addMotherboard(intel8);
    motherboard *intel9 = new motherboard("Intel LGA3 ITX DDR5 2 DIMMs 350$", "Intel", "LGA3", 2, "DDR5", 32, 2, 5,
                                          6, 3, 7, "ITX", 17, 17, 6, {"HDMI"}, {}, 350);
    intel9->setObjectName("Intel LGA3 ITX DDR5 2 DIMMs 350$");
    h->addMotherboard(intel9);

    // IN1
    motherboard *intel10 = new motherboard("Intel IN1 E-ATX DDR4 4 DIMMs 375$", "Intel", "IN1", 4, "DDR4", 64, 2, 3,
                                          10, 3, 5, "E-ATX", 30, 33, 6, {"HDMI"}, {}, 375);
    intel10->setObjectName("Intel IN1 E-ATX DDR4 4 DIMMs 375$");
    h->addMotherboard(intel10);
    motherboard *intel11 = new motherboard("Intel IN1 E-ATX DDR4 4 DIMMs 875$", "Intel", "IN1", 4, "DDR4", 256, 4, 3,
                                          22, 3, 5, "E-ATX", 30, 33, 6, {"HDMI"}, {}, 875);
    intel11->setObjectName("Intel IN1 E-ATX DDR4 4 DIMMs 875$");
    h->addMotherboard(intel11);
    motherboard *intel12 = new motherboard("Intel IN1 E-ATX DDR4 6 DIMMs 575$", "Intel", "IN1", 6, "DDR4", 96, 3, 3,
                                          18, 3, 5, "E-ATX", 30, 33, 6, {"HDMI"}, {}, 575);
    intel12->setObjectName("Intel IN1 E-ATX DDR4 6 DIMMs 575$");
    h->addMotherboard(intel12);
    motherboard *intel13 = new motherboard("Intel IN1 E-ATX DDR4 6 DIMMs 1375$", "Intel", "IN1", 6, "DDR4", 384, 6, 3,
                                          26, 3, 5, "E-ATX", 30, 33, 6, {"HDMI"}, {}, 1375);
    intel13->setObjectName("Intel IN1 E-ATX DDR4 6 DIMMs 1375$");
    h->addMotherboard(intel13);

    // Mining
    motherboard *intel14 = new motherboard("Intel Mining LGA2 2 DIMMs 300$", "Intel", "LGA2", 2, "DDR4", 32, 2, 10,
                                           4, 1, 10, "mATX", 24, 24, 2, {"HDMI"}, {}, 300);
    intel14->setObjectName("Intel Mining LGA2 2 DIMMs 300$");
    h->addMotherboard(intel14);

    // AMD Mobos
    // AM1
    motherboard *amd1 = new motherboard("AMD AM1 mATX DDR4 4 DIMMs 60$", "AMD", "AM1", 4, "DDR4", 32, 2, 3,
                                        4, 1, 5, "mATX", 24, 24, 4, {"HDMI"}, {}, 60);
    amd1->setObjectName("AMD AM1 mATX DDR4 4 DIMMs 60$");
    h->addMotherboard(amd1);
    motherboard *amd2 = new motherboard("AMD AM1 ATX DDR4 4 DIMMs 100$", "AMD", "AM1", 4, "DDR4", 64, 2, 3,
                                        4, 2, 5, "ATX", 30, 24, 4, {"HDMI"}, {}, 100);
    amd2->setObjectName("AMD AM1 ATX DDR4 4 DIMMs 100$");
    h->addMotherboard(amd2);
    motherboard *amd3 = new motherboard("AMD AM1 ITX DDR4 2 DIMMs 120$", "AMD", "AM1", 2, "DDR4", 32, 2, 3,
                                        2, 1, 4, "ITX", 17, 17, 4, {"HDMI"}, {}, 120);
    amd3->setObjectName("AMD AM1 ITX DDR4 2 DIMMs 120$");
    h->addMotherboard(amd3);

    // AM2
    motherboard *amd4 = new motherboard("AMD AM2 mATX DDR5 4 DIMMs 150$", "AMD", "AM2", 4, "DDR5", 32, 2, 3,
                                        4, 1, 5, "mATX", 24, 24, 4, {"HDMI"}, {}, 150);
    amd4->setObjectName("AMD AM2 mATX DDR5 4 DIMMs 150$");
    h->addMotherboard(amd4);
    motherboard *amd5 = new motherboard("AMD AM2 ATX DDR5 4 DIMMs 200$", "AMD", "AM2", 4, "DDR5", 64, 2, 3,
                                        4, 3, 5, "ATX", 30, 24, 4, {"HDMI"}, {}, 200);
    amd5->setObjectName("AMD AM2 ATX DDR5 4 DIMMs 200$");
    h->addMotherboard(amd5);
    motherboard *amd6 = new motherboard("AMD AM2 ITX DDR5 2 DIMMs 320$", "AMD", "AM2", 2, "DDR5", 32, 2, 3,
                                        2, 1, 4, "ITX", 17, 17, 4, {"HDMI"}, {}, 320);
    amd6->setObjectName("AMD AM2 ITX DDR5 2 DIMMs 320$");
    h->addMotherboard(amd6);

    // EP1
    motherboard *amd7 = new motherboard("AMD EP1 E-ATX DDR4 4 DIMMs 350$", "AMD", "EP1", 4, "DDR4", 128, 4, 4,
                                        10, 2, 6, "E-ATX", 30, 33, 4, {"HDMI"}, {}, 350);
    amd7->setObjectName("AMD EP1 E-ATX DDR4 4 DIMMs 350$");
    h->addMotherboard(amd7);
    motherboard *amd8 = new motherboard("AMD EP1 E-ATX DDR4 4 DIMMs 650$", "AMD", "EP1", 4, "DDR4", 512, 4, 4,
                                        20, 2, 6, "E-ATX", 30, 33, 4, {"HDMI"}, {}, 650);
    amd8->setObjectName("AMD EP1 E-ATX DDR4 4 DIMMs 650$");
    h->addMotherboard(amd8);
    motherboard *amd9 = new motherboard("AMD EP1 E-ATX DDR4 6 DIMMs 550$", "AMD", "EP1", 6, "DDR4", 160, 6, 4,
                                        16, 2, 6, "E-ATX", 30, 33, 4, {"HDMI"}, {}, 550);
    amd9->setObjectName("AMD EP1 E-ATX DDR4 6 DIMMs 550$");
    h->addMotherboard(amd9);
    motherboard *amd10 = new motherboard("AMD EP1 E-ATX DDR4 6 DIMMs 1650$", "AMD", "EP1", 6, "DDR4", 1024, 6, 4,
                                        40, 2, 6, "E-ATX", 30, 33, 4, {"HDMI"}, {}, 1650);
    amd10->setObjectName("AMD EP1 E-ATX DDR4 6 DIMMs 1650$");
    h->addMotherboard(amd10);

    // EP2
    motherboard *amd11 = new motherboard("AMD EP2 E-ATX DDR5 4 DIMMs 450$", "AMD", "EP2", 4, "DDR5", 128, 4, 4,
                                        10, 2, 6, "E-ATX", 30, 33, 4, {"HDMI"}, {}, 450);
    amd11->setObjectName("AMD EP2 E-ATX DDR5 4 DIMMs 450$");
    h->addMotherboard(amd11);
    motherboard *amd12 = new motherboard("AMD EP2 E-ATX DDR5 4 DIMMs 650$", "AMD", "EP2", 4, "DDR5", 512, 4, 4,
                                        20, 2, 6, "E-ATX", 30, 33, 4, {"HDMI"}, {}, 750);
    amd12->setObjectName("AMD EP2 E-ATX DDR5 4 DIMMs 750$");
    h->addMotherboard(amd12);
    motherboard *amd13 = new motherboard("AMD EP2 E-ATX DDR5 6 DIMMs 550$", "AMD", "EP2", 6, "DDR5", 160, 6, 4,
                                        16, 2, 6, "E-ATX", 30, 33, 4, {"HDMI"}, {}, 650);
    amd13->setObjectName("AMD EP2 E-ATX DDR5 6 DIMMs 650$");
    h->addMotherboard(amd13);
    motherboard *amd14 = new motherboard("AMD EP2 E-ATX DDR5 6 DIMMs 1650$", "AMD", "EP2", 6, "DDR5", 1024, 6, 4,
                                        40, 2, 6, "E-ATX", 30, 33, 4, {"HDMI"}, {}, 1450);
    amd14->setObjectName("AMD EP2 E-ATX DDR5 6 DIMMs 1450$");
    h->addMotherboard(amd14);

    // Mining
    motherboard *amd15 = new motherboard("AMD Mining AM1 2 DIMMs 200$", "AMD", "AM1", 2, "DDR4", 32, 2, 3,
                                         10, 1, 10, "ATX", 30, 24, 4, {"HDMI"}, {}, 200);
    amd15->setObjectName("AMD Mining AM1 2 DIMMs 200$");
    h->addMotherboard(amd15);
}

void specBuilderTests::createRAM(dataHolder *h)
{
    /*
     * DDR3 -> 2x2gb, 4x1gb, 2x4gb, 2x8gb, 4x4gb, 2x16gb
     * DDR4 -> 1x4gb, 2x4gb, 1x8gb, 2x8gb, 2x16gb, 4x16gb, 8x16gb, 8x32gb
     * DDR5 -> 2x4gb, 1x8gb, 2x8gb, 2x16gb, 4x16gb, 8x16gb, 8x32gb, 6x64gb
     *
     *  RAM(QString model, QString version, int size, int dimms, int speed,
     *      QList<int> timing, int price, bool hs = true)
    */

    // DDR3
    RAM *three1 = new RAM("DDR3 2x2GB, 20$", "DDR3", 4, 2, 1133, {4, 6, 7, 8}, 20);
    three1->setObjectName("DDR3 2x2GB, 20$");
    h->addRAM(three1);
    RAM *three2 = new RAM("DDR3 4x1GB, 15$", "DDR3", 4, 4, 1133, {4, 6, 7, 8}, 15);
    three2->setObjectName("DDR3 4x1GB, 15$");
    h->addRAM(three2);
    RAM *three3 = new RAM("DDR3 2x4GB, 40$", "DDR3", 8, 2, 1333, {4, 6, 7, 8}, 40);
    three3->setObjectName("DDR3 2x4GB, 40$");
    h->addRAM(three3);
    RAM *three4 = new RAM("DDR3 2x8GB, 80$", "DDR3", 16, 2, 1600, {4, 6, 7, 8}, 80);
    three4->setObjectName("DDR3 2x8GB, 80$");
    h->addRAM(three4);
    RAM *three5 = new RAM("DDR3 4x4GB, 70$", "DDR3", 16, 4, 1600, {4, 6, 7, 8}, 70);
    three5->setObjectName("DDR3 4x4GB, 70$");
    h->addRAM(three5);
    RAM *three6 = new RAM("DDR3 2x16GB, 200$", "DDR3", 32, 2, 1600, {4, 6, 7, 8}, 200);
    three6->setObjectName("DDR3 2x16GB, 200$");
    h->addRAM(three6);

    // DDR4
    RAM *four1 = new RAM("DDR4 1x4GB, 35$", "DDR4", 4, 1, 2133, {14, 16, 17, 18}, 35);
    four1->setObjectName("DDR4 1x4GB, 35$");
    h->addRAM(four1);
    RAM *four2 = new RAM("DDR4 2x4GB, 75$", "DDR4", 8, 2, 2133, {14, 16, 17, 18}, 75);
    four2->setObjectName("DDR4 2x4GB, 75$");
    h->addRAM(four2);
    RAM *four3 = new RAM("DDR4 1x8GB, 85$", "DDR4", 8, 1, 2133, {14, 16, 17, 18}, 85);
    four3->setObjectName("DDR4 1x8GB, 85$");
    h->addRAM(four3);
    RAM *four4 = new RAM("DDR4 2x8GB, 200$", "DDR4", 16, 2, 2666, {16, 18, 17, 18}, 200);
    four4->setObjectName("DDR4 2x8GB, 200$");
    h->addRAM(four4);
    RAM *four5 = new RAM("DDR4 2x16GB, 415$", "DDR4", 32, 2, 3133, {18, 16, 19, 18}, 415);
    four5->setObjectName("DDR4 2x16GB, 415$");
    h->addRAM(four5);
    RAM *four6 = new RAM("DDR4 4x16GB, 820$", "DDR4", 64, 4, 3133, {17, 16, 17, 18}, 820);
    four6->setObjectName("DDR4 4x16GB, 820$");
    h->addRAM(four6);
    RAM *four7 = new RAM("DDR4 8x16GB, 1550$", "DDR4", 128, 8, 2666, {19, 19, 21, 18}, 1550);
    four7->setObjectName("DDR4 8x16GB, 1550$");
    h->addRAM(four7);
    RAM *four8 = new RAM("DDR4 8x32GB, 3460$", "DDR4", 256, 8, 2400, {20, 21, 17, 19}, 3460);
    four8->setObjectName("DDR4 8x32GB, 3460$");
    h->addRAM(four8);

    // DDR5
    RAM *five1 = new RAM("DDR5 2x4GB, 90$", "DDR5", 8, 2, 4133, {14, 16, 17, 18}, 90);
    five1->setObjectName("DDR5 2x4GB, 90$");
    h->addRAM(five1);
    RAM *five2 = new RAM("DDR5 1x8GB, 100$", "DDR5", 8, 1, 4133, {14, 16, 17, 18}, 100);
    five2->setObjectName("DDR5 1x8GB, 100$");
    h->addRAM(five2);
    RAM *five3 = new RAM("DDR5 2x8GB, 215$", "DDR5", 16, 2, 4666, {16, 18, 17, 18}, 215);
    five3->setObjectName("DDR5 2x8GB, 215$");
    h->addRAM(five3);
    RAM *five4 = new RAM("DDR5 2x16GB, 430$", "DDR5", 32, 2, 5133, {18, 16, 19, 18}, 430);
    five4->setObjectName("DDR5 2x16GB, 430$");
    h->addRAM(five4);
    RAM *five5 = new RAM("DDR5 4x16GB, 850$", "DDR5", 64, 4, 5133, {17, 16, 17, 18}, 850);
    five5->setObjectName("DDR5 4x16GB, 850$");
    h->addRAM(five5);
    RAM *five6 = new RAM("DDR5 8x16GB, 1600$", "DDR5", 128, 8, 4133, {19, 19, 21, 18}, 1600);
    five6->setObjectName("DDR5 8x16GB, 1600$");
    h->addRAM(five6);
    RAM *five7 = new RAM("DDR5 8x32GB, 3500$", "DDR5", 256, 8, 4133, {20, 21, 17, 19}, 3500);
    five7->setObjectName("DDR5 8x32GB, 3500$");
    h->addRAM(five7);
    RAM *five8 = new RAM("DDR5 6x64GB, 7254$", "DDR5", 364, 6, 4133, {20, 21, 17, 19}, 7254);
    five8->setObjectName("DDR5 6x64GB, 7254$");
    h->addRAM(five8);
}

void specBuilderTests::createCoolers(dataHolder *h)
{
    /*
     * AIOs - 120 80w, 120 100w, 240 200w, 240 250w, 360 400w
     * Air - 12 40w, 12 100w, 13 150w, 16 250w, 18 350w, 8 500w (server -> expensive)
     *
    */

    // AIOs
    // AIO(QString model, int tdp, int fans, int maxFans, int rads, int h, QStringList sockets, int price)
    cooler *aio1 = new AIO("120mm LGA1, AM1 80W 30$", 80, 1, 2, 120, 3, {"LGA1", "AM1"}, 30);
    aio1->setObjectName("120mm LGA1, AM1 80W 30$");
    h->addCooler(aio1);
    cooler *aio2 = new AIO("120mm LGA1, LGA2, AM1 100W 40$", 100, 1, 2, 120, 3, {"LGA1", "LGA2", "AM1"}, 40);
    aio2->setObjectName("120mm LGA1, LGA2, AM1 100W 40$");
    h->addCooler(aio2);
    cooler *aio3 = new AIO("240mm LGA1, LGA2, AM1, AM2 200W 80$", 200, 2, 4, 240, 3, {"LGA1", "LGA2", "AM1", "AM2"}, 80);
    aio3->setObjectName("240mm LGA1, LGA2, AM1, AM2 200W 80$");
    h->addCooler(aio3);
    cooler *aio4 = new AIO("240mm LGA2, LGA3, AM1, AM2 250W 100$", 250, 2, 4, 240, 3, {"LGA2", "LGA3", "AM1", "AM2"}, 100);
    aio4->setObjectName("240mm LGA2, LGA3, AM1, AM2 250W 100$");
    h->addCooler(aio4);
    cooler *aio5 = new AIO("360mm LGA2, LGA3, AM2 400W 200$", 400, 3, 6, 360, 3, {"LGA2", "LGA3", "AM2"}, 200);
    aio5->setObjectName("360mm LGA2, LGA3, AM2 400W 200$");
    h->addCooler(aio5);

    // Air Coolers
    // airCooler(QString model, int tdp, int fans, int maxFans, int h, QStringList sockets, int price)
    cooler *air1 = new airCooler("12cm 40W LGA1, AM1 15$", 40, 1, 1, 12, {"LGA1", "AM1"}, 15);
    air1->setObjectName("12cm 40W LGA1, AM1 15$");
    h->addCooler(air1);
    cooler *air2 = new airCooler("12cm 100W LGA1, LGA2, AM1, AM2 25$", 100, 1, 1, 12, {"LGA1", "LGA2", "AM1", "AM2"}, 25);
    air2->setObjectName("12cm 100W LGA1, LGA2, AM1, AM2 25$");
    h->addCooler(air2);
    cooler *air3 = new airCooler("13cm 150W LGA2, LGA3, AM1, AM2 45$", 150, 1, 2, 13, {"LGA3", "LGA2", "AM1", "AM2"}, 45);
    air3->setObjectName("13cm 150W LGA2, LGA3, AM1, AM2 45$");
    h->addCooler(air3);
    cooler *air4 = new airCooler("16cm 250W LGA1, LGA2, LGA3, AM1, AM2 80$", 250, 2, 2, 16, {"LGA3", "LGA2", "LGA1", "AM1", "AM2"}, 80);
    air4->setObjectName("16cm 250W LGA1, LGA2, LGA3, AM1, AM2 80$");
    h->addCooler(air4);
    cooler *air5 = new airCooler("18cm 350W LGA1, LGA2, LGA3, AM1, AM2 120$", 350, 2, 2, 18, {"LGA3", "LGA2", "LGA1", "AM1", "AM2"}, 120);
    air5->setObjectName("18cm 350W LGA1, LGA2, LGA3, AM1, AM2 120$");
    h->addCooler(air5);
    cooler *air6 = new airCooler("8cm 500W IN1, IN2, EP1, EP2 400$", 500, 0, 0, 8, {"IN1", "IN2", "EP1", "EP2"}, 400);
    air6->setObjectName("8cm 500W IN1, IN2, EP1, EP2 400$ SERVER");
    h->addCooler(air6);
}

void specBuilderTests::createPSUs(dataHolder *h)
{
    /*
     * SFF - 450, 650, 850, 1000
     * ATX - 600(1 silver 1 none), 800 (1 Gold 1 none), 1000 (1 silver 1 platinum), 1200, 1500, 2000
     * Server - 1000, 1500, 2000, 3000, 4000
     *
     * PSU(QString model, QString modularity, QString ff, Efficiency efficiency, int wattage, int price, bool fan = true)
    */

    // SFF
    PSU *sff1 = new PSU("sff 450w Gold 80$", "Fully Modular", "SFF", Efficiency::Gold, 450, 80);
    sff1->setObjectName("sff 450w Gold 80$");
    h->addPSU(sff1);
    PSU *sff2 = new PSU("sff 650w Gold 140$", "Fully Modular", "SFF", Efficiency::Gold, 650, 140);
    sff2->setObjectName("sff 650w Gold 140$");
    h->addPSU(sff2);
    PSU *sff3 = new PSU("sff 850w Platinum 200$", "Fully Modular", "SFF", Efficiency::Platinum, 850, 80);
    sff3->setObjectName("sff 850w Platinum 200$");
    h->addPSU(sff3);
    PSU *sff4 = new PSU("sff 1000w Titanium 340$", "Fully Modular", "SFF", Efficiency::Titanium, 1000, 340);
    sff4->setObjectName("sff 1000w Titanium 340$");
    h->addPSU(sff4);

    // ATX
    PSU *atx1 = new PSU("ATX 600w None 40$", "Not modular", "ATX", Efficiency::None, 600, 40);
    atx1->setObjectName("ATX 600w None 40$");
    h->addPSU(atx1);
    PSU *atx2 = new PSU("ATX 600w Silver 50$", "Semi Modular", "ATX", Efficiency::Silver, 600, 50);
    atx2->setObjectName("ATX 600w Silver 50$");
    h->addPSU(atx2);
    PSU *atx3 = new PSU("ATX 800w None 60$", "Not modular", "ATX", Efficiency::None, 800, 60);
    atx3->setObjectName("ATX 800w None 60$");
    h->addPSU(atx3);
    PSU *atx4 = new PSU("ATX 800w Gold 75$", "Semi Modular", "ATX", Efficiency::Gold, 800, 75);
    atx4->setObjectName("ATX 800w Gold 75$");
    h->addPSU(atx4);
    PSU *atx5 = new PSU("ATX 1000w Silver 100$", "Semi Modular", "ATX", Efficiency::Silver, 1000, 100);
    atx5->setObjectName("ATX 1000w Silver 100$");
    h->addPSU(atx5);
    PSU *atx6 = new PSU("ATX 1000w Platinum 125$", "Fully Modular", "ATX", Efficiency::Platinum, 1000, 125);
    atx6->setObjectName("ATX 1000w Platinum 125$");
    h->addPSU(atx6);
    PSU *atx7 = new PSU("ATX 1200w Platinum 150$", "Fully Modular", "ATX", Efficiency::Platinum, 1200, 150);
    atx7->setObjectName("ATX 1200w Platinum 150$");
    h->addPSU(atx7);
    PSU *atx8 = new PSU("ATX 1500w Titanium 200$", "Fully Modular", "ATX", Efficiency::Titanium, 1500, 200);
    atx8->setObjectName("ATX 1500w Titanium 200$");
    h->addPSU(atx8);
    PSU *atx9 = new PSU("ATX 2000w Platinum 400$", "Fully Modular", "ATX", Efficiency::Platinum, 2000, 400);
    atx9->setObjectName("ATX 2000w Platinum 400$");
    h->addPSU(atx9);

    // Server
    PSU *server1 = new PSU("Server 1000w Gold 300$", "Not modular", "Server", Efficiency::Gold, 1000, 300);
    server1->setObjectName("Server 1000w Gold 300$");
    h->addPSU(server1);
    PSU *server2 = new PSU("Server 1500w Gold 800$", "Not modular", "Server", Efficiency::Gold, 1500, 800);
    server2->setObjectName("Server 1500w Gold 800$");
    h->addPSU(server2);
    PSU *server3 = new PSU("Server 2000w Gold 1700$", "Not modular", "Server", Efficiency::Gold, 2000, 1700);
    server3->setObjectName("Server 2000w Gold 1700$");
    h->addPSU(server3);
    PSU *server4 = new PSU("Server 3000w Gold 2500$", "Not modular", "Server", Efficiency::Gold, 3000, 2500);
    server4->setObjectName("Server 3000w Gold 2500$");
    h->addPSU(server4);
    PSU *server5 = new PSU("Server 4000w Gold 3000$", "Not modular", "Server", Efficiency::Gold, 4000, 3000);
    server5->setObjectName("Server 4000w Gold 3000$");
    h->addPSU(server5);
}

void specBuilderTests::createStorage(dataHolder *h)
{
    /*
     * HDDs - 500gb, 1tb, 2tb, 4tb, 8tb, 16tb
     * Sata SSDs - 250gb, 500gb, 1tb, 2tb, 4tb
     * m.2 SSDs - 250gb, 500gb, 1tb, 2tb
     *
    */

    // HDDs
    // hdd(QString model, QString port, QString size, int read, int write, int cache, int price)
    storage *hdd1 = new hdd("hdd 500gb 30$", "SATA3", "500GB", 350, 250, 32, 30);
    hdd1->setObjectName("hdd 500gb 30$");
    h->addStorage(hdd1);
    storage *hdd2 = new hdd("hdd 1TB 55$", "SATA3", "1TB", 350, 275, 32, 55);
    hdd2->setObjectName("hdd 1TB 55$");
    h->addStorage(hdd2);
    storage *hdd3 = new hdd("hdd 2TB 100$", "SATA3", "2TB", 330, 220, 32, 100);
    hdd3->setObjectName("hdd 2TB 100$");
    h->addStorage(hdd3);
    storage *hdd4 = new hdd("hdd 4TB 190$", "SATA3", "4TB", 350, 250, 32, 190);
    hdd4->setObjectName("hdd 4TB 190$");
    h->addStorage(hdd4);
    storage *hdd5 = new hdd("hdd 8TB 365$", "SATA3", "8TB", 350, 250, 32, 365);
    hdd5->setObjectName("hdd 8TB 365$");
    h->addStorage(hdd5);
    storage *hdd6 = new hdd("hdd 16TB 1000$", "SATA3", "16TB", 350, 250, 32, 1000);
    hdd6->setObjectName("hdd 16TB 1000$");
    h->addStorage(hdd6);

    // Sata SSDs
    // sataSSD(QString model, QString size, int read, int write, int cache, int price)
    storage *ssd1 = new sataSSD("sata ssd 250gb 30$", "250GB", 423, 356, 32, 30);
    ssd1->setObjectName("sata ssd 250gb 30$");
    h->addStorage(ssd1);
    storage *ssd2 = new sataSSD("sata ssd 500gb 63$", "500GB", 423, 356, 32, 63);
    ssd2->setObjectName("sata ssd 500gb 63$");
    h->addStorage(ssd2);
    storage *ssd3 = new sataSSD("sata ssd 1TB 130$", "1TB", 423, 356, 32, 130);
    ssd3->setObjectName("sata ssd 1TB 130$");
    h->addStorage(ssd3);
    storage *ssd4 = new sataSSD("sata ssd 2TB 230$", "2TB", 423, 356, 32, 230);
    ssd4->setObjectName("sata ssd 2TB 230$");
    h->addStorage(ssd4);
    storage *ssd5 = new sataSSD("sata ssd 4TB 530$", "4TB", 423, 356, 32, 530);
    ssd5->setObjectName("sata ssd 4TB 530$");
    h->addStorage(ssd5);

    // M.2 SSDs
    // m2SSD(QString model, QString size, int read, int write, int cache, int price)
    storage *m21 = new m2SSD("m.2 250gb 50$", "250GB", 1780, 1600, 128, 50);
    m21->setObjectName("m.2 250gb 50$");
    h->addStorage(m21);
    storage *m22 = new m2SSD("m.2 500gb 120$", "500GB", 1780, 1600, 128, 120);
    m22->setObjectName("m.2 500gb 120$");
    h->addStorage(m22);
    storage *m23 = new m2SSD("m.2 1TB 270$", "1TB", 2780, 2400, 128, 270);
    m23->setObjectName("m.2 1TB 270$");
    h->addStorage(m23);
    storage *m24 = new m2SSD("m.2 2TB 632$", "2TB", 3380, 3100, 128, 632);
    m24->setObjectName("m.2 2TB 632$");
    h->addStorage(m24);
}

void specBuilderTests::createCases(dataHolder *h)
{
    /*
     * ATX, matx, itx - 1 with 15cm cooler height, 1 with rad support, 1 with 20cm cooler height
     * 1 with just 3 pcie slots, 1 with 5 hdd slots and 2 ssd slots
     *
     * ITX with just 2 pcie slots, 1 with rad support, 1 with 14cm cooler height
     *
     * E-ATX with 6 pcie slots, 5 hdd slots, 10 hdd slots, 20 hdd slots
     *
     *  pcCase(QString model, QString ff, QStringList mbff, int gpu, int cooler, int pcieSlots,
     *     int fans, int hdds, int ssds, int usbs, int height, int width, int length,
     *     int price, bool rad = false, bool audio = true)
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
