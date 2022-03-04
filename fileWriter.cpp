#include "dataholder.h"

#include <fstream>
#include <QObject>
#include <QFile>
#include <QVariant>
#include <QVariantMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QIODevice>
#include <QDebug>

class fileWriter
{
private:
    dataHolder *m_db;
    QFile m_cpu;
    QFile m_gpu;
    QFile m_mobo;
    QFile m_ram;
    QFile m_storage;
    QFile m_case;
    QFile m_cooler;

public:
    fileWriter(dataHolder *db):
        m_db(db),
        m_cpu("/home/nave/Documents/QtProjects/PCPartPicker/database/CPU.JSON"),
        m_gpu("/home/nave/Documents/QtProjects/PCPartPicker/database/GPU.JSON"),
        m_mobo("/home/nave/Documents/QtProjects/PCPartPicker/database/Motherboard.JSON"),
        m_ram("/home/nave/Documents/QtProjects/PCPartPicker/database/RAM.JSON"),
        m_storage("/home/nave/Documents/QtProjects/PCPartPicker/database/Storage.JSON"),
        m_case("/home/nave/Documents/QtProjects/PCPartPicker/database/Case.JSON"),
        m_cooler("/home/nave/Documents/QtProjects/PCPartPicker/database/Cooler.JSON")
    {}
    ~fileWriter(){}

    void closeFiles()
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
        if (m_case.isOpen())
            m_case.close();
        else return;
        if (m_cooler.isOpen())
            m_cooler.close();
    }

    int openFiles()
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

    void cpuBackUp()
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
        m_cpu.write(doc.toJson());
        m_db->clearCPUMaps();
    }

    void gpuBackUp()
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
        gpumap.insert("NVidia", nvidiaGPUs);
        QJsonDocument doc = QJsonDocument::fromVariant(QVariant(gpumap));
        m_gpu.write(doc.toJson());
        m_db->clearGPUMaps();
    }

    void moboBackUp()
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
            delete moboToWrite;
            moboToWrite = m_db->removeMobo();
        }
        QJsonDocument doc = QJsonDocument::fromVariant(QVariant(mobomap));
        m_mobo.write(doc.toJson());
        m_db->clearMoboMaps();
    }

    void ramBackUp()
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
            delete ramToWrite;
            ramToWrite = m_db->removeRAM();
        }
        QJsonDocument doc = QJsonDocument::fromVariant(QVariant(rammap));
        m_ram.write(doc.toJson());
        m_db->clearRAMMaps();
    }

    void storageBackUp()
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
            delete driveToWrite;
            driveToWrite = m_db->removeStorage();
        }
        storagemap.insert("HDDs", QVariant(hddmap));
        storagemap.insert("SATA SSDs", QVariant(ssdmap));
        storagemap.insert("M.2 SSDs", QVariant(m2map));
        QJsonDocument doc = QJsonDocument::fromVariant(QVariant(storagemap));
        m_storage.write(doc.toJson());
        m_db->clearStorageMaps();
    }

    void coolerBackUp()
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
        m_cooler.write(doc.toJson());
        m_db->clearCoolerMaps();
    }

    void caseBackUp()
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
            delete caseToWrite;
            caseToWrite = m_db->removeCase();
        }
        QJsonDocument doc = QJsonDocument::fromVariant(QVariant(casemap));
        m_case.write(doc.toJson());
        m_db->clearCaseMaps();
    }

    bool backUp ()
    {
        if (openFiles() <= 0)
        {
            return false;
        }
        cpuBackUp();
        gpuBackUp();
        moboBackUp();
        ramBackUp();
        storageBackUp();
        coolerBackUp();
        caseBackUp();

        closeFiles();
        return true;
    }
};
