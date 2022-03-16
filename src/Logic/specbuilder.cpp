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
    QList<storage*> storage;
    PSU *psu;
    pcCase *pcCase;
    int caseBudget = budget * 0.1;
    storage.append(m_db->STORAGEMap()->value("Price").at(0));
    remaining -= storage.at(0)->getPrice();
    int firstBudget = budget;
    do {
        firstBudget = firstBudget * 0.35;
        mobo = m_db->findMobo(moboBudget, false, desiredCPU); // motherboard *findMobo(int budget, bool cheapest, QString manu)
        firstBudget -= mobo->getPrice();
        if (mobo == nullptr)
        {
            storage.clear();
            emit specs(nullptr, gpus, nullptr, nullptr, storage, nullptr, nullptr);
            return;
        }
        if (!m_comp->testCompatibility(mobo, storage.at(0)))
        {
            moboBudget = mobo->getPrice() - 1;
            continue;
        }
        cpu = m_db->findCPU(firstBudget, true, desiredCPU); // CPU *findCPU(int budget, bool cheapest, QString manu)
        firstBudget -= cpu->getPrice();
        if (cpu == nullptr || !m_comp->testCompatibility(mobo, cpu))
        {
            moboBudget = mobo->getPrice() - 1;
            continue;
        }
        ram = m_db->findRAM(firstBudget, true, mobo->getRAMVersion()); // RAM *findRAM(int budget, bool cheapest, QString version)
        firstBudget -= ram->getPrice();
        if (ram == nullptr || !m_comp->testCompatibility(mobo, ram) || firstBudget <= 0)
        {
            moboBudget = mobo->getPrice() - 1;
            continue;
        }
        if (!cpu->includesCooler())
        {
            cooler = m_db->findCooler(firstBudget, true, mobo->getSocket(), cpu->getTDP()); // cooler *findCooler(int budget, bool cheapest, QString socket, int TDP)
            firstBudget -= cooler->getPrice();
            if (cooler == nullptr || !m_comp->testCompatibility(mobo, cooler))
                moboBudget = mobo->getPrice() - 1;
                continue;
        }
        else
            cooler = nullptr;
        if (firstBudget < 0)
            moboBudget = mobo->getPrice() - 1;
    }
    while(firstBudget < 0);
    remaining -= budget * 0.35 - firstBudget;
    int secondBudget = budget * 0.15;
    do
    {
        secondBudget = budget * 0.15;
        pcCase = m_db->findCase(caseBudget, mobo, cooler, "mining"); // pcCase *findCase(int budget, bool cheapest, motherboard *mobo, cooler *cooler, QString purpose)
    if (pcCase == nullptr)
    {
        storage.clear();
        emit specs(nullptr, gpus, nullptr, nullptr, storage, nullptr, nullptr);
        return;
    }
    if (!m_comp->testCompatibility(pcCase, mobo) || !m_comp->testCompatibility(pcCase, storage.at(0)) ||
            !m_comp->testCompatibility(pcCase, cooler))
    secondBudget -= pcCase->getPrice();
    psu = m_db->findPSU(secondBudget, "mining"); // PSU *findPSU(int budget, QString purpose)
    if (psu == nullptr)
    {
        caseBudget = pcCase->getPrice() - 1;
        continue;
    }
    secondBudget -= psu->getPrice();
    }
    while (secondBudget < 0);
    remaining -= budget * 0.15 - secondBudget;
    gpus = m_db->findGPUs(remaining, "mining", pcCase->getExpansionSlots(), psu->getWattage(), mobo->getPCIeSlots());
    emit specs(cpu, gpus, mobo, ram, storage, cooler, pcCase);
}

void specbuilder::server(int budget)
{
    // emit specs(CPU *cpu, GPU *gpu, motherboard *mobo, RAM *ram, storage *storage, cooler *cooler, pcCase *pcCase)
}

void specbuilder::office(int budget)
{
    // logic here
    // emit specs(CPU *cpu, GPU *gpu, motherboard *mobo, RAM *ram, storage *storage, cooler *cooler, pcCase *pcCase)
}

void specbuilder::gaming(int budget)
{
    // logic here
    // emit specs(CPU *cpu, GPU *gpu, motherboard *mobo, RAM *ram, storage *storage, cooler *cooler, pcCase *pcCase)
}

void specbuilder::build()
{
    cout << "What is the budget of your build?\r\n";
    string temp;
    cin >> temp;
    int budget = atoi(temp.c_str());
    cout << "What is the purpose of your build?\r\n";
    string purpose;
    cin >> purpose;
    toLower(purpose);
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
    QStringList requestList;
    cout << "Per CPU, do you prefer Intel or AMD?\r\n";
    cin >> requests;
    return QString::fromStdString(requests).simplified();
}
