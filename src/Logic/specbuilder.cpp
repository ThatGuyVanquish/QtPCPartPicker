#include "../../include/Logic/specbuilder.h"

specbuilder::specbuilder(dataHolder *db, QObject *parent)
    : m_db(db),
      QObject{parent}
{}

void specbuilder::mining(int budget)
{
    QStringList requestList = requests();

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

void specbuilder::overclocking(int budget)
{
    // logic here
    // emit specs(CPU *cpu, GPU *gpu, motherboard *mobo, RAM *ram, storage *storage, cooler *cooler, pcCase *pcCase)
}

void specbuilder::general(int budget)
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
    else if (purpose == "overclocking")
        overclocking(budget);
    else if (purpose == "server")
        server(budget);
    else
        general(budget);
    return;
}


QStringList requests()
{
    cout << "Do you have any special requests?\r\n" <<
            "For example, RAM version, Intel or AMD, preferred GPU manufacturer?\r\n" <<
            "WRITE: DDRx | CPU INTEL or CPU AMD | GPU INTEL or GPU AMD or GPU NVIDIA\r\n" <<
            "STORAGE MIN size and\\or STORAGE MAX size | LONGEVITY\r\n" <<
            "Make sure to have a | between requests";
    string requests;
    cin >> requests;
    QStringList requestList = QString(requests.c_str()).split("|");
    foreach(QString val, requestList)
        val = val.simplified();
    return requestList;
}
