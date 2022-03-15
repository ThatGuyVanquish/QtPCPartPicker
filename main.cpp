//#include "Test/include/dbtests.h"
#include "Test/include/specbuildertests.h"
#include <QCoreApplication>
#include <QList>
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    specBuilderTests f("/home/nave/Documents/QtProjects/PCPartPicker/Test");
    dataHolder h("/home/nave/Documents/QtProjects/PCPartPicker/Test/");
    f.generate(&h);
    f.backup2(&h);
    return a.exec();
}
