#include "../../include/Database/dataholder.h"

QList<GPU *> dataHolder::findGPUs(int budget, int caseSlots, int maxLength, int maxHeight, int moboSlots,
                                  int wattage, QList<GPU *> gpuList, int index)
{
    if (budget < 0 || caseSlots < 0 || moboSlots < 0 || wattage < 0)
    {
        gpuList.pop_back();
        return gpuList;
    }
    if (index >= gpuMap["Price"].size() || caseSlots == 0 || moboSlots == 0 || wattage == 0)
        return gpuList;
    // We either pick this one or skip it
    GPU *currentGPU = gpuMap["Price"].at(gpuMap["Price"].size() - 1 - index);
    // Check if the current GPU fits within our case and power limitations
    if (currentGPU->getLength() > maxLength || currentGPU->getHeight() > maxHeight || currentGPU->getTDP() > wattage)
        return findGPUs(budget, caseSlots, maxLength, maxHeight,
                        moboSlots, wattage, gpuList, index + 1);

    // If it does, choose whether to use it or not to use it:
    // Pick this gpu:
    gpuList.append(currentGPU);
    QList<GPU*> list1 = findGPUs(budget - currentGPU->getPrice(), caseSlots - currentGPU->getSlots(), maxLength, maxHeight,
            moboSlots - 1, wattage - currentGPU->getTDP(), gpuList, index);
    int l1Wattage = 0;
    int l1Change = budget;
    foreach(GPU *gpu, list1)
    {
        l1Wattage += gpu->getTDP();
        l1Change -= gpu->getPrice();
    }
    // Skip this gpu:
    gpuList.pop_back();
    QList<GPU*> list2 = findGPUs(budget, caseSlots, maxLength, maxHeight,
            moboSlots, wattage, gpuList, index + 1);
    int l2Wattage = 0;
    int l2Change = budget;
    foreach(GPU *gpu, list2)
    {
        l2Wattage += gpu->getTDP();
        l2Change -= gpu->getPrice();
    }

    if (l1Wattage > l2Wattage || (l1Wattage == l2Wattage && l1Change > l2Change))
        return list1;
    return list2;
}

QList<storage *> dataHolder::findHDDs(int budget, int slotLimit, QList<storage*> list, int index)
{
    if (budget < 0 || slotLimit < 0)
    {
        list.pop_back();
        return list;
    }
    if (index >= storageMap["Price"].size() || slotLimit == 0)
        return list;

    // We either pick this one or skip it
    storage *hdd = storageMap["Price"].at(storageMap["Price"].size() - 1 - index);

    // Check if it's a hard drive or something else:
    if (hdd->getType() != "hdd")
        return findHDDs(budget, slotLimit, list, index + 1);

    // We pick this hdd:
    list.append(hdd);
    int l1Size = 0;
    int l1Cost = 0;
    QList<storage*> list1 = findHDDs(budget - hdd->getPrice(), slotLimit - 1, list, index);
    foreach(storage *drive, list1)
    {
        l1Size += drive->getSizeNum();
        l1Cost += drive->getPrice();
    }

    // We skip this hdd:
    list.pop_back();
    int l2Size = 0;
    int l2Cost = 0;
    QList<storage*> list2 = findHDDs(budget, slotLimit, list, index + 1);
    foreach(storage *drive, list2)
    {
        l2Size += drive->getSizeNum();
        l2Cost += drive->getPrice();
    }

    if (l1Size > l2Size || (l1Size == l2Size && l1Cost < l2Cost))
        return list1;
    return list2;
}

dataHolder::dataHolder(QString dir, QObject *parent)
    : QObject{parent},
      m_dbDirectory(dir),
      cpuMap(),
      gpuMap(),
      moboMap(),
      ramMap(),
      storageMap(),
      caseMap(),
      coolerMap()
{}

dataHolder::~dataHolder(){};

QString dataHolder::getDir()
{
    return m_dbDirectory;
}

QMap<QString, QList<CPU *> > *dataHolder::CPUMap()
{
    return &cpuMap;
}

QMap<QString, QList<GPU *> > *dataHolder::GPUMap()
{
    return &gpuMap;
}

QMap<QString, QList<motherboard *> > *dataHolder::MOBOMap()
{
    return &moboMap;
}

QMap<QString, QList<RAM *> > *dataHolder::RAMMap()
{
    return &ramMap;
}

QMap<QString, QList<cooler *> > *dataHolder::COOLERMap()
{
    return &coolerMap;
}

QMap<QString, QList<PSU *> > *dataHolder::PSUMap()
{
    return &psuMap;
}

QMap<QString, QList<storage *> > *dataHolder::STORAGEMap()
{
    return &storageMap;
}

QMap<QString, QList<pcCase *> > *dataHolder::CASEMap()
{
    return &caseMap;
}


template<typename T>
void insertByPrice(QList<T*> *lst, T *toInsert)
{
    int index = 0;
    if (lst->isEmpty())
    {
        lst->append(toInsert);
        return;
    }

    for (T* current : *lst)
    {
        if (toInsert->getPrice() >= current->getPrice())
            index++;
        else
            break;
    }
    lst->insert(lst->begin() + index, toInsert);
}

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

    // PSU Map initialization
    psuMap["Low W"] = QList<PSU*>({});
    psuMap["Mid W"] = QList<PSU*>({});
    psuMap["High W"] = QList<PSU*>({});
    psuMap["SFF"] = QList<PSU*>({});
    psuMap["ATX"] = QList<PSU*>({});
    psuMap["Server"] = QList<PSU*>({});
    psuMap["Price"] = QList<PSU*>({});

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
    switch (cores)
    {
        case 4:
        {
            cpuMap["4 Cores"].push_back(toInsert);
            break;
        }
        case 6:
        {
            cpuMap["6 Cores"].push_back(toInsert);
            break;
        }
        case 8:
        {
            cpuMap["8 Cores"].push_back(toInsert);
            break;
        }
        case 10:
        {
            cpuMap["10 Cores"].push_back(toInsert);
            break;
        }
        case 12:
        {
            cpuMap["12 Cores"].push_back(toInsert);
            break;
        }
        case 14:
        {
            cpuMap["14 Cores"].push_back(toInsert);
            break;
        }
        case 16:
        {
            cpuMap["16 Cores"].push_back(toInsert);
            break;
        }
    }

    // Insert into a QList which is sorted by price
    insertByPrice(&cpuMap["Price"], toInsert);
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

    // Insert into a QList which is sorted by price
    insertByPrice(&gpuMap["Price"], toInsert);
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
    {
        purpose = (QString::fromStdString(purpose).toLower()).toStdString();
        purpose == "mining" ? moboMap["Mining"].push_back(toInsert) : (purpose == "server" ? moboMap["Server"].push_back(toInsert) : moboMap["Overclocking"].push_back(toInsert));
    }
    else
    {
        if (toInsert->getSATASlots() > 10)
            moboMap["Server"].push_back(toInsert);
        if (toInsert->getPCIeSlots() > 6)
            moboMap["Mining"].push_back(toInsert);
    }
    // Mapping to ram slot version
    toInsert->getRAMVersion() == "DDR3" ? moboMap["DDR3"].push_back(toInsert) : (toInsert->getRAMVersion() == "DDR4" ?
    moboMap["DDR4"].push_back(toInsert) : moboMap["DDR5"].push_back(toInsert));

    // Mapping by price
    insertByPrice(&moboMap["Price"], toInsert);
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
    version == "DDR3" ? insertRAMBySpeed(&ramMap["DDR3"], toInsert) :
    (version == "DDR4" ? insertRAMBySpeed(&ramMap["DDR4"], toInsert) : insertRAMBySpeed(&ramMap["DDR5"], toInsert));

    // Map by price
    insertByPrice(&ramMap["Price"], toInsert);
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
    insertByPrice(&storageMap["Price"], toInsert);
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
    insertByPrice(&coolerMap["Price"], toInsert);
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

void dataHolder::addPSU(PSU *toInsert)
{
    // Mapping by wattage
    toInsert->getWattage() <= 600 ? insertPSUByWattage(&psuMap["Low W"], toInsert) :
    toInsert->getWattage() <= 1000 ? insertPSUByWattage(&psuMap["Mid W"], toInsert) :
    insertPSUByWattage(&psuMap["High W"], toInsert);

    // Mapping by form factor
    toInsert->getFormFactor() == "SFF" ? psuMap["SFF"].append(toInsert) :
    toInsert->getFormFactor() == "ATX" ? psuMap["ATX"].append(toInsert) :
    psuMap["Server"].append(toInsert);

    // Mapping by price
    insertByPrice(&psuMap["Price"], toInsert);
}

PSU* dataHolder::removePSU()
{
    if (psuMap["Price"].isEmpty())
        return nullptr;
    PSU* toRemove = psuMap["Price"].takeFirst();
    return toRemove;
}

void dataHolder::clearPSUMaps()
{
    psuMap["Low W"].clear();
    psuMap["Mid W"].clear();
    psuMap["High W"].clear();
    psuMap["SFF"].clear();
    psuMap["ATX"].clear();
    psuMap["Server"].clear();
    psuMap["Price"].clear();
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
    insertByPrice(&caseMap["Price"], toInsert);
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

void dataHolder::clearMaps()
{
    clearCPUMaps();
    clearGPUMaps();
    clearMoboMaps();
    clearRAMMaps();
    clearCoolerMaps();
    clearPSUMaps();
    clearStorageMaps();
    clearCaseMaps();
}

CPU *dataHolder::findCPU(int budget, QString manu, QString socket, QString purpose)
{
    if (budget < 0)
        return nullptr;
    if (purpose == "mining")
    {
        foreach(CPU *cpu, cpuMap["Price"])
        {
            if (cpu->getPrice() > budget)
                return nullptr;
            if (cpu->getManu().toLower() == manu.toLower() && cpu->getSocket().toLower() == socket.toLower())
                return cpu;
        }
    }
    if (purpose == "server")
    {
        for(int i = cpuMap["Price"].size() - 1; i >= 0; i--)
        {
            CPU *currentCPU = cpuMap["Price"].at(i);
            if (currentCPU->getPrice() > budget)
                continue;
            if (currentCPU->getManu().toLower() == manu.toLower())
            {
                if (manu.toLower() == "amd")
                {
                    if (currentCPU->getSocket() == "EP1" || currentCPU->getSocket() == "EP2")
                        return currentCPU;
                    else continue;
                }
                if (manu.toLower() == "intel")
                {
                    if (currentCPU->getSocket() == "IN1" || currentCPU->getSocket() == "IN2")
                        return currentCPU;
                    else continue;
                }
            }
        }
    }

    if (purpose == "office")
    {
        QList<CPU*> fastest; // Compared based on
        foreach(CPU *currentCPU, cpuMap["Price"])
        {
            if (currentCPU == nullptr || currentCPU->getPrice() > budget)
                break;
            if (currentCPU->getManu().toLower() == manu.toLower())
            {
                if (fastest.size() < 5)
                    fastest.append(currentCPU);
                else
                {
                    CPU *slowest = currentCPU;
                    int toRemoveIndex = 0;
                    for(int i = 0; i < 5; i++)
                        if (slowest > fastest.at(i))
                        {
                            toRemoveIndex = i;
                            slowest = fastest.at(i);
                        }
                    fastest.replace(toRemoveIndex, currentCPU);
                }
            }
        }
        for(int i = fastest.size() - 1; i >= 0; i--)
            if (fastest.at(i)->hasGraphics())
                return fastest.at(i);
        if (gpuMap["Price"].size() == 0)
            return nullptr;
        int cpuBudget = budget - gpuMap["Price"].at(0)->getPrice();
        for(int i = fastest.size() - 1; i >= 0; i--)
            if (fastest.at(i)->getPrice() <= cpuBudget)
                return fastest.at(i);
    }

    if (purpose == "gaming")
    {
        CPU *fastest = nullptr;
        foreach(CPU *currentCPU, cpuMap["Price"])
        {
            //cout << "testing cpu " + currentCPU->getModel().toStdString() << endl;
            if (currentCPU == nullptr)
                return fastest;
            if (currentCPU->getPrice() > budget)
                return fastest;
            if (currentCPU->getManu().toLower() == manu.toLower())
            {
                if (fastest == nullptr)
                    fastest = currentCPU;
                else
                    fastest = currentCPU > fastest ? currentCPU : fastest;
            }
        }
        return fastest;
    }
    return nullptr;
}

QList<GPU *> dataHolder::findGPUs(int budget, QString purpose, int caseSlots, int maxLength, int maxHeight,
                                  int moboSlots, int wattage)
{
    QList<GPU*> ret;
    if (budget < 0 || moboSlots == 0)
        return ret;
    if (purpose == "mining")
        return findGPUs(budget, caseSlots, maxLength, maxHeight, moboSlots, wattage, ret, 0);
    // Purpose is gaming as office and server don't use findGPUs
    for (int i = gpuMap["Price"].size() - 1; i >= 0; i--)
    {
        if (gpuMap["Price"].at(i)->getPrice() <= budget)
        {
            ret.append(gpuMap["Price"].at(i));
            return ret;
        }
    }
    return ret;
}

motherboard *dataHolder::findMobo(int budget, QString manu, QString socket, QString purpose)
{
    if (budget < 0)
        return nullptr;
    if (purpose == "mining")
    {
        motherboard *ret = nullptr;
        foreach(motherboard *mobo, moboMap["Mining"])
        {
            if (mobo == nullptr)
                return ret;
            if (mobo->getPrice() > budget)
                continue;

            if (mobo->getCPUManufacturer().toLower() == manu.toLower())
            {
                if (ret == nullptr || mobo->getPCIeSlots() > ret->getPCIeSlots())
                    ret = mobo;
            }
        }
        return ret;
    }
    motherboard *ret = nullptr; // Works for the 3 other spec options as they all have param socket NOTNULL
    foreach(motherboard *mobo, moboMap["Price"])
    {
        if (mobo == nullptr || mobo->getPrice() > budget)
            return ret;
        if (mobo->getCPUManufacturer().toLower() == manu.toLower() &&
                mobo->getSocket() == socket)
        {
            if (purpose == "server" && !moboMap["Server"].contains(mobo))
                continue;
            if (ret == nullptr)
                ret = mobo;
            else if (mobo->getPrice() > ret->getPrice())
                ret = mobo;
        }
    }
    return ret;
}

RAM *dataHolder::findRAM(int budget, bool cheapest, QString version)
{
    if (budget < 0)
        return nullptr;
    RAM *ret = nullptr;
    foreach(RAM *ram, ramMap["Price"])
    {
        if (ram->getPrice() > budget)
            return ret;
        if (ram->getVersion() == version)
        {
            if (cheapest)
                return ram;
            else
                ret = ram;
        }
    }
    return ret;
}

cooler *dataHolder::findCooler(int budget, QString socket, int TDP)
{
    if (budget < 0)
        return nullptr;
    foreach(cooler *cooler, coolerMap["Price"])
    {
        if (cooler->getPrice() > budget)
            return nullptr;
        if (cooler->canMount(socket) && cooler->canCool(TDP))
            return cooler;
    }
    return nullptr;
}

PSU *dataHolder::findPSU(int budget, QString purpose, int wattage)
{
    if (budget < 0)
        return nullptr;
    PSU *ret = nullptr;
    foreach(PSU *psu, psuMap["Price"])
    {
        if (psu->getPrice() > budget)
            return ret;
        if ((purpose == "mining" && psu->getFormFactor() != "Server") ||
                (purpose == "server" && psu->getFormFactor() == "Server"))
        {
            if (ret == nullptr || psu->getUsableWattage() > ret->getUsableWattage())
                ret = psu;
        }

        else if (purpose != "server" && purpose != "mining")
            if (psu->getFormFactor() != "Server" && psu->getUsableWattage() > wattage)
                return psu;
    }
    return ret;
}

QList<storage *> dataHolder::findStorage(int budget, QString purpose, pcCase *pcCase, motherboard *mobo)
{
    QList<storage*> ret;
    if (budget < 0 || (mobo->getM2Slots() == 0 &&
                        (mobo->getSATASlots() == 0 || (pcCase->getHDDSlots() == 0 && pcCase->getSSDSlots() == 0))))
        return ret;
    if (purpose == "office")
    {
        int remaining = budget;
        storage *m2ToInsert = nullptr;
        if (mobo->getM2Slots() > 0)
        {
            foreach(storage *m2, storageMap["M.2"])
            {
                if (m2->getPrice() <= budget / 3)
                {
                    if (!m2ToInsert || m2->getSizeNum() > m2ToInsert->getSizeNum())
                        m2ToInsert = m2;
                }
            }
            if (m2ToInsert)
            {
                ret.append(m2ToInsert);
                remaining -= m2ToInsert->getPrice();
            }
        }
        if (!m2ToInsert)
        {
            storage *sataSSDToInsert = nullptr;
            if (mobo->getSATASlots() > 1 && (pcCase->getSSDSlots() > 0 || pcCase->getHDDSlots() > 1))
            {
                storage *cheapest = storageMap["SSD"].at(0);
                foreach(storage *ssd, storageMap["SSD"])
                {
                    if (ssd->getPrice() <= budget / 3)
                    {
                        if (!sataSSDToInsert || ssd->getSizeNum() > sataSSDToInsert->getSizeNum())
                            sataSSDToInsert = ssd;
                    }
                    if (ssd->getPrice() < cheapest->getPrice() ||
                            (ssd->getPrice() == cheapest->getPrice() && ssd->getSizeNum() > cheapest->getSizeNum()))
                        cheapest = ssd;
                }
                if (sataSSDToInsert)
                {
                    ret.append(sataSSDToInsert);
                    remaining -= sataSSDToInsert->getPrice();
                }
                else if (cheapest->getPrice() <= budget)
                {
                    ret.append(cheapest);
                    remaining -= cheapest->getPrice();
                }
            }
        }
        // Either there is an ssd or there isn't, doesn't matter - get the largest HDD possible
        storage *hddToInsert = nullptr;
        foreach(storage* hdd, storageMap["HDD"])
        {
            if (hdd->getPrice() <= remaining)
            {
                if (!hddToInsert || hdd->getSizeNum() > hddToInsert->getSizeNum())
                    hddToInsert = hdd;
            }
        }
        if (hddToInsert)
            ret.append(hddToInsert);
        return ret;
    }
    else if (purpose == "gaming")
    {
        int remaining = budget;
        storage *m2ToInsert = nullptr;
        foreach(storage *m2, storageMap["M.2"])
        {
            if (mobo->getM2Slots() == 0)
                break;
            if (m2->getPrice() <= budget / 2)
            {
                if (!m2ToInsert || m2->getSizeNum() > m2ToInsert->getSizeNum())
                    m2ToInsert = m2;
            }
        }
        if (m2ToInsert)
        {
            ret.append(m2ToInsert);
            remaining -= m2ToInsert->getPrice();
        }
        else // Couldn't find an M.2 within the budget
        {
            if (mobo->getSATASlots() == 0)
            {
                ret.clear();
                return ret;
            }
            storage *ssdToInsert = nullptr;
            storage *biggestSSD = nullptr;
            foreach(storage *ssd, storageMap["SSD"])
            {
                if (ssd->getPrice() <= budget / 2)
                {
                    if (!ssdToInsert || ssd->getSizeNum() > ssdToInsert->getSizeNum())
                        ssdToInsert = ssd;
                }
                if (ssd->getPrice() <= budget)
                {
                    if (!biggestSSD || ssd->getSizeNum() > biggestSSD->getSizeNum())
                        biggestSSD = ssd;
                }
            }
            if (ssdToInsert)
            {
                ret.append(ssdToInsert);
                remaining -= ssdToInsert->getPrice();
            }
            else if (biggestSSD)
            {
                ret.append(biggestSSD);
                return ret;
            }
            else
            {
                ret.clear();
                return ret;
            }
        }
        if (remaining > 0 && (ret.at(0)->getPort() == "M.2" || mobo->getSATASlots() > 1))
        {
            storage *hddToInsert = nullptr;
            foreach(storage *hdd, storageMap["HDD"])
            {
                if (hdd->getPrice() <= remaining)
                {
                    if (!hddToInsert || hdd->getSizeNum() > hddToInsert->getSizeNum())
                        hddToInsert = hdd;
                }
            }
            if (hddToInsert)
                ret.append(hddToInsert);
        }
        return ret;
    }
    else if (purpose == "server")
    {
        int hddSlots = pcCase->getHDDSlots();
        int sataSlots = mobo->getSATASlots();
        int remaining = budget;
        int ssdBudget = budget * 0.05;
        storage *m2ToInsert = nullptr;
        storage *cheapestM2 = storageMap["M.2"].at(0);
        if (mobo->getM2Slots() > 0 && storageMap["M.2"].size() > 0) // Case motherboard has M.2 Slot
        {

            foreach(storage *m2, storageMap["M.2"])
            {
                if (m2->getPrice() <= ssdBudget)
                {
                    if (!m2ToInsert || m2->getSizeNum() > m2ToInsert->getSizeNum())
                        m2ToInsert = m2;
                }
                if (m2->getPrice() <= budget)
                {
                    if (m2->getPrice() < cheapestM2->getPrice())
                        cheapestM2 = m2;
                }
            }
        }
        if (m2ToInsert)
        {
            ret.append(m2ToInsert);
            remaining -= m2ToInsert->getPrice();
        }
        else // Can't fit an m.2 within 5% of the budget
        {
            storage *ssdToInsert = nullptr;
            storage *cheapestSSD = storageMap["SSD"].at(0);
            foreach(storage *ssd, storageMap["SSD"])
            {
                if (ssd->getPrice() <= ssdBudget)
                {
                    if (!ssdToInsert || ssd->getSizeNum() > ssdToInsert->getSizeNum())
                        ssdToInsert = ssd;
                }
                if (ssd->getPrice() <= budget)
                {
                    if (ssd->getPrice() < cheapestSSD->getPrice())
                        cheapestSSD = ssd;
                }
            }
            if (ssdToInsert) // Can fit a SATA SSD within 5% of the budget
            {
                ret.append(ssdToInsert);
                remaining -= ssdToInsert->getPrice();
                sataSlots--;
            }
            else if (mobo->getM2Slots() > 0) // If not, fit the cheapest M.2 SSD if possible
            {
                ret.append(cheapestM2);
                remaining -= cheapestM2->getPrice();
            }
            else if (cheapestSSD->getPrice() <= budget) // If not, fit the cheapest SATA SSD if possible
            {
                if (pcCase->getSSDSlots() > 0)
                {
                    ret.append(cheapestSSD);
                    remaining -= cheapestSSD->getPrice();
                    sataSlots--;
                }
                else if (hddSlots > 0)
                {
                    ret.append(cheapestSSD);
                    remaining -= cheapestSSD->getPrice();
                    hddSlots--;
                    sataSlots--;
                }
                else
                {
                    ret.clear();
                    return ret;
                }
            }
            else
            {
                ret.clear();
                return ret;
            }
        }
        // Fit the largest size of HDDs possible:
        QList<storage*> hdds;
        int slotLimit = min(hddSlots, sataSlots);
        hdds = findHDDs(remaining, slotLimit, hdds, 0);
        foreach(storage* hdd, hdds)
            ret.append(hdd);
        return ret;
    }
    return ret;
}

pcCase *dataHolder::findCase(int budget, QString purpose, motherboard *mobo, QList<GPU *> gpus, cooler *cooler)
{
    if (budget < 0)
        return nullptr;
    pcCase *ret = nullptr;
    foreach(pcCase *pcCase, caseMap["Price"])
    {
        if (pcCase->getPrice() > budget)
            return ret;
        if (purpose == "mining")
        {
            if (pcCase->fitsCooler(cooler) && pcCase->fitsMobo(mobo))
                if (ret == nullptr || pcCase->getExpansionSlots() > ret->getExpansionSlots())
                    ret = pcCase;
        }

        if (purpose == "server")
        {
            if (pcCase->fitsCooler(cooler) && pcCase->fitsMobo(mobo))
            {
                if (ret == nullptr || pcCase->getHDDSlots() > ret->getHDDSlots())
                    ret = pcCase;
            }
        }

        if (purpose == "office" || purpose == "gaming")
            if (pcCase->fitsCooler(cooler) && pcCase->fitsMobo(mobo))
            {
                if (gpus.size() == 0 || pcCase->fitsGPU(gpus.at(0)))
                    return pcCase;
            }
    }
    return ret;
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

void dataHolder::testPSUCompatibility(CPU *cpu, QList<GPU *> gpus)
{
    emit psuCompatibility(cpu, gpus);
}
