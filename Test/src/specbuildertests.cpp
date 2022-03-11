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

}

void specBuilderTests::createCoolers(dataHolder *h)
{

}

void specBuilderTests::createPSUs(dataHolder *h)
{

}

void specBuilderTests::createStorage(dataHolder *h)
{

}

void specBuilderTests::createCases(dataHolder *h)
{

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
