#ifndef SPECOBJECT_H
#define SPECOBJECT_H

#include "../Database/dataholder.h"
#include "../Database/filewriter.h"

#include <QObject>
#include <QDate>
#include <iostream>

using namespace std;

class specObject : public QObject
{
    Q_OBJECT

private:
    fileWriter m_fw;
    QString m_name;
    QDateTime m_creation;

public:
    explicit specObject(dataHolder *db, QObject *parent = nullptr);

public slots:
    void specs(CPU *cpu, QList<GPU*> gpus, motherboard *mobo, RAM *ram, QList<storage*> drives, cooler *cooler, PSU *psu, pcCase *pcCase);

};

#endif // SPECOBJECT_H
