#include "../../include/Logic/specbuilder.h"

specbuilder::specbuilder(dataHolder *db, QObject *parent)
    : m_db(db),
      QObject{parent}
{
    m_comp = new Compatibility(db);
}

void specbuilder::mining(int budget)
{
    int remaining = budget;
    QString desiredCPU = requests();
    CPU *cpu;
    QList<GPU*> gpus;
    motherboard *mobo;
    int moboBudget = 0.2 * budget;
    RAM *ram;
    cooler *cooler;
    QList<storage*> drives;
    PSU *psu;
    pcCase *pcCase;
    int caseBudget = budget * 0.1;
    drives.append(m_db->STORAGEMap()->value("Price").at(0));
    remaining -= drives.at(0)->getPrice();
    int firstBudget = budget;
    do {
        firstBudget = firstBudget * 0.35;
        cpu = nullptr;
        ram = nullptr;
        cooler = nullptr;
        mobo = m_db->findMobo(moboBudget, false, desiredCPU, "mining");
        if (mobo == nullptr)
        {
            drives.clear();
            emit specs(nullptr, gpus, nullptr, nullptr, drives, nullptr, nullptr, nullptr);
            return;
        }
        if (!m_comp->testCompatibility(mobo, drives.at(0)))
        {
            moboBudget = mobo->getPrice() - 1;
            firstBudget = -1;
            continue;
        }
        firstBudget -= mobo->getPrice();

        cpu = m_db->findCPU(firstBudget, desiredCPU, mobo->getSocket(),  "mining");
        if (cpu == nullptr || !m_comp->testCompatibility(mobo, cpu))
        {
            moboBudget = mobo->getPrice() - 1;
            firstBudget = -1;
            continue;
        }
        firstBudget -= cpu->getPrice();

        ram = m_db->findRAM(firstBudget, true, mobo->getRAMVersion());
        if (ram == nullptr || !m_comp->testCompatibility(mobo, ram) || firstBudget <= 0)
        {
            moboBudget = mobo->getPrice() - 1;
            firstBudget = -1;
            continue;
        }
        firstBudget -= ram->getPrice();

        if (!cpu->includesCooler())
        {
            cooler = m_db->findCooler(firstBudget, mobo->getSocket(), cpu->getTDP());
            if (cooler == nullptr || !m_comp->testCompatibility(mobo, cooler))
            {
                moboBudget = mobo->getPrice() - 1;
                firstBudget = -1;
                continue;
            }
            firstBudget -= cooler->getPrice();
        }
        else
            cooler = nullptr;
    }
    while(firstBudget < 0);

    remaining -= budget * 0.35 - firstBudget;

    int secondBudget = budget * 0.15;
    do
    {
        psu = nullptr;
        secondBudget = budget * 0.15;
        pcCase = m_db->findCase(caseBudget, "mining", mobo, gpus, cooler);
    if (pcCase == nullptr)
    {
        drives.clear();
        emit specs(nullptr, gpus, nullptr, nullptr, drives, nullptr, nullptr, nullptr);
        return;
    }
    if (!m_comp->testCompatibility(pcCase, mobo) || !m_comp->testCompatibility(pcCase, drives.at(0)) ||
            !m_comp->testCompatibility(pcCase, cooler))
    secondBudget -= pcCase->getPrice();
    psu = m_db->findPSU(secondBudget, "mining");
    if (psu == nullptr)
    {
        caseBudget = pcCase->getPrice() - 1;
        secondBudget = -1;
        continue;
    }
    secondBudget -= psu->getPrice();
    }
    while (secondBudget < 0);

    remaining -= budget * 0.15 - secondBudget;

    gpus = m_db->findGPUs(remaining, "mining", pcCase->getExpansionSlots(),
                          pcCase->getMaxGPULength(), pcCase->getMaxGPUHeight(),
                          mobo->getPCIeSlots(), psu->getWattage() - cpu->getTDP());

    emit specs(cpu, gpus, mobo, ram, drives, cooler, psu, pcCase);
}

void specbuilder::server(int budget)
{
    int remaining = budget;
    QString desiredCPU = requests();
    CPU *cpu;
    int cpuBudget = budget * 0.2;
    QList<GPU*> gpus;
    motherboard *mobo;
    RAM *ram;
    cooler *cooler;
    QList<storage*> drives;
    PSU *psu;
    int psuBudget = budget * 0.1;
    pcCase *pcCase;
    int firstBudget;
    do {
        firstBudget = budget * 0.4;
        mobo = nullptr;
        ram = nullptr;
        cooler = nullptr;
        cpu = m_db->findCPU(cpuBudget, desiredCPU, "", "server");
        if (cpu == nullptr)
        {
            emit specs(nullptr, gpus, nullptr, nullptr, drives, nullptr, nullptr, nullptr);
            return;
        }
        firstBudget -= cpu->getPrice();

        int coolerBudget = cpuBudget - cpu->getPrice();
        if (!cpu->includesCooler())
        {
            cooler = m_db->findCooler(coolerBudget, cpu->getSocket(), cpu->getTDP());
            if (cooler == nullptr)
            {
                cpuBudget = cpu->getPrice() - 1;
                firstBudget = -1;
                continue;
            }
        }
        if (cooler != nullptr)
            firstBudget -= cooler->getPrice();
        int moboBudget = budget * 0.3 - (cpu->getPrice() + cooler->getPrice());
        mobo = m_db->findMobo(moboBudget, false, desiredCPU, cpu->getSocket());
        if (mobo == nullptr)
        {
            cpuBudget = cpu->getPrice() - 1;
            firstBudget = -1;
            continue;
        }
        firstBudget -= mobo->getPrice() + cpu->getPrice();

        ram = m_db->findRAM(firstBudget, true, mobo->getRAMVersion());
        if (ram == nullptr || !m_comp->testCompatibility(mobo, ram) || firstBudget <= 0)
        {
            moboBudget = mobo->getPrice() - 1;
            firstBudget = -1;
            continue;
        }
        firstBudget -= ram->getPrice();
    }
    while(firstBudget < 0);

    remaining -= budget * 0.4 - firstBudget;

    int secondBudget;
    do
    {
        secondBudget = budget * 0.2;
        pcCase = nullptr;
        psu = m_db->findPSU(psuBudget, "server");
        if (psu == nullptr || !m_comp->testCompatibility(psu, cpu, gpus))
        {
            emit specs(nullptr, gpus, nullptr, nullptr, drives, nullptr, nullptr, nullptr);
            return;
        }
        secondBudget -= psu->getPrice();
        pcCase = m_db->findCase(secondBudget, "server", mobo, gpus, cooler);
    if (pcCase == nullptr)
    {
        psuBudget = psu->getPrice() - 1;
        secondBudget = -1;
        continue;
    }
    secondBudget -= pcCase->getPrice();
    }
    while (secondBudget < 0);

    remaining -= budget * 0.2 - secondBudget;

    drives = m_db->findStorage(remaining, "server", pcCase, mobo);

    emit specs(cpu, gpus, mobo, ram, drives, cooler, psu, pcCase);
}

void specbuilder::office(int budget)
{
    int remaining = budget;
    QString desiredCPU = requests();
    CPU *cpu;
    int cpuBudget = budget * 0.4;
    QList<GPU*> gpus;
    motherboard *mobo;
    int moboBudget = budget * 0.15;
    RAM *ram;
    cooler *cooler;
    QList<storage*> drives;
    PSU *psu;
    pcCase *pcCase;
    int caseBudget = budget * 0.1;
    int firstBudget;
    do {
        firstBudget = budget * 0.65;
        mobo = nullptr;
        ram = nullptr;
        cooler = nullptr;
        cpu = m_db->findCPU(cpuBudget, desiredCPU, "", "office");
        if (cpu == nullptr)
        {
            emit specs(nullptr, gpus, nullptr, nullptr, drives, nullptr, nullptr, nullptr);
            return;
        }
        firstBudget -= cpu->getPrice();
        if (!cpu->hasGraphics())
        {
            gpus.append(m_db->GPUMap()->value("Price").at(0));
            firstBudget -= gpus.at(0)->getPrice();
        }

        mobo = m_db->findMobo(moboBudget, false, desiredCPU, cpu->getSocket());
        if (mobo == nullptr || (mobo->getPCIeSlots() == 0 && gpus.size() != 0))
        {
            gpus.clear();
            emit specs(nullptr, gpus, nullptr, nullptr, drives, nullptr, nullptr, nullptr);
            return;
        }
        firstBudget -= mobo->getPrice();

        if (!cpu->includesCooler())
        {
            cooler = m_db->findCooler(firstBudget, cpu->getSocket(), cpu->getTDP());
            if (cooler == nullptr)
            {
                cpuBudget = cpu->getPrice() - 1;
                firstBudget = -1;
                continue;
            }
            firstBudget -= cooler->getPrice();
        }

        ram = m_db->findRAM(firstBudget, true, mobo->getRAMVersion());
        if (ram == nullptr || !m_comp->testCompatibility(mobo, ram))
        {
            cpuBudget = cpu->getPrice() - 1;
            firstBudget = -1;
            continue;
        }
        firstBudget -= ram->getPrice();
    }
    while(firstBudget < 0);

    remaining -= budget * 0.65 - firstBudget;

    int secondBudget;
    do
    {
        secondBudget = budget * 0.25;
        psu = nullptr;
        pcCase = m_db->findCase(caseBudget, "office", mobo, gpus, cooler);
        if (pcCase == nullptr)
        {
            gpus.clear();
            emit specs(nullptr, gpus, nullptr, nullptr, drives, nullptr, nullptr, nullptr);
            return;
        }
        secondBudget -= pcCase->getPrice();

        int tdp = cpu->getTDP();
        if (gpus.size() > 0)
            tdp += gpus.at(0)->getTDP();
        psu = m_db->findPSU(secondBudget, "office", tdp);
        if (psu == nullptr)
        {
            caseBudget = pcCase->getPrice() - 1;
            secondBudget = -1;
            continue;
        }
        secondBudget -= psu->getPrice();
    }
    while (secondBudget < 0);

    remaining -= budget * 0.25 - secondBudget;

    drives = m_db->findStorage(remaining, "office", pcCase, mobo);

    emit specs(cpu, gpus, mobo, ram, drives, cooler, psu, pcCase);
}

void specbuilder::gaming(int budget)
{
    int remaining = budget;
    QString desiredCPU = requests();
    CPU *cpu;
    int cpuBudget = budget * 0.17;
    QList<GPU*> gpus;
    int gpuBudget = budget * 0.4;
    motherboard *mobo;
    int moboBudget = budget * 0.12;
    RAM *ram;
    cooler *cooler;
    int coolerBudget = budget * 0.03;
    QList<storage*> drives;
    PSU *psu;
    pcCase *pcCase;
    int firstBudget;
    do {
        firstBudget = budget * 0.4;
        mobo = nullptr;
        ram = nullptr;
        cooler = nullptr;
        cpu = m_db->findCPU(cpuBudget, desiredCPU, "", "gaming");
        if (cpu == nullptr)
        {
            emit specs(nullptr, gpus, nullptr, nullptr, drives, nullptr, nullptr, nullptr);
            return;
        }
        firstBudget -= cpu->getPrice();

        mobo = m_db->findMobo(moboBudget, false, desiredCPU, cpu->getSocket(), "gaming");
        if (mobo == nullptr)
        {
            cpuBudget = cpu->getPrice() - 1;
            firstBudget = -1;
            continue;
        }
        firstBudget -= mobo->getPrice();

        if (!cpu->includesCooler())
        {
            cooler = m_db->findCooler(coolerBudget, cpu->getSocket(), cpu->getTDP());
            if (cooler == nullptr)
            {
                cpuBudget = cpu->getPrice() - 1;
                firstBudget = -1;
                continue;
            }
            firstBudget -= cooler->getPrice();
        }

        ram = m_db->findRAM(firstBudget, false, mobo->getRAMVersion());
        if (ram == nullptr || ram->getSize() < 8 || !m_comp->testCompatibility(mobo, ram))
        {
            cpuBudget = cpu->getPrice() - 1;
            firstBudget = -1;
            continue;
        }
        firstBudget -= ram->getPrice();
    }
    while(firstBudget < 0);

    remaining -= budget * 0.4 - firstBudget;

    int secondBudget;
    do
    {
        secondBudget = budget * 0.1;
        drives = m_db->findStorage(secondBudget, "gaming", nullptr, mobo);
        if (drives.size() == 0)
        {
            emit specs(nullptr, gpus, nullptr, nullptr, drives, nullptr, nullptr, nullptr);
            return;
        }
    }
    while (secondBudget < 0);

    remaining -= budget * 0.1 - secondBudget;
    int lastBudget;
    do
    {
        lastBudget = remaining;
        int psuBudget;
        int tdp = cpu->getTDP();
        gpus = m_db->findGPUs(gpuBudget, "gaming", -1, -1, -1, mobo->getPCIeSlots());

        if (gpus.at(0) != nullptr)
        {
            int gpuPrice = gpus.at(0)->getPrice();
            lastBudget -= gpuPrice;
            psuBudget = budget * 0.45 - gpuPrice;
            tdp += gpus.at(0)->getTDP();
        }
        else psuBudget = budget * 0.45;
        psu = m_db->findPSU(psuBudget, "gaming", tdp);
        if (psu == nullptr)
        {
            if (gpus.at(0) == nullptr)
            {
                drives.clear();
                emit specs(nullptr, gpus, nullptr, nullptr, drives, nullptr, nullptr, nullptr);
                return;
            }
            gpuBudget = gpus.at(0)->getPrice() - 1;
            lastBudget = -1;
            continue;
        }
        lastBudget -= psu->getPrice();

        pcCase = m_db->findCase(lastBudget, "gaming", mobo, gpus, cooler);
        if (pcCase == nullptr)
        {
            if (gpus.at(0) != nullptr)
            {
                gpuBudget = gpus.at(0)->getPrice() - 1;
                lastBudget = -1;
                continue;
            }
            else
            {
                drives.clear();
                emit specs(nullptr, gpus, nullptr, nullptr, drives, nullptr, nullptr, nullptr);
                return;
            }
        }
    }
    while (lastBudget < 0);
    emit specs(cpu, gpus, mobo, ram, drives, cooler, psu, pcCase);
}

void specbuilder::build()
{
    cout << "What is the budget of your build?\r\n";
    string temp;
    cin >> temp;
    int budget = atoi(temp.c_str());
    if (budget <= 0)
        return;
    cout << "What is the purpose of your build?\r\n";
    cin >> temp;
    QString purpose = QString::fromStdString(temp).simplified().toLower();
    if (purpose == "gaming")
        gaming(budget);
    else if (purpose == "mining")
        mining(budget);
    else if (purpose == "office")
        office(budget);
    else if (purpose == "server")
        server(budget);
    return;
}

QString requests()
{
    string requests;
    cout << "Per CPU, do you prefer Intel or AMD?\r\n";
    cin >> requests;
    return QString::fromStdString(requests).simplified().toLower();
}
