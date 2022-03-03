#ifndef TESTING_H
#define TESTING_H

#include <QObject>

class testing : public QObject
{
    Q_OBJECT
public:
    explicit testing(QObject *parent = nullptr);

signals:

};

#endif // TESTING_H
