#include "CPU.h"

class intelCPU: public CPU
{
    private:
        bool _unlocked;

    public:
        intelCPU(QString model, QString socket, int cores, double base, int l2, int l3, int lanes, int tdp, int price, bool igpu = true, bool cooler = false, int threads = -1, double boost = -1, bool unlocked = false):
        CPU(model, socket, cores, base, l2, l3, lanes, tdp, price, igpu, cooler, threads, boost),
        _unlocked(unlocked)
        {};
        ~intelCPU(){};
        
        bool isUnlocked() {return _unlocked;}

        QString getManu() {return "Intel";}

        string toString()
        {
            return "Manufacturer: Intel\n" + CPU::toString() + "Unlocked: " + (_unlocked ? "Yes" : "No") + "\n";
        }
};
