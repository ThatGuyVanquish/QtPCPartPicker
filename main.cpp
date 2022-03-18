#include <QCoreApplication>

#include "include/Logic/pcpartpicker.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    pcpartpicker app("/home/nave/Documents/QtProjects/PCPartPicker/database");
    app.run();
    return a.exec();
}
