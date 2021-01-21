#ifndef DEVICEWIDG_H
#define DEVICEWIDG_H

#include <QComboBox>
#include <QPushButton>
#include <QLabel>

class DeviceWidg
{
public:
    DeviceWidg(
            QComboBox   *list,
            QPushButton *refresh,
            QLabel      *mnf,
            QLabel      *sn,
            QPushButton *connect,
            QPushButton *disconnect
            );

    QComboBox * getListWidg();
    QLabel  * getMnfWidg();
    QLabel  * getSNWidg();
    void listEnabled(bool en);
    void refrEnabled(bool en);
    void conEnabled(bool en);
    void disconEnabled(bool en);

private:
    QComboBox   *list;
    QPushButton *refresh;
    QLabel      *mnf;
    QLabel      *sn;
    QPushButton *connect;
    QPushButton *disconnect;
};

#endif // DEVICEWIDG_H
