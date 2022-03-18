#include "../../include/Database/filereader.h"

fileReader::fileReader(QObject *parent)
    : QObject{parent}
{}

fileReader::fileReader(dataHolder *db):
    m_db(db),
    m_cpu(db->getDir() + "/CPU.JSON"),
    m_gpu(db->getDir() + "/GPU.JSON"),
    m_mobo(db->getDir() + "/Motherboard.JSON"),
    m_ram(db->getDir() + "/RAM.JSON"),
    m_storage(db->getDir() + "/Storage.JSON"),
    m_psu(db->getDir() + "/PSU.JSON"),
    m_case(db->getDir() + "/Case.JSON"),
    m_cooler(db->getDir() + "/Cooler.JSON")
{}

void fileReader::closeFiles()
{
    if (m_cpu.isOpen())
        m_cpu.close();
    else return;
    if (m_gpu.isOpen())
        m_gpu.close();
    else return;
    if (m_mobo.isOpen())
        m_mobo.close();
    else return;
    if (m_ram.isOpen())
        m_ram.close();
    else return;
    if (m_storage.isOpen())
        m_storage.close();
    else return;
    if (m_cooler.isOpen())
        m_cooler.close();
    else return;
    if (m_psu.isOpen())
        m_psu.close();
    else return;
    if (m_case.isOpen())
        m_case.close();
}

int fileReader::openFiles()
{
    if (!m_cpu.open(QIODevice::ReadWrite))
    {
        qCritical() << "Could not read from CPU file!";
        qCritical() << m_cpu.errorString();
        return -1;
    }

    if (!m_gpu.open(QIODevice::ReadWrite))
    {
        qCritical() << "Could not read from GPU file!";
        qCritical() << m_gpu.errorString();
        qInfo() << "Closing opened file";
        closeFiles();
        return -2;
    }

    if (!m_mobo.open(QIODevice::ReadWrite))
    {
        qCritical() << "Could not read from Motherboard file!";
        qCritical() << m_mobo.errorString();
        qInfo() << "Closing opened files";
        closeFiles();
        return -3;
    }

    if (!m_ram.open(QIODevice::ReadWrite))
    {
        qCritical() << "Could not read from RAM file!";
        qCritical() << m_ram.errorString();
        qInfo() << "Closing opened files";
        closeFiles();
        return -4;
    }

    if (!m_storage.open(QIODevice::ReadWrite))
    {
        qCritical() << "Could not read from Storage file!";
        qCritical() << m_storage.errorString();
        qInfo() << "Closing opened files";
        closeFiles();
        return -5;
    }

    if (!m_psu.open(QIODevice::ReadWrite))
    {
        qCritical() << "Could not read from PSU file!";
        qCritical() << m_psu.errorString();
        qInfo() << "Closing opened files";
        closeFiles();
        return -7;
    }

    if (!m_cooler.open(QIODevice::ReadWrite))
    {
        qCritical() << "Could not read from Cooler file!";
        qCritical() << m_cooler.errorString();
        qInfo() << "Closing opened files";
        closeFiles();
        return -7;
    }

    if (!m_case.open(QIODevice::ReadWrite))
    {
        qCritical() << "Could not read from Case file!";
        qCritical() << m_case.errorString();
        qInfo() << "Closing opened files";
        closeFiles();
        return -6;
    }

    return 1;
}

void fileReader::restoreCPUs(QFile *f)
{
    QByteArray data;
    if (f->isOpen())
        data = f->readAll();
    else
        data = m_cpu.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    m_cpu.close();

    // Restoration of Intel CPUs
    QVariantMap intelCPUs = qvariant_cast<QVariantMap>(doc["Intel"]);
    foreach(QString key, intelCPUs.keys())
    {
        QVariantMap currentCPU = qvariant_cast<QVariantMap>(intelCPUs.value(key));
        QMap<QString, QString> specs;
        foreach(QString spec, currentCPU.keys())
        {
            specs.insert(spec, currentCPU.value(spec).toString());
        }
        CPU *toInsert = new intelCPU(specs["Model"], specs["Socket"], specs["Cores"].toInt(), specs["BClock"].toDouble(),
                specs["L2"].toInt(), specs["L3"].toInt(), specs["PCIe"].toInt(), specs["TDP"].toInt(),
                specs["Price"].toInt(), specs["iGPU"].toInt(), specs["Cooler"].toInt(),
                specs["Threads"].toInt(), specs["Boost"].toDouble(), specs["Unlocked"].toInt());
        m_db->addCPU(toInsert);
    }

    // Restoration of AMD CPUs
    QVariantMap amdCPUs = qvariant_cast<QVariantMap>(doc["AMD"]);
    foreach(QString key, amdCPUs.keys())
    {
        QVariantMap currentCPU = qvariant_cast<QVariantMap>(amdCPUs.value(key));
        QMap<QString, QString> specs;
        foreach(QString spec, currentCPU.keys())
        {
            specs.insert(spec, currentCPU.value(spec).toString());
        }
        CPU *toInsert = new amdCPU(specs["Model"], specs["Socket"], specs["Cores"].toInt(), specs["BClock"].toDouble(),
                specs["L2"].toInt(), specs["L3"].toInt(), specs["PCIe"].toInt(), specs["TDP"].toInt(),
                specs["Price"].toInt(), specs["iGPU"].toInt(), specs["Cooler"].toInt(),
                specs["Threads"].toInt(), specs["Boost"].toDouble());
        m_db->addCPU(toInsert);
    }
}

void fileReader::restoreGPUs(QFile *f)
{
    QByteArray data;
    if (f->isOpen())
        data = f->readAll();
    else
        data = m_gpu.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    m_gpu.close();

    // Restoration of Intel GPUs
    QVariantMap intelGPUs = qvariant_cast<QVariantMap>(doc["Intel"]);
    foreach(QString key, intelGPUs.keys())
    {
        QVariantMap currentGPU = qvariant_cast<QVariantMap>(intelGPUs.value(key));
        QMap<QString, QString> specs;
        foreach(QString spec, currentGPU.keys())
        {
            specs.insert(spec, currentGPU.value(spec).toString());
        }
        GPU *toInsert = new intelGPU(specs["Model"], specs["PCIE"].toInt(), specs["VRAM"].toInt(),
                specs["BClock"].toInt(), specs["Bus"].toInt(), specs["TDP"].toInt(), specs["Slots"].toInt(),
                specs["Height"].toInt(), specs["Length"].toInt(), specs["Price"].toInt(), specs["Inputs"].split(", "),
                specs["Boost"].toInt());
        m_db->addGPU(toInsert);
    }

    // Restoration of AMD GPUs
    QVariantMap amdGPUs = qvariant_cast<QVariantMap>(doc["AMD"]);
    foreach(QString key, amdGPUs.keys())
    {
        QVariantMap currentGPU = qvariant_cast<QVariantMap>(amdGPUs.value(key));
        QMap<QString, QString> specs;
        foreach(QString spec, currentGPU.keys())
        {
            specs.insert(spec, currentGPU.value(spec).toString());
        }
        GPU *toInsert = new amdGPU(specs["Model"], specs["PCIE"].toInt(), specs["VRAM"].toInt(),
                specs["BClock"].toInt(), specs["Bus"].toInt(), specs["TDP"].toInt(), specs["Slots"].toInt(),
                specs["Height"].toInt(), specs["Length"].toInt(), specs["Price"].toInt(), specs["Inputs"].split(", "),
                specs["Boost"].toInt(), specs["Ray Tracing"].toInt());
        m_db->addGPU(toInsert);
    }

    // Restoration of Nvidia GPUs
    QVariantMap nvidiaGPUs = qvariant_cast<QVariantMap>(doc["Nvidia"]);
    foreach(QString key, nvidiaGPUs.keys())
    {
        QVariantMap currentGPU = qvariant_cast<QVariantMap>(nvidiaGPUs.value(key));
        QMap<QString, QString> specs;
        foreach(QString spec, currentGPU.keys())
        {
            specs.insert(spec, currentGPU.value(spec).toString());
        }
        GPU *toInsert = new nvidiaGPU(specs["Model"], specs["PCIE"].toInt(), specs["VRAM"].toInt(),
                specs["BClock"].toInt(), specs["Bus"].toInt(), specs["TDP"].toInt(), specs["Slots"].toInt(),
                specs["Height"].toInt(), specs["Length"].toInt(), specs["Price"].toInt(), specs["Inputs"].split(", "),
                specs["Boost"].toInt(), specs["Ray Tracing"].toInt(), specs["DLSS"].toInt());
        m_db->addGPU(toInsert);
    }
}

void fileReader::restoreMotherboards(QFile *f)
{
    QByteArray data;
    if (f->isOpen())
        data = f->readAll();
    else
        data = m_mobo.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    m_mobo.close();    
    QVariantMap mobos = qvariant_cast<QVariantMap>(doc["Motherboards"]);
    foreach(QString key, mobos.keys())
    {
        QVariantMap currentMobo = qvariant_cast<QVariantMap>(mobos.value(key));
        QMap<QString, QString> specs;
        foreach(QString spec, currentMobo.keys())
        {
            specs.insert(spec, currentMobo.value(spec).toString());
        }
        motherboard *toInsert = new motherboard(specs["Model"], specs["CPU Manufacturer"], specs["Socket"],
                specs["RAM Slots"].toInt(), specs["RAM Version"], specs["Max RAM Size"].toInt(),
                specs["RAM Channels"].toInt(), specs["PCIE Slots"].toInt(), specs["SATA Slots"].toInt(),
                specs["M.2 Slots"].toInt(), specs["Fan Headers"].toInt(), specs["Form Factor"],
                specs["Length"].toInt(), specs["Width"].toInt(), specs["USB Slots"].toInt(),
                specs["Video Outputs"].split(", "), specs["Audio Outputs"].split(", "),
                specs["Price"].toInt(), specs["Ethernet"].toInt(), specs["Wifi"].toInt());
        m_db->addMotherboard(toInsert);
    }
}

void fileReader::restoreRAM(QFile *f)
{
    QByteArray data;
    if (f->isOpen())
        data = f->readAll();
    else
        data = m_ram.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    m_ram.close();

    QVariantMap ram = qvariant_cast<QVariantMap>(doc["RAM"]);
    foreach(QString key, ram.keys())
    {
        QVariantMap currentRAM = qvariant_cast<QVariantMap>(ram.value(key));
        QMap<QString, QString> specs;
        foreach(QString spec, currentRAM.keys())
        {
            specs.insert(spec, currentRAM.value(spec).toString());
        }
        QList<int> timings;
        foreach(QString val, specs["Timings"].split(", "))
        {
            timings.append(val.toInt());
        }
        RAM *toInsert = new RAM(specs["Model"], specs["Version"], specs["Size"].toInt(), specs["DIMMS"].toInt(),
                specs["Speed"].toInt(), timings, specs["Price"].toInt(), specs["Heatsink"].toInt());
        m_db->addRAM(toInsert);
    }
}

void fileReader::restoreStorage(QFile *f)
{
    QByteArray data;
    if (f->isOpen())
        data = f->readAll();
    else
        data = m_storage.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    m_storage.close();

    // Restoring hard drives
    QVariantMap storageMap = qvariant_cast<QVariantMap>(doc["HDDs"]);
    foreach(QString key, storageMap.keys())
    {
        QVariantMap currentDrive = qvariant_cast<QVariantMap>(storageMap.value(key));
        QMap<QString, QString> specs;
        foreach(QString spec, currentDrive.keys())
        {
            specs.insert(spec, currentDrive.value(spec).toString());
        }
        storage *toInsert = new hdd(specs["Model"], specs["Port"], specs["Size"], specs["Read"].toInt(),
                specs["Write"].toInt(), specs["Cache"].toInt(), specs["Price"].toInt());
        m_db->addStorage(toInsert);
    }

    // Restoring M.2 SSDs
    storageMap = qvariant_cast<QVariantMap>(doc["M.2 SSDs"]);
    foreach(QString key, storageMap.keys())
    {
        QVariantMap currentDrive = qvariant_cast<QVariantMap>(storageMap.value(key));
        QMap<QString, QString> specs;
        foreach(QString spec, currentDrive.keys())
        {
            specs.insert(spec, currentDrive.value(spec).toString());
        }
        storage *toInsert = new m2SSD(specs["Model"], specs["Size"], specs["Read"].toInt(),
                    specs["Write"].toInt(), specs["Cache"].toInt(), specs["Price"].toInt());
        m_db->addStorage(toInsert);
    }

    // Restoring SATA3 SSDs
    storageMap = qvariant_cast<QVariantMap>(doc["M.2 SSDs"]);
    foreach(QString key, storageMap.keys())
    {
        QVariantMap currentDrive = qvariant_cast<QVariantMap>(storageMap.value(key));
        QMap<QString, QString> specs;
        foreach(QString spec, currentDrive.keys())
        {
            specs.insert(spec, currentDrive.value(spec).toString());
        }
        storage *toInsert = new sataSSD(specs["Model"], specs["Size"], specs["Read"].toInt(),
                    specs["Write"].toInt(), specs["Cache"].toInt(), specs["Price"].toInt());
        m_db->addStorage(toInsert);
    }
}

void fileReader::restoreCoolers(QFile *f)
{
    QByteArray data;
    if (f->isOpen())
        data = f->readAll();
    else
        data = m_cooler.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    m_cooler.close();

    // Restoring AIOs
    QVariantMap coolerMap = qvariant_cast<QVariantMap>(doc["AIO"]);
    foreach(QString key, coolerMap.keys())
    {
        QVariantMap currentCooler= qvariant_cast<QVariantMap>(coolerMap.value(key));
        QMap<QString, QString> specs;
        foreach(QString spec, currentCooler.keys())
        {
            specs.insert(spec, currentCooler.value(spec).toString());
        }
        cooler *toInsert = new AIO(specs["Model"], specs["TDP"].toInt(), specs["Included Fans"].toInt(),
                specs["Maximum Fans"].toInt(), specs["Radiator Size"].toInt(), specs["Cooler Height"].toInt(),
                specs["Sockets"].split(", "), specs["Price"].toInt());
        m_db->addCooler(toInsert);
    }

    // Restoring air coolers
    coolerMap = qvariant_cast<QVariantMap>(doc["Air Cooler"]);
    foreach(QString key, coolerMap.keys())
    {
        QVariantMap currentCooler= qvariant_cast<QVariantMap>(coolerMap.value(key));
        QMap<QString, QString> specs;
        foreach(QString spec, currentCooler.keys())
        {
            specs.insert(spec, currentCooler.value(spec).toString());
        }
        cooler *toInsert = new airCooler(specs["Model"], specs["TDP"].toInt(), specs["Included Fans"].toInt(),
                specs["Maximum Fans"].toInt(), specs["Cooler Height"].toInt(), specs["Sockets"].split(", "),
                specs["Price"].toInt());
        m_db->addCooler(toInsert);
    }
}

void fileReader::restorePSUs(QFile *f)
{
    QByteArray data;
    if (f->isOpen())
        data = f->readAll();
    else
        data = m_psu.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    m_psu.close();

    QVariantMap psuMap = qvariant_cast<QVariantMap>(doc["PSUs"]);
    foreach(QString key, psuMap.keys())
    {
        QVariantMap currentPSU= qvariant_cast<QVariantMap>(psuMap.value(key));
        QMap<QString, QString> specs;
        foreach(QString spec, currentPSU.keys())
        {
            specs.insert(spec, currentPSU.value(spec).toString());
        }
        PSU *toInsert = new PSU(specs["Model"], specs["Modularity"], specs["Form Factor"],
                getEfficiency(specs["Efficiency"]), specs["Wattage"].toInt(), specs["Price"].toInt(),
                specs["Fan"].toInt());
        m_db->addPSU(toInsert);
    }
}

void fileReader::restoreCases(QFile *f)
{
    QByteArray data;
    if (f->isOpen())
        data = f->readAll();
    else
        data = m_case.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    m_case.close();

    QVariantMap caseMap = qvariant_cast<QVariantMap>(doc["Cases"]);
    foreach(QString key, caseMap.keys())
    {
        QVariantMap currentCase= qvariant_cast<QVariantMap>(caseMap.value(key));
        QMap<QString, QString> specs;
        foreach(QString spec, currentCase.keys())
        {
            specs.insert(spec, currentCase.value(spec).toString());
        }
        pcCase *toInsert = new pcCase(specs["Model"], specs["Form Factor"], specs["Compatible Motherboards"].split(", "),
                specs["GPU Length"].toInt(), specs["Cooler Height"].toInt(), specs["Expansion Slots"].toInt(),
                specs["Fans"].toInt(), specs["HDD Slots"].toInt(), specs["SSD Slots"].toInt(),
                specs["USB Ports"].toInt(), specs["Height"].toInt(), specs["Width"].toInt(),
                specs["Length"].toInt(), specs["Price"].toInt(), specs["Fits Radiators"].toInt(),
                specs["Front Audio"].toInt());
        m_db->addCase(toInsert);
    }
}

bool fileReader::restore()
{
    if (openFiles() <= 0)
        return false;
    QFile f;
    restoreCPUs(&f);
    restoreGPUs(&f);
    restoreMotherboards(&f);
    restoreRAM(&f);
    restoreStorage(&f);
    restoreCoolers(&f);
    restorePSUs(&f);
    restoreCases(&f);
    closeFiles();

    return true;
}
