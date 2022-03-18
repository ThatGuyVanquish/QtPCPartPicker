#ifndef FILEWRITER_H
#define FILEWRITER_H

#include "dataholder.h"

class fileWriter
{
private:
    dataHolder *m_db;
    QFile m_cpu;
    QFile m_gpu;
    QFile m_mobo;
    QFile m_ram;
    QFile m_storage;
    QFile m_psu;
    QFile m_case;
    QFile m_cooler;

public:
    fileWriter(dataHolder *db);
    ~fileWriter(){}

    void closeFiles();
    int openFiles();

    void cpuBackup(QFile *f);
    void gpuBackup(QFile *f);
    void moboBackup(QFile *f);
    void ramBackup(QFile *f);
    void storageBackup(QFile *f);
    void coolerBackup(QFile *f);
    void psuBackup(QFile *f);
    void caseBackup(QFile *f);

    bool backup ();

    void writeCPU(QFile *target, CPU *cpu);
    void writeGPUs(QFile *target, QList<GPU *> gpus);
    void writeMobo(QFile *target, motherboard *mobo);
    void writeRAM(QFile *target, RAM *ram);
    void writeCooler(QFile *target, cooler *cooler);
    void writeStorage(QFile *target, QList<storage *> drives);
    void writePSU(QFile *target, PSU *psu);
    void writeCase(QFile *target, pcCase *pcCase);

    void writeSpecs(QString target, CPU *cpu, QList<GPU*> gpus, motherboard *mobo,
                    RAM *ram, cooler *cooler, QList<storage*> drives, PSU *psu, pcCase *pcCase);
};


#endif // FILEWRITER_H
