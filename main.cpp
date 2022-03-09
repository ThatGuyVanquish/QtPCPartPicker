#include "dbtests.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QFile f;
    if (f.isOpen())
        qInfo() << "Testing";
    else
        qInfo() <<"yea";
    return a.exec();
}
