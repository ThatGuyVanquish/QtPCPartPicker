#include "psu.h"

PSU::PSU(QObject *parent)
    : QObject{parent}
{}

PSU::PSU(QString model, QString modularity, QString formFactor, Efficiency efficiency, int wattage,
         int price, bool fan):
    _model(model),
    _modularity(modularity),
    _ff(formFactor),
    _efficiency(efficiency),
    _wattage(wattage),
    _price(price),
    _fan(fan),
    _canPower(false)
{}

QString PSU::getModel()
{
    return _model;
}

QString PSU::getModularity()
{
    return _modularity;
}

QString PSU::getFormFactor()
{
    return _ff;
}

QString PSU::efficiency()
{
    switch (_efficiency)
    {
        case Efficiency::None:
            return "None";
        case Efficiency::Bronze:
            return "80+ Bronze";
        case Efficiency::Silver:
            return "80+ Silver";
        case Efficiency::Gold:
            return "80+ Gold";
        case Efficiency::Platinum:
            return "80+ Platinum";
        case Efficiency::Titanium:
            return "80+ Titanium";
    }
}

int PSU::getWattage()
{
    return _wattage;
}

bool PSU::hasFan()
{
    return _fan;
}

int PSU::getPrice()
{
    return _price;
}

bool PSU::canPower()
{
    return _canPower;
}

void PSU::resetPower()
{
    _canPower = false;
}

int PSU::setPrice(int price)
{
    if (price < 0)
        return -1;
    _price = price;
    return 1;
}

QMap<QString, QString> PSU::backup()
{
    QMap<QString, QString> ret;
    ret["Model"] = _model;
    ret["Modularity"] = _modularity;
    ret["Form Factor"] = _ff;
    ret["Efficiency"] = efficiency();
    ret["Wattage"] = QString::number(_wattage);
    ret["Fan"] = QString::number(_fan);
    ret["Price"] = QString::number(_price);
    return ret;
}

string PSU::toString()
{
    return
        "Model: " + _model.toStdString() + "\n" +
        "Modularity: " + _modularity.toStdString() + "\n" +
        "Form Factor: " + _ff.toStdString() + "\n" +
        "Efficiency: " + efficiency().toStdString() + "\n" +
        "Wattage: " + to_string(_wattage) + "\n" +
        "Fan: " + (_fan ? "Yes" : "No") + "\n" +
            "MSRP: " + to_string(_price) + "\n";
}

double PSU::effPercentage()
{
    switch (_efficiency)
    {
        case Efficiency::None:
            return 0.7;
        case Efficiency::Bronze:
            return 0.8;
        case Efficiency::Silver:
            return 0.85;
        case Efficiency::Gold:
            return 0.9;
        case Efficiency::Platinum:
            return 0.95;
        case Efficiency::Titanium:
            return 1;
    }
}

void PSU::couldPower(QList<CPU *> cpus, QList<GPU *> gpus)
{
    double eff = effPercentage();
    int powerUsage = 0;
    foreach(CPU* cpu, cpus)
        powerUsage += cpu->getTDP();
    foreach(GPU* gpu, gpus)
        powerUsage += gpu->getTDP();
    _canPower = powerUsage <= _wattage * eff;
}
