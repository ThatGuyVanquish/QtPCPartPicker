#include "../../include/Logic/specobject.h"

specObject::specObject(dataHolder *db, QObject *parent)
    : m_fw(db),
      QObject{parent}
{}

void specObject::specs(CPU *cpu, QList<GPU *> gpus, motherboard *mobo, RAM *ram, QList<storage *> drives,
                       cooler *cooler, PSU *psu, pcCase *pcCase)
{
    cout << "Would you like to name this build?/r/n";
    string name;
    cin >> name;
    int cost = cpu->getPrice() + mobo->getPrice() + ram->getPrice() + pcCase->getPrice() + (cooler ? cooler->getPrice() : 0);
    foreach(GPU *gpu, gpus)
    {
        cost += gpu->getPrice();
    }
    foreach(storage *drive, drives)
        cost += drive-> getPrice();

    QString specName = QString::fromStdString(name).simplified();
    if (specName.size() == 0 || specName.toLower() == "no")
        specName = QDateTime::currentDateTime().toLocalTime().toString() + " Specsheet, cost " + QString::number(cost);
    QString target = "../../Specsheets/" + specName;
    m_fw.writeSpecs(target, cpu, gpus, mobo, ram, cooler, drives, psu, pcCase);
    // figure out how to open the file
}
