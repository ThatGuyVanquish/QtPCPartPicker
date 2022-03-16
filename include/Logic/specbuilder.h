#ifndef SPECBUILDER_H
#define SPECBUILDER_H

#include "compatibility.h"

#include <QObject>
#include <iostream>

using namespace std;

class specbuilder : public QObject
{
    Q_OBJECT
private:
    dataHolder *m_db;
    Compatibility *m_comp;

public:
    explicit specbuilder(dataHolder *db, QObject *parent = nullptr);
    void mining(int budget);
    void server(int budget);
    void office(int budget);
    void gaming(int budget);

public slots:
    void build();

signals:
    void specs(CPU *cpu, QList<GPU*> gpus, motherboard *mobo, RAM *ram, QList<storage*> storage, cooler *cooler, pcCase *pcCase);
};

static QString requests();

#endif // SPECBUILDER_H
