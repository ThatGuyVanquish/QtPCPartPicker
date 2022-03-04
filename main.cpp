#include <QCoreApplication>
#include "CPU.h"
#include "intelCPU.cpp"
#include "amdCPU.cpp"
#include "intelGPU.cpp"
#include "amdGPU.cpp"
#include "nvidiaGPU.cpp"
#include "motherboard.h"
#include "RAM.h"
#include "storage.h"
#include "hdd.cpp"
#include "sataSSD.cpp"
#include "m2SSD.cpp"
#include "pcCase.h"
#include "cooler.h"
#include "AIO.cpp"
#include "airCooler.cpp"
#include "dataholder.h"
#include "fileWriter.cpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CPU *cpu1 = new intelCPU("i5 4670K", "LGA1150", 4, 3.4, 15, 10, 20, 90, 200, true, false, -1, 4.2, true);
    CPU *cpu2 = new intelCPU("i7 8700K", "LGA1151", 6, 3.8, 25, 15, 24, 90, 300, true, false, 12, 4.5, true);
    CPU *cpu3 = new amdCPU("Ryzen 9 5950X", "AM4", 8, 3.4, 30, 15, 40, 150, 800, false, false, 16, 4.0);

    GPU *gpu1 = new intelGPU("Iris XE", 4, 8, 1800, 32, 40, 1, 3, 3, 43, {"HDMI"});
    GPU *gpu2 = new amdGPU("RX6800", 4, 8, 1200, 64, 250, 2, 20, 28, 800, {"DisplayPort 2.1"}, 1450, true);
    GPU *gpu3 = new nvidiaGPU("RTX3090Ti", 4, 16, 1950, 512, 350, 3, 21, 30, 1400, {"DVI-D"}, 2134, true);

    motherboard *m1 = new motherboard("MSI Z590 Godlike", "Intel", "LGA1700", 4, "DDR5", 128, 2, 4, 8, 4, 8, "ATX", 20, 34, 8, {"HDMI", "USB C"}, {"Left","Right"}, 1200);
    motherboard *m2 = new motherboard("ASUS ROG Hero EXTREME 9", "AMD", "AM4", 4, "DDR4", 64, 2, 3, 6, 2, 8, "ATX", 15, 43, 6, {"HDMI"}, {"Optical"}, 1000, true, true);


    dataHolder h(&a);
    h.addCPU(cpu1);
    h.addCPU(cpu2);
    h.addCPU(cpu3);
    fileWriter fw(&h);
    fw.backUp();
    return a.exec();
}
