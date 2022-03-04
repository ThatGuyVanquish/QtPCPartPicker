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
        m_cooler("/home/nave/Documents/QtProjects/PCPartPicker/database/Coler.JSON")
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

    bool backUp ()
    {
        if (openFiles() <= 0)
        {
            return false;
        }

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
            //delete cpuToWrite;
            cpuToWrite = m_db->removeCPU();
        }
        cpumap.insert("Intel", intelCPUs);
        cpumap.insert("AMD", amdCPUs);
        QJsonDocument doc = QJsonDocument::fromVariant(QVariant(cpumap));
        m_cpu.write(doc.toJson());
        m_db->clearCPUMaps();

        QVariantMap intelGPUs;
        QVariantMap amdGPUs;
        QVariantMap nvidiaGPUs;
        QVariantMap gpumap;
        QVariantMap gpuSpecs;
        GPU* gpuToWrite = m_db->removeGPU();
        while (gpuToWrite != nullptr)
        {
            foreach(QString key,)
            delete gpuToWrite;
            gpuToWrite = m_db->removeGPU();
        }
        gpufile.close();

        QFile mobofile("Motherboard.JSON");
        if (!mobofile.open(QIODevice::WriteOnly))
        {
            qCritical() << "Could not write file!";
            qCritical() << mobofile.errorString();
            return 0;
        }
        motherboard* moboToWrite = m_db->removeMobo();
        while (moboToWrite != nullptr)
        {
            // write to mobo file
            delete moboToWrite;
            moboToWrite = m_db->removeMobo();
        }
        mobofile.close();

        QFile ramfile("RAM.JSON");
        if (!ramfile.open(QIODevice::WriteOnly))
        {
            qCritical() << "Could not write file!";
            qCritical() << ramfile.errorString();
            return 0;
        }
        RAM* ramToWrite = m_db->removeRAM();
        while (ramToWrite != nullptr)
        {
            // write to ram file
            delete ramToWrite;
            ramToWrite = m_db->removeRAM();
        }
        ramfile.close();

        QFile storagefile("Storage.JSON");
        if (!storagefile.open(QIODevice::WriteOnly))
        {
            qCritical() << "Could not write file!";
            qCritical() << storagefile.errorString();
            return 0;
        }
        storage* driveToWrite = m_db->removeStorage();
        while (driveToWrite != nullptr)
        {
            // write to storage file
            delete driveToWrite;
            driveToWrite = m_db->removeStorage();
        }
        storagefile.close();

        QFile coolerfile("Cooler.JSON");
        if (!coolerfile.open(QIODevice::WriteOnly))
        {
            qCritical() << "Could not write file!";
            qCritical() << coolerfile.errorString();
            return 0;
        }
        cooler* coolerToWrite = m_db->removeCooler();
        while (coolerToWrite != nullptr)
        {
            // write to cooler filer
            delete coolerToWrite;
            coolerToWrite = m_db->removeCooler();
        }
        coolerfile.close();

        QFile casefile("Case.JSON");
        if (!casefile.open(QIODevice::WriteOnly))
        {
            qCritical() << "Could not write file!";
            qCritical() << casefile.errorString();
            return 0;
        }
        pcCase* caseToWrite = m_db->removeCase();
        while (caseToWrite != nullptr)
        {
            delete caseToWrite;
            caseToWrite = m_db->removeCase();
        }

        closeFiles();
        return true;
    }
};
