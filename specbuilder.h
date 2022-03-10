#ifndef SPECBUILDER_H
#define SPECBUILDER_H

#include "compatibility.h"

#include <iostream>
#include <QObject>

using namespace std;

class specbuilder : public QObject
{
    Q_OBJECT
private:
    dataHolder *m_db;

public:
    explicit specbuilder(dataHolder *db, QObject *parent = nullptr);
    void mining(int budget);
    void server(int budget);
    void office(int budget);
    void gaming(int budget);
    void overclocking(int budget);

public slots:
    void build(int budget, QString purpose);

signals:
    void specs(CPU *cpu, GPU *gpu, motherboard *mobo, RAM *ram, storage *storage, cooler *cooler, pcCase *pcCase);
};

inline void specbuilder::gaming(int budget)
{

}

#endif // SPECBUILDER_H
