#include "../../include/Logic/compatibility.h"

Compatibility::Compatibility(QObject *parent)
    : QObject{parent}
{

}

bool Compatibility::testCompatibility(motherboard *mobo, CPU *cpu)
{
    QObject::connect(m_data, &dataHolder::cpuCompatibility, mobo, &motherboard::cpuCompatibility);
    m_data->testMoboCompatibility(cpu);
    QObject::disconnect(m_data, &dataHolder::cpuCompatibility, mobo, &motherboard::cpuCompatibility);
    bool fits = mobo->cpuFits();
    mobo->resetCPU();
    return fits;
}

bool Compatibility::testCompatibility(motherboard *mobo, RAM *ram)
{
    QObject::connect(m_data, &dataHolder::ramCompatibility, mobo, &motherboard::ramCompatibility);
    m_data->testMoboCompatibility(ram);
    QObject::disconnect(m_data, &dataHolder::ramCompatibility, mobo, &motherboard::ramCompatibility);
    bool fits = mobo->ramFits();
    mobo->resetRAM();
    return fits;
}

bool Compatibility::testCompatibility(motherboard *mobo, storage *storage)
{
    QObject::connect(m_data, &dataHolder::storageCompatibility, mobo, &motherboard::storageCompatibility);
    m_data->testMoboCompatibility(storage);
    QObject::disconnect(m_data, &dataHolder::storageCompatibility, mobo, &motherboard::storageCompatibility);
    bool fits = mobo->storageFits();
    mobo->resetStorage();
    return fits;
}

bool Compatibility::testCompatibility(motherboard *mobo, cooler *cooler)
{
    QObject::connect(m_data, &dataHolder::coolerCompatibility, mobo, &motherboard::coolerCompatibility);
    m_data->testMoboCompatibility(cooler);
    QObject::disconnect(m_data, &dataHolder::coolerCompatibility, mobo, &motherboard::coolerCompatibility);
    bool fits = mobo->coolerFits();
    mobo->resetCooler();
    return fits;
}

bool Compatibility::testCompatibility(pcCase *pcCase, motherboard *mobo)
{
    QObject::connect(m_data, &dataHolder::motherboardCompatibility, pcCase, &pcCase::motherboardCompatibility);
    m_data->testCaseCompatibility(mobo);
    QObject::disconnect(m_data, &dataHolder::motherboardCompatibility, pcCase, &pcCase::motherboardCompatibility);
    bool fits = pcCase->moboFits();
    pcCase->resetMobo();
    return fits;
}

bool Compatibility::testCompatibility(pcCase *pcCase, storage *storage)
{
    QObject::connect(m_data, &dataHolder::storageSpaceAvailable, pcCase, &pcCase::storageCompatibility);
    m_data->testCaseCompatibility(storage);
    QObject::disconnect(m_data, &dataHolder::storageSpaceAvailable, pcCase, &pcCase::storageCompatibility);
    bool fits = pcCase->storageFits();
    pcCase->resetStorage();
    return fits;
}

bool Compatibility::testCompatibility(pcCase *pcCase, GPU *gpu)
{
    QObject::connect(m_data, &dataHolder::gpuCompatibility, pcCase, &pcCase::gpuCompatibility);
    m_data->testCaseCompatibility(gpu);
    QObject::disconnect(m_data, &dataHolder::gpuCompatibility, pcCase, &pcCase::gpuCompatibility);
    bool fits = pcCase->gpuFits();
    pcCase->resetGPU();
    return fits;
}

bool Compatibility::testCompatibility(pcCase *pcCase, cooler *cooler)
{
    QObject::connect(m_data, &dataHolder::coolerCompatibility, pcCase, &pcCase::coolerCompatibility);
    m_data->testCaseCompatibility(cooler);
    QObject::disconnect(m_data, &dataHolder::coolerCompatibility, pcCase, &pcCase::coolerCompatibility);
    bool fits = pcCase->coolerFits();
    pcCase->resetCooler();
    return fits;
}

bool Compatibility::testCompatibility(PSU *psu, CPU *cpu, QList<GPU *> gpus)
{
    QObject::connect(m_data, &dataHolder::psuCompatibility, psu, &PSU::couldPower);
    m_data->testPSUCompatibility(cpu, gpus);
    QObject::disconnect(m_data, &dataHolder::psuCompatibility, psu, &PSU::couldPower);
    bool powers = psu->canPower();
    psu->resetPower();
    return powers;
}
