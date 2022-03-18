#include "../../include/Logic/pcpartpicker.h"

pcpartpicker::pcpartpicker(QString dir, QObject *parent)
    : m_db(dir),
      QObject{parent}
{
    m_db.initialize();
    fileReader fr(&m_db);
    fr.restore();
}

void pcpartpicker::run()
{
    specbuilder builder(&m_db);
    while(true)
    {
        cout << "Would you like to get specs for a computer build? Y/N\r\n";
        string ans;
        cin >> ans;
        if (QString::fromStdString(ans).toLower() == "n")
            qFatal("Exiting...");
        else if (QString::fromStdString(ans).toLower() != "y")
            continue;
        specObject specs(&m_db);
        QObject::connect(&builder, &specbuilder::specs, &specs, &specObject::specs);
        builder.build();
        if (QFile(QString::fromStdString(specs.getFileDir())).exists())
            cout << "Click here to open the specsheet file:\r\n" + specs.getFileDir() << "\r\n";
        cout << "\r\n";
    }
}
