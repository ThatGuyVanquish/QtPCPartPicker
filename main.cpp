#include <QCoreApplication>

#include "include/Logic/pcpartpicker.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    dataHolder db("/home/nave/Documents/QtProjects/PCPartPicker/database");
//    db.initialize();
//    fileReader fr(&db);
//    fr.restore();
//    CPU *cpu = db.findCPU(100, "Intel", "", "gaming");
//    std::cout << "CPU Found is " + cpu->getModel().toStdString() << endl;

    pcpartpicker app("/home/nave/Documents/QtProjects/PCPartPicker/database");
    app.run();
    return a.exec();
}
