#include "filereader.h"

fileReader::fileReader(QObject *parent)
    : QObject{parent}
{}

fileReader::fileReader(dataHolder *db):
    m_db(db),
    m_cpu("/home/nave/Documents/QtProjects/PCPartPicker/database/CPU.JSON"),
    m_gpu("/home/nave/Documents/QtProjects/PCPartPicker/database/GPU.JSON"),
    m_mobo("/home/nave/Documents/QtProjects/PCPartPicker/database/Motherboard.JSON"),
    m_ram("/home/nave/Documents/QtProjects/PCPartPicker/database/RAM.JSON"),
    m_storage("/home/nave/Documents/QtProjects/PCPartPicker/database/Storage.JSON"),
    m_case("/home/nave/Documents/QtProjects/PCPartPicker/database/Case.JSON"),
    m_cooler("/home/nave/Documents/QtProjects/PCPartPicker/database/Cooler.JSON")
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
    if (m_case.isOpen())
        m_case.close();
    else return;
    if (m_cooler.isOpen())
        m_cooler.close();
}

int fileReader::openFiles()
{
    if (!m_cpu.open(QIODevice::ReadWrite))
    {
        qCritical() << "Could not write to CPU file!";
        qCritical() << m_cpu.errorString();
        return -1;
    }

    if (!m_gpu.open(QIODevice::ReadWrite))
    {
        qCritical() << "Could not write to GPU file!";
        qCritical() << m_gpu.errorString();
        qInfo() << "Closing opened file";
        closeFiles();
        return -2;
    }

    if (!m_mobo.open(QIODevice::ReadWrite))
    {
        qCritical() << "Could not write to Motherboard file!";
        qCritical() << m_mobo.errorString();
        qInfo() << "Closing opened files";
        closeFiles();
        return -3;
    }

    if (!m_ram.open(QIODevice::ReadWrite))
    {
        qCritical() << "Could not write to RAM file!";
        qCritical() << m_ram.errorString();
        qInfo() << "Closing opened files";
        closeFiles();
        return -4;
    }

    if (!m_storage.open(QIODevice::ReadWrite))
    {
        qCritical() << "Could not write to Storage file!";
        qCritical() << m_storage.errorString();
        qInfo() << "Closing opened files";
        closeFiles();
        return -5;
    }

    if (!m_case.open(QIODevice::ReadWrite))
    {
        qCritical() << "Could not write to Case file!";
        qCritical() << m_case.errorString();
        qInfo() << "Closing opened files";
        closeFiles();
        return -6;
    }

    if (!m_cooler.open(QIODevice::ReadWrite))
    {
        qCritical() << "Could not write to Cooler file!";
        qCritical() << m_cooler.errorString();
        qInfo() << "Closing opened files";
        closeFiles();
        return -7;
    }

    return 1;
}

void fileReader::restoreCPUs()
{
    QJsonDocument doc = QJsonDocument::fromJson(m_cpu.readAll());
}
