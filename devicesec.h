#ifndef DEVICESEC_H
#define DEVICESEC_H

#include <QComboBox>
#include <QLabel>
#include <QString>

class DeviceSec
{
public:

    static void populateDeviceList(QComboBox *combo);
    static void setDescriptors(int ind, QLabel *mnf, QLabel *sn);
    static bool connectCurrentDevice();
    static void disconnectCurrentDevice();
    static QString getDeviceName();
    static QString getDeviceSN();
    static QString exchangeData(const QString& command);

};


#endif // DEVICESEC_H
