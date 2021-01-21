#include "devicewidg.h"

DeviceWidg::DeviceWidg(
        QComboBox   *list,
        QPushButton *refresh,
        QLabel      *mnf,
        QLabel      *sn,
        QPushButton *connect,
        QPushButton *disconnect
        ) :
    list(list),
    refresh(refresh),
    mnf(mnf),
    sn(sn),
    connect(connect),
    disconnect(disconnect)
{
}

QComboBox * DeviceWidg::getListWidg()
{
    return list;
}

QLabel  * DeviceWidg::getMnfWidg()
{
    return mnf;
}

QLabel  * DeviceWidg::getSNWidg()
{
    return sn;
}

void DeviceWidg::listEnabled(bool en)
{
    list->setEnabled(en);
}

void DeviceWidg::refrEnabled(bool en)
{
    refresh->setEnabled(en);
}

void DeviceWidg::conEnabled(bool en)
{
    connect->setEnabled(en);
}

void DeviceWidg::disconEnabled(bool en)
{
    disconnect->setEnabled(en);
}
