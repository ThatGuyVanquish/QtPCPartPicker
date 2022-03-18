#ifndef DATAHOLDER_H
#define DATAHOLDER_H

#include "../PC_Parts/CPU/cpu.h"
#include "../PC_Parts/CPU/intelcpu.h"
#include "../PC_Parts/CPU/amdcpu.h"
#include "../PC_Parts/GPU/gpu.h"
#include "../PC_Parts/GPU/intelgpu.h"
#include "../PC_Parts/GPU/amdgpu.h"
#include "../PC_Parts/GPU/nvidiagpu.h"
#include "../PC_Parts/Motherboard/motherboard.h"
#include "../PC_Parts/RAM/ram.h"
#include "../PC_Parts/Cooler/cooler.h"
#include "../PC_Parts/Cooler/aio.h"
#include "../PC_Parts/Cooler/aircooler.h"
#include "../PC_Parts/PSU/psu.h"
#include "../PC_Parts/Storage/storage.h"
#include "../PC_Parts/Storage/hdd.h"
#include "../PC_Parts/Storage/satassd.h"
#include "../PC_Parts/Storage/m2ssd.h"
#include "../PC_Parts/Case/pccase.h"

#include <QObject>
#include <QDebug>
#include <QMap>
#include <QList>
#include <QVariantMap>
#include <QVariant>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QIODevice>
#include <fstream>

using namespace std;

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

    QList<GPU*> findGPUs(int budget, int caseSlots, int maxLength, int maxHeight, int moboSlots, int wattage, QList<GPU*> gpuList, int index);
    QList<storage*> findHDDs(int budget, int hddSlots, int sataSlots, QList<storage*> list, int index);

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

    void clearMaps();

    CPU *findCPU(int budget, QString manu, QString socket = "", QString purpose = "");
    QList<GPU*> findGPUs(int budget, QString purpose, int caseSlots, int maxLength, int maxHeight, int moboSlots, int wattage = -1);
    motherboard *findMobo(int budget, bool cheapest, QString manu, QString socket = nullptr, QString purpose = "");
    RAM *findRAM(int budget, bool cheapest, QString version);
    cooler *findCooler(int budget, QString socket, int TDP);
    PSU *findPSU(int budget, QString purpose, int wattage = -1);
    QList<storage*> findStorage(int budget, QString purpose, pcCase *pcCase, motherboard *mobo);
    pcCase *findCase(int budget, QString purpose, motherboard *mobo, QList<GPU*> gpus, cooler *cooler = nullptr);


    void testMoboCompatibility(CPU *cpu);
    void testMoboCompatibility(RAM *ram);
    void testMoboCompatibility(cooler *cooler);
    void testMoboCompatibility(storage *storage);

    void testCaseCompatibility(motherboard *mobo);
    void testCaseCompatibility(storage *storage);
    void testCaseCompatibility(GPU *gpu);
    void testCaseCompatibility(cooler *cooler);
    // void testCaseCompatibility(PSU *psu); future addition

    void testPSUCompatibility(CPU *cpu, QList<GPU*> gpus);

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
    void psuCompatibility(CPU *cpu, QList<GPU*> gpus);
};

static void insertRAMBySpeed(QList<RAM *> *v, RAM *toInsert)
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
