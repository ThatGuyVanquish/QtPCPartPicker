#ifndef DATAHOLDER_H
#define DATAHOLDER_H

#include "CPU.h"
#include "GPU.h"
#include "intelCPU.h"
#include "intelGPU.h"
#include "amdCPU.h"
#include "amdGPU.h"
#include "nvidiaGPU.h"
#include "motherboard.h"
#include "RAM.h"
#include "storage.h"
#include "hdd.h"
#include "sataSSD.h"
#include "m2SSD.h"
#include "pcCase.h"
#include "cooler.h"
#include "AIO.h"
#include "airCooler.h"
#include "psu.h"

#include <QObject>
#include <QFuture>
#include <QMap>
#include <QList>

using namespace std;

static void toLower(string str);
static void insertRAMBySpeed(QList<RAM*> v, RAM *toInsert);
static void insertPSUByWattage(QList<PSU*> v, PSU *toInsert);

class dataHolder : public QObject
{
    Q_OBJECT
private:
    QString m_dbDirectory;
    QMap<QString, QList<CPU*>> cpuMap; // Intel / AMD / CoreCount
    QMap<QString, QList<GPU*>> gpuMap;
    QMap<QString, QList<motherboard*>> moboMap; // Formfactors, intel/amd, ddr? pcie?
    QMap<QString, QList<RAM*>> ramMap;
    QMap<QString, QList<storage*>> storageMap;
    QMap<QString, QList<PSU*>> psuMap; // Price, wattage (under 600, 600-1000, over 1000), form factor
    QMap<QString, QList<pcCase*>> caseMap; // Formfactors
    QMap<QString, QList<cooler*>> coolerMap; //aio/air, socket compatibility

public:
    explicit dataHolder(QString dir, QObject *parent = nullptr);
    ~dataHolder();
    QString getDir();

    // For unit tests
    QMap<QString, QList<CPU*>> *CPUMap();
    QMap<QString, QList<GPU*>> *GPUMap();
    QMap<QString, QList<motherboard*>> *MOBOMap();
    QMap<QString, QList<RAM*>> *RAMMap();
    QMap<QString, QList<storage*>> *STORAGEMap();
    QMap<QString, QList<PSU*>> *PSUMap();
    QMap<QString, QList<pcCase*>> *CASEMap();
    QMap<QString, QList<cooler*>> *COOLERMap();

    void initialize();

    void addCPU(CPU *toInsert);
    CPU* removeCPU();
    void clearCPUMaps();

    void addGPU(GPU *toInsert);
    GPU* removeGPU();
    void clearGPUMaps();

    void addMotherboard(motherboard *toInsert, string purpose = "");
    motherboard* removeMobo();
    void clearMoboMaps();

    void addRAM(RAM *toInsert);
    RAM* removeRAM();
    void clearRAMMaps();

    void addStorage(storage *toInsert);
    storage* removeStorage();
    void clearStorageMaps();

    void addCooler(cooler *toInsert);
    cooler* removeCooler();
    void clearCoolerMaps();

    void addPSU(PSU *toInsert);
    PSU* removePSU();
    void clearPSUMaps();

    void addCase(pcCase *toInsert);
    pcCase* removeCase();
    void clearCaseMaps();

    void testMoboCompatibility(CPU *cpu);
    void testMoboCompatibility(RAM *ram);
    void testMoboCompatibility(cooler *cooler);
    void testMoboCompatibility(storage *storage);

    void testCaseCompatibility(motherboard *mobo);
    void testCaseCompatibility(storage *storage);
    void testCaseCompatibility(GPU *gpu);
    void testCaseCompatibility(cooler *cooler);
    // void testCaseCompatibility(PSU *psu); future addition

    void testPSUCompatibility(QList<CPU*>, QList<GPU*> gpus);

signals:
    // Motherboard related
    void cpuCompatibility(CPU *cpu);
    void ramCompatibility(RAM *ram);
    void coolerCompatibility(cooler *cooler);
    void storageCompatibility(storage *storage);

    // Case related
    void motherboardCompatibility(motherboard *mobo);
    void storageSpaceAvailable(storage *storage);
    void gpuCompatibility(GPU *gpu);
    void coolerSpaceAvailable(cooler *cooler);

    // PSU related
    void psuCompatibility(QList<CPU*> cpus, QList<GPU*> gpus);


public slots:
};

static void toLower(string str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return std::tolower(c);});
}

static void insertRAMBySpeed(QList<RAM*> *v, RAM* toInsert)
{
    int index = 0;
    if (v->isEmpty())
    {
        v->append(toInsert);
        return;
    }
    for (RAM* ram : *v)
    {
        if (toInsert->getSpeed() >= ram->getSpeed())
            index++;
        else
            break;
    }
    v->insert(v->begin() + index, toInsert);
}

static void insertPSUByWattage(QList<PSU*> *v, PSU *toInsert)
{
    int index = 0;
    if (v->isEmpty())
    {
        v->append(toInsert);
        return;
    }
    for (PSU* psu : *v)
    {
        if (toInsert->getWattage() >= psu->getWattage())
            index++;
        else
            break;
    }
    v->insert(v->begin() + index, toInsert);
}

#endif // DATAHOLDER_H
