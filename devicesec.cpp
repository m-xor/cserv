#include "devicesec.h"
#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort>
#include <QList>
#include <QDebug>
#include <QByteArray>


static QSerialPortInfo currentDevice;
static QSerialPort currentPort;

void DeviceSec::populateDeviceList(QComboBox *combo)
{
    combo->clear();
    combo->addItem("");
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        combo->addItem(info.description());
    }
}

void DeviceSec::setDescriptors(int ind, QLabel *mnf, QLabel *sn)
{
    if(ind < 1) {
        mnf->setText("N/A");
        sn->setText("N/A");
    } else {
        currentDevice = QSerialPortInfo::availablePorts().value(ind-1);
        mnf->setText(currentDevice.manufacturer());
        sn->setText(currentDevice.serialNumber());
    }
}

bool DeviceSec::connectCurrentDevice()
{
    currentPort.setPort(currentDevice);
    return currentPort.open(QIODevice::ReadWrite);
}

void DeviceSec::disconnectCurrentDevice()
{
    currentPort.close();
}

QString DeviceSec::getDeviceName()
{
    return currentDevice.description();
}

QString DeviceSec::getDeviceSN()
{
    return currentDevice.serialNumber();
}

QString DeviceSec::exchangeData(const QString& command)
{
    QString response;
    qint64 count = currentPort.write(command.toUtf8());

    if(count==-1 || count!=command.toUtf8().size()) {
        response = "Write error\n";
        qDebug() << response;
        return response;
    } else if(!currentPort.waitForBytesWritten(100)) {
        response = "Write timeout\n";
        qDebug() << response;
        return response;
    }

//    qDebug() << command << ":" << count << "/" << command.length() << endl;

    QByteArray data = currentPort.readAll();
    while(currentPort.waitForReadyRead(100)) {
        data.append(currentPort.readAll());
    }
    if(currentPort.error()!=QSerialPort::NoError && !data.isEmpty()) {
        response = data;
    } else {
        response = "Read error\n";
    }


    return response;
}
