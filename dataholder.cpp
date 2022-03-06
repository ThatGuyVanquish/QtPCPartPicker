#include "dataholder.h"

dataHolder::dataHolder(QObject *parent)
    : QObject{parent},
      cpuMap(),
      gpuMap(),
      moboMap(),
      ramMap(),
      storageMap(),
      caseMap(),
      coolerMap()
{}

dataHolder::~dataHolder(){};

// Logic to access database
void dataHolder::initialize()
{
    // CPU Map initialization
    cpuMap["Intel"] = QList<CPU*>({});
    cpuMap["AMD"] = QList<CPU*>({});
    cpuMap["4 Cores"] = QList<CPU*>({});
    cpuMap["6 Cores"] = QList<CPU*>({});
    cpuMap["8 Cores"] = QList<CPU*>({});
    cpuMap["10 Cores"] = QList<CPU*>({});
    cpuMap["12 Cores"] = QList<CPU*>({});
    cpuMap["14 Cores"] = QList<CPU*>({});
    cpuMap["16 Cores"] = QList<CPU*>({});
    cpuMap["Server"] = QList<CPU*>({});
    cpuMap["PC"] = QList<CPU*>({});
    cpuMap["Price"] = QList<CPU*>({});

    // GPU Map initialization
    gpuMap["Intel"] = QList<GPU*>({});
    gpuMap["AMD"] = QList<GPU*>({});
    gpuMap["Nvidia"] = QList<GPU*>({});
    gpuMap["Ray Tracing"] = QList<GPU*>({});
    gpuMap["DLSS"] = QList<GPU*>({});
    gpuMap["Price"] = QList<GPU*>({});

    // Motherboard Map initialization
    moboMap["Intel"] = QList<motherboard*>({});
    moboMap["AMD"] = QList<motherboard*>({});
    moboMap["DDR3"] = QList<motherboard*>({});
    moboMap["DDR4"] = QList<motherboard*>({});
    moboMap["DDR5"] = QList<motherboard*>({});
    moboMap["Server"] = QList<motherboard*>({});
    moboMap["Mining"] = QList<motherboard*>({});
    moboMap["Overclocking"] = QList<motherboard*>({});
    moboMap["Price"] = QList<motherboard*>({});

    // RAM Map initialization
    ramMap["DDR3"] = QList<RAM*>({});
    ramMap["DDR4"] = QList<RAM*>({});
    ramMap["DDR5"] = QList<RAM*>({});
    ramMap["Price"] = QList<RAM*>({});

    // Storage Map initialization
    storageMap["HDD"] = QList<storage*>({});
    storageMap["M.2"] = QList<storage*>({});
    storageMap["SSD"] = QList<storage*>({});
    storageMap["Size"] = QList<storage*>({});
    storageMap["Price"] = QList<storage*>({});

    // Cooler Map initialization
    coolerMap["AIO"] = QList<cooler*>({});
    coolerMap["Air"] = QList<cooler*>({});
    coolerMap["TDP"] = QList<cooler*>({});
    coolerMap["Price"] = QList<cooler*>({});
    // *** Would add socket based mapping but it might be too much right now, might add later ***

    // Case Map initialization
    caseMap["ITX"] = QList<pcCase*>({});
    caseMap["mATX"] = QList<pcCase*>({});
    caseMap["ATX"] = QList<pcCase*>({});
    caseMap["E-ATX"] = QList<pcCase*>({});
    caseMap["Volume"] = QList<pcCase*>({});
    caseMap["Price"] = QList<pcCase*>({});
}

void dataHolder::addCPU(CPU* toInsert)
{
    // Insert into manufacturer QLists
    toInsert->getManu() == "Intel" ? cpuMap["Intel"].push_back(toInsert) : cpuMap["AMD"].push_back(toInsert);

//    // Insert into core count QLists
//    int cores = toInsert->getCores();
//    if (cores > 16)
//        cpuMap["Server"].push_back(toInsert);
//    else
//        cpuMap["PC"].push_back(toInsert);
//    if (cores % 2 == 0 && 4 <= cores && cores <= 16)
//        {
//            cpuMap.find(to_string(cores) + " Cores").value().push_back(toInsert);
//        }

    // Insert into a QList which is sorted by price, by insertion sort
    int index = 0;
    for (CPU* current : cpuMap["Price"])
    {
        if (toInsert->getPrice() >= current->getPrice())
            index++;
        else
            break;
    }
    cpuMap["Price"].insert(cpuMap["Price"].begin() + index, toInsert);
}

CPU* dataHolder::removeCPU()
{
    if (cpuMap["Price"].isEmpty())
        return nullptr;
    CPU* toRemove = cpuMap["Price"].takeFirst();
    return toRemove;
}

void dataHolder::clearCPUMaps()
{
    cpuMap["Intel"].clear();
    cpuMap["AMD"].clear();
    cpuMap["4 Cores"].clear();
    cpuMap["6 Cores"].clear();
    cpuMap["8 Cores"].clear();
    cpuMap["10 Cores"].clear();
    cpuMap["12 Cores"].clear();
    cpuMap["14 Cores"].clear();
    cpuMap["16 Cores"].clear();
    cpuMap["Server"].clear();
    cpuMap["PC"].clear();
    cpuMap["Price"].clear();
}

void dataHolder::addGPU(GPU* toInsert)
{
    // Insert into manufacturer QLists
    toInsert->getManu() == "Nvidia" ? gpuMap["Nvidia"].push_back(toInsert) :
    toInsert->getManu() == "AMD" ? gpuMap["AMD"].push_back(toInsert) : gpuMap["Intel"].push_back(toInsert);

    //Insert into RT/DLSS
    if (toInsert->runsDLSS())
        gpuMap["DLSS"].push_back(toInsert);
    if (toInsert->hasRT())
        gpuMap["Ray Tracing"].push_back(toInsert);

    // Insert into a QList which is sorted by price, by insertion sort
    int index = 0;
    for (GPU* current : gpuMap["Price"])
    {
        if (toInsert->getPrice() >= current->getPrice())
            index++;
        else
            break;
    }
    gpuMap["Price"].insert(gpuMap["Price"].begin() + index, toInsert);
}

GPU* dataHolder::removeGPU()
{
    if (gpuMap["Price"].isEmpty())
        return nullptr;
    GPU* toRemove = gpuMap["Price"].takeFirst();
    return toRemove;
}

void dataHolder::clearGPUMaps()
{
    gpuMap["Intel"].clear();
    gpuMap["AMD"].clear();
    gpuMap["Nvidia"].clear();
    gpuMap["Ray Tracing"].clear();
    gpuMap["DLSS"].clear();
    gpuMap["Price"].clear();
}

void dataHolder::addMotherboard(motherboard* toInsert, string purpose)
{
    // Mapping by CPU manufacturer
    toInsert->getCPUManufacturer() == "Intel" ? moboMap["Intel"].push_back(toInsert) : moboMap["AMD"].push_back(toInsert);
    if (!purpose.empty())
        toLower(purpose);
        purpose == "mining" ? moboMap["Mining"].push_back(toInsert) : (purpose == "server" ? moboMap["Server"].push_back(toInsert) : moboMap["Overclocking"].push_back(toInsert));

    // Mapping to ram slot version
    toInsert->getRAMVersion() == "DDR3" ? moboMap["DDR3"].push_back(toInsert) : (toInsert->getRAMVersion() == "DDR4" ?
    moboMap["DDR4"].push_back(toInsert) : moboMap["DDR5"].push_back(toInsert));

    // Mapping by price
    int index = 0;
    for (motherboard* current : moboMap["Price"])
    {
        if (toInsert->getPrice() >= current->getPrice())
            index++;
        else
            break;
    }
    moboMap["Price"].insert(moboMap["Price"].begin() + index, toInsert);
}

motherboard* dataHolder::removeMobo()
{
    if (moboMap["Price"].isEmpty()) return nullptr;
    motherboard* toRemove = moboMap["Price"].takeFirst();
    return toRemove;
}

void dataHolder::clearMoboMaps()
{
    moboMap["Intel"].clear();
    moboMap["AMD"].clear();
    moboMap["DDR3"].clear();
    moboMap["DDR4"].clear();
    moboMap["DDR5"].clear();
    moboMap["Server"].clear();
    moboMap["Mining"].clear();
    moboMap["Overclocking"].clear();
    moboMap["Price"].clear();
}

void dataHolder::addRAM(RAM* toInsert)
{
    // Map by DDR Version, sort by speed
    QString version = toInsert->getVersion();
    version == "DDR3" ? insertRAMBySpeed(ramMap["DDR3"], toInsert) :
    (version == "DDR4" ? insertRAMBySpeed(ramMap["DDR4"], toInsert) : insertRAMBySpeed(ramMap["DDR5"], toInsert));

    // Map by price
    int index = 0;
    if (ramMap["Price"].isEmpty())
        ramMap["Price"].append(toInsert);

    for (RAM* current : ramMap["Price"])
    {
        if (toInsert->getPrice() >= current->getPrice())
            index++;
        else
            break;
    }
    ramMap["Price"].insert(ramMap["Price"].begin() + index, toInsert);
}

RAM* dataHolder::removeRAM()
{
    if (ramMap["Price"].isEmpty())
        return nullptr;
    RAM* toRemove = ramMap["Price"].takeFirst();
    return toRemove;
}

void dataHolder::clearRAMMaps()
{
    ramMap["DDR3"].clear();
    ramMap["DDR4"].clear();
    ramMap["DDR5"].clear();
    ramMap["Price"].clear();
}

void dataHolder::addStorage(storage* toInsert)
{
    // Mapping by type
    toInsert->getPort() == "M.2" ? storageMap["M.2"].push_back(toInsert) :
    (toInsert->getType() == "ssd" ? storageMap["SSD"].push_back(toInsert) : storageMap["HDD"].push_back(toInsert));

    // Mapping by size
    int index = 0;
    for (storage* drive : storageMap["Size"])
    {
        if (toInsert->getSize() >= drive->getSize())
            index++;
        else
            break;
    }
    storageMap["Size"].insert(storageMap["Size"].begin() + index, toInsert);

    // Mapping by price
    index = 0;
    for (storage* drive : storageMap["Price"])
    {
        if (toInsert->getPrice() >= drive->getPrice())
            index++;
        else
            break;
    }
    storageMap["Price"].insert(storageMap["Price"].begin() + index, toInsert);
}

storage* dataHolder::removeStorage()
{
    if (storageMap["Price"].isEmpty())
        return nullptr;
    storage* toRemove = storageMap["Price"].takeFirst();
    return toRemove;
}

void dataHolder::clearStorageMaps()
{
    storageMap["HDD"].clear();
    storageMap["M.2"].clear();
    storageMap["SSD"].clear();
    storageMap["Size"].clear();
    storageMap["Price"].clear();
}

void dataHolder::addCooler(cooler* toInsert)
{
    // Mapping by type
    toInsert->getRadiatorSize() > 0 ? coolerMap["AIO"].push_back(toInsert) : coolerMap["Air"].push_back(toInsert);

    // Mapping by cooling potency
    int index = 0;
    for (cooler* current : coolerMap["TDP"])
    {
        if (toInsert->getTDP() >= current->getTDP())
            index++;
        else
            break;
    }
    coolerMap["TDP"].insert(coolerMap["TDP"].begin() + index, toInsert);

    // Mapping by price
    index = 0;
    for (cooler* current : coolerMap["Price"])
    {
        if (toInsert->getPrice() >= current->getPrice())
            index++;
        else
            break;
    }
    coolerMap["Price"].insert(coolerMap["Price"].begin() + index, toInsert);
}

cooler* dataHolder::removeCooler()
{
    if (coolerMap["Price"].isEmpty())
        return nullptr;
    cooler* toRemove = coolerMap["Price"].takeFirst();
    return toRemove;
}

void dataHolder::clearCoolerMaps()
{
    coolerMap["AIO"].clear();
    coolerMap["Air"].clear();
    coolerMap["TDP"].clear();
    coolerMap["Price"].clear();
}

void dataHolder::addCase(pcCase* toInsert)
{
    // Mapping by motherboard support
    QStringList moboFFs = toInsert->getMoboSupport();
    for (QString mobo : moboFFs)
    {
        mobo == "ITX" ? caseMap["ITX"].push_back(toInsert) :
        mobo == "mATX" ? caseMap["mATX"].push_back(toInsert) :
        mobo == "ATX" ? caseMap["ATX"].push_back(toInsert) :
        caseMap["E-ATX"].push_back(toInsert);
    }

    // Mapping by volume
    int vol = toInsert->calculateCaseVolume();
    int index = 0;
    for (pcCase* current : caseMap["Volume"])
    {
        if (vol >= current->calculateCaseVolume())
            index++;
        else
            break;
    }
    caseMap["Volume"].insert(caseMap["Volume"].begin() + index, toInsert);

    // Mapping by price
    index = 0;
    for (pcCase* current : caseMap["Price"])
    {
        if (toInsert->getPrice() >= current->getPrice())
            index++;
        else
            break;
    }
    caseMap["Price"].insert(caseMap["Price"].begin() + index, toInsert);
}

pcCase* dataHolder::removeCase()
{
    if (caseMap["Price"].isEmpty())
        return nullptr;
    pcCase* toRemove = caseMap["Price"].takeFirst();
    return toRemove;
}

void dataHolder::clearCaseMaps()
{
    caseMap["ITX"].clear();
    caseMap["mATX"].clear();
    caseMap["ATX"].clear();
    caseMap["E-ATX"].clear();
    caseMap["Volume"].clear();
    caseMap["Price"].clear();
}

void dataHolder::testMoboCompatibility(CPU *cpu)
{
    emit cpuCompatibility(cpu);
}

void dataHolder::testMoboCompatibility(RAM *ram)
{
    emit ramCompatibility(ram);
}

void dataHolder::testMoboCompatibility(cooler *cooler)
{
    emit coolerCompatibility(cooler);
}

void dataHolder::testMoboCompatibility(storage *storage)
{
    emit storageCompatibility(storage);
}

void dataHolder::testCaseCompatibility(motherboard *mobo)
{
    emit motherboardCompatibility(mobo);
}

void dataHolder::testCaseCompatibility(storage *storage)
{
    emit storageSpaceAvailable(storage);
}

void dataHolder::testCaseCompatibility(GPU *gpu)
{
    emit gpuCompatibility(gpu);
}

void dataHolder::testCaseCompatibility(cooler *cooler)
{
    emit coolerSpaceAvailable(cooler);
}
