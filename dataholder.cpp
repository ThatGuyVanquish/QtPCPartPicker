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

    // Insert into core count QLists
    int cores = toInsert->getCores();
    if (cores > 16)
        cpuMap["Server"].push_back(toInsert);
    else
        cpuMap["PC"].push_back(toInsert);
    if (cores % 2 == 0 && 4 <= cores && cores <= 16)
        {
            cpuMap.find(to_string(cores) + " Cores").value().push_back(toInsert);
        }

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
    CPU* toRemove = cpuMap["Price"][0];
    if (toRemove == nullptr) return nullptr;
    cpuMap["Price"].pop_back();
    int cores = toRemove->getCores();
    QString manu = toRemove->getManu();
    // Erase from manufacturer QList
    manu == "Intel" ? eraseFrom(cpuMap["Intel"], toRemove) :
    eraseFrom(cpuMap["AMD"], toRemove);
    // Erase from core based QLists
    cores > 16 ? eraseFrom(cpuMap["Server"], toRemove) :
    eraseFrom(cpuMap["PC"], toRemove);
    switch (cores)
    {
        case 4:
            eraseFrom(cpuMap["4 Cores"], toRemove);
            break;
        case 6:
            eraseFrom(cpuMap["6 Cores"], toRemove);
            break;
        case 8:
            eraseFrom(cpuMap["8 Cores"], toRemove);
            break;
        case 10:
            eraseFrom(cpuMap["10 Cores"], toRemove);
            break;
        case 12:
            eraseFrom(cpuMap["12 Cores"], toRemove);
            break;
        case 14:
            eraseFrom(cpuMap["14 Cores"], toRemove);
            break;
        case 16:
            eraseFrom(cpuMap["16 Cores"], toRemove);
            break;
    }
    return toRemove;
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
    GPU* toRemove = gpuMap["Price"][0];
    if (toRemove == nullptr) return nullptr;
    gpuMap["Price"].pop_back();
    // Remove from manufacturer maps
    toRemove->getManu() == "Nvidia" ? eraseFrom(gpuMap["Nvidia"], toRemove) :
    toRemove->getManu() == "AMD" ? eraseFrom(gpuMap["AMD"], toRemove) :
    eraseFrom(gpuMap["Intel"], toRemove);
    // Remove from Ray Tracing map
    if (toRemove->hasRT())
        eraseFrom(gpuMap["Ray Tracing"], toRemove);
    // Remove from DLSS map
    if (toRemove->runsDLSS())
        eraseFrom(gpuMap["DLSS"], toRemove);
    return toRemove;
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
    motherboard* toRemove = moboMap["Price"][0];
    if (toRemove == nullptr) return nullptr;
    moboMap["Price"].pop_back();

    // Remove from CPU Manufacturer map
    toRemove->getCPUManufacturer() == "Intel" ? eraseFrom(moboMap["Intel"], toRemove) :
    eraseFrom(moboMap["AMD"], toRemove);

    // Remove from DDR map
    QString ddr = toRemove->getRAMVersion();
    ddr == "DDR3" ? eraseFrom(moboMap["DDR3"], toRemove) :
    ddr == "DDR4" ? eraseFrom(moboMap["DDR4"], toRemove) : eraseFrom(moboMap["DDR5"], toRemove);

    // Remove from purpose map
    auto iter = find(moboMap["Mining"].begin(), moboMap["Mining"].end(), toRemove);
    if (iter != moboMap["Mining"].end())
    {
        moboMap["Mining"].erase(iter);
        return toRemove;
    }
    iter = find(moboMap["Server"].begin(), moboMap["Server"].end(), toRemove);
    if (iter != moboMap["Server"].end())
    {
        moboMap["Server"].erase(iter);
        return toRemove;
    }
    iter = find(moboMap["Overclocking"].begin(), moboMap["Overclocking"].end(), toRemove);
    if (iter != moboMap["Overclocking"].end())
        moboMap["Overclocking"].erase(iter);
    return toRemove;
}

void dataHolder::addRAM(RAM* toInsert)
{
    // Map by DDR Version, sort by speed
    QString version = toInsert->getVersion();
    version == "DDR3" ? insertRAMBySpeed(ramMap["DDR3"], toInsert) :
    (version == "DDR4" ? insertRAMBySpeed(ramMap["DDR4"], toInsert) : insertRAMBySpeed(ramMap["DDR5"], toInsert));

    // Map by price
    int index = 0;
    for (RAM* current : ramMap["Price"])
    {
        if (toInsert->getPrice() >= current->getPrice())
            index++;
        else
        {
            ramMap["Price"].insert(ramMap["Price"].begin() + index, toInsert);
            break;
        }
    }
}

RAM* dataHolder::removeRAM()
{
    RAM* toRemove = ramMap["Price"][0];
    if (toRemove == nullptr) return nullptr;
    ramMap["Price"].pop_back();
    // Remove from DDR version based maps
    toRemove->getVersion() == "DDR3" ? eraseFrom(ramMap["DDR3"], toRemove) :
    toRemove->getVersion() == "DDR4" ? eraseFrom(ramMap["DDR4"], toRemove) :
    eraseFrom(ramMap["DDR5"], toRemove);
    return toRemove;
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
        {
            storageMap["Size"].insert(storageMap["Size"].begin() + index, toInsert);
            break;
        }
    }

    // Mapping by price
    index = 0;
    for (storage* drive : storageMap["Price"])
    {
        if (toInsert->getPrice() >= drive->getPrice())
            index++;
        else
        {
            storageMap["Price"].insert(storageMap["Price"].begin() + index, toInsert);
            break;
        }
    }
}

storage* dataHolder::removeStorage()
{
    storage* toRemove = storageMap["Price"][0];
    if (toRemove == nullptr) return nullptr;
    storageMap["Price"].pop_back();

    // Remove from port/type maps
    toRemove->getPort() == "M.2" ? eraseFrom(storageMap["M.2"], toRemove) :
    toRemove->getType() == "SSD" ? eraseFrom(storageMap["SSD"], toRemove) :
    eraseFrom(storageMap["HDD"], toRemove);

    // Remove from size map
    storageMap["Size"].erase(find(storageMap["Size"].begin(), storageMap["Size"].end(), toRemove));
    return toRemove;
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
        {
            coolerMap["TDP"].insert(coolerMap["TDP"].begin() + index, toInsert);
            break;
        }
    }

    // Mapping by price
    index = 0;
    for (cooler* current : coolerMap["Price"])
    {
        if (toInsert->getPrice() >= current->getPrice())
            index++;
        else
        {
            coolerMap["Price"].insert(coolerMap["Price"].begin() + index, toInsert);
            break;
        }
    }
}

cooler* dataHolder::removeCooler()
{
    cooler* toRemove = coolerMap["Price"][0];
    if (toRemove == nullptr) return nullptr;
    coolerMap["Price"].pop_back();

    // Remove from type based maps
    toRemove->getRadiatorSize() > 0 ? eraseFrom(coolerMap["AIO"], toRemove) :
    eraseFrom(coolerMap["Air"], toRemove);

    // Remove from TDP map
    eraseFrom(coolerMap["TDP"], toRemove);

    return toRemove;
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
        {
            caseMap["Volume"].insert(caseMap["Volume"].begin() + index, toInsert);
            break;
        }
    }

    // Mapping by price
    index = 0;
    for (pcCase* current : caseMap["Price"])
    {
        if (toInsert->getPrice() >= current->getPrice())
            index++;
        else
        {
            caseMap["Price"].insert(caseMap["Price"].begin() + index, toInsert);
            break;
        }
    }
}

pcCase* dataHolder::removeCase()
{
    pcCase* toRemove = caseMap["Price"][0];
    if (toRemove == nullptr) return nullptr;
    caseMap["Price"].pop_back();

    // Remove from mobo form factor based maps
    QStringList moboFF = toRemove->getMoboSupport();
    for (QString ff : moboFF)
    {
        ff == "ITX" ? eraseFrom(caseMap["ITX"], toRemove) :
        ff == "mATX" ? eraseFrom(caseMap["mATX"], toRemove) :
        ff == "ATX" ? eraseFrom(caseMap["ATX"], toRemove) :
        eraseFrom(caseMap["E-ATX"], toRemove);
    }

    // Remove from volume map
    eraseFrom(caseMap["Volume"], toRemove);

    return toRemove;
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
