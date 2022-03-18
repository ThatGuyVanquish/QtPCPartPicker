#include "../../include/Logic/specobject.h"

specObject::specObject(dataHolder *db, QObject *parent)
    : m_db(db),
      m_fw(db),
      QObject{parent}
{}

string specObject::getFileDir()
{
    return m_fileDir.toStdString();
}

void specObject::specs(CPU *cpu, QList<GPU *> gpus, motherboard *mobo, RAM *ram, QList<storage *> drives,
                       cooler *cooler, PSU *psu, pcCase *pcCase)
{
    if (!cpu)
    {
        cout << "Couldn't build a PC with the current database and given parameters \r\n";
        return;
    }
    m_creation = QDateTime::currentDateTime().toLocalTime();
    cout << "Would you like to name this build? \r\n";
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
    if (specName.size() == 0 || specName.toLower() == "no" || specName.toLower() == "n")
        specName = m_creation.toString() + " Specsheet, cost " + QString::number(cost);
    m_fileDir = m_db->getDir() + "/Specsheets/" + specName + ".JSON";
    m_fw.writeSpecs(m_fileDir, cpu, gpus, mobo, ram, cooler, drives, psu, pcCase);
}
