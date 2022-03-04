#include <QCoreApplication>
#include "CPU.h"
#include "intelCPU.cpp"
#include "dataholder.h"
#include "fileWriter.cpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CPU *cpu1 = new intelCPU("i5 4670K", "LGA1150", 4, 3.4, 15, 10, 20, 90, 200, true, false, -1, 4.2, true);
    CPU *cpu2 = new intelCPU("i7 8700K", "LGA1151", 6, 3.8, 25, 15, 24, 90, 300, true, false, 12, 4.5, true);
    dataHolder h(&a);
    h.addCPU(cpu1);
    h.addCPU(cpu2);
    fileWriter fw(&h);
    fw.backUp();
    return a.exec();
}
