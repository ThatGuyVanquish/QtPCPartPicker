#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "dataholder.h"

enum Part {cpu, gpu, mobo, ram, Storage, Cooler, PCCase};

class fileWriter
{
    private:
        dataHolder* _db;
    public:
        fileWriter(dataHolder* db): _db(db){}
        ~fileWriter(){}

        void backUp ()
        {
            CPU* cpuToWrite = _db->removeCPU();
            while (cpuToWrite != nullptr)
            {   
                // write to cpu file
                delete cpuToWrite;
                cpuToWrite = _db->removeCPU();
            }   

            GPU* gpuToWrite = _db->removeGPU();
            while (gpuToWrite != nullptr)
            {
                // write to gpu file
                delete gpuToWrite;
                gpuToWrite = _db->removeGPU();
            }

            motherboard* moboToWrite = _db->removeMobo();
            while (moboToWrite != nullptr)
            {
                // write to mobo file
                delete moboToWrite;
                moboToWrite = _db->removeMobo();
            }

            RAM* ramToWrite = _db->removeRAM();
            while (ramToWrite != nullptr)
            {
                // write to ram file
                delete ramToWrite;
                ramToWrite = _db->removeRAM();
            }
            
            storage* driveToWrite = _db->removeStorage();
            while (driveToWrite != nullptr)
            {
                // write to storage file
                delete driveToWrite;
                driveToWrite = _db->removeStorage();
            }

            cooler* coolerToWrite = _db->removeCooler();
            while (coolerToWrite != nullptr)
            {
                // write to cooler filer
                delete coolerToWrite;
                coolerToWrite = _db->removeCooler();
            }

            pcCase* caseToWrite = _db->removeCase();
            while (caseToWrite != nullptr)
            {
                delete caseToWrite;
                caseToWrite = _db->removeCase();
            }
        }
};
