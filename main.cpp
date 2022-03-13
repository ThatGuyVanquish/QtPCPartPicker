//#include "Test/include/dbtests.h"

#include <QCoreApplication>
#include <QList>
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int *test = new int(5);
    cout << "Is this even working?" << endl;
    QList<int*> trying({test, test});
    cout << trying.size() << endl;
    for(int *key : trying)
    {
        cout << "testing 123" << endl;
        cout << "value is" << to_string(*key) << endl;
    }
    return a.exec();
}
