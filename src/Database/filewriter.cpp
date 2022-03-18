#include "../../include/Database/filewriter.h"

fileWriter::fileWriter(dataHolder *db):
    m_db(db),
    m_cpu(db->getDir() + "CPU.JSON"),
    m_gpu(db->getDir() + "GPU.JSON"),
    m_mobo(db->getDir() + "Motherboard.JSON"),
    m_ram(db->getDir() + "RAM.JSON"),
    m_storage(db->getDir() + "Storage.JSON"),
    m_case(db->getDir() + "Case.JSON"),
    m_psu(db->getDir() + "PSU.JSON"),
    m_cooler(db->getDir() + "Cooler.JSON")
{}

void fileWriter::closeFiles()
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
    if (m_psu.isOpen())
        m_psu.close();
    else return;
    if (m_case.isOpen())
        m_case.close();
    else return;
    if (m_cooler.isOpen())
        m_cooler.close();
}

int fileWriter::openFiles()
{
    if (!m_cpu.open(QIODevice::WriteOnly))
    {
        qCritical() << "Could not write to CPU file!";
        qCritical() << m_cpu.errorString();
        return -1;
    }

    if (!m_gpu.open(QIODevice::WriteOnly))
    {
        qCritical() << "Could not write to GPU file!";
        qCritical() << m_gpu.errorString();
        qInfo() << "Closing opened file";
        closeFiles();
        return -2;
    }

    if (!m_mobo.open(QIODevice::WriteOnly))
    {
        qCritical() << "Could not write to Motherboard file!";
        qCritical() << m_mobo.errorString();
        qInfo() << "Closing opened files";
        closeFiles();
        return -3;
    }

    if (!m_ram.open(QIODevice::WriteOnly))
    {
        qCritical() << "Could not write to RAM file!";
        qCritical() << m_ram.errorString();
        qInfo() << "Closing opened files";
        closeFiles();
        return -4;
    }

    if (!m_storage.open(QIODevice::WriteOnly))
    {
        qCritical() << "Could not write to Storage file!";
        qCritical() << m_storage.errorString();
        qInfo() << "Closing opened files";
        closeFiles();
        return -5;
    }

    if (!m_psu.open(QIODevice::WriteOnly))
    {
        qCritical() << "Could not write to PSU file!";
        qCritical() << m_psu.errorString();
        qInfo() << "Closing opened files";
        closeFiles();
        return -5;
    }

    if (!m_case.open(QIODevice::WriteOnly))
    {
        qCritical() << "Could not write to Case file!";
        qCritical() << m_case.errorString();
        qInfo() << "Closing opened files";
        closeFiles();
        return -6;
    }

    if (!m_cooler.open(QIODevice::WriteOnly))
    {
        qCritical() << "Could not write to Cooler file!";
        qCritical() << m_cooler.errorString();
        qInfo() << "Closing opened files";
        closeFiles();
        return -7;
    }

    return 1;
}

void fileWriter::cpuBackup(QFile *f)
{
    QVariantMap intelCPUs;
    QVariantMap amdCPUs;
    QVariantMap cpumap;
    QVariantMap cpuSpecs;
    CPU *cpuToWrite = m_db->removeCPU();
    while (cpuToWrite != nullptr)
    {
        foreach(QString key, cpuToWrite->backup().keys())
        {
            cpuSpecs.insert(key, QVariant(cpuToWrite->backup().value(key)));
        }
        if (cpuToWrite->getManu() == "Intel")
            intelCPUs.insert(cpuToWrite->getModel(), QVariant(cpuSpecs));
        else
            amdCPUs.insert(cpuToWrite->getModel(), QVariant(cpuSpecs));
        cpuToWrite = m_db->removeCPU();
    }
    cpumap.insert("Intel", intelCPUs);
    cpumap.insert("AMD", amdCPUs);
    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(cpumap));
    if (f->isOpen())
        f->write(doc.toJson());
    else
        m_cpu.write(doc.toJson());
    m_db->clearCPUMaps();
}

void fileWriter::gpuBackup(QFile *f)
{
    QVariantMap intelGPUs;
    QVariantMap amdGPUs;
    QVariantMap nvidiaGPUs;
    QVariantMap gpumap;
    QVariantMap gpuSpecs;
    GPU* gpuToWrite = m_db->removeGPU();
    while (gpuToWrite != nullptr)
    {
        foreach(QString key, gpuToWrite->backup().keys())
        {
            gpuSpecs.insert(key, QVariant(gpuToWrite->backup().value(key)));
        }
        if (gpuToWrite->getManu() == "Intel")
            intelGPUs.insert(gpuToWrite->getModel(), QVariant(gpuSpecs));
        else if (gpuToWrite->getManu() == "AMD")
            amdGPUs.insert(gpuToWrite->getModel(), QVariant(gpuSpecs));
        else
            nvidiaGPUs.insert(gpuToWrite->getModel(), QVariant(gpuSpecs));
        gpuToWrite = m_db->removeGPU();
    }
    gpumap.insert("Intel", intelGPUs);
    gpumap.insert("AMD", amdGPUs);
    gpumap.insert("Nvidia", nvidiaGPUs);
    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(gpumap));
    if (f->isOpen())
        f->write(doc.toJson());
    else
        m_gpu.write(doc.toJson());
    m_db->clearGPUMaps();
}

void fileWriter::moboBackup(QFile *f)
{
    QVariantMap mobomap;
    QVariantMap moboSpecs;
    motherboard* moboToWrite = m_db->removeMobo();
    while (moboToWrite != nullptr)
    {
        foreach(QString key, moboToWrite->backup().keys())
        {
            moboSpecs.insert(key, QVariant(moboToWrite->backup().value(key)));
        }
        mobomap.insert(moboToWrite->getModel(), QVariant(moboSpecs));
        moboToWrite = m_db->removeMobo();
    }
    QVariantMap backupMap;
    backupMap["Motherboards"] = QVariant(mobomap);
    QJsonDocument doc = QJsonDocument::fromVariant(backupMap);
    if (f->isOpen())
        f->write(doc.toJson());
    else
        m_mobo.write(doc.toJson());
    m_db->clearMoboMaps();
}

void fileWriter::ramBackup(QFile *f)
{
    QVariantMap rammap;
    QVariantMap ramSpecs;
    RAM* ramToWrite = m_db->removeRAM();
    while (ramToWrite != nullptr)
    {
        foreach(QString key, ramToWrite->backup().keys())
        {
            ramSpecs.insert(key, QVariant(ramToWrite->backup().value(key)));
        }
        rammap.insert(ramToWrite->getModel(), QVariant(ramSpecs));
        ramToWrite = m_db->removeRAM();
    }
    QVariantMap backupMap;
    backupMap["RAM"] = QVariant(rammap);
    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(backupMap));
    if (f->isOpen())
        f->write(doc.toJson());
    else
        m_ram.write(doc.toJson());
    m_db->clearRAMMaps();
}

void fileWriter::storageBackup(QFile *f)
{
    QVariantMap m2map;
    QVariantMap hddmap;
    QVariantMap ssdmap;
    QVariantMap storageSpecs;
    QVariantMap storagemap;
    storage* driveToWrite = m_db->removeStorage();
    while (driveToWrite != nullptr)
    {
        foreach(QString key, driveToWrite->backup().keys())
        {
            storageSpecs.insert(key, driveToWrite->backup().value(key));
        }
        if (driveToWrite->getType() == "hdd")
            hddmap.insert(driveToWrite->getModel(), QVariant(storageSpecs));
        else if (driveToWrite->getPort() == "M.2")
            m2map.insert(driveToWrite->getModel(), QVariant(storageSpecs));
        else
            ssdmap.insert(driveToWrite->getModel(), QVariant(storageSpecs));
        driveToWrite = m_db->removeStorage();
    }
    storagemap.insert("HDDs", QVariant(hddmap));
    storagemap.insert("SATA SSDs", QVariant(ssdmap));
    storagemap.insert("M.2 SSDs", QVariant(m2map));
    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(storagemap));
    if (f->isOpen())
        f->write(doc.toJson());
    else
        m_storage.write(doc.toJson());
    m_db->clearStorageMaps();
}

void fileWriter::coolerBackup(QFile *f)
{
    QVariantMap aiomap;
    QVariantMap airmap;
    QVariantMap coolerSpecs;
    QVariantMap coolermap;
    cooler* coolerToWrite = m_db->removeCooler();
    while (coolerToWrite != nullptr)
    {
        foreach(QString key, coolerToWrite->backup().keys())
        {
            coolerSpecs.insert(key, coolerToWrite->backup().value(key));
        }
        if (coolerToWrite->getType() == "AIO")
            aiomap.insert(coolerToWrite->getModel(), QVariant(coolerSpecs));
        else
            airmap.insert(coolerToWrite->getModel(), QVariant(coolerSpecs));
        delete coolerToWrite;
        coolerToWrite = m_db->removeCooler();
    }
    coolermap.insert("AIO", QVariant(aiomap));
    coolermap.insert("Air Cooler", QVariant(airmap));
    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(coolermap));
    if (f->isOpen())
        f->write(doc.toJson());
    else
        m_cooler.write(doc.toJson());
    m_db->clearCoolerMaps();
}

void fileWriter::psuBackup(QFile *f)
{
    QVariantMap psumap;
    QVariantMap psuSpecs;
    PSU *psuToWrite = m_db->removePSU();
    while (psuToWrite != nullptr)
    {
        foreach(QString key, psuToWrite->backup().keys())
        {
            psuSpecs.insert(key, psuToWrite->backup().value(key));
        }
        psumap.insert(psuToWrite->getModel(), psuSpecs);
        psuToWrite = m_db->removePSU();
    }
    QVariantMap backupMap;
    backupMap["PSUs"] = QVariant(psumap);
    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(backupMap));
    if (f->isOpen())
        f->write(doc.toJson());
    else
        m_psu.write(doc.toJson());
    m_db->clearPSUMaps();
}

void fileWriter::caseBackup(QFile *f)
{
    QVariantMap casemap;
    QVariantMap caseSpecs;
    pcCase* caseToWrite = m_db->removeCase();
    while (caseToWrite != nullptr)
    {
        foreach(QString key, caseToWrite->backup().keys())
        {
            caseSpecs.insert(key, caseToWrite->backup().value(key));
        }
        casemap.insert(caseToWrite->getModel(), caseSpecs);
        caseToWrite = m_db->removeCase();
    }
    QVariantMap backupMap;
    backupMap["Cases"] = QVariant(casemap);
    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(backupMap));
    if (f->isOpen())
        f->write(doc.toJson());
    else
        m_case.write(doc.toJson());
    m_db->clearCaseMaps();
}

bool fileWriter::backup()
{
    if (openFiles() <= 0)
        return false;
    QFile f;
    cpuBackup(&f);
    gpuBackup(&f);
    moboBackup(&f);
    ramBackup(&f);
    storageBackup(&f);
    coolerBackup(&f);
    psuBackup(&f);
    caseBackup(&f);

    closeFiles();
    return true;
}

void fileWriter::writeCPU(QFile *target, CPU *cpu)
{
    QVariantMap specs;
    QMap<QString, QString> cpuSpecs = cpu->backup();
    foreach(QString key, cpuSpecs.keys())
    {
        specs.insert(key, QVariant(cpuSpecs.value(key)));
    }
    QVariantMap toWrite;
    toWrite.insert("CPU", QVariant(specs));
    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(toWrite));
    target->write(doc.toJson());
    qDebug() << "Finished writing CPU";
}

void fileWriter::writeGPUs(QFile *target, QList<GPU *> gpus)
{
    QVariantMap gpuMap;
    QVariantMap specs;
    foreach(GPU *gpu, gpus)
    {
        QMap<QString, QString> gpuSpecs = gpu->backup();
        foreach(QString key, gpuSpecs.keys())
        {
            specs.insert(key, QVariant(gpuSpecs.value(key)));
        }
        gpuMap.insert(gpu->getModel(), QVariant(specs));
    }
    QVariantMap toWrite;
    toWrite.insert("GPUs", QVariant(gpuMap));
    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(toWrite));
    target->write(doc.toJson());
    qDebug() << "Finished writing GPUs";
}

void fileWriter::writeMobo(QFile *target, motherboard *mobo)
{
    QVariantMap specs;
    QMap<QString, QString> moboSpecs = mobo->backup();
    foreach(QString key, moboSpecs.keys())
    {
        specs.insert(key, QVariant(moboSpecs.value(key)));
    }
    QVariantMap toWrite;
    toWrite.insert("Motherboard", QVariant(specs));
    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(toWrite));
    target->write(doc.toJson());
    qDebug() << "Finished writing Motherboard";
}

void fileWriter::writeRAM(QFile *target, RAM *ram)
{
    QVariantMap specs;
    QMap<QString, QString> ramSpecs = ram->backup();
    foreach(QString key, ramSpecs.keys())
    {
        specs.insert(key, QVariant(ramSpecs.value(key)));
    }
    QVariantMap toWrite;
    toWrite.insert("RAM", QVariant(specs));
    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(toWrite));
    target->write(doc.toJson());
    qDebug() << "Finished writing RAM";
}

void fileWriter::writeCooler(QFile *target, cooler *cooler)
{
    QVariantMap specs;
    QMap<QString, QString> coolerSpecs = cooler->backup();
    foreach(QString key, coolerSpecs.keys())
    {
        specs.insert(key, QVariant(coolerSpecs.value(key)));
    }
    QVariantMap toWrite;
    toWrite.insert("Cooler", QVariant(specs));
    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(toWrite));
    target->write(doc.toJson());
    qDebug() << "Finished writing Cooler";
}

void fileWriter::writeStorage(QFile *target, QList<storage *> drives)
{
    QVariantMap driveMap;
    QVariantMap specs;
    foreach(storage *drive, drives)
    {
        QMap<QString, QString> driveSpecs = drive->backup();
        foreach(QString key, driveSpecs.keys())
        {
            specs.insert(key, QVariant(driveSpecs.value(key)));
        }
        driveMap.insert(drive->getModel(), QVariant(specs));
    }
    QVariantMap toWrite;
    toWrite.insert("Storage", QVariant(driveMap));
    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(toWrite));
    target->write(doc.toJson());
    qDebug() << "Finished writing Storage";
}

void fileWriter::writePSU(QFile *target, PSU *psu)
{
    QVariantMap specs;
    QMap<QString, QString> psuSpecs = psu->backup();
    foreach(QString key, psuSpecs.keys())
    {
        specs.insert(key, QVariant(psuSpecs.value(key)));
    }
    QVariantMap toWrite;
    toWrite.insert("PSU", QVariant(specs));
    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(toWrite));
    target->write(doc.toJson());
    qDebug() << "Finished writing PSU";
}

void fileWriter::writeCase(QFile *target, pcCase *pcCase)
{
    QVariantMap specs;
    QMap<QString, QString> caseSpecs = pcCase->backup();
    foreach(QString key, caseSpecs.keys())
    {
        specs.insert(key, QVariant(caseSpecs.value(key)));
    }
    QVariantMap toWrite;
    toWrite.insert("Case", QVariant(specs));
    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(toWrite));
    target->write(doc.toJson());
    qDebug() << "Finished writing Case";
}

void fileWriter::writeSpecs(QString target, CPU *cpu, QList<GPU *> gpus, motherboard *mobo, RAM *ram,
                            cooler *cooler, QList<storage *> drives, PSU *psu, pcCase *pcCase)
{
    QFile f(target);
    if (!f.open(QIODevice::WriteOnly))
    {
        qCritical() << "Could not write to file!";
        qCritical() << f.errorString();
        return;
    }
    writeCPU(&f, cpu);
    writeGPUs(&f, gpus);
    writeMobo(&f, mobo);
    writeRAM(&f, ram);
    writeStorage(&f, drives);
    writeCooler(&f, cooler);
    writePSU(&f, psu);
    writeCase(&f, pcCase);
    f.close();
    qDebug() << "Finished writing specs! You can now open the file!";
}
