#ifndef PCPARTPICKER_H
#define PCPARTPICKER_H

#include "specbuilder.h"
#include "specobject.h"
#include "../Database/filereader.h"

#include <QObject>
#include <iostream>

using namespace std;

class pcpartpicker : public QObject
{
    Q_OBJECT
private:
    dataHolder m_db;

public:
    explicit pcpartpicker(QString dir, QObject *parent = nullptr);
    void run();

};

#endif // PCPARTPICKER_H
