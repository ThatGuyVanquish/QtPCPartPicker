#ifndef DATAHOLDER_H
#define DATAHOLDER_H

#include "cooler.h"
#include "CPU.h"
#include "GPU.h"
#include "motherboard.h"
#include "pcCase.h"
#include "RAM.h"
#include "storage.h"

#include <QObject>
#include <QFuture>
#include <QMap>
#include <QList>

using namespace std;

template<typename T>
    void eraseFrom(QList<T> vec, T toRemove)
    {
        vec.erase(std::find(vec.begin(), vec.end(), toRemove));
    }

static void toLower(string str);
static void insertRAMBySpeed(QList<RAM*> v, RAM* toInsert);

class dataHolder : public QObject
{
    Q_OBJECT
private:
    QMap<string, QList<CPU*>> cpuMap; // Intel / AMD / CoreCount
    QMap<string, QList<GPU*>> gpuMap;
    QMap<string, QList<motherboard*>> moboMap; // Formfactors, intel/amd, ddr? pcie?
    QMap<string, QList<RAM*>> ramMap;
    QMap<string, QList<storage*>> storageMap;
    QMap<string, QList<pcCase*>> caseMap; // Formfactors
    QMap<string, QList<cooler*>> coolerMap; //aio/air, socket compatibility

public:
    explicit dataHolder(QObject *parent = nullptr);
    ~dataHolder();

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

public slots:
};

static void toLower(string str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return std::tolower(c);});
}

static void insertRAMBySpeed(QList<RAM*> v, RAM* toInsert)
{
    int index = 0;
    for (RAM* ram : v)
    {
        if (toInsert->getSpeed() >= ram->getSpeed())
            index++;
        else
            break;
    }
    v.insert(v.begin() + index, toInsert);
}

#endif // DATAHOLDER_H
